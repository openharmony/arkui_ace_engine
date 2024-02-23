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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_ACTION_SHEET_ACTION_SHEET_MODEL_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_ACTION_SHEET_ACTION_SHEET_MODEL_H

#include <mutex>

#include "core/common/container.h"
#include "core/components/dialog/dialog_properties.h"

namespace OHOS::Ace {
class ActionSheetModel {
public:
    static ActionSheetModel* GetInstance();
    virtual ~ActionSheetModel() = default;

    virtual void ShowActionSheet(const DialogProperties& arg) = 0;
    virtual void SetAction(GestureEventFunc&& eventFunc, ActionSheetInfo& sheetInfo) = 0;
    virtual void SetCancel(std::function<void()>&& eventFunc, DialogProperties& arg) = 0;
    virtual void SetConfirm(GestureEventFunc&& gestureEvent, std::function<void()>&& eventFunc,
        ButtonInfo& buttonInfo, DialogProperties& arg) = 0;
    virtual void SetOnWillDismiss(std::function<void(const int32_t& info)>&& onWillDismissFunc,
        DialogProperties& arg) {};

private:
    static std::unique_ptr<ActionSheetModel> instance_;
    static std::mutex mutex_;
};
} // namespace OHOS::Ace
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_ACTION_SHEET_ACTION_SHEET_MODEL_H
