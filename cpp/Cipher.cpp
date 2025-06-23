#include "Cipher.hpp"
#include "CesarCipher.hpp"
#include "HillCipher.hpp"
#include "DictionaryCipher.hpp"

Cipher *Cipher::createCipher(CipherType cipherType, const std::string &cipherConfig)
{
    Cipher* newCipher = nullptr;
        
    switch (cipherType) 
    {
        case CipherType::CESAR:
            newCipher = new CesarCipher();
            break;
        case CipherType::DICTIONARY:
            newCipher = new DictionaryCipher();
            break;
        case CipherType::HILL:
            newCipher = new HillCipher();
            break;
        default:
            throw std::runtime_error("Unknown cipher type");
    }
    
    newCipher->setConfig(cipherConfig);
    return newCipher;
}

Cipher *Cipher::createCipher(const std::string &cipherTypeStr, const std::string &cipherConfig)
{
    return createCipher(Cipher::typeFromString(cipherTypeStr), cipherConfig);
}

std::string Cipher::getTypeString() const
{
    return Cipher::typeToString(getType());
}

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

CipherType Cipher::typeFromString(const std::string &str)
{
    if (str == "CESAR") return CipherType::CESAR;
    if (str == "DICTIONARY") return CipherType::DICTIONARY;
    if (str == "HILL") return CipherType::HILL;
    throw std::runtime_error("Unknown cipher type: " + str);
}

std::string Cipher::typeToString(CipherType type)
{
    switch (type) 
    {
        case CipherType::CESAR: return "CESAR";
        case CipherType::DICTIONARY: return "DICTIONARY";
        case CipherType::HILL: return "HILL";
        default: throw std::runtime_error("Invalid cipher type");
    }
}