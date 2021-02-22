#pragma once

#include <list>
#include <memory>
#include "dron.hh"
#include "lacze_do_gnuplota.hh"
#include "bar.hh"
#include "rectangle.hh"
#include "cuboid.hh"

/*!
 * \brief Modeluje pojęcie sceny
 * Klasa opisuje scenę na której będzie poruszać się obiekt
 * oraz będą przechowywane surface wody i surface dna.
 */
class stage {
private:
    /*! \brief Opisuje powierzchnię dna */
    surface dno;
    /*! \brief Opisuje powierzchnię wody */
    surface woda;
    /*! \brief Opisuje obiekt dron */
    dron dron_stage;
    /*! \brief Łącze z programem gnuplot */
    PzG::LaczeDoGNUPlota Lacze;

    /*! \brief lista z wskaźnikami na przeszkody */
    std::list<std::shared_ptr<obiekt>> lista_przeszkod;

    /*! \brief Rysuje wszystkie powierzchnie i obiekty na scenie */
    void rysuj() { Lacze.Rysuj(); }
    /*!
     * \brief Dodaje plik do łącza do gnuplota
     * \param[in] nazwa_pliku - nazwa dołączanego pliku
     */
    void lacze_dodaj_plik(const std::string& nazwa_pliku);

    /*!
     * \brief Dodaje przeszkodę na scenie
     * Metoda dodaje na scenę przeszkodę zapisaną w zadanych plikach
     * \param[in] nazwa_lok - nazwa pliku z danymi lokalnymi
     * \param[in] nazwa_glob - nazwa pliku z danymi globalnymi
     */
    void dodaj_przeszkode(const std::string& nazwa_lok, const std::string& nazwa_glob);

    /*!
     * \brief Zwraca informację o kolizji
     * Sprawdza czy jest kolizja z jakąś przeszkodą
     * \retval true - gdy będzie kolizja
     * \retval false - gdy nie będzie kolizja
     */
    bool kolizja() const;
    /*!
     * \brief Zwraca informację o kolizji z dnem
     * Metoda sprawdza czy nie ma kolizji z dnem
     * \retval true - gdy jest kolizja
     * \retval false - gdy nie ma kolizji
     */
    bool kolizja_dno() const;

    /*!
     * \brief Zwraca informację o wynurzenie
     * Sprawdza czy obiekt jest wynurzony
     * \retval true - gdy jest wynurzenie
     * \retval false - gdy nie ma wynurzenia
     */
    bool wynurzenie() const;

public:
    /*! \brief Konstruktor domyślny */
    stage() {}

    /*!
     * \brief Dodaje dno na scenę
     * Zapisuje pliki opisujące powierzchnię dna
     * \param[in] nazwa_lok - nazwa pliku z współrzędnymi lokalnymi
     * \param[in] nazwa_glob - nazwa pliku z współrzędnymi globalnymi
     */
    void dodaj_dno(const std::string& nazwa_lok, const std::string& nazwa_glob);
    /*!
     * \brief Dodaje wodę na scenę
     * Zapisuje pliki opisujące powierzchnię wody
     * \param[in] nazwa_lok - nazwa pliku z współrzędnymi lokalnymi
     * \param[in] nazwa_glob - nazwa pliku z współrzędnymi globalnymi
     */
    void dodaj_wode(const std::string& nazwa_lok, const std::string& nazwa_glob);
    /*!
     * \brief Dodaje body drona na scenę
     * Zapisuje pliki opisujące body
     * \param[in] nazwa_lok - nazwa pliku z współrzędnymi lokalnymi
     * \param[in] nazwa_glob - nazwa pliku z współrzędnymi globalnymi
     */
    void dodaj_body(const std::string& nazwa_lok, const std::string& nazwa_glob);
    /*!
     * \brief Dodaje lewą śrubę drona na scenę
     * Zapisuje pliki opisujące lewą śrubę
     * \param[in] nazwa_lok - nazwa pliku z współrzędnymi lokalnymi
     * \param[in] nazwa_glob - nazwa pliku z współrzędnymi globalnymi
     */
    void dodaj_left_motor(const std::string& nazwa_lok, const std::string& nazwa_glob);
    /*!
     * \brief Dodaje prawą śrubę drona na scenę
     * Zapisuje pliki opisujące prawą śrubę
     * \param[in] nazwa_lok - nazwa pliku z współrzędnymi lokalnymi
     * \param[in] nazwa_glob - nazwa pliku z współrzędnymi globalnymi
     */
    void dodaj_right_motor(const std::string& nazwa_lok, const std::string& nazwa_glob);
    /*!
     * \brief Dodaje prostopadłościan na scenę
     * Zapisuje pliki opisujące prostopadłościan i dodaje go na koniec listy przeszkód.
     * \param[in] nazwa_lok - nazwa pliku z współrzędnymi lokalnymi
     * \param[in] nazwa_glob - nazwa pliku z współrzędnymi globalnymi
     */
    void dodaj_cuboid(const std::string& nazwa_lok, const std::string& nazwa_glob);
    /*!
     * \brief Dodaje pręt na scenę
     * Zapisuje pliki opisujące pręt i dodaje go na koniec listy przeszkód.
     * \param[in] nazwa_lok - nazwa pliku z współrzędnymi lokalnymi
     * \param[in] nazwa_glob - nazwa pliku z współrzędnymi globalnymi
     */
    void dodaj_bar(const std::string& nazwa_lok, const std::string& nazwa_glob);
    /*!
     * \brief Dodaje prostokąt na scenę
     * Zapisuje pliki opisujące prostokąt i dodaje go na koniec listy przeszkód.
     * \param[in] nazwa_lok - nazwa pliku z współrzędnymi lokalnymi
     * \param[in] nazwa_glob - nazwa pliku z współrzędnymi globalnymi
     */
    void dodaj_rectangle(const std::string& nazwa_lok, const std::string& nazwa_glob);

    /*! \brief Inicjalizuje Łącze do gnuplota oraz drona */
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
