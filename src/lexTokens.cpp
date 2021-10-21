#include "lexTokens.hpp"

void lexTokens(Program* const program) {

    std::vector<Token>& tokens = program->tokens;
    std::vector<Command>& commands = program->commands;

    for (size_t i = 0; i < tokens.size(); i++) {
        switch (tokens[i].type) {
            // ! INPUT
            case TokenType::INTEGER:
            {
                commands.emplace_back(&tokens[i], CommandType::PUSH_INT, std::stoll(tokens[i].value));
                break;
            }
            // ! KEYWORD
            case TokenType::KEYWORD:
            {
                commands.emplace_back(&tokens[i], COMMAND_TYPE[tokens[i].value]);
                break;
            }
            default:
            {
                throw CorthException(1,
                    LOCATION_TAG(tokens[i].location) + ERROR_TAG +
                    fmt::format("The token {} is not defined.", TOKEN_NAME[tokens[i + 1].type])
                );
                break;
            }
        }
    }
}

