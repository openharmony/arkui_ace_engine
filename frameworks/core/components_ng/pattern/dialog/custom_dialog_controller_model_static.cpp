/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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
#include "core/components_ng/pattern/dialog/custom_dialog_controller_model_static.h"
#include "core/components_ng/pattern/dialog/dialog_pattern.h"
#include "core/components_ng/pattern/overlay/dialog_manager.h"

namespace OHOS::Ace::NG {
TaskExecutor::Task CustomDialogControllerModelStatic::ParseOpenDialogTask(int32_t currentId,
    const WeakPtr<AceType>& controller, DialogProperties& dialogProperties, std::vector<WeakPtr<AceType>>& dialogs,
    std::function<void()>&& buildFunc, const RefPtr<OverlayManager>& overlayManager)
{
    auto task = [currentId, controller, &dialogProperties, &dialogs, func = std::move(buildFunc),
                    weakOverlayManager = AceType::WeakClaim(AceType::RawPtr(overlayManager))]() mutable {
        ContainerScope scope(currentId);
        RefPtr<NG::FrameNode> dialog;
        auto overlayManager = weakOverlayManager.Upgrade();
        if (!overlayManager) {
            TAG_LOGE(AceLogTag::ACE_DIALOG, "OverlayManager is null.");
            return;
        }
        auto controllerPtr = controller.Upgrade();
        if (!controllerPtr) {
            TAG_LOGE(AceLogTag::ACE_DIALOG, "CustomDialogController is null.");
            return;
        }
        auto container = Container::Current();
        if (!container) {
            TAG_LOGE(AceLogTag::ACE_DIALOG, "Current container is null.");
            return;
        }
        if (dialogProperties.isShowInSubWindow) {
            dialog = SubwindowManager::GetInstance()->ShowDialogNG(dialogProperties, std::move(func));
            CHECK_NULL_VOID(dialog);
            if (dialogProperties.isModal && !dialogProperties.isSceneBoardDialog &&
                !container->IsUIExtensionWindow()) {
                auto mask = overlayManager->SetDialogMask(dialogProperties);
                if (!mask) {
                    TAG_LOGW(AceLogTag::ACE_DIALOG, "fail to set mask dialog.");
                    return;
                }
                overlayManager->SetMaskNodeId(dialog->GetId(), mask->GetId());
            }
        } else {
            dialog = overlayManager->ShowDialog(dialogProperties, std::move(func), false);
        }
        if (!dialog) {
            TAG_LOGE(AceLogTag::ACE_DIALOG, "fail to show dialog.");
            return;
        }
        TAG_LOGI(AceLogTag::ACE_DIALOG, "Controller/%{public}d create dialog node/%{public}d successfully.",
            dialogProperties.controllerId.value_or(-1), dialog->GetId());
        dialogs.emplace_back(dialog);
    };
    return task;
}

TaskExecutor::Task CustomDialogControllerModelStatic::ParseCloseDialogTask(const WeakPtr<AceType>& controller,
    DialogProperties& dialogProperties, std::vector<WeakPtr<AceType>>& dialogs,
    const RefPtr<OverlayManager>& overlayManager)
{
    auto task = [controller, &dialogs, &dialogProperties,
                    weakOverlayManager = AceType::WeakClaim(AceType::RawPtr(overlayManager))]() {
        auto overlayManager = weakOverlayManager.Upgrade();
        if (!overlayManager) {
            TAG_LOGE(AceLogTag::ACE_DIALOG, "OverlayManager is null.");
            return;
        }
        auto controllerPtr = controller.Upgrade();
        if (!controllerPtr) {
            TAG_LOGE(AceLogTag::ACE_DIALOG, "CustomDialogController is null.");
            return;
        }
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
            TAG_LOGW(AceLogTag::ACE_DIALOG, "Controller%{public}d dialog map is empty.",
                dialogProperties.controllerId.value_or(-1));
            return;
        }
        CHECK_NULL_VOID(dialog);
        if (dialogProperties.isShowInSubWindow) {
            SubwindowManager::GetInstance()->CloseDialogNG(dialog);
            dialogs.pop_back();
        } else {
            auto dialogPattern = dialog->GetPattern<DialogPattern>();
            if (dialogProperties.dialogLevelMode == LevelMode::EMBEDDED && dialogPattern) {
                overlayManager = dialogPattern->GetEmbeddedOverlay(overlayManager);
            }
            overlayManager->CloseDialog(dialog);
        }
    };
    return task;
}

void CustomDialogControllerModelStatic::SetOpenDialog(
    DialogProperties& dialogProperties, std::vector<WeakPtr<AceType>>& dialogs, const WeakPtr<AceType>& controller,
    std::function<RefPtr<UINode>()>&& builder)
{
    auto container = Container::Current();
    auto currentId = Container::CurrentId();
    if (!container) {
        TAG_LOGE(AceLogTag::ACE_DIALOG, "Container is null.");
        return;
    }
    if (container->IsSubContainer() && !dialogProperties.isShowInSubWindow) {
        currentId = SubwindowManager::GetInstance()->GetParentContainerId(Container::CurrentId());
        container = AceEngine::Get().GetContainer(currentId);
        if (!container) {
            TAG_LOGE(AceLogTag::ACE_DIALOG, "ParentContainer is null.");
            return;
        }
    }
    ContainerScope scope(currentId);
    auto pipelineContext = container->GetPipelineContext();
    CHECK_NULL_VOID(pipelineContext);
    auto context = AceType::DynamicCast<NG::PipelineContext>(pipelineContext);
    CHECK_NULL_VOID(context);
    auto overlayManager = context->GetOverlayManager();
    CHECK_NULL_VOID(overlayManager);

    dialogProperties.onStatusChanged = [](bool) {};
    const auto buildFunc = [func = std::move(builder)]() {
        const auto node = func();
        NG::ViewStackProcessor::GetInstance()->Push(node);
    };

    auto executor = context->GetTaskExecutor();
    if (!executor) {
        TAG_LOGE(AceLogTag::ACE_DIALOG, "Task executor is null.");
        return;
    }
    auto task = ParseOpenDialogTask(
        currentId, controller, dialogProperties, dialogs, std::move(buildFunc), overlayManager);
    executor->PostTask(task, TaskExecutor::TaskType::UI, "ArkUIDialogShowCustomDialog");
}

void CustomDialogControllerModelStatic::SetCloseDialog(
    DialogProperties& dialogProperties, std::vector<WeakPtr<AceType>>& dialogs, const WeakPtr<AceType>& controller)
{
    TAG_LOGI(AceLogTag::ACE_DIALOG, "CustomDialogController SetCloseDialog enter.");
    auto container = Container::Current();
    auto currentId = Container::CurrentId();
    if (!container) {
        TAG_LOGE(AceLogTag::ACE_DIALOG, "Container is null.");
        return;
    }
    if (container->IsSubContainer() && !dialogProperties.isShowInSubWindow) {
        currentId = SubwindowManager::GetInstance()->GetParentContainerId(Container::CurrentId());
        container = AceEngine::Get().GetContainer(currentId);
        if (!container) {
            TAG_LOGE(AceLogTag::ACE_DIALOG, "ParentContainer is null.");
            return;
        }
    }
    ContainerScope scope(currentId);
    auto pipelineContext = container->GetPipelineContext();
    CHECK_NULL_VOID(pipelineContext);
    auto context = AceType::DynamicCast<NG::PipelineContext>(pipelineContext);
    CHECK_NULL_VOID(context);
    auto overlayManager = context->GetOverlayManager();
    CHECK_NULL_VOID(overlayManager);
    auto executor = context->GetTaskExecutor();
    CHECK_NULL_VOID(executor);
    auto task = ParseCloseDialogTask(controller, dialogProperties, dialogs, overlayManager);
    executor->PostTask(task, TaskExecutor::TaskType::UI, "ArkUIDialogCloseCustomDialog");
}
} // namespace OHOS::Ace::NG
