#include "Token.hpp"

Token::Token() :
    location(),
    type(),
    value() { }

Token::Token(const Location* const _location, TokenType _type, const std::string* const _value) :
    location(*_location),
    type(_type),
    value(*_value) { }

std::ostream& operator<<(std::ostream& os, const TokenType& tokenType) {
    os << TOKEN_NAME[tokenType];
    return os;
}

std::ostream& operator<<(std::ostream& os, const Token& token) {
    os << "(" << token.location << ") " << token.type << " " << token.value;
    return os;
}