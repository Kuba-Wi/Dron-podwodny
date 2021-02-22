#pragma once

#include <array>
#include <cassert>
#include <cmath>
#include <iostream>
/*!
 * \brief modeluje pojęcie vectora
 * Szablon klasy modeluje pojęcie vectora dowolnego rozmiaru
 * i dowolnego typu
 */
template <typename Typ, int Rozmiar>
class TVector {
    /*! \brief Liczy wszystkie utworzone vectory 3D */
    static int lacznie_vectorow;
    /*! \brief Liczy aktualnie istniejące vectory 3D */
    static int aktualnie_vectorow;

    std::array<Typ, Rozmiar> skladowe; /*! kolejne składowe vectora */
public:
    /*!
     * \brief Konsturuktor
     * Tworzy nowy obiekt TVector.
     * Zwiększa o jeden pola statyczne klasy, jeśli vector
     * ma rozmiar równy 3.
     */
    TVector();
    /*!
     * \brief Konstruktor kopiujący
     * Kopiuje vector do obiektu, który wywołuje tę metodę.
     * Zwiększa o jeden pole aktualnie_vectorow3D, jeśli vector
     * ma rozmiar równy 3.
     * \param[in] vec - kopiowany vector
     */
    TVector(const TVector<Typ, Rozmiar>& vec);
    /*!
     * \brief Destruktor
     * Zmniejsza o jeden pole aktualnie_vectorow3D, jeśli vector
     * ma rozmiar równy 3.
     */
    ~TVector();

    /*!
     * \brief Odczytuje odpowiednią współrzędną vectora.
     * Metoda pozwala odczytać odpowiednią składową vectora.
     * \param[in] i - indeks składowej
     * \return i-tą składową vectora
     */
    Typ operator[](int i) const {
        assert(i < Rozmiar);
        return skladowe[i];
    }
    /*!
     * \brief Wpisuje odpowiednią składową vectora
     * Metoda pozwala wpisać odpowiednią składową vectora.
     * \param[in] i - indeks składowej
     * \return referencję do i-tej składowej
     */
    Typ& operator[](int i) {
        assert(i < Rozmiar);
        return skladowe[i];
    }

    /*!
     * \brief oblicza sumę dwóch vectorów
     * Metoda oblicza sumę dwóch vectorów.
     * \param[in] drugi - vector, który dodajemy
     * \return sumę dwóch vectorów
     */
    TVector<Typ, Rozmiar> operator+(const TVector<Typ, Rozmiar>& drugi) const;

    /*!
     * \brief Oblicza różnicę dwóch vectorów
     * Metoda oblicza różnicę dwóch vectorów.
     * \param[in] drugi - vectór, który odejmujemy
     * \return wynik odejmowania
     */
    TVector<Typ, Rozmiar> operator-(const TVector<Typ, Rozmiar>& drugi) const;

    /*!
     * \brief Oblicza iloczyn skalarny
     * Metoda liczy iloczyn skalarny dwóch vectorów.
     * \param[in] drugi - drugi składnik iloczynu
     * \return wynik mnożenia
     */
    Typ operator*(const TVector<Typ, Rozmiar>& drugi) const;
    /*!
     * \brief Oblicza iloczyn vectora przez liczbę
     * Metoda liczy iloczyn vectora przez liczbę
     * \param[in] liczba - liczba przez którą mnożymy
     * \return wynik mnożenia
     */
    TVector<Typ, Rozmiar> operator*(Typ liczba) const;

    /*!
     * \brief Oblicza iloraz vectora przez liczbę
     * Metoda liczy iloraz vectora przez liczbę
     * \param[in] liczba - liczba przez którą dzielimy
     * \return wynik dzielenia
     */
    TVector<Typ, Rozmiar> operator/(Typ liczba) const;
    /*!
     * \brief Oblicza długość vectora
     * Metoda oblicza długość vectora:
     * \return długość vectora
     */
    double dlugosc() const;

    /*!
     * \brief Zwraca łączną liczbę vectorów 3D
     * \retval lacznie_obiektow3D - pole klasy
     */
    static int lacznie_vectory() { return lacznie_vectorow; }
    /*!
     * \brief Zwraca aktualną liczbę vectorów 3D
     * \retval aktualnie_obiektow3D - pole klasy
     */
    static int aktualnie_vectory() { return aktualnie_vectorow; }
};

template <typename Typ, int Rozmiar>
int TVector<Typ, Rozmiar>::lacznie_vectorow = 0;

template <typename Typ, int Rozmiar>
int TVector<Typ, Rozmiar>::aktualnie_vectorow = 0;

template <typename Typ, int Rozmiar>
TVector<Typ, Rozmiar>::TVector() {
    if (Rozmiar == 3) {
        ++lacznie_vectorow;
        ++aktualnie_vectorow;
    }
}

template <typename Typ, int Rozmiar>
TVector<Typ, Rozmiar>::TVector(const TVector<Typ, Rozmiar>& vec) : skladowe(vec.skladowe) {
    if (Rozmiar == 3) {
        ++aktualnie_vectorow;
        ++lacznie_vectorow;
    }
}

template <typename Typ, int Rozmiar>
TVector<Typ, Rozmiar>::~TVector() {
    if (Rozmiar == 3)
        --aktualnie_vectorow;
}

template <typename Typ, int Rozmiar>
TVector<Typ, Rozmiar> TVector<Typ, Rozmiar>::operator+(const TVector<Typ, Rozmiar>& drugi) const {
    TVector<Typ, Rozmiar> Suma;

    for (int i = 0; i < Rozmiar; i++)
        Suma.skladowe[i] = skladowe[i] + drugi.skladowe[i];

    return Suma;
}

template <typename Typ, int Rozmiar>
TVector<Typ, Rozmiar> TVector<Typ, Rozmiar>::operator-(const TVector<Typ, Rozmiar>& drugi) const {
    TVector<Typ, Rozmiar> Roznica;

    for (int i = 0; i < Rozmiar; i++)
        Roznica.skladowe[i] = skladowe[i] - drugi.skladowe[i];

    return Roznica;
}

template <typename Typ, int Rozmiar>
Typ TVector<Typ, Rozmiar>::operator*(const TVector<Typ, Rozmiar>& drugi) const {
    Typ iloczyn = 0;

    for (int i = 0; i < Rozmiar; i++)
        iloczyn += skladowe[i] * drugi.skladowe[i];

    return iloczyn;
}

template <typename Typ, int Rozmiar>
TVector<Typ, Rozmiar> TVector<Typ, Rozmiar>::operator*(Typ liczba) const {
    TVector<Typ, Rozmiar> Wynik;

    for (int i = 0; i < Rozmiar; i++)
        Wynik.skladowe[i] = skladowe[i] * liczba;

    return Wynik;
}

template <typename Typ, int Rozmiar>
double TVector<Typ, Rozmiar>::dlugosc() const {
    double Wynik = 0;

    for (int i = 0; i < Rozmiar; i++)
        Wynik += skladowe[i] * skladowe[i];

    return sqrt(Wynik);
}

template <typename Typ, int Rozmiar>
TVector<Typ, Rozmiar> TVector<Typ, Rozmiar>::operator/(Typ liczba) const {
    TVector<Typ, Rozmiar> Wynik;

    for (int i = 0; i < Rozmiar; ++i)
        Wynik[i] = skladowe[i] / liczba;

    return Wynik;
}

/*!
 * Funkcja wczytuje vector:
 * Argumenty:
 * Strm - strumień wejściowy
 * vec - wczytywany vector
 * Zwracana:
 * referencję do Strm
 */
template <typename Typ, int Rozmiar>
std::istream& operator>>(std::istream& Strm, TVector<Typ, Rozmiar>& vec) {
    for (int i = 0; i < Rozmiar; i++)
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
template <typename Typ, int Rozmiar>
std::ostream& operator<<(std::ostream& Strm, const TVector<Typ, Rozmiar>& vec) {
    for (int i = 0; i < Rozmiar; i++)
        Strm << vec[i] << " ";

    Strm << std::endl;

    return Strm;
}
