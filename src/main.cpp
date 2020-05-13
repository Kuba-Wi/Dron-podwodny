#include "scena.hh"

using namespace std;

void naprawa_strumienia(istream & Strm) {
    Strm.clear();
    while(Strm.get() != '\n');
}

void obsluga_sceny() {
    scena glowna;
    glowna.dodaj_drona("dat/prostopadloscian.pow", "dat/prostopadloscian1.pow");
    glowna.dodaj_dno("dat/dno.pow", "dat/dno1.pow");
    glowna.inicjalizuj();

    char wybor = 'm';
    double kat;
    double odleglosc;

    while(wybor != 'k') {

        switch(wybor) {
            case 'r':
                cout << "\tPodaj wartosc kata (wznoszenia/opadania) w stopniach.\n";
                cout << "\tWartosc kata> ";
                cin >> kat;
                cin.get();
                if(!cin) {
                    naprawa_strumienia(cin);
                    break;
                }
                cout << "\nPodaj wartosc odleglosci, na ktora ma sie przemiescic dron.\n";
                cout << "\tWartosc odleglosci> ";
                cin >> odleglosc;
                cin.get();
                if(!cin) {
                    naprawa_strumienia(cin);
                    break;
                }
                glowna.ruch_prosto(kat, odleglosc);
                break;
            case 'o':
                cout << "\tPodaj wartosc kata w stopniach.\n";
                cout << "\tWartosc kata> ";
                cin >> kat;
                cin.get();
                if(!cin) {
                    naprawa_strumienia(cin);
                    break;
                }
                glowna.obrot(kat);
                break;
            case 'm':
                cout << "\tr - zadaj ruch na wprost\n";
                cout << "\to - zadaj zmiane orientacji\n";
                cout << "\tm - wyswietl menu\n\n";
                cout << "\tk - koniec dzialania programu\n";
                break;
        }
        cout << "\nTwoj wybor, m - menu> ";
        cin >> wybor;
    }

}

int main() {

  obsluga_sceny();


}