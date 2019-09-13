#include "code_audit/syntax_analyser.h"
#include "code_audit/compare_tree.h"
#include "code_audit/parser.h"
#include "code_audit/lexer.h"
#include "code_audit/auditor.h"
#include <set>
#include <cstdint>
#include <regex>

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

inline bool signOverflowAudit(Expression* expr, string &description, Context *context)
{
    if (auto var = extractVariable(expr, context))
    {
        if (var->type->sign)
        {
            char buffer[1024];
            sprintf(buffer, "Use signed interger '%s' as unsigned parameter.", var->name.c_str());
            description = string(buffer);
            return true;
        }
    }
}

void initAuditors(CodeAudit *auditor)
{
    auto bufferOverflowAuditor = new FunctionAuditor(1);
    auto operatorAuditor = new OperatorAuditor(1);
    auto formatAuditor = new FunctionAuditor(1);
    auto intergerOverflowAuditor = new FunctionAuditor(1);

    bufferOverflowAuditor->addAuditor("strcpy", [=](vector<Expression *> args, string &description, Context *context) -> bool {
        return bufferOverflowAudit(description, context, args[0], args[1]);
    });
    bufferOverflowAuditor->addAuditor("strncpy", [=](vector<Expression *> args, string &description, Context *context) -> bool {
        return bufferOverflowAudit(description, context, args[0], args[1], evaluate(args[2]));
    });
    bufferOverflowAuditor->addAuditor("memcpy", [=](vector<Expression *> args, string &description, Context *context) -> bool {
        return bufferOverflowAudit(description, context, args[0], args[1], evaluate(args[2]));
    });
    bufferOverflowAuditor->addAuditor("strcat", [=](vector<Expression *> args, string &description, Context *context) -> bool {
        return bufferOverflowAudit(description, context, args[0], args[1]);
    });
    bufferOverflowAuditor->addAuditor("strncat", [=](vector<Expression *> args, string &description, Context *context) -> bool {
        return bufferOverflowAudit(description, context, args[0], args[1], evaluate(args[2]));
    });
    bufferOverflowAuditor->addAuditor("sprintf", [=](vector<Expression *> args, string &description, Context *context) -> bool {
        return bufferOverflowAudit(description, context, args[0], args[1]);
    });
    bufferOverflowAuditor->addAuditor("vsprintf", [=](vector<Expression *> args, string &description, Context *context) -> bool {
        return bufferOverflowAudit(description, context, args[0], args[1]);
    });
    bufferOverflowAuditor->addAuditor("gets", [=](vector<Expression *> args, string &description, Context *context) -> bool {
        return bufferOverflowAudit(description, context, args[0], nullptr);
    });
    bufferOverflowAuditor->addAuditor("read", [=](vector<Expression *> args, string &description, Context *context) -> bool {
        return bufferOverflowAudit(description, context, args[1], nullptr, evaluate(args[2]));
    });
    bufferOverflowAuditor->addAuditor("sscanf", [=](vector<Expression *> args, string &description, Context *context) -> bool {
        return bufferOverflowAudit(description, context, args[2], args[0]);
    });
    bufferOverflowAuditor->addAuditor("fscanf", [=](vector<Expression *> args, string &description, Context *context) -> bool {
        return bufferOverflowAudit(description, context, args[2], nullptr);
    });

    formatAuditor->addAuditor("printf", [=](vector<Expression *> args, string &description, Context *context) -> bool {
        regex reg("%.");
        smatch match;
        auto format = extractConstant(args[0])->value;
        int idx = 1;
        while(regex_search(format, match, reg))
        {
            auto var = extractVariable(args[idx], context);
            if (!var)
            {
                description = "Arguments missmatch with format strings.";
                return true;
            }
            // %s with non-string
            auto arr = getTag<ArrayVar>(var);
            if (match.str() == "%s" && !((var->type->toString() == "char*") || (var->type->toString() == "char" && getTag<ArrayVar>(var))))
            {
                description = "Non-string variable with format string %s.";
                return true;
            }
            format = match.suffix();
            idx++;
        }
    });

    intergerOverflowAuditor->addAuditor("memcpy", [=](vector<Expression *> args, string &description, Context *context) -> bool {
        return signOverflowAudit(args[2], description, context);
    });
    intergerOverflowAuditor->addAuditor("strncpy", [=](vector<Expression *> args, string &description, Context *context) -> bool {
        return signOverflowAudit(args[2], description, context);
    });
    intergerOverflowAuditor->addAuditor("strncat", [=](vector<Expression *> args, string &description, Context *context) -> bool {
        return signOverflowAudit(args[2], description, context);
    });
    intergerOverflowAuditor->addAuditor("read", [=](vector<Expression *> args, string &description, Context *context) -> bool {
        return signOverflowAudit(args[2], description, context);
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
                    if (int size = evaluate(call->args->list->at(0)))
                        addTag(lvar, new ArrayVar(size));
                }
                if(lvar->type->pointerLevel>0)
                    addTag(lvar, new NullPtr());
            }
            if (auto constant = extractConstant(rhs))
            {
                if (constant->token.name == "null")
                {
                    addTag(lvar, new NullPtr());
                }
            }
            if(evaluateSize(lhs, context) < evaluateSize(rhs, context))
            {
                char buffer[1024];
                sprintf(buffer, "size of '%s' is larger than size of '%s', sign overflow might happen.", rhs->toString().c_str(), lhs->toString().c_str());
                description = string(buffer);
                return true;
            }
        }
    });

    auditor->addAuditor(new Auditor<VariableDefine>(1, [=](VariableDefine *def, string &description, int &pos, Context *context) -> bool {
        auto var = context->findVariable(def->id->token.attribute);
        // Add heap tag to 
        // type* x = malloc(size) or calloc, realloc, etc.
        if (auto call = extractFunctionCall(def->initValue))
        {
            if (call->name == "malloc" || call->name == "calloc" || call->name == "realloc")
            {
                addTag(var, new HeapAlloc());
                if(int size = evaluate(call->args->list->at(0)))
                    addTag(var, new ArrayVar(size));
            }
            // Add nullable tag to:
            // type* x = nullable_func();
            else
            {
                addTag(var, new NullPtr());
            }
        }
        // Add nullable tag to:
        // type* x = NULL;
        if (auto constant = extractConstant(def->initValue))
        {
            if(constant->token.name == "null")
            {
                addTag(var, new NullPtr());
            }
        }
    }));

    auditor->addAuditor(new Auditor<FunctionInvokeNode>(1, [=](FunctionInvokeNode *call, string &description, int &pos, Context *context) -> bool {
        for(auto & arg : *(call->args->list))
        {
            if(auto var = extractVariable(arg, context))
            {
                if(getTag<NullPtr>(var))
                {
                    pos = extractVariable(arg)->token.pos;
                    char buffer[1024];
                    sprintf(buffer, "Use of variable '%s', which could be value of NULL.", var->name.c_str());
                    description = string(buffer);
                    return true;
                }
            }
        }
    }));

    auditor->addAuditor(new Auditor<PrefixExpr>(1, [=](PrefixExpr *expr, string &description, int &pos, Context *context) -> bool {
        if(expr->op.attribute == "*")
        {
            if(auto var = extractVariable(expr->expr, context))
            {
                if (getTag<NullPtr>(var))
                {
                    char buffer[1024];
                    sprintf(buffer, "Dereference pointer '%s', which could be value of NULL.", var->name.c_str());
                    pos = extractVariable(expr->expr)->token.pos;
                    description = string(buffer);
                    return true;
                }
            }
        }
    }));

    auditor->addAuditor(bufferOverflowAuditor);
    auditor->addAuditor(operatorAuditor);
    auditor->addAuditor(formatAuditor);
    auditor->addAuditor(intergerOverflowAuditor);
}

} // namespace CodeAudit