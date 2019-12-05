#include "parser.h"
#include <map>
#include <vector>

using namespace std;
using namespace Parser;

enum SymbolType
{
    VARIABLE,
    LABEL,
    FUNCTION
};

struct Symbol
{
    SymbolType type;
    string name;
    size_t addr;
    TypeNode *type;
};

class SymbolTable
{
public:
    SymbolTable *upper = nullptr;
    map<string, Symbol> symbolMap;
    size_t size = 0;
    bool addSymbol(Symbol symbol);
};

enum Op
{
    Add,
    Sub,
    Multiply,
    Divide,
    Mod,
    And,
    Or,
    Not,
    Equal,
    NotEqual,
    Greater,
    GEqual,
    Less,
    LEqual,
    Nagtive,
    BitAnd,
    BitOr,
    BirXor,
    BitNot,
    LShift,
    RShift,
    Increase,
    Decrease,
    If,
    Loop,
    Goto,
};

enum OpTarget
{
    Null,
    Register,
    Memory,
};

struct Code
{
    Op op;
    OpTarget arg1, arg2, result;
};

class CodeBlock
{
public:
    size_t entryAddr;
    size_t size;
    SymbolTable *symbolTable;
    vector<Code> codeSequence;
};

class Program
{
public:
    vector<CodeBlock *> blocks;
    CodeBlock *entry;
};