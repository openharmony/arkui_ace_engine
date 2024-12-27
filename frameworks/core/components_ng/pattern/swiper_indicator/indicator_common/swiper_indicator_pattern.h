/*
 * Copyright (c) 2022-2024 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_SWIPER_INDICATOR_SWIPER_INDICATOR_PATTERN_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_SWIPER_INDICATOR_SWIPER_INDICATOR_PATTERN_H

#include "base/memory/ace_type.h"
#include "base/utils/utils.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/pattern.h"
#include "core/components_ng/pattern/swiper/swiper_pattern.h"
#include "core/components_ng/pattern/swiper_indicator/digit_indicator/digit_indicator_layout_algorithm.h"
#include "core/components_ng/pattern/swiper_indicator/dot_indicator/overlength_dot_indicator_paint_method.h"
#include "core/components_ng/pattern/swiper_indicator/dot_indicator/dot_indicator_layout_algorithm.h"
#include "core/components_ng/pattern/swiper_indicator/dot_indicator/dot_indicator_paint_method.h"
#include "core/components_ng/pattern/swiper_indicator/indicator_common/swiper_indicator_accessibility_property.h"
#include "core/components_ng/pattern/swiper_indicator/indicator_common/swiper_indicator_layout_property.h"
#include "core/components_ng/pattern/swiper_indicator/indicator_common/swiper_indicator_utils.h"
#include "core/components_ng/pattern/text/text_layout_property.h"
#include "core/components_ng/pattern/text/text_pattern.h"
namespace OHOS::Ace::NG {
class SwiperIndicatorPattern : public Pattern {
    DECLARE_ACE_TYPE(SwiperIndicatorPattern, Pattern);
public:
    SwiperIndicatorPattern() = default;
    ~SwiperIndicatorPattern() override = default;
    SwiperIndicatorPattern(SwiperIndicatorType indicatorType): swiperIndicatorType_(indicatorType)
    {}

    RefPtr<LayoutProperty> CreateLayoutProperty() override
    {
        return MakeRefPtr<SwiperIndicatorLayoutProperty>();
    }

    RefPtr<PaintProperty> CreatePaintProperty() override
    {
        if (SwiperIndicatorUtils::GetSwiperIndicatorType() == SwiperIndicatorType::DOT) {
            return MakeRefPtr<DotIndicatorPaintProperty>();
        } else {
            return MakeRefPtr<PaintProperty>();
        }
    }

    RefPtr<AccessibilityProperty> CreateAccessibilityProperty() override
    {
        return MakeRefPtr<SwiperIndicatorAccessibilityProperty>();
    }

    RefPtr<LayoutAlgorithm> CreateLayoutAlgorithm() override
    {
        auto swiperNode = GetSwiperNode();
        CHECK_NULL_RETURN(swiperNode, nullptr);
        auto swiperPattern = swiperNode->GetPattern<SwiperPattern>();
        CHECK_NULL_RETURN(swiperPattern, nullptr);
        if (swiperPattern->GetIndicatorType() == SwiperIndicatorType::DOT) {
            auto indicatorLayoutAlgorithm = MakeRefPtr<DotIndicatorLayoutAlgorithm>();
            indicatorLayoutAlgorithm->SetIsHoverOrPress(isHover_ || isPressed_);
            indicatorLayoutAlgorithm->SetHoverPoint(hoverPoint_);

            auto indicatorDisplayCount = Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_SIXTEEN) ?
                swiperPattern->DisplayIndicatorTotalCount() : swiperPattern->TotalCount();
            auto maxDisplayCount = swiperPattern->GetMaxDisplayCount();
            maxDisplayCount > 0 ? indicatorLayoutAlgorithm->SetIndicatorDisplayCount(maxDisplayCount)
                                : indicatorLayoutAlgorithm->SetIndicatorDisplayCount(indicatorDisplayCount);
            return indicatorLayoutAlgorithm;
        } else {
            auto indicatorLayoutAlgorithm = MakeRefPtr<DigitIndicatorLayoutAlgorithm>();
            indicatorLayoutAlgorithm->SetIsHoverOrPress(isHover_ || isPressed_);
            indicatorLayoutAlgorithm->SetHoverPoint(hoverPoint_);
            return indicatorLayoutAlgorithm;
        }
    }

    void SetDotIndicatorPaintMethodInfo(const RefPtr<SwiperPattern>& swiperPattern,
        RefPtr<DotIndicatorPaintMethod>& paintMethod,
        RefPtr<SwiperLayoutProperty>& swiperLayoutProperty)
    {
        CHECK_NULL_VOID(swiperPattern);
        CHECK_NULL_VOID(paintMethod);
        CHECK_NULL_VOID(swiperLayoutProperty);
        paintMethod->SetAxis(swiperPattern->GetDirection());
        paintMethod->SetCurrentIndex(swiperPattern->GetLoopIndex(swiperPattern->GetCurrentFirstIndex()));
        paintMethod->SetCurrentIndexActual(swiperPattern->GetLoopIndex(swiperPattern->GetCurrentIndex()));
        paintMethod->SetNextValidIndex(swiperPattern->GetNextValidIndex());
        paintMethod->SetHorizontalAndRightToLeft(swiperLayoutProperty->GetNonAutoLayoutDirection());
        paintMethod->SetItemCount(swiperPattern->DisplayIndicatorTotalCount());
        paintMethod->SetTotalItemCount(swiperPattern->TotalCount());
        paintMethod->SetSwipeByGroup(swiperLayoutProperty->GetSwipeByGroup().value_or(false));
        paintMethod->SetDisplayCount(swiperLayoutProperty->GetDisplayCount().value_or(1));
        gestureState_ = swiperPattern->GetGestureState();
        paintMethod->SetGestureState(gestureState_);
        paintMethod->SetTurnPageRate(swiperPattern->GetTurnPageRate());
        paintMethod->SetGroupTurnPageRate(swiperPattern->GetGroupTurnPageRate());
        paintMethod->SetIsLoop(swiperPattern->IsLoop());
        paintMethod->SetTouchBottomTypeLoop(swiperPattern->GetTouchBottomTypeLoop());
        paintMethod->SetIsHover(isHover_);
        paintMethod->SetIsPressed(isPressed_);
        paintMethod->SetHoverPoint(hoverPoint_);
        if (mouseClickIndex_) {
            mouseClickIndex_ = swiperPattern->GetLoopIndex(mouseClickIndex_.value());
        }
        paintMethod->SetMouseClickIndex(mouseClickIndex_);
        paintMethod->SetIsTouchBottom(touchBottomType_);
        paintMethod->SetTouchBottomRate(swiperPattern->GetTouchBottomRate());
        paintMethod->SetTouchBottomPageRate(swiperPattern->CalcCurrentTurnPageRate());
        paintMethod->SetFirstIndex(swiperPattern->GetLoopIndex(swiperPattern->GetFirstIndexInVisibleArea()));
        mouseClickIndex_ = std::nullopt;
    }

    RefPtr<NodePaintMethod> CreateNodePaintMethod() override
    {
        auto swiperNode = GetSwiperNode();
        CHECK_NULL_RETURN(swiperNode, nullptr);
        auto swiperPattern = swiperNode->GetPattern<SwiperPattern>();
        CHECK_NULL_RETURN(swiperPattern, nullptr);
        if (swiperPattern->GetIndicatorType() == SwiperIndicatorType::DOT) {
            if (swiperPattern->GetMaxDisplayCount() > 0) {
                SetIndicatorInteractive(false);
                return CreateOverlongDotIndicatorPaintMethod(swiperPattern);
            }

            SetIndicatorInteractive(swiperPattern->IsIndicatorInteractive());
            return CreateDotIndicatorPaintMethod(swiperPattern);
        }
        return nullptr;
    }

    RefPtr<FrameNode> GetSwiperNode() const
    {
        auto host = GetHost();
        CHECK_NULL_RETURN(host, nullptr);
        auto swiperNode = host->GetParent();
        CHECK_NULL_RETURN(swiperNode, nullptr);
        return DynamicCast<FrameNode>(swiperNode);
    }

    FocusPattern GetFocusPattern() const override
    {
        FocusPattern focusPattern = { FocusType::NODE, true, FocusStyleType::INNER_BORDER };
        auto pipelineContext = PipelineBase::GetCurrentContext();
        CHECK_NULL_RETURN(pipelineContext, FocusPattern());
        auto swiperTheme = pipelineContext->GetTheme<SwiperIndicatorTheme>();
        CHECK_NULL_RETURN(swiperTheme, FocusPattern());
        FocusPaintParam paintParam;
        paintParam.SetPaintWidth(swiperTheme->GetFocusedBorderWidth());
        paintParam.SetPaintColor(swiperTheme->GetFocusedColor());
        focusPattern.SetFocusPaintParams(paintParam);
        if (swiperIndicatorType_ != SwiperIndicatorType::DOT) {
            return focusPattern;
        }
        auto focusStyleType = static_cast<FocusStyleType>(swiperTheme->GetFocusStyleType());
        focusPattern.SetStyleType(focusStyleType);
        return focusPattern;
    }

    void SetChangeIndexWithAnimation(bool withAnimation)
    {
        changeIndexWithAnimation_ = withAnimation;
    }

    void SetJumpIndex(std::optional<int32_t> jumpIndex)
    {
        jumpIndex_ = jumpIndex;
    }

    void SetStartIndex(std::optional<int32_t> startIndex)
    {
        startIndex_ = startIndex;
    }

    void DumpAdvanceInfo() override;
    void DumpAdvanceInfo(std::unique_ptr<JsonValue>& json) override;
    void SetIndicatorInteractive(bool isInteractive);

private:
    void OnModifyDone() override;
    void OnAttachToFrameNode() override;
    bool OnDirtyLayoutWrapperSwap(const RefPtr<LayoutWrapper>& dirty, const DirtySwapConfig& config) override;
    void InitClickEvent(const RefPtr<GestureEventHub>& gestureHub);
    void HandleClick(const GestureEvent& info);
    void HandleMouseClick(const GestureEvent& info);
    void HandleTouchClick(const GestureEvent& info);
    void InitHoverMouseEvent();
    void InitTouchEvent(const RefPtr<GestureEventHub>& gestureHub);
    void HandleMouseEvent(const MouseInfo& info);
    void HandleHoverEvent(bool isHover);
    void HoverInAnimation(const Color& hoverColor);
    void HoverOutAnimation(const Color& normalColor);
    void HandleTouchEvent(const TouchEventInfo& info);
    void HandleTouchDown();
    void HandleTouchUp();
    void HandleDragStart(const GestureEvent& info);
    void HandleDragEnd(double dragVelocity);
    void GetMouseClickIndex();
    void UpdateTextContent(const RefPtr<SwiperIndicatorLayoutProperty>& layoutProperty,
        const RefPtr<FrameNode>& firstTextNode, const RefPtr<FrameNode>& lastTextNode);
    void UpdateTextContentSub(
        const RefPtr<SwiperIndicatorLayoutProperty>& layoutProperty,
        const RefPtr<FrameNode>& firstTextNode, const RefPtr<FrameNode>& lastTextNode);
    bool CheckIsTouchBottom(const GestureEvent& info);
    void InitLongPressEvent(const RefPtr<GestureEventHub>& gestureHub);
    void HandleLongPress(GestureEvent& info);
    void HandleLongDragUpdate(const TouchLocationInfo& info);
    bool CheckIsTouchBottom(const TouchLocationInfo& info);
    float HandleTouchClickMargin();
    int32_t GetCurrentIndex() const;
    void GetInnerFocusPaintRect(RoundRect& paintRect);
    void InitFocusEvent();
    void HandleFocusEvent();
    void HandleBlurEvent();
    void AddIsFocusActiveUpdateEvent();
    void RemoveIsFocusActiveUpdateEvent();
    void OnIsFocusActiveUpdate(bool isFocusAcitve);
    RefPtr<OverlengthDotIndicatorPaintMethod> CreateOverlongDotIndicatorPaintMethod(
        RefPtr<SwiperPattern> swiperPattern);
    RefPtr<DotIndicatorPaintMethod> CreateDotIndicatorPaintMethod(RefPtr<SwiperPattern> swiperPattern);
    RectF CalcBoundsRect() const;
    void UpdateOverlongPaintMethod(
        const RefPtr<SwiperPattern>& swiperPattern, RefPtr<OverlengthDotIndicatorPaintMethod>& overlongPaintMethod);
    int32_t GetDisplayCurrentIndex() const;
    void UpdateDigitalIndicator();
    void RegisterIndicatorChangeEvent();
    void ResetDotModifier();
    void ResetOverlongModifier();
    void UpdateFocusable() const;
    void CheckDragAndUpdate(
        const RefPtr<SwiperPattern>& swiperPattern, int32_t animationStartIndex, int32_t animationEndIndex);

    RefPtr<ClickEvent> clickEvent_;
    RefPtr<InputEvent> hoverEvent_;
    RefPtr<TouchEventImpl> touchEvent_;
    RefPtr<InputEvent> mouseEvent_;
    RefPtr<LongPressEvent> longPressEvent_;
    bool isHover_ = false;
    bool isPressed_ = false;
    PointF hoverPoint_;
    PointF dragStartPoint_;
    TouchBottomType touchBottomType_ = TouchBottomType::NONE;
    bool isClicked_ = false;
    bool isRepeatClicked_ = false;
    bool focusEventInitialized_ = false;
    std::function<void(bool)> isFocusActiveUpdateEvent_;

    std::optional<int32_t> mouseClickIndex_ = std::nullopt;
    RefPtr<DotIndicatorModifier> dotIndicatorModifier_;
    RefPtr<OverlengthDotIndicatorModifier> overlongDotIndicatorModifier_;
    SwiperIndicatorType swiperIndicatorType_ = SwiperIndicatorType::DOT;

    std::optional<int32_t> jumpIndex_;
    std::optional<int32_t> startIndex_;
    std::optional<bool> changeIndexWithAnimation_;
    GestureState gestureState_ = GestureState::GESTURE_STATE_INIT;
    ACE_DISALLOW_COPY_AND_MOVE(SwiperIndicatorPattern);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_SWIPER_INDICATOR_SWIPER_INDICATOR_PATTERN_H
