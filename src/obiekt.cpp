#include "obiekt.hh"
#include <cmath>
#include <fstream>

obiekt::obiekt() {
    for (int i = 0; i < 3; ++i)
        translation[i] = 0;

    all_angle = 0;
}

void obiekt::initialize_obiekt() {
    read_local();
    read_local_coordinates();

    TVector<double, 3> min_coord = coordinates[0];
    TVector<double, 3> max_coord = coordinates[0];

    for (auto& line : coordinates) {
        for (int i = 0; i < 3; ++i) {
            if (line[i] < min_coord[i])
                min_coord[i] = line[i];
            else if (line[i] > max_coord[i])
                max_coord[i] = line[i];
        }
    }

    local_centre = (min_coord + max_coord) / 2;
    lenght_half = (max_coord - min_coord) / 2;

    for (int i = 0; i < 3; ++i) {
        lenght_half[i] += 0.25;
    }
}

void obiekt::read_coordinates(const std::string& file_name) {
    std::ifstream read;
    read.open(file_name);
    if (!read.is_open())
        return;

    TVector<double, 3> line;
    coordinates.clear();

    read >> line;
    while (!read.eof()) {
        if (!read) {
            read.clear();
            while (read.get() != '\n')
                ;
        } else {
            coordinates.push_back(line);
        }
        read >> line;
    }

    read.close();
}

void obiekt::read_local_coordinates() {
    read_coordinates(local_file_name);
}

void obiekt::write_global_coordinates() {
    std::ofstream write;
    write.open(file_with_points);
    if (!write.is_open())
        return;

    int counter = 0;

    for (TVector<double, 3>& i : coordinates) {
        write << i;
        ++counter;
        if (counter == 4) {
            counter = 0;
            write << "#\n\n";
        }
    }

    write.close();
}

void obiekt::move_ahead(const TVector<double, 3>& mv) {
    for (TVector<double, 3>& x : coordinates)
        x = x + mv;
}

void obiekt::rotation(const TMatrix<double, 3>& rotation_matrix) {
    for (TVector<double, 3>& x : coordinates)
        x = rotation_matrix * x;
}

TVector<double, 3> obiekt::location() const {
    return local_centre + translation;
}
