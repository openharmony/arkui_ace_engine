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
#include "base/utils/utils.h"
#include "core/animation/spring_curve.h"
#include "core/components_ng/render/animation_utils.h"
#include "core/components_ng/render/drawing.h"

namespace OHOS::Ace::NG {
namespace {
constexpr Dimension INDICATOR_PADDING_DEFAULT = 12.0_vp;
constexpr uint32_t ITEM_HALF_WIDTH = 0;
constexpr uint32_t ITEM_HALF_HEIGHT = 1;
constexpr uint32_t SELECTED_ITEM_HALF_WIDTH = 2;
constexpr uint32_t SELECTED_ITEM_HALF_HEIGHT = 3;
constexpr Dimension INDICATOR_OFFSET_UNIT = 18.0_vp;
constexpr float BLACK_POINT_CENTER_BEZIER_CURVE_VELOCITY = 0.2f;
constexpr float CENTER_BEZIER_CURVE_MASS = 0.0f;
constexpr float CENTER_BEZIER_CURVE_STIFFNESS = 0.2f;
constexpr float CENTER_BEZIER_CURVE_DAMPING = 1.0f;
constexpr float OPACITY_CENTER_BEZIER_CURVE_VELOCITY = 0.33f;
constexpr float OPACITY_CENTER_BEZIER_CURVE_MASS = 0.0f;
constexpr float OPACITY_CENTER_BEZIER_CURVE_STIFFNESS = 0.67f;
constexpr float OPACITY_CENTER_BEZIER_CURVE_DAMPING = 1.0f;
constexpr float FIRST_FADING_RATIO = 0.5f;
constexpr float SECOND_FADING_RATIO = 0.75f;
constexpr float NORMAL_FADING_RATIO = 1.0f;
constexpr int32_t BLACK_POINT_DURATION = 400;
constexpr int32_t BLACK_POINT_RATIO_DURATION = 500;
constexpr int32_t POINT_OPACITY_DURATION = 1000;
constexpr int32_t NUM_0 = 0;
constexpr int32_t NUM_1 = 1;
constexpr int32_t NUM_2 = 2;
constexpr int32_t NUM_3 = 3;
constexpr int32_t NUM_4 = 4;
constexpr int32_t NUM_5 = 5;
constexpr int32_t NUM_6 = 6;
constexpr int32_t NUM_7 = 7;
constexpr int32_t NUM_8 = 8;
constexpr int32_t NUM_9 = 9;
constexpr int32_t NUM_10 = 10;
} // namespace

void OverlengthDotIndicatorModifier::onDraw(DrawingContext& context)
{
    ContentProperty contentProperty;
    contentProperty.backgroundColor = backgroundColor_->Get().ToColor();
    contentProperty.vectorBlackPointCenterX = vectorBlackPointCenterX_->Get();
    contentProperty.longPointLeftCenterX = longPointLeftCenterX_->Get();
    contentProperty.longPointRightCenterX = longPointRightCenterX_->Get();
    contentProperty.normalToHoverPointDilateRatio = normalToHoverPointDilateRatio_->Get();
    contentProperty.hoverToNormalPointDilateRatio = hoverToNormalPointDilateRatio_->Get();
    contentProperty.longPointDilateRatio = longPointDilateRatio_->Get();
    contentProperty.indicatorPadding = indicatorPadding_->Get();
    contentProperty.indicatorMargin = indicatorMargin_->Get();
    contentProperty.itemHalfSizes = itemHalfSizes_->Get();
    contentProperty.theFirstPointMove = theFirstPointMove_->Get();
    contentProperty.leftSecondPointSizeRate = leftSecondPointSizeRate_->Get();
    contentProperty.theSecondPointMove = theSecondPointMove_->Get();
    contentProperty.leftThirdPointSizeRate = leftThirdPointSizeRate_->Get();
    contentProperty.theThirdPointMove = theThirdPointMove_->Get();
    contentProperty.fourthPointMove = fourthPointMove_->Get();
    contentProperty.fifthPointMove = fifthPointMove_->Get();
    contentProperty.sixthPointMove = sixthPointMove_->Get();
    contentProperty.seventhPointMove = seventhPointMove_->Get();
    contentProperty.rightFirstPointSizeRate = rightFirstPointSizeRate_->Get();
    contentProperty.eighthPointMove = eighthPointMove_->Get();
    contentProperty.rightSecondPointSizeRate = rightSecondPointSizeRate_->Get();
    contentProperty.ninthPointMove = ninthPointMove_->Get();
    contentProperty.newPointMove = newPointMove_->Get();

    PaintBackground(context, contentProperty);
    PaintContent(context, contentProperty);
}

void OverlengthDotIndicatorModifier::PaintContent(DrawingContext& context, ContentProperty& contentProperty)
{
    PaintBlackPoint(context, contentProperty);
    RSCanvas& canvas = context.canvas;
    auto totalCount = contentProperty.vectorBlackPointCenterX.size();
    auto [leftCenterX, rightCenterX] = GetTouchBottomCenterX(contentProperty);

    OffsetF leftCenter = { leftCenterX, centerY_ };
    OffsetF rightCenter = { rightCenterX, centerY_ };
    OffsetF centerDistance = rightCenter - leftCenter;
    OffsetF centerDilateDistance = centerDistance * contentProperty.longPointDilateRatio;
    leftCenter -= (centerDilateDistance - centerDistance) * FIRST_FADING_RATIO;
    rightCenter += (centerDilateDistance - centerDistance) * FIRST_FADING_RATIO;
    PaintSelectedIndicator(
        canvas, leftCenter, rightCenter, contentProperty.itemHalfSizes * contentProperty.longPointDilateRatio);
    bool isLeftTouchBottom = (currentIndex_ == totalCount - NUM_1);
    bool isRightTouchBottom = (currentIndex_ == NUM_0);
    bool isTouchBottom = (isLeftTouchBottom || isRightTouchBottom);
    if (!isTouchBottom || totalCount == NUM_0 || !isTouchBottomLoop_) {
        return;
    }
}

void OverlengthDotIndicatorModifier::PaintBlackPoint(DrawingContext& context, ContentProperty& contentProperty)
{
    RSCanvas& canvas = context.canvas;
    auto totalCount = contentProperty.vectorBlackPointCenterX.size();
    std::vector<float> vecPointInfo;
    vecPointInfo.push_back(contentProperty.theFirstPointMove);
    vecPointInfo.push_back(contentProperty.theSecondPointMove);
    vecPointInfo.push_back(contentProperty.theThirdPointMove);
    vecPointInfo.push_back(contentProperty.fourthPointMove);
    vecPointInfo.push_back(contentProperty.fifthPointMove);
    vecPointInfo.push_back(contentProperty.sixthPointMove);
    vecPointInfo.push_back(contentProperty.seventhPointMove);
    vecPointInfo.push_back(contentProperty.eighthPointMove);
    vecPointInfo.push_back(contentProperty.ninthPointMove);
    vecPointInfo.push_back(contentProperty.newPointMove);
    for (size_t i = 0; i < totalCount; ++i) {
        LinearVector<float> itemHalfSizes = GetItemHalfSizes(i, contentProperty);
        OffsetF center = { contentProperty.vectorBlackPointCenterX[i], centerY_ };
        if (currentIndex_ > maxDisplayCount_ - NUM_3) {
            float centerX = vecPointInfo[i];
            center = { centerX, centerY_ };
        }
        if (currentIndex_ > maxDisplayCount_ - NUM_3) {
            if (i == NUM_0) {
                PaintUnselectedIndicator(canvas, center, itemHalfSizes, false, LinearColor(firstPointColor_->Get()));
            } else if (i == maxDisplayCount_) {
                PaintUnselectedIndicator(canvas, center, itemHalfSizes, false, LinearColor(newPointColor_->Get()));
            } else {
                PaintUnselectedIndicator(canvas, center, itemHalfSizes, false, LinearColor(unselectedColor_->Get()));
            }
        } else {
            if (i == maxDisplayCount_) {
                PaintUnselectedIndicator(canvas, center, itemHalfSizes, false, LinearColor(newPointColor_->Get()));
            } else {
                PaintUnselectedIndicator(canvas, center, itemHalfSizes, false, LinearColor(unselectedColor_->Get()));
            }
        }
    }
}

LinearVector<float> OverlengthDotIndicatorModifier::GetItemHalfSizes(size_t index, ContentProperty& contentProperty)
{
    if (normalToHoverIndex_.has_value() && normalToHoverIndex_ == index) {
        return contentProperty.itemHalfSizes * contentProperty.normalToHoverPointDilateRatio;
    }
    if (hoverToNormalIndex_.has_value() && hoverToNormalIndex_ == index) {
        return contentProperty.itemHalfSizes * contentProperty.hoverToNormalPointDilateRatio;
    }
    // The fade effect is triggered after the third navigation point
    bool specificPoint = NUM_2 <= currentIndex_ && index == NUM_0;
    if (specificPoint) {
        return contentProperty.itemHalfSizes * contentProperty.leftSecondPointSizeRate;
    }
    // Navigation points The last three points have a special action effect
    specificPoint = NUM_2 <= currentIndex_ && currentIndex_ < realItemCount_ - NUM_3;
    if (specificPoint) {
        if (currentIndex_ > maxDisplayCount_ - NUM_3) {
            specificPoint = index == contentProperty.vectorBlackPointCenterX.size() - NUM_2 || index == NUM_2;
            if (specificPoint) {
                return contentProperty.itemHalfSizes * contentProperty.leftThirdPointSizeRate;
            }
            specificPoint = index == contentProperty.vectorBlackPointCenterX.size() - NUM_1 || index == NUM_1;
            if (specificPoint) {
                return contentProperty.itemHalfSizes * contentProperty.leftSecondPointSizeRate;
            }
        } else {
            specificPoint = index == contentProperty.vectorBlackPointCenterX.size() - NUM_3 || index == NUM_1;
            if (specificPoint) {
                return contentProperty.itemHalfSizes * contentProperty.leftThirdPointSizeRate;
            }
            if (index == contentProperty.vectorBlackPointCenterX.size() - NUM_2 || index == NUM_0) {
                return contentProperty.itemHalfSizes * contentProperty.leftSecondPointSizeRate;
            }
        }
    }
    // The first two navigation points fade to the right
    if (currentIndex_ < NUM_2) {
        if (index == contentProperty.vectorBlackPointCenterX.size() - NUM_3) {
            return contentProperty.itemHalfSizes * SECOND_FADING_RATIO;
        }
        if (index == contentProperty.vectorBlackPointCenterX.size() - NUM_2) {
            return contentProperty.itemHalfSizes * FIRST_FADING_RATIO;
        }
    }
    // The last two pages
    if (currentIndex_ >= realItemCount_ - NUM_3) {
        if (index == NUM_1) {
            return contentProperty.itemHalfSizes * contentProperty.leftSecondPointSizeRate;
        }
        if (index == NUM_2) {
            return contentProperty.itemHalfSizes * contentProperty.leftThirdPointSizeRate;
        }
    }
    return contentProperty.itemHalfSizes;
}

void OverlengthDotIndicatorModifier::PaintUnselectedIndicator(RSCanvas& canvas, const OffsetF& center,
    const LinearVector<float>& itemHalfSizes, bool currentIndexFlag, const LinearColor& indicatorColor)
{
    RSBrush brush;
    brush.SetAntiAlias(true);
    brush.SetColor(ToRSColor(indicatorColor));
    canvas.AttachBrush(brush);
    bool bFlag = !NearEqual(itemHalfSizes[ITEM_HALF_WIDTH], itemHalfSizes[ITEM_HALF_HEIGHT]) || currentIndexFlag ||
        !isCustomSize_;
    if (bFlag) {
        float rectItemWidth = itemHalfSizes[ITEM_HALF_WIDTH] * NUM_2;
        float rectItemHeight = itemHalfSizes[ITEM_HALF_HEIGHT] * NUM_2;
        if (currentIndexFlag) {
            rectItemWidth = itemHalfSizes[SELECTED_ITEM_HALF_WIDTH] * NUM_2;
            rectItemHeight = itemHalfSizes[SELECTED_ITEM_HALF_HEIGHT] * NUM_2;
        }
        float rectLeft = (axis_ == Axis::HORIZONTAL ? center.GetX() - rectItemWidth * FIRST_FADING_RATIO
                                                    : center.GetY() - rectItemHeight * FIRST_FADING_RATIO);
        float rectTop = (axis_ == Axis::HORIZONTAL ? center.GetY() - rectItemHeight * FIRST_FADING_RATIO
                                                   : center.GetX() - rectItemWidth * FIRST_FADING_RATIO);
        float rectRight = (axis_ == Axis::HORIZONTAL ? center.GetX() + rectItemWidth * FIRST_FADING_RATIO
                                                     : center.GetY() + rectItemHeight * FIRST_FADING_RATIO);
        float rectBottom = (axis_ == Axis::HORIZONTAL ? center.GetY() + rectItemHeight * FIRST_FADING_RATIO
                                                      : center.GetX() + rectItemWidth * FIRST_FADING_RATIO);

        if (rectItemHeight > rectItemWidth || !isCustomSize_) {
            canvas.DrawRoundRect({ { rectLeft, rectTop, rectRight, rectBottom }, rectItemWidth, rectItemWidth });
        } else if (rectItemHeight < rectItemWidth) {
            canvas.DrawRoundRect({ { rectLeft, rectTop, rectRight, rectBottom }, rectItemHeight, rectItemHeight });
        } else {
            float customPointX = axis_ == Axis::HORIZONTAL ? center.GetX() : center.GetY();
            float customPointY = axis_ == Axis::HORIZONTAL ? center.GetY() : center.GetX();
            canvas.DrawCircle({ customPointX, customPointY }, rectItemHeight * FIRST_FADING_RATIO);
        }
    } else {
        float pointX = axis_ == Axis::HORIZONTAL ? center.GetX() : center.GetY();
        bool bSpecificBeg = currentIndex_ > maxDisplayCount_ - NUM_3;
        bool bmidPoint = currentIndex_ < realItemCount_ - NUM_2;
        bool blastPoint = currentIndex_ == realItemCount_ - NUM_2 || currentIndex_ == realItemCount_ - NUM_1;
        if (bSpecificBeg) {
            if (bmidPoint) {
                pointX = pointX +
                         (currentIndex_ - (maxDisplayCount_ - NUM_3) - NUM_1) * (INDICATOR_OFFSET_UNIT.ConvertToPx());
            } else if (blastPoint) {
                pointX = pointX + (realItemCount_ - maxDisplayCount_ - NUM_1) * (INDICATOR_OFFSET_UNIT.ConvertToPx());
            }
        }
        float pointY = axis_ == Axis::HORIZONTAL ? center.GetY() : center.GetX();
        canvas.DrawCircle({ pointX, pointY }, itemHalfSizes[ITEM_HALF_HEIGHT]);
    }
    canvas.DetachBrush();
}
void OverlengthDotIndicatorModifier::UpdateShrinkPaintProperty(
    const OffsetF& margin, const LinearVector<float>& normalItemHalfSizes,
    const LinearVector<float>& vectorBlackPointCenterX, const std::pair<float, float>& longPointCenterX)
{
    indicatorMargin_->Set(margin);
    indicatorPadding_->Set(static_cast<float>(INDICATOR_PADDING_DEFAULT.ConvertToPx()));

    if (longPointLeftAnimEnd_ && longPointRightAnimEnd_) {
        vectorBlackPointCenterX_->Set(vectorBlackPointCenterX);
        longPointLeftCenterX_->Set(longPointCenterX.first);
        longPointRightCenterX_->Set(longPointCenterX.second);
    }
    UpdateMaxDisplayProperty(vectorBlackPointCenterX);
    itemHalfSizes_->Set(normalItemHalfSizes);
    normalToHoverPointDilateRatio_->Set(NORMAL_FADING_RATIO);
    hoverToNormalPointDilateRatio_->Set(NORMAL_FADING_RATIO);
    longPointDilateRatio_->Set(NORMAL_FADING_RATIO);
    backgroundWidthDilateRatio_->Set(NORMAL_FADING_RATIO);
    backgroundHeightDilateRatio_->Set(NORMAL_FADING_RATIO);
}
void OverlengthDotIndicatorModifier::UpdateMaxDisplayProperty(const LinearVector<float>& vectorBlackPointCenterX)
{
    if (vectorBlackPointCenterX.size() <= NUM_6) {
        return;
    }
    float fixedOffset = (realItemCount_ - maxDisplayCount_) * (INDICATOR_OFFSET_UNIT.ConvertToPx());
    float variableOffset = (currentIndex_ - (maxDisplayCount_ - NUM_3)) * (INDICATOR_OFFSET_UNIT.ConvertToPx());
    if (currentIndex_ >= maxDisplayCount_ - NUM_3) {
        if (currentIndex_ < realItemCount_ - NUM_2) {
            UpdateDisplayProperty(vectorBlackPointCenterX, variableOffset);
        } else {
            UpdateDisplayProperty(vectorBlackPointCenterX, fixedOffset);
        }
        if (currentIndex_ > maxDisplayCount_ - NUM_3) {
            newPointColor_->Set(LinearColor(unselectedColor_->Get()));
        }
    }
}
void OverlengthDotIndicatorModifier::UpdateDisplayProperty(const LinearVector<float>& vectorBlackPointCenterX,
    const float variableOffset)
{
    auto vectorSize = vectorBlackPointCenterX.size();
    if (vectorSize <= NUM_6) {
        return;
    }
    theFirstPointMove_->Set(vectorBlackPointCenterX[NUM_0] - variableOffset);
    theSecondPointMove_->Set(vectorBlackPointCenterX[NUM_1] - variableOffset);
    theThirdPointMove_->Set(vectorBlackPointCenterX[NUM_2] - variableOffset);
    fourthPointMove_->Set(vectorBlackPointCenterX[NUM_3] - variableOffset);
    fifthPointMove_->Set(vectorBlackPointCenterX[NUM_4] - variableOffset);
    sixthPointMove_->Set(vectorBlackPointCenterX[NUM_5] - variableOffset);

    if (vectorSize == NUM_7) {
        seventhPointMove_->Set(vectorBlackPointCenterX[NUM_6] - variableOffset);
    } else if (vectorSize == NUM_8) {
        seventhPointMove_->Set(vectorBlackPointCenterX[NUM_6] - variableOffset);
        eighthPointMove_->Set(vectorBlackPointCenterX[NUM_7] - variableOffset);
    } else if (vectorSize == NUM_9) {
        seventhPointMove_->Set(vectorBlackPointCenterX[NUM_6] - variableOffset);
        eighthPointMove_->Set(vectorBlackPointCenterX[NUM_7] - variableOffset);
        ninthPointMove_->Set(vectorBlackPointCenterX[NUM_8] - variableOffset);
    } else if (vectorSize == NUM_10) {
        seventhPointMove_->Set(vectorBlackPointCenterX[NUM_6] - variableOffset);
        eighthPointMove_->Set(vectorBlackPointCenterX[NUM_7] - variableOffset);
        ninthPointMove_->Set(vectorBlackPointCenterX[NUM_8] - variableOffset);
        newPointMove_->Set(vectorBlackPointCenterX[NUM_9] - variableOffset);
    }
}
void OverlengthDotIndicatorModifier::UpdateNormalPaintProperty(
    const OffsetF& margin, const LinearVector<float>& normalItemHalfSizes,
    const LinearVector<float>& vectorBlackPointCenterX, const std::pair<float, float>& longPointCenterX)
{
    auto swiperTheme = GetSwiperIndicatorTheme();
    CHECK_NULL_VOID(swiperTheme);
    auto backgroundColor =
        indicatorMask_ ? swiperTheme->GetPressedColor() : swiperTheme->GetHoverColor().ChangeOpacity(0);
    UpdateShrinkPaintProperty(margin, normalItemHalfSizes, vectorBlackPointCenterX, longPointCenterX);
    UpdateBackgroundColor(backgroundColor);
}

void OverlengthDotIndicatorModifier::PlayBlackPointsAnimation(const LinearVector<float>& vectorBlackPointCenterX)
{
    if (maxDisplayCount_ < NUM_6) {
        return;
    }
    if (currentIndex_ > maxDisplayCount_ - NUM_3) {
        auto newPointColorCurve = AceType::MakeRefPtr<CubicCurve>(BLACK_POINT_CENTER_BEZIER_CURVE_VELOCITY,
        CENTER_BEZIER_CURVE_MASS, CENTER_BEZIER_CURVE_STIFFNESS, CENTER_BEZIER_CURVE_DAMPING);
        AnimationOption newPointColoroption;
        newPointColoroption.SetCurve(newPointColorCurve);
        newPointColoroption.SetDuration(BLACK_POINT_RATIO_DURATION);
        auto pointColor = LinearColor::TRANSPARENT;
        if (currentIndex_ >= realItemCount_ - NUM_3) {
            pointColor = LinearColor(unselectedColor_->Get());
        }
        newPointColor_->Set(pointColor);
        AnimationUtils::StartAnimation(
            newPointColoroption, [&]() { newPointColor_->Set(LinearColor(unselectedColor_->Get())); });
    }
    AnimationOption blackPointOption;
    auto pointMoveCurve = AceType::MakeRefPtr<CubicCurve>(BLACK_POINT_CENTER_BEZIER_CURVE_VELOCITY,
        CENTER_BEZIER_CURVE_MASS, CENTER_BEZIER_CURVE_STIFFNESS, CENTER_BEZIER_CURVE_DAMPING);
    blackPointOption.SetCurve(pointMoveCurve);
    blackPointOption.SetDuration(BLACK_POINT_DURATION);
    AnimationUtils::StartAnimation(blackPointOption, [&]() {
        theFirstPointMove_->Set(vectorBlackPointCenterX[NUM_0]);
        theSecondPointMove_->Set(vectorBlackPointCenterX[NUM_1]);
        theThirdPointMove_->Set(vectorBlackPointCenterX[NUM_2]);
        fourthPointMove_->Set(vectorBlackPointCenterX[NUM_3]);
        fifthPointMove_->Set(vectorBlackPointCenterX[NUM_4]);
        sixthPointMove_->Set(vectorBlackPointCenterX[NUM_5]);
        seventhPointMove_->Set(vectorBlackPointCenterX[NUM_6]);
        eighthPointMove_->Set(vectorBlackPointCenterX[NUM_7]);
        ninthPointMove_->Set(vectorBlackPointCenterX[NUM_8]);
        newPointMove_->Set(vectorBlackPointCenterX[NUM_9]);
        PlayPointOpacityAnimation();
    });

    auto sizeRateCurve = AceType::MakeRefPtr<CubicCurve>(BLACK_POINT_CENTER_BEZIER_CURVE_VELOCITY,
        CENTER_BEZIER_CURVE_MASS, CENTER_BEZIER_CURVE_STIFFNESS, CENTER_BEZIER_CURVE_DAMPING);
    AnimationOption sizeRateOption;
    sizeRateOption.SetCurve(sizeRateCurve);
    sizeRateOption.SetDuration(BLACK_POINT_RATIO_DURATION);
    AnimationUtils::StartAnimation(sizeRateOption, [&]() {
        leftSecondPointSizeRate_->Set(FIRST_FADING_RATIO);
        leftThirdPointSizeRate_->Set(SECOND_FADING_RATIO);
        rightFirstPointSizeRate_->Set(FIRST_FADING_RATIO);
        rightSecondPointSizeRate_->Set(NORMAL_FADING_RATIO);
    });
}
void OverlengthDotIndicatorModifier::PlayPointOpacityAnimation()
{
    AnimationOption optionOpacity;
    // x0:0.33, y0:0, x1:0.67, y1:1
    optionOpacity.SetCurve(AceType::MakeRefPtr<CubicCurve>(OPACITY_CENTER_BEZIER_CURVE_VELOCITY,
        OPACITY_CENTER_BEZIER_CURVE_MASS, OPACITY_CENTER_BEZIER_CURVE_STIFFNESS, OPACITY_CENTER_BEZIER_CURVE_DAMPING));
    optionOpacity.SetDuration(POINT_OPACITY_DURATION);
    isSelectedColorAnimEnd_ = false;
    isTouchBottomLoop_ = true;
    firstPointColor_->Set(LinearColor(unselectedColor_->Get()));
    auto weak = WeakClaim(this);
    AnimationUtils::StartAnimation(optionOpacity, [weak]() {
        auto modifier = weak.Upgrade();
        CHECK_NULL_VOID(modifier);
        modifier->firstPointColor_->Set(LinearColor::TRANSPARENT);
    });
}

void OverlengthDotIndicatorModifier::PlayIndicatorAnimation(const LinearVector<float>& vectorBlackPointCenterX,
    const std::vector<std::pair<float, float>>& longPointCenterX, GestureState gestureState,
    TouchBottomTypeLoop touchBottomTypeLoop)
{
    StopAnimation(false);
    isTouchBottomLoop_ = false;
    animationState_ = TouchBottomAnimationStage::STAGE_NONE;
    PlayBlackPointsAnimation(vectorBlackPointCenterX);
    PlayLongPointAnimation(longPointCenterX, gestureState, touchBottomTypeLoop, vectorBlackPointCenterX);
}
void OverlengthDotIndicatorModifier::StopAnimation(bool ifImmediately)
{
    DotIndicatorModifier::StopAnimation(ifImmediately);
    longPointLeftAnimEnd_ = true;
    longPointRightAnimEnd_ = true;
    ifNeedFinishCallback_ = false;
    newPointColor_->Set(LinearColor::TRANSPARENT);
    leftSecondPointSizeRate_->Set(FIRST_FADING_RATIO);
    leftThirdPointSizeRate_->Set(SECOND_FADING_RATIO);
    rightSecondPointSizeRate_->Set(SECOND_FADING_RATIO);
    rightFirstPointSizeRate_->Set(FIRST_FADING_RATIO);
}
} // namespace OHOS::Ace::NG
