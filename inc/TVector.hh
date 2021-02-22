#pragma once

#include <array>
#include <cassert>
#include <cmath>
#include <iostream>
/*!
 * \brief modeluje pojęcie Wektora
 * Szablon klasy modeluje pojęcie wektora dowolnego rozmiaru
 * i dowolnego typu
 */
template <typename Typ, int Rozmiar>
class TVector {
    /*! \brief Liczy wszystkie utworzone wektory 3D */
    static int lacznie_wektorow;
    /*! \brief Liczy aktualnie istniejące wektory 3D */
    static int aktualnie_wektorow;

    std::array<Typ, Rozmiar> skladowe; /*! kolejne składowe wektora */
public:
    /*!
     * \brief Konsturuktor
     * Tworzy nowy obiekt TVector.
     * Zwiększa o jeden pola statyczne klasy, jeśli wektor
     * ma rozmiar równy 3.
     */
    TVector();
    /*!
     * \brief Konstruktor kopiujący
     * Kopiuje wektor do obiektu, który wywołuje tę metodę.
     * Zwiększa o jeden pole aktualnie_wektorow3D, jeśli wektor
     * ma rozmiar równy 3.
     * \param[in] Wek - kopiowany wektor
     */
    TVector(const TVector<Typ, Rozmiar>& Wek);
    /*!
     * \brief Destruktor
     * Zmniejsza o jeden pole aktualnie_wektorow3D, jeśli wektor
     * ma rozmiar równy 3.
     */
    ~TVector();

    /*!
     * \brief Odczytuje odpowiednią współrzędną wektora.
     * Metoda pozwala odczytać odpowiednią składową wektora.
     * \param[in] i - indeks składowej
     * \return i-tą składową wektora
     */
    Typ operator[](int i) const {
        assert(i < Rozmiar);
        return skladowe[i];
    }
    /*!
     * \brief Wpisuje odpowiednią składową wektora
     * Metoda pozwala wpisać odpowiednią składową wektora.
     * \param[in] i - indeks składowej
     * \return referencję do i-tej składowej
     */
    Typ& operator[](int i) {
        assert(i < Rozmiar);
        return skladowe[i];
    }

    /*!
     * \brief oblicza sumę dwóch wektorów
     * Metoda oblicza sumę dwóch wektorów.
     * \param[in] drugi - wektor, który dodajemy
     * \return sumę dwóch wektorów
     */
    TVector<Typ, Rozmiar> operator+(const TVector<Typ, Rozmiar>& drugi) const;

    /*!
     * \brief Oblicza różnicę dwóch wektorów
     * Metoda oblicza różnicę dwóch wektorów.
     * \param[in] drugi - wektór, który odejmujemy
     * \return wynik odejmowania
     */
    TVector<Typ, Rozmiar> operator-(const TVector<Typ, Rozmiar>& drugi) const;

    /*!
     * \brief Oblicza iloczyn skalarny
     * Metoda liczy iloczyn skalarny dwóch wektorów.
     * \param[in] drugi - drugi składnik iloczynu
     * \return wynik mnożenia
     */
    Typ operator*(const TVector<Typ, Rozmiar>& drugi) const;
    /*!
     * \brief Oblicza iloczyn wektora przez liczbę
     * Metoda liczy iloczyn wektora przez liczbę
     * \param[in] liczba - liczba przez którą mnożymy
     * \return wynik mnożenia
     */
    TVector<Typ, Rozmiar> operator*(Typ liczba) const;

    /*!
     * \brief Oblicza iloraz wektora przez liczbę
     * Metoda liczy iloraz wektora przez liczbę
     * \param[in] liczba - liczba przez którą dzielimy
     * \return wynik dzielenia
     */
    TVector<Typ, Rozmiar> operator/(Typ liczba) const;
    /*!
     * \brief Oblicza długość wektora
     * Metoda oblicza długość wektora:
     * \return długość wektora
     */
    double dlugosc() const;

    /*!
     * \brief Zwraca łączną liczbę wektorów 3D
     * \retval lacznie_obiektow3D - pole klasy
     */
    static int lacznie_wektory() { return lacznie_wektorow; }
    /*!
     * \brief Zwraca aktualną liczbę wektorów 3D
     * \retval aktualnie_obiektow3D - pole klasy
     */
    static int aktualnie_wektory() { return aktualnie_wektorow; }
};

template <typename Typ, int Rozmiar>
int TVector<Typ, Rozmiar>::lacznie_wektorow = 0;

template <typename Typ, int Rozmiar>
int TVector<Typ, Rozmiar>::aktualnie_wektorow = 0;

template <typename Typ, int Rozmiar>
TVector<Typ, Rozmiar>::TVector() {
    if (Rozmiar == 3) {
        ++lacznie_wektorow;
        ++aktualnie_wektorow;
    }
}

template <typename Typ, int Rozmiar>
TVector<Typ, Rozmiar>::TVector(const TVector<Typ, Rozmiar>& Wek) : skladowe(Wek.skladowe) {
    if (Rozmiar == 3) {
        ++aktualnie_wektorow;
        ++lacznie_wektorow;
    }
}

template <typename Typ, int Rozmiar>
TVector<Typ, Rozmiar>::~TVector() {
    if (Rozmiar == 3)
        --aktualnie_wektorow;
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
 * Funkcja wczytuje wektor:
 * Argumenty:
 * Strm - strumień wejściowy
 * Wek - wczytywany Wektor
 * Zwracana:
 * referencję do Strm
 */
template <typename Typ, int Rozmiar>
std::istream& operator>>(std::istream& Strm, TVector<Typ, Rozmiar>& Wek) {
    for (int i = 0; i < Rozmiar; i++)
        Strm >> Wek[i];

    return Strm;
}

/*!
 * Funkcja wczytuje wektor:
 * Dane wejściowe:
 * Strm - strumień wyjściowy
 * Wek - wypisywany wektor
 * Wartość zwracana:
 * referencję do Strm
 */
template <typename Typ, int Rozmiar>
std::ostream& operator<<(std::ostream& Strm, const TVector<Typ, Rozmiar>& Wek) {
    for (int i = 0; i < Rozmiar; i++)
        Strm << Wek[i] << " ";

    Strm << std::endl;

    return Strm;
}