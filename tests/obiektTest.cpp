#include <fstream>
#include <string>
#include "TVector.hh"
#include "gtest/gtest.h"
#include "obiekt.hh"
#include "testFuctions.hh"

const std::string local_name = "../tests/obiekt_local.txt";
const std::string global_name = "../tests/obiekt_global.txt";

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
    std::istringstream str("1 1 1");
    TVector<double, 3> translation_3D;
    TVector<double, 3> local_3D;
    TVector<double, 3> global_3D;
    str >> translation_3D;

    ob.initialize_obiekt();
    ob.move_ahead(translation_3D);
    ob.write_global_coordinates();

    std::ifstream read_local(local_name);
    std::ifstream read_global(global_name);
    read_local >> local_3D;
    read_global >> global_3D;
    auto local_translated = local_3D + translation_3D;
    for(std::size_t i = 0; i < size_of_TVec_3D; ++i) {
        ASSERT_EQ(local_translated[i], global_3D[i]);
    }
    read_local >> local_3D;
    read_global >> global_3D;
    local_translated = local_3D + translation_3D;
    for(std::size_t i = 0; i < size_of_TVec_3D; ++i) {
        ASSERT_EQ(local_translated[i], global_3D[i]);
    }
    read_local.close();
    read_global.close();
    clean_global_file(); 
}

TEST_F(obiektTest, rotationFunctionShouldRotateObiect) {
    std::istringstream str("1 1 1 2 2 2 3 3 3");
    TMatrix<double, 3> rotation_matrix;
    TVector<double, 3> local_3D;
    TVector<double, 3> global_3D;
    str >> rotation_matrix;

    ob.initialize_obiekt();
    ob.rotation(rotation_matrix);
    ob.write_global_coordinates();

    std::ifstream read_local(local_name);
    std::ifstream read_global(global_name);
    read_local >> local_3D;
    read_global >> global_3D;
    auto local_rotated = rotation_matrix * local_3D;
    for(std::size_t i = 0; i < size_of_TVec_3D; ++i) {
        ASSERT_EQ(local_rotated[i], global_3D[i]);
    }
    read_local >> local_3D;
    read_global >> global_3D;
    local_rotated = rotation_matrix * local_3D;
    for(std::size_t i = 0; i < size_of_TVec_3D; ++i) {
        ASSERT_EQ(local_rotated[i], global_3D[i]);
    }
    read_local.close();
    read_global.close(); 
}
