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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_DATE_PICKER_DATE_PICKER_MODEL_NG_VIEW_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_DATE_PICKER_DATE_PICKER_MODEL_NG_VIEW_H

#include "base/i18n/localization.h"
#include "base/utils/macros.h"
#include "core/components/common/layout/constants.h"
#include "core/components/picker/picker_base_component.h"
#include "core/components_ng/pattern/picker/datepicker_event_hub.h"
#include "core/components_ng/pattern/picker/datepicker_layout_property.h"
#include "core/components_ng/pattern/picker/picker_model.h"

namespace OHOS::Ace::NG {
class ACE_EXPORT DatePickerModelNG : public DatePickerModel {
public:
    void CreateDatePicker(RefPtr<PickerTheme> theme) override;
    void CreateTimePicker(RefPtr<PickerTheme> theme) override {};
    void SetStartDate(const PickerDate& value) override;
    void SetEndDate(const PickerDate& value) override;
    void SetSelectedDate(const PickerDate& value) override;
    void SetMode(const DatePickerMode& value) override;
    void SetShowLunar(bool lunar) override;
    void SetOnChange(DateChangeEvent&& onChange) override;
    void SetOnDateChange(DateChangeEvent&& onChange) override;
    void SetSelectedTime(const PickerTime& selectedTime) override {};
    void SetHour24(bool value) override {};
    void SetDisappearTextStyle(const RefPtr<PickerTheme>& theme, const PickerTextStyle& value) override;
    void SetNormalTextStyle(const RefPtr<PickerTheme>& theme, const PickerTextStyle& value) override;
    void SetSelectedTextStyle(const RefPtr<PickerTheme>& theme, const PickerTextStyle& value) override;
    void HasUserDefinedDisappearFontFamily(bool isUserDefined) override;
    void HasUserDefinedNormalFontFamily(bool isUserDefined) override;
    void HasUserDefinedSelectedFontFamily(bool isUserDefined) override;
    void SetBackgroundColor(const Color& color) override;
    void HasUserDefinedOpacity() override;
    void SetEnableHapticFeedback(bool isEnableHapticFeedback) override;
    void UpdateUserSetSelectColor() override;
    static void SetStartDate(FrameNode* frameNode, const PickerDate& value);
    static void SetEndDate(FrameNode* frameNode, const PickerDate& value);
    static void SetSelectedDate(FrameNode* frameNode, const PickerDate& value);
    static void SetMode(FrameNode* frameNode, const DatePickerMode& value);
    static void SetOnDateChange(FrameNode* frameNode, DateChangeEvent&& onChange);
    static void SetOnChange(FrameNode* frameNode, DateChangeEvent&& onChange);
    static RefPtr<FrameNode> CreateFrameNode(int32_t nodeId);
    void SetChangeEvent(DateChangeEvent&& onChange) override;
    void SetDigitalCrownSensitivity(int32_t crownSensitivity) override;
    static void SetSelectedTextStyle(
        FrameNode* frameNode, const RefPtr<PickerTheme>& theme, const PickerTextStyle& value);
    static void SetNormalTextStyle(
        FrameNode* frameNode, const RefPtr<PickerTheme>& theme, const PickerTextStyle& value);
    static void SetDisappearTextStyle(
        FrameNode* frameNode, const RefPtr<PickerTheme>& theme, const PickerTextStyle& value);
    static void SetShowLunar(FrameNode* frameNode, bool lunar);
    static void SetBackgroundColor(FrameNode* frameNode, const Color& color);
    static PickerTextStyle getSelectedTextStyle(FrameNode* frameNode);
    static PickerTextStyle getNormalTextStyle(FrameNode* frameNode);
    static PickerTextStyle getDisappearTextStyle(FrameNode* frameNode);
    static int32_t getLunar(FrameNode* frameNode);
    static LunarDate getStartDate(FrameNode* frameNode);
    static LunarDate getEndDate(FrameNode* frameNode);
    static LunarDate getSelectedDate(FrameNode* frameNode);
    static DatePickerMode getMode(FrameNode* frameNode);
    static uint32_t getBackgroundColor(FrameNode* frameNode);
    static void SetDefaultAttributes(RefPtr<FrameNode>& frameNode, const RefPtr<PickerTheme>& pickerTheme);
    static const Dimension ConvertFontScaleValue(const Dimension& fontSizeValue);
    static bool GetEnableHapticFeedback(FrameNode* frameNode);
    static void SetEnableHapticFeedback(FrameNode* frameNode, bool isEnableHapticFeedback);
    static void SetDigitalCrownSensitivity(FrameNode* frameNode, int32_t crownSensitivity);
private:
    static RefPtr<FrameNode> CreateStackNode();
    static RefPtr<FrameNode> CreateColumnNode();
    static RefPtr<FrameNode> CreateButtonNode();
    void createMonthOrDayColumnNode(const RefPtr<FrameNode>& columnNode,
        const RefPtr<FrameNode>& dateNode, Color buttonBackgroundColor);
    void createYearColumnNode(const RefPtr<FrameNode>& columnNode, const RefPtr<FrameNode>& dateNode);
    std::string dateOrder = "";
    std::string dateTimeOrder = "";
};

class ACE_FORCE_EXPORT DatePickerDialogModelNG : public DatePickerDialogModel {
public:
    void SetDatePickerDialogShow(PickerDialogInfo& pickerDialog, NG::DatePickerSettingData& settingData,
        std::function<void()>&& onCancel, std::function<void(const std::string&)>&& onAccept,
        std::function<void(const std::string&)>&& onChange, std::function<void(const std::string&)>&& onDateAccept,
        std::function<void(const std::string&)>&& onDateChange, DatePickerType pickerType,
        PickerDialogEvent& pickerDialogEvent, const std::vector<ButtonInfo>& buttonInfos) override;
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_DATE_PICKER_DATE_PICKER_MODEL_NG_VIEW_H
