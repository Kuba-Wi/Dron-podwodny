#include "powierzchnia.hh"
#include "SWektor.hh"
#include <fstream>


powierzchnia::powierzchnia(const std::string & nazwa_lok, const std::string & nazwa_glob) {
    plik_lokalny = nazwa_lok;
    plik_z_punktami = nazwa_glob;
}

void powierzchnia::wczytaj_lok() {
    std::ifstream read;
    std::ofstream write;
    SWektor<double, 3> wiersz;

    read.open(plik_lokalny);
    write.open(plik_z_punktami);

    if(!(read.is_open() && write.is_open()))
        return;
    
    read >> wiersz;
    while(!read.eof()) {
        if(read.bad()) {
            read.clear();
            while(read.get() != '\n');
        }
        else
            write << wiersz;
        
        read >> wiersz;
    }

    read.close();
    write.close();
}