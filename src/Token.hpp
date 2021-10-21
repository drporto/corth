#ifndef CORTH_TOKEN_HPP_
#define CORTH_TOKEN_HPP_

#include <vector>
#include <string>
#include <map>

#include "Definitions.hpp"

#include "Location.hpp"

enum class TokenType {
    INTEGER = 0,
    CHAR,
    STRING,
    KEYWORD,
    META,
    WORD,
    COUNT
};

// static std::map<std::string, TokenType> TOKENTYPE = {
//     {"INTEGER", TokenType::INTEGER},
//     {"CHAR", TokenType::CHAR},
//     {"STRING", TokenType::STRING},
//     {"KEYWORD", TokenType::KEYWORD},
//     {"META", TokenType::META},
//     {"WORD", TokenType::WORD},
//     {"COUNT", TokenType::COUNT}
// };

static std::map<TokenType, std::string> TOKEN_NAME = {
    {TokenType::INTEGER, "INTEGER"},
    {TokenType::CHAR, "CHAR"},
    {TokenType::STRING, "STRING"},
    {TokenType::KEYWORD, "KEYWORD"},
    {TokenType::META, "META"},
    {TokenType::WORD, "WORD"},
    {TokenType::COUNT, "COUNT"}
};

struct Token {
    TokenType type;
    Location location;
    std::string value;

    Token();
    Token(TokenType _type, const Location& _location, const std::string& _value);
};

std::ostream& operator<<(std::ostream& os, const TokenType& tokenType);

std::ostream& operator<<(std::ostream& os, const Token& token);

#endif