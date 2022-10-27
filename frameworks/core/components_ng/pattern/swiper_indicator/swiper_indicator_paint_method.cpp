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

#include "core/components_ng/pattern/swiper_indicator/swiper_indicator_paint_method.h"

#include "third_party/skia/include/effects/SkGradientShader.h"

#include "base/geometry/ng/offset_t.h"
#include "base/memory/referenced.h"
#include "base/utils/utils.h"
#include "core/components/checkable/checkable_theme.h"
#include "core/components/common/layout/constants.h"
#include "core/components/common/properties/color.h"
#include "core/components/swiper/render_swiper.h"
#include "core/components_ng/pattern/swiper/swiper_layout_property.h"
#include "core/components_ng/render/drawing_prop_convertor.h"
#include "core/components_ng/render/paint_property.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {

namespace {
// for indicator
constexpr Dimension INDICATOR_POINT_PADDING_TOP = 9.0_vp;
constexpr uint32_t GRADIENT_COLOR_SIZE = 3;
} // namespace

CanvasDrawFunction SwiperIndicatorPaintMethod::GetContentDrawFunction(PaintWrapper* paintWrapper)
{
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_RETURN(pipeline, nullptr);
    scale_ = pipeline->GetDipScale();
    auto paintProperty = DynamicCast<SwiperIndicatorPaintProperty>(paintWrapper->GetPaintProperty());
    CHECK_NULL_RETURN(paintProperty, nullptr);

    auto size = paintProperty->GetSize();
    auto geometryNode = paintWrapper->GetGeometryNode();
    CHECK_NULL_RETURN(geometryNode, nullptr);

    SizeF contentSize;
    if (size.has_value()) {
        contentSize.SetHeight(static_cast<float>(size->ConvertToPx()));
    }
    auto contentOffset = geometryNode->GetContentOffset();

    auto paintFunc = [weak = WeakClaim(this), paintProperty, contentSize, showIndicator = showIndicator_,
                         contentOffset](RSCanvas& canvas) {
        auto swiper_ = weak.Upgrade();
        if (showIndicator && swiper_) {
            if (paintProperty->GetIndicatorMaskValue(false)) {
                swiper_->PaintMask(canvas, paintProperty, contentSize, contentOffset);
            }
            swiper_->PaintContent(canvas, paintProperty, contentSize, contentOffset);
        }
    };
    return paintFunc;
}

void SwiperIndicatorPaintMethod::PaintMask(RSCanvas& canvas, RefPtr<SwiperIndicatorPaintProperty> paintProperty,
    SizeF contentSize, OffsetF contentOffset) const
{
    SkPaint paint;
    paint.setAntiAlias(true);
    canvas.Save();

    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    std::vector<GradientColor> gradientColors = std::vector<GradientColor>(GRADIENT_COLOR_SIZE);
    gradientColors[0].SetColor(Color(0x00000000));
    gradientColors[1].SetColor(Color(0xff000000));
    gradientColors[2].SetColor(Color(0xff000000));
    SkPoint pts[2] = { SkPoint::Make(0.0f, 0.0f), SkPoint::Make(0.0f, 0.0f) };
    if (axis_ == Axis::HORIZONTAL) {
        pts[0] = SkPoint::Make(SkDoubleToScalar(contentOffset.GetX()),
            SkDoubleToScalar(contentOffset.GetY() - pipeline->NormalizeToPx(9.0_vp)));
        pts[1] = SkPoint::Make(SkDoubleToScalar(contentOffset.GetX()),
            SkDoubleToScalar(contentOffset.GetY() + pipeline->NormalizeToPx(15.0_vp)));
    } else {
        pts[0] = SkPoint::Make(SkDoubleToScalar(contentOffset.GetX() - pipeline->NormalizeToPx(9.0_vp)),
            SkDoubleToScalar(contentOffset.GetY()));
        pts[1] = SkPoint::Make(SkDoubleToScalar(contentOffset.GetX() + pipeline->NormalizeToPx(15.0_vp)),
            SkDoubleToScalar(contentOffset.GetY()));
    }
    LOGD("gradient--beginPoint x: %{public}f, y: %{public}f", pts[0].x(), pts[0].y());
    LOGD("gradient--endPoint x: %{public}f, y: %{public}f", pts[1].x(), pts[1].y());
    SkColor colors[gradientColors.size()];
    for (uint32_t i = 0; i < gradientColors.size(); ++i) {
        const auto& gradientColor = gradientColors[i];
        colors[i] = gradientColor.GetColor().GetValue();
    }
    const float pos[] = { 0.0f, 0.75f, 1.0f };

#ifdef USE_SYSTEM_SKIA
    paint.setShader(SkGradientShader::MakeLinear(pts, colors, pos, gradientColors.size(), SkShader::kClamp_TileMode));
#else
    paint.setShader(SkGradientShader::MakeLinear(pts, colors, pos, gradientColors.size(), SkTileMode::kClamp));
#endif
    auto contentOffsetX = static_cast<float>(contentOffset.GetX());
    auto contentOffsetY = static_cast<float>(contentOffset.GetY());
    if (axis_ == Axis::HORIZONTAL) {
        RSRect rRect(contentOffsetX, contentOffsetY - pipeline->NormalizeToPx(9.0_vp), contentOffsetX,
            contentOffsetY + pipeline->NormalizeToPx(15.0_vp));
        canvas.DrawRect(rRect);
    } else {
        RSRect rRect(contentOffsetX - pipeline->NormalizeToPx(9.0_vp), contentOffsetY,
            contentOffsetX + pipeline->NormalizeToPx(15.0_vp), contentOffsetY);
        canvas.DrawRect(rRect);
    }
}

void SwiperIndicatorPaintMethod::PaintContent(
    RSCanvas& canvas, RefPtr<SwiperIndicatorPaintProperty> paintProperty, SizeF contentSize, OffsetF contentOffset)
{
    auto pipelineContext = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipelineContext);
    auto swiperTheme = pipelineContext->GetTheme<SwitchTheme>();
    CHECK_NULL_VOID(swiperTheme);
    auto height = contentSize.Height();
    float radius = 0.0f;
    radius = height / 2.0f; // for radius
    auto hoverRadius_ = radius - radiusGap_;

    IndicatorProperties indicatorProperties = PrepareIndicatorProperties(paintProperty);
    Offset center = indicatorProperties.centerPadding;
    int32_t targetIndex = GetCurrentIndex();
    for (int32_t i = 0; i < itemCount_; i++) {
        if (i != targetIndex) {
            center += indicatorProperties.normalPaddingStart;
            RSBrush brush;
            brush.SetColor(ToRSColor(paintProperty->GetColor().value_or(swiperTheme->GetPointColor())));
            canvas.AttachBrush(brush);
            rosen::Point point;
            if (axis_ == Axis::HORIZONTAL) {
                point.SetX(center.GetX() + contentOffset.GetX());
                point.SetY(center.GetY() + contentOffset.GetY() + radius);
            } else {
                point.SetX(contentOffset.GetX());
                point.SetY(center.GetY() + contentOffset.GetY() + radius);
            }

            canvas.DrawCircle(point, hoverRadius_);
            center += indicatorProperties.normalPaddingEnd;
        } else {
            center += indicatorProperties.normalPaddingStart;
            RSBrush brush;
            brush.SetColor(ToRSColor(paintProperty->GetSelectedColor().value_or(swiperTheme->GetFocusColor())));
            canvas.AttachBrush(brush);
            rosen::Point point;
            if (axis_ == Axis::HORIZONTAL) {
                point.SetX(center.GetX() + contentOffset.GetX());
                point.SetY(center.GetY() + contentOffset.GetY() + radius);
            } else {
                point.SetX(contentOffset.GetX());
                point.SetY(center.GetY() + contentOffset.GetY() + radius);
            }

            canvas.DrawCircle(point, hoverRadius_);
            center += indicatorProperties.normalPaddingEnd;
        }
    }
}

SwiperIndicatorPaintMethod::IndicatorProperties SwiperIndicatorPaintMethod::PrepareIndicatorProperties(
    RefPtr<SwiperIndicatorPaintProperty> paintProperty) const
{
    auto pipeline = PipelineContext::GetCurrentContext();
    auto swiperTheme = pipeline->GetTheme<SwiperIndicatorTheme>();
    CHECK_NULL_RETURN(pipeline, IndicatorProperties(Offset(0.0, 0.0), Offset(0.0, 0.0), Offset(0.0, 0.0),
                                    Offset(0.0, 0.0), Offset(0.0, 0.0), 0.0, 0.0, 0.0, 0.0, 0.0));
    uint32_t normalColor = paintProperty->GetColor()->GetValue();
    uint32_t selectedColor = paintProperty->GetSelectedColor()->GetValue();
    double normalPointRadius = pipeline->NormalizeToPx(paintProperty->GetSizeValue(Dimension(0.0))) / 2.0;
    double selectedPointRadius = INDICATOR_POINT_PADDING_TOP.ConvertToPx();
    double indicatorPointPadding = swiperTheme->GetIndicatorPointPadding().Value() * scale_;
    if (axis_ == Axis::HORIZONTAL) {
        return IndicatorProperties(Offset(normalPointRadius, 0.0),
            Offset(normalPointRadius + indicatorPointPadding, 0.0), Offset(selectedPointRadius, 0.0),
            Offset(selectedPointRadius + indicatorPointPadding, 0.0), Offset(0.0, selectedPointRadius), normalColor,
            selectedColor, normalPointRadius, selectedPointRadius, indicatorPointPadding);
    } else {
        return IndicatorProperties(Offset(0.0, normalPointRadius),
            Offset(0.0, normalPointRadius + indicatorPointPadding), Offset(0.0, selectedPointRadius),
            Offset(0.0, selectedPointRadius + indicatorPointPadding), Offset(selectedPointRadius, 0.0), normalColor,
            selectedColor, normalPointRadius, selectedPointRadius, indicatorPointPadding);
    }
}

} // namespace OHOS::Ace::NG