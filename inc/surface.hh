#pragma once

#include <string>
#include "local_surface.hh"

/*!
 * \brief Modeluje pojęcie powierzchni
 *
 * Klasa przechowuje nazwę pliku z współrzędnymi
 * globalnymi powierzchni, z którego gnuplot odczytuje współrzędne
 * do rysowania.
 */
class surface : public local_surface {
protected:
    /*! \brief plik z którego będzie rysowana surface */
    std::string file_with_points;
    /*! \brief współrzędna z-towa powierzchni */
    double z_of_surface;

public:
    /*! \brief Konstruktor bezparametryczny */
    surface() {}
    /*! \brief Konstruktor zapisuje nazwę pliku lokalnego i globalnego
     * \param[in] local_name - nazwa pliku z współrzędnymi lokalnymi
     * \param[in] global_name - nazwa pliku z współrzędnymi globalnymi
     */
    surface(const std::string& local_name, const std::string& global_name)
        : local_surface(local_name), file_with_points(global_name) {}

    /*!
     * \brief Zapisuje plik lokalny
     * Metoda zapisuje nazwę pliku z współrzędnymi lokalnymi
     * \param[in] local_name - nazwa pliku z danymi lokalnymi
     */
    void add_local_file(const std::string& local_name);
    /*!
     * \brief Zapisuje plik globalny
     * Metoda zapisuje nazwę pliku z współrzędnymi globalnymi
     * \param[in] global_name - nazwa pliku z danymi lokalnymi
     */
    void add_global_file(const std::string& global_name);

    /*!
     * \brief Przepisuje plik lokalny do pliku z punktami
     * Metoda zapisuje współrzędne z pliku z współrzędnymi lokalnymi
     * do pliku z współrzędnymi globalnymi
     */
    void read_local();

    /*!
     * \brief zwraca wspolrzedną z-tową powierzchni
     * \retval z_of_surface - współrzędna klasy
     */
    double return_z() const { return z_of_surface; }
};
