#include "analyser.h"

SymbolTable::SymbolTable(SymbolTable* upper, bool isFunc)
{
    if(!upper)
        level = 0;
    else
        level = upper->level + 1;
    this->isFunction = isFunc;
    this->ExitPoint = {Symbol::NONE};
    this->upper = upper;
}
Symbol SymbolTable::find(string name)
{
    auto it = symbolMap.find(name);
    if (it == symbolMap.end())
    {
        if(upper == nullptr)
            return { Symbol::NONE };
        return upper->find(name);
    }
    auto symbol = symbolMap[name];
    symbol.level = level;
    return symbol;
}
bool SymbolTable::addSymbol(Symbol* symbol)
{
    if (symbolMap.find(symbol->name) != symbolMap.end())
        return false;

    if (symbol->type == Symbol::VARIABLE)
        symbol->addr = size;
    symbolMap[symbol->name] = *symbol;
    symbolList.push_back(*symbol);
    size += symbol->valueType->size();

    return true; 
}
void SymbolTable::updateTotalSize()
{
    _totalSize = max(_totalSize, size);
    if (this->upper)
    {
        this->upper->_totalSize = max(this->upper->_totalSize, this->upper->size + this->_totalSize);
        this->upper->updateTotalSize();
    }
}
size_t SymbolTable::offset()
{
    if(isFunction)
        return 0;
    if (!upper)
        return 0;
    return upper->size + upper->offset();
}
int SymbolTable::getAddr(size_t level, size_t offset)
{
    auto p = this;
    while(p != nullptr && p->level != level)
        p = p->upper;
    if(p!=nullptr)
    {
        return p->offset() + offset;
    }
    
    return -1;
}
string SymbolTable::nameOfVar(size_t offset)
{
    for(auto &pair : this->symbolMap)
    {
        if(pair.second.addr == offset)
            return pair.first;
    }
    return "";
}
size_t SymbolTable::totalSize()
{
    return this->_totalSize;
}
SymbolTable* SymbolTable::funcTable()
{
    for (auto p = this; p != nullptr; p = p->upper)
    {
        if(p->isFunction)
            return p;
    }
    return nullptr;
}

RegisterPool::RegisterPool()
{}
RegisterPool::RegisterPool(int capacity)
{
    pool = new queue<int>;
    for (int i = 0; i < capacity; i++)
    {
        pool->push(i + 1);
    }
}
int RegisterPool::get()
{
    if(pool->empty())
        return 0;
    auto n = pool->front();
    pool->pop();
    return n;
}
void RegisterPool::release(int n)
{
    pool->push(n);
}

CodeBlock::CodeBlock(int id) : registerPool(4)
{
    this->id = id;
}
CodeBlock::CodeBlock(int id, RegisterPool* registerPool)
{
    this->id = id;
    this->registerPool = *registerPool;
}

Type::Type(Type::BuiltInType type)
{
    this->type = type;
    this->base = nullptr;
}
Type::Type(Type* pointer)
{
    this->type = Type::POINTER;
    this->base = pointer;
}
Type::Type(Type* elementType, size_t length)
{
    this->type = Type::ARRAY;
    this->base = elementType;
    this->arraySize = length;
}
Type* Type::arithmeticType(Type* rhs)
{
    if(this->type == Type::POINTER)
    {
        if((int)rhs->type <=4)
            return this;
        else if(rhs->type == Type::ARRAY)
            return this;
        else
            return nullptr;
    }
    else if (rhs->type == Type::POINTER)
    {
        if ((int)this->type <= 4)
            return this;
        else if (this->type == Type::ARRAY)
            return rhs;
        else
            return nullptr;
    }
    return (int)this->type >= (int)rhs->type
               ? this
               : rhs;
}
Type* Type::logicalType(Type* rhs)
{
    return new Type(Type::INT32);
}
Type* Type::logicalType()
{
    return new Type(Type::INT32);
}
Type* Type::bitType()
{
    if(this->type == Type::INT64)
        return this;
    return new Type(Type::INT32);
}
Type* Type::bitType(Type* rhs)
{
    if(this->type == Type::INT64 ||rhs -> type == Type::INT64)
    {
        return new Type(Type::INT64);
    }
    return new Type(Type::INT32);
}
Type * Type::dereferenceType()
{
    if(this->type != Type::POINTER && this->type != Type::ARRAY)
        return nullptr;
    return this->base;
}
size_t Type::size()
{
    switch (type)
    {
    case Type::INT8 :
        return 1;
        break;
    case Type::INT16:
        return 2;
        break;
    case Type::INT32:
        return 4;
        break;
    case Type::INT64:
        return 8;
        break;
    case Type::FLOAT:
        return 4;
        break;
    case Type::DOUBLE:
        return 8;
        break;
    case Type::POINTER:
        return 4;
        break;
    case Type::ARRAY:
        return base->size() * arraySize;
        break;
    }
}

int Program::getLabel(string name)
{
    auto label = ++labelIdx;
    labels[label] = name;
    return label;
}
int Program::getLabel()
{
    auto label = ++labelIdx;
    labels[label] = "Label_" + to_string(label);
    return label;
}
CodeBlock *Program::newBlock(int id, RegisterPool *registerPool, SymbolTable* symbolTable)
{
    CodeBlock* block;
    if (registerPool)
        block = new CodeBlock(id, registerPool);
    else
        block = new CodeBlock(id);
    block->symbolTable = symbolTable;
    blocks[id] = block;
    return block;
}
CodeBlock *Program::newBlock(RegisterPool *registerPool, SymbolTable *symbolTable)
{
    CodeBlock *block;
    auto id = labelIdx + 1;
    id = getLabel("Block_" + to_string(id));
    if (registerPool)
        block = new CodeBlock(id, registerPool);
    else
        block = new CodeBlock(id);
    block->symbolTable = symbolTable;
    blocks[id] = block;
    return block;
}