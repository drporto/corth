#ifndef CORTH_COMMAND_HPP_
#define CORTH_COMMAND_HPP_

#include <vector>
#include <string>
#include <map>

#include "definitions.hpp"

#include "Token.hpp"

enum class CommandType {
    // ! INPUT
    PUSH_INT = 0,
    PUSH_STR,
    // ! OUTPUT
    PRINT,
    // ! MATH
    PLUS,
    MINUS,
    MULT,
    DIV,
    MOD,
    // ! BITWISE
    BIT_SHIFT_LEFT,
    BIT_SHIFT_RIGHT,
    BIT_AND,
    BIT_OR,
    BIT_XOR,
    // ! COMPARISSON
    EQUAL,
    DIFF,
    GREATER_THAN,
    LESS_THAN,
    // ! STACK MANIPULATION
    DROP,
    TWO_DROP,
    DUP,
    TWO_DUP,
    SWAP,
    TWO_SWAP,
    OVER,
    TWO_OVER,
    ROTATE_LEFT,
    ROTATE_RIGHT,
    // ! CONTROL FLOW
    IF,
    ELSE,
    ELIF,
    WHILE,
    DO,
    END,
    BREAK,
    // ! MEMORY
    MEM,
    LOAD,
    STORE,
    // ! SYSCALL
    SYSCALL,
    // ! COUNT
    COUNT
};

static std::map<CommandType, std::string> COMMAND_NAME = {
    // ! INPUT
    {CommandType::PUSH_INT, "PUSH_INT"},
    {CommandType::PUSH_STR, "PUSH_STR"},
    // ! OUTPUT
    {CommandType::PRINT, "PRINT"},
    // ! MATH
    {CommandType::PLUS, "PLUS"},
    {CommandType::MINUS, "MINUS"},
    {CommandType::MULT, "MULT"},
    {CommandType::DIV, "DIV"},
    {CommandType::MOD, "MOD"},
    // ! BITWISE
    {CommandType::BIT_SHIFT_LEFT, "BIT_SHIFT_LEFT"},
    {CommandType::BIT_SHIFT_RIGHT, "BIT_SHIFT_RIGHT"},
    {CommandType::BIT_AND, "BIT_AND"},
    {CommandType::BIT_OR, "BIT_OR"},
    {CommandType::BIT_XOR, "BIT_XOR"},
    // ! COMPARISSON
    {CommandType::EQUAL, "EQUAL"},
    {CommandType::DIFF, "DIFF"},
    {CommandType::GREATER_THAN, "GREATER_THAN"},
    {CommandType::LESS_THAN, "LESS_THAN"},
    // ! STACK MANIPULATION
    {CommandType::DROP, "DROP"},
    {CommandType::TWO_DROP, "2DROP"},
    {CommandType::DUP, "DUP"},
    {CommandType::TWO_DUP, "2DUP"},
    {CommandType::SWAP, "SWAP"},
    {CommandType::TWO_SWAP, "TWO_SWAP"},
    {CommandType::OVER, "OVER"},
    {CommandType::TWO_OVER, "TWO_OVER"},
    {CommandType::ROTATE_LEFT, "ROTATE_LEFT"},
    {CommandType::ROTATE_RIGHT, "ROTATE_RIGHT"},
    // ! CONTROL FLOW
    {CommandType::IF, "IF"},
    {CommandType::ELSE, "ELSE"},
    {CommandType::ELIF, "ELIF"},
    {CommandType::WHILE, "WHILE"},
    {CommandType::DO, "DO"},
    {CommandType::END, "END"},
    {CommandType::BREAK, "BREAK"},
    // ! MEMORY
    {CommandType::MEM, "MEM"},
    {CommandType::LOAD, "LOAD"},
    {CommandType::STORE, "STORE"},
    // ! SYSCALL
    {CommandType::SYSCALL, "SYSCALL"},
    // ! COUNT
    {CommandType::COUNT, "COUNT"}
};

static std::map<std::string, CommandType> COMMAND_TYPE = {
    // ! OUTPUT
    {"print", CommandType::PRINT},
    // ! MATH
    {"+", CommandType::PLUS},
    {"-", CommandType::MINUS},
    {"*", CommandType::MULT},
    {"/", CommandType::DIV},
    {"%", CommandType::MOD},
    // ! BITWISE
    {"<<", CommandType::BIT_SHIFT_LEFT},
    {">>", CommandType::BIT_SHIFT_RIGHT},
    {"&", CommandType::BIT_AND},
    {"|", CommandType::BIT_OR},
    {"^", CommandType::BIT_XOR},
    // ! COMPARISSON
    {"==", CommandType::EQUAL},
    {"!=", CommandType::DIFF},
    {">", CommandType::GREATER_THAN},
    {"<", CommandType::LESS_THAN},
    // ! STACK MANIPULATION
    {"drop", CommandType::DROP},
    {"2drop", CommandType::TWO_DROP},
    {"dup", CommandType::DUP},
    {"2dup", CommandType::TWO_DUP},
    {"swap",CommandType::SWAP},
    {"2swap", CommandType::TWO_SWAP},
    {"over", CommandType::OVER},
    {"2over", CommandType::TWO_OVER},
    {"<<<", CommandType::ROTATE_LEFT},
    {">>>", CommandType::ROTATE_RIGHT},
    // ! CONTROL FLOW
    {"if", CommandType::IF},
    {"else", CommandType::ELSE},
    {"elif", CommandType::ELIF},
    {"while", CommandType::WHILE},
    {"do", CommandType::DO},
    {"end", CommandType::END},
    {"break", CommandType::BREAK},
    // ! MEMORY
    {"mem", CommandType::MEM},
    {"@", CommandType::LOAD},
    {"!", CommandType::STORE},
    // ! SYSCALL
    {"syscall", CommandType::SYSCALL}
};

struct Command {
    Token* token;
    CommandType type;
    int64 operand;

    Command();
    Command(Token* _token, CommandType _type);
    Command(Token* _token, CommandType _type, int64 _operand);
};

std::ostream& operator<<(std::ostream& os, const CommandType& commandType);

std::ostream& operator<<(std::ostream& os, const Command& command);

#endif