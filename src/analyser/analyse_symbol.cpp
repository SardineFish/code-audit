#include "analyser.h"

#define ANALYSE(X) analyseSymbolInternal(program, X, table)

#define ANALYSE_X(X, TABLE) analyseSymbolInternal(program, X, TABLE)

#define ANALYSE_FOR(TYPE, NAME) else if (TYPE* NAME = dynamic_cast<TYPE*>(node))

#define foreach(X, ARRAY) for (auto& X : *(ARRAY))

bool evaluate(Expression* expr, uint64_t& value);
void analyseSymbolInternal(Program* program, ASTNode* node, SymbolTable* table);

Type* getType(TypeNode* typeNode, vector<Expression*>* dims)
{
    Type* type;
    if (typeNode->type.attribute == "void")
        type = new Type(Type::VOID);
    if (typeNode->type.attribute == "byte")
        type = new Type(Type::INT8);
    else if (typeNode->type.attribute == "char")
        type = new Type(Type::INT8);
    else if (typeNode->type.attribute == "short")
        type = new Type(Type::INT16);
    else if (typeNode->type.attribute == "int")
        type = new Type(Type::INT32);
    else if (typeNode->type.attribute == "long")
        type = new Type(Type::INT32);
    else if (typeNode->type.attribute == "long long")
        type = new Type(Type::INT64);
    else if (typeNode->type.attribute == "float")
        type = new Type(Type::FLOAT);
    else if (typeNode->type.attribute == "double")
        type = new Type(Type::DOUBLE);

    if (dims)
    {
        foreach (dim, dims)
        {
            uint64_t d = 0;
            if (!evaluate(dim, d))
            {
                perror("Dimension of array must be a constant.\n");
            }
            type = new Type(type, d);
        }
    }
    return type;
}

void analyseSymbol(Program* program, ASTTree* ast)
{
    program->gobalSymbols = new SymbolTable(nullptr);
    program->symbolTables.push_back(program->gobalSymbols);
    analyseSymbolInternal(program, ast, program->gobalSymbols);
}

// 对每个AST节点递归调用该函数，确保能够遍历所有AST节点
// 仅分析函数定义、变量定义两种AST节点，并添加到符号表
// 对于函数定义、if、for等包括BlockNode（代码块）的节点，构造新的符号表（变量的代码块作用域），并设置将该符号表作为上一层符号表的子符号表
void analyseSymbolInternal(Program* program, ASTNode* node, SymbolTable* table)
{
    // 使用C++11的动态类型检查，判断当前节点是哪个类的子类
    if(auto ast = dynamic_cast<ASTTree*>(node))
    {
        foreach(def, ast->globals)
            ANALYSE(def);
    }
    ANALYSE_FOR(VariableDefStatement, def)
    {
        foreach(var, def->vars)
        {
            ANALYSE(var);
        }
    }
    ANALYSE_FOR(VariableDefStatement, def)
    {
        foreach (var, def->vars)
        {
            ANALYSE(var);
        }
    }
    ANALYSE_FOR(VariableDefine, var)
    {
        Symbol symbol = {
            Symbol::VARIABLE,
            var->id->token.attribute,
            0,
            getType(var->type, var->arrayDimensions)
        };
        if (!table->addSymbol(&symbol))
        {
            fprintf(stderr, " variable '%s'.\n", symbol.name.c_str());
        }
    }
    ANALYSE_FOR(FunctionDefine, func)
    {
        auto labelID = program->getLabel(func->name);
        Symbol symbol = {
            Symbol::FUNCTION,
            func->name,
            labelID,
            new Type(nullptr)
        };
        if (!table->addSymbol(&symbol))
        {
            fprintf(stderr, "Redefind function '%s'.\n", symbol.name.c_str());
        }
        auto bodyTable = new SymbolTable(table);
        bodyTable->isFunction = true;
        foreach(arg, func->args)
        {
            ANALYSE_X(arg, bodyTable);
        }
        func->body->symbolTable = bodyTable;
        ANALYSE(func->body);
    }
    ANALYSE_FOR(BlockNode, block)
    {
        if(!block->symbolTable)
        {
            block->symbolTable = new SymbolTable(table);
        }
        foreach(statement, block->statements)
        {
            ANALYSE_X(statement, block->symbolTable);
        }
        /** 在每个代码块（函数体，if、else、for等代码块）分析结束后，
         * 更新当前代码块的总size，
         * 用于计算函数中所有局部变量需要的总空间
         * 同时可以得到每个符号表中的局部变量相对于函数局部变量内存基址的偏移地址
         * 因为函数体内存在多个嵌套的符号表
         *  
         **/

        block->symbolTable->updateTotalSize();
        program->symbolTables.push_back(block->symbolTable);
    }
    ANALYSE_FOR(If, if_struct)
    {
        ANALYSE(if_struct->body);
        foreach(elseif, if_struct->elseif)
        {
            ANALYSE(elseif->body);
        }
        if(if_struct->elseBody)
        {
            ANALYSE(if_struct->elseBody);
        }
    }
    ANALYSE_FOR(ForLoop, loop)
    {
        auto bodyTable = new SymbolTable(table);
        loop->body->symbolTable = bodyTable;
        if (loop->s1)
            ANALYSE_X(loop->s1, bodyTable);
        ANALYSE(loop->body);
    }
}

bool evaluate(Expression* expr, uint64_t& value)
{
    try
    {
        if (auto constant = dynamic_cast<Constant*>(expr))
        {
            value = stoull(constant->value);
            return true;
        }
    }
    catch (const std::exception& e)
    {
    }
    return false;
}

void printSymbolTables(Program* program)
{
    for(auto &table : program->symbolTables)
    {
        if(table->symbolList.size() <= 0)
            continue;
        printf("Name\t\tType\tAddr\tValueType\tLevel\t\n");
        printf("------------------------------------------------------\n");
        for (auto& symbol : table->symbolList)
        {
            string name = symbol.name;
            string type;
            switch(symbol.type)
            {
            case Symbol::VARIABLE:
                type = "VAR";
                break;
            case Symbol::FUNCTION:
                type = "FUNC";
                break;
            case Symbol::LABEL:
                type = "LABEL";
                break;
            }
            string valueType;
            switch(symbol.valueType->type)
            {
            case Type::INT32:
                valueType = "Int32";
            }
            printf("%s\t\t%s\t%d\t%s\t\t%d\n", name.c_str(), type.c_str(), symbol.addr, valueType.c_str(), table->level);
        }
        printf("\n\n");
    }
}