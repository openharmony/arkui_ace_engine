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
#include "core/components_ng/svg/parse/svg_linear_gradient.h"
#include "core/components_ng/svg/parse/svg_pattern.h"
#include "core/components_ng/svg/parse/svg_radial_gradient.h"
#include "core/components_ng/svg/parse/svg_transform.h"
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

void SvgGraphic::OnDraw(RSCanvas& canvas, const SvgLengthScaleRule& lengthRule)
{
    RSRecordingPath path = AsPath(lengthRule); // asPath override by graphic tag
    if (!path.IsValid()) {
        return;
    }
    auto bounds = path.GetBounds();
    Rect boundingRect(bounds.GetLeft(), bounds.GetTop(), bounds.GetWidth(), bounds.GetHeight());
    SvgCoordinateSystemContext svgCoordinateSystemContext(boundingRect, lengthRule.GetViewPort());
    svgCoordinateSystemContext.SetUseFillColor(lengthRule.UseFillColor());
    auto fillType = GetFillType();
    if (fillType != PaintType::NONE) {
        OnGraphicFill(canvas, svgCoordinateSystemContext, path, fillType);
    }
    auto strokeType = GetStrokeType();
    if (GreatNotEqual(attributes_.strokeState.GetLineWidth().Value(), 0.0) &&
        strokeType != PaintType::NONE) {
        OnGraphicStroke(canvas, svgCoordinateSystemContext, path, strokeType);
    }
}

void SvgGraphic::DumpDrawPathInfo(const RSRecordingPath& path)
{
    auto svgContext = svgContext_.Upgrade();
    if (!svgContext || svgContext->GetHasRecordedPath()) {
        return;
    }
    std::string dumpInfo = "";
    path.Dump(dumpInfo);
    svgContext->SetSvgDrawPathInfoDump(std::move(dumpInfo));
}

PaintType SvgGraphic::GetFillType()
{
    // fill="none" in this shape, return PaintType::None
    if (attributes_.fillState.IsFillNone()) {
        return PaintType::NONE;
    }
    // fill=pattern, gradient in this shape
    if (!attributes_.fillState.GetHref().empty()) {
        return GetHrefType(attributes_.fillState.GetHref());
    }
    // fill="color" case
    if (attributes_.fillState.HasColor()) {
        return PaintType::COLOR;
    }
    // this shape fill has no color, Href, gradient, but gradient inherit from parent
    auto& gradient = attributes_.fillState.GetGradient();
    if (gradient.has_value()) {
        auto href = gradient->GetHref();
        if (!href.empty()) {
            attributes_.fillState.SetHref(href);
            return GetHrefType(attributes_.fillState.GetHref());
        }
    }
    //By default No Fill in this shape and inherited from parent, apply the default color
    return PaintType::COLOR;
}

bool SvgGraphic::CheckHrefPattern()
{
    auto svgContext = svgContext_.Upgrade();
    CHECK_NULL_RETURN(svgContext, false);
    auto refSvgNode = svgContext->GetSvgNodeById(fillState_.GetHref());
    CHECK_NULL_RETURN(refSvgNode, false);
    return AceType::InstanceOf<SvgPattern>(refSvgNode);
}

PaintType SvgGraphic::GetHrefType(const std::string& href)
{
    auto svgContext = svgContext_.Upgrade();
    CHECK_NULL_RETURN(svgContext, PaintType::NONE);
    auto refSvgNode = svgContext->GetSvgNodeById(href);
    CHECK_NULL_RETURN(refSvgNode, PaintType::NONE);
    if (AceType::InstanceOf<SvgPattern>(refSvgNode)) {
        return PaintType::PATTERN;
    }
    if (AceType::InstanceOf<SvgLinearGradient>(refSvgNode)) {
        return PaintType::LINEAR_GRADIENT;
    }
    if (AceType::InstanceOf<SvgRadialGradient>(refSvgNode)) {
        return PaintType::RADIAL_GRADIENT;
    }
    return PaintType::NONE;
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

bool SvgGraphic::GradientHasColors()
{
    auto& gradient = attributes_.fillState.GetGradient();
    CHECK_NULL_RETURN(gradient, false);
    auto gradientColors = gradient->GetColors();
    if (gradientColors.empty()) {
        LOGW("SvgGraphic::GradientHasColors gradient doesn't has color");
        return false ;
    }
    return true;
}

bool SvgGraphic::InitBrush(RSCanvas& canvas, RSBrush& brush,
    const SvgCoordinateSystemContext& svgCoordinateSystemContext, PaintType type)
{
    bool setBrushResult = true;
    switch (type) {
        case PaintType::COLOR:
            SetBrushColor(brush, svgCoordinateSystemContext.UseFillColor());
            break;
        case PaintType::LINEAR_GRADIENT:
            setBrushResult = SetBrushLinearGradient(brush, svgCoordinateSystemContext);
            break;
        case PaintType::RADIAL_GRADIENT:
            setBrushResult = SetBrushRadialGradient(brush, svgCoordinateSystemContext);
            break;
        case PaintType::PATTERN:
            setBrushResult = SetBrushPattern(canvas,  brush, svgCoordinateSystemContext);
            break;
        default:
            break;
    }
    return setBrushResult;
}

// subgraph does not use image components parameter fillColor, example: mask
void SvgGraphic::SetBrushColor(RSBrush& brush, bool useFillColor)
{
    auto curOpacity = GetFillOpacity();
    auto imageComponentColor = GetFillColor();
    if (!imageComponentColor.has_value() || attributes_.fillState.IsFillNone() || !useFillColor) {
        brush.SetColor(attributes_.fillState.GetColor().BlendOpacity(curOpacity).GetValue());
        return;
    }
    brush.SetColor(imageComponentColor->BlendOpacity(curOpacity).GetValue());
}

RsLinearGradient SvgGraphic::ConvertToRsLinearGradient(const SvgLinearGradientInfo& linearGradientInfo)
{
    std::vector<RSScalar> pos;
    std::vector<RSColorQuad> colors;
    for (const auto& gradientColor : linearGradientInfo.colors) {
        pos.push_back(static_cast<RSScalar>(gradientColor.GetDimension().Value()));
        colors.push_back(
            gradientColor.GetColor().BlendOpacity(gradientColor.GetOpacity()).GetValue());
    }
    RSPoint startPoint(static_cast<RSScalar>(linearGradientInfo.x1), static_cast<RSScalar>(linearGradientInfo.y1));
    RSPoint endPoint(static_cast<RSScalar>(linearGradientInfo.x2), static_cast<RSScalar>(linearGradientInfo.y2));
    return RsLinearGradient({ .startPoint_ = startPoint, .endPoint_ = endPoint,
        .spreadMethod_ = static_cast<RSTileMode>(linearGradientInfo.spreadMethod),
        .pos_ = pos, .colors_ = colors });
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
    if (Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_FOURTEEN)) {
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
        if (Container::LessThanAPITargetVersion(PlatformVersion::VERSION_EIGHTEEN)) {
            fillColor = (color) ? *color : fillState_.GetColor();
        } else {
            fillColor = (color && !fillState_.IsFillNone()) ? *color : fillState_.GetColor();
        }
        if (fillColor.GetColorSpace() == ColorSpace::DISPLAY_P3) {
            auto p3Color = fillColor.BlendOpacity(curOpacity);
            fillBrush_.SetColor({ p3Color.GetRed() / 255.0, p3Color.GetGreen() / 255.0, p3Color.GetBlue() / 255.0,
                                    p3Color.GetAlpha() / 255.0 },
                RSColorSpace::CreateRGB(RSCMSTransferFuncType::SRGB, RSCMSMatrixType::DCIP3));
        } else {
            fillBrush_.SetColor(fillColor.BlendOpacity(curOpacity).GetValue());
        }
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
    if (Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_FOURTEEN)) {
        auto bounds = path_->GetBounds();
        auto maxBounds = std::max(bounds.GetWidth(), bounds.GetHeight());
        if (maxBounds != 0) {
            RSMatrix m;
            RSMatrix t;
            auto scaleX = bounds.GetWidth() / maxBounds;
            auto scaleY = bounds.GetHeight() / maxBounds;
            auto transX = (1 - scaleX) * (bounds.GetLeft() + bounds.GetWidth() * HALF);
            auto transY = (1 - scaleY) * (bounds.GetTop() + bounds.GetHeight() * HALF);
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

RSMatrix SvgGraphic::GetLocalMatrix(SvgLengthScaleUnit gradientUnits,
    const SvgCoordinateSystemContext& svgCoordinateSystemContext)
{
    if (gradientUnits == SvgLengthScaleUnit::OBJECT_BOUNDING_BOX) {
        auto bounds = svgCoordinateSystemContext.GetContainerRect();
        RSMatrix m;
        RSMatrix t;
        m.SetScale(bounds.Width(), bounds.Height());
        t.Translate(bounds.Left(), bounds.Top());
        t.PreConcat(m);
        return t;
    }
    return RSMatrix();
}

bool SvgGraphic::SetBrushLinearGradient(RSBrush& brush, const SvgCoordinateSystemContext& svgCoordinateSystemContext)
{
    if (!GradientHasColors()) {
        return false;
    }
    auto svgContext = svgContext_.Upgrade();
    CHECK_NULL_RETURN(svgContext, false);
    auto linearGradientNode =
        DynamicCast<SvgLinearGradient>(svgContext->GetSvgNodeById(attributes_.fillState.GetHref()));
    CHECK_NULL_RETURN(linearGradientNode, false);
    SetBrushOpacity(brush);
    RsLinearGradient rsLinearGradient =
        ConvertToRsLinearGradient(linearGradientNode->GetLinearGradientInfo(svgCoordinateSystemContext));
    auto rsMatrix = rsLinearGradient.matrix_.value_or(RSMatrix());
    RSMatrix t = GetLocalMatrix(linearGradientNode->GradientUnits(), svgCoordinateSystemContext);
    rsMatrix = rsMatrix * t;
    brush.SetShaderEffect(RSRecordingShaderEffect::CreateLinearGradient(rsLinearGradient.startPoint_,
        rsLinearGradient.endPoint_, rsLinearGradient.colors_, rsLinearGradient.pos_,
        rsLinearGradient.spreadMethod_, &rsMatrix));
    return true;
}

RsRadialGradient SvgGraphic::ConvertToRsRadialGradient(const SvgRadialGradientInfo& radialGradientInfo)
{
    std::vector<RSScalar> pos;
    std::vector<RSColorQuad> colors;
    for (const auto& gradientColor : radialGradientInfo.colors) {
        pos.push_back(static_cast<RSScalar>(gradientColor.GetDimension().Value()));
        colors.push_back(
            gradientColor.GetColor().BlendOpacity(gradientColor.GetOpacity()).GetValue());
    }
    RSPoint center(static_cast<RSScalar>(radialGradientInfo.cx), static_cast<RSScalar>(radialGradientInfo.cy));
    RSPoint focal(static_cast<RSScalar>(radialGradientInfo.fx), static_cast<RSScalar>(radialGradientInfo.fy));

    return RsRadialGradient({ .center_ = center, .focal_ = focal,
        .spreadMethod_ = static_cast<RSTileMode>(radialGradientInfo.spreadMethod),
        .r_ = static_cast<RSScalar>(radialGradientInfo.r), .pos_ = pos, .colors_ = colors});
}

bool SvgGraphic::SetBrushRadialGradient(RSBrush& brush, const SvgCoordinateSystemContext& svgCoordinateSystemContext)
{
    if (!GradientHasColors()) {
        return false;
    }
    auto svgContext = svgContext_.Upgrade();
    CHECK_NULL_RETURN(svgContext, false);
    auto radialGradientNode =
        DynamicCast<SvgRadialGradient>(svgContext->GetSvgNodeById(attributes_.fillState.GetHref()));
    CHECK_NULL_RETURN(radialGradientNode, false);
    SetBrushOpacity(brush);
    auto rsRadialGradient =
        ConvertToRsRadialGradient(radialGradientNode->GetRadialGradientInfo(svgCoordinateSystemContext));
    auto rsMatrix = rsRadialGradient.matrix_.value_or(RSMatrix());
    RSMatrix t = GetLocalMatrix(radialGradientNode->GradientUnits(), svgCoordinateSystemContext);
    rsMatrix = rsMatrix * t;
    if (rsRadialGradient.center_ == rsRadialGradient.focal_) {
        brush.SetShaderEffect(RSRecordingShaderEffect::CreateRadialGradient(rsRadialGradient.center_,
            rsRadialGradient.r_, rsRadialGradient.colors_, rsRadialGradient.pos_, rsRadialGradient.spreadMethod_,
            &rsMatrix));
    } else {
        brush.SetShaderEffect(RSRecordingShaderEffect::CreateTwoPointConical(rsRadialGradient.focal_, 0,
            rsRadialGradient.center_, rsRadialGradient.r_, rsRadialGradient.colors_,
            rsRadialGradient.pos_, rsRadialGradient.spreadMethod_, &rsMatrix));
    }
    return true;
}

bool SvgGraphic::SetBrushPattern(RSCanvas& canvas, RSBrush& brush,
    const SvgCoordinateSystemContext& svgCoordinateSystemContext)
{
    auto svgContext = svgContext_.Upgrade();
    CHECK_NULL_RETURN(svgContext, false);
    auto refPatternNode = DynamicCast<SvgPattern>(svgContext->GetSvgNodeById(attributes_.fillState.GetHref()));
    CHECK_NULL_RETURN(refPatternNode, false);
    refPatternNode->OnPatternEffect(canvas, brush, svgCoordinateSystemContext);
    return true;
}

double SvgGraphic::GetFillOpacity()
{
    auto curOpacity = 1.0;
    if (attributes_.hasOpacity) {
        curOpacity = opacity_ * (1.0f / UINT8_MAX);
    }
    curOpacity *= attributes_.fillState.GetOpacity().GetValue();
    return curOpacity;
}

double SvgGraphic::GetStrokeOpacity()
{
    auto curOpacity = 1.0;
    if (attributes_.hasOpacity) {
        curOpacity = opacity_ * (1.0f / UINT8_MAX);
    }
    curOpacity *= attributes_.strokeState.GetOpacity().GetValue();
    return curOpacity;
}

void SvgGraphic::SetBrushOpacity(RSBrush& brush)
{
    uint32_t alpha = GetFillOpacity() * UINT8_MAX;
    brush.SetAlpha(alpha);
    return;
}

void SvgGraphic::SetPenOpacity(RSPen& pen)
{
    uint32_t alpha = GetStrokeOpacity() * UINT8_MAX;
    pen.SetAlpha(alpha);
    return;
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

PaintType SvgGraphic::GetStrokeType()
{
    if (attributes_.strokeState.GetColor() == Color::TRANSPARENT) {
        return PaintType::NONE;
    }
    if (attributes_.strokeState.HasColor()) {
        return PaintType::COLOR;
    }
    if (!attributes_.strokeState.GetHref().empty()) {
        return GetHrefType(attributes_.strokeState.GetHref());
    }
    auto& gradient = attributes_.strokeState.GetGradient();
    if (gradient.has_value()) {
        auto href = gradient->GetHref();
        if (!href.empty()) {
            attributes_.strokeState.SetHref(href);
            return GetHrefType(attributes_.strokeState.GetHref());
        }
    }
    return PaintType::COLOR;
}

bool SvgGraphic::InitPenFill(RSPen& rsPen, const SvgCoordinateSystemContext& svgCoordinateSystemContext,
    PaintType type)
{
    bool setPenResult = true;
    switch (type) {
        case PaintType::COLOR:
            SetPenColor(rsPen);
            break;
        case PaintType::LINEAR_GRADIENT:
            setPenResult = SetPenLinearGradient(rsPen, svgCoordinateSystemContext);
            break;
        case PaintType::RADIAL_GRADIENT:
            setPenResult = SetPenRadialGradient(rsPen, svgCoordinateSystemContext);
            break;
        case PaintType::PATTERN:
            break;
        default:
            break;
    }
    return setPenResult;
}

void SvgGraphic::SetPenStyle(RSPen& rsPen)
{
    if (attributes_.strokeState.GetLineCap() == LineCapStyle::ROUND) {
        rsPen.SetCapStyle(RSPen::CapStyle::ROUND_CAP);
    } else if (attributes_.strokeState.GetLineCap() == LineCapStyle::SQUARE) {
        rsPen.SetCapStyle(RSPen::CapStyle::SQUARE_CAP);
    } else {
        rsPen.SetCapStyle(RSPen::CapStyle::FLAT_CAP);
    }
    if (attributes_.strokeState.GetLineJoin() == LineJoinStyle::ROUND) {
        rsPen.SetJoinStyle(RSPen::JoinStyle::ROUND_JOIN);
    } else if (attributes_.strokeState.GetLineJoin() == LineJoinStyle::BEVEL) {
        rsPen.SetJoinStyle(RSPen::JoinStyle::BEVEL_JOIN);
    } else {
        rsPen.SetJoinStyle(RSPen::JoinStyle::MITER_JOIN);
    }
    rsPen.SetWidth(static_cast<RSScalar>(attributes_.strokeState.GetLineWidth().Value()));
    rsPen.SetMiterLimit(static_cast<RSScalar>(attributes_.strokeState.GetMiterLimit()));
    rsPen.SetAntiAlias(true);
    auto lineDashState = attributes_.strokeState.GetLineDash().lineDash;
    if (lineDashState.empty()) {
        return;
    }

    auto intervalsLen = lineDashState.size();
    if (lineDashState.size() % 2 != 0) { // 2:judging odd
        intervalsLen = lineDashState.size() * 2; // 2:double size
    }
    RSScalar intervals[intervalsLen];
    for (size_t i = 0; i < intervalsLen; ++i) {
        intervals[i] = static_cast<RSScalar>(lineDashState[i % lineDashState.size()]);
    }
    RSScalar phase = static_cast<RSScalar>(attributes_.strokeState.GetLineDash().dashOffset);
    rsPen.SetPathEffect(RSRecordingPathEffect::CreateDashPathEffect(intervals, intervalsLen, phase));
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
        if (!Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_FOURTEEN)) {
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

void SvgGraphic::SetPenColor(RSPen& rsPen)
{
    auto curOpacity = GetStrokeOpacity();
    rsPen.SetColor(attributes_.strokeState.GetColor().BlendOpacity(curOpacity).GetValue());
}

void SvgGraphic::AddColorFilterEffect(RSPen& rsPen)
{
    auto colorFilter = GetColorFilter();
    if (!colorFilter.has_value()) {
        return;
    }
    if (colorFilter.value().colorFilterMatrix_) {
        RSColorMatrix colorMatrix;
        colorMatrix.SetArray(colorFilter.value().colorFilterMatrix_->data());
        auto filter = rsPen.GetFilter();
        filter.SetColorFilter(RSRecordingColorFilter::CreateMatrixColorFilter(colorMatrix));
        rsPen.SetFilter(filter);
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
    auto filter = rsPen.GetFilter();
    filter.SetColorFilter(*colorFilterSptrAddr);
    rsPen.SetFilter(filter);
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

bool SvgGraphic::SetPenLinearGradient(RSPen& rsPen, const SvgCoordinateSystemContext& svgCoordinateSystemContext)
{
    if (!GradientHasColors()) {
        return false;
    }
    auto svgContext = svgContext_.Upgrade();
    CHECK_NULL_RETURN(svgContext, false);
    auto linearGradientNode =
        DynamicCast<SvgLinearGradient>(svgContext->GetSvgNodeById(attributes_.strokeState.GetHref()));
    CHECK_NULL_RETURN(linearGradientNode, false);
    SetPenOpacity(rsPen);
    RsLinearGradient rsLinearGradient =
        ConvertToRsLinearGradient(linearGradientNode->GetLinearGradientInfo(svgCoordinateSystemContext));
    auto rsMatrix = rsLinearGradient.matrix_.value_or(RSMatrix());
    RSMatrix t = GetLocalMatrix(linearGradientNode->GradientUnits(), svgCoordinateSystemContext);
    rsMatrix = rsMatrix * t;
    rsPen.SetShaderEffect(RSRecordingShaderEffect::CreateLinearGradient(
        rsLinearGradient.startPoint_, rsLinearGradient.endPoint_, rsLinearGradient.colors_,
        rsLinearGradient.pos_, rsLinearGradient.spreadMethod_, &rsMatrix));
    return true;
}

bool SvgGraphic::SetPenRadialGradient(RSPen& rsPen, const SvgCoordinateSystemContext& svgCoordinateSystemContext)
{
    if (!GradientHasColors()) {
        return false;
    }
    auto svgContext = svgContext_.Upgrade();
    CHECK_NULL_RETURN(svgContext, false);
    auto radialGradientNode =
        DynamicCast<SvgRadialGradient>(svgContext->GetSvgNodeById(attributes_.strokeState.GetHref()));
    CHECK_NULL_RETURN(radialGradientNode, false);
    SetPenOpacity(rsPen);
    auto rsRadialGradient =
        ConvertToRsRadialGradient(radialGradientNode->GetRadialGradientInfo(svgCoordinateSystemContext));
    auto rsMatrix = rsRadialGradient.matrix_.value_or(RSMatrix());
    RSMatrix t = GetLocalMatrix(radialGradientNode->GradientUnits(), svgCoordinateSystemContext);
    rsMatrix = rsMatrix * t;
    if (rsRadialGradient.center_ == rsRadialGradient.focal_) {
        rsPen.SetShaderEffect(RSRecordingShaderEffect::CreateRadialGradient(rsRadialGradient.center_,
            rsRadialGradient.r_, rsRadialGradient.colors_, rsRadialGradient.pos_, rsRadialGradient.spreadMethod_,
            &rsMatrix));
    } else {
        rsPen.SetShaderEffect(RSRecordingShaderEffect::CreateTwoPointConical(rsRadialGradient.focal_, 0,
            rsRadialGradient.center_, rsRadialGradient.r_, rsRadialGradient.colors_, rsRadialGradient.pos_,
            rsRadialGradient.spreadMethod_, &rsMatrix));
    }
    return true;
}

std::optional<Color> SvgGraphic::GetFillColor()
{
    auto svgContext = svgContext_.Upgrade();
    CHECK_NULL_RETURN(svgContext, std::nullopt);
    return svgContext->GetFillColor();
}

void SvgGraphic::ApplyTransform(RSRecordingPath& path)
{
    auto matrix = RSMatrix();
    if (attributes_.transformVec.size() == 1) {
        if (attributes_.transformVec[0].funcType == "translate") {
            auto ret = NGSvgTransform::CreateTranslate(attributes_.transformVec[0].paramVec, matrix);
            if (ret) {
                LOGD("SvgGraphic::ApplyTransform calling translate");
                path.Transform(matrix);
            }
        }
        return;
    }
}
} // namespace OHOS::Ace::NG
