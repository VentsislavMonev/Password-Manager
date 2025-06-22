#include "CesarCipher.hpp"
#include "DictionaryCipher.hpp"
#include "HillCipher.hpp"
#include "Entry.hpp"
#include "Entries.hpp"
#include "SquaredMatrix_zn.hpp"
#include "PasswordFile.hpp"
#include <string>
#include <iostream>
#include <cstdlib>

#include <chrono>

int main() 
{
    auto start = std::chrono::high_resolution_clock::now();

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
        std::cout<<aloda.getConfig()<<std::endl;
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
    std::cout<< fellas.getConfig()<<std::endl;

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
    Entry vhod1("pei.com", "pei40", "oomf");
    Entry vhod2("pei.com", "40pei", "daddycool");
    Entry vhod3("pei.com (noviq)", "qvorov", "oomf");
    vhod1.setEncryptedPassword("def");
    std::cout<<fellas.decrypt(vhod1.getEncryptedPassword())<<std::endl;
    // std::cin>>vhod;
    std::cout<<vhod1;

    try
    {
        Entries vhodove;
        vhodove.add(vhod1);
        vhodove.add(vhod1);
        vhodove.add(vhod1);
        vhodove.add(vhod2);
        vhodove.add(vhod3);

        vhodove.add(vhod2);
        std::vector<Entry> resu = vhodove.getEncryptedPassword("pei.com");
        vhodove.remove("pei.com", "pei40");
        vhodove.add(vhod1);
        std::cout<<vhodove.remove(vhod1)<<std::endl;
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    

    // try
    // {
    //     Entries vhodove;
    //     vhodove.push_back(vhod);

    //     Entries copy(vhodove);

    //     Entries test; 
    //     test.push_back(vhod);
    //     test.push_back(vhod);
    //     test.push_back(vhod);

    //     test = copy;
    // }
    // catch(const std::exception& e)
    // {
    //     std::cerr << e.what() << '\n';
    // }
    
    
    // Matrix
    //
    SquaredMatrix_zn a({{1,2,3, 21}, {0,3,4, 23}, {1,2,14, 12}, {5,6,7, 23}},4,95);
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

    std::string text = " ~ ~+=_-1234567890qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM,.;':[]{}";
    // std::string text = "luBO !~}";
    // std::string text = " ";
    // std::string text = "";
    // std::string text = "~";
    // std::string text = "~~";
    // std::string text = "~~~";
    std::cout<<std::endl;
    try
    {

        SquaredMatrix_zn aa({{1,2,3},{0,1,3},{0,0,1}},3,95);
        HillCipher ivVI(a);
        HillCipher iv(a);
        std::string ivString = iv.encrypt(text);
        std::string ivPass = iv.decrypt(ivString);

        // // std::cout << "\"";
        // // for (size_t i = 0; i < ivString.size(); i++)
        // // {
        // //     std::cout<<i+1<<"."<< (int)ivString[i]<<" - ";
        // // }
        // // std::cout<<"\"   -   " << ivString.size() << std::endl;
        
        // // std::cout << "\""<< ivString << "\"   -   " << ivString.size() << std::endl;
        std::cout << "\"" << ivPass << "\"" << std::endl;
        std::cout << iv.getConfig() << std::endl;
        ivVI.setConfig(iv.getConfig());
        std::cout << iv.getConfig() <<'\n'<< std::endl;


        // createCipher test
        //
        Cipher* nenko = Cipher::createCipher(CipherType::HILL, iv.getConfig());
        Cipher* nenko1 = Cipher::createCipher(CipherType::CESAR, fellas.getConfig());
        std::cout<< nenko->getConfig()<<std::endl;
        std::cout<< nenko1->getConfig()<<std::endl;

        Cipher* rado = Cipher::createCipher("HILL",iv.getConfig());
        std::cout<< rado->decrypt(rado->encrypt("zmei"))<<std::endl;
        
    }
    catch(const std::exception& e)
    {
        std::cout << e.what() << std::endl;
    }

    try
    {
        // PasswordFile::createFile("zlodei","CESAR", "3","CESAR", "33");
        // PasswordFile razdvatrii("zlodei","CESAR", "33");
        HillCipher iv(a);
        // PasswordFile::createFile("zlodei", "CESAR", "3", "HILL", iv.getConfig());

        PasswordFile blackMidi ("zlodei", "HILL", iv.getConfig());
        blackMidi.save("twitter.com", "shpenci", "mnogo taina parola");
        
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;
    std::cout << "Time taken: " << duration.count() << " seconds"<<std::endl;    
    
    return 0;
}