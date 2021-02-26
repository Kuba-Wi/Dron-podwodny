#pragma once

#include <algorithm>
#include <cassert>
#include <cmath>
#include <iostream>
#include "TVector.hh"

/*!
 * Szablon klasy modeluje pojęcie macierzy.
 */
template <typename T, int Size>
class TMatrix {
    std::array<TVector<T, Size>, Size> columns; /*! kolejne columns macierzy */

    /*!
     * Metoda zamienia columns w macierzy.
     * Argumenty:
     * a - indeks columns do zamiany
     * b - indeks columns do zamiany
     * Brak wartości zwracanej
     */
    void swap_columns(std::size_t a, std::size_t b);

public:
    /*!
     * Metoda pozwala wpisać odpowiednią składową do macierzy.
     * Argumenty:
     * a - indeks wiersza macierzy
     * b - indeks columns macierzy
     * Zwraca:
     * referencję do składowej (a,b)
     */
    T& operator()(std::size_t a, std::size_t b);
    /*!
     * Metoda pozwala odczytać odpowiednią składową macierzy.
     * Argumenty:
     * a - indeks składowej
     * b - indeks columns macierzy
     * Zwraca:
     * składową (a,b)
     */
    T operator()(std::size_t a, std::size_t b) const;

    /*!
     * Metoda oblicza determinant macierzy.
     * Argumenty:   Brak
     * Zwraca:
     * determinant macierzy
     */
    T determinant() const;

    /*!
     * Metoda mnoży macierz przez vector.
     * Argumenty:
     * vec - vector przez, który mnożymy
     * Zwraca:
     * vector - iloczyn macierzy i vectora
     */
    TVector<T, Size> operator*(const TVector<T, Size>& vec) const;

    /*!
     * Metoda wstawia kolumnę do macierzy.
     * Argumenty:
     * vec - vector który wstawiamy
     * column - indeks zamienianej columns
     * Zwraca:
     * macierz po zamianie
     */
    TMatrix<T, Size> insert_column(const TVector<T, Size>& vec, std::size_t column) const;
};

template <typename T, int Size>
void TMatrix<T, Size>::swap_columns(std::size_t a, std::size_t b) {
    if (a < Size && b < Size)
        std::swap(columns[a], columns[b]);
}

template <typename T, int Size>
T& TMatrix<T, Size>::operator()(std::size_t a, std::size_t b) {
    assert(a < Size && b < Size);
    return columns[b][a];
}

template <typename T, int Size>
T TMatrix<T, Size>::operator()(std::size_t a, std::size_t b) const {
    assert(a < Size && b < Size);
    return columns[b][a];
}

template <typename T, int Size>
T TMatrix<T, Size>::determinant() const {
    TMatrix<T, Size> temp = *this;
    double parity = 1;
    int column_nr_to_swap = 0;
    T quotient;
    T determinant = 1;

    for (int i = 0; i < Size; i++) {

        column_nr_to_swap = i + 1;

        while (fabs(temp(i, i)) < pow(0.1, 12)) { 

            if (column_nr_to_swap == Size)
                return 0.0;

            else if (!(fabs(temp(i, column_nr_to_swap)) <
                       pow(0.1, 12))) {

                temp.swap_columns(column_nr_to_swap, i);
                parity = -parity;
            }
            column_nr_to_swap++;
        }
        determinant = determinant * temp(i, i);

        for (int j = i + 1; j < Size; j++) {

            quotient = temp(i, j) / temp(i, i);
            temp.columns[j] = temp.columns[j] - temp.columns[i] * quotient;
        }
    }
    determinant = determinant * parity;

    return determinant;
}

template <typename T, int Size>
TVector<T, Size> TMatrix<T, Size>::operator*(const TVector<T, Size>& vec) const {
    TVector<T, Size> temp_vec;
    T temp_num = 0;

    for (int w = 0; w < Size; w++) {
        for (int k = 0; k < Size; k++)
            temp_num += columns[k][w] * vec[k];

        temp_vec[w] = temp_num;
        temp_num = 0;
    }

    return temp_vec;
}

template <typename T, int Size>
TMatrix<T, Size> TMatrix<T, Size>::insert_column(const TVector<T, Size>& vec, std::size_t column) const {
    assert(column < Size);
    TMatrix<T, Size> temp = *this;

    for (int i = 0; i < Size; i++)
        temp(i, column) = vec[i];

    return temp;
}

/*!
 * Funkcja wczytuje macierz:
 * Argumenty:
 * Strm - strumień wejściowy
 * Mac - wczytywana macierz
 * Zwraca:
 * referencję do Strm
 */
template <typename T, int Size>
std::istream& operator>>(std::istream& Strm, TMatrix<T, Size>& Mac) {
    for (int a = 0; a < Size; a++)
        for (int b = 0; b < Size; b++)
            Strm >> Mac(b, a);

    return Strm;
}

/*!
 * Funkcja wypisuje macierz:
 * Argumenty:
 * Strm - strumień wyjściowy
 * Mac - wypisywana macierz
 * Zwraca:
 * referencję do Strm
 */
template <typename T, int Size>
std::ostream& operator<<(std::ostream& Strm, const TMatrix<T, Size>& Mac) {
    for (int a = 0; a < Size; a++) {
        Strm << "\t";
        for (int b = 0; b < Size; b++)
            Strm << Mac(a, b) << "   ";
        Strm << std::endl;
    }

    return Strm;
}
