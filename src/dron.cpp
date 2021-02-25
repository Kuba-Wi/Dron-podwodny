#include "dron.hh"

dron::dron() {
    for (int i = 0; i < size_of_TVec_3D; ++i)
        translation[i] = 0;

    all_angle = 0;
}

void dron::count_translation(TVector<double, size_of_TVec_3D>& vec, double rising_angle, double distance) const {
    const double pi = acos(-1);

    vec[0] = cos(pi * (all_angle / 180.0)) * cos(pi * (rising_angle / 180.0));
    vec[1] = sin(pi * (all_angle / 180.0)) * cos(pi * (rising_angle / 180.0));
    vec[2] = sin(pi * (rising_angle / 180.0));

    vec = vec * distance;
}

void dron::count_rotation_angle(TMatrix<double, size_of_TVec_3D>& rotation, double rotation_angle) const {
    const double pi = acos(-1);

    for (int i = 0; i < size_of_TVec_3D; ++i) {
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
    body.initialize_obiekt();
    left_motor.initialize_obiekt();
    right_motor.initialize_obiekt();

    TVector<double, size_of_TVec_3D> przesun;
    przesun[0] = -20;
    przesun[1] = -20;
    przesun[2] = 0;
    right_motor.inscribe_translation(przesun);
    przesun[1] = 20;
    left_motor.inscribe_translation(przesun);

    TMatrix<double, size_of_TVec_3D> rotation_temp;

    count_rotation_angle(rotation_temp, 0);

    left_motor_move(rotation_temp);
    right_motor_move(rotation_temp);
}

void dron::add_files_body(const std::string& local_name, const std::string& global_name) {
    body.add_local_file(local_name);
    body.add_global_file(global_name);
}

void dron::add_files_left_motor(const std::string& local_name, const std::string& global_name) {
    left_motor.add_local_file(local_name);
    left_motor.add_global_file(global_name);
}

void dron::add_files_right_motor(const std::string& local_name, const std::string& global_name) {
    right_motor.add_local_file(local_name);
    right_motor.add_global_file(global_name);
}

void dron::move_ahead(double rising_angle, double distance) {
    TVector<double, size_of_TVec_3D> temp_translation;
    TMatrix<double, size_of_TVec_3D> rotation;
    count_translation(temp_translation, rising_angle, distance);
    count_rotation_angle(rotation, all_angle);

    translation = translation + temp_translation;

    left_motor_move(rotation);
    right_motor_move(rotation);
    body_move(rotation);
}

void dron::rotation(double rotation_angle) {
    TMatrix<double, size_of_TVec_3D> rotation;

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

void dron::left_motor_move(const TMatrix<double, size_of_TVec_3D>& rotation) {
    left_motor.read_local_coordinates();

    left_motor.local_move();
    left_motor.rotation(rotation);
    left_motor.move_ahead(translation);

    left_motor.write_global_coordinates();
}

void dron::right_motor_move(const TMatrix<double, size_of_TVec_3D>& rotation) {
    right_motor.read_local_coordinates();

    right_motor.local_move();
    right_motor.rotation(rotation);
    right_motor.move_ahead(translation);

    right_motor.write_global_coordinates();
}

void dron::body_move(const TMatrix<double, size_of_TVec_3D>& rotation) {
    body.read_local_coordinates();

    body.rotation(rotation);
    body.move_ahead(translation);

    body.write_global_coordinates();
}

TVector<double, size_of_TVec_3D> dron::return_location() const {
    return translation + body.location();
}

TVector<double, size_of_TVec_3D> dron::return_lenghts() const {
    TVector<double, size_of_TVec_3D> motor_lenght = left_motor.return_lenght_halves();
    TVector<double, size_of_TVec_3D> body_lenght = body.return_lenght_halves();

    motor_lenght[0] = motor_lenght[1] = sqrt(motor_lenght[0] * motor_lenght[0] + motor_lenght[1] * motor_lenght[1]);
    body_lenght[0] = body_lenght[1] = sqrt(body_lenght[0] * body_lenght[0] + body_lenght[1] * body_lenght[1]);

    return body_lenght + motor_lenght;
}
