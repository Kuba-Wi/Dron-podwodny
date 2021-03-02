#include "stage.hh"
#include "lacze_do_gnuplota.hh"

using namespace std;

void stream_fix(istream& Strm) {
    Strm.clear();
    while (Strm.get() != '\n')
        ;
}

void obiects_info() {
    std::cout << "\n\tCurrent number of vector 3D obiects: " << TVector<double, 3>::return_current_vectors_3D() << "\n";
    std::cout << "\tCombined number of vector 3D obiects: " << TVector<double, 3>::return_all_vectors_3D() << "\n";
}

void stage_management() {
    PzG::LaczeDoGNUPlota link;
    stage main_stage(link);
    main_stage.add_body("../dat/body.pow", "../dat/body1.pow");
    main_stage.add_left_motor("../dat/left_motor.dat", "../dat/left_motor1.dat");
    main_stage.add_right_motor("../dat/right_motor.dat", "../dat/right_motor1.dat");

    main_stage.add_cuboid("../dat/cuboid.dat", "../dat/cuboid1.dat");
    main_stage.add_bar("../dat/bar.dat", "../dat/bar1.dat");
    main_stage.add_rectangle("../dat/rectangle.dat", "../dat/rectangle1.dat");

    main_stage.add_bottom("../dat/bottom.pow", "../dat/bottom1.pow");
    main_stage.add_water("../dat/water_surface.dat", "../dat/water_surface1.dat");
    main_stage.initialize();

    char choice = 'm';
    double angle;
    double distance;

    while (choice != 'q') {
        switch (choice) {
        case 'g':
            cout << "\tSet angle of rise/descent in degrees.\n";
            cout << "\tAngle value> ";
            cin >> angle;
            cin.get();
            if (!cin) {
                stream_fix(cin);
                break;
            }
            cout << "\nSet distance on which drone will move.\n";
            cout << "\tDistance value> ";
            cin >> distance;
            cin.get();
            if (!cin) {
                stream_fix(cin);
                break;
            }
            main_stage.move_ahead(angle, distance);
            break;
        case 'r':
            cout << "\tSet angle in degrees.\n";
            cout << "\tAngle value> ";
            cin >> angle;
            cin.get();
            if (!cin) {
                stream_fix(cin);
                break;
            }
            main_stage.rotation(angle);
            break;
        case 'm':
            cout << "\tg - go ahead\n";
            cout << "\tr - roate\n";
            cout << "\tm - menu\n\n";
            cout << "\tq - quit\n";
            break;
        }
        obiects_info();
        cout << "\nYour choice, m - menu> ";
        cin >> choice;
    }
}

int main() {
    stage_management();
    obiects_info();
}
