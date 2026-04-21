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

#ifndef IMAGE_FILTER_H
#define IMAGE_FILTER_H

#include <limits>

#include "effect/color_filter.h"
#include "effect/shader_effect.h"

#include "utils/rect.h"
#include "utils/sampling_options.h"
#include "utils/scalar.h"

namespace OHOS {
namespace Rosen {
namespace Drawing {
enum class ImageBlurType : uint8_t {
    KAWASE = 0,
    GAUSS,
};
class ImageFilterImpl;

static const Rect noCropRect = {
    -std::numeric_limits<scalar>::infinity(), -std::numeric_limits<scalar>::infinity(),
    std::numeric_limits<scalar>::infinity(), std::numeric_limits<scalar>::infinity()
};

class ImageFilter {
public:
    enum class FilterType {
        NO_TYPE,
        BLUR,
        COLOR_FILTER,
        OFFSET,
        ARITHMETIC,
        COMPOSE,
        GRADIENT_BLUR,
        BLEND,
        SHADER,
        IMAGE,
        HD_SAMPLE, // high definition sample
        LAZY_IMAGE_FILTER
    };
        static std::shared_ptr<ImageFilter> CreateBlurImageFilter(
        float sigmaX, float sigmaY, TileMode mode, std::shared_ptr<ImageFilter> input,
        ImageBlurType imageBlurType = ImageBlurType::GAUSS, const Rect& filterRect = noCropRect)
    {
        return std::make_shared<ImageFilter>();
    }

    static std::shared_ptr<ImageFilter> CreateColorFilterImageFilter(
        const ColorFilter& cf, std::shared_ptr<ImageFilter> input,
        const Rect& filterRect = noCropRect)
    {
        return std::make_shared<ImageFilter>();
    }

    static std::shared_ptr<ImageFilter> CreateArithmeticImageFilter(const std::vector<scalar>& coefficients,
        bool enforcePMColor, std::shared_ptr<ImageFilter> background,
        std::shared_ptr<ImageFilter> foreground, const Rect& filterRect = noCropRect)
    {
        return std::make_shared<ImageFilter>();
    }

    static std::shared_ptr<ImageFilter> CreateOffsetImageFilter(
        scalar dx, scalar dy, std::shared_ptr<ImageFilter> input, const Rect& filterRect = noCropRect)
    {
        return std::make_shared<ImageFilter>();
    }

    static std::shared_ptr<ImageFilter> CreateBlendImageFilter(BlendMode mode,
        std::shared_ptr<ImageFilter> background, std::shared_ptr<ImageFilter> foreground = nullptr,
        const Rect& filterRect = noCropRect)
    {
        return std::make_shared<ImageFilter>();
    }

    static std::shared_ptr<ImageFilter> CreateShaderImageFilter(
        std::shared_ptr<ShaderEffect> shader, const Rect& rect = {})
    {
        return std::make_shared<ImageFilter>();
    }
};
} // namespace Drawing
} // namespace Rosen
} // namespace OHOS
#endif
