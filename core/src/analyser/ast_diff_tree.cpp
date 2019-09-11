#include "code_audit/compare_tree.h"
#include "code_audit/parser.h"
#include "code_audit/syntax_analyser.h"

#define CMP_NODE(X)                                                                                                    \
    template <>                                                                                                        \
    ComparableNode<string>* toDiffNode<X>(X*);

#define CMP_NODE_DEF(TYPE, ARG)                                                                                        \
    template <>                                                                                                        \
    ComparableNode<string>* toDiffNode<TYPE>(TYPE * ARG)

#define CAST_TO(TYPE, PTR)                                                                                             \
    if (dynamic_cast<TYPE*>(PTR))                                                                                      \
        return toDiffNode<TYPE>(dynamic_cast<TYPE*>(PTR));

#define EMPTY_NODE (new ComparableNode<string>("[ ]"))

using namespace CodeAudit::SyntaxParser;

namespace CodeAudit
{

template <class T>
ComparableNode<string>* toDiffNode(T* node)
{
    throw runtime_error("Unknown AST node.");
}

CMP_NODE(ASTTree)
CMP_NODE(VariableDefine)
CMP_NODE(VariableDefStatement)
CMP_NODE(FunctionDefine)
CMP_NODE(BlockNode)
CMP_NODE(Statement)
CMP_NODE(VariableDefStatement)
CMP_NODE(ExpressionStatement)
CMP_NODE(ReturnStatement)
CMP_NODE(If)
CMP_NODE(ForLoop)
CMP_NODE(Expression)

bool comparer(const ComparableTree<string>::ChildPtr*a, const ComparableTree<string>::ChildPtr*b)
{
    return (*b)->element == (*a)->element;
}

ComparableTree<string>* createDiffTree(ASTTree* ast)
{
    auto tree = new ComparableTree<string>(comparer);
    auto root = toDiffNode<ASTTree>(ast);
    tree->root = root;
    tree->root->updateSize();
    return tree;
}

inline ComparableNode<string>* createNode(string element)
{
    return new ComparableNode<string>(element);
}
inline ComparableNode<string>* createNode(NodeType type, string element)
{
    return new ComparableNode<string>(type, element);
}

template <>
ComparableNode<string>* toDiffNode<ASTTree>(ASTTree* ast)
{
    auto node = new ComparableNode<string>(CMPR_SET, "global");
    for(auto & def : *(ast->globals))
    {
        if(dynamic_cast<VariableDefine*>(def))
            node->add(toDiffNode<VariableDefine>(dynamic_cast<VariableDefine*>(def)));
        else if(dynamic_cast<FunctionDefine*>(def))
            node->add(toDiffNode<FunctionDefine>(dynamic_cast<FunctionDefine*>(def)));
    }
    return node;
}

template <>
ComparableNode<string>* toDiffNode<VariableDefine>(VariableDefine* def)
{
    return new ComparableNode<string>(CMPR_SET, def->type->toString());
}

template <>
ComparableNode<string>* toDiffNode<VariableDefStatement>(VariableDefStatement* def)
{
    auto node = new ComparableNode<string>(CMPR_SET, "var-def");
    for (auto& var : *(def->vars))
    {
        node->add(new ComparableNode<string>(CMPR_SEQ, "var"));
    }
    return node;
}

template <>
ComparableNode<string>* toDiffNode<FunctionDefine>(FunctionDefine* func)
{
    auto node = new ComparableNode<string>(CMPR_SEQ, "func");
    auto args = new ComparableNode<string>(CMPR_SEQ, "args");
    for (auto& arg : *(func->args))
    {
        args->add(toDiffNode<VariableDefine>(arg));
    }
    node->add(args);
    node->add(toDiffNode<BlockNode>(func->body));
    return node;
}

template <>
ComparableNode<string>* toDiffNode<BlockNode>(BlockNode* block)
{
    auto node = new ComparableNode<string>(CMPR_SEQ, "block");
    for (auto& p : *(block->statements))
    {
        node->add(toDiffNode<Statement>(p));
    }
    return node;
}
template <>
ComparableNode<string>* toDiffNode<Statement>(Statement* statement)
{
    CAST_TO(ExpressionStatement, statement);
    CAST_TO(VariableDefStatement, statement);
    CAST_TO(ReturnStatement, statement);
    CAST_TO(If, statement);
    CAST_TO(ForLoop, statement);
}

CMP_NODE_DEF(ExpressionStatement, statement)
{
    return toDiffNode<Expression>(statement->expression);
}

CMP_NODE_DEF(PrefixExpr, expr)
{
    auto node = new ComparableNode<string>(CMPR_SEQ, "prefix");
    node->add(new ComparableNode<string>(expr->op.attribute));
    node->add(toDiffNode<Expression>(expr->expr));
    return node;
}

CMP_NODE_DEF(SubfixExpr, expr)
{
    auto node = new ComparableNode<string>(CMPR_SEQ, "subfix");
    node->add(toDiffNode<Expression>(expr->expr));
    node->add(new ComparableNode<string>(expr->op.attribute));
    return node;
}

CMP_NODE_DEF(InfixExpr, expr)
{
    auto node = new ComparableNode<string>(CMPR_SEQ, "infix");
    node->add(toDiffNode<Expression>(expr->left));
    node->add(new ComparableNode<string>(expr->op));
    node->add(toDiffNode<Expression>(expr->right));
    return node;
}

CMP_NODE_DEF(Constant, constant)
{
    return createNode("[const]");
}

CMP_NODE_DEF(Variable, var)
{
    return createNode("[var]");
}

CMP_NODE_DEF(TypeCast, var)
{
    auto node = new ComparableNode<string>(CMPR_SEQ, "typecast");
    node->add(createNode(var->type->toString()));
    node->add(toDiffNode<Expression>(var->target));
    return node;
}

CMP_NODE_DEF(ArraySubscript, arr)
{
    auto node = new ComparableNode<string>(CMPR_SEQ, "array");
    node->add(toDiffNode<Expression>(arr->target));
    node->add(toDiffNode<Expression>(arr->subscript));
    return node;
}

CMP_NODE_DEF(StructInit, arr)
{
    auto node = createNode("element-init");
    for (auto& element : *(arr->elements))
        node->add(toDiffNode<Expression>(element));
    return node;
}

CMP_NODE_DEF(FunctionInvokeNode, func)
{
    auto node = createNode("call");
    node->add(createNode(func->name));
    for(auto &arg : *(func->args->list))
    {
        node->add(toDiffNode<Expression>(arg));
    }
    return node;
}

CMP_NODE_DEF(Expression, expr)
{
    CAST_TO(Constant, expr);
    CAST_TO(Variable, expr);
    CAST_TO(PrefixExpr, expr);
    CAST_TO(SubfixExpr, expr);
    CAST_TO(InfixExpr, expr);
    CAST_TO(TypeCast, expr);
    CAST_TO(ArraySubscript, expr);
    CAST_TO(StructInit, expr);
    CAST_TO(VariableDefine, expr);
    CAST_TO(FunctionInvokeNode, expr);
    return createNode("[expr]");
}

CMP_NODE_DEF(ReturnStatement, rtn)
{
    auto node = createNode("return");
    node->add(toDiffNode<Expression>(rtn->expr));
    return node;
}

CMP_NODE_DEF(If, if_struct)
{
    auto node = createNode("if");
    node->add(toDiffNode<Expression>(if_struct->condition));
    node->add(toDiffNode<BlockNode>(if_struct->body));
    for (auto& elseif : *(if_struct->elseif))
    {
        auto elseifNode = createNode("elseif");
        elseifNode->add(toDiffNode<Expression>(elseif->condition));
        elseifNode->add(toDiffNode<BlockNode>(elseif->body));
        node->add(elseifNode);
    }
    if (if_struct->elseBody)
    {
        auto elseNode = createNode("elseif");
        elseNode->add(toDiffNode<BlockNode>(if_struct->elseBody));
        node->add(elseNode);
    }
    return node;
}

CMP_NODE_DEF(ForLoop, loop)
{
    auto node = createNode("for");
    if (loop->s1)
        node->add(toDiffNode<Expression>(loop->s1));
    else
        node->add(EMPTY_NODE);
    if (loop->s2)
        node->add(toDiffNode<Expression>(loop->s2));
    else
        node->add(EMPTY_NODE);
    if (loop->s3)
        node->add(toDiffNode<Expression>(loop->s3));
    else
        node->add(EMPTY_NODE);
    node->add(toDiffNode<BlockNode>(loop->body));
    return node;
}

} // namespace CodeAudit