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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_SWIPER_OVER_INDICATOR_SWIPER_INDICATOR_MODIFIER_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_SWIPER_OVER_INDICATOR_SWIPER_INDICATOR_MODIFIER_H

#include <optional>

#include "core/components/swiper/swiper_indicator_theme.h"
#include "core/components_ng/base/modifier.h"
#include "core/components_ng/pattern/swiper_indicator/dot_indicator/dot_indicator_modifier.h"
namespace OHOS::Ace::NG {
constexpr float ONE_IN_TWO = 0.5f;
constexpr float THREE_QUARTERS = 0.75f;
class OverlengthDotIndicatorModifier : public DotIndicatorModifier {
    DECLARE_ACE_TYPE(OverlengthDotIndicatorModifier, DotIndicatorModifier);

public:
    OverlengthDotIndicatorModifier()
        : DotIndicatorModifier(),
          firstPointOpacity_(AceType::MakeRefPtr<AnimatablePropertyUint8>(0)),
          newPointOpacity_(AceType::MakeRefPtr<AnimatablePropertyUint8>(0)),
          unselectedIndicatorWidth_(AceType::MakeRefPtr<AnimatablePropertyVectorFloat>(LinearVector<float>(0))),
          unselectedIndicatorHeight_(AceType::MakeRefPtr<AnimatablePropertyVectorFloat>(LinearVector<float>(0)))
    {
        AttachProperty(firstPointOpacity_);
        AttachProperty(newPointOpacity_);
        AttachProperty(unselectedIndicatorWidth_);
        AttachProperty(unselectedIndicatorHeight_);
    }
    ~OverlengthDotIndicatorModifier() override = default;

    void onDraw(DrawingContext& context) override;
    // paint
    void PaintContent(DrawingContext& context, ContentProperty& contentProperty) override;
    void PaintBlackPoint(DrawingContext& context, ContentProperty& contentProperty);
    void PaintUnselectedIndicator(
        RSCanvas& canvas, const OffsetF& center, float width, float height, const LinearColor& indicatorColor);
    void UpdateShrinkPaintProperty(const OffsetF& margin, const LinearVector<float>& normalItemHalfSizes,
        const std::pair<float, float>& longPointCenterX);

    void UpdateNormalPaintProperty(const OffsetF& margin, const LinearVector<float>& normalItemHalfSizes,
        const std::pair<float, float>& longPointCenterX);
    void SetRealItemCount(int32_t realItemCount)
    {
        realItemCount_ = realItemCount;
    }
   
    void SetMaxDisplayCount(int32_t maxDisplayCount)
    {
        maxDisplayCount_ = maxDisplayCount;
    }

    void PlayIndicatorAnimation(const OffsetF& margin, const LinearVector<float>& itemHalfSizes,
        GestureState gestureState, TouchBottomTypeLoop touchBottomTypeLoop);

    void SetMoveDirection(OverlongIndicatorMove moveDirection)
    {
        moveDirection_ = moveDirection;
    }

    void SetAnimationStartCenterX(const LinearVector<float>& animationStartCenterX)
    {
        animationStartCenterX_ = animationStartCenterX;
    }

    void SetAnimationEndCenterX(const LinearVector<float>& animationEndCenterX)
    {
        animationEndCenterX_ = animationEndCenterX;
    }

    void SetAnimationStartIndicatorWidth(const LinearVector<float>& animationStartIndicatorWidth)
    {
        animationStartIndicatorWidth_ = animationStartIndicatorWidth;
    }

    void SetAnimationEndIndicatorWidth(const LinearVector<float>& animationEndIndicatorWidth)
    {
        animationEndIndicatorWidth_ = animationEndIndicatorWidth;
    }

    void SetAnimationStartIndicatorHeight(const LinearVector<float>& animationStartIndicatorHeight)
    {
        animationStartIndicatorHeight_ = animationStartIndicatorHeight;
    }

    void SetAnimationEndIndicatorHeight(const LinearVector<float>& animationEndIndicatorHeight)
    {
        animationEndIndicatorHeight_ = animationEndIndicatorHeight;
    }

    OverlongType GetCurrentOverlongType() const
    {
        return currentOverlongType_;
    }

    void SetCurrentOverlongType(OverlongType currentOverlongType)
    {
        currentOverlongType_ = currentOverlongType;
    }

    void SetAnimationStartIndex(int32_t animationStartIndex)
    {
        animationStartIndex_ = animationStartIndex;
    }

    void SetAnimationEndIndex(int32_t animationEndIndex)
    {
        animationEndIndex_ = animationEndIndex;
    }

    int32_t GetAnimationEndIndex() const
    {
        return animationEndIndex_;
    }

    void SetTurnPageRate(float turnPageRate)
    {
        turnPageRate_ = turnPageRate;
    }

    void SetBlackPointCenterMoveRate(float blackPointCenterMoveRate)
    {
        blackPointCenterMoveRate_ = blackPointCenterMoveRate;
    }

    void SetLongPointLeftCenterMoveRate(float longPointLeftCenterMoveRate)
    {
        longPointLeftCenterMoveRate_ = longPointLeftCenterMoveRate;
    }

    void SetLongPointRightCenterMoveRate(float longPointRightCenterMoveRate)
    {
        longPointRightCenterMoveRate_ = longPointRightCenterMoveRate;
    }

    void SetGestureState(GestureState gestureState)
    {
        gestureState_ = gestureState;
    }

    void SetIsCustomSizeValue(bool isCustomSizeValue)
    {
        isCustomSizeValue_ = isCustomSizeValue;
    }

    void SetTouchBottomTypeLoop(TouchBottomTypeLoop touchBottomTypeLoop)
    {
        touchBottomTypeLoop_ = touchBottomTypeLoop;
    }

    void SetIsSwiperTouchDown(bool isSwiperTouchDown)
    {
        isSwiperTouchDown_ = isSwiperTouchDown;
    }

    void SetIsHorizontalAndRTL(bool isHorizontalAndRTL)
    {
        isHorizontalAndRTL_ = isHorizontalAndRTL;
    }

    void SetKeepStatus(bool keepStatus)
    {
        keepStatus_ = keepStatus;
    }

    void UpdateCurrentStatus()
    {
        currentSelectedIndex_ = targetSelectedIndex_;
        currentOverlongType_ = targetOverlongType_;
    }

    void SetNeedUpdate(bool needUpdate)
    {
        needUpdate_ = needUpdate;
    }

    void SetIsAutoPlay(bool isAutoPlay)
    {
        isAutoPlay_ = isAutoPlay;
    }

    void InitOverlongStatus(int32_t pageIndex);
    void InitOverlongSelectedIndex(int32_t pageIndex);
    void CalcTargetSelectedIndex(int32_t currentPageIndex, int32_t targetPageIndex);
    void CalcTargetSelectedIndexOnForward(int32_t currentPageIndex, int32_t targetPageIndex);
    void CalcTargetSelectedIndexOnBackward(int32_t currentPageIndex, int32_t targetPageIndex);
    void CalcTargetOverlongStatus(int32_t currentPageIndex, int32_t targetPageIndex);
    void StopAnimation(bool ifImmediately) override;

private:
    void PlayBlackPointsAnimation(const LinearVector<float>& itemHalfSizes);
    void CalcAnimationEndCenterX(const LinearVector<float>& itemHalfSizes);
    void CalcTargetStatusOnLongPointMove(const LinearVector<float>& itemHalfSizes);
    void CalcTargetStatusOnAllPointMoveForward(const LinearVector<float>& itemHalfSizes);
    void CalcTargetStatusOnAllPointMoveBackward(const LinearVector<float>& itemHalfSizes);
    std::pair<LinearVector<float>, std::pair<float, float>> CalcIndicatorCenterX(
        const LinearVector<float>& itemHalfSizes, int32_t selectedIndex, OverlongType overlongType);
    LinearVector<float> CalcIndicatorSize(
        const LinearVector<float>& itemHalfSizes, OverlongType overlongType, bool isWidth);
    void UpdateSelectedCenterXOnDrag(const LinearVector<float>& itemHalfSizes);
    void UpdateUnselectedCenterXOnDrag();
    int32_t CalcTargetIndexOnDrag() const;
    std::pair<float, float> CalcLongPointEndCenterXWithBlack(size_t index, const LinearVector<float>& itemHalfSizes);
    float GetMoveRateOnAllMove() const;
    int32_t GetBlackPointsAnimationDuration() const;
    void AdjustTargetStatus(int32_t targetPageIndex);
    std::pair<float, float> GetTouchBottomCenterX(ContentProperty& contentProperty);
    OverlongType RevertOverlongType(OverlongType overlongType) const;
    void StopBlackAnimation();

    RefPtr<AnimatablePropertyUint8> firstPointOpacity_;
    RefPtr<AnimatablePropertyUint8> newPointOpacity_;
    RefPtr<AnimatablePropertyVectorFloat> unselectedIndicatorWidth_;
    RefPtr<AnimatablePropertyVectorFloat> unselectedIndicatorHeight_;
    int32_t maxDisplayCount_ = 0;
    int32_t realItemCount_ = 0;
    OverlongIndicatorMove moveDirection_ = OverlongIndicatorMove::NONE;
    LinearVector<float> animationStartCenterX_ = {};
    LinearVector<float> animationEndCenterX_ = {};
    LinearVector<float> animationStartIndicatorWidth_ = {};
    LinearVector<float> animationEndIndicatorWidth_ = {};
    LinearVector<float> animationStartIndicatorHeight_ = {};
    LinearVector<float> animationEndIndicatorHeight_ = {};
    std::pair<float, float> overlongSelectedStartCenterX_ = { 0.0f, 0.0f};
    std::pair<float, float> overlongSelectedEndCenterX_ = { 0.0f, 0.0f};
    OffsetF normalMargin_ = { 0, 0 };

    int32_t animationStartIndex_ = 0;
    int32_t animationEndIndex_ = 0;
    int32_t currentSelectedIndex_ = 0;
    int32_t targetSelectedIndex_ = 0;
    OverlongType currentOverlongType_ = OverlongType::NONE;
    OverlongType targetOverlongType_ = OverlongType::NONE;
    float turnPageRate_ = 0.0f;
    float blackPointCenterMoveRate_ = 0.0f;
    float longPointLeftCenterMoveRate_ = 0.0f;
    float longPointRightCenterMoveRate_ = 0.0f;
    GestureState gestureState_ = GestureState::GESTURE_STATE_INIT;
    TouchBottomTypeLoop touchBottomTypeLoop_ = TouchBottomTypeLoop::TOUCH_BOTTOM_TYPE_LOOP_NONE;
    bool isCustomSizeValue_ = false;
    bool isSwiperTouchDown_ = false;
    bool keepStatus_ = false;
    bool blackPointsAnimEnd_ = true;
    bool isHorizontalAndRTL_ = false;
    bool needUpdate_ = true;
    bool isAutoPlay_ = false;
    ACE_DISALLOW_COPY_AND_MOVE(OverlengthDotIndicatorModifier);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_SWIPER_OVER_INDICATOR_SWIPER_INDICATOR_MODIFIER_H
