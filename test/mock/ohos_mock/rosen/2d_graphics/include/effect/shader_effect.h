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

#ifndef SHADER_EFFECT_H
#define SHADER_EFFECT_H

#include <vector>
#include <memory>

#include "draw/color.h"

#include "effect/color_space.h"

#include "image/image.h"
#include "image/picture.h"

#include "utils/point.h"
#include "utils/matrix.h"
#include "utils/sampling_options.h"

namespace OHOS {
namespace Rosen {
namespace Drawing {
enum class TileMode {
    CLAMP = 0,
    REPEAT,
    MIRROR,
    DECAL,
};

class ShaderEffect {
public:
    enum class ShaderEffectType : int32_t {
        NO_TYPE = 0,
        COLOR_SHADER,
        BLEND,
        IMAGE,
        PICTURE,
        LINEAR_GRADIENT,
        RADIAL_GRADIENT,
        CONICAL_GRADIENT,
        SWEEP_GRADIENT,
        LIGHT_UP,
        EXTEND_SHADER,
        SDF_SHADER,
        LAZY_SHADER
    };

    static std::shared_ptr<ShaderEffect> CreateSweepGradient(const Point& /* centerPt */,
        const std::vector<uint32_t>& /* colors */, const std::vector<float>& /* pos */, TileMode /* mode */,
        float /* startAngle */, float /* endAngle */, const Matrix* /* matrix */)
    {
        return std::make_shared<ShaderEffect>();
    }

    static std::shared_ptr<ShaderEffect> CreateLinearGradient(const Point& /* startPt */,
        const Point& /* endPt */, const std::vector<uint32_t>& /* colors */,
        const std::vector<float>& /* pos */, TileMode /* mode */, const Matrix* matrix = nullptr)
    {
        return std::make_shared<ShaderEffect>();
    }

    static std::shared_ptr<ShaderEffect> CreateRadialGradient(const Point& centerPt, scalar radius,
        const std::vector<ColorQuad>& colors, const std::vector<scalar>& pos, TileMode mode,
        const Matrix* matrix = nullptr)
    {
        return std::make_shared<ShaderEffect>();
    }

    static std::shared_ptr<ShaderEffect> CreateTwoPointConical(const Point& startPt, scalar startRadius,
        const Point& endPt, scalar endRadius, const std::vector<ColorQuad>& colors,
        const std::vector<scalar>& pos, TileMode mode, const Matrix* matrix)
    {
        return std::make_shared<ShaderEffect>();
    }

    static std::shared_ptr<ShaderEffect> CreateColorShader(ColorQuad color)
    {
        return std::make_shared<ShaderEffect>();
    }

    static std::shared_ptr<ShaderEffect> CreateImageShader(const Image& image, TileMode tileX,
        TileMode tileY, const SamplingOptions& sampling, const Matrix& matrix)
    {
        return std::make_shared<ShaderEffect>();
    }

    static std::shared_ptr<ShaderEffect> CreatePictureShader(const Picture& picture, TileMode tileX,
        TileMode tileY, const FilterMode& mode, const Matrix& matrix, const Rect& rect)
    {
        return std::make_shared<ShaderEffect>();
    }

    static std::shared_ptr<ShaderEffect> CreateSweepGradient(const Point& /* centerPt */,
        const std::vector<Color4f>& /* colors */, std::shared_ptr<ColorSpace> /* colorSpace */,
        const std::vector<float>& /* pos */, TileMode /* mode */, float /* startAngle */, float /* endAngle */,
        const Matrix* /* matrix */)
    {
        return std::make_shared<ShaderEffect>();
    }

    static std::shared_ptr<ShaderEffect> CreateLinearGradient(const Point& /* startPt */,
        const Point& /* endPt */, const std::vector<Color4f>& /* colors */,
        std::shared_ptr<ColorSpace> /* colorSpace */, const std::vector<float>& /* pos */, TileMode /* mode */,
        const Matrix* matrix = nullptr)
    {
        return std::make_shared<ShaderEffect>();
    }

    static std::shared_ptr<ShaderEffect> CreateRadialGradient(const Point& centerPt, scalar radius,
        const std::vector<Color4f>& /* colors */, std::shared_ptr<ColorSpace> /* colorSpace */,
        const std::vector<scalar>& pos, TileMode mode, const Matrix* matrix = nullptr)
    {
        return std::make_shared<ShaderEffect>();
    }

    static std::shared_ptr<ShaderEffect> CreateTwoPointConical(const Point& startPt, scalar startRadius,
        const Point& endPt, scalar endRadius, const std::vector<Color4f>& /* colors */,
        std::shared_ptr<ColorSpace> /* colorSpace */, const std::vector<scalar>& pos, TileMode mode,
        const Matrix* matrix)
    {
        return std::make_shared<ShaderEffect>();
    }
};
} // namespace Drawing
} // namespace Rosen
} // namespace OHOS
#endif
