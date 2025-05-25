#ifndef DICTIONARY_CIPHER_HPP
#define DICTIONARY_CIPHER_HPP

#include <string>
#include <vector>
#include "Cipher.hpp"

class DictionaryCipher : public Cipher
{
public:
    DictionaryCipher(const std::string& _dictionaryText);

public:
    virtual std::string encrypt(const std::string& text) const override;
    virtual std::string decrypt(const std::string& pass) const override;

    virtual std::string getType() const override;

private:
    void setDictionary(const std::string& textDictionary);

    void insertUnique(char value);

private:
    std::vector<char> dictionary;     //TODO to use set
};

#endif