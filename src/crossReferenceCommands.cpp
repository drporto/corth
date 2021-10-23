#include "crossReferenceCommands.hpp"

void crossReferenceCommands(Program* const program) {

    const std::vector<Macro>& macros = program->macros;
    std::vector<Command>& commands = program->commands;
    std::vector<size_t> ips;

    for (size_t i = 0; i < commands.size(); i++) {
        CommandType ct = commands[i].type;
        if (
            ct == CommandType::IF ||
            ct == CommandType::ELSE ||
            ct == CommandType::ELIF ||
            ct == CommandType::WHILE ||
            ct == CommandType::DO ||
            ct == CommandType::END ||
            ct == CommandType::BREAK
            )
            ips.push_back(i);
    }
    if (!ips.empty()) {
        std::reverse(ips.begin(), ips.end());
        crossReferenceBlocks(macros, commands, ips, 0);
    }
}

// !    IF,
// !    ELSE,
// !    ELIF,
// !    WHILE,
// !    DO,
// !    END,

void crossReferenceBlocks(const std::vector<Macro>& macros, std::vector<Command>& commands, std::vector<size_t>& ips, size_t end) {
#ifdef DEBUG
    std::cout << LOCATION_TAG(commands[ips[end]].token->location) << ips[end] << ": " << COMMAND_NAME[commands[ips[end]].type] << " " << commands[ips[end]].operand << std::endl;
#endif
    size_t start = end + 1;
    std::vector<size_t> ips_break;
    while (commands[ips[start]].type != CommandType::IF && commands[ips[start]].type != CommandType::WHILE) {
        if (commands[ips[start]].type == CommandType::END) crossReferenceBlocks(macros, commands, ips, start);
        else start++;
    }
#ifdef DEBUG
    std::cout << LOCATION_TAG(commands[ips[start]].token->location) << ips[start] << ": " << COMMAND_NAME[commands[ips[start]].type] << " " << commands[ips[start]].operand << std::endl;
#endif
    switch (commands[ips[start]].type) {
        case CommandType::IF:
        {
            commands[ips[end]].operand = ips[end] + 1;
            for (size_t i = end + 1; i < start; i++) {
                switch (commands[ips[i]].type) {
                    case CommandType::ELSE:
                    {
                        commands[ips[i]].operand = ips[end] + 1;
                        break;
                    }
                    case CommandType::ELIF:
                    {
                        commands[ips[i]].operand = ips[end] + 1;
                        break;
                    }
                    case CommandType::DO:
                    {
                        if (commands[ips[i - 1]].type != CommandType::BREAK)
                            commands[ips[i]].operand = ips[i - 1] + 1;
                        else
                            commands[ips[i]].operand = ips[i - 2] + 1;
                        break;
                    }
                    case CommandType::BREAK:
                    {
                        ips_break.push_back(ips[i]);
                        break;
                    }
                    default:
                    {
                        break;
                    }
                }
            }
            break;
        }
        case CommandType::WHILE:
        {
            commands[ips[end]].operand = ips[start] + 1;
            for (size_t i = end + 1; i < start; i++) {
                switch (commands[ips[i]].type) {
                    case CommandType::DO:
                    {
                        commands[ips[i]].operand = ips[end] + 1;
                        break;
                    }
                    case CommandType::BREAK:
                    {
                        commands[ips[i]].operand = ips[end] + 1;
                        break;
                    }
                    default:
                    {
                        break;
                    }
                }
            }
            break;
        }
        default:
        {
            PREPROC_ERROR(
                commands[ips[start]].token->location,
                fmt::format("crossReferenceBlocks: The command {} is not implemented yet.\n", COMMAND_NAME[commands[ips[start]].type]),
                commands[ips[start]].token->macrorefs
            );
        }
    }
#ifdef DEBUG
    for (int64 i = (int64)start; i >= (int64)end; i--) {
        std::cout << "    " << LOCATION_TAG(commands[ips[i]].token->location) << ips[i] << ": " << COMMAND_NAME[commands[ips[i]].type] << " " << commands[ips[i]].operand << std::endl;
    }
#endif
    if (!ips.empty()) {
        ips.erase(ips.begin() + end, ips.begin() + start + 1);
        ips.insert(ips.begin() + end, ips_break.begin(), ips_break.end());
    }
    }