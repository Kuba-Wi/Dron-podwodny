#include "obiekt.hh"
#include <fstream>
#include <cmath>


obiekt::obiekt() {
    for(int i = 0; i < 3; ++i)
        przesuniecie[i] = 0;
    
    laczny_kat_obrotu = 0;
}

void obiekt::inicjalizuj_obiekt() {
    wczytaj_wspolrzedne_lok();

    SWektor<double, 3> min_wsp = wspolrzedne[0];
    SWektor<double, 3> max_wsp = wspolrzedne[0];

    for(auto & wiersz : wspolrzedne) {

        for(int i = 0; i < 3; ++i) {

            if(wiersz[i] < min_wsp[i])
                min_wsp[i] = wiersz[i];
            else if(wiersz[i] > max_wsp[i])
                max_wsp[i] = wiersz[i];
        }
    }
    
    srodek_lok = (min_wsp + max_wsp) / 2;
    polowa_dl = (max_wsp - min_wsp) / 2;

    for(int i = 0; i < 3; ++i)
        polowa_dl[i] += 2;
}


void obiekt::wczytaj_wspolrz(const std::string & nazwa_pliku) {
    std::ifstream read;
    read.open(nazwa_pliku);
    if(!read.is_open())
        return;

    SWektor<double, 3> wiersz;
    wspolrzedne.clear();

    read >> wiersz;
    while(!read.eof()) {
        if(!read) {
            read.clear();
            while(read.get() != '\n');
        }
        else {
            wspolrzedne.push_back(wiersz);
        }
        read >> wiersz;
    }

    read.close();
}

void obiekt::wczytaj_wspolrzedne_lok() {
    wczytaj_wspolrz(nazwa_pliku_lok);
}
void obiekt::wczytaj_wspolrzedne_glob() {
    wczytaj_wspolrz(plik_z_punktami);
}

void obiekt::wpisz_wspolrzedne_glob() {
    std::ofstream write;
    write.open(plik_z_punktami);
    if(!write.is_open())
        return;
    
    int licznik = 0;

    for(SWektor<double, 3> & i: wspolrzedne) {
        write << i;
        ++licznik;
        if(licznik == 4) {
            licznik = 0;
            write << "#\n\n";
        }
    }
    
    write.close();
}

void obiekt::macierz_obrotu(SMacierz<double, 3> & obrot, double kat_obrotu) const {
    const double pi = acos(-1);

    for(int i = 0; i < 3; ++i) {
        obrot(2, i) = 0;
        obrot(i, 2) = 0;
    }
    obrot(2, 2) = 1;

    obrot(0, 0) = cos(pi*(kat_obrotu/180.0));
    obrot(1, 1) = obrot(0, 0);
    obrot(1, 0) = sin(pi*(kat_obrotu/180.0));
    obrot(0, 1) = -obrot(1, 0);
}

void obiekt::ruch_na_wprost(const SWektor<double, 3> & przesun) {
    for(SWektor<double, 3> &x : wspolrzedne)
        x = x + przesun;
}

void obiekt::obrot(const SMacierz<double, 3> & mac_obrotu) {
    for(SWektor<double, 3> &x : wspolrzedne)
        x = mac_obrotu * x;
}

SWektor<double, 3> obiekt::polozenie() const {
    return srodek_lok + przesuniecie;
}