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
constexpr Dimension INDICATOR_PADDING_HOVER = 12.0_vp;
constexpr float INDICATOR_ZOOM_IN_SCALE = 1.33f;
constexpr float INDICATOR_ZOOM_IN_SCALE_DEFAULT = 1.0f;

} // namespace

CanvasDrawFunction SwiperIndicatorPaintMethod::GetContentDrawFunction(PaintWrapper* paintWrapper)
{
    CHECK_NULL_RETURN(paintWrapper, nullptr);
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
        CHECK_NULL_VOID_NOLOG(swiper_);
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

    auto pipeline = PipelineBase::GetCurrentContext();
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

    auto indicatorPadding = INDICATOR_PADDING_DEFAULT;
    auto zoomInScale = INDICATOR_ZOOM_IN_SCALE_DEFAULT;
    if (isHover_ || isPressed_) {
        zoomInScale = INDICATOR_ZOOM_IN_SCALE;
        indicatorPadding = INDICATOR_PADDING_HOVER;
    }
    auto radius = userSize / 2.0;
    auto selectedSize = userSize * 2.0f;
    bool hasIndicatorHovered =
        HasIndicatorHovered(userSize, indicatorSize, zoomInScale, indicatorPadding.ConvertToPx());

    OffsetF center = OffsetF(static_cast<float>(indicatorPadding.ConvertToPx() + radius * zoomInScale),
        static_cast<float>(indicatorSize / 2.0));
    auto unselectedColor = paintProperty->GetColor().value_or(swiperTheme->GetColor());
    auto selectedColor = paintProperty->GetSelectedColorValue(swiperTheme->GetSelectedColor());

    for (int32_t i = 0; i < itemCount_; i++) {
        if (i != currentIndex_) {
            PaintUnselectedIndicator(canvas, center, unselectedColor, radius, zoomInScale, hasIndicatorHovered);
            center += OffsetF(static_cast<float>(INDICATOR_ITEM_SPACE.ConvertToPx() + userSize * zoomInScale), 0.0);
            continue;
        }

        PaintSelectedIndicator(canvas, center, selectedColor, userSize, zoomInScale, hasIndicatorHovered);
        center += OffsetF(static_cast<float>(INDICATOR_ITEM_SPACE.ConvertToPx() + selectedSize * zoomInScale), 0.0);
    }
}

void SwiperIndicatorPaintMethod::PaintUnselectedIndicator(RSCanvas& canvas, const OffsetF& center, const Color& color,
    double radius, double zoomInScale, bool hasIndicatorHovered)
{
    RSBrush brush;
    brush.SetColor(ToRSColor(color));
    canvas.AttachBrush(brush);
    rosen::Point point;
    if (axis_ == Axis::HORIZONTAL) {
        point.SetX(center.GetX());
        point.SetY(center.GetY());
    } else {
        point.SetX(center.GetY());
        point.SetY(center.GetX());
    }

    if (hasIndicatorHovered) {
        if (IsIndicatorPointHovered(point.GetX(), point.GetY(), static_cast<float>(radius * zoomInScale))) {
            zoomInScale = INDICATOR_ZOOM_IN_SCALE;
        } else {
            zoomInScale = INDICATOR_ZOOM_IN_SCALE_DEFAULT;
        }
    }

    canvas.DrawCircle(point, radius * zoomInScale);
}

void SwiperIndicatorPaintMethod::PaintSelectedIndicator(RSCanvas& canvas, const OffsetF& center, const Color& color,
    double userSize, double zoomInScale, bool hasIndicatorHovered)
{
    auto radius = userSize / 2.0;
    auto selectedSize = userSize * 2.0f;
    RSBrush brush;
    brush.SetColor(ToRSColor(color));
    canvas.AttachBrush(brush);
    Offset selectOffset;
    if (axis_ == Axis::HORIZONTAL) {
        selectOffset.SetX(center.GetX() - radius * zoomInScale);
        selectOffset.SetY(center.GetY() - radius * zoomInScale);
    } else {
        selectOffset.SetX(center.GetY() - radius * zoomInScale);
        selectOffset.SetY(center.GetX() - radius * zoomInScale);
    }

    if (hasIndicatorHovered) {
        auto rectWidth = axis_ == Axis::HORIZONTAL ? selectedSize * zoomInScale : userSize * zoomInScale;
        auto rectHeight = axis_ == Axis::HORIZONTAL ? userSize * zoomInScale : selectedSize * zoomInScale;
        RectF selectedRect(selectOffset.GetX(), selectOffset.GetY(), rectWidth, rectHeight);
        if (selectedRect.IsInRegion(hoverPoint_)) {
            zoomInScale = INDICATOR_ZOOM_IN_SCALE;
        } else {
            zoomInScale = INDICATOR_ZOOM_IN_SCALE_DEFAULT;
        }
    }

    if (axis_ == Axis::HORIZONTAL) {
        selectOffset.SetX(center.GetX() - radius * zoomInScale);
        selectOffset.SetY(center.GetY() - radius * zoomInScale);
    } else {
        selectOffset.SetX(center.GetY() - radius * zoomInScale);
        selectOffset.SetY(center.GetX() - radius * zoomInScale);
    }

    auto rectWidth = axis_ == Axis::HORIZONTAL ? selectedSize * zoomInScale + selectOffset.GetX()
                                               : userSize * zoomInScale + selectOffset.GetX();
    auto rectHeight = axis_ == Axis::HORIZONTAL ? userSize * zoomInScale + selectOffset.GetY()
                                                : selectedSize * zoomInScale + selectOffset.GetY();
    canvas.DrawRoundRect({ { selectOffset.GetX(), selectOffset.GetY(), rectWidth, rectHeight }, radius * zoomInScale,
        radius * zoomInScale });
}

bool SwiperIndicatorPaintMethod::IsIndicatorPointHovered(float x, float y, float radius)
{
    return hoverPoint_.GetX() >= (x - radius) && hoverPoint_.GetX() <= (x + radius) &&
           hoverPoint_.GetY() >= (y - radius) && hoverPoint_.GetY() <= (y + radius);
}

bool SwiperIndicatorPaintMethod::HasIndicatorHovered(
    double userSize, float indicatorSize, double zoomInScale, double indicatorPaddingPX)
{
    auto radius = userSize / 2.0;
    auto selectedSize = userSize * 2.0f;
    OffsetF center =
        OffsetF(static_cast<float>(indicatorPaddingPX + radius * zoomInScale), static_cast<float>(indicatorSize / 2.0));
    for (int32_t i = 0; i < itemCount_; i++) {
        if (i != currentIndex_) {
            rosen::Point point;
            if (axis_ == Axis::HORIZONTAL) {
                point.SetX(center.GetX());
                point.SetY(center.GetY());
            } else {
                point.SetX(center.GetY());
                point.SetY(center.GetX());
            }

            if (isHover_ && IsIndicatorPointHovered(point.GetX(), point.GetY(), radius * zoomInScale)) {
                return true;
            }

            center += OffsetF(static_cast<float>(INDICATOR_ITEM_SPACE.ConvertToPx() + userSize * zoomInScale), 0.0f);
            continue;
        }
        Offset selectOffset;
        if (axis_ == Axis::HORIZONTAL) {
            selectOffset.SetX(center.GetX() - radius * zoomInScale);
            selectOffset.SetY(center.GetY() - radius * zoomInScale);
        } else {
            selectOffset.SetX(center.GetY() - radius * zoomInScale);
            selectOffset.SetY(center.GetX() - radius * zoomInScale);
        }
        auto rectWidth = axis_ == Axis::HORIZONTAL ? selectedSize * zoomInScale : userSize * zoomInScale;
        auto rectHeight = axis_ == Axis::HORIZONTAL ? userSize * zoomInScale : selectedSize * zoomInScale;

        RectF selectedRect(selectOffset.GetX(), selectOffset.GetY(), rectWidth, rectHeight);
        if (isHover_ && selectedRect.IsInRegion(hoverPoint_)) {
            return true;
        }
        center += OffsetF(static_cast<float>(INDICATOR_ITEM_SPACE.ConvertToPx() + selectedSize * zoomInScale), 0.0f);
    }

    return false;
}

} // namespace OHOS::Ace::NG
