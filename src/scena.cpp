#include "scena.hh"
#include <iostream>

void scena::dodaj_dno(const std::string & nazwa_lok, const std::string & nazwa_glob) {
    dno = powierzchnia(nazwa_lok, nazwa_glob);
    
    dno.wczytaj_lok();

    char pom[100] = {0};
    nazwa_glob.copy(pom, 100);
    Lacze.DodajNazwePliku(pom);
}

void scena::dodaj_wode(const std::string & nazwa_lok, const std::string & nazwa_glob) {
    woda = powierzchnia(nazwa_lok, nazwa_glob);

    woda.wczytaj_lok();

    char pom[100] = {0};
    nazwa_glob.copy(pom, 100);
    Lacze.DodajNazwePliku(pom);
}

void scena::dodaj_drona(const std::string & nazwa_lok, const std::string & nazwa_glob) {
    dron = obiekt(nazwa_lok, nazwa_glob);

    dron.wczytaj_lok();

    char pom[100] = {0};
    nazwa_glob.copy(pom, 100);
    Lacze.DodajNazwePliku(pom);
}

void scena::inicjalizuj() {
    Lacze.ZmienTrybRys(PzG::TR_3D);
    Lacze.Inicjalizuj();
    rysuj();
}

void scena::ruch_prosto(double kat_wznoszenia, double odleglosc) {
    int kwant = 400;
    for(int i = 0; i < kwant; ++i) {
        dron.ruch_na_wprost(kat_wznoszenia, odleglosc/double(kwant));
        rysuj();
    }
}

void scena::obrot(double kat_obrotu) {
    int kwant = 360;
    for(int i = 0; i < kwant; ++i) {
        dron.obrot(kat_obrotu/double(kwant));
        rysuj();
    }
}
