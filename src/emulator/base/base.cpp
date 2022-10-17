
#include "../interface.hpp"

#include <signal.h>

#include <stdlib.h>
#include <stdio.h>


#include <future>
#include <string>
#include <thread>
#include <iostream>


bool STOP_EMULATOR = false;
void signal_handler(int signal_num)
{
    STOP_EMULATOR = true;
}

/// @brief getline with stop by signal
/// @param in - stream with input data
/// @param str - string to storage data
/// @param simb - simbol end of the string
/// @return was stop signal or not
bool localGetLine(std::istream& in, std::string& str, char simb) {
    char ch;
    while(true) {
        in.get(ch);
        if (STOP_EMULATOR) return false;

        if (ch == simb) return true;
        str += ch;
    }
    return false;
}

/// @brief This class helps emulate any device.
/// To emulate a specific device function convertResponseFromRequest for this device must be realized.
class EmulatorBase : public EmulatorI {
public:
    void StartEmulator(std::istream& in, std::ostream& out) {
        signal(SIGTERM, signal_handler);
        signal(SIGINT, signal_handler);
        
        auto fut = std::async(std::launch::async, [&in, &out, this] {
            std::string str;
            while(true) {
                str.clear();
                
                if (!localGetLine(in, str, '\n')) break;

                std::string res = this->convertResponseFromRequest(str);
                out << res << std::string("\n");
            }
        });
    }
};

