#ifndef CORTH_COMMAND_HPP_
#define CORHT_COMMAND_HPP_

#include <vector>
#include <string>
#include <map>

#include "Definitions.hpp"

#include "Token.hpp"

enum class CommandType {
    PUSH_INT,
    PUSH_STR,
    PLUS,
    PRINT,
    COUNT
};

static std::map<CommandType, std::string> COMMAND_NAME = {
    {CommandType::PUSH_INT, "PUSH_INT"},
    {CommandType::PUSH_STR, "PUSH_STR"},
    {CommandType::PLUS, "PLUS"},
    {CommandType::PRINT, "PRINT"},
    {CommandType::COUNT, "COUNT"},
};

static std::map<std::string, CommandType> COMMAND_TYPE = {
    {"+", CommandType::PLUS},
    {"print", CommandType::PRINT},
};

struct Command {

    Token* token;
    CommandType type;
    int64 operand;

    Command();
    Command(Token* _token, CommandType _type, int64 _operand);

};

std::ostream& operator<<(std::ostream& os, const CommandType& commandType);

std::ostream& operator<<(std::ostream& os, const Command& command);

#endif