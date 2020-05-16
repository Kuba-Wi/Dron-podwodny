#ifndef POWIERZCHNIA_HH
#define POWIERZCHNIA_HH

#include "powierzchnia_lokalna.hh"
#include <string>

class powierzchnia : public powierzchnia_lokalna {
    protected:
        /*! plik z którego będzie rysowana powierzchnia */
        std::string plik_z_punktami;
        /*! współrzędna z-towa powierzchni */
        double z_powierzchni;
    public:
        powierzchnia() {}
        powierzchnia(const std::string & nazwa_lok, const std::string & nazwa_glob);

        /*! dodaje plik lokalny ze wspolrzednymi */
        void dodaj_plik_lok(const std::string & nazwa_lok);
        /*! dodaje plik globalny ze wspolrzednymi */
        void dodaj_plik_glob(const std::string & nazwa_glob);
        
        /*! Wczytuje współrzędne lokalne do pliku z punktami */
        void wczytaj_lok();

        /*! zwraca wspolrzedna z-towa powierzchni*/
        double wysokosc_z() const { return z_powierzchni; }
};

#endif