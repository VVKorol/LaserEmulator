#include <iostream>

#include "src/emulator/laser/laser.cpp"


int main() {

    // Create variable Emulator
    LaserEmulator le;
    // Start Emulator with stream in and out.
    le.StartEmulator(std::cin, std::cout);

    return 0;
}