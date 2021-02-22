#include "hexagon.hh"
#include <cmath>
#include <fstream>

void hexagon::macierz_obrotu_x(TMatrix<double, 3>& obrot, double kat_obrotu) const {
    const double pi = acos(-1);

    obrot(0, 1) = 0;
    obrot(0, 2) = 0;
    obrot(1, 0) = 0;
    obrot(2, 0) = 0;

    obrot(0, 0) = 1;

    obrot(1, 1) = cos(pi * (kat_obrotu / 180.0));
    obrot(2, 2) = obrot(1, 1);
    obrot(2, 1) = sin(pi * (kat_obrotu / 180.0));
    obrot(1, 2) = -obrot(2, 1);
}

void hexagon::ruch_lokalny() {
    TMatrix<double, 3> mac_obrotu;

    laczny_kat_obrotu += 10;
    while (laczny_kat_obrotu >= 360.0)
        laczny_kat_obrotu -= 360.0;
    while (laczny_kat_obrotu <= -360.0)
        laczny_kat_obrotu += 360.0;

    macierz_obrotu_x(mac_obrotu, laczny_kat_obrotu);

    obrot(mac_obrotu);
    ruch_na_wprost(przesuniecie);
}
