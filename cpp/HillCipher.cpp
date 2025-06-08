#include "HillCipher.hpp"
#include <cstdlib>

HillCipher::HillCipher(const SquaredMatrix_zn &_keyMatrix) 
{
    if(_keyMatrix.getDimension()<3)
        throw std::invalid_argument("Key matrix must be with dimension bigger than 3 !");
    if(_keyMatrix.getModNumber()-1!='~' - ' ')
        throw std::invalid_argument("Key matrix must be from Z_"+ std::to_string(_keyMatrix.getModNumber()));
    if(!_keyMatrix.isInvertible())
        throw std::invalid_argument("Key matrix must be invertible!");

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
    std::string lengthHeader = encodeLengthHeader(text.length());
    
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
    for (size_t i = 4; i < length; ++i)  // Skip the header where length is stored
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
        char fill = static_cast<unsigned char>(rand() % '~' - ' ');
        current.push_back(fill);
    }
    encryptedPass+= multiplyMatrixWithString(current, keyMatrix);

    return encryptedPass;
}

CipherType HillCipher::getType() const
{
    return CipherType::HILL;
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

std::string HillCipher::getConfig() const
{
    int dimension = keyMatrix.getDimension();
    std::string config = std::to_string(dimension) + ":";
    for (int i = 0; i < dimension; ++i) 
    {
        for (int j = 0; j < dimension; ++j) 
        {
            config += std::to_string(keyMatrix[i][j]);
            if (i != dimension - 1 || j != dimension - 1) config += ",";
        }
    }
    return config;
}

void HillCipher::setConfig(const std::string &config)
{
    // checks if the config start with a number that should be the dimension and if it has a ':'
    size_t colonPos = config.find(':');
    if (colonPos == std::string::npos || (config[0]<'0' ||config[0]>'9')) throw std::runtime_error("Invalid Hill cipher config format");

    int dim = std::stoi(config.substr(0, colonPos));
    
    if(dim<3)
        throw std::invalid_argument("Key matrix must be with dim bigger than 3 !");

    std::vector<std::vector<int>> configMatrix (dim, std::vector<int>(dim));
    std::string matrixString = config.substr(colonPos + 1);
    size_t matrixStringLength = matrixString.length();
    size_t pos = 0;
    int row = 0, col = 0;

    while (pos < matrixStringLength && row < dim)
    {
        size_t nextComma = matrixString.find(',', pos);
        if (nextComma == std::string::npos) nextComma = matrixStringLength;
        
        // checks if the config is invalid
        if(config[pos]<'0' ||config[pos]>'9') throw std::runtime_error("Invalid Hill cipher config format");

        configMatrix[row][col] = std::stoi(matrixString.substr(pos, nextComma - pos));
        
        col++;
        if (col >= dim)
        {
            col = 0;
            row++;
        }
        
        pos = nextComma + 1;
    }
    
    SquaredMatrix_zn matrix_zn(configMatrix, dim, '~' - ' ' + 1);

    if(!matrix_zn.isInvertible())
        throw std::invalid_argument("Key matrix must be invertible!");

    keyMatrix = matrix_zn;
    invertedMatrix = keyMatrix.getInverseMatrix();
    
}
