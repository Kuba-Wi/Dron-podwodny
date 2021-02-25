#include <sstream>
#include "TMatrix.hh"
#include "gtest/gtest.h"

struct TMatrixTest : public ::testing::Test {
    const double mat_first = 1;
    const double mat_second = 2;
    const double mat_third = 3;
    const double mat_fourth = 4;
    const double vec_first = 5;
    const double vec_second = 6;

    TMatrix<double, 2> mat_2D;
    TVector<double, 2> vec_2D;
    TMatrixTest() {
        mat_2D(0, 0) = mat_first;
        mat_2D(0, 1) = mat_second;
        mat_2D(1, 0) = mat_third;
        mat_2D(1, 1) = mat_fourth;

        vec_2D[0] = vec_first;
        vec_2D[1] = vec_second;
    }
};

TEST_F(TMatrixTest, bracketsOperatorShouldReturnReferenceAndValueOfMatrixElement) {
    ++mat_2D(0, 0);
    ASSERT_EQ(mat_2D(0, 0), mat_first + 1);
}

TEST_F(TMatrixTest, determinantFunctionShouldReturnDeterminantOfMatrix) {
    ASSERT_EQ(mat_2D.determinant(), mat_first * mat_fourth - mat_second * mat_third);

    TMatrix<double, 3> matrix_3D;
    matrix_3D(0, 0) = 1;
    matrix_3D(0, 1) = 0;
    matrix_3D(0, 2) = 0;
    matrix_3D(1, 0) = 1;
    matrix_3D(1, 1) = 2;
    matrix_3D(1, 2) = 1;
    matrix_3D(2, 0) = 1;
    matrix_3D(2, 1) = 1;
    matrix_3D(2, 2) = 2;
    ASSERT_EQ(matrix_3D.determinant(), 3);
}

TEST_F(TMatrixTest, operatorMultiplyShouldMultiplyMatrixByVector) {
    auto vec_result = mat_2D * vec_2D;
    ASSERT_EQ(vec_result[0], vec_first * mat_first + vec_second * mat_second);
    ASSERT_EQ(vec_result[1], vec_first * mat_third + vec_second * mat_fourth);
}

TEST_F(TMatrixTest, insert_columnFunctionShouldInsertColumnToMatrix) {
    auto mat_result = mat_2D.insert_column(vec_2D, 0);
    ASSERT_EQ(mat_result(0, 0), vec_2D[0]);
    ASSERT_EQ(mat_result(1, 0), vec_2D[1]);
    ASSERT_EQ(mat_result(0, 1), mat_2D(0, 1));
    ASSERT_EQ(mat_result(1, 1), mat_2D(1, 1));
}

TEST(TMatrixTestInput, operatorReadShouldReadFromInput) {
    std::istringstream str("1 2 3 4");
    TMatrix<int, 2> mat_2D;
    str >> mat_2D;
    ASSERT_EQ(mat_2D(0, 0), 1);
    ASSERT_EQ(mat_2D(0, 1), 3);
    ASSERT_EQ(mat_2D(1, 0), 2);
    ASSERT_EQ(mat_2D(1, 1), 4);
}

TEST_F(TMatrixTest, operatorWriteShouldWriteToOutput) {
    TMatrix<int, 2> second_2D;
    std::stringstream str;
    str << mat_2D;
    str >> second_2D;
    ASSERT_EQ(mat_2D(0, 0), second_2D(0, 0));
    ASSERT_EQ(mat_2D(0, 1), second_2D(1, 0));
    ASSERT_EQ(mat_2D(1, 0), second_2D(0, 1));
    ASSERT_EQ(mat_2D(1, 1), second_2D(1, 1));
}
