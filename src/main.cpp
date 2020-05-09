#include "scena.hh"

using namespace std;

int main() {

    scena proba;

    proba.dodaj_drona("dat/prostopadloscian.pow", "dat/prostopadloscian1.pow");
    proba.inicjalizuj();
    proba.rysuj();
/*
    PzG::LaczeDoGNUPlota Lacze;
    Lacze.DodajNazwePliku("dat/prostopadloscian.pow");
    Lacze.ZmienTrybRys(PzG::TR_3D);
    Lacze.Inicjalizuj();
    Lacze.Rysuj();
*/
    char c;
    cout << "Nacisnij ENTER, aby zakonczyc ... " << flush;
    cin >> noskipws >> c;
}