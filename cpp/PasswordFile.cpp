#include "PasswordFile.hpp"

PasswordFile::PasswordFile(const std::string& _fileName, CipherType passwordCipherType, const std::string &passwordCipherConfig, CipherType fileCipherType, const std::string &fileCipherConfig)
    : passwordCipher(nullptr), fileCipher(nullptr)
{
    // Checks if a filewith this name exists
    validateString(_fileName);
    std::ifstream file(_fileName);
    if(file.good())
        throw std::runtime_error("File with this name already exists!");

    fileName=_fileName;
    try
    {
        passwordCipher = Cipher::createCipher(passwordCipherType,passwordCipherConfig);
        fileCipher = Cipher::createCipher(fileCipherType,fileCipherConfig);
    }
    catch(const std::exception& e)
    {
        delete passwordCipher;
        delete fileCipher;
        throw e;
    }
}

PasswordFile::PasswordFile(const std::string &_fileName, CipherType fileCipherType, const std::string &fileCipherConfig)
{
    if(file.good())
        throw std::runtime_error("File with this name already exists!");
}

PasswordFile::~PasswordFile()
{
    delete passwordCipher;
    delete fileCipher;
    passwordCipher=fileCipher=nullptr;
}

void PasswordFile::validateString(const std::string &str)
{
    if (str.empty()) {
        throw std::invalid_argument("Invalid string passed");
    }
}
