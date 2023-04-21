/*
 * Copyright (c) 2021-2022 Huawei Device Co., Ltd.
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
const std::vector<DialogAlignment> DIALOG_ALIGNMENT = { DialogAlignment::TOP, DialogAlignment::CENTER,
    DialogAlignment::BOTTOM, DialogAlignment::DEFAULT, DialogAlignment::TOP_START, DialogAlignment::TOP_END,
    DialogAlignment::CENTER_START, DialogAlignment::CENTER_END, DialogAlignment::BOTTOM_START,
    DialogAlignment::BOTTOM_END };

} // namespace

void CustomDialogControllerMdoelImpl::SetOpenDialog()
{
    auto scopedDelegate = EngineHelper::GetCurrentDelegate();
    if (!scopedDelegate) {
        // this case usually means there is no foreground container, need to figure out the reason.
        LOGE("scopedDelegate is null, please check");
        return;
    }

    // Cannot reuse component because might depend on state
    if (customDialog_) {
        customDialog_ = nullptr;
    }

    customDialog_ = ViewStackProcessor::GetInstance()->Finish();

    if (!customDialog_) {
        LOGE("Builder does not generate view.");
        return;
    }

    LOGI("JSCustomDialogController(ShowDialog)");
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
    dialogProperties_.customComponent = customDialog_;
    // EventMarker cancelMarker([cancelCallback = jsCancelFunction_]() {
    //     if (cancelCallback) {
    //         ACE_SCORING_EVENT("CustomDialog.cancel");
    //         cancelCallback->Execute();
    //     }
    // });
    // dialogProperties_.callbacks.try_emplace("cancel", cancelMarker);
    dialogProperties_.onStatusChanged = [this](bool isShown) {
        if (!isShown) {
            this->isShown_ = isShown;
        }
    };

    auto executor = context->GetTaskExecutor();
    if (!executor) {
        LOGE("JSCustomDialogController(ShowDialog) No Executor. Cannot post task.");
        return;
    }

    if (pending_) {
        LOGI("JSCustomDialogController(ShowDialog) current state is pending.");
        dialogOperation_.emplace_back(DialogOperation::DIALOG_OPEN);
        return;
    }

    if (isShown_) {
        LOGI("JSCustomDialogController(ShowDialog) CustomDialog has already shown.");
        return;
    }

    pending_ = true;
    auto task = [context, dialogProperties = dialogProperties_, this]() mutable {
        if (context) {
            this->dialogComponent_ = context->ShowDialog(dialogProperties, false, "CustomDialog");
        } else {
            LOGE("JSCustomDialogController(ShowDialog) context is null.");
        }
        this->NotifyDialogOperation(DialogOperation::DIALOG_OPEN);
    };
    auto stack = context->GetLastStack();
    auto result = false;
    if (stack) {
        result = executor->PostTask(task, TaskExecutor::TaskType::UI);
    } else {
        LOGE("JSCustomDialogController(ShowDialog) stack is null, post delay task.");
        result = executor->PostDelayedTask(task, TaskExecutor::TaskType::UI, DELAY_TIME_FOR_STACK);
    }
    if (!result) {
        LOGW("JSCustomDialogController(ShowDialog) fail to post task, reset pending status");
        pending_ = false;
    }
}

void CustomDialogControllerMdoelImpl::SetCloseDialog()
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

    if (pending_) {
        LOGI("JSCustomDialogController(CloseDialog) current state is pending.");
        dialogOperation_.emplace_back(DialogOperation::DIALOG_CLOSE);
        return;
    }

    pending_ = true;
    auto task = [lastStack, dialogComponent = dialogComponent_, this]() {
        if (!lastStack || !dialogComponent) {
            LOGI("JSCustomDialogController(CloseDialog) stack or dialog is null.");
            this->NotifyDialogOperation(DialogOperation::DIALOG_CLOSE);
            return;
        }
        auto animator = dialogComponent->GetAnimator();
        auto dialogId = dialogComponent->GetDialogId();
        if (animator) {
            if (!dialogComponent->HasStopListenerAdded()) {
                animator->AddStopListener([lastStack, dialogId] {
                    if (lastStack) {
                        lastStack->PopDialog(dialogId);
                    }
                });
                dialogComponent->SetHasStopListenerAdded(true);
            }
            animator->Play();
        } else {
            lastStack->PopDialog(dialogId);
        }
        this->NotifyDialogOperation(DialogOperation::DIALOG_CLOSE);
    };
    auto result = executor->PostTask(task, TaskExecutor::TaskType::UI);
    if (!result) {
        LOGW("JSCustomDialogController(CloseDialog) fail to post task, reset pending status");
        pending_ = false;
    }

    dialogComponent_ = nullptr;
}

void CustomDialogControllerMdoelImpl::NotifyDialogOperation(DialogOperation operation)
{
    LOGI("JSCustomDialogController(NotifyDialogOperation) operation: %{public}d", operation);
    if (operation == DialogOperation::DIALOG_OPEN) {
        isShown_ = true;
        pending_ = false;
        for (auto iter = dialogOperation_.begin(); iter != dialogOperation_.end();) {
            if (*iter == DialogOperation::DIALOG_OPEN) {
                dialogOperation_.erase(iter++);
                continue;
            }

            if (*iter == DialogOperation::DIALOG_CLOSE) {
                dialogOperation_.erase(iter);
                SetCloseDialog();
                break;
            }
        }
    } else if (operation == DialogOperation::DIALOG_CLOSE) {
        isShown_ = false;
        pending_ = false;
        for (auto iter = dialogOperation_.begin(); iter != dialogOperation_.end();) {
            if (*iter == DialogOperation::DIALOG_CLOSE) {
                dialogOperation_.erase(iter++);
                continue;
            }

            if (*iter == DialogOperation::DIALOG_OPEN) {
                dialogOperation_.erase(iter);
                SetOpenDialog();
                break;
            }
        }
    }
}
} // namespace OHOS::Ace::Framework