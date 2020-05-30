#ifndef OBIEKT_HH
#define OBIEKT_HH

#include <vector>

#include "SWektor.hh"
#include "powierzchnia.hh"
#include "SMacierz.hh"

/*!
 * \brief Modeluje pojęcie obiektu
 * Klasa opisuje obiekt geometryczny, który może się poruszać
 * i obracać wokół własnej osi. 
 */
class obiekt : public powierzchnia {
    protected:
        /*! \brief Przechowuje współrzędne punktów tworzących obiekt */
        std::vector<SWektor<double, 3>> wspolrzedne;
        /*! \brief Łączny kąt obrotu obiektu */
        double laczny_kat_obrotu;
        /*! \brief przesunięcie obiektu względem wspolrzednych lokalnych */
        SWektor<double, 3> przesuniecie;
        /*! \brief odległości środka obiektu od ścian */
        SWektor<double, 3> polowa_dl;
        /*! \brief Środek wspolrzednych lokalnych obiektu */
        SWektor<double, 3> srodek_lok;

        /*! 
         * \brief Wczytuje wspolrzedne z pliku
         * Wczytuje dane z pliku i zapisuje je do pola współrzędne
         * \param[in] nazwa_pliku - nazwa pliku z którego będą odczytywane dane 
         */
        void wczytaj_wspolrz(const std::string & nazwa_pliku);

    public:
        /*! 
         * \brief Konstruktor
         * Zeruje wektor przesunięcia i łączny kąt obrotu.
         */
        obiekt();

        virtual ~obiekt() {}
       
        /*!
         * \brief Inicjalizuje pola klasy
         * Wylicza srodek_lok oraz polowa_wysokosci, wpisuje plik lokalny do pliku z punktami
         * metoda powinna być wywołana przed wykonaniem ruchów przez obiekt
         */
        void inicjalizuj_obiekt();

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

        /*!
         * \brief Zwraca środek drona
         * Metoda zwraca wartość współrzędnych środka drona
         * \return Współrzędna środka drona
         */
        SWektor<double, 3> polozenie() const;

        /*!
         * \brief Zwraca wektor z polowami dlugości obiektu
         * Metoda zwraca połowę wysokości obiektu
         * \retval polowa_wysokosci - pole klasy 
         */
        SWektor<double, 3> zwroc_polowy_dlugosci() const { return polowa_dl; }
};



#endif