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

#include "mock_time_picker_dialog_view.h"

namespace OHOS::Ace::NG {
DialogProperties MockTimePickerDialogView::dialogProperties_;
TimePickerSettingData MockTimePickerDialogView::settingData_;
std::vector<ButtonInfo> MockTimePickerDialogView::buttonInfos_;
PickerTime MockTimePickerDialogView::pickerTime_;
DialogEvent MockTimePickerDialogView::acceptEvent_;
DialogEvent MockTimePickerDialogView::changeEvent_;
DialogGestureEvent MockTimePickerDialogView::cancelEvent_;

void MockTimePickerDialogView::SetData(const DialogProperties& dialogProperties,
    const TimePickerSettingData& settingData, const std::vector<ButtonInfo>& buttonInfos,
    std::map<std::string, PickerTime> pickerTime)
{
    dialogProperties_ = dialogProperties;
    settingData_ = settingData;
    buttonInfos_ = buttonInfos;
    pickerTime_ = pickerTime["selected"];
}

void MockTimePickerDialogView::SetCallbacks(std::map<std::string, NG::DialogEvent> dialogEvent,
    std::map<std::string, NG::DialogGestureEvent> dialogCancelEvent)
{
    acceptEvent_ = dialogEvent["acceptId"];
    changeEvent_ = dialogEvent["changeId"];
    cancelEvent_ = dialogCancelEvent["cancelId"];
}

DialogProperties MockTimePickerDialogView::GetDialogProperties()
{
    return dialogProperties_;
}

TimePickerSettingData MockTimePickerDialogView::GetSettingData()
{
    return settingData_;
}

std::vector<ButtonInfo> MockTimePickerDialogView::GetButtonInfos()
{
    return buttonInfos_;
}

PickerTime MockTimePickerDialogView::GetPickerTime()
{
    return pickerTime_;
}

void MockTimePickerDialogView::FireAcceptEvent(const std::string& value)
{
    if (acceptEvent_) {
        acceptEvent_(value);
    }
}
void MockTimePickerDialogView::FireChangeEvent(const std::string& value)
{
    if (changeEvent_) {
        changeEvent_(value);
    }
}

void MockTimePickerDialogView::FireCancelEvent()
{
    if (cancelEvent_) {
        cancelEvent_(GestureEvent());
    }
}

void MockTimePickerDialogView::FireWillAppear()
{
    dialogProperties_.onWillAppear();
}

void MockTimePickerDialogView::FireDidAppear()
{
    dialogProperties_.onDidAppear();
}

void MockTimePickerDialogView::FireWillDisappear()
{
    dialogProperties_.onWillDisappear();
}

void MockTimePickerDialogView::FireDidDisappear()
{
    dialogProperties_.onDidDisappear();
}
}