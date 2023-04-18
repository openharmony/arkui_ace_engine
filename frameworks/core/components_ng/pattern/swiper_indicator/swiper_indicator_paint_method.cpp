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
constexpr float HALF = 0.5f;
constexpr float DOUBLE = 2.0f;
// for indicator
constexpr Dimension INDICATOR_ITEM_SPACE = 8.0_vp;
constexpr Dimension INDICATOR_PADDING_DEFAULT = 13.0_vp;
constexpr Dimension INDICATOR_PADDING_HOVER = 12.0_vp;
constexpr float INDICATOR_ZOOM_IN_SCALE = 1.33f;

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
    swiperIndicatorModifier_->SetIndicatorMask(paintProperty->GetIndicatorMaskValue(false));
    swiperIndicatorModifier_->SetOffset(geometryNode->GetContentOffset());
    swiperIndicatorModifier_->SetIsHorizontal_(axis_ == Axis::HORIZONTAL);
    SizeF contentSize = geometryNode->GetFrameSize();
    centerY_ = (axis_ == Axis::HORIZONTAL ? contentSize.Height() : contentSize.Width()) * HALF;
    swiperIndicatorModifier_->SetCenterY(centerY_);

    if (isPressed_) {
        PaintPressIndicator(paintWrapper);
        swiperIndicatorModifier_->SetIsPressed(true);
    } else if (isHover_) {
        PaintHoverIndicator(paintWrapper);
        swiperIndicatorModifier_->SetIsHover(true);
    } else {
        PaintNormalIndicator(paintWrapper);
        swiperIndicatorModifier_->SetIsHover(false);
        swiperIndicatorModifier_->SetIsPressed(false);
    }
}

void SwiperIndicatorPaintMethod::PaintNormalIndicator(const PaintWrapper* paintWrapper)
{
    CHECK_NULL_VOID(paintWrapper);
    const auto& geometryNode = paintWrapper->GetGeometryNode();
    CHECK_NULL_VOID(geometryNode);
    auto paintProperty = DynamicCast<SwiperIndicatorPaintProperty>(paintWrapper->GetPaintProperty());
    CHECK_NULL_VOID(paintProperty);
    auto swiperTheme = GetSwiperIndicatorTheme();
    CHECK_NULL_VOID(swiperTheme);
    SizeF frameSize = geometryNode->GetFrameSize();

    float diameter = static_cast<float>(paintProperty->GetSizeValue(swiperTheme->GetSize()).ConvertToPx());
    float radius = diameter * HALF;
    CalculateNormalMargin(radius, frameSize);
    CalculatePointCenterX(radius, normalMargin_.GetX(), static_cast<float>(INDICATOR_PADDING_DEFAULT.ConvertToPx()),
        static_cast<float>(INDICATOR_ITEM_SPACE.ConvertToPx()), currentIndex_);

    if (swiperIndicatorModifier_->GetIsHover()) {
        swiperIndicatorModifier_->UpdateHoverToNormalPaintProperty(
            normalMargin_, radius, vectorBlackPointCenterX_, longPointCenterX_);
    } else if (swiperIndicatorModifier_->GetIsPressed()) {
        swiperIndicatorModifier_->UpdatePressToNormalPaintProperty(
            normalMargin_, radius, vectorBlackPointCenterX_, longPointCenterX_);
    } else {
        swiperIndicatorModifier_->UpdateNormalPaintProperty(
            normalMargin_, radius, vectorBlackPointCenterX_, longPointCenterX_);
    }
}

void SwiperIndicatorPaintMethod::PaintHoverIndicator(const PaintWrapper* paintWrapper)
{
    CHECK_NULL_VOID(paintWrapper);
    auto paintProperty = DynamicCast<SwiperIndicatorPaintProperty>(paintWrapper->GetPaintProperty());
    CHECK_NULL_VOID(paintProperty);
    auto swiperTheme = GetSwiperIndicatorTheme();
    CHECK_NULL_VOID(swiperTheme);
    float normalDiameter = static_cast<float>(paintProperty->GetSizeValue(swiperTheme->GetSize()).ConvertToPx());
    float radius = normalDiameter * HALF * INDICATOR_ZOOM_IN_SCALE;
    CalculatePointCenterX(radius, 0, static_cast<float>(INDICATOR_PADDING_HOVER.ConvertToPx()),
        static_cast<float>(INDICATOR_ITEM_SPACE.ConvertToPx()), currentIndex_);

    if (swiperIndicatorModifier_->GetIsPressed()) {
        swiperIndicatorModifier_->SetIsPressed(false);
        swiperIndicatorModifier_->UpdateHoverAndPressConversionPaintProperty();
    } else if (swiperIndicatorModifier_->GetIsHover()) {
        swiperIndicatorModifier_->UpdateHoverPaintProperty(radius, vectorBlackPointCenterX_, longPointCenterX_);
    } else {
        swiperIndicatorModifier_->UpdateNormalToHoverPaintProperty(radius, vectorBlackPointCenterX_, longPointCenterX_);
    }

    CalculateHoverIndex(radius);
    if (swiperIndicatorModifier_->GetNormalToHoverIndex() != hoverIndex_) {
        swiperIndicatorModifier_->SetHoverToNormalIndex(swiperIndicatorModifier_->GetNormalToHoverIndex());
        swiperIndicatorModifier_->UpdateHoverToNormalPointDilateRatio();
        swiperIndicatorModifier_->SetNormalToHoverIndex(hoverIndex_);
        swiperIndicatorModifier_->UpdateNormalToHoverPointDilateRatio();
    }
    if (mouseClickIndex_ && mouseClickIndex_ != currentIndex_) {
        CalculatePointCenterX(radius, 0, static_cast<float>(INDICATOR_PADDING_HOVER.ConvertToPx()),
            static_cast<float>(INDICATOR_ITEM_SPACE.ConvertToPx()), mouseClickIndex_.value());
        swiperIndicatorModifier_->UpdateAllPointCenterXAnimation(
            mouseClickIndex_ > currentIndex_, vectorBlackPointCenterX_, longPointCenterX_);
        longPointIsHover_ = true;
    }
    if (swiperIndicatorModifier_->GetLongPointIsHover() != longPointIsHover_) {
        swiperIndicatorModifier_->SetLongPointIsHover(longPointIsHover_);
        swiperIndicatorModifier_->UpdateLongPointDilateRatio();
    }
}

void SwiperIndicatorPaintMethod::PaintPressIndicator(const PaintWrapper* paintWrapper)
{
    CHECK_NULL_VOID(paintWrapper);
    auto paintProperty = DynamicCast<SwiperIndicatorPaintProperty>(paintWrapper->GetPaintProperty());
    CHECK_NULL_VOID(paintProperty);
    auto swiperTheme = GetSwiperIndicatorTheme();
    CHECK_NULL_VOID(swiperTheme);
    float normalDiameter = static_cast<float>(paintProperty->GetSizeValue(swiperTheme->GetSize()).ConvertToPx());
    float radius = normalDiameter * HALF * INDICATOR_ZOOM_IN_SCALE;
    CalculatePointCenterX(radius, 0, static_cast<float>(INDICATOR_PADDING_HOVER.ConvertToPx()),
        static_cast<float>(INDICATOR_ITEM_SPACE.ConvertToPx()), currentIndex_);
    if (swiperIndicatorModifier_->GetIsPressed()) {
        swiperIndicatorModifier_->UpdatePressPaintProperty(radius, vectorBlackPointCenterX_, longPointCenterX_);
    } else if (swiperIndicatorModifier_->GetIsHover()) {
        swiperIndicatorModifier_->SetIsPressed(true);
        swiperIndicatorModifier_->UpdateHoverAndPressConversionPaintProperty();
    } else {
        swiperIndicatorModifier_->UpdateNormalToPressPaintProperty(radius, vectorBlackPointCenterX_, longPointCenterX_);
    }
}

void SwiperIndicatorPaintMethod::CalculateNormalMargin(float radius, const SizeF& frameSize)
{
    float diameter = radius * DOUBLE;
    float allPointDiameterSum = diameter * static_cast<float>(itemCount_ + 1);
    auto allPointSpaceSum = static_cast<float>(INDICATOR_ITEM_SPACE.ConvertToPx() * (itemCount_ - 1));
    auto indicatorPadding = static_cast<float>(INDICATOR_PADDING_DEFAULT.ConvertToPx());
    float contentWidth = indicatorPadding + allPointDiameterSum + allPointSpaceSum + indicatorPadding;
    float contentHeight = indicatorPadding + diameter + indicatorPadding;
    float marginX = ((axis_ == Axis::HORIZONTAL ? frameSize.Width() : frameSize.Height()) - contentWidth) * HALF;
    float marginY = ((axis_ == Axis::HORIZONTAL ? frameSize.Height() : frameSize.Width()) - contentHeight) * HALF;
    normalMargin_.SetX(marginX);
    normalMargin_.SetY(marginY);
}

void SwiperIndicatorPaintMethod::CalculatePointCenterX(
    float radius, float margin, float padding, float space, int32_t index)
{
    float diameter = radius * DOUBLE;
    // Calculate the data required for the current pages
    LinearVector<float> startVectorBlackPointCenterX(itemCount_);
    float startLongPointLeftCenterX = 0.0f;
    float startLongPointRightCenterX = 0.0f;
    float startCenterX = margin + padding + radius;
    int32_t startCurrentIndex = index;
    // Calculate the data required for subsequent pages
    LinearVector<float> endVectorBlackPointCenterX(itemCount_);
    float endLongPointLeftCenterX = 0.0f;
    float endLongPointRightCenterX = 0.0f;
    float endCenterX = margin + padding + radius;
    int32_t endCurrentIndex = turnPageRate_ == 0.0f || turnPageRate_ <= -1.0f || turnPageRate_ >= 1.0f
                                  ? endCurrentIndex = index
                                  : (turnPageRate_ < 0.0f ? index + 1 : index - 1);
    if (endCurrentIndex == -1) {
        endCurrentIndex = itemCount_ - 1;
    } else if (endCurrentIndex == itemCount_) {
        endCurrentIndex = 0;
    }

    for (int32_t i = 0; i < itemCount_; ++i) {
        if (i != startCurrentIndex) {
            startVectorBlackPointCenterX[i] = startCenterX;
            startCenterX += space + diameter;
        } else {
            startVectorBlackPointCenterX[i] = startCenterX + radius;
            startLongPointLeftCenterX = startCenterX;
            startLongPointRightCenterX = startCenterX + diameter;
            startCenterX += space + diameter * DOUBLE;
        }
        if (i != endCurrentIndex) {
            endVectorBlackPointCenterX[i] = endCenterX;
            endCenterX += space + diameter;
        } else {
            endVectorBlackPointCenterX[i] = endCenterX + radius;
            endLongPointLeftCenterX = endCenterX;
            endLongPointRightCenterX = endCenterX + diameter;
            endCenterX += space + diameter * DOUBLE;
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
    longPointCenterX_.first =
        startLongPointLeftCenterX + (endLongPointLeftCenterX - startLongPointLeftCenterX) * longPointLeftCenterMoveRate;
    longPointCenterX_.second = startLongPointRightCenterX +
                               (endLongPointRightCenterX - startLongPointRightCenterX) * longPointRightCenterMoveRate;
}

void SwiperIndicatorPaintMethod::CalculateHoverIndex(float radius)
{
    if (!isHover_) {
        hoverIndex_ = std::nullopt;
        longPointIsHover_ = false;
        return;
    }
    for (size_t i = 0; i < vectorBlackPointCenterX_.size(); ++i) {
        OffsetF center = { vectorBlackPointCenterX_[i], centerY_ };
        if (isHoverPoint(hoverPoint_, center, center, radius)) {
            hoverIndex_ = i;
            break;
        }
    }

    OffsetF leftCenter = { longPointCenterX_.first, centerY_ };
    OffsetF rightCenter = { longPointCenterX_.second, centerY_ };
    longPointIsHover_ = isHoverPoint(hoverPoint_, leftCenter, rightCenter, radius);
}

bool SwiperIndicatorPaintMethod::isHoverPoint(
    const PointF& hoverPoint, const OffsetF& leftCenter, const OffsetF& rightCenter, float radius)
{
    float tempLeftCenterX = axis_ == Axis::HORIZONTAL ? leftCenter.GetX() : leftCenter.GetY();
    float tempLeftCenterY = axis_ == Axis::HORIZONTAL ? leftCenter.GetY() : leftCenter.GetX();
    float tempRightCenterX = axis_ == Axis::HORIZONTAL ? rightCenter.GetX() : rightCenter.GetY();
    float tempRightCenterY = axis_ == Axis::HORIZONTAL ? rightCenter.GetY() : rightCenter.GetX();
    return hoverPoint.GetX() >= (tempLeftCenterX - radius) && hoverPoint.GetX() <= (tempRightCenterX + radius) &&
           hoverPoint.GetY() >= (tempLeftCenterY - radius) && hoverPoint.GetY() <= (tempRightCenterY + radius);
}

} // namespace OHOS::Ace::NG
