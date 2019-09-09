#include "code_audit/parser.h"

namespace CodeAudit
{
namespace SyntaxParser
{

Parser::Parser()
{
}

ASTTree* AST;
void astCallback(ASTTree* ast)
{
    AST = ast;
}

ASTTree* Parser::parse(vector<Token>& tokens)
{
    reset_parser();
    set_tokens(&tokens);
    set_ast_callback(astCallback);
    yyparse();
    auto ast = AST;
    reset_parser();
    AST = nullptr;
    return ast;
}

} // namespace SyntaxParser
}