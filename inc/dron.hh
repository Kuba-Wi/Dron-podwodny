#pragma once
#include "obiekt.hh"
#include "szesciokat.hh"

class dron {
    private:
        obiekt korpus;
        szesciokat sruba_prawa;
        szesciokat sruba_lewa;
        /*! \brief Łączny kąt obrotu obiektu */
        double laczny_kat_obrotu;
        /*! \brief przesunięcie obiektu względem wspolrzednych lokalnych */
        SWektor<double, 3> przesuniecie;

    public:
        dron() {}
        void inicjalizuj_drona();
        //dodaje pliki lokalne i globalne dla korpusu wczytuje plik_lok do pliku_glob
        void dodaj_pliki_korpus(const std::string & nazwa_lok, const std::string & nazwa_glob);
        void dodaj_pliki_sruby_lewej(const std::string & nazwa_lok, const std::string & nazwa_glob);
        void dodaj_pliki_sruby_prawej(const std::string & nazwa_lok, const std::string & nazwa_glob);

        void ruch_na_wprost(double kat_wznoszenia, double odleglosc);
        void obrot(double kat_obrotu);

};