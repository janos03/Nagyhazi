#ifndef VONATOK_H
#define VONATOK_H
#include "string5.h"

    class Jarat {
        int maxhely;
        int* hely;
        String* megallok;
        int* idopont;
        int megallokszama;
        public:
        Jarat(): maxhely(0), hely(nullptr), megallok(nullptr), idopont(nullptr), megallokszama(0){};
        Jarat(int maxh, int* helyek, String* megallok, int* idopont, int szam);
        String* getmegallok(){return megallok;}
        int getmegallokszama(){return megallokszama;}
        int getmaxhely(){return maxhely;}
        void jaratkiir();
        void sethely(int n){maxhely = n;}
        Jarat& operator=(const Jarat& jarat);
        void jaratkiir_fajlba(std::ofstream& file);
        ~Jarat(){
            delete[] idopont;
            delete[] megallok;
            delete[] hely;
        }

    };

    class Jegy{
        String nev;
        bool kedvezmenyes;
        String kezdomegallo;
        String celmegallo;
        int idopont;
        public:
        Jegy() : nev(""), kedvezmenyes(false), kezdomegallo(""), celmegallo(""), idopont(0) {};
        Jegy(String n, bool kedv , String kezdo, String cel, int ido){
            nev = n;
            kedvezmenyes = kedv;
            kezdomegallo = kezdo;
            celmegallo = cel;
            idopont = ido;
        }
        String getnev(){return nev;}
        bool getkedvezmenyes(){return kedvezmenyes;}
        String getkezdomegallo(){ return kezdomegallo;}
        String getcelmegallo(){return celmegallo;}
        int getidopont(){return idopont;}
        void setnev(String n){nev =n;}
        void setkedv(bool kedv){kedvezmenyes = kedv;}
        void setkezdo(String kezdo){kezdomegallo = kezdo;}
        void setcel(String cel){celmegallo = cel;}
        void setido(int ido){idopont = ido;}
        void Nyomtat();

        Jegy& operator=(const Jegy& jegy){
            nev = jegy.nev;
            kedvezmenyes = jegy.kedvezmenyes;
            kezdomegallo = jegy.kezdomegallo;
            celmegallo = jegy.celmegallo;
            idopont = jegy.idopont;

            return *this;
        }
      
    };

    class Menetrend{
        Jarat* jaratok; 
        Jegy* jegyek;
        int jaratokszama;
        int jegyekszama;
        
        
        public:
        Menetrend(): jaratok(nullptr), jegyek(nullptr), jaratokszama(0), jegyekszama(0){};
        void jegyhozzaad(const Jegy& jegy);
        void jarathozzaad(const Jarat& jarat);
        Menetrend jegykeres(String kezdo, String cel);
        void menetrendKiir();
        int getjaratokszama(){return jaratokszama;};
        void menetrendbetolt(const char* filename);
        ~Menetrend(){delete[] jaratok; delete[] jegyek;}

    };

#endif