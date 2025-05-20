#ifndef DICTIONARY_CIPHER_HPP
#define DICTIONARY_CIPHER_HPP

#include <string>
#include <vector>
#include "Cipher.hpp"

class DictionaryCipher : public Cipher
{
public:
    DictionaryCipher();
    DictionaryCipher(const std::string& _dictionaryText);

public:
    virtual std::string encrypt(const std::string& text) const override;
    virtual std::string decrypt(const std::string& pass) const override;

    std::string getType() const override;

private:
    void initializeDictionary();

private:
    std::string dictionaryText;
    std::unordered_map<char, int> charToPos;
    std::unordered_map<int, char> posToChar;


    // struct DictionaryEntry
    // {
    //     char symbol;
    //     int key;
    // };
    // std::vector<DictionaryEntry> vec;
    // void aloda () 
    // {
    //     for (size_t i = 0; i < dictionaryText.size(); i++)
    //     {
    //         bool flag=false;
    //         DictionaryEntry da;
    //         da.key=i;
    //         da.symbol=dictionaryText[i];

    //         for (size_t j = 0; j < vec.size(); j++)
    //         {
    //             if(vec[j].symbol == da.symbol)
    //             {
    //                 flag=true;
    //                 break;
    //             }
    //         }

    //         if(!flag) 
    //         {
    //             vec.push_back(da);
    //         }
            
    //     }
    // }
};

#endif