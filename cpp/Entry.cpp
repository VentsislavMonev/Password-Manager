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
    if(!UTILITIES::validateString(_website) || _website.length()==0)
        throw std::invalid_argument("Invalid entry website!");
    website=_website;
}

void Entry::setUsername(const std::string &_username)
{
    if(!UTILITIES::validateString(_username) || _username.length()==0)
        throw std::invalid_argument("Invalid entry username!");
    username=_username;
}
// TODO da izpolzvam tuk Cipher::validate?

void Entry::setEncryptedPassword(const std::string& _encryptedPassword)
{
    if(_encryptedPassword.length()==0)
        throw std::invalid_argument("Encrypted password cannot be empty!");
    encryptedPassword=_encryptedPassword;
}

bool Entry::operator==(const Entry &other) const
{
    return (website==other.website&&username==other.username&& encryptedPassword==other.encryptedPassword) ;
}

bool Entry::operator!=(const Entry &other) const
{
    return !(*this==other);
}

// bool Entry::validateEntryText(const std::string &_website) const
// {
//     size_t length = _website.length();
//     for (size_t i = 0; i < length; i++)
//     {
//         if(_website[i]<'!' || _website[i]> '~')
//             return false;
//     }
//     return true;
// }

std::ostream &operator<<(std::ostream &os, const Entry &entry)
{
    os<<entry.website<<"\n";
    os<<entry.username<<"\n";
    os<<entry.encryptedPassword<<std::endl;
    return os;
}

std::istream &operator>>(std::istream &is, Entry &entry)
{
    std::string website,username,encryptedPasword;
    std::getline(is, website);
    std::getline(is, username);
    std::getline(is, encryptedPasword);
    try
    {
        Entry temp(website,username,encryptedPasword);
        entry = temp;
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << ""<<'\n';
    }
    
    return is;
}
