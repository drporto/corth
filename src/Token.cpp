#include "Token.hpp"

Token::Token() :
    location(),
    type(),
    value(),
    operand(),
    macropath() { }

Token::Token(const Location* const _location, TokenType _type, const std::string* const _value) :
    location(*_location),
    type(_type),
    value(*_value),
    operand(),
    macropath() { }

Token::Token(const Location* const _location, TokenType _type, const std::string* const _value, int64 _operand, const std::vector<byte>* const _macropath) :
    location(*_location),
    type(_type),
    value(*_value),
    operand(_operand),
    macropath(*_macropath) { };

std::ostream& operator<<(std::ostream& os, const TokenType& tokentype) {
    os << TOKENNAME[tokentype];
    return os;
}

std::ostream& operator<<(std::ostream& os, const Token& token) {
    os << "(" << token.location << ") " << token.type << " " << token.value;
    return os;
}