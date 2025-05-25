#include <iostream>
#include "CesarCipher.hpp"

int main() 
{
    CesarCipher fellas(3);
    CesarCipher hellas(-3);
    std::cout<<fellas.encrypt("abc")<< fellas.decrypt("def") << std::endl;
    std::cout<<hellas.encrypt("abc")<< hellas.decrypt("xyz") << std::endl;
    return 0;
}