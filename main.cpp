#include "CesarCipher.hpp"
#include "DictionaryCipher.hpp"
#include "HillCipher.hpp"
#include "Entry.hpp"
#include "Entries.hpp"
#include "SquaredMatrix_zn.hpp"
#include <string>
#include <iostream>

int main() 
{
    // Dictionary cipher
    //
    try
    {
        DictionaryCipher aloda("chanaluboegotin");
        std::string result = aloda.encrypt("bogotachan");
        std::string result1 = aloda.encrypt("ab");
        for (size_t i = 0; i < result.size(); i++)
        {
            std::cout<<(int)result[i]<<std::endl;
        }
        std::cout<<aloda.decrypt(result)<<std::endl;
        std::cout<<aloda.decrypt(result1)<<std::endl;
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }

    std::cout<<std::endl;


    // Cesar cipher
    //
    CesarCipher fellas(3);
    CesarCipher hellas(-3);

    std::cout<<fellas.encrypt("abc")<<std::endl<< fellas.decrypt("def") << std::endl;
    std::cout<<hellas.encrypt("456")<<std::endl<< hellas.decrypt("123") << std::endl<<std::endl;

    try
    {
        std::string str;
        str.push_back((char)24);
        // fellas.encrypt(str);
        fellas.decrypt(str);
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }

    
    
    // Entries
    //
    Entry vhod("pei.com", "pei40", "oomf");
    vhod.setEncryptedPassword("def");
    std::cout<<fellas.decrypt(vhod.getEncryptedPassword())<<std::endl;
    // std::cin>>vhod;
    std::cout<<vhod;

    try
    {
        Entries vhodove;
        vhodove.push_back(vhod);

        Entries copy(vhodove);

        Entries test; 
        test.push_back(vhod);
        test.push_back(vhod);
        test.push_back(vhod);

        test = copy;
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    
    
    // Matrix
    //
    SquaredMatrix_zn a({{1,2,3}, {0,3, 23}, {1,2, 12}}, 3,94);
    try {
        std::cout<<a.isInvertible()<<std::endl;
        a.print();

        std::cout<<std::endl;

        a.getInverseMatrix().print();

        std::cout<<std::endl;

        (a*a.getInverseMatrix()).print();
    }
    catch(const std::exception& error) {
          std::cout << error.what() << std::flush;
    }


    //Hill Cipher

    std::string text = "lubo e mnogo gotin ~~~~ az sum golqm g=fen na lubo";
    std::cout<<std::endl;

    try
    {
        HillCipher iv(a);
        std::string ivString = iv.encrypt(text);
        std::cout<< ivString<<std::endl<<std::endl;
        std::cout<< iv.decrypt(ivString);
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    
    
    return 0;
}