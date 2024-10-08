#ifndef VONATOK_H
#define VONATOK_H
#include "string5.h"

// Jarat osztály
    class Jarat {
        int jaratszam;
        int maxhely;
        int* hely;
        String* megallok;
        int* idopont;
        int megallokszama;
        public:

        Jarat():jaratszam(0), maxhely(0), hely(nullptr), megallok(nullptr), idopont(nullptr), megallokszama(0){};
        Jarat(int jaratszam ,int maxh, int* helyek, String* megallok, int* idopont, int szam);
        Jarat(const Jarat& jarat);

        String* getmegallok(){return megallok;}
        int getmegallokszama(){return megallokszama;}
        int getmaxhely(){return maxhely;}
        int getidopont(int index){return idopont[index];}
        int gethely(int i){return hely[i];}
        int getjaratszam(){return jaratszam;}
        void jaratkiir();
        void sethely(int n){maxhely = n;}
        void jaratkiir(std::ofstream& file);
        Jarat& operator=(const Jarat& jarat);
        bool jegyfoglal(int hely_index);
        ~Jarat(){
            delete[] idopont;
            delete[] megallok;
            delete[] hely;
        }

    };

// Jegy osztály
    class Jegy{
        String nev;
        bool kedvezmenyes;
        String kezdomegallo;
        String celmegallo;
        int idopont;
        int helyszam;
        public:
        Jegy() : nev(""), kedvezmenyes(false), kezdomegallo(""), celmegallo(""), idopont(0), helyszam(-1) {};
        Jegy(const Jegy& jegy);
        Jegy(String n, bool kedv , String kezdo, String cel, int ido){
            nev = n;
            kedvezmenyes = kedv;
            kezdomegallo = kezdo;
            celmegallo = cel;
            idopont = ido;
            helyszam = -1;
        }
        String getnev()const {return nev;}
        int gethelyszan() const {return helyszam;}
        bool getkedvezmenyes() const {return kedvezmenyes;}
        String getkezdomegallo()const{ return kezdomegallo;}
        String getcelmegallo()const{return celmegallo;}
        int getidopont()const{return idopont;}
        void setcel(String cel){celmegallo = cel;}
        void setido(int ido){idopont = ido;}
        void sethelyszam(int hely){helyszam = hely;}
        virtual void Nyomtat()const;
        virtual void Nyomtat(const char* filename)const;
        Jegy& operator=(const Jegy& jegy){
            nev = jegy.nev;
            kedvezmenyes = jegy.kedvezmenyes;
            kezdomegallo = jegy.kezdomegallo;
            celmegallo = jegy.celmegallo;
            idopont = jegy.idopont;
            helyszam = jegy.helyszam;

            return *this;
        }
      
    };

// Jegyatszallas osztály
    class Jegyatszallas: public Jegy{
    String* atszallas;
    int atszallasdarab;
    public:
    Jegyatszallas() : Jegy(), atszallas(nullptr) {}
    Jegyatszallas(String n, bool kedv, String kezdo, String cel, int ido, String* atsz, int atszdb);
    Jegyatszallas(const Jegyatszallas& jegy); 
        

    void Nyomtat() const override {
        Jegy::Nyomtat(); 
        std::cout << "Átszállás: " ;
        for (int i = 0; i < atszallasdarab; i++)
        {
        std::cout << atszallas[i] << " ";
            
        }
        std::cout << std::endl;
    }
    Jegyatszallas& operator=(const Jegyatszallas& jegy);
    void Nyomtat(const char* filename) const;
    ~Jegyatszallas(){
        delete[] atszallas;
    }


};

// Menetrend osztály
    class Menetrend{
        Jarat* jaratok; 
        Jegy* jegyek;
        Jegyatszallas* jegyekatszallas;
        int jaratokszama;
        int jegyekszama;
        int jegyekatszallassaldb;
        
        public:
        Menetrend(): jaratok(nullptr), jegyek(nullptr), jegyekatszallas(nullptr),jaratokszama(0), jegyekszama(0), jegyekatszallassaldb(0){};
        void jegyhozzaad(const Jegy& jegy);
        void jegyhozzaad(const Jegyatszallas& jegy);
        void jarathozzaad(const Jarat& jarat);
        Jegyatszallas* getjegyekatszallassal() const {return jegyekatszallas;}
        Jegy* getjegyek() const{ return jegyek;}
        Jarat* getjaratok() const { return jaratok; }
        int getjaratokszama()const{return jaratokszama;};
        int getjegyekszama()const {return jegyekszama;}
        int getjegyekatszallassaldb()const {return jegyekatszallassaldb;}
        void menetrendKiir() const;
        void menetrendKiir(const char* filename) const;
        void menetrendbetolt(const char* filename);
        Menetrend jegykeres(String kezdo, String cel);

        ~Menetrend(){delete[] jaratok; delete[] jegyek; delete[] jegyekatszallas;}

    };
    void jegyteszt(Menetrend& menetrend, Jegy& jegy);
    void frissitJarat(Menetrend& menetrend, Jarat& ujJarat);
#endif


