#include "vonatok.h"
#include "string5.h"
#include <iostream>

void displayMenu() {
    std::cout << "----- MENÜ -----" << std::endl;
    std::cout << "1. Jegyvásárlás" << std::endl;
    std::cout << "2. Jegykeresés" << std::endl;
    std::cout << "3. Kilépés" << std::endl;
    std::cout << "4. Mentés" << std::endl;
    std::cout << "5. Betöltés" << std::endl;
    std::cout << "6. Teszt" << std::endl;
    std::cout << "7. Modositas" << std::endl;
    std::cout << "----------------" << std::endl;
    std::cout << "Válasszon egy lehetőséget: ";
}

void jegyteszt(Menetrend& menetrend, Jegy jegy){
Menetrend talalt = menetrend.jegykeres(jegy.getkezdomegallo(), jegy.getcelmegallo());
    
    if (talalt.getjaratokszama() == 1) {
        menetrend.jegyhozzaad(jegy);
        std::cout << "Jegy sikeresen vásárolva." << std::endl;
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
            menetrend.jegyatszallashozzaad(jegy_atszallas);
            std::cout << "Átszállási jegy sikeresen vásárolva." << std::endl;
        } else {
            std::cout << "Nincs közös megálló a két járat között." << std::endl;
        }
    } else {
        std::cout << "Érvénytelen választás. Kérem válasszon újra." << std::endl;
    }
}

int main() {
    Menetrend menetrend;
   /*
    String helyek[] ={"A", "B", "C"};
    String helyek1[] ={"B", "C", "D"};
    String helyek2[] ={"D", "C", "E"};
    String helyek3[] ={"E", "F", "G"};
    int h[] ={3,3,3};
    int ido[] ={100,200,300};
    Jarat j(3,h, helyek,ido,3);
    Jarat j1(3,h,helyek1,ido,3);
    Jarat j2(3,h,helyek2,ido,3);
    Jarat j3(3,h,helyek3,ido,3);
    menetrend.jarathozzaad(j);
    menetrend.jarathozzaad(j1);
    menetrend.jarathozzaad(j2);
    menetrend.jarathozzaad(j3);
   */ 
    int choice;
    do {
        displayMenu();
        std::cin >> choice;

        switch (choice) {
            case 1: {
    char nev[100], kezdo[100], cel[100];
    int idopont;

    std::cout << "Adja meg a nevét: ";
    std::cin >> nev;
    std::cout << "Adja meg az utazás kezdőállomását: ";
    std::cin >> kezdo;
    std::cout << "Adja meg az utazás célállomását: ";
    std::cin >> cel;
    std::cout << "Adja meg az utazás időpontját: ";
    std::cin >> idopont;

    String nev_string(nev);
    String kezdo_string(kezdo);
    String cel_string(cel);

    Jegy jegy(nev_string, true, kezdo_string, cel_string, idopont);
    jegyteszt(menetrend, jegy);
    break;
}
            case 2: {
                char kezdo[100], cel[100];
                std::cout << "Adja meg az utazás kezdőállomását: ";
                std::cin >> kezdo;
                std::cout << "Adja meg az utazás célállomását: ";
                std::cin >> cel;

                String kezdo_string(kezdo);
                String cel_string(cel);

                Menetrend talalt_jarat = menetrend.jegykeres(kezdo_string, cel_string);
                if (talalt_jarat.getjaratokszama() != 0) {
                    std::cout << "Járat található az adott útvonalon." << std::endl;
                    talalt_jarat.menetrendKiir();
                } else {
                    std::cout << "Nincs járat az adott útvonalon." << std::endl;
                }
                break;
            }
            case 3: {
                std::cout << "Kilépés..." << std::endl;
                break; }      
            case 4: {

                std::cout << "Mentés..." << std::endl;
                menetrend.menetrend_kiir_fajlba("jaratok");
                break;
            }
            case 5: {

                std::cout << "Betöltés..." << std::endl;
                menetrend.menetrendbetolt("jaratok");
                break;
            }
            case 6: {

                std::cout << "Teszt..." << std::endl;
                menetrend.menetrendbetolt("jaratok");
                Jegy teszt1("teszt1", true, "A", "C", 100);
                Jegy teszt2("teszt2", false, "A", "D", 200);
                Jegy teszt3("teszt3", true,"B", "F",100 );
                jegyteszt(menetrend, teszt1);
                jegyteszt(menetrend, teszt2);
                jegyteszt(menetrend, teszt3);
                menetrend.menetrendKiir();
                Jegy* jegyek = menetrend.getjeyek();
                Jegyatszallas* jegyekat = menetrend.getjegyekatszallassal();
                for (int i = 0; i < menetrend.getjegyekszama(); i++)
                {
                    jegyek[i].Nyomtat();
                }
                for (int i = 0; i < menetrend.getjegyekatszallassaldb(); i++)
                {
                    jegyekat[i].atszallasNyomtat();

                }
                
                
                
                break;
            }
                default:
                std::cout << "Érvénytelen választás. Kérem válasszon újra." << std::endl;
                break;
        }
    } while (choice != 3);

    return 0;
}
