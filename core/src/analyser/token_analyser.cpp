#include "code_audit/token_analyser.h"
#include "code_audit/lexer.h"
#include "code_audit/diff.h"

namespace CodeAudit
{

double TokenBasedAnalyser::calcSimilarity(string source, string sample)
{
    Lexer lexer;
    vector<Token> sourceTokens;
    vector<Token> sampleTokens;
    vector<DiffChanges> changes;
    lexer.lex(source, sourceTokens);
    lexer.lex(sample, sampleTokens);
    if(this->tokenOnly)
        diff<Token>(sampleTokens, sourceTokens, changes, [](const Token *a, const Token *b) -> bool { return a->name == b->name; });
    else
        diff<Token>(sampleTokens, sourceTokens, changes, [](const Token *a, const Token *b) -> bool { return a->name == b->name && a->attribute == b->attribute; });
    mergeChanges(changes);
    int keepCount = 0;
    for(auto &p : changes)
        keepCount += p == DIFF_KEP;
    return (double)keepCount / changes.size();
}
}