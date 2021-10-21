#ifndef CORTH_MACRO_HPP_
#define CORTH_MACRO_HPP_

#include <vector>

#include "definitions.hpp"

#include "Location.hpp"
#include "Token.hpp"

struct Macro {
    std::string name;
    Location location;
    std::vector<Token> tokens;

    Macro(const std::string& _name, const Location& _location);
};

std::ostream& operator<<(std::ostream& os, const Macro& macro);

#endif