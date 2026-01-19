/*
 * Copyright (c) 2021-2024 Huawei Device Co., Ltd.
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

#ifndef MATRIX_H
#define MATRIX_H

#include <array>
#include <iostream>
#include <vector>

#include "utils/rect.h"
#include "utils/scalar.h"
#include "utils/point.h"

namespace OHOS {
namespace Rosen {
namespace Drawing {
enum class ScaleToFit {
    FILL_SCALETOFIT,
    START_SCALETOFIT,
    CENTER_SCALETOFIT,
    END_SCALETOFIT,
};

class Matrix {
public:
    // Matrix is a 3x3 float type matrix.
    static constexpr int MATRIX_SIZE = 9;
    static constexpr size_t ROW0 = 0;
    static constexpr size_t ROW1 = 1;
    static constexpr size_t ROW2 = 2;
    static constexpr size_t ROW3 = 3;
    static constexpr size_t COL0 = 0;
    static constexpr size_t COL1 = 1;
    static constexpr size_t COL2 = 2;
    static constexpr size_t COL3 = 3;
    using Buffer = std::array<scalar, MATRIX_SIZE>;

    enum Index {
        SCALE_X = 0,
        SKEW_X,
        TRANS_X,
        SKEW_Y,
        SCALE_Y,
        TRANS_Y,
        PERSP_0,
        PERSP_1,
        PERSP_2,
    };

    Matrix();
    Matrix(const Matrix& matrix);
    Matrix& operator=(const Matrix& matrix);
    virtual ~Matrix() {}
    static Matrix Skew(scalar kx, scalar ky)
    {
        Matrix m;
        m.SetSkew(kx, ky);
        return m;
    }

    void Rotate(scalar degree, scalar px, scalar py);
    void Translate(scalar dx, scalar dy);
    void Scale(scalar sx, scalar sy, scalar px, scalar py);
    void SetConcat(const Matrix& a, const Matrix& b);
    void SetScale(scalar sx, scalar sy);
    void SetScaleTranslate(scalar sx, scalar sy, scalar dx, scalar dy);

    void SetSinCos(scalar sinValue, scalar cosValue, scalar px, scalar py);

    void SetSkew(scalar kx, scalar ky);
    void SetSkew(scalar kx, scalar ky, scalar px, scalar py);

    void PreRotate(scalar degree);

    void PostRotate(scalar degree);

    void PostRotate(scalar degree, scalar px, scalar py);

    void PreTranslate(scalar dx, scalar dy);

    void PostTranslate(scalar dx, scalar dy);

    void PreScale(scalar sx, scalar sy);

    void PostScale(scalar sx, scalar sy);

    void PostScale(scalar sx, scalar sy, scalar px, scalar py);

    void PreSkew(scalar kx, scalar ky);

    void PostSkew(scalar kx, scalar ky);

    void PreSkew(scalar kx, scalar ky, scalar px, scalar py);

    void PostSkew(scalar kx, scalar ky, scalar px, scalar py);

    void PreConcat(const Matrix& other);

    void PostConcat(const Matrix& other);

    bool Invert(Matrix& inverse) const;
    Matrix operator*(const Matrix& other);

    bool operator==(const Matrix& other) const;
    void SetMatrix(scalar scaleX, scalar skewX, scalar transX, scalar skewY, scalar scaleY, scalar transY,
        scalar persp0, scalar persp1, scalar persp2);

    bool SetRectToRect(const Rect& src, const Rect& dst, ScaleToFit stf);

    void MapPoints(std::vector<Point>& dst, const std::vector<Point>& src, uint32_t count) const;

    scalar MapRadius(scalar radius) const;

    bool MapRect(Rect& dst, const Rect& src) const;

    bool SetPolyToPoly(const Point src[], const Point dst[], uint32_t count);

    void Set(Index index, scalar value);
    scalar Get(int index) const;

    void GetAll(Buffer& buffer) const;

    /**
     * @brief         Copies nine scalar values contained by Matrix from buffer.
     * @param buffer  Storage for nine scalar values
     */
    void SetAll(Buffer& buffer);

    bool IsAffine() const;

    bool IsIdentity() const;

    void PreRotate(scalar degree, scalar px, scalar py);
    void PreScale(scalar sx, scalar sy, scalar px, scalar py);

    bool RectStaysRect() const;

    void Reset();

    bool GetMinMaxScales(scalar scaleFactors[2]);
    bool HasPerspective() const;

    void Swap(Matrix& target);
};
} // namespace Drawing
} // namespace Rosen
} // namespace OHOS
#endif
