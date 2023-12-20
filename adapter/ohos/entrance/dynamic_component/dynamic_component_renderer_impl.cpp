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

#include "dynamic_component_renderer_impl.h"

#include <memory>

#include "interfaces/inner_api/ace/ui_content.h"
#include "native_engine/native_engine.h"

#include "adapter/ohos/entrance/dynamic_component/uv_task_wrapper_impl.h"
#include "adapter/ohos/entrance/ui_content_impl.h"
#include "base/thread/task_executor.h"
#include "base/utils/utils.h"
#include "core/common/ace_engine.h"
#include "core/common/container_scope.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {
DynamicComponentRendererImpl::DynamicComponentRendererImpl(const RefPtr<FrameNode>& host, int32_t hostInstanceId,
    const std::string& hapPath, const std::string& abcPath, const std::string& entryPoint, void* runtime)
    : hapPath_(hapPath), abcPath_(abcPath), entryPoint_(entryPoint), hostInstanceId_(hostInstanceId)
{
    host_ = WeakPtr(host);
    runtime_ = reinterpret_cast<NativeEngine*>(runtime);
}

std::shared_ptr<DynamicComponentRenderer> DynamicComponentRenderer::Create(const RefPtr<FrameNode>& host,
    int32_t hostInstanceId, const std::string& hapPath, const std::string& abcPath, const std::string& entryPoint,
    void* runtime)
{
    return std::make_shared<DynamicComponentRendererImpl>(host, hostInstanceId, hapPath, abcPath, entryPoint, runtime);
}

void DynamicComponentRendererImpl::CreateContent()
{
    CHECK_NULL_VOID(runtime_);
    if (!runtime_->IsRestrictedWorkerThread()) {
        LOGW("DynamicComponent should run in restricted worker thread");
        return;
    }

    auto napiEnv = reinterpret_cast<napi_env>(runtime_);
    auto uvTaskWrapper = std::make_shared<UVTaskWrapperImpl>(napiEnv);

    uvTaskWrapper->Call([weak = this->weak_from_this()]() {
        auto renderer = weak.lock();
        CHECK_NULL_VOID(renderer);

        // create UI Content
        LOGI("create dynamic UI Content");
        renderer->uiContent_ = UIContent::Create(nullptr, renderer->runtime_, true);
        CHECK_NULL_VOID(renderer->uiContent_);

        renderer->uiContent_->InitializeDynamic(renderer->hapPath_, renderer->abcPath_, renderer->entryPoint_);
        renderer->AttachRenderContext();
        LOGD("foreground dynamic UI content");
        renderer->uiContent_->Foreground();
    });
}

void DynamicComponentRendererImpl::AttachRenderContext()
{
    ContainerScope scope(hostInstanceId_);
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto taskExecutor = pipeline->GetTaskExecutor();
    CHECK_NULL_VOID(taskExecutor);
    taskExecutor->PostSyncTask(
        [weak = host_, instanceId = uiContent_->GetInstanceId()]() {
            auto host = weak.Upgrade();
            CHECK_NULL_VOID(host);
            auto renderContext = host->GetRenderContext();
            CHECK_NULL_VOID(renderContext);

            auto container = AceEngine::Get().GetContainer(instanceId);
            CHECK_NULL_VOID(container);
            auto pipeline = container->GetPipelineContext();
            CHECK_NULL_VOID(pipeline);
            auto pipelineContext = AceType::DynamicCast<NG::PipelineContext>(pipeline);
            CHECK_NULL_VOID(pipelineContext);
            auto rootElement = pipelineContext->GetRootElement();
            CHECK_NULL_VOID(rootElement);
            auto exRenderContext = rootElement->GetRenderContext();
            CHECK_NULL_VOID(exRenderContext);

            exRenderContext->SetClipToFrame(true);
            exRenderContext->SetClipToBounds(true);

            LOGD("add render context of dynamic component");
            renderContext->ClearChildren();
            renderContext->AddChild(exRenderContext, -1);

            host->MarkDirtyNode(PROPERTY_UPDATE_LAYOUT);
            auto parent = host->GetParent();
            CHECK_NULL_VOID(parent);
            parent->MarkNeedSyncRenderTree();
            parent->RebuildRenderContextTree();
            renderContext->RequestNextFrame();
        },
        TaskExecutor::TaskType::UI);
}

void DynamicComponentRendererImpl::TransferPointerEvent(const std::shared_ptr<MMI::PointerEvent>& pointerEvent)
{
    auto taskExecutor = GetTaskExecutor();
    CHECK_NULL_VOID(taskExecutor);
    taskExecutor->PostTask(
        [uiContent = uiContent_, pointerEvent]() {
            ContainerScope scope(uiContent->GetInstanceId());
            uiContent->ProcessPointerEvent(pointerEvent);
        },
        TaskExecutor::TaskType::UI);
}

void DynamicComponentRendererImpl::TransferKeyEvent(const std::shared_ptr<MMI::KeyEvent>& keyEvent)
{
    auto taskExecutor = GetTaskExecutor();
    CHECK_NULL_VOID(taskExecutor);
    taskExecutor->PostTask(
        [uiContent = uiContent_, keyEvent]() {
            ContainerScope scope(uiContent->GetInstanceId());
            uiContent->ProcessKeyEvent(keyEvent);
        },
        TaskExecutor::TaskType::UI);
}

void DynamicComponentRendererImpl::UpdateViewportConfig(const Ace::ViewportConfig& config,
    Rosen::WindowSizeChangeReason reason, const std::shared_ptr<Rosen::RSTransaction>& rsTransaction)
{
    LOGD("update dynamic component viewport");
    auto taskExecutor = GetTaskExecutor();
    CHECK_NULL_VOID(taskExecutor);
    taskExecutor->PostTask(
        [uiContent = uiContent_, config, reason, rsTransaction]() {
            ContainerScope scope(uiContent->GetInstanceId());
            auto width = config.Width();
            auto height = config.Height();
            uiContent->SetFormWidth(width);
            uiContent->SetFormHeight(height);
            uiContent->OnFormSurfaceChange(width, height);
            uiContent->UpdateViewportConfig(config, reason, rsTransaction);
        },
        TaskExecutor::TaskType::UI);
}

void DynamicComponentRendererImpl::DestroyContent()
{
    auto taskExecutor = GetTaskExecutor();
    CHECK_NULL_VOID(taskExecutor);
    taskExecutor->PostTask(
        [uiContent = uiContent_]() {
            ContainerScope scope(uiContent->GetInstanceId());
            uiContent->Destroy();
        },
        TaskExecutor::TaskType::UI);

    uiContent_ = nullptr;
}

RefPtr<TaskExecutor> DynamicComponentRendererImpl::GetTaskExecutor()
{
    CHECK_NULL_RETURN(uiContent_, nullptr);
    auto instanceId = uiContent_->GetInstanceId();
    auto container = AceEngine::Get().GetContainer(instanceId);
    CHECK_NULL_RETURN(container, nullptr);
    auto taskExecutor = container->GetTaskExecutor();
    return taskExecutor;
}
} // namespace OHOS::Ace::NG