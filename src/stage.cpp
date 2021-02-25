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
    TVector<double, size_of_TVec_3D> drone_lenghts = dron_stage.return_lenghts();
    TVector<double, size_of_TVec_3D> drone_centre = dron_stage.return_location();
    TVector<double, size_of_TVec_3D> obstacle_lenghts;
    TVector<double, size_of_TVec_3D> distance;

    bool is_colision = false;

    for (auto& obstacle : obstacles_list) {
        obstacle_lenghts = obstacle->return_lenght_halves();
        distance = drone_centre - obstacle->location();

        for (int i = 0; i < size_of_TVec_3D; ++i) {
            is_colision = (fabs(distance[i]) <= (obstacle_lenghts[i] + drone_lenghts[i]));
            if (!is_colision) {
                break;
            }
        }
        if (is_colision) {
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
    obstacles_list.back()->add_local_file(local_name);
    obstacles_list.back()->add_global_file(global_name);

    obstacles_list.back()->initialize_obiekt();

    link_add_file(global_name);
}

void stage::add_cuboid(const std::string& local_name, const std::string& global_name) {
    obstacles_list.push_back(std::make_shared<cuboid>());

    add_obstacle(local_name, global_name);
}

void stage::add_bar(const std::string& local_name, const std::string& global_name) {
    obstacles_list.push_back(std::make_shared<bar>());

    add_obstacle(local_name, global_name);
}

void stage::add_rectangle(const std::string& local_name, const std::string& global_name) {
    obstacles_list.push_back(std::make_shared<rectangle>());

    add_obstacle(local_name, global_name);
}

void stage::initialize() {
    link.ZmienTrybRys(PzG::TR_3D);
    link.Inicjalizuj();
    dron_stage.initialize_drone();
    draw();
}

void stage::move_ahead(double rising_angle, double distance) {
    int quantum = 250;
    for (int i = 0; i < quantum; ++i) {
        dron_stage.move_ahead(rising_angle, distance / double(quantum));
        if (colision() || colision_bottom()) {
            std::cout << "Colision!\n";
            dron_stage.move_ahead(rising_angle, -distance / double(quantum));
            break;
        } else if (emergence() && ((rising_angle > 0 && distance > 0) || (rising_angle < 0 && distance < 0))) {
            std::cout << "Emergence.\n";
            distance = distance * cos(acos(-1) * rising_angle / 180.0);
            rising_angle = 0;
        }
        draw();
    }
}

void stage::rotation(double rotation_angle) {
    int quantum = 360;
    for (int i = 0; i < quantum; ++i) {
        dron_stage.rotation(rotation_angle / double(quantum));
        draw();
    }
}
