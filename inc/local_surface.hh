#pragma once

#include <string>

/*!
 * \brief Modeluje powierzchnię lokalną
 * Klasa przechowuje nazwę pliku ze współrzędnymi lokalnymi powierzchni.
 */
class local_surface {
protected:
    /*! \brief nazwa pliku ze współrzędnymi lokalnymi powierzchni */
    std::string nazwa_pliku_lok;

public:
    /*! \brief konstruktor domyślny */
    local_surface() {}
    /*!
     * \brief Konstruktor zapisuje nazwę pliku
     * \param[in] nazwa - nazwa_pliku, który ma zostać zapisany
     */
    local_surface(const std::string& nazwa) : nazwa_pliku_lok(nazwa) {}
};
