#include "code_audit/syntax_analyser.h"
#include "code_audit/compare_tree.h"
#include "code_audit/parser.h"
#include "code_audit/lexer.h"

using namespace CodeAudit::SyntaxParser;

namespace CodeAudit
{

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
} // namespace CodeAudit