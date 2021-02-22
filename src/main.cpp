#include "stage.hh"

using namespace std;

void stream_fix(istream& Strm) {
    Strm.clear();
    while (Strm.get() != '\n')
        ;
}

void obiects_info() {
    std::cout << "\n\tAktualna liczba obiektow vector 3D: " << TVector<double, 3>::aktualnie_vectory() << "\n";
    std::cout << "\tLaczna liczba obiektow vector 3D: " << TVector<double, 3>::lacznie_vectory() << "\n";
}

void obsluga_sceny() {
    stage main_stage;
    main_stage.add_body("dat/body.pow", "dat/body1.pow");
    main_stage.add_left_motor("dat/left_motor.dat", "dat/left_motor1.dat");
    main_stage.add_right_motor("dat/right_motor.dat", "dat/right_motor1.dat");

    main_stage.add_cuboid("dat/cuboid.dat", "dat/cuboid1.dat");
    main_stage.add_bar("dat/bar.dat", "dat/bar1.dat");
    main_stage.add_rectangle("dat/rectangle.dat", "dat/rectangle1.dat");

    main_stage.add_bottom("dat/bottom.pow", "dat/bottom1.pow");
    main_stage.add_water("dat/water_surface.dat", "dat/water_surface1.dat");
    main_stage.inicjalizuj();

    char choice = 'm';
    double angle;
    double distance;

    while (choice != 'k') {
        switch (choice) {
        case 'r':
            cout << "\tPodaj wartosc anglea (wznoszenia/opadania) w stopniach.\n";
            cout << "\tWartosc anglea> ";
            cin >> angle;
            cin.get();
            if (!cin) {
                stream_fix(cin);
                break;
            }
            cout << "\nPodaj wartosc distancei, na ktora ma sie przemiescic dron.\n";
            cout << "\tWartosc distancei> ";
            cin >> distance;
            cin.get();
            if (!cin) {
                stream_fix(cin);
                break;
            }
            main_stage.ruch_prosto(angle, distance);
            break;
        case 'o':
            cout << "\tPodaj wartosc anglea w stopniach.\n";
            cout << "\tWartosc anglea> ";
            cin >> angle;
            cin.get();
            if (!cin) {
                stream_fix(cin);
                break;
            }
            main_stage.rotation(angle);
            break;
        case 'm':
            cout << "\tr - zadaj ruch na wprost\n";
            cout << "\to - zadaj zmiane orientacji\n";
            cout << "\tm - wyswietl menu\n\n";
            cout << "\tk - koniec dzialania programu\n";
            break;
        }
        obiects_info();
        cout << "\nTwoj choice, m - menu> ";
        cin >> choice;
    }
}

int main() {
    obsluga_sceny();
    obiects_info();
}
