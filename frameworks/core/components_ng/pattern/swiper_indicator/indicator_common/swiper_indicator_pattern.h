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
#include "core/components_ng/pattern/swiper_indicator/circle_dot_indicator/circle_dot_indicator_layout_algorithm.h"
#include "core/components_ng/pattern/swiper_indicator/circle_dot_indicator/circle_dot_indicator_paint_method.h"
#include "core/components_ng/pattern/swiper_indicator/digit_indicator/digit_indicator_layout_algorithm.h"
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

    RefPtr<LayoutProperty> CreateLayoutProperty() override
    {
        return MakeRefPtr<SwiperIndicatorLayoutProperty>();
    }

    RefPtr<PaintProperty> CreatePaintProperty() override
    {
        if (SwiperIndicatorUtils::GetSwiperIndicatorType() == SwiperIndicatorType::DOT) {
            return MakeRefPtr<DotIndicatorPaintProperty>();
        } else if (SwiperIndicatorUtils::GetSwiperIndicatorType() == SwiperIndicatorType::ARC_DOT) {
            return MakeRefPtr<CircleDotIndicatorPaintProperty>();
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

    RefPtr<DotIndicatorPaintMethod> CreateDotIndicatorPaintMethod(RefPtr<SwiperPattern> swiperPattern)
    {
        auto swiperLayoutProperty = swiperPattern->GetLayoutProperty<SwiperLayoutProperty>();
        CHECK_NULL_RETURN(swiperLayoutProperty, nullptr);
        auto paintMethod = MakeRefPtr<DotIndicatorPaintMethod>(dotIndicatorModifier_);
        paintMethod->SetAxis(swiperPattern->GetDirection());
        paintMethod->SetCurrentIndex(swiperPattern->GetLoopIndex(swiperPattern->GetCurrentFirstIndex()));
        paintMethod->SetCurrentIndexActual(swiperPattern->GetLoopIndex(swiperPattern->GetCurrentIndex()));
        paintMethod->SetNextValidIndex(swiperPattern->GetNextValidIndex());
        paintMethod->SetHorizontalAndRightToLeft(swiperLayoutProperty->GetNonAutoLayoutDirection());
        paintMethod->SetItemCount(swiperPattern->RealTotalCount());
        paintMethod->SetDisplayCount(swiperLayoutProperty->GetDisplayCount().value_or(1));
        paintMethod->SetGestureState(swiperPattern->GetGestureState());
        paintMethod->SetTurnPageRate(swiperPattern->GetTurnPageRate());
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
        mouseClickIndex_ = std::nullopt;
        return paintMethod;
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
        paintMethod->SetMouseClickIndex(mouseClickIndex_);
        mouseClickIndex_ = std::nullopt;
        return paintMethod;
    }

    RefPtr<NodePaintMethod> CreateNodePaintMethod() override
    {
        auto swiperNode = GetSwiperNode();
        CHECK_NULL_RETURN(swiperNode, nullptr);
        auto swiperPattern = swiperNode->GetPattern<SwiperPattern>();
        CHECK_NULL_RETURN(swiperPattern, nullptr);
        if (swiperPattern->GetIndicatorType() == SwiperIndicatorType::DOT) {
            if (!dotIndicatorModifier_) {
                dotIndicatorModifier_ = AceType::MakeRefPtr<DotIndicatorModifier>();
            }
            dotIndicatorModifier_->SetAnimationDuration(swiperPattern->GetDuration());
            dotIndicatorModifier_->SetLongPointHeadCurve(
                swiperPattern->GetCurveIncludeMotion(), swiperPattern->GetMotionVelocity());

            auto paintMethod = CreateDotIndicatorPaintMethod(swiperPattern);
            auto geometryNode = swiperNode->GetGeometryNode();
            CHECK_NULL_RETURN(geometryNode, nullptr);
            auto host = GetHost();
            CHECK_NULL_RETURN(host, nullptr);
            auto indicatorGeometryNode = host->GetGeometryNode();
            CHECK_NULL_RETURN(indicatorGeometryNode, nullptr);
            auto boundsValue =
                (geometryNode->GetFrameSize().Width() - indicatorGeometryNode->GetFrameSize().Width()) * 0.5f;
            auto boundsRectOriginX = -boundsValue;
            auto boundsRectOriginY = 0.0f;
            auto boundsRectWidth = geometryNode->GetFrameSize().Width();
            auto boundsRectHeight = indicatorGeometryNode->GetFrameSize().Height();
            if (swiperPattern->GetDirection() == Axis::VERTICAL) {
                boundsValue =
                    (geometryNode->GetFrameSize().Height() - indicatorGeometryNode->GetFrameSize().Height()) * 0.5f;
                boundsRectOriginX = 0.0f;
                boundsRectOriginY = -boundsValue;
                boundsRectWidth = indicatorGeometryNode->GetFrameSize().Width();
                boundsRectHeight = geometryNode->GetFrameSize().Height();
            }
            RectF boundsRect(boundsRectOriginX, boundsRectOriginY, boundsRectWidth, boundsRectHeight);
            dotIndicatorModifier_->SetBoundsRect(boundsRect);

            return paintMethod;
        } else if (swiperPattern->GetIndicatorType() == SwiperIndicatorType::ARC_DOT) {
            if (!circleDotIndicatorModifier_) {
                circleDotIndicatorModifier_ = AceType::MakeRefPtr<CircleDotIndicatorModifier>();
            }

            auto paintMethod = CreateCircleDotIndicatorPaintMethod(swiperPattern);
            return paintMethod;
        } else {
            return nullptr;
        }
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
        auto pipelineContext = PipelineBase::GetCurrentContext();
        CHECK_NULL_RETURN(pipelineContext, FocusPattern());
        auto swiperTheme = pipelineContext->GetTheme<SwiperIndicatorTheme>();
        CHECK_NULL_RETURN(swiperTheme, FocusPattern());
        FocusPaintParam paintParam;
        paintParam.SetPaintWidth(swiperTheme->GetFocusedBorderWidth());
        paintParam.SetPaintColor(swiperTheme->GetFocusedColor());
        return { FocusType::NODE, true, FocusStyleType::INNER_BORDER, paintParam };
    }

    void DumpAdvanceInfo() override;
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
    PointF GetCenterPointF();
    float ConvertAngleWithArcDirection(SwiperArcDirection arcDirection, const float& angle);
    float GetAngleWithPoint(const PointF& conter, const PointF& point);
    void HandleLongDragUpdate(const TouchLocationInfo& info);
    bool CheckIsTouchBottom(const TouchLocationInfo& info);
    float HandleTouchClickMargin();
    bool SetArcIndicatorHotRegion(const RefPtr<LayoutWrapper>& dirty, const DirtySwapConfig& config);
    bool CalculateArcIndicatorHotRegion(const RectF& frameRect, const OffsetF& contentOffset);
    OffsetF CalculateAngleOffset(float centerX, float centerY, float radius, double angle);
    OffsetF CalculateRectLayout(double angle, float radius, OffsetF angleOffset, Dimension& width, Dimension& height);
    int32_t GetCurrentIndex() const;
    void InitFocusEvent();
    void HandleFocusEvent();
    void HandleBlurEvent();
    void AddIsFocusActiveUpdateEvent();
    void RemoveIsFocusActiveUpdateEvent();
    void OnIsFocusActiveUpdate(bool isFocusAcitve);
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

    std::optional<int32_t> mouseClickIndex_ = std::nullopt;
    std::function<void(bool)> isFocusActiveUpdateEvent_;
    RefPtr<DotIndicatorModifier> dotIndicatorModifier_;
    RefPtr<CircleDotIndicatorModifier> circleDotIndicatorModifier_;
    SwiperIndicatorType swiperIndicatorType_ = SwiperIndicatorType::DOT;
    ACE_DISALLOW_COPY_AND_MOVE(SwiperIndicatorPattern);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_SWIPER_INDICATOR_SWIPER_INDICATOR_PATTERN_H
