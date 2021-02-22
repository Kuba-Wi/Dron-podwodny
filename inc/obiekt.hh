#pragma once

#include <vector>

#include "TMatrix.hh"
#include "TVector.hh"
#include "surface.hh"

/*!
 * \brief Modeluje pojęcie obiektu
 * Klasa opisuje obiekt geometryczny, który może się poruszać
 * i obracać wokół własnej osi.
 */
class obiekt : public surface {
protected:
    /*! \brief Przechowuje współrzędne punktów tworzących obiekt */
    std::vector<TVector<double, 3>> coordinates;
    /*! \brief Łączny kąt rotationu obiektu */
    double all_angle;
    /*! \brief przesunięcie obiektu względem wspolrzednych lokalnych */
    TVector<double, 3> translation;
    /*! \brief odległości środka obiektu od ścian */
    TVector<double, 3> lenght_half;
    /*! \brief Środek wspolrzednych lokalnych obiektu */
    TVector<double, 3> local_centre;

    /*!
     * \brief Wczytuje coordinates z pliku
     * Wczytuje dane z pliku i zapisuje je do pola współrzędne
     * \param[in] file_name - nazwa pliku z którego będą odczytywane dane
     */
    void read_coordinates(const std::string& file_name);

public:
    /*!
     * \brief Konstruktor
     * Zeruje vector przesunięcia i łączny kąt rotationu.
     */
    obiekt();
    /*! \brief Destruktor wirtualny */
    virtual ~obiekt() {}

    /*!
     * \brief initializee pola klasy
     * Wylicza local_centre oraz polowa_wysokosci, wpisuje plik lokalny do pliku z punktami
     * metoda powinna być wywołana przed wykonaniem ruchów przez obiekt
     */
    void initialize_obiekt();

    /*!
     * \brief Wczytuje coordinates lokalne
     * Wczytuje współrzędne z pliku z współrzędnymi lokalnymi
     * i zapisuje je do pola współrzędne.
     */
    void read_local_coordinates();

    /*!
     * \brief Wpisuje współrzędne do pliku_z_punktami
     * Zapisuje współrzędne z pola współrzędne do pliku globalnego
     */
    void write_global_coordinates();

    /*!
     * \brief Przeprowadza ruch na wprost
     * Powoduje ruch obiektu po prostej o zadany vector translacji
     * \param[in] mv - zadany vector
     */
    void move_ahead(const TVector<double, 3>& mv);

    /*!
     * \brief Powoduje obrót obiektu
     * Metoda powoduje obrót obiektu wokół własnej osi o zadaną macierz rotationu
     * \param[in] rotation_matrix - zadana macierz rotationu
     */
    void rotation(const TMatrix<double, 3>& rotation_matrix);

    /*!
     * \brief Zwraca środek drona
     * Metoda zwraca wartość współrzędnych środka drona
     * \return Współrzędna środka drona
     */
    TVector<double, 3> location() const;

    /*!
     * \brief Zwraca vector z polowami dlugości obiektu
     * Metoda zwraca połowę wysokości obiektu
     * \retval polowa_wysokosci - pole klasy
     */
    TVector<double, 3> return_lenght_halves() const { return lenght_half; }
};
