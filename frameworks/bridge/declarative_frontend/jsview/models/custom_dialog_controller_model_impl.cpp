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
#include "core/common/ace_engine.h"
#include "core/common/container.h"
#include "core/pipeline_ng/pipeline_context.h"
#include "frameworks/bridge/common/utils/engine_helper.h"
#include "frameworks/bridge/declarative_frontend/view_stack_processor.h"
#include "frameworks/core/components_ng/base/view_stack_processor.h"

namespace OHOS::Ace::Framework {
namespace {
constexpr uint32_t DELAY_TIME_FOR_STACK = 100;
} // namespace

void CustomDialogControllerModelImpl::SetOpenDialog(DialogProperties& dialogProperties,
    std::vector<WeakPtr<AceType>>& dialogs, std::function<void(RefPtr<AceType>&)>&& task, bool& pending,
    RefPtr<AceType>& aceType, std::function<void()>&& cancelTask)
{
    RefPtr<Container> container;
    auto current = Container::Current();
    if (current->IsSubContainer()) {
        auto parentContainerId = SubwindowManager::GetInstance()->GetParentContainerId(Container::CurrentId());
        container = AceEngine::Get().GetContainer(parentContainerId);
    } else {
        container = std::move(current);
    }
    auto context = AceType::DynamicCast<PipelineContext>(container->GetPipelineContext());
    if (!context) {
        LOGE("JSCustomDialogController No Context");
        return;
    }

    auto executor = context->GetTaskExecutor();
    if (!executor) {
        LOGE("JSCustomDialogController(ShowDialog) No Executor. Cannot post task.");
        return;
    }
    dialogProperties.callbacks.try_emplace("cancel", EventMarker(std::move(cancelTask)));
    auto func = task;
    auto dialogComponent = AceType::DynamicCast<AceType>(context->ShowDialog(dialogProperties, false, "CustomDialog"));
    auto task_impl = [dialogComponent, func]() mutable { func(dialogComponent); };

    pending = true;
    auto stack = context->GetLastStack();
    auto result = false;
    if (stack) {
        result = executor->PostTask(task_impl, TaskExecutor::TaskType::UI);
    } else {
        LOGE("JSCustomDialogController(ShowDialog) stack is null, post delay task.");
        result = executor->PostDelayedTask(task_impl, TaskExecutor::TaskType::UI, DELAY_TIME_FOR_STACK);
    }
    if (!result) {
        LOGW("JSCustomDialogController(ShowDialog) fail to post task, reset pending status");
        pending = false;
    }
}

void CustomDialogControllerModelImpl::SetCloseDialog(DialogProperties& dialogProperties,
    std::vector<WeakPtr<AceType>>& dialogs, bool& pending, std::function<void()>&& task,
    RefPtr<AceType>& dialogComponent)
{
    LOGI("JSCustomDialogController(CloseDialog)");
    RefPtr<Container> container;
    auto current = Container::Current();
    if (!current) {
        LOGE("Current is null.");
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
    pending = true;
    auto func = task;
    auto task_ = [lastStack, dialogComponent_ = dialogComponent, func]() {
        if (!lastStack || !dialogComponent_) {
            LOGI("JSCustomDialogController(CloseDialog) stack or dialog is null.");
            func();
            return;
        }
        auto animator = AceType::DynamicCast<DialogComponent>(dialogComponent_)->GetAnimator();
        auto dialogId = AceType::DynamicCast<DialogComponent>(dialogComponent_)->GetDialogId();
        if (animator) {
            if (!AceType::DynamicCast<DialogComponent>(dialogComponent_)->HasStopListenerAdded()) {
                animator->AddStopListener([lastStack, dialogId] {
                    if (lastStack) {
                        lastStack->PopDialog(dialogId);
                    }
                });
                AceType::DynamicCast<DialogComponent>(dialogComponent_)->SetHasStopListenerAdded(true);
            }
            animator->Play();
        } else {
            lastStack->PopDialog(dialogId);
        }
        func();
    };

    auto result = executor->PostTask(task_, TaskExecutor::TaskType::UI);
    if (!result) {
        LOGW("JSCustomDialogController(CloseDialog) fail to post task, reset pending status");
        pending = false;
    }

    dialogComponent = nullptr;
}
} // namespace OHOS::Ace::Framework