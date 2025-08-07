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

#include "adapter/ohos/entrance/picker/picker_haptic_interface.h"
#include "base/i18n/localization.h"
#include "core/components/common/properties/color.h"
#include "core/components/picker/picker_base_component.h"
#include "core/components/picker/picker_date_component.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/linear_layout/linear_layout_pattern.h"
#include "core/components_ng/pattern/picker_utils/picker_column_pattern.h"
#include "core/components_ng/pattern/picker_utils/picker_column_pattern_utils.h"
#include "core/components_ng/pattern/picker_utils/toss_animation_controller.h"
#include "core/components_ng/pattern/text/text_layout_property.h"
#include "core/components_ng/pattern/time_picker/timepicker_column_accessibility_property.h"
#include "core/components_ng/pattern/time_picker/timepicker_column_layout_algorithm.h"
#include "core/components_ng/pattern/time_picker/timepicker_layout_property.h"

namespace OHOS::Ace::NG {

class TimePickerColumnPattern : public PickerColumnPattern {
    DECLARE_ACE_TYPE(TimePickerColumnPattern, PickerColumnPattern);

public:
    TimePickerColumnPattern() : PickerColumnPattern() {}
    virtual ~TimePickerColumnPattern() = default;

    RefPtr<LayoutAlgorithm> CreateLayoutAlgorithm() override
    {
        auto layoutAlgorithm = MakeRefPtr<TimePickerColumnLayoutAlgorithm>();
        if (algorithmOffset_.size() == 0) {
            ResetAlgorithmOffset();
        }
        layoutAlgorithm->SetCurrentOffset(algorithmOffset_);
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

    void FlushCurrentOptions(bool isDown = false, bool isUpateTextContentOnly = false,
        bool isUpdateAnimationProperties = false, bool isTossPlaying = false) override;
    void UpdateColumnChildPosition(double offsetY) override;
    bool CanMove(bool isDown) const override;
    void ScrollTimeColumn();
    void UpdateCurrentOffset(float offset);

    const std::map<WeakPtr<FrameNode>, uint32_t>& GetOptions() const
    {
        return optionsTotalCount_;
    }

    void SetOptions(const std::map<WeakPtr<FrameNode>, uint32_t>& value)
    {
        optionsTotalCount_ = value;
    }

    uint32_t GetOptionCount() const override;

    void SetShowCount(const uint32_t showCount)
    {
        showCount_ = showCount;
        GetHost()->MarkModifyDone();
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

    void UpdateScrollDelta(double delta);

    void InitHapticController(const RefPtr<FrameNode>& host) override;
    bool IsStartEndTimeDefined();
    bool IsTossNeedToStop() override;

    uint32_t GetEnterIndex() const
    {
        return currentEnterIndex_;
    }

    void SetEnterIndex(uint32_t value)
    {
        if (value != currentEnterIndex_) {
            currentEnterIndex_ = value;
        }
    }

    void HandleEnterSelectedAreaEventCallback(bool refresh)
    {
        if (enterSelectedAreaEventCallback_) {
            enterSelectedAreaEventCallback_(refresh);
        }
    }

    const EventCallback& GetEnterSelectedAreaEventCallback() const
    {
        return enterSelectedAreaEventCallback_;
    }

    void SetEnterSelectedAreaEventCallback(EventCallback&& value)
    {
        enterSelectedAreaEventCallback_ = value;
    }

    const Color& GetButtonHoverColor() const override
    {
        return hoverColor_;
    }

    const Color& GetButtonBgColor() const override
    {
        return buttonBgColor_;
    }

    const Color& GetButtonPressColor() const override
    {
        return pressColor_;
    }

    std::string GetCurrentOption() const override;

    bool GetCanLoopFromLayoutProperty() const override;

private:
    void OnModifyDone() override;
    void SetDividerHeight(uint32_t showOptionCount);
    void ChangeTextStyle(uint32_t index, uint32_t showOptionCount, const RefPtr<TextLayoutProperty>& textLayoutProperty,
        const RefPtr<TimePickerLayoutProperty>& timePickerLayoutProperty);
    void ChangeAmPmTextStyle(uint32_t index, uint32_t showOptionCount,
        const RefPtr<TextLayoutProperty>& textLayoutProperty,
        const RefPtr<TimePickerLayoutProperty>& timePickerLayoutProperty);

    void InitOnKeyEvent(const RefPtr<FocusHub>& focusHub);
    bool OnKeyEvent(const KeyEvent& event);
    bool HandleDirectionKey(KeyCode code);
    void UpdateSelectedTextColor(const RefPtr<PickerTheme>& pickerTheme) override;
    void GetAnimationColor(uint32_t index, uint32_t showCount, Color& color, bool selectedMark = false);
    void UpdateAnimationColor(const RefPtr<PickerTheme>& pickerTheme);
#ifdef SUPPORT_DIGITAL_CROWN
    void HandleCrownMoveEvent(const CrownEvent& event);
#endif
    void TextPropertiesLinearAnimation(const RefPtr<TextLayoutProperty>& textLayoutProperty, uint32_t index,
        uint32_t showCount, bool isDown, double scale) override;
    void InitTextFontFamily() override;
    void HandleEnterSelectedArea(double scrollDelta, float shiftDistance, PickerScrollDirection dir) override;

    Color pressColor_;
    Color hoverColor_;
    Color buttonBgColor_ = Color::TRANSPARENT;
    bool hour24_ = SystemProperties::Is24HourClock();
    // column options number
    std::map<WeakPtr<FrameNode>, uint32_t> optionsTotalCount_;
    EventCallback enterSelectedAreaEventCallback_;
    uint32_t currentEnterIndex_ = 0;
    bool isVertical_ = true;
    float gradientHeight_ = 0.0f;
    float dividerHeight_ = 0.0f;
    float dividerSpacingWidth_ = 0.0f;
    double enterDelta_ = 0.0;
    float dividerSpacing_ = 0.0f;
    bool hasAppCustomFont_ = false;
    bool hasUserDefinedDisappearFontFamily_ = false;
    bool hasUserDefinedNormalFontFamily_ = false;
    bool hasUserDefinedSelectedFontFamily_ = false;
    bool isTossReadyToStop_ = false;
    ACE_DISALLOW_COPY_AND_MOVE(TimePickerColumnPattern);
    friend class PickerColumnPatternCircleUtils<TimePickerColumnPattern>;
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_TIME_PICKER_TIME_PICKER_COLUMN_PATTERN_H
