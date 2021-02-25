#pragma once

#include <array>
#include <cassert>
#include <cmath>
#include <iostream>

constexpr int size_of_TVec_3D = 3;
/*!
 * \brief modeluje pojęcie vectora
 * Szablon klasy modeluje pojęcie vectora dowolnego rozmiaru
 * i dowolnego typu
 */
template <typename T, int Size>
class TVector {
    /*! \brief Liczy wszystkie utworzone vectory 3D */
    static int all_vectors_3D;
    /*! \brief Liczy aktualnie istniejące vectory 3D */
    static int currently_vectors_3D;

    std::array<T, Size> components; /*! kolejne składowe vectora */
public:
    /*!
     * \brief Konsturuktor
     * Tworzy nowy obiekt TVector.
     * Zwiększa o jeden pola statyczne klasy, jeśli vector
     * ma Size równy 3.
     */
    TVector();
    /*!
     * \brief Konstruktor kopiujący
     * Kopiuje vector do obiektu, który wywołuje tę metodę.
     * Zwiększa o jeden pole currently_vectors_3D3D, jeśli vector
     * ma Size równy 3.
     * \param[in] vec - kopiowany vector
     */
    TVector(const TVector<T, Size>& vec);
    /*!
     * \brief Destruktor
     * Zmniejsza o jeden pole currently_vectors_3D3D, jeśli vector
     * ma Size równy 3.
     */
    ~TVector();

    /*!
     * \brief Odczytuje odpowiednią współrzędną vectora.
     * Metoda pozwala odczytać odpowiednią składową vectora.
     * \param[in] i - indeks składowej
     * \return i-tą składową vectora
     */
    T operator[](int i) const {
        assert(i < Size);
        return components[i];
    }
    /*!
     * \brief Wpisuje odpowiednią składową vectora
     * Metoda pozwala wpisać odpowiednią składową vectora.
     * \param[in] i - indeks składowej
     * \return referencję do i-tej składowej
     */
    T& operator[](int i) {
        assert(i < Size);
        return components[i];
    }

    /*!
     * \brief oblicza sumę dwóch vectorów
     * Metoda oblicza sumę dwóch vectorów.
     * \param[in] second - vector, który dodajemy
     * \return sumę dwóch vectorów
     */
    TVector<T, Size> operator+(const TVector<T, Size>& second) const;

    /*!
     * \brief Oblicza różnicę dwóch vectorów
     * Metoda oblicza różnicę dwóch vectorów.
     * \param[in] second - vectór, który odejmujemy
     * \return Result odejmowania
     */
    TVector<T, Size> operator-(const TVector<T, Size>& second) const;

    /*!
     * \brief Oblicza product skalarny
     * Metoda liczy product skalarny dwóch vectorów.
     * \param[in] second - second składnik iloczynu
     * \return Result mnożenia
     */
    T operator*(const TVector<T, Size>& second) const;
    /*!
     * \brief Oblicza product vectora przez liczbę
     * Metoda liczy product vectora przez liczbę
     * \param[in] number - number przez którą mnożymy
     * \return Result mnożenia
     */
    TVector<T, Size> operator*(T number) const;

    /*!
     * \brief Oblicza iloraz vectora przez liczbę
     * Metoda liczy iloraz vectora przez liczbę
     * \param[in] number - number przez którą dzielimy
     * \return Result dzielenia
     */
    TVector<T, Size> operator/(T number) const;
    /*!
     * \brief Oblicza długość vectora
     * Metoda oblicza długość vectora:
     * \return długość vectora
     */
    double lenght() const;

    /*!
     * \brief Zwraca łączną liczbę vectorów 3D
     * \retval lacznie_obiektow3D - pole klasy
     */
    static int return_all_vectors_3D() { return all_vectors_3D; }
    /*!
     * \brief Zwraca aktualną liczbę vectorów 3D
     * \retval aktualnie_obiektow3D - pole klasy
     */
    static int return_current_vectors_3D() { return currently_vectors_3D; }
};

template <typename T, int Size>
int TVector<T, Size>::all_vectors_3D = 0;

template <typename T, int Size>
int TVector<T, Size>::currently_vectors_3D = 0;

template <typename T, int Size>
TVector<T, Size>::TVector() {
    if (Size == 3) {
        ++all_vectors_3D;
        ++currently_vectors_3D;
    }
}

template <typename T, int Size>
TVector<T, Size>::TVector(const TVector<T, Size>& vec) : components(vec.components) {
    if (Size == 3) {
        ++currently_vectors_3D;
        ++all_vectors_3D;
    }
}

template <typename T, int Size>
TVector<T, Size>::~TVector() {
    if (Size == 3)
        --currently_vectors_3D;
}

template <typename T, int Size>
TVector<T, Size> TVector<T, Size>::operator+(const TVector<T, Size>& second) const {
    TVector<T, Size> Sum;

    for (int i = 0; i < Size; i++)
        Sum.components[i] = components[i] + second.components[i];

    return Sum;
}

template <typename T, int Size>
TVector<T, Size> TVector<T, Size>::operator-(const TVector<T, Size>& second) const {
    TVector<T, Size> difference;

    for (int i = 0; i < Size; i++)
        difference.components[i] = components[i] - second.components[i];

    return difference;
}

template <typename T, int Size>
T TVector<T, Size>::operator*(const TVector<T, Size>& second) const {
    T product = 0;

    for (int i = 0; i < Size; i++)
        product += components[i] * second.components[i];

    return product;
}

template <typename T, int Size>
TVector<T, Size> TVector<T, Size>::operator*(T number) const {
    TVector<T, Size> Result;

    for (int i = 0; i < Size; i++)
        Result.components[i] = components[i] * number;

    return Result;
}

template <typename T, int Size>
double TVector<T, Size>::lenght() const {
    double Result = 0;

    for (int i = 0; i < Size; i++)
        Result += components[i] * components[i];

    return sqrt(Result);
}

template <typename T, int Size>
TVector<T, Size> TVector<T, Size>::operator/(T number) const {
    TVector<T, Size> Result;

    for (int i = 0; i < Size; ++i)
        Result[i] = components[i] / number;

    return Result;
}

/*!
 * Funkcja wczytuje vector:
 * Argumenty:
 * Strm - strumień wejściowy
 * vec - wczytywany vector
 * Zwracana:
 * referencję do Strm
 */
template <typename T, int Size>
std::istream& operator>>(std::istream& Strm, TVector<T, Size>& vec) {
    for (int i = 0; i < Size; i++)
        Strm >> vec[i];

    return Strm;
}

/*!
 * Funkcja wczytuje vector:
 * Dane wejściowe:
 * Strm - strumień wyjściowy
 * vec - wypisywany vector
 * Wartość zwracana:
 * referencję do Strm
 */
template <typename T, int Size>
std::ostream& operator<<(std::ostream& Strm, const TVector<T, Size>& vec) {
    for (int i = 0; i < Size; i++)
        Strm << vec[i] << " ";

    Strm << std::endl;

    return Strm;
}
