#include "analyser.h"

void assemblyBlock(Program* program, CodeBlock* block, FILE* fp);
void assemblyOP(OP op, Program* program, CodeBlock* block, FILE* fp);
void assemblyFunction(Program* program, CodeBlock* block, FILE* fp);

/**
 * 生成目标代码的入口
 * 这里需要加入一些 MIPS 汇编的头部代码
 * .data 块里包含全局变量的声明（这个不在任务要求里，可以不管）
 * __start: 标签指明程序开始的位置
 * 此时用 move $fp, $sp 将栈顶指针移入$fp寄存器中，即将栈空间作为函数的局部变量空间
 * 这里的 $fp 寄存器用法类似于 X86 汇编中的 EBP 寄存器，
 * 对于函数里的局部变量 x ，在生成符号表时为其分配的偏移地址是 n ，那么访问这个局部变量的方式为 n($fp) （即地址 = n + $fp）
 **/
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
            fprintf(fp, "%s: .%s 0\n", var.first.c_str(), type.c_str());
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
        assemblyFunction(program, program->entry, fp);
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

/**
 * 翻译函数体
 * 进入一个函数时，需要申请一块栈内存空间，用于存放局部变量，在生成符号表时已经计算出函数所有局部变量所需要的总空间，
 * 于是让 $fp = $sp - total_size 即完成内存分配，新的 $fp 寄存器将被用于该函数的局部变量寻址
 * 同时需要将 $sp 也移动相同的长度（因为后续需要使用栈的时候要跳过这块局部变量内存空间）
 * 然后将 $ra 寄存器（即调用该函数前的指令位置）压栈保存（以免里面再次调用一个函数时覆写 $ra 寄存器）
 * 保存的 $ra 寄存器将在该函数返回时被 POP 还原出来
 **/
void assemblyFunction(Program *program, CodeBlock* block, FILE* fp)
{
    assemblyOP({
        OP::Label,
        {OpTarget::Label, block->id}
    }, program, block, fp);
    // fp = 
    assemblyOP({
        OP::Sub,
        {OpTarget::SP, 0, new Type(Type::INT32)},
        {OpTarget::SP, 0, new Type(Type::INT32)},
        {OpTarget::Constant, block->symbolTable->totalSize(), new Type(Type::INT32)},
    }, program, block, fp);
    assemblyOP({
        OP::Mov,
        {OpTarget::FP},
        {OpTarget::SP}
    }, program, block, fp);
    assemblyOP({
        OP::Push,
        {OpTarget::Null},
        {OpTarget::RA}
    }, program, block, fp);
    assemblyBlock(program, block, fp);
}

/**
 * 依次翻译代码块中的指令序列
 **/
void assemblyBlock(Program *program, CodeBlock *block, FILE *fp)
{
    for (auto &&op : block->codeSequence)
    {
        assemblyOP(op, program, block, fp);
    }
}

/**
 * 翻译内存寻址操作数，
 * 入上文所说的
 * 对于函数里的局部变量 x ，在生成符号表时为其分配的偏移地址是 n ，那么访问这个局部变量的方式为 n($fp) （即地址 = n + $fp）
 * 这里面的 $gp 是用于实现全局变量的，实验不要求，就不管了
 **/
string memOpTarget(OpTarget target, Program* program, CodeBlock* block)
{
    if (target.addition == 0)
    {
        auto name = program->global->symbolTable->nameOfVar(target.value);
        return name + "($gp)";
    }
    auto addr = target.value;
    return to_string(addr) + "($fp)";
}

/**
 * 将操作数翻译成 MIPS 指令中的操作数
 * 例如将 i 号临时寄存器翻译成 $ti
 * 将特殊寄存器 如 OpTarget::FP 翻译成 $fp 等
 **/
void targetText(OpTarget target, string &text, Program* program, CodeBlock* block)
{
    switch (target.type)
    {
    case OpTarget::Constant:
        text = to_string(target.value);
        break;
    case OpTarget::Register:
    case OpTarget::AddressRegister:
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
    case OpTarget::RA:
        text = "$ra";
        break;
    case OpTarget::Label:
        text = program->labels[target.value];
        break;
    case OpTarget::Memory:
        text = memOpTarget(target, program, block);
        break;
    case OpTarget::A0:
        text = "$a0";
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

/**
 * 用于生成 MIPS R型 指令的宏
 * add, sub, mul, div 之类的
 **/
#define OP_R(OP, RD, RS, RT) \
    fprintf(fp, OP " %s, %s, %s\n", toCStr(RD), toCStr(RS), toCStr(RT))

#define OP_L(OP, RS, RT) \
    fprintf(fp, OP " %s, %s\n", toCStr(RS), toCStr(RT))

#define OP_SW(SOURCE, TARGET, OFFSET) \
    fprintf(fp, "sw %s, %d(%s)\n", toCStr(SOURCE), OFFSET, toCStr(TARGET))
#define OP_LW(TARGET, SOURCE, OFFSET) \
    fprintf(fp, "lw %s, %d(%s)\n", toCStr(TARGET), OFFSET, toCStr(SOURCE))

#define BIN_OP_F(OP_TYPE, OP_STR)                                                                                      \
    case OP_TYPE:                                                                                                      \
    {                                                                                                                  \
        if (!op.result.valueType)                                                                                      \
            OP_R(OP_STR, rd, rs, rt);                                                                                  \
        else if (op.result.valueType->type == Type::FLOAT)                                                             \
            OP_R(OP_STR ".s", rd, rs, rt);                                                                             \
        else if (op.result.valueType->type == Type::DOUBLE)                                                            \
            OP_R(OP_STR ".d", rd, rs, rt);                                                                             \
        else                                                                                                           \
            OP_R(OP_STR, rd, rs, rt);                                                                                  \
        break;                                                                                                         \
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
    targetText(op.result, rd, program, block);
    targetText(op.arg1, rs, program, block);
    targetText(op.arg2, rt, program, block);

    switch (op.op)
    {
    case OP::Load:
    {
        /**
         * Load 指令将数据从内存移入寄存器，或将一个立即数存入寄存器
         **/
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
            else if(op.arg1.type == OpTarget::AddressRegister)
            {
                rs = "0(" + rs + ")";
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
        /**
         * Store 指令将寄存器中的值存入内存
         **/
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
        /**
         * Move 指令实现寄存器之间的赋值
         **/
        if(op.arg1.type == OpTarget::Constant)
            OP_L("li", rd, rs);
        else if(op.arg1.type == OpTarget::Memory)
        {
            assemblyOP({
                OP::Load,
                op.result,
                op.arg1,
                {OpTarget::Constant, 0}
            }, program, block, fp);
        }
        else
            OP_L("move", rd, rs);
        break;
    }
    case OP::Increase:
    {
        /**
         * 实现 a++ 这类的
         **/
        OP_R("addi", rd, rs, "1");
        break;
    }
    case OP::Decrease:
    {
        /**
         * 实现 a-- 之类的
         **/
        OP_R("subi", rd, rs, "1");
        break;
    }
    case OP::Add:                                           
    {
        if(!op.result.valueType)
            OP_R("add", rd, rs, rt);
        else if (op.result.valueType->type == Type::FLOAT)
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
        /**
         * 翻译标签，将 i 号标签翻译成 Label_i: 样的代码
         **/
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
        /**
         * 函数调用
         * 使用 jal func 指令，将当前指令寄存器（pc）的值写入 $ra 寄存器，并跳转到 func 这个标签处
         * 参数的传递已经在中间代码的部分实现了，这里目标代码只需要跳转即可
         **/
        fprintf(fp, "jal %s\n", (program->labels[op.result.value]).c_str());
        break;
    }
    case OP::Return:
    {
        /**
         * 将 $ra 寄存器的值从栈中 POP 出来（即该调用函数之前的指令地址）
         * 使用 MIPS jr $ra 指令实现跳转到 $ra 寄存器中的指令地址处执行
         * 即返回到调用函数前的指令处继续执行
         **/
        assemblyOP({
            OP::Pop,
            {OpTarget::RA}
        }, program, block, fp);
        assemblyOP({
            OP::Add,
            {OpTarget::SP, 0, new Type(Type::INT32)},
            {OpTarget::SP, 0, new Type(Type::INT32)},
            {OpTarget::Constant, block->symbolTable->funcTable()->totalSize(), new Type(Type::INT32)}
        }, program, block, fp);
        if(op.arg1.type != OpTarget::V0)
        {
            assemblyOP({
                OP::Mov,
                {OpTarget::V0},
                op.arg1
            }, program, block, fp);
        }
        fprintf(fp, "jr $ra    # return\n");
        break;
    }
    case OP::LoadAddr:
    {
        /**
         * 将一个局部变量的地址移入指定的寄存器
         * 对于偏移地址为 n 的局部变量 x，移入 $t0 寄存器，即翻译为：
         * $t0 = n + $fp
         **/
        auto addr = op.arg1.value;
        OP_R("add", rd, "$fp", to_string(addr));
        break;
    }
    case OP::If:
    {
        /**
         * 翻译 if 条件跳转
         * 并翻译 if 要执行的代码块
         **/
        fprintf(fp, "beqz %s, %s\n", rs.c_str(), rt.c_str());
        if(op.result.type != OpTarget::Null)
            assemblyBlock(program, program->blocks[op.result.value], fp);
        break;
    }
    case OP::Loop:
    {
        /**
         * 翻译 for 循环的代码块
         **/
        assemblyBlock(program, program->blocks[op.result.value], fp);
        break;
    }
    case OP::Goto:
    {
        /**
         * 无条件跳转
         * （用在循环里）
         **/
        fprintf(fp, "j %s\n", rs.c_str());
        break;
    }
    }
    fflush(fp);
}