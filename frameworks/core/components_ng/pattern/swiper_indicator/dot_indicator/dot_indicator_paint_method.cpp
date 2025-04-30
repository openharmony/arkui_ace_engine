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

#include "core/components/common/layout/constants.h"
#include "core/components/common/properties/color.h"
namespace OHOS::Ace::NG {
namespace {
// for indicator
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
constexpr float LONG_POINT_TAIL_RATIO = 0.5f;
constexpr float FIFTY_PERCENT = 0.5f;
constexpr float HALF_SELECTED_WIDTH = 2.0f;
constexpr float HALF_FLOAT = 0.5f;
constexpr int TWOFOLD = 2;
constexpr float HALF = 0.5f;
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
    CHECK_NULL_VOID(paintProperty);
    IsCustomSizeValue_ = paintProperty->GetIsCustomSizeValue(false);
    dotIndicatorModifier_->SetAxis(axis_);
    auto [currentIndex, currentIndexActual] = CalCurrentIndex();
    dotIndicatorModifier_->SetCurrentIndex(currentIndex);
    dotIndicatorModifier_->SetCurrentIndexActual(currentIndexActual);
    dotIndicatorModifier_->SetUnselectedColor(paintProperty->GetColorValue(swiperTheme->GetColor()));
    dotIndicatorModifier_->SetSelectedColor(paintProperty->GetSelectedColorValue(swiperTheme->GetSelectedColor()));
    dotIndicatorModifier_->SetIndicatorMask(paintProperty->GetIndicatorMaskValue(false));
    dotIndicatorModifier_->SetIsIndicatorCustomSize(IsCustomSizeValue_);
    dotIndicatorModifier_->SetOffset(geometryNode->GetContentOffset());
    dotIndicatorModifier_->SetIndicatorDotItemSpace(
        paintProperty->GetSpaceValue(swiperTheme->GetIndicatorDotItemSpace()));

    SizeF contentSize = geometryNode->GetFrameSize();
    centerY_ = (axis_ == Axis::HORIZONTAL ? contentSize.Height() : contentSize.Width()) * 0.5;
    dotIndicatorModifier_->SetCenterY(centerY_);
    if (touchBottomType_ != TouchBottomType::NONE) {
        if (!dotIndicatorModifier_->GetIsPressed()) {
            PaintPressIndicator(paintWrapper);
            dotIndicatorModifier_->SetIsPressed(true);
        }
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

std::pair<int32_t, int32_t> DotIndicatorPaintMethod::CalCurrentIndex()
{
    totalItemCount_ = Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_EIGHTEEN) ?
        totalItemCount_ : itemCount_;
    if (isHorizontalAndRightToLeft_) {
        if (isSwipeByGroup_) {
            currentIndex_ = totalItemCount_ - 1 - currentIndex_;
        } else {
            currentIndex_ = itemCount_ - 1 - currentIndex_;
        }
    }
    auto currentIndex = currentIndex_;
    auto currentIndexActual = currentIndexActual_;
    if (Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_EIGHTEEN) && isSwipeByGroup_ &&
        displayCount_ != 0) {
        currentIndex = currentIndex_ / displayCount_;
        currentIndexActual = currentIndexActual_ / displayCount_;
    }
    return { currentIndex, currentIndexActual };
}

bool DotIndicatorPaintMethod::NeedBottomAnimation() const
{
    auto currentIndexActual = currentIndexActual_;
    auto firstIndex = firstIndex_;
    if (Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_EIGHTEEN) && isSwipeByGroup_ &&
        displayCount_ != 0) {
        firstIndex /= displayCount_;
        currentIndexActual /= displayCount_;
    }
    firstIndex = isHorizontalAndRightToLeft_ ? itemCount_ - 1 - firstIndex : firstIndex;
    if (gestureState_ == GestureState::GESTURE_STATE_RELEASE_LEFT) {
        if (touchBottomTypeLoop_ == TouchBottomTypeLoop::TOUCH_BOTTOM_TYPE_LOOP_LEFT) {
            if (NearZero(touchBottomPageRate_)) {
                return true;
            }

            if (currentIndexActual != firstIndex && std::abs(touchBottomPageRate_) < FIFTY_PERCENT) {
                return false;
            }

            return true;
        }

        if (currentIndexActual == firstIndex && firstIndex == itemCount_ - 1 &&
            std::abs(touchBottomPageRate_) > FIFTY_PERCENT) {
            return true;
        }
    }

    if (gestureState_ == GestureState::GESTURE_STATE_RELEASE_RIGHT) {
        if (touchBottomTypeLoop_ == TouchBottomTypeLoop::TOUCH_BOTTOM_TYPE_LOOP_RIGHT) {
            if (currentIndexActual == firstIndex && std::abs(touchBottomPageRate_) > FIFTY_PERCENT) {
                return false;
            }

            return true;
        }

        if (currentIndexActual == 0 && firstIndex == itemCount_ - 1 &&
            std::abs(touchBottomPageRate_) < FIFTY_PERCENT) {
            return true;
        }
    }

    return false;
}

void DotIndicatorPaintMethod::GetLongPointAnimationStateSecondCenter(
    const PaintWrapper* paintWrapper, std::vector<std::pair<float, float>>& pointCenterX)
{
    if (NeedBottomAnimation()) {
        pointAnimationStage_ = PointAnimationStage::STATE_EXPAND_TO_LONG_POINT;
        auto [longPointCenterX, _] = CalculateLongPointCenterX(paintWrapper);
        pointAnimationStage_ = PointAnimationStage::STATE_SHRINKT_TO_BLACK_POINT;
        pointCenterX.push_back(longPointCenterX);
    }
}

void DotIndicatorPaintMethod::UpdateNormalIndicator(
    LinearVector<float>& itemHalfSizes, const PaintWrapper* paintWrapper)
{
    CHECK_NULL_VOID(dotIndicatorModifier_);
    if (gestureState_ == GestureState::GESTURE_STATE_RELEASE_LEFT ||
        gestureState_ == GestureState::GESTURE_STATE_RELEASE_RIGHT) {
        std::vector<std::pair<float, float>> pointCenterX({ longPointCenterX_ });
        GetLongPointAnimationStateSecondCenter(paintWrapper, pointCenterX);
        dotIndicatorModifier_->PlayIndicatorAnimation(
            vectorBlackPointCenterX_, pointCenterX, gestureState_, touchBottomTypeLoop_);
    } else {
        dotIndicatorModifier_->UpdateNormalPaintProperty(
            normalMargin_, itemHalfSizes, vectorBlackPointCenterX_, longPointCenterX_);
    }
}

void DotIndicatorPaintMethod::PaintNormalIndicator(const PaintWrapper* paintWrapper)
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

void DotIndicatorPaintMethod::PaintHoverIndicator(const PaintWrapper* paintWrapper)
{
    CHECK_NULL_VOID(dotIndicatorModifier_);
    CHECK_NULL_VOID(paintWrapper);
    auto paintProperty = DynamicCast<DotIndicatorPaintProperty>(paintWrapper->GetPaintProperty());
    CHECK_NULL_VOID(paintProperty);
    auto indicatorTheme = GetSwiperIndicatorTheme();
    CHECK_NULL_VOID(indicatorTheme);
    // diameter calculation
    auto itemWidth = static_cast<float>(paintProperty->GetItemWidthValue(indicatorTheme->GetSize()).ConvertToPx());
    auto itemHeight = static_cast<float>(paintProperty->GetItemHeightValue(indicatorTheme->GetSize()).ConvertToPx());
    auto selectedItemWidth =
        static_cast<float>(paintProperty->GetSelectedItemWidthValue(indicatorTheme->GetSize()).ConvertToPx());
    auto selectedItemHeight =
        static_cast<float>(paintProperty->GetSelectedItemHeightValue(indicatorTheme->GetSize()).ConvertToPx());
    // use radius calculation
    LinearVector<float> itemHalfSizes;
    float indicatorScale = indicatorTheme->GetIndicatorScale();
    itemHalfSizes.emplace_back(itemWidth * HALF * indicatorScale);
    itemHalfSizes.emplace_back(itemHeight * HALF * indicatorScale);
    itemHalfSizes.emplace_back(selectedItemWidth * HALF * indicatorScale);
    itemHalfSizes.emplace_back(selectedItemHeight * HALF * indicatorScale);
    Dimension paddingSide = indicatorTheme->GetIndicatorPaddingDot();
    Dimension indicatorDotItemSpace =
        paintProperty->GetSpaceValue(indicatorTheme->GetIndicatorDotItemSpace());
        
    longPointCenterX_ =
        CalculatePointCenterX(itemHalfSizes, 0, static_cast<float>(paddingSide.ConvertToPx()),
            static_cast<float>(indicatorDotItemSpace.ConvertToPx()), currentIndex_);
    if (dotIndicatorModifier_->GetIsPressed()) {
        dotIndicatorModifier_->SetIsPressed(false);
        dotIndicatorModifier_->UpdateHoverAndPressConversionPaintProperty();
    } else if (dotIndicatorModifier_->GetIsHover()) {
        if (!mouseClickIndex_.has_value()) {
            dotIndicatorModifier_->UpdateHoverPaintProperty(itemHalfSizes,
                vectorBlackPointCenterX_, longPointCenterX_);
        }
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

    PaintHoverIndicator(itemHalfSizes, paddingSide, indicatorDotItemSpace);
}

int32_t DotIndicatorPaintMethod::CalculateMouseClickIndexOnRTL()
{
    int32_t mouseClickIndex = 0;
    if (!mouseClickIndex_) {
        return mouseClickIndex;
    }

    if (isSwipeByGroup_) {
        mouseClickIndex = totalItemCount_ - 1 - mouseClickIndex_.value();
    } else {
        mouseClickIndex = itemCount_ - 1 - mouseClickIndex_.value();
    }

    return mouseClickIndex;
}

void DotIndicatorPaintMethod::PaintHoverIndicator(LinearVector<float>& itemHalfSizes, const Dimension paddingSide,
    const Dimension& indicatorDotItemSpace)
{
    CHECK_NULL_VOID(dotIndicatorModifier_);
    if (mouseClickIndex_) {
        if (currentIndex_ == totalItemCount_ - displayCount_ && !isLoop_ && mouseClickIndex_ > currentIndex_ &&
            mouseClickIndex_ < totalItemCount_) {
            longPointCenterX_ = CalculatePointCenterX(itemHalfSizes, 0, static_cast<float>(paddingSide.ConvertToPx()),
                static_cast<float>(indicatorDotItemSpace.ConvertToPx()), currentIndex_);
        } else {
            auto mouseClickIndex = isHorizontalAndRightToLeft_ ?
                CalculateMouseClickIndexOnRTL() : mouseClickIndex_.value();
            longPointCenterX_ = CalculatePointCenterX(itemHalfSizes, 0, static_cast<float>(paddingSide.ConvertToPx()),
                static_cast<float>(indicatorDotItemSpace.ConvertToPx()), mouseClickIndex);
        }
        dotIndicatorModifier_->UpdateAllPointCenterXAnimation(
            gestureState_, vectorBlackPointCenterX_, longPointCenterX_);
        mouseClickIndex_ = std::nullopt;
    }
    if (dotIndicatorModifier_->GetLongPointIsHover() != longPointIsHover_) {
        dotIndicatorModifier_->SetLongPointIsHover(longPointIsHover_);
        dotIndicatorModifier_->UpdateLongPointDilateRatio();
    }
}

void DotIndicatorPaintMethod::PaintPressIndicator(const PaintWrapper* paintWrapper)
{
    CHECK_NULL_VOID(dotIndicatorModifier_);
    CHECK_NULL_VOID(paintWrapper);
    auto paintProperty = DynamicCast<DotIndicatorPaintProperty>(paintWrapper->GetPaintProperty());
    CHECK_NULL_VOID(paintProperty);
    auto indicatorTheme = GetSwiperIndicatorTheme();
    CHECK_NULL_VOID(indicatorTheme);
    // diameter calculation
    auto itemWidth = static_cast<float>(paintProperty->GetItemWidthValue(indicatorTheme->GetSize()).ConvertToPx());
    auto itemHeight = static_cast<float>(paintProperty->GetItemHeightValue(indicatorTheme->GetSize()).ConvertToPx());
    auto selectedItemWidth =
        static_cast<float>(paintProperty->GetSelectedItemWidthValue(indicatorTheme->GetSize()).ConvertToPx());
    auto selectedItemHeight =
        static_cast<float>(paintProperty->GetSelectedItemHeightValue(indicatorTheme->GetSize()).ConvertToPx());
    // use radius calculation
    float indicatorScale = indicatorTheme->GetIndicatorScale();
    auto itemHalfWidth = itemWidth * HALF * indicatorScale;
    auto itemHalfHeight = itemHeight * HALF * indicatorScale;
    auto selectedItemHalfWidth = selectedItemWidth * HALF * indicatorScale;
    auto selectedItemHalfHeight = selectedItemHeight * HALF * indicatorScale;
    LinearVector<float> itemHalfSizes;
    itemHalfSizes.emplace_back(itemHalfWidth);
    itemHalfSizes.emplace_back(itemHalfHeight);
    itemHalfSizes.emplace_back(selectedItemHalfWidth);
    itemHalfSizes.emplace_back(selectedItemHalfHeight);
    Dimension paddingSide = indicatorTheme->GetIndicatorPaddingDot();
    Dimension indicatorDotItemSpace =
        paintProperty->GetSpaceValue(indicatorTheme->GetIndicatorDotItemSpace());
    longPointCenterX_ =
        CalculatePointCenterX(itemHalfSizes, 0, static_cast<float>(paddingSide.ConvertToPx()),
            static_cast<float>(indicatorDotItemSpace.ConvertToPx()), currentIndex_);
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

void DotIndicatorPaintMethod::CalculateNormalMargin(const LinearVector<float>& itemHalfSizes,
    const SizeF& frameSize, const int32_t displayCount, const Dimension& indicatorDotItemSpace, bool ignoreSize)
{
    // diameter calculation
    auto itemWidth = itemHalfSizes[ITEM_HALF_WIDTH] * 2;
    auto itemHeight = itemHalfSizes[ITEM_HALF_HEIGHT] * 2;
    auto selectedItemWidth = itemHalfSizes[SELECTED_ITEM_HALF_WIDTH] * 2;
    auto selectedItemHeight = itemHalfSizes[SELECTED_ITEM_HALF_HEIGHT] * 2;
    auto allPointDiameterSum = itemWidth * static_cast<float>(displayCount + 1);
    if (IsCustomSizeValue_) {
        allPointDiameterSum = itemWidth * static_cast<float>(displayCount - 1) + selectedItemWidth;
    }
    auto allPointSpaceSum = static_cast<float>(indicatorDotItemSpace.ConvertToPx()) * (displayCount - 1);
    auto indicatorTheme = GetSwiperIndicatorTheme();
    CHECK_NULL_VOID(indicatorTheme);
    Dimension paddingSide = indicatorTheme->GetIndicatorPaddingDot();
    auto indicatorPaddingSide = static_cast<float>(paddingSide.ConvertToPx());
    auto contentWidth = indicatorPaddingSide + allPointDiameterSum + allPointSpaceSum + indicatorPaddingSide;
    auto indicatorHeightPadding = indicatorTheme->GetIndicatorBgHeight().ConvertToPx();

    auto contentHeight = indicatorHeightPadding + itemHeight + indicatorHeightPadding;
    if (selectedItemHeight > itemHeight) {
        contentHeight = indicatorHeightPadding + selectedItemHeight + indicatorHeightPadding;
    }

    float marginX = ((axis_ == Axis::HORIZONTAL ? frameSize.Width() : frameSize.Height()) - contentWidth) * 0.5;
    float marginY = ((axis_ == Axis::HORIZONTAL ? frameSize.Height() : frameSize.Width()) - contentHeight) * 0.5;
    normalMargin_.SetX(marginX);
    normalMargin_.SetY(marginY);
}

std::pair<float, float> DotIndicatorPaintMethod::CalculatePointCenterX(
    const LinearVector<float>& itemHalfSizes, float margin, float padding, float space, int32_t index)
{
    if (itemCount_ == 0) {
        return { 0, 0 };
    }
    float startCenterX = margin + padding;
    float endCenterX = margin + padding;
    if (Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_EIGHTEEN)) {
        if (isSwipeByGroup_ && displayCount_ != 0) {
            index /= displayCount_;
        }
        if (isPressed_ && isSwipeByGroup_) {
            touchBottomTypeLoop_ = TouchBottomTypeLoop::TOUCH_BOTTOM_TYPE_LOOP_NONE;
        }
    }

    if (Positive(turnPageRate_)) {
        auto itemWidth = itemHalfSizes[ITEM_HALF_WIDTH] * TWOFOLD;
        auto selectedItemWidth = itemHalfSizes[SELECTED_ITEM_HALF_WIDTH] * TWOFOLD;
        float allPointDiameterSum = itemWidth * static_cast<float>(itemCount_ + 1);
        if (IsCustomSizeValue_) {
            allPointDiameterSum = itemWidth * static_cast<float>(itemCount_ - 1) + selectedItemWidth;
        }
        auto allPointSpaceSum = static_cast<float>(space * (itemCount_ - 1));
        
        float rectWidth = padding + allPointDiameterSum + allPointSpaceSum + padding;
        startCenterX = rectWidth - startCenterX;
        endCenterX = rectWidth - endCenterX;
        return BackwardCalculation(itemHalfSizes, startCenterX, endCenterX, space, index);
    }
    return ForwardCalculation(itemHalfSizes, startCenterX, endCenterX, space, index);
}

std::tuple<std::pair<float, float>, LinearVector<float>> DotIndicatorPaintMethod::CalculateLongPointCenterX(
    const PaintWrapper* paintWrapper)
{
    std::tuple<std::pair<float, float>, LinearVector<float>> tmp;
    CHECK_NULL_RETURN(paintWrapper, tmp);
    const auto& geometryNode = paintWrapper->GetGeometryNode();
    CHECK_NULL_RETURN(geometryNode, tmp);
    auto paintProperty = DynamicCast<DotIndicatorPaintProperty>(paintWrapper->GetPaintProperty());
    CHECK_NULL_RETURN(paintProperty, tmp);
    auto indicatorTheme = GetSwiperIndicatorTheme();
    CHECK_NULL_RETURN(indicatorTheme, tmp);
    SizeF frameSize = geometryNode->GetFrameSize();
    // diameter calculation
    auto itemWidth = static_cast<float>(paintProperty->GetItemWidthValue(indicatorTheme->GetSize()).ConvertToPx());
    auto itemHeight = static_cast<float>(paintProperty->GetItemHeightValue(indicatorTheme->GetSize()).ConvertToPx());
    auto selectedItemWidth =
        static_cast<float>(paintProperty->GetSelectedItemWidthValue(indicatorTheme->GetSize()).ConvertToPx());
    auto selectedItemHeight =
        static_cast<float>(paintProperty->GetSelectedItemHeightValue(indicatorTheme->GetSize()).ConvertToPx());
    // use radius calculation
    LinearVector<float> itemHalfSizes;
    itemHalfSizes.emplace_back(itemWidth * 0.5);
    itemHalfSizes.emplace_back(itemHeight * 0.5);
    itemHalfSizes.emplace_back(selectedItemWidth * 0.5);
    itemHalfSizes.emplace_back(selectedItemHeight * 0.5);

    Dimension indicatorDotItemSpace =
        paintProperty->GetSpaceValue(indicatorTheme->GetIndicatorDotItemSpace());
    bool ignoreSize = paintProperty->GetIgnoreSizeValue(false);
    CalculateNormalMargin(itemHalfSizes, frameSize, itemCount_, indicatorDotItemSpace, ignoreSize);
    Dimension paddingSide = indicatorTheme->GetIndicatorPaddingDot();
    auto longPointCenterX = CalculatePointCenterX(itemHalfSizes, normalMargin_.GetX(),
        static_cast<float>(paddingSide.ConvertToPx()),
        static_cast<float>(indicatorDotItemSpace.ConvertToPx()), currentIndex_);
    return { longPointCenterX, itemHalfSizes };
}

std::tuple<float, float, float> DotIndicatorPaintMethod::GetMoveRate()
{
    auto actualTurnPageRate = Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_EIGHTEEN) &&
        isSwipeByGroup_ ? groupTurnPageRate_ : turnPageRate_;
    float blackPointCenterMoveRate = CubicCurve(BLACK_POINT_CENTER_BEZIER_CURVE_VELOCITY, CENTER_BEZIER_CURVE_MASS,
        CENTER_BEZIER_CURVE_STIFFNESS, CENTER_BEZIER_CURVE_DAMPING).MoveInternal(std::abs(actualTurnPageRate));
    float longPointLeftCenterMoveRate = 0.0f;
    float longPointRightCenterMoveRate = 0.0f;
    if (isPressed_ && touchBottomTypeLoop_ == TouchBottomTypeLoop::TOUCH_BOTTOM_TYPE_LOOP_NONE) {
        longPointLeftCenterMoveRate = CubicCurve(turnPageRate_ > 0 ? LONG_POINT_LEFT_CENTER_BEZIER_CURVE_VELOCITY :
            LONG_POINT_RIGHT_CENTER_BEZIER_CURVE_VELOCITY, CENTER_BEZIER_CURVE_MASS, CENTER_BEZIER_CURVE_STIFFNESS,
            CENTER_BEZIER_CURVE_DAMPING).MoveInternal(std::abs(turnPageRate_));
        longPointRightCenterMoveRate = CubicCurve(turnPageRate_ > 0 ? LONG_POINT_RIGHT_CENTER_BEZIER_CURVE_VELOCITY :
            LONG_POINT_LEFT_CENTER_BEZIER_CURVE_VELOCITY, CENTER_BEZIER_CURVE_MASS, CENTER_BEZIER_CURVE_STIFFNESS,
            CENTER_BEZIER_CURVE_DAMPING).MoveInternal(std::abs(turnPageRate_));
    } else if (gestureState_ == GestureState::GESTURE_STATE_RELEASE_LEFT ||
               gestureState_ == GestureState::GESTURE_STATE_RELEASE_RIGHT) {
        blackPointCenterMoveRate = 1;
        longPointLeftCenterMoveRate = 1;
        longPointRightCenterMoveRate = 1;
    } else if (touchBottomTypeLoop_ == TouchBottomTypeLoop::TOUCH_BOTTOM_TYPE_LOOP_LEFT) {
        auto rateAbs = 1.0f - std::abs(actualTurnPageRate);
        // x0:0.33, y0:0, x1:0.67, y1:1
        longPointLeftCenterMoveRate = longPointRightCenterMoveRate = CubicCurve(0.33, 0, 0.67, 1).MoveInternal(rateAbs);
    } else if (touchBottomTypeLoop_ == TouchBottomTypeLoop::TOUCH_BOTTOM_TYPE_LOOP_RIGHT) {
        auto rateAbs = std::abs(actualTurnPageRate);
        // x0:0.33, y0:0, x1:0.67, y1:1
        longPointLeftCenterMoveRate = longPointRightCenterMoveRate = CubicCurve(0.33, 0, 0.67, 1).MoveInternal(rateAbs);
    } else if (gestureState_ == GestureState::GESTURE_STATE_FOLLOW_LEFT) {
        longPointLeftCenterMoveRate =std::abs(actualTurnPageRate);
        longPointRightCenterMoveRate = std::abs(actualTurnPageRate) +
                                       ((1 - longPointLeftCenterMoveRate) * LONG_POINT_TAIL_RATIO);
    } else if (gestureState_ == GestureState::GESTURE_STATE_FOLLOW_RIGHT) {
        longPointRightCenterMoveRate = std::abs(actualTurnPageRate);
        longPointLeftCenterMoveRate = std::abs(actualTurnPageRate) * LONG_POINT_TAIL_RATIO;
    }
    return { blackPointCenterMoveRate, longPointLeftCenterMoveRate, longPointRightCenterMoveRate };
}

std::pair<float, float> DotIndicatorPaintMethod::CalculatePointCenterX(
    const StarAndEndPointCenter& starAndEndPointCenter, const LinearVector<float>& startVectorBlackPointCenterX,
    const LinearVector<float>& endVectorBlackPointCenterX)
{
    const auto [blackPointCenterMoveRate, longPointLeftCenterMoveRate, longPointRightCenterMoveRate] = GetMoveRate();

    vectorBlackPointCenterX_.resize(itemCount_);
    for (int32_t i = 0; i < itemCount_; ++i) {
        vectorBlackPointCenterX_[i] = startVectorBlackPointCenterX[i] +
        (endVectorBlackPointCenterX[i] - startVectorBlackPointCenterX[i]) * blackPointCenterMoveRate;
    }

    std::pair<float, float> longPointCenterX;
    longPointCenterX.first = starAndEndPointCenter.startLongPointLeftCenterX +
        (starAndEndPointCenter.endLongPointLeftCenterX - starAndEndPointCenter.startLongPointLeftCenterX) *
            longPointLeftCenterMoveRate;
    longPointCenterX.second = starAndEndPointCenter.startLongPointRightCenterX +
        (starAndEndPointCenter.endLongPointRightCenterX - starAndEndPointCenter.startLongPointRightCenterX) *
            longPointRightCenterMoveRate;
    if (isHorizontalAndRightToLeft_) {
        longPointCenterX.first = starAndEndPointCenter.startLongPointLeftCenterX +
        (starAndEndPointCenter.endLongPointLeftCenterX - starAndEndPointCenter.startLongPointLeftCenterX) *
            longPointLeftCenterMoveRate;
        longPointCenterX.second = starAndEndPointCenter.startLongPointRightCenterX +
            (starAndEndPointCenter.endLongPointRightCenterX - starAndEndPointCenter.startLongPointRightCenterX) *
                longPointRightCenterMoveRate;
    }
    return longPointCenterX;
}

void DotIndicatorPaintMethod::CalculateHoverIndex(const LinearVector<float>& itemHalfSizes)
{
    CHECK_NULL_VOID(dotIndicatorModifier_);
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
    auto longPointCenterX = dotIndicatorModifier_->GetLongPointCenterX();

    OffsetF leftCenter = { longPointCenterX.first, centerY_ };
    OffsetF rightCenter = { longPointCenterX.second, centerY_ };
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
    CHECK_NULL_VOID(dotIndicatorModifier_);
    CHECK_NULL_VOID(paintWrapper);
    auto paintProperty = DynamicCast<DotIndicatorPaintProperty>(paintWrapper->GetPaintProperty());
    CHECK_NULL_VOID(paintProperty);
    auto indicatorTheme = GetSwiperIndicatorTheme();
    CHECK_NULL_VOID(indicatorTheme);

    // diameter calculation
    auto itemWidth = static_cast<float>(paintProperty->GetItemWidthValue(indicatorTheme->GetSize()).ConvertToPx());
    auto itemHeight = static_cast<float>(paintProperty->GetItemHeightValue(indicatorTheme->GetSize()).ConvertToPx());
    auto selectedItemWidth =
        static_cast<float>(paintProperty->GetSelectedItemWidthValue(indicatorTheme->GetSize()).ConvertToPx());
    auto selectedItemHeight =
        static_cast<float>(paintProperty->GetSelectedItemHeightValue(indicatorTheme->GetSize()).ConvertToPx());
    // use radius calculation
    LinearVector<float> itemHalfSizes;
    float indicatorScale = indicatorTheme->GetIndicatorScale();
    itemHalfSizes.emplace_back(itemWidth * HALF * indicatorScale);
    itemHalfSizes.emplace_back(itemHeight * HALF * indicatorScale);
    itemHalfSizes.emplace_back(selectedItemWidth * HALF * indicatorScale);
    itemHalfSizes.emplace_back(selectedItemHeight * HALF * indicatorScale);
    if (touchBottomType_ != TouchBottomType::NONE) {
        Dimension indicatorDotItemSpace = paintProperty->GetSpaceValue(indicatorTheme->GetIndicatorDotItemSpace());
        float allPointDiameterSum = itemWidth * static_cast<float>(itemCount_ + 1);
        if (IsCustomSizeValue_) {
            allPointDiameterSum = itemWidth * static_cast<float>(itemCount_ - 1) + selectedItemWidth;
        }
        float allPointSpaceSum = static_cast<float>(indicatorDotItemSpace.ConvertToPx()) * (itemCount_ - 1);
        Dimension paddingSide = indicatorTheme->GetIndicatorPaddingDot();
        float padding = static_cast<float>(paddingSide.ConvertToPx());
        float rectWidth = padding + allPointDiameterSum + allPointSpaceSum + padding;
        float newRectWidth =
            rectWidth * (TOUCH_BOTTOM_BACKGROUND_WIDTH_MULTIPLE - TOUCH_BOTTOM_DOT_WIDTH_MULTIPLE * itemCount_);
        auto changeValue = (newRectWidth - rectWidth) * touchBottomRate_;

        float space = static_cast<float>(indicatorDotItemSpace.ConvertToPx());
        if (itemCount_ > 1) {
            space = (rectWidth + changeValue - padding * 2 - allPointDiameterSum) / (itemCount_ - 1);
        }
        longPointCenterX_ = CalculatePointCenterX(itemHalfSizes, 0, padding, space, currentIndex_);
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

std::pair<int32_t, int32_t> DotIndicatorPaintMethod::GetIndexOnRTL(int32_t index)
{
    auto actualTurnPageRate = turnPageRate_;
    if (Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_EIGHTEEN) &&
        isSwipeByGroup_ && !NearZero(groupTurnPageRate_)) {
        actualTurnPageRate = groupTurnPageRate_;
    }

    int32_t startCurrentIndex = index;
    auto isInvalid = NearEqual(actualTurnPageRate, 0.0f) || LessOrEqualCustomPrecision(actualTurnPageRate, -1.0f) ||
                     GreatOrEqualCustomPrecision(actualTurnPageRate, 1.0f);
    if (!isInvalid) {
        startCurrentIndex = LessNotEqualCustomPrecision(actualTurnPageRate, 0.0f) ? index - 1 : index + 1;
    }

    if (startCurrentIndex <= -1) {
        if (isLoop_) {
            startCurrentIndex = itemCount_ - 1;
        } else {
            startCurrentIndex = 0;
            if (index <= -1) {
                index = 0;
            }
        }
    }

    return { startCurrentIndex, index };
}

std::pair<int32_t, int32_t> DotIndicatorPaintMethod::GetIndex(int32_t index)
{
    if (mouseClickIndex_ || gestureState_ == GestureState::GESTURE_STATE_RELEASE_LEFT ||
        gestureState_ == GestureState::GESTURE_STATE_RELEASE_RIGHT) {
        turnPageRate_ = 0;
        groupTurnPageRate_ = 0;
    }

    if (isHorizontalAndRightToLeft_ && !isPressed_) {
        return GetIndexOnRTL(index);
    }

    auto actualTurnPageRate = turnPageRate_;
    if (Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_EIGHTEEN) &&
        isSwipeByGroup_ && groupTurnPageRate_ != 0) {
        actualTurnPageRate = groupTurnPageRate_;
    }

    // item may be invalid in auto linear scene
    if (nextValidIndex_ >= 0) {
        int32_t startCurrentIndex = index;
        int32_t endCurrentIndex = NearEqual(turnPageRate_, 0.0f) || LessOrEqualCustomPrecision(turnPageRate_, -1.0f) ||
                                          GreatOrEqualCustomPrecision(turnPageRate_, 1.0f)
                                      ? index
                                      : nextValidIndex_;
        // reach edge scene
        if (startCurrentIndex > endCurrentIndex) {
            startCurrentIndex = currentIndexActual_;
            endCurrentIndex = currentIndexActual_;
        }
        return { startCurrentIndex, endCurrentIndex };
    }

    int32_t startCurrentIndex = index;
    int32_t endCurrentIndex = NearEqual(actualTurnPageRate, 0.0f) ||
        LessOrEqualCustomPrecision(actualTurnPageRate, -1.0f) || GreatOrEqualCustomPrecision(actualTurnPageRate, 1.0f)
                                  ? endCurrentIndex = index
                                  : (LessNotEqualCustomPrecision(actualTurnPageRate, 0.0f) ? index + 1 : index - 1);
    if (endCurrentIndex == -1) {
        endCurrentIndex = itemCount_ - 1;
    } else if (endCurrentIndex >= itemCount_) {
        if (isLoop_) {
            endCurrentIndex = 0;
        } else {
            if (startCurrentIndex >= itemCount_) {
                startCurrentIndex = itemCount_ - 1;
            }
            endCurrentIndex = itemCount_ - 1;
        }
    }

    return { startCurrentIndex, endCurrentIndex };
}

std::pair<int32_t, int32_t> DotIndicatorPaintMethod::GetStartAndEndIndex(int32_t index)
{
    auto [startCurrentIndex, endCurrentIndex] = GetIndex(index);

    if (pointAnimationStage_ == PointAnimationStage::STATE_EXPAND_TO_LONG_POINT &&
        gestureState_ == GestureState::GESTURE_STATE_RELEASE_LEFT &&
        touchBottomTypeLoop_ == TouchBottomTypeLoop::TOUCH_BOTTOM_TYPE_LOOP_LEFT) {
        endCurrentIndex = startCurrentIndex;
        return { startCurrentIndex, endCurrentIndex };
    } else if (pointAnimationStage_ == PointAnimationStage::STATE_EXPAND_TO_LONG_POINT &&
               gestureState_ == GestureState::GESTURE_STATE_RELEASE_RIGHT &&
               touchBottomTypeLoop_ == TouchBottomTypeLoop::TOUCH_BOTTOM_TYPE_LOOP_RIGHT) {
        endCurrentIndex = startCurrentIndex = 0;
        return { startCurrentIndex, endCurrentIndex };
    }

    auto actualTurnPageRate = Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_EIGHTEEN) &&
        isSwipeByGroup_ ? groupTurnPageRate_ : turnPageRate_;
    if (touchBottomTypeLoop_ != TouchBottomTypeLoop::TOUCH_BOTTOM_TYPE_LOOP_NONE && Negative(actualTurnPageRate)) {
        if (std::abs(actualTurnPageRate) >= FIFTY_PERCENT) {
            return { endCurrentIndex, endCurrentIndex };
        }

        return { startCurrentIndex, startCurrentIndex };
    }

    return { startCurrentIndex, endCurrentIndex };
}

bool DotIndicatorPaintMethod::AdjustPointCenterXForTouchBottomNew(StarAndEndPointCenter& pointCenter,
    LinearVector<float>& endVectorBlackPointCenterX, int32_t endCurrentIndex, float selectedItemWidth)
{
    auto pageRate = std::abs(touchBottomPageRate_);
    bool releaseLeftBottom = (gestureState_ == GestureState::GESTURE_STATE_RELEASE_LEFT &&
                              touchBottomTypeLoop_ == TouchBottomTypeLoop::TOUCH_BOTTOM_TYPE_LOOP_LEFT);
    bool releaseRightBottom = (gestureState_ == GestureState::GESTURE_STATE_RELEASE_RIGHT &&
                               touchBottomTypeLoop_ == TouchBottomTypeLoop::TOUCH_BOTTOM_TYPE_LOOP_RIGHT);
    if ((releaseLeftBottom && (!NearZero(touchBottomPageRate_) && pageRate <= FIFTY_PERCENT)) ||
        (releaseRightBottom && pageRate >= FIFTY_PERCENT)) {
        return true;
    }

    bool dragLeftBottom = (gestureState_ == GestureState::GESTURE_STATE_FOLLOW_LEFT &&
                           touchBottomTypeLoop_ == TouchBottomTypeLoop::TOUCH_BOTTOM_TYPE_LOOP_LEFT);
    bool dragRightBottom = (gestureState_ == GestureState::GESTURE_STATE_FOLLOW_RIGHT &&
                            touchBottomTypeLoop_ == TouchBottomTypeLoop::TOUCH_BOTTOM_TYPE_LOOP_RIGHT);
    if (dragLeftBottom && (!NearZero(touchBottomPageRate_) && pageRate <= FIFTY_PERCENT)) {
        pointCenter.startLongPointLeftCenterX = pointCenter.startLongPointRightCenterX =
            endVectorBlackPointCenterX[endCurrentIndex];
        pointCenter.endLongPointLeftCenterX =
            endVectorBlackPointCenterX[endCurrentIndex] - selectedItemWidth / HALF_SELECTED_WIDTH;
        pointCenter.endLongPointRightCenterX =
            endVectorBlackPointCenterX[endCurrentIndex] + selectedItemWidth / HALF_SELECTED_WIDTH;
        return true;
    }

    if (dragRightBottom && pageRate >= FIFTY_PERCENT) {
        pointCenter.startLongPointLeftCenterX = pointCenter.startLongPointRightCenterX = endVectorBlackPointCenterX[0];
        pointCenter.endLongPointLeftCenterX = endVectorBlackPointCenterX[0] - selectedItemWidth / HALF_SELECTED_WIDTH;
        pointCenter.endLongPointRightCenterX = endVectorBlackPointCenterX[0] + selectedItemWidth / HALF_SELECTED_WIDTH;
        return true;
    }

    return false;
}

void DotIndicatorPaintMethod::AdjustPointCenterXForTouchBottom(StarAndEndPointCenter& pointCenter,
    LinearVector<float>& endVectorBlackPointCenterX, int32_t startCurrentIndex, int32_t endCurrentIndex,
    float selectedItemWidth, int32_t index)
{
    if (AdjustPointCenterXForTouchBottomNew(
        pointCenter, endVectorBlackPointCenterX, endCurrentIndex, selectedItemWidth)) {
        return;
    }

    if (Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_EIGHTEEN) && isSwipeByGroup_ && !isLoop_) {
        return;
    }

    auto [startIndex, endIndex] = GetIndex(index);
    if (touchBottomTypeLoop_ == TouchBottomTypeLoop::TOUCH_BOTTOM_TYPE_LOOP_LEFT &&
        pointAnimationStage_ != PointAnimationStage::STATE_EXPAND_TO_LONG_POINT &&
        (!(endIndex == startIndex && startIndex != 0) ||
            (gestureState_ == GestureState::GESTURE_STATE_RELEASE_RIGHT ||
                gestureState_ == GestureState::GESTURE_STATE_RELEASE_LEFT))) {
        pointCenter.endLongPointRightCenterX = pointCenter.endLongPointLeftCenterX = endVectorBlackPointCenterX[0];
    } else if (touchBottomTypeLoop_ == TouchBottomTypeLoop::TOUCH_BOTTOM_TYPE_LOOP_RIGHT &&
               pointAnimationStage_ != PointAnimationStage::STATE_EXPAND_TO_LONG_POINT) {
        pointCenter.endLongPointRightCenterX = pointCenter.endLongPointLeftCenterX =
            endVectorBlackPointCenterX[startCurrentIndex];
    }

    if (pointAnimationStage_ == PointAnimationStage::STATE_EXPAND_TO_LONG_POINT &&
        gestureState_ == GestureState::GESTURE_STATE_RELEASE_LEFT &&
        touchBottomTypeLoop_ == TouchBottomTypeLoop::TOUCH_BOTTOM_TYPE_LOOP_LEFT) {
        pointCenter.startLongPointRightCenterX = endVectorBlackPointCenterX[endCurrentIndex];
        pointCenter.endLongPointLeftCenterX =
            endVectorBlackPointCenterX[endCurrentIndex] - (selectedItemWidth / HALF_SELECTED_WIDTH);
    } else if (pointAnimationStage_ == PointAnimationStage::STATE_EXPAND_TO_LONG_POINT &&
               gestureState_ == GestureState::GESTURE_STATE_RELEASE_RIGHT &&
               touchBottomTypeLoop_ == TouchBottomTypeLoop::TOUCH_BOTTOM_TYPE_LOOP_RIGHT) {
        pointCenter.startLongPointRightCenterX = endVectorBlackPointCenterX[0];
        pointCenter.endLongPointLeftCenterX = endVectorBlackPointCenterX[0] - (selectedItemWidth / HALF_SELECTED_WIDTH);
    }
}

std::pair<float, float> DotIndicatorPaintMethod::ForwardCalculation(
    const LinearVector<float>& itemHalfSizes, float startCenterX, float endCenterX, float space, int32_t index)
{
    auto itemWidth = itemHalfSizes[ITEM_HALF_WIDTH] * TWOFOLD;
    auto selectedItemWidth = itemHalfSizes[SELECTED_ITEM_HALF_WIDTH] * TWOFOLD;
    auto itemHalfWidth = itemHalfSizes[SELECTED_ITEM_HALF_WIDTH];
    if (IsCustomSizeValue_) {
        selectedItemWidth = itemHalfSizes[SELECTED_ITEM_HALF_WIDTH];
        itemHalfWidth = itemHalfSizes[SELECTED_ITEM_HALF_WIDTH] * HALF_FLOAT;
    }
    StarAndEndPointCenter pointCenter;
    // Calculate the data required for the current pages
    LinearVector<float> startVectorBlackPointCenterX(itemCount_);
    // Calculate the data required for subsequent pages
    LinearVector<float> endVectorBlackPointCenterX(itemCount_);

    auto [startCurrentIndex, endCurrentIndex] = GetStartAndEndIndex(index);
    for (int32_t i = 0; i < itemCount_; ++i) {
        if (i != startCurrentIndex) {
            startVectorBlackPointCenterX[i] = startCenterX + itemHalfSizes[ITEM_HALF_WIDTH];
            startCenterX += itemWidth;
        } else {
            startVectorBlackPointCenterX[i] = startCenterX + selectedItemWidth;
            pointCenter.startLongPointLeftCenterX = startCenterX + itemHalfWidth;
            pointCenter.startLongPointRightCenterX = pointCenter.startLongPointLeftCenterX + selectedItemWidth;
            startCenterX += selectedItemWidth * TWOFOLD;
        }
        if (i != endCurrentIndex) {
            endVectorBlackPointCenterX[i] = endCenterX + itemHalfSizes[ITEM_HALF_WIDTH];
            endCenterX += itemWidth;
        } else {
            endVectorBlackPointCenterX[i] = endCenterX + selectedItemWidth;
            pointCenter.endLongPointLeftCenterX = endCenterX + itemHalfWidth;
            pointCenter.endLongPointRightCenterX = pointCenter.endLongPointLeftCenterX + selectedItemWidth;
            endCenterX += selectedItemWidth * TWOFOLD;
        }
        startCenterX += space;
        endCenterX += space;
    }
    AdjustPointCenterXForTouchBottom(
        pointCenter, endVectorBlackPointCenterX, startCurrentIndex, endCurrentIndex, selectedItemWidth, index);
    return CalculatePointCenterX(pointCenter, startVectorBlackPointCenterX, endVectorBlackPointCenterX);
}

std::pair<float, float> DotIndicatorPaintMethod::BackwardCalculation(
    const LinearVector<float>& itemHalfSizes, float startCenterX, float endCenterX, float space, int32_t index)
{
    int32_t startCurrentIndex = index;
    auto itemWidth = itemHalfSizes[ITEM_HALF_WIDTH] * TWOFOLD;
    auto selectedItemWidth = itemHalfSizes[SELECTED_ITEM_HALF_WIDTH] * TWOFOLD;
    auto itemHalfWidth = itemHalfSizes[SELECTED_ITEM_HALF_WIDTH];
    if (IsCustomSizeValue_) {
        selectedItemWidth = itemHalfSizes[SELECTED_ITEM_HALF_WIDTH];
        itemHalfWidth = itemHalfSizes[SELECTED_ITEM_HALF_WIDTH] * HALF_FLOAT;
    }
    StarAndEndPointCenter pointCenter;
    // Calculate the data required for the current pages
    LinearVector<float> startVectorBlackPointCenterX(itemCount_);
    // Calculate the data required for subsequent pages
    LinearVector<float> endVectorBlackPointCenterX(itemCount_);
    int32_t endCurrentIndex = NearEqual(turnPageRate_, 0.0f) || turnPageRate_ <= -1.0f || turnPageRate_ >= 1.0f
        ? endCurrentIndex = index : (turnPageRate_ < 0.0f ? index + 1 : index - 1);
    if (endCurrentIndex == -1) {
        endCurrentIndex = itemCount_ - 1;
    } else if (endCurrentIndex == itemCount_) {
        endCurrentIndex = 0;
    }
    for (int32_t i = itemCount_ - 1; i >= 0; --i) {
        if (i != startCurrentIndex) {
            startVectorBlackPointCenterX[i] = startCenterX - itemHalfSizes[ITEM_HALF_WIDTH];
            startCenterX -= itemWidth;
        } else {
            startVectorBlackPointCenterX[i] = startCenterX - itemHalfWidth;
            pointCenter.startLongPointRightCenterX = startCenterX - itemHalfWidth;
            pointCenter.startLongPointLeftCenterX = pointCenter.startLongPointRightCenterX - selectedItemWidth;
            startCenterX -= selectedItemWidth * TWOFOLD;
        }
        if (i != endCurrentIndex) {
            endVectorBlackPointCenterX[i] = endCenterX - itemHalfSizes[ITEM_HALF_WIDTH];
            endCenterX -= itemWidth;
        } else {
            endVectorBlackPointCenterX[i] = endCenterX - itemHalfWidth;
            pointCenter.endLongPointRightCenterX = endCenterX - itemHalfWidth;
            pointCenter.endLongPointLeftCenterX = pointCenter.endLongPointRightCenterX - selectedItemWidth;
            endCenterX -= selectedItemWidth * TWOFOLD;
        }
        startCenterX -= space;
        endCenterX -= space;
    }
    return CalculatePointCenterX(pointCenter, startVectorBlackPointCenterX, endVectorBlackPointCenterX);
}
} // namespace OHOS::Ace::NG
