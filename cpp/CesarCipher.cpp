#include <stdexcept>
#include "CesarCipher.hpp"
#include "DictionaryCipher.hpp"

CesarCipher::CesarCipher(short _shift)
{
    setShift(_shift);
}

std::string CesarCipher::encrypt(const std::string &text) const
{
    if(!validate(text))
        throw std::invalid_argument("Invalid password to encrypt only allowed charachters are small and capital letters, numbers, and the symbols: #; $; %; &; '; (; ); *; +; ,; -; .; /");

    std::string result = "";

    for (size_t i = 0; i < text.size(); i++)
    {
        result+=ShiftChar(text[i], shift);
    }
    return result;    
}

std::string CesarCipher::decrypt(const std::string &pass) const
{
    std::string result = "";

    for (size_t i = 0; i < pass.size(); i++)
    {
        result+=ShiftChar(pass[i], -shift);
    }
    return result;
}

std::string CesarCipher::getType() const
{
    return "Cesar";
}

short CesarCipher::getShift() const
{
    return shift;
}

void CesarCipher::setShift(short _shift)
{
    shift = mod(_shift);
}

char CesarCipher::ShiftChar(char c, short shift) const
{
    if(shift==0)
    {
        return c;
    }
    if (c>='A' && c<='Z')
    {
        return mod(c-'A' + shift)+'A';
    }
    else if(c>='a' && c<='z')
    {
        int a = mod(c-'a' + shift)+'a';
        return a;
    }
    else
    {
        return c;
    }
}

short CesarCipher::mod(short a) const
{
    const short alphabetLength = 26; 
    return (a % alphabetLength + alphabetLength) % alphabetLength;
}
