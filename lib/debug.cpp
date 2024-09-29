#include "debug.h"
#include <iostream>

void epaperapi::debug::DebugLog(std::string message) { std::cout << "[epaperapi]: " << message << std::endl << std::flush; }