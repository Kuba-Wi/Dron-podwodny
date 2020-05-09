#include "powierzchnia_lokalna.hh"

void powierzchnia_lokalna::dodaj_plik_lok(const std::string & nazwa) {
    if(!nazwa_pliku.size())
        nazwa_pliku = nazwa;
}