/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

#ifndef PEN_H
#define PEN_H

#include "draw/brush.h"
#include "draw/color.h"
#include "effect/filter.h"
#include "effect/path_effect.h"
#include "utils/rect.h"

namespace OHOS {
namespace Rosen {
namespace Drawing {
class Pen {
public:
    enum class JoinStyle {
        MITER_JOIN,
        ROUND_JOIN,
        BEVEL_JOIN,
        DEFAULT_JOIN = MITER_JOIN
    };

    enum class CapStyle {
        FLAT_CAP,
        ROUND_CAP,
        SQUARE_CAP,
        DEFAULT_CAP = FLAT_CAP
    };

    Pen() = default;
    ~Pen() = default;

    virtual void SetAntiAlias(bool aa) {}
    virtual void SetBlendMode(BlendMode mode) {}
    virtual void SetWidth(float width) {}
    virtual void SetCapStyle(CapStyle cap) {}
    virtual void SetColor(const Color& color) {}
    virtual void SetColor(int color) {}
    virtual void SetFilter(const Filter& filter) {}
    virtual void SetShaderEffect(std::shared_ptr<ShaderEffect> /* effect */) {}
    virtual void SetPathEffect(std::shared_ptr<PathEffect> /* effect */) {}
    virtual void SetJoinStyle(JoinStyle js) {}
    virtual void SetMiterLimit(float limit) {}
    virtual void SetAlpha(uint32_t alpha) {}
    virtual void SetAlphaF(float alpha) {}
    virtual void Reset() {}
    virtual std::shared_ptr<ShaderEffect> GetShaderEffect()
    {
        return std::make_shared<ShaderEffect>();
    }

    virtual float GetWidth()
    {
        return .0f;
    }

    virtual Filter GetFilter()
    {
        Filter filter = {};
        return filter;
    }
};
} // namespace Drawing
} // namespace Rosen
} // namespace OHOS
#endif
