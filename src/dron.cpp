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
    left_motor.inicjalizuj_obiekt();
    right_motor.inicjalizuj_obiekt();

    TVector<double, 3> przesun;
    przesun[0] = -20;
    przesun[1] = -20;
    przesun[2] = 0;
    right_motor.wpisz_przesuniecie(przesun);
    przesun[1] = 20;
    left_motor.wpisz_przesuniecie(przesun);

    TMatrix<double, 3> obrot_temp;

    wylicz_macierz_obrotu(obrot_temp, 0);

    left_motor_ruch(obrot_temp);
    right_motor_ruch(obrot_temp);
}

void dron::dodaj_pliki_body(const std::string& nazwa_lok, const std::string& nazwa_glob) {
    body.dodaj_plik_lok(nazwa_lok);
    body.dodaj_plik_glob(nazwa_glob);
}

void dron::dodaj_pliki_sruby_lewej(const std::string& nazwa_lok, const std::string& nazwa_glob) {
    left_motor.dodaj_plik_lok(nazwa_lok);
    left_motor.dodaj_plik_glob(nazwa_glob);
}

void dron::dodaj_pliki_sruby_prawej(const std::string& nazwa_lok, const std::string& nazwa_glob) {
    right_motor.dodaj_plik_lok(nazwa_lok);
    right_motor.dodaj_plik_glob(nazwa_glob);
}

void dron::ruch_na_wprost(double kat_wznoszenia, double odleglosc) {
    TVector<double, 3> translacja;
    TMatrix<double, 3> obrot;
    wylicz_translacje(translacja, kat_wznoszenia, odleglosc);
    wylicz_macierz_obrotu(obrot, laczny_kat_obrotu);

    translacja = translacja * odleglosc;
    przesuniecie = przesuniecie + translacja;

    left_motor_ruch(obrot);
    right_motor_ruch(obrot);
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

    left_motor_ruch(obrot);
    right_motor_ruch(obrot);
    body_ruch(obrot);
}

void dron::left_motor_ruch(const TMatrix<double, 3>& obrot) {
    left_motor.wczytaj_wspolrzedne_lok();

    left_motor.ruch_lokalny();
    left_motor.obrot(obrot);
    left_motor.ruch_na_wprost(przesuniecie);

    left_motor.wpisz_wspolrzedne_glob();
}

void dron::right_motor_ruch(const TMatrix<double, 3>& obrot) {
    right_motor.wczytaj_wspolrzedne_lok();

    right_motor.ruch_lokalny();
    right_motor.obrot(obrot);
    right_motor.ruch_na_wprost(przesuniecie);

    right_motor.wpisz_wspolrzedne_glob();
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
    TVector<double, 3> dlugosc_sr = left_motor.zwroc_polowy_dlugosci();
    TVector<double, 3> dlugosc_kor = body.zwroc_polowy_dlugosci();

    dlugosc_sr[0] = dlugosc_sr[1] = sqrt(dlugosc_sr[0] * dlugosc_sr[0] + dlugosc_sr[1] * dlugosc_sr[1]);
    dlugosc_kor[0] = dlugosc_kor[1] = sqrt(dlugosc_kor[0] * dlugosc_kor[0] + dlugosc_kor[1] * dlugosc_kor[1]);

    return dlugosc_kor + dlugosc_sr;
}
