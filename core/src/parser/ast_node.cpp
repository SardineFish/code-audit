#include "code_audit/parser.h"

namespace CodeAudit
{
namespace SyntaxParser
{

string ASTNode::toString()
{
    return "";
}

TokenNode::TokenNode(){}
TokenNode::TokenNode(Token t)
{
    this->token = t;
}
string TokenNode::toString()
{
    return this->token.name;
}

TypeNode::TypeNode(bool sign, Token type) : sign(sign), type(type){}
string TypeNode::toString()
{
    string str = "";
    if(!this->sign)
        str += "unsigned ";
    str += this->type.attribute;
    for (int i = 0; i < this->pointerLevel;i++)
        str += "*";
    return str;
}

InfixExpr::InfixExpr(string op, Expression* left, Expression* right)
{
    this->op = op;
    this->left = left;
    this->right = right;
}
string InfixExpr::toString()
{
    return "(" + this->left->toString() + this->op + this->right->toString() + ")";
}

string ExpressionStatement::toString()
{
    return this->expression->toString();
}

string BlockNode::toString()
{
    string str = "{\n";
    for(auto & statement : *(this->statements))
    {
        str += statement->toString() + "\n";
    }
    str += "}\n";
    return str;
}

Variable::Variable(Token t)
{
    this->name = t.attribute;
    this->token = t;
}
string Variable::toString()
{
    return this->name;
}

Constant::Constant(Token t)
{
    this->value = t.attribute;
    this->token = t;
}
string Constant::toString()
{
    return this->value;
}

FunctionInvokeNode::FunctionInvokeNode(Token id, ListNode<Expression>* args)
{
    this->id = id;
    this->name = id.attribute;
    this->args = args;
}
string FunctionInvokeNode::toString()
{
    string str = this->name + "(";
    for(auto & arg : *(this->args->list))
    {
        str += arg->toString() + ",";
    }
    return str + ")";
}

string FunctionDefine::toString()
{
    string str = this->type->toString() + " " + this->id->token.attribute + "(";
    for(auto & arg : *(this->args->list))
    {
        str += arg->type->toString() + " " + arg->id->token.attribute + ",";
    }
    str += ")\n";
    str += this->body->toString();
    return str;
}

string ASTTree::toString()
{
    string str = "";
    for(auto & def : *(this->globals))
    {
        str += def->toString() + "\n";
    }
    return str;
}

ReturnStatement::ReturnStatement(Expression* expr)
{
    this->expr = expr;
}
string ReturnStatement::toString()
{
    return "return " + this->expr->toString();
}

ConditionStructure::ConditionStructure(Expression* expr, BlockNode* body): condition(expr), body(body){}


If::If(Expression* a, BlockNode* b) : ConditionStructure(a, b) {}
string If::toString()
{
    string str = "if (" + this->condition->toString() + ")\n" + this->body->toString();
    for(auto & p : *(this->elseif))
    {
        str += "elseif (" + p->condition->toString() + ")\n" + p->body->toString();
    }
    if(this->elseBody != nullptr)
        str += "else\n" + this->elseBody->toString();
    return str;
}

string ForLoop::toString()
{
    string str = "for (";
    if(this->s1)
        str += this->s1->toString();
    str += ";";
    if (this->s2)
        str += this->s2->toString();
    str += ";";
    if(this->s3)
        str += this->s3->toString();
    str += ")\n";
    str += this->body->toString();

    return str;
}

string VariableDefine::toString()
{
    string str = this->type->toString() + " " + this->id->token.attribute;
    if(this->arraySize != nullptr)
        str += "[" + this->arraySize->toString() + "]";
    if(this->initValue != nullptr )
        str += "=" + this->initValue->toString();
    return str;
}

VariableDefine::VariableDefine(TypeNode* type, TokenNode* id, Expression* value, Expression* size)
    : type(type), id(id), initValue(value), arraySize(size){}

string VariableDefStatement::toString()
{
    string str = "";
    for(auto & var : *(this->vars))
    {
        str += var->toString() + ",";
    }
    return str;
}

}
}