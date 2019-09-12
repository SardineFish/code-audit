#pragma once

#ifndef AUDITOR_IMPL
#define AUDITOR_IMPL

#include "source_code.h"
#include "parser.h"
#include <functional>
#include <tuple>
#include <map>

using namespace std;
using namespace CodeAudit::SyntaxParser;

namespace CodeAudit
{

struct Vulnerability
{
    int line;
    int column;
    int level;
    string description;
};

class Context;
class VariableTracker;

class AuditorBase
{
public:
    int level;
    AuditorBase(int level);
    virtual bool tryAudit(ASTNode *node, string &description, int &pos, Context *context);
};

template <class T>
class Auditor : public AuditorBase
{
private:
    function<bool(T *, string &, int &, Context *)> auditor;

public:
    Auditor(int level, function<bool(T *, string &, int &, Context *)> auditor);
    virtual bool tryAudit(ASTNode *node, string &description, int &pos, Context *context) override;
};

template <typename T>
class Tag
{
public:
    static T *get(VariableTracker *var);
    static void add(VariableTracker *var, T *tag);
};

#define DEFINE_VAR_TAG(NAME)                            \
    class NAME : public VariableTag                     \
    {                                                   \
    };                                                  \
    template NAME *getTag<NAME>(VariableTracker * var); \
    template void addTag<NAME>(VariableTracker * var, NAME * tag);

class VariableTag
{
public:
    VariableTag() {}
    virtual ~VariableTag() = default;
};

template <class T>
T *getTag(VariableTracker *var)
{
    if(!var)
        return nullptr;
    for (auto &tag : (var->tags))
    {
        if (auto cast = dynamic_cast<T *>(tag))
            return cast;
    }
    return nullptr;
}

template <class T>
void addTag(VariableTracker *var, T *tag)
{
    if(!var)
        return;
    var->tags.push_back(tag);
}

class ArrayVar : public VariableTag
{
public:
    int size;
    ArrayVar(int size) : size(size) {}
};

template ArrayVar *getTag<ArrayVar>(VariableTracker *var);
template void addTag<ArrayVar>(VariableTracker *var, ArrayVar *tag);

DEFINE_VAR_TAG(StackAlloc)
DEFINE_VAR_TAG(HeapAlloc)
DEFINE_VAR_TAG(GlobalVariable)

class VariableTracker
{
public:
    TypeNode *type;
    string name;
    Token token;
    vector<VariableTag *> tags;
    VariableTracker(TypeNode *type, Token token);
};

class Context
{
public:
    Context *upper;
    vector<VariableTracker *> variables;
    Context(Context *upper);
    VariableTracker *findVariable(string name);
    void addVar(TypeNode *type, Token token);
    void addVar(VariableTracker *var);
};

class CodeAudit
{
public:
    vector<AuditorBase *> auditors;
    void addAuditor(AuditorBase *auditor);
    vector<Vulnerability> audit(SourceCode *source);
};

class FunctionAuditor : public AuditorBase
{
public:
    typedef function<bool(vector<Expression *> &args, string &description, Context *context)> AuditorCallback;
    map<string, AuditorCallback> auditors;
    FunctionAuditor(int level);
    void addAuditor(string funcName, AuditorCallback);
    virtual bool tryAudit(ASTNode *node, string &description, int &pos, Context *context) override;
};

class OperatorAuditor : public AuditorBase
{
public:
    typedef function<bool(Expression *lhs, Expression *rhs, string &description, Context *context)> AuditorCallback;
    map<string, AuditorCallback> auditors;
    OperatorAuditor(int level) : AuditorBase(level) {}
    void addAuditor(string funcName, AuditorCallback);
    virtual bool tryAudit(ASTNode *node, string &description, int &pos, Context *context) override;
};

int evaluate(Expression *expr);

VariableTracker *extractVariable(Expression *expr, Context *context);

Constant *extractConstant(Expression *expr);

FunctionInvokeNode *extractFunctionCall(Expression *expr);

TypeNode *getTypeOf(Expression *expr, Context *context);

int locateExpression(Expression *expr);

int evaluateSize(Expression *expr, Context *context);

} // namespace CodeAudit

#endif