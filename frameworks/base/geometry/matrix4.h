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

#ifndef FOUNDATION_ACE_FRAMEWORKS_BASE_GEOMETRY_MATRIX4_H
#define FOUNDATION_ACE_FRAMEWORKS_BASE_GEOMETRY_MATRIX4_H

#include "base/geometry/point.h"

namespace OHOS::Ace {

class ACE_EXPORT Matrix4 final {
public:
    // Matrix dimension is 4X4.
    static constexpr int32_t DIMENSION = 4;
    // Crate an identity matrix.
    static Matrix4 CreateIdentity();
    // Multiplies this matrix by another that translates coordinates by the vector (x, y, z).
    static Matrix4 CreateTranslate(float x, float y, float z);
    // Multiplies this matrix by another that scales coordinates by the vector (x, y, z).
    static Matrix4 CreateScale(float x, float y, float z);
    // Multiplies this matrix by another that rotates coordinates through angle degrees about the vector (dx, dy, dz).
    static Matrix4 CreateRotate(float angle, float dx, float dy, float dz);
    // Returns the inverse of this matrix. Returns the identity if this matrix cannot be inverted;
    static Matrix4 Invert(const Matrix4& matrix);

    Matrix4();
    Matrix4(const Matrix4& matrix);
    Matrix4(
        float m00, float m01, float m02, float m03,
        float m10, float m11, float m12, float m13,
        float m20, float m21, float m22, float m23,
        float m30, float m31, float m32, float m33);
    ~Matrix4() = default;
    void SetScale(float x, float y, float z);
    float GetScaleX() const;
    float GetScaleY() const;
    void Rotate(float angle, float dx, float dy, float dz);
    void SetEntry(int32_t row, int32_t col, float value);
    bool IsIdentityMatrix() const;
    int32_t Count() const;

    bool operator==(const Matrix4& matrix) const;
    Matrix4 operator*(float num);
    Matrix4 operator*(const Matrix4& matrix);
    // Transform point by the matrix
    Point operator*(const Point& point);
    Matrix4& operator=(const Matrix4& matrix);
    float operator[](int32_t index) const;

private:
    static Matrix4 CreateInvert(const Matrix4& matrix);
    float operator()(int32_t row, int32_t col) const;

    float matrix4x4_[DIMENSION][DIMENSION] = {
        { 0.0f, 0.0f, 0.0f, 0.0f },
        { 0.0f, 0.0f, 0.0f, 0.0f },
        { 0.0f, 0.0f, 0.0f, 0.0f },
        { 0.0f, 0.0f, 0.0f, 0.0f },
    };
};

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_BASE_GEOMETRY_MATRIX4_H
