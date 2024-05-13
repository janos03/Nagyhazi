#include "vonatok.h"
#include "string5.h"
#include <iostream>

//-------------------------------------------------------------------------------------
//  main.cpp, ebben van a menü és benne a teszt is.
//  Van egy bekommentezett szekció, azért kell ha nincs fájl amibeől beolvassunk ne kelljen egyesével fevenni a járatokat.
//  A Teszt csak annyit csinál hogy betölti fájlból a menetrendet, létrehoz egy átszállásos, egy sima és egy nem tallató esetet kivizsgálja, útvonalat keres majd hozzáadja a menetrendez illetve kiírja fájlba a jegyet.
//--------------------------------------------------------------------------------------
//  A memóriaszivárgást lehet nézni memtrace.h-val, de nem ezt használtam, hanem valgrindot így nincs includeolva sehol.



void displayMenu() {
    std::cout << "----- MENÜ -----" << std::endl;
    std::cout << "1. Jegyvásárlás" << std::endl;
    std::cout << "2. Jegykeresés" << std::endl;
    std::cout << "3. Kilépés" << std::endl;
    std::cout << "4. Mentés" << std::endl;
    std::cout << "5. Betöltés" << std::endl;
    std::cout << "6. Teszt" << std::endl;
    std::cout << "7. Járat hozzáadása" << std::endl;
    std::cout << "8. Menetrend kilistázása" << std::endl;
    std::cout << "----------------" << std::endl;
    std::cout << "Válasszon egy lehetőséget: ";
}

void clear(){
    std::cin.clear(); // Állapot visszaállítása
    std::cin.ignore(10000, '\n'); // Tisztítás
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
         if (!(std::cin >> choice)) {
            std::cout << "Érvénytelen választás. Kérem válasszon újra." << std::endl;
            clear(); // Puffer ürítése
            continue;
        }

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
    if (idopont < 0)
    {
        std::cout << "Az időpont nem lehet negatív szám";
        break;
    }
    
    String nev_string(nev);
    String kezdo_string(kezdo);
    String cel_string(cel);

    Jegy jegy(nev_string, true, kezdo_string, cel_string, idopont);
    jegyteszt(menetrend, jegy);
    break;
}
            case 2: {
                char kezdo[100], cel[100]; //Nem hinném, hogy ennél hosszabb nevű állomás létezne
                std::cout << "Adja meg az utazás kezdőállomását: ";
                std::cin >> kezdo;
                std::cout << "Adja meg az utazás célállomását: ";
                std::cin >> cel;

                String kezdo_string(kezdo);
                String cel_string(cel);

                Menetrend talalt_jarat   = menetrend.jegykeres(kezdo_string, cel_string);
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
                Jegy teszt4("teszt4", false, "F", "G", 200);
                jegyteszt(menetrend, teszt1);
                jegyteszt(menetrend, teszt2);
                jegyteszt(menetrend, teszt3);
                jegyteszt(menetrend, teszt4);
                menetrend.menetrendKiir();
                Jegy* jegyek = menetrend.getjegyek();
                Jegyatszallas* jegyekat = menetrend.getjegyekatszallassal();
                for (int i = 0; i < menetrend.getjegyekszama(); i++)
                {
                    jegyek[i].Nyomtat();
                    jegyek[i].jegykiirfajlba("tesztjegy");
                }
                for (int i = 0; i < menetrend.getjegyekatszallassaldb(); i++)
                {
                    jegyekat[i].Nyomtat();
                    jegyekat[i].jegykiirfajlba("tesztjegy");

                }
                
                
                
                break;
            }
            case 7: {
                    int maxh;
                std::cout << "Adja meg a járat maximális férőhelyét: ";
                std::cin >> maxh;

                int megallok_szama;
                std::cout << "Adja meg a megallok számát: ";
                std::cin >> megallok_szama;

                // Dinamikus tömbök létrehozása a megallok és idopontok tárolásához
                String* megallok = new String[megallok_szama];
                int* idopontok = new int[megallok_szama];
                int* helyek = new int[megallok_szama];
                // Adatok bekérése a felhasználótól
                for (int i = 0; i < megallok_szama; ++i) {
                    char megallo[100];
                    int idopont;

                    std::cout << "Adja meg az " << i + 1 << ". állomást: ";
                    std::cin >> megallo;
                    std::cout << "Adja meg az " << i + 1 << ". állomás indulási időpontját: ";
                    std::cin >> idopont;
                    helyek[i] = 0;
                    megallok[i] = String(megallo);
                    idopontok[i] = idopont;
                }

                // Létrehozzuk a Jarat objektumot az adatokból
                Jarat uj_jarat(maxh, helyek, megallok, idopontok, megallok_szama);
    
                // Hozzáadjuk az új járatot a menetrendhez
                menetrend.jarathozzaad(uj_jarat);

                // Felszabadítjuk a dinamikusan foglalt memóriát
                delete[] megallok;
                delete[] idopontok;
                delete[] helyek;
                std::cout << "Járat sikeresen hozzáadva." << std::endl;
            break;

            }
            case 8: {
                std::cout << "-----------------------------" << std::endl;
                menetrend.menetrendKiir();

                break;
            }
            
                default:
                std::cout << "Érvénytelen választás. Kérem válasszon újra." << std::endl;
                break;
        }
    } while (choice != 3);

    return 0;
}
