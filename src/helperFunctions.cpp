#include "helperFunctions.hpp"

bool isInteger(std::string str) {
    return (
        (str.find_first_of("0123456789") != std::string::npos)
        &&
        (
            (str.find_first_not_of("0123456789") == std::string::npos)
            ||
            ((str.find_last_of('-') == 0) && (str.find_first_not_of("0123456789", 1) == std::string::npos))
            )
        );
}

bool isChar(std::string str) {
    return
        (
            (str.find('\'') == 0 && str.rfind('\'') == 2)
            ||
            (str.find('\'') == 0 && str.find('\\') == 1 && str.rfind('\'') == 3)
            );
}

bool isString(std::string str) {
    return str.find('\"') == 0 && str.rfind('\"') == (str.size() - 1);
}

bool isKeyword(std::string str) {
    return (bool)COMMAND_TYPE[str];
}

bool isPreprocessor(std::string str) {
    return str.compare("INCLUDE") == 0 || str.compare("MACRO") == 0 || str.compare("MEMORY") == 0 || str.compare("END") == 0;
}

unsigned char pureStrToUnicodeChar(std::string purestr) {
    if (purestr.at(0) == '\\') return transf[purestr.at(1)];
    else return purestr.at(0);
}

std::string pureStrToUnicodeStr(std::string purestr) {
    std::string unicodestring;
    for (size_t i = 0; i < purestr.size(); i++) {
        if (purestr.at(i) == '\\') unicodestring.push_back(transf[purestr.at(++i)]);
        else unicodestring.push_back(purestr.at(i));
    }
    return unicodestring;
}