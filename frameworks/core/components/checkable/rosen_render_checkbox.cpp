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

#ifndef USE_ROSEN_DRAWING
#include "include/core/SkMaskFilter.h"
#include "include/core/SkPaint.h"
#include "include/core/SkPath.h"
#endif

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
#ifndef USE_ROSEN_DRAWING
    SkPaint strokePaint;
    SkPaint shadowPaint;
    shadowPaint.setAntiAlias(true);
    strokePaint.setAntiAlias(true);
    shadowPaint.setColor(shadowColor_);
    shadowPaint.setStrokeCap(SkPaint::kRound_Cap);
    SetStrokeWidth(NormalizeToPx(checkStroke_ + shadowWidth_ * 2), shadowPaint);
    SetUIStatus(canvas, paintOffset, strokePaint, shadowPaint);
#else
    RSPen strokePen;
    RSPen shadowPen;
    shadowPen.SetAntiAlias(true);
    strokePen.SetAntiAlias(true);
    shadowPen.SetColor(shadowColor_);
    shadowPen.SetCapStyle(RSPen::CapStyle::ROUND_CAP);
    SetStrokeWidth(NormalizeToPx(checkStroke_ + shadowWidth_ * 2), shadowPen);
    SetUIStatus(canvas, paintOffset, strokePen, shadowPen);
#endif
}

#ifndef USE_ROSEN_DRAWING
void RosenRenderCheckbox::SetUIStatus(SkCanvas* canvas,
    const Offset& paintOffset, SkPaint& strokePaint, SkPaint& shadowPaint)
#else
void RosenRenderCheckbox::SetUIStatus(RSCanvas* canvas,
    const Offset& paintOffset, RSPen& strokePaint, RSPen& shadowPaint)
#endif
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

#ifndef USE_ROSEN_DRAWING
void RosenRenderCheckbox::DrawActiveBorder(SkCanvas* canvas, const Offset& paintOffset, SkPaint& strokePaint) const
{
    SkPaint skPaint;
    skPaint.setAntiAlias(true);
    skPaint.setColor(activeColor_);
    DrawBorder(canvas, paintOffset, skPaint, drawSize_);

    SetStrokeWidth(NormalizeToPx(checkStroke_), strokePaint);
    strokePaint.setColor(pointColor_);
    strokePaint.setStrokeCap(SkPaint::kRound_Cap);
}
#else
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
#endif

#ifndef USE_ROSEN_DRAWING
void RosenRenderCheckbox::DrawPartSelect(
    SkCanvas* canvas, const Offset& origin, SkPaint& paint, const SkPaint& shadowPaint) const
{
    SkPath path;
    double originX = origin.GetX();
    double originY = origin.GetY();
    const Offset start =
        Offset(drawSize_.Width() * CHECK_MARK_PART_START_X_POSITION, drawSize_.Width() * CHECK_MARK_PART_Y_POSITION);
    const Offset end =
        Offset(drawSize_.Width() * CHECK_MARK_PART_END_Y_POSITION, drawSize_.Width() * CHECK_MARK_PART_Y_POSITION);

    path.moveTo(originX + start.GetX(), originY + start.GetY());
    path.lineTo(originX + end.GetX(), originY + end.GetY());
    canvas->drawPath(path, shadowPaint);
    canvas->drawPath(path, paint);
}
#else
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
#endif

#ifndef USE_ROSEN_DRAWING
void RosenRenderCheckbox::DrawUnselected(
    SkCanvas* canvas, const Offset& origin, uint32_t paintColor, SkPaint& paint) const
#else
void RosenRenderCheckbox::DrawUnselected(
    RSCanvas* canvas, const Offset& origin, uint32_t paintColor, RSPen& pen) const
#endif
{
    Offset paintOffset = origin;
    auto borderWidth = NormalizeToPx(borderWidth_);
#ifndef USE_ROSEN_DRAWING
    SetStrokeWidth(borderWidth, paint);
#else
    SetStrokeWidth(borderWidth, pen);
#endif
    double strokeOffset = borderWidth / 2;
    paintOffset += Offset(strokeOffset, strokeOffset);
    Size paintSize = drawSize_;
    paintSize.SetWidth(paintSize.Width() - borderWidth);
    paintSize.SetHeight(paintSize.Height() - borderWidth);
#ifndef USE_ROSEN_DRAWING
    paint.setColor(paintColor);
    auto bgPaint = paint;
    bgPaint.setColor(inactivePointColor_);
    bgPaint.setStyle(SkPaint::Style::kFill_Style);
    DrawBorder(canvas, paintOffset, bgPaint, paintSize);
    DrawBorder(canvas, paintOffset, paint, paintSize);
#else
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
#endif
}

#ifndef USE_ROSEN_DRAWING
void RosenRenderCheckbox::DrawCheck(
    SkCanvas* canvas, const Offset& origin, const SkPaint& paint, const SkPaint& shadowPaint) const
{
    SkPath path;
    double originX = origin.GetX();
    double originY = origin.GetY();
    const Offset start =
        Offset(drawSize_.Width() * CHECK_MARK_START_X_POSITION, drawSize_.Width() * CHECK_MARK_START_Y_POSITION);
    const Offset middle =
        Offset(drawSize_.Width() * CHECK_MARK_MIDDLE_X_POSITION, drawSize_.Width() * CHECK_MARK_MIDDLE_Y_POSITION);
    const Offset end =
        Offset(drawSize_.Width() * CHECK_MARK_END_X_POSITION, drawSize_.Width() * CHECK_MARK_END_Y_POSITION);

    path.moveTo(originX + start.GetX(), originY + start.GetY());
    path.lineTo(originX + middle.GetX(), originY + middle.GetY());

    canvas->drawPath(path, shadowPaint);
    canvas->drawPath(path, paint);
    path.moveTo(originX + middle.GetX(), originY + middle.GetY());
    path.lineTo(originX + end.GetX(), originY + end.GetY());

    canvas->drawPath(path, shadowPaint);
    canvas->drawPath(path, paint);
}
#else
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
#endif

#ifndef USE_ROSEN_DRAWING
void RosenRenderCheckbox::DrawBorder(
    SkCanvas* canvas, const Offset& origin, const SkPaint& paint, const Size& paintSize) const
{
    SkRRect rrect;
    double originX = origin.GetX();
    double originY = origin.GetY();
    double borderRadius = NormalizeToPx(borderRadius_);
    rrect = SkRRect::MakeRectXY(
        { originX, originY, paintSize.Width() + originX, paintSize.Height() + originY }, borderRadius, borderRadius);
    canvas->drawRRect(rrect, paint);
}
#else
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
#endif

#ifndef USE_ROSEN_DRAWING
void RosenRenderCheckbox::DrawAnimationOffToOn(
    SkCanvas* canvas, const Offset& origin, const SkPaint& paint, const SkPaint& shadowPaint) const
#else
void RosenRenderCheckbox::DrawAnimationOffToOn(RSCanvas* canvas, const Offset& origin,
    const RSPen& pen, const RSPen& shadowPen) const
#endif
{
#ifndef USE_ROSEN_DRAWING
    SkPath path;
#else
    RSPath path;
#endif
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
#ifndef USE_ROSEN_DRAWING
    path.moveTo(originX + start.GetX(), originY + start.GetY());
    double ratio = DEFAULT_MIN_CHECKBOX_SHAPE_SCALE;
    if (shapeScale_ < CHECK_MARK_LEFT_ANIMATION_PERCENT) {
        ratio = shapeScale_ / CHECK_MARK_LEFT_ANIMATION_PERCENT;
        path.lineTo(originX + start.GetX() + deltaX * ratio, originY + start.GetY() + deltaY * ratio);
    } else {
        path.lineTo(originX + middle.GetX(), originY + middle.GetY());
    }
    canvas->drawPath(path, shadowPaint);
    canvas->drawPath(path, paint);
    if (shapeScale_ > CHECK_MARK_LEFT_ANIMATION_PERCENT) {
        deltaX = end.GetX() - middle.GetX();
        deltaY = middle.GetY() - end.GetY();
        path.moveTo(originX + middle.GetX(), originY + middle.GetY());
        if (shapeScale_ == DEFAULT_MAX_CHECKBOX_SHAPE_SCALE) {
            path.lineTo(originX + end.GetX(), originY + end.GetY());
        } else {
            ratio = (shapeScale_ - CHECK_MARK_LEFT_ANIMATION_PERCENT) / CHECK_MARK_RIGHT_ANIMATION_PERCENT;
            path.lineTo(originX + middle.GetX() + deltaX * ratio, originY + middle.GetY() - deltaY * ratio);
        }
        canvas->drawPath(path, shadowPaint);
        canvas->drawPath(path, paint);
    }
#else
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
#endif
}

#ifndef USE_ROSEN_DRAWING
void RosenRenderCheckbox::DrawAnimationOnToOff(
    SkCanvas* canvas, const Offset& origin, const SkPaint& paint, const SkPaint& shadowPaint) const
#else
void RosenRenderCheckbox::DrawAnimationOnToOff(RSCanvas* canvas, const Offset& origin,
    const RSPen& pen, const RSPen& shadowPen) const
#endif
{
    if (shapeScale_ == DEFAULT_MIN_CHECKBOX_SHAPE_SCALE) {
        return;
    }
#ifndef USE_ROSEN_DRAWING
    SkPath path;
#else
    RSRecordingPath path;
#endif
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
#ifndef USE_ROSEN_DRAWING
    path.moveTo(originX + start.GetX() + deltaX * ratio, originY + start.GetY() + deltaY * ratio);
    deltaX = middlePoint.GetX() - middle.GetX();
    deltaY = middle.GetY() - middlePoint.GetY();
    path.lineTo(originX + middle.GetX() + deltaX * ratio, originY + middle.GetY() - deltaY * ratio);
    canvas->drawPath(path, shadowPaint);
    canvas->drawPath(path, paint);
    path.moveTo(originX + middle.GetX() + deltaX * ratio, originY + middle.GetY() - deltaY * ratio);
    deltaX = end.GetX() - middlePoint.GetX();
    deltaY = middlePoint.GetY() - end.GetY();
    path.lineTo(originX + end.GetX() - deltaX * ratio, originY + end.GetY() + deltaY * ratio);
    canvas->drawPath(path, shadowPaint);
    canvas->drawPath(path, paint);
#else
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
#endif
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

#ifndef USE_ROSEN_DRAWING
    SkPaint paint;
    paint.setColor(FOCUS_BORDER_COLOR);
    paint.setStyle(SkPaint::Style::kStroke_Style);
    paint.setStrokeWidth(NormalizeToPx(FOCUS_BORDER_WIDTH));
    paint.setAntiAlias(true);
    SkRRect rRect;
    rRect.setRectXY(SkRect::MakeIWH(focusBorderWidth, focusBorderHeight), focusRadius, focusRadius);
    rRect.offset(offset.GetX() - NormalizeToPx(FOCUS_PADDING + FOCUS_BORDER_WIDTH / 2),
        offset.GetY() - NormalizeToPx(FOCUS_PADDING + FOCUS_BORDER_WIDTH / 2));
    canvas->drawRRect(rRect, paint);
#else
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
#endif
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
