/**
 *
 * \file string5.cpp
 *
 * Itt kell megvalósítania a hiányzó tagfüggvényeket.
 * Segítségül megadtuk a C++ nem OO eszközeinek felhasználásával készített String-kezelő
 * függvényke neveit.
 *
 * Ha valamit INLINE-ként valósít meg, akkor annak a string5.h-ba kell kerülnie,
 * akár kívül akár osztályon belül definiálja. (Az inline függvényeknek minden
 * fordítási egységben elérhetőknek kell lenniük)
 * *
 * A teszteléskor ne felejtse el beállítani a string5.h állományban az ELKESZULT makrót.
 * 
 */

#ifdef _MSC_VER
// MSC ne adjon figyelmeztető üzenetet a C sztringkezelő függvényeire
  #define _CRT_SECURE_NO_WARNINGS
#endif

#include <iostream>             // Kiíratáshoz
#include <cstring>              // Sztringműveletekhez

#include "memtrace.h"           // a standard headerek után kell lennie
#include "string5.h"


/// Konstruktorok: egy char karakterből (createString)
///                egy nullával lezárt char sorozatból (createString)

/// Másoló konstruktor: String-ből készít (createString)

/// Destruktor (disposeString)

/// operator=
String& String::operator=(const String& str) {
    if(&str != this) {
        len = str.size();
        delete[] pData;
        pData = new char[len + 1];
        const char *c_str = str.c_str();
        for(size_t i = 0; i <= len; ++i)
            pData[i] = c_str[i];
    }
    return *this;
}

/// [] operátorok: egy megadott indexű elem REFERENCIÁJÁVAL térnek vissza (charAtString)
/// indexhiba esetén const char * kivételt dob!
char& String::operator[](size_t idx) const{
  if (idx >= len)
  {
    throw "L8CN1A";
  }
  return pData[idx];
  
}

/// + operátorok:
///                 String-hez jobbról karaktert ad (addString)
String String::operator+(const char c) const{
    size_t old_len = size();
    size_t len = old_len + 1;
    char *str = new char[len + 1];
    for(size_t i = 0; i < old_len; ++i)
        str[i] = c_str()[i];
    str[old_len] = c;
    str[old_len + 1] = '\0';

    String res(str);
    delete[] str;
    return res;
}
///                 String-hez String-et ad (addString)

String String::operator+(const String& s) const {
    size_t regi_len = size();
    size_t add_len = s.size();
    size_t len = regi_len + add_len;
    char *str = new char[len + 1];
    for(size_t i = 0; i < regi_len; ++i)
        str[i] = c_str()[i];
    for(size_t i = 0; i < add_len; ++i)
        str[regi_len + i] = s.c_str()[i];
    str[len] = '\0';

    String res(str);
    delete[] str;
    return res;
}

/// << operator, ami kiír az ostream-re
std::ostream& operator<<(std::ostream& os, const String& str) {
    os << str.c_str();
    return os;
}

/// >> operátor, ami beolvas az istream-ről egy szót


String operator+(const char& c, const String& str) {
    String a(c);
    return a + str;
}

bool String::operator==(const String& s){
    if (strlen != s.strlen)
    {
        return false
    }
    for (size_t i = 0; i < strlen; i++)
    {
        if (s[i] != this[i])
        {
            return false;
        }
        
    }
    return true;
    
    
}