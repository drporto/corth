#ifndef CORTH_PREPROCESS_TOKENS_HPP_
#define CORTH_PREPROCESS_TOKENS_HPP_

#include <string>

#include "definitions.hpp"
#include "helperFunctions.hpp"
#include "CorthException.hpp"

#include "Program.hpp"
#include "MacroRef.hpp"

#include "lexSourceCode.hpp"

void preprocessTokens(Program* const program);

#endif