//Here i store all the things for releasing this, if you are messing around and not contributing, you can delete this file
#pragma once

#include <string>

#ifndef VER
    #define VER "1.1.0"
#endif

#ifndef BT
    #define BT "DEBUG"      // STABLE - RELEASE - DEBUG
#endif

#ifndef TARGET
    #define TARGET "Win"
#endif

std::string build_data()
{
    std::string str;
    str += TARGET;
    str += "-";
    str += VER;
    str += "-";
    str += BT;
    
    return str;
}