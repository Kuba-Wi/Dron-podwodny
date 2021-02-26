#include <fstream>
#include <sstream>
#include <string>
#include "TVector.hh"
#include "gtest/gtest.h"
#include "surface.hh"
#include "testFuctions.hh"

const std::string local_name = "../tests/surface_local.txt";
const std::string global_name = "../tests/surface_global.txt";

TEST(surfaceTest, read_localFunctionShouldReadLocalFileAndWriteItToGlobalFile) {
    surface surf(local_name, global_name);
    surf.read_local();
    check_reading_writing_to_file(local_name, global_name);
}

TEST(surfaceTest, return_zFunctionShouldReturnZCoordinateOfSurface) {
    surface surf;
    surf.add_local_file(local_name);
    surf.add_global_file(global_name);
    surf.read_local();

    std::istringstream in;
    std::string str;
    std::ifstream read_local;
    read_local.open(local_name.c_str());
    if (!read_local.is_open()) {
        ASSERT_TRUE(false);
    }
    std::getline(read_local, str);
    read_local.close();

    in.str(str);
    TVector<int, 3> vec_3D;
    in >> vec_3D;
    ASSERT_EQ(vec_3D[2], surf.return_z());
}
