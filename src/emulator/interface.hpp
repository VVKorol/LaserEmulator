// #pragma once

#include <iostream>
#include <string>

class EmulatorI {
public:
      virtual void StartEmulator(std::istream& in, std::ostream& out) = 0;
      virtual std::string convertResponseFromRequest(std::string& in) = 0;
};