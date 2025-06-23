#include "PasswordFile.hpp"
#include <fstream>

PasswordFile* PasswordFile::instance = nullptr;
bool PasswordFile::fileLoaded = false;

PasswordFile &PasswordFile::getInstance()
{
    if (!instance) {
        throw std::runtime_error("There isnt created an instance from this class!");
    }
    return *instance;
}

void PasswordFile::createFile(const std::string &_fileName, const std::string &passwordCipherType, const std::string &passwordCipherConfig, const std::string &fileCipherType, const std::string &fileCipherConfig)
{
    //
    // Creates an instance if it isnt already loaded one
    //
    if (fileLoaded) 
    {
        throw std::runtime_error("A password file is already loaded!");
    }
    instance = new PasswordFile();


    //
    // Checks if name is valid
    //
    instance->fileName=_fileName;
    try
    {
        instance->validateFileName(instance->fileName);
    }
    catch(const std::exception& e)
    {
        delete instance;
        throw e;
    }

    //
    // Sets the ciphers for passwords and for the file
    //
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
        delete instance;
        throw e;
    }
    instance->fileCipher = fileCipher;
    instance->passwordCipher = passwordCipher;

    //
    // Creates the file and checks it
    //
    std::ofstream file(instance->fileName, std::ios::binary);
    if(!file.good())
    {
        delete passwordCipher;
        delete fileCipher;
        delete instance;
        throw std::runtime_error("Files is bad!");
    } 
    else std::cout<<"File was created!"<<std::endl;

    //
    // Encrypt and write the header that contains the password cipher to the file and add a new line at the end
    //
    try
    {
        instance->writeHeader(file);
    }
    catch(const std::exception& e)
    {
        delete instance;
        file.close();
        throw e;
    }
    
    //
    // Checks if its all good
    //
    if(!file.good())
    {
        delete instance;
        throw std::runtime_error("Error writing to file!");
    }
    file.close();

    //
    // Sets password file as loaded
    //
    fileLoaded = true;
}

void PasswordFile::openFile(const std::string &_fileName, const std::string &fileCipherType, const std::string &fileCipherConfig)
{
    //
    // Creates an instance if it isnt already loaded one
    //
    if (fileLoaded) 
    {
        throw std::runtime_error("A password file is already loaded. Close it first.");
    }
    instance = new PasswordFile();

    //
    // Checks if name is valid and if file exists
    // 
    instance->fileName = _fileName;
    try
    {
        instance->validateFileNameOpen(instance->fileName);
    }
    catch(const std::exception& e)
    {
        delete instance;
        throw e;
    }
 
    //
    // Sets the cipher for the file
    //
    std::string encryptedContent = "";
    try
    {
        encryptedContent = instance->getFileHeader(_fileName);
        instance->setFileCipher(fileCipherType,fileCipherConfig);
    }
    catch(const std::exception& e)
    {
        delete instance;
        throw e;
    }

    //
    // Reads decrypted password cipher configs from file
    //
    std::string encryptedHeader = "";
    try
    {
        size_t pos = encryptedContent.find('\n');
        if(pos == std::string::npos) pos=encryptedContent.length();

        encryptedHeader = encryptedContent.substr(0,pos);
        std::string decryptedHeader = instance->fileCipher->decrypt(encryptedHeader);

        size_t firstDelimeterPos = decryptedHeader.find('|');

        std::string passwordCipherType = decryptedHeader.substr(0,firstDelimeterPos);
        std::string passwordCipherConfig = decryptedHeader.substr(firstDelimeterPos+1);

        instance->passwordCipher = Cipher::createCipher(passwordCipherType, passwordCipherConfig);
    }
    catch(const std::exception& e)
    {
        delete instance;
        throw e;
    }

    //
    // If there is no data/entries it returns
    //
    if(encryptedHeader.length()+1 >= encryptedContent.length()) 
        return;
    


    //
    // Gets the data and splits it first by new lines to get the different entries line by line then it
    // iterates through each entry and split it into 3 so it can decrypt each part and fills each entry to data
    //
    std::string encryptedData = encryptedContent.substr(encryptedHeader.size()+1);
    std::vector<std::string> lines = instance->split(encryptedData,(char)-2);
    size_t size = lines.size();
    for (size_t i = 0; i < size; i++)
    {
        char delimeter = lines[i].back();
        lines[i].pop_back();
        try
        {
            std::vector<std::string> entryVec = instance->split(lines[i], delimeter);
            for (size_t i = 0; i < entryVec.size(); i++)
            {
                entryVec[i] = instance->fileCipher->decrypt(entryVec[i]);
            }
            
            Entry entry(entryVec);
            instance->data.add(entry);
        }
        catch(const std::exception& e)
        {
            delete instance;
            throw e;
        }
    }
}

bool PasswordFile::isFileLoaded()
{
    return fileLoaded;
}

void PasswordFile::closeFile()
{
    if (instance) {
        delete instance;
        instance = nullptr;
    }
    fileLoaded = false;
}

PasswordFile::~PasswordFile()
{
    delete passwordCipher;
    delete fileCipher;
    passwordCipher=fileCipher=nullptr;
}

void PasswordFile::save(const std::string &website, const std::string &user, const std::string &password)
{
    data.add({website,user,instance->passwordCipher->encrypt(password)});
    instance->isChanged = true;
}

std::vector<Entry> PasswordFile::getEntries(const std::string &website, const std::string &username) const
{
    std::vector<Entry> entries = data.getEncryptedPassword(website,username);
    size_t size = entries.size();
    for (size_t i = 0; i < size; i++)
    {
        entries[i].setEncryptedPassword(instance->passwordCipher->decrypt(entries[i].getEncryptedPassword()));
    }
    return entries;
}

void PasswordFile::update(const std::string &website, const std::string &username, const std::string &encryptedPassword)
{
    data.update(website,username,instance->passwordCipher->encrypt(encryptedPassword));
    instance->isChanged = true;
}

bool PasswordFile::deleteEntry(const std::string &website, const std::string &username)
{
    return data.remove(website,username);
    instance->isChanged = true;
}

void PasswordFile::validateFileName(const std::string& _fileName)
{
    if(_fileName.empty())
        throw std::invalid_argument("Cannot create a file with empty username!");
    std::ifstream checkFile(_fileName);
    if(checkFile.good())
        throw std::runtime_error("File already exists!");
    checkFile.close();
}

void PasswordFile::validateFileNameOpen(const std::string& _fileName)
{
    if(_fileName.empty())
        throw std::invalid_argument("Cannot create a file with empty username!");
    std::ifstream checkFile(_fileName);
    if(!checkFile.good())
        throw std::runtime_error("No such file exists or file is bad!");
    checkFile.close();
}

std::string PasswordFile::getFileHeader(const std::string &_fileName)
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

std::vector<std::string> PasswordFile::split(const std::string &str, char delimiter)
{
    std::vector<std::string> tokens;
    if (str.empty()) return tokens; 
    
    size_t start = 0;
    size_t end = str.find(delimiter);

    if (end == std::string::npos)
    {
        tokens.push_back(str);
        return tokens;
    }
    
    while (end != std::string::npos) 
    {
        tokens.push_back(str.substr(start, end - start));
        start = end + 1;
        end = str.find(delimiter, start);
    }
    if (start < str.length())
    {
        tokens.push_back(str.substr(start));
    }
    
   return tokens;
}

void PasswordFile::createBackup() const
{
    std::string backupFileName = instance->fileName + ".backup";
    
    std::ifstream orignalFile(instance->fileName, std::ios::binary);
    if (!orignalFile) 
    {
        throw std::runtime_error("Failed to open original file for backup: " + instance->fileName);
    }
    
    std::ofstream backupFile(backupFileName, std::ios::binary);
    if (!backupFile) 
    {
        orignalFile.close();
        throw std::runtime_error("Failed to create backup file: " + backupFileName);
    }
    

    backupFile << orignalFile.rdbuf();
    // if(!orignalFile.rdbuf())
    // {
    //     backupFile << orignalFile.rdbuf();
    // }
    // else 
    // {
    //     orignalFile.close();    
    //     backupFile.close();    
    //     throw std::runtime_error("Failed to read data from original file: " + instance->fileName);
    // }

    if (orignalFile.fail() || backupFile.fail()) 
    {
        orignalFile.close();
        backupFile.close();
        throw std::runtime_error("Failed to copy data to backup file: " + backupFileName);
    }
    
    orignalFile.close();
    backupFile.close();
}

void PasswordFile::writeChanges() const
{
    std::ofstream file(instance->fileName,std::ios::binary);
    if (!file) 
    {
        throw std::runtime_error("Failed to open file for writing: " + instance->fileName);
    }

    size_t dataSize = instance->data.getSize();
    try
    {
        writeHeader(file);
        for (size_t i = 0; i < dataSize; i++)
        {
            instance->writeEntry(data[i], file);
        }
    }
    catch(const std::exception& e)
    {
        file.close();
        throw e;
    }
    
    file.close();
}

bool PasswordFile::saveFile() const
{
    if(!instance->isChanged)
    {
        return true;
    }

    try 
    {
        createBackup();
        std::string message = "Backup file created: "+ instance->fileName + ".backup";
        std::cout << message << std::endl;
    } 
    catch (const std::exception& e) 
    {
        std::string errorMsg = e.what();
        std::string message = "Coulnd't create backup file. Save failed. Original file is untouched.\nError message:" + errorMsg;
        std::cerr<< message <<std::endl;
        return false;
    }

    try
    {
        writeChanges();
        std::cout<<"File is saved successfully!"<<std::endl;
        instance->isChanged=false;
        return true;
    }
    catch(const std::exception& e)
    {
        std::string errorMsg = e.what();
        std::string message = "Original file is corupted! There is a backup file: "+ instance->fileName+".backup\nError message:" + errorMsg;
        std::cerr<<message<<std::endl;
        return false;
    }
}

void PasswordFile::writeEntry(const Entry &entry, std::ofstream& file) const 
{
    if(!file)
    {
        throw std::runtime_error("File is bad. Couldn't save entry to file: "+instance->fileName);
    }

    file<<instance->fileCipher->encrypt(entry.getWebsite())<<entry.getDelimetere()<<
    instance->fileCipher->encrypt(entry.getUsername())<<entry.getDelimetere()<<
    instance->fileCipher->encrypt(entry.getEncryptedPassword())<<entry.getDelimetere()<<(char)-2;

    if(!file)
    {
        throw std::runtime_error("Failed to write entry to file: " + instance->fileName);
    }
}

void PasswordFile::writeHeader(std::ofstream& file) const
{
    std::string fileHeader = instance->passwordCipher->getTypeString() + "|" + instance->passwordCipher->getConfig();
    std::string encryptedContent = "";
    try
    {
        encryptedContent = instance->fileCipher->encrypt(fileHeader);
    }
    catch(const std::exception&)
    {
        throw std::runtime_error("Error encrypting file header!");
    }
    file << encryptedContent<<'\n';
}