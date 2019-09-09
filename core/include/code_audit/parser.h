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
  public:
    virtual string toString();
};

class TokenNode : public ASTNode
{
  public:
    Token token;
    TokenNode();
    TokenNode(Token t);
    virtual string toString() override;
};

class TypeNode : public ASTNode
{
  public:
    bool sign = true;
    Token type;
    int pointerLevel = 0;
    TypeNode(bool sign, Token type);
    virtual string toString() override;
};

class Expression : public ASTNode
{
};

class InfixExpr : public Expression
{
  public:
    string op;
    Expression* left;
    Expression* right;
    InfixExpr(string op, Expression* left, Expression* right);
    virtual string toString() override;
};

class Statement : public ASTNode
{
};

class ExpressionStatement : public Statement
{
  public:
    Expression* expression;
    virtual string toString() override;
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
    vector<Statement*>* statements = new vector<Statement*>;
    virtual string toString() override;
};

class Variable : public Expression
{
  public:
    string name;
    Token token;
    Variable(Token t);
    virtual string toString() override;
};

class Constant : public Expression
{
  public:
    string value;
    Token token;
    Constant(Token t);
    virtual string toString() override;
};

class FunctionInvokeNode : public Expression
{
  public:
    string name;
    Token id;
    ListNode<Expression>* args;
    FunctionInvokeNode(Token id, ListNode<Expression>* args);
    virtual string toString() override;
};

class ParameterNode : public ASTNode
{
  public:
    TypeNode* type;
    TokenNode* id;
};

class FunctionDefine : public Statement
{
  public:
    string name;
    TypeNode* type;
    TokenNode* id;
    ListNode<ParameterNode>* args;
    BlockNode* body;
    virtual string toString() override;
};

class ReturnStatement : public Statement
{
  public:
    Expression* expr;
    ReturnStatement(Expression* expr);
    virtual string toString() override;
};

class ConditionStructure : public Statement
{
  public:
    Expression* condition;
    BlockNode* body;
    ConditionStructure(Expression* condition, BlockNode* body);
};

class If : public ConditionStructure
{
  public:
    vector<ConditionStructure*>* elseif;
    BlockNode* elseBody;
    If(Expression* condition, BlockNode* body);
    virtual string toString() override;
};

class ForLoop : public Statement
{
  public:
    Expression* s1 = nullptr;
    Expression* s2 = nullptr;
    Expression* s3 = nullptr;
    BlockNode* body;
    virtual string toString() override;
};

class VariableDefine : public Expression
{
  public:
    TypeNode* type;
    TokenNode* id;
    Expression* initValue;
    Expression* arraySize;
    VariableDefine(TypeNode* type, TokenNode* id, Expression* value, Expression* size);
    virtual string toString() override;
};

class VariableDefStatement : public Statement
{
  public:
    vector<VariableDefine*>* vars = new vector<VariableDefine*>;
    virtual string toString() override;
};

class ASTTree : public ASTNode
{
  public:
    vector<Statement*>* globals = new vector<Statement*>;
    virtual string toString() override;
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

} // namespace SyntaxParser
} // namespace CodeAudit
