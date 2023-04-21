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

#include "core/components_ng/pattern/dialog/custom_dialog_controller_model_ng.h"

#include "base/subwindow/subwindow_manager.h"
#include "core/common/ace_engine.h"
#include "core/common/container.h"
#include "core/pipeline_ng/pipeline_context.h"
#include "frameworks/bridge/common/utils/engine_helper.h"
#include "frameworks/bridge/declarative_frontend/view_stack_processor.h"
#include "frameworks/core/components_ng/base/view_stack_processor.h"

namespace OHOS::Ace::NG {
CustomDialogControllerMdoelNG::CustomDialogControllerMdoelNG()
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
    auto context_ = AceType::DynamicCast<NG::PipelineContext>(pipelineContext);
    CHECK_NULL_VOID(context_);
    overlayManager = context_->GetOverlayManager();
    CHECK_NULL_VOID(overlayManager);

    NG::ScopedViewStackProcessor builderViewStackProcessor;
    LOGD("custom JS node building");
}

void CustomDialogControllerMdoelNG::SetOpenDialog()
{
    auto customNode = NG::ViewStackProcessor::GetInstance()->Finish();
    CHECK_NULL_VOID(customNode);

    WeakPtr<NG::FrameNode> dialog;
    if (dialogProperties_.isShowInSubWindow) {
        dialog = SubwindowManager::GetInstance()->ShowDialogNG(dialogProperties_, customNode);
    } else {
        dialog = overlayManager->ShowDialog(dialogProperties_, customNode, false);
    }
    dialogs_.emplace_back(dialog);
}

void CustomDialogControllerMdoelNG::SetCloseDialog()
{
    RefPtr<NG::FrameNode> dialog;
    while (!dialogs_.empty()) {
        dialog = dialogs_.back().Upgrade();
        if (dialog && !dialog->IsRemoving()) {
            // get the dialog not removed currently
            break;
        }
        dialogs_.pop_back();
    }

    if (dialogs_.empty()) {
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
    if (container->IsSubContainer() && !dialogProperties_.isShowInSubWindow) {
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
    dialogs_.pop_back();
}
} // namespace OHOS::Ace::NG