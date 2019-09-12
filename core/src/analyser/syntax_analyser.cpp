#include "code_audit/syntax_analyser.h"
#include "code_audit/compare_tree.h"
#include "code_audit/parser.h"
#include "code_audit/lexer.h"
#include "code_audit/auditor.h"
#include <set>

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

vector<Vulnerability> SyntaxBasedAnalyser::audit(SourceCode*source)
{
    CodeAudit *auditor = new CodeAudit;
    initAuditors(auditor);
    auto vulns = auditor->audit(source);
    return vulns;
}

void initAuditors(CodeAudit* auditor)
{
    auto functionAuditor = new FunctionAuditor(1);
    auto operatorAuditor = new OperatorAuditor(1);

    functionAuditor->addAuditor("strcpy", [=](vector<Expression *> args, string &description, Context *context) -> bool {
        auto argDst = extractVariable(args[0], context);
        auto argSrc = extractVariable(args[1], context);
        auto sizeDst = getTag<ArrayVar>(argDst);
        auto sizeSrc = getTag<ArrayVar>(argSrc);
        if (sizeDst && sizeSrc && sizeDst->size < sizeSrc->size)
        {
            if(getTag<StackAlloc>(argDst))
            {
                description = "Buffer will overflow on stack.";
                return true;
            }
            else if(getTag<HeapAlloc>(argDst))
            {
                description = "Buffer will overflow on heap.";
                return true;
            }
        }
        if (argDst && getTag<StackAlloc>(argDst))
        {
            description = "Buffer might overflow on stack.";
            return true;
        }
        else if (argDst && getTag<HeapAlloc>(argDst))
        {
            description = "Buffer might overflow on heap.";
            return true;
        }
        return false;
    });


    auditor->addAuditor(functionAuditor);
    auditor->addAuditor(operatorAuditor);
}

} // namespace CodeAudit