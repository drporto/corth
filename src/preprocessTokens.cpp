#include "preprocessTokens.hpp"

void preprocessTokens(Program* const program) {

    std::vector<Macro>& macros = program->macros;
    std::vector<Token>& tokens = program->tokens;

    size_t i = 0;
    while (i < tokens.size()) {
        switch (tokens[i].type) {
            case TokenType::PREPROCESSOR:
            {
                if (tokens[i].value.compare("MACRO") == 0) {
                    if (tokens[i + 1].type != TokenType::WORD) {
                        throw CorthException(PREPROC_ERROR_CODE,
                            LOCATION_TAG(tokens[i].location) + PREPROC_ERROR_TAG +
                            fmt::format("The MACRO {} must be named with a WORD.", tokens[i + 1].value)
                        );
                    }
                    macros.emplace_back(tokens[i + 1].value, tokens[i].location);
                    size_t start = i + 2, end = start;
                    while (tokens[end].value.compare("END") != 0) end++;
                    macros.back().tokens.assign(tokens.begin() + start, tokens.begin() + end);
                    tokens.erase(tokens.begin() + i, tokens.begin() + end + 1);
                }
                else {
                    throw CorthException(PREPROC_ERROR_CODE,
                        LOCATION_TAG(tokens[i].location) + PREPROC_ERROR_TAG +
                        fmt::format("Token of type {} with value {} is not implemented yet.\n", TOKEN_NAME[tokens[i].type], tokens[i].value)
                    );
                }
                break;
            }
            case TokenType::WORD:
            {
                // ! SEARCH MACROS
                size_t indexmacro = (size_t)-1;
                for (size_t j = 0; j < macros.size(); j++) {
                    if (tokens[i].value.compare(macros[j].name) == 0) {
                        indexmacro = j;
                        break;
                    }
                }
                if (indexmacro != -1) {
                    tokens.insert(tokens.begin() + i + 1, macros[indexmacro].tokens.begin(), macros[indexmacro].tokens.end());
                    tokens.erase(tokens.begin() + i);
                    break;
                }
                // ! SEARCH MEMORY

                throw CorthException(PREPROC_ERROR_CODE,
                    LOCATION_TAG(tokens[i].location) + PREPROC_ERROR_TAG +
                    fmt::format("Token of type {} with value {} was not defined.\n", TOKEN_NAME[tokens[i].type], tokens[i].value)
                );
                break;
            }
            default:
            {
                i++;
                break;
            }
        }
    }
}