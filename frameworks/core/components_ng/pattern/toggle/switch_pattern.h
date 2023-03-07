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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_SWITCH_SWITCH_PATTERN_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_SWITCH_SWITCH_PATTERN_H

#include "base/geometry/axis.h"
#include "base/geometry/size.h"
#include "base/memory/referenced.h"
#include "core/components/checkable/checkable_theme.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/event/event_hub.h"
#include "core/components_ng/pattern/pattern.h"
#include "core/components_ng/pattern/toggle/switch_event_hub.h"
#include "core/components_ng/pattern/toggle/switch_layout_algorithm.h"
#include "core/components_ng/pattern/toggle/switch_paint_method.h"
#include "core/components_ng/pattern/toggle/switch_paint_property.h"

namespace OHOS::Ace::NG {

class SwitchPattern : public Pattern {
    DECLARE_ACE_TYPE(SwitchPattern, Pattern);

public:
    SwitchPattern() = default;

    ~SwitchPattern() override = default;

    RefPtr<EventHub> CreateEventHub() override
    {
        return MakeRefPtr<SwitchEventHub>();
    }

    RefPtr<LayoutAlgorithm> CreateLayoutAlgorithm() override
    {
        return MakeRefPtr<SwitchLayoutAlgorithm>();
    }

    RefPtr<PaintProperty> CreatePaintProperty() override
    {
        auto paintProperty = MakeRefPtr<SwitchPaintProperty>();
        paintProperty->UpdateCurrentOffset(currentOffset_);
        return paintProperty;
    }

    RefPtr<NodePaintMethod> CreateNodePaintMethod() override
    {
        auto host = GetHost();
        CHECK_NULL_RETURN(host, nullptr);
        if (!switchModifier_) {
            auto pipeline = PipelineBase::GetCurrentContext();
            auto switchTheme = pipeline->GetTheme<SwitchTheme>();
            auto paintProperty = host->GetPaintProperty<SwitchPaintProperty>();
            auto isSelect = paintProperty->GetIsOnValue(false);
            auto boardColor = isSelect ? paintProperty->GetSelectedColorValue(switchTheme->GetActiveColor())
                                       : switchTheme->GetInactivePointColor();
            switchModifier_ = AceType::MakeRefPtr<SwitchModifier>(isSelect, boardColor, currentOffset_);
        }
        auto paintMethod = MakeRefPtr<SwitchPaintMethod>(switchModifier_);
        paintMethod->SetIsSelect(isOnBeforeAnimate_.value_or(false));
        auto eventHub = host->GetEventHub<EventHub>();
        CHECK_NULL_RETURN(eventHub, nullptr);
        auto enabled = eventHub->IsEnabled();
        paintMethod->SetEnabled(enabled);
        paintMethod->SetMainDelta(currentOffset_);
        paintMethod->SetIsHover(isHover_);
        return paintMethod;
    }

    FocusPattern GetFocusPattern() const override
    {
        FocusPaintParam focusPaintParams;

        auto pipelineContext = PipelineBase::GetCurrentContext();
        CHECK_NULL_RETURN(pipelineContext, FocusPattern());
        auto switchTheme = pipelineContext->GetTheme<SwitchTheme>();
        CHECK_NULL_RETURN(switchTheme, FocusPattern());
        auto focusPaintcolor = switchTheme->GetActiveColor();
        focusPaintParams.SetPaintColor(focusPaintcolor);
        focusPaintParams.SetFocusPadding(Dimension(2.0_vp));

        return { FocusType::NODE, true, FocusStyleType::CUSTOM_REGION, focusPaintParams };
    }

private:
    void OnModifyDone() override;
    void UpdateCurrentOffset(float offset);
    void OnAttachToFrameNode() override;
    bool OnDirtyLayoutWrapperSwap(const RefPtr<LayoutWrapper>& dirty, bool skipMeasure, bool skipLayout) override;
    void PlayTranslateAnimation(float startPos, float endPos);
    RefPtr<Curve> GetCurve() const;
    int32_t GetDuration() const;
    void StopTranslateAnimation();
    void UpdateChangeEvent() const;
    void OnChange();
    void OnTouchDown();
    void OnTouchUp();
    void HandleMouseEvent(bool isHover);
    float GetSwitchWidth() const;

    // Init pan recognizer to move items when drag update, play translate animation when drag end.
    void InitPanEvent(const RefPtr<GestureEventHub>& gestureHub);
    void InitClickEvent();
    void InitTouchEvent();
    void InitMouseEvent();

    // Init key event
    void InitOnKeyEvent(const RefPtr<FocusHub>& focusHub);
    bool OnKeyEvent(const KeyEvent& event);
    void GetInnerFocusPaintRect(RoundRect& paintRect);

    void HandleDragUpdate(const GestureEvent& info);
    void HandleDragEnd();

    bool IsOutOfBoundary(double mainOffset) const;
    void OnClick();
    void AddHotZoneRect();

    RefPtr<PanEvent> panEvent_;

    RefPtr<Animator> controller_;
    RefPtr<ClickEvent> clickListener_;
    RefPtr<CurveAnimation<double>> translate_;
    std::optional<bool> isOn_;
    std::optional<bool> isOnBeforeAnimate_;
    bool changeFlag_ = false;
    float currentOffset_ = 0.0f;

    RefPtr<TouchEventImpl> touchListener_;
    RefPtr<InputEvent> mouseEvent_;
    bool isTouch_ = false;
    bool isHover_ = false;

    float width_ = 0.0f;
    float height_ = 0.0f;
    Dimension hotZoneHorizontalPadding_;
    Dimension hotZoneVerticalPadding_;
    OffsetF offset_;
    SizeF size_;
    OffsetF hotZoneOffset_;
    SizeF hotZoneSize_;

    RefPtr<SwitchModifier> switchModifier_;

    ACE_DISALLOW_COPY_AND_MOVE(SwitchPattern);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_SWITCH_SWITCH_PATTERN_H