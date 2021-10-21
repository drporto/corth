#ifndef CORTH_MACRO_REF_HPP_
#define CORTH_MACRO_REF_HPP_

#include "definitions.hpp"

#include "Location.hpp"

struct MacroRef {
    size_t macroindex;
    Location location;

    MacroRef(size_t _macroindex, const Location& _location);
};

#endif