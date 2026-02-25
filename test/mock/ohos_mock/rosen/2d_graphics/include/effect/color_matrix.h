/*
 * Copyright (c) 2021-2023 Huawei Device Co., Ltd.
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

#ifndef COLOR_MATRIX_H
#define COLOR_MATRIX_H

#include "utils/scalar.h"

namespace OHOS {
namespace Rosen {
namespace Drawing {
class ColorMatrix {
public:
    enum Index {
        SCALE_FACTOR_FOR_R = 0,
        G_FACTOR_FOR_R = 1,
        B_FACTOR_FOR_R = 2,
        A_FACTOR_FOR_R = 3,
        TRANS_FOR_R = 4,

        R_FACTOR_FOR_G = 5,
        SCALE_FACTOR_FOR_G = 6,
        B_FACTOR_FOR_G = 7,
        A_FACTOR_FOR_G = 8,
        TRANS_FOR_G = 9,

        R_FACTOR_FOR_B = 10,
        G_FACTOR_FOR_B = 11,
        SCALE_FACTOR_FOR_B = 12,
        A_FACTOR_FOR_B = 13,
        TRANS_FOR_B = 14,

        R_FACTOR_FOR_A = 15,
        G_FACTOR_FOR_A = 16,
        B_FACTOR_FOR_A = 17,
        SCALE_FACTOR_FOR_A = 18,
        TRANS_FOR_A = 19,
    };

    // Color matrix is a 4x5 float type matrix.
    constexpr static int MATRIX_SIZE = 20;
    ColorMatrix() noexcept;
    ~ColorMatrix();

    void SetIdentity();
    void SetArray(const scalar src[MATRIX_SIZE]);
    void GetArray(scalar (&dst)[MATRIX_SIZE]) const;
    void SetConcat(const ColorMatrix& m1, const ColorMatrix& m2);
    void PreConcat(const ColorMatrix& m);
    void PostConcat(const ColorMatrix& m);
    void SetScale(scalar sr, scalar sg, scalar sb, scalar sa);

    /*
     * @brief      Set the ColorMatrix to a saturation matrix.
     * @param sat  Saturation value, 0 maps to gray-scale, 1 is identity
     */
    void SetSaturation(scalar sat);

private:
    scalar array_[MATRIX_SIZE] = { 0 };
};
} // namespace Drawing
} // namespace Rosen
} // namespace OHOS
#endif
