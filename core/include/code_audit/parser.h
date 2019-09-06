#pragma once
#include "lexer.h"
#include <string>

using namespace std;
namespace CodeAudit
{
namespace SyntaxParser
{

class ASTNode
{
};

class TokenNode : public ASTNode
{
  public:
    Token token;
};

class StatementNode : ASTNode
{
};

template <class T>
class ListNode : public ASTNode
{
  public:
    vector<T*>* list = new vector<T*>;
};

class BlockNode : public ASTNode
{
  public:
    vector<StatementNode*>* statements = new vector<StatementNode*>;
};

class ExpressionNode : public StatementNode
{
  public:
    ExpressionNode* left;
    ExpressionNode* right;
    TokenNode* op;
};

class VariableNode : public ExpressionNode, public TokenNode
{
  public:
    string name;
};

class FunctionInvokeNode : public ExpressionNode
{
  public:
    string name;
    vector<ExpressionNode*>* args = new vector<ExpressionNode*>;
};

class ParameterNode : public ASTNode
{
  public:
    TokenNode* type;
    TokenNode* id;
};

class FunctionDefine : public ASTNode
{
  public:
    string name;
    TokenNode* type;
    TokenNode* id;
    ListNode<ParameterNode>* args;
    BlockNode* body;
};

class ASTTree : public ASTNode
{
  public:
    vector<FunctionDefine*>* globalDefinitions = new vector<FunctionDefine*>;
};

class Parser
{
  public:
    Parser();
    ASTTree* parse(vector<Token>& tokens);
};

void set_tokens(vector<Token>* tokens);

void set_ast_callback(void (*callback)(ASTTree*));

void reset_parser();

int yyparse();



}
}

