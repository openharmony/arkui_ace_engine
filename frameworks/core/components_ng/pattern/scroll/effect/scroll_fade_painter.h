/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_SCROLL_EFFECT_SCROLL_FADE_PAINTER_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_SCROLL_EFFECT_SCROLL_FADE_PAINTER_H

#include "base/geometry/ng/offset_t.h"
#include "base/geometry/ng/size_t.h"
#include "base/memory/ace_type.h"
#include "core/components/common/properties/color.h"
#include "core/components_ng/render/drawing.h"

namespace OHOS::Ace::NG {
enum class OverScrollDirection {
    UP = 0,
    DOWN,
    LEFT,
    RIGHT,
};

class ScrollFadePainter : public AceType {
    DECLARE_ACE_TYPE(ScrollFadePainter, AceType);

public:
    void PaintSide(RSCanvas& context, const SizeF& size, const OffsetF& offset);

    Color GetColor() const
    {
        return color_;
    }

    void SetColor(const Color& color)
    {
        color_ = color;
    }

    float GetOpacity() const
    {
        return opacity_;
    }

    void SetOpacity(float opacity)
    {
        opacity_ = opacity;
    }

    float GetScaleFactor() const
    {
        return scaleFactor_;
    }

    void SetScaleFactor(float scaleFactor)
    {
        scaleFactor_ = scaleFactor;
    }

    void SetDirection(OverScrollDirection direction)
    {
        direction_ = direction;
    }

    OverScrollDirection GetDirection() const
    {
        return direction_;
    }

protected:
    void Paint(RSCanvas& canvas, const SizeF& size, const OffsetF& offset);

    OverScrollDirection direction_ = OverScrollDirection::UP;
    Color color_ = Color::GRAY;
    float opacity_ = 0.0f;
    float scaleFactor_ = 0.0f;
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_SCROLL_EFFECT_SCROLL_FADE_PAINTER_H