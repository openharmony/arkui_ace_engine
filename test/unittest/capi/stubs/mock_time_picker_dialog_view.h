/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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
#ifndef CAPI_STUBS_MOCK_TIME_PICKER_DIALOG_H
#define CAPI_STUBS_MOCK_TIME_PICKER_DIALOG_H

#include "core/components/picker/picker_base_component.h"

namespace OHOS::Ace::NG {
class MockTimePickerDialogView {
public:
    static void SetData(const DialogProperties& dialogProperties,
        const TimePickerSettingData& settingData, const std::vector<ButtonInfo>& buttonInfos,
        std::map<std::string, PickerTime> pickerTime);
    static void SetCallbacks(std::map<std::string, NG::DialogEvent> dialogEvent,
        std::map<std::string, NG::DialogGestureEvent> dialogCancelEvent);
    static DialogProperties GetDialogProperties();
    static TimePickerSettingData GetSettingData();
    static std::vector<ButtonInfo> GetButtonInfos();
    static PickerTime GetPickerTime();
    static void FireAcceptEvent(const std::string& value);
    static void FireChangeEvent(const std::string& value);
    static void FireCancelEvent();
    static void FireWillAppear();
    static void FireDidAppear();
    static void FireWillDisappear();
    static void FireDidDisappear();
private:
    static DialogProperties dialogProperties_;
    static TimePickerSettingData settingData_;
    static std::vector<ButtonInfo> buttonInfos_;
    static PickerTime pickerTime_;
    static DialogEvent acceptEvent_;
    static DialogEvent changeEvent_;
    static DialogGestureEvent cancelEvent_;
};
} // namespace OHOS::Ace::NG
#endif // CAPI_STUBS_MOCK_TIME_PICKER_DIALOG_H
