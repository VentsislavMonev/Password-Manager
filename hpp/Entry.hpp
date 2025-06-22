#ifndef ENTRY_HPP
#define ENTRY_HPP

#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>

class Entry
{
public:
    Entry();
    Entry(const std::string& _website, const std::string& _username, const std::string& _encryptedPassword, char _delimeter=255);
    Entry(const std::vector<std::string>& vec);

    void setWebsite(const std::string& _website);
    void setUsername(const std::string& _username);
    void setEncryptedPassword(const std::string& _encryptedPassword);

    const std::string& getWebsite()const { return website;}
    const std::string& getUsername()const { return username;}
    const std::string& getEncryptedPassword()const { return encryptedPassword;}
    char getDelimetere()const {return delimeter;}

    friend std::ostream& operator<<(std::ostream& os, const Entry& entry);
    friend std::istream& operator>>(std::istream& is, Entry& entry);
    
    bool operator==(const Entry& other)const;
    bool operator!=(const Entry& other)const;

private:
    
    // bool validateEntryText(const std::string& _website) const;
    
    std::string website;
    std::string username;
    std::string encryptedPassword;
    char delimeter;
};


#endif