#include "powierzchnia.hh"
#include <fstream>
#include "SWektor.hh"

void powierzchnia::dodaj_plik_lok(const std::string& nazwa_lok) {
    nazwa_pliku_lok = nazwa_lok;
}

void powierzchnia::dodaj_plik_glob(const std::string& nazwa_glob) {
    plik_z_punktami = nazwa_glob;
}

void powierzchnia::wczytaj_lok() {
    std::ifstream read;
    std::ofstream write;
    SWektor<double, 3> wiersz;

    read.open(nazwa_pliku_lok);
    write.open(plik_z_punktami);

    if (!(read.is_open() && write.is_open()))
        return;

    read >> wiersz;
    while (!read.eof()) {
        if (!read) {
            read.clear();
            while (read.get() != '\n')
                ;
            write << "#\n\n";
        } else
            write << wiersz;

        read >> wiersz;
    }

    z_powierzchni = wiersz[2];

    read.close();
    write.close();
}
