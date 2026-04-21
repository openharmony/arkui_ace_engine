/*
 * Copyright (c) 2021-2025 Huawei Device Co., Ltd.
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

#ifndef COLOR_FILTER_H
#define COLOR_FILTER_H

#include <memory>

#include "color_matrix.h"

#include "draw/blend_mode.h"
#include "draw/color.h"

namespace OHOS {
namespace Rosen {
namespace Drawing {
class ColorFilter {
public:
    enum class FilterType {
        NO_TYPE = 0,
        BLEND_MODE,
        MATRIX,
        LINEAR_TO_SRGB_GAMMA,
        SRGB_GAMMA_TO_LINEAR,
        COMPOSE,
        LUMA,
        OVER_DRAW,
        LIGHTING,
    };

    // Color matrix is a 4x5 float type matrix.
    constexpr static int MATRIX_SIZE = 20;
    constexpr static int OVER_DRAW_COLOR_NUM = 6;

    static std::shared_ptr<ColorFilter> CreateMatrixColorFilter(ColorMatrix& /* cm */)
    {
        return std::make_shared<ColorFilter>();
    }

    static std::shared_ptr<ColorFilter> CreateMatrixColorFilter(
        ColorMatrix& /* cm */, Clamp /* clamp */)
    {
        return std::make_shared<ColorFilter>();
    }

    static std::shared_ptr<ColorFilter> CreateSrgbGammaToLinear()
    {
        return std::make_shared<ColorFilter>();
    }

    static std::shared_ptr<ColorFilter> CreateLinearToSrgbGamma()
    {
        return std::make_shared<ColorFilter>();
    }

    static std::shared_ptr<ColorFilter> CreateLumaColorFilter()
    {
        return std::make_shared<ColorFilter>();
    }

    static std::shared_ptr<ColorFilter> CreateComposeColorFilter(ColorFilter& f1, ColorFilter& f2)
    {
        return std::make_shared<ColorFilter>();
    }
};
} // namespace Drawing
} // namespace Rosen
} // namespace OHOS
#endif
