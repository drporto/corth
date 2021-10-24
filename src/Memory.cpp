#include "Memory.hpp"

Memory::Memory(const std::string& _name, const Location& _location, size_t _address, size_t _size) :
    name(_name),
    location(_location),
    address(_address),
    size(_size) { }