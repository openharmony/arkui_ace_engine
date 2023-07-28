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
#include "core/components_ng/pattern/swiper_indicator/indicator_common/swiper_indicator_utils.h"
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

constexpr float BLACK_POINT_CENTER_BEZIER_CURVE_VELOCITY = 0.4f;
constexpr float LONG_POINT_LEFT_CENTER_BEZIER_CURVE_VELOCITY = 0.2f;
constexpr float LONG_POINT_RIGHT_CENTER_BEZIER_CURVE_VELOCITY = 1.0f;
constexpr float CENTER_BEZIER_CURVE_MASS = 0.0f;
constexpr float CENTER_BEZIER_CURVE_STIFFNESS = 1.0f;
constexpr float CENTER_BEZIER_CURVE_DAMPING = 1.0f;
constexpr uint32_t ITEM_HALF_WIDTH = 0;
constexpr uint32_t ITEM_HALF_HEIGHT = 1;
constexpr uint32_t SELECTED_ITEM_HALF_WIDTH = 2;
constexpr uint32_t SELECTED_ITEM_HALF_HEIGHT = 3;
constexpr float TOUCH_BOTTOM_BACKGROUND_WIDTH_MULTIPLE = 1.225f;
constexpr float TOUCH_BOTTOM_DOT_WIDTH_MULTIPLE = 0.0125f;

constexpr int TWOFOLD = 2;
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
    IsCustomSizeValue_ = paintProperty->GetIsCustomSizeValue(false);
    dotIndicatorModifier_->SetAxis(axis_);
    dotIndicatorModifier_->SetCurrentIndex(currentIndex_);
    dotIndicatorModifier_->SetUnselectedColor(paintProperty->GetColorValue(swiperTheme->GetColor()));
    dotIndicatorModifier_->SetSelectedColor(paintProperty->GetSelectedColorValue(swiperTheme->GetSelectedColor()));
    dotIndicatorModifier_->SetIndicatorMask(paintProperty->GetIndicatorMaskValue(false));
    dotIndicatorModifier_->SetIsIndicatorCustomSize(IsCustomSizeValue_);
    dotIndicatorModifier_->SetOffset(geometryNode->GetContentOffset());
    SizeF contentSize = geometryNode->GetFrameSize();
    centerY_ = (axis_ == Axis::HORIZONTAL ? contentSize.Height() : contentSize.Width()) * 0.5;
    dotIndicatorModifier_->SetCenterY(centerY_);
    if (touchBottomType_ != TouchBottomType::NONE) {
        UpdateBackground(paintWrapper);
    } else if (isPressed_) {
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
    // diameter calculation
    auto itemWidth = static_cast<float>(paintProperty->GetItemWidthValue(swiperTheme->GetSize()).ConvertToPx());
    auto itemHeight = static_cast<float>(paintProperty->GetItemHeightValue(swiperTheme->GetSize()).ConvertToPx());
    auto selectedItemWidth = static_cast<float>(
        paintProperty->GetSelectedItemWidthValue(swiperTheme->GetSize()).ConvertToPx());
    auto selectedItemHeight = static_cast<float>(
        paintProperty->GetSelectedItemHeightValue(swiperTheme->GetSize()).ConvertToPx());
    // use radius calculation
    LinearVector<float> itemHalfSizes;
    itemHalfSizes.emplace_back(itemWidth * 0.5);
    itemHalfSizes.emplace_back(itemHeight * 0.5);
    itemHalfSizes.emplace_back(selectedItemWidth * 0.5);
    itemHalfSizes.emplace_back(selectedItemHeight * 0.5);
    CalculateNormalMargin(itemHalfSizes, frameSize);
    CalculatePointCenterX(
        itemHalfSizes, normalMargin_.GetX(), static_cast<float>(INDICATOR_PADDING_DEFAULT.ConvertToPx()),
        static_cast<float>(INDICATOR_ITEM_SPACE.ConvertToPx()), currentIndex_);

    if (dotIndicatorModifier_->GetIsHover()) {
        dotIndicatorModifier_->UpdateHoverToNormalPaintProperty(
            normalMargin_, itemHalfSizes, vectorBlackPointCenterX_, longPointCenterX_);
    } else if (dotIndicatorModifier_->GetIsPressed()) {
        dotIndicatorModifier_->UpdatePressToNormalPaintProperty(
            normalMargin_, itemHalfSizes, vectorBlackPointCenterX_, longPointCenterX_);
    } else {
        dotIndicatorModifier_->UpdateNormalPaintProperty(
            normalMargin_, itemHalfSizes, vectorBlackPointCenterX_, longPointCenterX_);
    }
}

void DotIndicatorPaintMethod::PaintHoverIndicator(const PaintWrapper* paintWrapper)
{
    CHECK_NULL_VOID(paintWrapper);
    auto paintProperty = DynamicCast<DotIndicatorPaintProperty>(paintWrapper->GetPaintProperty());
    CHECK_NULL_VOID(paintProperty);
    auto swiperTheme = GetSwiperIndicatorTheme();
    CHECK_NULL_VOID(swiperTheme);
    // diameter calculation
    auto itemWidth = static_cast<float>(paintProperty->GetItemWidthValue(swiperTheme->GetSize()).ConvertToPx());
    auto itemHeight = static_cast<float>(paintProperty->GetItemHeightValue(swiperTheme->GetSize()).ConvertToPx());
    auto selectedItemWidth = static_cast<float>(
        paintProperty->GetSelectedItemWidthValue(swiperTheme->GetSize()).ConvertToPx());
    auto selectedItemHeight = static_cast<float>(
        paintProperty->GetSelectedItemHeightValue(swiperTheme->GetSize()).ConvertToPx());
    // use radius calculation
    LinearVector<float> itemHalfSizes;
    itemHalfSizes.emplace_back(itemWidth * 0.5 * INDICATOR_ZOOM_IN_SCALE);
    itemHalfSizes.emplace_back(itemHeight * 0.5 * INDICATOR_ZOOM_IN_SCALE);
    itemHalfSizes.emplace_back(selectedItemWidth * 0.5 * INDICATOR_ZOOM_IN_SCALE);
    itemHalfSizes.emplace_back(selectedItemHeight * 0.5 * INDICATOR_ZOOM_IN_SCALE);
    CalculatePointCenterX(itemHalfSizes, 0, static_cast<float>(INDICATOR_PADDING_HOVER.ConvertToPx()),
        static_cast<float>(INDICATOR_ITEM_SPACE.ConvertToPx()), currentIndex_);

    if (dotIndicatorModifier_->GetIsPressed()) {
        dotIndicatorModifier_->SetIsPressed(false);
        dotIndicatorModifier_->UpdateHoverAndPressConversionPaintProperty();
    } else if (dotIndicatorModifier_->GetIsHover()) {
        dotIndicatorModifier_->UpdateHoverPaintProperty(itemHalfSizes, vectorBlackPointCenterX_, longPointCenterX_);
    } else {
        dotIndicatorModifier_->UpdateNormalToHoverPaintProperty(
            itemHalfSizes, vectorBlackPointCenterX_, longPointCenterX_);
    }

    CalculateHoverIndex(itemHalfSizes);
    if (dotIndicatorModifier_->GetNormalToHoverIndex() != hoverIndex_) {
        dotIndicatorModifier_->SetHoverToNormalIndex(dotIndicatorModifier_->GetNormalToHoverIndex());
        dotIndicatorModifier_->UpdateHoverToNormalPointDilateRatio();
        dotIndicatorModifier_->SetNormalToHoverIndex(hoverIndex_);
        dotIndicatorModifier_->UpdateNormalToHoverPointDilateRatio();
    }
    if (mouseClickIndex_ && mouseClickIndex_ != currentIndex_) {
        CalculatePointCenterX(itemHalfSizes, 0, static_cast<float>(INDICATOR_PADDING_HOVER.ConvertToPx()),
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
    // diameter calculation
    auto itemWidth = static_cast<float>(paintProperty->GetItemWidthValue(swiperTheme->GetSize()).ConvertToPx());
    auto itemHeight = static_cast<float>(paintProperty->GetItemHeightValue(swiperTheme->GetSize()).ConvertToPx());
    auto selectedItemWidth = static_cast<float>(
        paintProperty->GetSelectedItemWidthValue(swiperTheme->GetSize()).ConvertToPx());
    auto selectedItemHeight = static_cast<float>(
        paintProperty->GetSelectedItemHeightValue(swiperTheme->GetSize()).ConvertToPx());
    // use radius calculation
    auto itemHalfWidth = itemWidth * 0.5 * INDICATOR_ZOOM_IN_SCALE;
    auto itemHalfHeight = itemHeight * 0.5 * INDICATOR_ZOOM_IN_SCALE;
    auto selectedItemHalfWidth = selectedItemWidth * 0.5 * INDICATOR_ZOOM_IN_SCALE;
    auto selectedItemHalfHeight = selectedItemHeight * 0.5 * INDICATOR_ZOOM_IN_SCALE;
    LinearVector<float> itemHalfSizes;
    itemHalfSizes.emplace_back(itemHalfWidth);
    itemHalfSizes.emplace_back(itemHalfHeight);
    itemHalfSizes.emplace_back(selectedItemHalfWidth);
    itemHalfSizes.emplace_back(selectedItemHalfHeight);
    CalculatePointCenterX(itemHalfSizes, 0, static_cast<float>(INDICATOR_PADDING_HOVER.ConvertToPx()),
        static_cast<float>(INDICATOR_ITEM_SPACE.ConvertToPx()), currentIndex_);
    if (dotIndicatorModifier_->GetIsPressed()) {
        dotIndicatorModifier_->UpdatePressPaintProperty(itemHalfSizes, vectorBlackPointCenterX_, longPointCenterX_);
    } else if (dotIndicatorModifier_->GetIsHover()) {
        dotIndicatorModifier_->SetIsPressed(true);
        dotIndicatorModifier_->UpdateHoverAndPressConversionPaintProperty();
    } else {
        dotIndicatorModifier_->UpdateNormalToPressPaintProperty(
            itemHalfSizes, vectorBlackPointCenterX_, longPointCenterX_);
    }
}

void DotIndicatorPaintMethod::CalculateNormalMargin(const LinearVector<float>& itemHalfSizes, const SizeF& frameSize)
{
    // diameter calculation
    auto itemWidth = itemHalfSizes[ITEM_HALF_WIDTH] * 2;
    auto itemHeight = itemHalfSizes[ITEM_HALF_HEIGHT] * 2;
    auto selectedItemWidth = itemHalfSizes[SELECTED_ITEM_HALF_WIDTH] * 2;
    auto selectedItemHeight = itemHalfSizes[SELECTED_ITEM_HALF_HEIGHT] * 2;
    auto allPointDiameterSum = itemWidth * static_cast<float>(itemCount_ - 1) + selectedItemWidth;
    auto allPointSpaceSum = static_cast<float>(INDICATOR_ITEM_SPACE.ConvertToPx() * (itemCount_ - 1));
    auto indicatorPadding = static_cast<float>(INDICATOR_PADDING_DEFAULT.ConvertToPx());
    auto contentWidth = indicatorPadding + allPointDiameterSum + allPointSpaceSum + indicatorPadding;
    auto contentHeight = indicatorPadding + itemHeight + indicatorPadding;
    if (selectedItemHeight > itemHeight) {
        contentHeight = indicatorPadding + selectedItemHeight + indicatorPadding;
    }
    float marginX = ((axis_ == Axis::HORIZONTAL ? frameSize.Width() : frameSize.Height()) - contentWidth) * 0.5;
    float marginY = ((axis_ == Axis::HORIZONTAL ? frameSize.Height() : frameSize.Width()) - contentHeight) * 0.5;
    normalMargin_.SetX(marginX);
    normalMargin_.SetY(marginY);
}

void DotIndicatorPaintMethod::CalculatePointCenterX(
    const LinearVector<float>& itemHalfSizes, float margin, float padding, float space, int32_t index)
{
    auto itemWidth = itemHalfSizes[ITEM_HALF_WIDTH] * TWOFOLD;
    auto selectedItemWidth = itemHalfSizes[SELECTED_ITEM_HALF_WIDTH] * TWOFOLD;
    // Calculate the data required for the current pages
    LinearVector<float> startVectorBlackPointCenterX(itemCount_);
    float startLongPointLeftCenterX = 0.0f;
    float startLongPointRightCenterX = 0.0f;
    float startCenterX = margin + padding;
    int32_t startCurrentIndex = index;
    // Calculate the data required for subsequent pages
    LinearVector<float> endVectorBlackPointCenterX(itemCount_);
    float endLongPointLeftCenterX = 0.0f;
    float endLongPointRightCenterX = 0.0f;
    float endCenterX = margin + padding;
    int32_t endCurrentIndex = NearEqual(turnPageRate_, 0.0f) || turnPageRate_ <= -1.0f || turnPageRate_ >= 1.0f ?
        endCurrentIndex = index : (turnPageRate_ < 0.0f ? index + 1 : index - 1);
    if (endCurrentIndex == -1) {
        endCurrentIndex = itemCount_ - 1;
    } else if (endCurrentIndex == itemCount_) {
        endCurrentIndex = 0;
    }
    for (int32_t i = 0; i < itemCount_; ++i) {
        if (i != startCurrentIndex) {
            startVectorBlackPointCenterX[i] = startCenterX + itemHalfSizes[ITEM_HALF_WIDTH];
            startCenterX += itemWidth;
        } else {
            if (IsCustomSizeValue_) {
                startVectorBlackPointCenterX[i] = startCenterX + itemHalfSizes[SELECTED_ITEM_HALF_WIDTH];
                startLongPointLeftCenterX = startCenterX + itemHalfSizes[SELECTED_ITEM_HALF_WIDTH];
                startLongPointRightCenterX = startLongPointLeftCenterX;
                startCenterX += selectedItemWidth;
            } else {
                startVectorBlackPointCenterX[i] = startCenterX + itemHalfSizes[SELECTED_ITEM_HALF_WIDTH];
                startLongPointLeftCenterX = startCenterX + itemHalfSizes[SELECTED_ITEM_HALF_WIDTH];
                startLongPointRightCenterX = startLongPointLeftCenterX + selectedItemWidth;
                startCenterX += selectedItemWidth * TWOFOLD;
            }
        }
        if (i != endCurrentIndex) {
            endVectorBlackPointCenterX[i] = endCenterX + itemHalfSizes[SELECTED_ITEM_HALF_WIDTH];
            endCenterX += itemWidth;
        } else {
            if (IsCustomSizeValue_) {
                endVectorBlackPointCenterX[i] = endCenterX + itemHalfSizes[SELECTED_ITEM_HALF_WIDTH];
                endLongPointLeftCenterX = endCenterX + itemHalfSizes[SELECTED_ITEM_HALF_WIDTH];
                endLongPointRightCenterX = endLongPointLeftCenterX;
                endCenterX += selectedItemWidth;
            } else {
                endVectorBlackPointCenterX[i] = endCenterX + itemHalfSizes[SELECTED_ITEM_HALF_WIDTH];
                endLongPointLeftCenterX = endCenterX + itemHalfSizes[SELECTED_ITEM_HALF_WIDTH];
                endLongPointRightCenterX = endLongPointLeftCenterX + selectedItemWidth;
                endCenterX += selectedItemWidth * TWOFOLD;
            }
        }
        startCenterX += space;
        endCenterX += space;
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
        CENTER_BEZIER_CURVE_STIFFNESS, CENTER_BEZIER_CURVE_DAMPING).MoveInternal(std::abs(turnPageRate_));
    float longPointLeftCenterMoveRate = CubicCurve(turnPageRate_ > 0 ?
        LONG_POINT_LEFT_CENTER_BEZIER_CURVE_VELOCITY : LONG_POINT_RIGHT_CENTER_BEZIER_CURVE_VELOCITY,
        CENTER_BEZIER_CURVE_MASS, CENTER_BEZIER_CURVE_STIFFNESS,
        CENTER_BEZIER_CURVE_DAMPING).MoveInternal(std::abs(turnPageRate_));
    float longPointRightCenterMoveRate = CubicCurve(turnPageRate_ > 0 ?
        LONG_POINT_RIGHT_CENTER_BEZIER_CURVE_VELOCITY : LONG_POINT_LEFT_CENTER_BEZIER_CURVE_VELOCITY,
        CENTER_BEZIER_CURVE_MASS, CENTER_BEZIER_CURVE_STIFFNESS,
        CENTER_BEZIER_CURVE_DAMPING).MoveInternal(std::abs(turnPageRate_));
    vectorBlackPointCenterX_.resize(itemCount_);
    for (int32_t i = 0; i < itemCount_; ++i) {
        vectorBlackPointCenterX_[i] = startVectorBlackPointCenterX[i] +
        (endVectorBlackPointCenterX[i] - startVectorBlackPointCenterX[i]) * blackPointCenterMoveRate;
    }
    longPointCenterX_.first = starAndEndPointCenter.startLongPointLeftCenterX +
        (starAndEndPointCenter.endLongPointLeftCenterX - starAndEndPointCenter.startLongPointLeftCenterX) *
        longPointLeftCenterMoveRate;
    longPointCenterX_.second = starAndEndPointCenter.startLongPointRightCenterX +
        (starAndEndPointCenter.endLongPointRightCenterX - starAndEndPointCenter.startLongPointRightCenterX) *
        longPointRightCenterMoveRate;
}

void DotIndicatorPaintMethod::CalculateHoverIndex(const LinearVector<float>& itemHalfSizes)
{
    if (!isHover_) {
        hoverIndex_ = std::nullopt;
        longPointIsHover_ = false;
        return;
    }
    for (size_t i = 0; i < vectorBlackPointCenterX_.size(); ++i) {
        OffsetF center = { vectorBlackPointCenterX_[i], centerY_ };
        if (isHoverPoint(hoverPoint_, center, center, itemHalfSizes)) {
            hoverIndex_ = i;
            break;
        }
    }

    OffsetF leftCenter = { longPointCenterX_.first, centerY_ };
    OffsetF rightCenter = { longPointCenterX_.second, centerY_ };
    longPointIsHover_ = isHoverPoint(hoverPoint_, leftCenter, rightCenter, itemHalfSizes);
}

bool DotIndicatorPaintMethod::isHoverPoint(
    const PointF& hoverPoint, const OffsetF& leftCenter,
    const OffsetF& rightCenter, const LinearVector<float>& itemHalfSizes)
{
    float tempLeftCenterX = axis_ == Axis::HORIZONTAL ? leftCenter.GetX() : leftCenter.GetY();
    float tempLeftCenterY = axis_ == Axis::HORIZONTAL ? leftCenter.GetY() : leftCenter.GetX();
    float tempRightCenterX = axis_ == Axis::HORIZONTAL ? rightCenter.GetX() : rightCenter.GetY();
    float tempRightCenterY = axis_ == Axis::HORIZONTAL ? rightCenter.GetY() : rightCenter.GetX();
    float itemHalfWidth = itemHalfSizes[ITEM_HALF_WIDTH];
    float itemHalfHeight = itemHalfSizes[ITEM_HALF_HEIGHT];
    if (hoverIndex_ == currentIndex_) {
        itemHalfWidth = itemHalfSizes[SELECTED_ITEM_HALF_WIDTH];
        itemHalfHeight = itemHalfSizes[SELECTED_ITEM_HALF_HEIGHT];
    }
    return hoverPoint.GetX() >= (tempLeftCenterX - itemHalfWidth) && (hoverPoint.GetX() <=
                (tempRightCenterX + itemHalfWidth)) && (hoverPoint.GetY() >= (tempLeftCenterY - itemHalfHeight)) &&
                (hoverPoint.GetY() <= (tempRightCenterY + itemHalfHeight));
}

void DotIndicatorPaintMethod::UpdateBackground(const PaintWrapper* paintWrapper)
{
    CHECK_NULL_VOID(paintWrapper);
    auto paintProperty = DynamicCast<DotIndicatorPaintProperty>(paintWrapper->GetPaintProperty());
    CHECK_NULL_VOID(paintProperty);
    auto swiperTheme = GetSwiperIndicatorTheme();
    CHECK_NULL_VOID(swiperTheme);

    // diameter calculation
    auto itemWidth = static_cast<float>(paintProperty->GetItemWidthValue(swiperTheme->GetSize()).ConvertToPx());
    auto itemHeight = static_cast<float>(paintProperty->GetItemHeightValue(swiperTheme->GetSize()).ConvertToPx());
    auto selectedItemWidth =
        static_cast<float>(paintProperty->GetSelectedItemWidthValue(swiperTheme->GetSize()).ConvertToPx());
    auto selectedItemHeight =
        static_cast<float>(paintProperty->GetSelectedItemHeightValue(swiperTheme->GetSize()).ConvertToPx());
    // use radius calculation
    LinearVector<float> itemHalfSizes;
    itemHalfSizes.emplace_back(itemWidth * 0.5f * INDICATOR_ZOOM_IN_SCALE);
    itemHalfSizes.emplace_back(itemHeight * 0.5f * INDICATOR_ZOOM_IN_SCALE);
    itemHalfSizes.emplace_back(selectedItemWidth * 0.5f * INDICATOR_ZOOM_IN_SCALE);
    itemHalfSizes.emplace_back(selectedItemHeight * 0.5f * INDICATOR_ZOOM_IN_SCALE);
    if (touchBottomType_ != TouchBottomType::NONE) {
        float allPointDiameterSum = itemWidth * static_cast<float>(itemCount_ + 1);
        if (IsCustomSizeValue_) {
            allPointDiameterSum = itemWidth * static_cast<float>(itemCount_ - 1) + selectedItemWidth;
        }
        float allPointSpaceSum = static_cast<float>(INDICATOR_ITEM_SPACE.ConvertToPx()) * (itemCount_ - 1);
        float padding = static_cast<float>(INDICATOR_PADDING_DEFAULT.ConvertToPx());
        float rectWidth = padding + allPointDiameterSum + allPointSpaceSum + padding;
        float newRectWidth =
            rectWidth * (TOUCH_BOTTOM_BACKGROUND_WIDTH_MULTIPLE - TOUCH_BOTTOM_DOT_WIDTH_MULTIPLE * itemCount_);
        auto changeValue = (newRectWidth - rectWidth) * touchBottomRate_;

        float space = static_cast<float>(INDICATOR_ITEM_SPACE.ConvertToPx());
        if (itemCount_ > 1) {
            space = (rectWidth + changeValue - padding * 2 - allPointDiameterSum) / (itemCount_ - 1);
        }
        CalculatePointCenterX(itemHalfSizes, 0, padding, space, currentIndex_);
        if (touchBottomType_ == TouchBottomType::START) {
            for (size_t index = 0; index < vectorBlackPointCenterX_.size(); index++) {
                vectorBlackPointCenterX_[index] = vectorBlackPointCenterX_[index] - changeValue;
            }
            longPointCenterX_.first = longPointCenterX_.first - changeValue;
            longPointCenterX_.second = longPointCenterX_.second - changeValue;
        }
    }
    dotIndicatorModifier_->UpdateTouchBottomAnimation(
        touchBottomType_, vectorBlackPointCenterX_, longPointCenterX_, touchBottomRate_);
}
} // namespace OHOS::Ace::NG

