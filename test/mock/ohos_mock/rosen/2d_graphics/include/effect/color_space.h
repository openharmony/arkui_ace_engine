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

#ifndef COLOR_SPACE_H
#define COLOR_SPACE_H

#include <memory>
#include <string>

namespace OHOS {
namespace Rosen {
namespace Drawing {
enum class CMSTransferFuncType {
    SRGB = 0,
    DOT2,
    LINEAR,
    REC2020,
    HLG,
};

enum class CMSMatrixType {
    SRGB = 0,
    ADOBE_RGB,
    DCIP3,
    REC2020,
    XYZ,
};

// CMSMatrix3x3 is a 3x3 float type matrix.
constexpr static int MATRIX3_SIZE = 3;

struct CMSMatrix3x3 {
    float vals[MATRIX3_SIZE][MATRIX3_SIZE];
};

struct CMSTransferFunction {
    float g, a, b, c, d, e, f;
};

class ColorSpace {
public:
    enum class ColorSpaceType {
        NO_TYPE,
        SRGB,
        SRGB_LINEAR,
        REF_IMAGE,
        RGB,
    };
    static std::shared_ptr<ColorSpace> CreateSRGB()
    {
        return std::make_shared<ColorSpace>();
    }

    static std::shared_ptr<ColorSpace> CreateRGB(
        const CMSTransferFuncType& func, const CMSMatrixType& matrix)
    {
        return std::make_shared<ColorSpace>();
    }
};
} // namespace Drawing
} // namespace Rosen
} // namespace OHOS
#endif
