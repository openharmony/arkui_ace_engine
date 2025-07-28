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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_DIALOG_CUSTOM_DIALOG_CONTROLLER_MODEL_NG_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_DIALOG_CUSTOM_DIALOG_CONTROLLER_MODEL_NG_H

#include "core/components_ng/pattern/dialog/custom_dialog_controller_model.h"
#include "core/pipeline_ng/pipeline_context.h"
#include "base/memory/ace_type.h"

namespace OHOS::Ace::NG {
class ACE_EXPORT CustomDialogControllerModelNG : public OHOS::Ace::CustomDialogControllerModel {
public:
    void SetOpenDialog(DialogProperties& dialogProperties, const WeakPtr<AceType>& controller,
        std::vector<WeakPtr<AceType>>& dialogs, bool& pending, bool& isShown, std::function<void()>&& cancelTask,
        std::function<void()>&& buildFunc, RefPtr<AceType>& dialogComponent, RefPtr<AceType>& customDialog,
        std::list<DialogOperation>& dialogOperation, bool& hasBind) override;
    static RefPtr<UINode> SetOpenDialogWithNode(DialogProperties& dialogProperties,
        const RefPtr<UINode>& customNode);
    void SetCloseDialog(DialogProperties& dialogProperties, const WeakPtr<AceType>& controller,
        std::vector<WeakPtr<AceType>>& dialogs, bool& pending, bool& isShown, std::function<void()>&& cancelTask,
        RefPtr<AceType>& dialogComponent, RefPtr<AceType>& customDialog,
        std::list<DialogOperation>& dialogOperation) override;
    static void SetCloseDialogForNDK(FrameNode* dialogNode);
    PromptActionCommonState GetState(std::vector<WeakPtr<AceType>>& dialogs, bool& hasBind) override;
    static PromptActionCommonState GetStateWithNode(FrameNode* dialogNode);

private:
    TaskExecutor::Task ParseOpenDialogTask(int32_t currentId, const WeakPtr<AceType>& controller,
        DialogProperties& dialogProperties, std::vector<WeakPtr<AceType>>& dialogs, std::function<void()>&& buildFunc,
        bool& hasBind, bool& isShown);
    static void SetOpenDialogInTask(const RefPtr<OverlayManager>& overlayManager, const RefPtr<Container>& container,
        const WeakPtr<AceType>& controller, RefPtr<NG::FrameNode>& dialog, DialogProperties& dialogProperties,
        std::function<void()>&& func, bool& isShown);
    TaskExecutor::Task ParseCloseDialogTask(const WeakPtr<AceType>& controller, DialogProperties& dialogProperties,
        std::vector<WeakPtr<AceType>>& dialogs, const RefPtr<OverlayManager>& overlayManager);
};
} // namespace OHOS::Ace::NG
#endif // FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_DIALOG_JS_CUSTOM_DIALOG_CONTROLLER_H
