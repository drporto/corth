#include "Macro.hpp"

Macro::Macro(const std::string& _name, const Location& _location) :
    name(_name),
    location(_location),
    tokens() { }

std::ostream& operator<<(std::ostream& os, const Macro& macro) {
    os << "(" << macro.location << ") " << macro.name;
    //if (macro.parentmacro != -1) os << " FROM MACRO [" << macro.parentmacro << "]";
    os << "\n    COMMANDS:\n";
    for (size_t i = 0; i < macro.tokens.size(); i++) {
        std::cout << "    " << "[" << i << "]: " << macro.tokens[i];
        if (i != macro.tokens.size() - 1) std::cout << '\n';
    }
    return os;
}