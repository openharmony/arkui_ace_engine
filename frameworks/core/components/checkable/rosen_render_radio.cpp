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

#include "core/components/checkable/rosen_render_radio.h"

#include "core/components/common/painter/rosen_universal_painter.h"
#include "core/pipeline/base/rosen_render_context.h"

namespace OHOS::Ace {

constexpr double HALF = 0.5;
constexpr Dimension FOCUS_PADDING = 2.0_vp;
constexpr Dimension FOCUS_BORDER_WIDTH = 2.0_vp;
constexpr uint32_t FOCUS_BORDER_COLOR = 0xFF0A59F7;
constexpr uint32_t PRESS_COLOR = 0x19000000;
constexpr uint32_t HOVER_COLOR = 0x0C000000;

void RosenRenderRadio::Paint(RenderContext& context, const Offset& offset)
{
    auto paintOffset = offset + paintPosition_;
    auto canvas = static_cast<RosenRenderContext*>(&context)->GetCanvas();
    if (!canvas) {
        LOGE("Paint canvas is null");
        return;
    }
#ifndef USE_ROSEN_DRAWING
    SkPaint paint;
    paint.setAntiAlias(true);
#else
    RSPen pen;
    pen.SetAntiAlias(true);
    RSBrush brush;
#endif
    if (!isDeclarative_) {
        if (IsPhone() && onFocus_) {
            RequestFocusBorder(paintOffset, drawSize_, drawSize_.Width() / 2.0);
        }
    } else {
        if ((IsPhone() || IsTablet()) && onFocus_) {
            DrawFocusBorder(context, paintOffset);
        }
        if ((IsPhone() || IsTablet()) && isTouch_) {
            DrawTouchBoard(offset, context);
        }
        if ((IsPhone() || IsTablet()) && isHover_) {
            DrawHoverBoard(offset, context);
        }
    }
    double centerX = outCircleRadius_ + paintOffset.GetX();
    double centerY = outCircleRadius_ + paintOffset.GetY();
    auto borderWidth = NormalizeToPx(borderWidth_);
#ifndef USE_ROSEN_DRAWING
    switch (uiStatus_) {
        case UIStatus::SELECTED:
            // draw stroke border
            paint.setAntiAlias(true);
            paint.setColor(activeColor_);
            if (disabled_) {
                paint.setColor(Color(activeColor_).BlendOpacity(ConfigureOpacity(disabled_)).GetValue());
            }
            canvas->drawCircle(centerX, centerY, outCircleRadius_ * totalScale_, paint);

            // draw shadow
            if (!NearZero(pointScale_) && !NearEqual(pointScale_, 1.0)) {
                paint.setColor(shadowColor_);
                canvas->drawCircle(
                    centerX, centerY, outCircleRadius_ * pointScale_ + NormalizeToPx(shadowWidth_), paint);
            }

            // draw inner circle
            paint.setColor(pointColor_);
            canvas->drawCircle(centerX, centerY, outCircleRadius_ * pointScale_, paint);
            break;
        case UIStatus::UNSELECTED:
            // draw inner circle
            paint.setColor(inactivePointColor_);
            canvas->drawCircle(centerX, centerY, outCircleRadius_ - borderWidth / 2.0, paint);

            // draw border with unselected color
            paint.setColor(inactiveColor_);
            if (disabled_) {
                paint.setColor(Color(inactiveColor_).BlendOpacity(ConfigureOpacity(disabled_)).GetValue());
            }
            SetStrokeWidth(borderWidth, paint);
            canvas->drawCircle(centerX, centerY, outCircleRadius_ - borderWidth / 2.0, paint);
            break;
        case UIStatus::FOCUS: // focus of unselected
            // draw inner circle
            paint.setColor(inactivePointColor_);
            canvas->drawCircle(centerX, centerY, outCircleRadius_ - borderWidth / 2.0, paint);

            // draw border with focus color
            SetStrokeWidth(borderWidth, paint);
            paint.setColor(focusColor_);
            canvas->drawCircle(centerX, centerY, outCircleRadius_ - borderWidth / 2.0, paint);
            break;
        default:
            LOGE("unknown ui status");
            break;
    }
#else
    switch (uiStatus_) {
        case UIStatus::SELECTED:
            // draw stroke border
            brush.SetAntiAlias(true);
            brush.SetColor(activeColor_);
            if (disabled_) {
                brush.SetColor(Color(activeColor_).BlendOpacity(ConfigureOpacity(disabled_)).GetValue());
            }
            canvas->AttachBrush(brush);
            canvas->DrawCircle(RSPoint(centerX, centerY), outCircleRadius_ * totalScale_);
            canvas->DetachBrush();

            // draw shadow
            if (!NearZero(pointScale_) && !NearEqual(pointScale_, 1.0)) {
                brush.SetColor(shadowColor_);
                canvas->AttachBrush(brush);
                canvas->DrawCircle(RSPoint(centerX, centerY),
                    outCircleRadius_ * pointScale_ + NormalizeToPx(shadowWidth_));
                canvas->DetachBrush();
            }

            // draw inner circle
            brush.SetColor(pointColor_);
            canvas->AttachBrush(brush);
            canvas->DrawCircle(RSPoint(centerX, centerY), outCircleRadius_ * pointScale_);
            canvas->DetachBrush();
            break;
        case UIStatus::UNSELECTED:
            // draw inner circle
            brush.SetColor(inactivePointColor_);
            canvas->AttachBrush(brush);
            canvas->DrawCircle(RSPoint(centerX, centerY), outCircleRadius_ - borderWidth / 2.0);
            canvas->DetachBrush();

            // draw border with unselected color
            pen.SetColor(inactiveColor_);
            if (disabled_) {
                pen.SetColor(Color(inactiveColor_).BlendOpacity(ConfigureOpacity(disabled_)).GetValue());
            }
            SetStrokeWidth(borderWidth, pen);
            canvas->AttachPen(pen);
            canvas->DrawCircle(RSPoint(centerX, centerY), outCircleRadius_ - borderWidth / 2.0);
            canvas->DetachPen();
            break;
        case UIStatus::FOCUS: // focus of unselected
            // draw inner circle
            pen.SetColor(inactivePointColor_);
            canvas->AttachPen(pen);
            canvas->DrawCircle(RSPoint(centerX, centerY), outCircleRadius_ - borderWidth / 2.0);
            canvas->DetachPen();

            // draw border with focus color
            SetStrokeWidth(borderWidth, pen);
            pen.SetColor(focusColor_);
            canvas->AttachPen(pen);
            canvas->DrawCircle(RSPoint(centerX, centerY), outCircleRadius_ - borderWidth / 2.0);
            canvas->DetachPen();
            break;
        default:
            LOGE("unknown ui status");
            break;
    }
#endif
}

void RosenRenderRadio::DrawFocusBorder(RenderContext& context, const Offset& offset)
{
    auto canvas = static_cast<RosenRenderContext*>(&context)->GetCanvas();
    if (!canvas) {
        return;
    }
    double focusBorderWidth = drawSize_.Width() + NormalizeToPx(FOCUS_PADDING * 2 + FOCUS_BORDER_WIDTH);
    double focusBorderHeight = drawSize_.Height() + NormalizeToPx(FOCUS_PADDING * 2 + FOCUS_BORDER_WIDTH);
    double focusRadius = focusBorderHeight * HALF;
#ifndef USE_ROSEN_DRAWING
    SkPaint paint;
    paint.setColor(FOCUS_BORDER_COLOR);
    paint.setStrokeWidth(NormalizeToPx(FOCUS_BORDER_WIDTH));
    paint.setStyle(SkPaint::Style::kStroke_Style);
    paint.setAntiAlias(true);
    SkRRect rRect;
    rRect.setRectXY(SkRect::MakeIWH(focusBorderWidth, focusBorderHeight), focusRadius, focusRadius);
    rRect.offset(offset.GetX() - NormalizeToPx(FOCUS_PADDING + FOCUS_BORDER_WIDTH * HALF),
        offset.GetY() - NormalizeToPx(FOCUS_PADDING + FOCUS_BORDER_WIDTH * HALF));
    canvas->drawRRect(rRect, paint);
#else
    RSPen pen;
    pen.SetColor(FOCUS_BORDER_COLOR);
    pen.SetWidth(NormalizeToPx(FOCUS_BORDER_WIDTH));
    pen.SetAntiAlias(true);
    RSRoundRect rRect(
        RSRect(0, 0, focusBorderWidth, focusBorderHeight), focusRadius, focusRadius);
    rRect.Offset(offset.GetX() - NormalizeToPx(FOCUS_PADDING + FOCUS_BORDER_WIDTH * HALF),
        offset.GetY() - NormalizeToPx(FOCUS_PADDING + FOCUS_BORDER_WIDTH * HALF));
    canvas->AttachPen(pen);
    canvas->DrawRoundRect(rRect);
    canvas->DetachPen();
#endif
}

void RosenRenderRadio::DrawTouchBoard(const Offset& offset, RenderContext& context)
{
    auto canvas = static_cast<RosenRenderContext*>(&context)->GetCanvas();
    if (!canvas) {
        return;
    }
    double dipScale = 1.0;
    auto pipelineContext = GetContext().Upgrade();
    if (pipelineContext) {
        dipScale = pipelineContext->GetDipScale();
    }
    RosenUniversalPainter::DrawRRectBackground(canvas, RRect::MakeRRect(Rect(offset.GetX(), offset.GetY(),
        width_, height_), Radius(height_ * HALF)), PRESS_COLOR, dipScale);
}

void RosenRenderRadio::DrawHoverBoard(const Offset& offset, RenderContext& context)
{
    auto canvas = static_cast<RosenRenderContext*>(&context)->GetCanvas();
    if (!canvas) {
        return;
    }
    Size hoverSize = Size(width_, height_);
    RosenUniversalPainter::DrawHoverBackground(canvas, Rect(offset, hoverSize), HOVER_COLOR, height_ * HALF);
}

} // namespace OHOS::Ace
