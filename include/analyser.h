#include "parser.h"
#include <map>
#include <vector>
#include <queue>
#include <stack>

using namespace std;
using namespace Parser;

#define REGISTER_COUNT 4


struct OpTarget
{
    enum OpTargetType
    {
        Null,
        Register,
        Memory,
        Constant,
        Label,
        AddressRegister,
        SP,
        RA,
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
        SysCall,
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

struct FunctionSymbol 
{
    string name;
    vector<Type *> args;
    Type *returnType;
    Symbol symbol;
    CodeBlock *block;
};

class Program
{
public:
    CodeBlock *entry = nullptr;
    map<int, CodeBlock *> blocks;
    map<int, string> labels;
    map<string, FunctionSymbol> functions;
    vector<SymbolTable*> symbolTables;
    CodeBlock* global;
    SymbolTable* gobalSymbols;
    int getLabel(string name);
    int getLabel();
    CodeBlock *newBlock(int id, RegisterPool *registerPool, SymbolTable *SymbolTable);
    CodeBlock *newBlock(RegisterPool *registerPool, SymbolTable *SymbolTable);

private:
    int labelIdx = 0;
};

Program *analyse(ASTTree *ast);

void assemblyText(Program *program, FILE *fp);

void analyseSymbol(Program* program, ASTTree* ast);

void printSymbolTables(Program* program);