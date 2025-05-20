#ifndef HILL_CIPHER_HPP
#define HILL_CIPHER_HPP

#include <vector>
#include "Cipher.hpp"

class HillCipher : public Cipher
{
public:
    HillCipher();

private:
    std::vector<std::vector<short>> keyMatrix;
    std::vector<std::vector<short>> inverseMatrix;
    // da vidq kak she stane
};

#endif