#include "Token.hpp"

Token::Token() :
    location(),
    type(),
    value(),
    macrorefs() { }

Token::Token(TokenType _type, const Location& _location, const std::string& _value) :
    type(_type),
    location(_location),
    value(_value),
    macrorefs() { }

std::ostream& operator<<(std::ostream& os, const TokenType& tokenType) {
    os << TOKEN_NAME[tokenType];
    return os;
}

std::ostream& operator<<(std::ostream& os, const Token& token) {
    os << "(" << token.location << ") " << token.type << " " << token.value;
    return os;
}