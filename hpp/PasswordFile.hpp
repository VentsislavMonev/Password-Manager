#ifndef PASSWORDFILE_HPP
#define PASSWORDFILE_HPP

#include "Entries.hpp"
#include "Cipher.hpp"
#include <string>
#include <fstream>

class PasswordFile
{
public:
    // create a password file 
    PasswordFile(const std::string& _fileName, CipherType passwordCipherType, const std::string& passwordCipherConfig, CipherType fileCipherType, const std::string& fileCipherConfig);

    // opens an existing password file
    PasswordFile(const std::string& _fileName,CipherType fileCipherType, const std::string& fileCipherConfig);

    ~PasswordFile();

private:
    void validateString(const std::string& str);

private:
    std::string fileName;
    Cipher* passwordCipher;
    Cipher* fileCipher;
    Entries data;
};

#endif

// TODO to make a default constructor and make the current open and create constructors in a functions