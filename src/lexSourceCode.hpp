#ifndef CORTH_LEX_SOURCE_CODE_HPP_
#define CORTH_LEX_SOURCE_CODE_HPP_

#include <fstream>
#include <string>
#include <vector>

#include "definitions.hpp"
#include "helperFunctions.hpp"

#include "CorthException.hpp"
#include "Program.hpp"

void lexSourceCode(std::string filepath, Program* const program);

void lexSourceCode(std::string filepath, std::vector<Token>& tokens);

#endif