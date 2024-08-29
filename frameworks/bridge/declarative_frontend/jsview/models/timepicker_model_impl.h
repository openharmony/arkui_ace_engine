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

#ifndef FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_MODELS_TIMEPICKER_MODEL_IMPL_H
#define FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_MODELS_TIMEPICKER_MODEL_IMPL_H

#include "core/components_ng/pattern/time_picker/timepicker_model.h"

namespace OHOS::Ace::Framework {
class TimePickerModelImpl : public TimePickerModel {
public:
    TimePickerModelImpl() = default;
    ~TimePickerModelImpl() override = default;

    void CreateTimePicker(RefPtr<PickerTheme> pickerTheme, bool hasSecond = false) override;
    void SetSelectedTime(const PickerTime& value) override;
    void SetOnChange(ChangeEvent&& onChange) override;
    void SetHour24(bool isUseMilitaryTime) override;
    void SetWheelModeEnabled(bool wheelModeEnabled) override {};
    void SetDisappearTextStyle(const RefPtr<PickerTheme>& theme, const NG::PickerTextStyle& value) override {};
    void SetNormalTextStyle(const RefPtr<PickerTheme>& theme, const NG::PickerTextStyle& value) override {};
    void SetSelectedTextStyle(const RefPtr<PickerTheme>& theme, const NG::PickerTextStyle& value) override {};
    void HasUserDefinedDisappearFontFamily(bool isUserDefined) override {};
    void HasUserDefinedNormalFontFamily(bool isUserDefined) override {};
    void HasUserDefinedSelectedFontFamily(bool isUserDefined) override {};
    void SetBackgroundColor(const Color& color) override;
    void SetChangeEvent(ChangeEvent&& onChange) override {};
    void HasUserDefinedOpacity() override {};
};

class TimePickerDialogModelImpl : public TimePickerDialogModel {
public:
    TimePickerDialogModelImpl() = default;
    ~TimePickerDialogModelImpl() override = default;

    void SetTimePickerDialogShow(PickerDialogInfo& pickerDialog, NG::TimePickerSettingData& settingData,
        std::function<void()>&& onCancel, std::function<void(const std::string&)>&& onAccept,
        std::function<void(const std::string&)>&& onChange, TimePickerDialogEvent& timePickerDialogEvent,
        const std::vector<ButtonInfo>& buttonInfos) override;
};
} // namespace OHOS::Ace::Framework
#endif // FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_MODELS_TIMEPICKER_MODEL_IMPL_H
