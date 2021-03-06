#include "code_audit/parser.h"
#include <fstream>
#include <iostream>

using namespace std;
using namespace CodeAudit;
using namespace CodeAudit::SyntaxParser;

int main(int argc, char** argv)
{
    char buffer[8192];
    if (argc > 1)
    {
        fstream fs;
        fs.open(string(argv[1]));
        fs.get(buffer, 8192, EOF);
        fs.close();
    }
    else
    {
        cin.get(buffer, 8192, EOF);
    }
    string source(buffer);

    vector<Token> tokens;
    Lexer lexer;
    Parser parser;

    lexer.lex(source, tokens);
    auto ast = parser.parse(tokens);
    cout << ast->toString();

    return 0;
}