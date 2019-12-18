#include "analyser.h"

void assemblyBlock(Program* program, CodeBlock* block, FILE* fp);
void assemblyOP(OP op, Program* program, CodeBlock* block, FILE* fp);
void assemblyFunction(Program* program, CodeBlock* block, FILE* fp);

void assemblyText(Program *program, FILE *fp)
{
    // Assembly Global Variables
    fprintf(fp, ".data\n");
    for (auto& var : program->global->symbolTable->symbolMap)
    {
        string type = "";
        switch(var.second.valueType->type)
        {
        case Type::INT32:
            type = "word";
            break;
        }
        if (var.second.type == Symbol::VARIABLE)
        {
            fprintf(fp, "%s: %s 0\n", var.first, type.c_str());
        }
    }
    fprintf(fp, "\n");
    fprintf(fp, "\n.text\n__start:\n");
    assemblyOP({
        OP::Mov,
        {OpTarget::FP},
        {OpTarget::SP}
    }, program, program->entry, fp);

    if (program->entry)
    {
        assemblyBlock(program, program->entry, fp);
        assemblyOP({OP::Load,
                    {OpTarget::V0},
                    {OpTarget::Constant, 10}},
                   program, program->entry, fp);
        assemblyOP({OP::SysCall}, program, program->entry, fp);
    }

    for (auto &func : program->functions)
    {
        if (func.first == "main")
            continue;

        assemblyFunction(program, func.second.block, fp);
    }
}

void assemblyFunction(Program *program, CodeBlock* block, FILE* fp)
{
    assemblyOP({
        OP::Sub,
        {OpTarget::SP, 0, new Type(Type::INT32)},
        {OpTarget::FP, 0, new Type(Type::INT32)},
        {OpTarget::Constant, block->symbolTable->totalSize(), new Type(Type::INT32)}
    }, program, block, fp);
    assemblyOP({
        OP::Push,
        {OpTarget::Null},
        {OpTarget::AR}
    }, program, block, fp);
    assemblyBlock(program, block, fp);
}

void assemblyBlock(Program *program, CodeBlock *block, FILE *fp)
{
    for (auto &&op : block->codeSequence)
    {
        assemblyOP(op, program, block, fp);
    }
}

void targetText(OpTarget target, string &text, Program* program, CodeBlock* block)
{
    switch (target.type)
    {
    case OpTarget::Constant:
        text = to_string(target.value);
        break;
    case OpTarget::Register:
        text = target.valueType->type == Type::DOUBLE || target.valueType->type == Type::FLOAT
                   ? "$f" + to_string(target.value)
                   : "$t" + to_string(target.value);
        break;
    case OpTarget::V0:
        text = "$v0";
        break;
    case OpTarget::SP:
        text = "$sp";
        break;
    case OpTarget::FP:
        text = "$fp";
        break;
    case OpTarget::AR:
        text = "$ar";
        break;
    case OpTarget::Label:
        text = program->labels[target.value];
        break;
    case OpTarget::Memory:
        auto arr = block->symbolTable->getAddr(target.addition, target.value);
        text = to_string(arr) + "($fp)";
        break;
    }
}

template <typename T> 
const char *toCStr(T str)
{
    return nullptr;
}

template <>
const char* toCStr<string>(string str)
{
    return str.c_str();
}
template <>
const char* toCStr<const char*>(const char* str)
{
    return str;
}

#define OP_R(OP, RD, RS, RT) \
    fprintf(fp, OP " %s, %s, %s\n", toCStr(RD), toCStr(RS), toCStr(RT))

#define OP_L(OP, RS, RT) \
    fprintf(fp, OP " %s, %s\n", toCStr(RS), toCStr(RT))

#define OP_SW(SOURCE, TARGET, OFFSET) \
    fprintf(fp, "sw %s, %d(%s)\n", toCStr(SOURCE), OFFSET, toCStr(TARGET))
#define OP_LW(TARGET, SOURCE, OFFSET) \
    fprintf(fp, "lw %s, %d(%s)\n", toCStr(TARGET), OFFSET, toCStr(SOURCE))

#define BIN_OP_F(OP_TYPE, OP_STR)                             \
    case OP_TYPE:                                           \
    {                                                       \
        if (op.result.valueType->type == Type::FLOAT)       \
            OP_R(OP_STR ".s", rd, rs, rt);                  \
        else if (op.result.valueType->type == Type::DOUBLE) \
            OP_R(OP_STR ".d", rd, rs, rt);                  \
        else                                                \
            OP_R(OP_STR, rd, rs, rt);                       \
        break;                                              \
    }

#define BIN_OP_I(OP_TYPE, OP_STR)                           \
    case OP_TYPE:                                           \
    {                                                       \
        if (op.arg2.type == OpTarget::Constant)             \
            OP_R(OP_STR "i", rd, rs, rt);                   \
        else                                                \
            OP_R(OP_STR, rd, rs, rt);                       \
        break;                                              \
    }

#define BIN_OP(OP_TYPE, OP_STR)   \
    case OP_TYPE:                 \
    {                             \
        OP_R(OP_STR, rd, rs, rt); \
        break;                    \
    }

#define SGL_OP(OP_TYPE, OP_STR)                             \
    case OP_TYPE:                                           \
    {                                                       \
        if(op.arg2.type == OpTarget::Constant)\
        if (op.result.valueType->type == Type::FLOAT)       \
            OP_L(OP_STR ".s", rd, rs);                  \
        else if (op.result.valueType->type == Type::DOUBLE) \
            OP_L(OP_STR ".d", rd, rs);                  \
        else                                                \
            OP_L(OP_STR, rd, rs);                       \
        break;

string memOpTarget(OpTarget target, Program* program, CodeBlock* block)
{
    if(target.addition == 0)
    {
        auto name = program->global->symbolTable->nameOfVar(target.value);
        return name + "($gp)";
    }
    auto addr = to_string(block->symbolTable->getAddr(target.addition, target.value));
    return addr + "($fp)";
}

void assemblyOP(OP op, Program *program, CodeBlock *block, FILE *fp)
{
    string rd, rs, rt;
    targetText(op.result, rd, program, block);
    targetText(op.arg1, rs, program, block);
    targetText(op.arg2, rt, program, block);

    switch (op.op)
    {
    case OP::Load:
    {
        if (op.arg1.type == OpTarget::Constant)
        {
            OP_L("li", rd, rs);
        }
        else
        {
            if (op.arg1.type == OpTarget::Memory)
            {
                rs = memOpTarget(op.arg1, program, block);
            }
            switch (op.arg1.valueType->type)
            {
            case Type::INT8:
                OP_L("lb", rd, rs);
                break;
            case Type::INT16:
                OP_L("lh", rd, rs);
                break;
            case Type::INT64:
                OP_L("ld", rd, rs);
                break;
            case Type::FLOAT:
                OP_L("l.s", rd, rs);
                break;
            case Type::DOUBLE:
                OP_L("l.d", rd, rs);
                break;
            default:
                OP_L("lw", rd, rs);
            }
        }
        break;
    }
    case OP::Store:
    {
        if(op.result.type==OpTarget::Memory)
        {
            rd = memOpTarget(op.result, program, block);
            OP_L("sw", rs, rd);
        }
        else
            OP_SW(rs.c_str(), rd.c_str(), op.arg2.value);
        break;
    }
    case OP::Mov:
    {
        if(op.arg2.type == OpTarget::Constant)
            OP_L("li", rd, rs);
        else
            OP_L("move", rd, rs);
        break;
    }
    case OP::Add:                                           
    {                                                       
        if (op.result.valueType->type == Type::FLOAT)       
            OP_R("add.s", rd, rs, rt);                  
        else if (op.result.valueType->type == Type::DOUBLE) 
            OP_R("add.d", rd, rs, rt);                  
        else
            fprintf(fp, "add"" %s, %s, %s\n", rd.c_str(), rs.c_str(), rt.c_str());
        break;
    }
    BIN_OP_F(OP::Sub, "sub")
    BIN_OP_F(OP::Multiply, "mul")
    BIN_OP_F(OP::Divide, "div")
    case OP::Mod:
    {
        if (op.result.valueType->type == Type::FLOAT)
            OP_R("div.s", rd, rs, rt);
        else if (op.result.valueType->type == Type::DOUBLE)
            OP_R("div.d", rd, rs, rt);
        else
            OP_R("div", rd, rs, rt);
        fprintf(fp, "mfhi %s\n", rd.c_str());
        break;
    }
    BIN_OP_I(OP::And, "and")
    BIN_OP_I(OP::Or, "or")
    BIN_OP_I(OP::Less, "slt")
    BIN_OP(OP::LEqual, "sle")
    BIN_OP(OP::Greater, "sgt")
    BIN_OP(OP::GEqual, "sge")
    BIN_OP(OP::Equal, "seq")
    BIN_OP(OP::NotEqual, "sne")
    case OP::LShift:
    {
        if (op.arg2.type == OpTarget::Constant)
            OP_R("sll", rd, rs, rt);
        else
            OP_R("sllv", rd, rs, rt);
        break;
    }
    case OP::RShift:
    {
        if (op.arg2.type == OpTarget::Constant)
            OP_R("srl", rd, rs, rt);
        else
            OP_R("srlv", rd, rs, rt);
        break;
    }
    case OP::Push:
    {
        fprintf(fp, "        # PUSH %s\n", rs.c_str());
        // $sp = $sp - 4
        OP_R("sub", "$sp", "$sp", "4");
        OP_SW(rs, "$sp", 0);
        break;
    }
    case OP::Pop:
    {
        fprintf(fp, "        # POP %s\n", rd.c_str());
        OP_LW(rd, "$sp", 0);
        OP_R("add", "$sp", "$sp", "4");
        break;
    }
    case OP::Label:
    {
        fprintf(fp, "%s:\n", (program->labels[op.result.value]).c_str());
        break;
    }
    case OP::SysCall:
    {
        fprintf(fp, "syscall\n");
        break;
    }
    case OP::Call:
    {
        fprintf(fp, "jal %s\n", (program->labels[op.result.value]).c_str());
        break;
    }
    case OP::Return:
    {
        assemblyOP({
            OP::Pop,
            {OpTarget::AR}
        }, program, block, fp);
        if(op.arg1.type != OpTarget::V0)
            OP_L("move", "$v0", rs);
        fprintf(fp, "jr $ra    # return\n");
        break;
    }
    case OP::LoadAddr:
    {
        auto addr = block->symbolTable->getAddr(op.arg1.addition, op.arg1.value);
        OP_R("sub", rd, "$fp", to_string(addr));
        break;
    }
    case OP::If:
    {
        fprintf(fp, "beqz %s, %s\n", rs.c_str(), rt.c_str());
        if(op.result.type != OpTarget::Null)
            assemblyBlock(program, program->blocks[op.result.value], fp);
        break;
    }
    case OP::Loop:
    {
        assemblyBlock(program, program->blocks[op.result.value], fp);
        break;
    }
    case OP::Goto:
    {
        fprintf(fp, "j %s\n", rs.c_str());
        break;
    }
    }
    fflush(fp);
}