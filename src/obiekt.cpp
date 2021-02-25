#include "obiekt.hh"
#include <cmath>
#include <fstream>

obiekt::obiekt() : all_angle(0) {
    for (int i = 0; i < size_of_TVec_3D; ++i)
        translation[i] = 0;
}

void obiekt::initialize_obiekt() {
    read_local();
    read_local_coordinates();

    TVector<double, size_of_TVec_3D> min_coord = coordinates[0];
    TVector<double, size_of_TVec_3D> max_coord = coordinates[0];

    for (auto& line : coordinates) {
        for (int i = 0; i < size_of_TVec_3D; ++i) {
            if (line[i] < min_coord[i])
                min_coord[i] = line[i];
            else if (line[i] > max_coord[i])
                max_coord[i] = line[i];
        }
    }

    local_centre = (min_coord + max_coord) / 2;
    lenght_half = (max_coord - min_coord) / 2;

    for (int i = 0; i < size_of_TVec_3D; ++i) {
        lenght_half[i] += 0.25;
    }
}

void obiekt::read_coordinates(const std::string& file_name) {
    std::ifstream read;
    read.open(file_name);
    if (!read.is_open())
        return;

    TVector<double, size_of_TVec_3D> line;
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

    for (TVector<double, size_of_TVec_3D>& i : coordinates) {
        write << i;
        ++counter;
        if (counter == 4) {
            counter = 0;
            write << "#\n\n";
        }
    }

    write.close();
}

void obiekt::move_ahead(const TVector<double, size_of_TVec_3D>& mv) {
    for (TVector<double, size_of_TVec_3D>& x : coordinates)
        x = x + mv;
}

void obiekt::rotation(const TMatrix<double, size_of_TVec_3D>& rotation_matrix) {
    for (TVector<double, size_of_TVec_3D>& x : coordinates)
        x = rotation_matrix * x;
}

TVector<double, size_of_TVec_3D> obiekt::location() const {
    return local_centre + translation;
}
