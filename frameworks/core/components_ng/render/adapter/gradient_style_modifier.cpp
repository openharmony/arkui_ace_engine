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

#include "core/components_ng/render/adapter/gradient_style_modifier.h"

#include "base/geometry/dimension.h"
#include "base/log/log_wrapper.h"
#include "base/utils/utils.h"
#include "core/components_ng/render/adapter/graphic_modifier.h"
#include "core/components_ng/render/adapter/skia_decoration_painter.h"

namespace OHOS::Ace::NG {
namespace {
constexpr double MAX_COLOR_STOP = 100.0;
} // namespace
void GradientStyleModifier::Draw(RSDrawingContext& context) const
{
    CHECK_NULL_VOID(colors_);
    CHECK_NULL_VOID(colorStops_);
    std::shared_ptr<SkCanvas> skCanvas { context.canvas, [](SkCanvas* /* unused */) {} };
    RSCanvas rsCanvas(&skCanvas);
    SizeF contentSize(context.width, context.height);
    PaintGradient(rsCanvas, contentSize);
}

void GradientStyleModifier::PaintGradient(RSCanvas& canvas, const SizeF& frameSize) const
{
    if (Negative(frameSize.Height()) || Negative(frameSize.Width())) {
        return;
    }
    auto shader = SkiaDecorationPainter::CreateGradientShader(GetGradient(), frameSize);
    SkPaint paint;
    paint.setAntiAlias(true);
    paint.setShader(shader);

    auto imageInfo = SkImageInfo::Make(
        frameSize.Width(), frameSize.Height(), SkColorType::kRGBA_8888_SkColorType, SkAlphaType::kOpaque_SkAlphaType);
    SkBitmap skBitmap;
    skBitmap.allocPixels(imageInfo);

    std::unique_ptr<SkCanvas> skCanvas = std::make_unique<SkCanvas>(skBitmap);
    skCanvas->drawPaint(paint);
    auto skImage = SkImage::MakeFromBitmap(skBitmap);
    RSImage rsImage(&skImage);

    canvas.Save();
    if (borderRadius_.has_value()) {
        RSRoundRect rRect(
            RSRect(0, 0, frameSize.Width(), frameSize.Height()), borderRadius_.value().x_, borderRadius_.value().y_);
        canvas.ClipRoundRect(rRect, RSClipOp::INTERSECT, true);
    }
    canvas.DrawImageRect(
        rsImage, OHOS::Rosen::Drawing::Rect(0.0, 0.0, frameSize.Width(), frameSize.Height()), rosen::SamplingOptions());
    canvas.Restore();
}

Gradient GradientStyleModifier::GetGradient() const
{
    Gradient gradient;
    std::vector<Color> colors = colors_->Get().GetColors();
    std::vector<Dimension> stops = colorStops_->Get().GetColorStops();
    if (gradient_) {
        gradient = gradient_->Get();
    }
    auto size = colors.size();
    gradient.ClearColors();
    GradientColor color;
    for (size_t index = 0; index < size; index++) {
        color.SetColor(colors[index]);
        auto colorStop =
            stops[index].Value() > MAX_COLOR_STOP ? Dimension(MAX_COLOR_STOP, DimensionUnit::PERCENT) : stops[index];
        color.SetDimension(colorStop);
        gradient.AddColor(color);
    }
    return gradient;
}

void GradientStyleModifier::SetGradient(const Gradient& gradient)
{
    if (!colors_) {
        colors_ = std::make_shared<Rosen::RSAnimatableProperty<ColorAnimatableArithmetic>>(
            ColorAnimatableArithmetic(gradient));
        AttachProperty(colors_);
    } else {
        colors_->Set(ColorAnimatableArithmetic(gradient));
    }
    if (!colorStops_) {
        colorStops_ = std::make_shared<Rosen::RSAnimatableProperty<ColorStopAnimatableArithmetic>>(
            ColorStopAnimatableArithmetic(gradient));
        AttachProperty(colorStops_);
    } else {
        colorStops_->Set(ColorStopAnimatableArithmetic(gradient));
    }
    if (!gradient_) {
        gradient_ = std::make_shared<Rosen::RSProperty<Gradient>>(gradient);
        AttachProperty(gradient_);
    } else {
        gradient_->Set(gradient);
    }
}

ColorAnimatableArithmetic::ColorAnimatableArithmetic(const Gradient& gradient)
{
    for (const auto& color : gradient.GetColors()) {
        colors_.push_back(color.GetColor());
    }
}

ColorAnimatableArithmetic ColorAnimatableArithmetic::Add(const ColorAnimatableArithmetic& value) const
{
    auto srcColorSize = colors_.size();
    auto dstColorSize = value.colors_.size();
    auto idealSize = std::min(srcColorSize, dstColorSize);

    ColorAnimatableArithmetic result;
    size_t index = 0;
    for (; index < idealSize; index++) {
        Color color = Color::FromARGB(colors_[index].GetAlpha() + value.colors_[index].GetAlpha(),
            colors_[index].GetRed() + value.colors_[index].GetRed(),
            colors_[index].GetGreen() + value.colors_[index].GetGreen(),
            colors_[index].GetBlue() + value.colors_[index].GetBlue());
        result.colors_.push_back(color);
    }
    if (srcColorSize > dstColorSize) {
        for (; index < srcColorSize; index++) {
            result.colors_.push_back(colors_[index]);
        }
    } else {
        for (; index < dstColorSize; index++) {
            result.colors_.push_back(value.colors_[index]);
        }
    }
    return result;
}

ColorAnimatableArithmetic ColorAnimatableArithmetic::Minus(const ColorAnimatableArithmetic& value) const
{
    auto srcColorSize = colors_.size();
    auto dstColorSize = value.colors_.size();
    auto idealSize = std::min(srcColorSize, dstColorSize);

    ColorAnimatableArithmetic result;
    size_t index = 0;
    for (; index < idealSize; index++) {
        Color color = Color::FromARGB(colors_[index].GetAlpha() - value.colors_[index].GetAlpha(),
            colors_[index].GetRed() - value.colors_[index].GetRed(),
            colors_[index].GetGreen() - value.colors_[index].GetGreen(),
            colors_[index].GetBlue() - value.colors_[index].GetBlue());
        result.colors_.push_back(color);
    }
    if (srcColorSize > dstColorSize) {
        for (; index < srcColorSize; index++) {
            result.colors_.push_back(colors_[index]);
        }
    } else {
        for (; index < dstColorSize; index++) {
            result.colors_.push_back(value.colors_[index]);
        }
    }
    return result;
}

ColorAnimatableArithmetic ColorAnimatableArithmetic::Multiply(const float scale) const
{
    auto srcColorSize = colors_.size();
    ColorAnimatableArithmetic result;
    size_t index = 0;
    for (; index < srcColorSize; index++) {
        Color color = Color::FromARGB(colors_[index].GetAlpha() * scale, colors_[index].GetRed() * scale,
            colors_[index].GetGreen() * scale, colors_[index].GetBlue() * scale);
        result.colors_.push_back(color);
    }
    return result;
}

bool ColorAnimatableArithmetic::IsEqual(const ColorAnimatableArithmetic& value) const
{
    auto srcColorSize = colors_.size();
    auto dstColorSize = value.colors_.size();
    if (srcColorSize != dstColorSize) {
        return false;
    }
    for (size_t index = 0; index < srcColorSize; index++) {
        if (colors_[index] != value.colors_[index]) {
            return false;
        }
    }
    return true;
}

ColorStopAnimatableArithmetic::ColorStopAnimatableArithmetic(const Gradient& gradient)
{
    for (const auto& colorStop : gradient.GetColors()) {
        colorStops_.push_back(colorStop.GetDimension());
    }
}

ColorStopAnimatableArithmetic ColorStopAnimatableArithmetic::Add(const ColorStopAnimatableArithmetic& value) const
{
    auto srcColorStopSize = colorStops_.size();
    auto dstColorStopSize = value.colorStops_.size();
    auto idealSize = std::min(srcColorStopSize, dstColorStopSize);

    ColorStopAnimatableArithmetic result;
    size_t index = 0;
    for (; index < idealSize; index++) {
        auto colorStop = colorStops_[index].Value() + value.colorStops_[index].Value();
        result.colorStops_.push_back(Dimension(colorStop, DimensionUnit::PERCENT));
    }
    if (srcColorStopSize > dstColorStopSize) {
        for (; index < srcColorStopSize; index++) {
            result.colorStops_.push_back(colorStops_[index]);
        }
    } else {
        for (; index < dstColorStopSize; index++) {
            result.colorStops_.push_back(value.colorStops_[index]);
        }
    }
    return result;
}

ColorStopAnimatableArithmetic ColorStopAnimatableArithmetic::Minus(const ColorStopAnimatableArithmetic& value) const
{
    auto srcColorStopSize = colorStops_.size();
    auto dstColorStopSize = value.colorStops_.size();
    auto idealSize = std::min(srcColorStopSize, dstColorStopSize);

    ColorStopAnimatableArithmetic result;
    size_t index = 0;
    for (; index < idealSize; index++) {
        auto colorStop = colorStops_[index].Value() - value.colorStops_[index].Value();
        result.colorStops_.push_back(Dimension(colorStop, DimensionUnit::PERCENT));
    }
    if (srcColorStopSize > dstColorStopSize) {
        for (; index < srcColorStopSize; index++) {
            result.colorStops_.push_back(colorStops_[index]);
        }
    } else {
        for (; index < dstColorStopSize; index++) {
            result.colorStops_.push_back(value.colorStops_[index]);
        }
    }
    return result;
}

ColorStopAnimatableArithmetic ColorStopAnimatableArithmetic::Multiply(const float scale) const
{
    auto srcColorStopSize = colorStops_.size();

    ColorStopAnimatableArithmetic result;
    for (size_t index = 0; index < srcColorStopSize; index++) {
        auto colorStop = colorStops_[index].Value() * scale;
        result.colorStops_.push_back(Dimension(colorStop, DimensionUnit::PERCENT));
    }
    return result;
}

bool ColorStopAnimatableArithmetic::IsEqual(const ColorStopAnimatableArithmetic& value) const
{
    auto srcColorStopSize = colorStops_.size();
    auto dstColorStopSize = value.colorStops_.size();
    if (srcColorStopSize != dstColorStopSize) {
        return false;
    }
    for (size_t index = 0; index < srcColorStopSize; index++) {
        if (!NearEqual(colorStops_[index].Value(), value.colorStops_[index].Value())) {
            return false;
        }
    }
    return true;
}
} // namespace OHOS::Ace::NG
