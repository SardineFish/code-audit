#pragma once

#include <string>
#include <vector>

using namespace std;

namespace CodeAudit
{

struct Token
{
    string name;
    string attribute;
    int pos;
};

class Lexer
{
public:
    typedef vector<Token> TokenList;
    Lexer();
    void lex(string source, vector<Token>& tokenList);
    vector<Token> lex(string source);

private:
};
}