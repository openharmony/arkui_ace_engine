/*
 * Copyright (c) 2022-2024 Huawei Device Co., Ltd.
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

#include "core/components_ng/svg/parse/svg_graphic.h"

#include "include/core/SkScalar.h"
#include "include/effects/SkDashPathEffect.h"
#include "include/effects/SkGradientShader.h"

#include "base/utils/utils.h"
#include "core/components/declaration/svg/svg_declaration.h"

namespace OHOS::Ace::NG {
void SvgGraphic::OnDraw(RSCanvas& canvas, const Size& layout, const std::optional<Color>& color)
{
#ifndef USE_ROSEN_DRAWING
    fillPaint_.reset();
    strokePaint_.reset();
#else
    fillBrush_.Reset();
    strokePen_.Reset();
#endif
    path_ = AsPath(layout); // asPath override by graphic tag
    UpdateFillGradient(layout);
    if (UpdateFillStyle(color)) {
        OnGraphicFill();
    }
    UpdateStrokeGradient(layout);
    if (UpdateStrokeStyle()) {
        OnGraphicStroke();
    }
    if (!fillState_.GetHref().empty()) {
        auto svgContext = svgContext_.Upgrade();
        auto refSvgNode = svgContext->GetSvgNodeById(fillState_.GetHref());
        CHECK_NULL_VOID(refSvgNode);
        refSvgNode->Draw(canvas, layout, color);
    }
}

void SvgGraphic::SetLinearGradient(const Size& viewPort, Gradient& gradient)
{
    auto bounds = AsBounds(viewPort);
    auto width = bounds.Width();
    auto height = bounds.Height();

    const auto& linearGradient = gradient.GetLinearGradient();
    auto gradientInfo = LinearGradientInfo();

    gradientInfo.x1 = linearGradient.x1 ? ConvertDimensionToPx(linearGradient.x1.value(), width) : 0.0;
    if (linearGradient.x1 && linearGradient.x1.value().Unit() == DimensionUnit::PERCENT) {
        gradientInfo.x1 += bounds.Left();
    }
    gradientInfo.y1 = linearGradient.y1 ? ConvertDimensionToPx(linearGradient.y1.value(), height) : 0.0;
    if (linearGradient.y1 && linearGradient.y1.value().Unit() == DimensionUnit::PERCENT) {
        gradientInfo.y1 += bounds.Top();
    }
    gradientInfo.x2 = ConvertDimensionToPx((linearGradient.x2 ? linearGradient.x2.value() : 1.0_pct), width);
    if (linearGradient.x2 && linearGradient.x2.value().Unit() == DimensionUnit::PERCENT) {
        gradientInfo.x2 += bounds.Left();
    }
    gradientInfo.y2 = linearGradient.y2 ? ConvertDimensionToPx(linearGradient.y2.value(), height) : 0.0;
    if (linearGradient.y2 && linearGradient.y2.value().Unit() == DimensionUnit::PERCENT) {
        gradientInfo.y2 += bounds.Top();
    }

    gradient.SetLinearGradientInfo(gradientInfo);
}

void SvgGraphic::SetRadialGradient(const Size& viewPort, Gradient& gradient)
{
    auto bounds = AsBounds(viewPort);
    auto width = bounds.Width();
    auto height = bounds.Height();

    const auto& radialGradient = gradient.GetRadialGradient();
    auto gradientInfo = RadialGradientInfo();

    gradientInfo.r = ConvertDimensionToPx(radialGradient.radialHorizontalSize ?
        Dimension(radialGradient.radialHorizontalSize.value().Value(),
        radialGradient.radialHorizontalSize.value().Unit()) : 0.5_pct, sqrt(width * height));
    gradientInfo.cx = ConvertDimensionToPx(radialGradient.radialCenterX ?
        Dimension(radialGradient.radialCenterX.value().Value(),
        radialGradient.radialCenterX.value().Unit()) : 0.5_pct, width) + bounds.Left();
    gradientInfo.cy = ConvertDimensionToPx(radialGradient.radialCenterY ?
        Dimension(radialGradient.radialCenterY.value().Value(),
        radialGradient.radialCenterY.value().Unit()) : 0.5_pct, height) + bounds.Top();
    if (radialGradient.fRadialCenterX && radialGradient.fRadialCenterX->IsValid()) {
        gradientInfo.fx = ConvertDimensionToPx(radialGradient.fRadialCenterX.value(), width) + bounds.Left();
    } else {
        gradientInfo.fx = gradientInfo.cx;
    }
    if (radialGradient.fRadialCenterY && radialGradient.fRadialCenterY->IsValid()) {
        gradientInfo.fy = ConvertDimensionToPx(radialGradient.fRadialCenterY.value(), height) + bounds.Top();
    } else {
        gradientInfo.fy = gradientInfo.cy;
    }
    gradient.SetRadialGradientInfo(gradientInfo);
}

void SvgGraphic::UpdateFillGradient(const Size& viewPort)
{
    fillState_ = attributes_.fillState;
    auto& gradient = fillState_.GetGradient();
    CHECK_NULL_VOID(gradient);
    if (gradient->GetType() == GradientType::LINEAR) {
        SetLinearGradient(viewPort, gradient.value());
    } else if (gradient->GetType() == GradientType::RADIAL) {
        SetRadialGradient(viewPort, gradient.value());
    }
}

void SvgGraphic::UpdateStrokeGradient(const Size& viewPort)
{
    auto& gradient = attributes_.strokeState.GetGradient();
    CHECK_NULL_VOID(gradient);
    if (gradient->GetType() == GradientType::LINEAR) {
        SetLinearGradient(viewPort, gradient.value());
    } else if (gradient->GetType() == GradientType::RADIAL) {
        SetRadialGradient(viewPort, gradient.value());
    }
}

bool SvgGraphic::UpdateFillStyle(const std::optional<Color>& color, bool antiAlias)
{
    if (!color && fillState_.GetColor() == Color::TRANSPARENT && !fillState_.GetGradient()) {
        return false;
    }
    double curOpacity = fillState_.GetOpacity().GetValue() * opacity_ * (1.0f / UINT8_MAX);
#ifndef USE_ROSEN_DRAWING
    fillPaint_.setStyle(SkPaint::Style::kFill_Style);
    fillPaint_.setAntiAlias(antiAlias);
#else
    fillBrush_.SetAntiAlias(antiAlias);
#endif
    if (fillState_.GetGradient()) {
        return SetGradientStyle(curOpacity);
    } else {
        auto fillColor = (color) ? *color : fillState_.GetColor();
#ifndef USE_ROSEN_DRAWING
        fillPaint_.setColor(fillColor.BlendOpacity(curOpacity).GetValue());
#else
        fillBrush_.SetColor(fillColor.BlendOpacity(curOpacity).GetValue());
#endif
    }
    return true;
}

bool SvgGraphic::SetGradientStyle(double opacity)
{
    auto gradient = fillState_.GetGradient();
    CHECK_NULL_RETURN(gradient, false);
    auto gradientColors = gradient->GetColors();
    if (gradientColors.empty()) {
        return false;
    }
#ifdef USE_ROSEN_DRAWING
    std::vector<RSScalar> pos;
    std::vector<RSColorQuad> colors;
    for (const auto& gradientColor : gradientColors) {
        pos.push_back(static_cast<RSScalar>(gradientColor.GetDimension().Value()));
        colors.push_back(
            gradientColor.GetColor().BlendOpacity(gradientColor.GetOpacity()).BlendOpacity(opacity).GetValue());
    }
    if (gradient->GetType() == GradientType::LINEAR) {
        auto info = gradient->GetLinearGradientInfo();
        std::array<RSPoint, 2> pts = { RSPoint(static_cast<RSScalar>(info.x1), static_cast<RSScalar>(info.y1)),
            RSPoint(static_cast<RSScalar>(info.x2), static_cast<RSScalar>(info.y2)) };
        fillBrush_.SetShaderEffect(RSRecordingShaderEffect::CreateLinearGradient(
            pts[0], pts[1], colors, pos, static_cast<RSTileMode>(gradient->GetSpreadMethod())));
    }
    if (gradient->GetType() == GradientType::RADIAL) {
        auto info = gradient->GetRadialGradientInfo();
        auto center = RSPoint(static_cast<RSScalar>(info.cx), static_cast<RSScalar>(info.cy));
        auto focal = RSPoint(static_cast<RSScalar>(info.fx), static_cast<RSScalar>(info.fx));
        if (center == focal) {
            fillBrush_.SetShaderEffect(RSRecordingShaderEffect::CreateRadialGradient(center,
                static_cast<RSScalar>(info.r), colors, pos, static_cast<RSTileMode>(gradient->GetSpreadMethod())));
        } else {
            RSMatrix matrix;
            fillBrush_.SetShaderEffect(RSRecordingShaderEffect::CreateTwoPointConical(focal, 0, center,
                static_cast<RSScalar>(info.r), colors, pos, static_cast<RSTileMode>(gradient->GetSpreadMethod()),
                &matrix));
        }
    }
#endif
    return true;
}

void SvgGraphic::SetStrokeGradientStyle(double opacity)
{
    const auto& strokeState = attributes_.strokeState;
    auto gradient = strokeState.GetGradient();
    CHECK_NULL_VOID(gradient);
    auto gradientColors = gradient->GetColors();
    if (gradientColors.empty()) {
        return;
    }
#ifdef USE_ROSEN_DRAWING
    std::vector<RSScalar> pos;
    std::vector<RSColorQuad> colors;
    for (const auto& gradientColor : gradientColors) {
        pos.push_back(static_cast<RSScalar>(gradientColor.GetDimension().Value()));
        colors.push_back(
            gradientColor.GetColor().BlendOpacity(gradientColor.GetOpacity()).BlendOpacity(opacity).GetValue());
    }
    if (gradient->GetType() == GradientType::LINEAR) {
        auto info = gradient->GetLinearGradientInfo();
        std::array<RSPoint, 2> pts = { RSPoint(static_cast<RSScalar>(info.x1), static_cast<RSScalar>(info.y1)),
            RSPoint(static_cast<RSScalar>(info.x2), static_cast<RSScalar>(info.y2)) };
        strokePen_.SetShaderEffect(RSRecordingShaderEffect::CreateLinearGradient(
            pts[0], pts[1], colors, pos, static_cast<RSTileMode>(gradient->GetSpreadMethod())));
    }
    if (gradient->GetType() == GradientType::RADIAL) {
        auto info = gradient->GetRadialGradientInfo();
        auto center = RSPoint(static_cast<RSScalar>(info.cx), static_cast<RSScalar>(info.cy));
        auto focal = RSPoint(static_cast<RSScalar>(info.fx), static_cast<RSScalar>(info.fx));
        if (center == focal) {
            strokePen_.SetShaderEffect(RSRecordingShaderEffect::CreateRadialGradient(center,
                static_cast<RSScalar>(info.r), colors, pos, static_cast<RSTileMode>(gradient->GetSpreadMethod())));
        } else {
            RSMatrix matrix;
            strokePen_.SetShaderEffect(RSRecordingShaderEffect::CreateTwoPointConical(focal, 0, center,
                static_cast<RSScalar>(info.r), colors, pos, static_cast<RSTileMode>(gradient->GetSpreadMethod()),
                &matrix));
        }
    }
#endif
}

bool SvgGraphic::UpdateStrokeStyle(bool antiAlias)
{
    const auto& strokeState = attributes_.strokeState;
    auto colorFilter = GetColorFilter();
    if (!colorFilter.has_value() && strokeState.GetColor() == Color::TRANSPARENT && !strokeState.GetGradient()) {
        return false;
    }
    if (!GreatNotEqual(strokeState.GetLineWidth().Value(), 0.0)) {
        return false;
    }
#ifdef USE_ROSEN_DRAWING
    double curOpacity = strokeState.GetOpacity().GetValue() * opacity_ * (1.0f / UINT8_MAX);
    if (strokeState.GetGradient()) {
        SetStrokeGradientStyle(curOpacity);
    } else {
        strokePen_.SetColor(strokeState.GetColor().BlendOpacity(curOpacity).GetValue());
    }
    if (strokeState.GetLineCap() == LineCapStyle::ROUND) {
        strokePen_.SetCapStyle(RSPen::CapStyle::ROUND_CAP);
    } else if (strokeState.GetLineCap() == LineCapStyle::SQUARE) {
        strokePen_.SetCapStyle(RSPen::CapStyle::SQUARE_CAP);
    } else {
        strokePen_.SetCapStyle(RSPen::CapStyle::FLAT_CAP);
    }
    if (strokeState.GetLineJoin() == LineJoinStyle::ROUND) {
        strokePen_.SetJoinStyle(RSPen::JoinStyle::ROUND_JOIN);
    } else if (strokeState.GetLineJoin() == LineJoinStyle::BEVEL) {
        strokePen_.SetJoinStyle(RSPen::JoinStyle::BEVEL_JOIN);
    } else {
        strokePen_.SetJoinStyle(RSPen::JoinStyle::MITER_JOIN);
    }
    strokePen_.SetWidth(static_cast<RSScalar>(strokeState.GetLineWidth().Value()));
    strokePen_.SetMiterLimit(static_cast<RSScalar>(strokeState.GetMiterLimit()));
    strokePen_.SetAntiAlias(antiAlias);

    auto filter = strokePen_.GetFilter();
    UpdateColorFilter(filter);
    strokePen_.SetFilter(filter);
#endif
    UpdateLineDash();
    return true;
}

void SvgGraphic::UpdateLineDash()
{
    const auto& strokeState = attributes_.strokeState;
    if (!strokeState.GetLineDash().lineDash.empty()) {
        auto lineDashState = strokeState.GetLineDash().lineDash;
#ifndef USE_ROSEN_DRAWING
        std::vector<SkScalar> intervals(lineDashState.size());
        for (size_t i = 0; i < lineDashState.size(); ++i) {
            intervals[i] = SkDoubleToScalar(lineDashState[i]);
        }
        SkScalar phase = SkDoubleToScalar(strokeState.GetLineDash().dashOffset);
        strokePaint_.setPathEffect(SkDashPathEffect::Make(intervals.data(), lineDashState.size(), phase));
#else
        RSScalar intervals[lineDashState.size()];
        for (size_t i = 0; i < lineDashState.size(); ++i) {
            intervals[i] = static_cast<RSScalar>(lineDashState[i]);
        }
        RSScalar phase = static_cast<RSScalar>(strokeState.GetLineDash().dashOffset);
        strokePen_.SetPathEffect(RSRecordingPathEffect::CreateDashPathEffect(intervals, lineDashState.size(), phase));
#endif
    }
}

void SvgGraphic::UpdateColorFilter(RSFilter& filter)
{
    auto colorFilter = GetColorFilter();
    if (!colorFilter.has_value()) {
        return;
    }
    if (colorFilter.value().colorFilterMatrix_) {
        RSColorMatrix colorMatrix;
        colorMatrix.SetArray(colorFilter.value().colorFilterMatrix_->data());
        filter.SetColorFilter(RSRecordingColorFilter::CreateMatrixColorFilter(colorMatrix));
        return;
    }
    if (!colorFilter.value().colorFilterDrawing_) {
        return;
    }
    auto colorFilterSptrAddr = static_cast<std::shared_ptr<RSColorFilter>*>(
        colorFilter.value().colorFilterDrawing_->GetDrawingColorFilterSptrAddr());
    if (!colorFilterSptrAddr || !(*colorFilterSptrAddr)) {
        return;
    }
    filter.SetColorFilter(*colorFilterSptrAddr);
}
} // namespace OHOS::Ace::NG
