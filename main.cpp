#include "CesarCipher.hpp"
#include "DictionaryCipher.hpp"
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

    try
    {
        std::string text = "lubo e mnogo gotin!";
        int matrixSize = 3;
        int remain = text.length()%matrixSize;
        size_t gei = text.length();

        const short allowedSymbolsCount = '~' - ' '; 
        // return (a % allowedSymbolsCount + allowedSymbolsCount) % allowedSymbolsCount;

        std::string ecnryptedPass;
        for (size_t i = 0; i < gei-remain ; i+=matrixSize)
        {
            std::string current;
            current.push_back((text[i]% allowedSymbolsCount + allowedSymbolsCount) % allowedSymbolsCount);
            current.push_back((text[i+1]% allowedSymbolsCount + allowedSymbolsCount) % allowedSymbolsCount);
            current.push_back((text[i+2]% allowedSymbolsCount + allowedSymbolsCount) % allowedSymbolsCount);

            

            std::string encryptedCurr;

            for (int i = 0; i < matrixSize; ++i) {
                int sum = 0;
                for (int j = 0; j < matrixSize; ++j) {
                    sum = (sum + a[i][j] * current[j]) % allowedSymbolsCount;
                }
                encryptedCurr.push_back((sum + allowedSymbolsCount) % allowedSymbolsCount);
                std::cout<<(int)sum<<", ";
            }
            ecnryptedPass+=encryptedCurr;
        }

        std::string current="";
        for (size_t i = gei-remain; i < gei; i++)
        {
            current.push_back((text[i]% allowedSymbolsCount + allowedSymbolsCount) % allowedSymbolsCount);
        }

        for (size_t i = remain; i < matrixSize; i++)
        {
            current.push_back(static_cast<char>(126-32));
        }



        std::string encryptedCurr;
        for (int i = 0; i < matrixSize; ++i) {
            int sum = 0;
            for (int j = 0; j < matrixSize; ++j) {
                sum = (sum + a[i][j] * current[j]) % allowedSymbolsCount;
            }
            encryptedCurr.push_back((sum + allowedSymbolsCount) % allowedSymbolsCount);
            std::cout<<(int)sum<<", ";
        }
        ecnryptedPass+=encryptedCurr;

        int index = ecnryptedPass.find((char)(126-32), gei-remain);
        ecnryptedPass = ecnryptedPass.substr(0,index);
        
        
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    
    return 0;
}