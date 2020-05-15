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

        /*! rysuje wszystkie powierzchnie i obiekty na scenie */
        void rysuj() { Lacze.Rysuj(); }

        /*! zwrace tru gdy wykonanie ruchu zakończy się kolizją */
        bool kolizja(double kat_wznoszenia, double odleglosc) const;

        /*! zwraca true gdy jest wynurzenie */
        bool wynurzenie() const;
    public:
        scena() {}

        /*! dodaje dno do sceny i do lacza do gnuplota */
        void dodaj_dno(const std::string & nazwa_lok, const std::string & nazwa_glob);
        void dodaj_wode(const std::string & nazwa_lok, const std::string & nazwa_glob);
        void dodaj_drona(const std::string & nazwa_lok, const std::string & nazwa_glob);

        /*! startuje gnuplota */
        void inicjalizuj();

        void ruch_prosto(double kat_wznoszenia, double odleglosc);
        void obrot(double kat_obrotu);



};


#endif