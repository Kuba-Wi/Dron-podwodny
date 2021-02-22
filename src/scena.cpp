#include "scena.hh"
#include <iostream>
#include <cmath>


bool scena::kolizja_dno() const {
    return (fabs(dron_scena.zwroc_polozenie()[2] - dno.zwroc_z()) <= dron_scena.zwroc_dlugosci()[2]);
}

bool scena::wynurzenie() const {
    return (fabs(dron_scena.zwroc_polozenie()[2] - woda.zwroc_z()) <= dron_scena.zwroc_dlugosci()[2] - 20);
}

bool scena::kolizja() const {
    SWektor<double, 3> dlugosci_drona = dron_scena.zwroc_dlugosci();
    SWektor<double, 3> srodek_drona = dron_scena.zwroc_polozenie();
    SWektor<double, 3> dlugosci_przeszkody;
    SWektor<double, 3> odleglosci;

    bool jest_kolizja = false;

    for(auto& przeszkoda : lista_przeszkod) {
        dlugosci_przeszkody = przeszkoda->zwroc_polowy_dlugosci();
        odleglosci = srodek_drona - przeszkoda->polozenie();

        for(int i = 0; i < 3; ++i) {
            jest_kolizja = (fabs(odleglosci[i]) <= (dlugosci_przeszkody[i] + dlugosci_drona[i]));
            if(!jest_kolizja) {
                break;
            }
        }
        if(jest_kolizja) {
            return true;
        }
    }
    return false;
}


void scena::lacze_dodaj_plik(const std::string& nazwa_pliku) {
    Lacze.DodajNazwePliku(nazwa_pliku.c_str());
}


void scena::dodaj_dno(const std::string & nazwa_lok, const std::string & nazwa_glob) {
    dno.dodaj_plik_lok(nazwa_lok);
    dno.dodaj_plik_glob(nazwa_glob);
    
    dno.wczytaj_lok();

    lacze_dodaj_plik(nazwa_glob);
}

void scena::dodaj_wode(const std::string & nazwa_lok, const std::string & nazwa_glob) {
    woda.dodaj_plik_lok(nazwa_lok);
    woda.dodaj_plik_glob(nazwa_glob);

    woda.wczytaj_lok();

    lacze_dodaj_plik(nazwa_glob);
}

void scena::dodaj_korpus(const std::string & nazwa_lok, const std::string & nazwa_glob) {
    dron_scena.dodaj_pliki_korpus(nazwa_lok, nazwa_glob);

    lacze_dodaj_plik(nazwa_glob);
}

void scena::dodaj_sruba_lewa(const std::string & nazwa_lok, const std::string & nazwa_glob) {
    dron_scena.dodaj_pliki_sruby_lewej(nazwa_lok, nazwa_glob);

    lacze_dodaj_plik(nazwa_glob);
}

void scena::dodaj_sruba_prawa(const std::string & nazwa_lok, const std::string & nazwa_glob) {
    dron_scena.dodaj_pliki_sruby_prawej(nazwa_lok, nazwa_glob);

    lacze_dodaj_plik(nazwa_glob);
}

void scena::dodaj_przeszkode(const std::string & nazwa_lok, const std::string & nazwa_glob) {

    lista_przeszkod.back()->dodaj_plik_lok(nazwa_lok);
    lista_przeszkod.back()->dodaj_plik_glob(nazwa_glob);

    lista_przeszkod.back()->inicjalizuj_obiekt();

    lacze_dodaj_plik(nazwa_glob);
}

void scena::dodaj_prostopadloscian(const std::string & nazwa_lok, const std::string & nazwa_glob) {
    lista_przeszkod.push_back(std::make_shared<prostopadloscian>());

    dodaj_przeszkode(nazwa_lok, nazwa_glob);
}

void scena::dodaj_pret(const std::string & nazwa_lok, const std::string & nazwa_glob) {
    lista_przeszkod.push_back(std::make_shared<pret>());

    dodaj_przeszkode(nazwa_lok, nazwa_glob);
}

void scena::dodaj_prostokat(const std::string & nazwa_lok, const std::string & nazwa_glob) {
    lista_przeszkod.push_back(std::make_shared<prostokat>());

    dodaj_przeszkode(nazwa_lok, nazwa_glob);
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
        dron_scena.ruch_na_wprost(kat_wznoszenia, odleglosc/double(kwant));
        if(kolizja() || kolizja_dno()) {
            std::cout << "Kolizja!\n";
            dron_scena.ruch_na_wprost(kat_wznoszenia, -odleglosc/double(kwant));
            break;
        } else if(wynurzenie() && ((kat_wznoszenia > 0 && odleglosc > 0) || (kat_wznoszenia < 0 && odleglosc < 0))) {
            std::cout << "Wynurzenie.\n";
            odleglosc = odleglosc * cos(acos(-1) * kat_wznoszenia / 180.0);
            kat_wznoszenia = 0;
        }
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

