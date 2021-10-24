#ifndef CORTH_MEMORY_HPP_
#define CORTH_MEMORY_HPP_

#include <string>

#include "definitions.hpp"

#include "Location.hpp"

struct Memory {
    std::string name;
    Location location;
    size_t address;
    size_t size;

    Memory(const std::string& _name, const Location& _location, size_t _address, size_t _size);
};

#endif