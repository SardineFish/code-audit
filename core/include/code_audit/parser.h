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

class Expression : public ASTNode
{
};

class TypeNode : public Expression
{
  public:
    bool sign = true;
    Token type;
    int pointerLevel = 0;
    TypeNode(bool sign, Token type);
    virtual string toString() override;
};

class StructInit : public Expression
{
  public:
    vector<Expression*>* elements;
    virtual string toString() override;
};

class PrefixExpr : public Expression 
{
  public:
    Token op;
    Expression* expr;
    PrefixExpr(Token op, Expression* expr);
    virtual string toString() override;
};
class SubfixExpr : public Expression
{
  public:
    Token op;
    Expression* expr;
    SubfixExpr(Expression* expr, Token op);
    virtual string toString() override;
};

class ArraySubscript : public Expression
{
  public:
    Expression* target;
    Expression* subscript;
    ArraySubscript(Expression* target, Expression* subscript);
    virtual string toString() override;
};

class TypeCast : public Expression
{
  public:
    TypeNode* type;
    Expression* target;
    TypeCast(TypeNode* type, Expression* target);
    virtual string toString() override;
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

class EmptyStatement : public Statement
{
  public:
    virtual string toString()override {
        return ";";
    }
};

class KeywordStatement : public Statement
{
  public:
    Token keyword;
    KeywordStatement(Token token);
    virtual string toString() override;
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

class VariableDefine : public Expression
{
  public:
    TypeNode* type;
    TokenNode* id;
    Expression* initValue;
    vector<Expression*>* arrayDimensions;
    VariableDefine(TypeNode* type, TokenNode* id, Expression* value);
    virtual string toString() override;
};

class VariableDefStatement : public Statement
{
  public:
    vector<VariableDefine*>* vars = new vector<VariableDefine*>;
    virtual string toString() override;
};

class FunctionDeclare : public Statement
{
  public:
    TypeNode* type;
    TokenNode* id;
    vector<VariableDefine*>* args = new vector<VariableDefine*>;
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
    vector<VariableDefine*>* args;
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

class ASTTree : public ASTNode
{
  public:
    vector<ASTNode*>* globals = new vector<ASTNode*>;
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
