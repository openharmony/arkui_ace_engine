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

#include "core/common/container.h"
#include "core/components_ng/svg/parse/svg_pattern.h"

namespace OHOS::Ace::NG {
namespace {
    constexpr double HALF = 0.5;
} // namespace

void SvgGraphic::OnDraw(RSCanvas& canvas, const Size& layout, const std::optional<Color>& color)
{
    fillBrush_.Reset();
    strokePen_.Reset();
    path_ = AsPath(layout); // asPath override by graphic tag
    UpdateFillGradient(layout);
    if (UpdateFillStyle(color)) {
        OnGraphicFill();
    }
    if (Container::LessThanAPITargetVersion(PlatformVersion::VERSION_FOURTEEN)) {
        UpdateStrokeGradient(layout);
        if (UpdateStrokeStyle()) {
            OnGraphicStroke();
        }
        if (!fillState_.GetHref().empty()) {
            auto svgContext = svgContext_.Upgrade();
            CHECK_NULL_VOID(svgContext);
            auto refSvgNode = svgContext->GetSvgNodeById(fillState_.GetHref());
            CHECK_NULL_VOID(refSvgNode);
            refSvgNode->Draw(canvas, layout, color);
        }
        return;
    }
    if (!fillState_.GetHref().empty()) {
        auto svgContext = svgContext_.Upgrade();
        CHECK_NULL_VOID(svgContext);
        auto refSvgNode = svgContext->GetSvgNodeById(fillState_.GetHref());
        CHECK_NULL_VOID(refSvgNode);
        auto bounds = AsPath(layout).GetBounds();
        Rect rect = Rect { bounds.GetLeft(), bounds.GetTop(), bounds.GetWidth(), bounds.GetHeight() };
        auto svgpattern = AceType::DynamicCast<SvgPattern>(refSvgNode);
        CHECK_NULL_VOID(svgpattern);
        svgpattern->SetBoundingBoxRect(rect);
        refSvgNode->Draw(canvas, layout, color);
    }
    UpdateStrokeGradient(layout);
    if (UpdateStrokeStyle()) {
        OnGraphicStroke();
    }
}

bool SvgGraphic::CheckHrefPattern()
{
    auto svgContext = svgContext_.Upgrade();
    CHECK_NULL_RETURN(svgContext, false);
    auto refSvgNode = svgContext->GetSvgNodeById(fillState_.GetHref());
    CHECK_NULL_RETURN(refSvgNode, false);
    return AceType::InstanceOf<SvgPattern>(refSvgNode);
}

void SvgGraphic::SetLinearGradient(const Size& viewPort, OHOS::Ace::Gradient& gradient)
{
    auto bounds = AsBounds(viewPort);
    auto width = bounds.Width();
    auto height = bounds.Height();

    const auto& linearGradient = gradient.GetLinearGradient();
    auto gradientInfo = OHOS::Ace::LinearGradientInfo();

    if (Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_FOURTEEN) &&
        NearEqual(linearGradient.x1, linearGradient.y1) && NearEqual(linearGradient.x2, linearGradient.y2)) {
        RectifyTargetSize(bounds, width, height);
    }

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

void SvgGraphic::SetRadialGradient(const Size& viewPort, OHOS::Ace::Gradient& gradient)
{
    auto bounds = AsBounds(viewPort);
    auto width = bounds.Width();
    auto height = bounds.Height();

    const auto& radialGradient = gradient.GetRadialGradient();
    auto gradientInfo = OHOS::Ace::RadialGradientInfo();

    gradientInfo.r = ConvertDimensionToPx(radialGradient.radialHorizontalSize ?
        Dimension(radialGradient.radialHorizontalSize.value().Value(),
        radialGradient.radialHorizontalSize.value().Unit()) : 0.5_pct, std::max(width, height));
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
    if (Container::LessThanAPITargetVersion(PlatformVersion::VERSION_FOURTEEN)) {
        gradientInfo.r = ConvertDimensionToPx(radialGradient.radialHorizontalSize ?
            Dimension(radialGradient.radialHorizontalSize.value().Value(),
            radialGradient.radialHorizontalSize.value().Unit()) : 0.5_pct, std::sqrt(width * height));
        gradientInfo.fy = gradientInfo.fx;
    } else {
        gradientInfo.r = ConvertDimensionToPx(radialGradient.radialHorizontalSize ?
            Dimension(radialGradient.radialHorizontalSize.value().Value(),
            radialGradient.radialHorizontalSize.value().Unit()) : 0.5_pct, std::max(width, height));
    }
    gradient.SetRadialGradientInfo(gradientInfo);
}

void SvgGraphic::UpdateFillGradient(const Size& viewPort)
{
    fillState_ = attributes_.fillState;
    auto& gradient = fillState_.GetGradient();
    CHECK_NULL_VOID(gradient);
    if (gradient->GetType() == OHOS::Ace::GradientType::LINEAR) {
        SetLinearGradient(viewPort, gradient.value());
    } else if (gradient->GetType() == OHOS::Ace::GradientType::RADIAL) {
        SetRadialGradient(viewPort, gradient.value());
    }
}

void SvgGraphic::UpdateStrokeGradient(const Size& viewPort)
{
    auto& gradient = attributes_.strokeState.GetGradient();
    CHECK_NULL_VOID(gradient);
    if (gradient->GetType() == OHOS::Ace::GradientType::LINEAR) {
        SetLinearGradient(viewPort, gradient.value());
    } else if (gradient->GetType() == OHOS::Ace::GradientType::RADIAL) {
        SetRadialGradient(viewPort, gradient.value());
    }
}

bool SvgGraphic::UpdateFillStyle(const std::optional<Color>& color, bool antiAlias)
{
    if (!color && fillState_.GetColor() == Color::TRANSPARENT && !fillState_.GetGradient()) {
        return false;
    }
    if (Container::GreatOrEqualAPIVersion(PlatformVersion::VERSION_FOURTEEN)) {
        if (!fillState_.GetHref().empty() && CheckHrefPattern()) {
            fillState_.SetColor(Color::TRANSPARENT);
        }
    }
    double curOpacity = fillState_.GetOpacity().GetValue() * opacity_ * (1.0f / UINT8_MAX);
    fillBrush_.SetAntiAlias(antiAlias);
    if (fillState_.GetGradient()) {
        if (Container::LessThanAPITargetVersion(PlatformVersion::VERSION_FOURTEEN)) {
            SetGradientStyle(curOpacity);
            return true;
        }
        return SetGradientStyle(curOpacity);
    } else {
        Color fillColor;
        if (Container::LessThanAPITargetVersion(PlatformVersion::VERSION_SIXTEEN)) {
            fillColor = (color) ? *color : fillState_.GetColor();
        } else {
            fillColor = (color && !fillState_.IsFillNone()) ? *color : fillState_.GetColor();
        }
        fillBrush_.SetColor(fillColor.BlendOpacity(curOpacity).GetValue());
    }
    return true;
}

void SvgGraphic::SetGradientFillStyle(const std::optional<OHOS::Ace::Gradient>& gradient,
    std::vector<RSScalar> pos, std::vector<RSColorQuad> colors)
{
    RSMatrix result;
    auto info = gradient->GetRadialGradientInfo();
    auto center = RSPoint(static_cast<RSScalar>(info.cx), static_cast<RSScalar>(info.cy));
    auto focal = RSPoint(static_cast<RSScalar>(info.fx), static_cast<RSScalar>(info.fy));
    if (Container::GreatOrEqualAPIVersion(PlatformVersion::VERSION_FOURTEEN)) {
        auto bounds = path_.GetBounds();
        auto maxBounds = std::max(bounds.GetWidth(), bounds.GetHeight());
        if (maxBounds != 0) {
            RSMatrix m, t;
            auto scaleX = bounds.GetWidth() / maxBounds;
            auto scaleY = bounds.GetHeight() / maxBounds;
            auto transX = (1 - scaleX) * (bounds.GetLeft() + bounds.GetWidth()* HALF);
            auto transY = (1 - scaleY) * (bounds.GetTop() + bounds.GetHeight()* HALF);
            m.SetScale(scaleX, scaleY);
            t.Translate(transX, transY);
            t.PreConcat(m);
            result = t;
        }
        if (center == focal) {
            fillBrush_.SetShaderEffect(RSRecordingShaderEffect::CreateRadialGradient(center,
                static_cast<RSScalar>(info.r), colors, pos, static_cast<RSTileMode>(gradient->GetSpreadMethod())));
        } else {
            fillBrush_.SetShaderEffect(RSRecordingShaderEffect::CreateTwoPointConical(focal, 0, center,
                static_cast<RSScalar>(info.r), colors, pos, static_cast<RSTileMode>(gradient->GetSpreadMethod()),
                &result));
        }
    } else {
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
}

bool SvgGraphic::SetGradientStyle(double opacity)
{
    auto gradient = fillState_.GetGradient();
    CHECK_NULL_RETURN(gradient, false);
    auto gradientColors = gradient->GetColors();
    if (gradientColors.empty()) {
        return false;
    }
    std::vector<RSScalar> pos;
    std::vector<RSColorQuad> colors;
    for (const auto& gradientColor : gradientColors) {
        pos.push_back(static_cast<RSScalar>(gradientColor.GetDimension().Value()));
        colors.push_back(
            gradientColor.GetColor().BlendOpacity(gradientColor.GetOpacity()).BlendOpacity(opacity).GetValue());
    }
    if (gradient->GetType() == OHOS::Ace::GradientType::LINEAR) {
        auto info = gradient->GetLinearGradientInfo();
        std::array<RSPoint, 2> pts = { RSPoint(static_cast<RSScalar>(info.x1), static_cast<RSScalar>(info.y1)),
            RSPoint(static_cast<RSScalar>(info.x2), static_cast<RSScalar>(info.y2)) };
        fillBrush_.SetShaderEffect(RSRecordingShaderEffect::CreateLinearGradient(
            pts[0], pts[1], colors, pos, static_cast<RSTileMode>(gradient->GetSpreadMethod())));
    }
    if (gradient->GetType() == OHOS::Ace::GradientType::RADIAL) {
        SetGradientFillStyle(gradient, pos, colors);
    }
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
    std::vector<RSScalar> pos;
    std::vector<RSColorQuad> colors;
    for (const auto& gradientColor : gradientColors) {
        pos.push_back(static_cast<RSScalar>(gradientColor.GetDimension().Value()));
        colors.push_back(
            gradientColor.GetColor().BlendOpacity(gradientColor.GetOpacity()).BlendOpacity(opacity).GetValue());
    }
    if (gradient->GetType() == OHOS::Ace::GradientType::LINEAR) {
        auto info = gradient->GetLinearGradientInfo();
        std::array<RSPoint, 2> pts = { RSPoint(static_cast<RSScalar>(info.x1), static_cast<RSScalar>(info.y1)),
            RSPoint(static_cast<RSScalar>(info.x2), static_cast<RSScalar>(info.y2)) };
        strokePen_.SetShaderEffect(RSRecordingShaderEffect::CreateLinearGradient(
            pts[0], pts[1], colors, pos, static_cast<RSTileMode>(gradient->GetSpreadMethod())));
    }
    if (gradient->GetType() == OHOS::Ace::GradientType::RADIAL) {
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
    UpdateLineDash();
    return true;
}

void SvgGraphic::UpdateLineDash()
{
    const auto& strokeState = attributes_.strokeState;
    if (!strokeState.GetLineDash().lineDash.empty()) {
        auto lineDashState = strokeState.GetLineDash().lineDash;
        if (!Container::GreatOrEqualAPIVersion(PlatformVersion::VERSION_FOURTEEN)) {
            RSScalar intervals[lineDashState.size()];
            for (size_t i = 0; i < lineDashState.size(); ++i) {
                intervals[i] = static_cast<RSScalar>(lineDashState[i]);
            }
            RSScalar phase = static_cast<RSScalar>(strokeState.GetLineDash().dashOffset);
            strokePen_.SetPathEffect(
                RSRecordingPathEffect::CreateDashPathEffect(intervals, lineDashState.size(), phase));
        } else {
            auto intervalsLen = lineDashState.size();

            if (lineDashState.size() % 2 != 0) { // 2:judging odd
                intervalsLen = lineDashState.size() * 2; // 2:double size
            }
            RSScalar intervals[intervalsLen];
            for (size_t i = 0; i < intervalsLen; ++i) {
                intervals[i] = static_cast<RSScalar>(lineDashState[i % lineDashState.size()]);
            }
            RSScalar phase = static_cast<RSScalar>(strokeState.GetLineDash().dashOffset);
            strokePen_.SetPathEffect(RSRecordingPathEffect::CreateDashPathEffect(intervals, intervalsLen, phase));
        }
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

void SvgGraphic::RectifyTargetSize(const Rect& bounds, double& width, double& height)
{
    if (NearZero(bounds.Height())) {
        return;
    }
    auto scalar = bounds.Width() / bounds.Height();
    width = 2 * bounds.Height() * sin(std::atan(scalar)) * cos(atan(scalar));  // 2: algorithm parameters
    height = 2 * bounds.Height() * sin(std::atan(scalar)) * sin(atan(scalar)); // 2: algorithm parameters
}
} // namespace OHOS::Ace::NG
