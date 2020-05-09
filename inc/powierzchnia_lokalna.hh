#ifndef POWIERZCHNIA_LOK_HH
#define POWIERZCHNIA_LOK_HH

#include <string>

class powierzchnia_lokalna {
    protected:
        /*! nazwa pliku ze współrzędnymi lokalnymi powierzchni */
        std::string nazwa_pliku;
    public:
        powierzchnia_lokalna() {}
        powierzchnia_lokalna(const std::string & nazwa) : nazwa_pliku(nazwa) {}

        /*! Zmienia lub dodaje nazwę pliku */
        void dodaj_plik_lok(const std::string & nazwa);
};

#endif