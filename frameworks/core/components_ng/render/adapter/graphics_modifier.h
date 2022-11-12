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
#include "core/components_ng/render/adapter/rosen_foreground_modifier.h"
#include "core/components_ng/render/adapter/skia_decoration_painter.h"

namespace OHOS::Ace::NG {

using RSDrawingContext = Rosen::RSDrawingContext;

class GrayScaleModifier : public RSForegroundStyleModifier {
public:
    GrayScaleModifier() = default;
    ~GrayScaleModifier() override = default;

    void Draw(RSDrawingContext& context) const override
    {
        SkiaDecorationPainter::PaintGrayScale(
            SizeF(context.width, context.height), context.canvas, property_->Get());
    }

    void SetCustomData(const float data)
    {
        if (property_ == nullptr) {
            property_ = std::make_shared<Rosen::RSAnimatableProperty<float>>(data);
            AttachProperty(property_);
        } else {
            property_->Set(data);
        }
    }

private:
    std::shared_ptr<Rosen::RSAnimatableProperty<float>> property_;
};

class BrightnessModifier : public RSForegroundStyleModifier {
public:
    BrightnessModifier() = default;
    ~BrightnessModifier() override = default;

    void Draw(RSDrawingContext& context) const override
    {
        SkiaDecorationPainter::PaintBrightness(
            SizeF(context.width, context.height), context.canvas, property_->Get());
    }

    void SetCustomData(const float data)
    {
        if (property_ == nullptr) {
            property_ = std::make_shared<Rosen::RSAnimatableProperty<float>>(data);
            AttachProperty(property_);
        } else {
            property_->Set(data);
        }
    }

private:
    std::shared_ptr<Rosen::RSAnimatableProperty<float>> property_;
};

class ContrastModifier : public RSForegroundStyleModifier {
public:
    ContrastModifier() = default;
    ~ContrastModifier() override = default;

    void Draw(RSDrawingContext& context) const override
    {
        SkiaDecorationPainter::PaintContrast(
            SizeF(context.width, context.height), context.canvas, property_->Get());
    }

    void SetCustomData(const float data)
    {
        if (property_ == nullptr) {
            property_ = std::make_shared<Rosen::RSAnimatableProperty<float>>(data);
            AttachProperty(property_);
        } else {
            property_->Set(data);
        }
    }

private:
    std::shared_ptr<Rosen::RSAnimatableProperty<float>> property_;
};

class SaturateModifier : public RSForegroundStyleModifier {
public:
    SaturateModifier() = default;
    ~SaturateModifier() override = default;

    void Draw(RSDrawingContext& context) const override
    {
        SkiaDecorationPainter::PaintSaturate(
            SizeF(context.width, context.height), context.canvas, property_->Get());
    }

    void SetCustomData(const float data)
    {
        if (property_ == nullptr) {
            property_ = std::make_shared<Rosen::RSAnimatableProperty<float>>(data);
            AttachProperty(property_);
        } else {
            property_->Set(data);
        }
    }

private:
    std::shared_ptr<Rosen::RSAnimatableProperty<float>> property_;
};

class SepiaModifier : public RSForegroundStyleModifier {
public:
    SepiaModifier() = default;
    ~SepiaModifier() override = default;

    void Draw(RSDrawingContext& context) const override
    {
        SkiaDecorationPainter::PaintSepia(
            SizeF(context.width, context.height), context.canvas, property_->Get());
    }

    void SetCustomData(const float data)
    {
        if (property_ == nullptr) {
            property_ = std::make_shared<Rosen::RSAnimatableProperty<float>>(data);
            AttachProperty(property_);
        } else {
            property_->Set(data);
        }
    }

private:
    std::shared_ptr<Rosen::RSAnimatableProperty<float>> property_;
};

class InvertModifier : public RSForegroundStyleModifier {
public:
    InvertModifier() = default;
    ~InvertModifier() override = default;

    void Draw(RSDrawingContext& context) const override
    {
        SkiaDecorationPainter::PaintInvert(
            SizeF(context.width, context.height), context.canvas, property_->Get());
    }

    void SetCustomData(const float data)
    {
        if (property_ == nullptr) {
            property_ = std::make_shared<Rosen::RSAnimatableProperty<float>>(data);
            AttachProperty(property_);
        } else {
            property_->Set(data);
        }
    }

private:
    std::shared_ptr<Rosen::RSAnimatableProperty<float>> property_;
};

class HueRotateModifier : public RSForegroundStyleModifier {
public:
    HueRotateModifier() = default;
    ~HueRotateModifier() override = default;

    void Draw(RSDrawingContext& context) const override
    {
        SkiaDecorationPainter::PaintHueRotate(
            SizeF(context.width, context.height), context.canvas, property_->Get());
    }

    void SetCustomData(const float data)
    {
        if (property_ == nullptr) {
            property_ = std::make_shared<Rosen::RSAnimatableProperty<float>>(data);
            AttachProperty(property_);
        } else {
            property_->Set(data);
        }
    }

private:
    std::shared_ptr<Rosen::RSAnimatableProperty<float>> property_;
};

class ColorBlend : public Rosen::RSAnimatableArithmetic<ColorBlend> {
public:
    ColorBlend() = default;
    explicit ColorBlend(const Color& color) : colorBlend_(color) {}
    ~ColorBlend() override = default;

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

private:
    Color colorBlend_;
};

class ColorBlendModifier : public RSForegroundStyleModifier {
public:
    ColorBlendModifier() = default;
    ~ColorBlendModifier() override = default;

    void Draw(RSDrawingContext& context) const override
    {
        SkiaDecorationPainter::PaintColorBlend(
            SizeF(context.width, context.height), context.canvas, property_->Get().GetColor());
    }

    void SetCustomData(const ColorBlend& data)
    {
        if (property_ == nullptr) {
            property_ = std::make_shared<Rosen::RSAnimatableProperty<ColorBlend>>(data);
            AttachProperty(property_);
        } else {
            property_->Set(data);
        }
    }

private:
    std::shared_ptr<Rosen::RSAnimatableProperty<ColorBlend>> property_;
};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_RENDER_GRAPHICS_MODIFIER_PAINTER_H