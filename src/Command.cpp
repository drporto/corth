#include "Command.hpp"

Command::Command() :
    token(nullptr),
    type(),
    operand() { }

Command::Command(Token* _token, CommandType _type) :
    token(_token),
    type(_type),
    operand(0) { }

Command::Command(Token* _token, CommandType _type, int64 _operand) :
    token(_token),
    type(_type),
    operand(_operand) { }

std::ostream& operator<<(std::ostream& os, const CommandType& commandType) {
    os << COMMAND_NAME[commandType];
    return os;
}

std::ostream& operator<<(std::ostream& os, const Command& command) {
    switch (command.type) {
        case CommandType::PUSH_STR: {
            os << "(" << command.token->location << ") " << command.type << " " << command.token->value;
            break;
        }
        case CommandType::PUSH_INT: {
            os << "(" << command.token->location << ") " << command.type << " " << command.operand;
            break;
        }
        default:
        {
            os << "(" << command.token->location << ") " << command.type;
            break;
        }
    }
    return os;
}