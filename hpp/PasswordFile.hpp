#ifndef PASSWORDFILE_HPP
#define PASSWORDFILE_HPP

#include "Entries.hpp"
#include "Cipher.hpp"
#include <string>
#include <vector>

class PasswordFile
{
public:
    // create a password file 

    // opens an existing password file
    PasswordFile(const std::string& _fileName,const std::string& fileCipherType, const std::string& fileCipherConfig);
    ~PasswordFile();

    void save(const std::string& website, const std::string& username, const std::string& password);
    // TODO da vrushta entries | da vidq da vrushtam referenciq demek da opravq purvo v entries da se vrushta referenciq
    std::vector<Entry> load(const std::string& website);
    Entry load(const std::string& website, const std::string& username);
    void update(const std::string& website, const std::string& username, const std::string& newPassword);
    

    static void createFile( const std::string& _fileName,
                            const std::string& passwordCipherType,
                            const std::string& passwordCipherConfig,
                            const std::string& fileCipherType,
                            const std::string& fileCipherConfig);

private:
    void validateFileName(const std::string& str);
    std::string getStringFromFile(const std::string& _fileName);
    void writeFileContent(const std::string& content) const;


    std::vector<std::string> split(const std::string& str, char delimiter); 
    


    void setFileCipher(const std::string& fileCipherType, const std::string& fileCipherConfig);
    void setPasswordCipher(const std::string& passwordCipherType, const std::string& passwordCipherConfig);

private:
    std::string fileName;
    Cipher* passwordCipher;
    Cipher* fileCipher;
    Entries data;
};

#endif

// TODO to make a default constructor and make the current open and create constructors in a functions