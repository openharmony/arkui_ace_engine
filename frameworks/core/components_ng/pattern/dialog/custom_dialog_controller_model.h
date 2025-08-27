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

#include "core/common/ace_engine.h"
#include "core/common/container.h"
namespace OHOS::Ace {
struct DialogProperties;
enum class DialogOperation {
    DIALOG_OPEN = 0,
    DIALOG_CLOSE,
};

class ACE_FORCE_EXPORT CustomDialogControllerModel {
public:
    static CustomDialogControllerModel* GetInstance();
    virtual ~CustomDialogControllerModel() = default;

    virtual void SetOpenDialog(DialogProperties& dialogProperties, const WeakPtr<AceType>& controller,
        std::vector<WeakPtr<AceType>>& dialogs, bool& pending, bool& isShown, std::function<void()>&& cancelTask,
        std::function<void()>&& buildFunc, RefPtr<AceType>& dialogComponent, RefPtr<AceType>& customDialog,
        std::list<DialogOperation>& dialogOperation, bool& hasBind) = 0;
    virtual void SetCloseDialog(DialogProperties& dialogProperties, const WeakPtr<AceType>& controller,
        std::vector<WeakPtr<AceType>>& dialogs, bool& pending, bool& isShown, std::function<void()>&& cancelTask,
        RefPtr<AceType>& dialogComponent, RefPtr<AceType>& customDialog,
        std::list<DialogOperation>& dialogOperation) = 0;

    virtual PromptActionCommonState GetState(std::vector<WeakPtr<AceType>>& dialogs, bool& hasBind) = 0;
private:
    static std::unique_ptr<CustomDialogControllerModel> instance_;
    static std::mutex mutex_;
};
} // namespace OHOS::Ace
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_DIALOG_CUSTOM_DIALOG_CONTROLLER_MODEL_NG_H
