#include <iostream>
#include <fstream>
#include "string5.h"
#include "vonatok.h"

//----------------------------------------------------------------------------
//  vonatok.cpp, ebben a fájlban van megvalósítva a legtöbb tagfüggvény, és pár globális függvény is
//  Minden olyan függvény ami pár sorból áll azt a vonatok.h-ban van megírva
//----------------------------------------------------------------------------

//Tagfüggvények:--------------------------------------------------------

//Járat konstruktora:
Jarat::Jarat(int jaratszam, int maxh, int* helyek, String* megallok, int* idopont, int szam)
    :jaratszam(jaratszam), maxhely(maxh), megallokszama(szam) {
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
    :jaratszam(jarat.jaratszam), maxhely(jarat.maxhely), megallokszama(jarat.megallokszama) {
    hely = new int[megallokszama];
    idopont = new int[megallokszama];
    megallok = new String[megallokszama];

    for (int i = 0; i < megallokszama; ++i) {
        hely[i] = jarat.hely[i];
        idopont[i] = jarat.idopont[i];
        megallok[i] = jarat.megallok[i];
    }
}

//Kiírja a megállókat illetve az időpontokat;
void Jarat::jaratkiir(){
    std::cout << jaratszam << std::endl;
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
    jaratszam = jarat.jaratszam;

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

//kiíírja a képernyőre a jegy információit
void Jegy::Nyomtat() const{
    std::cout << "Név: " << nev << std::endl;
    std::cout << "Kedvezményes: " << (kedvezmenyes ? "Igen" : "Nem") << std::endl;
    std::cout << "Kezdő megálló: " << kezdomegallo << std::endl;
    std::cout << "Cél megálló: " << celmegallo << std::endl;
    int ora = idopont / 60; 
    int perc = idopont % 60; 
    std::cout << "Indulás időpontja: " << ora << ":" << perc << std::endl;
}

//Jegy információk kiírása egy fájlba, "hasonlít" egy valódi jegyhez, ez a valódi nyomtatás

void Jegy::jegykiirfajlba(const char* filename) const{
    std::ofstream file(filename, std::ios::app); // Hozzáfüzés mód beállítása
    if (!file.is_open())
    {
        std::cerr << "Hiba: A fájl nem nyitható meg.";
        return;
    }
    file.exceptions(std::ifstream::badbit);
    file << "------------------------" << std::endl;
    file << "      Menetjegy      " << std:: endl;
    file << std::endl;
    file << "Név: " << nev << std::endl;
    file << "Kedvezményes: " << (kedvezmenyes ? "igen" : "nem") << std::endl;
    file << "Helyszám: " << helyszam << std::endl;
    file << "Időpont: " << idopont/60 << ":" << idopont%60 <<std::endl;
    file << "Kezdőmegálló: " << kezdomegallo << std::endl;
    file << "Célállomás: " << celmegallo << std::endl;
    file << "-------------------------" << std::endl;
    file.close();
}

void Jegyatszallas::jegykiirfajlba(const char* filename) const{
        Jegy::jegykiirfajlba(filename);
        std::ofstream file(filename, std::ios::app);
        file.exceptions(std::ifstream::badbit);
        file << "Átszállás: " << atszallas << std::endl;
        file << "-----------------------" << std::endl;
        file.close();
}

//jelenleg nem használt függvény, célja a  helyfoglalás lebonyolítása lenne, erre még nem találtam ki a pontos metódust, maximum annyi lesz, hogy ahol járat van ott 1-el csökkent, de benne hagyok mintdent hogy később implementálható legyen. UPDATE!!!: Megoldottam és ezzel már működik a helyfoglalás


bool Jarat::jegyfoglal(int hely_index) {
        if (hely[hely_index] >= 0 && hely[hely_index] < maxhely)
        {
            hely[hely_index]++;
            return true;
        }else{
          std::cout <<  "Sajnálom nincs elég hely a vonaton." << std::endl; 
          return false;
        }
        
}

//jegy hozzáadása a jegy listához a menetrend osztályban
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

//ugyanazt mint az előző csak az átszállásos jegyeknél
void Menetrend::jegyhozzaad(const Jegyatszallas& jegy) {
        Jegyatszallas* tmp = new Jegyatszallas[jegyekatszallassaldb + 1];
        for (int i = 0; i < jegyekatszallassaldb; i++) {
            tmp[i] = jegyekatszallas[i];
        }
        delete[] jegyekatszallas;
        jegyekatszallas = tmp;
        jegyekatszallas[jegyekatszallassaldb++] = jegy;
    }
//járat hozzáadása a menetrendhez
 void Menetrend::jarathozzaad(const Jarat& jarat) {
        
            Jarat* tmp = new Jarat[jaratokszama+1];
            for (int i = 0; i < jaratokszama; i++) {
                tmp[i] = jaratok[i];
            }
            delete[] jaratok;
            jaratok = tmp;
        
        jaratok[jaratokszama++] = jarat;
    }
//jegy keresés, legbonyolultabb algoritmus az egész feladatban, félek hozzányúlni.... 
Menetrend Menetrend::jegykeres(String kezdo, String cel) {
    Menetrend utvonal;
    bool talalt_kezdo = false;
    bool talalt_cel = false;

    for (int i = 0; i < jaratokszama; i++) {
        String* megallok = jaratok[i].getmegallok();
        for (int j = 0; j < jaratok[i].getmegallokszama(); j++) {
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

    int* szulo = new int[jaratokszama]; 
    bool* bejart = new bool[jaratokszama]{false}; 
    int* sor = new int[jaratokszama]; 
    for (int i = 0; i < jaratokszama; i++) {
        szulo[i] = -1; 
    }

    int eleje = 0, hatulja = 0; 
    for (int i = 0; i < jaratokszama; i++) {
        String* megallok = jaratok[i].getmegallok();
        for (int j = 0; j < jaratok[i].getmegallokszama(); j++) {
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
        for (int j = 0; j < jaratok[aktiv].getmegallokszama(); j++) {
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
        for (int i = 0; i < jaratokszama; i++) {
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
    // Helyfoglalás leegyszerűsítve |update|!!!!: megoldottam így ez feleslegesség vált, de a sethely függvényt nem törlöm ki.

    /*Jarat* jarathely = utvonal.getjaratok();
    for (int i = 0; i < utvonal.getjaratokszama(); i++)
    {
        int hely = jarathely[i].getmaxhely();
        if (hely <= 0)
        {
            std::cout << "Nincs elég hely a vonaton." ;
        }
        
        jarathely[i].sethely(hely-1);
    }*/
    
}

void Menetrend::menetrendKiir()const{
    std::cout << "Menetrend" << std::endl;;
    for (int i = 0; i < jaratokszama; i++)
    {
       jaratok[i].jaratkiir();
    }
    

}

void Jarat::jaratkiir(std::ofstream& file) {
    file << jaratszam << std::endl;
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

void Menetrend::menetrendKiir(const char* filename)const {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Hiba: A fájl nem nyitható meg." << std::endl;
        return;
    }
    for (int i = 0; i < jaratokszama; i++) {
        jaratok[i].jaratkiir(file);
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
        int jaratszam;
        int megallokszam;
        if (!(file >> jaratszam >> megallokszam)) { // Ellenőrizzük a beolvasás eredményét
            break; // Ha a beolvasás sikertelen, kilépünk a ciklusból
        }
        
        int* helyek = new int[megallokszam];
        char** megallok_tmp = new char*[megallokszam];
        int* idopontok = new int[megallokszam];

        // Adatok beolvasása
        for (int i = 0; i < megallokszam; ++i) {
            if (!(file >> helyek[i])) {
                break; // Ha a beolvasás sikertelen, kilépünk a ciklusból
            }
        }
        for (int i = 0; i < megallokszam; ++i) {
            megallok_tmp[i] = new char[256]; 
            if (!(file >> megallok_tmp[i])) {
                break; // Ha a beolvasás sikertelen, kilépünk a ciklusból
            }
        }
        for (int i = 0; i < megallokszam; ++i) {
            if (!(file >> idopontok[i])) {
                break; // Ha a beolvasás sikertelen, kilépünk a ciklusból
            }
        }

        // String objektumok létrehozása
        String* megallok = new String[megallokszam];
        for (int i = 0; i < megallokszam; ++i) {
            megallok[i] = String(megallok_tmp[i]);
            delete[] megallok_tmp[i];
        }

        // Jarat objektum létrehozása és hozzáadása a menetrendhez
        Jarat jarat(jaratszam, megallokszam, helyek, megallok, idopontok, megallokszam);
        jarathozzaad(jarat);

        // Dinamikusan foglalt memória felszabadítása
        delete[] helyek;
        delete[] megallok;
        delete[] idopontok;
        delete[] megallok_tmp;
    }

    file.close();
}



//Globális függvények:-------------------------------------------------------------

void jegyteszt(Menetrend& menetrend, Jegy& jegy){
Menetrend talalt = menetrend.jegykeres(jegy.getkezdomegallo(), jegy.getcelmegallo());
    bool vanhely = true;

    //sima Jegy kezelése:
    //###############################################################
    if (talalt.getjaratokszama() == 1) {
        Jarat* jarathely = talalt.getjaratok();
        int kezdo;
        int cel;
        for (int i = 0; i < talalt.getjaratokszama(); i++)
        {
            String* megallok = jarathely[i].getmegallok();
            // Nem foglalkozok azzal ha valaki A-ból A ba megy akkor sétáljon és ne vegyen jegyet
            for (int j = 0; j < jarathely[i].getmegallokszama(); j++) 
            {
                if (megallok[j] == jegy.getkezdomegallo()){kezdo = j; jegy.setido(jarathely[i].getidopont(j));}else if(megallok[j] == jegy.getcelmegallo()){cel = j;} 
            }

            for (int j = kezdo; j < cel ; j++){
                
                if(!jarathely[i].jegyfoglal(j)){vanhely = false;} 
            
            }
            if (vanhely)
            {
                jegy.sethelyszam(jarathely[0].gethely(kezdo));
                std::cout <<jarathely[0].gethely(kezdo) << " ez a helyzám"; //érdekesség, ezt kiírja minden jegyvásárláskor és jól... viszont a fájlban már nem jó
                menetrend.jegyhozzaad(jegy);
                std::cout << "Jegy sikeresen vásárolva." << std::endl;
                for (int i = 0; i < talalt.getjaratokszama(); i++)
                {
                frissitJarat(menetrend, jarathely[i]);
                }
              
            }
            
            
        }
        

        
    //Átszállásos jegy kezelése:
    //#################################################################

    } else if (talalt.getjaratokszama() == 2) {
        // Ellenőrizzük, hogy a két járat között van-e közös pont
        String* kezdo_megallok = talalt.getjaratok()[0].getmegallok();
        String* cel_megallok = talalt.getjaratok()[1].getmegallok();
        String atszallas_megallo;
        for (int i = 0; i < talalt.getjaratok()[0].getmegallokszama(); ++i) {
            for (int j = 0; j < talalt.getjaratok()[1].getmegallokszama(); ++j) {
                if (kezdo_megallok[i] == cel_megallok[j]) {
                    atszallas_megallo = kezdo_megallok[i];
                    break;
                }
            }
        }
        if (!(atszallas_megallo=="")) {
            Jegyatszallas jegy_atszallas(jegy.getnev(), true, jegy.getkezdomegallo(), jegy.getcelmegallo(), jegy.getidopont(), atszallas_megallo);
            Jarat* jarathely = talalt.getjaratok();
            int kezdo;
            int cel;
            //amiatt kell 2 darab atszallasindex jelző, mert az első járatban nem feltétlen ugyanazon a helyen van mint a második járatban 
            int atszallas1 = -1, atszallas2; // ide dob egy warningot azt tudom de csak amiatt mert nincs inicializálva, de jelen esetben ezt nem is kell.
            for (int i = 0; i < talalt.getjaratokszama(); i++)
            {
                String* megallok = jarathely[i].getmegallok();
                // Nem foglalkozok azzal ha valaki A-ból A ba megy akkor sétáljon és ne vegyen jegyet
                for (int j = 0; j < jarathely[i].getmegallokszama(); j++) 
                {
                    if (megallok[j] == jegy.getkezdomegallo()){kezdo = j;}else if(megallok[j] == jegy.getcelmegallo()){cel = j;}else if(megallok[j] == atszallas_megallo){atszallas2 = j;}else if(atszallas1 == -1 && megallok[j] == atszallas_megallo){atszallas1 = j;}
                }
                
                
                }
                    for (int i = kezdo; i < atszallas1; i++)
                {
                    if(!jarathely[1].jegyfoglal(i)){vanhely = false;};
                }
                    for (int i = atszallas2; i < cel; i++)
                {
                    if(!jarathely[0].jegyfoglal(i)){vanhely = false;};
                 
                }
                if (vanhely)
                {
            
                    jegy.sethelyszam(jarathely[0].gethely(kezdo));
                    menetrend.jegyhozzaad(jegy_atszallas);
                    std::cout << "Átszállási jegy sikeresen vásárolva." << std::endl;
                for (int i = 0; i < talalt.getjaratokszama(); i++)
                    {
                    frissitJarat(menetrend, jarathely[i]);
                    }
                }
                
            
            
        } else {
            std::cout << "Nincs közös megálló a két járat között." << std::endl;
        }
    } else {
        std::cout << "Érvénytelen választás. Kérem válasszon újra." << std::endl;
    }
}
void frissitJarat(Menetrend& menetrend, Jarat& ujJarat) {
    Jarat* jaratok = menetrend.getjaratok();
    int jaratokSzama = menetrend.getjaratokszama();
    
    // Megkeressük a járatot az azonosító alapján
    for (int i = 0; i < jaratokSzama; ++i) {
        if (jaratok[i].getjaratszam() == ujJarat.getjaratszam()) {
            // Ha megtaláltuk a megfelelő járatot, felülírjuk azt az új járattal
            jaratok[i] = ujJarat;
            break; 
        }
    }
}

