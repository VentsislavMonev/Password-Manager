#ifndef CIPHER_HPP
#define CIPHER_HPP

#include <string>
#include <vector>

class Cipher {
public:

    Cipher() = default;
    virtual ~Cipher() = default;

    virtual std::string encrypt(const std::string& text) const = 0;
    virtual std::string decrypt(const std::string& pass) const = 0;

    virtual std::string getType() const = 0;

    bool validate(const std::string& text)const;

    //serialize
    //deserialize

private: 
};

#endif

