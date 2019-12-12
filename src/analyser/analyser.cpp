#include "analyser.h"

#define ANALYSE_FOR(TYPE, NAME) \
    else if (TYPE *NAME = dynamic_cast<TYPE *>(node))

#define ANALYSE(X) \
    auditInternal(X, program, block)

#define ANALYSE_X(X, BLOCK) \
    auditInternal(X, program, BLOCK)

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
    if ((TARGET).type == OpTarget::Register) \
        block->registerPool.release((TARGET).value);

Type* getType(TypeNode* typeNode, int dim)
{
    Type *type;
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
    for (int i = 0; i < dim;i++)
    {
        type = new Type(type);
    }
    return type;
}

void auditInternal(ASTNode *node, Program* program, CodeBlock* block)
{
    if (node == nullptr)
        return;

    if (auto ast = dynamic_cast<ASTTree *>(node))
    {
        program = new Program();
        block = program->newBlock(program->getLabel("_Code"), nullptr, new SymbolTable(nullptr));

        foreach (def, ast->globals)
            ANALYSE(def);
    }
    ANALYSE_FOR(VariableDefStatement, def)
    {
        foreach (var, def->vars)
            ANALYSE(var);
    }
    ANALYSE_FOR(VariableDefine, var)
    {
        Symbol symbol = {
            Symbol::VARIABLE,
            var->id->token.attribute,
            0,
            getType(var->type, var->arrayDimensions->size())
        };
        if(!block->symbolTable->addSymbol(&symbol))
        {
            fprintf(stderr, "Redefind variable '%s'.\n", symbol.name.c_str());
        }

        ANALYSE(var->initValue);
        POP(block->targetStack, val);
        OpTarget temp = {
            OpTarget::Register,
            block->registerPool.get(),
            symbol.valueType
        };
        OP op = {
            OP::LoadAddr,
            temp,
            {OpTarget::Memory, symbol.addr | (symbol.level << 32), symbol.valueType}
        };
        block->codeSequence.push_back(op);
        op = {
            OP::Store,
            temp,
            val
        };
        RELEASE_REG(val);
        RELEASE_REG(temp);
    }
    ANALYSE_FOR(FunctionDefine, func)
    {
        auto funcBlock = program->newBlock(nullptr, new SymbolTable(block->symbolTable, true));
        
        auto labelID = program->getLabel(func->name);
        Symbol symbol = {
            Symbol::FUNCTION,
            func->name,
            labelID,
            new Type(nullptr)
        };
        block->symbolTable->addSymbol(&symbol);

        // insert label
        OP op = {
            OP::Label,
            {OpTarget::Label, labelID}
        };
        funcBlock->codeSequence.push_back(op);

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
        POP(block->targetStack, _);
    }
    ANALYSE_FOR(InfixExpr, expr)
    {
        ANALYSE(expr->left);
        ANALYSE(expr->right);
        auto rhs = block->targetStack.top();
        block->targetStack.pop();
        auto lhs = block->targetStack.top();
        block->targetStack.pop();

        /**
         * 
         * TODO: 
         * - Add type to lhs, rhs, result  
         * 
         * 
         * 
         * 
         * 
         **/

        // // Avoid dual mem access
        // // Add op MOV R, [addr]
        // if(lhs.type == OpTarget::Memory && rhs.type == OpTarget::Memory)
        // {
        //     auto lhsReg = block->registerPool.get();
        //     OpTarget lhsTarget = { OpTarget::Register, lhsReg };
        //     block->codeSequence.push_back({
        //         OP::Mov,
        //         lhsTarget,
        //         lhs,
        //         {OpTarget::Null, 0}
        //     });
        //     lhs = lhsTarget;
        // }

        OpTarget result = {OpTarget::Register, block->registerPool.get(), lhs.valueType->arithmeticType(rhs.valueType)};
        if(result.valueType == nullptr)
        {
            // report a type error.
            perror("Type Error");
        }
        OP op;

        if(expr->op == "=")
        {
            if(lhs.type != OpTarget::Memory)
            {
                perror("Invalid lhs.\n");
            }
            if(rhs.type == OpTarget::Memory)
            {
                OpTarget temp = {
                    OpTarget::Register,
                    block->registerPool.get(),
                    rhs.valueType
                };
                op = {
                    OP::Load,
                    temp,
                    rhs
                };
                block->codeSequence.push_back(op);
                RELEASE_REG(rhs);
                rhs = temp;
            }
        }
        if(expr->op == "=")
        {
            op = {
                OP::Store,
                lhs,
                rhs
            };
            auto t = result;
            result = rhs;
            rhs = t;
        }
        if(expr->op == "+")
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
        RELEASE_REG(lhs);
        RELEASE_REG(rhs);
        // $3 = $1 + $2
        // $4 = $1 + $3
        // $1 = $3 + $4
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
        auto symbol = block->symbolTable->find(val->name);
        if(symbol.type == Symbol::NONE)
        {
            fprintf(stderr, "Undefinded symbol '%s'.\n", val->name.c_str());
        }
        OpTarget target = {
            OpTarget::Memory,
            symbol.addr | (symbol.level << 32),
            symbol.valueType,
        };
        OpTarget reg = {
            OpTarget::Register,
            block->registerPool.get(),
            symbol.valueType
        };
        OP op = {
            OP::LoadAddr,
            reg,
            target
        };
        block->codeSequence.push_back(op);
        block->targetStack.push(reg);
    }
    ANALYSE_FOR(PrefixExpr, expr)
    {
        ANALYSE(expr->expr);
        auto arg = block->targetStack.top();
        block->targetStack.pop();
        OpTarget result = {OpTarget::Register, block->registerPool.get()};
        OP op;
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
        ANALYSE(expr->expr);

        auto target = block->targetStack.top();
        block->targetStack.pop();
        
        OP op;
        if (expr->op.attribute == "++")
        {
            if (target.type != OpTarget::Memory)
            {
                // invalid lhs
            }
            op = {
                OP::Increase,
                target,
                target,
                {OpTarget::Null, 0}};
        }
        else if (expr->op.attribute == "--")
        {
            op = {
                OP::Decrease,
                target,
                target,
                {OpTarget::Null, 0}};
        }

        block->codeSequence.push_back(op);
        block->targetStack.push(target);
    }
    ANALYSE_FOR(ArraySubscript, expr)
    {
        ANALYSE(expr->target);
        ANALYSE(expr->subscript);
        auto offset = block->targetStack.top();
        block->targetStack.pop();
        auto array = block->targetStack.top();
        block->targetStack.pop();

        OpTarget temp = {
            OpTarget::Register,
            block->registerPool.get(),
            nullptr
        };

        // temp = array + offset * sizeof(*array)
        // temp = offset * sizeof(*array)
        OP op = {
            OP::Multiply,
            temp,
            offset,
            {OpTarget::Constant, array.valueType->base->size()}};
        block->codeSequence.push_back(op);

        // temp = temp + array
        op = {
            OP::Add,
            temp,
            temp,
            array,
        };
        block->codeSequence.push_back(op);

        temp.valueType = array.valueType->dereferenceType();
        // temp = [temp]
        op = {
            OP::Load,
            temp,
            temp,
            {OpTarget::Null}};
        block->codeSequence.push_back(op);

        if(array.type == OpTarget::Register)
            block->registerPool.release(array.value);
        if(offset.type == OpTarget::Register)
            block->registerPool.release(array.value);
        block->targetStack.push(temp);
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
        else if(symbol.type == Symbol::NONE)
        {
            fprintf(stderr, "Undefinded symbol '%s'", call->name.c_str());
        }
        else
        {
            fprintf(stderr, "Invalid call of non-function type '%s'", call->name.c_str());
        }

        OP op;
        // Save registers
        for (auto i = 0; i < REGISTER_COUNT; i++)
        {
            op = {
                OP::Push,
                {OpTarget::Null},
                {OpTarget::Register, i, nullptr},
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

        foreach (arg, call->args->list)
        {
            ANALYSE(arg);

            POP(block->targetStack, param);

            op = {
                OP::Push,
                {OpTarget::Null},
                param,
                {OpTarget::Null}};
            block->codeSequence.push_back(op);
            if (param.type == OpTarget::Register)
                block->registerPool.release(param.value);
        }
        
        op = {
            OP::Call,
            {OpTarget::Null},
            func,
            {OpTarget::Null}
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
                {OpTarget::Register, i, nullptr}
            };
            block->codeSequence.push_back(op);
        }

        block->targetStack.push({OpTarget::V0});
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

        auto bodyBlock = program->newBlock(&block->registerPool, new SymbolTable(block->symbolTable));

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

            auto bodyBlock = program->newBlock(endpoint.value, &block->registerPool, new SymbolTable(block->symbolTable));

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
            auto bodyBlock = program->newBlock(endpoint.value, &block->registerPool, new SymbolTable(block->symbolTable));
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
                {OpTarget::Null},
                endpoint
            });
        }
        block->codeSequence.push_back({
            OP::Label,
            {OpTarget::Null},
            exitpoint
        });
        
    }
    ANALYSE_FOR(ForLoop, loop)
    {
        auto bodyBlock = program->newBlock(&block->registerPool, new SymbolTable(block->symbolTable));
        block->codeSequence.push_back({
            OP::Loop,
            {OpTarget::Label, bodyBlock->id}
        });
        OpTarget entry = {
            OpTarget::Label,
            program->getLabel(),
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
            {OpTarget::Null},
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
        bodyBlock->codeSequence.push_back({
            OP::Label,
            {OpTarget::Null},
            exit
        });
    }
    ANALYSE_FOR(ReturnStatement, rtn)
    {
        if(rtn->expr)
        {
            ANALYSE(rtn->expr);
            POP(block->targetStack, val);
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