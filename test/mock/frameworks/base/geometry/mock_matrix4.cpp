/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

namespace OHOS::Ace {
Matrix4 Matrix4::CreateIdentity()
{
    return Matrix4();
}

Matrix4::Matrix4()
{
    for (int32_t col = 0; col < DIMENSION; ++col) {
        for (int32_t row = 0; row < DIMENSION; ++row) {
            matrix4x4_[col][row] = (col == row) ? 1.0 : 0.0;
        }
    }
}

Matrix4::Matrix4(const Matrix4& matrix)
{
    for (int32_t col = 0; col < DIMENSION; ++col) {
        for (int32_t row = 0; row < DIMENSION; ++row) {
            matrix4x4_[col][row] = matrix.matrix4x4_[col][row];
        }
    }
}

Matrix4& Matrix4::operator=(const Matrix4& matrix)
{
    if (this != &matrix) {
        for (int32_t col = 0; col < DIMENSION; ++col) {
            for (int32_t row = 0; row < DIMENSION; ++row) {
                matrix4x4_[col][row] = matrix.matrix4x4_[col][row];
            }
        }
    }
    return *this;
}

bool Matrix4::operator==(const Matrix4& matrix) const
{
    for (int32_t col = 0; col < DIMENSION; ++col) {
        for (int32_t row = 0; row < DIMENSION; ++row) {
            if (matrix4x4_[col][row] != matrix.matrix4x4_[col][row]) {
                return false;
            }
        }
    }
    return true;
}
std::string Matrix4::ToString() const
{
    return "";
}
} // namespace OHOS::Ace

namespace OHOS::Ace {
Matrix4::Matrix4(double m00, double m01, double m02, double m03, double m10, double m11, double m12, double m13,
    double m20, double m21, double m22, double m23, double m30, double m31, double m32, double m33)
{
    matrix4x4_[0][0] = static_cast<float>(m00);
    matrix4x4_[0][1] = static_cast<float>(m01);
    matrix4x4_[0][2] = static_cast<float>(m02);
    matrix4x4_[0][3] = static_cast<float>(m03);
    matrix4x4_[1][0] = static_cast<float>(m10);
    matrix4x4_[1][1] = static_cast<float>(m11);
    matrix4x4_[1][2] = static_cast<float>(m12);
    matrix4x4_[1][3] = static_cast<float>(m13);
    matrix4x4_[2][0] = static_cast<float>(m20);
    matrix4x4_[2][1] = static_cast<float>(m21);
    matrix4x4_[2][2] = static_cast<float>(m22);
    matrix4x4_[2][3] = static_cast<float>(m23);
    matrix4x4_[3][0] = static_cast<float>(m30);
    matrix4x4_[3][1] = static_cast<float>(m31);
    matrix4x4_[3][2] = static_cast<float>(m32);
    matrix4x4_[3][3] = static_cast<float>(m33);
}
} // namespace OHOS::Ace
