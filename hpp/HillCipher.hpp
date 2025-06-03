#ifndef HILL_CIPHER_HPP
#define HILL_CIPHER_HPP

#include "Cipher.hpp"
#include "SquaredMatrix_zn.hpp"
#include <vector>
#include <stdexcept>

class HillCipher : public Cipher
{
public:
    HillCipher(const SquaredMatrix_zn& _keyMatrix);

public:
    virtual std::string encrypt(const std::string& text) const override;
    virtual std::string decrypt(const std::string& pass) const override;
    std::string getType() const override;

private:
    int mod(int a)const;
    std::string multiplyMatrixWithString(std::string& text, const SquaredMatrix_zn& matrix)const;
    bool validateDecrypt(const std::string& text)const;
    std::string getDividedPassword(const std::string& text, const SquaredMatrix_zn& matrix)const;
    std::string getRemainingPassword(const std::string& text, const SquaredMatrix_zn& matrix)const;
private:
    SquaredMatrix_zn keyMatrix;
    SquaredMatrix_zn  invertedMatrix;
    char fill;
    // da vidq kak she stane
};

#endif