// #include "HillCipher.hpp"

// HillCipher::HillCipher()
// {
// }

// HillCipher::HillCipher(const SquaredMatrix_zn &_keyMatrix) :keyMatrix(_keyMatrix), fill('\0')
// {
//     //TODO to make it work with a random matrix dimension
//     // if(_keyMatrix.getDimension()!=3)
//     //     throw std::invalid_argument("Key matrix must be with dimension 3!");
//     invertedMatrix = keyMatrix.getInverseMatrix();
// }


// std::string DictionaryCipher::encrypt(const std::string &text) const
// {
//     int remain = text.length()%3;
//     int count = text.length() - remain;
//     size_t length = text.length();

//     std::string result;
//     for (size_t i = 0; i < count ; i=i+3)
//     {
//         std::string current;
//         current.reserve(3);
//         current[0]=text[i];
//         current[1]=text[i+1];
//         current[2]=text[i+2];
//     }
    
// }

// std::string DictionaryCipher::decrypt(const std::string &pass) const
// {

// }