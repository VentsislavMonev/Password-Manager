#include "Cipher.hpp"

bool Cipher::validate(const std::string &text) const
{
    size_t length = text.size();
    for (size_t i = 0; i < length; i++)
    {
        // The last line includes special charachters such as '#', '$', '(', ')', '+' 
        // and so on in the ascii table all the way to '0' so thats why itscombined in the last condition
        if( (text[i]<'a' || text[i]>'z') &&
            (text[i]<'A' || text[i]>'Z') &&
            (text[i]<'#' || text[i]>'9'))
        {
            return false;
        }
    }
    return true;
    
}