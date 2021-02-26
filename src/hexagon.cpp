#include "hexagon.hh"
#include <cmath>
#include <fstream>

hexagon::hexagon() : obiekt() {
    for (int i = 0; i < size_of_TVec_3D; ++i)
        translation[i] = 0;
}

void hexagon::rotation_matrix_x(TMatrix<double, size_of_TVec_3D>& rotation, double rotation_angle) const {
    const double pi = acos(-1);

    rotation(0, 1) = 0;
    rotation(0, 2) = 0;
    rotation(1, 0) = 0;
    rotation(2, 0) = 0;

    rotation(0, 0) = 1;

    rotation(1, 1) = cos(pi * (rotation_angle / 180.0));
    rotation(2, 2) = rotation(1, 1);
    rotation(2, 1) = sin(pi * (rotation_angle / 180.0));
    rotation(1, 2) = -rotation(2, 1);
}

void hexagon::local_move() {
    TMatrix<double, size_of_TVec_3D> rotation_matrix;

    all_angle += 10;
    while (all_angle >= 360.0)
        all_angle -= 360.0;
    while (all_angle <= -360.0)
        all_angle += 360.0;

    rotation_matrix_x(rotation_matrix, all_angle);

    rotation(rotation_matrix);
    move_ahead(translation);
}

TVector<double, size_of_TVec_3D> hexagon::location() const {
    return local_centre + translation;
}
