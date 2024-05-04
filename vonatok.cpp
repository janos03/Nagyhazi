#include <iostream>
#include "string5.h"
#include "vonatok.h"

Jarat::Jarat(int maxh, int* helyek, String* megallok, int* idopont, int szam): maxhely(maxh), hely(helyek), megallok(megallok), idopont(idopont), megallokszama(szam){};

void Jarat::jaratkiir(){
    for (int i = 0; i < megallokszama; i++)
    {
        std::cout << megallok[i] << " ";
    }
    std::cout << std::endl;
    for (int i = 0; i < megallokszama; i++)
    {
        std::cout << idopont[i];
    }
    
}

Jarat& Jarat::operator=(const Jarat& jarat){
    maxhely = jarat.maxhely;
    delete[] hely;
    megallokszama = jarat.megallokszama;
    hely = new int[megallokszama];
       delete[] megallok;
    megallok = new String[megallokszama];
    delete[] idopont;
    idopont = new int[megallokszama];
    for (int i = 0; i < megallokszama; i++)
    {
        hely[i] = jarat.hely[i];
        megallok[i] = jarat.megallok[i];
        idopont[i] = jarat.idopont[i];
    }
    return *this;
    
}

void Jegy::Nyomtat(){
    std::cout << "Részletek: " << std::endl;
}



void Menetrend::jegyhozzaad(const Jegy& jegy){
    Jegy* tmp = new Jegy[jegyekszama+1];
    for (int i = 0; i < jegyekszama; i++)
    {
        tmp[i] = jegyek[i];
    }
    tmp[jegyekszama] = jegy;
    jegyekszama++;
    

}

void Menetrend::jarathozzaad(const Jarat& jarat){
    Jarat* tmp = new Jarat[jaratokszama+1];
    for (int i = 0; i < jaratokszama; i++)
    {
        tmp[i] = jaratok[i];
    }
    jaratokszama++;
    tmp[jaratokszama] = jarat;
    
}

Jarat* Menetrend::jegykeres(String kezdo, String cel){
    int talalt1 = -1;
    int talalt2 = -1;
    for (int i = 0; i < jaratokszama; i++)
    {
            String* tmp = jaratok[i].getmegallok();
        for (int j = 0; j < jaratok[i].getmegallokszama(); j++)
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
    if (talalt1 == -1 || talalt2 == -1) // a két feltételt fel kell cserélni :D
    {
            std::cout << "nincs ilyen útvonal";
            return nullptr;
        
    }else if(talalt1 == talalt2){
    
        std::cout << "van talalat" << std::endl;
        Jarat* lista = new Jarat[1];
        lista[0] = jaratok[talalt1];
        return lista;
    
    }else{
        Menetrend lehetseges;
        for (int i = 0; i < jaratokszama; i++)
        {
            String* tmp = jaratok[i].getmegallok();
            for (int j = 0; j < jaratok[i].getmegallokszama(); j++)
            {
                if (tmp[j] == cel || tmp[j] == kezdo)
                {
                    lehetseges.jarathozzaad(jaratok[i]);
                }
                
                
            }
            
        }
        
        //közös pontok vizsgálata majd később
        

    }

    return nullptr;
    
}

void Menetrend::menetrendKiir(){
    std::cout << "Menetrend";
    for (int i = 0; i < jaratokszama; i++)
    {
       jaratok[i].jaratkiir();
    }
    

}

void Menetrend::menetrendbetolt(const char* filename){

}

