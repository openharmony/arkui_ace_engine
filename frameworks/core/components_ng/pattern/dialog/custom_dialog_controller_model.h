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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_DIALOG_CUSTOM_DIALOG_CONTROLLER_MODEL_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_DIALOG_CUSTOM_DIALOG_CONTROLLER_MODEL_H

#include <mutex>

#include "core/components/dialog/dialog_component.h"

namespace OHOS::Ace {
enum class DialogOperation {
    DIALOG_OPEN = 0,
    DIALOG_CLOSE,
};

class CustomDialogControllerModel {
public:
    static CustomDialogControllerModel* GetInstance();
    virtual ~CustomDialogControllerModel() = default;

    virtual RefPtr<AceType> SetOpenDialog()
    {
        return nullptr;
    };
    virtual void SetOpenDialog(DialogProperties& dialogProperties, std::vector<WeakPtr<AceType>>& dialogs,
        std::function<void(RefPtr<AceType>&)>&& task, bool& pending, RefPtr<AceType>& overlayManager,
        std::function<void()>&& cancelTask) = 0;
    virtual void SetCloseDialog(DialogProperties& dialogProperties, std::vector<WeakPtr<AceType>>& dialogs,
        bool& pending, std::function<void()>&& task, RefPtr<AceType>& dialogComponent) = 0;
    virtual void setOnCancel(std::function<void()>&& event, std::function<void()>&& onCancel) {};
private:
    static std::unique_ptr<CustomDialogControllerModel> instance_;
    static std::mutex mutex_;
};
} // namespace OHOS::Ace
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_DIALOG_CUSTOM_DIALOG_CONTROLLER_MODEL_NG_H