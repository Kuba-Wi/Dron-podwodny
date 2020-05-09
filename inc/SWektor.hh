#ifndef SWEKTOR_HH
#define SWEKTOR_HH

#include <iostream>
#include <cassert>
#include <cmath>
/*!
 * Szablon klasy modeluje pojęcie Wektora
 */
template<typename Typ, int Rozmiar>
class SWektor {

    Typ skladowe[Rozmiar]; /*! kolejne składowe wektora */
  public:
    /*!
     * Metoda pozwala odczytać odpowiednią składową wektora.
     * Argumenty:
     * i - indeks składowej
     * Zwraca:
     * i-tą składową wektora
     */
    Typ operator [](int i) const { assert(i < Rozmiar); return skladowe[i]; }
    /*!
     * Metoda pozwala wpisać odpowiednią składową wektora.
     * Argumenty:
     * i - indeks składowej
     * Zwraca:
     * referencję do i-tej składowej
     */
    Typ & operator [](int i) { assert(i < Rozmiar); return skladowe[i]; }

    /*!
     * Metoda oblicza sumę dwóch wektorów.
     * Argumenty:
     * drugi - wektor, który dodajemy
     * Zwraca:
     * sumę dwóch wektorów
     */
    SWektor<Typ, Rozmiar> operator +(const SWektor<Typ, Rozmiar> & drugi) const;

    /*!
     * Metoda oblicza różnicę dwóch wektorów.
     * Argumenty:
     * drugi - wektór, który odejmujemy
     * Zwraca:
     * wynik odejmowania
     */
    SWektor<Typ, Rozmiar> operator -(const SWektor<Typ, Rozmiar> & drugi) const;

    /*!
     * Metoda liczy iloczyn skalarny dwóch wektorów.
     * Argumenty:
     * drugi - drugi składnik iloczynu
     * Zwraca:
     * wynik mnożenia
     */
    Typ operator *(const SWektor<Typ, Rozmiar> & drugi) const;
    /*!
     * Metoda liczy iloczyn wektora przez liczbę
     * Argumenty:
     * liczba - liczba przez którą mnożymy
     * Zwraca:
     * wynik mnożenia
     */
    SWektor<Typ, Rozmiar> operator *(Typ liczba) const;

    /*!
     * Metoda oblicza długość wektora:
     * Argumenty:   Brak
     * Zwraca:  długość wektora
     */
    double dlugosc() const;
};


template<typename Typ, int Rozmiar>
SWektor<Typ, Rozmiar> SWektor<Typ, Rozmiar>::operator +(const SWektor<Typ, Rozmiar> & drugi) const {
    SWektor<Typ, Rozmiar> Suma;

    for(int i = 0; i < Rozmiar; i++)
        Suma.skladowe[i] = skladowe[i] + drugi.skladowe[i];
    
    return Suma;
}

template<typename Typ, int Rozmiar>
SWektor<Typ, Rozmiar> SWektor<Typ, Rozmiar>::operator -(const SWektor<Typ, Rozmiar> & drugi) const {
    SWektor<Typ, Rozmiar> Roznica;

    for (int i = 0; i < Rozmiar; i++)
        Roznica.skladowe[i] = skladowe[i] - drugi.skladowe[i];
    
    return Roznica;
}

template<typename Typ, int Rozmiar>
Typ SWektor<Typ, Rozmiar>::operator *(const SWektor<Typ, Rozmiar> & drugi) const {
    Typ iloczyn = 0;

    for (int i = 0; i < Rozmiar; i++)
        iloczyn += skladowe[i] * drugi.skladowe[i];
    
    return iloczyn;
}

template<typename Typ, int Rozmiar>
SWektor<Typ, Rozmiar> SWektor<Typ, Rozmiar>::operator *(Typ liczba) const {
    SWektor<Typ, Rozmiar> Wynik;

    for (int i = 0; i < Rozmiar; i++)
        Wynik.skladowe[i] = skladowe[i] * liczba;

    return Wynik;
}

template<typename Typ, int Rozmiar>
double SWektor<Typ, Rozmiar>::dlugosc() const {
    double Wynik = 0;

    for(int i = 0; i < Rozmiar; i++)
        Wynik += skladowe[i] * skladowe[i];
    
    return sqrt(Wynik);
}




/*!
 * Funkcja wczytuje wektor:
 * Argumenty:
 * Strm - strumień wejściowy
 * Wek - wczytywany Wektor
 * Zwracana:
 * referencję do Strm
 */
template<typename Typ, int Rozmiar>
std::istream& operator >> (std::istream &Strm, SWektor<Typ, Rozmiar> &Wek) {

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
template<typename Typ, int Rozmiar>
std::ostream& operator << (std::ostream &Strm, const SWektor<Typ, Rozmiar> &Wek) {

    for(int i = 0; i < Rozmiar; i++)
        Strm << Wek[i] << "   ";
    
    Strm << std::endl;

    return Strm;
}

#endif