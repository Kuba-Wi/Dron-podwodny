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
        //przesuniecie sruby wzgledem korpusu może dodam później
        SWektor<double, 3> przesuniecie_lok_sruby;


        void wylicz_translacje(SWektor<double, 3> & wek, double kat_wznoszenia, double odleglosc) const;

        void wylicz_macierz_obrotu(SMacierz<double, 3> & obrot, double kat_obrotu) const;

    public:
        //zeruje przesuniecie_lok_sruby
        dron();
        void inicjalizuj_drona();
        //dodaje pliki lokalne i globalne dla korpusu wczytuje plik_lok do pliku_glob
        void dodaj_pliki_korpus(const std::string & nazwa_lok, const std::string & nazwa_glob);
        void dodaj_pliki_sruby_lewej(const std::string & nazwa_lok, const std::string & nazwa_glob);
        void dodaj_pliki_sruby_prawej(const std::string & nazwa_lok, const std::string & nazwa_glob);

        void ruch_na_wprost(double kat_wznoszenia, double odleglosc);
        void obrot(double kat_obrotu);
        //ruch sruby lewej o przesuniecie i zadana macierz obrotu
        void sruba_lewa_ruch(const SMacierz<double, 3> & obrot);
        void sruba_prawa_ruch(const SMacierz<double, 3> & obrot);
        void korpus_ruch(const SMacierz<double, 3> & obrot);

};