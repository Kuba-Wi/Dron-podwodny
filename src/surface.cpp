#include "surface.hh"
#include <fstream>
#include "TVector.hh"

void surface::dodaj_plik_lok(const std::string& local_name) {
    local_file_name = local_name;
}

void surface::dodaj_plik_glob(const std::string& global_name) {
    plik_z_punktami = global_name;
}

void surface::wczytaj_lok() {
    std::ifstream read;
    std::ofstream write;
    TVector<double, 3> wiersz;

    read.open(local_file_name);
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
