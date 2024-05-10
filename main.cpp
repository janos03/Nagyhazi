#include "vonatok.h"
#include "string5.h"
#include <iostream>

int main() {
    // Jaratok létrehozása
    int helyek1[] = {1, 2, 3};
    int idopontok1[] = {100, 200, 300};
    String megallok1[] = {"A", "B", "C"};
    Jarat jarat1(3, helyek1, megallok1, idopontok1, 3);
    std::cout << jarat1.getmegallokszama() << " " << jarat1.getmaxhely() << std::endl;

    int helyek2[] = {4, 5, 6};
    int idopontok2[] = {400, 500, 600};
    String megallok2[] = {"X", "Y", "Z"};
    Jarat jarat2(3, helyek2, megallok2, idopontok2, 3);
    std::cout << jarat2.getmegallokszama() << " " << jarat2.getmaxhely() << std::endl;

    int helyek3[] = {1,2,3};
    int idopontok[] = {100,200,300};
    String megallok3[] = {"Y", "Z", "C"};
    Jarat jarat3(3, helyek3, megallok3, idopontok, 3);

    //Jegyek létrehozása
    Jegy jegy1("Kovács Józsi", true, "A", "C", 100);
    std::cout << jegy1.getkezdomegallo() << std::endl;
    Jegy jegy2("Aranka", false, "X", "Z", 500);
    std::cout << jegy2.getnev() << std::endl;

    // Menetrend létrehozása és elemek hozzáadása
    Menetrend menetrend;
    menetrend.jarathozzaad(jarat1);
    menetrend.jarathozzaad(jarat2);
    menetrend.jarathozzaad(jarat3);
    menetrend.jegyhozzaad(jegy1);
    menetrend.jegyhozzaad(jegy2);

    // Jegy keresése
   
    String kezdo = "X";
    String cel = "C";
    Menetrend talalt_jarat = menetrend.jegykeres(kezdo, cel);
    if (talalt_jarat.getjaratokszama() != 0) {
        std::cout << "Járat található az adott útvonalon." << std::endl;
        talalt_jarat.menetrendKiir();
    } else {
        std::cout << "Nincs járat az adott útvonalon." << std::endl;

    }
    
      String kezdo2 = "A";
    String cel2 = "C";
    Menetrend talalt_jarat2 = menetrend.jegykeres(kezdo2, cel2);
    if (talalt_jarat2.getjaratokszama() != 0) {
        std::cout << "Járat található az adott útvonalon." << std::endl;
        talalt_jarat2.menetrendKiir();
    } else {
        std::cout << "Nincs járat az adott útvonalon." << std::endl;

    }
      String kezdo3 = "A";
    String cel3 = "D";
    Menetrend talalt_jarat3 = menetrend.jegykeres(kezdo3, cel3);
    if (talalt_jarat3.getjaratokszama() != 0) {
        std::cout << "Járat található az adott útvonalon." << std::endl;
        talalt_jarat3.menetrendKiir();
    } else {
        std::cout << "Nincs járat az adott útvonalon." << std::endl;

    }
   

    return 0;
}