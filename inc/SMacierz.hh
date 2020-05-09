#ifndef SMACIERZ_HH
#define SMACIERZ_HH

#include "SWektor.hh"
#include <iostream>
#include <cmath>
#include <algorithm>
#include <cassert>


/*!
 * Szablon klasy modeluje pojęcie macierzy.
 */
template<typename Typ, int Rozmiar>
class SMacierz {

    SWektor<Typ, Rozmiar> kolumny[Rozmiar]; /*! kolejne kolumny macierzy */

    /*!
     * Metoda zamienia kolumny w macierzy.
     * Argumenty:
     * a - indeks kolumny do zamiany
     * b - indeks kolumny do zamiany
     * Brak wartości zwracanej
     */
    void zamien_kolumny(unsigned int a, unsigned int b);
  public:

    /*!
     * Metoda pozwala wpisać odpowiednią składową do macierzy.
     * Argumenty:
     * a - indeks wiersza macierzy
     * b - indeks kolumny macierzy
     * Zwraca:
     * referencję do składowej (a,b)
     */
    Typ & operator ()(unsigned int a, unsigned int b);
    /*!
     * Metoda pozwala odczytać odpowiednią składową macierzy.
     * Argumenty:
     * a - indeks składowej
     * b - indeks kolumny macierzy
     * Zwraca:
     * składową (a,b)
     */
    Typ operator ()(unsigned int a, unsigned int b) const;

    /*!
     * Metoda oblicza wyznacznik macierzy.
     * Argumenty:   Brak
     * Zwraca:
     * wyznacznik macierzy
     */
    Typ wyznacznik() const;

    /*!
     * Metoda mnoży macierz przez wektor.
     * Argumenty:
     * Wek - wektor przez, który mnożymy
     * Zwraca:
     * wektor - iloczyn macierzy i wektora
     */
    SWektor<Typ, Rozmiar> operator *(const SWektor<Typ, Rozmiar> & Wek) const;

    /*!
     * Metoda wstawia kolumnę do macierzy.
     * Argumenty:
     * Wek - wektor który wstawiamy
     * kolumna - indeks zamienianej kolumny
     * Zwraca:
     * macierz po zamianie
     */
    SMacierz<Typ, Rozmiar> wstaw_kolumne(const SWektor<Typ, Rozmiar> & Wek, unsigned int kolumna) const;
};

template<typename Typ, int Rozmiar>
void SMacierz<Typ, Rozmiar>::zamien_kolumny(unsigned int a, unsigned int b) {

    if(a < Rozmiar && b < Rozmiar)
        std::swap(kolumny[a], kolumny[b]);
}

template<typename Typ, int Rozmiar>
Typ & SMacierz<Typ, Rozmiar>::operator ()(unsigned int a, unsigned int b) {

    assert(a < Rozmiar && b < Rozmiar);
    return kolumny[b][a]; 
}

template<typename Typ, int Rozmiar>
Typ SMacierz<Typ, Rozmiar>::operator ()(unsigned int a, unsigned int b) const {

    assert(a < Rozmiar && b < Rozmiar);
    return kolumny[b][a];
}


template<typename Typ, int Rozmiar>
Typ SMacierz<Typ, Rozmiar>::wyznacznik() const {

    SMacierz<Typ, Rozmiar> pom = *this;
    double parzystosc = 1;           //parzystosc zamian kolumn wpływa na znak wyznacznika
    int nr_do_zam = 0;              //indeks kolumny z która ma zostać zamieniona kolumna i
    Typ iloraz;                  //zmienna pomocnicza do obliczania ilorazu dwóch kolumn
    Typ wyznacznik = 1;

    for(int i = 0; i < Rozmiar; i++) {               //kolejne indeksy kolumn

        nr_do_zam = i+1;
       
        while(fabs(pom(i,i)) < pow(0.1, 12)) {          //gdy pom(i,i)==0
        
            if(nr_do_zam == Rozmiar)            //wyznacznik równy zero gdy w pierwszej kolumnie same zera
                return 0.0;

            else if(!(fabs(pom(i, nr_do_zam)) < pow(0.1, 12))) {  //gdy wiersz do zam nie ma 0 na pierwszej ważnej pozycji
            
                pom.zamien_kolumny(nr_do_zam, i);
                parzystosc = -parzystosc;
            }
            nr_do_zam++;
        }
        wyznacznik = wyznacznik * pom(i,i);

        for(int j = i+1; j < Rozmiar; j++) {             //kolejne kolumny od ktorych odejmujemy kolumne i
        
            iloraz = pom(i,j) / pom(i,i);                   
            pom.kolumny[j] = pom.kolumny[j] - pom.kolumny[i] * iloraz;
        }
    }
    wyznacznik = wyznacznik * parzystosc;

    return wyznacznik;
}


template<typename Typ, int Rozmiar>
SWektor<Typ, Rozmiar> SMacierz<Typ, Rozmiar>::operator *(const SWektor<Typ, Rozmiar> &Wek) const {

    SWektor<Typ, Rozmiar> pom;
    Typ skl_pom;
    skl_pom = 0;

    for(int w = 0; w < Rozmiar; w++)
    {
        for(int k = 0; k < Rozmiar; k++)
            skl_pom = skl_pom + kolumny[k][w] * Wek[k];

        pom[w] = skl_pom;
        skl_pom = 0;  
    }

    return pom;
}

template<typename Typ, int Rozmiar>
SMacierz<Typ, Rozmiar> SMacierz<Typ, Rozmiar>::wstaw_kolumne(const SWektor<Typ, Rozmiar> & Wek, unsigned int kolumna) const {

    assert(kolumna < Rozmiar);
    SMacierz<Typ, Rozmiar> pom = *this;

    for(int i = 0; i < Rozmiar; i++)
        pom(i, kolumna) = Wek[i];
    
    return pom;
}



/*!
 * Funkcja wczytuje macierz:
 * Argumenty:
 * Strm - strumień wejściowy
 * Mac - wczytywana macierz
 * Zwraca:
 * referencję do Strm
 */
template<typename Typ, int Rozmiar>
std::istream & operator >> (std::istream &Strm, SMacierz<Typ, Rozmiar> &Mac) {

    for(int a = 0; a < Rozmiar; a++)
        for(int b = 0; b < Rozmiar; b++)
            Strm >> Mac(b,a);                 //bo macierz Mac w pliku to macierz transponowana
    
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
template<typename Typ, int Rozmiar>
std::ostream & operator << (std::ostream &Strm, const SMacierz<Typ, Rozmiar> &Mac) {
    
    for(int a = 0; a < Rozmiar; a++)
    {
        Strm << "\t";
        for(int b = 0; b < Rozmiar; b++)
            Strm << Mac(a,b) << "   ";
        Strm << std::endl;
    }
    
    return Strm;
}


#endif
