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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_SWIPER_INDICATOR_DOT_INDICATOR_PAINT_METHOD_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_SWIPER_INDICATOR_DOT_INDICATOR_PAINT_METHOD_H

#include "core/common/container.h"
#include "core/components/common/properties/swiper_indicator.h"
#include "core/components_ng/pattern/swiper_indicator/dot_indicator/dot_indicator_modifier.h"
#include "core/components_ng/pattern/swiper_indicator/dot_indicator/dot_indicator_paint_property.h"
#include "core/components_ng/render/canvas_image.h"
#include "core/components_ng/render/node_paint_method.h"
#include "core/components_ng/render/paint_wrapper.h"
#include "core/components_ng/render/render_context.h"

namespace OHOS::Ace::NG {
enum class PointAnimationStage { STATE_SHRINKT_TO_BLACK_POINT, STATE_EXPAND_TO_LONG_POINT };

class ACE_EXPORT DotIndicatorPaintMethod : public NodePaintMethod {
    DECLARE_ACE_TYPE(DotIndicatorPaintMethod, NodePaintMethod)
public:
    explicit DotIndicatorPaintMethod(const RefPtr<DotIndicatorModifier>& dotIndicatorModifier)
        : dotIndicatorModifier_(dotIndicatorModifier)
    {}
    DotIndicatorPaintMethod() = default;
    ~DotIndicatorPaintMethod() override = default;

    RefPtr<Modifier> GetContentModifier(PaintWrapper* paintWrapper) override
    {
        CHECK_NULL_RETURN(dotIndicatorModifier_, nullptr);
        return dotIndicatorModifier_;
    }

    void UpdateContentModifier(PaintWrapper* paintWrapper) override;
    virtual void PaintNormalIndicator(const PaintWrapper* paintWrapper);
    void PaintHoverIndicator(const PaintWrapper* paintWrapper);
    void PaintHoverIndicator(LinearVector<float>& itemHalfSizes, const Dimension paddingSide);
    void PaintPressIndicator(const PaintWrapper* paintWrapper);
    void CalculateNormalMargin(
        const LinearVector<float>& itemHalfSizes, const SizeF& frameSize, const int32_t displayCount);
    virtual std::pair<float, float> CalculatePointCenterX(
        const LinearVector<float>& itemHalfSizes, float margin, float padding, float space, int32_t index);
    void CalculateHoverIndex(const LinearVector<float>& itemHalfSizes);
    bool isHoverPoint(const PointF& hoverPoint, const OffsetF& leftCenter,
        const OffsetF& rightCenter, const LinearVector<float>& itemHalfSizes);

    void UpdateBackground(const PaintWrapper* paintWrapper);
    void SetCurrentIndex(int32_t index)
    {
        currentIndex_ = index;
    }

    void SetItemCount(int32_t itemCount)
    {
        itemCount_ = itemCount;
    }

    void SetTotalItemCount(int32_t totalItemCount)
    {
        totalItemCount_ = totalItemCount;
    }

    void SetDisplayCount(int32_t displayCount)
    {
        displayCount_ = displayCount;
    }

    void SetSwipeByGroup(bool isSwipeByGroup)
    {
        isSwipeByGroup_ = isSwipeByGroup;
    }

    void SetAxis(Axis axis)
    {
        axis_ = axis;
    }

    Axis GetAxis() const
    {
        return axis_;
    }

    void SetIsLoop(bool isLoop)
    {
        isLoop_ = isLoop;
    }

    void SetIsHover(bool isHover)
    {
        isHover_ = isHover;
    }

    void SetIsPressed(bool isPressed)
    {
        isPressed_ = isPressed;
    }

    void SetHoverPoint(const PointF& hoverPoint)
    {
        hoverPoint_ = hoverPoint;
    }

    void SetTurnPageRate(float turnPageRate)
    {
        turnPageRate_ = turnPageRate;
    }

    void SetGroupTurnPageRate(float groupTurnPageRate)
    {
        groupTurnPageRate_ = groupTurnPageRate;
    }

    void SetGestureState(GestureState gestureState)
    {
        gestureState_ = gestureState;
    }

    void SetTouchBottomTypeLoop(TouchBottomTypeLoop touchBottomTypeLoop)
    {
        touchBottomTypeLoop_ = touchBottomTypeLoop;
    }

    void SetTouchBottomRate(float touchBottomRate)
    {
        touchBottomRate_ = touchBottomRate;
    }

    void SetTouchBottomPageRate(float touchBottomPageRate)
    {
        touchBottomPageRate_ = touchBottomPageRate;
    }

    void SetMouseClickIndex(const std::optional<int32_t>& mouseClickIndex)
    {
        mouseClickIndex_ = mouseClickIndex;
    }

    void SetIsTouchBottom(TouchBottomType touchBottomType)
    {
        touchBottomType_ = touchBottomType;
    }

    void SetPointAnimationStage(PointAnimationStage pointAnimationStage)
    {
        pointAnimationStage_ = pointAnimationStage;
    }

    void SetCurrentIndexActual(int32_t currentIndexActual)
    {
        currentIndexActual_ = currentIndexActual;
    }

    void SetNextValidIndex(int32_t nextValidIndex)
    {
        nextValidIndex_ = nextValidIndex;
    }

    void SetHorizontalAndRightToLeft(TextDirection textDirection)
    {
        isHorizontalAndRightToLeft_ = axis_ == Axis::HORIZONTAL && textDirection == TextDirection::RTL;
    }

    void SetFirstIndex(int32_t index)
    {
        firstIndex_ = index;
    }

protected:
    struct StarAndEndPointCenter {
        float startLongPointLeftCenterX = 0.0f;
        float endLongPointLeftCenterX = 0.0f;
        float startLongPointRightCenterX = 0.0f;
        float endLongPointRightCenterX = 0.0f;
    };
    virtual std::pair<float, float> CalculatePointCenterX(const StarAndEndPointCenter& starAndEndPointCenter,
        const LinearVector<float>& startVectorBlackPointCenterX,
        const LinearVector<float>& endVectorBlackPointCenterX);
    virtual std::tuple<std::pair<float, float>, LinearVector<float>> CalculateLongPointCenterX(
        const PaintWrapper* paintWrapper);
    virtual std::pair<float, float> ForwardCalculation(
        const LinearVector<float>& itemHalfSizes, float startCenterX, float endCenterX, float space, int32_t index);
    std::pair<float, float> BackwardCalculation(
        const LinearVector<float>& itemHalfSizes, float startCenterX, float endCenterX, float space, int32_t index);
    static RefPtr<OHOS::Ace::SwiperIndicatorTheme> GetSwiperIndicatorTheme()
    {
        auto pipelineContext = PipelineBase::GetCurrentContext();
        CHECK_NULL_RETURN(pipelineContext, nullptr);
        auto swiperTheme = pipelineContext->GetTheme<SwiperIndicatorTheme>();
        CHECK_NULL_RETURN(swiperTheme, nullptr);
        return swiperTheme;
    }
    virtual void UpdateNormalIndicator(LinearVector<float>& itemHalfSizes, const PaintWrapper* paintWrapper);
    std::pair<int32_t, int32_t> GetStartAndEndIndex(int32_t index);
    void GetLongPointAnimationStateSecondCenter(
        const PaintWrapper* paintWrapper, std::vector<std::pair<float, float>>& pointCenterX);
    std::tuple<float, float, float> GetMoveRate();
    void AdjustPointCenterXForTouchBottom(StarAndEndPointCenter& pointCenter,
        LinearVector<float>& endVectorBlackPointCenterX, int32_t startCurrentIndex, int32_t endCurrentIndex,
        float selectedItemWidth, int32_t index);
    bool AdjustPointCenterXForTouchBottomNew(StarAndEndPointCenter& pointCenter,
        LinearVector<float>& endVectorBlackPointCenterX, int32_t endCurrentIndex, float selectedItemWidth);
    std::pair<int32_t, int32_t> GetIndex(int32_t index);
    std::pair<int32_t, int32_t> GetIndexOnRTL(int32_t index);
    bool NeedBottomAnimation() const;
    int32_t CalculateMouseClickIndexOnRTL();
    std::pair<int32_t, int32_t> CalCurrentIndex();

    RefPtr<DotIndicatorModifier> dotIndicatorModifier_;
    PointF hoverPoint_;
    std::optional<int32_t> hoverIndex_ = std::nullopt;
    std::optional<int32_t> mouseClickIndex_ = std::nullopt;
    Axis axis_ = Axis::HORIZONTAL;
    int32_t currentIndex_ = 0;
    int32_t currentIndexActual_ = 0;
    int32_t firstIndex_ = 0;
    int32_t nextValidIndex_ = 0;
    int32_t itemCount_ = 0;
    int32_t totalItemCount_ = 0;
    int32_t displayCount_ = 1;
    float turnPageRate_ = 0.0f;
    float groupTurnPageRate_ = 0.0f;
    GestureState gestureState_ = GestureState::GESTURE_STATE_INIT;
    TouchBottomTypeLoop touchBottomTypeLoop_ = TouchBottomTypeLoop::TOUCH_BOTTOM_TYPE_LOOP_NONE;
    PointAnimationStage pointAnimationStage_ = PointAnimationStage::STATE_SHRINKT_TO_BLACK_POINT;
    float touchBottomRate_ = 0.0f;
    float touchBottomPageRate_ = 0.0f;
    bool isHorizontalAndRightToLeft_ = false;
    bool isLoop_ = true;
    bool isHover_ = false;
    bool isPressed_ = false;
    bool longPointIsHover_ = false;
    bool IsCustomSizeValue_ = false;
    bool isSwipeByGroup_ = false;
    // Animatable properties for updating Modifier
    LinearVector<float> vectorBlackPointCenterX_ = {};
    std::pair<float, float> longPointCenterX_ = { 0, 0 };
    OffsetF normalMargin_ = { 0, 0 };
    float centerY_ = 0.0f;
    TouchBottomType touchBottomType_ = TouchBottomType::NONE;
    ACE_DISALLOW_COPY_AND_MOVE(DotIndicatorPaintMethod);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_SWIPER_INDICATOR_DOT_INDICATOR_PAINT_METHOD_H