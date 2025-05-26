/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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

#include "core/components_ng/pattern/swiper_indicator/dot_indicator/overlength_dot_indicator_paint_method.h"

namespace OHOS::Ace::NG {
namespace {
// for indicator
constexpr Dimension INDICATOR_PADDING_DEFAULT = 12.0_vp;
constexpr uint32_t ITEM_HALF_WIDTH = 0;
constexpr uint32_t SELECTED_ITEM_HALF_WIDTH = 2;
constexpr int TWOFOLD = 2;
constexpr Dimension INDICATOR_OFFSET_UNIT = 18.0_vp;
constexpr int32_t NUM_0 = 0;
constexpr int32_t NUM_1 = 1;
constexpr int32_t NUM_2 = 2;
constexpr int32_t NUM_3 = 3;
constexpr float HALF_FLOAT = 0.5f;
} // namespace

void OverlengthDotIndicatorPaintMethod::UpdateContentModifier(PaintWrapper* paintWrapper)
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
    CHECK_NULL_VOID(paintProperty);
    IsCustomSizeValue_ = paintProperty->GetIsCustomSizeValue(false);
    dotIndicatorModifier_->SetAxis(axis_);
    dotIndicatorModifier_->SetCurrentIndex(currentIndex_);
    dotIndicatorModifier_->SetMaxDisplayCount(maxDisplayCount_);
    dotIndicatorModifier_->SetRealItemCount(realItemCount_);
    dotIndicatorModifier_->SetUnselectedColor(paintProperty->GetColorValue(swiperTheme->GetColor()));
    dotIndicatorModifier_->SetSelectedColor(paintProperty->GetSelectedColorValue(swiperTheme->GetSelectedColor()));
    dotIndicatorModifier_->SetIndicatorMask(paintProperty->GetIndicatorMaskValue(false));
    dotIndicatorModifier_->SetIsIndicatorCustomSize(IsCustomSizeValue_);
    dotIndicatorModifier_->SetOffset(geometryNode->GetContentOffset());
    dotIndicatorModifier_->SetAnimationStartIndex(animationStartIndex_);
    dotIndicatorModifier_->SetAnimationEndIndex(animationEndIndex_);
    dotIndicatorModifier_->SetKeepStatus(keepStatus_);
    dotIndicatorModifier_->SetIsHorizontalAndRTL(isHorizontalAndRightToLeft_);
    dotIndicatorModifier_->SetNeedUpdate(true);
    dotIndicatorModifier_->SetForceStopPageRate(FLT_MAX);
    dotIndicatorModifier_->SetIndicatorDotItemSpace(paintProperty->GetSpaceValue(
        swiperTheme->GetIndicatorDotItemSpace()));
    
    SizeF contentSize = geometryNode->GetFrameSize();
    centerY_ = (axis_ == Axis::HORIZONTAL ? contentSize.Height() : contentSize.Width()) * HALF_FLOAT;
    dotIndicatorModifier_->SetCenterY(centerY_);

    if (dotIndicatorModifier_->GetCurrentOverlongType() == OverlongType::NONE) {
        dotIndicatorModifier_->InitOverlongStatus(currentIndex_);
    }

    if (touchBottomType_ == TouchBottomType::NONE && !isPressed_ && !isHover_) {
        PaintNormalIndicator(paintWrapper);
        dotIndicatorModifier_->SetIsHover(false);
        dotIndicatorModifier_->SetIsPressed(false);
    }
}

void OverlengthDotIndicatorPaintMethod::UpdateNormalIndicator(
    LinearVector<float>& itemHalfSizes, const PaintWrapper* paintWrapper)
{
    CHECK_NULL_VOID(dotIndicatorModifier_);
    dotIndicatorModifier_->SetTurnPageRate(turnPageRate_);
    dotIndicatorModifier_->SetGestureState(gestureState_);
    dotIndicatorModifier_->SetIsCustomSizeValue(IsCustomSizeValue_);
    dotIndicatorModifier_->SetTouchBottomTypeLoop(touchBottomTypeLoop_);
    if (gestureState_ == GestureState::GESTURE_STATE_RELEASE_LEFT ||
        gestureState_ == GestureState::GESTURE_STATE_RELEASE_RIGHT) {
        dotIndicatorModifier_->PlayIndicatorAnimation(
            normalMargin_, itemHalfSizes, gestureState_, touchBottomTypeLoop_);
    } else {
        const auto [blackPointCenterMoveRate, longPointLeftCenterMoveRate, longPointRightCenterMoveRate] =
            GetMoveRate();
        dotIndicatorModifier_->SetBlackPointCenterMoveRate(blackPointCenterMoveRate);
        dotIndicatorModifier_->SetLongPointLeftCenterMoveRate(longPointLeftCenterMoveRate);
        dotIndicatorModifier_->SetLongPointRightCenterMoveRate(longPointRightCenterMoveRate);
        dotIndicatorModifier_->UpdateNormalPaintProperty(normalMargin_, itemHalfSizes, overlongSelectedCenterX_);
    }
}

void OverlengthDotIndicatorPaintMethod::PaintNormalIndicator(const PaintWrapper* paintWrapper)
{
    CHECK_NULL_VOID(dotIndicatorModifier_);
    auto [longPointCenterX, itemHalfSizes] = CalculateLongPointCenterX(paintWrapper);
    longPointCenterX_ = longPointCenterX;
    if (dotIndicatorModifier_->GetIsHover()) {
        dotIndicatorModifier_->UpdateHoverToNormalPaintProperty(
            normalMargin_, itemHalfSizes, vectorBlackPointCenterX_, longPointCenterX_);
    } else if (dotIndicatorModifier_->GetIsPressed()) {
        dotIndicatorModifier_->UpdatePressToNormalPaintProperty(
            normalMargin_, itemHalfSizes, vectorBlackPointCenterX_, longPointCenterX_);
    } else {
        UpdateNormalIndicator(itemHalfSizes, paintWrapper);
    }
}
std::pair<float, float> OverlengthDotIndicatorPaintMethod::CalculatePointCenterX(
    const LinearVector<float>& itemHalfSizes, float margin, float padding, float space, int32_t index)
{
    if (itemCount_ == 0) {
        return { 0, 0 };
    }
    float startCenterX = margin + padding;
    float endCenterX = margin + padding;
    if (Positive(turnPageRate_)) {
        auto itemWidth = itemHalfSizes[ITEM_HALF_WIDTH] * TWOFOLD;
        auto selectedItemWidth = itemHalfSizes[SELECTED_ITEM_HALF_WIDTH] * TWOFOLD;
        float allPointDiameterSum = itemWidth * static_cast<float>(itemCount_ + NUM_1);
        if (IsCustomSizeValue_) {
            allPointDiameterSum = itemWidth * static_cast<float>(itemCount_ - NUM_1) + selectedItemWidth;
        }
        auto allPointSpaceSum = static_cast<float>(space * (itemCount_ - NUM_1));
        float rectWidth = padding + allPointDiameterSum + allPointSpaceSum + padding;
        startCenterX = rectWidth - startCenterX;
        endCenterX = rectWidth - endCenterX;
        return BackwardCalculation(itemHalfSizes, startCenterX, endCenterX, space, index);
    }
    return ForwardCalculation(itemHalfSizes, startCenterX, endCenterX, space, index);
}

std::tuple<std::pair<float, float>, LinearVector<float>> OverlengthDotIndicatorPaintMethod::CalculateLongPointCenterX(
    const PaintWrapper* paintWrapper)
{
    std::tuple<std::pair<float, float>, LinearVector<float>> tmp;
    CHECK_NULL_RETURN(paintWrapper, tmp);
    const auto& geometryNode = paintWrapper->GetGeometryNode();
    CHECK_NULL_RETURN(geometryNode, tmp);
    auto paintProperty = DynamicCast<DotIndicatorPaintProperty>(paintWrapper->GetPaintProperty());
    CHECK_NULL_RETURN(paintProperty, tmp);
    auto swiperTheme = GetSwiperIndicatorTheme();
    CHECK_NULL_RETURN(swiperTheme, tmp);
    SizeF frameSize = geometryNode->GetFrameSize();
    // diameter calculation
    auto itemWidth = static_cast<float>(paintProperty->GetItemWidthValue(swiperTheme->GetSize()).ConvertToPx());
    auto itemHeight = static_cast<float>(paintProperty->GetItemHeightValue(swiperTheme->GetSize()).ConvertToPx());
    auto selectedItemWidth =
        static_cast<float>(paintProperty->GetSelectedItemWidthValue(swiperTheme->GetSize()).ConvertToPx());
    auto selectedItemHeight =
        static_cast<float>(paintProperty->GetSelectedItemHeightValue(swiperTheme->GetSize()).ConvertToPx());

    int32_t displayCount = itemCount_;
    // use radius calculation
    Dimension indicatorDotItemSpace =
        paintProperty->GetSpaceValue(swiperTheme->GetIndicatorDotItemSpace());
    auto itemSpace = indicatorDotItemSpace.ConvertToPx();
    if (maxDisplayCount_ > 0) {
        displayCount = maxDisplayCount_;
    }
    LinearVector<float> itemHalfSizes;
    itemHalfSizes.emplace_back(itemWidth * HALF_FLOAT);
    itemHalfSizes.emplace_back(itemHeight * HALF_FLOAT);
    itemHalfSizes.emplace_back(selectedItemWidth * HALF_FLOAT);
    itemHalfSizes.emplace_back(selectedItemHeight * HALF_FLOAT);
    bool ignoreSize = paintProperty->GetIgnoreSizeValue(false);
    CalculateNormalMargin(itemHalfSizes, frameSize, displayCount, indicatorDotItemSpace, ignoreSize);

    auto longPointCenterX = CalculatePointCenterX(itemHalfSizes, normalMargin_.GetX(),
        static_cast<float>(INDICATOR_PADDING_DEFAULT.ConvertToPx()), static_cast<float>(itemSpace), currentIndex_);
    return { longPointCenterX, itemHalfSizes };
}

std::pair<float, float> OverlengthDotIndicatorPaintMethod::CalculatePointCenterX(
    const StarAndEndPointCenter& starAndEndPointCenter, const LinearVector<float>& startVectorBlackPointCenterX,
    const LinearVector<float>& endVectorBlackPointCenterX)
{
    const auto [blackPointCenterMoveRate, longPointLeftCenterMoveRate, longPointRightCenterMoveRate] = GetMoveRate();
    vectorBlackPointBegCenterX_.resize(itemCount_);
    vectorBlackPointCenterX_.resize(itemCount_);
    for (int32_t i = 0; i < itemCount_; ++i) {
        vectorBlackPointCenterX_[i] =
            startVectorBlackPointCenterX[i] +
            (endVectorBlackPointCenterX[i] - startVectorBlackPointCenterX[i]) * blackPointCenterMoveRate;
        if (currentIndex_ > (maxDisplayCount_ - NUM_3)) {
            if (currentIndex_ < realItemCount_ - NUM_2) {
                vectorBlackPointBegCenterX_[i] =
                    startVectorBlackPointCenterX[i] -
                    (currentIndex_ - (maxDisplayCount_ - NUM_3)) * (INDICATOR_OFFSET_UNIT.ConvertToPx()) +
                    (endVectorBlackPointCenterX[i] - startVectorBlackPointCenterX[i]) * blackPointCenterMoveRate;
            } else {
                vectorBlackPointBegCenterX_[i] =
                    startVectorBlackPointCenterX[i] -
                    (realItemCount_ - maxDisplayCount_) * (INDICATOR_OFFSET_UNIT.ConvertToPx()) +
                    (endVectorBlackPointCenterX[i] - startVectorBlackPointCenterX[i]) * blackPointCenterMoveRate;
            }
        } else {
            vectorBlackPointBegCenterX_[i] =
                startVectorBlackPointCenterX[i] +
                (endVectorBlackPointCenterX[i] - startVectorBlackPointCenterX[i]) * blackPointCenterMoveRate;
        }
    }
    std::pair<float, float> longPointCenterX;
    longPointCenterX.first =
        starAndEndPointCenter.startLongPointLeftCenterX +
        (starAndEndPointCenter.endLongPointLeftCenterX - starAndEndPointCenter.startLongPointLeftCenterX) *
            longPointLeftCenterMoveRate;
    longPointCenterX.second =
        starAndEndPointCenter.startLongPointRightCenterX +
        (starAndEndPointCenter.endLongPointRightCenterX - starAndEndPointCenter.startLongPointRightCenterX) *
            longPointRightCenterMoveRate;
    return longPointCenterX;
}
std::pair<float, float> OverlengthDotIndicatorPaintMethod::ForwardCalculation(
    const LinearVector<float>& itemHalfSizes, float startCenterX, float endCenterX, float space, int32_t index)
{
    auto selectedItemWidth = itemHalfSizes[SELECTED_ITEM_HALF_WIDTH] * TWOFOLD;
    StarAndEndPointCenter pointCenter;
    // Calculate the data required for the current pages
    LinearVector<float> startVectorBlackPointCenterX(itemCount_);
    // Calculate the data required for subsequent pages
    LinearVector<float> endVectorBlackPointCenterX(itemCount_);

    int32_t nposStation = 0;
    AnalysisIndexRange(nposStation);
    auto [startCurrentIndex, endCurrentIndex] = GetStartAndEndIndex(index);
    for (int32_t i = 0; i < itemCount_; ++i) {
        float item_width = itemHalfSizes[ITEM_HALF_WIDTH];
        if (i != startCurrentIndex) {
            startVectorBlackPointCenterX[i] = startCenterX + item_width;
            startCenterX += item_width * TWOFOLD;
        } else {
            if (IsCustomSizeValue_) {
                startVectorBlackPointCenterX[i] = startCenterX + itemHalfSizes[SELECTED_ITEM_HALF_WIDTH];
                pointCenter.startLongPointLeftCenterX = startCenterX + itemHalfSizes[SELECTED_ITEM_HALF_WIDTH];
                pointCenter.startLongPointRightCenterX = pointCenter.startLongPointLeftCenterX;
                startCenterX += selectedItemWidth;
            } else {
                startVectorBlackPointCenterX[i] = startCenterX + selectedItemWidth;
                pointCenter.startLongPointLeftCenterX = startCenterX + itemHalfSizes[SELECTED_ITEM_HALF_WIDTH];
                pointCenter.startLongPointRightCenterX = pointCenter.startLongPointLeftCenterX + selectedItemWidth;
                startCenterX += selectedItemWidth * TWOFOLD;
            }
        }
        if (i != endCurrentIndex) {
            endVectorBlackPointCenterX[i] = endCenterX + item_width;
            endCenterX += item_width * TWOFOLD;
        } else {
            if (IsCustomSizeValue_) {
                endVectorBlackPointCenterX[i] = endCenterX + itemHalfSizes[SELECTED_ITEM_HALF_WIDTH];
                pointCenter.endLongPointLeftCenterX = endCenterX + itemHalfSizes[SELECTED_ITEM_HALF_WIDTH];
                pointCenter.endLongPointRightCenterX = pointCenter.endLongPointLeftCenterX;
                endCenterX += selectedItemWidth;
            } else {
                endVectorBlackPointCenterX[i] = endCenterX + selectedItemWidth;
                pointCenter.endLongPointLeftCenterX = endCenterX + itemHalfSizes[SELECTED_ITEM_HALF_WIDTH];
                pointCenter.endLongPointRightCenterX = pointCenter.endLongPointLeftCenterX + selectedItemWidth;
                endCenterX += selectedItemWidth * TWOFOLD;
            }
        }
        startCenterX += space;
        endCenterX += space;
    }

    AdjustPointCenterXForTouchBottom(
        pointCenter, endVectorBlackPointCenterX, startCurrentIndex, endCurrentIndex, selectedItemWidth, index);
    return CalculatePointCenterX(pointCenter, startVectorBlackPointCenterX, endVectorBlackPointCenterX);
}
void OverlengthDotIndicatorPaintMethod::AnalysisIndexRange(int32_t& nposStation)
{
    if (currentIndex_ == NUM_0 || currentIndex_ == NUM_1) {
        nposStation = NUM_1;
    } else if (currentIndex_ >= NUM_2 && currentIndex_ < realItemCount_ - NUM_2) {
        nposStation = NUM_2;
    } else if (currentIndex_ >= realItemCount_ - NUM_2) {
        nposStation = NUM_3;
    }
}

void OverlengthDotIndicatorPaintMethod::CalculateNormalMargin(const LinearVector<float>& itemHalfSizes,
    const SizeF& frameSize, const int32_t displayCount, const Dimension& indicatorDotItemSpace, bool ignoreSize)
{
    if (maxDisplayCount_ > 0 && isBindIndicator_) {
        normalMargin_.Reset();
        return;
    }

    DotIndicatorPaintMethod::CalculateNormalMargin(
        itemHalfSizes, frameSize, displayCount, indicatorDotItemSpace, ignoreSize);
}
} // namespace OHOS::Ace::NG
