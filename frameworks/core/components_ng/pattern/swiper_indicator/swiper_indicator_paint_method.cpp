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
#include "core/pipeline/pipeline_base.h"

namespace OHOS::Ace::NG {

namespace {
// for indicator
constexpr uint32_t GRADIENT_COLOR_SIZE = 3;
constexpr Dimension INDICATOR_ITEM_SPACE = 8.0_vp;
constexpr Dimension INDICATOR_PADDING_DEFAULT = 13.0_vp;

} // namespace

CanvasDrawFunction SwiperIndicatorPaintMethod::GetContentDrawFunction(PaintWrapper* paintWrapper)
{
    auto paintProperty = DynamicCast<SwiperIndicatorPaintProperty>(paintWrapper->GetPaintProperty());
    CHECK_NULL_RETURN(paintProperty, nullptr);
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_RETURN(pipeline, nullptr);
    auto theme = pipeline->GetTheme<SwiperIndicatorTheme>();
    const auto& geometryNode = paintWrapper->GetGeometryNode();
    CHECK_NULL_RETURN(geometryNode, nullptr);
    SizeF contentSize = geometryNode->GetFrameSize();
    auto contentOffset = geometryNode->GetContentOffset();

    auto paintFunc = [weak = WeakClaim(this), paintProperty, contentSize, contentOffset](RSCanvas& canvas) {
        auto swiper_ = weak.Upgrade();
        CHECK_NULL_VOID(swiper_);
        if (paintProperty->GetIndicatorMaskValue(false)) {
            swiper_->PaintMask(canvas, paintProperty, contentSize, contentOffset);
        }
        swiper_->PaintContent(canvas, paintProperty, contentSize);
    };
    return paintFunc;
}

void SwiperIndicatorPaintMethod::PaintMask(
    RSCanvas& canvas, RefPtr<SwiperIndicatorPaintProperty> paintProperty, SizeF contentSize, OffsetF contentOffset)
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
    RSCanvas& canvas, const RefPtr<SwiperIndicatorPaintProperty>& paintProperty, SizeF contentSize)
{
    auto pipelineContext = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipelineContext);
    auto swiperTheme = pipelineContext->GetTheme<SwiperIndicatorTheme>();
    CHECK_NULL_VOID(swiperTheme);
    auto indicatorSize = axis_ == Axis::HORIZONTAL ? contentSize.Height() : contentSize.Width();
    auto userSize = paintProperty->GetSizeValue(swiperTheme->GetSize()).ConvertToPx();
    if (LessNotEqual(userSize, 0.0)) {
        userSize = swiperTheme->GetSize().ConvertToPx();
    }
    auto radius = userSize / 2.0;
    auto selectedSize = userSize * 2.0f;

    Offset center = Offset(INDICATOR_PADDING_DEFAULT.ConvertToPx() + radius, indicatorSize / 2.0);
    for (int32_t i = 0; i < itemCount_; i++) {
        if (i != currentIndex_) {
            RSBrush brush;
            brush.SetColor(ToRSColor(paintProperty->GetColor().value_or(swiperTheme->GetColor())));
            canvas.AttachBrush(brush);
            rosen::Point point;
            if (axis_ == Axis::HORIZONTAL) {
                point.SetX(center.GetX());
                point.SetY(center.GetY());
            } else {
                point.SetX(center.GetY());
                point.SetY(center.GetX());
            }

            canvas.DrawCircle(point, radius);
            center += Offset(INDICATOR_ITEM_SPACE.ConvertToPx() + userSize, 0.0);
            continue;
        }
        RSBrush brush;
        brush.SetColor(ToRSColor(paintProperty->GetSelectedColorValue(swiperTheme->GetSelectedColor())));
        canvas.AttachBrush(brush);
        Offset selectOffset;
        if (axis_ == Axis::HORIZONTAL) {
            selectOffset.SetX(center.GetX() - radius);
            selectOffset.SetY(center.GetY() - radius);
        } else {
            selectOffset.SetX(center.GetY() - radius);
            selectOffset.SetY(center.GetX() - radius);
        }
        auto rectWidth =
            axis_ == Axis::HORIZONTAL ? selectedSize + selectOffset.GetX() : userSize + selectOffset.GetX();
        auto rectHeight =
            axis_ == Axis::HORIZONTAL ? userSize + selectOffset.GetY() : selectedSize + selectOffset.GetY();
        canvas.DrawRoundRect({ { selectOffset.GetX(), selectOffset.GetY(), rectWidth, rectHeight }, radius, radius });
        center += Offset(INDICATOR_ITEM_SPACE.ConvertToPx() + selectedSize, 0.0);
    }
}

} // namespace OHOS::Ace::NG