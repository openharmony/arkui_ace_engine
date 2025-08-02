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
#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_RENDER_GRAPHICS_MODIFIER_PAINTER_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_RENDER_GRAPHICS_MODIFIER_PAINTER_H

#include <memory>

#ifndef USE_ROSEN_DRAWING
#include "include/core/SkRRect.h"
#endif
#include "render_service_client/core/modifier/rs_property.h"
#include "render_service_client/core/modifier_ng/custom/rs_foreground_style_modifier.h"

#include "core/components/common/properties/color.h"
#ifdef USE_ROSEN_DRAWING
#include "core/components_ng/render/drawing_forward.h"
#endif

namespace OHOS::Ace::NG {
using RSDrawingContext = Rosen::ModifierNG::RSDrawingContext;
using RSForegroundStyleModifier = Rosen::ModifierNG::RSForegroundStyleModifier;

// common parent class of graphic effect modifiers
class GraphicModifier : public RSForegroundStyleModifier {
public:
    void SetCustomData(float data);

    void SetCornerRadius(const Rosen::Vector4f& radius);

protected:
#ifndef USE_ROSEN_DRAWING
    SkRRect MakeRRect(const RSDrawingContext& context) const;
#else
    RSRoundRect MakeRRect(const RSDrawingContext& context) const;
#endif

    std::shared_ptr<Rosen::RSAnimatableProperty<float>> property_;
    std::shared_ptr<Rosen::RSAnimatableProperty<Rosen::Vector4f>> radius_;
};

class GrayScaleModifier : public GraphicModifier {
public:
    void Draw(RSDrawingContext& context) const override;
};

class BrightnessModifier : public GraphicModifier {
public:
    void Draw(RSDrawingContext& context) const override;
};

class ContrastModifier : public GraphicModifier {
public:
    void Draw(RSDrawingContext& context) const override;
};

class SaturateModifier : public GraphicModifier {
public:
    void Draw(RSDrawingContext& context) const override;
};

class SepiaModifier : public GraphicModifier {
public:
    void Draw(RSDrawingContext& context) const override;
};

class InvertModifier : public GraphicModifier {
public:
    void Draw(RSDrawingContext& context) const override;
};

class HueRotateModifier : public GraphicModifier {
public:
    void Draw(RSDrawingContext& context) const override;
};

class ColorBlend : public Rosen::RSAnimatableArithmetic<ColorBlend> {
public:
    ColorBlend() = default;
    explicit ColorBlend(const Color& color) : colorBlend_(color) {}

    ColorBlend Add(const ColorBlend& value) const override
    {
        return ColorBlend(colorBlend_ + value.colorBlend_);
    }

    ColorBlend Minus(const ColorBlend& value) const override
    {
        return ColorBlend(colorBlend_ - value.colorBlend_);
    }

    ColorBlend Multiply(const float scale) const override
    {
        return ColorBlend(colorBlend_ * scale);
    }

    bool IsEqual(const ColorBlend& value) const override
    {
        return colorBlend_ == value.colorBlend_;
    }

    Color GetColor()
    {
        return colorBlend_;
    }
    Color colorBlend_;
};

class ColorBlendModifier : public GraphicModifier {
public:
    void Draw(RSDrawingContext& context) const override;

    void SetCustomData(const ColorBlend& data);

private:
    std::shared_ptr<Rosen::RSAnimatableProperty<ColorBlend>> colorProp_;
};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_RENDER_GRAPHICS_MODIFIER_PAINTER_H