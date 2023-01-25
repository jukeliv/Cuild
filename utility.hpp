#pragma once

#include <sstream>
#include <fstream>
#include <string>

void zero(void* ptr, size_t len)
{
    memset(ptr, 0, len);
}

std::string read(const char* path)
{
    std::ifstream file(path);

    std::string buf;
    std::string str;
    
    if(!file.is_open())
    {
        fprintf(stderr, "Couldn't read file %s\n", path);
        return NULL;
    }

    while(file.good())
    {
        std::getline(file, buf);
        str += buf + "\n";
    }

    file.close();
    
    str.push_back('\0');

    return str;
}

bool is_space(char check)
{
    if(check == ' ' || check == '\t' || check == '\n')
        return true;
    return false;
}