#ifndef CIPHER_HPP
#define CIPHER_HPP

#include <string>

class Cipher {
public:

    Cipher();
    virtual ~Cipher() = default;

    virtual std::string encrypt(const std::string& text) const = 0;
    virtual std::string decrypt(const std::string& pass) const = 0;

    virtual std::string getType() const = 0;

    //serialize
    //deserialize

private: 
};

#endif

