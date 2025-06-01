#include "Entry.hpp"
#include "Utility.hpp"

Entry::Entry(const std::string &_website, const std::string &_username, const std::string &_encryptedPassword)
{
    setWebsite(_website);
    setUsername(_username);
    setEncryptedPassword(_encryptedPassword);
}

Entry::Entry() : website("Default_Website"), username("Default_Username"), encryptedPassword("Default_Encrypted_Password"){}

void Entry::setWebsite(const std::string &_website)
{
    if(!validateEntryText(_website))
        throw std::invalid_argument("Invalid entry website!");
    website=_website;
}

void Entry::setUsername(const std::string &_username)
{
    if(!UTILITIES::validateString(_username))
        throw std::invalid_argument("Invalid entry username!");
    username=_username;
}

void Entry::setEncryptedPassword(const std::string& _encryptedPassword)
{
    encryptedPassword=_encryptedPassword;
}

bool Entry::validateEntryText(const std::string &_website) const
{
    size_t length = _website.length();
    for (size_t i = 0; i < length; i++)
    {
        if(_website[i]<'!' || _website[i]> '~')
            return false;
    }
    return true;
}

std::ostream &operator<<(std::ostream &os, const Entry &entry)
{
    os<<entry.website<<"\n";
    os<<entry.username<<"\n";
    os<<entry.encryptedPassword<<std::endl;
    return os;
}

std::istream &operator>>(std::istream &is, Entry &entry)
{
    std::string a,b,c, div;
    std::getline(is, a);
    std::getline(is, b);
    std::getline(is, c);
    try
    {
        Entry temp(a,b,c);
        entry = temp;
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << ""<<'\n';
    }
    
    return is;
}
