#include "testFuctions.hh"
#include "gtest/gtest.h"
#include <algorithm>
#include <fstream>

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
