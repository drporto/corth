#ifndef CORTH_LOCATION_HPP_
#define CORTH_LOCATION_HPP_

#include <iostream>
#include <string>

#include "Definitions.hpp"

struct Location {
    std::string filepath;
    int64 line;
    int64 column;

    Location();
    Location(const std::string* const, int64, int64);
};

std::ostream& operator<<(std::ostream& os, const Location& location);

#endif