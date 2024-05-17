#ifndef STRING12_H
#define STRING12_H


#include <iostream>



/**
 * A String osztály.
 * A 'pData'-ban vannak a karakterek (a lezáró nullával együtt), 'len' a hossza.
 * A hosszba nem számít bele a lezáró nulla.
 *
 * Korábban a len adattag unsigned int típusú volt. Most helyette a size_t típust használjuk.
 * Ezzel a típussal tér vissza a sizeof operator is, később több helyen ezt használjuk
 * mérettípusként.

 */
class String {
    char *pData;        ///< pointer az adatra
    size_t len;         ///< hossz lezáró nulla nélkül
public:
/// Kiírunk egy Stringet (debug célokra)
/// Ezt a tagfüggvényt elkészítettük, hogy használja a hibák felderítéséhez.
/// Igény szerint módosítható
/// @param txt - nullával lezárt szövegre mutató pointer.
///              Ezt a szöveget írjuk ki a debug információ előtt.
    void printDbg(const char *txt = "") const {
        std::cout << txt << "[" << len << "], "
                  << (pData ? pData : "(NULL)") << '|' << std::endl;
    }

/// Az első két feladatot előre megoldottuk, de lehet, hogy nem jól.
/// Az üres sztring reprezentációja nem szerencsés, mert így NULL pointerré
/// konvertál a c_str(), ami külön kezelést igényel a későbbiekben.
/// Ezt a teszt program sem fogadja el.
/// Gondolja végig, és változtassa meg!
/// Két lehetőség van:
///     a) nem NULL pointert tárol, hanem ténylegesen üres sztringet.
///     b) NULL-t tárol, de a c_str() üres sztringet ad vissza helyette
///        Ebben az esetben ügyelnie kell a másolásokra (másoló kostruktor op=) is,
///        nehogy NULL pointert kapjon az strcpy!
/// Bármelyik megoldás jó, mert ez az osztály belügye.


    /// Paraméter nélküli konstruktor:
    String() : len(0) {
        pData = new char[1];
        pData[0] = '\0';
    }

    /// Sztring hosszát adja vissza.
    /// @return sztring tényleges hossza (lezáró nulla nélkül).
    size_t size() const { return len; }

    /// C-sztringet ad vissza
    /// @return pointer a tárolt, vagy azzal azonos tartalmú nullával lezárt sztring-re.
    const char* c_str() const { return pData;}

/// Itt folytassa a tagfüggvények deklarációit a feladatoknak megfelelően.
/// ...

    String(const char c){
        len = 1;
        pData = new char[2];
        pData[0] = c;
        pData[1] = '\0';
    }

    String(const char* c){
        int charlen = 0;
        while(c[charlen] != '\0'){
            charlen++;
        }
        
        pData = new char[charlen+1];
        len = charlen;
        charlen = 0;
        while (c[charlen] != '\0')
        {
            pData[charlen] = c[charlen];
            charlen++;
        }
        pData[charlen] = '\0';
        
        
        
        
    }

    String(const String& s){
        this->len = s.len;
        this->pData = new char[len+1];
        for (size_t i = 0; i <= len; i++)
        {
            this->pData[i] = s.pData[i];
        }
        
    }

    ~String() {
        delete[] pData;
    }

    String& operator=(const String& str);

    String operator+(const String& s) const;
    String operator+(const char c) const;
    bool operator==(const String& s) const;
    char& operator[](size_t idx) const;

    
}; /// Itt az osztály deklarációjának vége

/// Ide kerülnek a globális operátorok deklarációi.
/// ...


std::ostream& operator<<(std::ostream& os, const String& str);

std::istream& operator>>(std::istream& is, const String& str);

String operator+(const char& c, const String& str);

#endif
