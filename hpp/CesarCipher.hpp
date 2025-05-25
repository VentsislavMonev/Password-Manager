#ifndef CESAR_CIPHER_HPP
#define CESAR_CIPHER_HPP

#include <iostream>
#include <string>
#include "Cipher.hpp"

class CesarCipher: public Cipher
{
public:
    CesarCipher(short _shift);

public:
    virtual std::string encrypt(const std::string& text) const override;
    virtual std::string decrypt(const std::string& pass) const override;

    std::string getType() const override;
    short getShift()const;

// Functions
private:
    void setShift(short _shift);    

    char ShiftChar(char c, short shift)const;
    
    short mod(short a)const;
    
// Members
private:
    short shift;
    static const  short ALPABET_LENGTH = 26;
};

#endif

//TODO 
//da dobavq set/get za shift
//da opravq konstrukturite