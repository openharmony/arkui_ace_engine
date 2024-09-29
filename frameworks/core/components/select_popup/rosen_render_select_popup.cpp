/*
 * Copyright (c) 2021-2023 Huawei Device Co., Ltd.
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

#include "core/components/select_popup/rosen_render_select_popup.h"

#ifndef USE_ROSEN_DRAWING
#include "include/core/SkMaskFilter.h"
#include "include/core/SkRect.h"
#include "include/effects/SkGradientShader.h"
#endif

#include "core/components/common/painter/rosen_decoration_painter.h"
#include "core/pipeline/base/rosen_render_context.h"

namespace OHOS::Ace {
namespace {

const Dimension GRADIENT_HEIGHT = Dimension(50, DimensionUnit::VP);
const uint8_t GRADIENT_END_GRADIENT = 255;

} // namespace

double RosenRenderSelectPopup::GetOptionLeft() const
{
    if (renderOptions_.empty()) {
        return 0.0;
    }

    auto option = renderOptions_[0];
    if (!option) {
        return 0.0;
    }

    return option->GetGlobalOffset().GetX();
}

double RosenRenderSelectPopup::GetOptionTop() const
{
    auto scroll = renderScroll_;
    if (!scroll) {
        return 0.0;
    }

    return scroll->GetGlobalOffset().GetY();
}

double RosenRenderSelectPopup::GetOptionBottom() const
{
    auto scroll = renderScroll_;
    if (!scroll) {
        return 0.0;
    }

    return scroll->GetGlobalOffset().GetY() + scroll->GetLayoutSize().Height();
}

double RosenRenderSelectPopup::GetOptionWidth() const
{
    if (renderOptions_.empty()) {
        return 0.0;
    }

    auto option = renderOptions_[0];
    if (!option) {
        return 0.0;
    }

    return option->GetLayoutSize().Width();
}

void RosenRenderSelectPopup::PaintGradient(RenderContext& context, bool isTop)
{
    auto canvas = static_cast<RosenRenderContext*>(&context)->GetCanvas();
    if (!canvas) {
        LOGE("Paint canvas is null");
        return;
    }
#ifndef USE_ROSEN_DRAWING
    SkPaint paintGradient;
    Rect gradientRect;
    auto interval = NormalizeToPx(optionInterval_);
    auto yPos = isTop ? GetOptionTop() : GetOptionBottom() - NormalizeToPx(GRADIENT_HEIGHT);
    gradientRect.SetOffset(Offset(GetOptionLeft() + interval, yPos));
    gradientRect.SetHeight(NormalizeToPx(GRADIENT_HEIGHT));
    gradientRect.SetWidth(GetOptionWidth() - 2 * interval);
    SkPoint beginPoint = SkPoint::Make(SkDoubleToScalar(gradientRect.Left()), SkDoubleToScalar(gradientRect.Top()));
    SkPoint endPoint = SkPoint::Make(SkDoubleToScalar(gradientRect.Left()), SkDoubleToScalar(gradientRect.Bottom()));
    SkPoint points[2] = { beginPoint, endPoint };
    // color with red 13, green 13, and blue 13 is used for color stop (0.85) in gradient
    SkColor colors[2] = { tvBackColor_.ChangeAlpha(0).GetValue(),
        Color::FromRGB(13, 13, 13).ChangeAlpha(GRADIENT_END_GRADIENT).GetValue() };
    if (isTop) {
        colors[0] = Color::FromRGB(13, 13, 13).ChangeAlpha(GRADIENT_END_GRADIENT).GetValue();
        colors[1] = tvBackColor_.ChangeAlpha(0).GetValue();
    }
    const float stopPositions[2] = { 0.0f, 0.85f };

    paintGradient.setShader(
        SkGradientShader::MakeLinear(points, colors, stopPositions, std::size(colors), SkTileMode::kMirror));
    canvas->drawRect(
        { gradientRect.Left(), gradientRect.Top(), gradientRect.Right(), gradientRect.Bottom() }, paintGradient);
#else
    RSPen penGradient;
    Rect gradientRect;
    auto interval = NormalizeToPx(optionInterval_);
    auto yPos = isTop ? GetOptionTop() : GetOptionBottom() - NormalizeToPx(GRADIENT_HEIGHT);
    gradientRect.SetOffset(Offset(GetOptionLeft() + interval, yPos));
    gradientRect.SetHeight(NormalizeToPx(GRADIENT_HEIGHT));
    gradientRect.SetWidth(GetOptionWidth() - 2 * interval);
    RSPoint beginPoint(static_cast<RSScalar>(gradientRect.Left()), static_cast<RSScalar>(gradientRect.Top()));
    RSPoint endPoint(static_cast<RSScalar>(gradientRect.Left()), static_cast<RSScalar>(gradientRect.Bottom()));
    std::vector<RSPoint> points = { beginPoint, endPoint };
    // color with red 13, green 13, and blue 13 is used for color stop (0.85) in gradient
    std::vector<RSColorQuad> colors = { tvBackColor_.ChangeAlpha(0).GetValue(),
        Color::FromRGB(13, 13, 13).ChangeAlpha(GRADIENT_END_GRADIENT).GetValue() };
    if (isTop) {
        colors.at(0) = Color::FromRGB(13, 13, 13).ChangeAlpha(GRADIENT_END_GRADIENT).GetValue();
        colors.at(1) = tvBackColor_.ChangeAlpha(0).GetValue();
    }
    const std::vector<RSScalar> stopPositions = { 0.0f, 0.85f };
    penGradient.SetShaderEffect(
        RSShaderEffect::CreateLinearGradient(points.at(0), points.at(1), colors, stopPositions, RSTileMode::MIRROR));
    canvas->AttachPen(penGradient);
    canvas->DrawRect(RSRect(gradientRect.Left(), gradientRect.Top(), gradientRect.Right(), gradientRect.Bottom()));
    canvas->DetachPen();
#endif
}

void RosenRenderSelectPopup::Paint(RenderContext& context, const Offset& offset)
{
    if (!isFullScreen_ && isWattingForAnimationStart_) {
        return;
    }

    {
        auto canvas = static_cast<RosenRenderContext*>(&context)->GetCanvas();
        if (!canvas) {
            LOGE("Paint canvas is null");
            return;
        }
#ifndef USE_ROSEN_DRAWING
        canvas->save();
        SkPaint paint;
        paint.setARGB(tvBackColor_.GetAlpha(), tvBackColor_.GetRed(), tvBackColor_.GetGreen(), tvBackColor_.GetBlue());
        auto size = GetLayoutSize();
        canvas->drawRect(SkRect::MakeWH(size.Width(), size.Height()), paint);
        canvas->restore();
#else
        canvas->Save();
        RSPen pen;
        pen.SetARGB(tvBackColor_.GetAlpha(), tvBackColor_.GetRed(), tvBackColor_.GetGreen(), tvBackColor_.GetBlue());
        auto size = GetLayoutSize();
        canvas->AttachPen(pen);
        canvas->DrawRect(RSRect(0, 0, size.Width(), size.Height()));
        canvas->DetachPen();
        canvas->Restore();
#endif
    }
    RenderNode::Paint(context, offset);

    if (!renderScroll_ || SystemProperties::GetDeviceType() != DeviceType::TV) {
        return;
    }
    if (!renderScroll_->IsAtBottom()) {
        PaintGradient(context, false);
    }

    if (!renderScroll_->IsAtTop()) {
        PaintGradient(context, true);
    }
}

} // namespace OHOS::Ace
