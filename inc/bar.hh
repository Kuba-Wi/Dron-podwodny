#pragma once

#include "obiekt.hh"

/*!
 * \brief Modeluje pojęcie pręta
 * Klasa modeluje pojęcie pręta, dziedziczy po klasie obiekt.
 * Utworzona w celu skorzystania z rzutowania w górę.
 */
class bar : public obiekt {
public:
    /*! Wirtualny destruktor */
    virtual ~bar() {}
};
