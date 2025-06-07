#ifndef HILL_CIPHER_HPP
#define HILL_CIPHER_HPP

#include "Cipher.hpp"
#include "SquaredMatrix_zn.hpp"

class HillCipher : public Cipher
{
public:
    HillCipher(const SquaredMatrix_zn& _keyMatrix);

public:
    virtual std::string encrypt(const std::string& text) const override;
    virtual std::string decrypt(const std::string& pass) const override;
    virtual CipherType getType() const override;
    virtual std::string getConfig() const;
    virtual void setConfig(const std::string& config);

private:
    std::string multiplyMatrixWithString(const std::string& text, const SquaredMatrix_zn& matrix)const;
    bool validateDecrypt(const std::string& text)const;

    std::string encodeLengthHeader(size_t length) const;
    size_t decodeLengthHeader(const std::string& header) const;
    std::string processDividedText(const std::string& text, const SquaredMatrix_zn& matrix, int offset)const;

    std::string getRemainingPassword(const std::string& text, const SquaredMatrix_zn& matrix)const;
private:
    SquaredMatrix_zn keyMatrix;
    SquaredMatrix_zn  invertedMatrix;
};

#endif