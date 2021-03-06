#include <algorithm>
#include <cmath>
#include <fstream>
#include "gtest/gtest.h"
#include "testFuctions.hh"

void rtrim_string(std::string& str) {
    str.erase(std::find_if(str.rbegin(), str.rend(), [](auto ch) { return !std::isspace(ch); }).base(), str.end());
}

void check_reading_writing_to_file(const std::string& local_name, const std::string& global_name) {
    std::string local_line;
    std::string global_line;
    std::ifstream read_local;
    std::ifstream read_global;
    read_local.open(local_name);
    read_global.open(global_name);

    ASSERT_TRUE(read_local.is_open() && read_global.is_open());

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

void check_moved(const TMatrix<double, 3>& rotation_3D,
                 const TVector<double, 3>& translation_3D,
                 const TVector<double, 3>& local_3D,
                 const TVector<double, 3>& global_3D) {
    auto local_moved = rotation_3D * local_3D + translation_3D;
    for (std::size_t i = 0; i < size_of_TVec_3D; ++i) {
        ASSERT_TRUE(fabs(local_moved[i] - global_3D[i]) < pow(0.1, 4));
    }
}

void check_move_and_rotation(const std::string& local_name,
                             const std::string& global_name,
                             const TMatrix<double, 3>& rotation_3D,
                             const TVector<double, 3>& translation_3D) {
    TVector<double, 3> local_3D;
    TVector<double, 3> global_3D;
    std::ifstream read_local(local_name);
    ASSERT_TRUE(read_local.is_open());
    std::ifstream read_global(global_name);
    ASSERT_TRUE(read_global.is_open());
    read_local >> local_3D;
    read_global >> global_3D;
    check_moved(rotation_3D, translation_3D, local_3D, global_3D);
    read_local >> local_3D;
    read_global >> global_3D;
    check_moved(rotation_3D, translation_3D, local_3D, global_3D);
    read_local.close();
    read_global.close();
}

void rotation_z(TMatrix<double, size_of_TVec_3D>& rotation, double rotation_angle) {
    constexpr double pi = acos(-1);
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
