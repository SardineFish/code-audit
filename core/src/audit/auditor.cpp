#pragma once
#include "code_audit/auditor.h"

using namespace CodeAudit::SyntaxParser;

namespace CodeAudit
{

void auditInternal(SourceCode *source, ASTNode *node, vector<AuditorBase *> &auditors, vector<Vulnerability> &vulns, Context *context);

AuditorBase::AuditorBase(int level)
{
    this->level = level;
}

bool AuditorBase::tryAudit(ASTNode *node, string &description, int &pos, Context *context)
{
    return false;
}

template <class T>
Auditor<T>::Auditor(int level, function<bool(T *, string &, int &, Context *)> auditor) : AuditorBase(level)
{
    this->auditor = auditor;
}
template <class T>
bool Auditor<T>::tryAudit(ASTNode *node, string &description, int &pos, Context *context)
{
    auto castNode = dynamic_cast<T *>(node);
    if (!castNode)
    {
        return false;
    }
    return this->auditor(castNode, description, pos, context);
}

VariableTracker::VariableTracker(TypeNode *type, Token token) : type(type), token(token)
{
    this->name = token.attribute;
}

Context::Context(Context *upper)
{
    this->upper = upper;
}
VariableTracker *Context::findVariable(string name)
{
    for (auto &var : (this->variables))
    {
        if (var->name == name)
            return var;
    }
    if (this->upper == nullptr)
        return nullptr;
    return this->upper->findVariable(name);
}
void Context::addVar(TypeNode *type, Token token)
{
    this->variables.push_back(new VariableTracker(type, token));
}
void Context::addVar(VariableTracker *var)
{
    this->variables.push_back(var);
}

void CodeAudit::addAuditor(AuditorBase *auditor)
{
    this->auditors.push_back(auditor);
}
vector<Vulnerability> CodeAudit::audit(SourceCode *source)
{
    auto lexer = new Lexer;
    auto parser = new Parser;
    auto tokens = lexer->lex(source->source);
    auto ast = parser->parse(tokens);
    vector<Vulnerability> vulns;
    auditInternal(source, ast, this->auditors, vulns, nullptr);
    return vulns;
}

template <typename T>
void Tag<T>::add(VariableTracker *var, T *tag)
{
    var->tags.push_back(tag);
}

template <typename T>
T* Tag<T>::get(VariableTracker *var)
{
    for (auto &tag : (var->tags))
    {
        if (auto cast = dynamic_cast<T*>(tag))
            return cast;
    }
    return nullptr;
}

int evaluate(Expression *expr)
{
    try
    {
        if (auto constant = dynamic_cast<Constant *>(expr))
        {
            return stoi(constant->value);
        }
    }
    catch (const std::exception &e)
    {
        return 0;
    }
}

FunctionAuditor::FunctionAuditor(int level):AuditorBase(level){}
void FunctionAuditor::addAuditor(string func, FunctionAuditor::AuditorCallback auditor)
{
    this->auditors[func] = auditor;
}
bool FunctionAuditor::tryAudit(ASTNode *node, string &description, int &pos, Context *context)
{
    if(auto func = dynamic_cast<FunctionInvokeNode*>(node))
    {
        if(this->auditors.find(func->name) != this->auditors.end())
        {
            pos = locateExpression(func);
            return this->auditors[func->name](*(func->args->list), description, context);
        }
    }
    return false;
}

void OperatorAuditor::addAuditor(string op, OperatorAuditor::AuditorCallback auditor)
{
    this->auditors[op] = auditor;
}
bool OperatorAuditor::tryAudit(ASTNode *node, string &description, int &pos, Context *context)
{
    if (auto expr = dynamic_cast<InfixExpr *>(node))
    {
        if (this->auditors.find(expr->op) != this->auditors.end())
        {
            pos = locateExpression(expr);
            return this->auditors[expr->op](expr->left, expr->right, description, context);
        }
    }
    return false;
}

VariableTracker *extractVariable(Expression *expr, Context* context)
{
    if(expr == nullptr)
        return nullptr;
    if (auto var = dynamic_cast<Variable *>(expr))
    {
        if(auto tracker = context->findVariable(var->name))
            return tracker;
        return nullptr;
    }
    else if (auto prefix = dynamic_cast<PrefixExpr *>(expr))
        return extractVariable(prefix->expr, context);
    else if (auto subfix = dynamic_cast<SubfixExpr *>(expr))
        return extractVariable(subfix->expr, context);
    else if (auto arr = dynamic_cast<ArraySubscript *>(expr))
        return extractVariable(arr->target, context);
    else if (auto cast = dynamic_cast<TypeCast*>(expr))
        return extractVariable(cast->target, context);
    return nullptr;
}

Constant *extractConstant(Expression *expr)
{
    if (expr == nullptr)
        return nullptr;
    if (auto var = dynamic_cast<Constant *>(expr))
        return var;
    else if (auto prefix = dynamic_cast<PrefixExpr *>(expr))
        return extractConstant(prefix->expr);
    else if (auto subfix = dynamic_cast<SubfixExpr *>(expr))
        return extractConstant(subfix->expr);
    else if (auto cast = dynamic_cast<TypeCast *>(expr))
        return extractConstant(cast->target);
    return nullptr;
}

FunctionInvokeNode *extractFunctionCall(Expression* expr)
{
    if (expr == nullptr)
        return nullptr;
    if (auto call = dynamic_cast<FunctionInvokeNode *>(expr))
        return call;
    else if (auto prefix = dynamic_cast<PrefixExpr *>(expr))
        return extractFunctionCall(prefix->expr);
    else if (auto subfix = dynamic_cast<SubfixExpr *>(expr))
        return extractFunctionCall(subfix->expr);
    else if (auto cast = dynamic_cast<TypeCast *>(expr))
        return extractFunctionCall(cast->target);
}

int locateExpression(Expression *expr)
{
    if (expr == nullptr)
        return 0;
    if (auto var = dynamic_cast<Constant *>(expr))
        return var->token.pos;
    else if (auto var = dynamic_cast<Variable*>(expr))
        return var->token.pos;
    else if (auto prefix = dynamic_cast<PrefixExpr *>(expr))
        return prefix->op.pos;
    else if (auto subfix = dynamic_cast<SubfixExpr *>(expr))
        return subfix->op.pos;
    else if (auto call = dynamic_cast<FunctionInvokeNode *>(expr))
        return call->id.pos;
    else if (auto infix = dynamic_cast<InfixExpr *>(expr))
        return locateExpression(infix->left);
    else if (auto cast = dynamic_cast<TypeCast *>(expr))
        return locateExpression(cast->target);
    else if(auto arr = dynamic_cast<ArraySubscript*>(expr))
        return locateExpression(arr->target);
    return 0;
}

TypeNode* getTypeOf(Expression *expr, Context* context)
{
    if (expr == nullptr)
        return nullptr;
    if (auto var = dynamic_cast<Variable *>(expr))
    {
        if(auto track = context->findVariable(var->token.attribute))
            return track->type;
    }
    else if (auto prefix = dynamic_cast<PrefixExpr *>(expr))
        return getTypeOf(prefix->expr, context);
    else if (auto subfix = dynamic_cast<SubfixExpr *>(expr))
        return getTypeOf(subfix->expr, context);
    else if (auto arr = dynamic_cast<ArraySubscript *>(expr))
        return getTypeOf(arr->target, context);
    else if (auto cast = dynamic_cast<TypeCast *>(expr))
        return cast->type;
    return nullptr;
}

#define AUDIT_FOR(TYPE, NAME) \
    else if (TYPE *NAME = dynamic_cast<TYPE *>(node))

#define AUDIT(X) \
    auditInternal(source, X, auditors, vulns, context)

#define AUDIT_X(X, CONTEXT) \
    auditInternal(source, X, auditors, vulns, CONTEXT)

#define foreach(X, ARRAY) \
    for (auto &X : *(ARRAY))

inline void runAuditors(SourceCode* source, vector<AuditorBase*>& auditors, ASTNode* node, vector<Vulnerability>& vulns, Context* context)
{
    for (auto auditor : auditors)
    {
        string description = "";
        int pos;
        if (auditor->tryAudit(node, description, pos, context))
        {
            Vulnerability v;
            v.line = source->lineAt(pos);
            v.column = source->columnAt(pos);
            v.description = description;
            v.level = auditor->level;
            vulns.push_back(v);
        }
    }
}

void auditInternal(SourceCode *source, ASTNode *node, vector<AuditorBase *> &auditors, vector<Vulnerability> &vulns, Context *context)
{
    runAuditors(source, auditors, node, vulns, context);
    if (auto ast = dynamic_cast<ASTTree *>(node))
    {
        auto global = new Context(nullptr);
        foreach (def, ast->globals)
            AUDIT_X(def, global);
    }
    AUDIT_FOR(VariableDefStatement, def)
    {
        foreach (var, def->vars)
            AUDIT(var);
    }
    AUDIT_FOR(VariableDefine, var)
    {
        auto track = new VariableTracker(var->type, var->id->token);
        if (var->arrayDimensions->size() > 0)
        {
            Tag<ArrayVar>::add(track, new ArrayVar(evaluate(var->arrayDimensions->at(0))));
        }
        if(context->upper == nullptr)
            Tag<GlobalVariable>::add(track, new GlobalVariable);
        else
            Tag<StackAlloc>::add(track, new StackAlloc);
        context->addVar(track);
    }
    AUDIT_FOR(FunctionDefine, func)
    {
        auto funcContext = new Context(context);
        foreach (var, func->args)
            AUDIT_X(var, funcContext);
        AUDIT_X(func->body, funcContext);
    }
    AUDIT_FOR(BlockNode, block)
    {
        foreach (statement, block->statements)
            AUDIT(statement);
    }
    AUDIT_FOR(ExpressionStatement, statement)
    {
        AUDIT(statement->expression);
    }
    AUDIT_FOR(InfixExpr, expr)
    {
        AUDIT(expr->left);
        AUDIT(expr->right);
    }
    AUDIT_FOR(PrefixExpr, expr)
    {
        AUDIT(expr->expr);
    }
    AUDIT_FOR(SubfixExpr, expr)
    {
        AUDIT(expr->expr);
    }
    AUDIT_FOR(ArraySubscript, expr)
    {
        AUDIT(expr->target);
    }
    AUDIT_FOR(TypeCast, expr)
    {
        AUDIT(expr->target);
    }
    AUDIT_FOR(FunctionInvokeNode, call)
    {
        foreach (arg, call->args->list)
        {
            AUDIT(arg);
        }
    }
    AUDIT_FOR(If, if_struct)
    {
        auto subContext = new Context(context);
        AUDIT_X(if_struct->condition, subContext);
        foreach (elseif, if_struct->elseif)
        {
            AUDIT_X(elseif, subContext);
        }
        if (if_struct->elseBody)
            AUDIT_X(if_struct->elseBody, subContext);
    }
    AUDIT_FOR(ForLoop, loop)
    {
        auto subContext = new Context(context);
        if (loop->s1)
            AUDIT_X(loop->s1, subContext);
        if (loop->s2)
            AUDIT_X(loop->s2, subContext);
        if (loop->s3)
            AUDIT_X(loop->s3, subContext);
        AUDIT_X(loop->body, subContext);
    }
    AUDIT_FOR(ReturnStatement, rtn)
    {
        AUDIT(rtn->expr);
    }
}

#define INSTANT_AUDITOR(TYPE) \
    template class Auditor<TYPE>;

INSTANT_AUDITOR(Expression)
INSTANT_AUDITOR(InfixExpr)
INSTANT_AUDITOR(Constant)
INSTANT_AUDITOR(VariableDefine)
INSTANT_AUDITOR(Variable)
INSTANT_AUDITOR(FunctionInvokeNode)


} // namespace CodeAudit