#include "stage.hh"
#include <cmath>
#include <iostream>

bool stage::colision_bottom() const {
    return (fabs(dron_stage.return_location()[2] - bottom.return_z()) <= dron_stage.return_lenghts()[2]);
}

bool stage::emergence() const {
    return (fabs(dron_stage.return_location()[2] - water.return_z()) <= dron_stage.return_lenghts()[2] - 20);
}

bool stage::colision() const {
    TVector<double, 3> dlugosci_drona = dron_stage.return_lenghts();
    TVector<double, 3> srodek_drona = dron_stage.return_location();
    TVector<double, 3> dlugosci_przeszkody;
    TVector<double, 3> distancei;

    bool jest_colision = false;

    for (auto& przeszkoda : lista_przeszkod) {
        dlugosci_przeszkody = przeszkoda->return_lenght_halves();
        distancei = srodek_drona - przeszkoda->location();

        for (int i = 0; i < 3; ++i) {
            jest_colision = (fabs(distancei[i]) <= (dlugosci_przeszkody[i] + dlugosci_drona[i]));
            if (!jest_colision) {
                break;
            }
        }
        if (jest_colision) {
            return true;
        }
    }
    return false;
}

void stage::link_add_file(const std::string& file_name) {
    link.DodajNazwePliku(file_name.c_str());
}

void stage::add_bottom(const std::string& local_name, const std::string& global_name) {
    bottom.add_local_file(local_name);
    bottom.add_global_file(global_name);

    bottom.read_local();

    link_add_file(global_name);
}

void stage::add_water(const std::string& local_name, const std::string& global_name) {
    water.add_local_file(local_name);
    water.add_global_file(global_name);

    water.read_local();

    link_add_file(global_name);
}

void stage::add_body(const std::string& local_name, const std::string& global_name) {
    dron_stage.add_files_body(local_name, global_name);

    link_add_file(global_name);
}

void stage::add_left_motor(const std::string& local_name, const std::string& global_name) {
    dron_stage.add_files_left_motor(local_name, global_name);

    link_add_file(global_name);
}

void stage::add_right_motor(const std::string& local_name, const std::string& global_name) {
    dron_stage.add_files_right_motor(local_name, global_name);

    link_add_file(global_name);
}

void stage::add_obstacle(const std::string& local_name, const std::string& global_name) {
    lista_przeszkod.back()->add_local_file(local_name);
    lista_przeszkod.back()->add_global_file(global_name);

    lista_przeszkod.back()->initialize_obiekt();

    link_add_file(global_name);
}

void stage::add_cuboid(const std::string& local_name, const std::string& global_name) {
    lista_przeszkod.push_back(std::make_shared<cuboid>());

    add_obstacle(local_name, global_name);
}

void stage::add_bar(const std::string& local_name, const std::string& global_name) {
    lista_przeszkod.push_back(std::make_shared<bar>());

    add_obstacle(local_name, global_name);
}

void stage::add_rectangle(const std::string& local_name, const std::string& global_name) {
    lista_przeszkod.push_back(std::make_shared<rectangle>());

    add_obstacle(local_name, global_name);
}

void stage::initialize() {
    link.ZmienTrybRys(PzG::TR_3D);
    link.Inicjalizuj();
    dron_stage.initialize_drone();
    draw();
}

void stage::move_ahead(double rising_angle, double distance) {
    int kwant = 250;
    for (int i = 0; i < kwant; ++i) {
        dron_stage.move_ahead(rising_angle, distance / double(kwant));
        if (colision() || colision_bottom()) {
            std::cout << "colision!\n";
            dron_stage.move_ahead(rising_angle, -distance / double(kwant));
            break;
        } else if (emergence() && ((rising_angle > 0 && distance > 0) || (rising_angle < 0 && distance < 0))) {
            std::cout << "emergence.\n";
            distance = distance * cos(acos(-1) * rising_angle / 180.0);
            rising_angle = 0;
        }
        draw();
    }
}

void stage::rotation(double rotation_angle) {
    int kwant = 360;
    for (int i = 0; i < kwant; ++i) {
        dron_stage.rotation(rotation_angle / double(kwant));
        draw();
    }
}
