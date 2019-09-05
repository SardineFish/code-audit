#include <cstdio>
#include <iostream>
#include <fstream>
#include "code_audit/lexer.h"

using namespace std;
using namespace CodeAudit;

void printToken(Token t)
{
    printf("<%s %s>\n", t.name.c_str(), t.attribute.c_str());
}

int main(int argc, char** argv)
{
    char buffer[8192];
    if(argc > 1)
    {
        fstream fs;
        fs.open(string(argv[1]));
        fs.get(buffer, 8192, EOF);
    }
    else
        cin.get(buffer, 8192, EOF);
    Lexer lexer;
    vector<Token> tokens;
    lexer.lex(string(buffer), tokens);

    for(auto &token : tokens)
    {
        printToken(token);
    }

    return 0;
}