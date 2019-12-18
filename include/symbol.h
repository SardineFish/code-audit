#pragma once

#include <string>
#include <map>

using namespace std;

class Type
{
  public:
    enum BuiltInType
    {
        VOID = 0,
        INT8 = 1,
        INT16 = 2,
        INT32 = 3,
        INT64 = 4,
        FLOAT = 5,
        DOUBLE = 6,
        POINTER = 7,
        ARRAY = 8,
    };
    Type* base;
    BuiltInType type;
    size_t arraySize = 1;
    size_t size();
    Type* arithmeticType(Type* rhs);
    Type* logicalType(Type* rhs);
    Type* logicalType();
    Type* bitType();
    Type* bitType(Type* rhs);
    Type* dereferenceType();
    Type(BuiltInType type);
    Type(Type* pointerBase);
    Type(Type* elementType, size_t length);
};

struct Symbol
{
    enum SymbolType
    {
        NONE,
        VARIABLE,
        LABEL,
        FUNCTION,
    };
    SymbolType type;
    string name;
    size_t addr;
    Type* valueType;
    int level;
};

class SymbolTable
{
  public:
    bool isFunction;
    Symbol ExitPoint;
    SymbolTable* upper = nullptr;
    map<string, Symbol> symbolMap;
    vector<Symbol> symbolList;
    size_t size = 0;
    int level;
    bool addSymbol(Symbol* symbol);
    SymbolTable(SymbolTable* upper, bool isFunc = false);
    Symbol find(string name);
    int getAddr(size_t level, size_t offset);
    SymbolTable* funcTable();
    size_t totalSize();
    size_t offset();
    string nameOfVar(size_t offset);
    void updateTotalSize();

  private:
    size_t _totalSize = 0;
};