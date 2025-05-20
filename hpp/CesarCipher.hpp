#ifndef CESAR_CIPHER_HPP
#define CESAR_CIPHER_HPP

#include <string>
#include "Cipher.hpp"

class CesarCipher: public Cipher
{
public:
    CesarCipher();
    CesarCipher(short shift);

public:
    virtual std::string encrypt(const std::string& text) const override;//
    virtual std::string decrypt(const std::string& pass) const override;//

    std::string getType() const override;//

// Functions
private:
    char ShiftChar(char c, short shift)const;//
    short mod(short a, short b)const;//
    
// Members
private:
    short shift
};

#endif

//TODO 
//da dobavq set/get za shift
//da opravq konstrukturite