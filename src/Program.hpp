#ifndef CORTH_PROGRAM_HPP_
#define CORTH_PROGRAM_HPP_

#include <vector>

#include "Definitions.hpp"

#include "Token.hpp"
#include "Macro.hpp"
#include "Command.hpp"

struct Program {
    std::vector<Token> tokens;
    std::vector<Macro> macros;
    std::vector<Command> commands;

    Program();
};

#endif