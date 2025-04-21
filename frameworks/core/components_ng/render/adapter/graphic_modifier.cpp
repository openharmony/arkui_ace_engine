/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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

#include "graphic_modifier.h"

#ifndef USE_ROSEN_DRAWING
#include "include/core/SkRect.h"

#include "core/components_ng/render/adapter/skia_decoration_painter.h"
#else
#include "core/components_ng/render/adapter/drawing_decoration_painter.h"
#endif

namespace OHOS::Ace::NG {
void GraphicModifier::SetCornerRadius(const Rosen::Vector4f& radius)
{
    if (!radius_) {
        radius_ = std::make_shared<Rosen::RSAnimatableProperty<Rosen::Vector4f>>(radius);
        AttachProperty(radius_);
    } else {
        radius_->Set(radius);
    }
}

void GraphicModifier::SetCustomData(float data)
{
    if (!property_) {
        property_ = std::make_shared<Rosen::RSAnimatableProperty<float>>(data);
        AttachProperty(property_);
    } else {
        property_->Set(data);
    }
}

#ifndef USE_ROSEN_DRAWING
SkRRect GraphicModifier::MakeRRect(const RSDrawingContext& context) const
{
    SkRect rect = SkRect::MakeSize({ context.width, context.height });
    SkRRect rRect;
    SkVector radii[4];
    if (radius_) {
        radii[SkRRect::kUpperLeft_Corner].set(radius_->Get().x_, radius_->Get().x_),
            radii[SkRRect::kUpperRight_Corner].set(radius_->Get().y_, radius_->Get().y_);
        radii[SkRRect::kLowerRight_Corner].set(radius_->Get().z_, radius_->Get().z_);
        radii[SkRRect::kLowerLeft_Corner].set(radius_->Get().w_, radius_->Get().w_);
    }
    rRect.setRectRadii(rect, radii);
    return rRect;
}
#else
RSRoundRect GraphicModifier::MakeRRect(const RSDrawingContext& context) const
{
    RSRect rect(0, 0, context.width, context.height);
    std::vector<RSPoint> radii(4);
    if (radius_) {
        radii[RSRoundRect::TOP_LEFT_POS] = {radius_->Get().x_, radius_->Get().x_};
        radii[RSRoundRect::TOP_RIGHT_POS] = {radius_->Get().y_, radius_->Get().y_};
        radii[RSRoundRect::BOTTOM_RIGHT_POS] = {radius_->Get().z_, radius_->Get().z_};
        radii[RSRoundRect::BOTTOM_LEFT_POS] = {radius_->Get().w_, radius_->Get().w_};
    }
    return RSRoundRect(rect, radii);
}
#endif

void GrayScaleModifier::Draw(RSDrawingContext& context) const
{
    if (property_) {
        auto rRect = MakeRRect(context);
#ifndef USE_ROSEN_DRAWING
        SkiaDecorationPainter::PaintGrayScale(rRect, context.canvas, property_->Get());
#else
        DrawingDecorationPainter::PaintGrayScale(rRect, context.canvas, property_->Get());
#endif
    }
}

void BrightnessModifier::Draw(RSDrawingContext& context) const
{
    if (property_) {
        auto rRect = MakeRRect(context);
#ifndef USE_ROSEN_DRAWING
        SkiaDecorationPainter::PaintBrightness(rRect, context.canvas, property_->Get());
#else
        DrawingDecorationPainter::PaintBrightness(rRect, context.canvas, property_->Get());
#endif
    }
}

void ContrastModifier::Draw(RSDrawingContext& context) const
{
    if (property_) {
        auto rRect = MakeRRect(context);
#ifndef USE_ROSEN_DRAWING
        SkiaDecorationPainter::PaintContrast(rRect, context.canvas, property_->Get());
#else
        DrawingDecorationPainter::PaintContrast(rRect, context.canvas, property_->Get());
#endif
    }
}

void SaturateModifier::Draw(RSDrawingContext& context) const
{
    if (property_) {
        auto rRect = MakeRRect(context);
#ifndef USE_ROSEN_DRAWING
        SkiaDecorationPainter::PaintSaturate(rRect, context.canvas, property_->Get());
#else
        DrawingDecorationPainter::PaintSaturate(rRect, context.canvas, property_->Get());
#endif
    }
}

void SepiaModifier::Draw(RSDrawingContext& context) const
{
    if (property_) {
        auto rRect = MakeRRect(context);
#ifndef USE_ROSEN_DRAWING
        SkiaDecorationPainter::PaintSepia(rRect, context.canvas, property_->Get());
#else
        DrawingDecorationPainter::PaintSepia(rRect, context.canvas, property_->Get());
#endif
    }
}

void InvertModifier::Draw(RSDrawingContext& context) const
{
    if (property_) {
        auto rRect = MakeRRect(context);
#ifndef USE_ROSEN_DRAWING
        SkiaDecorationPainter::PaintInvert(rRect, context.canvas, property_->Get());
#else
        DrawingDecorationPainter::PaintInvert(rRect, context.canvas, property_->Get());
#endif
    }
}

void HueRotateModifier::Draw(RSDrawingContext& context) const
{
    if (property_) {
        auto rRect = MakeRRect(context);
#ifndef USE_ROSEN_DRAWING
        SkiaDecorationPainter::PaintHueRotate(rRect, context.canvas, property_->Get());
#else
        DrawingDecorationPainter::PaintHueRotate(rRect, context.canvas, property_->Get());
#endif
    }
}

void ColorBlendModifier::Draw(RSDrawingContext& context) const
{
    if (colorProp_) {
        auto rRect = MakeRRect(context);
#ifndef USE_ROSEN_DRAWING
        SkiaDecorationPainter::PaintColorBlend(rRect, context.canvas, colorProp_->Get().GetColor());
#else
        DrawingDecorationPainter::PaintColorBlend(rRect, context.canvas, colorProp_->Get().GetColor());
#endif
    }
}

void ColorBlendModifier::SetCustomData(const ColorBlend& data)
{
    if (!colorProp_) {
        colorProp_ = std::make_shared<Rosen::RSAnimatableProperty<ColorBlend>>(data);
        AttachProperty(colorProp_);
    } else {
        colorProp_->Set(data);
    }
}
} // namespace OHOS::Ace::NG
