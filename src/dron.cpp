#include "dron.hh"

dron::dron() {
    for (int i = 0; i < 3; ++i)
        translation[i] = 0;

    all_angle = 0;
}

void dron::count_translation(TVector<double, 3>& translacja, double rising_angle, double distance) const {
    const double pi = acos(-1);

    translacja[0] = cos(pi * (all_angle / 180.0)) * cos(pi * (rising_angle / 180.0));
    translacja[1] = sin(pi * (all_angle / 180.0)) * cos(pi * (rising_angle / 180.0));
    translacja[2] = sin(pi * (rising_angle / 180.0));
}

void dron::count_rotation_angle(TMatrix<double, 3>& rotation, double rotation_angle) const {
    const double pi = acos(-1);

    for (int i = 0; i < 3; ++i) {
        rotation(2, i) = 0;
        rotation(i, 2) = 0;
    }
    rotation(2, 2) = 1;

    rotation(0, 0) = cos(pi * (rotation_angle / 180.0));
    rotation(1, 1) = rotation(0, 0);
    rotation(1, 0) = sin(pi * (rotation_angle / 180.0));
    rotation(0, 1) = -rotation(1, 0);
}

void dron::initialize_drone() {
    body.inicjalizuj_obiekt();
    left_motor.inicjalizuj_obiekt();
    right_motor.inicjalizuj_obiekt();

    TVector<double, 3> przesun;
    przesun[0] = -20;
    przesun[1] = -20;
    przesun[2] = 0;
    right_motor.inscribe_translation(przesun);
    przesun[1] = 20;
    left_motor.inscribe_translation(przesun);

    TMatrix<double, 3> rotation_temp;

    count_rotation_angle(rotation_temp, 0);

    left_motor_move(rotation_temp);
    right_motor_move(rotation_temp);
}

void dron::add_files_body(const std::string& local_name, const std::string& global_name) {
    body.dodaj_plik_lok(local_name);
    body.dodaj_plik_glob(global_name);
}

void dron::add_files_left_motor(const std::string& local_name, const std::string& global_name) {
    left_motor.dodaj_plik_lok(local_name);
    left_motor.dodaj_plik_glob(global_name);
}

void dron::add_files_right_motor(const std::string& local_name, const std::string& global_name) {
    right_motor.dodaj_plik_lok(local_name);
    right_motor.dodaj_plik_glob(global_name);
}

void dron::move_ahead(double rising_angle, double distance) {
    TVector<double, 3> translacja;
    TMatrix<double, 3> rotation;
    count_translation(translacja, rising_angle, distance);
    count_rotation_angle(rotation, all_angle);

    translacja = translacja * distance;
    translation = translation + translacja;

    left_motor_move(rotation);
    right_motor_move(rotation);
    body_move(rotation);
}

void dron::rotation(double rotation_angle) {
    TMatrix<double, 3> rotation;

    all_angle += rotation_angle;
    while (all_angle >= 360.0)
        all_angle -= 360.0;
    while (all_angle <= -360.0)
        all_angle += 360.0;

    count_rotation_angle(rotation, all_angle);

    left_motor_move(rotation);
    right_motor_move(rotation);
    body_move(rotation);
}

void dron::left_motor_move(const TMatrix<double, 3>& rotation) {
    left_motor.wczytaj_wspolrzedne_lok();

    left_motor.local_move();
    left_motor.rotation(rotation);
    left_motor.move_ahead(translation);

    left_motor.wpisz_wspolrzedne_glob();
}

void dron::right_motor_move(const TMatrix<double, 3>& rotation) {
    right_motor.wczytaj_wspolrzedne_lok();

    right_motor.local_move();
    right_motor.rotation(rotation);
    right_motor.move_ahead(translation);

    right_motor.wpisz_wspolrzedne_glob();
}

void dron::body_move(const TMatrix<double, 3>& rotation) {
    body.wczytaj_wspolrzedne_lok();

    body.rotation(rotation);
    body.move_ahead(translation);

    body.wpisz_wspolrzedne_glob();
}

TVector<double, 3> dron::return_location() const {
    return translation + body.polozenie();
}

TVector<double, 3> dron::return_lenghts() const {
    TVector<double, 3> dlugosc_sr = left_motor.zwroc_polowy_dlugosci();
    TVector<double, 3> dlugosc_kor = body.zwroc_polowy_dlugosci();

    dlugosc_sr[0] = dlugosc_sr[1] = sqrt(dlugosc_sr[0] * dlugosc_sr[0] + dlugosc_sr[1] * dlugosc_sr[1]);
    dlugosc_kor[0] = dlugosc_kor[1] = sqrt(dlugosc_kor[0] * dlugosc_kor[0] + dlugosc_kor[1] * dlugosc_kor[1]);

    return dlugosc_kor + dlugosc_sr;
}
