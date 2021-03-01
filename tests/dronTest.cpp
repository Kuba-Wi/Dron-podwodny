#include <fstream>
#include <sstream>
#include <string>
#include "TMatrix.hh"
#include "TVector.hh"
#include "dron.hh"
#include "gtest/gtest.h"
#include "testFuctions.hh"

const std::string body_local = "../tests/dat_files/body_local.txt";
const std::string body_global = "../tests/dat_files/body_global.txt";
const std::string left_motor_local = "../tests/dat_files/left_motor_local.txt";
const std::string left_motor_global = "../tests/dat_files/left_motor_global.txt";
const std::string right_motor_local = "../tests/dat_files/right_motor_local.txt";
const std::string right_motor_global = "../tests/dat_files/right_motor_global.txt";

struct dronTest : public ::testing::Test {
    dron drone;
    const double local_move = 20;
    const double pi = acos(-1);
    TVector<double, 3> l_motor_relocation_3D;
    TVector<double, 3> r_motor_relocation_3D;
    TMatrix<double, 3> rotation_local_3D;
    dronTest() {
        drone.add_files_body(body_local, body_global);
        drone.add_files_left_motor(left_motor_local, left_motor_global);
        drone.add_files_right_motor(right_motor_local, right_motor_global);
        drone.initialize_drone();

        l_motor_relocation_3D[0] = -local_move;
        l_motor_relocation_3D[1] = local_move;
        l_motor_relocation_3D[2] = 0;
        r_motor_relocation_3D[0] = -local_move;
        r_motor_relocation_3D[1] = -local_move;
        r_motor_relocation_3D[2] = 0;

        rotation_local_3D(0, 1) = 0;
        rotation_local_3D(0, 2) = 0;
        rotation_local_3D(1, 0) = 0;
        rotation_local_3D(2, 0) = 0;
        rotation_local_3D(0, 0) = 1;
        rotation_local_3D(1, 1) = cos(pi * (1 / 180.0));
        rotation_local_3D(2, 2) = rotation_local_3D(1, 1);
        rotation_local_3D(2, 1) = sin(pi * (1 / 180.0));
        rotation_local_3D(1, 2) = -rotation_local_3D(2, 1);
    }
};

TEST_F(dronTest, initialize_droneFunctionShouldWriteCoordinatesToGlobalFiles) {
    std::istringstream str("1 0 0 0 1 0 0 0 1");
    TMatrix<double, 3> rotation_3D;
    str >> rotation_3D;

    check_reading_writing_to_file(body_local, body_global);
    check_move_and_rotation(left_motor_local, left_motor_global, rotation_3D, l_motor_relocation_3D);
    check_move_and_rotation(right_motor_local, right_motor_global, rotation_3D, r_motor_relocation_3D);
}

TEST_F(dronTest, move_aheadFunctionShouldMoveDrone) {
    constexpr double rising_angle = 30;
    constexpr double distance = 10;
    drone.move_ahead(rising_angle, distance);

    TVector<double, 3> translation_3D;
    translation_3D[0] = cos(pi * (rising_angle / 180.0));
    translation_3D[1] = 0;
    translation_3D[2] = 0.5;
    translation_3D = translation_3D * distance;

    std::istringstream str("1 0 0 0 1 0 0 0 1");
    TMatrix<double, 3> rotation_3D;
    str >> rotation_3D;
    check_move_and_rotation(body_local, body_global, rotation_3D, translation_3D);
    check_move_and_rotation(left_motor_local, left_motor_global, rotation_local_3D,
                            l_motor_relocation_3D + translation_3D);
    check_move_and_rotation(right_motor_local, right_motor_global, rotation_local_3D,
                            r_motor_relocation_3D + translation_3D);
}

TEST_F(dronTest, rotationFunctionShouldRotateDrone) {
    constexpr double rotation_angle = 30;
    drone.rotation(rotation_angle);

    std::istringstream str_vec("0 0 0");
    TVector<double, 3> translation_3D;
    str_vec >> translation_3D;
    TMatrix<double, 3> rotation_3D;
    rotation_z(rotation_3D, rotation_angle);
    check_move_and_rotation(body_local, body_global, rotation_3D, translation_3D);

    TMatrix<double, 3> motor_rotation_3D;
    for (std::size_t i = 0; i < size_of_TVec_3D; ++i) {
        for (std::size_t j = 0; j < size_of_TVec_3D; ++j)
            motor_rotation_3D(i, j) = rotation_3D(i, 0) * rotation_local_3D(0, j) +
                                      rotation_3D(i, 1) * rotation_local_3D(1, j) +
                                      rotation_3D(i, 2) * rotation_local_3D(2, j);
    }
    check_move_and_rotation(left_motor_local, left_motor_global, motor_rotation_3D,
                            rotation_3D * l_motor_relocation_3D);
    check_move_and_rotation(right_motor_local, right_motor_global, motor_rotation_3D,
                            rotation_3D * r_motor_relocation_3D);
}

TEST_F(dronTest, return_locationFunctionShouldReturnLocationOfDrone) {
    constexpr double angle = 30;
    constexpr double distance = 10;
    drone.move_ahead(angle, distance);
    drone.rotation(angle);

    TVector<double, 3> translation_3D;
    translation_3D[0] = cos(pi * (angle / 180.0));
    translation_3D[1] = 0;
    translation_3D[2] = 0.5;
    translation_3D = translation_3D * distance;

    TVector<double, 3> first_3D;
    TVector<double, 3> second_3D;
    std::ifstream read(body_local);
    read >> first_3D;
    read >> second_3D;
    read.close();
    const auto result = (second_3D + first_3D) / 2 + translation_3D;

    const auto drone_location = drone.return_location();
    ASSERT_EQ(drone_location[0], result[0]);
    ASSERT_EQ(drone_location[1], result[1]);
    ASSERT_EQ(drone_location[2], result[2]);
}

TEST_F(dronTest, return_lengthsFunctionShouldReturnLengthsOfDrone) {
    constexpr double safe_border = 0.25;
    auto drone_lengths = drone.return_lenghts();

    TVector<double, 3> first_3D;
    TVector<double, 3> second_3D;
    std::ifstream read(body_local);
    read >> first_3D;
    read >> second_3D;
    read.close();

    auto body_lengths = (second_3D - first_3D) / 2;
    body_lengths[0] += safe_border;
    body_lengths[1] += safe_border;
    body_lengths[2] += safe_border;
    body_lengths[0] = body_lengths[1] = sqrt(body_lengths[0] * body_lengths[0] + body_lengths[1] * body_lengths[1]);

    read.open(left_motor_local);
    read >> first_3D;
    read >> second_3D;
    read.close();
    auto motor_lengths = (second_3D - first_3D) / 2;
    motor_lengths[0] += safe_border;
    motor_lengths[1] += safe_border;
    motor_lengths[2] += safe_border;
    motor_lengths[0] = motor_lengths[1] =
        sqrt(motor_lengths[0] * motor_lengths[0] + motor_lengths[1] * motor_lengths[1]);

    const auto result = body_lengths + motor_lengths;
    ASSERT_EQ(drone_lengths[0], result[0]);
    ASSERT_EQ(drone_lengths[1], result[1]);
    ASSERT_EQ(drone_lengths[2], result[2]);
}
