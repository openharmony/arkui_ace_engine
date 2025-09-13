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

#include "core/components_ng/pattern/swiper_indicator/dot_indicator/overlength_dot_indicator_modifier.h"
#include "core/components_ng/pattern/swiper_indicator/indicator_common/swiper_indicator_utils.h"

namespace OHOS::Ace::NG {
namespace {
constexpr Dimension INDICATOR_PADDING_DEFAULT = 12.0_vp;
constexpr float BLACK_POINT_CENTER_BEZIER_CURVE_VELOCITY = 0.2f;
constexpr float CENTER_BEZIER_CURVE_MASS = 0.0f;
constexpr float CENTER_BEZIER_CURVE_STIFFNESS = 0.2f;
constexpr float CENTER_BEZIER_CURVE_DAMPING = 1.0f;
constexpr float SMALLEST_POINT_RATIO = 1.0f / 3.0f;
constexpr float SECOND_SMALLEST_POINT_RATIO = 2.0f / 3.0f;
constexpr float NORMAL_FADING_RATIO = 1.0f;
constexpr double FULL_ALPHA = 255.0;
constexpr int32_t BLACK_POINT_DURATION = 400;
constexpr int32_t LEFT_FIRST_POINT_INDEX = 0;
constexpr int32_t SECOND_POINT_INDEX = 1;
constexpr int32_t THIRD_POINT_INDEX = 2;
constexpr uint32_t ITEM_HALF_WIDTH = 0;
constexpr uint32_t ITEM_HALF_HEIGHT = 1;
constexpr uint32_t SELECTED_ITEM_HALF_WIDTH = 2;
constexpr uint32_t SELECTED_ITEM_HALF_HEIGHT = 3;
constexpr float HALF_FLOAT = 0.5f;
constexpr int32_t OVERLONG_SMALL_COUNT = 2;
constexpr int32_t DOUBLE_INT = 2;
} // namespace

void OverlengthDotIndicatorModifier::onDraw(DrawingContext& context)
{
    ContentProperty contentProperty;
    contentProperty.backgroundColor = backgroundColor_->Get().ToColor();
    contentProperty.unselectedIndicatorWidth = unselectedIndicatorWidth_->Get();
    contentProperty.unselectedIndicatorHeight = unselectedIndicatorHeight_->Get();
    contentProperty.vectorBlackPointCenterX = vectorBlackPointCenterX_->Get();
    contentProperty.longPointLeftCenterX = longPointLeftCenterX_->Get();
    contentProperty.longPointRightCenterX = longPointRightCenterX_->Get();
    contentProperty.normalToHoverPointDilateRatio = normalToHoverPointDilateRatio_->Get();
    contentProperty.hoverToNormalPointDilateRatio = hoverToNormalPointDilateRatio_->Get();
    contentProperty.longPointDilateRatio = longPointDilateRatio_->Get();
    contentProperty.indicatorPadding = indicatorPadding_->Get();
    contentProperty.indicatorMargin = indicatorMargin_->Get();
    contentProperty.itemHalfSizes = itemHalfSizes_->Get();
    contentProperty.firstPointOpacity = firstPointOpacity_->Get();
    contentProperty.newPointOpacity = newPointOpacity_->Get();

    PaintBackground(context, contentProperty, maxDisplayCount_, isBindIndicator_);
    PaintContent(context, contentProperty);
    isDrawbackground_ = false;
}

void OverlengthDotIndicatorModifier::PaintBackground(
    DrawingContext& context, const ContentProperty& contentProperty, int32_t maxDisplayCount, bool isBindIndicator)
{
    CHECK_NULL_VOID(contentProperty.backgroundColor.GetAlpha());
    auto itemWidth = contentProperty.itemHalfSizes[ITEM_HALF_WIDTH] * 2;
    auto itemHeight = contentProperty.itemHalfSizes[ITEM_HALF_HEIGHT] * 2;
    auto selectedItemWidth = contentProperty.itemHalfSizes[SELECTED_ITEM_HALF_WIDTH] * 2;
    auto selectedItemHeight = contentProperty.itemHalfSizes[SELECTED_ITEM_HALF_HEIGHT] * 2;
    auto pointNumber = static_cast<float>(contentProperty.vectorBlackPointCenterX.size());
    float allPointDiameterSum = itemWidth * static_cast<float>(pointNumber + 1);
    if (isCustomSize_) {
        allPointDiameterSum = itemWidth * static_cast<float>(pointNumber - 1) + selectedItemWidth;
    }
    float allPointSpaceSum = static_cast<float>(GetIndicatorDotItemSpace().ConvertToPx()) * (pointNumber - 1);

    if (maxDisplayCount > 0) {
        allPointSpaceSum = static_cast<float>(GetIndicatorDotItemSpace().ConvertToPx()) * (maxDisplayCount - 1);
        allPointDiameterSum = itemWidth * (maxDisplayCount - OVERLONG_SMALL_COUNT - 1) + selectedItemWidth +
                              itemWidth * SECOND_SMALLEST_POINT_RATIO + itemWidth * SMALLEST_POINT_RATIO;
    }

    // Background necessary property
    float rectWidth =
        contentProperty.indicatorPadding + allPointDiameterSum + allPointSpaceSum + contentProperty.indicatorPadding;
    auto indicatorTheme = GetSwiperIndicatorTheme();
    CHECK_NULL_VOID(indicatorTheme);
    auto indicatorHeightPadding = indicatorTheme->GetIndicatorBgHeight().ConvertToPx();
    float rectHeight = indicatorHeightPadding + itemHeight + indicatorHeightPadding;
    if (selectedItemHeight > itemHeight) {
        rectHeight = indicatorHeightPadding + selectedItemHeight + indicatorHeightPadding;
    }

    auto [rectLeft, rectRight, rectTop, rectBottom] =
        CalcAndAdjustIndicatorPaintRect(contentProperty, rectWidth, rectHeight);
    // Paint background
    RSCanvas& canvas = context.canvas;
    RSBrush brush;
    brush.SetAntiAlias(true);
    brush.SetColor(ToRSColor(contentProperty.backgroundColor));
    canvas.AttachBrush(brush);
    auto radius = axis_ == Axis::HORIZONTAL ? rectHeight : rectWidth;
    backgroundStart_ = axis_ == Axis::HORIZONTAL ? rectLeft : rectTop;
    backgroundEnd_ = axis_ == Axis::HORIZONTAL ? rectRight : rectBottom;
    canvas.DrawRoundRect({ { rectLeft, rectTop, rectRight, rectBottom }, radius, radius });
    canvas.DetachBrush();
}

std::pair<float, float> OverlengthDotIndicatorModifier::GetTouchBottomCenterX(ContentProperty& contentProperty)
{
    float leftCenterX = contentProperty.longPointLeftCenterX;
    float rightCenterX = contentProperty.longPointRightCenterX;

    if (isCustomSize_ || contentProperty.vectorBlackPointCenterX.empty() ||
        static_cast<int32_t>(contentProperty.vectorBlackPointCenterX.size()) < maxDisplayCount_) {
        return { leftCenterX, rightCenterX };
    }

    auto currentIndex = isHorizontalAndRTL_ ? realItemCount_ - 1 - currentIndex_ : currentIndex_;
    bool isLeftTouchBottom = (currentIndex == realItemCount_ - 1);
    bool isRightTouchBottom = (currentIndex == 0);
    float radius = (rightCenterX - leftCenterX) * HALF_FLOAT;
    if ((animationState_ == TouchBottomAnimationStage::STAGE_SHRINKT_TO_BLACK_POINT && isLeftTouchBottom) ||
        (animationState_ == TouchBottomAnimationStage::STAGE_EXPAND_TO_LONG_POINT && isRightTouchBottom)) {
        leftCenterX = contentProperty.vectorBlackPointCenterX[0] - radius;
        rightCenterX = contentProperty.vectorBlackPointCenterX[0] + radius;
    } else if ((animationState_ == TouchBottomAnimationStage::STAGE_EXPAND_TO_LONG_POINT && isLeftTouchBottom) ||
               (animationState_ == TouchBottomAnimationStage::STAGE_SHRINKT_TO_BLACK_POINT && isRightTouchBottom)) {
        leftCenterX = contentProperty.vectorBlackPointCenterX[maxDisplayCount_ - 1] - radius;
        rightCenterX = contentProperty.vectorBlackPointCenterX[maxDisplayCount_ - 1] + radius;
    }

    return { leftCenterX, rightCenterX };
}

void OverlengthDotIndicatorModifier::PaintContent(DrawingContext& context, ContentProperty& contentProperty)
{
    PaintBlackPoint(context, contentProperty);
    RSCanvas& canvas = context.canvas;
    auto [leftCenterX, rightCenterX] = GetTouchBottomCenterX(contentProperty);

    OffsetF leftCenter = { leftCenterX, centerY_ };
    OffsetF rightCenter = { rightCenterX, centerY_ };
    OffsetF centerDistance = rightCenter - leftCenter;
    OffsetF centerDilateDistance = centerDistance * contentProperty.longPointDilateRatio;
    leftCenter -= (centerDilateDistance - centerDistance) * HALF_FLOAT;
    rightCenter += (centerDilateDistance - centerDistance) * HALF_FLOAT;
    PaintSelectedIndicator(
        canvas, leftCenter, rightCenter, contentProperty.itemHalfSizes * contentProperty.longPointDilateRatio, true);
}

void OverlengthDotIndicatorModifier::PaintBlackPoint(DrawingContext& context, ContentProperty& contentProperty)
{
    RSCanvas& canvas = context.canvas;
    auto totalCount = contentProperty.vectorBlackPointCenterX.size();
    for (size_t i = 0; i < totalCount; ++i) {
        if (i >= contentProperty.unselectedIndicatorWidth.size() ||
            i >= contentProperty.unselectedIndicatorHeight.size()) {
            break;
        }

        OffsetF center = { contentProperty.vectorBlackPointCenterX[i], centerY_ };
        float width = contentProperty.unselectedIndicatorWidth[i];
        float height = contentProperty.unselectedIndicatorHeight[i];

        auto paintColor = unselectedColor_->Get();
        bool isFirstPoint = (i == 0 && moveDirection_ == OverlongIndicatorMove::MOVE_BACKWARD) ||
                            (i == totalCount - 2 && moveDirection_ == OverlongIndicatorMove::MOVE_FORWARD);
        if (isFirstPoint) {
            // first point color
            paintColor = paintColor.BlendOpacity(contentProperty.firstPointOpacity / FULL_ALPHA);
        } else if (i == totalCount - 1 && moveDirection_ != OverlongIndicatorMove::NONE) {
            // new point color
            paintColor = paintColor.BlendOpacity(contentProperty.newPointOpacity / FULL_ALPHA);
        }
        if (isDrawbackground_ || (center.GetX() - width * HALF_FLOAT > backgroundStart_ &&
                                     center.GetX() + width * HALF_FLOAT < backgroundEnd_)) {
            PaintUnselectedIndicator(canvas, center, width, height, LinearColor(paintColor));
        }
    }
}

void OverlengthDotIndicatorModifier::PaintUnselectedIndicator(
    RSCanvas& canvas, const OffsetF& center, float width, float height, const LinearColor& indicatorColor)
{
    RSBrush brush;
    brush.SetAntiAlias(true);
    brush.SetColor(ToRSColor(indicatorColor));
    canvas.AttachBrush(brush);
    if (!NearEqual(width, height) || !isCustomSize_) {
        float rectLeft =
            (axis_ == Axis::HORIZONTAL ? center.GetX() - width * HALF_FLOAT : center.GetY() - height * HALF_FLOAT);
        float rectTop =
            (axis_ == Axis::HORIZONTAL ? center.GetY() - height * HALF_FLOAT : center.GetX() - width * HALF_FLOAT);
        float rectRight =
            (axis_ == Axis::HORIZONTAL ? center.GetX() + width * HALF_FLOAT : center.GetY() + height * HALF_FLOAT);
        float rectBottom =
            (axis_ == Axis::HORIZONTAL ? center.GetY() + height * HALF_FLOAT : center.GetX() + width * HALF_FLOAT);

        if (height > width || !isCustomSize_) {
            canvas.DrawRoundRect({ { rectLeft, rectTop, rectRight, rectBottom }, width, width });
        } else if (height < width) {
            canvas.DrawRoundRect({ { rectLeft, rectTop, rectRight, rectBottom }, height, height });
        } else {
            float customPointX = axis_ == Axis::HORIZONTAL ? center.GetX() : center.GetY();
            float customPointY = axis_ == Axis::HORIZONTAL ? center.GetY() : center.GetX();
            canvas.DrawCircle({ customPointX, customPointY }, height * HALF_FLOAT);
        }
    } else {
        float pointX = axis_ == Axis::HORIZONTAL ? center.GetX() : center.GetY();
        float pointY = axis_ == Axis::HORIZONTAL ? center.GetY() : center.GetX();
        canvas.DrawCircle({ pointX, pointY }, width * HALF_FLOAT);
    }
    canvas.DetachBrush();
}

void OverlengthDotIndicatorModifier::UpdateShrinkPaintProperty(const OffsetF& margin,
    const LinearVector<float>& normalItemHalfSizes, const std::pair<float, float>& longPointCenterX)
{
    indicatorMargin_->Set(margin);
    indicatorPadding_->Set(static_cast<float>(INDICATOR_PADDING_DEFAULT.ConvertToPx()));

    if (longPointLeftAnimEnd_ && longPointRightAnimEnd_) {
        longPointLeftCenterX_->Set(longPointCenterX.first);
        longPointRightCenterX_->Set(longPointCenterX.second);
    }

    AnimationOption option;
    option.SetDuration(0);
    option.SetCurve(Curves::LINEAR);
    AnimationUtils::StartAnimation(option, [weak = WeakClaim(this)]() {
        auto modifier = weak.Upgrade();
        CHECK_NULL_VOID(modifier);
        modifier->vectorBlackPointCenterX_->Set(modifier->animationEndCenterX_);
        modifier->unselectedIndicatorWidth_->Set(modifier->animationEndIndicatorWidth_);
        modifier->unselectedIndicatorHeight_->Set(modifier->animationEndIndicatorHeight_);
    });
    itemHalfSizes_->Set(normalItemHalfSizes);
    normalToHoverPointDilateRatio_->Set(NORMAL_FADING_RATIO);
    hoverToNormalPointDilateRatio_->Set(NORMAL_FADING_RATIO);
    longPointDilateRatio_->Set(NORMAL_FADING_RATIO);
    backgroundWidthDilateRatio_->Set(NORMAL_FADING_RATIO);
    backgroundHeightDilateRatio_->Set(NORMAL_FADING_RATIO);

    if (blackPointsAnimEnd_) {
        currentSelectedIndex_ = targetSelectedIndex_;
        currentOverlongType_ = targetOverlongType_;
    }
}

void OverlengthDotIndicatorModifier::UpdateNormalPaintProperty(const OffsetF& margin,
    const LinearVector<float>& normalItemHalfSizes, const std::pair<float, float>& longPointCenterX)
{
    normalMargin_ = margin;
    CalcAnimationEndCenterX(normalItemHalfSizes);
    auto swiperTheme = GetSwiperIndicatorTheme();
    CHECK_NULL_VOID(swiperTheme);
    auto backgroundColor =
        indicatorMask_ ? swiperTheme->GetPressedColor() : swiperTheme->GetHoverColor().ChangeOpacity(0);
    UpdateShrinkPaintProperty(margin, normalItemHalfSizes, overlongSelectedEndCenterX_);
    UpdateBackgroundColor(backgroundColor);
}

std::pair<float, float> OverlengthDotIndicatorModifier::CalcLongPointEndCenterXWithBlack(
    size_t index, const LinearVector<float>& itemHalfSizes)
{
    if (isHorizontalAndRTL_) {
        index = static_cast<size_t>(maxDisplayCount_ - 1 - static_cast<int32_t>(index));
    }

    if (index >= animationEndCenterX_.size()) {
        return std::make_pair(0.0f, 0.0f);
    }

    auto selectedIndicatorRadius = itemHalfSizes[SELECTED_ITEM_HALF_WIDTH];
    if (!isCustomSizeValue_) {
        selectedIndicatorRadius *= 2.0f;
    }

    auto longPointLeftEndCenterX = animationEndCenterX_[index] - selectedIndicatorRadius * HALF_FLOAT;
    auto longPointRightEndCenterX = animationEndCenterX_[index] + selectedIndicatorRadius * HALF_FLOAT;
    return std::make_pair(longPointLeftEndCenterX, longPointRightEndCenterX);
}

int32_t OverlengthDotIndicatorModifier::GetBlackPointsAnimationDuration() const
{
    if (InstanceOf<InterpolatingSpring>(headCurve_)) {
        return BLACK_POINT_DURATION;
    }

    return animationDuration_;
}

bool OverlengthDotIndicatorModifier::NeedUpdateWhenAnimationFinish() const
{
    if (NearZero(forceStopPageRate_) || NearEqual(forceStopPageRate_, -1.0f) ||
        NearEqual(forceStopPageRate_, FLT_MAX)) {
        return true;
    }

    if ((currentSelectedIndex_ == 0 && targetSelectedIndex_ == maxDisplayCount_ - 1) ||
        (currentSelectedIndex_ == maxDisplayCount_ - 1 && targetSelectedIndex_ == 0)) {
        return true;
    }

    if (std::abs(forceStopPageRate_) < HALF_FLOAT && currentSelectedIndex_ < targetSelectedIndex_) {
        return false;
    }

    if (std::abs(forceStopPageRate_) >= HALF_FLOAT && currentSelectedIndex_ > targetSelectedIndex_) {
        return false;
    }

    if (std::abs(forceStopPageRate_) < HALF_FLOAT && animationStartIndex_ < animationEndIndex_) {
        return false;
    }

    if (std::abs(forceStopPageRate_) >= HALF_FLOAT && animationStartIndex_ > animationEndIndex_) {
        return false;
    }

    return true;
}

void OverlengthDotIndicatorModifier::PlayBlackPointsAnimation(const LinearVector<float>& itemHalfSizes)
{
    AnimationOption blackPointOption;
    auto pointMoveCurve = AceType::MakeRefPtr<CubicCurve>(BLACK_POINT_CENTER_BEZIER_CURVE_VELOCITY,
        CENTER_BEZIER_CURVE_MASS, CENTER_BEZIER_CURVE_STIFFNESS, CENTER_BEZIER_CURVE_DAMPING);
    blackPointOption.SetCurve(pointMoveCurve);
    blackPointOption.SetDuration(GetBlackPointsAnimationDuration());

    vectorBlackPointCenterX_->Set(animationStartCenterX_);
    unselectedIndicatorWidth_->Set(animationStartIndicatorWidth_);
    unselectedIndicatorHeight_->Set(animationStartIndicatorHeight_);
    firstPointOpacity_->Set(UINT8_MAX);
    newPointOpacity_->Set(0);
    isSelectedColorAnimEnd_ = false;
    isTouchBottomLoop_ = true;
    auto longPointEndCenterX =
        CalcLongPointEndCenterXWithBlack(static_cast<size_t>(targetSelectedIndex_), itemHalfSizes);
    blackPointsAnimEnd_ = false;
    AnimationUtils::StartAnimation(blackPointOption, [&]() {
        vectorBlackPointCenterX_->Set(animationEndCenterX_);
        unselectedIndicatorWidth_->Set(animationEndIndicatorWidth_);
        unselectedIndicatorHeight_->Set(animationEndIndicatorHeight_);

        if (moveDirection_ != OverlongIndicatorMove::NONE) {
            firstPointOpacity_->Set(0);
            newPointOpacity_->Set(UINT8_MAX);
            longPointLeftCenterX_->Set(longPointEndCenterX.first);
            longPointRightCenterX_->Set(longPointEndCenterX.second);
        }
    }, [weak = WeakClaim(this)]() {
        auto modifier = weak.Upgrade();
        CHECK_NULL_VOID(modifier);

        if (!modifier->NeedUpdateWhenAnimationFinish()) {
            return;
        }

        if (!modifier->blackPointsAnimEnd_ && (modifier->needUpdate_ || !modifier->isAutoPlay_)) {
            modifier->currentSelectedIndex_ = modifier->targetSelectedIndex_;
            modifier->currentOverlongType_ = modifier->targetOverlongType_;
            modifier->blackPointsAnimEnd_ = true;
            modifier->needUpdate_ = false;
        }
    });
}

OverlongType OverlengthDotIndicatorModifier::RevertOverlongType(OverlongType overlongType) const
{
    if (overlongType == OverlongType::LEFT_NORMAL_RIGHT_FADEOUT) {
        return OverlongType::LEFT_FADEOUT_RIGHT_NORMAL;
    } else if (overlongType == OverlongType::LEFT_FADEOUT_RIGHT_NORMAL) {
        return OverlongType::LEFT_NORMAL_RIGHT_FADEOUT;
    }

    return overlongType;
}

LinearVector<float> OverlengthDotIndicatorModifier::CalcIndicatorSize(
    const LinearVector<float>& itemHalfSizes, OverlongType overlongType, bool isWidth)
{
    if (isHorizontalAndRTL_) {
        overlongType = RevertOverlongType(overlongType);
    }

    auto unselectedIndicatorRadius = isWidth ? itemHalfSizes[0] : itemHalfSizes[1];
    LinearVector<float> indicatorSize(maxDisplayCount_ + 1);

    auto secondSmallestRadius = unselectedIndicatorRadius * SECOND_SMALLEST_POINT_RATIO;
    auto smallestRadius = unselectedIndicatorRadius * SMALLEST_POINT_RATIO;

    for (int32_t i = 0; i < maxDisplayCount_; i++) {
        if (i == LEFT_FIRST_POINT_INDEX) {
            if (overlongType == OverlongType::LEFT_NORMAL_RIGHT_FADEOUT) {
                indicatorSize[i] = unselectedIndicatorRadius * 2;
            } else {
                indicatorSize[i] = smallestRadius * 2;
            }
            continue;
        }

        if (i == SECOND_POINT_INDEX) {
            if (overlongType == OverlongType::LEFT_NORMAL_RIGHT_FADEOUT) {
                indicatorSize[i] = unselectedIndicatorRadius * 2;
            } else {
                indicatorSize[i] = secondSmallestRadius * 2;
            }
            continue;
        }

        if (i >= THIRD_POINT_INDEX && i <= maxDisplayCount_ - 1 - THIRD_POINT_INDEX) {
            indicatorSize[i] = unselectedIndicatorRadius * 2;
            continue;
        }

        if (i == maxDisplayCount_ - 1 - SECOND_POINT_INDEX) {
            if (overlongType == OverlongType::LEFT_FADEOUT_RIGHT_NORMAL) {
                indicatorSize[i] = unselectedIndicatorRadius * 2;
            } else {
                indicatorSize[i] = secondSmallestRadius * 2;
            }
            continue;
        }

        if (i == maxDisplayCount_ - 1) {
            if (overlongType == OverlongType::LEFT_FADEOUT_RIGHT_NORMAL) {
                indicatorSize[i] = unselectedIndicatorRadius * 2;
            } else {
                indicatorSize[i] = smallestRadius * 2;
            }
            continue;
        }
    }

    return indicatorSize;
}

void OverlengthDotIndicatorModifier::UpdateSelectedCenterXOnDrag(const LinearVector<float>& itemHalfSizes)
{
    if (gestureState_ != GestureState::GESTURE_STATE_FOLLOW_LEFT &&
        gestureState_ != GestureState::GESTURE_STATE_FOLLOW_RIGHT) {
        return;
    }

    auto leftMoveRate = longPointLeftCenterMoveRate_;
    auto rightMoveRate = longPointRightCenterMoveRate_;
    if (gestureState_ == GestureState::GESTURE_STATE_FOLLOW_LEFT &&
        touchBottomTypeLoop_ == TouchBottomTypeLoop::TOUCH_BOTTOM_TYPE_LOOP_NONE) {
        leftMoveRate = 1.0f - longPointLeftCenterMoveRate_;
        rightMoveRate = 1.0f - longPointRightCenterMoveRate_;
    }

    auto targetIndex = isHorizontalAndRTL_ ? currentSelectedIndex_ - 1 : currentSelectedIndex_ + 1;
    if (gestureState_ == GestureState::GESTURE_STATE_FOLLOW_LEFT) {
        targetIndex = isHorizontalAndRTL_ ? currentSelectedIndex_ + 1 : currentSelectedIndex_ - 1;
    }

    auto longPointEndCenterX = CalcLongPointEndCenterXWithBlack(static_cast<size_t>(targetIndex), itemHalfSizes);
    if (touchBottomTypeLoop_ != TouchBottomTypeLoop::TOUCH_BOTTOM_TYPE_LOOP_NONE) {
        auto dragTargetCenterX = (overlongSelectedEndCenterX_.second + overlongSelectedEndCenterX_.first) * HALF_FLOAT;
        overlongSelectedEndCenterX_.first = overlongSelectedStartCenterX_.first +
                                            (dragTargetCenterX - overlongSelectedStartCenterX_.first) * leftMoveRate;

        overlongSelectedEndCenterX_.second = overlongSelectedStartCenterX_.second +
                                             (dragTargetCenterX - overlongSelectedStartCenterX_.second) * rightMoveRate;
    } else {
        auto leftDistance = overlongSelectedEndCenterX_.first - overlongSelectedStartCenterX_.first;
        auto rightDistance = overlongSelectedEndCenterX_.second - overlongSelectedStartCenterX_.second;
        if (currentSelectedIndex_ == targetSelectedIndex_ && isSwiperTouchDown_) {
            leftDistance = longPointEndCenterX.first - overlongSelectedStartCenterX_.first;
            rightDistance = longPointEndCenterX.second - overlongSelectedStartCenterX_.second;
        }

        overlongSelectedEndCenterX_.first = overlongSelectedStartCenterX_.first + leftDistance * leftMoveRate;
        overlongSelectedEndCenterX_.second = overlongSelectedStartCenterX_.second + rightDistance * rightMoveRate;
    }
}

float OverlengthDotIndicatorModifier::GetMoveRateOnAllMove() const
{
    float blackPointCenterMoveRate = CubicCurve(BLACK_POINT_CENTER_BEZIER_CURVE_VELOCITY, CENTER_BEZIER_CURVE_MASS,
        CENTER_BEZIER_CURVE_STIFFNESS, CENTER_BEZIER_CURVE_DAMPING)
                                         .MoveInternal(std::abs(turnPageRate_));
    if (gestureState_ == GestureState::GESTURE_STATE_RELEASE_LEFT ||
        gestureState_ == GestureState::GESTURE_STATE_RELEASE_RIGHT) {
        blackPointCenterMoveRate = 1.0f;
    }

    return blackPointCenterMoveRate;
}

void OverlengthDotIndicatorModifier::UpdateUnselectedCenterXOnDrag()
{
    if (gestureState_ != GestureState::GESTURE_STATE_FOLLOW_LEFT &&
        gestureState_ != GestureState::GESTURE_STATE_FOLLOW_RIGHT) {
        return;
    }

    auto moveRate = blackPointCenterMoveRate_;
    if (currentOverlongType_ != targetOverlongType_ || currentSelectedIndex_ == targetSelectedIndex_) {
        moveRate = GetMoveRateOnAllMove();
    }

    if (gestureState_ == GestureState::GESTURE_STATE_FOLLOW_LEFT &&
        touchBottomTypeLoop_ == TouchBottomTypeLoop::TOUCH_BOTTOM_TYPE_LOOP_NONE) {
        moveRate = 1.0f - moveRate;
    }

    for (size_t i = 0; i < animationEndIndicatorWidth_.size(); i++) {
        animationEndIndicatorWidth_[i] = animationStartIndicatorWidth_[i] +
                                         (animationEndIndicatorWidth_[i] - animationStartIndicatorWidth_[i]) * moveRate;
    }

    for (size_t i = 0; i < animationEndIndicatorHeight_.size(); i++) {
        animationEndIndicatorHeight_[i] =
            animationStartIndicatorHeight_[i] +
            (animationEndIndicatorHeight_[i] - animationStartIndicatorHeight_[i]) * moveRate;
    }

    for (size_t i = 0; i < animationEndCenterX_.size(); i++) {
        animationEndCenterX_[i] =
            animationStartCenterX_[i] + (animationEndCenterX_[i] - animationStartCenterX_[i]) * moveRate;
    }
}

int32_t OverlengthDotIndicatorModifier::CalcTargetIndexOnDrag() const
{
    if (NearEqual(turnPageRate_, 0.0f)) {
        return animationEndIndex_;
    }

    auto startIndex = isHorizontalAndRTL_ ? realItemCount_ - 1 - animationStartIndex_ : animationStartIndex_;
    auto endIndex = isHorizontalAndRTL_ ? realItemCount_ - 1 - animationEndIndex_ : animationEndIndex_;
    if (startIndex == endIndex) {
        if (startIndex == realItemCount_ - 1) {
            return animationStartIndex_;
        }
        return isHorizontalAndRTL_ ? animationStartIndex_ - 1 : animationStartIndex_ + 1;
    }

    if (startIndex == 0 && endIndex == realItemCount_ - 1) {
        return animationStartIndex_;
    }

    return animationEndIndex_;
}

void OverlengthDotIndicatorModifier::CalcTargetStatusOnLongPointMove(const LinearVector<float>& itemHalfSizes)
{
    auto endCenterX = CalcIndicatorCenterX(itemHalfSizes, targetSelectedIndex_, targetOverlongType_);
    animationEndCenterX_ = endCenterX.first;
    overlongSelectedEndCenterX_ = endCenterX.second;
    animationStartIndicatorWidth_ = CalcIndicatorSize(itemHalfSizes, currentOverlongType_, true);
    animationStartIndicatorHeight_ = CalcIndicatorSize(itemHalfSizes, currentOverlongType_, false);

    animationEndIndicatorWidth_ = CalcIndicatorSize(itemHalfSizes, targetOverlongType_, true);
    animationEndIndicatorHeight_ = CalcIndicatorSize(itemHalfSizes, targetOverlongType_, false);

    if (isLoop_ && touchBottomTypeLoop_ != TouchBottomTypeLoop::TOUCH_BOTTOM_TYPE_LOOP_NONE) {
        animationStartCenterX_.resize(maxDisplayCount_);
        animationEndCenterX_.resize(maxDisplayCount_);
        animationStartIndicatorWidth_.resize(maxDisplayCount_);
        animationStartIndicatorHeight_.resize(maxDisplayCount_);
        animationEndIndicatorWidth_.resize(maxDisplayCount_);
        animationEndIndicatorHeight_.resize(maxDisplayCount_);
    }

    if (isSwiperTouchDown_ && (gestureState_ == GestureState::GESTURE_STATE_FOLLOW_LEFT ||
                                  gestureState_ == GestureState::GESTURE_STATE_FOLLOW_RIGHT)) {
        if (NearZero(turnPageRate_) && touchBottomTypeLoop_ != TouchBottomTypeLoop::TOUCH_BOTTOM_TYPE_LOOP_NONE) {
            return;
        }

        UpdateUnselectedCenterXOnDrag();
        UpdateSelectedCenterXOnDrag(itemHalfSizes);
        targetSelectedIndex_ = currentSelectedIndex_;
        targetOverlongType_ = currentOverlongType_;
    }
}

void OverlengthDotIndicatorModifier::CalcTargetStatusOnAllPointMoveForward(const LinearVector<float>& itemHalfSizes)
{
    auto targetCenterX = CalcIndicatorCenterX(itemHalfSizes, targetSelectedIndex_, targetOverlongType_);
    overlongSelectedEndCenterX_ = targetCenterX.second;
    auto targetIndicatorWidth = CalcIndicatorSize(itemHalfSizes, targetOverlongType_, true);
    auto targetIndicatorHeight = CalcIndicatorSize(itemHalfSizes, targetOverlongType_, false);

    float itemSpacePx = static_cast<float>(GetIndicatorDotItemSpace().ConvertToPx());
    // calc new point current position
    animationStartCenterX_[maxDisplayCount_] =
        animationStartCenterX_[0] - animationStartIndicatorWidth_[0] - itemSpacePx;
    animationStartIndicatorWidth_[maxDisplayCount_] = animationStartIndicatorWidth_[0];
    animationStartIndicatorHeight_[maxDisplayCount_] = animationStartIndicatorHeight_[0];

    // calc new point target position
    animationEndCenterX_[maxDisplayCount_] = targetCenterX.first[0];
    animationEndIndicatorWidth_[maxDisplayCount_] = targetIndicatorWidth[0];
    animationEndIndicatorHeight_[maxDisplayCount_] = targetIndicatorHeight[0];

    for (int32_t i = 0; i < maxDisplayCount_ - 1; i++) {
        animationEndCenterX_[i] = targetCenterX.first[i + 1];
        animationEndIndicatorWidth_[i] = targetIndicatorWidth[i + 1];
        animationEndIndicatorHeight_[i] = targetIndicatorHeight[i + 1];
    }

    animationEndCenterX_[maxDisplayCount_ - 1] =
        targetCenterX.first[maxDisplayCount_ - 1] + targetIndicatorWidth[maxDisplayCount_ - 1] + itemSpacePx;
    animationEndIndicatorWidth_[maxDisplayCount_ - 1] = targetIndicatorWidth[maxDisplayCount_ - 1];
    animationEndIndicatorHeight_[maxDisplayCount_ - 1] = targetIndicatorHeight[maxDisplayCount_ - 1];

    UpdateUnselectedCenterXOnDrag();
    UpdateSelectedCenterXOnDrag(itemHalfSizes);

    if (isSwiperTouchDown_ && (gestureState_ == GestureState::GESTURE_STATE_FOLLOW_LEFT ||
                                  gestureState_ == GestureState::GESTURE_STATE_FOLLOW_RIGHT)) {
        targetSelectedIndex_ = currentSelectedIndex_;
        targetOverlongType_ = currentOverlongType_;

        auto opacityMoveRate = GetMoveRateOnAllMove();
        auto firstPointOpacity = static_cast<uint8_t>(UINT8_MAX * opacityMoveRate);
        auto newPointOpacity = static_cast<uint8_t>(UINT8_MAX * (1.0f - opacityMoveRate));
        firstPointOpacity_->Set(firstPointOpacity);
        newPointOpacity_->Set(newPointOpacity);
    }
}

void OverlengthDotIndicatorModifier::CalcTargetStatusOnAllPointMoveBackward(const LinearVector<float>& itemHalfSizes)
{
    auto targetCenterX = CalcIndicatorCenterX(itemHalfSizes, targetSelectedIndex_, targetOverlongType_);
    overlongSelectedEndCenterX_ = targetCenterX.second;
    auto targetIndicatorWidth = CalcIndicatorSize(itemHalfSizes, targetOverlongType_, true);
    auto targetIndicatorHeight = CalcIndicatorSize(itemHalfSizes, targetOverlongType_, false);

    float itemSpacePx = static_cast<float>(GetIndicatorDotItemSpace().ConvertToPx());
    // calc new point current position
    animationStartCenterX_[maxDisplayCount_] = animationStartCenterX_[maxDisplayCount_ - 1] +
                                               animationStartIndicatorWidth_[maxDisplayCount_ - 1] + itemSpacePx;
    animationStartIndicatorWidth_[maxDisplayCount_] = animationStartIndicatorWidth_[maxDisplayCount_ - 1];
    animationStartIndicatorHeight_[maxDisplayCount_] = animationStartIndicatorHeight_[maxDisplayCount_ - 1];

    // calc first point target position
    auto distance = std::abs(targetCenterX.first[1] - targetCenterX.first[0]);
    animationEndCenterX_[0] = targetCenterX.first[0] - distance;
    animationEndIndicatorWidth_[0] = targetIndicatorWidth[0];
    animationEndIndicatorHeight_[0] = targetIndicatorHeight[0];

    for (int32_t i = 1; i <= maxDisplayCount_; i++) {
        animationEndCenterX_[i] = targetCenterX.first[i - 1];
        animationEndIndicatorWidth_[i] = targetIndicatorWidth[i - 1];
        animationEndIndicatorHeight_[i] = targetIndicatorHeight[i - 1];
    }

    UpdateUnselectedCenterXOnDrag();
    UpdateSelectedCenterXOnDrag(itemHalfSizes);

    if (isSwiperTouchDown_ && (gestureState_ == GestureState::GESTURE_STATE_FOLLOW_LEFT ||
                                  gestureState_ == GestureState::GESTURE_STATE_FOLLOW_RIGHT)) {
        targetSelectedIndex_ = currentSelectedIndex_;
        targetOverlongType_ = currentOverlongType_;

        auto opacityMoveRate = GetMoveRateOnAllMove();
        auto firstPointOpacity = static_cast<uint8_t>(UINT8_MAX * (1.0f - opacityMoveRate));
        auto newPointOpacity = static_cast<uint8_t>(UINT8_MAX * opacityMoveRate);
        firstPointOpacity_->Set(firstPointOpacity);
        newPointOpacity_->Set(newPointOpacity);
    }
}

void OverlengthDotIndicatorModifier::CalcAnimationEndCenterX(const LinearVector<float>& itemHalfSizes)
{
    if (isSwiperTouchDown_ && (gestureState_ == GestureState::GESTURE_STATE_FOLLOW_LEFT ||
                                  gestureState_ == GestureState::GESTURE_STATE_FOLLOW_RIGHT)) {
        animationEndIndex_ = CalcTargetIndexOnDrag();
    }

    CalcTargetOverlongStatus(animationStartIndex_, animationEndIndex_);

    auto startCenterX = CalcIndicatorCenterX(itemHalfSizes, currentSelectedIndex_, currentOverlongType_);
    animationStartCenterX_ = startCenterX.first;
    overlongSelectedStartCenterX_ = startCenterX.second;

    // long point move or no move
    if (currentSelectedIndex_ != targetSelectedIndex_ || animationStartIndex_ == animationEndIndex_) {
        moveDirection_ = OverlongIndicatorMove::NONE;
        CalcTargetStatusOnLongPointMove(itemHalfSizes);
        return;
    }

    animationStartIndicatorWidth_ = CalcIndicatorSize(itemHalfSizes, currentOverlongType_, true);
    animationStartIndicatorHeight_ = CalcIndicatorSize(itemHalfSizes, currentOverlongType_, false);
    animationEndCenterX_.resize(maxDisplayCount_ + 1);
    animationEndIndicatorWidth_.resize(maxDisplayCount_ + 1);
    animationEndIndicatorHeight_.resize(maxDisplayCount_ + 1);

    auto isBackward =
        isHorizontalAndRTL_ ? animationStartIndex_ > animationEndIndex_ : animationStartIndex_ < animationEndIndex_;
    if (isBackward) {
        moveDirection_ = OverlongIndicatorMove::MOVE_BACKWARD;
        CalcTargetStatusOnAllPointMoveBackward(itemHalfSizes);
        return;
    }

    moveDirection_ = OverlongIndicatorMove::MOVE_FORWARD;
    CalcTargetStatusOnAllPointMoveForward(itemHalfSizes);
}

void OverlengthDotIndicatorModifier::PlayIndicatorAnimation(const OffsetF& margin,
    const LinearVector<float>& itemHalfSizes, GestureState gestureState, TouchBottomTypeLoop touchBottomTypeLoop)
{
    StopBlackAnimation();

    needUpdate_ = false;
    blackPointsAnimEnd_ = true;
    currentSelectedIndex_ = targetSelectedIndex_;
    currentOverlongType_ = targetOverlongType_;
    isTouchBottomLoop_ = false;
    animationState_ = TouchBottomAnimationStage::STAGE_NONE;
    normalMargin_ = margin;
    CalcAnimationEndCenterX(itemHalfSizes);
    PlayBlackPointsAnimation(itemHalfSizes);

    std::vector<std::pair<float, float>> pointCenterX;
    if ((currentSelectedIndex_ == 0 && targetSelectedIndex_ == maxDisplayCount_ - 1) ||
        (currentSelectedIndex_ == maxDisplayCount_ - 1 && targetSelectedIndex_ == 0)) {
        auto currentSelectedIndex =
            isHorizontalAndRTL_ ? maxDisplayCount_ - 1 - currentSelectedIndex_ : currentSelectedIndex_;
        overlongSelectedStartCenterX_.first = animationEndCenterX_[currentSelectedIndex];
        overlongSelectedStartCenterX_.second = animationEndCenterX_[currentSelectedIndex];
        pointCenterX.emplace_back(overlongSelectedStartCenterX_);
        pointCenterX.emplace_back(overlongSelectedEndCenterX_);
    } else {
        pointCenterX.emplace_back(overlongSelectedEndCenterX_);
    }

    PlayLongPointAnimation(pointCenterX, gestureState, touchBottomTypeLoop, animationEndCenterX_, false);
}

void OverlengthDotIndicatorModifier::StopBlackAnimation()
{
    AnimationOption option;
    option.SetDuration(0);
    option.SetCurve(Curves::LINEAR);
    AnimationUtils::StartAnimation(option, [weak = WeakClaim(this)]() {
        auto modifier = weak.Upgrade();
        CHECK_NULL_VOID(modifier);
        modifier->vectorBlackPointCenterX_->Set(modifier->vectorBlackPointCenterX_->Get());
        modifier->firstPointOpacity_->Set(modifier->firstPointOpacity_->Get());
        modifier->newPointOpacity_->Set(modifier->newPointOpacity_->Get());
        modifier->unselectedIndicatorWidth_->Set(modifier->unselectedIndicatorWidth_->Get());
        modifier->unselectedIndicatorHeight_->Set(modifier->unselectedIndicatorHeight_->Get());
    });

    longPointLeftAnimEnd_ = true;
    longPointRightAnimEnd_ = true;
    ifNeedFinishCallback_ = false;
}

void OverlengthDotIndicatorModifier::StopAnimation(bool ifImmediately)
{
    if (ifImmediately) {
        AnimationOption option;
        option.SetDuration(0);
        option.SetCurve(Curves::LINEAR);
        AnimationUtils::StartAnimation(option, [weak = WeakClaim(this)]() {
            auto modifier = weak.Upgrade();
            CHECK_NULL_VOID(modifier);
            modifier->longPointLeftCenterX_->Set(modifier->longPointLeftCenterX_->Get());
            modifier->longPointRightCenterX_->Set(modifier->longPointRightCenterX_->Get());
        });
    }

    StopBlackAnimation();
}

void OverlengthDotIndicatorModifier::InitOverlongSelectedIndex(int32_t pageIndex)
{
    if (pageIndex < maxDisplayCount_ - 1 - THIRD_POINT_INDEX) {
        targetSelectedIndex_ = pageIndex;
        return;
    }

    if (pageIndex >= maxDisplayCount_ - 1 - THIRD_POINT_INDEX && pageIndex < realItemCount_ - 1 - THIRD_POINT_INDEX) {
        targetSelectedIndex_ = maxDisplayCount_ - 1 - THIRD_POINT_INDEX;
        return;
    }

    if (pageIndex >= maxDisplayCount_ - 1 - THIRD_POINT_INDEX && pageIndex == realItemCount_ - 1 - THIRD_POINT_INDEX) {
        targetSelectedIndex_ = maxDisplayCount_ - 1 - THIRD_POINT_INDEX;
        return;
    }

    if (pageIndex >= maxDisplayCount_ - 1 - THIRD_POINT_INDEX && pageIndex == realItemCount_ - 1 - SECOND_POINT_INDEX) {
        targetSelectedIndex_ = maxDisplayCount_ - 1 - SECOND_POINT_INDEX;
        return;
    }

    if (pageIndex >= maxDisplayCount_ - 1 - THIRD_POINT_INDEX && pageIndex == realItemCount_ - 1) {
        targetSelectedIndex_ = maxDisplayCount_ - 1;
        return;
    }
}

void OverlengthDotIndicatorModifier::InitOverlongStatus(int32_t pageIndex)
{
    if (pageIndex < maxDisplayCount_ - 1 - THIRD_POINT_INDEX) {
        currentSelectedIndex_ = pageIndex;
        currentOverlongType_ = OverlongType::LEFT_NORMAL_RIGHT_FADEOUT;

        targetSelectedIndex_ = currentSelectedIndex_;
        targetOverlongType_ = currentOverlongType_;
        return;
    }

    if (pageIndex >= maxDisplayCount_ - 1 - THIRD_POINT_INDEX && pageIndex < realItemCount_ - 1 - THIRD_POINT_INDEX) {
        currentSelectedIndex_ = maxDisplayCount_ - 1 - THIRD_POINT_INDEX;
        currentOverlongType_ = OverlongType::LEFT_FADEOUT_RIGHT_FADEOUT;

        targetSelectedIndex_ = currentSelectedIndex_;
        targetOverlongType_ = currentOverlongType_;
        return;
    }

    if (pageIndex >= maxDisplayCount_ - 1 - THIRD_POINT_INDEX && pageIndex == realItemCount_ - 1 - THIRD_POINT_INDEX) {
        currentSelectedIndex_ = maxDisplayCount_ - 1 - THIRD_POINT_INDEX;
        currentOverlongType_ = OverlongType::LEFT_FADEOUT_RIGHT_NORMAL;

        targetSelectedIndex_ = currentSelectedIndex_;
        targetOverlongType_ = currentOverlongType_;
        return;
    }

    if (pageIndex >= maxDisplayCount_ - 1 - THIRD_POINT_INDEX && pageIndex == realItemCount_ - 1 - SECOND_POINT_INDEX) {
        currentSelectedIndex_ = maxDisplayCount_ - 1 - SECOND_POINT_INDEX;
        currentOverlongType_ = OverlongType::LEFT_FADEOUT_RIGHT_NORMAL;

        targetSelectedIndex_ = currentSelectedIndex_;
        targetOverlongType_ = currentOverlongType_;
        return;
    }

    if (pageIndex >= maxDisplayCount_ - 1 - THIRD_POINT_INDEX && pageIndex == realItemCount_ - 1) {
        currentSelectedIndex_ = maxDisplayCount_ - 1;
        currentOverlongType_ = OverlongType::LEFT_FADEOUT_RIGHT_NORMAL;

        targetSelectedIndex_ = currentSelectedIndex_;
        targetOverlongType_ = currentOverlongType_;
        return;
    }
}

void OverlengthDotIndicatorModifier::CalcTargetSelectedIndex(int32_t currentPageIndex, int32_t targetPageIndex)
{
    if (currentPageIndex == targetPageIndex || keepStatus_) {
        return;
    }

    if (currentPageIndex < targetPageIndex) {
        CalcTargetSelectedIndexOnForward(currentPageIndex, targetPageIndex);
        return;
    }

    CalcTargetSelectedIndexOnBackward(currentPageIndex, targetPageIndex);
}

void OverlengthDotIndicatorModifier::CalcTargetOverlongStatus(int32_t currentPageIndex, int32_t targetPageIndex)
{
    if (currentPageIndex == targetPageIndex || currentOverlongType_ == OverlongType::NONE || keepStatus_) {
        AdjustTargetStatus(targetPageIndex);
        return;
    }

    if (currentPageIndex == realItemCount_ - 1 && targetPageIndex == 0) {
        targetSelectedIndex_ = 0;
        targetOverlongType_ = OverlongType::LEFT_NORMAL_RIGHT_FADEOUT;
        return;
    }

    if (currentPageIndex == 0 && targetPageIndex == realItemCount_ - 1) {
        targetSelectedIndex_ = maxDisplayCount_ - 1;
        targetOverlongType_ = OverlongType::LEFT_FADEOUT_RIGHT_NORMAL;
        return;
    }

    CalcTargetSelectedIndex(currentPageIndex, targetPageIndex);

    if (currentPageIndex < targetPageIndex) {
        if (currentOverlongType_ == OverlongType::LEFT_NORMAL_RIGHT_FADEOUT) {
            if (targetSelectedIndex_ < maxDisplayCount_ - 1 - THIRD_POINT_INDEX) {
                targetOverlongType_ = OverlongType::LEFT_NORMAL_RIGHT_FADEOUT;
            } else if (targetSelectedIndex_ == maxDisplayCount_ - 1 - THIRD_POINT_INDEX) {
                targetOverlongType_ = OverlongType::LEFT_FADEOUT_RIGHT_FADEOUT;
            }
        } else if (currentOverlongType_ == OverlongType::LEFT_FADEOUT_RIGHT_NORMAL) {
            targetOverlongType_ = OverlongType::LEFT_FADEOUT_RIGHT_NORMAL;
        } else {
            if (targetSelectedIndex_ < maxDisplayCount_ - 1 - THIRD_POINT_INDEX) {
                targetOverlongType_ = OverlongType::LEFT_FADEOUT_RIGHT_FADEOUT;
            } else if (targetSelectedIndex_ == maxDisplayCount_ - 1 - THIRD_POINT_INDEX) {
                if (targetPageIndex < realItemCount_ - 1 - THIRD_POINT_INDEX) {
                    targetOverlongType_ = OverlongType::LEFT_FADEOUT_RIGHT_FADEOUT;
                } else {
                    targetOverlongType_ = OverlongType::LEFT_FADEOUT_RIGHT_NORMAL;
                }
            } else {
                targetOverlongType_ = OverlongType::LEFT_FADEOUT_RIGHT_NORMAL;
            }
        }

        return;
    }

    if (currentOverlongType_ == OverlongType::LEFT_NORMAL_RIGHT_FADEOUT) {
        targetOverlongType_ = OverlongType::LEFT_NORMAL_RIGHT_FADEOUT;
    } else if (currentOverlongType_ == OverlongType::LEFT_FADEOUT_RIGHT_NORMAL) {
        if (targetSelectedIndex_ > THIRD_POINT_INDEX) {
            targetOverlongType_ = OverlongType::LEFT_FADEOUT_RIGHT_NORMAL;
        } else if (targetSelectedIndex_ == THIRD_POINT_INDEX) {
            if (targetPageIndex > THIRD_POINT_INDEX) {
                targetOverlongType_ = OverlongType::LEFT_FADEOUT_RIGHT_FADEOUT;
            } else {
                targetOverlongType_ = OverlongType::LEFT_NORMAL_RIGHT_FADEOUT;
            }
        } else {
            targetOverlongType_ = OverlongType::LEFT_NORMAL_RIGHT_FADEOUT;
        }
    } else {
        if (targetSelectedIndex_ > THIRD_POINT_INDEX) {
            targetOverlongType_ = OverlongType::LEFT_FADEOUT_RIGHT_FADEOUT;
        } else if (targetSelectedIndex_ == THIRD_POINT_INDEX) {
            if (targetPageIndex > THIRD_POINT_INDEX) {
                targetOverlongType_ = OverlongType::LEFT_FADEOUT_RIGHT_FADEOUT;
            } else {
                targetOverlongType_ = OverlongType::LEFT_NORMAL_RIGHT_FADEOUT;
            }
        } else {
            targetOverlongType_ = OverlongType::LEFT_NORMAL_RIGHT_FADEOUT;
        }
    }
}

float OverlengthDotIndicatorModifier::CalcRealPadding(
    float unselectedIndicatorRadius, float selectedIndicatorRadius, OverlongType overlongType) const
{
    auto padding = static_cast<float>(INDICATOR_PADDING_DEFAULT.ConvertToPx());
    auto indicatorTheme = GetSwiperIndicatorTheme();
    CHECK_NULL_RETURN(indicatorTheme, padding);
    auto indicatorDotItemSpace = indicatorTheme->GetIndicatorDotItemSpace();
    auto userItemWidth = unselectedIndicatorRadius * DOUBLE_INT;
    auto userSelectedItemWidth = selectedIndicatorRadius * DOUBLE_INT;
    auto allPointSpaceSum = static_cast<float>(indicatorDotItemSpace.ConvertToPx()) * (maxDisplayCount_ - 1);
    auto allPointDiameterSum = userItemWidth * (maxDisplayCount_ - OVERLONG_SMALL_COUNT - 1) + userSelectedItemWidth +
                               userItemWidth * SECOND_SMALLEST_POINT_RATIO + userItemWidth * SMALLEST_POINT_RATIO;

    auto paddingSide = indicatorTheme->GetIndicatorPaddingDot();
    auto indicatorPaddingSide = static_cast<float>(paddingSide.ConvertToPx());
    auto maxContentWidth = indicatorPaddingSide + allPointDiameterSum + allPointSpaceSum + indicatorPaddingSide;
    if (overlongType == OverlongType::LEFT_FADEOUT_RIGHT_FADEOUT) {
        allPointDiameterSum = userItemWidth * (maxDisplayCount_ - OVERLONG_SMALL_COUNT * DOUBLE_INT - 1) +
                              userSelectedItemWidth + userItemWidth * SECOND_SMALLEST_POINT_RATIO * DOUBLE_INT +
                              userItemWidth * SMALLEST_POINT_RATIO * DOUBLE_INT;
    }

    auto realContentWidth = indicatorPaddingSide + allPointDiameterSum + allPointSpaceSum + indicatorPaddingSide;
    return padding + (maxContentWidth - realContentWidth) * HALF_FLOAT;
}

std::pair<LinearVector<float>, std::pair<float, float>> OverlengthDotIndicatorModifier::CalcIndicatorCenterX(
    const LinearVector<float>& itemHalfSizes, int32_t selectedIndex, OverlongType overlongType)
{
    if (isHorizontalAndRTL_) {
        selectedIndex = maxDisplayCount_ - 1 - selectedIndex;
        overlongType = RevertOverlongType(overlongType);
    }

    auto unselectedIndicatorRadius = itemHalfSizes[ITEM_HALF_WIDTH];
    auto selectedIndicatorRadius = itemHalfSizes[SELECTED_ITEM_HALF_WIDTH];
    if (!isCustomSizeValue_) {
        selectedIndicatorRadius *= 2.0f;
    }

    LinearVector<float> indicatorCenterX(maxDisplayCount_ + 1);
    std::pair<float, float> longPointCenterX;
    float itemSpacePx = static_cast<float>(GetIndicatorDotItemSpace().ConvertToPx());
    auto leftFirstRadius = unselectedIndicatorRadius * SMALLEST_POINT_RATIO;
    auto leftSecondRadius = unselectedIndicatorRadius * SECOND_SMALLEST_POINT_RATIO;
    auto rightFirstRadius = unselectedIndicatorRadius * SMALLEST_POINT_RATIO;
    auto rightSecondRadius = unselectedIndicatorRadius * SECOND_SMALLEST_POINT_RATIO;

    auto realPadding = CalcRealPadding(unselectedIndicatorRadius, selectedIndicatorRadius, overlongType);
    auto startIndicatorCenterX = normalMargin_.GetX() + realPadding;
    for (int32_t i = 0; i < maxDisplayCount_; i++) {
        if (i == LEFT_FIRST_POINT_INDEX) {
            if (i == selectedIndex) {
                startIndicatorCenterX += selectedIndicatorRadius;
                indicatorCenterX[i] = startIndicatorCenterX;
                startIndicatorCenterX += selectedIndicatorRadius;

                longPointCenterX.first =
                    indicatorCenterX[i] - (isCustomSizeValue_ ? 0.0f : selectedIndicatorRadius * 0.5f);
                longPointCenterX.second =
                    indicatorCenterX[i] + (isCustomSizeValue_ ? 0.0f : selectedIndicatorRadius * 0.5f);
            } else if (overlongType == OverlongType::LEFT_NORMAL_RIGHT_FADEOUT) {
                startIndicatorCenterX += unselectedIndicatorRadius;
                indicatorCenterX[i] = startIndicatorCenterX;
                startIndicatorCenterX += unselectedIndicatorRadius;
            } else {
                startIndicatorCenterX += leftFirstRadius;
                indicatorCenterX[i] = startIndicatorCenterX;
                startIndicatorCenterX += leftFirstRadius;
            }
            continue;
        }

        if (i == SECOND_POINT_INDEX) {
            if (i == selectedIndex) {
                startIndicatorCenterX += itemSpacePx + selectedIndicatorRadius;
                indicatorCenterX[i] = startIndicatorCenterX;
                startIndicatorCenterX += selectedIndicatorRadius;

                longPointCenterX.first =
                    indicatorCenterX[i] - (isCustomSizeValue_ ? 0.0f : selectedIndicatorRadius * 0.5f);
                longPointCenterX.second =
                    indicatorCenterX[i] + (isCustomSizeValue_ ? 0.0f : selectedIndicatorRadius * 0.5f);
            } else if (overlongType == OverlongType::LEFT_NORMAL_RIGHT_FADEOUT) {
                startIndicatorCenterX += itemSpacePx + unselectedIndicatorRadius;
                indicatorCenterX[i] = startIndicatorCenterX;
                startIndicatorCenterX += unselectedIndicatorRadius;
            } else {
                startIndicatorCenterX += itemSpacePx + leftSecondRadius;
                indicatorCenterX[i] = startIndicatorCenterX;
                startIndicatorCenterX += leftSecondRadius;
            }
            continue;
        }

        if (i >= THIRD_POINT_INDEX && i <= maxDisplayCount_ - 1 - THIRD_POINT_INDEX) {
            if (i == selectedIndex) {
                startIndicatorCenterX += itemSpacePx + selectedIndicatorRadius;
                indicatorCenterX[i] = startIndicatorCenterX;
                startIndicatorCenterX += selectedIndicatorRadius;

                longPointCenterX.first =
                    indicatorCenterX[i] - (isCustomSizeValue_ ? 0.0f : selectedIndicatorRadius * 0.5f);
                longPointCenterX.second =
                    indicatorCenterX[i] + (isCustomSizeValue_ ? 0.0f : selectedIndicatorRadius * 0.5f);
            } else {
                startIndicatorCenterX += itemSpacePx + unselectedIndicatorRadius;
                indicatorCenterX[i] = startIndicatorCenterX;
                startIndicatorCenterX += unselectedIndicatorRadius;
            }
            continue;
        }

        if (i == maxDisplayCount_ - 1 - SECOND_POINT_INDEX) {
            if (i == selectedIndex) {
                startIndicatorCenterX += itemSpacePx + selectedIndicatorRadius;
                indicatorCenterX[i] = startIndicatorCenterX;
                startIndicatorCenterX += selectedIndicatorRadius;

                longPointCenterX.first =
                    indicatorCenterX[i] - (isCustomSizeValue_ ? 0.0f : selectedIndicatorRadius * 0.5f);
                longPointCenterX.second =
                    indicatorCenterX[i] + (isCustomSizeValue_ ? 0.0f : selectedIndicatorRadius * 0.5f);
            } else if (overlongType == OverlongType::LEFT_FADEOUT_RIGHT_NORMAL) {
                startIndicatorCenterX += itemSpacePx + unselectedIndicatorRadius;
                indicatorCenterX[i] = startIndicatorCenterX;
                startIndicatorCenterX += unselectedIndicatorRadius;
            } else {
                startIndicatorCenterX += itemSpacePx + rightSecondRadius;
                indicatorCenterX[i] = startIndicatorCenterX;
                startIndicatorCenterX += rightSecondRadius;
            }
            continue;
        }

        if (i == maxDisplayCount_ - 1) {
            if (i == selectedIndex) {
                startIndicatorCenterX += itemSpacePx + selectedIndicatorRadius;
                indicatorCenterX[i] = startIndicatorCenterX;
                startIndicatorCenterX += selectedIndicatorRadius;

                longPointCenterX.first =
                    indicatorCenterX[i] - (isCustomSizeValue_ ? 0.0f : selectedIndicatorRadius * 0.5f);
                longPointCenterX.second =
                    indicatorCenterX[i] + (isCustomSizeValue_ ? 0.0f : selectedIndicatorRadius * 0.5f);
            } else if (overlongType == OverlongType::LEFT_FADEOUT_RIGHT_NORMAL) {
                startIndicatorCenterX += itemSpacePx + unselectedIndicatorRadius;
                indicatorCenterX[i] = startIndicatorCenterX;
                startIndicatorCenterX += unselectedIndicatorRadius;
            } else {
                startIndicatorCenterX += itemSpacePx + rightFirstRadius;
                indicatorCenterX[i] = startIndicatorCenterX;
                startIndicatorCenterX += rightFirstRadius;
            }
            continue;
        }
    }

    return std::make_pair(indicatorCenterX, longPointCenterX);
}

void OverlengthDotIndicatorModifier::AdjustTargetStatus(int32_t targetPageIndex)
{
    targetSelectedIndex_ = SwiperIndicatorUtils::GetLoopIndex(targetSelectedIndex_, maxDisplayCount_);
    if (targetPageIndex == 0 || targetPageIndex == SECOND_POINT_INDEX || targetPageIndex == THIRD_POINT_INDEX) {
        targetSelectedIndex_ = targetPageIndex;
        targetOverlongType_ = OverlongType::LEFT_NORMAL_RIGHT_FADEOUT;
        return;
    }

    if (targetPageIndex == realItemCount_ - 1) {
        targetSelectedIndex_ = maxDisplayCount_ - 1;
        targetOverlongType_ = OverlongType::LEFT_FADEOUT_RIGHT_NORMAL;
        return;
    }

    if (targetPageIndex == realItemCount_ - 1 - SECOND_POINT_INDEX) {
        targetSelectedIndex_ = maxDisplayCount_ - 1 - SECOND_POINT_INDEX;
        targetOverlongType_ = OverlongType::LEFT_FADEOUT_RIGHT_NORMAL;
        return;
    }

    if (targetPageIndex == realItemCount_ - 1 - THIRD_POINT_INDEX) {
        targetSelectedIndex_ = maxDisplayCount_ - 1 - THIRD_POINT_INDEX;
        targetOverlongType_ = OverlongType::LEFT_FADEOUT_RIGHT_NORMAL;
        return;
    }

    if (targetPageIndex > THIRD_POINT_INDEX && targetSelectedIndex_ < THIRD_POINT_INDEX) {
        InitOverlongSelectedIndex(targetPageIndex);
        return;
    }

    if (targetPageIndex < realItemCount_ - 1 - THIRD_POINT_INDEX &&
        targetSelectedIndex_ > maxDisplayCount_ - 1 - THIRD_POINT_INDEX) {
        InitOverlongSelectedIndex(targetPageIndex);
        return;
    }
}

void OverlengthDotIndicatorModifier::CalcTargetSelectedIndexOnForward(int32_t currentPageIndex, int32_t targetPageIndex)
{
    auto step = std::abs(targetPageIndex - currentPageIndex);
    auto rightThirdIndicatorIndex = maxDisplayCount_ - 1 - THIRD_POINT_INDEX;
    auto rightSecondPageIndex = realItemCount_ - 1 - SECOND_POINT_INDEX;
    if (currentSelectedIndex_ == rightThirdIndicatorIndex) {
        if (targetPageIndex < rightSecondPageIndex) {
            step = 0;
        } else {
            step = targetPageIndex - currentPageIndex;
        }
    } else if (currentSelectedIndex_ < rightThirdIndicatorIndex) {
        if (targetPageIndex < rightSecondPageIndex) {
            step = std::min(targetPageIndex - currentPageIndex, rightThirdIndicatorIndex - currentSelectedIndex_);
        } else if (targetPageIndex == rightSecondPageIndex) {
            step = rightThirdIndicatorIndex - currentSelectedIndex_ + 1;
        } else {
            step = rightThirdIndicatorIndex - currentSelectedIndex_ + THIRD_POINT_INDEX;
        }
    } else {
        step = targetPageIndex - currentPageIndex;
    }

    targetSelectedIndex_ = currentSelectedIndex_ + step;
    AdjustTargetStatus(targetPageIndex);
}

void OverlengthDotIndicatorModifier::CalcTargetSelectedIndexOnBackward(
    int32_t currentPageIndex, int32_t targetPageIndex)
{
    auto step = std::abs(targetPageIndex - currentPageIndex);
    if (currentSelectedIndex_ > THIRD_POINT_INDEX) {
        if (targetPageIndex > SECOND_POINT_INDEX) {
            step = std::min(currentPageIndex - targetPageIndex, currentSelectedIndex_ - THIRD_POINT_INDEX);
        } else if (targetPageIndex == SECOND_POINT_INDEX) {
            step = currentSelectedIndex_ - SECOND_POINT_INDEX;
        } else {
            step = currentSelectedIndex_ - LEFT_FIRST_POINT_INDEX;
        }
    } else if (currentSelectedIndex_ == THIRD_POINT_INDEX) {
        if (targetPageIndex > SECOND_POINT_INDEX) {
            step = 0;
        } else if (targetPageIndex == SECOND_POINT_INDEX) {
            step = SECOND_POINT_INDEX;
        } else {
            step = THIRD_POINT_INDEX;
        }
    } else {
        step = currentPageIndex - targetPageIndex;
    }

    targetSelectedIndex_ = currentSelectedIndex_ - step;
    AdjustTargetStatus(targetPageIndex);
}

} // namespace OHOS::Ace::NG
