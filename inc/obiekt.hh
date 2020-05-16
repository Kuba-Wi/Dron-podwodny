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
    private:
        /*! \brief Liczy wszystkie utworzone wektory 3D */
        static int lacznie_obiektow3D;
        /*! \brief Liczy aktualnie istniejące wektory 3D */
        static int aktualnie_obiektow3D;

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
        obiekt();
        /*! 
         * \brief Destruktor
         * Zmniejsza liczbę aktualnie_obiektow o ilość współrzędnych
         * alktualnie istniejących.
         */
        ~obiekt() { aktualnie_obiektow3D -= wspolrzedne.size(); }
       
        /*! wylicza polozenie zetowe środka lokalnego drona oraz polowe wysokosci*/
        /*!
         * \brief Inicjalizuje pola klasy
         * Wylicza srodek_lok oraz polowa_wysokosci
         */
        void inicjalizuj_obiekt();

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

        /*! zwraca wartość współrzędnej z-towej środka drona */
        /*!
         * \brief Zwraca środek drona
         * \return Współrzędna zetowa środka drona
         */
        double polozenie_z() const;

        /*!
         * \brief Zwraca polowę wysokości obiektu
         * \retval polowa_wysokosci - pole klasy 
         */
        double promien() const { return polowa_wysokosci; }

        /*!
         * \brief Zwraca łączną liczbę wektorów 3D
         * \retval lacznie_obiektow3D - pole klasy
         */
        static int lacznie_obiekty() { return lacznie_obiektow3D; }
        /*!
         * \brief Zwraca aktualną liczbę wektorów 3D
         * \retval aktualnie_obiektow3D - pole klasy
         */
        static int aktualnie_obiekty() { return aktualnie_obiektow3D; }
};



#endif