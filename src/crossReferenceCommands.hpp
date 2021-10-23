#ifndef CORTH_CROSS_REFERENCE_COMMANDS_HPP_
#define CORTH_CROSS_REFERENCE_COMMANDS_HPP_

#include <vector>

#include "definitions.hpp"
#include "CorthException.hpp"

#include "Program.hpp"

void crossReferenceCommands(Program* const program);

void crossReferenceBlocks(const std::vector<Macro>& macros, std::vector<Command>& commands, std::vector<size_t>& ips, size_t end);

#endif