#include <iostream>
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
    delete[] jegyek;
    jegyek = tmp;
    jegyek[jegyekszama++] = jegy;
    

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

    // Ellenőrizzük, hogy van-e közös megállója a kezdő és célállomásnak
    for (int i = 0; i < jaratokszama; ++i) {
        String* megallot = jaratok[i].getmegallok();
        for (int j = 0; j < jaratok[i].getmegallokszama(); ++j) {
            if (megallot[j] == kezdo) {
                talalt_kezdo = true;
            }
            if (megallot[j] == cel) {
                talalt_cel = true;
            }
        }
    }

    // Ha nincs közös megálló, akkor nincs járat az adott útvonalon
    if (!talalt_kezdo || !talalt_cel) {
        std::cout << "Nincs járat az adott útvonalon." << std::endl;
        return utvonal;
    }

    // Szélességi keresés tömbbel
    bool* visited = new bool[jaratokszama]{false}; // Látogatott állapotok tömbje
    int* queue = new int[jaratokszama]; // Sor a szélességi kereséshez
    int* parent = new int[jaratokszama]; // Szülők tömbje az útvonal visszavezetéséhez
    for (int i = 0; i < jaratokszama; ++i) {
        parent[i] = -1; // Kezdetben nincsenek szülők
    }

    int front = 0, rear = 0; // Sor elő- és hátsó mutatója
    for (int i = 0; i < jaratokszama; ++i) {
        String* megallot = jaratok[i].getmegallok();
        for (int j = 0; j < jaratok[i].getmegallokszama(); ++j) {
            if (megallot[j] == kezdo) {
                visited[i] = true;
                queue[rear++] = i;
                parent[i] = -1; // A kezdőpontnak nincs szülője
                break;
            }
        }
    }

    // Szélességi keresés
    bool talalt = false;
    while (front != rear) {
        int current = queue[front++];
        String* megallot = jaratok[current].getmegallok();
        for (int j = 0; j < jaratok[current].getmegallokszama(); ++j) {
            if (megallot[j] == cel) {
                talalt = true;
                break;
            }
        }
        if (talalt) break;

        for (int i = 0; i < jaratokszama; ++i) {
            if (!visited[i]) {
                String* masik_megallot = jaratok[i].getmegallok();
                for (int k = 0; k < jaratok[i].getmegallokszama(); ++k) {
                    for (int l = 0; l < jaratok[current].getmegallokszama(); ++l) {
                        if (masik_megallot[k] == megallot[l]) {
                            visited[i] = true;
                            queue[rear++] = i;
                            parent[i] = current;
                        }
                    }
                }
            }
        }
    }

    // Visszavezetés az útvonalra
    if (talalt) {
        int current = rear - 1; // Utolsó elem az útvonal végpontja
        while (current != -1) {
            utvonal.jarathozzaad(jaratok[current]);
            current = parent[current];
        }
    } else {
        std::cout << "Nincs járat az adott útvonalon." << std::endl;
    }

    delete[] visited;
    delete[] queue;
    delete[] parent;

    return utvonal;
    }


void Menetrend::menetrendKiir(){
    std::cout << "Menetrend" << std::endl;;
    for (int i = 0; i < jaratokszama; i++)
    {
       jaratok[i].jaratkiir();
    }
    

}


void Menetrend::menetrendbetolt(const char* filename){

}

