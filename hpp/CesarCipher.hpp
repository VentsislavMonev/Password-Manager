#ifndef CESAR_CIPHER_HPP
#define CESAR_CIPHER_HPP

#include "Cipher.hpp"

class CesarCipher: public Cipher
{
public:
    CesarCipher(short _shift);

public:

    /// @brief checks if the text is valid and encrypt the english letters from the alphabet
    // with a Cesar cipher with the private shift variable
    // it doesnt encrypt other symbols
    /// @param text this text will be encrypted
    /// @return it will return the encrypted text
    virtual std::string encrypt(const std::string& text) const override;

    /// @brief decrypt a password that was encrypted by this class instance
    /// @param pass this is the container where the password that we want to decrypt is
    /// @return the decrypted original password will be returned
    virtual std::string decrypt(const std::string& pass) const override;

    std::string getType() const override;
    short getShift()const; //TODO make private?

private:

    /// @brief sets the shift by which we will encrypt and gets its module 
    /// @param _shift it gets this numbers module of 85
    void setShift(short _shift);    

    /// @brief shift a char by a given offset
    /// @param c the char that will be shifted
    /// @param offset how much we will shift by
    /// @return the shifted char
    char ShiftChar(char c, short offset)const;
    
    /// @brief implements a simple math module of the count of the allowed symbols 85
    /// @param a the number from which we will get the module
    /// @return the module of 85 of the number a
    short mod(short a)const;
    
private:
    short shift;
};

#endif

//TODO 
//da dobavq set/get za shift
//da opravq konstrukturite