#include "dron.hh"


void dron::inicjalizuj_drona() {
    korpus.inicjalizuj_obiekt();
    sruba_lewa.inicjalizuj_szesciokat();
    sruba_prawa.inicjalizuj_szesciokat();
}

void dron::dodaj_pliki_korpus(const std::string & nazwa_lok, const std::string & nazwa_glob) {
    korpus.dodaj_plik_lok(nazwa_lok);
    korpus.dodaj_plik_glob(nazwa_glob);

    korpus.wczytaj_lok();
}

void dron::dodaj_pliki_sruby_lewej(const std::string & nazwa_lok, const std::string & nazwa_glob) {
    sruba_lewa.dodaj_plik_lok(nazwa_lok);
    sruba_lewa.dodaj_plik_glob(nazwa_glob);

    sruba_lewa.wczytaj_lok();
}

void dron::dodaj_pliki_sruby_prawej(const std::string & nazwa_lok, const std::string & nazwa_glob) {
    sruba_prawa.dodaj_plik_lok(nazwa_lok);
    sruba_prawa.dodaj_plik_glob(nazwa_glob);

    sruba_prawa.wczytaj_lok();
}

void dron::ruch_na_wprost(double kat_wznoszenia, double odleglosc) {
    korpus.ruch_na_wprost(kat_wznoszenia, odleglosc);

    sruba_lewa.ruch_na_wprost(kat_wznoszenia, odleglosc);
    sruba_prawa.ruch_na_wprost(kat_wznoszenia, odleglosc);

    SWektor<double, 3> translacja;
    const double pi = acos(-1);

    translacja[0] = cos(pi*(laczny_kat_obrotu/180.0)) * cos(pi*(kat_wznoszenia/180.0));
    translacja[1] = sin(pi*(laczny_kat_obrotu/180.0)) * cos(pi*(kat_wznoszenia/180.0));
    translacja[2] = sin(pi*(kat_wznoszenia/180.0));

    translacja = translacja * odleglosc;
    przesuniecie = przesuniecie + translacja;
}

void dron::obrot(double kat_obrotu) {

    korpus.obrot(kat_obrotu);
    sruba_lewa.obrot(kat_obrotu);
    sruba_prawa.obrot(kat_obrotu);

    laczny_kat_obrotu += kat_obrotu;
    while(laczny_kat_obrotu >= 360.0)
        laczny_kat_obrotu -= 360.0;
    while(laczny_kat_obrotu <= -360.0)
        laczny_kat_obrotu += 360.0;
}
