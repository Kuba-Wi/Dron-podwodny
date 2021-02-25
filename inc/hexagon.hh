#pragma once
#include <vector>
#include "TMatrix.hh"
#include "TVector.hh"
#include "obiekt.hh"

/*!
 * \brief Modeluje pojęcie graniastosłupa sześciokątnego
 * Klasa opisuje graniastosłup sześciokątny, który może się poruszać
 * i obracać wokół własnej osi.
 */
class hexagon : public obiekt {
private:
    /*!
     * \brief wylicza macierz rotationu
     * Metoda wylicza macierz rotationu wokół osi OX.
     */
    void rotation_matrix_x(TMatrix<double, size_of_TVec_3D>& rotation, double rotation_angle) const;

public:
    /*!
     * \brief Konstruktor
     * Zeruje vector przesunięcia i łączny kąt rotationu.
     */
    hexagon() : obiekt() {}

    /*!
     * \brief Zmienia przesunięcie graniastosłupa
     * Metoda wpisuje vector wejściowy do vectora przesunięcie.
     * \param[in] mv - vector, który ma być przepisany
     */
    void inscribe_translation(const TVector<double, size_of_TVec_3D>& mv) { translation = mv; }

    /*!
     * \brief Powoduje ruch o vector przesunięcie
     * Metoda powoduje przesunięcie graniastosłupa o vector przesunięcie
     * oraz obrót wokół osi 0X.
     */
    void local_move();
};
