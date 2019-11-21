#include "code_audit/parser.h"

namespace CodeAudit
{
namespace SyntaxParser
{

string indent(string input, int level)
{
    string output = "";
    for (int i = 0; i < level;i++)
        output += "  ";
    return output + input + "\n";
}

#define PrintASTItem(STR, NAME, BODY, LEVEL) \
    STR += indent(NAME, LEVEL);              \
    STR += (BODY)->toASTString(LEVEL + 1);

string ASTNode::toString()
{
    return "";
}
string ASTNode::toASTString(int level)
{
    return indent("", level);
}

TokenNode::TokenNode(){}
TokenNode::TokenNode(Token t)
{
    this->token = t;
}
string TokenNode::toString()
{
    return this->token.attribute;
}
string TokenNode::toASTString(int level)
{
    return indent(this->token.attribute, level);
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
string TypeNode::toASTString(int level)
{
    string str = "";
    if(this->sign)
        str += indent("signed: true", level);
    else
        str += indent("signed: false", level);
    str += indent("name: " + this->type.attribute, level);
    str += indent("pointer: " + to_string(this->pointerLevel), level);
    return str;
}

string StructInit::toString()
{
    string str = "{";
    for(auto & element : *(this->elements))
    {
        if(element!=nullptr)
            str += element->toString() + ",";
    }
    return str + "}";
}
string StructInit::toASTString(int level)
{
    string str = indent("elements: ", level);
    for(auto & element : *this->elements)
    {
        if(element != nullptr)
            str += element->toASTString(level + 1);
    }
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
string InfixExpr::toASTString(int level)
{
    string str = indent("infix: " + this->op, level);
    str += this->left->toASTString(level + 1);
    str += this->right->toASTString(level + 1);
    return str;
}

PrefixExpr::PrefixExpr(Token op, Expression* expr): op(op), expr(expr){}
string PrefixExpr::toString()
{
    return "(" + this->op.attribute + "(" + this->expr->toString() + "))";
}
string PrefixExpr::toASTString(int level)
{
    string str = indent("prefix: " + this->op.attribute, level);
    str += this->expr->toASTString(level + 1);
    return str;
}

SubfixExpr::SubfixExpr(Expression* expr, Token op) : expr(expr), op(op){}
string SubfixExpr::toString()
{
    return "((" + this->expr->toString() + ")" + this->op.attribute + ")";
}
string SubfixExpr::toASTString(int level)
{
    string str = indent("subfix: " + this->op.attribute, level);
    str += this->expr->toASTString(level + 1);
    return str;
}

ArraySubscript::ArraySubscript(Expression* target, Expression* subscript) : target(target), subscript(subscript) {}
string ArraySubscript::toString()
{
    return "(" + this->target->toString() + ")[" + this->subscript->toString() + "]";
}
string ArraySubscript::toASTString(int level)
{
    string str = indent("Array subscript", level);
    str += indent("index: ", level + 1);
    str += this->subscript->toASTString(level + 2);
    str += indent("array: ", level + 1);
    str += this->target->toASTString(level + 2);
    return str;
}

TypeCast::TypeCast(TypeNode* type, Expression* target) : type(type), target(target) {}
string TypeCast::toString()
{
    return "(" + this->type->toString() + ")(" + this->target->toString() + ")";
}
string TypeCast::toASTString(int level)
{
    string str = indent("typecast", level);
    str += indent("type: ", level + 1);
    str += this->type->toASTString(level + 2);
    str += indent("expr: ", level + 1);
    str += this->target->toASTString(level + 2);
    return str;
}

string ExpressionStatement::toString()
{
    return this->expression->toString();
}
string ExpressionStatement::toASTString(int level)
{
    string str = indent("statement", level);
    str += this->expression->toASTString(level + 1);
    return str;
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
string BlockNode::toASTString(int level)
{
    string str = indent("block", level);
    for(auto & statement :*this->statements)
        str += statement->toASTString(level + 1);
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
string Variable::toASTString(int level)
{
    return indent("variable: " + this->name, level);
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
string Constant::toASTString(int level)
{
    return indent("constant: " + this->value, level);
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
string FunctionInvokeNode::toASTString(int level)
{
    string str = indent("func-invoke", level);
    str += indent("name: " + this->name, level + 1);
    str += indent("params: ", level + 1);
    for (auto &arg : *(this->args->list))
    {
        str += arg->toASTString(level + 2);
    }
    return str;
}

string FunctionDeclare::toString()
{
    string str = "";
    str += this->type->toString() + " ";
    str += this->id->token.attribute + "(";
    for (auto & arg : *(this->args))
    {
        str += arg->toString() + ",";
    }
    str += ")";
    return str;
}

string FunctionDefine::toString()
{
    string str = this->type->toString() + " " + this->id->token.attribute + "(";
    for(auto & arg : *(this->args))
    {
        str += arg->toString() + ",";
    }
    str += ")\n";
    str += this->body->toString();
    return str;
}
string FunctionDefine::toASTString(int level)
{
    string str = indent("func-define", level);
    str += indent("type:", level + 1);
    str += this->type->toASTString(level + 2);
    str += indent("name: " + this->id->token.attribute, level + 1);
    str += indent("params:", level + 1);
    for (auto &arg : *(this->args))
    {
        str += arg->toASTString(level + 2);
    }
    PrintASTItem(str, "body:", this->body, level + 1);
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
string ASTTree::toASTString(int level)
{
    string str = indent("AST-root", level);
    for (auto &def : *(this->globals))
    {
        str += def->toASTString(level + 1);
    }
    return str;
}

ReturnStatement::ReturnStatement(Expression* expr)
{
    this->expr = expr;
}
string ReturnStatement::toString()
{
    if(!this->expr)
        return "return ;";
    return "return " + this->expr->toString() + ";";
}
string ReturnStatement::toASTString(int level)
{
    string str = indent("return", level);
    str += this->expr->toASTString(level + 1);
    return str;
}

ConditionStructure::ConditionStructure(Expression* expr, BlockNode* body): condition(expr), body(body){}
string ConditionStructure::toASTString(int level)
{
    string str = indent("condition: ", level);
    str += this->condition->toASTString(level + 1);
    PrintASTItem(str, "body:", this->body, level + 1);
    return str;
}


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
string If::toASTString(int level)
{
    string str = indent("if", level);
    str += indent("condition: ", level + 1);
    str += this->condition->toASTString(level + 2);
    str += indent("body: ", level + 1);
    str += this->body->toASTString(level + 2);
    for (auto &p : *(this->elseif))
    {
        PrintASTItem(str, "else-if: ", p, level + 1);
    }
    if(this->elseBody != nullptr)
    {
        PrintASTItem(str, "else:", this->elseBody, level + 1);
    }
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
string ForLoop::toASTString(int level)
{
    string str = indent("for-loop", level);
    str += indent("statement-1: ", level + 1);
    if(this->s1)
        str += this->s1->toASTString(level + 2);
    str += indent("statement-2: ", level + 1);
    if (this->s2)
        str += this->s2->toASTString(level + 2);
    str += indent("statement-3: ", level + 1);
    if (this->s3)
        str += this->s3->toASTString(level + 2);
    PrintASTItem(str, "body:", this->body, level + 1);
    return str;
}

KeywordStatement::KeywordStatement(Token token): keyword(token){}
string KeywordStatement::toString()
{
    return this->keyword.attribute;
}

VariableDefine::VariableDefine(TypeNode* type, TokenNode* id, Expression* value)
    : type(type), id(id), initValue(value)
{
}
string VariableDefine::toString()
{
    string str = this->type->toString() + " ";
    if(this->id)
        str +=this->id->token.attribute;
    for(auto & arr : *(this->arrayDimensions))
    {
        str += "[";
        if(arr != nullptr)
            str += arr->toString();
        str += "]";
    }
    if(this->initValue != nullptr )
        str += "=" + this->initValue->toString();
    return str;
}
string VariableDefine::toASTString(int level)
{
    string str = indent("variable", level);
    if(this->id)
        str += indent("name: " + this->id->token.attribute, level + 1);
    if(!this->arrayDimensions->empty())
    {
        str += indent("array-define", level + 1);
        for (auto &arr : *(this->arrayDimensions))
        {
            str += indent("array-size: ", level + 2);
            str += arr->toASTString(level + 3);
        }
    }
    if(this->initValue != nullptr)
    {
        str += indent("initial-value", level + 1);
        str += this->initValue->toASTString(level + 2);
    }
    return str;
}


string VariableDefStatement::toString()
{
    string str = "";
    for(auto & var : *(this->vars))
    {
        str += var->toString() + ",";
    }
    return str;
}
string VariableDefStatement::toASTString(int level)
{
    string str = indent("variable-define", level);
    for (auto &var : *(this->vars))
    {
        str += var->toASTString(level + 1);
    }
    return str;
}

}
}