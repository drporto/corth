#ifndef CORTH_HELPER_FUNCTIONS_HPP_
#define CORTH_HELPER_FUNCTIONS_HPP_

#include <map>
#include <string>

#include "definitions.hpp"

#include "Command.hpp"

static std::map<unsigned char, unsigned char> transf = {
    {'n','\n'},
    {'\'','\''},
    {'\"','\"'},
    {'\\','\\'},
};

bool isInteger(std::string str);
bool isChar(std::string str);
bool isString(std::string str);
bool isKeyword(std::string str);
bool isMeta(std::string str);

byte pureStrToUnicodeChar(std::string purestr);
std::string pureStrToUnicodeStr(std::string purestr);

#endif