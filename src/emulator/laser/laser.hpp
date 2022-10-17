

#include "../base/base.cpp"
#include "../../laser/interface.hpp"

#include <future>

/// @brief This class to emulate laser.
/// To add new command:
/// 1. Add realisation of function
/// 2. Add command to enum Commands
/// 3. Add command name to ToString method
/// 4. Add command to CommandByName
/// 5. Add method to switch in responseFromRequest
class LaserEmulator : public LaserI, public EmulatorBase {
public:
    std::string convertResponseFromRequest(std::string& in);

    bool Start();
    bool Stop();
    bool GetStatus(int*);
    bool KeepAliveSignal();
    bool SetPower(int);
    bool SetPower(std::string);
    bool GetPower(int*);
    bool SetSillyMod(bool);
private:
    /// @brief realise silly mod process. Silly mod interprets all incoming command strings backwards. 
    /// @param in string to convert
    void convertFromSillyMod(std::string& in);


    std::atomic_bool emissionStatus = false;
    bool sillyMod = false;
    bool waitKal = false;
    int power = 0;
};