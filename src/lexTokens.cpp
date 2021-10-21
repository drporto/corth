#include "lexTokens.hpp"

void lexTokens(Program* const program) {

    std::vector<Token>& tokens = program->tokens;
    std::vector<Command>& commands = program->commands;

    for (size_t i = 0; i < tokens.size(); i++) {
        switch (tokens[i].type) {
            // ! INTEGER
            case TokenType::INTEGER:
            {
                commands.emplace_back(&tokens[i], CommandType::PUSH_INT, std::stoll(tokens[i].value));
                break;
            }
            // ! CHAR
            case TokenType::CHAR:
            {
                commands.emplace_back(&tokens[i], CommandType::PUSH_INT, (int64)pureStrToUnicodeChar(tokens[i].value));
                break;
            }
            // ! STRING
            case TokenType::STRING:
            {
                commands.emplace_back(&tokens[i], CommandType::PUSH_STR);
                break;
            }
            // ! KEYWORD
            case TokenType::KEYWORD:
            {
                commands.emplace_back(&tokens[i], COMMAND_TYPE[tokens[i].value]);
                break;
            }
            // ! META
            case TokenType::META:
            {
                break;
            }
            // ! WORD
            case TokenType::WORD:
            {
                throw CorthException(PREPROC_ERROR_CODE,
                    LOCATION_TAG(tokens[i].location) + PREPROC_ERROR_TAG +
                    fmt::format("The token {} with value {} is not valid.", TOKEN_NAME[tokens[i].type], tokens[i].value)
                );
                break;
            }
            default:
            {
                throw CorthException(PREPROC_ERROR_CODE,
                    LOCATION_TAG(tokens[i].location) + PREPROC_ERROR_TAG +
                    fmt::format("The token {} with value {} is not defined.", TOKEN_NAME[tokens[i].type], tokens[i].value)
                );
                break;
            }
        }
    }
}

