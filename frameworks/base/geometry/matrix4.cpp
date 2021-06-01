/*
 * Copyright (c) 2021 Huawei Device Co., Ltd.
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

#include "base/geometry/matrix4.h"

#include <algorithm>

#include "base/utils/utils.h"

namespace OHOS::Ace {
namespace {

constexpr int32_t MATRIX_LENGTH = Matrix4::DIMENSION * Matrix4::DIMENSION;

inline bool IsEqual(const float& left, const float& right)
{
    return NearEqual(left, right);
}

} // namespace

Matrix4 Matrix4::CreateIdentity()
{
    return Matrix4(
        1.0f, 0.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f);
}

Matrix4 Matrix4::CreateTranslate(float x, float y, float z)
{
    return Matrix4(
        1.0f, 0.0f, 0.0f, x,
        0.0f, 1.0f, 0.0f, y,
        0.0f, 0.0f, 1.0f, z,
        0.0f, 0.0f, 0.0f, 1.0f);
}

Matrix4 Matrix4::CreateScale(float x, float y, float z)
{
    return Matrix4(
        x, 0.0f, 0.0f, 0.0f,
        0.0f, y, 0.0f, 0.0f,
        0.0f, 0.0f, z, 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f);
}

Matrix4 Matrix4::CreateRotate(float angle, float dx, float dy, float dz)
{
    // (x,y,z) need normalize
    float sum = dx * dx + dy * dy + dz * dz;
    if (NearZero(sum)) {
        return Matrix4::CreateIdentity();
    }

    float x = dx / sqrt(sum);
    float y = dy / sqrt(sum);
    float z = dz / sqrt(sum);
    float redian = static_cast<float>(angle * (M_PI / 180.0f));
    float cosValue = cosf(redian);
    float sinValue = sinf(redian);

    return Matrix4(cosValue + (x * x * (1.0f - cosValue)), (x * y * (1.0f - cosValue)) - (z * sinValue),
        (x * z * (1.0f - cosValue)) + (y * sinValue), 0.0f, (y * x * (1.0f - cosValue)) + (z * sinValue),
        cosValue + (y * y * (1.0f - cosValue)), (y * z * (1.0f - cosValue)) - (x * sinValue), 0.0f,
        (z * x * (1.0f - cosValue)) - (y * sinValue), (z * y * (1.0f - cosValue)) + (x * sinValue),
        cosValue + (z * z * (1.0f - cosValue)), 0.0f, 0.0f, 0.0f, 0.0f, 1.0f);
}

Matrix4 Matrix4::Invert(const Matrix4& matrix)
{
    Matrix4 inverted = CreateInvert(matrix);
    float determinant = matrix(0, 0) * inverted(0, 0) +
                        matrix(0, 1) * inverted(1, 0) +
                        matrix(0, 2) * inverted(2, 0) +
                        matrix(0, 3) * inverted(3, 0);

    if (!NearZero(determinant)) {
        inverted = inverted * (1.0f / determinant);
    } else {
        inverted = CreateIdentity();
    }

    return inverted;
}

Matrix4::Matrix4()
    : Matrix4(1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f)
{}

Matrix4::Matrix4(const Matrix4& matrix)
{
    std::copy_n(&matrix.matrix4x4_[0][0], MATRIX_LENGTH, &matrix4x4_[0][0]);
}

Matrix4::Matrix4(float m00, float m01, float m02, float m03, float m10, float m11, float m12, float m13, float m20,
    float m21, float m22, float m23, float m30, float m31, float m32, float m33)
{
    matrix4x4_[0][0] = m00;
    matrix4x4_[1][0] = m01;
    matrix4x4_[2][0] = m02;
    matrix4x4_[3][0] = m03;
    matrix4x4_[0][1] = m10;
    matrix4x4_[1][1] = m11;
    matrix4x4_[2][1] = m12;
    matrix4x4_[3][1] = m13;
    matrix4x4_[0][2] = m20;
    matrix4x4_[1][2] = m21;
    matrix4x4_[2][2] = m22;
    matrix4x4_[3][2] = m23;
    matrix4x4_[0][3] = m30;
    matrix4x4_[1][3] = m31;
    matrix4x4_[2][3] = m32;
    matrix4x4_[3][3] = m33;
}

void Matrix4::SetScale(float x, float y, float z)
{
    // The 4X4 matrix scale index is [0][0], [1][1], [2][2], [3][3].
    matrix4x4_[0][0] = x;
    matrix4x4_[1][1] = y;
    matrix4x4_[2][2] = z;
    matrix4x4_[3][3] = 1.0f;
}

float Matrix4::GetScaleX() const
{
    return matrix4x4_[0][0];
}

float Matrix4::GetScaleY() const
{
    return matrix4x4_[1][1];
}

void Matrix4::SetEntry(int32_t row, int32_t col, float value)
{
    if ((row < 0 || row >= DIMENSION) || (col < 0 || col >= DIMENSION)) {
        return;
    }
    matrix4x4_[row][col] = value;
}

bool Matrix4::IsIdentityMatrix() const
{
    return *this == CreateIdentity();
}

void Matrix4::Rotate(float angle, float dx, float dy, float dz)
{
    Matrix4 transform = *this;
    *this = transform * CreateRotate(angle, dx, dy, dz);
}

int32_t Matrix4::Count() const
{
    return MATRIX_LENGTH;
}

Matrix4 Matrix4::CreateInvert(const Matrix4& matrix)
{
    return Matrix4(
        matrix(1, 1) * matrix(2, 2) * matrix(3, 3) - matrix(1, 1) * matrix(2, 3) * matrix(3, 2) -
            matrix(2, 1) * matrix(1, 2) * matrix(3, 3) + matrix(2, 1) * matrix(1, 3) * matrix(3, 2) +
            matrix(3, 1) * matrix(1, 2) * matrix(2, 3) - matrix(3, 1) * matrix(1, 3) * matrix(2, 2),
        -matrix(1, 0) * matrix(2, 2) * matrix(3, 3) + matrix(1, 0) * matrix(2, 3) * matrix(3, 2) +
            matrix(2, 0) * matrix(1, 2) * matrix(3, 3) - matrix(2, 0) * matrix(1, 3) * matrix(3, 2) -
            matrix(3, 0) * matrix(1, 2) * matrix(2, 3) + matrix(3, 0) * matrix(1, 3) * matrix(2, 2),
        matrix(1, 0) * matrix(2, 1) * matrix(3, 3) - matrix(1, 0) * matrix(2, 3) * matrix(3, 1) -
            matrix(2, 0) * matrix(1, 1) * matrix(3, 3) + matrix(2, 0) * matrix(1, 3) * matrix(3, 1) +
            matrix(3, 0) * matrix(1, 1) * matrix(2, 3) - matrix(3, 0) * matrix(1, 3) * matrix(2, 1),
        -matrix(1, 0) * matrix(2, 1) * matrix(3, 2) + matrix(1, 0) * matrix(2, 2) * matrix(3, 1) +
            matrix(2, 0) * matrix(1, 1) * matrix(3, 2) - matrix(2, 0) * matrix(1, 2) * matrix(3, 1) -
            matrix(3, 0) * matrix(1, 1) * matrix(2, 2) + matrix(3, 0) * matrix(1, 2) * matrix(2, 1),
        -matrix(0, 1) * matrix(2, 2) * matrix(3, 3) + matrix(0, 1) * matrix(2, 3) * matrix(3, 2) +
            matrix(2, 1) * matrix(0, 2) * matrix(3, 3) - matrix(2, 1) * matrix(0, 3) * matrix(3, 2) -
            matrix(3, 1) * matrix(0, 2) * matrix(2, 3) + matrix(3, 1) * matrix(0, 3) * matrix(2, 2),
        matrix(0, 0) * matrix(2, 2) * matrix(3, 3) - matrix(0, 0) * matrix(2, 3) * matrix(3, 2) -
            matrix(2, 0) * matrix(0, 2) * matrix(3, 3) + matrix(2, 0) * matrix(0, 3) * matrix(3, 2) +
            matrix(3, 0) * matrix(0, 2) * matrix(2, 3) - matrix(3, 0) * matrix(0, 3) * matrix(2, 2),
        -matrix(0, 0) * matrix(2, 1) * matrix(3, 3) + matrix(0, 0) * matrix(2, 3) * matrix(3, 1) +
            matrix(2, 0) * matrix(0, 1) * matrix(3, 3) - matrix(2, 0) * matrix(0, 3) * matrix(3, 1) -
            matrix(3, 0) * matrix(0, 1) * matrix(2, 3) + matrix(3, 0) * matrix(0, 3) * matrix(2, 1),
        matrix(0, 0) * matrix(2, 1) * matrix(3, 2) - matrix(0, 0) * matrix(2, 2) * matrix(3, 1) -
            matrix(2, 0) * matrix(0, 1) * matrix(3, 2) + matrix(2, 0) * matrix(0, 2) * matrix(3, 1) +
            matrix(3, 0) * matrix(0, 1) * matrix(2, 2) - matrix(3, 0) * matrix(0, 2) * matrix(2, 1),
        matrix(0, 1) * matrix(1, 2) * matrix(3, 3) - matrix(0, 1) * matrix(1, 3) * matrix(3, 2) -
            matrix(1, 1) * matrix(0, 2) * matrix(3, 3) + matrix(1, 1) * matrix(0, 3) * matrix(3, 2) +
            matrix(3, 1) * matrix(0, 2) * matrix(1, 3) - matrix(3, 1) * matrix(0, 3) * matrix(1, 2),
        -matrix(0, 0) * matrix(1, 2) * matrix(3, 3) + matrix(0, 0) * matrix(1, 3) * matrix(3, 2) +
            matrix(1, 0) * matrix(0, 2) * matrix(3, 3) - matrix(1, 0) * matrix(0, 3) * matrix(3, 2) -
            matrix(3, 0) * matrix(0, 2) * matrix(1, 3) + matrix(3, 0) * matrix(0, 3) * matrix(1, 2),
        matrix(0, 0) * matrix(1, 1) * matrix(3, 3) - matrix(0, 0) * matrix(1, 3) * matrix(3, 1) -
            matrix(1, 0) * matrix(0, 1) * matrix(3, 3) + matrix(1, 0) * matrix(0, 3) * matrix(3, 1) +
            matrix(3, 0) * matrix(0, 1) * matrix(1, 3) - matrix(3, 0) * matrix(0, 3) * matrix(1, 1),
        -matrix(0, 0) * matrix(1, 1) * matrix(3, 2) + matrix(0, 0) * matrix(1, 2) * matrix(3, 1) +
            matrix(1, 0) * matrix(0, 1) * matrix(3, 2) - matrix(1, 0) * matrix(0, 2) * matrix(3, 1) -
            matrix(3, 0) * matrix(0, 1) * matrix(1, 2) + matrix(3, 0) * matrix(0, 2) * matrix(1, 1),
        -matrix(0, 1) * matrix(1, 2) * matrix(2, 3) + matrix(0, 1) * matrix(1, 3) * matrix(2, 2) +
            matrix(1, 1) * matrix(0, 2) * matrix(2, 3) - matrix(1, 1) * matrix(0, 3) * matrix(2, 2) -
            matrix(2, 1) * matrix(0, 2) * matrix(1, 3) + matrix(2, 1) * matrix(0, 3) * matrix(1, 2),
        matrix(0, 0) * matrix(1, 2) * matrix(2, 3) - matrix(0, 0) * matrix(1, 3) * matrix(2, 2) -
            matrix(1, 0) * matrix(0, 2) * matrix(2, 3) + matrix(1, 0) * matrix(0, 3) * matrix(2, 2) +
            matrix(2, 0) * matrix(0, 2) * matrix(1, 3) - matrix(2, 0) * matrix(0, 3) * matrix(1, 2),
        -matrix(0, 0) * matrix(1, 1) * matrix(2, 3) + matrix(0, 0) * matrix(1, 3) * matrix(2, 1) +
            matrix(1, 0) * matrix(0, 1) * matrix(2, 3) - matrix(1, 0) * matrix(0, 3) * matrix(2, 1) -
            matrix(2, 0) * matrix(0, 1) * matrix(1, 3) + matrix(2, 0) * matrix(0, 3) * matrix(1, 1),
        matrix(0, 0) * matrix(1, 1) * matrix(2, 2) - matrix(0, 0) * matrix(1, 2) * matrix(2, 1) -
            matrix(1, 0) * matrix(0, 1) * matrix(2, 2) + matrix(1, 0) * matrix(0, 2) * matrix(2, 1) +
            matrix(2, 0) * matrix(0, 1) * matrix(1, 2) - matrix(2, 0) * matrix(0, 2) * matrix(1, 1));
}

bool Matrix4::operator==(const Matrix4& matrix) const
{
    return std::equal(&matrix4x4_[0][0], &matrix4x4_[0][0] + MATRIX_LENGTH, &matrix.matrix4x4_[0][0], IsEqual);
}

Matrix4 Matrix4::operator*(float num)
{
    Matrix4 ret(*this);
    std::for_each_n(&ret.matrix4x4_[0][0], MATRIX_LENGTH, [num](float& v) { v *= num; });
    return ret;
}

Matrix4 Matrix4::operator*(const Matrix4& matrix)
{
    return Matrix4(
        matrix4x4_[0][0] * matrix(0, 0) + matrix4x4_[1][0] * matrix(0, 1) + matrix4x4_[2][0] * matrix(0, 2) +
            matrix4x4_[3][0] * matrix(0, 3),
        matrix4x4_[0][0] * matrix(1, 0) + matrix4x4_[1][0] * matrix(1, 1) + matrix4x4_[2][0] * matrix(1, 2) +
            matrix4x4_[3][0] * matrix(1, 3),
        matrix4x4_[0][0] * matrix(2, 0) + matrix4x4_[1][0] * matrix(2, 1) + matrix4x4_[2][0] * matrix(2, 2) +
            matrix4x4_[3][0] * matrix(2, 3),
        matrix4x4_[0][0] * matrix(3, 0) + matrix4x4_[1][0] * matrix(3, 1) + matrix4x4_[2][0] * matrix(3, 2) +
            matrix4x4_[3][0] * matrix(3, 3),
        matrix4x4_[0][1] * matrix(0, 0) + matrix4x4_[1][1] * matrix(0, 1) + matrix4x4_[2][1] * matrix(0, 2) +
            matrix4x4_[3][1] * matrix(0, 3),
        matrix4x4_[0][1] * matrix(1, 0) + matrix4x4_[1][1] * matrix(1, 1) + matrix4x4_[2][1] * matrix(1, 2) +
            matrix4x4_[3][1] * matrix(1, 3),
        matrix4x4_[0][1] * matrix(2, 0) + matrix4x4_[1][1] * matrix(2, 1) + matrix4x4_[2][1] * matrix(2, 2) +
            matrix4x4_[3][1] * matrix(2, 3),
        matrix4x4_[0][1] * matrix(3, 0) + matrix4x4_[1][1] * matrix(3, 1) + matrix4x4_[2][1] * matrix(3, 2) +
            matrix4x4_[3][1] * matrix(3, 3),
        matrix4x4_[0][2] * matrix(0, 0) + matrix4x4_[1][2] * matrix(0, 1) + matrix4x4_[2][2] * matrix(0, 2) +
            matrix4x4_[3][2] * matrix(0, 3),
        matrix4x4_[0][2] * matrix(1, 0) + matrix4x4_[1][2] * matrix(1, 1) + matrix4x4_[2][2] * matrix(1, 2) +
            matrix4x4_[3][2] * matrix(1, 3),
        matrix4x4_[0][2] * matrix(2, 0) + matrix4x4_[1][2] * matrix(2, 1) + matrix4x4_[2][2] * matrix(2, 2) +
            matrix4x4_[3][2] * matrix(2, 3),
        matrix4x4_[0][2] * matrix(3, 0) + matrix4x4_[1][2] * matrix(3, 1) + matrix4x4_[2][2] * matrix(3, 2) +
            matrix4x4_[3][2] * matrix(3, 3),
        matrix4x4_[0][3] * matrix(0, 0) + matrix4x4_[1][3] * matrix(0, 1) + matrix4x4_[2][3] * matrix(0, 2) +
            matrix4x4_[3][3] * matrix(0, 3),
        matrix4x4_[0][3] * matrix(1, 0) + matrix4x4_[1][3] * matrix(1, 1) + matrix4x4_[2][3] * matrix(1, 2) +
            matrix4x4_[3][3] * matrix(1, 3),
        matrix4x4_[0][3] * matrix(2, 0) + matrix4x4_[1][3] * matrix(2, 1) + matrix4x4_[2][3] * matrix(2, 2) +
            matrix4x4_[3][3] * matrix(2, 3),
        matrix4x4_[0][3] * matrix(3, 0) + matrix4x4_[1][3] * matrix(3, 1) + matrix4x4_[2][3] * matrix(3, 2) +
            matrix4x4_[3][3] * matrix(3, 3));
}

Point Matrix4::operator*(const Point& point)
{
    double x = point.GetX();
    double y = point.GetY();
    return Point(matrix4x4_[0][0] * x + matrix4x4_[1][0] * y + matrix4x4_[3][0],
                 matrix4x4_[0][1] * x + matrix4x4_[1][1] * y + matrix4x4_[3][1]);
}

Matrix4& Matrix4::operator=(const Matrix4& matrix)
{
    if (this == &matrix) {
        return *this;
    }
    std::copy_n(&matrix.matrix4x4_[0][0], MATRIX_LENGTH, &matrix4x4_[0][0]);
    return *this;
}

float Matrix4::operator[](int32_t index) const
{
    if (index < 0 || index >= MATRIX_LENGTH) {
        return 0.0f;
    }
    int32_t row = index / DIMENSION;
    int32_t col = index % DIMENSION;
    return matrix4x4_[row][col];
}

float Matrix4::operator()(int32_t row, int32_t col) const
{
    // Caller guarantee row and col in range of [0, 3].
    return matrix4x4_[row][col];
}

} // namespace OHOS::Ace