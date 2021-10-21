#include "Token.hpp"

Token::Token() :
    location(),
    type(),
    value() { }

Token::Token(TokenType _type, Location* const _location, std::string* const _value) :
    type(_type),
    location(*_location),
    value(*_value) { }

std::ostream& operator<<(std::ostream& os, const TokenType& tokenType) {
    os << TOKEN_NAME[tokenType];
    return os;
}

std::ostream& operator<<(std::ostream& os, const Token& token) {
    os << "(" << token.location << ") " << token.type << " " << token.value;
    return os;
}