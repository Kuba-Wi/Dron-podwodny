#include "obiekt.hh"
#include <fstream>
#include "SWektor.hh"

obiekt::obiekt() {
    for(int i = 0; i < 3; ++i)
        przesuniecie[i] = 0;
    
    laczny_kat_obrotu = 0;
}

obiekt::obiekt(const std::string & nazwa_lok, const std::string & nazwa_glob) : 
                powierzchnia(nazwa_lok, nazwa_glob) {
    for(int i = 0; i < 3; ++i)
        przesuniecie[i] = 0;
    
    laczny_kat_obrotu = 0;
}

void obiekt::wczytaj_wspolrzedne() {
    std::ifstream read;
    read.open(plik_lokalny);
    if(!read.is_open())
        return;

    SWektor<double, 3> wiersz;
    wspolrzedne.clear();

    read >> wiersz;
    while(!read.eof()) {
        if(read.bad()) {
            read.clear();
            while(read.get() != '\n');
        }
        else
            wspolrzedne.push_back(wiersz);
        
        read >> wiersz;
    }

    read.close();
}

void obiekt::wpisz_wspolrzedne_glob() {
    std::ofstream write;
    write.open(plik_z_punktami);
    if(!write.is_open())
        return;

    for(SWektor<double, 3> & i: wspolrzedne)
        write << i;
    
    write.close();
}