#ifndef UTILITIES
#define UTILITIES

#include <string>

bool validateString(const std::string& string)
{
    size_t length = string.length();
    for (size_t i = 0; i < length; i++)
    {
        if(string[i] < ' ' || string[i]> '~')
        {
            return false;
        }
    }
    return true;
}

#endif