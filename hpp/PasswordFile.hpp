#ifndef PASSWORDFILE_HPP
#define PASSWORDFILE_HPP

#include "Entries.hpp"
#include "Cipher.hpp"
#include <string>
#include <vector>

class PasswordFile 
{
public:
    PasswordFile(const PasswordFile&) = delete;
    PasswordFile& operator=(const PasswordFile&) = delete;

    static PasswordFile& getInstance();
    static bool isFileLoaded();
    static void closeFile();

    static void createFile( const std::string& _fileName,
                            const std::string& passwordCipherType,
                            const std::string& passwordCipherConfig,
                            const std::string& fileCipherType,
                            const std::string& fileCipherConfig);

    static void openFile(   const std::string& _fileName,
                            const std::string& fileCipherType,
                            const std::string& fileCipherConfig);

public:
    void save(const std::string& website, const std::string& user, const std::string& password);
    std::vector<Entry> getEntries(const std::string& website, const std::string& username="")const;
    void update(const std::string& website,const std::string& username, const std::string& encryptedPassword);
    bool deleteEntry(const std::string& website, const std::string& username ="");

    bool saveFile()const;
private:
    PasswordFile(): fileName(""), passwordCipher(nullptr), fileCipher(nullptr), data(), isChanged(false){}
    ~PasswordFile();

private:
    static PasswordFile* instance;
    static bool fileLoaded;
    
private:
    
    void validateFileName(const std::string& _fileName);
    void validateFileNameOpen(const std::string& _fileName);

    std::string getFileContent(const std::string& _fileName);
    void setFileCipher(const std::string& fileCipherType, const std::string& fileCipherConfig);

    std::vector<std::string> split(const std::string& str, char delimiter); 

    void createBackup()const;
    void writeChanges()const;
    void writeEntry(const Entry& entry, std::ofstream& file)const;
    void writeHeader(std::ofstream& file)const;

private:
    std::string fileName;
    Cipher* passwordCipher;
    Cipher* fileCipher;
    Entries data;
    bool isChanged;
};

#endif
