/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
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

#include "core/components_ng/pattern/pattern.h"
#include "core/components_ng/pattern/slider/slider_event_hub.h"
#include "core/components_ng/pattern/slider/slider_layout_algorithm.h"
#include "core/components_ng/pattern/slider/slider_layout_property.h"
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
        SliderPaintMethod::Parameters paintParameters { trackThickness_, blockDiameter_, sliderLength_, borderBlank_,
            stepRatio_, valueRatio_, hotBlockShadowWidth_, hotFlag_, mouseHoverFlag_, mousePressedFlag_ };
        return MakeRefPtr<SliderPaintMethod>(paintParameters);
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
        return MakeRefPtr<SliderLayoutAlgorithm>(bubbleFlag_, circleCenter_);
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

    bool HasBubbleNode() const
    {
        return bubbleId_.has_value();
    }

    int32_t GetBubbleId()
    {
        if (!bubbleId_.has_value()) {
            bubbleId_ = ElementRegister::GetInstance()->MakeUniqueId();
        }
        return bubbleId_.value();
    }

private:
    void OnModifyDone() override;
    bool OnDirtyLayoutWrapperSwap(const RefPtr<LayoutWrapper>& dirty, bool skipMeasure, bool skipLayout) override;

    void UpdateCircleCenterOffset();
    void UpdateTipsValue();
    void UpdateBubbleNode();
    void CreateAndSetBubbleNode();
    void RemoveBubbleNode();

    void UpdateMarkDirtyNode(const PropertyChangeFlag& Flag);
    Axis GetDirection() const;

    void InitTouchEvent(const RefPtr<GestureEventHub>& gestureHub);
    void HandleTouchEvent(const TouchEventInfo& info);
    void InitMouseEvent(const RefPtr<InputEventHub>& inputEventHub);
    void HandleMouseEvent(const MouseInfo& info);
    void HandleHoverEvent(bool isHover);
    void InitPanEvent(const RefPtr<GestureEventHub>& gestureHub);
    void HandlingGestureEvent(const GestureEvent& info);
    void HandledGestureEvent();

    void UpdateValueByLocalLocation(const std::optional<Offset>& localLocation);
    void FireChangeEvent(int32_t mode);

    void InitOnKeyEvent(const RefPtr<FocusHub>& focusHub);
    void GetInnerFocusPaintRect(RoundRect& paintRect);
    void GetOutsetInnerFocusPaintRect(RoundRect& paintRect);
    void GetInsetInnerFocusPaintRect(RoundRect& paintRect);
    bool OnKeyEvent(const KeyEvent& event);
    void PaintFocusState();
    bool MoveStep(int32_t stepCount);

    Axis direction_ = Axis::HORIZONTAL;
    enum SliderChangeMode { Begin = 0, Moving = 1, End = 2, Click = 3 };
    float value_ = 0.0f;
    bool showTips_ = false;
    bool hotFlag_ = false;
    bool valueChangeFlag_ = false;
    bool mouseHoverFlag_ = false;
    bool mousePressedFlag_ = false;

    float stepRatio_ = 1.0f / 100.0f;
    float valueRatio_ = 0.0f;
    float sliderLength_ = 0.0f;
    float borderBlank_ = 0.0f;
    float hotBlockShadowWidth_ = 0.0f;
    OffsetF circleCenter_ = { 0, 0 };

    float trackThickness_ = 0.0f;
    float blockDiameter_ = 0.0f;
    float blockHotSize_ = 0.0f;

    RefPtr<TouchEventImpl> touchEvent_;
    RefPtr<PanEvent> panEvent_;
    RefPtr<InputEvent> mouseEvent_;
    RefPtr<InputEvent> hoverEvent_;

    std::optional<int32_t> bubbleId_;
    bool bubbleFlag_ = false;

    ACE_DISALLOW_COPY_AND_MOVE(SliderPattern);
};

} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_SLIDER_SLIDER_PATTERN_H