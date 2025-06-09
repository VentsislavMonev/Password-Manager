#ifndef UTILITIES
#define UTILITIES

#include <string>

bool validateString(const std::string& string)
{
    if(string.length()==0) return false;

    char first =' ';
    char last ='~';
    size_t length = string.length();
    for (size_t i = 0; i < length; i++)
    {
        if(string[i] < first || string[i]> last)
        {
            return false;
        }
    }
    return true;
}

#endif