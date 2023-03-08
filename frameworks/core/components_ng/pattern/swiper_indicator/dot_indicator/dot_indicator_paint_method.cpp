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

#include "core/components_ng/pattern/swiper_indicator/dot_indicator/dot_indicator_paint_method.h"

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

void DotIndicatorPaintMethod::UpdateContentModifier(PaintWrapper* paintWrapper)
{
    CHECK_NULL_VOID(dotIndicatorModifier_);
    CHECK_NULL_VOID(paintWrapper);

    auto pipelineContext = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipelineContext);
    auto swiperTheme = pipelineContext->GetTheme<SwiperIndicatorTheme>();
    CHECK_NULL_VOID(swiperTheme);

    const auto& geometryNode = paintWrapper->GetGeometryNode();
    CHECK_NULL_VOID(geometryNode);

    auto paintProperty = DynamicCast<DotIndicatorPaintProperty>(paintWrapper->GetPaintProperty());
    dotIndicatorModifier_->SetAxis(axis_);
    dotIndicatorModifier_->SetUnselectedColor(paintProperty->GetColorValue(swiperTheme->GetColor()));
    dotIndicatorModifier_->SetSelectedColor(paintProperty->GetSelectedColorValue(swiperTheme->GetSelectedColor()));
    dotIndicatorModifier_->SetIndicatorMask(paintProperty->GetIndicatorMaskValue(false));
    dotIndicatorModifier_->SetOffset(geometryNode->GetContentOffset());
    SizeF contentSize = geometryNode->GetFrameSize();
    centerY_ = (axis_ == Axis::HORIZONTAL ? contentSize.Height() : contentSize.Width()) * HALF;
    dotIndicatorModifier_->SetCenterY(centerY_);

    if (isPressed_) {
        PaintPressIndicator(paintWrapper);
        dotIndicatorModifier_->SetIsPressed(true);
    } else if (isHover_) {
        PaintHoverIndicator(paintWrapper);
        dotIndicatorModifier_->SetIsHover(true);
    } else {
        PaintNormalIndicator(paintWrapper);
        dotIndicatorModifier_->SetIsHover(false);
        dotIndicatorModifier_->SetIsPressed(false);
    }
}

void DotIndicatorPaintMethod::PaintNormalIndicator(const PaintWrapper* paintWrapper)
{
    CHECK_NULL_VOID(paintWrapper);
    const auto& geometryNode = paintWrapper->GetGeometryNode();
    CHECK_NULL_VOID(geometryNode);
    auto paintProperty = DynamicCast<DotIndicatorPaintProperty>(paintWrapper->GetPaintProperty());
    CHECK_NULL_VOID(paintProperty);
    auto swiperTheme = GetSwiperIndicatorTheme();
    CHECK_NULL_VOID(swiperTheme);
    SizeF frameSize = geometryNode->GetFrameSize();

    float diameter = static_cast<float>(paintProperty->GetSizeValue(swiperTheme->GetSize()).ConvertToPx());
    float radius = diameter * HALF;
    CalculateNormalMargin(radius, frameSize);
    CalculatePointCenterX(radius, normalMargin_.GetX(), static_cast<float>(INDICATOR_PADDING_DEFAULT.ConvertToPx()),
        static_cast<float>(INDICATOR_ITEM_SPACE.ConvertToPx()), currentIndex_);

    if (dotIndicatorModifier_->GetIsHover()) {
        dotIndicatorModifier_->UpdateHoverToNormalPaintProperty(
            normalMargin_, radius, vectorBlackPointCenterX_, longPointCenterX_);
    } else if (dotIndicatorModifier_->GetIsPressed()) {
        dotIndicatorModifier_->UpdatePressToNormalPaintProperty(
            normalMargin_, radius, vectorBlackPointCenterX_, longPointCenterX_);
    } else {
        dotIndicatorModifier_->UpdateNormalPaintProperty(
            normalMargin_, radius, vectorBlackPointCenterX_, longPointCenterX_);
    }
}

void DotIndicatorPaintMethod::PaintHoverIndicator(const PaintWrapper* paintWrapper)
{
    CHECK_NULL_VOID(paintWrapper);
    auto paintProperty = DynamicCast<DotIndicatorPaintProperty>(paintWrapper->GetPaintProperty());
    CHECK_NULL_VOID(paintProperty);
    auto swiperTheme = GetSwiperIndicatorTheme();
    CHECK_NULL_VOID(swiperTheme);
    float normalDiameter = static_cast<float>(paintProperty->GetSizeValue(swiperTheme->GetSize()).ConvertToPx());
    float radius = normalDiameter * HALF * INDICATOR_ZOOM_IN_SCALE;
    CalculatePointCenterX(radius, 0, static_cast<float>(INDICATOR_PADDING_HOVER.ConvertToPx()),
        static_cast<float>(INDICATOR_ITEM_SPACE.ConvertToPx()), currentIndex_);

    if (dotIndicatorModifier_->GetIsPressed()) {
        dotIndicatorModifier_->SetIsPressed(false);
        dotIndicatorModifier_->UpdateHoverAndPressConversionPaintProperty();
    } else if (dotIndicatorModifier_->GetIsHover()) {
        dotIndicatorModifier_->UpdateHoverPaintProperty(radius, vectorBlackPointCenterX_, longPointCenterX_);
    } else {
        dotIndicatorModifier_->UpdateNormalToHoverPaintProperty(radius, vectorBlackPointCenterX_, longPointCenterX_);
    }

    CalculateHoverIndex(radius);
    if (dotIndicatorModifier_->GetNormalToHoverIndex() != hoverIndex_) {
        dotIndicatorModifier_->SetHoverToNormalIndex(dotIndicatorModifier_->GetNormalToHoverIndex());
        dotIndicatorModifier_->UpdateHoverToNormalPointDilateRatio();
        dotIndicatorModifier_->SetNormalToHoverIndex(hoverIndex_);
        dotIndicatorModifier_->UpdateNormalToHoverPointDilateRatio();
    }
    if (mouseClickIndex_ && mouseClickIndex_ != currentIndex_) {
        CalculatePointCenterX(radius, 0, static_cast<float>(INDICATOR_PADDING_HOVER.ConvertToPx()),
            static_cast<float>(INDICATOR_ITEM_SPACE.ConvertToPx()), mouseClickIndex_.value());
        dotIndicatorModifier_->UpdateAllPointCenterXAnimation(
            mouseClickIndex_ > currentIndex_, vectorBlackPointCenterX_, longPointCenterX_);
        longPointIsHover_ = true;
    }
    if (dotIndicatorModifier_->GetLongPointIsHover() != longPointIsHover_) {
        dotIndicatorModifier_->SetLongPointIsHover(longPointIsHover_);
        dotIndicatorModifier_->UpdateLongPointDilateRatio();
    }
}

void DotIndicatorPaintMethod::PaintPressIndicator(const PaintWrapper* paintWrapper)
{
    CHECK_NULL_VOID(paintWrapper);
    auto paintProperty = DynamicCast<DotIndicatorPaintProperty>(paintWrapper->GetPaintProperty());
    CHECK_NULL_VOID(paintProperty);
    auto swiperTheme = GetSwiperIndicatorTheme();
    CHECK_NULL_VOID(swiperTheme);
    float normalDiameter = static_cast<float>(paintProperty->GetSizeValue(swiperTheme->GetSize()).ConvertToPx());
    float radius = normalDiameter * HALF * INDICATOR_ZOOM_IN_SCALE;
    CalculatePointCenterX(radius, 0, static_cast<float>(INDICATOR_PADDING_HOVER.ConvertToPx()),
        static_cast<float>(INDICATOR_ITEM_SPACE.ConvertToPx()), currentIndex_);
    if (dotIndicatorModifier_->GetIsPressed()) {
        dotIndicatorModifier_->UpdatePressPaintProperty(radius, vectorBlackPointCenterX_, longPointCenterX_);
    } else if (dotIndicatorModifier_->GetIsHover()) {
        dotIndicatorModifier_->SetIsPressed(true);
        dotIndicatorModifier_->UpdateHoverAndPressConversionPaintProperty();
    } else {
        dotIndicatorModifier_->UpdateNormalToPressPaintProperty(radius, vectorBlackPointCenterX_, longPointCenterX_);
    }
}

void DotIndicatorPaintMethod::CalculateNormalMargin(float radius, const SizeF& frameSize)
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

void DotIndicatorPaintMethod::CalculatePointCenterX(
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
    StarAndEndPointCenter starAndEndPointCenter;
    starAndEndPointCenter.startLongPointLeftCenterX = startLongPointLeftCenterX;
    starAndEndPointCenter.endLongPointLeftCenterX = endLongPointLeftCenterX;
    starAndEndPointCenter.startLongPointRightCenterX = startLongPointRightCenterX;
    starAndEndPointCenter.endLongPointRightCenterX = endLongPointRightCenterX;
    CalculatePointCenterX(starAndEndPointCenter, startVectorBlackPointCenterX, endVectorBlackPointCenterX);
}

void DotIndicatorPaintMethod::CalculatePointCenterX(const StarAndEndPointCenter& starAndEndPointCenter,
    const LinearVector<float>& startVectorBlackPointCenterX, const LinearVector<float>& endVectorBlackPointCenterX)
{
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
        starAndEndPointCenter.startLongPointLeftCenterX +
        (starAndEndPointCenter.endLongPointLeftCenterX - starAndEndPointCenter.startLongPointLeftCenterX) *
            longPointLeftCenterMoveRate;
    longPointCenterX_.second =
        starAndEndPointCenter.startLongPointRightCenterX +
        (starAndEndPointCenter.endLongPointRightCenterX - starAndEndPointCenter.startLongPointRightCenterX) *
            longPointRightCenterMoveRate;
}

void DotIndicatorPaintMethod::CalculateHoverIndex(float radius)
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

bool DotIndicatorPaintMethod::isHoverPoint(
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
