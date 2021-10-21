#ifndef CORTH_CUSTOM_EXCEPTION_HPP_
#define CORTH_CUSTOM_EXCEPTION_HPP_

#include <exception>
#include <string>

#include <fmt/core.h>
#include <fmt/color.h>

#include "definitions.hpp"

#define LOCATION_STYLE fmt::fg(fmt::color::floral_white)
#define PREPROC_ERROR_STYLE fmt::fg(fmt::color::orange) | fmt::emphasis::bold
#define RUNTIME_ERROR_STYLE fmt::fg(fmt::color::crimson) | fmt::emphasis::bold
#define SYSTEM_ERROR_STYLE fmt::fg(fmt::color::gold) | fmt::emphasis::bold
#define MACRO_STYLE fmt::fg(fmt::color::royal_blue) | fmt::emphasis::bold
#define INFO_STYLE fmt::fg(fmt::color::lime_green) | fmt::emphasis::bold

#define LOCATION_TAG(LOC) fmt::format(LOCATION_STYLE, "({}:{}:{}): ", LOC.filepath, LOC.line, LOC.column)
#define PREPROC_ERROR_TAG fmt::format(PREPROC_ERROR_STYLE, "[PREPROC ERROR] ")
#define RUNTIME_ERROR_TAG fmt::format(RUNTIME_ERROR_STYLE, "[RUNTIME ERROR] ")
#define SYSTEM_ERROR_TAG fmt::format(SYSTEM_ERROR_STYLE, "[SYSTEM ERROR] ")
#define MACRO_TAG fmt::format(MACRO_STYLE, "[MACRO] ")
#define INFO_TAG fmt::format(INFO_STYLE, "[INFO] ")

#define PREPROC_ERROR_CODE 1
#define RUNTIME_ERROR_CODE 2
#define SYSTEM_ERROR_CODE 3

#define EXPAND_MACROS(EM, MR) for (size_t i = 0; i < MR.size(); i++) EM += (LOCATION_TAG(MR[MR.size() - 1 - i].location) + MACRO_TAG + fmt::format("Expanded from {}.\n", macros[MR[MR.size() - 1 - i].macroindex].name));

class CorthException : public std::exception {
private:
    std::string message;
    int errorCode;
public:
    CorthException(int _errorCode, const std::string& _message);

    const char* what() const;

    const std::string& getMessage();
    const int& getErrorCode();
};

//#define TRY(F) try { F; } catch (CustomException& e) { std::cerr << e.what() << std::endl; }
// #define ASSERT(COMP, M, ...) if(!(COMP)) throw CPP_EXCEPTION(M, ##__VA_ARGS__)

#endif