#include "DictionaryCipher.hpp"
#include <stdexcept>

void DictionaryCipher::setDictionary(const std::string& textDictionary)
{
    if(textDictionary.length() == 0)
        throw std::invalid_argument("Dictionary text is empty!");
    
    size_t length = textDictionary.length();
    for (size_t i = 0; i < length; ++i)
    {
        insertUnique(textDictionary[i]);    
    }
}

void DictionaryCipher::insertUnique(char value)
{
    for (char v : dictionary) {
        if (v == value) {
            return;
        }
    }
    dictionary.push_back(value);
}

CipherType DictionaryCipher::getType() const
{
    return CipherType::DICTIONARY;
}

DictionaryCipher::DictionaryCipher(const std::string &_dictionaryText)
{
    setDictionary(_dictionaryText);
    keyText = _dictionaryText;
}

std::string DictionaryCipher::encrypt(const std::string &text) const
{
    if(!isTextInDictionary(text))
        throw std::invalid_argument("Invalid password to encrypt! Only allowed charachters are the ones that are in the dictionary text");
    
    std::string result = "";
    size_t dictionaryLength = dictionary.size();
    size_t textLength = text.length();
    for (size_t i = 0; i < textLength; ++i)
    {
        for (size_t j = 0; j < dictionaryLength; ++j)
        {
            if(text[i]==dictionary[j])
            {
                result.push_back(static_cast<char>(j));
            }
        }
    }
    return result;
}

std::string DictionaryCipher::decrypt(const std::string &pass) const
{
    if(!checkForMissMatch(pass))
        throw std::invalid_argument("Password couldn`t be decrypted. Possibly wasnt encrypted from this instance");

    std::string result="";
    size_t length = pass.length();
    for (size_t i = 0; i < length; ++i)
    {
        result+=dictionary[pass[i]];
    }
    return result;
}

bool DictionaryCipher::isTextInDictionary(const std::string &text) const
{
    size_t length = text.size();
    for (size_t i = 0; i < length; ++i)
    {
        if(!containsChar(text[i]))
        {
            return false;
        }
    }
    return true;
}

bool DictionaryCipher::checkForMissMatch(const std::string &text) const
{
    size_t dictionaryLength= dictionary.size();
    size_t textlength = text.length();
    for (size_t i = 0; i < textlength; ++i)
    {
        if(text[i]>=dictionaryLength)
            return false;
    }
    return true;
    
}

bool DictionaryCipher::containsChar(char c)const
{
    size_t length = dictionary.size();
    for (size_t i = 0; i < length; ++i)
    {
        if(dictionary[i]==c)
            return true;
    }
    return false;
    
}

std::string DictionaryCipher::getConfig() const
{
    return keyText;
}

void DictionaryCipher::setConfig(const std::string &config)
{
    setDictionary(config);
    keyText=config;
}