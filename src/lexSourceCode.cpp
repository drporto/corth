#include "lexSourceCode.hpp"

void lexSourceCode(std::string filepath, Program* const program) {
    std::ifstream file(filepath);
    if (!file.is_open()) {
        throw CorthException(2,
            SYSTEM_TAG +
            fmt::format("The file {} was not found", filepath)
        );
    }

    std::vector<Token>& tokens = program->tokens;

    std::string lineString;

    for (size_t line = 0; getline(file, lineString); line++) {
        if (lineString.empty()) continue;

        size_t column(0);
        size_t endcolumn(0);

        std::string tokenValue;

        while (true) {
            column = endcolumn;
            column = lineString.find_first_not_of(" ", column);
            if (column == std::string::npos) break;
            if (lineString[column] == '\'' || lineString[column] == '\"') {
                for (endcolumn = column + 1; lineString[endcolumn] != lineString[column]; endcolumn++)
                    if (lineString[endcolumn] == '\\')
                        endcolumn++;
                endcolumn++;
            }
            else {
                endcolumn = lineString.find(' ', column);
            }

            Location location = Location(filepath, line + 1, column + 1);
            tokenValue = lineString.substr(column, endcolumn - column);

            // ! TokenType
            // * INTEGER
            if (tokenValue.find("//") == 0) break;
            else if (isInteger(tokenValue)) {
                tokens.emplace_back(TokenType::INTEGER, &location, &tokenValue);
                continue;
            }
            // * CHAR
            else if (isChar(tokenValue)) {
                tokenValue = tokenValue.substr(1, tokenValue.size() - 2);
                tokens.emplace_back(TokenType::CHAR, &location, &tokenValue);
                continue;
            }
            // * STRING
            else if (isString(tokenValue)) {
                tokenValue = tokenValue.substr(1, tokenValue.size() - 2);
                tokens.emplace_back(TokenType::STRING, &location, &tokenValue);
                continue;
            }
            // * KEYWORD
            else if (isKeyword(tokenValue)) {
                tokens.emplace_back(TokenType::KEYWORD, &location, &tokenValue);
                continue;
            }
            // * META
            else if (isMeta(tokenValue)) {
                tokens.emplace_back(TokenType::META, &location, &tokenValue);
                continue;
            }
            // * WORD
            else {
                tokens.emplace_back(TokenType::WORD, &location, &tokenValue);
                continue;
            }
        }
    }
    file.close();
}