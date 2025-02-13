/*
 * Copyright (c) 2022-2025 Huawei Device Co., Ltd.
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
#include "core/components_ng/pattern/swiper_indicator/circle_dot_indicator/circle_dot_indicator_layout_algorithm.h"
#include "core/components_ng/pattern/swiper_indicator/circle_dot_indicator/circle_dot_indicator_paint_method.h"
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
        if (swiperIndicatorType_ == SwiperIndicatorType::DOT) {
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
        if (GetIndicatorType() == SwiperIndicatorType::DOT) {
            auto indicatorLayoutAlgorithm = MakeRefPtr<DotIndicatorLayoutAlgorithm>();
            indicatorLayoutAlgorithm->SetIsHoverOrPress(isHover_ || isPressed_);
            indicatorLayoutAlgorithm->SetHoverPoint(hoverPoint_);

            auto indicatorDisplayCount = Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_SIXTEEN) ?
                swiperPattern->DisplayIndicatorTotalCount() : swiperPattern->TotalCount();
            auto maxDisplayCount = swiperPattern->GetMaxDisplayCount();
            maxDisplayCount > 0 ? indicatorLayoutAlgorithm->SetIndicatorDisplayCount(maxDisplayCount)
                                : indicatorLayoutAlgorithm->SetIndicatorDisplayCount(indicatorDisplayCount);
            return indicatorLayoutAlgorithm;
        } else if (swiperPattern->GetIndicatorType() == SwiperIndicatorType::ARC_DOT) {
            auto indicatorLayoutAlgorithm = MakeRefPtr<CircleDotIndicatorLayoutAlgorithm>();
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
        auto currentTurnPageRate = Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_SIXTEEN) &&
            swiperLayoutProperty->GetSwipeByGroup().value_or(false) ?
            swiperPattern->CalculateGroupTurnPageRate(0.0f) : swiperPattern->CalcCurrentTurnPageRate();
        paintMethod->SetTouchBottomPageRate(currentTurnPageRate);
        paintMethod->SetFirstIndex(swiperPattern->GetLoopIndex(swiperPattern->GetFirstIndexInVisibleArea()));
        mouseClickIndex_ = std::nullopt;
    }

    RefPtr<CircleDotIndicatorPaintMethod> CreateCircleDotIndicatorPaintMethod(RefPtr<SwiperPattern> swiperPattern)
    {
        auto swiperLayoutProperty = swiperPattern->GetLayoutProperty<SwiperLayoutProperty>();
        CHECK_NULL_RETURN(swiperLayoutProperty, nullptr);
        auto paintMethod = MakeRefPtr<CircleDotIndicatorPaintMethod>(circleDotIndicatorModifier_);
        paintMethod->SetAxis(swiperPattern->GetDirection());
        paintMethod->SetCurrentIndex(swiperPattern->GetLoopIndex(swiperPattern->GetCurrentFirstIndex()));
        paintMethod->SetCurrentIndexActual(swiperPattern->GetLoopIndex(swiperPattern->GetCurrentIndex()));
        paintMethod->SetNextValidIndex(swiperPattern->GetNextValidIndex());
        paintMethod->SetItemCount(swiperPattern->RealTotalCount());
        paintMethod->SetGestureState(swiperPattern->GetGestureState());
        paintMethod->SetTurnPageRate(swiperPattern->GetTurnPageRate());
        paintMethod->SetTouchBottomTypeLoop(swiperPattern->GetTouchBottomTypeLoop());
        paintMethod->SetIsLongPressed(isLongPressed_);
        if (mouseClickIndex_) {
            mouseClickIndex_ = swiperPattern->GetLoopIndex(mouseClickIndex_.value());
        }
        paintMethod->SetIsTouchBottom(touchBottomType_);
        paintMethod->SetMouseClickIndex(mouseClickIndex_);
        paintMethod->SetTouchBottomRate(swiperPattern->GetTouchBottomRate());
        mouseClickIndex_ = std::nullopt;
        return paintMethod;
    }

    RefPtr<NodePaintMethod> CreateNodePaintMethod() override
    {
        auto swiperNode = GetSwiperNode();
        CHECK_NULL_RETURN(swiperNode, nullptr);
        auto swiperPattern = swiperNode->GetPattern<SwiperPattern>();
        CHECK_NULL_RETURN(swiperPattern, nullptr);
        if (GetIndicatorType() == SwiperIndicatorType::DOT) {
            if (swiperPattern->GetMaxDisplayCount() > 0) {
                SetIndicatorInteractive(false);
                return CreateOverlongDotIndicatorPaintMethod(swiperPattern);
            }

            SetIndicatorInteractive(swiperPattern->IsIndicatorInteractive());
            return CreateDotIndicatorPaintMethod(swiperPattern);
        } else if (swiperPattern->GetIndicatorType() == SwiperIndicatorType::ARC_DOT) {
            if (!circleDotIndicatorModifier_) {
                circleDotIndicatorModifier_ = AceType::MakeRefPtr<CircleDotIndicatorModifier>();
                circleDotIndicatorModifier_->SetLongPointHeadCurve(swiperPattern->GetCurveIncludeMotion());
            }

            auto paintMethod = CreateCircleDotIndicatorPaintMethod(swiperPattern);
            return paintMethod;
        }
        return nullptr;
    }

    virtual RefPtr<FrameNode> GetSwiperNode() const
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
    virtual bool SetArcIndicatorHotRegion(const RefPtr<LayoutWrapper>& dirty, const DirtySwapConfig& config)
    {
        return false;
    }
    virtual PointF GetCenterPointF()
    {
        return PointF(0.0, 0.0);
    }
    virtual float GetAngleWithPoint(const PointF& conter, const PointF& point)
    {
        return 0.0;
    }
    virtual void InitAccessibilityFocusEvent(){};
    virtual Axis GetDirection() const;
    virtual bool GetDotCurrentOffset(OffsetF& offset, float indicatorWidth, float indicatorHeight);
    void OnModifyDone() override;
    void IndicatorOnChange();
    void InitIndicatorEvent();
    virtual bool GetDigitFrameSize(RefPtr<GeometryNode>& geoNode, SizeF& frameSize) const;
    virtual int32_t RealTotalCount() const;
    virtual int32_t GetCurrentIndex() const;
    void ResetDotModifier();
    
private:
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
    bool CheckIsTouchBottom(const TouchLocationInfo& info);
    float HandleTouchClickMargin();
    int32_t GetInitialIndex() const;
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
    void UpdateOverlongPaintMethod(
        const RefPtr<SwiperPattern>& swiperPattern, RefPtr<OverlengthDotIndicatorPaintMethod>& overlongPaintMethod);
    int32_t GetDisplayCurrentIndex() const;
    void UpdateDigitalIndicator();
    void RegisterIndicatorChangeEvent();
    std::pair<int32_t, int32_t> CalculateStepAndItemCount() const;
    std::pair<int32_t, int32_t> CalculateStepAndItemCountDefault() const;
    void UpdateFocusable() const;
    void CheckDragAndUpdate(
        const RefPtr<SwiperPattern>& swiperPattern, int32_t animationStartIndex, int32_t animationEndIndex);

    double GetIndicatorDragAngleThreshold(bool isMaxAngle);
    RefPtr<ClickEvent> clickEvent_;
    RefPtr<InputEvent> hoverEvent_;
    RefPtr<TouchEventImpl> touchEvent_;
    RefPtr<InputEvent> mouseEvent_;
    RefPtr<LongPressEvent> longPressEvent_;
    bool isHover_ = false;
    bool isPressed_ = false;
    bool isLongPressed_ = false;
    PointF hoverPoint_;
    PointF dragStartPoint_;
    TouchBottomType touchBottomType_ = TouchBottomType::NONE;
    bool isClicked_ = false;
    bool isRepeatClicked_ = false;
    bool focusEventInitialized_ = false;
    std::function<void(bool)> isFocusActiveUpdateEvent_;

    std::optional<int32_t> mouseClickIndex_ = std::nullopt;
    RefPtr<DotIndicatorModifier> dotIndicatorModifier_;
    RefPtr<CircleDotIndicatorModifier> circleDotIndicatorModifier_;
    RefPtr<OverlengthDotIndicatorModifier> overlongDotIndicatorModifier_;
    SwiperIndicatorType swiperIndicatorType_ = SwiperIndicatorType::DOT;

    std::optional<int32_t> jumpIndex_;
    std::optional<int32_t> startIndex_;
    std::optional<bool> changeIndexWithAnimation_;
    GestureState gestureState_ = GestureState::GESTURE_STATE_INIT;
    ACE_DISALLOW_COPY_AND_MOVE(SwiperIndicatorPattern);

protected:
    OffsetF CalculateAngleOffset(float centerX, float centerY, float radius, double angle);
    OffsetF CalculateRectLayout(double angle, float radius, OffsetF angleOffset, Dimension& width, Dimension& height);
    virtual void FireChangeEvent() const {}
    virtual void FireIndicatorIndexChangeEvent(int32_t index) const {}
    virtual void SwipeTo(std::optional<int32_t> mouseClickIndex);
    virtual void ShowPrevious();
    virtual void ShowNext();
    virtual void ChangeIndex(int32_t index, bool useAnimation);
    virtual bool IsHorizontalAndRightToLeft() const;
    virtual TextDirection GetNonAutoLayoutDirection() const;
    virtual void GetTextContentSub(std::string& firstContent, std::string& lastContent) const;
    virtual int32_t GetCurrentShownIndex() const;
    virtual int32_t DisplayIndicatorTotalCount() const;
    virtual bool IsLoop() const;
    virtual int32_t GetTouchCurrentIndex() const;
    virtual std::pair<int32_t, int32_t> CalMouseClickIndexStartAndEnd(int32_t itemCount, int32_t currentIndex);
    virtual void HandleLongDragUpdate(const TouchLocationInfo& info);

    RefPtr<SwiperPattern> GetSwiperPattern() const
    {
        auto swiperNode = GetSwiperNode();
        CHECK_NULL_RETURN(swiperNode, nullptr);
        return swiperNode->GetPattern<SwiperPattern>();
    }

    virtual SwiperIndicatorType GetIndicatorType() const
    {
        auto swiperPattern = GetSwiperPattern();
        CHECK_NULL_RETURN(swiperPattern, SwiperIndicatorType::DOT);
        return swiperPattern->GetIndicatorType();
    }

    const bool& IsHover() const
    {
        return isHover_;
    }

    const bool& IsPressed() const
    {
        return isPressed_;
    }

    const PointF& GetHoverPoint() const
    {
        return hoverPoint_;
    }

    std::optional<int32_t> GetOptinalMouseClickIndex() const
    {
        return mouseClickIndex_;
    }

    void SetMouseClickIndex(int32_t mouseClickIndex)
    {
        if (mouseClickIndex_) {
            mouseClickIndex_ = mouseClickIndex;
        }
    }

    void ResetOptinalMouseClickIndex()
    {
        mouseClickIndex_ = std::nullopt;
    }

    const TouchBottomType& GetTouchBottomType() const
    {
        return touchBottomType_;
    }

    const RefPtr<DotIndicatorModifier>& GetDotIndicatorModifier() const
    {
        return dotIndicatorModifier_;
    }
 
    void SetDotIndicatorModifier(RefPtr<DotIndicatorModifier> dotIndicatorModifier)
    {
        dotIndicatorModifier_ = dotIndicatorModifier;
    }

    const RefPtr<OverlengthDotIndicatorModifier>& GetOverlengthDotIndicatorModifier() const
    {
        return overlongDotIndicatorModifier_;
    }

    void SetOverlengthDotIndicatorModifier(RefPtr<OverlengthDotIndicatorModifier> overlongDotIndicatorModifier)
    {
        overlongDotIndicatorModifier_ = overlongDotIndicatorModifier;
    }

    const PointF& GetDragStartPoint() const
    {
        return dragStartPoint_;
    }

    void SetDragStartPoint(PointF dragStartPoint)
    {
        dragStartPoint_ = dragStartPoint;
    }

    RectF CalcBoundsRect() const;
    int32_t GetLoopIndex(int32_t originalIndex) const;
    void ResetOverlongModifier();
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_SWIPER_INDICATOR_SWIPER_INDICATOR_PATTERN_H
