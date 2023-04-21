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
#include "core/common/ace_engine.h"
#include "core/common/container.h"
#include "core/pipeline_ng/pipeline_context.h"
#include "frameworks/bridge/common/utils/engine_helper.h"
#include "frameworks/bridge/declarative_frontend/view_stack_processor.h"
#include "frameworks/core/components_ng/base/view_stack_processor.h"

namespace OHOS::Ace::NG {
RefPtr<AceType> CustomDialogControllerModelNG::SetOpenDialog()
{
    auto container = Container::Current();
    auto currentId = Container::CurrentId();
    if (container->IsSubContainer()) {
        currentId = SubwindowManager::GetInstance()->GetParentContainerId(Container::CurrentId());
        container = AceEngine::Get().GetContainer(currentId);
    }
    ContainerScope scope(currentId);
    auto pipelineContext = container->GetPipelineContext();
    auto context = AceType::DynamicCast<NG::PipelineContext>(pipelineContext);
    return context->GetOverlayManager();
}

void CustomDialogControllerModelNG::SetOpenDialog(DialogProperties& dialogProperties,
    std::vector<WeakPtr<AceType>>& dialogs, std::function<void(RefPtr<AceType>&)>&& task, bool& pending,
    RefPtr<AceType>& overlayManager, std::function<void()>&& cancelTask)
{
    auto overlayManager_ = AceType::DynamicCast<OverlayManager>(overlayManager);
    auto customNode = NG::ViewStackProcessor::GetInstance()->Finish();
    CHECK_NULL_VOID(customNode);

    WeakPtr<NG::FrameNode> dialog;
    if (dialogProperties.isShowInSubWindow) {
        dialog = SubwindowManager::GetInstance()->ShowDialogNG(dialogProperties, customNode);
    } else {
        dialog = overlayManager_->ShowDialog(dialogProperties, customNode, false);
    }
    dialogs.emplace_back(dialog);
}

void CustomDialogControllerModelNG::SetCloseDialog(DialogProperties& dialogProperties,
    std::vector<WeakPtr<AceType>>& dialogs, bool& pending, std::function<void()>&& task,
    RefPtr<AceType>& dialogComponent)
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

void CustomDialogControllerModelNG::setOnCancel(std::function<void()>&& event, std::function<void()>&& onCancel)
{
    event = onCancel;
}
} // namespace OHOS::Ace::NG