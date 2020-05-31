#pragma once
#include "obiekt.hh"
#include <vector>
#include "SWektor.hh"
#include "SMacierz.hh"

/*!
 * \brief Modeluje pojęcie graniastosłupa sześciokątnego
 * Klasa opisuje graniastosłup sześciokątny, który może się poruszać
 * i obracać wokół własnej osi. 
 */
class szesciokat : public obiekt {
    private:
        /*!
         * \brief wylicza macierz obrotu
         * Metoda wylicza macierz obrotu wokół osi OX.
         */
        void macierz_obrotu_x(SMacierz<double, 3> & obrot, double kat_obrotu) const;
    public:
        /*! 
         * \brief Konstruktor
         * Zeruje wektor przesunięcia i łączny kąt obrotu.
         */
        szesciokat() : obiekt() {}

        /*!
         * \brief Zmienia przesunięcie graniastosłupa
         * Metoda wpisuje wektor wejściowy do wektora przesunięcie.
         * \param[in] przesun - wektor, który ma być przepisany
         */
        void wpisz_przesuniecie(const SWektor<double, 3> & przesun) { przesuniecie = przesun; }

        /*!
         * \brief Powoduje ruch o wektor przesunięcie
         * Metoda powoduje przesunięcie graniastosłupa o wektor przesunięcie
         * oraz obrót wokół osi 0X.
         */
        void ruch_lokalny();
};