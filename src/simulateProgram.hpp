#ifndef CORTH_SIMULATE_PROGRAM_HPP_
#define CORTH_SIMULATE_PROGRAM_HPP_

#include <iostream>
#include <vector>

#include <fmt/core.h>
#include <fmt/color.h>

#include "definitions.hpp"
#include "helperFunctions.hpp"

#include "CorthException.hpp"
#include "Program.hpp"

int simulateProgram(Program* const program);

#endif