#include <iostream>
#include "CesarCipher.hpp"
#include "DictionaryCipher.hpp"

int main() 
{
    CesarCipher fellas(3);
    CesarCipher hellas(-3);
    std::cout<<fellas.encrypt("abc")<< fellas.decrypt("def") << std::endl;
    std::cout<<hellas.encrypt("abc")<< hellas.decrypt("xyz") << std::endl<<std::endl;

    DictionaryCipher aloda("aluboegotin");
    std::string result = aloda.encrypt("bogota");
    for (size_t i = 0; i < result.size(); i++)
    {
        std::cout<<(int)result[i]<<std::endl;
    }
    
    std::cout<<aloda.decrypt(result)<<std::endl;
    return 0;
}