#include <sstream>
#include "TVector.hh"
#include "gtest/gtest.h"

TEST(TVectorTest, numberOfAllAndCurrentTVectorsShouldChange) {
    constexpr int number_of_vectors_3D = 1;
    TVector<int, 5> vec_5D;
    ASSERT_EQ(vec_5D.return_all_vectors_3D(), 0);
    ASSERT_EQ(vec_5D.return_current_vectors_3D(), 0);
    {
        TVector<int, 3> vec_3D;
        ASSERT_EQ(vec_3D.return_all_vectors_3D(), number_of_vectors_3D);
        ASSERT_EQ(vec_3D.return_current_vectors_3D(), number_of_vectors_3D);
    }
    const int all_vectors = TVector<int, 3>::return_all_vectors_3D();
    const int current_vectors = TVector<int, 3>::return_current_vectors_3D();
    ASSERT_EQ(all_vectors, number_of_vectors_3D);
    ASSERT_EQ(current_vectors, 0);
}

TEST(TVectorTest, squareBracketsOperatorShouldReturnValueAndReference) {
    constexpr int value = 42;
    TVector<int, 3> vec_3D;
    vec_3D[1] = value;
    ++vec_3D[1];
    ASSERT_EQ(vec_3D[1], value + 1);
}

struct TVectorTestInt : public ::testing::Test {
    const int first_val = 1;
    const int second_val = 2;
    TVector<int, 2> first_2D;
    TVector<int, 2> second_2D;
    TVectorTestInt() {
        first_2D[0] = first_val;
        first_2D[1] = first_val;
        second_2D[0] = second_val;
        second_2D[1] = second_val;
    }
};

TEST_F(TVectorTestInt, operatorPlusShouldAddTVectors) {
    auto sum_2D = first_2D + second_2D;
    ASSERT_EQ(sum_2D[0], first_val + second_val);
    ASSERT_EQ(sum_2D[1], first_val + second_val);
}

TEST_F(TVectorTestInt, operatorMinusShouldSubstractVectors) {
    auto difference_2D = first_2D - second_2D;
    ASSERT_EQ(difference_2D[0], first_val - second_val);
    ASSERT_EQ(difference_2D[1], first_val - second_val);
}

TEST_F(TVectorTestInt, operatorMultiplyShouldMultiplyVectors) {
    auto result = first_2D * second_2D;
    ASSERT_EQ(result, 2 * first_val * second_val);
}

TEST_F(TVectorTestInt, operatorMultiplyShouldMultiplyVectorByNumber) {
    constexpr int factor = 4;
    auto vec_2D = first_2D * factor;

    ASSERT_EQ(vec_2D[0], first_val * factor);
    ASSERT_EQ(vec_2D[1], first_val * factor);
}

struct TVectorTestDouble : public ::testing::Test {
    const double first_val = 3;
    const double second_val = 4;
    TVector<double, 2> vec_2D;
    TVectorTestDouble() {
        vec_2D[0] = first_val;
        vec_2D[1] = second_val;
    }
};

TEST_F(TVectorTestDouble, operatorDivideShouldDivideVectorByNumber) {
    constexpr double divisor = 4;
    vec_2D = vec_2D / divisor;

    ASSERT_EQ(vec_2D[0], first_val / divisor);
    ASSERT_EQ(vec_2D[1], second_val / divisor);
}

TEST_F(TVectorTestDouble, lengthFunctionShouldReturnLengthOfVector) {
    constexpr double len = 5;
    ASSERT_EQ(vec_2D.lenght(), len);
}

TEST(TVectorTest, operatorReadShouldReadFromInput) {
    std::istringstream str("0 1 2");
    TVector<int, 3> vec_3D;
    str >> vec_3D;
    ASSERT_EQ(vec_3D[0], 0);
    ASSERT_EQ(vec_3D[1], 1);
    ASSERT_EQ(vec_3D[2], 2);
}

TEST_F(TVectorTestInt, operatorWriteShouldWriteToOutput) {
    std::stringstream str;
    str << first_2D;
    str >> second_2D;
    ASSERT_EQ(first_2D[0], second_2D[0]);
    ASSERT_EQ(first_2D[1], second_2D[1]);
}
