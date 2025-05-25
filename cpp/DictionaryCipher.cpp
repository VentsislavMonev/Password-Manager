#include "DictionaryCipher.hpp"

void DictionaryCipher::setDictionary(const std::string textDictionary)
{
    size_t length = textDictionary.size();
    for (size_t i = 0; i < length; i++)
    {
        inserUnique(dictionary, textDictionary[i]);     //TODO do i somehow need to add a validation for textDictionary?
    }
    
}

// If the value is in there dont add anything so it doesnt duplicate
void DictionaryCipher::inserUnique(std::vector<char> &set, char value)
{
    for (char v : set) {
        if (v == value) {
            return;
        }
    }
    set.push_back(value);
}

std::string DictionaryCipher::getType() const
{
    return "Dictionary";
}

std::string DictionaryCipher::decrypt(const std::string &pass) const
{
    
    //TODO to change so that decrypt takes a vector
    std::string result="";
    size_t length = pass.length();
    for (size_t i = 0; i < length; i++)
    {
        result+=dictionary[pass[i]];
    }
    
}
