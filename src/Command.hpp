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
    // ! CONTROL FLOW
    IF,
    WHILE,
    DO,
    END,
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
    // ! CONTROL FLOW
    {CommandType::IF, "IF"},
    {CommandType::WHILE, "WHILE"},
    {CommandType::DO, "DO"},
    {CommandType::END, "END"},
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
    // ! CONTROL FLOW
    {"if", CommandType::IF},
    {"while", CommandType::WHILE},
    {"do", CommandType::DO},
    {"end", CommandType::END},
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