#ifndef ENTRY_HPP
#define ENTRY_HPP

#include <iostream>
#include <string>
#include <stdexcept>

class Entry
{
public:
    Entry();
    Entry(const std::string& _website, const std::string& _username, const std::string& _encryptedPassword);

    void setWebsite(const std::string& _website);
    void setUsername(const std::string& _username);
    void setEncryptedPassword(const std::string& _encryptedPassword);

    const std::string& getWebsite()const { return website;}
    const std::string& getUsername()const { return username;}
    const std::string& getEncryptedPassword()const { return encryptedPassword;}

    friend std::ostream& operator<<(std::ostream& os, const Entry& entry);
    friend std::istream& operator>>(std::istream& is, Entry& entry);
    
    bool operator==(const Entry& other)const;
    bool operator!=(const Entry& other)const;

    private:
    
    // bool validateEntryText(const std::string& _website) const;
    
    std::string website;
    std::string username;
    std::string encryptedPassword;
};


#endif