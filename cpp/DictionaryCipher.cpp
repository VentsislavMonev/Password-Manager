#include <stdexcept>
#include "DictionaryCipher.hpp"

void DictionaryCipher::setDictionary(const std::string& textDictionary)
{
    if(!validate(textDictionary))
        throw std::invalid_argument("Invalid password to encrypt only allowed charachters are small and capital letters, numbers, and the symbols: #; $; %; &; '; (; ); *; +; ,; -; .; /");

    size_t length = textDictionary.length();
    for (size_t i = 0; i < length; i++)
    {
        insertUnique(textDictionary[i]);     //TODO do i somehow need to add a validation for textDictionary?
    }
}

// If the value is in there dont add anything so it doesnt duplicate
void DictionaryCipher::insertUnique(char value)
{
    for (char v : dictionary) {
        if (v == value) {
            return;
        }
    }
    dictionary.push_back(value);
}

std::string DictionaryCipher::getType() const
{
    return "Dictionary";
}

DictionaryCipher::DictionaryCipher(const std::string &_dictionaryText)
{
    setDictionary(_dictionaryText);
}

std::string DictionaryCipher::encrypt(const std::string &text) const
{
    if(!validate(text))
        throw std::invalid_argument("Invalid password to encrypt only allowed charachters are small and capital letters, numbers, and the symbols: #; $; %; &; '; (; ); *; +; ,; -; .; /");

    std::string result = "";
    size_t dictionaryLength = dictionary.size();
    size_t textLength = text.length();
    for (size_t i = 0; i < textLength; i++)
    {
        for (size_t j = 0; j < dictionaryLength; j++)
        {
            if(text[i]==dictionary[j])
            {
                result.push_back(j);
            }
        }
    }
    return result;
}

std::string DictionaryCipher::decrypt(const std::string &pass) const
{
    std::string result="";
    size_t length = pass.length();
    for (size_t i = 0; i < length; i++)
    {
        result+=dictionary[pass[i]];
    }
    return result;
}
