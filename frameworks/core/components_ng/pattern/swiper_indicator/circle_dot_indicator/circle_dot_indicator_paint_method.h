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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_SWIPER_INDICATOR_CIRCLE_DOT_INDICATOR_PAINT_METHOD_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_SWIPER_INDICATOR_CIRCLE_DOT_INDICATOR_PAINT_METHOD_H

#include "core/components/common/properties/swiper_indicator.h"
#include "core/components/declaration/swiper/swiper_declaration.h"
#include "core/components_ng/pattern/swiper_indicator/circle_dot_indicator/circle_dot_indicator_modifier.h"
#include "core/components_ng/pattern/swiper_indicator/circle_dot_indicator/circle_dot_indicator_paint_property.h"
#include "core/components_ng/pattern/swiper_indicator/dot_indicator/dot_indicator_paint_method.h"
#include "core/components_ng/render/canvas_image.h"
#include "core/components_ng/render/node_paint_method.h"
#include "core/components_ng/render/paint_wrapper.h"
#include "core/components_ng/render/render_context.h"

namespace OHOS::Ace::NG {
namespace {
constexpr int32_t MAX_INDICATOR_DOT_COUNT = 15;
constexpr int32_t TRIGGER_BOUNDARY_DISTANCE = 2;
} // namespace
class ACE_EXPORT CircleDotIndicatorPaintMethod : public NodePaintMethod {
    DECLARE_ACE_TYPE(CircleDotIndicatorPaintMethod, NodePaintMethod)
public:
    explicit CircleDotIndicatorPaintMethod(const RefPtr<CircleDotIndicatorModifier>& circleDotIndicatorModifier)
        : circleDotIndicatorModifier_(circleDotIndicatorModifier)
    {}
    ~CircleDotIndicatorPaintMethod() override = default;

    RefPtr<Modifier> GetContentModifier(PaintWrapper* paintWrapper) override
    {
        CHECK_NULL_RETURN(circleDotIndicatorModifier_, nullptr);
        return circleDotIndicatorModifier_;
    }

    void UpdateContentModifier(PaintWrapper* paintWrapper) override;
    void PaintNormalIndicator(const PaintWrapper* paintWrapper);
    void PaintPressIndicator(const PaintWrapper* paintWrapper);
    std::pair<float, float> CalculatePointAngle(const LinearVector<float>& itemSizes, int32_t currentIndex);

    void SetCurrentIndex(int32_t index)
    {
        currentIndex_ = index;
    }

    void SetItemCount(int32_t itemCount)
    {
        itemCount_ = itemCount;
    }

    void SetAxis(Axis axis)
    {
        axis_ = axis;
    }

    Axis GetAxis() const
    {
        return axis_;
    }

    void SetIsLongPressed(bool isLongPressed)
    {
        isLongPressed_ = isLongPressed;
    }

    void SetTurnPageRate(float turnPageRate)
    {
        turnPageRate_ = turnPageRate;
    }

    void SetGestureState(GestureState gestureState)
    {
        gestureState_ = gestureState;
    }

    void SetTouchBottomTypeLoop(TouchBottomTypeLoop touchBottomTypeLoop)
    {
        touchBottomTypeLoop_ = touchBottomTypeLoop;
    }

    void SetMouseClickIndex(const std::optional<int32_t>& mouseClickIndex)
    {
        mouseClickIndex_ = mouseClickIndex;
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

    void SetIsTouchBottom(TouchBottomType touchBottomType)
    {
        touchBottomType_ = touchBottomType;
    }

    void SetTouchBottomRate(float touchBottomRate)
    {
        touchBottomRate_ = touchBottomRate;
    }

    void UpdateBackground(const PaintWrapper* paintWrapper);

private:
    void CalculateLongPointCenterAngle(float longPointLeftCenterMoveRate, float longPointRightCenterMoveRate);
    std::tuple<std::pair<float, float>, LinearVector<float>> CalculateLongPointCenterAngle(
        const PaintWrapper* paintWrapper, bool isNormal);
    void UpdateNormalIndicator(LinearVector<float>& itemSizes, const PaintWrapper* paintWrapper);
    std::pair<int32_t, int32_t> GetStartAndEndIndex(int32_t index);
    std::pair<int32_t, int32_t> GetIndex(int32_t index);
    int32_t GetHalfIndex();
    float GetBlackPointAngle(const LinearVector<float>& itemSizes, int32_t index, int32_t currentIndex, float offset);
    std::pair<float, float> GetLongPointAngle(
        const LinearVector<float>& itemSizes, int32_t currentIndex, int32_t indicatorStartIndex);
    float GetAllPointArcAngle(const LinearVector<float>& itemSizes, int32_t currentIndex);
    void CalculatePointRadius(int32_t index, int32_t indicatorStartIndex);
    void CalculateRemainPointRadius(int32_t index, float itemNormalRadius, float itemMinorRadius, float itemMiniRadius,
        int32_t indicatorStartIndex);
    bool CalculateStartPointRadius(int32_t index, float itemNormalRadius, float itemMinorRadius, float itemMiniRadius,
        int32_t indicatorStartIndex);
    float CalculateBlackPointRotateAngle(int32_t indicatorStartIndex, int32_t itemIndex);
    int32_t CalculateIndicatorStartIndex(int32_t priorIndicatorIndex);
    int32_t CalculateInitIndicatorPosition();
    void SetFadeOutState(int32_t indicatorStartIndex);
    float GetFadeOutPadding(float dotPaddingAngle, int32_t itemIndex, int32_t currentIndex,
        const LinearVector<float>& itemSizes, int32_t symbol);
    std::tuple<float, float, float> GetMoveRate();
    void CalculatePointCenterAngle();

    RefPtr<CircleDotIndicatorModifier> circleDotIndicatorModifier_;
    std::optional<int32_t> mouseClickIndex_ = std::nullopt;
    Axis axis_ = Axis::HORIZONTAL;
    int32_t currentIndex_ = 0;
    int32_t currentIndexActual_ = 0;
    int32_t nextValidIndex_ = 0;
    int32_t itemCount_ = 0;
    int32_t indicatorStartIndex_ = 0;
    float turnPageRate_ = 0.0f;
    float touchBottomRate_ = 0.0f;
    SwiperArcDirection arcDirection_ = SwiperArcDirection::SIX_CLOCK_DIRECTION;
    GestureState gestureState_ = GestureState::GESTURE_STATE_INIT;
    TouchBottomTypeLoop touchBottomTypeLoop_ = TouchBottomTypeLoop::TOUCH_BOTTOM_TYPE_LOOP_NONE;
    PointAnimationStage pointAnimationStage_ = PointAnimationStage::STATE_SHRINKT_TO_BLACK_POINT;
    bool isLongPressed_ = false;
    // Animatable properties for updating Modifier
    LinearVector<float> vectorBlackPointAngle_ = {};
    LinearVector<float> vectorBlackPointRadius_ = {};
    std::pair<float, float> longPointAngle_ = { 0, 0 };
    LinearVector<float> longPointCenter_ = {};
    ACE_DISALLOW_COPY_AND_MOVE(CircleDotIndicatorPaintMethod);
    TouchBottomType touchBottomType_ = TouchBottomType::NONE;
    FadeOutState fadeOutState_ = FadeOutState::FADE_OUT_NONE;
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_SWIPER_INDICATOR_CIRCLE_DOT_INDICATOR_PAINT_METHOD_H