#include "code_audit/lexer.h"
#include "code_audit/c_lexer.h"
#include <string>

using namespace std;

namespace CodeAudit
{

void tokenCallback(token_t token, void* state)
{
    vector<Token> *tokens = (vector<Token> *)state;
    Token t;
    t.name = string(token.name);
    t.attribute = string(token.attribute);
    t.pos = token.pos;
    tokens->push_back(t);
}

Lexer::Lexer()
{

}

void Lexer::lex(string source, vector<Token>& tokens)
{
    set_token_callback(tokenCallback, &tokens);
    auto cstr = source.c_str();
    lexer(cstr);
}

}