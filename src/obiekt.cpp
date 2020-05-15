#include "obiekt.hh"
#include <fstream>
#include <cmath>

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

    wczytaj_wspolrzedne(nazwa_lok);
    polowa_wysokosci = fabs(wspolrzedne[0][2] - wspolrzedne[1][2]);
}

void obiekt::wczytaj_wspolrzedne(const std::string & nazwa_pliku) {
    std::ifstream read;
    read.open(nazwa_pliku);
    if(!read.is_open())
        return;

    SWektor<double, 3> wiersz;
    wspolrzedne.erase(wspolrzedne.begin(), wspolrzedne.end());

    read >> wiersz;
    while(!read.eof()) {
        if(!read) {
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

void obiekt::ruch_na_wprost(double kat_wznoszenia, double odleglosc) {
    wczytaj_wspolrzedne(plik_z_punktami);

    const double pi = acos(-1);

    SWektor<double, 3> translacja;

    translacja[0] = cos(pi*(laczny_kat_obrotu/180.0)) * cos(pi*(kat_wznoszenia/180.0));
    translacja[1] = sin(pi*(laczny_kat_obrotu/180.0)) * cos(pi*(kat_wznoszenia/180.0));
    translacja[2] = sin(pi*(kat_wznoszenia/180.0));

    translacja = translacja * odleglosc;

    for(SWektor<double, 3> &x : wspolrzedne)
        x = x + translacja;

    przesuniecie = przesuniecie + translacja;    
    wpisz_wspolrzedne_glob();
}

void obiekt::obrot(double kat_obrotu) {
    wczytaj_wspolrzedne(plik_lokalny);

    SMacierz<double, 3> obrot;

    laczny_kat_obrotu += kat_obrotu;
    while(laczny_kat_obrotu >= 360.0)
        laczny_kat_obrotu -= 360.0;
    while(laczny_kat_obrotu <= -360.0)
        laczny_kat_obrotu += 360.0;

    macierz_obrotu(obrot, laczny_kat_obrotu);

    for(SWektor<double, 3> &x : wspolrzedne)
        x = obrot * x + przesuniecie;

    
    wpisz_wspolrzedne_glob();
}

double obiekt::dolna_sciana() const {
    return przesuniecie[2] - polowa_wysokosci;
}