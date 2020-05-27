#pragma once
#include "obiekt.hh"
#include "szesciokat.hh"
#include <array>

class dron {
    private:
        obiekt korpus;
        std::array<szesciokat, 2> sruby;
        /*! \brief Łączny kąt obrotu obiektu */
        double laczny_kat_obrotu;
        /*! \brief przesunięcie obiektu względem wspolrzednych lokalnych */
        SWektor<double, 3> przesuniecie;

    public:
        dron() {}

        void inicjalizuj_drona();

        void ruch_na_wprost(double kat_wznoszenia, double odleglosc);
        void obrot(double kat_obrotu);

};