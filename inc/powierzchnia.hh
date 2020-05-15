#ifndef POWIERZCHNIA_HH
#define POWIERZCHNIA_HH

#include <string>

class powierzchnia {
    protected:
        /*! plik z którego będzie rysowana powierzchnia */
        std::string plik_z_punktami;
        /*! przechowuje wspolrzedne lokalne powierzchni */
        std::string plik_lokalny;
        /*! współrzędna z-towa powierzchni */
        double z_powierzchni;
    public:
        powierzchnia() {}
        powierzchnia(const std::string & nazwa_lok, const std::string & nazwa_glob);
        
        /*! Wczytuje współrzędne lokalne do pliku z punktami */
        void wczytaj_lok();

        double polozenie_z() const { return z_powierzchni; }
};

#endif