#include "Location.hpp"

Location::Location() : filepath(), line(), column() { };

Location::Location(const std::string& _filepath, int64 _line, int64 _column) :
    filepath(_filepath),
    line(_line),
    column(_column) { }

std::ostream& operator<<(std::ostream& os, const Location& location) {
    os << location.filepath << ':' << location.line << ':' << location.column;
    return os;
}