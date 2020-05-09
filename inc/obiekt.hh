#ifndef OBIEKT_HH
#define OBIEKT_HH

#include <vector>

#include "SWektor.hh"
#include "powierzchnia.hh"

class obiekt : public powierzchnia {
    private:
        /*! zawiera wspolrzedne punktów obiektu, który ma zostać narysowany*/
        std::vector<SWektor<double, 3>> wspolrzedne;
        /*! o jaki kąt został dotychczas obrócony obiekt */
        double laczny_kat_obrotu;
        /*! przesunięcie obiektu względem wspolrzednych lokalnych */
        SWektor<double, 3> przesuniecie;

        /*! wpisuje wspolrzedne z vectora do pliku globalnego*/
        void wpisz_wspolrzedne_glob();
         /*! wczytuje wspolrzedne lokalne do wektora */
        void wczytaj_wspolrzedne();
    public:
        obiekt() {}
        obiekt(const std::string & nazwa_lok, const std::string & nazwa_glob) : 
                powierzchnia(nazwa_lok, nazwa_glob) {}

        void ruch_na_wprost(double kat_wznoszenia, double odleglosc);
        void obrot(double kat_obrotu);
};



#endif