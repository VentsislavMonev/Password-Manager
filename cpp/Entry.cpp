#include "Entry.hpp"
#include "Utility.hpp"

Entry::Entry(const std::string &_website, const std::string &_username, const std::string &_encryptedPassword, char _delimeter) : delimeter(_delimeter)
{
    setWebsite(_website);
    setUsername(_username);
    setEncryptedPassword(_encryptedPassword);
}

Entry::Entry(const std::vector<std::string> &vec)
{
    if(vec.size()!=3) throw std::invalid_argument("Invalid entry vector!");
    setWebsite(vec[0]);
    setUsername(vec[1]);
    setEncryptedPassword(vec[2]);
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
    os<<entry.website<< entry.delimeter <<entry.username<< entry.delimeter <<entry.encryptedPassword<< entry.delimeter <<'\n';
    return os;
}

std::istream &operator>>(std::istream &is, Entry &entry)
{
    std::string line;
    if (!std::getline(is, line))
        return is;

    if (line.empty())
        return is;

    entry.delimeter = line.back();

    size_t first = line.find(entry.delimeter);
    size_t second = line.find(entry.delimeter, first + 1);
    size_t third = line.find(entry.delimeter, second + 1);

    if (first == std::string::npos || second == std::string::npos || third == std::string::npos)
        return is;

    entry.website = line.substr(0, first);
    entry.username = line.substr(first + 1, second - first - 1);
    entry.encryptedPassword = line.substr(second + 1,third - second- 1);

    return is;
}
