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

#include "core/components/checkable/rosen_render_checkbox.h"

#include "core/components/common/painter/rosen_universal_painter.h"
#include "core/pipeline/base/rosen_render_context.h"

namespace OHOS::Ace {
namespace {

constexpr float CHECK_MARK_START_X_POSITION = 0.25f;
constexpr float CHECK_MARK_START_Y_POSITION = 0.49f;
constexpr float CHECK_MARK_MIDDLE_X_POSITION = 0.44f;
constexpr float CHECK_MARK_MIDDLE_Y_POSITION = 0.68f;
constexpr float CHECK_MARK_END_X_POSITION = 0.76f;
constexpr float CHECK_MARK_END_Y_POSITION = 0.33f;
constexpr float CHECK_MARK_PART_START_X_POSITION = 0.20f;
constexpr float CHECK_MARK_PART_END_Y_POSITION = 0.80f;
constexpr float CHECK_MARK_PART_Y_POSITION = 0.50f;
constexpr double CHECK_MARK_LEFT_ANIMATION_PERCENT = 0.45;
constexpr double CHECK_MARK_RIGHT_ANIMATION_PERCENT = 0.55;
constexpr double DEFAULT_MAX_CHECKBOX_SHAPE_SCALE = 1.0;
constexpr double DEFAULT_MIN_CHECKBOX_SHAPE_SCALE = 0.0;
constexpr Dimension FOCUS_PADDING = 2.0_vp;
constexpr Dimension FOCUS_BORDER_WIDTH = 2.0_vp;
constexpr uint32_t FOCUS_BORDER_COLOR = 0xFF0A59F7;
constexpr Dimension PRESS_BORDER_RADIUS = 8.0_vp;
constexpr Dimension HOVER_BORDER_RADIUS = 8.0_vp;
constexpr uint32_t PRESS_COLOR = 0x19000000;
constexpr uint32_t HOVER_COLOR = 0x0C000000;

} // namespace

void RosenRenderCheckbox::Paint(RenderContext& context, const Offset& offset)
{
    auto canvas = static_cast<RosenRenderContext*>(&context)->GetCanvas();
    if (!canvas) {
        LOGE("Paint canvas is null");
        return;
    }
    auto paintOffset = offset + paintPosition_;
    if (isDeclarative_) {
        if ((IsPhone() || IsTablet()) && onFocus_) {
            DrawFocusBorder(context, paintOffset);
        }
        if ((IsPhone() || IsTablet()) && isTouch_) {
            DrawTouchBoard(offset, context);
        }
        if ((IsPhone() || IsTablet()) && isHover_) {
            DrawHoverBoard(offset, context);
        }
    } else {
        if (IsPhone() && onFocus_) {
            RequestFocusBorder(paintOffset, drawSize_, NormalizeToPx(borderRadius_));
        }
    }
    RSPen strokePen;
    RSPen shadowPen;
    shadowPen.SetAntiAlias(true);
    strokePen.SetAntiAlias(true);
    shadowPen.SetColor(shadowColor_);
    shadowPen.SetCapStyle(RSPen::CapStyle::ROUND_CAP);
    SetStrokeWidth(NormalizeToPx(checkStroke_ + shadowWidth_ * 2), shadowPen);
    SetUIStatus(canvas, paintOffset, strokePen, shadowPen);
}

void RosenRenderCheckbox::SetUIStatus(RSCanvas* canvas,
    const Offset& paintOffset, RSPen& strokePaint, RSPen& shadowPaint)
{
    switch (uiStatus_) {
        case UIStatus::SELECTED: {
            DrawActiveBorder(canvas, paintOffset, strokePaint);
            DrawCheck(canvas, paintOffset, strokePaint, shadowPaint);
            break;
        }
        case UIStatus::UNSELECTED: {
            DrawUnselected(canvas, paintOffset, inactiveColor_, strokePaint);
            break;
        }
        case UIStatus::FOCUS: { // focus of unselected
            DrawUnselected(canvas, paintOffset, focusColor_, strokePaint);
            break;
        }
        case UIStatus::OFF_TO_ON: {
            DrawActiveBorder(canvas, paintOffset, strokePaint);
            DrawAnimationOffToOn(canvas, paintOffset, strokePaint, shadowPaint);
            break;
        }
        case UIStatus::ON_TO_OFF: {
            DrawActiveBorder(canvas, paintOffset, strokePaint);
            DrawAnimationOnToOff(canvas, paintOffset, strokePaint, shadowPaint);
            break;
        }
        case UIStatus::PART: {
            DrawActiveBorder(canvas, paintOffset, strokePaint);
            DrawPartSelect(canvas, paintOffset, strokePaint, shadowPaint);
            break;
        }
        case UIStatus::PART_TO_OFF: {
            DrawUnselected(canvas, paintOffset, inactiveColor_, strokePaint);
            break;
        }
        case UIStatus::OFF_TO_PART: {
            DrawUnselected(canvas, paintOffset, inactiveColor_, strokePaint);
            break;
        }
        case UIStatus::PART_TO_ON: {
            DrawUnselected(canvas, paintOffset, inactiveColor_, strokePaint);
            break;
        }
        case UIStatus::ON_TO_PART: {
            DrawUnselected(canvas, paintOffset, inactiveColor_, strokePaint);
            break;
        }
        default:
            LOGE("unknown ui status");
            break;
    }
}

void RosenRenderCheckbox::DrawActiveBorder(
    RSCanvas* canvas, const Offset& paintOffset, RSPen& strokePen) const
{
    RSBrush brush;
    brush.SetAntiAlias(true);
    brush.SetColor(activeColor_);
    canvas->AttachBrush(brush);
    DrawBorder(canvas, paintOffset, drawSize_);
    canvas->DetachBrush();

    SetStrokeWidth(NormalizeToPx(checkStroke_), strokePen);
    strokePen.SetColor(pointColor_);
    strokePen.SetCapStyle(RSPen::CapStyle::ROUND_CAP);
}

void RosenRenderCheckbox::DrawPartSelect(RSCanvas* canvas, const Offset& origin,
    RSPen& pen, const RSPen& shadowPen) const
{
    RSRecordingPath path;
    double originX = origin.GetX();
    double originY = origin.GetY();
    const Offset start =
        Offset(drawSize_.Width() * CHECK_MARK_PART_START_X_POSITION, drawSize_.Width() * CHECK_MARK_PART_Y_POSITION);
    const Offset end =
        Offset(drawSize_.Width() * CHECK_MARK_PART_END_Y_POSITION, drawSize_.Width() * CHECK_MARK_PART_Y_POSITION);

    path.MoveTo(originX + start.GetX(), originY + start.GetY());
    path.LineTo(originX + end.GetX(), originY + end.GetY());

    canvas->AttachPen(shadowPen);
    canvas->DrawPath(path);
    canvas->DetachPen();
    canvas->AttachPen(pen);
    canvas->DrawPath(path);
    canvas->DetachPen();
}

void RosenRenderCheckbox::DrawUnselected(
    RSCanvas* canvas, const Offset& origin, uint32_t paintColor, RSPen& pen) const
{
    Offset paintOffset = origin;
    auto borderWidth = NormalizeToPx(borderWidth_);
    SetStrokeWidth(borderWidth, pen);
    double strokeOffset = borderWidth / 2;
    paintOffset += Offset(strokeOffset, strokeOffset);
    Size paintSize = drawSize_;
    paintSize.SetWidth(paintSize.Width() - borderWidth);
    paintSize.SetHeight(paintSize.Height() - borderWidth);
    pen.SetColor(paintColor);

    RSBrush bgBrush;
    bgBrush.SetColor(inactivePointColor_);
    bgBrush.SetAntiAlias(pen.IsAntiAlias());

    canvas->AttachBrush(bgBrush);
    DrawBorder(canvas, paintOffset, paintSize);
    canvas->DetachBrush();

    canvas->AttachPen(pen);
    DrawBorder(canvas, paintOffset, paintSize);
    canvas->DetachPen();
}

void RosenRenderCheckbox::DrawCheck(RSCanvas* canvas, const Offset& origin,
    const RSPen& pen, const RSPen& shadowPen) const
{
    RSRecordingPath path;
    double originX = origin.GetX();
    double originY = origin.GetY();
    const Offset start =
        Offset(drawSize_.Width() * CHECK_MARK_START_X_POSITION, drawSize_.Width() * CHECK_MARK_START_Y_POSITION);
    const Offset middle =
        Offset(drawSize_.Width() * CHECK_MARK_MIDDLE_X_POSITION, drawSize_.Width() * CHECK_MARK_MIDDLE_Y_POSITION);
    const Offset end =
        Offset(drawSize_.Width() * CHECK_MARK_END_X_POSITION, drawSize_.Width() * CHECK_MARK_END_Y_POSITION);

    path.MoveTo(originX + start.GetX(), originY + start.GetY());
    path.LineTo(originX + middle.GetX(), originY + middle.GetY());

    canvas->AttachPen(shadowPen);
    canvas->DrawPath(path);
    canvas->DetachPen();

    canvas->AttachPen(pen);
    canvas->DrawPath(path);
    canvas->DetachPen();

    path.MoveTo(originX + middle.GetX(), originY + middle.GetY());
    path.LineTo(originX + end.GetX(), originY + end.GetY());

    canvas->AttachPen(shadowPen);
    canvas->DrawPath(path);
    canvas->DetachPen();

    canvas->AttachPen(pen);
    canvas->DrawPath(path);
    canvas->DetachPen();
}

void RosenRenderCheckbox::DrawBorder(RSCanvas* canvas, const Offset& origin, const Size& paintSize) const
{
    double originX = origin.GetX();
    double originY = origin.GetY();
    double borderRadius = NormalizeToPx(borderRadius_);
    RSRoundRect rrect(
        RSRect(originX, originY, paintSize.Width() + originX, paintSize.Height() + originY),
        borderRadius, borderRadius);
    canvas->DrawRoundRect(rrect);
}

void RosenRenderCheckbox::DrawAnimationOffToOn(RSCanvas* canvas, const Offset& origin,
    const RSPen& pen, const RSPen& shadowPen) const
{
    RSPath path;
    double originX = origin.GetX();
    double originY = origin.GetY();
    const Offset start =
        Offset(drawSize_.Width() * CHECK_MARK_START_X_POSITION, drawSize_.Width() * CHECK_MARK_START_Y_POSITION);
    const Offset middle =
        Offset(drawSize_.Width() * CHECK_MARK_MIDDLE_X_POSITION, drawSize_.Width() * CHECK_MARK_MIDDLE_Y_POSITION);
    const Offset end =
        Offset(drawSize_.Width() * CHECK_MARK_END_X_POSITION, drawSize_.Width() * CHECK_MARK_END_Y_POSITION);

    double deltaX = middle.GetX() - start.GetX();
    double deltaY = middle.GetY() - start.GetY();
    path.MoveTo(originX + start.GetX(), originY + start.GetY());
    double ratio = DEFAULT_MIN_CHECKBOX_SHAPE_SCALE;
    if (shapeScale_ < CHECK_MARK_LEFT_ANIMATION_PERCENT) {
        ratio = shapeScale_ / CHECK_MARK_LEFT_ANIMATION_PERCENT;
        path.LineTo(originX + start.GetX() + deltaX * ratio, originY + start.GetY() + deltaY * ratio);
    } else {
        path.LineTo(originX + middle.GetX(), originY + middle.GetY());
    }
    canvas->AttachPen(shadowPen);
    canvas->DrawPath(path);
    canvas->DetachPen();

    canvas->AttachPen(pen);
    canvas->DrawPath(path);
    canvas->DetachPen();

    if (shapeScale_ > CHECK_MARK_LEFT_ANIMATION_PERCENT) {
        deltaX = end.GetX() - middle.GetX();
        deltaY = middle.GetY() - end.GetY();
        path.MoveTo(originX + middle.GetX(), originY + middle.GetY());
        if (shapeScale_ == DEFAULT_MAX_CHECKBOX_SHAPE_SCALE) {
            path.LineTo(originX + end.GetX(), originY + end.GetY());
        } else {
            ratio = (shapeScale_ - CHECK_MARK_LEFT_ANIMATION_PERCENT) / CHECK_MARK_RIGHT_ANIMATION_PERCENT;
            path.LineTo(originX + middle.GetX() + deltaX * ratio, originY + middle.GetY() - deltaY * ratio);
        }
        canvas->AttachPen(shadowPen);
        canvas->DrawPath(path);
        canvas->DetachPen();

        canvas->AttachPen(pen);
        canvas->DrawPath(path);
        canvas->DetachPen();
    }
}

void RosenRenderCheckbox::DrawAnimationOnToOff(RSCanvas* canvas, const Offset& origin,
    const RSPen& pen, const RSPen& shadowPen) const
{
    if (shapeScale_ == DEFAULT_MIN_CHECKBOX_SHAPE_SCALE) {
        return;
    }
    RSRecordingPath path;
    double originX = origin.GetX();
    double originY = origin.GetY();
    const Offset start =
        Offset(drawSize_.Width() * CHECK_MARK_START_X_POSITION, drawSize_.Width() * CHECK_MARK_START_Y_POSITION);
    const Offset middle =
        Offset(drawSize_.Width() * CHECK_MARK_MIDDLE_X_POSITION, drawSize_.Width() * CHECK_MARK_MIDDLE_Y_POSITION);
    const Offset end =
        Offset(drawSize_.Width() * CHECK_MARK_END_X_POSITION, drawSize_.Width() * CHECK_MARK_END_Y_POSITION);
    const Offset middlePoint = Offset(drawSize_.Width() / 2, drawSize_.Height() / 2);
    double deltaX = middlePoint.GetX() - start.GetX();
    double deltaY = middlePoint.GetY() - start.GetY();
    double ratio = DEFAULT_MAX_CHECKBOX_SHAPE_SCALE - shapeScale_;
    path.MoveTo(originX + start.GetX() + deltaX * ratio, originY + start.GetY() + deltaY * ratio);
    deltaX = middlePoint.GetX() - middle.GetX();
    deltaY = middle.GetY() - middlePoint.GetY();
    path.LineTo(originX + middle.GetX() + deltaX * ratio, originY + middle.GetY() - deltaY * ratio);

    canvas->AttachPen(shadowPen);
    canvas->DrawPath(path);
    canvas->DetachPen();

    canvas->AttachPen(pen);
    canvas->DrawPath(path);
    canvas->DetachPen();

    path.MoveTo(originX + middle.GetX() + deltaX * ratio, originY + middle.GetY() - deltaY * ratio);
    deltaX = end.GetX() - middlePoint.GetX();
    deltaY = middlePoint.GetY() - end.GetY();
    path.LineTo(originX + end.GetX() - deltaX * ratio, originY + end.GetY() + deltaY * ratio);

    canvas->AttachPen(shadowPen);
    canvas->DrawPath(path);
    canvas->DetachPen();

    canvas->AttachPen(pen);
    canvas->DrawPath(path);
    canvas->DetachPen();
}

void RosenRenderCheckbox::DrawFocusBorder(RenderContext& context, const Offset& offset)
{
    auto canvas = static_cast<RosenRenderContext*>(&context)->GetCanvas();
    if (!canvas) {
        LOGE("paint canvas is null");
        return;
    }
    Size paintSize = drawSize_;
    double focusBorderHeight = paintSize.Height() + NormalizeToPx(FOCUS_PADDING * 2 + FOCUS_BORDER_WIDTH);
    double focusBorderWidth = paintSize.Width() + NormalizeToPx(FOCUS_PADDING * 2 + FOCUS_BORDER_WIDTH);
    double focusRadius = NormalizeToPx(borderRadius_ + FOCUS_PADDING);

    RSPen pen;
    pen.SetColor(FOCUS_BORDER_COLOR);
    pen.SetWidth(NormalizeToPx(FOCUS_BORDER_WIDTH));
    pen.SetAntiAlias(true);
    RSRoundRect rRect(
        RSRect(0, 0, focusBorderWidth, focusBorderHeight), focusRadius, focusRadius);
    rRect.Offset(offset.GetX() - NormalizeToPx(FOCUS_PADDING + FOCUS_BORDER_WIDTH / 2),
        offset.GetY() - NormalizeToPx(FOCUS_PADDING + FOCUS_BORDER_WIDTH / 2));
    canvas->AttachPen(pen);
    canvas->DrawRoundRect(rRect);
    canvas->DetachPen();
}

void RosenRenderCheckbox::DrawTouchBoard(const Offset& offset, RenderContext& context)
{
    auto canvas = static_cast<RosenRenderContext*>(&context)->GetCanvas();
    if (!canvas) {
        LOGE("Paint canvas is null");
        return;
    }
    double dipScale = 1.0;
    auto pipelineContext = GetContext().Upgrade();
    if (pipelineContext) {
        dipScale = pipelineContext->GetDipScale();
    }
    RosenUniversalPainter::DrawRRectBackground(canvas, RRect::MakeRRect(Rect(offset.GetX(), offset.GetY(),
        width_, height_), Radius(NormalizeToPx(PRESS_BORDER_RADIUS))), PRESS_COLOR, dipScale);
}

void RosenRenderCheckbox::DrawHoverBoard(const Offset& offset, RenderContext& context)
{
    auto canvas = static_cast<RosenRenderContext*>(&context)->GetCanvas();
    if (!canvas) {
        LOGE("Paint canvas is null");
        return;
    }
    Size hoverSize = Size(width_, height_);
    RosenUniversalPainter::DrawHoverBackground(canvas, Rect(offset, hoverSize), HOVER_COLOR,
        NormalizeToPx(HOVER_BORDER_RADIUS));
}

} // namespace OHOS::Ace
