#include "Entries.hpp"

void Entries::add(const Entry &entry)
{
    size_t length = entries.size();
    for (size_t i = 0; i < length; ++i)
    {
        if (entries[i].getWebsite() == entry.getWebsite() && entries[i].getUsername() == entry.getUsername()) 
        {
            return;
        }
    }
    entries.push_back(entry);
}

const std::vector<Entry> Entries::getEncryptedPassword(const std::string &website, const std::string &username)const
{
    std::vector<Entry> result;
    if(username.length()!=0)
    {
        size_t length = entries.size();
        for (size_t i = 0; i < length; ++i)
        {
            if(entries[i].getWebsite()==website && entries[i].getUsername()==username)
            {
                result.push_back(entries[i]);
                return result;
            }
        }
        throw std::runtime_error("There hasnt been set an user for this website");
    }
    else 
    {
        size_t length = entries.size();
        for (size_t i = 0; i < length; ++i)
        {
            if(entries[i].getWebsite()==website)
            {
                result.push_back(entries[i]);
            }
        }
        if(result.empty())
            throw std::runtime_error("There arent any entries for this website");
        return result;
    }
}

bool Entries::remove(const Entry &entry)
{
    size_t length = entries.size();
    for (size_t i = 0; i < length; ++i)
    {
        if(entries[i]==entry)
        {
            entries.erase(entries.begin() + i);
            return true;
        }
    }
    return false;   
}

bool Entries::remove(const std::string &website, const std::string &username)
{
    bool isSuccesful = false;
    if(username.length()!=0)
    {
        size_t length = entries.size();
        for (size_t i = 0; i < length; ++i)
        {
            if(entries[i].getWebsite()==website && entries[i].getUsername()==username)
            {
                entries.erase(entries.begin() + i);
                isSuccesful=true;
                break;
            }
        }
        
    }
    else 
    {
        for (size_t i = 0; i < entries.size();)
        {
            if (entries[i].getWebsite() == website)
            {
                entries.erase(entries.begin() + i);
                isSuccesful=true;
            } 
            else 
            {
                ++i; 
            }
        }
    }
    return isSuccesful;
}

void Entries::update(const std::string &website, const std::string &username, const std::string &encryptedPassword)
{
    size_t length = entries.size();
    for (size_t i = 0; i < length; ++i)
    {
        if(entries[i].getWebsite()==website && entries[i].getUsername()==username)
        {
            if(entries[i].getEncryptedPassword() == encryptedPassword)
                throw std::runtime_error("New password is the same as the old one!");
            entries[i].setEncryptedPassword(encryptedPassword);
            return;
        }
    }
    throw std::runtime_error("There isnt set a password fot this user for this website");
}

Entry& Entries::operator[](size_t i)
{
    if(i>= entries.size()) throw std::out_of_range("Out of range in entries!");
        return entries[i];
}

const Entry& Entries::operator[](size_t i) const
{
    if(i>= entries.size()) throw std::out_of_range("Out of range in entries!");
        return entries[i];
}
