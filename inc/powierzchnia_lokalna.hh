#ifndef POWIERZCHNIA_LOK_HH
#define POWIERZCHNIA_LOK_HH

#include <string>

/*!
 * \brief Modeluje powierzchnię lokalną
 * Klasa przechowuje nazwę pliku ze współrzędnymi lokalnymi powierzchni.
 */
class powierzchnia_lokalna {
    protected:
        /*! \brief nazwa pliku ze współrzędnymi lokalnymi powierzchni */
        std::string nazwa_pliku_lok;
    public:
        /*! \brief konstruktor domyślny */
        powierzchnia_lokalna() {}
        /*! 
         * \brief Konstruktor zapisuje nazwę pliku
         * \param[in] nazwa - nazwa_pliku, który ma zostać zapisany
         */
        powierzchnia_lokalna(const std::string & nazwa) : nazwa_pliku_lok(nazwa) {}
};

#endif