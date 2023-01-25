#include "../include/utility.h"

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