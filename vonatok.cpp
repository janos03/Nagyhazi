#include <iostream>
#include <fstream>
#include "string5.h"
#include "vonatok.h"

Jarat::Jarat(int maxh, int* helyek, String* megallok, int* idopont, int szam)
    : maxhely(maxh), megallokszama(szam) {
    hely = new int[megallokszama];
    this->idopont = new int[megallokszama];
    this->megallok = new String[megallokszama];

    for (int i = 0; i < megallokszama; ++i) {
        hely[i] = helyek[i];
        this->idopont[i] = idopont[i];
        this->megallok[i] = megallok[i];
    }
}

Jarat::Jarat(const Jarat& jarat)
    : maxhely(jarat.maxhely), megallokszama(jarat.megallokszama) {
    hely = new int[megallokszama];
    idopont = new int[megallokszama];
    megallok = new String[megallokszama];

    for (int i = 0; i < megallokszama; ++i) {
        hely[i] = jarat.hely[i];
        idopont[i] = jarat.idopont[i];
        megallok[i] = jarat.megallok[i];
    }
}

void Jarat::jaratkiir(){
    for (int i = 0; i < megallokszama; i++)
    {
        std::cout << megallok[i] << " ";
    }
    std::cout << std::endl;
    for (int i = 0; i < megallokszama; i++)
    {
        std::cout << idopont[i] << " ";
    }
    std::cout << std::endl;
    
}

Jarat& Jarat::operator=(const Jarat& jarat) {
    if (this == &jarat) {
        return *this;
    }

    maxhely = jarat.maxhely;
    megallokszama = jarat.megallokszama;

    delete[] hely;
    delete[] idopont;
    delete[] megallok;

    hely = new int[megallokszama];
    idopont = new int[megallokszama];
    megallok = new String[megallokszama];

    for (int i = 0; i < megallokszama; ++i) {
        hely[i] = jarat.hely[i];
        idopont[i] = jarat.idopont[i];
        megallok[i] = jarat.megallok[i];
    }

    return *this;
}

void Jegy::Nyomtat() {
    std::cout << "Név: " << nev << std::endl;
    std::cout << "Kedvezményes: " << (kedvezmenyes ? "Igen" : "Nem") << std::endl;
    std::cout << "Kezdő megálló: " << kezdomegallo << std::endl;
    std::cout << "Cél megálló: " << celmegallo << std::endl;
    int ora = idopont / 60; 
    int perc = idopont % 60; 
    std::cout << "Indulás időpontja: " << ora << ":" << perc << std::endl;
}

void Jarat::jegyfoglal(int hely_index) {
        if (hely[hely_index] >= 0)
        {
            hely[hely_index]--;
        }else{
          std::cout <<  "Sajnálom nincs elég hely a vonaton." << std::endl; 
        }
        
}

void Menetrend::jegyhozzaad(const Jegy& jegy){

    Jegy* tmp = new Jegy[jegyekszama+1];
    for (int i = 0; i < jegyekszama; i++)
    {
        tmp[i] = jegyek[i];
    }
    delete[] jegyek;
    jegyek = tmp;
    jegyek[jegyekszama++] = jegy;
    

}

void Menetrend::jegyatszallashozzaad(const Jegyatszallas& jegy) {
        Jegyatszallas* tmp = new Jegyatszallas[jegyekatszallassaldb + 1];
        for (int i = 0; i < jegyekatszallassaldb; i++) {
            tmp[i] = jegyekatszallas[i];
        }
        delete[] jegyekatszallas;
        jegyekatszallas = tmp;
        jegyekatszallas[jegyekatszallassaldb++] = jegy;
    }

 void Menetrend::jarathozzaad(const Jarat& jarat) {
        
            Jarat* tmp = new Jarat[jaratokszama+1];
            for (int i = 0; i < jaratokszama; i++) {
                tmp[i] = jaratok[i];
            }
            delete[] jaratok;
            jaratok = tmp;
        
        jaratok[jaratokszama++] = jarat;
    }

Menetrend Menetrend::jegykeres(String kezdo, String cel) {
    Menetrend utvonal;
    bool talalt_kezdo = false;
    bool talalt_cel = false;

    for (int i = 0; i < jaratokszama; ++i) {
        String* megallok = jaratok[i].getmegallok();
        for (int j = 0; j < jaratok[i].getmegallokszama(); ++j) {
            if (megallok[j] == kezdo) {
                talalt_kezdo = true;
            }
            if (megallok[j] == cel) {
                talalt_cel = true;
            }
        }
    }

    if (!talalt_kezdo || !talalt_cel) {
        std::cout << "Nincs járat az adott útvonalon." << std::endl;
        return utvonal;
    }

    bool* bejart = new bool[jaratokszama]{false}; 
    int* sor = new int[jaratokszama]; 
    int* szulo = new int[jaratokszama]; 
    for (int i = 0; i < jaratokszama; ++i) {
        szulo[i] = -1; 
    }

    int eleje = 0, hatulja = 0; 
    for (int i = 0; i < jaratokszama; ++i) {
        String* megallok = jaratok[i].getmegallok();
        for (int j = 0; j < jaratok[i].getmegallokszama(); ++j) {
            if (megallok[j] == kezdo) {
                bejart[i] = true;
                sor[hatulja++] = i;
                szulo[i] = -1; 
                break;
            }
        }
    }

    while (eleje != hatulja) {
        int aktiv = sor[eleje++];
        String* megallok = jaratok[aktiv].getmegallok();
        for (int j = 0; j < jaratok[aktiv].getmegallokszama(); ++j) {
            if (megallok[j] == cel) {
                utvonal.jarathozzaad(jaratok[aktiv]);
                int elozo = szulo[aktiv];
                while (elozo != -1) {
                    utvonal.jarathozzaad(jaratok[elozo]);
                    elozo = szulo[elozo];
                }
                delete[] bejart;
                delete[] sor;
                delete[] szulo;
                return utvonal;
            }
        }
        for (int i = 0; i < jaratokszama; ++i) {
            if (!bejart[i]) {
                String* masik_megallok = jaratok[i].getmegallok();
                for (int k = 0; k < jaratok[i].getmegallokszama(); ++k) {
                    for (int l = 0; l < jaratok[aktiv].getmegallokszama(); ++l) {
                        if (masik_megallok[k] == megallok[l]) {
                            bejart[i] = true;
                            sor[hatulja++] = i;
                            szulo[i] = aktiv;
                        }
                    }
                }
            }
        }
    }

    std::cout << "Nincs járat az adott útvonalon." << std::endl;
    delete[] bejart;
    delete[] sor;
    delete[] szulo;
    return utvonal;
}



void Menetrend::menetrendKiir(){
    std::cout << "Menetrend" << std::endl;;
    for (int i = 0; i < jaratokszama; i++)
    {
       jaratok[i].jaratkiir();
    }
    

}

void Jarat::jaratkiir_fajlba(std::ofstream& file) {
    file << megallokszama << std::endl; 
    for (int i = 0; i < megallokszama; i++) {
        file << hely[i] << " "; 
    }
    file << std::endl;
    for (int i = 0; i < megallokszama; i++) {
        file << megallok[i] << " "; 
    }
    file << std::endl;
    for (int i = 0; i < megallokszama; i++) {
        file << idopont[i] << " "; 
    }
    file << std::endl;
}

void Menetrend::menetrend_kiir_fajlba(const char* filename) {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Hiba: A fájl nem nyitható meg." << std::endl;
        return;
    }
    for (int i = 0; i < jaratokszama; i++) {
        jaratok[i].jaratkiir_fajlba(file);
    }
    file.close();
}

void Menetrend::menetrendbetolt(const char* filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Hiba: A fájl nem nyitható meg." << std::endl;
        return;
    }

    while (true) {
        int megallokszam;
        file >> megallokszam;
        if (file.eof()) { // Ellenőrizzük, hogy elértük-e a fájl végét
            break; // Ha igen, kilépünk a ciklusból
        }
        
        int* helyek = new int[megallokszam];
        char** megallok_tmp = new char*[megallokszam];
        int* idopontok = new int[megallokszam];

        // Adatok beolvasása
        for (int i = 0; i < megallokszam; ++i) {
            file >> helyek[i];
        }
        for (int i = 0; i < megallokszam; ++i) {
            megallok_tmp[i] = new char[256]; 
            file >> megallok_tmp[i];
        }
        for (int i = 0; i < megallokszam; ++i) {
            file >> idopontok[i];
        }

        // String objektumok létrehozása
        String* megallok = new String[megallokszam];
        for (int i = 0; i < megallokszam; ++i) {
            megallok[i] = String(megallok_tmp[i]);
            delete[] megallok_tmp[i];
        }

        // Jarat objektum létrehozása és hozzáadása a menetrendhez
        Jarat jarat(megallokszam, helyek, megallok, idopontok, megallokszam);
        jarathozzaad(jarat);

        // Dinamikusan foglalt memória felszabadítása
        delete[] helyek;
        delete[] megallok;
        delete[] idopontok;
        delete[] megallok_tmp;
    }

    file.close();
}


