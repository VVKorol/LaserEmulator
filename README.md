# LaserEmulator
LaserEmulator has 2 basic interface - laser and emulator. 
Laser - is real object with basic function.
You can found command in file commands.

I will not list the entire list of commands and their operation conditions, because if you are interested in this, most likely you sent it to me. =)

Emulator - is Basic class to emulate any device that work with stream.

# How it works

// Create variable Emulator
LaserEmulator le;
// Start Emulator with stream in and out.
le.StartEmulator(std::cin, std::cout);

# How to modify
## New Emulator
1. Create new Class based on EmulatorBase.
2. Realize convertResponseFromRequest in this class

## New Function in LaserEmulator
0. Add New fucntion to LaserI (laser interface)
1. Add realisation of the function to LaserEmulator
2. Add command to enum Commands
3. Add command name to ToString method
4. Add command to CommandByName
5. Add method to switch in responseFromRequest
