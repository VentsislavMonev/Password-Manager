#include "HillCipher.hpp"
HillCipher::HillCipher(const SquaredMatrix_zn &_keyMatrix) : fill('\0')
{
    //TODO to make it work with a random matrix dimension
    // if(_keyMatrix.getDimension()!=3)
    //     throw std::invalid_argument("Key matrix must be with dimension 3!");
    keyMatrix = _keyMatrix;
    invertedMatrix = keyMatrix.getInverseMatrix();
}


std::string HillCipher::encrypt(const std::string &text) const
{
    if(!Cipher::validate(text))
        throw std::invalid_argument("Invalid password to encrypt only allowed charachters are the chars from 32 to 126");

    std::string encryptedPass = getDividedPassword(text, keyMatrix);
    encryptedPass += getRemainingPassword(text, keyMatrix);

    return encryptedPass;
}

std::string HillCipher::decrypt(const std::string &pass) const
{
    if(!validateDecrypt(pass))
        throw std::invalid_argument("Password couldn`t be decrypted. Possibly wasnt encrypted from this instance");

    std::string decryptedPass = getDividedPassword(pass, invertedMatrix);
    decryptedPass += getRemainingPassword(pass, invertedMatrix);

    for (size_t i = 0; i < decryptedPass.length(); i++)
    {
        decryptedPass[i]+='~'-' ';
    }
    

    return decryptedPass;
}


int HillCipher::mod(int a) const
{
    const int allowedSymbolsCount = '~' - ' '; 
    return (a % allowedSymbolsCount + allowedSymbolsCount) % allowedSymbolsCount;
}

std::string HillCipher::multiplyMatrixWithString(std::string &text, const SquaredMatrix_zn& matrix) const
{
    int matrixSize = matrix.getDimension();
    int remain = text.length()%matrixSize;

    std::string encryptText = "";
    for (int i = 0; i < matrixSize; ++i) 
    {
        int sum = 0;
        for (int j = 0; j < matrixSize; ++j) 
        {
            sum = matrix.normalizeModulo(sum + matrix.modularMultiply(static_cast<int>(matrix[i][j]), static_cast<int>(text[j])));
        }
        encryptText.push_back(sum);
    }
    return encryptText;
}

bool HillCipher::validateDecrypt(const std::string &text) const
{
    size_t length = text.length();
    for (size_t i = 0; i < length; i++)
    {
        if(text[i]<0 || text[i]>=keyMatrix.getModNumber())
            return false;
    }
    return true;
}

// Cuts the text by length of the key matrix size so it can be multiplied with it
std::string HillCipher::getDividedPassword(const std::string& text, const SquaredMatrix_zn& matrix) const
{
    int matrixSize = matrix.getDimension();
    size_t textLength = text.length();
    int remain = textLength%matrixSize;

    std::string encryptedPass = "";
    for (size_t i = 0; i < textLength-remain ; i+=matrixSize)
    {
        std::string current;
        for (size_t j = 0; j < matrixSize; ++j)
        {
            current.push_back(mod(text[i+j]));
        }
        
        encryptedPass += multiplyMatrixWithString(current,matrix);
    }
    return encryptedPass;
}

// Gets the remainder of the text if there is any
std::string HillCipher::getRemainingPassword(const std::string& text, const SquaredMatrix_zn& matrix) const
{
    int matrixSize = matrix.getDimension();
    size_t textLength = text.length();
    int remain = textLength%matrixSize;

    std::string encryptedPass = "";

    if(remain!=0)
    {
        std::string current="";
        for (size_t i = textLength-remain; i < textLength; ++i)
        {
            current.push_back(mod(text[i]));
        }
        for (size_t i = remain; i < matrixSize; ++i)
        {
            current.push_back(static_cast<char>(keyMatrix.getModNumber()));
        }
        encryptedPass+= multiplyMatrixWithString(current, keyMatrix);
    }

    size_t index = encryptedPass.find(static_cast<char>(keyMatrix.getModNumber()), 0);
    encryptedPass = encryptedPass.substr(0,index);

    return encryptedPass;
}

std::string HillCipher::getType() const
{
    return "Hill";
}
