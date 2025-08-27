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

#include "base/subwindow/subwindow_manager.h"
#include "core/components_ng/pattern/dialog/dialog_pattern.h"
#include "core/components_ng/pattern/overlay/dialog_manager.h"

namespace OHOS::Ace::NG {
void CustomDialogControllerModelNG::SetOpenDialog(DialogProperties& dialogProperties,
    const WeakPtr<AceType>& controller, std::vector<WeakPtr<AceType>>& dialogs,
    bool& pending, bool& isShown, std::function<void()>&& cancelTask, std::function<void()>&& buildFunc,
    RefPtr<AceType>& dialogComponent, RefPtr<AceType>& customDialog, std::list<DialogOperation>& dialogOperation,
    bool& hasBind)
{
    auto container = Container::Current();
    auto currentId = Container::CurrentId();
    if (!container) {
        TAG_LOGE(AceLogTag::ACE_DIALOG, "Container is null.");
        return;
    }

    auto pipelineContext = container->GetPipelineContext();
    CHECK_NULL_VOID(pipelineContext);
    auto context = AceType::DynamicCast<NG::PipelineContext>(pipelineContext);
    CHECK_NULL_VOID(context);
    auto executor = context->GetTaskExecutor();
    if (!executor) {
        TAG_LOGE(AceLogTag::ACE_DIALOG, "Task executor is null.");
        return;
    }
    auto task = ParseOpenDialogTask(
        currentId, controller, dialogProperties, dialogs, std::move(buildFunc), hasBind, isShown);
    executor->PostTask(task, TaskExecutor::TaskType::UI, "ArkUIDialogShowCustomDialog");
}

void CustomDialogControllerModelNG::SetOpenDialogInTask(const RefPtr<OverlayManager>& overlayManager, const RefPtr<Container>& container,
    const WeakPtr<AceType>& controller, RefPtr<NG::FrameNode>& dialog, DialogProperties& dialogProperties,
    std::function<void()>&& func, bool& isShown)
{
    if (!overlayManager || !container) {
        TAG_LOGE(AceLogTag::ACE_DIALOG, "set open dialog in task, manager or container is null.");
        return;
    }
    dialogProperties.onStatusChanged = [&isShown](bool isShownStatus) {
        if (!isShownStatus) {
            isShown = isShownStatus;
        }
    };
    dialogProperties.isUserCreatedDialog = true;
    auto controllerPtr = controller.Upgrade();
    if (!controllerPtr) {
        TAG_LOGE(AceLogTag::ACE_DIALOG, "set open dialog in task, controller is null.");
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
}

TaskExecutor::Task CustomDialogControllerModelNG::ParseOpenDialogTask(int32_t currentId,
    const WeakPtr<AceType>& controller, DialogProperties& dialogProperties, std::vector<WeakPtr<AceType>>& dialogs,
    std::function<void()>&& buildFunc, bool& hasBind, bool& isShown)
{
    auto task = [currentId, controller, &dialogProperties, &dialogs, func = std::move(buildFunc),
            &hasBind, isShown]() mutable {
        auto controllerPtr = controller.Upgrade();
        if (!controllerPtr) {
            TAG_LOGE(AceLogTag::ACE_DIALOG, "parse open dialog, controller is null.");
            return;
        }
        auto container = AceEngine::Get().GetContainer(currentId);
        CHECK_NULL_VOID(container);
        auto isSubContainer = container->IsSubContainer();
        auto expandDisplay = SubwindowManager::GetInstance()->GetIsExpandDisplay();
        auto enableOpenSubwindowInSubwindow = expandDisplay || container->IsPcOrFreeMultiWindowCapability();
        if (!enableOpenSubwindowInSubwindow && isSubContainer && dialogProperties.isShowInSubWindow) {
            TAG_LOGW(AceLogTag::ACE_DIALOG, "subwindow can not open dialog in subwindow");
            return;
        }
        if (isSubContainer && (!dialogProperties.isShowInSubWindow || enableOpenSubwindowInSubwindow)) {
            currentId = SubwindowManager::GetInstance()->GetParentContainerId(Container::CurrentId());
            container = AceEngine::Get().GetContainer(currentId);
            if (!container) {
                TAG_LOGE(AceLogTag::ACE_DIALOG, "ParentContainer is null.");
                return;
            }
        }
        ContainerScope scope(currentId);
        auto context = AceType::DynamicCast<NG::PipelineContext>(container->GetPipelineContext());
        CHECK_NULL_VOID(context);
        auto overlayManager = context->GetOverlayManager();
        CHECK_NULL_VOID(overlayManager);
        if (dialogProperties.dialogLevelMode == LevelMode::EMBEDDED) {
            auto embeddedOverlay = NG::DialogManager::GetEmbeddedOverlay(dialogProperties.dialogLevelUniqueId, context);
            if (embeddedOverlay) {
                overlayManager = embeddedOverlay;
            }
        }
        RefPtr<NG::FrameNode> dialog;
        CustomDialogControllerModelNG::SetOpenDialogInTask(overlayManager, container, controller, dialog,
            dialogProperties, std::move(func), isShown);
        if (!dialog) {
            TAG_LOGE(AceLogTag::ACE_DIALOG, "fail to show dialog.");
            return;
        }
        TAG_LOGI(AceLogTag::ACE_DIALOG, "Controller/%{public}d create dialog node/%{public}d successfully.",
            dialogProperties.controllerId.value_or(-1), dialog->GetId());
        dialogs.emplace_back(dialog);
        hasBind = true;
    };
    return task;
}

RefPtr<UINode> CustomDialogControllerModelNG::SetOpenDialogWithNode(DialogProperties& dialogProperties,
    const RefPtr<UINode>& customNode)
{
    ContainerScope scope(Container::CurrentIdSafely());
    auto container = Container::Current();
    CHECK_NULL_RETURN(container, nullptr);
    if (container->IsSubContainer() && !dialogProperties.isShowInSubWindow) {
        auto currentId = SubwindowManager::GetInstance()->GetParentContainerId(Container::CurrentId());
        container = AceEngine::Get().GetContainer(currentId);
        CHECK_NULL_RETURN(container, nullptr);
    }
    auto pipelineContext = container->GetPipelineContext();
    CHECK_NULL_RETURN(pipelineContext, nullptr);
    auto context = AceType::DynamicCast<NG::PipelineContext>(pipelineContext);
    CHECK_NULL_RETURN(context, nullptr);
    auto overlayManager = context->GetOverlayManager();
    CHECK_NULL_RETURN(overlayManager, nullptr);
    if (dialogProperties.dialogLevelMode == LevelMode::EMBEDDED) {
        auto embeddedOverlay = NG::DialogManager::GetEmbeddedOverlay(dialogProperties.dialogLevelUniqueId, context);
        if (embeddedOverlay) {
            overlayManager = embeddedOverlay;
        }
    }
    dialogProperties.isUserCreatedDialog = true;
    RefPtr<NG::FrameNode> dialog;
    if (dialogProperties.isShowInSubWindow) {
        dialog = SubwindowManager::GetInstance()->ShowDialogNGWithNode(dialogProperties, customNode);
        CHECK_NULL_RETURN(dialog, nullptr);
        if (dialogProperties.isModal && !dialogProperties.isSceneBoardDialog && !container->IsUIExtensionWindow()) {
            DialogProperties Maskarg;
            Maskarg.isMask = true;
            Maskarg.autoCancel = dialogProperties.autoCancel;
            Maskarg.maskColor = dialogProperties.maskColor;
            auto mask = overlayManager->ShowDialogWithNode(Maskarg, nullptr, false);
            CHECK_NULL_RETURN(mask, dialog);
            overlayManager->SetMaskNodeId(dialog->GetId(), mask->GetId());
        }
    } else {
        dialog = overlayManager->ShowDialogWithNode(dialogProperties, customNode, false);
    }
    return dialog;
}

void CustomDialogControllerModelNG::SetCloseDialog(DialogProperties& dialogProperties,
    const WeakPtr<AceType>& controller, std::vector<WeakPtr<AceType>>& dialogs,
    bool& pending, bool& isShown, std::function<void()>&& cancelTask, RefPtr<AceType>& dialogComponent,
    RefPtr<AceType>& customDialog, std::list<DialogOperation>& dialogOperation)
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

TaskExecutor::Task CustomDialogControllerModelNG::ParseCloseDialogTask(const WeakPtr<AceType>& controller,
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

void CustomDialogControllerModelNG::SetCloseDialogForNDK(FrameNode* dialogNode)
{
    CHECK_NULL_VOID(dialogNode);
    dialogNode->SetIsUseTransitionAnimator(true);
    auto dialogRef = AceType::Claim(dialogNode);
    if (!Container::Current()) {
        // close dialog when current container is null, so we should get container through current safelyId
        ContainerScope scope(Container::CurrentIdSafely());
        auto container = Container::Current();
        CHECK_NULL_VOID(container);
        auto pipelineContext = container->GetPipelineContext();
        CHECK_NULL_VOID(pipelineContext);
        auto context = AceType::DynamicCast<NG::PipelineContext>(pipelineContext);
        CHECK_NULL_VOID(context);
        auto overlayManager = context->GetOverlayManager();
        CHECK_NULL_VOID(overlayManager);
        auto currentOverlay = DialogManager::GetInstance().GetEmbeddedOverlayWithNode(dialogRef);
        if (currentOverlay) {
            overlayManager = currentOverlay;
        }
        overlayManager->CloseDialog(dialogRef);
    } else {
        // close dialog when current container is not null, so we should get pipelineContext through dialogNode
        auto nodeContext = dialogNode->GetContextWithCheck();
        CHECK_NULL_VOID(nodeContext);
        auto overlay = nodeContext->GetOverlayManager();
        CHECK_NULL_VOID(overlay);
        auto currentOverlay = DialogManager::GetInstance().GetEmbeddedOverlayWithNode(dialogRef);
        if (currentOverlay) {
            overlay = currentOverlay;
        }
        overlay->CloseDialog(dialogRef);
    }
}

PromptActionCommonState CustomDialogControllerModelNG::GetState(std::vector<WeakPtr<AceType>>& dialogs, bool& hasBind)
{
    RefPtr<NG::FrameNode> dialog;
    PromptActionCommonState state = PromptActionCommonState::UNINITIALIZED;
    if (hasBind) {
        state = PromptActionCommonState::INITIALIZED;
    }
    while (!dialogs.empty()) {
        dialog = AceType::DynamicCast<NG::FrameNode>(dialogs.back().Upgrade());
        if (dialog) {
            // get the dialog not removed currently
            break;
        }
        dialogs.pop_back();
    }
    if (!dialog) {
        if (hasBind) {
            return PromptActionCommonState::DISAPPEARED;
        }
        return state;
    }
    auto dialogPattern = dialog->GetPattern<DialogPattern>();
    if (!dialogPattern) {
        return state;
    }
    state = dialogPattern->GetState();
    return state;
}

PromptActionCommonState CustomDialogControllerModelNG::GetStateWithNode(FrameNode* dialogNode)
{
    PromptActionCommonState state = PromptActionCommonState::INITIALIZED;
    CHECK_NULL_RETURN(dialogNode, state);
    auto dialogRef = AceType::Claim(dialogNode);
    auto dialogPattern = dialogRef->GetPattern<DialogPattern>();
    CHECK_NULL_RETURN(dialogPattern, state);
    state = dialogPattern->GetState();
    return state;
}
} // namespace OHOS::Ace::NG
