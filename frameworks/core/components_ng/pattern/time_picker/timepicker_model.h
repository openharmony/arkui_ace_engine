/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_TIME_PICKER_TIME_PICKER_MODEL_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_TIME_PICKER_TIME_PICKER_MODEL_H

#include <mutex>

#include "base/i18n/time_format.h"
#include "core/components/picker/picker_data.h"
#include "core/components/picker/picker_theme.h"
#include "core/components_ng/pattern/picker/picker_model.h"
#include "core/components_ng/pattern/picker/picker_type_define.h"

namespace OHOS::Ace {
using ChangeEvent = std::function<void(const BaseEventInfo* info)>;
struct TimePickerDialogEvent {
    std::function<void()> onDidAppear;
    std::function<void()> onDidDisappear;
    std::function<void()> onWillAppear;
    std::function<void()> onWillDisappear;
};
class TimePickerModel {
public:
    static TimePickerModel* GetInstance();
    virtual ~TimePickerModel() = default;

    virtual void CreateTimePicker(RefPtr<PickerTheme> pickerTheme, bool hasSecond = false) = 0;
    virtual void SetStartTime(const PickerTime& value) = 0;
    virtual void SetEndTime(const PickerTime& value) = 0;
    virtual void SetSelectedTime(const PickerTime& value) = 0;
    virtual void SetOnChange(ChangeEvent&& onChange) = 0;
    virtual void SetOnEnterSelectedArea(ChangeEvent&& onEnterSelectedArea) = 0;
    virtual void SetHour24(bool isUseMilitaryTime) = 0;
    virtual void SetIsEnableHapticFeedback(bool isEnableHapticFeedback) {};
    virtual void SetDateTimeOptions(ZeroPrefixType& hourType,
        ZeroPrefixType& minuteType, ZeroPrefixType& secondType) {};
    virtual void SetWheelModeEnabled(bool wheelModeEnabled) = 0;
    virtual void SetDisappearTextStyle(const RefPtr<PickerTheme>& theme, const NG::PickerTextStyle& value) = 0;
    virtual void SetNormalTextStyle(const RefPtr<PickerTheme>& theme, const NG::PickerTextStyle& value) = 0;
    virtual void SetSelectedTextStyle(const RefPtr<PickerTheme>& theme, const NG::PickerTextStyle& value) = 0;
    virtual void HasUserDefinedDisappearFontFamily(bool isUserDefined) = 0;
    virtual void HasUserDefinedNormalFontFamily(bool isUserDefined) = 0;
    virtual void HasUserDefinedSelectedFontFamily(bool isUserDefined) = 0;
    virtual void SetBackgroundColor(const Color& color) = 0;
    virtual void SetChangeEvent(ChangeEvent&& onChange) = 0;
    virtual void HasUserDefinedOpacity() = 0;
    virtual void SetEnableCascade(bool isEnableCascade) = 0;

private:
    static std::unique_ptr<TimePickerModel> timePickerInstance_;
    static std::once_flag onceFlag_;
};

class TimePickerDialogModel {
public:
    static TimePickerDialogModel* GetInstance();
    virtual ~TimePickerDialogModel() = default;

    virtual void SetTimePickerDialogShow(PickerDialogInfo& pickerDialog, NG::TimePickerSettingData& settingData,
        std::function<void()>&& onCancel, std::function<void(const std::string&)>&& onAccept,
        std::function<void(const std::string&)>&& onChange,
        std::function<void(const std::string&)>&& onEnterSelectedArea, TimePickerDialogEvent& timePickerDialogEvent,
        const std::vector<ButtonInfo>& buttonInfos) = 0;

private:
    static std::unique_ptr<TimePickerDialogModel> timePickerDialogInstance_;
    static std::once_flag onceFlag_;
};
} // namespace OHOS::Ace
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_TIME_PICKER_TIME_PICKER_MODEL_H
