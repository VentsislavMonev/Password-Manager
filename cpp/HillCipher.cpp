#include "HillCipher.hpp"
#include <iostream>

HillCipher::HillCipher(const SquaredMatrix_zn &_keyMatrix) : fill('\0')
{
    if(_keyMatrix.getDimension()<3)
        throw std::invalid_argument("Key matrix must be with dimension bigger than 3 !");
    keyMatrix = _keyMatrix;
    invertedMatrix = keyMatrix.getInverseMatrix();
}


std::string HillCipher::encrypt(const std::string &text) const
{
    if(!Cipher::validate(text))
        throw std::invalid_argument("Invalid password to encrypt only allowed charachters are the chars from 32 to 126");

    std::string encryptedPass = processDividedText(text, keyMatrix, ' ');
    encryptedPass += getRemainingPassword(text, keyMatrix);
    
    // Prepend length header. 4 bytes for length
    size_t originalLength = text.length();
    std::string lengthHeader = encodeLengthHeader(originalLength);
    
    return lengthHeader + encryptedPass;
}

std::string HillCipher::decrypt(const std::string &pass) const
{
    if(!validateDecrypt(pass))
        throw std::invalid_argument("Password couldn`t be decrypted. Possibly wasnt encrypted from this instance");

    size_t originalLength = decodeLengthHeader(pass.substr(0, 4));
    
    // Extract actual encrypted content. Skip 4-byte header
    std::string actualEncrypted = pass.substr(4);
    std::string decrypted = processDividedText(actualEncrypted, invertedMatrix, 0);

    // Adds the offset we removed
    for (char& c : decrypted)
    {
        c+=' ';
    }
    
    // Return only the original length (removes padding automatically)
    if(originalLength > decrypted.length())
        throw std::invalid_argument("Invalid length header - corrupted data!");
    
    return decrypted.substr(0, originalLength);
}

std::string HillCipher::multiplyMatrixWithString(const std::string &text, const SquaredMatrix_zn& matrix) const
{
    int matrixSize = matrix.getDimension();
    int remain = text.length()%matrixSize;

    std::string encryptText = "";
    for (int i = 0; i < matrixSize; ++i) 
    {
        int sum = 0;
        for (int j = 0; j < matrixSize; ++j) 
        {
            sum = sum + matrix[i][j]*static_cast<int>(text[j]);
        }
        sum = sum%matrix.getModNumber();
        encryptText.push_back(sum);
    }
    return encryptText;
}

bool HillCipher::validateDecrypt(const std::string &text) const
{
    if(text.length() < 4)
        return false;
    
    size_t length = text.length();
    for (size_t i = 4; i < length; i++)  // Skip the header where length is stored
    {
        if(text[i] < 0 || text[i] >= keyMatrix.getModNumber())
            return false;
    }
    return true;
}

// Cuts the text by length of the key matrix size so it can be multiplied with it
std::string HillCipher::processDividedText(const std::string& text, const SquaredMatrix_zn& matrix, int offset) const
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
            current.push_back(text[i+j]-offset);
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
    
    if(remain==0)
        return "";
    
    std::string encryptedPass = "";
    std::string current="";

    // Get the reamining symbols from the text
    for (size_t i = textLength-remain; i < textLength; ++i)
    {
        current.push_back(text[i]-' ');
    }

    // Fill the rest with fictive symbols so it can do the matrix multiplication
    for (size_t i = remain; i < matrixSize; ++i)
    {
        // TODO Maybe add different things instead of only fill symbols 
        current.push_back(fill);
    }
    encryptedPass+= multiplyMatrixWithString(current, keyMatrix);

    return encryptedPass;
}

std::string HillCipher::getType() const
{
    return "Hill";
}

// Helper method to encode length as 4-byte header
std::string HillCipher::encodeLengthHeader(size_t length) const
{
    std::string header(4, '\0');
    header[0] = (length >> 24) & 0xFF;
    header[1] = (length >> 16) & 0xFF;
    header[2] = (length >> 8) & 0xFF;
    header[3] = length & 0xFF;
    return header;
}

// Helper method to decode length from 4-byte header
size_t HillCipher::decodeLengthHeader(const std::string& header) const
{
    if(header.length() != 4)
        throw std::invalid_argument("Invalid length header");
    
    size_t length = 0;
    length |= (static_cast<unsigned char>(header[0]) << 24);
    length |= (static_cast<unsigned char>(header[1]) << 16);
    length |= (static_cast<unsigned char>(header[2]) << 8);
    length |= static_cast<unsigned char>(header[3]);
    return length;
}