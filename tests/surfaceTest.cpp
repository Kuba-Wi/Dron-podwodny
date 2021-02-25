#include <algorithm>
#include <fstream>
#include <sstream>
#include <string>
#include "TVector.hh"
#include "gtest/gtest.h"
#include "surface.hh"

const std::string local_name = "../tests/surface_local.txt";
const std::string global_name = "../tests/surface_global.txt";

void rtrim_string(std::string& str) {
    str.erase(std::find_if(str.rbegin(), str.rend(), [](auto ch) { return !std::isspace(ch); }).base(), str.end());
}

TEST(surfaceTest, read_localFunctionShouldReadLocalFileAndWriteItToGlobalFile) {
    surface surf(local_name, global_name);
    surf.read_local();

    std::string local_line;
    std::string global_line;
    std::ifstream read_local;
    std::ifstream read_global;
    read_local.open(local_name);
    read_global.open(global_name);

    if (!read_local.is_open() || !read_global.is_open()) {
        ASSERT_TRUE(false);
    }

    while (!read_local.eof() && !read_global.eof()) {
        std::getline(read_local, local_line);
        std::getline(read_global, global_line);
        rtrim_string(local_line);
        rtrim_string(global_line);
        ASSERT_EQ(local_line, global_line);
    }
    read_local.close();
    read_global.close();
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
