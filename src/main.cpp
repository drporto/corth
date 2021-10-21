#include <iostream>
#include <chrono>

#include <fmt/core.h>
#include <fmt/color.h>

#include "definitions.hpp"
#include "CorthException.hpp"

#include "Program.hpp"

#include "lexSourceCode.hpp"
#include "preprocessTokens.hpp"
#include "lexTokens.hpp"
#include "crossReferenceCommands.hpp"
#include "simulateProgram.hpp"

struct RuntimeStatus {
    int exitCode = 0;
    bool simulation = false;
    bool time = false;
    double preprocessorTime = 0;
    double simulationTime = 0;
    bool filepathset = false;
    std::string filepath = "";
};

int main(int argc, char* argv[]) {
    RuntimeStatus runtimeStatus;
    Program program;

    try {
        for (size_t i = 1; i < argc; i++) {
            std::string arg = argv[i];
            if (arg.find("--") == 0 && !runtimeStatus.filepathset) {
                if (arg.compare("--simulate") == 0) { runtimeStatus.simulation = true; continue; }
                else if (arg.compare("--time") == 0) { runtimeStatus.time = true; continue; }
                else throw CorthException(SYSTEM_ERROR_CODE, SYSTEM_ERROR_TAG + fmt::format("{} is not a valid command line argument\n", arg));
            }
            else {
                if (!runtimeStatus.filepathset) {
                    runtimeStatus.filepath = arg;
                    runtimeStatus.filepathset = true;
                    continue;
                }
                break;
            }
        }
        auto start = std::chrono::high_resolution_clock::now();
        lexSourceCode(runtimeStatus.filepath, &program);
        preprocessTokens(&program);
        lexTokens(&program);
        crossReferenceCommands(&program);
        auto end = std::chrono::high_resolution_clock::now();
        runtimeStatus.preprocessorTime = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count() * 1e-9;

#ifdef DEBUG
        std::cout << "TOKENS: \n";
        for (size_t i = 0; i < program.tokens.size(); i++) std::cout << "[" << i << "]: " << program.tokens[i] << '\n';
        std::cout << std::endl;

        // std::cout << "MACROS: \n";
        // for (size_t i = 0; i < macros.size(); i++) std::cout << "[" << i << "]: " << macros[i] << '\n';
        // std::cout << std::endl;

        // std::cout << "MEMORY: \n";
        // for (size_t i = 0; i < memories.size(); i++) std::cout << "[" << i << "]: " << memories[i] << '\n';
        // std::cout << std::endl;

        std::cout << "COMMANDS: \n";
        for (size_t i = 0; i < program.commands.size(); i++) std::cout << "[" << i << "]: " << program.commands[i] << '\n';
        std::cout << "----------" << std::endl;
#endif

        start = std::chrono::high_resolution_clock::now();
        runtimeStatus.exitCode = simulateProgram(&program);
        end = std::chrono::high_resolution_clock::now();
        runtimeStatus.simulationTime = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count() * 1e-9;

    }
    catch (CorthException& e) {
        runtimeStatus.exitCode = e.getErrorCode();
        std::cerr << e.getMessage() << std::endl;
    }

    if (runtimeStatus.time) {
        if (runtimeStatus.exitCode == 0)std::cout << '\n';
        std::cout << fmt::format("Preprocessor took {:.9f} seconds", runtimeStatus.preprocessorTime) << std::endl;
        std::cout << fmt::format("  Simulation took {:.9f} seconds", runtimeStatus.simulationTime) << std::endl;
    }

    if (runtimeStatus.exitCode != 0)
        std::cout << fmt::format("Program exited ") << fmt::format(fmt::fg(fmt::color::indian_red), "abnormally") << fmt::format(" with code {}", runtimeStatus.exitCode) << std::ends;
    else
        std::cout << fmt::format("Program exited ") << fmt::format(fmt::fg(fmt::color::pale_green), "successfully") << fmt::format(" with code {}", runtimeStatus.exitCode) << std::ends;

    return runtimeStatus.exitCode;
}