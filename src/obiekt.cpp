#include "obiekt.hh"
#include <fstream>
#include <cmath>

obiekt::obiekt() {
    for(int i = 0; i < 3; ++i)
        przesuniecie[i] = 0;
    
    laczny_kat_obrotu = 0;
}

obiekt::obiekt(const std::string & nazwa_lok, const std::string & nazwa_glob) : 
                powierzchnia(nazwa_lok, nazwa_glob) {
    for(int i = 0; i < 3; ++i)
        przesuniecie[i] = 0;
    
    laczny_kat_obrotu = 0;
}

void obiekt::wczytaj_wspolrzedne() {
    std::ifstream read;
    read.open(plik_lokalny);
    if(!read.is_open())
        return;

    SWektor<double, 3> wiersz;
    wspolrzedne.clear();

    read >> wiersz;
    while(!read.eof()) {
        if(!read) {
            read.clear();
            while(read.get() != '\n');
        }
        else
            wspolrzedne.push_back(wiersz);
        
        read >> wiersz;
    }

    read.close();
}

void obiekt::wpisz_wspolrzedne_glob() {
    std::ofstream write;
    write.open(plik_z_punktami);
    if(!write.is_open())
        return;
    
    int licznik = 0;

    for(SWektor<double, 3> & i: wspolrzedne) {
        write << i;
        ++licznik;
        if(licznik == 4) {
            licznik = 0;
            write << "#\n\n";
        }
    }
    
    write.close();
}

void obiekt::macierz_obrotu(SMacierz<double, 3> & obrot, osie os_obrotu, double kat_obrotu) const {
    const double pi = acos(-1);

    int przejscie = 1, poczatek = 0;      //o ile pól przechodzimy w pętli for i od którego pola zaczynamy
    if(os_obrotu == X)
        poczatek = 1;
    else if(os_obrotu == Y)
        przejscie = 2;


    for(int i = 0; i < 3; ++i) {
        obrot(os_obrotu, i) = 0;
        obrot(i, os_obrotu) = 0;
    }
    obrot(os_obrotu, os_obrotu) = 1;

    obrot(poczatek,poczatek) = cos(pi*(kat_obrotu/180.0));
    obrot(poczatek+przejscie, poczatek+przejscie) = obrot(poczatek, poczatek);
    obrot(poczatek, poczatek+przejscie) = -sin(pi*(kat_obrotu/180.0));
    obrot(poczatek+przejscie, poczatek) = -obrot(poczatek, poczatek+przejscie);
}

void obiekt::ruch_na_wprost(double kat_wznoszenia, double odleglosc) {
    wczytaj_wspolrzedne();

    SWektor<double, 3> translacja;
    SMacierz<double, 3> obrot;

    for(int i = 1; i < 3; ++i)
        translacja[i] = 0;
    translacja[0] = odleglosc;

    macierz_obrotu(obrot, Z, laczny_kat_obrotu);
    translacja = obrot * translacja;            

    macierz_obrotu(obrot, X, kat_wznoszenia);
    translacja = obrot * translacja;

    macierz_obrotu(obrot, Y, kat_wznoszenia);
    translacja = obrot * translacja;

    for(SWektor<double, 3> &x : wspolrzedne)
        x = x + translacja;
    
    wpisz_wspolrzedne_glob();
}