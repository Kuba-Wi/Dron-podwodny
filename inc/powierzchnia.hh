#pragma once

#include <string>
#include "powierzchnia_lokalna.hh"

/*!
 * \brief Modeluje pojęcie powierzchni
 *
 * Klasa przechowuje nazwę pliku z współrzędnymi
 * globalnymi powierzchni, z którego gnuplot odczytuje współrzędne
 * do rysowania.
 */
class powierzchnia : public powierzchnia_lokalna {
protected:
    /*! \brief plik z którego będzie rysowana powierzchnia */
    std::string plik_z_punktami;
    /*! \brief współrzędna z-towa powierzchni */
    double z_powierzchni;

public:
    /*! \brief Konstruktor bezparametryczny */
    powierzchnia() {}
    /*! \brief Konstruktor zapisuje nazwę pliku lokalnego i globalnego
     * \param[in] nazwa_lok - nazwa pliku z współrzędnymi lokalnymi
     * \param[in] nazwa_glob - nazwa pliku z współrzędnymi globalnymi
     */
    powierzchnia(const std::string& nazwa_lok, const std::string& nazwa_glob)
        : powierzchnia_lokalna(nazwa_lok), plik_z_punktami(nazwa_glob) {}

    /*!
     * \brief Zapisuje plik lokalny
     * Metoda zapisuje nazwę pliku z współrzędnymi lokalnymi
     * \param[in] nazwa_lok - nazwa pliku z danymi lokalnymi
     */
    void dodaj_plik_lok(const std::string& nazwa_lok);
    /*!
     * \brief Zapisuje plik globalny
     * Metoda zapisuje nazwę pliku z współrzędnymi globalnymi
     * \param[in] nazwa_glob - nazwa pliku z danymi lokalnymi
     */
    void dodaj_plik_glob(const std::string& nazwa_glob);

    /*!
     * \brief Przepisuje plik lokalny do pliku z punktami
     * Metoda zapisuje współrzędne z pliku z współrzędnymi lokalnymi
     * do pliku z współrzędnymi globalnymi
     */
    void wczytaj_lok();

    /*!
     * \brief zwraca wspolrzedną z-tową powierzchni
     * \retval z_powierzchni - współrzędna klasy
     */
    double zwroc_z() const { return z_powierzchni; }
};
