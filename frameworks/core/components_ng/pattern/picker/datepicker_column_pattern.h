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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_DATE_PICKER_DATE_PICKER_COLUMN_PATTERN_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_DATE_PICKER_DATE_PICKER_COLUMN_PATTERN_H

#include <cstdint>
#include <utility>

#include "adapter/ohos/entrance/picker/picker_haptic_factory.h"
#include "base/i18n/localization.h"
#include "core/components/picker/picker_theme.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/linear_layout/linear_layout_pattern.h"
#include "core/components_ng/pattern/picker/datepicker_column_accessibility_property.h"
#include "core/components_ng/pattern/picker/datepicker_column_layout_algorithm.h"
#include "core/components_ng/pattern/picker/datepicker_event_hub.h"
#include "core/components_ng/pattern/picker/datepicker_layout_property.h"
#include "core/components_ng/pattern/picker/datepicker_paint_method.h"
#include "core/components_ng/pattern/picker/datepicker_row_layout_property.h"
#include "core/components_ng/pattern/picker_utils/picker_column_pattern.h"
#include "core/components_ng/pattern/picker_utils/picker_column_pattern_utils.h"
#include "core/components_ng/pattern/picker_utils/toss_animation_controller.h"
#include "core/components_ng/pattern/text/text_layout_property.h"
#include "core/pipeline_ng/ui_task_scheduler.h"

namespace OHOS::Ace::NG {

class DatePickerColumnPattern : public PickerColumnPattern {
    DECLARE_ACE_TYPE(DatePickerColumnPattern, PickerColumnPattern);

public:
    DatePickerColumnPattern() : PickerColumnPattern(true) {};
    virtual ~DatePickerColumnPattern() = default;

    RefPtr<LayoutAlgorithm> CreateLayoutAlgorithm() override
    {
        auto layoutAlgorithm = MakeRefPtr<DatePickerColumnLayoutAlgorithm>();
        if (algorithmOffset_.size() == 0) {
            ResetAlgorithmOffset();
        }
        layoutAlgorithm->SetCurrentOffset(algorithmOffset_);
        return layoutAlgorithm;
    }

    RefPtr<LayoutProperty> CreateLayoutProperty() override
    {
        return MakeRefPtr<DataPickerLayoutProperty>();
    }

    RefPtr<AccessibilityProperty> CreateAccessibilityProperty() override
    {
        return MakeRefPtr<DatePickerColumnAccessibilityProperty>();
    }

    void FlushCurrentOptions(
        bool isDown = false, bool isUpateTextContentOnly = false, bool isUpdateAnimationProperties = false) override;

    void UpdateColumnChildPosition(double offsetY) override;
    bool CanMove(bool isDown) const override;

    const std::map<WeakPtr<FrameNode>, std::vector<PickerDateF>>& GetOptions() const
    {
        return options_;
    }

    void SetOptions(const std::map<WeakPtr<FrameNode>, std::vector<PickerDateF>>& value)
    {
        options_ = value;
    }

    void SetShowCount(const uint32_t showCount)
    {
        showCount_ = showCount;
    }

    const Color& GetButtonBgColor() const override
    {
        return buttonBgColor_;
    }

    const Color& GetButtonPressColor() const override
    {
        return pressColor_;
    }

    void UpdateColumnButtonFocusState(bool haveFocus, bool needMarkDirty);
    void InitHapticController(const RefPtr<FrameNode>& host) override;

private:
    void OnModifyDone() override;
    void SetDividerHeight(uint32_t showOptionCount);
    void InitSelectorButtonProperties(const RefPtr<PickerTheme>& pickerTheme);
    void UpdateSelectorButtonProps(bool haveFocus, bool needMarkDirty);
    const Color& GetButtonHoverColor() const override;
    void UpdateTextAreaPadding(const RefPtr<PickerTheme>& pickerTheme,
        const RefPtr<TextLayoutProperty>& textLayoutProperty);
    int32_t CalcScrollIndex(int32_t totalOptionCount, int32_t currentIndex, bool canLoop, int32_t step);
    void UpdateSelectedTextColor(const RefPtr<PickerTheme>& pickerTheme) override;
    void UpdateAnimationColor(const RefPtr<PickerTheme>& pickerTheme);
    void UpdatePickerTextProperties(uint32_t index, uint32_t showOptionCount,
        const RefPtr<TextLayoutProperty>& textLayoutProperty,
        const RefPtr<DataPickerRowLayoutProperty>& dataPickerRowLayoutProperty);
    void UpdateDisappearTextProperties(const RefPtr<PickerTheme>& pickerTheme,
        const RefPtr<TextLayoutProperty>& textLayoutProperty,
        const RefPtr<DataPickerRowLayoutProperty>& timePickerLayoutProperty);
    void UpdateCandidateTextProperties(const RefPtr<PickerTheme>& pickerTheme,
        const RefPtr<TextLayoutProperty>& textLayoutProperty,
        const RefPtr<DataPickerRowLayoutProperty>& timePickerLayoutProperty);
    void UpdateSelectedTextProperties(const RefPtr<PickerTheme>& pickerTheme,
        const RefPtr<TextLayoutProperty>& textLayoutProperty,
        const RefPtr<DataPickerRowLayoutProperty>& timePickerLayoutProperty);
    void TextPropertiesLinearAnimation(const RefPtr<TextLayoutProperty>& textLayoutProperty, uint32_t index,
        uint32_t showCount, bool isDown, double scale) override;
    void InitTextFontFamily() override;
    uint32_t GetOptionCount() const override;
    bool GetOptionItemCount(uint32_t& itemCounts) override;
    bool IsLanscape(uint32_t itemCount) override;

    std::map<WeakPtr<FrameNode>, std::vector<PickerDateF>> options_;
    int32_t currentChildIndex_ = 0;
    float gradientHeight_ = 0.0f;
    float dividerHeight_ = 0.0f;
    float dividerSpacingWidth_ = 0.0f;
    float dividerSpacing_ = 0.0f;
    FontWeight SelectedWeight_ = FontWeight::MEDIUM;
    FontWeight CandidateWeight_ = FontWeight::REGULAR;
    Color pressColor_;
    Color hoverColor_;
    Color buttonBgColor_ = Color::TRANSPARENT;
    Color buttonDefaultBgColor_ = Color::TRANSPARENT;
    Color buttonFocusBgColor_ = Color::TRANSPARENT;
    Color buttonDefaultBorderColor_ = Color::TRANSPARENT;
    Color buttonFocusBorderColor_ = Color::TRANSPARENT;
    Color selectorTextFocusColor_ = Color::WHITE;
    Dimension buttonDefaultBorderWidth_ = 0.0_vp;
    Dimension buttonFocusBorderWidth_ = 0.0_vp;
    bool isFirstTimeUpdateButtonProps_ = true;
    bool hasAppCustomFont_ = false;
    bool hasUserDefinedDisappearFontFamily_ = false;
    bool hasUserDefinedNormalFontFamily_ = false;
    bool hasUserDefinedSelectedFontFamily_ = false;
    ACE_DISALLOW_COPY_AND_MOVE(DatePickerColumnPattern);
    friend class PickerColumnPatternCircleUtils<DatePickerColumnPattern>;
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_DATE_PICKER_DATE_PICKER_COLUMN_PATTERN_H
