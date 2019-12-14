#include "analyser.h"

void assemblyBlock(Program *program, CodeBlock *block, FILE *fp);
void assemblyOP(OP op, Program *program, CodeBlock *block, FILE *fp);

void assemblyText(Program *program, FILE *fp)
{
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

        assemblyBlock(program, func.second.block, fp);
    }
}

void assemblyBlock(Program *program, CodeBlock *block, FILE *fp)
{
    for (auto &&op : block->codeSequence)
    {
        assemblyOP(op, program, block, fp);
    }
}

void targetText(OpTarget target, string &text)
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
    }
}

#define OP_R(OP, RD, RS, RT) \
    fprintf(fp, OP "%s, %s, %s\n", RD.c_str(), RS.c_str(), RT.c_str())

#define OP_L(OP, RS, RT) \
    fprintf(fp, OP "%s, %s\n", RS.c_str(), RT.c_str())

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

void assemblyOP(OP op, Program *program, CodeBlock *block, FILE *fp)
{
    string rd, rs, rt;
    targetText(op.result, rd);
    targetText(op.arg1, rs);
    targetText(op.arg2, rt);

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
        fprintf(fp, "sw %s, %lld(%s)\n", rd.c_str(), op.arg2.value, rs.c_str());
        break;
    }
    case OP::Mov:
    {
        if(op.arg2.type == OpTarget::Constant)
            OP_L("li", rd, rs);
        else
            OP_L("move", rd, rs);
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
        fprintf(fp, "mfhi %s", rd);
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
    }
    fflush(fp);
}