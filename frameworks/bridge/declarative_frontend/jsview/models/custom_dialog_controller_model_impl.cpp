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

#include "bridge/declarative_frontend/jsview/models/custom_dialog_controller_model_impl.h"

#include "base/subwindow/subwindow_manager.h"
#include "core/components/dialog/dialog_component.h"
#include "frameworks/bridge/declarative_frontend/view_stack_processor.h"

namespace OHOS::Ace::Framework {
namespace {
constexpr uint32_t DELAY_TIME_FOR_STACK = 100;
} // namespace

void CustomDialogControllerModelImpl::NotifyDialogOperation(DialogOperation operation,
    DialogProperties& dialogProperties, bool& pending, bool& isShown, std::function<void()>&& cancelTask,
    RefPtr<AceType>& dialogComponent, RefPtr<AceType>& customDialog, std::list<DialogOperation>& dialogOperation)
{
    LOGI("JSCustomDialogController(NotifyDialogOperation) operation: %{public}d", operation);
    if (operation == DialogOperation::DIALOG_OPEN) {
        isShown = true;
        pending = false;
        for (auto iter = dialogOperation.begin(); iter != dialogOperation.end();) {
            if (*iter == DialogOperation::DIALOG_OPEN) {
                dialogOperation.erase(iter++);
                continue;
            }

            if (*iter == DialogOperation::DIALOG_CLOSE) {
                dialogOperation.erase(iter);
                CloseDialog(dialogProperties, pending, isShown, std::move(cancelTask), dialogComponent, customDialog,
                    dialogOperation);
                break;
            }
        }
    } else if (operation == DialogOperation::DIALOG_CLOSE) {
        isShown = false;
        pending = false;
        for (auto iter = dialogOperation.begin(); iter != dialogOperation.end();) {
            if (*iter == DialogOperation::DIALOG_CLOSE) {
                dialogOperation.erase(iter++);
                continue;
            }

            if (*iter == DialogOperation::DIALOG_OPEN) {
                dialogOperation.erase(iter);
                ShowDialog(dialogProperties, pending, isShown, std::move(cancelTask), dialogComponent, customDialog,
                    dialogOperation);
                break;
            }
        }
    }
}

void CustomDialogControllerModelImpl::ShowDialog(DialogProperties& dialogProperties, bool& pending, bool& isShown,
    std::function<void()>&& cancelTask, RefPtr<AceType>& dialogComponent, RefPtr<AceType>& customDialog,
    std::list<DialogOperation>& dialogOperation)
{
    RefPtr<Container> container;
    auto current = Container::Current();
    if (!current) {
        LOGE("Container is null.");
        return;
    }
    if (current->IsSubContainer()) {
        auto parentContainerId = SubwindowManager::GetInstance()->GetParentContainerId(Container::CurrentId());
        container = AceEngine::Get().GetContainer(parentContainerId);
    } else {
        container = std::move(current);
    }
    if (!container) {
        LOGE("Container is null.");
        return;
    }
    auto context = AceType::DynamicCast<PipelineContext>(container->GetPipelineContext());
    if (!context) {
        LOGE("JSCustomDialogController No Context");
        return;
    }
    dialogProperties.customComponent = customDialog;
    dialogProperties.callbacks.try_emplace("cancel", EventMarker(std::move(cancelTask)));
    dialogProperties.onStatusChanged = [&isShown](bool isShownStatus) {
        if (!isShownStatus) {
            isShown = isShownStatus;
        }
    };

    auto executor = context->GetTaskExecutor();
    if (!executor) {
        LOGE("JSCustomDialogController(ShowDialog) No Executor. Cannot post task.");
        return;
    }

    if (pending) {
        LOGI("JSCustomDialogController(ShowDialog) current state is pending.");
        dialogOperation.emplace_back(DialogOperation::DIALOG_OPEN);
        return;
    }

    if (isShown) {
        LOGI("JSCustomDialogController(ShowDialog) CustomDialog has already shown.");
        return;
    }

    pending = true;
    auto task = [context, showDialogProperties = dialogProperties, &dialogProperties, &pending, &isShown, &cancelTask,
                    &dialogComponent, &customDialog, &dialogOperation, this]() mutable {
        if (context) {
            dialogComponent = context->ShowDialog(showDialogProperties, false, "CustomDialog");
        } else {
            LOGE("JSCustomDialogController(ShowDialog) context is null.");
        }
        this->NotifyDialogOperation(DialogOperation::DIALOG_OPEN, dialogProperties, pending, isShown,
            std::move(cancelTask), dialogComponent, customDialog, dialogOperation);
    };
    auto stack = context->GetLastStack();
    auto result = false;
    if (stack) {
        result = executor->PostTask(task, TaskExecutor::TaskType::UI, "ArkUICustomDialogNotifyOpenOperation");
    } else {
        LOGE("JSCustomDialogController(ShowDialog) stack is null, post delay task.");
        result = executor->PostDelayedTask(
            task, TaskExecutor::TaskType::UI, DELAY_TIME_FOR_STACK, "ArkUICustomDialogNotifyOpenOperationDelay");
    }
    if (!result) {
        LOGW("JSCustomDialogController(ShowDialog) fail to post task, reset pending status");
        pending = false;
    }
}

void CustomDialogControllerModelImpl::CloseDialog(DialogProperties& dialogProperties, bool& pending, bool& isShown,
    std::function<void()>&& cancelTask, RefPtr<AceType>& dialogComponent, RefPtr<AceType>& customDialog,
    std::list<DialogOperation>& dialogOperation)
{
    LOGI("JSCustomDialogController(CloseDialog)");
    RefPtr<Container> container;
    auto current = Container::Current();
    if (!current) {
        LOGE("Container is null.");
        return;
    }
    if (current->IsSubContainer()) {
        auto parentContainerId = SubwindowManager::GetInstance()->GetParentContainerId(Container::CurrentId());
        container = AceEngine::Get().GetContainer(parentContainerId);
    } else {
        container = std::move(current);
    }
    if (!container) {
        LOGE("Container is null.");
        return;
    }
    auto context = AceType::DynamicCast<PipelineContext>(container->GetPipelineContext());
    if (!context) {
        LOGE("JSCustomDialogController No Context");
        return;
    }
    const auto& lastStack = context->GetLastStack();
    if (!lastStack) {
        LOGE("JSCustomDialogController No Stack!");
        return;
    }
    auto executor = context->GetTaskExecutor();
    if (!executor) {
        LOGE("JSCustomDialogController(CloseDialog) No Executor. Cannot post task.");
        return;
    }

    if (pending) {
        LOGI("JSCustomDialogController(CloseDialog) current state is pending.");
        dialogOperation.emplace_back(DialogOperation::DIALOG_CLOSE);
        return;
    }

    pending = true;
    auto task = [lastStack, showDialogComponent = dialogComponent, &dialogProperties, &pending, &isShown, &cancelTask,
                    &dialogComponent, &customDialog, &dialogOperation, this]() {
        if (!lastStack || !showDialogComponent) {
            LOGI("JSCustomDialogController(CloseDialog) stack or dialog is null.");
            this->NotifyDialogOperation(DialogOperation::DIALOG_CLOSE, dialogProperties, pending, isShown,
                std::move(cancelTask), dialogComponent, customDialog, dialogOperation);
            return;
        }
        auto animator = AceType::DynamicCast<DialogComponent>(showDialogComponent)->GetAnimator();
        auto dialogId = AceType::DynamicCast<DialogComponent>(showDialogComponent)->GetDialogId();
        if (animator) {
            if (!AceType::DynamicCast<DialogComponent>(showDialogComponent)->HasStopListenerAdded()) {
                animator->AddStopListener([lastStack, dialogId] {
                    if (lastStack) {
                        lastStack->PopDialog(dialogId);
                    }
                });
                AceType::DynamicCast<DialogComponent>(showDialogComponent)->SetHasStopListenerAdded(true);
            }
            animator->Play();
        } else {
            lastStack->PopDialog(dialogId);
        }
        this->NotifyDialogOperation(DialogOperation::DIALOG_CLOSE, dialogProperties, pending, isShown,
            std::move(cancelTask), dialogComponent, customDialog, dialogOperation);
    };
    auto result = executor->PostTask(task, TaskExecutor::TaskType::UI, "ArkUICustomDialogNotifyCloseOperation");
    if (!result) {
        LOGW("JSCustomDialogController(CloseDialog) fail to post task, reset pending status");
        pending = false;
    }

    dialogComponent = nullptr;
}

void CustomDialogControllerModelImpl::SetOpenDialog(DialogProperties& dialogProperties,
    const WeakPtr<AceType>& controller, std::vector<WeakPtr<AceType>>& dialogs,
    bool& pending, bool& isShown, std::function<void()>&& cancelTask, std::function<void()>&& buildFunc,
    RefPtr<AceType>& dialogComponent, RefPtr<AceType>& customDialog, std::list<DialogOperation>& dialogOperation)
{
    // Cannot reuse component because might depend on state
    if (customDialog) {
        customDialog = nullptr;
    }
    buildFunc();
    customDialog = ViewStackProcessor::GetInstance()->Finish();
    if (!customDialog) {
        LOGE("Builder does not generate view.");
        return;
    }

    ShowDialog(
        dialogProperties, pending, isShown, std::move(cancelTask), dialogComponent, customDialog, dialogOperation);
}

void CustomDialogControllerModelImpl::SetCloseDialog(DialogProperties& dialogProperties,
    const WeakPtr<AceType>& controller, std::vector<WeakPtr<AceType>>& dialogs,
    bool& pending, bool& isShown, std::function<void()>&& cancelTask, RefPtr<AceType>& dialogComponent,
    RefPtr<AceType>& customDialog, std::list<DialogOperation>& dialogOperation)
{
    CloseDialog(
        dialogProperties, pending, isShown, std::move(cancelTask), dialogComponent, customDialog, dialogOperation);
}
} // namespace OHOS::Ace::Framework
