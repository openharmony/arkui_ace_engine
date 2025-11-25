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

#include "mock_text_picker_dialog_view.h"

namespace OHOS::Ace::NG {
DialogProperties MockTextPickerDialogView::dialogProperties_;
TextPickerSettingData MockTextPickerDialogView::settingData_;
std::vector<ButtonInfo> MockTextPickerDialogView::buttonInfos_;
DialogTextEvent MockTextPickerDialogView::acceptEvent_;
DialogTextEvent MockTextPickerDialogView::changeEvent_;
DialogGestureEvent MockTextPickerDialogView::cancelEvent_;

void MockTextPickerDialogView::Show(const DialogProperties& dialogProperties,
    const TextPickerSettingData& settingData, const std::vector<ButtonInfo>& buttonInfos,
    std::map<std::string, NG::DialogTextEvent> dialogEvent,
    std::map<std::string, NG::DialogGestureEvent> dialogCancelEvent)
{
    dialogProperties_ = dialogProperties;
    settingData_ = settingData;
    buttonInfos_ = buttonInfos;
    acceptEvent_ = dialogEvent["acceptId"];
    changeEvent_ = dialogEvent["changeId"];
    cancelEvent_ = dialogCancelEvent["cancelId"];
}

DialogProperties MockTextPickerDialogView::GetDialogProperties()
{
    return dialogProperties_;
}

TextPickerSettingData MockTextPickerDialogView::GetSettingData()
{
    return settingData_;
}

std::vector<ButtonInfo> MockTextPickerDialogView::GetButtonInfos()
{
    return buttonInfos_;
}

void MockTextPickerDialogView::FireAcceptEvent(const std::string& value)
{
    if (acceptEvent_) {
        acceptEvent_(value);
    }
}
void MockTextPickerDialogView::FireChangeEvent(const std::string& value)
{
    if (changeEvent_) {
        changeEvent_(value);
    }
}

void MockTextPickerDialogView::FireCancelEvent()
{
    if (cancelEvent_) {
        cancelEvent_(GestureEvent());
    }
}

void MockTextPickerDialogView::FireWillAppear()
{
    dialogProperties_.onWillAppear();
}

void MockTextPickerDialogView::FireDidAppear()
{
    dialogProperties_.onDidAppear();
}

void MockTextPickerDialogView::FireWillDisappear()
{
    dialogProperties_.onWillDisappear();
}

void MockTextPickerDialogView::FireDidDisappear()
{
    dialogProperties_.onDidDisappear();
}
}