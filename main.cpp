#include "CesarCipher.hpp"
#include "DictionaryCipher.hpp"
#include "HillCipher.hpp"
#include "Entry.hpp"
#include "Entries.hpp"
#include "SquaredMatrix_zn.hpp"
#include <string>
#include <iostream>

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
    SquaredMatrix_zn a({{ 1,  2,  3,  4,  5,  6,  7,  8,  9, 10 },
    { 0,  1,  2,  3,  4,  5,  6,  7,  8,  9 },
    { 0,  0,  1,  2,  3,  4,  5,  6,  7,  8 },
    { 0,  0,  0,  1,  2,  3,  4,  5,  6,  7 },
    { 0,  0,  0,  0,  1,  2,  3,  4,  5,  6 },
    { 0,  0,  0,  0,  0,  1,  2,  3,  4,  5 },
    { 0,  0,  0,  0,  0,  0,  1,  2,  3,  4 },
    { 0,  0,  0,  0,  0,  0,  0,  1,  2,  3 },
    { 0,  0,  0,  0,  0,  0,  0,  0,  1,  2 },
    { 0,  0,  0,  0,  0,  0,  0,  0,  0,  1 }}, 10,95);
    try {
        // std::cout<<a.isInvertible()<<std::endl;
        // a.print();

        // std::cout<<std::endl;

        // a.getInverseMatrix().print();

        // std::cout<<std::endl;

        // (a*a.getInverseMatrix()).print();
    }
    catch(const std::exception& error) {
          std::cout << error.what() << std::flush;
    }


    //Hill Cipher

    std::string text = "lubo e mnogo GOTIN ~~~~ az sum golqm g=fen na lubo!ok mislq che tova e gotovo i bi trqbvalo da raboti za bezumno golqm tekst zashtoto pazq pametta v nachaloto i izpolzvam 4 byte a taka che eto istoriqta za kalofer ot wikipedia 15 puti:Kalofer was founded in the 16th century (1533). From the very beginning, it enjoyed town privileges, which allowed it to preserve its typical Bulgarian character. At the height of its economic boom, some 1,200 devices for producing traditional colored Bulgarian wollen threads (gaitan) operated at the town. The town has been burnt down at least three times. Forestation has mostly covered traces from the damage, but they can still be found here and there.With the passage of time, the residents of Kalofer devised their own methods of survival and cultivated a strength of character, which has remained their typical personality trait until today. Every single time the town was burnt, the people of Kalofer built it all over again, carrying stones from their own farming land, working through the night. Reconstruction activities usually started by re-building the church or the monastery.In July 1877, an attack by Circassian bashi-bazouk led to the massacre of 618 Bulgarians from the town and the nearby villages, while the entire town was (yet again) burned to the ground, along with 1308 houses, 250 stores, 200 ginning undertakings and watermills and 1400 stables.[2] Some 1,000 additional people lost their lives from exposure and the elements while climbing the Balkan Mountains in an attempt to reach Troyan. Kalofer was founded in the 16th century (1533). From the very beginning, it enjoyed town privileges, which allowed it to preserve its typical Bulgarian character. At the height of its economic boom, some 1,200 devices for producing traditional colored Bulgarian wollen threads (gaitan) operated at the town. The town has been burnt down at least three times. Forestation has mostly covered traces from the damage, but they can still be found here and there.With the passage of time, the residents of Kalofer devised their own methods of survival and cultivated a strength of character, which has remained their typical personality trait until today. Every single time the town was burnt, the people of Kalofer built it all over again, carrying stones from their own farming land, working through the night. Reconstruction activities usually started by re-building the church or the monastery.In July 1877, an attack by Circassian bashi-bazouk led to the massacre of 618 Bulgarians from the town and the nearby villages, while the entire town was (yet again) burned to the ground, along with 1308 houses, 250 stores, 200 ginning undertakings and watermills and 1400 stables.[2] Some 1,000 additional people lost their lives from exposure and the elements while climbing the Balkan Mountains in an attempt to reach Troyan. Kalofer was founded in the 16th century (1533). From the very beginning, it enjoyed town privileges, which allowed it to preserve its typical Bulgarian character. At the height of its economic boom, some 1,200 devices for producing traditional colored Bulgarian wollen threads (gaitan) operated at the town. The town has been burnt down at least three times. Forestation has mostly covered traces from the damage, but they can still be found here and there.With the passage of time, the residents of Kalofer devised their own methods of survival and cultivated a strength of character, which has remained their typical personality trait until today. Every single time the town was burnt, the people of Kalofer built it all over again, carrying stones from their own farming land, working through the night. Reconstruction activities usually started by re-building the church or the monastery.In July 1877, an attack by Circassian bashi-bazouk led to the massacre of 618 Bulgarians from the town and the nearby villages, while the entire town was (yet again) burned to the ground, along with 1308 houses, 250 stores, 200 ginning undertakings and watermills and 1400 stables.[2] Some 1,000 additional people lost their lives from exposure and the elements while climbing the Balkan Mountains in an attempt to reach Troyan. Kalofer was founded in the 16th century (1533). From the very beginning, it enjoyed town privileges, which allowed it to preserve its typical Bulgarian character. At the height of its economic boom, some 1,200 devices for producing traditional colored Bulgarian wollen threads (gaitan) operated at the town. The town has been burnt down at least three times. Forestation has mostly covered traces from the damage, but they can still be found here and there.With the passage of time, the residents of Kalofer devised their own methods of survival and cultivated a strength of character, which has remained their typical personality trait until today. Every single time the town was burnt, the people of Kalofer built it all over again, carrying stones from their own farming land, working through the night. Reconstruction activities usually started by re-building the church or the monastery.In July 1877, an attack by Circassian bashi-bazouk led to the massacre of 618 Bulgarians from the town and the nearby villages, while the entire town was (yet again) burned to the ground, along with 1308 houses, 250 stores, 200 ginning undertakings and watermills and 1400 stables.[2] Some 1,000 additional people lost their lives from exposure and the elements while climbing the Balkan Mountains in an attempt to reach Troyan. Kalofer was founded in the 16th century (1533). From the very beginning, it enjoyed town privileges, which allowed it to preserve its typical Bulgarian character. At the height of its economic boom, some 1,200 devices for producing traditional colored Bulgarian wollen threads (gaitan) operated at the town. The town has been burnt down at least three times. Forestation has mostly covered traces from the damage, but they can still be found here and there.With the passage of time, the residents of Kalofer devised their own methods of survival and cultivated a strength of character, which has remained their typical personality trait until today. Every single time the town was burnt, the people of Kalofer built it all over again, carrying stones from their own farming land, working through the night. Reconstruction activities usually started by re-building the church or the monastery.In July 1877, an attack by Circassian bashi-bazouk led to the massacre of 618 Bulgarians from the town and the nearby villages, while the entire town was (yet again) burned to the ground, along with 1308 houses, 250 stores, 200 ginning undertakings and watermills and 1400 stables.[2] Some 1,000 additional people lost their lives from exposure and the elements while climbing the Balkan Mountains in an attempt to reach Troyan. Kalofer was founded in the 16th century (1533). From the very beginning, it enjoyed town privileges, which allowed it to preserve its typical Bulgarian character. At the height of its economic boom, some 1,200 devices for producing traditional colored Bulgarian wollen threads (gaitan) operated at the town. The town has been burnt down at least three times. Forestation has mostly covered traces from the damage, but they can still be found here and there.With the passage of time, the residents of Kalofer devised their own methods of survival and cultivated a strength of character, which has remained their typical personality trait until today. Every single time the town was burnt, the people of Kalofer built it all over again, carrying stones from their own farming land, working through the night. Reconstruction activities usually started by re-building the church or the monastery.In July 1877, an attack by Circassian bashi-bazouk led to the massacre of 618 Bulgarians from the town and the nearby villages, while the entire town was (yet again) burned to the ground, along with 1308 houses, 250 stores, 200 ginning undertakings and watermills and 1400 stables.[2] Some 1,000 additional people lost their lives from exposure and the elements while climbing the Balkan Mountains in an attempt to reach Troyan. Kalofer was founded in the 16th century (1533). From the very beginning, it enjoyed town privileges, which allowed it to preserve its typical Bulgarian character. At the height of its economic boom, some 1,200 devices for producing traditional colored Bulgarian wollen threads (gaitan) operated at the town. The town has been burnt down at least three times. Forestation has mostly covered traces from the damage, but they can still be found here and there.With the passage of time, the residents of Kalofer devised their own methods of survival and cultivated a strength of character, which has remained their typical personality trait until today. Every single time the town was burnt, the people of Kalofer built it all over again, carrying stones from their own farming land, working through the night. Reconstruction activities usually started by re-building the church or the monastery.In July 1877, an attack by Circassian bashi-bazouk led to the massacre of 618 Bulgarians from the town and the nearby villages, while the entire town was (yet again) burned to the ground, along with 1308 houses, 250 stores, 200 ginning undertakings and watermills and 1400 stables.[2] Some 1,000 additional people lost their lives from exposure and the elements while climbing the Balkan Mountains in an attempt to reach Troyan. Kalofer was founded in the 16th century (1533). From the very beginning, it enjoyed town privileges, which allowed it to preserve its typical Bulgarian character. At the height of its economic boom, some 1,200 devices for producing traditional colored Bulgarian wollen threads (gaitan) operated at the town. The town has been burnt down at least three times. Forestation has mostly covered traces from the damage, but they can still be found here and there.With the passage of time, the residents of Kalofer devised their own methods of survival and cultivated a strength of character, which has remained their typical personality trait until today. Every single time the town was burnt, the people of Kalofer built it all over again, carrying stones from their own farming land, working through the night. Reconstruction activities usually started by re-building the church or the monastery.In July 1877, an attack by Circassian bashi-bazouk led to the massacre of 618 Bulgarians from the town and the nearby villages, while the entire town was (yet again) burned to the ground, along with 1308 houses, 250 stores, 200 ginning undertakings and watermills and 1400 stables.[2] Some 1,000 additional people lost their lives from exposure and the elements while climbing the Balkan Mountains in an attempt to reach Troyan. Kalofer was founded in the 16th century (1533). From the very beginning, it enjoyed town privileges, which allowed it to preserve its typical Bulgarian character. At the height of its economic boom, some 1,200 devices for producing traditional colored Bulgarian wollen threads (gaitan) operated at the town. The town has been burnt down at least three times. Forestation has mostly covered traces from the damage, but they can still be found here and there.With the passage of time, the residents of Kalofer devised their own methods of survival and cultivated a strength of character, which has remained their typical personality trait until today. Every single time the town was burnt, the people of Kalofer built it all over again, carrying stones from their own farming land, working through the night. Reconstruction activities usually started by re-building the church or the monastery.In July 1877, an attack by Circassian bashi-bazouk led to the massacre of 618 Bulgarians from the town and the nearby villages, while the entire town was (yet again) burned to the ground, along with 1308 houses, 250 stores, 200 ginning undertakings and watermills and 1400 stables.[2] Some 1,000 additional people lost their lives from exposure and the elements while climbing the Balkan Mountains in an attempt to reach Troyan. Kalofer was founded in the 16th century (1533). From the very beginning, it enjoyed town privileges, which allowed it to preserve its typical Bulgarian character. At the height of its economic boom, some 1,200 devices for producing traditional colored Bulgarian wollen threads (gaitan) operated at the town. The town has been burnt down at least three times. Forestation has mostly covered traces from the damage, but they can still be found here and there.With the passage of time, the residents of Kalofer devised their own methods of survival and cultivated a strength of character, which has remained their typical personality trait until today. Every single time the town was burnt, the people of Kalofer built it all over again, carrying stones from their own farming land, working through the night. Reconstruction activities usually started by re-building the church or the monastery.In July 1877, an attack by Circassian bashi-bazouk led to the massacre of 618 Bulgarians from the town and the nearby villages, while the entire town was (yet again) burned to the ground, along with 1308 houses, 250 stores, 200 ginning undertakings and watermills and 1400 stables.[2] Some 1,000 additional people lost their lives from exposure and the elements while climbing the Balkan Mountains in an attempt to reach Troyan. Kalofer was founded in the 16th century (1533). From the very beginning, it enjoyed town privileges, which allowed it to preserve its typical Bulgarian character. At the height of its economic boom, some 1,200 devices for producing traditional colored Bulgarian wollen threads (gaitan) operated at the town. The town has been burnt down at least three times. Forestation has mostly covered traces from the damage, but they can still be found here and there.With the passage of time, the residents of Kalofer devised their own methods of survival and cultivated a strength of character, which has remained their typical personality trait until today. Every single time the town was burnt, the people of Kalofer built it all over again, carrying stones from their own farming land, working through the night. Reconstruction activities usually started by re-building the church or the monastery.In July 1877, an attack by Circassian bashi-bazouk led to the massacre of 618 Bulgarians from the town and the nearby villages, while the entire town was (yet again) burned to the ground, along with 1308 houses, 250 stores, 200 ginning undertakings and watermills and 1400 stables.[2] Some 1,000 additional people lost their lives from exposure and the elements while climbing the Balkan Mountains in an attempt to reach Troyan. Kalofer was founded in the 16th century (1533). From the very beginning, it enjoyed town privileges, which allowed it to preserve its typical Bulgarian character. At the height of its economic boom, some 1,200 devices for producing traditional colored Bulgarian wollen threads (gaitan) operated at the town. The town has been burnt down at least three times. Forestation has mostly covered traces from the damage, but they can still be found here and there.With the passage of time, the residents of Kalofer devised their own methods of survival and cultivated a strength of character, which has remained their typical personality trait until today. Every single time the town was burnt, the people of Kalofer built it all over again, carrying stones from their own farming land, working through the night. Reconstruction activities usually started by re-building the church or the monastery.In July 1877, an attack by Circassian bashi-bazouk led to the massacre of 618 Bulgarians from the town and the nearby villages, while the entire town was (yet again) burned to the ground, along with 1308 houses, 250 stores, 200 ginning undertakings and watermills and 1400 stables.[2] Some 1,000 additional people lost their lives from exposure and the elements while climbing the Balkan Mountains in an attempt to reach Troyan. Kalofer was founded in the 16th century (1533). From the very beginning, it enjoyed town privileges, which allowed it to preserve its typical Bulgarian character. At the height of its economic boom, some 1,200 devices for producing traditional colored Bulgarian wollen threads (gaitan) operated at the town. The town has been burnt down at least three times. Forestation has mostly covered traces from the damage, but they can still be found here and there.With the passage of time, the residents of Kalofer devised their own methods of survival and cultivated a strength of character, which has remained their typical personality trait until today. Every single time the town was burnt, the people of Kalofer built it all over again, carrying stones from their own farming land, working through the night. Reconstruction activities usually started by re-building the church or the monastery.In July 1877, an attack by Circassian bashi-bazouk led to the massacre of 618 Bulgarians from the town and the nearby villages, while the entire town was (yet again) burned to the ground, along with 1308 houses, 250 stores, 200 ginning undertakings and watermills and 1400 stables.[2] Some 1,000 additional people lost their lives from exposure and the elements while climbing the Balkan Mountains in an attempt to reach Troyan. Kalofer was founded in the 16th century (1533). From the very beginning, it enjoyed town privileges, which allowed it to preserve its typical Bulgarian character. At the height of its economic boom, some 1,200 devices for producing traditional colored Bulgarian wollen threads (gaitan) operated at the town. The town has been burnt down at least three times. Forestation has mostly covered traces from the damage, but they can still be found here and there.With the passage of time, the residents of Kalofer devised their own methods of survival and cultivated a strength of character, which has remained their typical personality trait until today. Every single time the town was burnt, the people of Kalofer built it all over again, carrying stones from their own farming land, working through the night. Reconstruction activities usually started by re-building the church or the monastery.In July 1877, an attack by Circassian bashi-bazouk led to the massacre of 618 Bulgarians from the town and the nearby villages, while the entire town was (yet again) burned to the ground, along with 1308 houses, 250 stores, 200 ginning undertakings and watermills and 1400 stables.[2] Some 1,000 additional people lost their lives from exposure and the elements while climbing the Balkan Mountains in an attempt to reach Troyan. Kalofer was founded in the 16th century (1533). From the very beginning, it enjoyed town privileges, which allowed it to preserve its typical Bulgarian character. At the height of its economic boom, some 1,200 devices for producing traditional colored Bulgarian wollen threads (gaitan) operated at the town. The town has been burnt down at least three times. Forestation has mostly covered traces from the damage, but they can still be found here and there.With the passage of time, the residents of Kalofer devised their own methods of survival and cultivated a strength of character, which has remained their typical personality trait until today. Every single time the town was burnt, the people of Kalofer built it all over again, carrying stones from their own farming land, working through the night. Reconstruction activities usually started by re-building the church or the monastery.In July 1877, an attack by Circassian bashi-bazouk led to the massacre of 618 Bulgarians from the town and the nearby villages, while the entire town was (yet again) burned to the ground, along with 1308 houses, 250 stores, 200 ginning undertakings and watermills and 1400 stables.[2] Some 1,000 additional people lost their lives from exposure and the elements while climbing the Balkan Mountains in an attempt to reach Troyan. ";
    // std::string text = "luBO !~}";
    // std::string text = " ";
    // std::string text = "";
    // std::string text = "~";
    // std::string text = "~~";
    // std::string text = "~~~";
    // std::string text = "{~ =+-_a sdASDZXC zxc ~}";
    std::cout<<std::endl;
    try
    {
        HillCipher iv(a);
        std::string ivString = iv.encrypt(text);
        std::string ivPass = iv.decrypt(ivString);

        // std::cout << "\"";
        // for (size_t i = 0; i < ivString.size(); i++)
        // {
        //     std::cout<<i+1<<"."<< (int)ivString[i]<<" - ";
        // }
        // std::cout<<"\"   -   " << ivString.size() << std::endl;
        
        // std::cout << "\""<< ivString << "\"   -   " << ivString.size() << std::endl;
        std::cout << "\"" << ivPass << "\"" << std::endl;
    }
    catch(const std::exception& e)
    {
        std::cout << e.what() << std::endl;
    }
    
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;
    std::cout << "Time taken: " << duration.count() << " seconds"<<std::endl;
    return 0;
}