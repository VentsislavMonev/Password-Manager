#include "Cipher.hpp"

bool Cipher::validate(const std::string &text) const
{
    char first =' ';
    char last ='~';
    size_t length = text.size();
    for (size_t i = 0; i < length; i++)
    {
        if(text[i] < first || text[i]> last)
        {
            return false;
        }
    }
    return true;
    
}
//TODO da izpolzvam validate ot utilities?