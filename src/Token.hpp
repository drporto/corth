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
    PREPROCESSOR,
    WORD,
    COUNT
};

// static std::map<std::string, TokenType> TOKENTYPE = {
//     {"INTEGER", TokenType::INTEGER},
//     {"CHAR", TokenType::CHAR},
//     {"STRING", TokenType::STRING},
//     {"KEYWORD", TokenType::KEYWORD},
//     {"PREPROCESSOR", TokenType::PREPROCESSOR},
//     {"WORD", TokenType::WORD},
//     {"COUNT", TokenType::COUNT}
// };

static std::map<TokenType, std::string> TOKENNAME = {
    {TokenType::INTEGER, "INTEGER"},
    {TokenType::CHAR, "CHAR"},
    {TokenType::STRING, "STRING"},
    {TokenType::KEYWORD, "KEYWORD"},
    {TokenType::PREPROCESSOR, "PREPROCESSOR"},
    {TokenType::WORD, "WORD"},
    {TokenType::COUNT, "COUNT"}
};

struct Token {
    Location location;
    TokenType type;
    std::string value;
    int64 operand;
    std::vector<byte> macropath;

    Token();
    Token(const Location* const _location, TokenType _type, const std::string* const _value);
    Token(const Location* const _location, TokenType _type, const std::string* const _value, int64 _operand, const std::vector<byte>* const _macropath);
};

std::ostream& operator<<(std::ostream& os, const TokenType& tokentype);

std::ostream& operator<<(std::ostream& os, const Token& token);

#endif