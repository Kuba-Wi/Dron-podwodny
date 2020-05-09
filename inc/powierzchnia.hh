#ifndef POWIERZCHNIA_HH
#define POWIERZCHNIA_HH

#include <string>

#include "powierzchnia_lokalna.hh"


class powierzchnia : public powierzchnia_lokalna {
    protected:
        /*! plik z którego będzie rysowana powierzchnia */
        std::string plik_z_punktami;
    public:
        powierzchnia() {}
        powierzchnia(const std::string & nazwa_lok, const std::string & nazwa_glob) : 
                    powierzchnia_lokalna(nazwa_lok), plik_z_punktami(nazwa_glob) {}
        /*! Wczytuje współrzędne lokalne do pliku z punktami */
        void wczytaj_lok();
};

#endif