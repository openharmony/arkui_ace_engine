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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_TIME_PICKER_TIME_PICKER_MODEL_NG_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_TIME_PICKER_TIME_PICKER_MODEL_NG_H

#include "core/components/common/layout/constants.h"
#include "core/components/picker/picker_base_component.h"
#include "core/components_ng/pattern/time_picker/timepicker_model.h"

namespace OHOS::Ace::NG {
using TimeChangeEvent = std::function<void(const BaseEventInfo* info)>;

class ACE_EXPORT TimePickerModelNG : public TimePickerModel {
public:
    void CreateTimePicker(RefPtr<PickerTheme> pickerTheme) override;
    void SetSelectedTime(const PickerTime& value) override;
    void SetOnChange(TimeChangeEvent&& onChange) override;
    void SetHour24(bool isUseMilitaryTime) override;
    void SetDisappearTextStyle(const RefPtr<PickerTheme>& theme, const PickerTextStyle& value) override;
    void SetNormalTextStyle(const RefPtr<PickerTheme>& theme, const PickerTextStyle& value) override;
    void SetSelectedTextStyle(const RefPtr<PickerTheme>& theme, const PickerTextStyle& value) override;
    void SetBackgroundColor(const Color& color) override;
    void SetChangeEvent(TimeChangeEvent&& onChange) override;

private:
    static RefPtr<FrameNode> CreateStackNode();
    static RefPtr<FrameNode> CreateButtonNode();
};

class ACE_EXPORT TimePickerDialogModelNG : public TimePickerDialogModel {
public:
    void SetTimePickerDialogShow(PickerDialogInfo& pickerDialog, NG::TimePickerSettingData& settingData,
        std::function<void()>&& onCancel, std::function<void(const std::string&)>&& onAccept,
        std::function<void(const std::string&)>&& onChange) override;
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_TIME_PICKER_TIME_PICKER_MODEL_NG_H
