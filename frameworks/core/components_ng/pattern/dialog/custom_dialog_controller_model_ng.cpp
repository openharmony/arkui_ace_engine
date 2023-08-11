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

#include "core/components_ng/pattern/dialog/custom_dialog_controller_model_ng.h"

#include "base/memory/ace_type.h"
#include "base/subwindow/subwindow_manager.h"
#include "base/thread/task_executor.h"
#include "core/common/container_scope.h"

namespace OHOS::Ace::NG {
void CustomDialogControllerModelNG::SetOpenDialog(DialogProperties& dialogProperties,
    std::vector<WeakPtr<AceType>>& dialogs, bool& pending, bool& isShown, std::function<void()>&& cancelTask,
    std::function<void()>&& buildFunc, RefPtr<AceType>& dialogComponent, RefPtr<AceType>& customDialog,
    std::list<DialogOperation>& dialogOperation)
{
    auto container = Container::Current();
    auto currentId = Container::CurrentId();
    CHECK_NULL_VOID(container);
    if (container->IsSubContainer()) {
        currentId = SubwindowManager::GetInstance()->GetParentContainerId(Container::CurrentId());
        container = AceEngine::Get().GetContainer(currentId);
    }
    ContainerScope scope(currentId);
    auto pipelineContext = container->GetPipelineContext();
    CHECK_NULL_VOID(pipelineContext);
    auto context = AceType::DynamicCast<NG::PipelineContext>(pipelineContext);
    CHECK_NULL_VOID(context);
    auto overlayManager = context->GetOverlayManager();
    CHECK_NULL_VOID(overlayManager);

    dialogProperties.onStatusChanged = [&isShown](bool isShownStatus) {
        if (!isShownStatus) {
            isShown = isShownStatus;
        }
    };

    auto executor = context->GetTaskExecutor();
    CHECK_NULL_VOID(executor);
    auto task = [currentId, dialogProperties, dialogs, func = std::move(buildFunc),
                    weakOverlayManager = AceType::WeakClaim(AceType::RawPtr(overlayManager))]() mutable {
        ContainerScope scope(currentId);
        WeakPtr<NG::FrameNode> dialog;
        if (dialogProperties.isShowInSubWindow) {
            dialog = SubwindowManager::GetInstance()->ShowDialogNG(dialogProperties, std::move(func));
        } else {
            auto overlayManager = weakOverlayManager.Upgrade();
            CHECK_NULL_VOID(overlayManager);
            dialog = overlayManager->ShowDialog(dialogProperties, std::move(func), false);
        }
        dialogs.emplace_back(dialog);
    };
    executor->PostTask(task, TaskExecutor::TaskType::UI);
}

void CustomDialogControllerModelNG::SetCloseDialog(DialogProperties& dialogProperties,
    std::vector<WeakPtr<AceType>>& dialogs, bool& pending, bool& isShown, std::function<void()>&& cancelTask,
    RefPtr<AceType>& dialogComponent, RefPtr<AceType>& customDialog, std::list<DialogOperation>& dialogOperation)
{
    RefPtr<NG::FrameNode> dialog;
    while (!dialogs.empty()) {
        dialog = AceType::DynamicCast<NG::FrameNode>(dialogs.back().Upgrade());
        if (dialog && !dialog->IsRemoving()) {
            // get the dialog not removed currently
            break;
        }
        dialogs.pop_back();
    }

    if (dialogs.empty()) {
        LOGW("dialogs are empty");
        return;
    }
    if (!dialog) {
        LOGW("dialog is null");
        return;
    }
    auto container = Container::Current();
    auto currentId = Container::CurrentId();
    CHECK_NULL_VOID(container);
    if (container->IsSubContainer() && !dialogProperties.isShowInSubWindow) {
        currentId = SubwindowManager::GetInstance()->GetParentContainerId(Container::CurrentId());
        container = AceEngine::Get().GetContainer(currentId);
    }
    ContainerScope scope(currentId);
    auto pipelineContext = container->GetPipelineContext();
    CHECK_NULL_VOID(pipelineContext);
    auto context = AceType::DynamicCast<NG::PipelineContext>(pipelineContext);
    CHECK_NULL_VOID(context);
    auto overlayManager = context->GetOverlayManager();
    CHECK_NULL_VOID(overlayManager);
    overlayManager->CloseDialog(dialog);
    dialogs.pop_back();
}
} // namespace OHOS::Ace::NG
