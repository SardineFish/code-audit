#include "parser.h"
#include <map>
#include <vector>
#include <queue>
#include <stack>

using namespace std;
using namespace Parser;

#define REGISTER_COUNT 4

class Type
{
public:
    enum BuiltInType
    {
        INT8 = 1,
        INT16 = 2,
        INT32 = 3,
        INT64 = 4,
        FLOAT = 5,
        DOUBLE = 6,
        POINTER = 7,
        ARRAY = 8,
    };
    Type *base;
    BuiltInType type;
    size_t arraySize = 1;
    size_t size();
    Type *arithmeticType(Type* rhs);
    Type *logicalType(Type *rhs);
    Type *logicalType();
    Type *bitType();
    Type *bitType(Type* rhs);
    Type *dereferenceType();
    Type(BuiltInType type);
    Type(Type *pointerBase);
    Type(Type *elementType, size_t length);
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
    Type *valueType;
    int level;
};

class SymbolTable
{
public:
    bool isFunction;
    Symbol ExitPoint;
    SymbolTable *upper = nullptr;
    map<string, Symbol> symbolMap;
    size_t size = 0;
    int level;
    bool addSymbol(Symbol *symbol);
    SymbolTable(SymbolTable *upper, bool isFunc = false);
    Symbol find(string name);
    size_t totalSize();
private:
    size_t _totalSize;
    void updateTotalSize(size_t childSize);
};

struct OpTarget
{
    enum OpTargetType
    {
        Null,
        Register,
        Memory,
        Constant,
        Label,
        SP,
        AR,
        FP,
        V0,
    };
    OpTargetType type;
    uint64_t value;
    Type *valueType;
    uint32_t addition;
};

struct OP
{
    enum OpType
    {
        Load,
        Store,
        /*    */ Mov,
        /* +  */ Add,
        /* -  */ Sub,
        /* *  */ Multiply,
        /* /  */ Divide,
        /* %  */ Mod,
        /* && */ And,
        /* || */ Or,
        /* !  */ Not,
        /* == */ Equal,
        /* != */ NotEqual,
        /* >  */ Greater,
        /* >= */ GEqual,
        /* <  */ Less,
        /* <= */ LEqual,
        /* !  */ Nagtive,
        /* &  */ BitAnd,
        /* |  */ BitOr,
        /* ^  */ BirXor,
        /* ~  */ BitNot,
        /* << */ LShift,
        /* >> */ RShift,
        /* ++ */ Increase,
        /* -- */ Decrease,
        /* */ If,
        /* */ Loop,
        /**/Goto,
        Push,
        Pop,
        Label,
        Call,
        Return,
        LoadAddr,
    };
    OpType op;
    OpTarget result, arg1, arg2;
};

class RegisterPool
{
public:
    queue<int>* pool;
    int get();
    void release(int);
    RegisterPool(int capacity);
    RegisterPool();
};

class CodeBlock
{
public:
    int id;
    size_t entryAddr;
    size_t size;
    SymbolTable *symbolTable;
    RegisterPool registerPool;
    vector<OP> codeSequence;
    stack<OpTarget> targetStack;
    CodeBlock(int id);
    CodeBlock(int id, RegisterPool *registerPool);
};

class Program
{
public:
    CodeBlock *entry = nullptr;
    map<int, CodeBlock *> blocks;
    map<int, string> labels;
    int getLabel(string name);
    int getLabel();
    CodeBlock *newBlock(int id, RegisterPool *registerPool, SymbolTable* SymbolTable);
    CodeBlock *newBlock(RegisterPool *registerPool, SymbolTable *SymbolTable);

private:
    int labelIdx = 0;
};

Program *analyse(ASTTree *ast);