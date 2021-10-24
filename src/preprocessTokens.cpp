#include "preprocessTokens.hpp"

void preprocessTokens(Program* const program) {

    std::vector<Memory>& memories = program->memories;
    std::vector<Macro>& macros = program->macros;
    std::vector<Token>& tokens = program->tokens;

    size_t i = 0;
    while (i < tokens.size()) {
        switch (tokens[i].type) {
            case TokenType::PREPROCESSOR:
            {
                // ! INCLUDE
                if (tokens[i].value.compare("INCLUDE") == 0) {
                    if (tokens[i + 1].type != TokenType::STRING) {
                        throw CorthException(PREPROC_ERROR_CODE,
                            LOCATION_TAG(tokens[i].location) + PREPROC_ERROR_TAG +
                            fmt::format("The INCLUDE file \'{0}\' is a {1} and it must be a STRING.\n", tokens[i + 1].value, TOKEN_NAME[tokens[i + 1].type])
                        );
                    }
                    std::vector<Token> includeTokens;
                    lexSourceCode(pureStrToUnicodeStr(tokens[i + 1].value), includeTokens);
                    tokens.insert(tokens.begin() + i + 2, includeTokens.begin(), includeTokens.end());
                    tokens.erase(tokens.begin() + i, tokens.begin() + i + 2);
                }
                // ! MACRO
                else if (tokens[i].value.compare("MACRO") == 0) {
                    if (tokens[i + 1].type != TokenType::WORD) {
                        throw CorthException(PREPROC_ERROR_CODE,
                            LOCATION_TAG(tokens[i].location) + PREPROC_ERROR_TAG +
                            fmt::format("The MACRO name \'{0}\' is a {1} and it must be a WORD.", tokens[i + 1].value, TOKEN_NAME[tokens[i + 1].type])
                        );
                    }
                    macros.emplace_back(tokens[i + 1].value, tokens[i].location);
                    size_t start = i + 2, end = start;
                    while (tokens[end].value.compare("END") != 0) end++;
                    macros.back().tokens.assign(tokens.begin() + start, tokens.begin() + end);
                    tokens.erase(tokens.begin() + i, tokens.begin() + end + 1);
                }
                // ! MEMORY
                else if (tokens[i].value.compare("MEMORY") == 0) {
                    if (tokens[i + 1].type != TokenType::WORD) {
                        throw CorthException(PREPROC_ERROR_CODE,
                            LOCATION_TAG(tokens[i].location) + PREPROC_ERROR_TAG +
                            fmt::format("The MEMORY name \'{0}\' is a {1} and it must be a WORD.", tokens[i + 1].value, TOKEN_NAME[tokens[i + 1].type])
                        );
                    }
                    size_t start = i + 2, end = start;
                    std::vector<size_t> memorystack;
                    while (tokens[end].value.compare("END") != 0) {
                        if (isInteger(tokens[end].value)) {
                            memorystack.push_back(std::stoull(tokens[end].value));
                        }
                        else if (tokens[end].value.compare("+") == 0) {
                            size_t rvalue = memorystack.back(); memorystack.pop_back();
                            size_t lvalue = memorystack.back(); memorystack.pop_back();
                            memorystack.push_back(lvalue + rvalue);
                        }
                        else if (tokens[end].value.compare("*") == 0) {
                            size_t rvalue = memorystack.back(); memorystack.pop_back();
                            size_t lvalue = memorystack.back(); memorystack.pop_back();
                            memorystack.push_back(lvalue * rvalue);
                        }
                        else {
                            size_t macroindex = (size_t)-1;
                            for (size_t j = 0; j < macros.size(); j++) {
                                if (tokens[end].value.compare(macros[j].name) == 0) {
                                    macroindex = j;
                                    break;
                                }
                            }
                            if (macroindex != -1) {
                                tokens.insert(tokens.begin() + end + 1, macros[macroindex].tokens.begin(), macros[macroindex].tokens.end());
                                tokens.erase(tokens.begin() + end);
                                continue;
                            }
                            PREPROC_ERROR(
                                tokens[i].location,
                                fmt::format("Can only tokens of type INTEGER, PLUS and MULT in MEMORY definition.\n"),
                                tokens[i].macrorefs
                            );
                        }
                        end++;
                    }
                    if (memorystack.size() == 1) {
                        size_t address = 0;
                        if (!memories.empty()) address = memories.back().address + memories.back().size;
                        memories.emplace_back(tokens[i + 1].value, tokens[i].location, address, memorystack[0]);
                        tokens.erase(tokens.begin() + i, tokens.begin() + end + 1);
                    }
                    else {
                        PREPROC_ERROR(
                            tokens[i].location,
                            fmt::format("Invalid size in MEMORY definition.\n", TOKEN_NAME[tokens[i].type], tokens[i].value),
                            tokens[i].macrorefs
                        );
                    }
                }
                // ! DEFAULT
                else {
                    PREPROC_ERROR(
                        tokens[i].location,
                        fmt::format("Token of type {} with value \'{}\' is not defined.\n", TOKEN_NAME[tokens[i].type], tokens[i].value),
                        tokens[i].macrorefs
                    );
                }
                break;
            }
            case TokenType::WORD:
            {
                // ! SEARCH MACROS
                size_t macroindex = (size_t)-1;
                for (size_t j = 0; j < macros.size(); j++) {
                    if (tokens[i].value.compare(macros[j].name) == 0) {
                        macroindex = j;
                        break;
                    }
                }
                if (macroindex != -1) {
                    tokens.insert(tokens.begin() + i + 1, macros[macroindex].tokens.begin(), macros[macroindex].tokens.end());
                    for (size_t j = (i + 1); j < (i + 1) + macros[macroindex].tokens.size(); j++) {
                        tokens[j].macrorefs = tokens[i].macrorefs;
                        tokens[j].macrorefs.emplace_back(macroindex, tokens[i].location);
                    }
                    tokens.erase(tokens.begin() + i);
                    break;
                }
                // ! SEARCH MEMORY
                size_t memoryindex = (size_t)-1;
                for (size_t j = 0; j < memories.size(); j++) {
                    if (tokens[i].value.compare(memories[j].name) == 0) {
                        memoryindex = j;
                        break;
                    }
                }
                if (memoryindex != -1) {
                    tokens.insert(tokens.begin() + i + 1, Token(TokenType::MEMORY, tokens[i].location, std::to_string(memoryindex)));
                    tokens.erase(tokens.begin() + i);
                    break;
                }
                // ! DEFAULT
                PREPROC_ERROR(
                    tokens[i].location,
                    fmt::format("Token of type {} with value \'{}\' is not defined.\n", TOKEN_NAME[tokens[i].type], tokens[i].value),
                    tokens[i].macrorefs
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