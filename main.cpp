#include "vonatok.h"
#include "string5.h"

int main() {
    // Jaratok létrehozása
    int helyek1[] = {1, 2, 3};
    int idopontok1[] = {100, 200, 300};
    String megallok1[] = {"A", "B", "C"};
    Jarat jarat1(3, helyek1, megallok1, idopontok1, 3);

    int helyek2[] = {4, 5, 6};
    int idopontok2[] = {400, 500, 600};
    String megallok2[] = {"X", "Y", "Z"};
    Jarat jarat2(3, helyek2, megallok2, idopontok2, 3);

    // Jegyek létrehozása
    Jegy jegy1("Kovács Józsi", true, "A", "C", 100);
    Jegy jegy2("Aranka", false, "X", "Z", 500);

    // Menetrend létrehozása és elemek hozzáadása
    Menetrend menetrend;
    menetrend.jarathozzaad(jarat1);
    menetrend.jarathozzaad(jarat2);
    menetrend.jegyhozzaad(jegy1);
    menetrend.jegyhozzaad(jegy2);

    // Jegy keresése
    String kezdo = "A";
    String cel = "C";
    Jarat* talalt_jarat = menetrend.jegykeres(kezdo, cel);
    if (talalt_jarat != nullptr) {
        std::cout << "Járat található az adott útvonalon." << std::endl;
    } else {
        std::cout << "Nincs járat az adott útvonalon." << std::endl;
    }

    return 0;
}