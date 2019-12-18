#include "analyser.h"

#define ANALYSE_FOR(TYPE, NAME) \
    else if (TYPE *NAME = dynamic_cast<TYPE *>(node))

#define ANALYSE(X) \
    analyseInternal(X, program, block)

#define ANALYSE_X(X, BLOCK) \
    analyseInternal(X, program, BLOCK)

#define BUILD_INFIX(OP_STR, OP_TYPE) \
    else if (expr->op == OP_STR)     \
        op = {                       \
            OP_TYPE,                 \
            result,                  \
            lhs,                     \
            rhs};

#define foreach(X, ARRAY) \
    for (auto &X : *(ARRAY))

#define POP(STACK, X)     \
    auto X = (STACK).top(); \
    (STACK).pop();

#define RELEASE_REG(TARGET)                      \
    if ((TARGET).type == OpTarget::Register || (TARGET).type == OpTarget::AddressRegister) \
        block->registerPool.release((TARGET).value);

bool evaluate_T(Expression *expr, uint64_t &value);
void auditInternal(ASTNode *node, Program *program, CodeBlock *block);

Type *getType_T(TypeNode *typeNode, vector<Expression *> *dims)
{
    Type *type;
    if (typeNode->type.attribute == "void")
        type = new Type(Type::VOID);
    if (typeNode->type.attribute == "byte")
        type = new Type(Type::INT8);
    else if (typeNode->type.attribute == "char")
        type = new Type(Type::INT8);
    else if (typeNode->type.attribute == "short")
        type = new Type(Type::INT16);
    else if(typeNode->type.attribute == "int")
        type = new Type(Type::INT32);
    else if (typeNode->type.attribute == "long")
        type = new Type(Type::INT32);
    else if (typeNode->type.attribute == "long long")
        type = new Type(Type::INT64);
    else if (typeNode->type.attribute == "float")
        type = new Type(Type::FLOAT);
    else if (typeNode->type.attribute == "double")
        type = new Type(Type::DOUBLE);
    
    if(dims)
    {
        foreach(dim, dims)
        {
            uint64_t d = 0;
            if(!evaluate_T(dim, d))
            {
                perror("Dimension of array must be a constant.\n");
            }
            type = new Type(type, d);
        }
    }
    return type;
}

Program* analyse(ASTTree* ast)
{
    auto program = new Program();

    analyseSymbol(program, ast);

    analyseInternal(ast, program, nullptr);

    auto symbol = program->global->symbolTable->find("main");
    if(symbol.type == Symbol::NONE)
    {
        perror("Entry 'main' not found.\n");
    }
    else
    {
        program->entry = program->blocks[symbol.addr];
    }

    return program;
}

/**
 * 对每个AST节点递归调用该函数
 * 基于C++11的动态类型检查
 * 判断ASTNode属于哪个类的对象指针
 **/
void analyseInternal(ASTNode *node, Program* program, CodeBlock* block)
{
    if (node == nullptr)
        return;

    if (auto ast = dynamic_cast<ASTTree *>(node))
    {
        block = program->newBlock(program->getLabel("_Code"), nullptr,program->gobalSymbols);
        program->global = block;

        foreach (def, ast->globals)
            ANALYSE(def);
    }
    ANALYSE_FOR(VariableDefStatement, def)
    {
        OpTarget lastVar;
        foreach (var, def->vars)
        {
            ANALYSE(var);
            POP(block->targetStack, target);
            lastVar = target;
        }
        block->targetStack.push(lastVar);
    }
    /**
     * 变量定义，这里实现变量初始化赋值的操作，
     * 符号表项已经在符号表分析的时候添加了
     **/
    ANALYSE_FOR(VariableDefine, var)
    {
        Symbol symbol = block->symbolTable->find(var->id->token.attribute);
        if (var->initValue)
        {
            OpTarget varAddr = {
                OpTarget::Register,
                block->registerPool.get(),
                symbol.valueType};
            OP op = {
                OP::LoadAddr,
                varAddr,
                {OpTarget::Memory, block->symbolTable->getAddr(symbol.level, symbol.addr), symbol.valueType, symbol.level}};
            block->codeSequence.push_back(op);

            /**
             * 处理 int a[] = {1, 2, 3, 4} 这样的数组初始化赋值
             * 依次分析并翻译列表中每一个表达式节点，
             * 将每次计算得到的值存到数组内存的相应偏移位置中
             **/
            if(StructInit* initValue = dynamic_cast<StructInit*>(var->initValue))
            {
                size_t size = symbol.valueType->base->size();
                size_t offset = 0;
                foreach (element, initValue->elements)
                {
                    ANALYSE(element);
                    POP(block->targetStack, val);
                    OpTarget tempReg = val;
                    if (val.type != OpTarget::Register)
                    {
                        tempReg = {
                            OpTarget::Register,
                            block->registerPool.get(),
                            symbol.valueType};
                        block->codeSequence.push_back({
                            OP::Load,
                            tempReg,
                            val
                        });
                    }
                    // offset(varAddr) = $val
                    block->codeSequence.push_back({
                        OP::Store,
                        varAddr,
                        tempReg,
                        {OpTarget::Constant, offset}
                    });
                    RELEASE_REG(tempReg);
                    offset += size;
                }
            }
            else
            {
                /**
                 * 一般的赋值 int a = b 这样
                 * 翻译b表达式，并将结果存入a的内存地址中
                 **/
                ANALYSE(var->initValue);
                POP(block->targetStack, val);
                if(val.type == OpTarget::Memory || val.type == OpTarget::Constant || val.type == OpTarget::AddressRegister)
                {
                    OpTarget temp = {
                        OpTarget::Register,
                        block->registerPool.get(),
                        val.valueType
                    };
                    block->codeSequence.push_back({
                        OP::Load,
                        temp,
                        val
                    });
                    val = temp;
                }
                block->codeSequence.push_back({
                    OP::Store,
                    varAddr,
                    val,
                    {OpTarget::Constant, 0}});
                RELEASE_REG(val);
            }
            RELEASE_REG(varAddr);
        }
        block->targetStack.push({OpTarget::Memory, symbol.addr, symbol.valueType, symbol.level});
    }
    ANALYSE_FOR(FunctionDefine, func)
    {
        Symbol symbol = block->symbolTable->find(func->name);
        auto labelID = symbol.addr;

        auto funcBlock = program->newBlock(labelID, nullptr, func->body->symbolTable);

        FunctionSymbol funcSymbol;
        funcSymbol.name = func->name;
        foreach (arg, func->args)
            funcSymbol.args.push_back(getType_T(arg->type, nullptr));
        funcSymbol.returnType = getType_T(func->type, nullptr);
        funcSymbol.symbol = symbol;
        funcSymbol.block = funcBlock;
        program->functions[func->name] = funcSymbol;

        foreach (var, func->args)
            ANALYSE_X(var, funcBlock);
        ANALYSE_X(func->body, funcBlock);
    }
    ANALYSE_FOR(BlockNode, blockNode)
    {
        foreach (statement, blockNode->statements)
            ANALYSE(statement);
    }
    ANALYSE_FOR(ExpressionStatement, statement)
    {
        ANALYSE(statement->expression);
        POP(block->targetStack, target);
        RELEASE_REG(target);
    }
    ANALYSE_FOR(InfixExpr, expr)
    {
        /**
         * 翻译二元运算符 + - * / 等
         * 递归翻译左右操作数
         * 并获取左右操作数（从结果栈中pop出来）
         * 获取一个临时寄存器 $t
         * 生成运算指令 OP $t, lhs, rhs
         * $t push 进入结果栈，以便上层表达式取用
         **/
        ANALYSE(expr->left);
        ANALYSE(expr->right);
        auto rhs = block->targetStack.top();
        block->targetStack.pop();
        auto lhs = block->targetStack.top();
        block->targetStack.pop();


        /**
         * 左右操作数不能同时为常量（MIPS指令集不支持两个常量作为源操作数）
         * 将左操作数移入一个临时寄存器
         **/
        if(lhs.type == OpTarget::Constant)
        {
            auto lhsReg = block->registerPool.get();
            OpTarget lhsTarget = { OpTarget::Register, lhsReg, lhs.valueType };
            block->codeSequence.push_back({
                OP::Load,
                lhsTarget,
                lhs,
                {OpTarget::Constant, 0}
            });
            lhs = lhsTarget;
        }

        OpTarget result = {OpTarget::Register, block->registerPool.get(), lhs.valueType->arithmeticType(rhs.valueType)};
        if(result.valueType == nullptr)
        {
            // report a type error.
            perror("Type Error");
        }
        OP op;

        /**
         * 处理右操作数，若右操作数是一个内存变量，或者是一个保存了内存地址的寄存器（数组的元素地址）
         * 读取该内存的数据到一个临时寄存器中
         **/
        if(rhs.type == OpTarget::Memory)
        {
            OpTarget rhsReg = {
                OpTarget::Register,
                block->registerPool.get(),
                rhs.valueType
            };
            block->codeSequence.push_back({
                OP::Load,
                rhsReg,
                rhs,
                {OpTarget::Constant, 0}
            });
            rhs = rhsReg;
        }
        else if (rhs.type == OpTarget::AddressRegister)
        {
            block->codeSequence.push_back({
                OP::Load,
                rhs,
                rhs,
                {OpTarget::Constant, 0}
            });
            rhs.type = OpTarget::Register;
        }

        /**
         * 处理左操作数
         * 对于赋值运算，如果左操作数是一个内存变量，将内存变量的地址（当前局部变量基址 + 局部变量的偏移地址）储存到一个临时寄存器，
         * 以便后续使用寄存器间接寻址，将右操作属存入该内存地址中；
         * 
         * 对于非赋值运算，如果左操作属是一个内存变量，或者是一个保存了内存地址的寄存器（数组的元素地址）
         * 读取该内存中的数值到一个临时寄存器中
         **/
        if(expr->op == "=")
        {
            if(lhs.type == OpTarget::Memory)
            {
                OpTarget lhsReg = {
                    OpTarget::Register,
                    block->registerPool.get(),
                    lhs.valueType
                };
                block->codeSequence.push_back({
                    OP::LoadAddr,
                    lhsReg,
                    lhs
                });
                lhs = lhsReg;
            }
        }
        else
        {
            if(lhs.type == OpTarget::Memory)
            {
                OpTarget lhsReg = {
                    OpTarget::Register,
                    block->registerPool.get(),
                    lhs.valueType
                };
                block->codeSequence.push_back({
                    OP::Load,
                    lhsReg,
                    lhs,
                    {OpTarget::Constant, 0}
                });
                lhs = lhsReg;
            }
            else if (lhs.type == OpTarget::AddressRegister)
            {
                block->codeSequence.push_back({
                    OP::Load,
                    lhs,
                    lhs,
                    {OpTarget::Constant, 0}
                });
            }
        }
        
        
        if(expr->op == "=")
        {
            op = {
                OP::Store,
                lhs,
                rhs,
                {OpTarget::Constant, 0}
            };
            auto t = result;
            result = rhs;
            rhs = t;
        }
        else if(expr->op == "+")
            op = {
                OP::Add,
                result,
                lhs,
                rhs};
        BUILD_INFIX("-", OP::Sub)
        BUILD_INFIX("*", OP::Multiply)
        BUILD_INFIX("/", OP::Divide)
        BUILD_INFIX("%", OP::Mod)
        BUILD_INFIX("&&", OP::And)
        BUILD_INFIX("||", OP::Or)
        BUILD_INFIX("==", OP::Equal)
        BUILD_INFIX("!=", OP::NotEqual)
        BUILD_INFIX(">", OP::Greater)
        BUILD_INFIX(">=", OP::GEqual)
        BUILD_INFIX("<", OP::Less)
        BUILD_INFIX("<=", OP::LEqual)
        BUILD_INFIX("!", OP::Nagtive)
        BUILD_INFIX("&", OP::BitAnd)
        BUILD_INFIX("|", OP::BitOr)
        BUILD_INFIX("^", OP::BirXor)
        BUILD_INFIX("<<", OP::LShift)
        BUILD_INFIX(">>", OP::RShift)

        block->codeSequence.push_back(op);
        block->targetStack.push(result);

        /**
         * 左右操作数已经使用完毕，将其临时寄存器释放回寄存器池中
         **/
        RELEASE_REG(lhs);
        RELEASE_REG(rhs);
    }
    ANALYSE_FOR(NumberConstant, constant)
    {
        OpTarget target = {
            OpTarget::Constant,
            constant->value,
            new Type(Type::INT32),
        };
        block->targetStack.push(target);
    }
    ANALYSE_FOR(CharConstant, constant)
    {
        OpTarget target = {
            OpTarget::Constant,
            constant->value,
            new Type(Type::INT8),
        };
        block->targetStack.push(target);
    }
    ANALYSE_FOR(Variable, val)
    {
        /**
         * 对于表达式中的变量，
         * 构造一个表示内存变量的 OpTarget，并push到结果栈中
         **/
        auto symbol = block->symbolTable->find(val->name);
        if(symbol.type == Symbol::NONE)
        {
            fprintf(stderr, "Undefinded symbol '%s'.\n", val->name.c_str());
            symbol.valueType = new Type(Type::INT32);
        }
        OpTarget target = {
            OpTarget::Memory,
            block->symbolTable->getAddr(symbol.level, symbol.addr),
            symbol.valueType,
            symbol.level 
        };
        block->targetStack.push(target);
    }
    ANALYSE_FOR(PrefixExpr, expr)
    {
        /**
         * 前缀表达式 ++a --a -1 这样的，实现方式类似双目运算符，
         * 递归翻译其操作数，并从结果栈中取出该操作数，
         * 如果操作舒是内存变量，将其读出到一个临时寄存器中
         * 对于++a --a，还要将计算结果写回原操作数的内存中
         * 并将计算结果push入结果栈
         **/
        ANALYSE(expr->expr);
        auto arg = block->targetStack.top();
        block->targetStack.pop();
        OpTarget result = {OpTarget::Register, block->registerPool.get()};
        OP op;
        if (arg.type == OpTarget::Memory)
        {
            OpTarget argReg = {
                OpTarget::Register,
                block->registerPool.get(),
                arg.valueType};
            block->codeSequence.push_back({OP::Load, argReg, arg, {OpTarget::Constant, 0}});
            arg = argReg;
        }
        if(expr->op.attribute == "!")
        {
            result.valueType = arg.valueType->logicalType();
            op = {
                OP::Not,
                result,
                arg,
                {OpTarget::Null, 0}};
        }
        else if (expr->op.attribute == "~")
        {
            result.valueType = arg.valueType->bitType();
            op = {
                OP::BitNot,
                result,
                arg,
                {OpTarget::Null, 0}};
        }
        else if (expr->op.attribute == "-")
        {
            result.valueType = arg.valueType;
            op = {
                OP::Nagtive,
                result,
                arg,
                {OpTarget::Null, 0}};
        }
        else if (expr->op.attribute == "++")
        {
            if(arg.type != OpTarget::Memory)
            {
                // invalid lhs
            }
            op = {
                OP::Increase,
                arg,
                arg,
                {OpTarget::Null, 0}};

            // We dont need a new register.
            block->registerPool.release(result.value);
            result = arg;
        }
        else if (expr->op.attribute == "--")
        {
            if (arg.type != OpTarget::Memory)
            {
                // invalid lhs
            }
            op = {
                OP::Decrease,
                arg,
                arg,
                {OpTarget::Null, 0}};
            block->registerPool.release(result.value);
            result = arg;
        }

        block->codeSequence.push_back(op);
        if(arg.type == OpTarget::Register)
            block->registerPool.release(arg.value);
        block->targetStack.push(result);
    }
    ANALYSE_FOR(SubfixExpr, expr)
    {
        /**
         * 分析后缀单目运算符表达式，a--, i++这类
         * 同上，
         * 区别是，这里压入结果栈中的数值是计算前的结果(因此在计算前额外申请一个临时寄存器，将计算前的数值存入寄存器中)
         * 将计算后的结果存入源操作数的内存中
         * 并将计算前的结果的临时寄存器压入结果栈
         **/
        ANALYSE(expr->expr);

        auto target = block->targetStack.top();
        block->targetStack.pop();
        OpTarget targetVal = target;
        OpTarget tempVal = {
            OpTarget::Register,
            block->registerPool.get(),
            target.valueType
        };

        if (target.type == OpTarget::Memory)
        {
            OpTarget targetVal = {
                OpTarget::Register,
                block->registerPool.get(),
                target.valueType};
            block->codeSequence.push_back({OP::Load, targetVal, target, {OpTarget::Constant, 0}});
        }
        else if (target.type == OpTarget::AddressRegister)
        {
            OpTarget targetVal = {
                OpTarget::Register,
                block->registerPool.get(),
                target.valueType};
            block->codeSequence.push_back({
                OP::Load,
                targetVal,
                target,
                {OpTarget::Constant, 0}
            });
        }
        block->codeSequence.push_back({
            OP::Mov,
            tempVal,
            targetVal
        });
        
        OP op;
        if (expr->op.attribute == "++")
        {
            if (target.type != OpTarget::Memory)
            {
                // invalid lhs
            }
            op = {
                OP::Increase,
                tempVal,
                tempVal,
                {OpTarget::Null, 0}};
        }
        else if (expr->op.attribute == "--")
        {
            op = {
                OP::Decrease,
                tempVal,
                tempVal,
                {OpTarget::Null, 0}};
        }

        block->codeSequence.push_back(op);

        block->codeSequence.push_back({
            OP::Store,
            target,
            tempVal,
            {OpTarget::Constant, 0}
        });
        RELEASE_REG(tempVal);
        RELEASE_REG(target);
        block->targetStack.push(targetVal);
    }
    ANALYSE_FOR(ArraySubscript, expr)
    {
        /**
         * 数组下标访问 array[index] 这样的表达式
         * 首先翻译数组 array （其实没什么必要额外递归翻译，反正肯定是一个局部变量）
         * 翻译数组下标表达式 index
         * 并从结果栈中取出这两个OpTarget
         * 对于下标表达式 index， 将其乘上数组元素的大小，并加上数组的地址，
         * $t = &array + sizeof(*array) * index
         * 存到一个临时寄存器中，并压入结果栈
         **/
        ANALYSE(expr->target);
        ANALYSE(expr->subscript);
        auto offset = block->targetStack.top();
        block->targetStack.pop();
        auto array = block->targetStack.top();
        block->targetStack.pop();

        OpTarget temp = {
            OpTarget::Register,
            block->registerPool.get(),
            new Type(Type::INT32)
        };

        // temp = offset * sizeof(*array)
        if(offset.type == OpTarget::Memory)
        {
            OpTarget reg = {
                OpTarget::Register,
                block->registerPool.get(),
                new Type(Type::INT32)
            };
            block->codeSequence.push_back({
                OP::Load,
                reg,
                offset
            });
            offset = reg;
        }
        OP op = {
            OP::Multiply,
            temp,
            offset,
            {OpTarget::Constant, array.valueType->base->size()}};
        block->codeSequence.push_back(op);

        OpTarget reg = {
                OpTarget::AddressRegister,
                block->registerPool.get(),
                new Type(Type::INT32)
            };
            block->codeSequence.push_back({
                OP::LoadAddr,
                reg,
                array
            });
            block->codeSequence.push_back({
                OP::Add,
                reg,
                reg,
                temp
            });
            block->targetStack.push(reg);
            RELEASE_REG(array);
            RELEASE_REG(offset);
            RELEASE_REG(temp);
    }
    ANALYSE_FOR(TypeCast, expr)
    {
        ANALYSE(expr->target);
    }
    ANALYSE_FOR(FunctionInvokeNode, call)
    {
        auto symbol = block->symbolTable->find(call->name);
        OpTarget func = {
            OpTarget::Label,
            symbol.addr,
            nullptr
        };
        if (symbol.type == Symbol::FUNCTION)
        {
            func = {
                OpTarget::Label,
                symbol.addr,
                new Type(nullptr)
            };
        }
        else if (symbol.type == Symbol::NONE)
        {
            fprintf(stderr, "Call to undefinded function '%s'.\n", call->name.c_str());
        }
        else
        {
            fprintf(stderr, "Invalid call of non-function type '%s'.\n", call->name.c_str());
        }
        auto regType = new Type(Type::INT32);
        OP op;
        // Save registers
        for (auto i = 0; i < REGISTER_COUNT; i++)
        {
            op = {
                OP::Push,
                {OpTarget::Null},
                {OpTarget::Register, i, regType},
                {OpTarget::Null}
            };
            block->codeSequence.push_back(op);
        }
        // Push frame pointer
        op = {
            OP::Push,
            {OpTarget::Null},
            {OpTarget::FP},
            {OpTarget::Null}
        };
        block->codeSequence.push_back(op);

        auto callee = program->functions[call->name];
        auto calleeFrameSize = callee.block->symbolTable->totalSize();
        OpTarget calleeFP = {
            OpTarget::Register,
            block->registerPool.get(),
            new Type(Type::INT32)
        };
        block->codeSequence.push_back({
            OP::Sub,
            calleeFP,
            {OpTarget::SP},
            {OpTarget::Constant, calleeFrameSize}
        });
        int argIdx = 0;
        foreach (arg, call->args->list)
        {
            ANALYSE(arg);

            POP(block->targetStack, param);
            if(param.type == OpTarget::Memory)
            {
                OpTarget reg = {
                    OpTarget::Register,
                    block->registerPool.get(),
                    param.valueType
                };
                block->codeSequence.push_back({
                    OP::Load,
                    reg,
                    param
                });
                param = reg;
            }
            else if(param.type == OpTarget::Constant)
            {
                OpTarget reg = {
                    OpTarget::Register,
                    block->registerPool.get(),
                    param.valueType
                };
                block->codeSequence.push_back({
                    OP::Load,
                    reg,
                    param
                });
                param = reg;
            }

            block->codeSequence.push_back({
                OP::Store,
                calleeFP,
                param,
                {OpTarget::Constant, callee.block->symbolTable->symbolList[argIdx].addr}
            });

            RELEASE_REG(param);
            argIdx++;
        }
        RELEASE_REG(calleeFP);
        /*block->codeSequence.push_back({
            OP::Sub,
            {OpTarget::FP},
            {OpTarget::FP},
            {OpTarget::Constant, calleeFrameSize}
        });*/

        op = {
            OP::Call,
            func,
        };
        block->codeSequence.push_back(op);
        // pop frame pointer
        op = {
            OP::Pop,
            {OpTarget::FP}
        };
        block->codeSequence.push_back(op);
        // pop registers
        for (auto i = REGISTER_COUNT - 1; i >= 0; i--)
        {
            op = {
                OP::Pop,
                {OpTarget::Register, i, regType}
            };
            block->codeSequence.push_back(op);
        }

        block->targetStack.push({OpTarget::V0, 0, program->functions[call->name].returnType});
    }
    ANALYSE_FOR(If, if_struct)
    {
        ANALYSE(if_struct->condition);
        auto condition = block->targetStack.top();
        block->targetStack.pop();
        //POP(block->targetStack, condition);
        OpTarget endpoint = {
            OpTarget::Label,
            program->getLabel(),
            nullptr
        };
        OpTarget exitpoint = {
            OpTarget::Label,
            program->getLabel(),
            nullptr
        };

        auto bodyBlock = program->newBlock(&block->registerPool, if_struct->body->symbolTable);
        /*bodyBlock->codeSequence.push_back({
            OP::Label,
            {OpTarget::Label, bodyBlock->id}
        });*/

        OP op = {
            OP::If,
            {OpTarget::Label, bodyBlock->id, nullptr},
            condition,
            endpoint
        };
        block->codeSequence.push_back(op);
        RELEASE_REG(condition);
        // Build body
        ANALYSE_X(if_struct->body, bodyBlock);
        bodyBlock->codeSequence.push_back({
            OP::Goto,
            {OpTarget::Null},
            exitpoint
        });

        foreach (elseif, if_struct->elseif)
        {
            ANALYSE(elseif->condition);
            auto condition = block->targetStack.top();
            block->targetStack.pop();

            auto bodyBlock = program->newBlock(endpoint.value, &block->registerPool, elseif->body->symbolTable);


            endpoint = {
                OpTarget::Label,
                program->getLabel(),
                nullptr
            };
            op = {
                OP::If,
                {OpTarget::Label, bodyBlock->id, nullptr},
                condition,
                endpoint
            };
            block->codeSequence.push_back(op);
            RELEASE_REG(condition);

            ANALYSE_X(elseif->body, bodyBlock);
            bodyBlock->codeSequence.push_back({
                OP::Goto,
                {OpTarget::Null},
                exitpoint
            });
        }
        if(if_struct->elseBody)
        {
            auto bodyBlock = program->newBlock(endpoint.value, &block->registerPool, if_struct->elseBody->symbolTable);
            ANALYSE_X(if_struct->elseBody, bodyBlock);
            bodyBlock->codeSequence.push_back({
                OP::Goto,
                {OpTarget::Null},
                exitpoint
            });
        }
        else
        {
            block->codeSequence.push_back({
                OP::Label,
                endpoint
            });
        }
        block->codeSequence.push_back({
            OP::Label,
            exitpoint
        });
        
    }
    ANALYSE_FOR(ForLoop, loop)
    {
        auto id = program->getLabel();
        id = program->getLabel("Loop_" + to_string(id));
        auto bodyBlock = program->newBlock(id, &block->registerPool, loop->body->symbolTable);

        OpTarget entry = {
            OpTarget::Label,
            id,
            nullptr};
        OpTarget exit = {
            OpTarget::Label,
            program->getLabel(),
            nullptr};
        bodyBlock->symbolTable->ExitPoint = {
            Symbol::LABEL,
            program->labels[exit.value],
            exit.value,
            new Type(nullptr)
        };
        if (loop->s1)
        {
            ANALYSE_X(loop->s1, bodyBlock);
            POP(bodyBlock->targetStack, t);
        }
        bodyBlock->codeSequence.push_back({
            OP::Label,
            entry
        });
        if (loop->s2)
        {
            ANALYSE_X(loop->s2, bodyBlock);
            POP(bodyBlock->targetStack, condition);
            bodyBlock->codeSequence.push_back({
                OP::If,
                {OpTarget::Null},
                condition,
                exit
            });
            RELEASE_REG(condition);
        }
        ANALYSE_X(loop->body, bodyBlock);

        if (loop->s3)
        {
            ANALYSE_X(loop->s3, bodyBlock);
            POP(bodyBlock->targetStack, _);
        }
        bodyBlock->codeSequence.push_back({
            OP::Goto,
            {OpTarget::Null},
            entry
        });  
        block->codeSequence.push_back({
            OP::Loop,
            {OpTarget::Label, bodyBlock->id}
        });
        block->codeSequence.push_back({
            OP::Label,
            exit
        });      
    }
    ANALYSE_FOR(ReturnStatement, rtn)
    {
        if(rtn->expr)
        {
            ANALYSE(rtn->expr);
            POP(block->targetStack, val);
            if(val.type == OpTarget::Memory)
            {
                block->codeSequence.push_back({
                    OP::Load,
                    {OpTarget::V0},
                    val
                });
            }
            if(val.type == OpTarget::Constant)
            {
                block->codeSequence.push_back({
                    OP::Load,
                    {OpTarget::V0},
                    val
                });
                val = {OpTarget::V0};
            }
            block->codeSequence.push_back({
                OP::Return,
                {OpTarget::Null},
                val
            });
            RELEASE_REG(val);
        }
        else
        {
            block->codeSequence.push_back({
                OP::Return,
                {OpTarget::Null},
                {OpTarget::Null}
            });
        }
    }
}

bool evaluate_T(Expression *expr, uint64_t& value)
{
    try
    {
        if (auto constant = dynamic_cast<Constant *>(expr))
        {
            value = stoull(constant->value);
            return true;
        }
    }
    catch (const std::exception &e)
    {
        
    }
    return false;
}