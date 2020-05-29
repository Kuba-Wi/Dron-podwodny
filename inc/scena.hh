#ifndef SCENA_HH
#define SCEN_HH

#include "dron.hh"
#include "lacze_do_gnuplota.hh"
#include <list>
#include <memory>

/*!
 * \brief Modeluje pojęcie sceny
 * Klasa opisuje scenę na której będzie poruszać się obiekt
 * oraz będą przechowywane powierzchnia wody i powierzchnia dna.
 */
class scena {
    private:
        /*! \brief Opisuje powierzchnię dna */
        powierzchnia dno;
        /*! \brief Opisuje powierzchnię wody */
        powierzchnia woda;
        /*! \brief Opisuje obiekt dron */
        dron dron_scena;
        /*! \brief Łącze z programem gnuplot */
        PzG::LaczeDoGNUPlota Lacze;

        //lista z przeszkodami
        std::list<std::shared_ptr<obiekt>> lista_przeszkod;

        /*! \brief Rysuje wszystkie powierzchnie i obiekty na scenie */
        void rysuj() { Lacze.Rysuj(); }
        void lacze_dodaj_plik(const std::string& nazwa_pliku);

        /*!
         * \brief Zwraca informację o kolizji
         * Sprawdza czy wykonanie ruchu na zadane odległość i kąt wznoszenia
         * będzie skutkować kolizją
         * \retval true - gdy będzie kolizja
         * \retval false - gdy nie będzie kolizja 
         */
       // bool kolizja(double kat_wznoszenia, double odleglosc) const;

        /*!
         * \brief Zwraca informację o wynurzenie
         * Sprawdza czy obiekt jest wynurzony
         * \retval true - gdy jest wynurzenie
         * \retval false - gdy nie ma wynurzenia 
         */
        //bool wynurzenie() const;
    public:
        /*! \brief Konstruktor domyślny */
        scena() {}

        /*!
         * \brief Dodaje dno do sceny
         * Zapisuje pliki opisujące powierzchnię dna
         * \param[in] nazwa_lok - nazwa pliku z współrzędnymi lokalnymi
         * \param[in] nazwa_glob - nazwa pliku z współrzędnymi globalnymi
         */
        void dodaj_dno(const std::string & nazwa_lok, const std::string & nazwa_glob);
        /*!
         * \brief Dodaje wodę do sceny
         * Zapisuje pliki opisujące powierzchnię wody
         * \param[in] nazwa_lok - nazwa pliku z współrzędnymi lokalnymi
         * \param[in] nazwa_glob - nazwa pliku z współrzędnymi globalnymi
         */
        void dodaj_wode(const std::string & nazwa_lok, const std::string & nazwa_glob);
        /*!
         * \brief Dodaje obiekt dron do sceny
         * Zapisuje pliki opisujące obiekt dron i inicjalizuje go
         * \param[in] nazwa_lok - nazwa pliku z współrzędnymi lokalnymi
         * \param[in] nazwa_glob - nazwa pliku z współrzędnymi globalnymi
         */
        void dodaj_korpus(const std::string & nazwa_lok, const std::string & nazwa_glob);

        void dodaj_sruba_lewa(const std::string & nazwa_lok, const std::string & nazwa_glob);
        void dodaj_sruba_prawa(const std::string & nazwa_lok, const std::string & nazwa_glob);
        //dodaje przeszkodę na scenę
        void dodaj_przeszkode(const std::string & nazwa_lok, const std::string & nazwa_glob);

        /*! \brief Inicjalizuje Łącze do gnuplota */
        void inicjalizuj();

        /*! 
         * \brief Powoduje ruch drona na wprost
         * Powoduje ruch obiektu dron na wprost na zadaną odległość
         * i o dany kąt wznoszenia
         * \param[in] kat_wznoszenia - kąt o jaki ma się wznieść dron
         * \param[in] odleglosc - odległość na jaką ma się przemiaeścić dron
         */
        void ruch_prosto(double kat_wznoszenia, double odleglosc);
        /*!
         * \brief Powoduje obrót drona
         * Powoduje obrót drona wokół własnej osi o zadany kąt
         * \param[in] kat_obrotu - kąt o jaki ma być wykonany obrót
         */
        void obrot(double kat_obrotu);

};


#endif