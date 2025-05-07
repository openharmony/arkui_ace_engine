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
constexpr uint32_t ITEM_MINOR_PADDING = 6;
constexpr uint32_t ITEM_MINI_PADDING = 7;

constexpr Dimension ITEM_SHRINK_RADIUS = 2.5_vp;
constexpr Dimension SLECTED_ITEM_SHRINK_RADIUS = 2.5_vp;
constexpr Dimension CONTAINER_SHRINK_RADIUS = 8.0_vp;
constexpr float ITEM_SHRINK_PADDING = 5.0;
constexpr float ITEM_SHRINK_MINOR_PADDING = 4.5;
constexpr float ITEM_SHRINK_MINI_PADDING = 4.0;
constexpr float ITEM_SHRINK_FADE_PADDING = 3.5;
constexpr float SELECTED_ITEM_SHRINK_PADDING = 7.0;
constexpr float ACTIVE_ITEM_SHRINK_ANGLE = 4.0;

constexpr Dimension ITEM_DILATE_RADIUS = 4.0_vp;
constexpr Dimension SLECTED_ITEM_DILATE_RADIUS = 4.0_vp;
constexpr Dimension CONTAINER_DILATE_RADIUS = 12.0_vp;
constexpr float ITEM_DILATE_PADDING = 10.0;
constexpr float ITEM_DILATE_MINOR_PADDING = 9.0;
constexpr float ITEM_DILATE_MINI_PADDING = 8.0;
constexpr float ITEM_DILATE_FADE_PADDING = 6.0;
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
constexpr int32_t RIGHT_THIRD_DOT_INDEX = 12;
constexpr int32_t RIGHT_SECOND_DOT_INDEX = 13;
constexpr int32_t RIGHT_FIRST_DOT_INDEX = 14;
constexpr int32_t HALF_DIVISOR = 2;
constexpr int32_t DIPLOID = 2;
constexpr int32_t NUMBER_TWO = 2;
constexpr int32_t ACTUAL_SUBTRACT_INDEX = 1;
constexpr float BLACK_POINT_CENTER_BEZIER_CURVE_VELOCITY = 0.4f;
constexpr float CENTER_BEZIER_CURVE_MASS = 0.0f;
constexpr float CENTER_BEZIER_CURVE_STIFFNESS = 1.0f;
constexpr float CENTER_BEZIER_CURVE_DAMPING = 1.0f;
constexpr float LONG_POINT_TAIL_RATIO = 0.5f;
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
    if (isHorizontalAndRightToLeft_) {
        currentIndex_ = itemCount_ - 1 - currentIndex_;
    }

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
    // The number 0.5 represents equal division
    float centerY = (axis_ == Axis::HORIZONTAL ? contentSize.Height() : contentSize.Width()) * 0.5;
    float centerX = (axis_ == Axis::HORIZONTAL ? contentSize.Width() : contentSize.Height()) * 0.5;
    float centerR = std::min(centerX, centerY);
    circleDotIndicatorModifier_->SetCenterX(centerX);
    circleDotIndicatorModifier_->SetCenterY(centerY);
    circleDotIndicatorModifier_->SetCircleRadius(centerR);
    circleDotIndicatorModifier_->SetTouchBottomRate(touchBottomRate_);
    circleDotIndicatorModifier_->SetTouchBottomType(touchBottomType_);

    if (isLongPressed_) {
        PaintPressIndicator(paintWrapper);
        circleDotIndicatorModifier_->SetIsPressed(true);
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
        circleDotIndicatorModifier_->PlayIndicatorAnimation(
            vectorBlackPointAngle_, vectorBlackPointRadius_, longPointAngle_, gestureState_);
    } else {
        circleDotIndicatorModifier_->UpdateNormalPaintProperty(
            itemSizes, vectorBlackPointAngle_, vectorBlackPointRadius_, longPointAngle_);
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
        CalculatePointCenterAngle();
        UpdateNormalIndicator(itemSizes, paintWrapper);
    }
}

void CircleDotIndicatorPaintMethod::PaintPressIndicator(const PaintWrapper* paintWrapper)
{
    CHECK_NULL_VOID(paintWrapper);
    LinearVector<float> itemSizes;
    // The number 0.5 represents equal division
    itemSizes.emplace_back(static_cast<float>(ITEM_DILATE_RADIUS.ConvertToPx()));
    itemSizes.emplace_back(static_cast<float>(SLECTED_ITEM_DILATE_RADIUS.ConvertToPx()));
    itemSizes.emplace_back(static_cast<float>(CONTAINER_DILATE_RADIUS.ConvertToPx()));
    itemSizes.emplace_back(ITEM_DILATE_PADDING);
    itemSizes.emplace_back(SELECTED_ITEM_DILATE_PADDING);
    itemSizes.emplace_back(ACTIVE_ITEM_DILATE_ANGLE);
    itemSizes.emplace_back(ITEM_DILATE_MINOR_PADDING);
    itemSizes.emplace_back(ITEM_DILATE_MINI_PADDING);

    longPointAngle_ = CalculatePointAngle(itemSizes, currentIndex_);
    if (circleDotIndicatorModifier_->GetIsPressed()) {
        if (touchBottomType_ != TouchBottomType::NONE) {
            UpdateBackground(paintWrapper);
            return;
        }
        circleDotIndicatorModifier_->PlayIndicatorAnimation(
            vectorBlackPointAngle_, vectorBlackPointRadius_, longPointAngle_, gestureState_);
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
        itemNormalRadius = ITEM_DILATE_RADIUS.ConvertToPx();
    } else {
        itemMiniRadius = ITEM_SHRINK_MINI_DIAMETER.ConvertToPx() / HALF_DIVISOR;
        itemMinorRadius = ITEM_SHRINK_MINOR_DIAMETER.ConvertToPx() / HALF_DIVISOR;
        itemNormalRadius = ITEM_SHRINK_RADIUS.ConvertToPx();
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

float CircleDotIndicatorPaintMethod::CalculateBlackPointRotateAngle(int32_t indicatorStartIndex, int32_t itemIndex)
{
    if (itemCount_ > MAX_INDICATOR_DOT_COUNT) {
        auto itemPadding = ITEM_SHRINK_PADDING;
        auto fadePadding = ITEM_SHRINK_PADDING - ITEM_SHRINK_FADE_PADDING;
        if (isLongPressed_) {
            itemPadding = ITEM_DILATE_PADDING;
            fadePadding = ITEM_DILATE_PADDING - ITEM_DILATE_FADE_PADDING;
        }
        auto rotateAngle = -((itemCount_ - MAX_INDICATOR_DOT_COUNT) / HALF_DIVISOR - indicatorStartIndex) * itemPadding;
        if (itemCount_ % HALF_DIVISOR == 0) {
            rotateAngle = rotateAngle - itemPadding / HALF_DIVISOR;
        }
        if (itemIndex < indicatorStartIndex) {
            rotateAngle = rotateAngle - ((indicatorStartIndex - itemIndex - 1) * itemPadding + fadePadding);
        }
        if (itemIndex >= indicatorStartIndex + MAX_INDICATOR_DOT_COUNT) {
            rotateAngle = rotateAngle +
                          ((itemIndex - (indicatorStartIndex + MAX_INDICATOR_DOT_COUNT)) * itemPadding + fadePadding);
        }
        return rotateAngle;
    } else {
        return 0.0;
    }
}

int32_t CircleDotIndicatorPaintMethod::CalculateIndicatorStartIndex(int32_t priorIndicatorIndex)
{
    if (itemCount_ > MAX_INDICATOR_DOT_COUNT) {
        int32_t indicatorStartIndex = priorIndicatorIndex;
        if ((!isLongPressed_ && gestureState_ == GestureState::GESTURE_STATE_RELEASE_RIGHT) ||
            (isLongPressed_ && gestureState_ == GestureState::GESTURE_STATE_FOLLOW_RIGHT)) {
            if (currentIndex_ >= MAX_INDICATOR_DOT_COUNT - TRIGGER_BOUNDARY_DISTANCE &&
                currentIndex_ < itemCount_ - TRIGGER_BOUNDARY_DISTANCE &&
                currentIndex_ - priorIndicatorIndex >= RIGHT_SECOND_DOT_INDEX) {
                indicatorStartIndex =
                    currentIndex_ - (MAX_INDICATOR_DOT_COUNT - TRIGGER_BOUNDARY_DISTANCE) + ACTUAL_SUBTRACT_INDEX;
            } else if (currentIndex_ >= itemCount_ - TRIGGER_BOUNDARY_DISTANCE) {
                indicatorStartIndex = itemCount_ - MAX_INDICATOR_DOT_COUNT;
            }
        } else if ((!isLongPressed_ && gestureState_ == GestureState::GESTURE_STATE_RELEASE_LEFT) ||
                   (isLongPressed_ && gestureState_ == GestureState::GESTURE_STATE_FOLLOW_LEFT)) {
            if (currentIndex_ < itemCount_ - RIGHT_SECOND_DOT_INDEX && currentIndex_ >= LEFT_THIRD_DOT_INDEX &&
                currentIndex_ - priorIndicatorIndex < LEFT_THIRD_DOT_INDEX) {
                indicatorStartIndex = currentIndex_ - LEFT_THIRD_DOT_INDEX;
            } else if (currentIndex_ < LEFT_THIRD_DOT_INDEX) {
                indicatorStartIndex = 0;
            }
        }
        circleDotIndicatorModifier_->SetIndicatorStartIndex(indicatorStartIndex);
        indicatorStartIndex_ = indicatorStartIndex;
        return indicatorStartIndex;
    } else {
        return 0;
    }
}

int32_t CircleDotIndicatorPaintMethod::CalculateInitIndicatorPosition()
{
    int32_t indicatorStartIndex = 0;
    if (itemCount_ > MAX_INDICATOR_DOT_COUNT) {
        if (currentIndex_ > MAX_INDICATOR_DOT_COUNT / HALF_DIVISOR &&
            currentIndex_ < itemCount_ - (MAX_INDICATOR_DOT_COUNT / HALF_DIVISOR)) {
            indicatorStartIndex = currentIndex_ - (MAX_INDICATOR_DOT_COUNT / HALF_DIVISOR);
        } else if (currentIndex_ >= itemCount_ - (MAX_INDICATOR_DOT_COUNT / HALF_DIVISOR)) {
            indicatorStartIndex = itemCount_ - MAX_INDICATOR_DOT_COUNT;
        } else {
            indicatorStartIndex = 0;
        }
        circleDotIndicatorModifier_->SetInitState(false);
        circleDotIndicatorModifier_->SetIndicatorStartIndex(indicatorStartIndex);
    }
    indicatorStartIndex_ = indicatorStartIndex;
    return indicatorStartIndex;
}

void CircleDotIndicatorPaintMethod::SetFadeOutState(int32_t indicatorStartIndex)
{
    if (itemCount_ > MAX_INDICATOR_DOT_COUNT) {
        if (indicatorStartIndex > 0 && indicatorStartIndex < itemCount_ - MAX_INDICATOR_DOT_COUNT) {
            // fadeOut bilateral
            fadeOutState_ = FadeOutState::FADE_OUT_BILATERAL;
        } else if (indicatorStartIndex == 0) {
            // fadeOut right
            fadeOutState_ = FadeOutState::FADE_OUT_RIGHT;
        } else {
            // fadeOut left
            fadeOutState_ = FadeOutState::FADE_OUT_LEFT;
        }
    } else {
        // fadeOut none
        fadeOutState_ = FadeOutState::FADE_OUT_NONE;
    }
}

float CircleDotIndicatorPaintMethod::GetFadeOutPadding(float dotPaddingAngle, int32_t itemIndex, int32_t currentIndex,
    const LinearVector<float>& itemSizes, int32_t symbol)
{
    float dotPaddingAngleSum = dotPaddingAngle;
    float itemPadding = itemSizes[ITEM_PADDING];
    float itemMinorPadding = itemSizes[ITEM_MINOR_PADDING];
    float itemMiniPadding = itemSizes[ITEM_MINI_PADDING];
    if (fadeOutState_ == FadeOutState::FADE_OUT_NONE) {
        return dotPaddingAngleSum;
    }
    if (fadeOutState_ == FadeOutState::FADE_OUT_LEFT || fadeOutState_ == FadeOutState::FADE_OUT_BILATERAL) {
        if (currentIndex == indicatorStartIndex_ + LEFT_THIRD_DOT_INDEX) {
            if (itemIndex > indicatorStartIndex_) {
                dotPaddingAngleSum = dotPaddingAngle - symbol * (itemPadding - itemMiniPadding);
            }
        } else if (currentIndex > indicatorStartIndex_ + LEFT_THIRD_DOT_INDEX) {
            if (itemIndex == indicatorStartIndex_ + LEFT_SECOND_DOT_INDEX) {
                dotPaddingAngleSum = dotPaddingAngle - symbol * (itemPadding - itemMiniPadding);
            } else if (itemIndex > indicatorStartIndex_ + LEFT_SECOND_DOT_INDEX) {
                dotPaddingAngleSum =
                    dotPaddingAngle - symbol * (itemPadding * DIPLOID - itemMinorPadding - itemMiniPadding);
            }
        }
    }
    if (fadeOutState_ == FadeOutState::FADE_OUT_RIGHT || fadeOutState_ == FadeOutState::FADE_OUT_BILATERAL) {
        if (currentIndex == indicatorStartIndex_ + RIGHT_THIRD_DOT_INDEX) {
            if (itemIndex > indicatorStartIndex_ + RIGHT_SECOND_DOT_INDEX) {
                dotPaddingAngleSum = dotPaddingAngleSum - symbol * (itemPadding - itemMiniPadding);
            }
        } else if (currentIndex < indicatorStartIndex_ + RIGHT_THIRD_DOT_INDEX) {
            if (itemIndex == indicatorStartIndex_ + RIGHT_SECOND_DOT_INDEX) {
                dotPaddingAngleSum = dotPaddingAngleSum - symbol * (itemPadding - itemMinorPadding);
            }
            if (itemIndex > indicatorStartIndex_ + RIGHT_SECOND_DOT_INDEX) {
                dotPaddingAngleSum =
                    dotPaddingAngleSum - symbol * (itemPadding * DIPLOID - itemMinorPadding - itemMiniPadding);
            }
        }
    }
    return dotPaddingAngleSum;
}

std::tuple<float, float, float> CircleDotIndicatorPaintMethod::GetMoveRate()
{
    auto actualTurnPageRate = turnPageRate_;
    float blackPointCenterMoveRate = 0.0f;
    float longPointLeftCenterMoveRate = 0.0f;
    float longPointRightCenterMoveRate = 0.0f;

    if (gestureState_ == GestureState::GESTURE_STATE_FOLLOW_LEFT &&
        GreatNotEqual(std::abs(actualTurnPageRate), 0.0f)) {
        blackPointCenterMoveRate = CubicCurve(BLACK_POINT_CENTER_BEZIER_CURVE_VELOCITY, CENTER_BEZIER_CURVE_MASS,
            CENTER_BEZIER_CURVE_STIFFNESS, CENTER_BEZIER_CURVE_DAMPING)
                                       .MoveInternal(1.0 - std::abs(actualTurnPageRate));
        longPointLeftCenterMoveRate = 1.0 - std::abs(actualTurnPageRate);
        longPointRightCenterMoveRate = longPointLeftCenterMoveRate * LONG_POINT_TAIL_RATIO;
    } else if (gestureState_ == GestureState::GESTURE_STATE_FOLLOW_RIGHT) {
        blackPointCenterMoveRate = CubicCurve(BLACK_POINT_CENTER_BEZIER_CURVE_VELOCITY, CENTER_BEZIER_CURVE_MASS,
            CENTER_BEZIER_CURVE_STIFFNESS, CENTER_BEZIER_CURVE_DAMPING)
                                       .MoveInternal(std::abs(actualTurnPageRate));
        longPointRightCenterMoveRate = std::abs(actualTurnPageRate);
        longPointLeftCenterMoveRate = std::abs(actualTurnPageRate) * LONG_POINT_TAIL_RATIO;
    }
    return { blackPointCenterMoveRate, longPointLeftCenterMoveRate, longPointRightCenterMoveRate };
}

void CircleDotIndicatorPaintMethod::CalculatePointCenterAngle()
{
    const auto [blackPointCenterMoveRate, longPointLeftCenterMoveRate, longPointRightCenterMoveRate] = GetMoveRate();
    for (int32_t i = 0; i < itemCount_; ++i) {
        if (gestureState_ == GestureState::GESTURE_STATE_FOLLOW_RIGHT) {
            if (currentIndex_ == itemCount_ - 1) {
                break;
            }
            if (currentIndex_ == 0 && i == 0) {
                vectorBlackPointAngle_[i] += (ACTIVE_ITEM_SHRINK_ANGLE / NUMBER_TWO) * blackPointCenterMoveRate;
            }
            if (currentIndex_ == 0 && i > 1) {
                vectorBlackPointAngle_[i] -= (ACTIVE_ITEM_SHRINK_ANGLE / NUMBER_TWO) * blackPointCenterMoveRate;
            }
            if (currentIndex_ != 0 && (i == currentIndex_ || i == currentIndex_ + 1)) {
                vectorBlackPointAngle_[i] += (ACTIVE_ITEM_SHRINK_ANGLE / NUMBER_TWO) * blackPointCenterMoveRate;
            }
        } else if (gestureState_ == GestureState::GESTURE_STATE_FOLLOW_LEFT) {
            if (currentIndex_ == 0) {
                break;
            }
            if (currentIndex_ == itemCount_ - 1 && i == itemCount_ - 1) {
                vectorBlackPointAngle_[i] -= (ACTIVE_ITEM_SHRINK_ANGLE / NUMBER_TWO) * blackPointCenterMoveRate;
            }
            if (currentIndex_ == itemCount_ - 1 && i < itemCount_ - NUMBER_TWO) {
                vectorBlackPointAngle_[i] += (ACTIVE_ITEM_SHRINK_ANGLE / NUMBER_TWO) * blackPointCenterMoveRate;
            }
            if (currentIndex_ != itemCount_ - 1 && (i == currentIndex_ || i == currentIndex_ + 1)) {
                vectorBlackPointAngle_[i] -= (ACTIVE_ITEM_SHRINK_ANGLE / NUMBER_TWO) * blackPointCenterMoveRate;
            }
        }
    }
    CalculateLongPointCenterAngle(longPointLeftCenterMoveRate, longPointRightCenterMoveRate);
}

void CircleDotIndicatorPaintMethod::CalculateLongPointCenterAngle(
    float longPointLeftCenterMoveRate, float longPointRightCenterMoveRate)
{
    if (gestureState_ == GestureState::GESTURE_STATE_FOLLOW_RIGHT) {
        longPointAngle_.first = longPointAngle_.first - ITEM_SHRINK_PADDING * longPointLeftCenterMoveRate;
        longPointAngle_.second = longPointAngle_.second - ITEM_SHRINK_PADDING * longPointRightCenterMoveRate;
    } else if (gestureState_ == GestureState::GESTURE_STATE_FOLLOW_LEFT) {
        longPointAngle_.first = longPointAngle_.first + ITEM_SHRINK_PADDING * longPointLeftCenterMoveRate;
        longPointAngle_.second = longPointAngle_.second + ITEM_SHRINK_PADDING * longPointRightCenterMoveRate;
    }
}

std::pair<float, float> CircleDotIndicatorPaintMethod::CalculatePointAngle(
    const LinearVector<float>& itemSizes, int32_t currentIndex)
{
    if (itemCount_ == 0) {
        return { 0.0, 0.0 };
    }
    auto [startCurrentIndex, endCurrentIndex] = GetStartAndEndIndex(currentIndex);
    int index = endCurrentIndex;
    if (gestureState_ == GestureState::GESTURE_STATE_FOLLOW_RIGHT) {
        index = startCurrentIndex;
    }
    auto priorIndicatorIndex = circleDotIndicatorModifier_->GetIndicatorStartIndex();
    int32_t indicatorStartIndex = 0;
    if (circleDotIndicatorModifier_->GetInitState() || currentIndex_ < priorIndicatorIndex ||
        currentIndex_ >= priorIndicatorIndex + MAX_INDICATOR_DOT_COUNT) {
        indicatorStartIndex = CalculateInitIndicatorPosition();
    } else {
        indicatorStartIndex = CalculateIndicatorStartIndex(priorIndicatorIndex);
    }
    SetFadeOutState(indicatorStartIndex);
    vectorBlackPointAngle_.resize(itemCount_);
    vectorBlackPointRadius_.resize(itemCount_);
    for (int32_t i = 0; i < itemCount_; ++i) {
        float offset = CalculateBlackPointRotateAngle(indicatorStartIndex, i);
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
        itemSizes.emplace_back(static_cast<float>(ITEM_SHRINK_RADIUS.ConvertToPx()));
        itemSizes.emplace_back(static_cast<float>(SLECTED_ITEM_SHRINK_RADIUS.ConvertToPx()));
        itemSizes.emplace_back(static_cast<float>(CONTAINER_SHRINK_RADIUS.ConvertToPx()));
        itemSizes.emplace_back(ITEM_SHRINK_PADDING);
        itemSizes.emplace_back(SELECTED_ITEM_SHRINK_PADDING);
        itemSizes.emplace_back(ACTIVE_ITEM_SHRINK_ANGLE);
        itemSizes.emplace_back(ITEM_SHRINK_MINOR_PADDING);
        itemSizes.emplace_back(ITEM_SHRINK_MINI_PADDING);
    } else {
        itemSizes.emplace_back(static_cast<float>(ITEM_DILATE_RADIUS.ConvertToPx()));
        itemSizes.emplace_back(static_cast<float>(SLECTED_ITEM_DILATE_RADIUS.ConvertToPx()));
        itemSizes.emplace_back(static_cast<float>(CONTAINER_DILATE_RADIUS.ConvertToPx()));
        itemSizes.emplace_back(ITEM_DILATE_PADDING);
        itemSizes.emplace_back(SELECTED_ITEM_DILATE_PADDING);
        itemSizes.emplace_back(ACTIVE_ITEM_DILATE_ANGLE);
        itemSizes.emplace_back(ITEM_DILATE_MINOR_PADDING);
        itemSizes.emplace_back(ITEM_DILATE_MINI_PADDING);
    }

    auto longPointAngle = CalculatePointAngle(itemSizes, currentIndex_);
    return { longPointAngle, itemSizes };
}

int32_t CircleDotIndicatorPaintMethod::GetHalfIndex()
{
    if (itemCount_ == 1) {
        return itemCount_ - 1;
    }
    if (itemCount_ % NUMBER_TWO == 0) {
        return (itemCount_ / NUMBER_TWO) - 1;
    }
    return (itemCount_ - 1) / NUMBER_TWO;
}

std::pair<float, float> CircleDotIndicatorPaintMethod::GetLongPointAngle(
    const LinearVector<float>& itemSizes, int32_t currentIndex, int32_t indicatorStartIndex)
{
    float dotActiveAngle = itemSizes[ACTIVE_ITEM_ANGLE];
    float offset = CalculateBlackPointRotateAngle(indicatorStartIndex, currentIndex);
    float selectItemAngle = GetBlackPointAngle(itemSizes, currentIndex, currentIndex, offset);
    float LongPointStartAngle = 0.0;
    float LongPointEndAngle = 0.0;
    // The number 2 represents equal division
    if (arcDirection_ == SwiperArcDirection::SIX_CLOCK_DIRECTION) {
        LongPointStartAngle = QUARTER_CIRCLE_ANGLE + selectItemAngle + dotActiveAngle / NUMBER_TWO;
    } else if (arcDirection_ == SwiperArcDirection::THREE_CLOCK_DIRECTION) {
        LongPointStartAngle = selectItemAngle + dotActiveAngle / NUMBER_TWO;
    } else {
        LongPointStartAngle = HALF_CIRCLE_ANGLE + selectItemAngle + dotActiveAngle / NUMBER_TWO;
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
                (itemCount_ - ITEM_TWO_NUM) * dotPaddingAngle + dotActivePaddingAngle + dotActiveAngle / NUMBER_TWO;
        } else {
            allPointArcAngle = dotActiveAngle;
        }
    } else {
        allPointArcAngle = (itemCount_ - ITEM_THREE_NUM) * dotPaddingAngle + dotActivePaddingAngle * NUMBER_TWO;
    }
    return GetFadeOutPadding(allPointArcAngle, itemCount_ - 1, currentIndex, itemSizes, 1);
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
                itemCenterAngle = (allPointArcAngle / HALF_DIVISOR) - (dotActiveAngle / HALF_DIVISOR);
            } else {
                // NUMBER_TWO: half of angle
                itemCenterAngle = (allPointArcAngle / NUMBER_TWO) - (dotActiveAngle / NUMBER_TWO) -
                                  dotActivePaddingAngle - (itemIndex - 1) * dotPaddingAngle;    // 1: exclude one point
            }
        } else if (itemIndex == currentIndex) {
            itemCenterAngle = (allPointArcAngle / NUMBER_TWO) -                          // NUMBER_TWO: half of angle
                              (itemIndex - 1) * dotPaddingAngle - dotActivePaddingAngle; // 1: exclude one point
        } else if (itemIndex > currentIndex) {
            // NUMBER_TWO: half of angle
            itemCenterAngle = (allPointArcAngle / NUMBER_TWO) - (itemIndex - NUMBER_TWO) * dotPaddingAngle -
                              dotActivePaddingAngle * NUMBER_TWO;                        // NUMBER_TWO: diploid
        } else {
            // NUMBER_TWO: half of angle
            itemCenterAngle = (allPointArcAngle / NUMBER_TWO) - itemIndex * dotPaddingAngle;
        }
        itemCenterAngle = GetFadeOutPadding(itemCenterAngle, itemIndex, currentIndex, itemSizes, -1); // -1: minus sybol
    } else {
        if (itemIndex == 0) {
            itemCenterAngle = (dotActiveAngle / NUMBER_TWO) + dotActivePaddingAngle + // NUMBER_TWO: half of angle
                              (itemIndex - 1) * dotPaddingAngle -            // 1: exclude one point
                              (allPointArcAngle / NUMBER_TWO);                        // NUMBER_TWO: half of angle
        } else if (itemIndex == currentIndex) {
            itemCenterAngle = (itemIndex - 1) * dotPaddingAngle + dotActivePaddingAngle - // 1: exclude one point
                              (allPointArcAngle / NUMBER_TWO);                            // NUMBER_TWO: half of angle
        } else if (itemIndex > currentIndex) {
            itemCenterAngle = (itemIndex - ITEM_TWO_NUM) * dotPaddingAngle + dotActivePaddingAngle * NUMBER_TWO -
                              (allPointArcAngle / NUMBER_TWO); // NUMBER_TWO: half of angle
        } else {
            // NUMBER_TWO: half of angle
            itemCenterAngle = itemIndex * dotPaddingAngle - (allPointArcAngle / NUMBER_TWO);
        }
        itemCenterAngle = GetFadeOutPadding(itemCenterAngle, itemIndex, currentIndex, itemSizes, 1); // 1: plus sybol
        itemCenterAngle = -itemCenterAngle;
    }
    return itemCenterAngle + offset;
}

std::pair<int32_t, int32_t> CircleDotIndicatorPaintMethod::GetIndexOnRTL(int32_t index)
{
    int32_t startCurrentIndex = index;
    auto isInvalid = NearEqual(turnPageRate_, 0.0f) || LessOrEqualCustomPrecision(turnPageRate_, -1.0f) ||
                     GreatOrEqualCustomPrecision(turnPageRate_, 1.0f);
    if (!isInvalid) {
        startCurrentIndex = LessNotEqualCustomPrecision(turnPageRate_, 0.0f) ? index - 1 : index + 1;
    }

    if (startCurrentIndex == -1) {
        startCurrentIndex = itemCount_ - 1;
    }

    return { startCurrentIndex, index };
}

std::pair<int32_t, int32_t> CircleDotIndicatorPaintMethod::GetIndex(int32_t index)
{
    if (mouseClickIndex_ || gestureState_ == GestureState::GESTURE_STATE_RELEASE_LEFT ||
        gestureState_ == GestureState::GESTURE_STATE_RELEASE_RIGHT) {
        turnPageRate_ = 0;
    }

    if (isHorizontalAndRightToLeft_) {
        return GetIndexOnRTL(index);
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
    auto tempLongAngle = longPointAngle_;
    auto tempvector = vectorBlackPointAngle_;
    float itemChangeValue = (ITEM_PADDING * touchBottomRate_) / HALF_DIVISOR;
    int displayAreaCount = itemCount_;
    if (itemCount_ >= MAX_INDICATOR_DOT_COUNT) {
        displayAreaCount = MAX_INDICATOR_DOT_COUNT;
    }
    float longAngleChangeValue = (displayAreaCount - 1) * itemChangeValue;

    if (touchBottomType_ == TouchBottomType::END) {
        for (auto indexLeft = static_cast<int32_t>(tempvector.size()) - displayAreaCount;
             indexLeft < static_cast<int32_t>(tempvector.size()); indexLeft++) {
            tempvector[indexLeft] -=
                (indexLeft - (static_cast<int32_t>(tempvector.size()) - displayAreaCount)) * itemChangeValue;
        }
        longAngleChangeValue *= -1;
    }

    if (touchBottomType_ == TouchBottomType::START) {
        for (int32_t indexRight = displayAreaCount - 1; indexRight >= 0; indexRight--) {
            tempvector[indexRight] += (displayAreaCount - 1 - indexRight) * itemChangeValue;
        }
    }

    tempLongAngle.first += longAngleChangeValue;
    tempLongAngle.second += longAngleChangeValue;
    float backgroundOffset = (displayAreaCount - 1) * itemChangeValue;
    circleDotIndicatorModifier_->UpdateTouchBottomAnimation(tempvector, tempLongAngle, backgroundOffset);
}
} // namespace OHOS::Ace::NG
