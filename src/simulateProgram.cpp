#include "simulateProgram.hpp"

int simulateProgram(Program* const program) {

    std::vector<Command>& commands = program->commands;

    int exitCode = 0;
    size_t ip = 0;
    std::vector<int64>stack;
    std::vector<byte>memory(STRING_CAPACITY + MEMORY_CAPACITY);

    while (ip < commands.size()) {
        const CommandType& type = commands[ip].type;
        const Location& location = commands[ip].token->location;
        const std::string& tokenValue = commands[ip].token->value;
        const int64& operand = commands[ip].operand;
        switch (type) {
            // ! INPUT
            // * PUSH_INT
            case CommandType::PUSH_INT:
            {
                stack.push_back(operand);
                ip++;
                break;
            }
            // * PUSH_STR
            case CommandType::PUSH_STR:
            {
                std::string unicodeword = pureStrToUnicodeStr(tokenValue);
                size_t unicodewordsize = unicodeword.size();
                if (unicodewordsize + 1 >= STRING_CAPACITY) {
                    std::string errorMessage =
                        LOCATION_TAG(location) + RUNTIME_ERROR_TAG +
                        fmt::format("The string \"{}\" causes the memory to overflow.\n", tokenValue);
                    // EXPAND_MACROS(errorMessage);
                    throw CorthException(RUNTIME_ERROR_CODE, errorMessage);
                }
                stack.push_back(unicodewordsize + 1);
                for (size_t i = 0; i < unicodewordsize; i++) {
                    memory[i] = unicodeword[i];
                }
                memory[unicodewordsize] = '\0';
                stack.push_back(0);
                ip++;
                break;
            }
            // ! OUTPUT
            // * PRINT
            case CommandType::PRINT:
            {
                int64 lvalue = stack.back(); stack.pop_back();
                std::cout << lvalue << std::endl;
                ip++;
                break;
            }
            // ! MATH
            // * PLUS
            case CommandType::PLUS:
            {
                // ? lvalue rvalue
                int64 rvalue = stack.back(); stack.pop_back();
                int64 lvalue = stack.back(); stack.pop_back();
                stack.push_back(lvalue + rvalue);
                ip++;
                break;
            }
            // * MINUS
            case CommandType::MINUS:
            {
                // ? lvalue rvalue
                int64 rvalue = stack.back(); stack.pop_back();
                int64 lvalue = stack.back(); stack.pop_back();
                stack.push_back(lvalue - rvalue);
                ip++;
                break;
            }
            // * MULT
            case CommandType::MULT:
            {
                // ? lvalue rvalue
                int64 rvalue = stack.back(); stack.pop_back();
                int64 lvalue = stack.back(); stack.pop_back();
                stack.push_back(lvalue * rvalue);
                ip++;
                break;
            }
            // * DIV
            case CommandType::DIV:
            {
                // ? lvalue rvalue
                int64 rvalue = stack.back(); stack.pop_back();
                int64 lvalue = stack.back(); stack.pop_back();
                stack.push_back(lvalue / rvalue);
                ip++;
                break;
            }
            // * MOD
            case CommandType::MOD:
            {
                // ? lvalue rvalue
                int64 rvalue = stack.back(); stack.pop_back();
                int64 lvalue = stack.back(); stack.pop_back();
                stack.push_back(lvalue % rvalue);
                ip++;
                break;
            }
            // // ! BITWISE
            // // * BIT_SHIFT_LEFT
            // case CommandType::BIT_SHIFT_LEFT:
            // {
            //     // ? lvalue rvalue
            //     int64 rvalue = stack.back(); stack.pop_back();
            //     int64 lvalue = stack.back(); stack.pop_back();
            //     stack.push_back(lvalue << rvalue);
            //     ip++;
            //     break;
            // }
            // // * BIT_SHIFT_RIGHT
            // case CommandType::BIT_SHIFT_RIGHT:
            // {
            //     // ? lvalue rvalue
            //     int64 rvalue = stack.back(); stack.pop_back();
            //     int64 lvalue = stack.back(); stack.pop_back();
            //     stack.push_back(lvalue >> rvalue);
            //     ip++;
            //     break;
            // }
            // // * BIT_AND
            // case CommandType::BIT_AND:
            // {
            //     // ? lvalue rvalue
            //     int64 rvalue = stack.back(); stack.pop_back();
            //     int64 lvalue = stack.back(); stack.pop_back();
            //     stack.push_back(lvalue & rvalue);
            //     ip++;
            //     break;
            // }
            // // * BIT_OR
            // case CommandType::BIT_OR:
            // {
            //     // ? lvalue rvalue
            //     int64 rvalue = stack.back(); stack.pop_back();
            //     int64 lvalue = stack.back(); stack.pop_back();
            //     stack.push_back(lvalue | rvalue);
            //     ip++;
            //     break;
            // }
            // case CommandType::BIT_XOR:
            // {
            //     // ? lvalue rvalue
            //     int64 rvalue = stack.back(); stack.pop_back();
            //     int64 lvalue = stack.back(); stack.pop_back();
            //     stack.push_back(lvalue ^ rvalue);
            //     ip++;
            //     break;
            // }
            // ! COMPARISON
            // * EQUAL
            case CommandType::EQUAL:
            {
                // ? lvalue rvalue
                int64 rvalue = stack.back(); stack.pop_back();
                int64 lvalue = stack.back(); stack.pop_back();
                stack.push_back((int64)(lvalue == rvalue));
                ip++;
                break;
            }
            // * DIFF
            case CommandType::DIFF:
            {
                // ? lvalue rvalue
                int64 rvalue = stack.back(); stack.pop_back();
                int64 lvalue = stack.back(); stack.pop_back();
                stack.push_back((int64)(lvalue != rvalue));
                ip++;
                break;
            }
            // * LESS_THAN
            case CommandType::LESS_THAN:
            {
                // ? lvalue rvalue
                int64 rvalue = stack.back(); stack.pop_back();
                int64 lvalue = stack.back(); stack.pop_back();
                stack.push_back((int64)(lvalue < rvalue));
                ip++;
                break;
            }
            // * GREATER_THAN
            case CommandType::GREATER_THAN:
            {
                // ? lvalue rvalue
                int64 rvalue = stack.back(); stack.pop_back();
                int64 lvalue = stack.back(); stack.pop_back();
                stack.push_back((int64)(lvalue > rvalue));
                ip++;
                break;
            }
            // // ! MEMORY
            // // * MEM
            // case CommandType::MEM:
            // {
            //     stack.push_back(STRING_CAPACITY);
            //     ip++;
            //     break;
            // }
            // // * LOAD
            // case CommandType::LOAD:
            // {
            //     // ? addr
            //     int64 addr = stack.back(); stack.pop_back();
            //     stack.push_back((int64)memory[addr]);
            //     ip++;
            //     break;
            // }
            // // * STORE
            // case CommandType::STORE:
            // {
            //     // ? value addr
            //     int64 addr = stack.back(); stack.pop_back();
            //     int64 value = stack.back(); stack.pop_back();
            //     memory[addr] = (byte)value;
            //     ip++;
            //     break;
            // }
            // ! SYSCALL
            case CommandType::SYSCALL:
            {
                int64 syscallname = stack.back(); stack.pop_back();
                size_t argc = (size_t)stack.back(); stack.pop_back();
                int64 arg[6];
                for (size_t i = 5; i > (5 - argc); i--) {
                    arg[i] = stack.back(); stack.pop_back();
                }
                switch (syscallname) {
                    case 1: // * WRITE
                    {
                        // ? @@@@@ fd = arg[5] @@@@@ addr = arg[4] @@@@@ count = arg[3]
                        std::string output;
                        output.assign(memory.begin() + arg[4], memory.begin() + arg[4] + arg[3]);
                        switch (arg[5]) {
                            case 1: // * STDOUT
                            {
                                std::cout << output;
                                break;
                            }
                            default:
                            {
                                std::string errorMessage =
                                    LOCATION_TAG(location) + RUNTIME_ERROR_TAG +
                                    fmt::format("The file descriptor {} is not defined for the write syscall.\n", arg[5]);
                                //EXPAND_MACROS(errorMessage);
                                throw CorthException(RUNTIME_ERROR_CODE, errorMessage);
                            }
                        }
                        break;
                    }
                    case 60:
                    {
                        // ? @@@@@ exit_code = arg[5]
                        exitCode = (int)arg[5];
                        break;
                    }
                    default:
                    {
                        std::string errorMessage =
                            LOCATION_TAG(location) + RUNTIME_ERROR_TAG +
                            fmt::format("The syscallname {} is not defined.\n", syscallname);
                        //EXPAND_MACROS(errorMessage);
                        throw CorthException(RUNTIME_ERROR_CODE, errorMessage);
                    }
                }
                ip++;
                break;
            }
            // ! STACK FLOW
            // * DUP
            case CommandType::DUP:
            {
                stack.push_back(stack.back());
                ip++;
                break;
            }
            // * 2DUP
            case CommandType::TWO_DUP:
            {
                // ? lvalue rvalue
                int64 rvalue = stack.back(); stack.pop_back();
                int64 lvalue = stack.back(); stack.pop_back();
                stack.push_back(lvalue);
                stack.push_back(rvalue);
                stack.push_back(lvalue);
                stack.push_back(rvalue);
                ip++;
                break;
            }
            // // * SWAP
            // case CommandType::SWAP:
            // {
            //     // ? v1 v2
            //     int64 v2 = stack.back(); stack.pop_back();
            //     int64 v1 = stack.back(); stack.pop_back();
            //     stack.push_back(v2);
            //     stack.push_back(v1);
            //     ip++;
            //     break;
            // }
            // // * 2SWAP
            // case CommandType::TWO_SWAP:
            // {
            //     // ? v1 v2 v3 v4
            //     int64 v4 = stack.back(); stack.pop_back();
            //     int64 v3 = stack.back(); stack.pop_back();
            //     int64 v2 = stack.back(); stack.pop_back();
            //     int64 v1 = stack.back(); stack.pop_back();
            //     stack.push_back(v3);
            //     stack.push_back(v4);
            //     stack.push_back(v1);
            //     stack.push_back(v2);
            //     ip++;
            //     break;
            // }
            // * DROP
            case CommandType::DROP:
            {
                stack.pop_back();
                ip++;
                break;
            }
            // * 2DROP
            case CommandType::TWO_DROP:
            {
                stack.pop_back(); stack.pop_back();
                ip++;
                break;
            }
            // case CommandType::OVER:
            // {
            //     // ? v1      v2
            //     // ? end()-2 end()-1
            //     stack.push_back(*(stack.end() - 2));
            //     ip++;
            //     break;
            // }
            // case CommandType::TWOOVER:
            // {
            //     // ? v1      v2      v3      v4
            //     // ? end()-4 end()-3 end()-2 end()-1
            //     stack.push_back(*(stack.end() - 4));
            //     stack.push_back(*(stack.end() - 4));
            //     ip++;
            //     break;
            // }
            // // * ROTATE_LEFT
            // case CommandType::ROTATE_LEFT:
            // {
            //     // ? v1 v2 v3
            //     int64 v3 = stack.back(); stack.pop_back();
            //     int64 v2 = stack.back(); stack.pop_back();
            //     int64 v1 = stack.back(); stack.pop_back();
            //     stack.push_back(v2);
            //     stack.push_back(v3);
            //     stack.push_back(v1);
            //     ip++;
            //     break;
            // }
            // // * ROTATE_LEFT
            // case CommandType::ROTATE_RIGHT:
            // {
            //     // ? v1 v2 v3
            //     int64 v3 = stack.back(); stack.pop_back();
            //     int64 v2 = stack.back(); stack.pop_back();
            //     int64 v1 = stack.back(); stack.pop_back();
            //     stack.push_back(v3);
            //     stack.push_back(v1);
            //     stack.push_back(v2);
            //     ip++;
            //     break;
            // }
            // ! CONTROL FLOW
            // * IF
            case CommandType::IF:
            {
                ip++;
                break;
            }
            // * ELSE
            // case CommandType::ELSE:
            // {
            //     ip = operand;
            //     break;
            // }
            // * WHILE
            case CommandType::WHILE:
            {
                ip++;
                break;
            }
            // * DO
            case CommandType::DO:
            {
                int64 lvalue = stack.back(); stack.pop_back();
                ip = (lvalue != 0) ? ip + 1 : operand;
                break;
            }
            // * END
            case CommandType::END:
            {
                ip = operand;
                break;
            }
            // * BREAKPOINT
            default:
            {
                std::string errorMessage =
                    LOCATION_TAG(location) + RUNTIME_ERROR_TAG +
                    fmt::format("The command {} is not implemented.\n", COMMAND_NAME[type]);
                //EXPAND_MACROS(errorMessage);
                throw CorthException(RUNTIME_ERROR_CODE, errorMessage);
            }
        }
    }
    return exitCode;
}