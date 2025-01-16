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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_INDICATOR_PATTERN_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_INDICATOR_PATTERN_H

#include "core/components_ng/pattern/swiper_indicator/indicator_common/indicator_controller.h"
#include "core/components_ng/pattern/swiper_indicator/indicator_common/indicator_event_hub.h"
#include "core/components_ng/pattern/swiper_indicator/indicator_common/swiper_indicator_layout_property.h"
#include "core/components_ng/pattern/swiper_indicator/indicator_common/swiper_indicator_pattern.h"
#include "core/components_ng/pattern/swiper_indicator/indicator_common/indicator_accessibility.h"
namespace OHOS::Ace::NG {
class IndicatorPattern : public SwiperIndicatorPattern {
    DECLARE_ACE_TYPE(IndicatorPattern, SwiperIndicatorPattern);

public:
    IndicatorPattern();
    ~IndicatorPattern() override = default;

    RefPtr<AccessibilityProperty> CreateAccessibilityProperty() override
    {
        return MakeRefPtr<IndicatorAccessibilityProperty>();
    }

    SwiperIndicatorType GetIndicatorType() const override
    {
        return GetIndicatorTypeFromProperty();
    }

    RefPtr<EventHub> CreateEventHub() override
    {
        return MakeRefPtr<IndicatorEventHub>();
    }

    const RefPtr<IndicatorController>& GetIndicatorController() const
    {
        return indicatorController_;
    }

    void UpdateChangeEvent(ChangeEvent&& event)
    {
        if (!changeEvent_) {
            changeEvent_ = std::make_shared<ChangeEvent>(event);
            auto eventHub = GetEventHub<IndicatorEventHub>();
            CHECK_NULL_VOID(eventHub);
            eventHub->AddOnChangeEvent(changeEvent_);
        } else {
            (*changeEvent_).swap(event);
        }
    }

    void SetSwiperParameters(const SwiperParameters& swiperParameters)
    {
        swiperParameters_ = std::make_shared<SwiperParameters>(swiperParameters);
    }

    void SetSwiperDigitalParameters(const SwiperDigitalParameters& swiperDigitalParameters);
    bool GetDigitFrameSize(RefPtr<GeometryNode>& geoNode, SizeF& frameSize) const override;
    bool GetDotCurrentOffset(OffsetF& offset, float indicatorWidth, float indicatorHeight) override;

    RefPtr<FrameNode> WeakUINode2RefFrameNode(WeakPtr<NG::UINode>& weakUINode) const
    {
        auto refUINode = weakUINode.Upgrade();
        CHECK_NULL_RETURN(refUINode, nullptr);
        auto frameNode = DynamicCast<FrameNode>(refUINode);
        CHECK_NULL_RETURN(frameNode, nullptr);
        return frameNode;
    }

    RefPtr<FrameNode> GetBindSwiperNode() const
    {
        auto controller = GetIndicatorController();
        CHECK_NULL_RETURN(controller, nullptr);
        auto weakUINode = controller->GetSwiperNode();
        return WeakUINode2RefFrameNode(weakUINode);
    }

    RefPtr<LayoutAlgorithm> CreateLayoutAlgorithm() override
    {
        if (GetBindSwiperNode()) {
            return SwiperIndicatorPattern::CreateLayoutAlgorithm();
        }

        if (GetIndicatorType() == SwiperIndicatorType::DOT) {
            auto indicatorLayoutAlgorithm = MakeRefPtr<DotIndicatorLayoutAlgorithm>();
            indicatorLayoutAlgorithm->SetIsHoverOrPress(IsHover() || IsPressed());
            indicatorLayoutAlgorithm->SetHoverPoint(GetHoverPoint());
            indicatorLayoutAlgorithm->SetIndicatorDisplayCount(GetCountFromProperty());
            return indicatorLayoutAlgorithm;
        } else {
            auto indicatorLayoutAlgorithm = MakeRefPtr<DigitIndicatorLayoutAlgorithm>();
            indicatorLayoutAlgorithm->SetIsHoverOrPress(IsHover() || IsPressed());
            indicatorLayoutAlgorithm->SetHoverPoint(GetHoverPoint());
            return indicatorLayoutAlgorithm;
        }
    }

    RefPtr<FrameNode> GetSwiperNode() const override
    {
        return GetBindSwiperNode();
    }

    RefPtr<NodePaintMethod> CreateNodePaintMethod() override
    {
        if (GetBindSwiperNode()) {
            return SwiperIndicatorPattern::CreateNodePaintMethod();
        }

        if (GetIndicatorType() == SwiperIndicatorType::DOT) {
            return CreateDotIndicatorPaintMethodInSingleMode();
        }
        return nullptr;
    }

    void SetCurrentIndexInSingleMode(int32_t index)
    {
        currentIndexInSingleMode_ = index;
    }

    RefPtr<DotIndicatorPaintMethod> CreateDotIndicatorPaintMethodInSingleMode()
    {
        ResetOverlongModifier();

        if (!GetDotIndicatorModifier()) {
            SetDotIndicatorModifier(AceType::MakeRefPtr<DotIndicatorModifier>());
        }

        auto paintMethod = MakeRefPtr<DotIndicatorPaintMethod>(GetDotIndicatorModifier());
        SetDotIndicatorPaintMethodInfoInSingleMode(paintMethod);

        GetDotIndicatorModifier()->SetBoundsRect(CalcBoundsRect());
        return paintMethod;
    }

    void SetDotIndicatorPaintMethodInfoInSingleMode(RefPtr<DotIndicatorPaintMethod>& paintMethod)
    {
        paintMethod->SetAxis(GetDirection());
        paintMethod->SetCurrentIndex(GetLoopIndex(currentIndexInSingleMode_));
        paintMethod->SetCurrentIndexActual(GetLoopIndex(currentIndexInSingleMode_));
        paintMethod->SetHorizontalAndRightToLeft(GetNonAutoLayoutDirection());
        paintMethod->SetItemCount(RealTotalCount());
        paintMethod->SetGestureState(singleGestureState_);
        paintMethod->SetIsLoop(IsLoop());
        paintMethod->SetIsHover(IsHover());
        paintMethod->SetIsPressed(IsPressed());
        paintMethod->SetHoverPoint(GetHoverPoint());
        if (GetOptinalMouseClickIndex()) {
            SetMouseClickIndex(GetLoopIndex(GetOptinalMouseClickIndex().value()));
        }
        paintMethod->SetMouseClickIndex(GetOptinalMouseClickIndex());
        paintMethod->SetIsTouchBottom(GetTouchBottomType());
        GetOptinalMouseClickIndex() = std::nullopt;
    }

    const bool& IsIndicatorCustomSize() const
    {
        return isCustomSize_;
    }

    void SetIsIndicatorCustomSize(bool isCustomSize)
    {
        isCustomSize_ = isCustomSize;
    }
    void OnIndexChangeInSingleMode(int32_t index);
    void ShowPrevious() override;
    void ShowNext() override;
    void ChangeIndex(int32_t index, bool useAnimation) override;
    int32_t GetCurrentIndex() const override;
    int32_t GetCurrentShownIndex() const override;
    int32_t DisplayIndicatorTotalCount() const override;
    int32_t RealTotalCount() const override;
    Axis GetDirection() const override;
    bool IsHorizontalAndRightToLeft() const override;
    TextDirection GetNonAutoLayoutDirection() const override;
    bool IsLoop() const override;
    void GetTextContentSub(std::string& firstContent, std::string& lastContent) const override;
    void SwipeTo(std::optional<int32_t> mouseClickIndex) override;
    void OnModifyDone() override;
    int32_t currentIndexInSingleMode_ = 0;
    int32_t hasSetInitialIndex_ = false;

protected:
    void FireChangeEvent() const override;
    SwiperIndicatorType GetIndicatorTypeFromProperty() const;
    Axis GetDirectionFromProperty() const;
    int32_t GetInitialIndexFromProperty() const;
    int32_t GetCountFromProperty() const;
    bool IsLoopFromProperty() const;

private:
    void InitIndicatorController();
    std::shared_ptr<SwiperParameters> GetSwiperParameters();
    std::shared_ptr<SwiperDigitalParameters> GetSwiperDigitalParameters();
    void SaveDotIndicatorProperty();
    void SaveDigitIndicatorProperty();
    void UpdatePaintProperty();
    RefPtr<IndicatorController> indicatorController_;
    mutable std::shared_ptr<SwiperParameters> swiperParameters_;
    mutable std::shared_ptr<SwiperDigitalParameters> swiperDigitalParameters_;
    ChangeEventPtr changeEvent_;
    GestureState singleGestureState_ = GestureState::GESTURE_STATE_INIT;
    bool isCustomSize_ = false;
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_INDICATOR_PATTERN_H
