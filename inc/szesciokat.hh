#pragma once
#include "powierzchnia.hh"
#include <vector>
#include "SWektor.hh"
#include "SMacierz.hh"

class szesciokat : public powierzchnia {
    private:
        /*! \brief Przechowuje współrzędne punktów tworzących obiekt */
        std::vector<SWektor<double, 3>> wspolrzedne;
        /*! \brief Łączny kąt obrotu obiektu */
        double laczny_kat_obrotu;
        /*! \brief przesunięcie obiektu względem wspolrzednych lokalnych */
        SWektor<double, 3> przesuniecie;
        /*! \brief odległości środka szesciokata od ścian */
        SWektor<double, 3> polowa_dl;
        /*! \brief Środek wspolrzednych lokalnych obiektu */
        SWektor<double, 3> srodek_lok;

        /*! 
         * \brief Wczytuje wspolrzedne z pliku
         * Wczytuje dane z pliku i zapisuje je do pola współrzędne
         * \param[in] nazwa_pliku - nazwa pliku z którego będą odczytywane dane 
         */
        void wczytaj_wspolrz(const std::string & nazwa_pliku);
        /*! 
          * \brief Wczytuje wspolrzedne globalne
          * Wczytuje współrzędne z pliku z punktami 
          * i zapisuje je do pola współrzędne. 
          */
        void wczytaj_wspolrzedne_glob();
        /*! 
         * \brief Wypełnia macierz obrotu o zadany kat
         * Wypełnia macierz służącą do transformacji współrzędnych obiektu.
         * \param[in] obrot - macierz, która ma być zapisana
         * \param[in] kat_obrotu - kąt jakim ma być wypełniona macierz
         */
        void macierz_obrotu(SMacierz<double, 3> & obrot, double kat_obrotu) const;

    public:
        /*! 
         * \brief Konstruktor
         * Zeruje wektor przesunięcia i łączny kąt obrotu.
         */
        szesciokat();
        //wpisuje wektor przesun do współrzędnych przesunięcie
        void wpisz_przesuniecie(const SWektor<double, 3> & przesun) { przesuniecie = przesun; }
       
        /*!
         * \brief Inicjalizuje pola klasy
         * Wylicza srodek_lok oraz polowa_wysokosci,
         * metoda powinna być wywołana przed wykonaniem ruchów przez obiekt
         */
        void inicjalizuj_szesciokat();

        /*! 
          * \brief Wczytuje wspolrzedne lokalne
          * Wczytuje współrzędne z pliku z współrzędnymi lokalnymi 
          * i zapisuje je do pola współrzędne. 
          */
        void wczytaj_wspolrzedne_lok();
        /*!
         * \brief Wpisuje współrzędne do pliku_z_punktami
         * Zapisuje współrzędne z pola współrzędne do pliku globalnego 
         */
        void wpisz_wspolrzedne_glob();

        void macierz_obrotu_z(SMacierz<double, 3> & obrot, double kat_obrotu) const;

        /*!
         * \brief Przeprowadza ruch na wprost
         * Powoduje ruch obiektu po prostej do góry lub do dołu
         * o zadany kąt oraz na zadaną odległość
         * \param[in] kat_wznoszenia - katruchu do góry
         * \param[in] odleglosc - dystans do pokonania
         */
        void ruch_na_wprost(const SWektor<double, 3> & przesun);
        /*!
         * \brief Powoduje obrót obiektu
         * Metoda powoduje obrót obiektu wokół własnej osi o zadany kąt
         * \param[in] kat_obrotu - zadany kąt
         */
        void obrot(const SMacierz<double, 3> & mac_obrotu);
        //ruch o wspolrzedne sruby
        void ruch_lokalny();

        /*!
         * \brief Zwraca środek drona
         * Metoda zwraca wartość współrzędnej zetowej drona
         * \return Współrzędna zetowa środka drona
         */
        SWektor<double, 3> polozenie() const;

        /*!
         * \brief Zwraca polowę wysokości obiektu
         * Metoda zwraca połowę wysokości obiektu
         * \retval polowa_wysokosci - pole klasy 
         */
        SWektor<double, 3> polowa_dlugosci() const { return polowa_dl; }

        //zwraca przesuniecie szesciokata
        SWektor<double, 3> zwroc_przesuniecie() const { return przesuniecie; }

        double zwroc_kat_obrotu() const { return laczny_kat_obrotu; }

};