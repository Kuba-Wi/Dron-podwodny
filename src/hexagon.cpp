#include "hexagon.hh"
#include <cmath>
#include <fstream>

void hexagon::macierz_rotationu_x(TMatrix<double, 3>& rotation, double rotation_angle) const {
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

void hexagon::ruch_lokalny() {
    TMatrix<double, 3> mac_rotationu;

    all_angle += 10;
    while (all_angle >= 360.0)
        all_angle -= 360.0;
    while (all_angle <= -360.0)
        all_angle += 360.0;

    macierz_rotationu_x(mac_rotationu, all_angle);

    rotation(mac_rotationu);
    move_ahead(translation);
}
