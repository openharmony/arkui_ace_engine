/*
 * Copyright (c) 2022-2023 Huawei Device Co., Ltd.
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

#include <valarray>

#include "core/components/common/layout/constants.h"
#include "core/components/common/properties/color.h"
#include "core/components/swiper/render_swiper.h"
#include "core/components_ng/pattern/swiper/swiper_layout_property.h"
#include "core/components_ng/render/paint_property.h"
#include "core/pipeline/pipeline_base.h"

namespace OHOS::Ace::NG {

namespace {
// for indicator
constexpr Dimension INDICATOR_ITEM_SPACE = 8.0_vp;
constexpr Dimension INDICATOR_PADDING_DEFAULT = 13.0_vp;
constexpr Dimension INDICATOR_PADDING_HOVER = 12.0_vp;
constexpr float INDICATOR_ZOOM_IN_SCALE = 1.33f;
constexpr float INDICATOR_ZOOM_IN_SCALE_DEFAULT = 1.0f;

constexpr float BLACK_POINT_CENTER_BEZIER_CURVE_VELOCITY = 0.4f;
constexpr float LONG_POINT_LEFT_CENTER_BEZIER_CURVE_VELOCITY = 0.2f;
constexpr float LONG_POINT_RIGHT_CENTER_BEZIER_CURVE_VELOCITY = 1.0f;
constexpr float CENTER_BEZIER_CURVE_MASS = 0.0f;
constexpr float CENTER_BEZIER_CURVE_STIFFNESS = 1.0f;
constexpr float CENTER_BEZIER_CURVE_DAMPING = 1.0f;
} // namespace

void SwiperIndicatorPaintMethod::UpdateContentModifier(PaintWrapper* paintWrapper)
{
    CHECK_NULL_VOID(swiperIndicatorModifier_);
    CHECK_NULL_VOID(paintWrapper);

    auto pipelineContext = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipelineContext);
    auto swiperTheme = pipelineContext->GetTheme<SwiperIndicatorTheme>();
    CHECK_NULL_VOID(swiperTheme);

    const auto& geometryNode = paintWrapper->GetGeometryNode();
    CHECK_NULL_VOID(geometryNode);

    auto paintProperty = DynamicCast<SwiperIndicatorPaintProperty>(paintWrapper->GetPaintProperty());
    swiperIndicatorModifier_->SetAxis(axis_);
    swiperIndicatorModifier_->SetUnselectedColor(paintProperty->GetColorValue(swiperTheme->GetColor()));
    swiperIndicatorModifier_->SetSelectedColor(paintProperty->GetSelectedColorValue(swiperTheme->GetSelectedColor()));
    swiperIndicatorModifier_->SetHoverPoint(hoverPoint_);
    swiperIndicatorModifier_->SetIndicatorMask(paintProperty->GetIndicatorMaskValue(false));
    swiperIndicatorModifier_->SetOffset(geometryNode->GetContentOffset());
    // Update center coordinates
    CalculatePointRadius(paintWrapper);
    swiperIndicatorModifier_->UpdatePointRadius(pointRadius_);
    swiperIndicatorModifier_->UpdateHoverPointRadius(pointRadius_, hoverPointRadius_);
    CalculatePointCenterX(paintWrapper);
    swiperIndicatorModifier_->UpdateVectorBlackPointCenterX(vectorBlackPointCenterX_);
    swiperIndicatorModifier_->UpdateLongPointLeftCenterX(longPointLeftCenterX_, turnPageRate_ >= 1.0f);
    swiperIndicatorModifier_->UpdateLongPointRightCenterX(longPointRightCenterX_, turnPageRate_ <= -1.0f);
    CalculatePointCenterY(paintWrapper);
    swiperIndicatorModifier_->UpdateCenterY(centerY_);
}

void SwiperIndicatorPaintMethod::CalculatePointCenterX(const PaintWrapper* paintWrapper)
{
    CHECK_NULL_VOID(paintWrapper);
    auto indicatorPadding = static_cast<float>(
        ((isHover_ || isPressed_) ? INDICATOR_PADDING_HOVER : INDICATOR_PADDING_DEFAULT).ConvertToPx());
    float diameter = pointRadius_ * 2;
    // Calculate the data required for the current pages
    LinearVector<float> startVectorBlackPointCenterX(itemCount_);
    float startLongPointLeftCenterX = 0.0f;
    float startLongPointRightCenterX = 0.0f;
    float startCenterX = indicatorPadding + pointRadius_;
    int32_t startCurrentIndex = currentIndex_;
    // Calculate the data required for subsequent pages
    LinearVector<float> endVectorBlackPointCenterX(itemCount_);
    float endLongPointLeftCenterX = 0.0f;
    float endLongPointRightCenterX = 0.0f;
    float endCenterX = indicatorPadding + pointRadius_;
    int32_t endCurrentIndex = turnPageRate_ == 0.0f || turnPageRate_ <= -1.0f || turnPageRate_ >= 1.0f
                                  ? endCurrentIndex = currentIndex_
                                  : (turnPageRate_ < 0.0f ? currentIndex_ + 1 : currentIndex_ - 1);
    if (endCurrentIndex == -1) {
        endCurrentIndex = itemCount_ - 1;
    } else if (endCurrentIndex == itemCount_) {
        endCurrentIndex = 0;
    }

    for (int32_t i = 0; i < itemCount_; ++i) {
        if (i != startCurrentIndex) {
            startVectorBlackPointCenterX[i] = startCenterX;
            startCenterX += static_cast<float>(INDICATOR_ITEM_SPACE.ConvertToPx()) + diameter;
        } else {
            startVectorBlackPointCenterX[i] = startCenterX + pointRadius_;
            startLongPointLeftCenterX = startCenterX;
            startLongPointRightCenterX = startCenterX + diameter;
            startCenterX += static_cast<float>(INDICATOR_ITEM_SPACE.ConvertToPx()) + diameter * 2;
        }
        if (i != endCurrentIndex) {
            endVectorBlackPointCenterX[i] = endCenterX;
            endCenterX += static_cast<float>(INDICATOR_ITEM_SPACE.ConvertToPx()) + diameter;
        } else {
            endVectorBlackPointCenterX[i] = endCenterX + pointRadius_;
            endLongPointLeftCenterX = endCenterX;
            endLongPointRightCenterX = endCenterX + diameter;
            endCenterX += static_cast<float>(INDICATOR_ITEM_SPACE.ConvertToPx()) + diameter * 2;
        }
    }
    float blackPointCenterMoveRate = CubicCurve(BLACK_POINT_CENTER_BEZIER_CURVE_VELOCITY, CENTER_BEZIER_CURVE_MASS,
        CENTER_BEZIER_CURVE_STIFFNESS, CENTER_BEZIER_CURVE_DAMPING)
                                         .MoveInternal(std::abs(turnPageRate_));
    float longPointLeftCenterMoveRate = CubicCurve(turnPageRate_ > 0 ? LONG_POINT_LEFT_CENTER_BEZIER_CURVE_VELOCITY
                                                                     : LONG_POINT_RIGHT_CENTER_BEZIER_CURVE_VELOCITY,
        CENTER_BEZIER_CURVE_MASS, CENTER_BEZIER_CURVE_STIFFNESS, CENTER_BEZIER_CURVE_DAMPING)
                                            .MoveInternal(std::abs(turnPageRate_));
    float longPointRightCenterMoveRate = CubicCurve(turnPageRate_ > 0 ? LONG_POINT_RIGHT_CENTER_BEZIER_CURVE_VELOCITY
                                                                      : LONG_POINT_LEFT_CENTER_BEZIER_CURVE_VELOCITY,
        CENTER_BEZIER_CURVE_MASS, CENTER_BEZIER_CURVE_STIFFNESS, CENTER_BEZIER_CURVE_DAMPING)
                                             .MoveInternal(std::abs(turnPageRate_));
    vectorBlackPointCenterX_.resize(itemCount_);
    for (int32_t i = 0; i < itemCount_; ++i) {
        vectorBlackPointCenterX_[i] =
            startVectorBlackPointCenterX[i] +
            (endVectorBlackPointCenterX[i] - startVectorBlackPointCenterX[i]) * blackPointCenterMoveRate;
    }
    longPointLeftCenterX_ =
        startLongPointLeftCenterX + (endLongPointLeftCenterX - startLongPointLeftCenterX) * longPointLeftCenterMoveRate;
    longPointRightCenterX_ = startLongPointRightCenterX +
                             (endLongPointRightCenterX - startLongPointRightCenterX) * longPointRightCenterMoveRate;
}

void SwiperIndicatorPaintMethod::CalculatePointCenterY(const PaintWrapper* paintWrapper)
{
    CHECK_NULL_VOID(paintWrapper);
    const auto& geometryNode = paintWrapper->GetGeometryNode();
    CHECK_NULL_VOID(geometryNode);
    SizeF contentSize = geometryNode->GetFrameSize();
    auto indicatorSize = axis_ == Axis::HORIZONTAL ? contentSize.Height() : contentSize.Width();
    centerY_ = indicatorSize / 2;
}

void SwiperIndicatorPaintMethod::CalculatePointRadius(const PaintWrapper* paintWrapper)
{
    CHECK_NULL_VOID(paintWrapper);
    auto paintProperty = DynamicCast<SwiperIndicatorPaintProperty>(paintWrapper->GetPaintProperty());
    CHECK_NULL_VOID(paintProperty);
    auto pipelineContext = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipelineContext);
    auto swiperTheme = pipelineContext->GetTheme<SwiperIndicatorTheme>();
    CHECK_NULL_VOID(swiperTheme);
    float zoomInScale = (isHover_ || isPressed_) ? INDICATOR_ZOOM_IN_SCALE : INDICATOR_ZOOM_IN_SCALE_DEFAULT;
    float diameter = static_cast<float>(paintProperty->GetSizeValue(swiperTheme->GetSize()).ConvertToPx());
    pointRadius_ = diameter / 2 * zoomInScale;
    hoverPointRadius_ = pointRadius_ * INDICATOR_ZOOM_IN_SCALE;
}

} // namespace OHOS::Ace::NG
