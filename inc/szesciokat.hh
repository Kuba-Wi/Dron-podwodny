#pragma once
#include "obiekt.hh"
#include <vector>
#include "SWektor.hh"
#include "SMacierz.hh"

class szesciokat : public obiekt {
    private:
        //zapisuje macierz obrotu wokół osi x
        void macierz_obrotu_x(SMacierz<double, 3> & obrot, double kat_obrotu) const;
    public:
        /*! 
         * \brief Konstruktor
         * Zeruje wektor przesunięcia i łączny kąt obrotu.
         */
        szesciokat() : obiekt() {}
        //wpisuje wektor przesun do współrzędnych przesunięcie
        void wpisz_przesuniecie(const SWektor<double, 3> & przesun) { przesuniecie = przesun; }

        //ruch o wspolrzedne sruby
        void ruch_lokalny();
};