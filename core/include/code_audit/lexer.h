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
};

class Lexer
{
public:
    Lexer();
    void lex(string source, vector<Token>& tokenList);

private:
};
}