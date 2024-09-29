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

#include "core/components/checkable/rosen_render_switch.h"

#ifndef USE_ROSEN_DRAWING
#include "include/core/SkRRect.h"
#endif

#include "core/components/common/painter/rosen_universal_painter.h"
#include "core/pipeline/base/rosen_render_context.h"

namespace OHOS::Ace {

constexpr double HALF = 0.5;
constexpr Dimension FOCUS_PADDING = 2.0_vp;
constexpr Dimension FOCUS_BORDER_WIDTH = 2.0_vp;
constexpr Dimension PRESS_BORDER_RADIUS = 8.0_vp;
constexpr Dimension HOVER_BORDER_RADIUS = 8.0_vp;
constexpr uint32_t FOCUS_BORDER_COLOR = 0xFF0A59F7;
constexpr uint32_t PRESS_COLOR = 0x19000000;
constexpr uint32_t HOVER_COLOR = 0x0C000000;

void RosenRenderSwitch::Paint(RenderContext& context, const Offset& offset)
{
    auto canvas = static_cast<RosenRenderContext*>(&context)->GetCanvas();
    if (!canvas) {
        LOGE("Paint canvas is null");
        return;
    }
#ifndef USE_ROSEN_DRAWING
    SkAutoCanvasRestore acr(canvas, true);
    canvas->clipRect(SkRect::MakeWH(GetLayoutSize().Width(), GetLayoutSize().Height()));
    Offset paintOffset = offset + paintPosition_;
    SkPaint trackPaint;
    SkPaint paint;
    trackPaint.setAntiAlias(true);
    paint.setAntiAlias(true);
#else
    RSAutoCanvasRestore acr(*canvas, true);
    canvas->ClipRect(RSRect(0, 0, GetLayoutSize().Width(), GetLayoutSize().Height()),
        RSClipOp::INTERSECT);
    Offset paintOffset = offset + paintPosition_;
    RosenPaint trackPaint;
    trackPaint.pen.SetAntiAlias(true);
    trackPaint.brush.SetAntiAlias(true);
    trackPaint.useBrush = true;
#endif

    double originX = paintOffset.GetX();
    double originY = paintOffset.GetY();
    double pointOriginX = paintOffset.GetX() + currentPointOriginX_;
    double pointOriginY = paintOffset.GetY() + NormalizeToPx(pointPadding_);

    uint32_t trackColor = 0;
    uint32_t pointColor = 0;
    paintTrackSize_ = switchSize_;
#ifndef USE_ROSEN_DRAWING
    SetPaintStyle(originX, originY, trackColor, pointColor, trackPaint);
#else
    SetPaintStyle(originX, originY, trackColor, pointColor, trackPaint);
#endif
    if (!isDeclarative_) {
        if (IsPhone() && onFocus_) {
            RequestFocusBorder(paintOffset, switchSize_, switchSize_.Height() / 2.0);
        }
    } else {
        if ((IsPhone() || IsTablet()) && onFocus_) {
            PaintFocusBorder(context, paintOffset);
        }
        if ((IsPhone() || IsTablet()) && isTouch_) {
            PaintTouchBoard(offset, context);
        }
        if ((IsPhone() || IsTablet()) && isHover_) {
            PaintHoverBoard(offset, context);
        }
    }

    // paint track rect
    if (!isSwitchDuringAnimation_) {
#ifndef USE_ROSEN_DRAWING
#ifdef OHOS_PLATFORM
        auto recordingCanvas = static_cast<Rosen::RSRecordingCanvas*>(canvas);
        recordingCanvas->SaveAlpha();
        recordingCanvas->MultiplyAlpha(ConfigureOpacity(disabled_));
        PaintTrack(canvas, trackPaint, originX, originY, trackColor);
        recordingCanvas->RestoreAlpha();
#else
        PaintTrack(canvas, trackPaint, originX, originY, trackColor);
#endif
#else
#ifdef OHOS_PLATFORM
        LOGE("Drawing is not supported");
        PaintTrack(canvas, trackPaint, originX, originY, trackColor);
#else
        PaintTrack(canvas, trackPaint, originX, originY, trackColor);
#endif
#endif
    } else {
        // current status is during the switch on/off
#ifndef USE_ROSEN_DRAWING
        DrawTrackAnimation(paintOffset, canvas, trackPaint);
#else
        DrawTrackAnimation(paintOffset, canvas, trackPaint);
#endif
    }

    // paint center point
#ifndef USE_ROSEN_DRAWING
    PaintCenterPoint(canvas, paint, pointOriginX, pointOriginY, pointColor);
#else
    PaintCenterPoint(canvas, pointOriginX, pointOriginY, pointColor);
#endif

    // paint text
    if (renderTextOn_ && renderTextOff_ && showText_) {
        PaintText(Offset(pointOriginX, pointOriginY), context);
    }
}

#ifndef USE_ROSEN_DRAWING
void RosenRenderSwitch::PaintTrack(
    SkCanvas* canvas, SkPaint& trackPaint, double originX, double originY, uint32_t trackColor) const
{
    auto& skPaint = trackPaint;
    SkRRect rrect;
    double trackRadius = switchSize_.Height() / 2.0;
    rrect =
        SkRRect::MakeRectXY({ originX, originY, paintTrackSize_.Width() + originX, paintTrackSize_.Height() + originY },
            trackRadius, trackRadius);
    skPaint.setAntiAlias(true);
    skPaint.setColor(trackColor);
    canvas->drawRRect(rrect, skPaint);
}
#else
void RosenRenderSwitch::PaintTrack(RSCanvas* canvas, RosenPaint& trackPaint, double originX,
    double originY, uint32_t trackColor) const
{
    double trackRadius = switchSize_.Height() / 2.0;
    RSRoundRect rrect(
        RSRect(originX, originY, paintTrackSize_.Width() + originX, paintTrackSize_.Height() + originY),
            trackRadius, trackRadius);
    if (trackPaint.useBrush) {
        trackPaint.brush.SetAntiAlias(true);
        trackPaint.brush.SetColor(trackColor);
        canvas->AttachBrush(trackPaint.brush);
        canvas->DrawRoundRect(rrect);
        canvas->DetachBrush();
    } else {
        trackPaint.pen.SetAntiAlias(true);
        trackPaint.pen.SetColor(trackColor);
        canvas->AttachPen(trackPaint.pen);
        canvas->DrawRoundRect(rrect);
        canvas->DetachPen();
    }
}
#endif

#ifndef USE_ROSEN_DRAWING
void RosenRenderSwitch::PaintCenterPoint(
    SkCanvas* canvas, SkPaint& paint, double pointOriginX, double pointOriginY, uint32_t pointColor) const
{
    auto& skPaint = paint;
    SkRRect rrect;
    skPaint.setAntiAlias(true);
    skPaint.setColor(pointColor);
    rrect = SkRRect::MakeRectXY(
        { pointOriginX, pointOriginY, rawPointSize_.Width() + pointOriginX, rawPointSize_.Height() + pointOriginY },
        pointRadius_, pointRadius_);
    canvas->drawRRect(rrect, skPaint);
    double shadowBorderWidth = NormalizeToPx(shadowWidth_);
    SetStrokeWidth(shadowBorderWidth, paint);
    skPaint.setColor(shadowColor_);
    rrect = SkRRect::MakeRectXY({ pointOriginX - shadowBorderWidth, pointOriginY - shadowBorderWidth,
                                    rawPointSize_.Width() + pointOriginX + shadowBorderWidth,
                                    rawPointSize_.Height() + pointOriginY + shadowBorderWidth },
        pointRadius_ + shadowBorderWidth, pointRadius_ + shadowBorderWidth);
    canvas->drawRRect(rrect, skPaint);
}
#else
void RosenRenderSwitch::PaintCenterPoint(RSCanvas* canvas,
    double pointOriginX, double pointOriginY, uint32_t pointColor) const
{
    RSPen pen;
    RSBrush brush;
    RSRoundRect rrect;
    pen.SetAntiAlias(true);
    brush.SetAntiAlias(true);
    brush.SetColor(pointColor);
    rrect = RSRoundRect(
        RSRect(
            pointOriginX, pointOriginY, rawPointSize_.Width() + pointOriginX, rawPointSize_.Height() + pointOriginY),
        pointRadius_, pointRadius_);
    canvas->AttachBrush(brush);
    canvas->DrawRoundRect(rrect);
    canvas->DetachBrush();
    double shadowBorderWidth = NormalizeToPx(shadowWidth_);
    SetStrokeWidth(shadowBorderWidth, pen);
    pen.SetColor(shadowColor_);
    rrect = RSRoundRect(
        RSRect(pointOriginX - shadowBorderWidth, pointOriginY - shadowBorderWidth,
            rawPointSize_.Width() + pointOriginX + shadowBorderWidth,
            rawPointSize_.Height() + pointOriginY + shadowBorderWidth),
        pointRadius_ + shadowBorderWidth, pointRadius_ + shadowBorderWidth);
    canvas->AttachPen(pen);
    canvas->DrawRoundRect(rrect);
    canvas->DetachPen();
}
#endif

#ifndef USE_ROSEN_DRAWING
void RosenRenderSwitch::DrawTrackAnimation(const Offset& paintOffset, SkCanvas* canvas, SkPaint& trackPaint) const
#else
void RosenRenderSwitch::DrawTrackAnimation(
    const Offset& paintOffset, RSCanvas* canvas, RosenPaint& trackPaint) const
#endif
{
    if (!canvas) {
        LOGE("DrawTrackAnimation Paint canvas is null");
        return;
    }
    double trackRadius = switchSize_.Height() / 2.0;
    switch (uiStatus_) {
        case UIStatus::OFF_TO_ON:
        case UIStatus::ON_TO_OFF:
            DrawTrackOffAndOn(paintOffset, trackRadius, canvas, trackPaint);
            break;
        default:
            LOGE("DrawTrackAnimation current uiStatus is not correct");
            break;
    }
}

#ifndef USE_ROSEN_DRAWING
void RosenRenderSwitch::DrawTrackOffAndOn(
    const Offset& paintOffset, double trackRadius, SkCanvas* canvas, SkPaint& trackPaint) const
#else
void RosenRenderSwitch::DrawTrackOffAndOn(const Offset& paintOffset, double trackRadius,
    RSCanvas* canvas, RosenPaint& trackPaint) const
#endif
{
#ifndef USE_ROSEN_DRAWING
    auto& skPaint = trackPaint;
#endif
    auto pointPadding = NormalizeToPx(pointPadding_);
    double originX = paintOffset.GetX();
    double originY = paintOffset.GetY();
    double pointOriginX = paintOffset.GetX() + currentPointOriginX_;
    double pointOriginY = paintOffset.GetY() + pointPadding;
    // paint the bottom track rect first
#ifndef USE_ROSEN_DRAWING
    SkRRect rrectUpper;
    SkRRect rrectBottom;
    skPaint.setAntiAlias(true);
    rrectBottom =
        SkRRect::MakeRectXY({ originX, originY, paintTrackSize_.Width() + originX, paintTrackSize_.Height() + originY },
            trackRadius, trackRadius);
    skPaint.setColor(inactiveColor_);
    canvas->drawRRect(rrectBottom, skPaint);
#else
    RSRoundRect rrectUpper;
    RSRoundRect rrectBottom = RSRoundRect(
        RSRect(originX, originY, paintTrackSize_.Width() + originX, paintTrackSize_.Height() + originY),
        trackRadius, trackRadius);
    if (trackPaint.useBrush) {
        trackPaint.brush.SetAntiAlias(true);
        trackPaint.brush.SetColor(inactiveColor_);
        canvas->AttachBrush(trackPaint.brush);
        canvas->DrawRoundRect(rrectBottom);
        canvas->DetachBrush();
    } else {
        trackPaint.pen.SetAntiAlias(true);
        trackPaint.pen.SetColor(inactiveColor_);
        canvas->AttachPen(trackPaint.pen);
        canvas->DrawRoundRect(rrectBottom);
        canvas->DetachPen();
    }
#endif

    // paint the upper track rect
    auto width = switchSize_.Width() - rawPointSize_.Width() - pointPadding * 3.0;
    if (NearZero(width)) {
        LOGE("the width is zero");
        return;
    }
    double ratio = (currentPointOriginX_ - pointPadding * 2.0) / width;
    double trackStartDelta = pointPadding;
    double trackStartX = originX + pointPadding - (trackStartDelta * ratio);
    double trackEnd = (rawPointSize_.Width() + pointOriginX) + pointPadding * ratio;
    double trackHeightDelta = paintTrackSize_.Height() + originY - (rawPointSize_.Height() + pointOriginY);
    double radiusDelta = trackRadius - pointRadius_;
    double trackStartY = pointOriginY - (pointPadding * ratio);
#ifndef USE_ROSEN_DRAWING
    rrectUpper = SkRRect::MakeRectXY(
        { trackStartX, trackStartY, trackEnd, rawPointSize_.Height() + pointOriginY + trackHeightDelta * ratio },
        pointRadius_ + radiusDelta * ratio, pointRadius_ + radiusDelta * ratio);
    skPaint.setColor(activeColor_);
    canvas->drawRRect(rrectUpper, skPaint);
#else
    rrectUpper = RSRoundRect(
        RSRect(
            trackStartX, trackStartY, trackEnd, rawPointSize_.Height() + pointOriginY + trackHeightDelta * ratio),
        pointRadius_ + radiusDelta * ratio, pointRadius_ + radiusDelta * ratio);
    if (trackPaint.useBrush) {
        trackPaint.brush.SetColor(activeColor_);
        canvas->AttachBrush(trackPaint.brush);
        canvas->DrawRoundRect(rrectUpper);
        canvas->DetachBrush();
    } else {
        trackPaint.pen.SetColor(activeColor_);
        canvas->AttachPen(trackPaint.pen);
        canvas->DrawRoundRect(rrectUpper);
        canvas->DetachPen();
    }
#endif
}

#ifndef USE_ROSEN_DRAWING
void RosenRenderSwitch::SetPaintStyle(
    double& originX, double& originY, uint32_t& trackColor, uint32_t& pointColor, SkPaint& trackPaint)
#else
void RosenRenderSwitch::SetPaintStyle(
    double& originX, double& originY, uint32_t& trackColor, uint32_t& pointColor, RosenPaint& trackPaint)
#endif
{
    auto borderWidth = NormalizeToPx(borderWidth_);
    switch (uiStatus_) {
        case UIStatus::SELECTED:
            trackColor = activeColor_;
            pointColor = pointColor_;
            isSwitchDuringAnimation_ = false;
            break;
        case UIStatus::UNSELECTED: {
            if (backgroundSolid_) {
                trackColor = inactiveColor_;
                pointColor = pointColor_;
            } else {
#ifndef USE_ROSEN_DRAWING
                SetStrokeWidth(static_cast<float>(borderWidth), trackPaint);
#else
                SetStrokeWidth(static_cast<float>(borderWidth), trackPaint.pen);
                trackPaint.useBrush = false;
#endif
                double strokeOffset = borderWidth / 2.0;
                paintTrackSize_.SetWidth(switchSize_.Width() - borderWidth);
                paintTrackSize_.SetHeight(switchSize_.Height() - borderWidth);
                originX += strokeOffset;
                originY += strokeOffset;
                trackColor = inactiveColor_;
                pointColor = inactiveColor_;
            }
            isSwitchDuringAnimation_ = false;
            break;
        }
        case UIStatus::FOCUS: { // focus of unselected
#ifndef USE_ROSEN_DRAWING
            SetStrokeWidth(static_cast<float>(borderWidth), trackPaint);
#else
            SetStrokeWidth(static_cast<float>(borderWidth), trackPaint.pen);
            trackPaint.useBrush = false;
#endif
            double strokeOffset = borderWidth / 2.0;
            paintTrackSize_.SetWidth(switchSize_.Width() - borderWidth);
            paintTrackSize_.SetHeight(switchSize_.Height() - borderWidth);
            originX += strokeOffset;
            originY += strokeOffset;
            trackColor = focusColor_;
            pointColor = focusColor_;
            isSwitchDuringAnimation_ = false;
            break;
        }
        case UIStatus::OFF_TO_ON:
        case UIStatus::ON_TO_OFF: {
            isSwitchDuringAnimation_ = true;
            pointColor = pointColor_;
            break;
        }
        default:
            LOGE("unknown ui status");
            break;
    }
}

Size RosenRenderSwitch::CalculateTextSize(const std::string& text, RefPtr<RenderText>& renderText)
{
    if (!renderText) {
        LOGW("the render text is nullptr");
        return Size();
    }
    renderText->SetTextData(text);
    renderText->PerformLayout();
    return renderText->GetLayoutSize();
}

void RosenRenderSwitch::PaintFocusBorder(RenderContext& context, const Offset& offset)
{
    auto canvas = static_cast<RosenRenderContext*>(&context)->GetCanvas();
    if (!canvas) {
        return;
    }
    double focusBorderHeight = switchSize_.Height() + NormalizeToPx(FOCUS_PADDING * 2 + FOCUS_BORDER_WIDTH);
    double focusBorderWidth = switchSize_.Width() + NormalizeToPx(FOCUS_PADDING * 2 + FOCUS_BORDER_WIDTH);
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

void RosenRenderSwitch::PaintTouchBoard(const Offset& offset, RenderContext& context)
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
        width_, height_), Radius(NormalizeToPx(PRESS_BORDER_RADIUS))), PRESS_COLOR, dipScale);
}

void RosenRenderSwitch::PaintHoverBoard(const Offset& offset, RenderContext& context)
{
    auto canvas = static_cast<RosenRenderContext*>(&context)->GetCanvas();
    if (!canvas) {
        return;
    }
    Size hoverSize = Size(width_, height_);
    RosenUniversalPainter::DrawHoverBackground(canvas, Rect(offset, hoverSize), HOVER_COLOR,
        NormalizeToPx(HOVER_BORDER_RADIUS));
}

} // namespace OHOS::Ace
