#include "dron.hh"


dron::dron() {
    for(int i = 0; i < 3; ++i)
        przesuniecie_lok_sruby[i] = 0;
}

void dron::wylicz_translacje(SWektor<double, 3> & translacja, double kat_wznoszenia, double odleglosc) const {
    const double pi = acos(-1);

    translacja[0] = cos(pi*(laczny_kat_obrotu/180.0)) * cos(pi*(kat_wznoszenia/180.0));
    translacja[1] = sin(pi*(laczny_kat_obrotu/180.0)) * cos(pi*(kat_wznoszenia/180.0));
    translacja[2] = sin(pi*(kat_wznoszenia/180.0));
}

void dron::wylicz_macierz_obrotu(SMacierz<double, 3> & obrot, double kat_obrotu) const {
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


void dron::inicjalizuj_drona() {
    korpus.inicjalizuj_obiekt();
    sruba_lewa.inicjalizuj_szesciokat();
    sruba_prawa.inicjalizuj_szesciokat();

    SWektor<double, 3> przesun;
    przesun[0] = -20;
    przesun[1] = -20;
    przesun[2] = 0;
    sruba_prawa.wpisz_przesuniecie(przesun);
    przesun[1] = 20;
    sruba_lewa.wpisz_przesuniecie(przesun);
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

    SWektor<double, 3> translacja;
    SMacierz<double, 3> obrot;
    wylicz_translacje(translacja, kat_wznoszenia, odleglosc);
    wylicz_macierz_obrotu(obrot, laczny_kat_obrotu);

    translacja = translacja * odleglosc;
    przesuniecie = przesuniecie + translacja;

    sruba_lewa_ruch(obrot);
    sruba_prawa_ruch(obrot);
    korpus_ruch(obrot);
}

void dron::obrot(double kat_obrotu) {

    SMacierz<double, 3> obrot;

    laczny_kat_obrotu += kat_obrotu;
    while(laczny_kat_obrotu >= 360.0)
        laczny_kat_obrotu -= 360.0;
    while(laczny_kat_obrotu <= -360.0)
        laczny_kat_obrotu += 360.0;

    wylicz_macierz_obrotu(obrot, laczny_kat_obrotu);

    sruba_lewa_ruch(obrot);
    sruba_prawa_ruch(obrot);
    korpus_ruch(obrot);
}

void dron::sruba_lewa_ruch(const SMacierz<double, 3> & obrot) {
    sruba_lewa.wczytaj_wspolrzedne_lok();

    sruba_lewa.ruch_lokalny();
    sruba_lewa.obrot(obrot);
    sruba_lewa.ruch_na_wprost(przesuniecie);

    sruba_lewa.wpisz_wspolrzedne_glob();
}

void dron::sruba_prawa_ruch(const SMacierz<double, 3> & obrot) {
    sruba_prawa.wczytaj_wspolrzedne_lok();

    sruba_prawa.ruch_lokalny();
    sruba_prawa.obrot(obrot);
    sruba_prawa.ruch_na_wprost(przesuniecie);

    sruba_prawa.wpisz_wspolrzedne_glob();
}

void dron::korpus_ruch(const SMacierz<double, 3> & obrot) {
    korpus.wczytaj_wspolrzedne_lok();

    korpus.obrot(obrot);
    korpus.ruch_na_wprost(przesuniecie);

    korpus.wpisz_wspolrzedne_glob();
}