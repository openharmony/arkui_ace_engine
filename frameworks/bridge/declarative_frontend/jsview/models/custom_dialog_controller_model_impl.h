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

#ifndef FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_MODELS_DIALOG_CUSTOM_DIALOG_CONTROLLER_MODEL_IMPL_H
#define FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_MODELS_DIALOG_CUSTOM_DIALOG_CONTROLLER_MODEL_IMPL_H

#include "core/components_ng/pattern/dialog/custom_dialog_controller_model.h"

namespace OHOS::Ace::Framework {
class CustomDialogControllerModelImpl : public OHOS::Ace::CustomDialogControllerModel {
public:
    void SetOpenDialog(DialogProperties& dialogProperties, const WeakPtr<AceType>& controller,
        std::vector<WeakPtr<AceType>>& dialogs, bool& pending, bool& isShown, std::function<void()>&& cancelTask,
        std::function<void()>&& buildFunc, RefPtr<AceType>& dialogComponent, RefPtr<AceType>& customDialog,
        std::list<DialogOperation>& dialogOperation) override;
    void SetCloseDialog(DialogProperties& dialogProperties, const WeakPtr<AceType>& controller,
        std::vector<WeakPtr<AceType>>& dialogs, bool& pending, bool& isShown, std::function<void()>&& cancelTask,
        RefPtr<AceType>& dialogComponent, RefPtr<AceType>& customDialog,
        std::list<DialogOperation>& dialogOperation) override;

private:
    void ShowDialog(DialogProperties& dialogProperties, bool& pending, bool& isShown,
        std::function<void()>&& cancelTask, RefPtr<AceType>& dialogComponent, RefPtr<AceType>& customDialog,
        std::list<DialogOperation>& dialogOperation);
    void CloseDialog(DialogProperties& dialogProperties, bool& pending, bool& isShown,
        std::function<void()>&& cancelTask, RefPtr<AceType>& dialogComponent, RefPtr<AceType>& customDialog,
        std::list<DialogOperation>& dialogOperation);
    void NotifyDialogOperation(DialogOperation operation, DialogProperties& dialogProperties, bool& pending,
        bool& isShown, std::function<void()>&& cancelTask, RefPtr<AceType>& dialogComponent,
        RefPtr<AceType>& customDialog, std::list<DialogOperation>& dialogOperation);
};
} // namespace OHOS::Ace::Framework
#endif // FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_MODELS_DIALOG_CUSTOM_DIALOG_CONTROLLER_MODEL_IMPL_H
