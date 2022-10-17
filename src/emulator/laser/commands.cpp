
#include <map>
#include <string>

const char* DEFAULT_RESPONSE("UK!");

/// @brief All commands that work with laser
enum Commands {
    STR, 
    STP, 
    ST, 
    KAL,
    PWSet,
    PWGet,
    ESM, 
    DSM,
};

constexpr const char* ToString(Commands v) {
    switch (v)
    {
    case Commands::STR: return "STR";
    case Commands::STP: return "STP";
    case Commands::ST : return "ST?";
    case Commands::KAL: return "KAL";
    case Commands::PWSet: return "PW=";
    case Commands::PWGet: return "PW?";
    case Commands::ESM: return "ESM";
    case Commands::DSM: return "DSM";
    default: return DEFAULT_RESPONSE;
    }
}

std::string to_string(const Commands& v) {
    return ToString(v);
}

const std::map<std::string, Commands> CommandByName = {
    {"STR", Commands::STR},
    {"STP", Commands::STP},
    {"ST?", Commands::ST },
    {"KAL", Commands::KAL},
    {"PW=", Commands::PWSet},
    {"PW?", Commands::PWGet},
    {"ESM", Commands::ESM},
    {"DSM", Commands::DSM},
};
