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

#include "render_service_client/core/modifier/rs_extended_modifier.h"
#include "render_service_client/core/modifier/rs_property.h"

#include "base/geometry/dimension.h"
#include "core/components/common/properties/color.h"
#include "core/components_ng/render/adapter/skia_decoration_painter.h"

namespace OHOS::Ace::NG {

using RSDrawingContext = Rosen::RSDrawingContext;

// common parent class of graphic effect modifiers
class GraphicModifier : public Rosen::RSForegroundStyleModifier {
public:
    void SetCustomData(const float data)
    {
        if (!property_) {
            property_ = std::make_shared<Rosen::RSAnimatableProperty<float>>(data);
            AttachProperty(property_);
        } else {
            LOGD("changing modifier property %f", data);
            property_->Set(data);
        }
    }

protected:
    std::shared_ptr<Rosen::RSAnimatableProperty<float>> property_;
};

class GrayScaleModifier : public GraphicModifier {
public:
    void Draw(RSDrawingContext& context) const override
    {
        if (property_) {
            SkiaDecorationPainter::PaintGrayScale(
                SizeF(context.width, context.height), context.canvas, property_->Get());
        }
    }
};

class BrightnessModifier : public GraphicModifier {
public:
    void Draw(RSDrawingContext& context) const override
    {
        if (property_) {
            SkiaDecorationPainter::PaintBrightness(
                SizeF(context.width, context.height), context.canvas, property_->Get());
        }
    }
};

class ContrastModifier : public GraphicModifier {
public:
    void Draw(RSDrawingContext& context) const override
    {
        if (property_) {
            SkiaDecorationPainter::PaintContrast(
                SizeF(context.width, context.height), context.canvas, property_->Get());
        }
    }
};

class SaturateModifier : public GraphicModifier {
public:
    void Draw(RSDrawingContext& context) const override
    {
        if (property_) {
            SkiaDecorationPainter::PaintSaturate(
                SizeF(context.width, context.height), context.canvas, property_->Get());
        }
    }
};

class SepiaModifier : public GraphicModifier {
public:
    void Draw(RSDrawingContext& context) const override
    {
        if (property_) {
            SkiaDecorationPainter::PaintSepia(SizeF(context.width, context.height), context.canvas, property_->Get());
        }
    }
};

class InvertModifier : public GraphicModifier {
public:
    void Draw(RSDrawingContext& context) const override
    {
        if (property_) {
            SkiaDecorationPainter::PaintInvert(SizeF(context.width, context.height), context.canvas, property_->Get());
        }
    }
};

class HueRotateModifier : public GraphicModifier {
public:
    void Draw(RSDrawingContext& context) const override
    {
        if (property_) {
            SkiaDecorationPainter::PaintHueRotate(
                SizeF(context.width, context.height), context.canvas, property_->Get());
        }
    }
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

class ColorBlendModifier : public Rosen::RSForegroundStyleModifier {
public:
    void Draw(RSDrawingContext& context) const override
    {
        if (property_) {
            SkiaDecorationPainter::PaintColorBlend(
                SizeF(context.width, context.height), context.canvas, property_->Get().GetColor());
        }
    }

    Rosen::RSModifierType GetModifierType() const override
    {
        return Rosen::RSModifierType::FOREGROUND_STYLE;
    }

    void SetCustomData(const ColorBlend& data)
    {
        if (!property_) {
            property_ = std::make_shared<Rosen::RSAnimatableProperty<ColorBlend>>(data);
            AttachProperty(property_);
        } else {
            property_->Set(data);
        }
    }
    std::shared_ptr<Rosen::RSAnimatableProperty<ColorBlend>> property_;
};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_RENDER_GRAPHICS_MODIFIER_PAINTER_H