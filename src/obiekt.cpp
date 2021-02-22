#include "obiekt.hh"
#include <cmath>
#include <fstream>

obiekt::obiekt() {
    for (int i = 0; i < 3; ++i)
        translation[i] = 0;

    all_angle = 0;
}

void obiekt::inicjalizuj_obiekt() {
    wczytaj_lok();
    wczytaj_wspolrzedne_lok();

    TVector<double, 3> min_wsp = wspolrzedne[0];
    TVector<double, 3> max_wsp = wspolrzedne[0];

    for (auto& wiersz : wspolrzedne) {
        for (int i = 0; i < 3; ++i) {
            if (wiersz[i] < min_wsp[i])
                min_wsp[i] = wiersz[i];
            else if (wiersz[i] > max_wsp[i])
                max_wsp[i] = wiersz[i];
        }
    }

    srodek_lok = (min_wsp + max_wsp) / 2;
    polowa_dl = (max_wsp - min_wsp) / 2;

    for (int i = 0; i < 3; ++i) {
        polowa_dl[i] += 0.25;
    }
}

void obiekt::wczytaj_wspolrz(const std::string& nazwa_pliku) {
    std::ifstream read;
    read.open(nazwa_pliku);
    if (!read.is_open())
        return;

    TVector<double, 3> wiersz;
    wspolrzedne.clear();

    read >> wiersz;
    while (!read.eof()) {
        if (!read) {
            read.clear();
            while (read.get() != '\n')
                ;
        } else {
            wspolrzedne.push_back(wiersz);
        }
        read >> wiersz;
    }

    read.close();
}

void obiekt::wczytaj_wspolrzedne_lok() {
    wczytaj_wspolrz(local_file_name);
}

void obiekt::wpisz_wspolrzedne_glob() {
    std::ofstream write;
    write.open(plik_z_punktami);
    if (!write.is_open())
        return;

    int licznik = 0;

    for (TVector<double, 3>& i : wspolrzedne) {
        write << i;
        ++licznik;
        if (licznik == 4) {
            licznik = 0;
            write << "#\n\n";
        }
    }

    write.close();
}

void obiekt::move_ahead(const TVector<double, 3>& przesun) {
    for (TVector<double, 3>& x : wspolrzedne)
        x = x + przesun;
}

void obiekt::rotation(const TMatrix<double, 3>& mac_rotationu) {
    for (TVector<double, 3>& x : wspolrzedne)
        x = mac_rotationu * x;
}

TVector<double, 3> obiekt::polozenie() const {
    return srodek_lok + translation;
}
