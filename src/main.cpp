#include "stage.hh"

using namespace std;

void naprawa_strumienia(istream& Strm) {
    Strm.clear();
    while (Strm.get() != '\n')
        ;
}

void inf_o_obiektach() {
    std::cout << "\n\tAktualna liczba obiektow wektor 3D: " << TVector<double, 3>::aktualnie_wektory() << "\n";
    std::cout << "\tLaczna liczba obiektow wektor 3D: " << TVector<double, 3>::lacznie_wektory() << "\n";
}

void obsluga_sceny() {
    stage glowna;
    glowna.add_body("dat/body.pow", "dat/body1.pow");
    glowna.add_left_motor("dat/left_motor.dat", "dat/left_motor1.dat");
    glowna.add_right_motor("dat/right_motor.dat", "dat/right_motor1.dat");

    glowna.add_cuboid("dat/cuboid.dat", "dat/cuboid1.dat");
    glowna.add_bar("dat/bar.dat", "dat/bar1.dat");
    glowna.dodaj_rectangle("dat/rectangle.dat", "dat/rectangle1.dat");

    glowna.dodaj_bottom("dat/bottom.pow", "dat/bottom1.pow");
    glowna.add_water("dat/water_surface.dat", "dat/water_surface1.dat");
    glowna.inicjalizuj();

    char wybor = 'm';
    double kat;
    double odleglosc;

    while (wybor != 'k') {
        switch (wybor) {
        case 'r':
            cout << "\tPodaj wartosc kata (wznoszenia/opadania) w stopniach.\n";
            cout << "\tWartosc kata> ";
            cin >> kat;
            cin.get();
            if (!cin) {
                naprawa_strumienia(cin);
                break;
            }
            cout << "\nPodaj wartosc odleglosci, na ktora ma sie przemiescic dron.\n";
            cout << "\tWartosc odleglosci> ";
            cin >> odleglosc;
            cin.get();
            if (!cin) {
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
            if (!cin) {
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
        inf_o_obiektach();
        cout << "\nTwoj wybor, m - menu> ";
        cin >> wybor;
    }
}

int main() {
    obsluga_sceny();
    inf_o_obiektach();
}
