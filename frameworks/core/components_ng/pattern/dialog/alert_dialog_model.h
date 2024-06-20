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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_DIALOG_DIALOG_MODEL_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_DIALOG_DIALOG_MODEL_H

#include <mutex>

#include "core/components_ng/pattern/dialog/dialog_event_hub.h"

namespace OHOS::Ace {
class ACE_FORCE_EXPORT AlertDialogModel {
public:
    static AlertDialogModel* GetInstance();
    virtual ~AlertDialogModel() = default;
    virtual void SetParseButtonObj(std::function<void()>&& eventFuncImpl, ButtonInfo& buttonInfo, DialogProperties& arg,
        const std::string& property) = 0;
    virtual void SetOnCancel(std::function<void()>&& eventFunc, DialogProperties& arg) = 0;
    virtual void SetShowDialog(const DialogProperties& arg) = 0;
    virtual void SetOnWillDismiss(std::function<void(const int32_t& info)>&& onWillDismissFunc,
        DialogProperties& arg) {};

private:
    static std::unique_ptr<AlertDialogModel> instance_;
    static std::mutex mutex_;
};
} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_DIALOG_DIALOG_MODEL_H
