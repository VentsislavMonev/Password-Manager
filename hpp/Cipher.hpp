#ifndef CIPHER_HPP
#define CIPHER_HPP

#include <string>

enum class CipherType 
{
    CESAR,
    DICTIONARY,
    HILL
};

class Cipher {
public:

    Cipher() = default;
    virtual ~Cipher() = default;

    /// @brief function that encrypt passwords in the cipher classes
    /// @param text this text will be encrypted
    /// @return it will return the encrypted text
    virtual std::string encrypt(const std::string& text) const = 0;

    /// @brief function that decrypts texts in the cipher classes
    /// @param pass this will be decrypted to the original password
    /// @return it will return the decrypted original password
    virtual std::string decrypt(const std::string& pass) const = 0;

    virtual CipherType getType() const = 0;
    virtual std::string getConfig() const = 0;
    virtual void setConfig(const std::string& config) = 0;

    /// @brief checks if the text containsChar only chars from 32 to 126  
    /// @param text this text will be checked 
    /// @return it will return true if the text meets the before said conditions and else it will return false
    bool validate(const std::string& text)const;

    //serialize
    //deserialize

private:
};

#endif

