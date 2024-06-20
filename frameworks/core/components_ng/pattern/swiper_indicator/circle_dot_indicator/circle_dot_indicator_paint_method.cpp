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

#include "core/components_ng/pattern/swiper_indicator/circle_dot_indicator/circle_dot_indicator_paint_method.h"

#include <valarray>

#include "core/components/common/layout/constants.h"
#include "core/components/common/properties/color.h"
#include "core/components/swiper/render_swiper.h"
#include "core/components_ng/pattern/swiper/swiper_layout_property.h"
#include "core/components_ng/pattern/swiper_indicator/indicator_common/swiper_indicator_utils.h"
#include "core/components_ng/render/paint_property.h"
#include "core/pipeline/pipeline_base.h"

namespace OHOS::Ace::NG {
namespace {
constexpr uint32_t ITEM_PADDING = 3;
constexpr uint32_t SELECTED_ITEM_PADDING = 4;
constexpr uint32_t ACTIVE_ITEM_ANGLE = 5;

constexpr Dimension ITEM_SHRINK_DIAMETER = 5.0_vp;
constexpr Dimension SLECTED_ITEM_SHRINK_DIAMETER = 5.0_vp;
constexpr Dimension CONTAINER_SHRINK_DIAMETER = 16.0_vp;
constexpr float ITEM_SHRINK_PADDING = 5.0;
constexpr float SELECTED_ITEM_SHRINK_PADDING = 7.0;
constexpr float ACTIVE_ITEM_SHRINK_ANGLE = 4.0;
constexpr float BACKGROUND_OFFSET = 3.0;

constexpr Dimension ITEM_DILATE_DIAMETER = 8.0_vp;
constexpr Dimension SLECTED_ITEM_DILATE_DIAMETER = 8.0_vp;
constexpr Dimension CONTAINER_DILATE_DIAMETER = 24.0_vp;
constexpr float ITEM_DILATE_PADDING = 10.0;
constexpr float SELECTED_ITEM_DILATE_PADDING = 14.0;
constexpr float ACTIVE_ITEM_DILATE_ANGLE = 8.0;
constexpr double QUARTER_CIRCLE_ANGLE = 90.0;
constexpr double HALF_CIRCLE_ANGLE = 180.0;
constexpr int32_t ITEM_TWO_NUM = 2;
constexpr int32_t ITEM_THREE_NUM = 3;

constexpr Dimension ITEM_SHRINK_MINOR_DIAMETER = 3.5_vp;
constexpr Dimension ITEM_SHRINK_MINI_DIAMETER = 2.5_vp;
constexpr Dimension ITEM_DILATE_MINOR_DIAMETER = 6.0_vp;
constexpr Dimension ITEM_DILATE_MINI_DIAMETER = 4.0_vp;
constexpr int32_t LEFT_SECOND_DOT_INDEX = 1;
constexpr int32_t LEFT_THIRD_DOT_INDEX = 2;
constexpr int32_t RIGHT_SECOND_DOT_INDEX = 13;
constexpr int32_t RIGHT_FIRST_DOT_INDEX = 14;
constexpr int32_t HALF_DIVISOR = 2;
constexpr int32_t RELATIVE_STEP = 1;
} // namespace

void CircleDotIndicatorPaintMethod::UpdateContentModifier(PaintWrapper* paintWrapper)
{
    CHECK_NULL_VOID(circleDotIndicatorModifier_);
    CHECK_NULL_VOID(paintWrapper);
    auto pipelineContext = PipelineBase::GetCurrentContextSafely();
    CHECK_NULL_VOID(pipelineContext);
    auto swiperTheme = pipelineContext->GetTheme<SwiperIndicatorTheme>();
    CHECK_NULL_VOID(swiperTheme);
    const auto& geometryNode = paintWrapper->GetGeometryNode();
    CHECK_NULL_VOID(geometryNode);
    auto paintProperty = DynamicCast<CircleDotIndicatorPaintProperty>(paintWrapper->GetPaintProperty());
    CHECK_NULL_VOID(paintProperty);
    circleDotIndicatorModifier_->SetAxis(axis_);
    circleDotIndicatorModifier_->SetCurrentIndex(currentIndex_);
    arcDirection_ = paintProperty->GetArcDirectionValue(SwiperArcDirection::SIX_CLOCK_DIRECTION);
    circleDotIndicatorModifier_->SetArcDirection(
        paintProperty->GetArcDirectionValue(SwiperArcDirection::SIX_CLOCK_DIRECTION));
    circleDotIndicatorModifier_->SetUnselectedColor(paintProperty->GetColorValue(swiperTheme->GetArcItemColor()));
    circleDotIndicatorModifier_->SetSelectedColor(
        paintProperty->GetSelectedColorValue(swiperTheme->GetArcSelectedItemColor()));
    circleDotIndicatorModifier_->SetBackgroundColor(
        paintProperty->GetContainerColorValue(swiperTheme->GetArcContainerColor()));
    circleDotIndicatorModifier_->SetMaskColor(paintProperty->GetMaskColorValue(swiperTheme->GetArcMaskColor()));

    const auto& contentSize = geometryNode->GetFrameSize();
    //The number 0.5 represents equal division
    float centerY = (axis_ == Axis::HORIZONTAL ? contentSize.Height() : contentSize.Width()) * 0.5;
    float centerX = (axis_ == Axis::HORIZONTAL ? contentSize.Width() : contentSize.Height()) * 0.5;
    float centerR = std::min(centerX, centerY);
    circleDotIndicatorModifier_->SetCenterX(centerX);
    circleDotIndicatorModifier_->SetCenterY(centerY);
    circleDotIndicatorModifier_->SetCircleRadius(centerR);

    if (isLongPressed_) {
        PaintPressIndicator(paintWrapper);
        circleDotIndicatorModifier_->SetIsPressed(true);
        UpdateBackground(paintWrapper);
    } else {
        PaintNormalIndicator(paintWrapper);
        circleDotIndicatorModifier_->SetIsPressed(false);
    }
}

void CircleDotIndicatorPaintMethod::UpdateNormalIndicator(
    LinearVector<float>& itemSizes, const PaintWrapper* paintWrapper)
{
    if (gestureState_ == GestureState::GESTURE_STATE_RELEASE_LEFT ||
        gestureState_ == GestureState::GESTURE_STATE_RELEASE_RIGHT) {
        circleDotIndicatorModifier_->PlayIndicatorAnimation(vectorBlackPointAngle_, vectorBlackPointRadius_,
                                                            longPointAngle_, gestureState_);
    } else {
        circleDotIndicatorModifier_->UpdateNormalPaintProperty(itemSizes, vectorBlackPointAngle_,
                                                               vectorBlackPointRadius_, longPointAngle_);
    }
}

void CircleDotIndicatorPaintMethod::PaintNormalIndicator(const PaintWrapper* paintWrapper)
{
    auto [longPointAngle, itemSizes] = CalculateLongPointCenterAngle(paintWrapper, true);
    longPointAngle_ = longPointAngle;
    if (circleDotIndicatorModifier_->GetIsPressed()) {
        circleDotIndicatorModifier_->UpdatePressToNormalPaintProperty(
            itemSizes, vectorBlackPointAngle_, vectorBlackPointRadius_, longPointAngle_);
    } else {
        UpdateNormalIndicator(itemSizes, paintWrapper);
    }
}

void CircleDotIndicatorPaintMethod::PaintPressIndicator(const PaintWrapper* paintWrapper)
{
    CHECK_NULL_VOID(paintWrapper);
    LinearVector<float> itemSizes;
    // The number 0.5 represents equal division
    itemSizes.emplace_back(static_cast<float>(ITEM_DILATE_DIAMETER.ConvertToPx()) * 0.5);
    itemSizes.emplace_back(static_cast<float>(SLECTED_ITEM_DILATE_DIAMETER.ConvertToPx()) * 0.5);
    itemSizes.emplace_back(static_cast<float>(CONTAINER_DILATE_DIAMETER.ConvertToPx()) * 0.5);
    itemSizes.emplace_back(ITEM_DILATE_PADDING);
    itemSizes.emplace_back(SELECTED_ITEM_DILATE_PADDING);
    itemSizes.emplace_back(ACTIVE_ITEM_DILATE_ANGLE);

    longPointAngle_ = CalculatePointAngle(itemSizes, currentIndex_);
    if (circleDotIndicatorModifier_->GetIsPressed()) {
        circleDotIndicatorModifier_->PlayIndicatorAnimation(vectorBlackPointAngle_, vectorBlackPointRadius_,
                                                            longPointAngle_, gestureState_);
    } else {
        circleDotIndicatorModifier_->UpdateNormalToPressPaintProperty(
            itemSizes, vectorBlackPointAngle_, vectorBlackPointRadius_, longPointAngle_);
    }
}

void CircleDotIndicatorPaintMethod::CalculatePointRadius(int32_t index, int32_t indicatorStartIndex)
{
    float itemMiniRadius = 0.0;
    float itemMinorRadius = 0.0;
    float itemNormalRadius = 0.0;
    if (isLongPressed_) {
        itemMiniRadius = ITEM_DILATE_MINI_DIAMETER.ConvertToPx() / HALF_DIVISOR;
        itemMinorRadius = ITEM_DILATE_MINOR_DIAMETER.ConvertToPx() / HALF_DIVISOR;
        itemNormalRadius = ITEM_DILATE_DIAMETER.ConvertToPx() / HALF_DIVISOR;
    } else {
        itemMiniRadius = ITEM_SHRINK_MINI_DIAMETER.ConvertToPx() / HALF_DIVISOR;
        itemMinorRadius = ITEM_SHRINK_MINOR_DIAMETER.ConvertToPx() / HALF_DIVISOR;
        itemNormalRadius = ITEM_SHRINK_DIAMETER.ConvertToPx() / HALF_DIVISOR;
    }
    if (itemCount_ > MAX_INDICATOR_DOT_COUNT) {
        bool unsetFlag =
            CalculateStartPointRadius(index, itemNormalRadius, itemMinorRadius, itemMiniRadius, indicatorStartIndex);
        if (unsetFlag) {
            CalculateRemainPointRadius(index, itemNormalRadius, itemMinorRadius, itemMiniRadius, indicatorStartIndex);
        }
    } else {
        vectorBlackPointRadius_[index] = itemNormalRadius;
    }
}

bool CircleDotIndicatorPaintMethod::CalculateStartPointRadius(
    int32_t index, float itemNormalRadius, float itemMinorRadius, float itemMiniRadius, int32_t indicatorStartIndex)
{
    bool unsetFlag = false;
    if (indicatorStartIndex > 0) {
        if (index < indicatorStartIndex) {
            vectorBlackPointRadius_[index] = 0;
        } else if (index == indicatorStartIndex) {
            vectorBlackPointRadius_[index] = itemMiniRadius;
        } else if (index == indicatorStartIndex + LEFT_SECOND_DOT_INDEX) {
            vectorBlackPointRadius_[index] = itemMinorRadius;
        } else {
            unsetFlag = true;
        }
    } else {
        if (index < indicatorStartIndex + LEFT_SECOND_DOT_INDEX) {
            vectorBlackPointRadius_[index] = itemNormalRadius;
        } else {
            unsetFlag = true;
        }
    }
    return unsetFlag;
}

void CircleDotIndicatorPaintMethod::CalculateRemainPointRadius(
    int32_t index, float itemNormalRadius, float itemMinorRadius, float itemMiniRadius, int32_t indicatorStartIndex)
{
    if (indicatorStartIndex + MAX_INDICATOR_DOT_COUNT < itemCount_) {
        if (index == indicatorStartIndex + RIGHT_SECOND_DOT_INDEX) {
            vectorBlackPointRadius_[index] = itemMinorRadius;
        } else if (index == indicatorStartIndex + RIGHT_FIRST_DOT_INDEX) {
            vectorBlackPointRadius_[index] = itemMiniRadius;
        } else if (index > indicatorStartIndex + RIGHT_FIRST_DOT_INDEX) {
            vectorBlackPointRadius_[index] = 0;
        } else {
            vectorBlackPointRadius_[index] = itemNormalRadius;
        }
    } else {
        vectorBlackPointRadius_[index] = itemNormalRadius;
    }
}

float CircleDotIndicatorPaintMethod::CalculateBlackPointRotateAngle(int32_t indicatorStartIndex)
{
    if (itemCount_ > MAX_INDICATOR_DOT_COUNT) {
        auto itemPadding = ITEM_SHRINK_PADDING;
        if (isLongPressed_) {
            itemPadding = ITEM_DILATE_PADDING;
        }
        return -((itemCount_ - MAX_INDICATOR_DOT_COUNT) / HALF_DIVISOR - indicatorStartIndex) * itemPadding;
    } else {
        return 0.0;
    }
}

int32_t CircleDotIndicatorPaintMethod::CalculateIndicatorStartIndex()
{
    if (itemCount_ > MAX_INDICATOR_DOT_COUNT) {
        auto priorIndicatorIndex = circleDotIndicatorModifier_->GetIndicatorStartIndex();
        int32_t indicatorStartIndex = priorIndicatorIndex;
        if (gestureState_ == GestureState::GESTURE_STATE_RELEASE_RIGHT) {
            if (currentIndex_ >= MAX_INDICATOR_DOT_COUNT - TRIGGER_BOUNDARY_DISTANCE &&
                currentIndex_ < itemCount_ - TRIGGER_BOUNDARY_DISTANCE &&
                currentIndex_ - priorIndicatorIndex >= RIGHT_SECOND_DOT_INDEX) {
                indicatorStartIndex =
                    currentIndex_ - (MAX_INDICATOR_DOT_COUNT - TRIGGER_BOUNDARY_DISTANCE) + RELATIVE_STEP;
            } else if (currentIndex_ >= itemCount_ - TRIGGER_BOUNDARY_DISTANCE) {
                indicatorStartIndex = itemCount_ - MAX_INDICATOR_DOT_COUNT;
            }
        } else if (gestureState_ == GestureState::GESTURE_STATE_RELEASE_LEFT) {
            if (currentIndex_ < itemCount_ - RIGHT_SECOND_DOT_INDEX && currentIndex_ >= LEFT_THIRD_DOT_INDEX &&
                currentIndex_ - priorIndicatorIndex < LEFT_THIRD_DOT_INDEX) {
                indicatorStartIndex = currentIndex_ - LEFT_THIRD_DOT_INDEX;
            } else if (currentIndex_ < LEFT_THIRD_DOT_INDEX) {
                indicatorStartIndex = 0;
            }
        }
        circleDotIndicatorModifier_->SetIndicatorStartIndex(indicatorStartIndex);
        return indicatorStartIndex;
    } else {
        return 0;
    }
}

std::pair<float, float> CircleDotIndicatorPaintMethod::CalculatePointAngle(
    const LinearVector<float>& itemSizes, int32_t currentIndex)
{
    if (itemCount_ == 0) {
        return {0.0, 0.0};
    }
    auto [startCurrentIndex, endCurrentIndex] = GetStartAndEndIndex(currentIndex);
    int index = endCurrentIndex;
    if (gestureState_ == GestureState::GESTURE_STATE_FOLLOW_RIGHT) {
        index = startCurrentIndex;
    }
    int32_t indicatorStartIndex = CalculateIndicatorStartIndex();
    vectorBlackPointAngle_.resize(itemCount_);
    vectorBlackPointRadius_.resize(itemCount_);
    float offset = CalculateBlackPointRotateAngle(indicatorStartIndex);
    for (int32_t i = 0; i < itemCount_; ++i) {
        vectorBlackPointAngle_[i] = GetBlackPointAngle(itemSizes, i, index, offset);
        CalculatePointRadius(i, indicatorStartIndex);
    }

    return GetLongPointAngle(itemSizes, index, indicatorStartIndex);
}

std::tuple<std::pair<float, float>, LinearVector<float>> CircleDotIndicatorPaintMethod::CalculateLongPointCenterAngle(
    const PaintWrapper* paintWrapper, bool isNormal)
{
    std::tuple<std::pair<float, float>, LinearVector<float>> tmp;
    CHECK_NULL_RETURN(paintWrapper, tmp);
    LinearVector<float> itemSizes;
    // The number 0.5 represents equal division
    if (isNormal) {
        itemSizes.emplace_back(static_cast<float>(ITEM_SHRINK_DIAMETER.ConvertToPx()) * 0.5);
        itemSizes.emplace_back(static_cast<float>(SLECTED_ITEM_SHRINK_DIAMETER.ConvertToPx()) * 0.5);
        itemSizes.emplace_back(static_cast<float>(CONTAINER_SHRINK_DIAMETER.ConvertToPx()) * 0.5);
        itemSizes.emplace_back(ITEM_SHRINK_PADDING);
        itemSizes.emplace_back(SELECTED_ITEM_SHRINK_PADDING);
        itemSizes.emplace_back(ACTIVE_ITEM_SHRINK_ANGLE);
    } else {
        itemSizes.emplace_back(static_cast<float>(ITEM_DILATE_DIAMETER.ConvertToPx()) * 0.5);
        itemSizes.emplace_back(static_cast<float>(SLECTED_ITEM_DILATE_DIAMETER.ConvertToPx()) * 0.5);
        itemSizes.emplace_back(static_cast<float>(CONTAINER_DILATE_DIAMETER.ConvertToPx()) * 0.5);
        itemSizes.emplace_back(ITEM_DILATE_PADDING);
        itemSizes.emplace_back(SELECTED_ITEM_DILATE_PADDING);
        itemSizes.emplace_back(ACTIVE_ITEM_DILATE_ANGLE);
    }

    auto longPointAngle = CalculatePointAngle(itemSizes, currentIndex_);
    return { longPointAngle, itemSizes };
}

int32_t CircleDotIndicatorPaintMethod::GetHalfIndex()
{
    if (itemCount_ == 1) {
        return itemCount_ - 1;
    }
    if (itemCount_ % 2 == 0) {
        return (itemCount_ / 2) - 1;
    }
    return (itemCount_ - 1) / 2;
}

std::pair<int32_t, int32_t> CircleDotIndicatorPaintMethod::GetLongPointAngle(
    const LinearVector<float>& itemSizes, int32_t currentIndex, int32_t indicatorStartIndex)
{
    float dotActiveAngle = itemSizes[ACTIVE_ITEM_ANGLE];
    float offset = CalculateBlackPointRotateAngle(indicatorStartIndex);
    float selectItemAngle = GetBlackPointAngle(itemSizes, currentIndex, currentIndex, offset);
    float LongPointStartAngle = 0.0;
    float LongPointEndAngle = 0.0;
    // The number 2 represents equal division
    if (arcDirection_ == SwiperArcDirection::SIX_CLOCK_DIRECTION) {
        LongPointStartAngle = QUARTER_CIRCLE_ANGLE + selectItemAngle + dotActiveAngle / 2;
    } else if (arcDirection_ == SwiperArcDirection::THREE_CLOCK_DIRECTION) {
        LongPointStartAngle = selectItemAngle + dotActiveAngle / 2;
    } else {
        LongPointStartAngle = HALF_CIRCLE_ANGLE + selectItemAngle + dotActiveAngle / 2;
    }
    LongPointEndAngle = LongPointStartAngle - dotActiveAngle;
    return { LongPointStartAngle, LongPointEndAngle };
}

float CircleDotIndicatorPaintMethod::GetAllPointArcAngle(const LinearVector<float>& itemSizes, int32_t currentIndex)
{
    float dotPaddingAngle = itemSizes[ITEM_PADDING];
    float dotActivePaddingAngle = itemSizes[SELECTED_ITEM_PADDING];
    float dotActiveAngle = itemSizes[ACTIVE_ITEM_ANGLE];
    float allPointArcAngle = 0;
    // The number 2 represents equal division
    if (currentIndex == 0 || currentIndex == itemCount_ - 1) {
        if (itemCount_ >= ITEM_TWO_NUM) {
            allPointArcAngle =
                (itemCount_ - ITEM_TWO_NUM) * dotPaddingAngle + dotActivePaddingAngle + dotActiveAngle / 2;
        } else {
            allPointArcAngle = dotActiveAngle;
        }
    } else {
        allPointArcAngle = (itemCount_ - ITEM_THREE_NUM) * dotPaddingAngle + dotActivePaddingAngle * 2;
    }
    return allPointArcAngle;
}

float CircleDotIndicatorPaintMethod::GetBlackPointAngle(
    const LinearVector<float>& itemSizes, int32_t index, int32_t currentIndex, float offset)
{
    float dotPaddingAngle = itemSizes[ITEM_PADDING];
    float dotActivePaddingAngle = itemSizes[SELECTED_ITEM_PADDING];
    float dotActiveAngle = itemSizes[ACTIVE_ITEM_ANGLE];
    float allPointArcAngle = GetAllPointArcAngle(itemSizes, currentIndex);

    float itemCenterAngle = 0.0;
    int32_t itemIndex = index;
    int32_t halIndex = GetHalfIndex();
    if (itemIndex <= halIndex) {
        if (itemCount_ == 1) {
            itemCenterAngle = 0.0;
        } else if (currentIndex == 0) {
            if (itemIndex == 0) {
                itemCenterAngle = (allPointArcAngle / 2) - (dotActiveAngle / 2);
            } else {
                itemCenterAngle = (allPointArcAngle / 2) - (dotActiveAngle / 2) -
                    dotActivePaddingAngle - (itemIndex -1) * dotPaddingAngle;
            }
        } else if (itemIndex == currentIndex) {
            itemCenterAngle = (allPointArcAngle / 2) - (itemIndex -1) * dotPaddingAngle - dotActivePaddingAngle;
        } else if (itemIndex > currentIndex) {
            itemCenterAngle = (allPointArcAngle / 2) - (itemIndex -2) * dotPaddingAngle - dotActivePaddingAngle * 2;
        } else {
            itemCenterAngle = (allPointArcAngle / 2) - itemIndex * dotPaddingAngle;
        }
    } else {
        if (itemIndex == 0) {
            itemCenterAngle = (dotActiveAngle / 2) + dotActivePaddingAngle +
                (itemIndex -1) * dotPaddingAngle - (allPointArcAngle / 2);
        } else if (itemIndex == currentIndex) {
            itemCenterAngle = (itemIndex - 1) * dotPaddingAngle + dotActivePaddingAngle - (allPointArcAngle / 2);
        } else if (itemIndex > currentIndex) {
            itemCenterAngle =
                (itemIndex - ITEM_TWO_NUM) * dotPaddingAngle + dotActivePaddingAngle * 2 - (allPointArcAngle / 2);
        } else {
            itemCenterAngle = itemIndex * dotPaddingAngle - (allPointArcAngle / 2);
        }
        itemCenterAngle = -itemCenterAngle;
    }
    return itemCenterAngle + offset;
}

std::pair<int32_t, int32_t> CircleDotIndicatorPaintMethod::GetIndex(int32_t index)
{
    if (mouseClickIndex_ || gestureState_ == GestureState::GESTURE_STATE_RELEASE_LEFT ||
        gestureState_ == GestureState::GESTURE_STATE_RELEASE_RIGHT) {
        turnPageRate_ = 0;
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
    int32_t endCurrentIndex = NearEqual(turnPageRate_, 0.0f) || LessOrEqualCustomPrecision(turnPageRate_, -1.0f) ||
                                      GreatOrEqualCustomPrecision(turnPageRate_, 1.0f)
                                  ? endCurrentIndex = index
                                  : (LessNotEqualCustomPrecision(turnPageRate_, 0.0f) ? index + 1 : index - 1);
    if (endCurrentIndex == -1) {
        endCurrentIndex = itemCount_ - 1;
    } else if (endCurrentIndex == itemCount_) {
        endCurrentIndex = 0;
    }
    return { startCurrentIndex, endCurrentIndex };
}

std::pair<int32_t, int32_t> CircleDotIndicatorPaintMethod::GetStartAndEndIndex(int32_t index)
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

    if (touchBottomTypeLoop_ == TouchBottomTypeLoop::TOUCH_BOTTOM_TYPE_LOOP_LEFT &&
        !(endCurrentIndex == startCurrentIndex && startCurrentIndex != 0)) {
        startCurrentIndex = endCurrentIndex = 0;
    } else if (gestureState_ == GestureState::GESTURE_STATE_RELEASE_RIGHT &&
               touchBottomTypeLoop_ == TouchBottomTypeLoop::TOUCH_BOTTOM_TYPE_LOOP_RIGHT) {
        endCurrentIndex = startCurrentIndex = itemCount_ - 1;
    } else if (touchBottomTypeLoop_ == TouchBottomTypeLoop::TOUCH_BOTTOM_TYPE_LOOP_RIGHT) {
        endCurrentIndex = startCurrentIndex;
    }

    return { startCurrentIndex, endCurrentIndex };
}

void CircleDotIndicatorPaintMethod::UpdateBackground(const PaintWrapper* paintWrapper)
{
    float offset = 0.0;
    auto offSetPoint = vectorBlackPointAngle_;
    if (gestureState_ == GestureState::GESTURE_STATE_FOLLOW_RIGHT) {
        for (size_t indexLeft = 0; indexLeft < currentIndex_; indexLeft++) {
            offSetPoint[indexLeft] -= BACKGROUND_OFFSET / itemCount_;
            offset -= BACKGROUND_OFFSET / itemCount_;
        }
    }

    if (gestureState_ == GestureState::GESTURE_STATE_FOLLOW_LEFT) {
        for (size_t indexRight = itemCount_ - 1; indexRight > currentIndex_; indexRight--) {
            offSetPoint[indexRight] += BACKGROUND_OFFSET / itemCount_;
            offset += BACKGROUND_OFFSET / itemCount_;
        }
    }

    circleDotIndicatorModifier_->UpdateTouchBottomAnimation(touchBottomType_, offSetPoint, longPointAngle_, offset);
    return;
}
} // namespace OHOS::Ace::NG
