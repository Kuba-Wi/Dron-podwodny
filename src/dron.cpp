#include "dron.hh"

dron::dron() {
    for (int i = 0; i < 3; ++i)
        przesuniecie[i] = 0;

    laczny_kat_obrotu = 0;
}

void dron::wylicz_translacje(TVector<double, 3>& translacja, double kat_wznoszenia, double odleglosc) const {
    const double pi = acos(-1);

    translacja[0] = cos(pi * (laczny_kat_obrotu / 180.0)) * cos(pi * (kat_wznoszenia / 180.0));
    translacja[1] = sin(pi * (laczny_kat_obrotu / 180.0)) * cos(pi * (kat_wznoszenia / 180.0));
    translacja[2] = sin(pi * (kat_wznoszenia / 180.0));
}

void dron::wylicz_macierz_obrotu(TMatrix<double, 3>& obrot, double kat_obrotu) const {
    const double pi = acos(-1);

    for (int i = 0; i < 3; ++i) {
        obrot(2, i) = 0;
        obrot(i, 2) = 0;
    }
    obrot(2, 2) = 1;

    obrot(0, 0) = cos(pi * (kat_obrotu / 180.0));
    obrot(1, 1) = obrot(0, 0);
    obrot(1, 0) = sin(pi * (kat_obrotu / 180.0));
    obrot(0, 1) = -obrot(1, 0);
}

void dron::inicjalizuj_drona() {
    body.inicjalizuj_obiekt();
    sruba_lewa.inicjalizuj_obiekt();
    sruba_prawa.inicjalizuj_obiekt();

    TVector<double, 3> przesun;
    przesun[0] = -20;
    przesun[1] = -20;
    przesun[2] = 0;
    sruba_prawa.wpisz_przesuniecie(przesun);
    przesun[1] = 20;
    sruba_lewa.wpisz_przesuniecie(przesun);

    TMatrix<double, 3> obrot_temp;

    wylicz_macierz_obrotu(obrot_temp, 0);

    sruba_lewa_ruch(obrot_temp);
    sruba_prawa_ruch(obrot_temp);
}

void dron::dodaj_pliki_body(const std::string& nazwa_lok, const std::string& nazwa_glob) {
    body.dodaj_plik_lok(nazwa_lok);
    body.dodaj_plik_glob(nazwa_glob);
}

void dron::dodaj_pliki_sruby_lewej(const std::string& nazwa_lok, const std::string& nazwa_glob) {
    sruba_lewa.dodaj_plik_lok(nazwa_lok);
    sruba_lewa.dodaj_plik_glob(nazwa_glob);
}

void dron::dodaj_pliki_sruby_prawej(const std::string& nazwa_lok, const std::string& nazwa_glob) {
    sruba_prawa.dodaj_plik_lok(nazwa_lok);
    sruba_prawa.dodaj_plik_glob(nazwa_glob);
}

void dron::ruch_na_wprost(double kat_wznoszenia, double odleglosc) {
    TVector<double, 3> translacja;
    TMatrix<double, 3> obrot;
    wylicz_translacje(translacja, kat_wznoszenia, odleglosc);
    wylicz_macierz_obrotu(obrot, laczny_kat_obrotu);

    translacja = translacja * odleglosc;
    przesuniecie = przesuniecie + translacja;

    sruba_lewa_ruch(obrot);
    sruba_prawa_ruch(obrot);
    body_ruch(obrot);
}

void dron::obrot(double kat_obrotu) {
    TMatrix<double, 3> obrot;

    laczny_kat_obrotu += kat_obrotu;
    while (laczny_kat_obrotu >= 360.0)
        laczny_kat_obrotu -= 360.0;
    while (laczny_kat_obrotu <= -360.0)
        laczny_kat_obrotu += 360.0;

    wylicz_macierz_obrotu(obrot, laczny_kat_obrotu);

    sruba_lewa_ruch(obrot);
    sruba_prawa_ruch(obrot);
    body_ruch(obrot);
}

void dron::sruba_lewa_ruch(const TMatrix<double, 3>& obrot) {
    sruba_lewa.wczytaj_wspolrzedne_lok();

    sruba_lewa.ruch_lokalny();
    sruba_lewa.obrot(obrot);
    sruba_lewa.ruch_na_wprost(przesuniecie);

    sruba_lewa.wpisz_wspolrzedne_glob();
}

void dron::sruba_prawa_ruch(const TMatrix<double, 3>& obrot) {
    sruba_prawa.wczytaj_wspolrzedne_lok();

    sruba_prawa.ruch_lokalny();
    sruba_prawa.obrot(obrot);
    sruba_prawa.ruch_na_wprost(przesuniecie);

    sruba_prawa.wpisz_wspolrzedne_glob();
}

void dron::body_ruch(const TMatrix<double, 3>& obrot) {
    body.wczytaj_wspolrzedne_lok();

    body.obrot(obrot);
    body.ruch_na_wprost(przesuniecie);

    body.wpisz_wspolrzedne_glob();
}

TVector<double, 3> dron::zwroc_polozenie() const {
    return przesuniecie + body.polozenie();
}

TVector<double, 3> dron::zwroc_dlugosci() const {
    TVector<double, 3> dlugosc_sr = sruba_lewa.zwroc_polowy_dlugosci();
    TVector<double, 3> dlugosc_kor = body.zwroc_polowy_dlugosci();

    dlugosc_sr[0] = dlugosc_sr[1] = sqrt(dlugosc_sr[0] * dlugosc_sr[0] + dlugosc_sr[1] * dlugosc_sr[1]);
    dlugosc_kor[0] = dlugosc_kor[1] = sqrt(dlugosc_kor[0] * dlugosc_kor[0] + dlugosc_kor[1] * dlugosc_kor[1]);

    return dlugosc_kor + dlugosc_sr;
}
