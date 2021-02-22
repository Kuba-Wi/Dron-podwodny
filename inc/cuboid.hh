#pragma once

#include "obiekt.hh"

/*!
 * \brief Modeluje pojęcie prostokąta
 * Klasa modeluje pojęcie prostokąta, dziedziczy po klasie obiekt.
 * Utworzona w celu skorzystania z rzutowania w górę.
 */
class cuboid : public obiekt {
public:
    /*! \brief Wirtualny destruktor */
    virtual ~cuboid() {}
};
