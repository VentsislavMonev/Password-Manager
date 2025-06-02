#include "CesarCipher.hpp"
#include <stdexcept>

CesarCipher::CesarCipher(short _shift)
{
    setShift(_shift);
}

std::string CesarCipher::encrypt(const std::string &text) const
{
    if(!validate(text))
        throw std::invalid_argument("Invalid password to encrypt only allowed charachters are the chars from 32 to 126");

    std::string result = "";

    for (size_t i = 0; i < text.size(); i++)
    {
        result+=ShiftChar(text[i], shift);
    }
    return result;    
}

std::string CesarCipher::decrypt(const std::string &pass) const
{
    if(!validate(pass))
        throw std::invalid_argument("This password wasnt encrypted by this cipher! It couldnt be decrypted.");

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

char CesarCipher::ShiftChar(char c, short offset) const
{
    // this is the code if i have to shift only letters

    // if(offset==0)
    // {
    //     return c;
    // }
    // if (c>='A' && c<='Z')
    // {
    //     return mod(c-'A' + offset)+'A';
    // }
    // else if(c>='a' && c<='z')
    // {
    //     int a = mod(c-'a' + offset)+'a';
    //     return a;
    // }
    // else
    // {
    //     return c;
    // }

    if(offset!=0)
        return mod(c-' ' + offset)+' ';
    else return c;
}

short CesarCipher::mod(short a) const
{
    const short allowedSymbolsCount = '~' - ' '; 
    return (a % allowedSymbolsCount + allowedSymbolsCount) % allowedSymbolsCount;
}
