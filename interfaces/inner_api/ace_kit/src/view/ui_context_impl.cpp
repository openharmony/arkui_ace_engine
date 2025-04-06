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

#include "interfaces/inner_api/ace_kit/src/view/ui_context_impl.h"

#include "ui/base/utils/utils.h"
#include "interfaces/inner_api/ace_kit/src/view/frame_node_impl.h"
#include "interfaces/inner_api/ace_kit/src/view/overlay/overlay_manager_impl.h"

#include "base/thread/task_executor.h"
#include "bridge/common/utils/engine_helper.h"
#include "core/common/container_scope.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::Kit {

RefPtr<UIContext> UIContext::Current()
{
    const auto& pipeline = NG::PipelineContext::GetCurrentContextSafelyWithCheck();
    CHECK_NULL_RETURN(pipeline, nullptr);
    return pipeline->GetUIContext();
}

UIContextImpl::~UIContextImpl()
{
    Reset();
}

void UIContextImpl::Reset()
{
    context_ = nullptr;
}

void UIContextImpl::RunScopeUITaskSync(Task&& task, const std::string& name)
{
    CHECK_NULL_VOID(context_);
    const auto& taskExecutor = context_->GetTaskExecutor();
    CHECK_NULL_VOID(taskExecutor);
    ContainerScope scope(context_->GetInstanceId());
    taskExecutor->PostSyncTask(task, TaskExecutor::TaskType::UI, name);
}

void UIContextImpl::RunScopeUITask(Task&& task, const std::string& name)
{
    CHECK_NULL_VOID(context_);
    const auto& taskExecutor = context_->GetTaskExecutor();
    CHECK_NULL_VOID(taskExecutor);
    ContainerScope scope(context_->GetInstanceId());
    taskExecutor->PostTask(task, TaskExecutor::TaskType::UI, name);
}

void UIContextImpl::OnBackPressed()
{
    CHECK_NULL_VOID(context_);
    bool result = context_->OnBackPressed();
    if (!result) {
        auto delegate = OHOS::Ace::EngineHelper::GetCurrentDelegate();
        CHECK_NULL_VOID(delegate);
        delegate->Back("");
    }
}

ColorMode UIContextImpl::GetLocalColorMode()
{
    CHECK_NULL_RETURN(context_, ColorMode::COLOR_MODE_UNDEFINED);
    return static_cast<ColorMode>(context_->GetLocalColorMode());
}

ColorMode UIContextImpl::GetColorMode()
{
    CHECK_NULL_RETURN(context_, ColorMode::COLOR_MODE_UNDEFINED);
    return static_cast<ColorMode>(context_->GetColorMode());
}

float UIContextImpl::GetFontScale()
{
    CHECK_NULL_RETURN(context_, 1.0f);
    return context_->GetFontScale();
}

RefPtr<OverlayManager> UIContextImpl::GetOverlayManager()
{
    if (overlayManager_) {
        return overlayManager_;
    }
    CHECK_NULL_RETURN(context_, nullptr);
    overlayManager_ = AceType::MakeRefPtr<OverlayManagerImpl>(context_);
    return overlayManager_;
}
} // namespace OHOS::Ace::Kit
