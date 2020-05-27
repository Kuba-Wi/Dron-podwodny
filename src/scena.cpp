#include "scena.hh"
#include <iostream>
#include <cmath>


// bool scena::kolizja(double kat_wznoszenia, double odleglosc) const {
//     double przesun_dol = sin(acos(-1) * (kat_wznoszenia/180.0)) * odleglosc;

//     return (fabs(dron.polozenie_z() + przesun_dol - dno.zwroc_z()) <= dron.promien());
// }

// bool scena::wynurzenie() const {
//     return (fabs(dron.polozenie_z() - woda.zwroc_z()) <= dron.promien());
// }



void scena::dodaj_dno(const std::string & nazwa_lok, const std::string & nazwa_glob) {
    dno.dodaj_plik_lok(nazwa_lok);
    dno.dodaj_plik_glob(nazwa_glob);
    
    dno.wczytaj_lok();

    char pom[100] = {0};
    nazwa_glob.copy(pom, 100);
    Lacze.DodajNazwePliku(pom);
}

void scena::dodaj_wode(const std::string & nazwa_lok, const std::string & nazwa_glob) {
    woda.dodaj_plik_lok(nazwa_lok);
    woda.dodaj_plik_glob(nazwa_glob);

    woda.wczytaj_lok();

    char pom[100] = {0};
    nazwa_glob.copy(pom, 100);
    Lacze.DodajNazwePliku(pom);
}

void scena::dodaj_korpus(const std::string & nazwa_lok, const std::string & nazwa_glob) {
    dron_scena.dodaj_pliki_korpus(nazwa_lok, nazwa_glob);

    char pom[100] = {0};
    nazwa_glob.copy(pom, 100);
    Lacze.DodajNazwePliku(pom);
}

void scena::dodaj_sruba_lewa(const std::string & nazwa_lok, const std::string & nazwa_glob) {
    dron_scena.dodaj_pliki_sruby_lewej(nazwa_lok, nazwa_glob);

    char pom[100] = {0};
    nazwa_glob.copy(pom, 100);
    Lacze.DodajNazwePliku(pom);
}

void scena::dodaj_sruba_prawa(const std::string & nazwa_lok, const std::string & nazwa_glob) {
    dron_scena.dodaj_pliki_sruby_prawej(nazwa_lok, nazwa_glob);

    char pom[100] = {0};
    nazwa_glob.copy(pom, 100);
    Lacze.DodajNazwePliku(pom);
}

void scena::inicjalizuj() {
    Lacze.ZmienTrybRys(PzG::TR_3D);
    Lacze.Inicjalizuj();
    dron_scena.inicjalizuj_drona();
    rysuj();
}

void scena::ruch_prosto(double kat_wznoszenia, double odleglosc) {
    int kwant = 250;
    for(int i = 0; i < kwant; ++i) {
        // if(kolizja(kat_wznoszenia, odleglosc/double(kwant))) {
        //     std::cout << "Kolizja.\n";
        //     break;
        // } else if(wynurzenie() && ((kat_wznoszenia > 0 && odleglosc > 0) || (kat_wznoszenia < 0 && odleglosc < 0))) {
        //     std::cout << "Wynurzenie.\n";
        //     odleglosc = odleglosc * cos(acos(-1) * kat_wznoszenia / 180.0);
        //     kat_wznoszenia = 0;
        // }
        dron_scena.ruch_na_wprost(kat_wznoszenia, odleglosc/double(kwant));
        rysuj();
    }
}

void scena::obrot(double kat_obrotu) {
    int kwant = 360;
    for(int i = 0; i < kwant; ++i) {
        dron_scena.obrot(kat_obrotu/double(kwant));
        rysuj();
    }
}

