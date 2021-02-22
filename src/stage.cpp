#include "stage.hh"
#include <cmath>
#include <iostream>

bool stage::kolizja_bottom() const {
    return (fabs(dron_stage.return_location()[2] - bottom.zwroc_z()) <= dron_stage.return_lenghts()[2]);
}

bool stage::wynurzenie() const {
    return (fabs(dron_stage.return_location()[2] - woda.zwroc_z()) <= dron_stage.return_lenghts()[2] - 20);
}

bool stage::kolizja() const {
    TVector<double, 3> dlugosci_drona = dron_stage.return_lenghts();
    TVector<double, 3> srodek_drona = dron_stage.return_location();
    TVector<double, 3> dlugosci_przeszkody;
    TVector<double, 3> distancei;

    bool jest_kolizja = false;

    for (auto& przeszkoda : lista_przeszkod) {
        dlugosci_przeszkody = przeszkoda->return_lenght_halves();
        distancei = srodek_drona - przeszkoda->location();

        for (int i = 0; i < 3; ++i) {
            jest_kolizja = (fabs(distancei[i]) <= (dlugosci_przeszkody[i] + dlugosci_drona[i]));
            if (!jest_kolizja) {
                break;
            }
        }
        if (jest_kolizja) {
            return true;
        }
    }
    return false;
}

void stage::lacze_dodaj_plik(const std::string& file_name) {
    Lacze.DodajNazwePliku(file_name.c_str());
}

void stage::add_bottom(const std::string& local_name, const std::string& global_name) {
    bottom.dodaj_plik_lok(local_name);
    bottom.dodaj_plik_glob(global_name);

    bottom.wczytaj_lok();

    lacze_dodaj_plik(global_name);
}

void stage::add_water(const std::string& local_name, const std::string& global_name) {
    woda.dodaj_plik_lok(local_name);
    woda.dodaj_plik_glob(global_name);

    woda.wczytaj_lok();

    lacze_dodaj_plik(global_name);
}

void stage::add_body(const std::string& local_name, const std::string& global_name) {
    dron_stage.add_files_body(local_name, global_name);

    lacze_dodaj_plik(global_name);
}

void stage::add_left_motor(const std::string& local_name, const std::string& global_name) {
    dron_stage.add_files_left_motor(local_name, global_name);

    lacze_dodaj_plik(global_name);
}

void stage::add_right_motor(const std::string& local_name, const std::string& global_name) {
    dron_stage.add_files_right_motor(local_name, global_name);

    lacze_dodaj_plik(global_name);
}

void stage::dodaj_przeszkode(const std::string& local_name, const std::string& global_name) {
    lista_przeszkod.back()->dodaj_plik_lok(local_name);
    lista_przeszkod.back()->dodaj_plik_glob(global_name);

    lista_przeszkod.back()->initialize_obiekt();

    lacze_dodaj_plik(global_name);
}

void stage::add_cuboid(const std::string& local_name, const std::string& global_name) {
    lista_przeszkod.push_back(std::make_shared<cuboid>());

    dodaj_przeszkode(local_name, global_name);
}

void stage::add_bar(const std::string& local_name, const std::string& global_name) {
    lista_przeszkod.push_back(std::make_shared<bar>());

    dodaj_przeszkode(local_name, global_name);
}

void stage::add_rectangle(const std::string& local_name, const std::string& global_name) {
    lista_przeszkod.push_back(std::make_shared<rectangle>());

    dodaj_przeszkode(local_name, global_name);
}

void stage::inicjalizuj() {
    Lacze.ZmienTrybRys(PzG::TR_3D);
    Lacze.Inicjalizuj();
    dron_stage.initialize_drone();
    rysuj();
}

void stage::ruch_prosto(double rising_angle, double distance) {
    int kwant = 250;
    for (int i = 0; i < kwant; ++i) {
        dron_stage.move_ahead(rising_angle, distance / double(kwant));
        if (kolizja() || kolizja_bottom()) {
            std::cout << "Kolizja!\n";
            dron_stage.move_ahead(rising_angle, -distance / double(kwant));
            break;
        } else if (wynurzenie() && ((rising_angle > 0 && distance > 0) || (rising_angle < 0 && distance < 0))) {
            std::cout << "Wynurzenie.\n";
            distance = distance * cos(acos(-1) * rising_angle / 180.0);
            rising_angle = 0;
        }
        rysuj();
    }
}

void stage::rotation(double rotation_angle) {
    int kwant = 360;
    for (int i = 0; i < kwant; ++i) {
        dron_stage.rotation(rotation_angle / double(kwant));
        rysuj();
    }
}
