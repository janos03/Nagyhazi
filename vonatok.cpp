#include <iostream>
#include <fstream>
#include "string5.h"
#include "vonatok.h"

//----------------------------------------------------------------------------
//  vonatok.cpp, ebben a fájlban van megvalósítva a legtöbb tagfüggvény, és pár globális függvény is
//  Minden olyan függvény ami pár sorból áll azt a vonatok.h-ban van megírva
//  A kommentek gondolatmeneteket is tartalmaznak, ami már nem érvényes ott hagyom jelzem, de legalább látom hogy mit csináltam
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

Jegy::Jegy(const Jegy& jegy) {
    nev = jegy.nev;
    kedvezmenyes = jegy.kedvezmenyes;
    kezdomegallo = jegy.kezdomegallo;
    celmegallo = jegy.celmegallo;
    idopont = jegy.idopont;
    helyszam = jegy.helyszam;
}

Jegyatszallas::Jegyatszallas(String n, bool kedv, String kezdo, String cel, int ido, String* atsz, int atszdb): Jegy(n, kedv, kezdo, cel, ido), atszallasdarab(atszdb){
    if (atszallasdarab > 0) {
        atszallas = new String[atszallasdarab];
        for (int i = 0; i < atszallasdarab; ++i) {
            this->atszallas[i] = atszallas[i];
        }
    } else {
        atszallas = nullptr;
    }
  
}

Jegyatszallas::Jegyatszallas(const Jegyatszallas& jegy) : Jegy(jegy) {
    if (jegy.atszallasdarab > 0) {
        atszallas = new String[jegy.atszallasdarab];
        for (int i = 0; i < jegy.atszallasdarab; ++i) {
            atszallas[i] = jegy.atszallas[i];
        }
    } else {
        atszallas = nullptr;
    }
    atszallasdarab = jegy.atszallasdarab;
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

void Jegy::Nyomtat(const char* filename) const{
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

void Jegyatszallas::Nyomtat(const char* filename) const{
        Jegy::Nyomtat(filename);
        std::ofstream file(filename, std::ios::app);
        file.exceptions(std::ifstream::badbit);
        file << "Átszállás: " << atszallas << std::endl;
        file << "-----------------------" << std::endl;
        file.close();
}

Jegyatszallas& Jegyatszallas::operator=(const Jegyatszallas& jegy){
     if (this == &jegy) 
        return *this;

   
    Jegy::operator=(jegy);

    delete[] atszallas; 

    if (jegy.atszallasdarab > 0) {
        atszallas = new String[jegy.atszallasdarab];
        for (int i = 0; i < jegy.atszallasdarab; ++i) {
            atszallas[i] = jegy.atszallas[i];
        }
    } else {
        atszallas = nullptr;
    }
    
    atszallasdarab = jegy.atszallasdarab;

    return *this;
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

        // Ellenőrizzük, hogy a kezdő és a cél megálló létezik-e
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
            std::cout << "Nem található útvonal." << std::endl;
            return utvonal;
        }

        // Szülő és bejárt adatszerkezetek inicializálása
        int* szulo = new int[jaratokszama];
        bool* bejart = new bool[jaratokszama]{false};
        int* sor = new int[jaratokszama];
        String* megallok_szulo = new String[jaratokszama];
        for (int i = 0; i < jaratokszama; ++i) {
            szulo[i] = -1;
        }

        int eleje = 0, hatulja = 0;

        // Kezdő állomás beállítása
        for (int i = 0; i < jaratokszama; i++) {
            String* megallok = jaratok[i].getmegallok();
            for (int j = 0; j < jaratok[i].getmegallokszama(); j++) {
                if (megallok[j] == kezdo) {
                    bejart[i] = true;
                    sor[hatulja++] = i;
                    szulo[i] = -1;
                    megallok_szulo[i] = kezdo;
                    break;
                }
            }
        }

        // Bejárás
        while (eleje != hatulja) {
            int aktiv = sor[eleje++];
            String* megallok = jaratok[aktiv].getmegallok();

            for (int j = 0; j < jaratok[aktiv].getmegallokszama(); j++) {
                if (megallok[j] == cel) {
                    utvonal.jarathozzaad(jaratok[aktiv]);
                    String elozo = megallok_szulo[aktiv];
                    int elozo_jarat = szulo[aktiv];

                    while (elozo_jarat != -1) {
                        utvonal.jarathozzaad(jaratok[elozo_jarat]);
                        elozo = megallok_szulo[elozo_jarat];
                        elozo_jarat = szulo[elozo_jarat];
                    }

                    delete[] bejart;
                    delete[] sor;
                    delete[] szulo;
                    delete[] megallok_szulo;
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
                                megallok_szulo[i] = masik_megallok[k];
                                break;
                            }
                        }
                        if (bejart[i]) break;
                    }
                }
            }
        }

        std::cout << "Nem található útvonal." << std::endl;
        delete[] bejart;
        delete[] sor;
        delete[] szulo;
        delete[] megallok_szulo;

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
        return utvonal;
    
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
    file << maxhely <<std::endl;
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
        int maxhely;
        if (!(file >> jaratszam >> megallokszam >> maxhely)) { // Ellenőrizzük a beolvasás eredményét
            break; // Ha a beolvasás sikertelen, kilépünk a ciklusból
        }
        
        int* helyek = new int[megallokszam];
        char** megallok_tmp = new char*[megallokszam];
        int* idopontok = new int[megallokszam];

        // Adatok beolvasása
        for (int i = 0; i < megallokszam; i++) {
            if (!(file >> helyek[i])) {
                break; // Ha a beolvasás sikertelen, kilépünk a ciklusból
            }
        }
        for (int i = 0; i < megallokszam; i++) {
            megallok_tmp[i] = new char[256]; 
            if (!(file >> megallok_tmp[i])) {
                break; // Ha a beolvasás sikertelen, kilépünk a ciklusból
            }
        }
        for (int i = 0; i < megallokszam; i++) {
            if (!(file >> idopontok[i])) {
                break; // Ha a beolvasás sikertelen, kilépünk a ciklusból
            }
        }

        // String objektumok létrehozása
        String* megallok = new String[megallokszam];
        for (int i = 0; i < megallokszam; i++) {
            megallok[i] = String(megallok_tmp[i]);
            delete[] megallok_tmp[i];
        }

        // Jarat objektum létrehozása és hozzáadása a menetrendhez
        Jarat jarat(jaratszam, maxhely, helyek, megallok, idopontok, megallokszam);
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
// ezt a függvényt szétszedni kisebbekre meg lehet de csak azért hogy kisebb függvények legyenek nincs értelme....
// át kell írni mert működik a keresés, és emiatt ez most nem fog precízen, illetve most sehogy...
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

    } else if (talalt.getjaratokszama() >= 2) {
        // Ellenőrizzük, hogy a két járat között van-e közös pont
        String* atszallas_megallok = new String[talalt.getjaratokszama()-1];
        for (int i = 0; i < talalt.getjaratokszama()-1; i++)
        {
        String* cel_megallok = talalt.getjaratok()[i+1].getmegallok();
        String* kezdo_megallok = talalt.getjaratok()[i].getmegallok();
            for (int j = 0; j < talalt.getjaratok()[i].getmegallokszama(); j++)
            {
                for (int k = 0; k < talalt.getjaratok()[i+1].getmegallokszama(); k++)
                {
                    if(kezdo_megallok[j] == cel_megallok[k])atszallas_megallok[i] = kezdo_megallok[j];
                }
                
            }
            
        }
        
       
            Jegyatszallas jegy_atszallas(jegy.getnev(), true, jegy.getkezdomegallo(), jegy.getcelmegallo(), jegy.getidopont(), atszallas_megallok ,talalt.getjaratokszama()-1);
            Jarat* jarathely = talalt.getjaratok();
            int kezdo;
            int cel;
            String celmegallo = jegy.getcelmegallo();
            //amiatt kell 2 darab atszallasindex jelző, mert az első járatban nem feltétlen ugyanazon a helyen van mint a második járatban 
            int atszallas1 = -1, atszallas2; // ide dob egy warningot azt tudom de csak amiatt mert nincs inicializálva, de jelen esetben ezt nem is kell.
            for (int i = 0; i < talalt.getjaratokszama(); i++)
            {
                String* megallok = jarathely[i].getmegallok();
                // Nem foglalkozok azzal ha valaki A-ból A ba megy akkor sétáljon és ne vegyen jegyet
                
                for (int j = 0; j < jarathely[i].getmegallokszama(); j++) 
                {
                  if (megallok[j] == celmegallo)
                  {
                    kezdo = j;
                  }else if (i < talalt.getjaratokszama()-1)
                  {
                    if (megallok[j] == atszallas_megallok[i])
                    {
                    cel = j;
                        
                    }
                    
                  }else if (megallok[j] == jegy.getkezdomegallo())
                  {
                    cel = j;
                  }
                  
                  
                  
                }
                if (kezdo < cel)
                {
                    for (int j = kezdo; j < cel; j++)
                    {
                        if(!(jarathely[i].jegyfoglal(j))){delete[] atszallas_megallok; return;}
                    }
                    
                }else{
                    for (int j = cel; j < kezdo; j++)
                    {
                        if(!(jarathely[i].jegyfoglal(j))){delete[] atszallas_megallok; return;}
                    }
                    
                }
                
                celmegallo = atszallas_megallok[i];
                
            }
                
            
                    jegy.sethelyszam(jarathely[0].gethely(cel));
                    menetrend.jegyhozzaad(jegy_atszallas);
                    std::cout << "Átszállási jegy sikeresen vásárolva." << std::endl;
                for (int i = 0; i < talalt.getjaratokszama(); i++)
                    {
                    frissitJarat(menetrend, jarathely[i]);
                    }        
         delete[] atszallas_megallok;
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

