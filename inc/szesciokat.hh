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
        /*! \brief odległość środka drona od ściany górnej */
        double polowa_wysokosci;
        /*! \brief Środek wspolrzednych lokalnych obiektu */
        double srodek_lok;

        /*! 
         * \brief Wczytuje wspolrzedne z pliku
         * Wczytuje dane z pliku i zapisuje je do pola współrzędne
         * \param[in] nazwa_pliku - nazwa pliku z którego będą odczytywane dane 
         */
        void wczytaj_wspolrz(const std::string & nazwa_pliku);
         /*! 
          * \brief Wczytuje wspolrzedne lokalne
          * Wczytuje współrzędne z pliku z współrzędnymi lokalnymi 
          * i zapisuje je do pola współrzędne. 
          */
        void wczytaj_wspolrzedne_lok();
        /*! 
          * \brief Wczytuje wspolrzedne globalne
          * Wczytuje współrzędne z pliku z punktami 
          * i zapisuje je do pola współrzędne. 
          */
        void wczytaj_wspolrzedne_glob();
        
        /*!
         * \brief Wpisuje współrzędne do pliku_z_punktami
         * Zapisuje współrzędne z pola współrzędne do pliku globalnego 
         */
        void wpisz_wspolrzedne_glob();
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
       
        /*!
         * \brief Inicjalizuje pola klasy
         * Wylicza srodek_lok oraz polowa_wysokosci,
         * metoda powinna być wywołana przed wykonaniem ruchów przez obiekt
         */
        void inicjalizuj_szesciokat();

        /*!
         * \brief Przeprowadza ruch na wprost
         * Powoduje ruch obiektu po prostej do góry lub do dołu
         * o zadany kąt oraz na zadaną odległość
         * \param[in] kat_wznoszenia - katruchu do góry
         * \param[in] odleglosc - dystans do pokonania
         */
        void ruch_na_wprost(double kat_wznoszenia, double odleglosc);

        /*!
         * \brief Powoduje obrót obiektu
         * Metoda powoduje obrót obiektu wokół własnej osi o zadany kąt
         * \param[in] kat_obrotu - zadany kąt
         */
        void obrot(double kat_obrotu);

        /*!
         * \brief Zwraca środek drona
         * Metoda zwraca wartość współrzędnej zetowej drona
         * \return Współrzędna zetowa środka drona
         */
        double polozenie_z() const;

        /*!
         * \brief Zwraca polowę wysokości obiektu
         * Metoda zwraca połowę wysokości obiektu
         * \retval polowa_wysokosci - pole klasy 
         */
        double polowa_wys() const { return polowa_wysokosci; }
};