/*
 * Copyright (c) 2021 Huawei Device Co., Ltd.
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

#include "core/components/common/painter/flutter_decoration_painter.h"

#include <cmath>

#include "flutter/common/task_runners.h"
#include "flutter/lib/ui/ui_dart_state.h"
#include "include/core/SkColor.h"
#include "include/core/SkMaskFilter.h"
#include "include/effects/Sk1DPathEffect.h"
#include "include/effects/SkBlurImageFilter.h"
#include "include/effects/SkDashPathEffect.h"
#include "include/effects/SkGradientShader.h"
#include "include/utils/SkShadowUtils.h"

#include "core/components/common/properties/color.h"
#include "core/pipeline/base/flutter_render_context.h"
#include "core/pipeline/base/render_node.h"
#include "core/pipeline/pipeline_context.h"

namespace OHOS::Ace {
namespace {

constexpr int32_t DOUBLE_WIDTH = 2;
constexpr int32_t DASHED_LINE_LENGTH = 3;
constexpr float BLUR_SIGMA_SCALE = 0.57735f;
constexpr double DEGREES_90 = 90.0;
constexpr double DEGREES_180 = 180.0;
constexpr double DEGREES_270 = 270.0;
constexpr double DEGREES_360 = 360.0;
constexpr float SHADER_PERCENT_ZERO = 0.0f;

constexpr float SHADER_PERCENT_FULL = 1.0f;
constexpr float SHADER_PERCENT_NONE_EXIST = -9999.0f;

} // namespace

FlutterDecorationPainter::FlutterDecorationPainter(
    const RefPtr<Decoration>& decoration, const Rect& paintRect, const Size& paintSize, double dipScale)
    : dipScale_(dipScale), paintRect_(paintRect), decoration_(decoration), paintSize_(paintSize)
{}

void FlutterDecorationPainter::PaintDecoration(const Offset& offset, SkCanvas* canvas, RenderContext& context)
{
    if (!canvas) {
        LOGE("PaintDecoration failed, canvas is null.");
        return;
    }
    if (decoration_) {
        canvas->save();
        SkPaint paint;

        if (opacity_ != UINT8_MAX) {
            paint.setAlpha(opacity_);
        }

        Border border = decoration_->GetBorder();
        flutter::RRect outerRRect = GetBoxRRect(offset + margin_.GetOffsetInPx(scale_), border, 0.0, true);
        if (clipLayer_) {
            // If you want to clip the rounded edges, you need to set a Cliplayer first.
            clipLayer_->SetClipRRect(outerRRect);
        }
        PaintBoxShadows(outerRRect.sk_rrect, decoration_->GetShadows(), canvas);
        canvas->clipRRect(outerRRect.sk_rrect, true);
        PaintColorAndImage(offset, canvas, paint, context);
        if (border.HasValue()) {
            // set AntiAlias
            paint.setAntiAlias(true);
            if (CheckBorderAllEqual(border)) {
                flutter::RRect innerRRect =
                    GetBoxRRect(offset + margin_.GetOffsetInPx(scale_), border, SK_ScalarHalf, true);
                PaintAllEqualBorder(innerRRect, border, canvas, paint);
            } else {
                paint.setStyle(SkPaint::Style::kStroke_Style);
                PaintBorder(offset + margin_.GetOffsetInPx(scale_), border, canvas, paint);
            }
        }
        canvas->restore();
    }
}

void FlutterDecorationPainter::PaintBlur(
    const flutter::RRect& outerRRect, SkCanvas* canvas, const Dimension& blurRadius)
{
    auto radius = NormalizeToPx(blurRadius);
    if (GreatNotEqual(radius, 0.0)) {
        if (canvas) {
            canvas->save();
            canvas->clipRRect(outerRRect.sk_rrect, true);
            // picture will be discard if nothing draw
            canvas->drawColor(Color::TRANSPARENT.GetValue());
            sk_sp<SkImageFilter> filter =
                SkBlurImageFilter::Make(ConvertRadiusToSigma(radius), ConvertRadiusToSigma(radius), nullptr);
            SkCanvas::SaveLayerRec slr(nullptr, nullptr, filter.get(), SkCanvas::kInitWithPrevious_SaveLayerFlag);
            canvas->saveLayer(slr);
            canvas->restore();
            canvas->restore();
        }
    }
}

flutter::RRect FlutterDecorationPainter::GetBoxOuterRRect(const Offset& offset)
{
    flutter::RRect outerRRect;
    if (decoration_) {
        Border border = decoration_->GetBorder();
        outerRRect = GetBoxRRect(offset + margin_.GetOffsetInPx(scale_), border, 0.0, true);
    } else {
        Rect paintSize = paintRect_ + offset;
        outerRRect.sk_rrect = SkRRect::MakeRect(
            SkRect::MakeLTRB(paintSize.Left(), paintSize.Top(), paintSize.Right(), paintSize.Bottom()));
    }
    outerRRect.is_null = false;
    return outerRRect;
}

void FlutterDecorationPainter::PaintColorAndImage(
    const Offset& offset, SkCanvas* canvas, SkPaint& paint, RenderContext& renderContext)
{
    if (!decoration_) {
        return;
    }

    // paint backColor
    bool paintBgColor = false;
    paint.setStyle(SkPaint::Style::kFill_Style);
    Color backColor = decoration_->GetBackgroundColor();
    Color animationColor = decoration_->GetAnimationColor();
    if (backColor != Color::TRANSPARENT) {
        paint.setColor(backColor.GetValue());
        canvas->drawRect(
            SkRect::MakeXYWH(offset.GetX() + NormalizeToPx(margin_.Left()),
                offset.GetY() + NormalizeToPx(margin_.Top()), GetLayoutSize().Width() - NormalizeToPx(margin_.Right()),
                GetLayoutSize().Height() - NormalizeToPx(margin_.Bottom())),
            paint);
        paintBgColor = true;
    }
    if (animationColor != Color::TRANSPARENT) {
        paint.setColor(animationColor.GetValue());
        canvas->drawRect(
            SkRect::MakeXYWH(offset.GetX() + NormalizeToPx(margin_.Left()),
                offset.GetY() + NormalizeToPx(margin_.Top()), GetLayoutSize().Width() - NormalizeToPx(margin_.Right()),
                GetLayoutSize().Height() - NormalizeToPx(margin_.Bottom())),
            paint);
    }

    // paint background image.
    RefPtr<ArcBackground> arcBG = decoration_->GetArcBackground();
    if (arcBG) {
        Color arcColor = arcBG->GetColor();
        if (arcColor != Color::TRANSPARENT) {
            paint.setColor(arcColor.GetValue());
            canvas->drawCircle(arcBG->GetCenter().GetX(), arcBG->GetCenter().GetY(), arcBG->GetRadius(), paint);
            paintBgColor = true;
        }
    }
    if (paintBgColor) {
        return;
    }
    // paint background image.
    if (decoration_->GetImage()) {
        PaintImage(offset, renderContext);
        return;
    }
    // paint Gradient color.
    if (decoration_->GetGradient().IsValid()) {
        PaintGradient(offset, canvas, paint);
    }
}

flutter::RRect FlutterDecorationPainter::GetBoxRRect(
    const Offset& offset, const Border& border, double shrinkFactor, bool isRound)
{
    flutter::RRect rrect = flutter::RRect();
    SkRect skRect {};
    SkVector fRadii[4] = { { 0.0, 0.0 }, { 0.0, 0.0 }, { 0.0, 0.0 }, { 0.0, 0.0 } };
    if (CheckBorderEdgeForRRect(border)) {
        BorderEdge borderEdge = border.Left();
        double borderWidth = NormalizeToPx(borderEdge.GetWidth());
        skRect.setXYWH(SkDoubleToScalar(offset.GetX() + shrinkFactor * borderWidth),
            SkDoubleToScalar(offset.GetY() + shrinkFactor * borderWidth),
            SkDoubleToScalar(paintSize_.Width() - shrinkFactor * DOUBLE_WIDTH * borderWidth),
            SkDoubleToScalar(paintSize_.Height() - shrinkFactor * DOUBLE_WIDTH * borderWidth));
        if (isRound) {
            fRadii[SkRRect::kUpperLeft_Corner].set(
                SkDoubleToScalar(
                    std::max(NormalizeToPx(border.TopLeftRadius().GetX()) - shrinkFactor * borderWidth, 0.0)),
                SkDoubleToScalar(
                    std::max(NormalizeToPx(border.TopLeftRadius().GetY()) - shrinkFactor * borderWidth, 0.0)));
            fRadii[SkRRect::kUpperRight_Corner].set(
                SkDoubleToScalar(
                    std::max(NormalizeToPx(border.TopRightRadius().GetX()) - shrinkFactor * borderWidth, 0.0)),
                SkDoubleToScalar(
                    std::max(NormalizeToPx(border.TopRightRadius().GetY()) - shrinkFactor * borderWidth, 0.0)));
            fRadii[SkRRect::kLowerRight_Corner].set(
                SkDoubleToScalar(
                    std::max(NormalizeToPx(border.BottomRightRadius().GetX()) - shrinkFactor * borderWidth, 0.0)),
                SkDoubleToScalar(
                    std::max(NormalizeToPx(border.BottomRightRadius().GetY()) - shrinkFactor * borderWidth, 0.0)));
            fRadii[SkRRect::kLowerLeft_Corner].set(
                SkDoubleToScalar(
                    std::max(NormalizeToPx(border.BottomLeftRadius().GetX()) - shrinkFactor * borderWidth, 0.0)),
                SkDoubleToScalar(
                    std::max(NormalizeToPx(border.BottomLeftRadius().GetY()) - shrinkFactor * borderWidth, 0.0)));
        }
    } else {
        skRect.setXYWH(SkDoubleToScalar(offset.GetX() + shrinkFactor * NormalizeToPx(border.Left().GetWidth())),
            SkDoubleToScalar(offset.GetY() + shrinkFactor * NormalizeToPx(border.Top().GetWidth())),
            SkDoubleToScalar(
                paintSize_.Width() - shrinkFactor * DOUBLE_WIDTH * NormalizeToPx(border.Right().GetWidth())),
            SkDoubleToScalar(paintSize_.Height() - shrinkFactor * (NormalizeToPx(border.Bottom().GetWidth()) +
                                                                      NormalizeToPx(border.Top().GetWidth()))));
    }
    rrect.sk_rrect.setRectRadii(skRect, fRadii);
    return rrect;
}

void FlutterDecorationPainter::PaintAllEqualBorder(
    const flutter::RRect& rrect, const Border& border, SkCanvas* canvas, SkPaint& paint)
{
    BorderEdge borderEdge = border.Left();
    if (borderEdge.GetColor() == border.Top().GetColor() && borderEdge.GetColor() == border.Right().GetColor() &&
        borderEdge.GetColor() == border.Bottom().GetColor()) {
        SetBorderStyle(borderEdge, paint);
    } else {
        SetBorderStyle(borderEdge, paint, true);
    }
    canvas->drawRRect(rrect.sk_rrect, paint);
}

void FlutterDecorationPainter::SetBorderStyle(const BorderEdge& borderEdge, SkPaint& paint, bool useDefaultColor)
{
    if (borderEdge.HasValue()) {
        double width = NormalizeToPx(borderEdge.GetWidth());
        uint32_t color = useDefaultColor ? Color::BLACK.GetValue() : borderEdge.GetColor().GetValue();
        paint.setStrokeWidth(width);
        paint.setColor(color);
        paint.setStyle(SkPaint::Style::kStroke_Style);
        if (borderEdge.GetBorderStyle() == BorderStyle::DOTTED) {
            SkPath dotPath;
            dotPath.addCircle(0.0f, 0.0f, SkDoubleToScalar(width / 2.0));
            paint.setPathEffect(SkPath1DPathEffect::Make(dotPath, width * 2.0, 0.0, SkPath1DPathEffect::kRotate_Style));
        } else if (borderEdge.GetBorderStyle() == BorderStyle::DASHED) {
            const float intervals[] = { SkDoubleToScalar(width * DASHED_LINE_LENGTH),
                SkDoubleToScalar(width * DASHED_LINE_LENGTH) };
            paint.setPathEffect(SkDashPathEffect::Make(intervals, SK_ARRAY_COUNT(intervals), 0.0));
        } else {
            paint.setPathEffect(nullptr);
        }
    }
}

void FlutterDecorationPainter::PaintBorder(const Offset& offset, const Border& border, SkCanvas* canvas, SkPaint& paint)
{
    // paint left border edge.
    BorderEdge left = border.Left();
    if (left.HasValue()) {
        SetBorderStyle(left, paint);
        canvas->drawLine(offset.GetX() + SK_ScalarHalf * NormalizeToPx(left.GetWidth()), offset.GetY(),
            offset.GetX() + SK_ScalarHalf * NormalizeToPx(left.GetWidth()), offset.GetY() + paintSize_.Height(), paint);
    }

    // paint top border edge.
    BorderEdge top = border.Top();
    if (top.HasValue()) {
        SetBorderStyle(top, paint);
        canvas->drawLine(offset.GetX(), offset.GetY() + SK_ScalarHalf * NormalizeToPx(top.GetWidth()),
            offset.GetX() + paintSize_.Width(), offset.GetY() + SK_ScalarHalf * NormalizeToPx(top.GetWidth()), paint);
    }

    // paint right border edge.
    BorderEdge right = border.Right();
    if (right.HasValue()) {
        SetBorderStyle(right, paint);
        canvas->drawLine(offset.GetX() + paintSize_.Width() - SK_ScalarHalf * NormalizeToPx(right.GetWidth()),
            offset.GetY(), offset.GetX() + paintSize_.Width() - SK_ScalarHalf * NormalizeToPx(right.GetWidth()),
            offset.GetY() + paintSize_.Height(), paint);
    }

    // paint bottom border edge.
    BorderEdge bottom = border.Bottom();
    if (bottom.HasValue()) {
        SetBorderStyle(bottom, paint);
        canvas->drawLine(offset.GetX(),
            offset.GetY() + paintSize_.Height() - SK_ScalarHalf * NormalizeToPx(bottom.GetWidth()),
            offset.GetX() + paintSize_.Width(),
            offset.GetY() + paintSize_.Height() - SK_ScalarHalf * NormalizeToPx(bottom.GetWidth()), paint);
    }
}

// Add for box-shadow, otherwise using PaintShadow().
void FlutterDecorationPainter::PaintBoxShadows(
    const SkRRect& rrect, const std::vector<Shadow>& shadows, SkCanvas* canvas)
{
    if (!canvas) {
        LOGE("PaintBoxShadows failed, canvas is null.");
        return;
    }
    canvas->save();
    // The location of the component itself does not draw a shadow
    canvas->clipRRect(rrect, SkClipOp::kDifference, true);

    if (!shadows.empty()) {
        for (const auto& shadow : shadows) {
            if (!shadow.IsValid()) {
                LOGW("The current shadow is not drawn if the shadow is invalid.");
                continue;
            }
            if (shadow.GetHardwareAcceleration()) {
                // Do not support blurRadius and spreadRadius to paint shadow, use elevation.
                PaintShadow(SkPath().addRRect(rrect), shadow, canvas);
            } else {
                SkRRect shadowRRect = rrect;
                // Keep the original rounded corners.
                SkVector fRadii[4] = {
                    rrect.radii(SkRRect::kUpperLeft_Corner),
                    rrect.radii(SkRRect::kUpperRight_Corner),
                    rrect.radii(SkRRect::kLowerRight_Corner),
                    rrect.radii(SkRRect::kLowerLeft_Corner)
                };

                SkScalar left = rrect.rect().left();
                SkScalar top = rrect.rect().top();
                auto width = rrect.width() + DOUBLE_WIDTH * shadow.GetSpreadRadius();
                auto height = rrect.height() + DOUBLE_WIDTH * shadow.GetSpreadRadius();
                SkRect skRect {};
                skRect.setXYWH(left + SkDoubleToScalar(shadow.GetOffset().GetX() - shadow.GetSpreadRadius()),
                    top + SkDoubleToScalar(shadow.GetOffset().GetY() - shadow.GetSpreadRadius()),
                    SkDoubleToScalar(width > 0.0 ? width : 0.0), SkDoubleToScalar(height > 0.0 ? height : 0.0));
                shadowRRect.setRectRadii(skRect, fRadii);
                SkPaint paint;
                paint.setColor(shadow.GetColor().GetValue());
                paint.setAntiAlias(true);
                paint.setMaskFilter(SkMaskFilter::MakeBlur(
                    SkBlurStyle::kNormal_SkBlurStyle, ConvertRadiusToSigma(shadow.GetBlurRadius())));
                canvas->drawRRect(shadowRRect, paint);
            }
        }
    }
    canvas->restore();
}

void FlutterDecorationPainter::PaintShadow(const SkPath& path, const Shadow& shadow, SkCanvas* canvas)
{
    if (!canvas) {
        LOGE("PaintShadow failed, canvas is null.");
        return;
    }
    if (!shadow.IsValid()) {
        LOGW("The current shadow is not drawn if the shadow is invalid.");
        return;
    }

    canvas->save();
    SkPath skPath = path;
    skPath.offset(shadow.GetOffset().GetX(), shadow.GetOffset().GetY());
    SkColor spotColor = shadow.GetColor().GetValue();
    if (shadow.GetHardwareAcceleration()) {
        // PlaneParams represents the coordinates of the component, and here we only need to focus on the elevation
        // of the component.
        SkPoint3 planeParams = { 0.0f, 0.0f, shadow.GetElevation() };

        // LightPos is the location of a spot light source, which is by default located directly above the center
        // of the component.
        SkPoint3 lightPos = { skPath.getBounds().centerX(), skPath.getBounds().centerY(), shadow.GetLightHeight() };

        // Current ambient color is not available.
        SkColor ambientColor = SkColorSetARGB(0, 0, 0, 0);
        SkShadowUtils::DrawShadow(canvas, skPath, planeParams, lightPos, shadow.GetLightRadius(), ambientColor,
            spotColor, SkShadowFlags::kTransparentOccluder_ShadowFlag);
    } else {
        SkPaint paint;
        paint.setColor(spotColor);
        paint.setAntiAlias(true);
        paint.setMaskFilter(SkMaskFilter::MakeBlur(kNormal_SkBlurStyle, ConvertRadiusToSigma(shadow.GetBlurRadius())));
        canvas->drawPath(skPath, paint);
    }
    canvas->restore();
}

void FlutterDecorationPainter::PaintImage(const Offset& offset, RenderContext& context)
{
    if (decoration_) {
        RefPtr<BackgroundImage> backgroundImage = decoration_->GetImage();
        if (backgroundImage && renderImage_) {
            renderImage_->RenderWithContext(context, offset);
        }
    }
}

void FlutterDecorationPainter::PaintGradient(const Offset& offset, SkCanvas* canvas, SkPaint& paint)
{
    // paint gradient.
    Gradient gradient = decoration_->GetGradient();
    if (NearZero(paintSize_.Width()) || NearZero(paintSize_.Height())) {
        return;
    }
    if (gradient.IsValid()) {
        if (gradient.GetRepeat()) {
            GetShaderForRepeat(offset, gradient, paint);
        } else {
            GetShaderForClamp(offset, gradient, paint);
        }
        canvas->drawRect(
            SkRect::MakeXYWH(offset.GetX() + margin_.LeftPx(), offset.GetY() + margin_.TopPx(),
                GetLayoutSize().Width() - margin_.RightPx(), GetLayoutSize().Height() - margin_.BottomPx()),
            paint);
        paint.reset();
    }
}

void FlutterDecorationPainter::GetShaderForRepeat(const Offset& offset, const Gradient& gradient, SkPaint& paint)
{
    std::vector<GradientColor> gradientColors = gradient.GetColors();
    const int32_t colorsSize = gradientColors.size();
    SkColor colors[colorsSize];
    int32_t maxPercentIndex = 0;
    float pos[colorsSize];
    for (int32_t i = 0; i < colorsSize; ++i) {
        const auto& gradientColor = gradientColors[i];
        colors[i] = gradientColor.GetColor().GetValue();
        if (!gradientColor.GetHasValue()) {
            if (i == 0) {
                pos[i] = SHADER_PERCENT_ZERO;
            } else if (i == colorsSize - 1) {
                pos[i] = SHADER_PERCENT_FULL;
                maxPercentIndex = i;
            } else {
                pos[i] = SHADER_PERCENT_NONE_EXIST;
            }
        } else {
            pos[i] = GetShaderPercent(gradientColor.GetDimension(), gradient);
            if (pos[i] < pos[maxPercentIndex]) {
                pos[i] = pos[maxPercentIndex];
            }
            if (pos[i] > pos[maxPercentIndex]) {
                maxPercentIndex = i;
            }
        }
    }
    SkPoint firstPoint = gradientColors.front().GetHasValue()
                             ? GetShaderStopPoint(offset, gradientColors.front().GetDimension(), gradient)
                             : GetGradientBeginPoint(offset, gradient);
    SkPoint lastPoint = gradientColors.back().GetHasValue()
                            ? GetShaderStopPoint(offset, gradientColors.at(maxPercentIndex).GetDimension(), gradient)
                            : GetGradientEndPoint(offset, gradient);
    float lastPercent = gradientColors.back().GetHasValue()
                            ? (GetShaderPercent(gradientColors.at(maxPercentIndex).GetDimension(), gradient) - pos[0])
                            : SHADER_PERCENT_FULL;
    if (NearZero(lastPercent)) {
        lastPercent = SHADER_PERCENT_FULL;
    }
    SkPoint pts[2] = { firstPoint, lastPoint };
    RecalculatePosition(pos, colorsSize);
    float firstPercent = pos[0];
    for (int32_t i = 0; i < colorsSize; ++i) {
        pos[i] = (pos[i] - firstPercent) / lastPercent;
    }
#ifdef USE_SYSTEM_SKIA
    paint.setShader(SkGradientShader::MakeLinear(pts, colors, pos, colorsSize, SkShader::kRepeat_TileMode));
#else
    paint.setShader(SkGradientShader::MakeLinear(pts, colors, pos, colorsSize, SkTileMode::kRepeat));
#endif
}

void FlutterDecorationPainter::GetShaderForClamp(const Offset& offset, const Gradient& gradient, SkPaint& paint) const
{
    SkPoint beginPoint = GetGradientBeginPoint(offset, gradient);
    SkPoint endPoint = GetGradientEndPoint(offset, gradient);
    SkPoint pts[2] = { beginPoint, endPoint };
    std::vector<GradientColor> gradientColors = gradient.GetColors();
    SkColor colors[gradientColors.size()];
    float pos[gradientColors.size()];
    int32_t colorsSize = gradientColors.size();
    int32_t maxPercentIndex = 0;
    for (auto i = 0; i < colorsSize; ++i) {
        const auto& gradientColor = gradientColors[i];
        colors[i] = gradientColor.GetColor().GetValue();
        if (gradientColor.GetHasValue()) {
            pos[i] = GetShaderPercent(gradientColor.GetDimension(), gradient);
            if (pos[i] < pos[maxPercentIndex]) {
                pos[i] = pos[maxPercentIndex];
            }
            if (pos[i] > pos[maxPercentIndex]) {
                maxPercentIndex = i;
            }
        } else {
            if (i == 0) {
                pos[i] = SHADER_PERCENT_ZERO;
            } else {
                pos[i] = SHADER_PERCENT_NONE_EXIST;
            }
        }
    }
    RecalculatePosition(pos, colorsSize);

#ifdef USE_SYSTEM_SKIA
    paint.setShader(SkGradientShader::MakeLinear(pts, colors, pos, gradientColors.size(), SkShader::kClamp_TileMode));
#else
    paint.setShader(SkGradientShader::MakeLinear(pts, colors, pos, gradientColors.size(), SkTileMode::kClamp));
#endif
}

float FlutterDecorationPainter::GetShaderPercent(const Dimension& dimension, const Gradient& gradient) const
{
    float percent = 0.0f;
    if (gradient.GetUseAngle()) {
        double angle = std::fmod(gradient.GetAngle(), DEGREES_360);
        if (angle < 0.0) {
            angle = DEGREES_360 - std::abs(angle);
        }
        percent = SkDoubleToScalar(GetShaderPercentByAngle(dimension, angle));
    } else {
        percent = SkDoubleToScalar(GetShaderPercentByDirection(dimension, gradient));
    }
    if (percent < SHADER_PERCENT_ZERO) {
        percent = SHADER_PERCENT_ZERO;
    }
    if (percent > SHADER_PERCENT_FULL) {
        percent = SHADER_PERCENT_FULL;
    }
    return percent;
}

double FlutterDecorationPainter::GetShaderPercentByDirection(const Dimension& dimension, const Gradient& gradient) const
{
    double stopPoint = 0.0;
    switch (gradient.GetDirection()) {
        case GradientDirection::LEFT:
        case GradientDirection::RIGHT:
            stopPoint = GetShaderPercentEq90Degrees(dimension);
            break;
        case GradientDirection::TOP:
        case GradientDirection::BOTTOM:
            stopPoint = GetShaderPercentEq0Degrees(dimension);
            break;
        case GradientDirection::LEFT_TOP:
        case GradientDirection::RIGHT_TOP:
        case GradientDirection::RIGHT_BOTTOM:
        case GradientDirection::LEFT_BOTTOM: {
            if (dimension.Unit() == DimensionUnit::PX || dimension.Unit() == DimensionUnit::VP) {
                double hypotenuse = GetRectHypotenuse();
                if (!NearZero(hypotenuse)) {
                    stopPoint = NormalizeToPx(dimension) / hypotenuse;
                }
            } else {
                stopPoint = dimension.Value() / PERCENT_TRANSLATE;
            }
            break;
        }
        default:
            break;
    }
    return stopPoint;
}

SkPoint FlutterDecorationPainter::GetShaderStopPoint(
    const Offset& offset, const Dimension& dimension, const Gradient& gradient) const
{
    SkPoint skPoint;
    if (gradient.GetUseAngle()) {
        double angle = std::fmod(gradient.GetAngle(), DEGREES_360);
        if (angle < 0.0) {
            angle = DEGREES_360 - std::abs(angle);
        }
        skPoint = GetShaderStopPointByAngle(offset, dimension, angle);
    } else {
        skPoint = GetShaderStopPointByDirection(offset, dimension, gradient);
    }
    return skPoint;
}

double FlutterDecorationPainter::GetShaderPercentByAngle(const Dimension& dimension, double angle) const
{
    double percent = 0.0;
    if (NearZero(angle)) {
        percent = GetShaderPercentEq0Degrees(dimension);
    } else if (angle < DEGREES_90) {
        double diagonalAngle = GetDiagonalAngle(angle);
        percent = GetShaderPercentForAngle(dimension, angle, diagonalAngle);
    } else if (NearZero(angle - DEGREES_90)) {
        percent = GetShaderPercentEq90Degrees(dimension);
    } else if (angle < DEGREES_180) {
        double diagonalAngle = GetDiagonalAngle(angle);
        percent = GetShaderPercentForAngle(dimension, angle - DEGREES_90, diagonalAngle);
    } else if (NearZero(angle - DEGREES_180)) {
        percent = GetShaderPercentEq0Degrees(dimension);
    } else if (angle < DEGREES_270) {
        double diagonalAngle = GetDiagonalAngle(angle);
        percent = GetShaderPercentForAngle(dimension, angle - DEGREES_180, diagonalAngle);
    } else if (NearZero(angle - DEGREES_270)) {
        percent = GetShaderPercentEq90Degrees(dimension);
    } else {
        double diagonalAngle = GetDiagonalAngle(angle);
        percent = GetShaderPercentForAngle(dimension, angle - DEGREES_270, diagonalAngle);
    }
    return percent;
}

SkPoint FlutterDecorationPainter::GetShaderStopPointByDirection(
    const Offset& offset, const Dimension& dimension, const Gradient& gradient) const
{
    SkPoint skPoint;
    switch (gradient.GetDirection()) {
        case GradientDirection::LEFT:
            skPoint = GetShaderStopPointEq270Degrees(offset, dimension);
            break;
        case GradientDirection::LEFT_TOP:
            skPoint = GetShaderStopPointLeftTop(offset, dimension);
            break;
        case GradientDirection::TOP:
            skPoint = GetShaderStopPointEq0Degrees(offset, dimension);
            break;
        case GradientDirection::RIGHT_TOP:
            skPoint = GetShaderStopPointRightTop(offset, dimension);
            break;
        case GradientDirection::RIGHT:
            skPoint = GetShaderStopPointEq90Degrees(offset, dimension);
            break;
        case GradientDirection::RIGHT_BOTTOM:
            skPoint = GetShaderStopPointRightBottom(offset, dimension);
            break;
        case GradientDirection::BOTTOM:
            skPoint = GetShaderStopPointEq180Degrees(offset, dimension);
            break;
        case GradientDirection::LEFT_BOTTOM:
            skPoint = GetShaderStopPointLeftBottom(offset, dimension);
            break;
        default:
            skPoint = GetShaderStopPointEq0Degrees(offset, dimension);
            LOGE("default gradient direction");
            break;
    }
    return skPoint;
}

SkPoint FlutterDecorationPainter::GetShaderStopPointByAngle(
    const Offset& offset, const Dimension& dimension, double angle) const
{
    SkPoint skPoint;
    if (NearZero(angle)) {
        skPoint = GetShaderStopPointEq0Degrees(offset, dimension);
    } else if (angle < DEGREES_90) {
        double diagonalAngle = GetDiagonalAngle(angle);
        skPoint = GetShaderStopPointLT90Degrees(offset, dimension, angle, diagonalAngle);
    } else if (NearZero(angle - DEGREES_90)) {
        skPoint = GetShaderStopPointEq90Degrees(offset, dimension);
    } else if (angle < DEGREES_180) {
        double diagonalAngle = GetDiagonalAngle(angle);
        skPoint = GetShaderStopPointLT180Degrees(offset, dimension, angle - DEGREES_90, diagonalAngle);
    } else if (NearZero(angle - DEGREES_180)) {
        skPoint = GetShaderStopPointEq180Degrees(offset, dimension);
    } else if (angle < DEGREES_270) {
        double diagonalAngle = GetDiagonalAngle(angle);
        skPoint = GetShaderStopPointLT270Degrees(offset, dimension, angle - DEGREES_180, diagonalAngle);
    } else if (NearZero(angle - DEGREES_270)) {
        skPoint = GetShaderStopPointEq270Degrees(offset, dimension);
    } else {
        double diagonalAngle = GetDiagonalAngle(angle);
        skPoint = GetShaderStopPointLT360Degrees(offset, dimension, angle - DEGREES_270, diagonalAngle);
    }
    return skPoint;
}

SkPoint FlutterDecorationPainter::GetShaderStopPointLeftTop(const Offset& offset, const Dimension& dimension) const
{
    if (dimension.Unit() == DimensionUnit::PX || dimension.Unit() == DimensionUnit::VP) {
        double hypotenuse = GetRectHypotenuse();
        double length = std::min(NormalizeToPx(dimension), hypotenuse);
        if (NearZero(hypotenuse)) {
            return SkPoint::Make(GetRightOffset(offset), GetBottomOffset(offset));
        } else {
            return SkPoint::Make(GetRightOffset(offset) - dimension.Value() * paintSize_.Width() / hypotenuse,
                GetBottomOffset(offset) - length * paintSize_.Height() / hypotenuse);
        }
    } else {
        double percent = std::min(dimension.Value(), PERCENT_TRANSLATE);
        return SkPoint::Make(GetRightOffset(offset) - dimension.Value() * paintSize_.Width() / PERCENT_TRANSLATE,
            GetBottomOffset(offset) - percent * paintSize_.Height() / PERCENT_TRANSLATE);
    }
}

SkPoint FlutterDecorationPainter::GetShaderStopPointLeftBottom(const Offset& offset, const Dimension& dimension) const
{
    if (dimension.Unit() == DimensionUnit::PX || dimension.Unit() == DimensionUnit::VP) {
        double hypotenuse = GetRectHypotenuse();
        double length = std::min(NormalizeToPx(dimension), hypotenuse);
        if (NearZero(hypotenuse)) {
            return SkPoint::Make(GetRightOffset(offset), GetTopOffset(offset));
        } else {
            return SkPoint::Make(GetRightOffset(offset) - dimension.Value() * paintSize_.Width() / hypotenuse,
                GetTopOffset(offset) + length * paintSize_.Height() / hypotenuse);
        }
    } else {
        double percent = std::min(dimension.Value(), PERCENT_TRANSLATE);
        return SkPoint::Make(GetRightOffset(offset) - dimension.Value() * paintSize_.Width() / PERCENT_TRANSLATE,
            GetTopOffset(offset) + percent * paintSize_.Height() / PERCENT_TRANSLATE);
    }
}

SkPoint FlutterDecorationPainter::GetShaderStopPointRightTop(const Offset& offset, const Dimension& dimension) const
{
    if (dimension.Unit() == DimensionUnit::PX || dimension.Unit() == DimensionUnit::VP) {
        double hypotenuse = GetRectHypotenuse();
        double length = std::min(NormalizeToPx(dimension), hypotenuse);
        if (NearZero(hypotenuse)) {
            return SkPoint::Make(GetLeftOffset(offset), GetBottomOffset(offset));
        } else {
            return SkPoint::Make(GetLeftOffset(offset) + length * paintSize_.Width() / hypotenuse,
                GetBottomOffset(offset) - dimension.Value() * paintSize_.Height() / hypotenuse);
        }
    } else {
        double percent = std::min(dimension.Value(), PERCENT_TRANSLATE);
        return SkPoint::Make(GetLeftOffset(offset) + dimension.Value() * paintSize_.Width() / PERCENT_TRANSLATE,
            GetBottomOffset(offset) - percent * paintSize_.Height() / PERCENT_TRANSLATE);
    }
}

SkPoint FlutterDecorationPainter::GetShaderStopPointRightBottom(const Offset& offset, const Dimension& dimension) const
{
    if (dimension.Unit() == DimensionUnit::PX || dimension.Unit() == DimensionUnit::VP) {
        double hypotenuse = GetRectHypotenuse();
        double length = std::min(NormalizeToPx(dimension), hypotenuse);
        if (NearZero(hypotenuse)) {
            return SkPoint::Make(GetLeftOffset(offset), GetTopOffset(offset));
        } else {
            return SkPoint::Make(GetLeftOffset(offset) + dimension.Value() * paintSize_.Width() / hypotenuse,
                GetTopOffset(offset) + length * paintSize_.Height() / hypotenuse);
        }
    } else {
        double percent = std::min(dimension.Value(), PERCENT_TRANSLATE);
        return SkPoint::Make(GetLeftOffset(offset) + dimension.Value() * paintSize_.Width() / PERCENT_TRANSLATE,
            GetTopOffset(offset) + percent * paintSize_.Height() / PERCENT_TRANSLATE);
    }
}

double FlutterDecorationPainter::GetShaderPercentEq0Degrees(const Dimension& dimension) const
{
    if (dimension.Unit() == DimensionUnit::PX || dimension.Unit() == DimensionUnit::VP) {
        return NormalizeToPx(dimension) / paintSize_.Height();
    } else {
        return dimension.Value() / PERCENT_TRANSLATE;
    }
}

double FlutterDecorationPainter::GetShaderPercentEq90Degrees(const Dimension& dimension) const
{
    if (dimension.Unit() == DimensionUnit::PX || dimension.Unit() == DimensionUnit::VP) {
        return NormalizeToPx(dimension) / paintSize_.Width();
    } else {
        return dimension.Value() / PERCENT_TRANSLATE;
    }
}

SkPoint FlutterDecorationPainter::GetShaderStopPointEq0Degrees(const Offset& offset, const Dimension& dimension) const
{
    if (dimension.Unit() == DimensionUnit::PX || dimension.Unit() == DimensionUnit::VP) {
        double length = std::min(NormalizeToPx(dimension), paintSize_.Height());
        return SkPoint::Make(GetLeftOffset(offset), GetBottomOffset(offset) - length);
    } else {
        double percent = std::min(dimension.Value(), PERCENT_TRANSLATE);
        return SkPoint::Make(
            GetLeftOffset(offset), GetBottomOffset(offset) - percent * paintSize_.Height() / PERCENT_TRANSLATE);
    }
}

SkPoint FlutterDecorationPainter::GetShaderStopPointEq90Degrees(const Offset& offset, const Dimension& dimension) const
{
    if (dimension.Unit() == DimensionUnit::PX || dimension.Unit() == DimensionUnit::VP) {
        double length = std::min(NormalizeToPx(dimension), paintSize_.Width());
        return SkPoint::Make(GetLeftOffset(offset) + length, GetTopOffset(offset));
    } else {
        double percent = std::min(dimension.Value(), PERCENT_TRANSLATE);
        return SkPoint::Make(
            GetLeftOffset(offset) + percent * paintSize_.Width() / PERCENT_TRANSLATE, GetTopOffset(offset));
    }
}

SkPoint FlutterDecorationPainter::GetShaderStopPointEq180Degrees(const Offset& offset, const Dimension& dimension) const
{
    if (dimension.Unit() == DimensionUnit::PX || dimension.Unit() == DimensionUnit::VP) {
        double length = std::min(NormalizeToPx(dimension), paintSize_.Height());
        return SkPoint::Make(GetLeftOffset(offset), GetTopOffset(offset) + length);
    } else {
        double percent = std::min(dimension.Value(), PERCENT_TRANSLATE);
        return SkPoint::Make(
            GetLeftOffset(offset), GetTopOffset(offset) + percent * paintSize_.Height() / PERCENT_TRANSLATE);
    }
}

SkPoint FlutterDecorationPainter::GetShaderStopPointEq270Degrees(const Offset& offset, const Dimension& dimension) const
{
    if (dimension.Unit() == DimensionUnit::PX || dimension.Unit() == DimensionUnit::VP) {
        double length = std::min(NormalizeToPx(dimension), paintSize_.Width());
        return SkPoint::Make(GetRightOffset(offset) - length, GetTopOffset(offset));
    } else {
        double percent = std::min(dimension.Value(), PERCENT_TRANSLATE);
        return SkPoint::Make(
            GetRightOffset(offset) - percent * paintSize_.Width() / PERCENT_TRANSLATE, GetTopOffset(offset));
    }
}

SkPoint FlutterDecorationPainter::GetShaderStopPointLT90Degrees(
    const Offset& offset, const Dimension& dimension, double angle, double diagonalAngle) const
{
    double hypotenuse = GetHypotenuse(dimension, angle, diagonalAngle);
    return SkPoint::Make(GetLeftOffset(offset) + hypotenuse * std::sin(SkDegreesToRadians(angle)),
        GetBottomOffset(offset) - hypotenuse * std::sin(SkDegreesToRadians(DEGREES_90 - angle)));
}

SkPoint FlutterDecorationPainter::GetShaderStopPointLT180Degrees(
    const Offset& offset, const Dimension& dimension, double angle, double diagonalAngle) const
{
    double hypotenuse = GetHypotenuse(dimension, angle, diagonalAngle);
    return SkPoint::Make(GetLeftOffset(offset) + hypotenuse * std::sin(SkDegreesToRadians(DEGREES_90 - angle)),
        GetTopOffset(offset) + hypotenuse * std::sin(SkDegreesToRadians(angle)));
}

SkPoint FlutterDecorationPainter::GetShaderStopPointLT270Degrees(
    const Offset& offset, const Dimension& dimension, double angle, double diagonalAngle) const
{
    double hypotenuse = GetHypotenuse(dimension, angle, diagonalAngle);
    return SkPoint::Make(GetRightOffset(offset) - hypotenuse * std::sin(SkDegreesToRadians(angle)),
        GetTopOffset(offset) + hypotenuse * std::sin(SkDegreesToRadians(DEGREES_90 - angle)));
}

SkPoint FlutterDecorationPainter::GetShaderStopPointLT360Degrees(
    const Offset& offset, const Dimension& dimension, double angle, double diagonalAngle) const
{
    double hypotenuse = GetHypotenuse(dimension, angle, diagonalAngle);
    return SkPoint::Make(GetRightOffset(offset) - hypotenuse * std::sin(SkDegreesToRadians(DEGREES_90 - angle)),
        GetBottomOffset(offset) - hypotenuse * std::sin(SkDegreesToRadians(angle)));
}

double FlutterDecorationPainter::GetHypotenuse(const Dimension& dimension, double angle, double diagonalAngle) const
{
    if (dimension.Unit() == DimensionUnit::PX || dimension.Unit() == DimensionUnit::VP) {
        return std::min(NormalizeToPx(dimension), GetRectHypotenuse());
    } else {
        double percent = std::min(dimension.Value(), PERCENT_TRANSLATE);
        double hypotenuseAngle = GetHypotenuseAngle(angle, diagonalAngle);
        return sin(SkDegreesToRadians(hypotenuseAngle)) * percent *
               std::sqrt(paintSize_.Width() * paintSize_.Width() + paintSize_.Height() * paintSize_.Height()) /
               PERCENT_TRANSLATE;
    }
}

double FlutterDecorationPainter::GetDiagonalAngle(double angle) const
{
    double diagonalAngle;
    if (angle < DEGREES_90) {
        diagonalAngle = SkRadiansToDegrees(std::atan(paintSize_.Height() / paintSize_.Width()));
    } else if (angle < DEGREES_180) {
        diagonalAngle = SkRadiansToDegrees(std::atan(paintSize_.Width() / paintSize_.Height()));
    } else if (angle < DEGREES_270) {
        diagonalAngle = SkRadiansToDegrees(std::atan(paintSize_.Height() / paintSize_.Width()));
    } else {
        diagonalAngle = SkRadiansToDegrees(std::atan(paintSize_.Width() / paintSize_.Height()));
    }
    return diagonalAngle;
}

double FlutterDecorationPainter::GetHypotenuseAngle(double angle, double diagonalAngle) const
{
    double hypotenuseAngle;
    if (angle < (DEGREES_90 - diagonalAngle)) {
        hypotenuseAngle = diagonalAngle + angle;
    } else if (angle > (DEGREES_90 - diagonalAngle)) {
        hypotenuseAngle = DEGREES_180 - diagonalAngle - angle;
    } else {
        hypotenuseAngle = DEGREES_90;
    }
    return hypotenuseAngle;
}

double FlutterDecorationPainter::GetShaderPercentForAngle(
    const Dimension& dimension, double angle, double diagonalAngle) const
{
    if (dimension.IsValid()) {
        if (dimension.Unit() == DimensionUnit::PX || dimension.Unit() == DimensionUnit::VP) {
            double hypotenuseAngle = GetHypotenuseAngle(angle, diagonalAngle);
            double hypotenuse = GetRectHypotenuse();
            double sinValue = sin(SkDegreesToRadians(hypotenuseAngle));
            if (NearZero(sinValue) || NearZero(hypotenuse)) {
                return SHADER_PERCENT_ZERO;
            }
            return NormalizeToPx(dimension) / sinValue / hypotenuse;
        } else {
            return SkDoubleToScalar(dimension.Value() / PERCENT_TRANSLATE);
        }
    } else {
        return SHADER_PERCENT_ZERO;
    }
}

SkPoint FlutterDecorationPainter::GetGradientBeginPoint(const Offset& offset, const Gradient& gradient) const
{
    SkPoint skPoint;
    if (gradient.GetUseAngle()) {
        double angle = std::fmod(gradient.GetAngle(), DEGREES_360);
        if (angle < 0.0) {
            angle = DEGREES_360 - std::abs(angle);
        }
        skPoint = GetBeginPointByAngle(offset, angle);
    } else {
        skPoint = GetBeginPointByDirection(offset, gradient);
    }
    return skPoint;
}

SkPoint FlutterDecorationPainter::GetBeginPointByAngle(const Offset& offset, double angle) const
{
    SkPoint skPoint;
    if (NearZero(angle)) {
        skPoint = SkPoint::Make(GetLeftOffset(offset), GetBottomOffset(offset));
    } else if (angle < DEGREES_90) {
        skPoint = SkPoint::Make(GetLeftOffset(offset), GetBottomOffset(offset));
    } else if (NearZero(angle - DEGREES_90)) {
        skPoint = SkPoint::Make(GetLeftOffset(offset), GetTopOffset(offset));
    } else if (angle < DEGREES_180) {
        skPoint = SkPoint::Make(GetLeftOffset(offset), GetTopOffset(offset));
    } else if (NearZero(angle - DEGREES_180)) {
        skPoint = SkPoint::Make(GetLeftOffset(offset), GetTopOffset(offset));
    } else if (angle < DEGREES_270) {
        skPoint = SkPoint::Make(GetRightOffset(offset), GetTopOffset(offset));
    } else if (NearZero(angle - DEGREES_270)) {
        skPoint = SkPoint::Make(GetRightOffset(offset), GetTopOffset(offset));
    } else if (angle < DEGREES_360) {
        skPoint = SkPoint::Make(GetRightOffset(offset), GetBottomOffset(offset));
    } else {
        skPoint = SkPoint::Make(GetLeftOffset(offset), GetBottomOffset(offset));
    }
    return skPoint;
}

SkPoint FlutterDecorationPainter::GetBeginPointByDirection(const Offset& offset, const Gradient& gradient) const
{
    double beginX = 0.0;
    double beginY = 0.0;
    switch (gradient.GetDirection()) {
        case GradientDirection::LEFT:
            beginX = GetRightOffset(offset);
            beginY = GetTopOffset(offset);
            break;
        case GradientDirection::LEFT_TOP:
            beginX = GetRightOffset(offset);
            beginY = GetBottomOffset(offset);
            break;
        case GradientDirection::TOP:
        case GradientDirection::RIGHT_TOP:
            beginX = GetLeftOffset(offset);
            beginY = GetBottomOffset(offset);
            break;
        case GradientDirection::RIGHT:
            beginX = GetLeftOffset(offset);
            beginY = GetTopOffset(offset);
            break;
        case GradientDirection::RIGHT_BOTTOM:
        case GradientDirection::BOTTOM:
            beginX = GetLeftOffset(offset);
            beginY = GetTopOffset(offset);
            break;
        case GradientDirection::LEFT_BOTTOM:
            beginX = GetRightOffset(offset);
            beginY = GetTopOffset(offset);
            break;
        default:
            break;
    }
    return SkPoint::Make(SkDoubleToScalar(beginX), SkDoubleToScalar(beginY));
}

SkPoint FlutterDecorationPainter::GetGradientEndPoint(const Offset& offset, const Gradient& gradient) const
{
    Dimension endDimension = Dimension(PERCENT_TRANSLATE, DimensionUnit::PERCENT);
    return GetShaderStopPoint(offset, endDimension, gradient);
}

void FlutterDecorationPainter::RecalculatePosition(float pos[], int32_t colorsSize) const
{
    float preview = SHADER_PERCENT_ZERO;
    int32_t num = 0;
    for (int32_t i = 0; i < colorsSize; ++i) {
        if (pos[i] == SHADER_PERCENT_NONE_EXIST) {
            if (i == 0) {
                pos[i] = SHADER_PERCENT_ZERO;
            } else if (i == colorsSize - 1) {
                pos[i] = SHADER_PERCENT_FULL;
            } else {
                if (num == 0) {
                    preview = pos[i - 1];
                }
                num++;
            }
        }
        if (pos[i] != SHADER_PERCENT_NONE_EXIST && num > 0) {
            float avgPercent = (pos[i] - preview) / SkIntToFloat(num + 1);
            for (int32_t j = i - num; j < i; ++j) {
                pos[j] = pos[j - 1] + avgPercent;
            }
            preview = SHADER_PERCENT_ZERO;
            num = 0;
        }
    }
}

double FlutterDecorationPainter::GetRectHypotenuse() const
{
    return std::sqrt(paintSize_.Width() * paintSize_.Width() + paintSize_.Height() * paintSize_.Height());
}

float FlutterDecorationPainter::ConvertRadiusToSigma(float radius)
{
    return radius > 0.0f ? BLUR_SIGMA_SCALE * radius + SK_ScalarHalf : 0.0f;
}

bool FlutterDecorationPainter::CheckBorderAllEqual(const Border& border)
{
    if (CheckBorderEdgeForRRect(border)) {
        Color leftColor = border.Left().GetColor();
        return leftColor == border.Top().GetColor() && leftColor == border.Right().GetColor() &&
               leftColor == border.Bottom().GetColor();
    }
    return false;
}

bool FlutterDecorationPainter::CheckBorderEdgeForRRect(const Border& border)
{
    double leftWidth = NormalizeToPx(border.Left().GetWidth());
    if (NearEqual(leftWidth, NormalizeToPx(border.Top().GetWidth())) &&
        NearEqual(leftWidth, NormalizeToPx(border.Right().GetWidth())) &&
        NearEqual(leftWidth, NormalizeToPx(border.Bottom().GetWidth()))) {
        BorderStyle leftStyle = border.Left().GetBorderStyle();
        return leftStyle == border.Top().GetBorderStyle() && leftStyle == border.Right().GetBorderStyle() &&
               leftStyle == border.Bottom().GetBorderStyle();
    }
    return false;
}

double FlutterDecorationPainter::GetLeftOffset(const Offset& offset) const
{
    return offset.GetX() + margin_.LeftPx();
}

double FlutterDecorationPainter::GetRightOffset(const Offset& offset) const
{
    return offset.GetX() + GetLayoutSize().Width() - margin_.RightPx();
}

double FlutterDecorationPainter::GetTopOffset(const Offset& offset) const
{
    return offset.GetY() + margin_.TopPx();
}

double FlutterDecorationPainter::GetBottomOffset(const Offset& offset) const
{
    return offset.GetY() + GetLayoutSize().Height() - margin_.BottomPx();
}

double FlutterDecorationPainter::NormalizeToPx(const Dimension& dimension) const
{
    if ((dimension.Unit() == DimensionUnit::VP) || (dimension.Unit() == DimensionUnit::FP)) {
        return (dimension.Value() * dipScale_);
    }
    return dimension.Value();
}

} // namespace OHOS::Ace