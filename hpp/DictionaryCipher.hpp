#ifndef DICTIONARY_CIPHER_HPP
#define DICTIONARY_CIPHER_HPP

#include "Cipher.hpp"
#include <vector>

class DictionaryCipher : public Cipher
{
public:
    /// @brief it fills the dictionary by a given text and  makes sure it doesnt have duplicates
    /// @param _dictionaryText the text from which the dictionary will be filled
    DictionaryCipher(const std::string& _dictionaryText);

public:

    /// @brief checks if the text charachters are contained in the dictionary
    // and encrypts the text by replacing the letters with their keys in the dictionary
    /// @param text this text will be encrypted
    /// @return it will return the encrypted text
    virtual std::string encrypt(const std::string& text) const override;

    /// @brief decrypt a password that was encrypted by this class instance
    /// @param pass this is the container where the password that we want to decrypt is
    /// @return the decrypted original password will be returned if it was encrypted by this instance. Throws otherwise 
    virtual std::string decrypt(const std::string& pass) const override;

    virtual std::string getType() const override;

private:

    /// @brief checks if a text symbols are from the dictionary
    /// @param text the text that will be checked
    /// @return it will return true if the text symbols are from the dictionary and false if they arent
    bool isTextInDictionary(const std::string& text) const;

    /// @brief checks if the given text can be decrypted from this dictionary
    /// @param text given text to be checked
    /// @return returns true or false if the text can be decrypted
    bool checkForMissMatch(const std::string& text) const;

    /// @brief checks if a single letters is from the dictionary 
    /// @param c the letter that will be checked
    /// @return if the letters is in the dictionary
    bool containsChar(char c)const;

    /// @brief validates a text and if its valid it adds its symbols into the dictionary in the form of a set
    /// @param textDictionary the text that will be used
    void setDictionary(const std::string& textDictionary);

    /// @brief checks if a value is already in the dictionary and if not it adds it
    /// @param value the value that will be checked and maybe added
    void insertUnique(char value);

private:
    std::vector<char> dictionary;     //TODO to use set
};

#endif