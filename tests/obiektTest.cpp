#include <fstream>
#include <string>
#include "TVector.hh"
#include "gtest/gtest.h"
#include "obiekt.hh"
#include "testFuctions.hh"

const std::string local_name = "../tests/dat_files/obiekt_local.txt";
const std::string global_name = "../tests/dat_files/obiekt_global.txt";

void clean_global_file() {
    std::ofstream strm(global_name);
    strm << "";
    strm.close();
}

struct obiektTest : public ::testing::Test {
    obiekt ob;
    obiektTest() {
        ob.add_local_file(local_name);
        ob.add_global_file(global_name);
    }
};

TEST_F(obiektTest, initialize_obiektFunctionShouldReadLocalCoordinatesAndWriteThemToGlobalFile) {
    ob.initialize_obiekt();
    check_reading_writing_to_file(local_name, global_name);
    clean_global_file();
}

TEST_F(obiektTest, return_lenght_halvesFunctionShouldReturnTVectorOfObiektHalfDimensions) {
    TVector<double, 3> first_3D;
    TVector<double, 3> second_3D;
    std::ifstream read(local_name);
    read >> first_3D;
    read >> second_3D;
    read.close();
    const auto result = (second_3D - first_3D) / 2;
    constexpr double safe_border = 0.25;

    ob.initialize_obiekt();
    auto half_dimensions = ob.return_lenght_halves();
    ASSERT_EQ(half_dimensions[0], result[0] + safe_border);
    ASSERT_EQ(half_dimensions[1], result[1] + safe_border);
    ASSERT_EQ(half_dimensions[2], result[2] + safe_border);
    clean_global_file();
}

TEST_F(obiektTest, locationFunctionShouldReturnLocalLocationOfObiekt) {
    TVector<double, 3> first_3D;
    TVector<double, 3> second_3D;
    std::ifstream read(local_name);
    read >> first_3D;
    read >> second_3D;
    read.close();
    const auto result = (second_3D + first_3D) / 2;

    ob.initialize_obiekt();
    auto location = ob.location();
    ASSERT_EQ(location[0], result[0]);
    ASSERT_EQ(location[1], result[1]);
    ASSERT_EQ(location[2], result[2]);
    clean_global_file();
}

TEST_F(obiektTest, readWriteFunctionsShouldReadFromLocalFileAndWriteToGlobalFile) {
    ob.read_local_coordinates();
    ob.write_global_coordinates();
    check_reading_writing_to_file(local_name, global_name);
    clean_global_file();
}

TEST_F(obiektTest, move_aheadFunctionShouldMoveObiect) {
    std::istringstream write_vec("1 1 1");
    std::istringstream write_mat("1 0 0 0 1 0 0 0 1");
    TVector<double, 3> translation_3D;
    TMatrix<double, 3> rotation_3D;
    write_vec >> translation_3D;
    write_mat >> rotation_3D;

    ob.initialize_obiekt();
    ob.move_ahead(translation_3D);
    ob.write_global_coordinates();

    check_move_and_rotation(local_name, global_name, rotation_3D, translation_3D);
    clean_global_file();
}

TEST_F(obiektTest, rotationFunctionShouldRotateObiect) {
    std::istringstream write_vec("0 0 0");
    std::istringstream write_mat("1 1 1 2 2 2 3 3 3");
    TVector<double, 3> translation_3D;
    TMatrix<double, 3> rotation_3D;
    write_vec >> translation_3D;
    write_mat >> rotation_3D;

    ob.initialize_obiekt();
    ob.rotation(rotation_3D);
    ob.write_global_coordinates();

    check_move_and_rotation(local_name, global_name, rotation_3D, translation_3D);
}
