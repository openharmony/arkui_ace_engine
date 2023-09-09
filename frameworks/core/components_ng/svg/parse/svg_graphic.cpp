/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
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

#include "frameworks/core/components_ng/svg/parse/svg_graphic.h"

#include "include/core/SkScalar.h"
#include "include/effects/SkDashPathEffect.h"
#include "include/effects/SkGradientShader.h"

#include "base/utils/utils.h"

namespace OHOS::Ace::NG {
void SvgGraphic::UpdateGradient(const Size& viewPort)
{
    fillState_ = declaration_->GetFillState();
    auto& gradient = fillState_.GetGradient();
    CHECK_NULL_VOID(gradient);
    auto bounds = AsBounds(viewPort);
    auto width = bounds.Width();
    auto height = bounds.Height();
    if (gradient->GetType() == GradientType::LINEAR) {
        const auto& linearGradient = gradient->GetLinearGradient();
        auto gradientInfo = LinearGradientInfo();
        auto x1 = linearGradient.x1 ? ConvertDimensionToPx(linearGradient.x1.value(), width) : 0.0;
        gradientInfo.x1 = x1 + bounds.Left();
        auto y1 = linearGradient.y1 ? ConvertDimensionToPx(linearGradient.y1.value(), height) : 0.0;
        gradientInfo.y1 = y1 + bounds.Top();
        auto x2 = ConvertDimensionToPx((linearGradient.x2 ? linearGradient.x2.value() : 1.0_pct), width);
        gradientInfo.x2 = x2 + bounds.Left();
        auto y2 = linearGradient.y2 ? ConvertDimensionToPx(linearGradient.y2.value(), height) : 0.0;
        gradientInfo.y2 = y2 + bounds.Top();
        gradient->SetLinearGradientInfo(gradientInfo);
    }
    if (gradient->GetType() == GradientType::RADIAL) {
        const auto& radialGradient = gradient->GetRadialGradient();
        auto gradientInfo = RadialGradientInfo();
        Dimension radialHorizontalSize = Dimension(
            radialGradient.radialHorizontalSize.value().Value(), radialGradient.radialHorizontalSize.value().Unit());
        gradientInfo.r = ConvertDimensionToPx(
            radialGradient.radialHorizontalSize ? radialHorizontalSize : 0.5_pct, sqrt(width * height));
        Dimension radialCenterX =
            Dimension(radialGradient.radialCenterX.value().Value(), radialGradient.radialCenterX.value().Unit());
        gradientInfo.cx =
            ConvertDimensionToPx(radialGradient.radialCenterX ? radialCenterX : 0.5_pct, width) + bounds.Left();
        Dimension radialCenterY =
            Dimension(radialGradient.radialCenterY.value().Value(), radialGradient.radialCenterY.value().Unit());
        gradientInfo.cy =
            ConvertDimensionToPx(radialGradient.radialCenterY ? radialCenterY : 0.5_pct, height) + bounds.Top();
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
        gradient->SetRadialGradientInfo(gradientInfo);
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
        SetGradientStyle(curOpacity);
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

void SvgGraphic::SetGradientStyle(double opacity)
{
    auto gradient = fillState_.GetGradient();
    CHECK_NULL_VOID(gradient);
    auto gradientColors = gradient->GetColors();
    if (gradientColors.empty()) {
        return;
    }
#ifndef USE_ROSEN_DRAWING
    std::vector<SkScalar> pos;
    std::vector<SkColor> colors;
    for (const auto& gradientColor : gradientColors) {
        pos.push_back(static_cast<SkScalar>(gradientColor.GetDimension().Value()));
        colors.push_back(
            gradientColor.GetColor().BlendOpacity(gradientColor.GetOpacity()).BlendOpacity(opacity).GetValue());
    }
    if (gradient->GetType() == GradientType::LINEAR) {
        auto info = gradient->GetLinearGradientInfo();
        std::array<SkPoint, 2> pts = { SkPoint::Make(static_cast<SkScalar>(info.x1), static_cast<SkScalar>(info.y1)),
            SkPoint::Make(static_cast<SkScalar>(info.x2), static_cast<SkScalar>(info.y2)) };
#ifdef USE_SYSTEM_SKIA
        fillPaint_.setShader(SkGradientShader::MakeLinear(pts.data(), colors.data(), pos.data(), gradientColors.size(),
            static_cast<SkShader::TileMode>(gradient->GetSpreadMethod()), 0, nullptr));
#else
        fillPaint_.setShader(SkGradientShader::MakeLinear(pts.data(), colors.data(), pos.data(), gradientColors.size(),
            static_cast<SkTileMode>(gradient->GetSpreadMethod()), 0, nullptr));
#endif
    }
    if (gradient->GetType() == GradientType::RADIAL) {
        auto info = gradient->GetRadialGradientInfo();
        auto center = SkPoint::Make(static_cast<SkScalar>(info.cx), static_cast<SkScalar>(info.cy));
        auto focal = SkPoint::Make(static_cast<SkScalar>(info.fx), static_cast<SkScalar>(info.fx));
#ifdef USE_SYSTEM_SKIA
        if (center == focal) {
            fillPaint_.setShader(
                SkGradientShader::MakeRadial(center, static_cast<SkScalar>(info.r), colors.data(), pos.data(),
                    gradientColors.size(), static_cast<SkShader::TileMode>(gradient->GetSpreadMethod()), 0, nullptr));
        } else {
            fillPaint_.setShader(SkGradientShader::MakeTwoPointConical(focal, 0, center, static_cast<SkScalar>(info.r),
                colors.data(), pos.data(), gradientColors.size(),
                static_cast<SkShader::TileMode>(gradient->GetSpreadMethod()), 0, nullptr));
        }
#else
        if (center == focal) {
            fillPaint_.setShader(SkGradientShader::MakeRadial(center, static_cast<SkScalar>(info.r), colors.data(),
                pos.data(), gradientColors.size(), static_cast<SkTileMode>(gradient->GetSpreadMethod()), 0, nullptr));
        } else {
            fillPaint_.setShader(SkGradientShader::MakeTwoPointConical(focal, 0, center, static_cast<SkScalar>(info.r),
                colors.data(), pos.data(), gradientColors.size(), static_cast<SkTileMode>(gradient->GetSpreadMethod()),
                0, nullptr));
        }
#endif
    }
#else
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
        fillBrush_.SetShaderEffect(RSRecordingShaderEffect::CreateLinearGradient(pts[0], pts[1], colors, pos,
            static_cast<RSTileMode>(gradient->GetSpreadMethod())));
    }
    if (gradient->GetType() == GradientType::RADIAL) {
        auto info = gradient->GetRadialGradientInfo();
        auto center = RSPoint(static_cast<RSScalar>(info.cx), static_cast<RSScalar>(info.cy));
        auto focal = RSPoint(static_cast<RSScalar>(info.fx), static_cast<RSScalar>(info.fx));
        if (center == focal) {
            fillBrush_.SetShaderEffect(RSRecordingShaderEffect::CreateRadialGradient(center,
                static_cast<RSScalar>(info.r), colors, pos, static_cast<RSTileMode>(gradient->GetSpreadMethod())));
        } else {
            fillBrush_.SetShaderEffect(RSRecordingShaderEffect::CreateTwoPointConical(focal, 0, center,
                static_cast<RSScalar>(info.r), colors, pos, static_cast<RSTileMode>(gradient->GetSpreadMethod())));
        }
    }
#endif
}

bool SvgGraphic::UpdateStrokeStyle(bool antiAlias)
{
    const auto& strokeState = declaration_->GetStrokeState();
    if (strokeState.GetColor() == Color::TRANSPARENT) {
        return false;
    }
    if (!GreatNotEqual(strokeState.GetLineWidth().Value(), 0.0)) {
        return false;
    }
#ifndef USE_ROSEN_DRAWING
    strokePaint_.setStyle(SkPaint::Style::kStroke_Style);
    double curOpacity = strokeState.GetOpacity().GetValue() * opacity_ * (1.0f / UINT8_MAX);
    strokePaint_.setColor(strokeState.GetColor().BlendOpacity(curOpacity).GetValue());
    if (strokeState.GetLineCap() == LineCapStyle::ROUND) {
        strokePaint_.setStrokeCap(SkPaint::Cap::kRound_Cap);
    } else if (strokeState.GetLineCap() == LineCapStyle::SQUARE) {
        strokePaint_.setStrokeCap(SkPaint::Cap::kSquare_Cap);
    } else {
        strokePaint_.setStrokeCap(SkPaint::Cap::kButt_Cap);
    }
    if (strokeState.GetLineJoin() == LineJoinStyle::ROUND) {
        strokePaint_.setStrokeJoin(SkPaint::Join::kRound_Join);
    } else if (strokeState.GetLineJoin() == LineJoinStyle::BEVEL) {
        strokePaint_.setStrokeJoin(SkPaint::Join::kBevel_Join);
    } else {
        strokePaint_.setStrokeJoin(SkPaint::Join::kMiter_Join);
    }
    strokePaint_.setStrokeWidth(static_cast<SkScalar>(strokeState.GetLineWidth().Value()));
    strokePaint_.setStrokeMiter(static_cast<SkScalar>(strokeState.GetMiterLimit()));
    strokePaint_.setAntiAlias(antiAlias);
#else
    double curOpacity = strokeState.GetOpacity().GetValue() * opacity_ * (1.0f / UINT8_MAX);
    strokePen_.SetColor(strokeState.GetColor().BlendOpacity(curOpacity).GetValue());
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
#endif
    UpdateLineDash();
    return true;
}
void SvgGraphic::UpdateLineDash()
{
    const auto& strokeState = declaration_->GetStrokeState();
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
        std::vector<RSScalar> intervals(lineDashState.size());
        for (size_t i = 0; i < lineDashState.size(); ++i) {
            intervals[i] = static_cast<RSScalar>(lineDashState[i]);
        }
        RSScalar phase = static_cast<RSScalar>(strokeState.GetLineDash().dashOffset);
        strokePen_.SetPathEffect(
            RSRecordingPathEffect::CreateDashPathEffect(intervals, phase));
#endif
    }
}

} // namespace OHOS::Ace::NG
