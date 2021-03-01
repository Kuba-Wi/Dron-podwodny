#include <cmath>
#include <sstream>
#include "TMatrix.hh"
#include "TVector.hh"
#include "gtest/gtest.h"
#include "stage.hh"
#include "testFuctions.hh"

const std::string bottom_local = "../tests/dat_files/bottom_local.txt";
const std::string bottom_global = "../tests/dat_files/bottom_global.txt";
const std::string water_local = "../tests/dat_files/water_local.txt";
const std::string water_global = "../tests/dat_files/water_global.txt";
const std::string body_local = "../tests/dat_files/body_local.txt";
const std::string body_global = "../tests/dat_files/body_global.txt";
const std::string left_motor_local = "../tests/dat_files/left_motor_local.txt";
const std::string left_motor_global = "../tests/dat_files/left_motor_global.txt";
const std::string right_motor_local = "../tests/dat_files/right_motor_local.txt";
const std::string right_motor_global = "../tests/dat_files/right_motor_global.txt";
const std::string bar_local = "../tests/dat_files/bar_local.txt";
const std::string bar_global = "../tests/dat_files/bar_global.txt";
const std::string cuboid_local = "../tests/dat_files/cuboid_local.txt";
const std::string cuboid_global = "../tests/dat_files/cuboid_global.txt";
const std::string rectangle_local = "../tests/dat_files/rectangle_local.txt";
const std::string rectangle_global = "../tests/dat_files/rectangle_global.txt";

struct stageTest : public ::testing::Test {
    stage st;
    TVector<double, 3> l_motor_relocation_3D;
    TVector<double, 3> r_motor_relocation_3D;
    TMatrix<double, 3> rotation_local_3D;
    stageTest() {
        st.add_bottom(bottom_local, bottom_global);
        st.add_water(water_local, water_global);
        st.add_body(body_local, body_global);
        st.add_left_motor(left_motor_local, left_motor_global);
        st.add_right_motor(right_motor_local, right_motor_global);
        st.add_bar(bar_local, bar_global);
        st.add_cuboid(cuboid_local, cuboid_global);
        st.add_rectangle(rectangle_local, rectangle_global);
        st.initialize();

        const double local_move = 20;
        l_motor_relocation_3D[0] = -local_move;
        l_motor_relocation_3D[1] = local_move;
        l_motor_relocation_3D[2] = 0;
        r_motor_relocation_3D[0] = -local_move;
        r_motor_relocation_3D[1] = -local_move;
        r_motor_relocation_3D[2] = 0;

        const double pi = acos(-1);
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

TEST_F(stageTest, initializeAndAddFunctionsShouldAddAndInitializeObiectsOnStage) {
    std::istringstream str("1 0 0 0 1 0 0 0 1");
    TMatrix<double, 3> rotation_3D;
    str >> rotation_3D;
    check_move_and_rotation(left_motor_local, left_motor_global, rotation_3D, l_motor_relocation_3D);
    check_move_and_rotation(right_motor_local, right_motor_global, rotation_3D, r_motor_relocation_3D);

    check_reading_writing_to_file(bottom_local, bottom_global);
    check_reading_writing_to_file(water_local, water_global);
    check_reading_writing_to_file(body_local, body_global);
    check_reading_writing_to_file(bar_local, bar_global);
    check_reading_writing_to_file(cuboid_local, cuboid_global);
    check_reading_writing_to_file(rectangle_local, rectangle_global);
}

TEST_F(stageTest, move_aheadFunctionShouldMoveDroneOnStage) {
    constexpr double angle = 30;
    constexpr double distance = 2;
    st.move_ahead(angle, distance);

    TMatrix<double, 3> rotation_3D;
    std::istringstream str("1 0 0 0 1 0 0 0 1");
    str >> rotation_3D;

    const double pi = acos(-1);
    TVector<double, 3> translation_3D;
    translation_3D[0] = cos(pi * (angle / 180.0));
    translation_3D[1] = 0;
    translation_3D[2] = 0.5;
    translation_3D = translation_3D * distance;
    check_move_and_rotation(body_local, body_global, rotation_3D, translation_3D);
}

TEST_F(stageTest, rotationFunctionShouldRotateDroneOnStage) {
    constexpr double rotation_angle = 30;
    st.rotation(rotation_angle);

    std::istringstream str_vec("0 0 0");
    TVector<double, 3> translation_3D;
    str_vec >> translation_3D;
    TMatrix<double, 3> rotation_3D;
    rotation_z(rotation_3D, rotation_angle);
    check_move_and_rotation(body_local, body_global, rotation_3D, translation_3D);
}
