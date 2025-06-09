#include "PasswordFile.hpp"
#include <fstream>

PasswordFile::PasswordFile(const std::string &_fileName, const std::string& fileCipherType, const std::string &fileCipherConfig) : passwordCipher(nullptr), fileCipher(nullptr)
{
    validateFileName(_fileName);
    fileName = _fileName;

    std::string encryptedContent = getStringFromFile(_fileName);
    
    setFileCipher(fileCipherType,fileCipherConfig);


    // TODO to check if the positions is valid 
    size_t pos = encryptedContent.find('\n');
    std::string decryptedHeader = fileCipher->decrypt(encryptedContent.substr(0, pos));
    size_t firstDelimeterPos = decryptedHeader.find('|');
    std::string passwordCipherString = decryptedHeader.substr(0,firstDelimeterPos);
    std::string passwordCipherConfig = decryptedHeader.substr(firstDelimeterPos+1);

    setPasswordCipher(passwordCipherString, passwordCipherConfig);

    std::string encryptedData = encryptedContent.substr(decryptedHeader.size()+1);
    std::vector<std::string> lines = split(encryptedData, '\n');
    size_t size = lines.size();
    for (size_t i = 0; i < size; i++)
    {
        char delimeter = lines[i].back();
        lines[i].pop_back();
        try
        {
            std::vector<std::string> entryVec = split(lines[i], delimeter);
            for (size_t i = 0; i < entryVec.size(); i++)
            {
                entryVec[i] = passwordCipher->decrypt(entryVec[i]);
            }
            
            Entry entry(entryVec);
            data.add(entry);
        }
        catch(const std::exception& e)
        {
            delete passwordCipher;
            delete fileCipher;
            throw std::runtime_error("Invalid password file data corupted!");
        }
    }
}

PasswordFile::~PasswordFile()
{
    delete passwordCipher;
    delete fileCipher;
    passwordCipher=fileCipher=nullptr;
}

void PasswordFile::save(const std::string &website, const std::string &username, const std::string &password)
{
    Entry newEntry(website, username, passwordCipher->encrypt(password));
    data.add(newEntry);    
}


std::vector<Entry> PasswordFile::load(const std::string &website)
{
    return data.getEncryptedPassword(website);
}


Entry PasswordFile::load(const std::string &website, const std::string& username)
{
    return data.getEncryptedPassword(website)[0];
}


void PasswordFile::update(const std::string &website, const std::string &username, const std::string &newPassword)
{
    data.update(website,username,newPassword);
}

void PasswordFile::createFile(const std::string &_fileName, const std::string& passwordCipherType, const std::string &passwordCipherConfig, const std::string& fileCipherType, const std::string &fileCipherConfig)
{
    if(_fileName.empty())
        throw std::invalid_argument("Cannot create a file with empty username!");
    std::ifstream checkFile(_fileName);
    if(checkFile.good())
        throw std::runtime_error("File with this name already exists!");
    checkFile.close();

    Cipher* passwordCipher = nullptr;
    Cipher* fileCipher = nullptr;
    try
    {
        passwordCipher = Cipher::createCipher(passwordCipherType, passwordCipherConfig);
        fileCipher = Cipher::createCipher(fileCipherType, fileCipherConfig);
    }
    catch(const std::exception& e)
    {
        delete passwordCipher;
        delete fileCipher;
        throw e;
    }

    std::ofstream file(_fileName);       

    if(!file.good())
    {
        delete passwordCipher;
        delete fileCipher;
        throw std::runtime_error("Files is bad!");
    } 
    else std::cout<<"File was created!"<<std::endl;

    std::string fileHeader = passwordCipherType + "|" + passwordCipherConfig;
    std::string encryptedContent = "";
    try
    {
        encryptedContent = fileCipher->encrypt(fileHeader);
    }
    catch(const std::exception& e)
    {
        delete passwordCipher;
        delete fileCipher;
        throw std::runtime_error("Error writing to file!");
    }
    
    
    file << encryptedContent;
    if(!file.good())
    {
        delete passwordCipher;
        delete fileCipher;
        throw std::runtime_error("Error writing to file!");
    }

    file.close();
}

void PasswordFile::validateFileName(const std::string& _fileName)
{
    if(_fileName.empty())
        throw std::invalid_argument("Cannot create a file with empty username!");
    std::ifstream checkFile(_fileName);
    if(!checkFile.good())
        throw std::runtime_error("File is bad!");

    checkFile.close();
}

std::string PasswordFile::getStringFromFile(const std::string &_fileName)
{
    std::ifstream file(_fileName, std::ios::binary);
    if (!file.is_open()) {
        throw std::runtime_error("File is bad!");
    }
    
    file.seekg(0, std::ios::end);
    std::streampos fileSize = file.tellg();
    file.seekg(0, std::ios::beg);
    
    std::string content(fileSize, '\0');
    file.read(&content[0], fileSize);
    
    file.close();
    return content;
}

void PasswordFile::writeFileContent(const std::string& content) const 
{
    std::string encryptedContent = fileCipher->encrypt(content);
    
    std::ofstream file(fileName);
    if (!file.is_open()) 
    {
        throw std::runtime_error("File is bad!");
    }
    
    file << encryptedContent;
    file.close();
}


std::vector<std::string> PasswordFile::split(const std::string &str, char delimiter)
{
    std::vector<std::string> tokens;
    size_t start = 0;
    size_t end = str.find(delimiter);
    
    while (end != std::string::npos) 
    {
        tokens.push_back(str.substr(start, end - start));
        start = end + 1;
        end = str.find(delimiter, start);
    }
    tokens.push_back(str.substr(start));
    
    return tokens;
}


void PasswordFile::setFileCipher(const std::string &fileCipherType, const std::string &fileCipherConfig)
{
    fileCipher = nullptr;
    try
    {
        fileCipher = Cipher::createCipher(fileCipherType, fileCipherConfig);
    }
    catch(const std::exception& e)
    {
        delete fileCipher;
        throw e;
    }    
}

void PasswordFile::setPasswordCipher(const std::string &passwordCipherType, const std::string &passwordCipherConfig)
{
    passwordCipher = nullptr;
    try
    {
        passwordCipher = Cipher::createCipher(passwordCipherType, passwordCipherConfig);
    }
    catch(const std::exception& e)
    {
        delete passwordCipher;
        delete fileCipher;
        throw e;
    }
}
// TODO to fix the stoi thing where if it starts with a number and then letters it says its godo and returns the number