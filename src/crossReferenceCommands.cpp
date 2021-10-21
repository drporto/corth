#include "crossReferenceCommands.hpp"

void crossReferenceCommands(Program* const program) {

    const std::vector<Macro>& macros = program->macros;
    std::vector<Command>& commands = program->commands;

    size_t ref_ip = 0;

    std::vector<size_t> stack;
    for (size_t ip = 0; ip < commands.size(); ip++) {
        const Command& command = commands[ip];
        switch (commands[ip].type) {
            // ! CONTROL FLOW
            // ! IF
            case CommandType::IF:
            {
                stack.push_back(ip); // ? IF_ip
                break;
            }
            // ! ELSE
            case CommandType::ELSE:
            {
                ref_ip = stack.back();
                switch (commands[ref_ip].type) {
                    case CommandType::DO:
                    {
                        size_t DO_ip = stack.back(); stack.pop_back();
                        ref_ip = stack.back();
                        switch (commands[ref_ip].type) {
                            case CommandType::IF:
                            {
                                // ? IF DO <ELSE>
                                //size_t IF_ip = stack.back();
                                commands[DO_ip].operand = ip + 1;
                                stack.push_back(ip);
                                break;
                                // ? IF ELSE
                            }
                            case CommandType::ELIF:
                            {
                                // ? IF [ELIF ... ELIF] DO <ELSE>
                                commands[DO_ip].operand = ip + 1;
                                stack.push_back(ip);
                                break;
                                // ? IF [ELIF ... ELIF] ELSE
                            }
                            default:
                            {
                                PREPROC_ERROR(
                                    commands[ip].token->location,
                                    fmt::format("The command ELSE must be inside a [EL]IF-DO block, from which a [EL]IF is missing.\n"),
                                    commands[ip].token->macrorefs
                                );
                                break;
                            }
                        }
                        break;
                    }
                    default:
                    {
                        PREPROC_ERROR(
                            commands[ip].token->location,
                            fmt::format("The command ELSE must be inside a [EL]IF-DO block, from which a DO is missing.\n"),
                            commands[ip].token->macrorefs
                        );
                        break;
                    }
                }
                break;
            }
            // ! ELIF
            case CommandType::ELIF:
            {
                ref_ip = stack.back();
                switch (commands[ref_ip].type) {
                    case CommandType::DO:
                    {
                        size_t DO_ip = stack.back(); stack.pop_back();
                        ref_ip = stack.back();
                        switch (commands[ref_ip].type) {
                            case CommandType::IF:
                            {
                                // ? IF DO <ELIF>
                                commands[DO_ip].operand = ip + 1;
                                stack.push_back(ip);
                                break;
                                // ? IF ELIF
                            }
                            case CommandType::ELIF:
                            {
                                // ? IF [ELIF ... ELIF] DO <ELIF>
                                commands[DO_ip].operand = ip + 1;
                                stack.push_back(ip);
                                break;
                                // ? IF [ELIF ... ELIF] ELIF
                            }
                            default:
                            {
                                PREPROC_ERROR(
                                    commands[ip].token->location,
                                    fmt::format("The command ELIF must be inside a [EL]IF-DO block, from which a [EL]IF is missing.\n"),
                                    commands[ip].token->macrorefs
                                );
                                break;
                            }
                        }
                        break;
                    }
                    default:
                    {
                        PREPROC_ERROR(
                            commands[ip].token->location,
                            fmt::format("The command ELIF must be inside a [EL]IF-DO block, from which a DO is missing.\n"),
                            commands[ip].token->macrorefs
                        );
                        break;
                    }
                }
                break;
            }
            // ! WHILE
            case CommandType::WHILE:
            {
                stack.push_back(ip); // ? WHILE_ip
                break;
            }
            // ! DO
            case CommandType::DO:
            {
                stack.push_back(ip); // ? DO_ip
                break;
            }
            // ! END
            case CommandType::END:
            {
                ref_ip = stack.back();
                switch (commands[ref_ip].type) {
                    case CommandType::ELSE:
                    {
                        // ? IF [ELIF ... ELIF] ELSE <END>
                        size_t LAST_ip = stack.back();
                        while (commands[LAST_ip].type != CommandType::IF) {
                            commands[LAST_ip].operand = ip + 1;
                            stack.pop_back();
                            LAST_ip = stack.back();
                        }
                        stack.pop_back();
                        commands[ip].operand = ip + 1;
                        break;
                        // ?
                    }
                    case CommandType::DO:
                    {
                        size_t DO_ip = stack.back(); stack.pop_back();
                        ref_ip = stack.back();
                        switch (commands[ref_ip].type) {
                            case CommandType::IF:
                            {
                                // ? IF DO <END>
                                //size_t IF_ip = stack.back();
                                stack.pop_back();
                                commands[DO_ip].operand = ip + 1;
                                commands[ip].operand = ip + 1;
                                break;
                                // ?
                            }
                            case CommandType::ELIF:
                            {
                                // ? IF [ELIF ... ELIF] ELIF <END>
                                size_t LAST_ip = stack.back();
                                while (commands[LAST_ip].type != CommandType::IF) {
                                    commands[LAST_ip].operand = ip + 1;
                                    stack.pop_back();
                                    LAST_ip = stack.back();
                                }
                                stack.pop_back();
                                commands[ip].operand = ip + 1;
                                break;
                                // ?
                            }
                            case CommandType::WHILE: {
                                // ? WHILE DO <END>
                                size_t WHILE_ip = stack.back(); stack.pop_back();
                                commands[DO_ip].operand = ip + 1;
                                commands[ip].operand = WHILE_ip + 1;
                                break;
                                // ?
                            }
                            default:
                            {
                                break;
                            }
                        }
                        break;
                    }
                    default:
                    {
                        break;
                    }
                }
                break;
            }
            default:
            {
                break;
            }
        }
    }
}