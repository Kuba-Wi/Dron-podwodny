#include <cmath>
#include <fstream>
#include <sstream>
#include <string>
#include "TMatrix.hh"
#include "TVector.hh"
#include "gtest/gtest.h"
#include "hexagon.hh"
#include "testFuctions.hh"

const std::string local_name = "../tests/hexagon_local.txt";
const std::string global_name = "../tests/hexagon_global.txt";

struct hexagonTest : public ::testing::Test {
    hexagon hex;
    hexagonTest() {
        hex.add_local_file(local_name);
        hex.add_global_file(global_name);
        hex.initialize_obiekt();
    }
};

TEST_F(hexagonTest, locationFunctionShouldReturnLocationOfHexagon) {
    std::istringstream str("1 2 3");
    TVector<double, 3> translation_3D;
    str >> translation_3D;
    hex.inscribe_translation(translation_3D);
    const auto location = hex.location();

    TVector<double, 3> first_3D;
    TVector<double, 3> second_3D;
    std::ifstream read(local_name);
    read >> first_3D;
    read >> second_3D;
    read.close();
    const auto result = (second_3D + first_3D) / 2 + translation_3D;
    ASSERT_EQ(location[0], result[0]);
    ASSERT_EQ(location[1], result[1]);
    ASSERT_EQ(location[2], result[2]);
}

TEST_F(hexagonTest, local_moveFunctionShouldMoveHexagon) {
    std::istringstream str("1 2 3");
    TVector<double, 3> translation_3D;
    str >> translation_3D;
    hex.inscribe_translation(translation_3D);
    hex.local_move();
    hex.write_global_coordinates();

    std::istringstream write_mat("1 0 0 0 1 0 0 0 1");
    TMatrix<double, 3> rotation_3D;
    write_mat >> rotation_3D;
    check_move_and_rotation(local_name, global_name, rotation_3D, translation_3D);
}
