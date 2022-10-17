#include <string>

class LaserI {
public:
    /// @brief Starts emission of the laser.
    /// @return false if emission is currently on
    virtual bool Start() = 0;
    
    /// @brief Stop emission of the laser.
    /// @return false if emission is currently off
    virtual bool Stop() = 0;

    /// @brief Returns the emission status of the laser.
    /// @param Value to get status of the laser.
    /// @return false has some error in process
    virtual bool GetStatus(int*) = 0;

    /// @brief keep-alive signals for longer than 5 seconds, the laser automatically turns
    /// @return false if emission is currently off or keep-alive signals in process now
    virtual bool KeepAliveSignal() = 0;

    /// @brief Sets the current laser power
    /// @param  level of power in range 1-100. for string uses mask "|num" (4 example, "|1")
    /// @return false if emission is currently off or level not in range.
    virtual bool SetPower(int) = 0;
    virtual bool SetPower(std::string) = 0;

    /// @brief Return the current laser power
    /// @param  Value to get current laser power
    /// @return false has some error in process
    virtual bool GetPower(int*) = 0;


    /// @brief Set/unset SillyMod
    /// @param  true|false (for on|off mod)
    /// @return false has some error in process
    virtual bool SetSillyMod(bool) = 0;
};