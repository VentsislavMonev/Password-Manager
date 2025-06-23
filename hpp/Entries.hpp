#ifndef ENTRIES_HPP
#define ENTRIES_HPP

#include "Entry.hpp"
#include <vector>

class Entries
{
public:
    void add(const Entry& entry);
    
    // TODO da vidq dali da vrushta direktno Entries instanciq
    const std::vector<Entry> getEncryptedPassword(const std::string& website, const std::string& username="")const;
    
    bool remove(const Entry& entry);
    bool remove(const std::string& website, const std::string& username ="");

    void update(const std::string& website,const std::string& username, const std::string& encryptedPassword );
    
    Entry& operator[](size_t i);
    const Entry& operator[](size_t i)const;

    size_t getSize()const {return entries.size();}

private:
    std::vector<Entry> entries;
};

#endif