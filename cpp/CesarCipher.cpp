#include "CesarCipher.hpp"

std::string CesarCipher::encrypt(const std::string &text) const
{
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

char CesarCipher::ShiftChar(char c, short shift) const
{
    char newChar = ' ';
    if (c>=65 && c<=90)
    {
        newChar = mod((c-65 + shift),26)+65;
    }
    else if(c>=97 && c<=122)
    {
        newChar = mod((c-97 + shift),26)+97;
    }
    else
    {
        newChar=c;
    }
    return newChar;
}

short CesarCipher::mod(short a, short b) const
{
    return (a % b + b) % b;
}
