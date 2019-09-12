#include "code_audit/syntax_analyser.h"
#include "code_audit/compare_tree.h"
#include "code_audit/parser.h"
#include "code_audit/lexer.h"
#include "code_audit/auditor.h"
#include <set>
#include <cstdint>

using namespace std;
using namespace CodeAudit::SyntaxParser;

namespace CodeAudit
{

void initAuditors(CodeAudit *auditor);

double SyntaxBasedAnalyser::calcSimilarity(string source, string sample)
{
    auto lexer = new Lexer();
    auto parser = new Parser();
    Lexer::TokenList tokens;
    lexer->lex(source, tokens);
    auto sourceAST = parser->parse(tokens);
    tokens.clear();
    lexer->lex(sample, tokens);
    auto sampleAST = parser->parse(tokens);
    auto srcTree = createDiffTree(sourceAST);
    auto dstTree = createDiffTree(sampleAST);
    auto similarity = srcTree->compareTo(dstTree);
    similarity = dstTree->compareTo(srcTree);
    return similarity;
}

vector<Vulnerability> SyntaxBasedAnalyser::audit(string source)
{
    CodeAudit *auditor = new CodeAudit;
    auto sourceCode = new SourceCode(source);
    initAuditors(auditor);
    auto vulns = auditor->audit(sourceCode);
    return vulns;
}

vector<Vulnerability> SyntaxBasedAnalyser::audit(SourceCode *source)
{
    CodeAudit *auditor = new CodeAudit;
    initAuditors(auditor);
    vector<Vulnerability> vulns = auditor->audit(source);
    delete auditor;
    return vulns;
}

inline const char* overflowPosition(VariableTracker* var)
{
    if(getTag<HeapAlloc>(var))
        return "heap";
    else if (getTag<StackAlloc>(var))
        return "stack";
    return "memory";
}

inline bool bufferOverflowAudit(string &description, Context *context, Expression *dst, Expression *src, int length = 0)
{
    char buffer[1024];
    auto argDst = extractVariable(dst, context);
    auto argSrc = extractVariable(src, context);
    auto sizeDst = getTag<ArrayVar>(argDst);
    auto sizeSrc = getTag<ArrayVar>(argSrc);
    // sizeof(dst) < sizeof(src) || sizeof(dst) < cpy_len || sizeof(src) < cpy_len
    if(sizeDst && sizeSrc && sizeDst->size < sizeSrc->size)
    {
        sprintf(buffer, "'%s' is larger than '%s', overflow will happen on %s.", argSrc->name.c_str(), argDst->name.c_str(), overflowPosition(argDst));
        description = string(buffer);
        return true;
    }
    else if (sizeDst && sizeDst->size < length)
    {
        sprintf(buffer, "Destination '%s' is smaller than size: %d, overflow will happen on %s.", argDst->name.c_str(), length, overflowPosition(argDst));
        description = string(buffer);
        return true;
    }
    else if (sizeSrc && sizeSrc->size < length)
    {
        sprintf(buffer, "Source '%s' is smaller than size: %d, overflow will happen on %s.", argSrc->name.c_str(), length, overflowPosition(argSrc));
        description = string(buffer);
        return true;
    }
    auto constSrc = extractConstant(src);
    if (sizeDst && constSrc && sizeDst->size < constSrc->value.size())
    {
        sprintf(buffer, "%s is larger than '%s', overflow will happen on %s.", constSrc->value.c_str(), argDst->name.c_str(), overflowPosition(argDst));
        description = string(buffer);
        return true;
    }
    else if(argDst)
    {
        sprintf(buffer, "Usage of unsafe function, memory overflow might happen on %s.", overflowPosition(argDst));
        description = string(buffer);
        return true;
    }
    else if (argSrc)
    {
        sprintf(buffer, "Usage of unsafe function, memory overflow might happen on %s.", overflowPosition(argSrc));
        description = string(buffer);
        return true;
    }
    
    return false;
}

void initAuditors(CodeAudit *auditor)
{
    auto functionAuditor = new FunctionAuditor(1);
    auto operatorAuditor = new OperatorAuditor(1);

    functionAuditor->addAuditor("strcpy", [=](vector<Expression *> args, string &description, Context *context) -> bool {
        return bufferOverflowAudit(description, context, args[0], args[1]);
    });
    functionAuditor->addAuditor("strncpy", [=](vector<Expression *> args, string &description, Context *context) -> bool {
        return bufferOverflowAudit(description, context, args[0], args[1], evaluate(args[2]));
    });
    functionAuditor->addAuditor("memcpy", [=](vector<Expression *> args, string &description, Context *context) -> bool {
        return bufferOverflowAudit(description, context, args[0], args[1], evaluate(args[2]));
    });
    functionAuditor->addAuditor("strcat", [=](vector<Expression *> args, string &description, Context *context) -> bool {
        return bufferOverflowAudit(description, context, args[0], args[1]);
    });
    functionAuditor->addAuditor("strncat", [=](vector<Expression *> args, string &description, Context *context) -> bool {
        return bufferOverflowAudit(description, context, args[0], args[1], evaluate(args[2]));
    });
    functionAuditor->addAuditor("sprintf", [=](vector<Expression *> args, string &description, Context *context) -> bool {
        return bufferOverflowAudit(description, context, args[0], args[1]);
    });
    functionAuditor->addAuditor("vsprintf", [=](vector<Expression *> args, string &description, Context *context) -> bool {
        return bufferOverflowAudit(description, context, args[0], args[1]);
    });
    functionAuditor->addAuditor("gets", [=](vector<Expression *> args, string &description, Context *context) -> bool {
        return bufferOverflowAudit(description, context, args[0], nullptr);
    });
    functionAuditor->addAuditor("read", [=](vector<Expression *> args, string &description, Context *context) -> bool {
        return bufferOverflowAudit(description, context, args[1], nullptr, evaluate(args[2]));
    });
    functionAuditor->addAuditor("sscanf", [=](vector<Expression *> args, string &description, Context *context) -> bool {
        return bufferOverflowAudit(description, context, args[2], args[0]);
    });
    functionAuditor->addAuditor("fscanf", [=](vector<Expression *> args, string &description, Context *context) -> bool {
        return bufferOverflowAudit(description, context, args[2], nullptr);
    });

    operatorAuditor->addAuditor("=", [=](Expression *lhs, Expression *rhs, string &description, Context *context) -> bool {
        auto lvar = extractVariable(lhs, context);
        if(lvar)
        {
            if (auto call = extractFunctionCall(rhs))
            {
                if (call->name == "malloc" || call->name == "calloc" || call->name == "realloc")
                {
                    addTag(lvar, new HeapAlloc());
                }
            }
        }
    });

    auditor->addAuditor(functionAuditor);
    auditor->addAuditor(operatorAuditor);
}

} // namespace CodeAudit