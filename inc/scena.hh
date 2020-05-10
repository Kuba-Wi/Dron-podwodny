#ifndef SCENA_HH
#define SCEN_HH

#include "obiekt.hh"
#include "lacze_do_gnuplota.hh"


class scena {
    private:
        powierzchnia dno;
        powierzchnia woda;
        obiekt dron;
        PzG::LaczeDoGNUPlota Lacze;
    public:
        scena() {}

        /*! dodaje dno do sceny i do lacza do gnuplota */
        void dodaj_dno(const std::string & nazwa_lok, const std::string & nazwa_glob);
        void dodaj_wode(const std::string & nazwa_lok, const std::string & nazwa_glob);
        void dodaj_drona(const std::string & nazwa_lok, const std::string & nazwa_glob);

        /*! startuje gnuplota */
        void inicjalizuj();
        /*! rysuje wszystkie powierzchnie i obiekty na scenie */
        void rysuj() { Lacze.Rysuj(); }

        void ruch_prosto(double kat_wznoszenia, double odleglosc);



};


#endif