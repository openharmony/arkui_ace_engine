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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_SLIDER_SLIDER_PATTERN_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_SLIDER_SLIDER_PATTERN_H

#include <cstddef>
#include <optional>

#include "core/components_ng/pattern/pattern.h"
#include "core/components_ng/pattern/slider/slider_content_modifier.h"
#include "core/components_ng/pattern/slider/slider_event_hub.h"
#include "core/components_ng/pattern/slider/slider_layout_algorithm.h"
#include "core/components_ng/pattern/slider/slider_layout_property.h"
#include "core/components_ng/pattern/slider/slider_model_ng.h"
#include "core/components_ng/pattern/slider/slider_paint_method.h"
#include "core/components_ng/pattern/slider/slider_paint_property.h"

namespace OHOS::Ace::NG {
class SliderPattern : public Pattern {
    DECLARE_ACE_TYPE(SliderPattern, Pattern);

public:
    SliderPattern() = default;
    ~SliderPattern() override = default;

    RefPtr<NodePaintMethod> CreateNodePaintMethod() override
    {
        if (!IsSliderVisible()) {
            return nullptr;
        }
        auto paintParameters = UpdateContentParameters();
        if (!sliderContentModifier_) {
            sliderContentModifier_ = AceType::MakeRefPtr<SliderContentModifier>(
                paintParameters,
                [weak = WeakClaim(this)](float x) {
                    auto pattern = weak.Upgrade();
                    CHECK_NULL_VOID(pattern);
                    pattern->UpdateImagePositionX(x);
                },
                [weak = WeakClaim(this)](float y) {
                    auto pattern = weak.Upgrade();
                    CHECK_NULL_VOID(pattern);
                    pattern->UpdateImagePositionY(y);
                });
        }
        sliderContentModifier_->SetUseContentModifier(UseContentModifier());
        auto overlayGlobalOffset = CalculateGlobalSafeOffset();
        std::pair<OffsetF, float> BubbleVertex = GetBubbleVertexPosition(circleCenter_, trackThickness_, blockSize_);
        SliderPaintMethod::TipParameters tipParameters { bubbleFlag_, BubbleVertex.first, overlayGlobalOffset };
        if (!sliderTipModifier_ && bubbleFlag_) {
            sliderTipModifier_ = AceType::MakeRefPtr<SliderTipModifier>([weak = WeakClaim(this)]() {
                auto pattern = weak.Upgrade();
                if (!pattern) {
                    return std::pair<OffsetF, float>();
                }
                auto blockCenter = pattern->GetBlockCenter();
                auto trackThickness = pattern->sliderContentModifier_->GetTrackThickness();
                auto blockSize = pattern->sliderContentModifier_->GetBlockSize();
                return pattern->GetBubbleVertexPosition(blockCenter, trackThickness, blockSize);
            });
        }
        auto textDirection = TextDirection::AUTO;
        auto layoutProperty = GetLayoutProperty<SliderLayoutProperty>();
        if (layoutProperty) {
            textDirection = layoutProperty->GetLayoutDirection();
        }
        return MakeRefPtr<SliderPaintMethod>(sliderContentModifier_, paintParameters, sliderLength_, borderBlank_,
            sliderTipModifier_, tipParameters, textDirection);
    }

    RefPtr<LayoutProperty> CreateLayoutProperty() override
    {
        return MakeRefPtr<SliderLayoutProperty>();
    }

    RefPtr<PaintProperty> CreatePaintProperty() override
    {
        return MakeRefPtr<SliderPaintProperty>();
    }

    RefPtr<LayoutAlgorithm> CreateLayoutAlgorithm() override
    {
        return MakeRefPtr<SliderLayoutAlgorithm>();
    }

    RefPtr<AccessibilityProperty> CreateAccessibilityProperty() override;

    RefPtr<EventHub> CreateEventHub() override
    {
        return MakeRefPtr<SliderEventHub>();
    }

    FocusPattern GetFocusPattern() const override
    {
        return { FocusType::NODE, true, FocusStyleType::CUSTOM_REGION };
    }

    const OffsetF& GetBlockCenter() const
    {
        return circleCenter_;
    }

    std::optional<OffsetF> GetAnimatableBlockCenter() const
    {
        if (sliderContentModifier_ != nullptr) {
            auto blockCenter = sliderContentModifier_->GetBlockCenter();
            return OffsetF(blockCenter.GetX(), blockCenter.GetY());
        }
        return std::nullopt;
    }

    float GetValueRatio() const
    {
        return valueRatio_;
    }

    std::string ProvideRestoreInfo() override;
    void OnRestoreInfo(const std::string& restoreInfo) override;
    OffsetF CalculateGlobalSafeOffset();
    void UpdateValue(float value);
    void OnWindowSizeChanged(int32_t width, int32_t height, WindowSizeChangeReason type) override;

    void SetBuilderFunc(SliderMakeCallback&& makeFunc)
    {
        if (makeFunc == nullptr) {
            makeFunc_ = std::nullopt;
            OnModifyDone();
            return;
        }
        makeFunc_ = std::move(makeFunc);
        if (sliderContentModifier_) {
            sliderContentModifier_->SetUseContentModifier(true);
        }
    }

    bool UseContentModifier()
    {
        return contentModifierNode_ != nullptr;
    }

    void SetSliderValue(double value, int32_t mode);

private:
    void OnAttachToFrameNode() override;
    void OnDetachFromFrameNode(FrameNode* frameNode) override;
    void OnModifyDone() override;
    void CalcSliderValue();
    void CancelExceptionValue(float& min, float& max, float& step);
    bool OnDirtyLayoutWrapperSwap(const RefPtr<LayoutWrapper>& dirty, bool skipMeasure, bool skipLayout) override;
    bool UpdateParameters();
    void CreateParagraphFunc();
    void CreateParagraphAndLayout(
        const TextStyle& textStyle, const std::string& content, const LayoutConstraintF& contentConstraint);
    bool CreateParagraph(const TextStyle& textStyle, std::string content);
    void UpdateCircleCenterOffset();
    void UpdateTipsValue();
    void UpdateBubbleSizeAndLayout();
    void UpdateBubble();
    void InitializeBubble();

    bool AtMousePanArea(const Offset& offsetInFrame);
    bool AtTouchPanArea(const Offset& offsetInFrame);
    bool AtPanArea(const Offset& offset, const SourceType& sourceType);

    void UpdateMarkDirtyNode(const PropertyChangeFlag& Flag);
    Axis GetDirection() const;

    void InitClickEvent(const RefPtr<GestureEventHub>& gestureHub);
    void InitTouchEvent(const RefPtr<GestureEventHub>& gestureHub);
    void HandleTouchEvent(const TouchEventInfo& info);
    void HandleTouchDown(const Offset& location, SourceType sourceType);
    void HandleTouchUp(const Offset& location, SourceType sourceType);
    void InitMouseEvent(const RefPtr<InputEventHub>& inputEventHub);
    void HandleMouseEvent(const MouseInfo& info);
    void HandleHoverEvent(bool isHover);
    void HandleEnabled();
    void InitPanEvent(const RefPtr<GestureEventHub>& gestureHub);
    void HandlingGestureStart(const GestureEvent& info);
    void HandlingGestureEvent(const GestureEvent& info);
    void HandledGestureEvent();

    void UpdateValueByLocalLocation(const std::optional<Offset>& localLocation);
    void FireChangeEvent(int32_t mode);

    void InitOnKeyEvent(const RefPtr<FocusHub>& focusHub);
    void GetInnerFocusPaintRect(RoundRect& paintRect);
    void GetOutsetInnerFocusPaintRect(RoundRect& paintRect);
    void GetInsetAndNoneInnerFocusPaintRect(RoundRect& paintRect);
    bool OnKeyEvent(const KeyEvent& event);
    void PaintFocusState();
    bool MoveStep(int32_t stepCount);

    bool IsSliderVisible();
    void RegisterVisibleAreaChange();
    void OnWindowHide() override;
    void OnWindowShow() override;
    void StartAnimation();
    void StopAnimation();

    void OpenTranslateAnimation(SliderStatus status);
    void CloseTranslateAnimation();
    SliderContentModifier::Parameters UpdateContentParameters();
    void GetSelectPosition(SliderContentModifier::Parameters& parameters, float centerWidth, const OffsetF& offset);
    void GetBackgroundPosition(SliderContentModifier::Parameters& parameters, float centerWidth, const OffsetF& offset);
    void GetCirclePosition(SliderContentModifier::Parameters& parameters, float centerWidth, const OffsetF& offset);
    void UpdateBlock();
    void LayoutImageNode();
    void UpdateImagePositionX(float centerX);
    void UpdateImagePositionY(float centerY);
    std::pair<OffsetF, float> GetBubbleVertexPosition(
        const OffsetF& blockCenter, float trackThickness, const SizeF& blockSize);
    void SetAccessibilityAction();
    void UpdateTipState();
    void OnIsFocusActiveUpdate(bool isFocusActive);
    void AddIsFocusActiveUpdateEvent();
    void RemoveIsFocusActiveUpdateEvent();
    bool isMinResponseExceed(const std::optional<Offset>& localLocation);
    void FireBuilder();
    RefPtr<FrameNode> BuildContentModifierNode();
    float GetValueInValidRange(const RefPtr<SliderPaintProperty>& paintProperty, float value, float min, float max);
    void UpdateToValidValue();
    void AccessibilityVirtualNodeRenderTask();
    void InitAccessibilityHoverEvent();
    void HandleAccessibilityHoverEvent(bool state, const AccessibilityHoverInfo& info);
    bool InitAccessibilityVirtualNode();
    void ModifyAccessibilityVirtualNode();
    void AddStepPointsAccessibilityVirtualNode();
    void HandleTextOnAccessibilityFocusCallback();
    void HandleSliderOnAccessibilityFocusCallback();
    void UpdateStepAccessibilityVirtualNode();
    std::string GetPointAccessibilityTxt(uint32_t pointIndex, float stepRatio, float min, float max);
    uint32_t GetCurrentStepIndex();
    SizeF GetStepPointAccessibilityVirtualNodeSize();
    void UpdateStepPointsAccessibilityVirtualNodeSelected();
    void SetStepPointsAccessibilityVirtualNodeEvent(
        const RefPtr<FrameNode>& pointNode, uint32_t index, bool isClickAbled, bool reverse);
    void SetStepPointAccessibilityVirtualNode(
        const RefPtr<FrameNode>& pointNode, const SizeF& size, const PointF& point, const std::string& txt);
    void SendAccessibilityValueEvent(int32_t mode);

    std::optional<SliderMakeCallback> makeFunc_;
    RefPtr<FrameNode> contentModifierNode_;
    void SetSkipGestureEvents()
    {
        skipGestureEvents_ = true;
    }
    void ResetSkipGestureEvents()
    {
        skipGestureEvents_ = false;
    }
    bool IsSkipGestureEvents()
    {
        return skipGestureEvents_;
    }

    Axis direction_ = Axis::HORIZONTAL;
    enum SliderChangeMode { Begin = 0, Moving = 1, End = 2, Click = 3 };
    float value_ = 0.0f;
    float minResponse_ = 0.0f;
    bool skipGestureEvents_ = false;
    float minResponseStartValue_ = value_;
    bool isMinResponseExceedFlag_ = false;
    SourceType eventSourceDevice_ = SourceType::NONE;
    Offset eventLocalLocation_ {};
    bool showTips_ = false;
    bool hotFlag_ = false; // whether the mouse is hovering over the slider
    bool valueChangeFlag_ = false;
    bool mouseHoverFlag_ = false;
    bool mousePressedFlag_ = false;
    bool axisFlag_ = false; // Wheel operation flag
    bool focusFlag_ = false;
    bool panMoveFlag_ = false;
    bool hasVisibleChangeRegistered_ = false;
    bool isVisibleArea_ = true;
    bool isShow_ = true;
    SliderModelNG::SliderInteraction sliderInteractionMode_ = SliderModelNG::SliderInteraction::SLIDE_AND_CLICK;
    bool allowDragEvents_ = true;
    int32_t fingerId_ = -1;
    std::optional<Offset> lastTouchLocation_ = std::nullopt;

    float valueRatio_ = 0.0f;
    float sliderLength_ = 0.0f;
    float borderBlank_ = 0.0f;
    float hotBlockShadowWidth_ = 0.0f;
    double axisOffset_ = 0.0;
    OffsetF circleCenter_ = { 0.0f, 0.0f }; // Relative to the content area

    float trackThickness_ = 0.0f;
    SizeF blockHotSize_;
    SizeF blockSize_;

    RefPtr<TouchEventImpl> touchEvent_;
    RefPtr<ClickEvent> clickListener_;
    RefPtr<PanEvent> panEvent_;
    RefPtr<InputEvent> mouseEvent_;
    RefPtr<InputEvent> hoverEvent_;

    RefPtr<SliderContentModifier> sliderContentModifier_;

    // tip Parameters
    bool bubbleFlag_ = false;
    RefPtr<SliderTipModifier> sliderTipModifier_;

    RefPtr<FrameNode> imageFrameNode_;
    std::function<void(bool)> isFocusActiveUpdateEvent_;
    bool isFocusActive_ = false;

    RefPtr<FrameNode> parentAccessibilityNode_;
    std::vector<RefPtr<FrameNode>> pointAccessibilityNodeVec_;
    std::vector<GestureEventFunc> pointAccessibilityNodeEventVec_;
    bool isInitAccessibilityVirtualNode_ = false;
    uint64_t lastAccessibilityValueTime_ = 0;
    float accessibilityValue_ = 0.0f;
    
    ACE_DISALLOW_COPY_AND_MOVE(SliderPattern);
};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_SLIDER_SLIDER_PATTERN_H
