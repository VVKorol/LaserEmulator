#include "laser.hpp"
#include "commands.cpp"

#include <algorithm>
#include <thread>
#include <future>
#include <iostream>

std::pair<int, std::string> getIntValue(const std::string& str);

const int KAL_SIGNAL_TIME(5);

// emulate laser methods
bool LaserEmulator::Start() {
    if (this->emissionStatus.load()) {
        return false;
    }

    this->emissionStatus.exchange(true);
    return true;
}

bool LaserEmulator::Stop() {
    if (!this->emissionStatus.load()) {
        return false;
    }

    this->emissionStatus.exchange(false);
    return true;
}

bool LaserEmulator::GetStatus(int * val) {
    *val = this->emissionStatus.load() ? 1 : 0;
    return true;
}
std::future<void> fut;
bool LaserEmulator::KeepAliveSignal() {
    if (this->waitKal) return false;
    if (!this->emissionStatus.load()) return false;
    fut = std::async(std::launch::async, [this]{
        std::this_thread::sleep_for(std::chrono::seconds(KAL_SIGNAL_TIME));
        this->emissionStatus.exchange(false);
        this->waitKal = false;
    });
        
    this->waitKal = true;
    return true;
}

bool LaserEmulator::GetPower(int* val) {
    *val = this->emissionStatus.load() ? this->power : 0;
    return true;
}

bool LaserEmulator::SetPower(std::string val) {
    auto [valInt, subStr] = getIntValue(val);
    if (subStr.size() != 0) return false;

    return this->SetPower(valInt);
}

bool LaserEmulator::SetPower(int val) {
    if (!this->emissionStatus.load()) return false;
    if (val > 100) return false;

    this->power = val;

    return true;
}

bool LaserEmulator::SetSillyMod(bool sillyMod) {
    this->sillyMod = sillyMod;
    return true;
}

///////////////////////////
/////// Emulator functions:

void LaserEmulator::convertFromSillyMod(std::string& in) {
    std::reverse(in.begin(), in.end());
}

std::string LaserEmulator::convertResponseFromRequest(std::string& in) {
    if (in.size() < 3) {
        return DEFAULT_RESPONSE;
    }

    if (this->sillyMod) {
        this->convertFromSillyMod(in);
    }

    auto commandStr = in.substr(0, 3);
    auto it = CommandByName.find(commandStr);
    if (it == CommandByName.end()) return DEFAULT_RESPONSE;
    auto command = it->second;

    bool res;
    int* addValue = nullptr;

    switch (command)
    {
        case Commands::STR: 
            res = this->Start();
            break;
        case Commands::STP:
            res = this->Stop();
            break;
        case Commands::ST :
            addValue = new int;
            res = this->GetStatus(addValue);
            break;
        case Commands::KAL:
            res = this->KeepAliveSignal();
            break;
        case Commands::PWSet:
            res = this->SetPower(in.substr(3, in.size()-3));
            break;
        case Commands::PWGet: 
            addValue = new int;
            res = this->GetPower(addValue);
            break;
        case Commands::ESM: 
            res = this->SetSillyMod(true);
            break;
        case Commands::DSM: 
            res = this->SetSillyMod(false);
            break;
        default: return DEFAULT_RESPONSE;
    }

    std::string outStr = ToString(command);

    if (addValue != nullptr) {
        outStr += "|";
        outStr += std::to_string(*addValue);
    }

    outStr += res ? "#" : "!";

    return outStr;
}

// getIntValue - return int value from string and next string.
// All numbers start with "|" simbol.
// If string include some string after number - this substring is returned
// example: 
//// One number: val, ss = getIntValue("|34"); // val == 34, ss == ""
//// Two number: 
//       val1, ss = getIntValue("|34|66"); // val1 == 34, ss == "|66"
//       val2, ss = getIntValue(ss); // val1 = 34, val2 == 66, ss == ""
std::pair<int, std::string> getIntValue(const std::string& str) {
    if (str.size() < 2) return {-1, str};
    if (str[0] != '|') return {-1, str};
    
    std::string::size_type sz;
    auto s = str.substr(1, str.size() - 1);
    
    int num = std::stoi (s,&sz);
    return {num, s.substr(sz)};
}
