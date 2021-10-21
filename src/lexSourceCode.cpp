#include "lexSourceCode.hpp"

void lexSourceCode(std::string filepath, Program* const program) {
    std::ifstream file(filepath);
    if (!file.is_open()) {
        throw CorthException(SYSTEM_ERROR_CODE,
            SYSTEM_ERROR_TAG +
            fmt::format("The file {} was not found.\n", filepath)
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

            Location location(filepath, line + 1, column + 1);
            tokenValue = lineString.substr(column, endcolumn - column);


            if (tokenValue.find("//") == 0) break;
            // ! PREPROCESSOR
            else if (isPreprocessor(tokenValue)) {
                tokens.emplace_back(TokenType::PREPROCESSOR, location, tokenValue);
                continue;
            }
            // ! INTEGER
            else if (isInteger(tokenValue)) {
                tokens.emplace_back(TokenType::INTEGER, location, tokenValue);
                continue;
            }
            // ! CHAR
            else if (isChar(tokenValue)) {
                tokens.emplace_back(TokenType::CHAR, location, tokenValue.substr(1, tokenValue.size() - 2));
                continue;
            }
            // ! STRING
            else if (isString(tokenValue)) {
                tokens.emplace_back(TokenType::STRING, location, tokenValue.substr(1, tokenValue.size() - 2));
                continue;
            }
            // ! KEYWORD
            else if (isKeyword(tokenValue)) {
                tokens.emplace_back(TokenType::KEYWORD, location, tokenValue);
                continue;
            }
            // ! WORD
            else {
                tokens.emplace_back(TokenType::WORD, location, tokenValue);
                continue;
            }
        }
    }
    file.close();
}