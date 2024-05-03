#include <iostream>
#include "string5.h"
#include "vonatok.h"

Jarat::Jarat(int maxh, int* helyek, String* megallok, int* idopont, int szam): maxhely(maxh), hely(helyek), megallok(megallok), idopont(idopont), megallokszama(szam){};

void Jarat::jaratkiir(){
    for (size_t i = 0; i < megallokszama; i++)
    {
        std::cout << megallok[i] << " ";
    }
    std::cout << std::endl;
    for (size_t i = 0; i < megallokszama; i++)
    {
        std::cout << idopont[i];
    }
    
}

Jarat Jarat::operator=(const Jarat& jarat){
    maxhely = jarat.maxhely;
    delete[] hely;
    megallokszama = jarat.megallokszama;
    hely = new int[megallokszama];
       delete[] megallok;
    megallok = new String[megallokszama];
    delete[] idopont;
    idopont = new int[megallokszama];
    for (size_t i = 0; i < megallokszama; i++)
    {
        hely[i] = jarat.hely[i];
        megallok[i] = jarat.megallok[i];
        idopont[i] = jarat.idopont[i];
    }
    
}

void Jegy::Nyomtat(){
    std::cout << "Részletek: " << std::endl;
}

Menetrend::Menetrend(): jaratok(nullptr), jegyek(nullptr), jaratokszama(0), jegyekszama(0){};

void Menetrend::jegyhozzaad(const Jegy& jegy){
    Jegy* tmp = new Jegy[jegyekszama+1];
    for (size_t i = 0; i < jegyekszama; i++)
    {
        tmp[i] = jegyek[i];
    }
    jegyekszama++;
    tmp[jegyekszama] = jegy;
    

}

void Menetrend::jarathozzaad(const Jarat& jarat){
    Jarat* tmp = new Jarat[jaratokszama+1];
    for (size_t i = 0; i < jaratokszama; i++)
    {
        tmp[i] = jaratok[i];
    }
    jaratokszama++;
    tmp[jaratokszama] = jarat;
    
}

void Menetrend::jegykeres(String kezdo, String cel){
    int talalt1 = -1;
    int talalt2 = -1;
    for (size_t i = 0; i < jaratokszama; i++)
    {
            String* tmp = jaratok[i].getmegallok();
        for (size_t j = 0; j < jaratok[i].getmegallokszama(); j++)
        {
            if (tmp[j] == kezdo)
            {
                talalt1 = i;
            }
            if (tmp[j] == cel)
            {
                talalt2 = i;
            }   
        }

        
    }
    if (talalt1 == talalt2) // a két feltételt fel kell cserélni :D
    {
        std::cout << "van talalat" << std::endl;
        
    }else if(talalt1 == -1 || talalt2 == -1){
    
            std::cout << "nincs ilyen útvonal";
    
    }else{
        Menetrend lehetseges;
        for (size_t i = 0; i < jaratokszama; i++)
        {
            String* tmp = jaratok[i].getmegallok();
            for (size_t j = 0; j < jaratok[i].getmegallokszama(); j++)
            {
                if (tmp[j] == cel || tmp[j] == kezdo)
                {
                    lehetseges.jarathozzaad(jaratok[i]);
                }
                
                
            }
            
        }
        
        //közös pontok vizsgálata

    }

    
    
}

void Menetrend::menetrendKiir(){
    std::cout << "Menetrend";
    for (size_t i = 0; i < jaratokszama; i++)
    {
       jaratok[i].jaratkiir();
    }
    

}

void Menetrend::menetrendbetolt(const char* filename){

}

