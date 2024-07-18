/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <cmath>

#include "gtest/gtest.h"

#include "base/geometry/matrix3.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace {
namespace {
constexpr double DEFAULT_DOUBLE0 = 0.0;
constexpr double DEFAULT_DOUBLE1 = 1.0;
constexpr double DEFAULT_DOUBLE2 = 2.0;
constexpr double DEFAULT_DOUBLE3 = 3.0;

constexpr int32_t VALID_ROW0 = 0;
constexpr int32_t VALID_COL0 = 0;
constexpr int32_t VALID_ROW1 = 1;
constexpr int32_t VALID_COL1 = 1;
constexpr int32_t VALID_ROW2 = 2;
constexpr int32_t VALID_COL2 = 2;
constexpr uint32_t VALID_DIMENSION = 3;

constexpr int32_t INVALID_ROW_NEG = -1;
constexpr int32_t INVALID_COL_NEG = -1;
constexpr int32_t INVALID_ROW_POS = 5;
constexpr int32_t INVALID_COL_POS = 5;

constexpr uint32_t ROW_NUM = 4;
constexpr uint32_t COLUMN_NUM = 4;
} // namespace

class Matrix3Test : public testing::Test {};

/**
 * @tc.name: Matrix3Test001
 * @tc.desc: Test the function SetEntry of the classes Matrix3, Matrix3N and MatrixN3.
 * @tc.type: FUNC
 */
HWTEST_F(Matrix3Test, Matrix3Test001, TestSize.Level1)
{
    /**
     * @tc.steps1: initialize parameters.
     */
    Matrix3 matrixObj1;
    std::string initStrObj1 = matrixObj1.ToString();
    Matrix3N matrix3NObj1(COLUMN_NUM);
    std::string initStr3NObj1 = matrix3NObj1.ToString();
    MatrixN3 matrixN3Obj1(ROW_NUM);
    std::string initStrN3Obj1 = matrixN3Obj1.ToString();

    /**
     * @tc.steps2: Call the function SetEntry of the classes Matrix3.
     * @tc.expected: Set the value of a legal location, the value of the corresponding location changes normally.
     *               Set the value of an illegal location, there is no change.
     */
    matrixObj1.SetEntry(INVALID_ROW_NEG, INVALID_COL_NEG, DEFAULT_DOUBLE1);
    EXPECT_EQ(matrixObj1.ToString(), initStrObj1);
    matrixObj1.SetEntry(INVALID_ROW_POS, INVALID_COL_POS, DEFAULT_DOUBLE1);
    EXPECT_EQ(matrixObj1.ToString(), initStrObj1);
    matrixObj1.SetEntry(VALID_ROW0, VALID_COL0, DEFAULT_DOUBLE1);
    EXPECT_DOUBLE_EQ(matrixObj1[VALID_ROW0][VALID_COL0], DEFAULT_DOUBLE1);

    /**
     * @tc.steps3: Call the function SetEntry of the classes Matrix3N.
     * @tc.expected: Set the value of a legal location, the value of the corresponding location changes normally.
     *               Set the value of an illegal location, there is no change.
     */
    matrix3NObj1.SetEntry(INVALID_ROW_POS, INVALID_COL_POS, DEFAULT_DOUBLE1);
    EXPECT_EQ(matrix3NObj1.ToString(), initStr3NObj1);
    matrix3NObj1.SetEntry(VALID_ROW0, VALID_COL0, DEFAULT_DOUBLE1);
    EXPECT_DOUBLE_EQ(matrix3NObj1[VALID_ROW0][VALID_COL0], DEFAULT_DOUBLE1);

    /**
     * @tc.steps4: Call the function SetEntry of the classes MatrixN3.
     * @tc.expected: Set the value of a legal location, the value of the corresponding location changes normally.
     *               Set the value of an illegal location, there is no change.
     */
    matrixN3Obj1.SetEntry(INVALID_ROW_POS, INVALID_COL_POS, DEFAULT_DOUBLE1);
    EXPECT_EQ(matrixN3Obj1.ToString(), initStrN3Obj1);
    matrixN3Obj1.SetEntry(VALID_ROW0, VALID_COL0, DEFAULT_DOUBLE1);
    EXPECT_DOUBLE_EQ(matrixN3Obj1[VALID_ROW0][VALID_COL0], DEFAULT_DOUBLE1);
}

/**
 * @tc.name: Matrix3Test002
 * @tc.desc: Test the function Transpose of the classes Matrix3, Matrix3N and MatrixN3.
 * @tc.type: FUNC
 */
HWTEST_F(Matrix3Test, Matrix3Test002, TestSize.Level1)
{
    /**
     * @tc.steps1: initialize parameters.
     */
    Matrix3 matrixObj1;
    matrixObj1.SetEntry(VALID_ROW0, VALID_COL2, DEFAULT_DOUBLE1);
    Matrix3N matrix3NObj1(COLUMN_NUM);
    matrix3NObj1.SetEntry(VALID_ROW0, VALID_COL2, DEFAULT_DOUBLE1);
    MatrixN3 matrixN3Obj1(ROW_NUM);
    matrixN3Obj1.SetEntry(VALID_ROW0, VALID_COL2, DEFAULT_DOUBLE1);

    /**
     * @tc.steps2: Call the function Transpose of the classes Matrix3.
     * @tc.expected: The value of corresponding locations of two matrixes is equal.
     */
    Matrix3 matrixObj2 = matrixObj1.Transpose();
    EXPECT_DOUBLE_EQ(matrixObj2[VALID_ROW2][VALID_COL0], DEFAULT_DOUBLE1);

    /**
     * @tc.steps3: Call the function Transpose of the classes Matrix3N.
     * @tc.expected: The value of corresponding locations of two matrixes is equal.
     */
    MatrixN3 matrixN3Obj2 = matrix3NObj1.Transpose();
    EXPECT_DOUBLE_EQ(matrixN3Obj2[VALID_ROW2][VALID_COL0], DEFAULT_DOUBLE1);

    /**
     * @tc.steps4: Call the function Transpose of the classes MatrixN3.
     * @tc.expected: The value of corresponding locations of two matrixes is equal.
     */
    Matrix3N matrix3NObj2 = matrixN3Obj1.Transpose();
    EXPECT_DOUBLE_EQ(matrix3NObj2[VALID_ROW2][VALID_COL0], DEFAULT_DOUBLE1);
}

/**
 * @tc.name: Matrix3Test003
 * @tc.desc: Test the function inverse of the class Matrix3.
 * @tc.type: FUNC
 */
HWTEST_F(Matrix3Test, Matrix3Test003, TestSize.Level1)
{
    /**
     * @tc.steps1: initialize parameters.
     */
    Matrix3 matrixObj1;
    matrixObj1.SetEntry(VALID_ROW0, VALID_COL0, DEFAULT_DOUBLE1);
    Matrix3 matrixObj2;
    std::string initStrObj2 = matrixObj2.ToString();

    /**
     * @tc.steps2: Call the function inverse of the matrix with determinant 0.
     * @tc.expected: The function inverse does not work, and the matrix matrixObj2 is not changed.
     */
    EXPECT_FALSE(matrixObj1.Invert(matrixObj2));
    EXPECT_EQ(matrixObj2.ToString(), initStrObj2);

    /**
     * @tc.steps3: Set the matrix matrixObj1 to identity matrix.
     */
    matrixObj1.SetEntry(VALID_ROW1, VALID_COL1, DEFAULT_DOUBLE1);
    matrixObj1.SetEntry(VALID_ROW2, VALID_COL2, DEFAULT_DOUBLE1);

    /**
     * @tc.steps4: Call the function inverse of the identity matrix.
     * @tc.expected: The inverse matrix of matrixObj2 is the identity matrix, and is set to the matrix matrixObj2.
     */
    EXPECT_TRUE(matrixObj1.Invert(matrixObj2));
    EXPECT_NE(matrixObj2.ToString(), initStrObj2);
    EXPECT_DOUBLE_EQ(matrixObj2[VALID_ROW0][VALID_COL0], DEFAULT_DOUBLE1);
    EXPECT_DOUBLE_EQ(matrixObj2[VALID_ROW1][VALID_COL1], DEFAULT_DOUBLE1);
    EXPECT_DOUBLE_EQ(matrixObj2[VALID_ROW2][VALID_COL2], DEFAULT_DOUBLE1);
}

/**
 * @tc.name: Matrix3Test004
 * @tc.desc: Test the function operator* of classes Matrix3 and Matrix3N.
 * @tc.type: FUNC
 */
HWTEST_F(Matrix3Test, Matrix3Test004, TestSize.Level1)
{
    /**
     * @tc.steps1: initialize parameters.
     */
    Matrix3 matrixObj1;
    matrixObj1.SetEntry(VALID_ROW0, VALID_COL0, DEFAULT_DOUBLE1);
    matrixObj1.SetEntry(VALID_ROW1, VALID_COL1, DEFAULT_DOUBLE1);
    matrixObj1.SetEntry(VALID_ROW2, VALID_COL2, DEFAULT_DOUBLE1);
    Matrix3N matrix3NObj1(COLUMN_NUM);
    matrix3NObj1.SetEntry(VALID_ROW0, VALID_COL0, DEFAULT_DOUBLE1);
    matrix3NObj1.SetEntry(VALID_ROW1, VALID_COL1, DEFAULT_DOUBLE2);
    matrix3NObj1.SetEntry(VALID_ROW2, VALID_COL2, DEFAULT_DOUBLE3);
    MatrixN3 matrixN3Obj1(ROW_NUM);
    matrixN3Obj1.SetEntry(VALID_ROW0, VALID_COL0, DEFAULT_DOUBLE1);
    matrixN3Obj1.SetEntry(VALID_ROW1, VALID_COL1, 1.0 / DEFAULT_DOUBLE2);
    matrixN3Obj1.SetEntry(VALID_ROW2, VALID_COL2, 1.0 / DEFAULT_DOUBLE3);

    /**
     * @tc.steps2:  Call the function operator* of classes Matrix3 with the identity matrix matrixObj1.
     * @tc.expected: The product of matrixes matrixObj1 and matrix3NObj1 is equal to matrix3NObj2.
     */
    Matrix3N matrix3NObj2 = matrixObj1 * matrix3NObj1;
    EXPECT_EQ(matrix3NObj1.ToString(), matrix3NObj2.ToString());

    /**
     * @tc.steps3:  Call the function operator* of classes Matrix3N.
     * @tc.expected: The product of matrixes matrix3NObj1 and matrixN3Obj1 is equal to matrixObj1.
     */
    Matrix3 matrixObj2 = matrix3NObj1 * matrixN3Obj1;
    EXPECT_EQ(matrixObj2.ToString(), matrixObj1.ToString());
}

/**
 * @tc.name: Matrix3Test005
 * @tc.desc: Test the function MapScalars of the class Matrix3.
 * @tc.type: FUNC
 */
HWTEST_F(Matrix3Test, Matrix3Test005, TestSize.Level1)
{
    /**
     * @tc.steps1: initialize parameters.
     */
    Matrix3 matrixObj1;
    matrixObj1.SetEntry(VALID_ROW0, VALID_COL0, DEFAULT_DOUBLE1);
    matrixObj1.SetEntry(VALID_ROW1, VALID_COL1, DEFAULT_DOUBLE2);
    matrixObj1.SetEntry(VALID_ROW2, VALID_COL2, DEFAULT_DOUBLE3);

    /**
     * @tc.steps2: Given the vector srcVec whose size is invalid, test the
     *            function MapScalars with single parameter.
     * @tc.expected: The function MapScalars does not work and all values of the return vector are equal to zero.
     */
    std::vector<double> srcVec = { DEFAULT_DOUBLE1, DEFAULT_DOUBLE1 };
    std::vector<double> dstVec = matrixObj1.MapScalars(srcVec);
    EXPECT_EQ(dstVec.size(), VALID_DIMENSION);
    EXPECT_EQ(dstVec[0], DEFAULT_DOUBLE0);
    EXPECT_EQ(dstVec[1], DEFAULT_DOUBLE0);
    EXPECT_EQ(dstVec[2], DEFAULT_DOUBLE0);

    /**
     * @tc.steps3: Given the vector srcVec whose size is valid, test the
     *            function MapScalars with single parameter.
     * @tc.expected: The values of return vector is equal to values on the diagonal of matrixObj1.
     */
    srcVec.push_back(DEFAULT_DOUBLE1);
    dstVec = matrixObj1.MapScalars(srcVec);
    EXPECT_EQ(dstVec[0], DEFAULT_DOUBLE1);
    EXPECT_EQ(dstVec[1], DEFAULT_DOUBLE2);
    EXPECT_EQ(dstVec[2], DEFAULT_DOUBLE3);

    /**
     * @tc.steps4: Given the vector srcVec whose size is invalid, test the
     *            function MapScalars with two parameters.
     * @tc.expected: The function MapScalars does not work and the return vector is empty.
     */
    srcVec.clear();
    dstVec.clear();
    srcVec.push_back(DEFAULT_DOUBLE1);
    srcVec.push_back(DEFAULT_DOUBLE1);
    EXPECT_FALSE(matrixObj1.MapScalars(srcVec, dstVec));
    EXPECT_TRUE(dstVec.empty());

    /**
     * @tc.steps5: Given the vector srcVec whose size is valid, test the
     *            function MapScalars with two parameters.
     * @tc.expected: The values of return vector is equal to values on the diagonal of matrixObj1.
     */
    srcVec.push_back(DEFAULT_DOUBLE1);
    EXPECT_TRUE(matrixObj1.MapScalars(srcVec, dstVec));
    EXPECT_EQ(dstVec[0], DEFAULT_DOUBLE1);
    EXPECT_EQ(dstVec[1], DEFAULT_DOUBLE2);
    EXPECT_EQ(dstVec[2], DEFAULT_DOUBLE3);
}

/**
 * @tc.name: Matrix3Test006
 * @tc.desc: Test the function MapScalars of the class Matrix3N.
 * @tc.type: FUNC
 */
HWTEST_F(Matrix3Test, Matrix3Test006, TestSize.Level1)
{
    /**
     * @tc.steps1: initialize parameters.
     */
    Matrix3N matrix3NObj1(COLUMN_NUM);
    matrix3NObj1.SetEntry(VALID_ROW0, VALID_COL0, DEFAULT_DOUBLE1);
    matrix3NObj1.SetEntry(VALID_ROW1, VALID_COL1, DEFAULT_DOUBLE2);
    matrix3NObj1.SetEntry(VALID_ROW2, VALID_COL2, DEFAULT_DOUBLE3);

    /**
     * @tc.steps2: Given the vector srcVec whose size is invalid, test the
     *            function MapScalars with single parameter.
     * @tc.expected: The function MapScalars does not work and all values of the return vector are equal to zero.
     */
    std::vector<double> srcVec = { DEFAULT_DOUBLE1, DEFAULT_DOUBLE1 };
    std::vector<double> dstVec = matrix3NObj1.MapScalars(srcVec);
    EXPECT_EQ(dstVec.size(), VALID_DIMENSION);
    EXPECT_EQ(dstVec[0], DEFAULT_DOUBLE0);
    EXPECT_EQ(dstVec[1], DEFAULT_DOUBLE0);
    EXPECT_EQ(dstVec[2], DEFAULT_DOUBLE0);

    /**
     * @tc.steps3: Given the vector srcVec whose size is valid, test the
     *            function MapScalars with single parameter.
     * @tc.expected: The values of return vector is equal to values on the diagonal of matrix3NObj1.
     */
    srcVec.push_back(DEFAULT_DOUBLE1);
    srcVec.push_back(DEFAULT_DOUBLE1);
    dstVec = matrix3NObj1.MapScalars(srcVec);
    EXPECT_EQ(dstVec[0], DEFAULT_DOUBLE1);
    EXPECT_EQ(dstVec[1], DEFAULT_DOUBLE2);
    EXPECT_EQ(dstVec[2], DEFAULT_DOUBLE3);

    /**
     * @tc.steps4: Given the vector srcVec whose size is invalid, test the
     *            function MapScalars with two parameters.
     * @tc.expected: The function MapScalars does not work and the return vector is empty.
     */
    srcVec.clear();
    dstVec.clear();
    srcVec.push_back(DEFAULT_DOUBLE1);
    srcVec.push_back(DEFAULT_DOUBLE1);
    EXPECT_FALSE(matrix3NObj1.MapScalars(srcVec, dstVec));
    EXPECT_TRUE(dstVec.empty());

    /**
     * @tc.steps: Given the vector srcVec whose size is valid, test the
     *            function MapScalars with two parameters.
     * @tc.expected: The values of return vector is equal to values on the diagonal of matrix3NObj1.
     */
    srcVec.push_back(DEFAULT_DOUBLE1);
    srcVec.push_back(DEFAULT_DOUBLE1);
    EXPECT_TRUE(matrix3NObj1.MapScalars(srcVec, dstVec));
    EXPECT_EQ(dstVec[0], DEFAULT_DOUBLE1);
    EXPECT_EQ(dstVec[1], DEFAULT_DOUBLE2);
    EXPECT_EQ(dstVec[2], DEFAULT_DOUBLE3);
}

/**
 * @tc.name: Matrix3Test007
 * @tc.desc: Test the function MapScalars of the class MatrixN3.
 * @tc.type: FUNC
 */
HWTEST_F(Matrix3Test, Matrix3Test007, TestSize.Level1)
{
    /**
     * @tc.steps1: initialize parameters.
     */
    MatrixN3 matrixN3Obj1(ROW_NUM);
    matrixN3Obj1.SetEntry(VALID_ROW0, VALID_COL0, DEFAULT_DOUBLE1);
    matrixN3Obj1.SetEntry(VALID_ROW1, VALID_COL1, DEFAULT_DOUBLE2);
    matrixN3Obj1.SetEntry(VALID_ROW2, VALID_COL2, DEFAULT_DOUBLE3);

    /**
     * @tc.steps2: Given the vector srcVec whose size is invalid, test the function MapScalars.
     * @tc.expected: The function MapScalars does not work and all values of the return vector are equal to zero.
     */
    std::vector<double> srcVec = { DEFAULT_DOUBLE1, DEFAULT_DOUBLE1 };
    std::vector<double> dstVec = matrixN3Obj1.MapScalars(srcVec);
    EXPECT_EQ(dstVec.size(), ROW_NUM);
    EXPECT_EQ(dstVec[0], DEFAULT_DOUBLE0);
    EXPECT_EQ(dstVec[1], DEFAULT_DOUBLE0);
    EXPECT_EQ(dstVec[2], DEFAULT_DOUBLE0);
    EXPECT_EQ(dstVec[3], DEFAULT_DOUBLE0);

    /**
     * @tc.steps3: Given the vector srcVec whose size is valid, test the function MapScalars.
     * @tc.expected: The values of return vector is equal to values on the diagonal of matrixN3Obj1.
     */
    srcVec.push_back(DEFAULT_DOUBLE1);
    dstVec = matrixN3Obj1.MapScalars(srcVec);
    EXPECT_EQ(dstVec[0], DEFAULT_DOUBLE1);
    EXPECT_EQ(dstVec[1], DEFAULT_DOUBLE2);
    EXPECT_EQ(dstVec[2], DEFAULT_DOUBLE3);
    EXPECT_EQ(dstVec[3], DEFAULT_DOUBLE0);
}

/**
 * @tc.name: Matrix3Test008
 * @tc.desc: Test the function SetEntry for Matrix3/Matrix3N
 * @tc.type: FUNC
 */
HWTEST_F(Matrix3Test, Matrix3Test008, TestSize.Level1)
{
    /**
     * @tc.steps1: initialize parameters.Matrix3::SetEntry: index out of range
     */
    Matrix3 matrixObj1;
    // true false false false
    matrixObj1.SetEntry(-1, 2, 5.0f);
    // false true false false
    matrixObj1.SetEntry(10, 2, 5.0f);
    // false false true false
    matrixObj1.SetEntry(0, -1, 5.0f);
    // false false false true
    matrixObj1.SetEntry(0, 10, 5.0f);
    // false false false false
    matrixObj1.SetEntry(0, 2, 5.0f);
    EXPECT_EQ(matrixObj1(0, 2) == 5.0f, true);

    /**
     * @tc.steps2: Matrix3N::SetEntry: index out of range
     */
    Matrix3N matrix3NObj1(3);
    // true false
    bool ret = matrix3NObj1.SetEntry(10, 2, 5.0f);
    EXPECT_FALSE(ret);
    // false true
    bool ret2 = matrix3NObj1.SetEntry(0, 3, 5.0f);
    EXPECT_FALSE(ret2);
    // false false
    bool ret3 = matrix3NObj1.SetEntry(0, 2, 5.0f);
    EXPECT_TRUE(ret3);

    /**
     * @tc.steps3: MatrixN3::SetEntry: index out of range
     */
    MatrixN3 matrixN3Obj1(3);
    // true false
    bool ret4 = matrixN3Obj1.SetEntry(3, 2, 5.0f);
    EXPECT_FALSE(ret4);
    // false true
    bool ret5 = matrixN3Obj1.SetEntry(0, 10, 5.0f);
    EXPECT_FALSE(ret5);
    // false false
    bool ret6 = matrixN3Obj1.SetEntry(0, 2, 5.0f);
    EXPECT_TRUE(ret6);

    // Matrix3N::operator*: matrix size not match
    MatrixN3 matrixN3Obj2(2);
    Matrix3 ret7 = matrix3NObj1 * matrixN3Obj2;
    EXPECT_EQ(ret7(0, 0) == 0.0f, true);
}
} // namespace OHOS::Ace
