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

TEST(TVectorTest, operatorPlusShouldAddTVectors) {
    constexpr int first_val = 1;
    constexpr int second_val = 2;
    TVector<int, 2> first_2D;
    TVector<int, 2> second_2D;

    first_2D[0] = first_val;
    first_2D[1] = first_val;
    second_2D[0] = second_val;
    second_2D[1] = second_val;
    auto sum_2D = first_2D + second_2D;

    ASSERT_EQ(sum_2D[0], first_val + second_val);
    ASSERT_EQ(sum_2D[1], first_val + second_val);
}

TEST(TVectorTest, operatorMinusShouldSubstractVectors) {
    constexpr int first_val = 1;
    constexpr int second_val = 2;
    TVector<int, 2> first_2D;
    TVector<int, 2> second_2D;

    first_2D[0] = first_val;
    first_2D[1] = first_val;
    second_2D[0] = second_val;
    second_2D[1] = second_val;
    auto sum_2D = first_2D - second_2D;

    ASSERT_EQ(sum_2D[0], first_val - second_val);
    ASSERT_EQ(sum_2D[1], first_val - second_val);
}

TEST(TVectorTest, operatorMultiplyShouldMultiplyVectorByNumber) {
    constexpr int first_val = 1;
    constexpr int second_val = 2;
    TVector<int, 2> vec_2D;
    vec_2D[0] = first_val;
    vec_2D[1] = first_val;
    vec_2D = vec_2D * second_val;

    ASSERT_EQ(vec_2D[0], first_val * second_val);
    ASSERT_EQ(vec_2D[1], first_val * second_val);
}

TEST(TVectorTest, operatorMultiplyShouldMultiplyVectors) {
    constexpr int first_val = 1;
    constexpr int second_val = 2;
    TVector<int, 2> first_2D;
    TVector<int, 2> second_2D;

    first_2D[0] = first_val;
    first_2D[1] = first_val;
    second_2D[0] = second_val;
    second_2D[1] = second_val;

    auto result = first_2D * second_2D;
    ASSERT_EQ(result, 2 * first_val * second_val);
}

TEST(TVectorTest, operatorDivideShouldDivideVectorByNumber) {
    constexpr int first_val = 4;
    constexpr int second_val = 2;
    TVector<int, 2> vec_2D;
    vec_2D[0] = first_val;
    vec_2D[1] = first_val;
    vec_2D = vec_2D / second_val;

    ASSERT_EQ(vec_2D[0], first_val / second_val);
    ASSERT_EQ(vec_2D[1], first_val / second_val);
}

TEST(TVectorTest, lengthFunctionShouldReturnLengthOfVector) {
    constexpr double first_val = 3;
    constexpr double second_val = 4;
    constexpr double len = 5;
    TVector<double, 2> vec_2D;
    vec_2D[0] = first_val;
    vec_2D[1] = second_val;
    ASSERT_EQ(vec_2D.lenght(), len);
}
