#pragma once
#include "obiekt.hh"
#include <vector>
#include "SWektor.hh"
#include "SMacierz.hh"

class szesciokat : public obiekt {
       
    public:
        /*! 
         * \brief Konstruktor
         * Zeruje wektor przesunięcia i łączny kąt obrotu.
         */
        szesciokat() : obiekt() {}
        //wpisuje wektor przesun do współrzędnych przesunięcie
        void wpisz_przesuniecie(const SWektor<double, 3> & przesun) { przesuniecie = przesun; }
       

        void macierz_obrotu_z(SMacierz<double, 3> & obrot, double kat_obrotu) const;

        //ruch o wspolrzedne sruby
        void ruch_lokalny();
};