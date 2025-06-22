#include "PasswordFile.hpp"
#include <fstream>

PasswordFile::PasswordFile(const std::string &_fileName, const std::string& fileCipherType, const std::string &fileCipherConfig) : passwordCipher(nullptr), fileCipher(nullptr), isChanged(false)
{
    validateFileName(_fileName);
    fileName = _fileName;

    std::string encryptedContent = getStringFromFile(_fileName);
    
    setFileCipher(fileCipherType,fileCipherConfig);

    size_t pos = encryptedContent.find('\n');
    if(pos == std::string::npos) pos=encryptedContent.length();
    std::string encryptedHeader = encryptedContent.substr(0,pos);
    std::string decryptedHeader = fileCipher->decrypt(encryptedHeader);
    size_t firstDelimeterPos = decryptedHeader.find('|');
    std::string passwordCipherString = decryptedHeader.substr(0,firstDelimeterPos);
    std::string passwordCipherConfig = decryptedHeader.substr(firstDelimeterPos+1);

    setPasswordCipher(passwordCipherString, passwordCipherConfig);

    if(encryptedHeader.length()+1 > encryptedContent.length()) 
        return;

    std::string encryptedData = encryptedContent.substr(encryptedHeader.size()+1);
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

bool PasswordFile::saveToFile() const
{
    if (!isChanged)
    {
        return true; 
    }


    std::string tempFile = fileName + ".tmp";
    std::string backupFile = fileName + ".backup";
    
    std::string header = passwordCipher->getTypeString()+'|'+passwordCipher->getConfig();
    std::string encryptedHeader = fileCipher->encrypt(header) + '\n';
    std::string encryptedContent = encryptedHeader + serializeData();

    std::ofstream outFile(tempFile);
    if (!outFile) {
        throw std::runtime_error("File is bad!");
    }
    
    outFile << encryptedContent;
    outFile.flush();
    
    if (outFile.fail()) {
        throw std::runtime_error("Failed to write to temporary file");
    }

    if (fileExists(fileName)) {
        if (!copyFile(fileName, backupFile)) {
            removeFile(tempFile);
            throw std::runtime_error("Failed to create backup");
        }
    }
    
    if (!renameFile(tempFile, fileName)) {
        if (fileExists(backupFile)) {
            if (!renameFile(backupFile, fileName)) {
                throw std::runtime_error("Critical error: Failed to save and restore backup");
            }
        }
        throw std::runtime_error("Failed to replace original file");
    }
    
    removeFile(backupFile);
    try 
    {
        std::string tempFile = fileName + ".tmp";
        std::string backupFile = fileName + ".backup";
        
        std::string header = passwordCipher->getTypeString()+'|'+passwordCipher->getConfig();
        std::string encryptedHeader = fileCipher->encrypt(header) + '\n';
        std::string encryptedContent = encryptedHeader + serializeData();

        std::ofstream outFile(tempFile, std::ios::binary);
        if (!outFile) {
            throw std::runtime_error("File is bad!");
        }
        
        outFile << encryptedContent;
        if (!outFile) {
            removeFile(tempFile);
            throw std::runtime_error("Failed to write to temp file");
        }
        outFile.close();
    
        if (fileExists(fileName)) {
            if (!copyFile(fileName, backupFile)) {
                removeFile(tempFile);
                throw std::runtime_error("Failed to create backup");
            }
        }

        if (!renameFile(tempFile, fileName)) {
            removeFile(tempFile);
            throw std::runtime_error("Failed to replace original file");
        }

        removeFile(backupFile);
        
        return true;
    }
    catch (...) {
        if (fileExists(tempFile)) removeFile(tempFile);
        throw;
    }
    
    return true;
}

void PasswordFile::createFile(const std::string &_fileName, const std::string &passwordCipherType, const std::string &passwordCipherConfig, const std::string &fileCipherType, const std::string &fileCipherConfig)
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
    
    
    file << encryptedContent<<'\n';
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
    if (!file) {
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
    if (!file) 
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

// TODO to try catch if anything and see how to handle it
std::string PasswordFile::serializeData()const
{
    std::string result ="";
    size_t count = data.getSize();
    for (size_t i = 0; i < count; i++)
    {
        result = result + 
            fileCipher->encrypt(data[i].getWebsite()) + data[i].getDelimetere() +
            fileCipher->encrypt(data[i].getUsername()) + data[i].getDelimetere() +
            fileCipher->encrypt(data[i].getEncryptedPassword()) + data[i].getDelimetere()+ data[i].getDelimetere() + '\n';
    }
    return result;
}

bool PasswordFile::copyFile(const std::string& source, const std::string& destination) const
{
    std::ofstream destinationFile(destination);
    if (!destinationFile) {
        return false;
    }
    
    try
    {
        std::string content = getStringFromFile(source);
        destinationFile << content;
        destinationFile.flush();
    }
    catch(const std::exception& e)
    {
        return false;
    }

    bool result = destinationFile.good();
    destinationFile.close();

    return result;
}

bool PasswordFile::renameFile(const std::string& oldName, const std::string& newName) const
{
    return std::rename(oldName.c_str(), newName.c_str()) == 0;
}

bool PasswordFile::removeFile(const std::string& filename) const
{
    return std::remove(filename.c_str()) == 0;
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