#ifndef OBIEKT_HH
#define OBIEKT_HH

#include <vector>

#include "SWektor.hh"
#include "powierzchnia.hh"
#include "SMacierz.hh"

class obiekt : public powierzchnia {
    private:
        /*! zawiera wspolrzedne punktów obiektu, który ma zostać narysowany*/
        std::vector<SWektor<double, 3>> wspolrzedne;
        /*! o jaki kąt został dotychczas obrócony obiekt */
        double laczny_kat_obrotu;
        /*! przesunięcie obiektu względem wspolrzednych lokalnych */
        SWektor<double, 3> przesuniecie;
        /*! odległość środka drona od ściany górnej */
        double polowa_wysokosci;
        /*! polorzenie zetowe lokalnego środka drona */
        double srodek_lok;

        /*! wczytuje wspolrzedne z pliku do wektora */
        void wczytaj_wspolrz(const std::string & nazwa_pliku);
         /*! wczytuje wspolrzedne lokalne do wektora */
        void wczytaj_wspolrzedne_lok();
        /*! wczytuje wspolrzedne globalne do wektora */
        void wczytaj_wspolrzedne_glob();
        
        /*! wpisuje wspolrzedne z vectora do pliku globalnego*/
        void wpisz_wspolrzedne_glob();
        /*! wypełnia macierz obrotu o zadany kat*/
        void macierz_obrotu(SMacierz<double, 3> & obrot, double kat_obrotu) const;

    public:
        obiekt();
       // obiekt(const std::string & nazwa_lok, const std::string & nazwa_glob);
        /*! wylicza polozenie zetowe środka lokalnego drona oraz polowe wysokosci*/
        void inicjalizuj_obiekt();

        void ruch_na_wprost(double kat_wznoszenia, double odleglosc);
        void obrot(double kat_obrotu);

        /*! zwraca wartość współrzędnej z-towej środka drona */
        double polozenie_z() const;

        /*! zwraca polowe wysokości drona */
        double promien() const { return polowa_wysokosci; }
};



#endif