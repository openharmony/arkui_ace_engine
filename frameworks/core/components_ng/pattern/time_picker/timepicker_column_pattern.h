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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_TIME_PICKER_TIME_PICKER_COLUMN_PATTERN_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_TIME_PICKER_TIME_PICKER_COLUMN_PATTERN_H

#include <utility>

#include "base/i18n/localization.h"
#include "core/components/common/properties/color.h"
#include "core/components/picker/picker_base_component.h"
#include "core/components/picker/picker_date_component.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/linear_layout/linear_layout_pattern.h"
#include "core/components_ng/pattern/text/text_layout_property.h"
#include "core/components_ng/pattern/time_picker/timepicker_column_accessibility_property.h"
#include "core/components_ng/pattern/time_picker/timepicker_column_layout_algorithm.h"
#include "core/components_ng/pattern/time_picker/timepicker_layout_property.h"
#include "core/components_ng/pattern/time_picker/toss_animation_controller.h"

namespace OHOS::Ace::NG {

using ColumnChangeCallback = std::function<void(const RefPtr<FrameNode>&, bool, uint32_t, bool)>;
using ColumnFinishCallback = std::function<void(bool)>;
using EventCallback = std::function<void(bool)>;

struct TextProperties {
    Dimension upFontSize;
    Dimension fontSize;
    Dimension downFontSize;
    Color upColor;
    Color currentColor;
    Color downColor;
};

class TimePickerColumnPattern : public LinearLayoutPattern {
    DECLARE_ACE_TYPE(TimePickerColumnPattern, LinearLayoutPattern);

public:
    TimePickerColumnPattern() : LinearLayoutPattern(true) {};

    ~TimePickerColumnPattern() override = default;

    RefPtr<LayoutAlgorithm> CreateLayoutAlgorithm() override
    {
        auto layoutAlgorithm = MakeRefPtr<TimePickerColumnLayoutAlgorithm>();
        layoutAlgorithm->SetCurrentOffset(GetCurrentOffset());
        return layoutAlgorithm;
    }

    RefPtr<LayoutProperty> CreateLayoutProperty() override
    {
        return MakeRefPtr<LinearLayoutProperty>(isVertical_);
    }

    RefPtr<AccessibilityProperty> CreateAccessibilityProperty() override
    {
        return MakeRefPtr<TimePickerColumnAccessibilityProperty>();
    }

    void FlushCurrentOptions(bool isDown = false, bool isUpateTextContentOnly = false);

    bool NotLoopOptions() const;

    void UpdateColumnChildPosition(double offsetY);

    bool CanMove(bool isDown) const;

    bool InnerHandleScroll(bool isDown, bool isUpatePropertiesOnly = false);

    void ScrollTimeColumn();

    void UpdateCurrentOffset(float offset);

    uint32_t GetCurrentIndex() const
    {
        return currentIndex_;
    }

    void SetCurrentIndex(uint32_t value)
    {
        currentIndex_ = value;
    }

    float GetCurrentOffset() const
    {
        return deltaSize_;
    }

    void SetCurrentOffset(float deltaSize)
    {
        deltaSize_ = deltaSize;
    }

    const std::map<RefPtr<FrameNode>, uint32_t>& GetOptions() const
    {
        return optionsTotalCount_;
    }

    void SetOptions(const std::map<RefPtr<FrameNode>, uint32_t>& value)
    {
        optionsTotalCount_ = value;
    }

    uint32_t GetShowCount() const
    {
        return showCount_;
    }

    void SetShowCount(const uint32_t showCount)
    {
        showCount_ = showCount;
        GetHost()->MarkModifyDone();
    }

    void HandleChangeCallback(bool isAdd, bool needNotify)
    {
        if (changeCallback_) {
            changeCallback_(GetHost(), isAdd, GetCurrentIndex(), needNotify);
        } else {
            LOGE("change callback is null.");
        }
    }

    const ColumnChangeCallback& GetChangeCallback() const
    {
        return changeCallback_;
    }

    void SetChangeCallback(ColumnChangeCallback&& value)
    {
        changeCallback_ = value;
    }

    void HandleEventCallback(bool refresh)
    {
        if (EventCallback_) {
            EventCallback_(refresh);
        } else {
            LOGE("event callback is null.");
        }
    }

    const EventCallback& GetEventCallback() const
    {
        return EventCallback_;
    }

    void SetEventCallback(EventCallback&& value)
    {
        EventCallback_ = value;
    }

    FocusPattern GetFocusPattern() const override
    {
        return { FocusType::NODE, true };
    }

    void SetHour24(bool value)
    {
        hour24_ = value;
    }

    bool GetHour24() const
    {
        return hour24_;
    }

    const RefPtr<TimePickerTossAnimationController>& GetToss() const
    {
        return tossAnimationController_;
    }
      
    void SetLocalDownDistance(float value)
    {
        localDownDistance_ = value;
    }

    float GetLocalDownDistance() const
    {
        return localDownDistance_;
    }

    void UpdateToss(double offsetY);

    void TossStoped();

    void UpdateScrollDelta(double delta);

private:
    void OnModifyDone() override;
    void OnAttachToFrameNode() override;
    bool OnDirtyLayoutWrapperSwap(const RefPtr<LayoutWrapper>& dirty, const DirtySwapConfig& config) override;
    void SetDividerHeight(uint32_t showOptionCount);
    void ChangeTextStyle(uint32_t index, uint32_t showOptionCount,
        const RefPtr<TextLayoutProperty>& textLayoutProperty,
        const RefPtr<TimePickerLayoutProperty>& timePickerLayoutProperty);
    void ChangeAmPmTextStyle(uint32_t index, uint32_t showOptionCount,
        const RefPtr<TextLayoutProperty>& textLayoutProperty,
        const RefPtr<TimePickerLayoutProperty>& timePickerLayoutProperty);

    void InitOnKeyEvent(const RefPtr<FocusHub>& focusHub);
    bool OnKeyEvent(const KeyEvent& event);
    bool HandleDirectionKey(KeyCode code);

    void InitPanEvent(const RefPtr<GestureEventHub>& gestureHub);
    void HandleDragStart(const GestureEvent& event);
    void HandleDragMove(const GestureEvent& event);
    void HandleDragEnd();
    void CreateAnimation();
    RefPtr<CurveAnimation<double>> CreateAnimation(double from, double to);
    void HandleCurveStopped();
    void ScrollOption(double delta, bool isJump = false);

    void OnTouchDown();
    void OnTouchUp();
    void InitMouseAndPressEvent();
    void HandleMouseEvent(bool isHover);
    void SetButtonBackgroundColor(const Color& pressColor);
    void PlayPressAnimation(const Color& pressColor);
    void PlayHoverAnimation(const Color& color);
    void UpdateDisappearTextProperties(const RefPtr<PickerTheme>& pickerTheme,
        const RefPtr<TextLayoutProperty>& textLayoutProperty,
        const RefPtr<TimePickerLayoutProperty>& timePickerLayoutProperty);
    void UpdateCandidateTextProperties(const RefPtr<PickerTheme>& pickerTheme,
        const RefPtr<TextLayoutProperty>& textLayoutProperty,
        const RefPtr<TimePickerLayoutProperty>& timePickerLayoutProperty);
    void UpdateSelectedTextProperties(const RefPtr<PickerTheme>& pickerTheme,
        const RefPtr<TextLayoutProperty>& textLayoutProperty,
        const RefPtr<TimePickerLayoutProperty>& timePickerLayoutProperty);
    void AddAnimationTextProperties(uint32_t currentIndex, const RefPtr<TextLayoutProperty>& textLayoutProperty);
    void UpdateTextPropertiesLinear(bool isDown, double scale);
    void TextPropertiesLinearAnimation(const RefPtr<TextLayoutProperty>& textLayoutProperty,
        uint32_t index, uint32_t showCount, bool isDown, double scale);
    void FlushAnimationTextProperties(bool isDown);
    Dimension LinearFontSize(const Dimension& startFontSize, const Dimension& endFontSize, double percent);
    void SetAccessibilityAction();

    float localDownDistance_ = 0.0f;
    Color pressColor_;
    Color hoverColor_;
    RefPtr<TouchEventImpl> touchListener_;
    RefPtr<InputEvent> mouseEvent_;
    bool hour24_ = !Localization::GetInstance()->IsAmPmHour();
    // column options number
    std::map<RefPtr<FrameNode>, uint32_t> optionsTotalCount_;
    ColumnChangeCallback changeCallback_;
    EventCallback EventCallback_;
    uint32_t currentIndex_ = 0;
    double yLast_ = 0.0;
    double yOffset_ = 0.0;
    double jumpInterval_;
    uint32_t showCount_ = 0;
    bool isVertical_ = true;
    float gradientHeight_;
    float dividerHeight_;
    float dividerSpacingWidth_;

    float deltaSize_ = 0.0f;
    RefPtr<PanEvent> panEvent_;
    bool pressed_ = false;
    bool hoverd_ = false;
    double scrollDelta_ = 0.0;
    bool animationCreated_ = false;
    RefPtr<Animator> toController_;
    RefPtr<Animator> fromController_;
    RefPtr<CurveAnimation<double>> fromBottomCurve_;
    RefPtr<CurveAnimation<double>> fromTopCurve_;
    RefPtr<TimePickerTossAnimationController> tossAnimationController_ =
        AceType::MakeRefPtr<TimePickerTossAnimationController>();
    std::vector<TextProperties> animationProperties_;
    bool isJump_ = false;

    ACE_DISALLOW_COPY_AND_MOVE(TimePickerColumnPattern);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_TIME_PICKER_TIME_PICKER_COLUMN_PATTERN_H
