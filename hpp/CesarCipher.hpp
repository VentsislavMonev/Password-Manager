#ifndef CESAR_CIPHER_HPP
#define CESAR_CIPHER_HPP

#include "Cipher.hpp"

class CesarCipher: public Cipher
{
public:
    CesarCipher(int _shift);

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
    virtual std::string getConfig() const;
    virtual void setConfig(const std::string& config);

    virtual CipherType getType() const override;
    
private:
    int getShift()const;  //TODO to remove this function?
    
    /// @brief sets the shift by which we will encrypt and gets its module 
    /// @param _shift it gets this numbers module of 94
    void setShift(int _shift);    

    /// @brief shift a char by a given offset
    /// @param c the char that will be shifted
    /// @param offset how much we will shift by
    /// @return the shifted char
    char ShiftChar(char c, int offset)const;
    
    /// @brief implements a simple math module of the count of the allowed symbols 94
    /// @param a the number from which we will get the module
    /// @return the module of 94 of the number a
    int mod(int a)const;
    
private:
    int shift;
};

#endif