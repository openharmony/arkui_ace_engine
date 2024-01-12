/*
 * Copyright (c) 2023-2024 Huawei Device Co., Ltd.
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
#include "bridge/card_frontend/form_frontend_declarative.h"
#include "core/common/container.h"
#include "core/common/container_scope.h"
#include "core/components_ng/pattern/stage/page_pattern.h"
#include "core/components_ng/pattern/ui_extension/ui_extension_pattern.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {
DynamicComponentRendererImpl::DynamicComponentRendererImpl(const RefPtr<FrameNode>& host, const std::string& hapPath,
    const std::string& abcPath, const std::string& entryPoint, void* runtime)
    : hapPath_(hapPath), abcPath_(abcPath), entryPoint_(entryPoint)
{
    host_ = WeakPtr(host);
    runtime_ = reinterpret_cast<NativeEngine*>(runtime);
}

RefPtr<DynamicComponentRenderer> DynamicComponentRenderer::Create(const RefPtr<FrameNode>& host,
    const std::string& hapPath, const std::string& abcPath, const std::string& entryPoint, void* runtime)
{
    return AceType::MakeRefPtr<DynamicComponentRendererImpl>(host, hapPath, abcPath, entryPoint, runtime);
}

void DynamicComponentRendererImpl::CreateContent()
{
    hostInstanceId_ = Container::CurrentId();

    CHECK_NULL_VOID(runtime_);
    if (!runtime_->IsRestrictedWorkerThread()) {
        TAG_LOGW(AceLogTag::ACE_DYNAMIC_COMPONENT, "DynamicComponent should run in restricted worker thread");
        return;
    }

    auto napiEnv = reinterpret_cast<napi_env>(runtime_);
    auto uvTaskWrapper = std::make_shared<UVTaskWrapperImpl>(napiEnv);
    uvTaskWrapper->Call([weak = WeakClaim(this)]() {
        auto renderer = weak.Upgrade();
        CHECK_NULL_VOID(renderer);

        // create UI Content
        TAG_LOGI(AceLogTag::ACE_DYNAMIC_COMPONENT, "create dynamic UI Content");
        renderer->uiContent_ = UIContent::Create(nullptr, renderer->runtime_, true);
        CHECK_NULL_VOID(renderer->uiContent_);

        renderer->uiContent_->InitializeDynamic(renderer->hapPath_, renderer->abcPath_, renderer->entryPoint_);
        ContainerScope scope(renderer->uiContent_->GetInstanceId());
        renderer->RegisterSizeChangedCallback();
        renderer->AttachRenderContext();
        TAG_LOGI(AceLogTag::ACE_DYNAMIC_COMPONENT, "foreground dynamic UI content");
        renderer->uiContent_->Foreground();
    });
}

void DynamicComponentRendererImpl::RegisterSizeChangedCallback()
{
    CHECK_NULL_VOID(uiContent_);
    auto container = Container::GetContainer(uiContent_->GetInstanceId());
    CHECK_NULL_VOID(container);
    auto frontend = AceType::DynamicCast<OHOS::Ace::FormFrontendDeclarative>(container->GetFrontend());
    CHECK_NULL_VOID(frontend);
    auto delegate = frontend->GetDelegate();
    CHECK_NULL_VOID(delegate);
    auto pageRouterManager = delegate->GetPageRouterManager();
    CHECK_NULL_VOID(pageRouterManager);
    auto pageNode = pageRouterManager->GetCurrentPageNode();
    CHECK_NULL_VOID(pageNode);
    auto pagePattern = AceType::DynamicCast<PagePattern>(pageNode->GetPattern());
    CHECK_NULL_VOID(pagePattern);

    auto dynamicPageSizeCallback = [weak = WeakClaim(this)](SizeF size) {
        auto renderer = weak.Upgrade();
        CHECK_NULL_VOID(renderer);
        auto width = size.Width();
        auto height = size.Height();
        if (!NearEqual(renderer->contentSize_.Width(), width) || !NearEqual(renderer->contentSize_.Height(), height)) {
            renderer->contentSize_.SetSizeT(size);
            TAG_LOGI(AceLogTag::ACE_DYNAMIC_COMPONENT, "dynamic card size: width=%{public}f, height=%{public}f", width,
                height);
            auto hostTaskExecutor = renderer->GetHostTaskExecutor();
            CHECK_NULL_VOID(hostTaskExecutor);
            hostTaskExecutor->PostTask(
                [hostWeak = renderer->host_, hostInstanceId = renderer->hostInstanceId_, width, height]() {
                    ContainerScope scope(hostInstanceId);
                    auto host = hostWeak.Upgrade();
                    CHECK_NULL_VOID(host);
                    auto pattern = AceType::DynamicCast<UIExtensionPattern>(host->GetPattern());
                    CHECK_NULL_VOID(pattern);
                    pattern->OnSizeChanged(width, height);
                },
                TaskExecutor::TaskType::UI);
        }
    };
    pagePattern->SetDynamicPageSizeCallback(std::move(dynamicPageSizeCallback));
}

void DynamicComponentRendererImpl::AttachRenderContext()
{
    auto taskExecutor = GetHostTaskExecutor();
    CHECK_NULL_VOID(taskExecutor);
    taskExecutor->PostSyncTask(
        [weak = host_, hostInstanceId = hostInstanceId_, instanceId = uiContent_->GetInstanceId()]() {
            ContainerScope scope(hostInstanceId);
            auto host = weak.Upgrade();
            CHECK_NULL_VOID(host);
            auto hostRenderContext = host->GetRenderContext();
            CHECK_NULL_VOID(hostRenderContext);

            auto container = Container::GetContainer(instanceId);
            CHECK_NULL_VOID(container);
            auto pipeline = container->GetPipelineContext();
            CHECK_NULL_VOID(pipeline);
            auto pipelineContext = AceType::DynamicCast<NG::PipelineContext>(pipeline);
            CHECK_NULL_VOID(pipelineContext);
            auto rootElement = pipelineContext->GetRootElement();
            CHECK_NULL_VOID(rootElement);
            auto renderContext = rootElement->GetRenderContext();
            CHECK_NULL_VOID(renderContext);

            renderContext->SetClipToFrame(true);
            renderContext->SetClipToBounds(true);

            TAG_LOGI(AceLogTag::ACE_DYNAMIC_COMPONENT, "add render context of dynamic component for '%{public}d'",
                instanceId);
            hostRenderContext->ClearChildren();
            hostRenderContext->AddChild(renderContext, -1);

            host->MarkDirtyNode(PROPERTY_UPDATE_LAYOUT);
            auto parent = host->GetParent();
            CHECK_NULL_VOID(parent);
            parent->MarkNeedSyncRenderTree();
            parent->RebuildRenderContextTree();
            hostRenderContext->RequestNextFrame();
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

void DynamicComponentRendererImpl::UpdateViewportConfig(const ViewportConfig& config,
    Rosen::WindowSizeChangeReason reason, const std::shared_ptr<Rosen::RSTransaction>& rsTransaction)
{
    CHECK_NULL_VOID(uiContent_);

    ViewportConfig vpConfig;
    vpConfig.SetDensity(config.Density());
    vpConfig.SetPosition(config.Left(), config.Top());
    vpConfig.SetOrientation(config.Orientation());

    if (NearZero(config.Width()) && NearZero(config.Height()) && !adaptive_) {
        TAG_LOGI(AceLogTag::ACE_DYNAMIC_COMPONENT, "set adaptive size for dynamic component '%{public}d'",
            uiContent_->GetInstanceId());
        adaptive_ = true;
        int32_t deviceWidth = 0;
        int32_t deviceHeight = 0;
        auto defaultDisplay = Rosen::DisplayManager::GetInstance().GetDefaultDisplay();
        if (defaultDisplay) {
            deviceWidth = defaultDisplay->GetWidth();
            deviceHeight = defaultDisplay->GetHeight();
        }
        vpConfig.SetSize(deviceWidth, deviceHeight);
    } else {
        vpConfig.SetSize(config.Width(), config.Height());
    }

    auto taskExecutor = GetTaskExecutor();
    CHECK_NULL_VOID(taskExecutor);
    taskExecutor->PostTask(
        [weak = WeakClaim(this), vpConfig, reason, rsTransaction]() {
            auto renderer = weak.Upgrade();
            CHECK_NULL_VOID(renderer);
            CHECK_NULL_VOID(renderer->uiContent_);
            ContainerScope scope(renderer->uiContent_->GetInstanceId());
            auto width = vpConfig.Width();
            auto height = vpConfig.Height();
            renderer->uiContent_->SetFormWidth(width);
            renderer->uiContent_->SetFormHeight(height);
            renderer->uiContent_->OnFormSurfaceChange(width, height);
            renderer->uiContent_->UpdateViewportConfig(vpConfig, reason, rsTransaction);
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
            TAG_LOGI(AceLogTag::ACE_DYNAMIC_COMPONENT, "destroy dynamic UI content");
            uiContent->Destroy();
        },
        TaskExecutor::TaskType::UI);
}

RefPtr<TaskExecutor> DynamicComponentRendererImpl::GetTaskExecutor()
{
    CHECK_NULL_RETURN(uiContent_, nullptr);
    auto container = Container::GetContainer(uiContent_->GetInstanceId());
    CHECK_NULL_RETURN(container, nullptr);
    return container->GetTaskExecutor();
}

RefPtr<TaskExecutor> DynamicComponentRendererImpl::GetHostTaskExecutor()
{
    auto container = Container::GetContainer(hostInstanceId_);
    CHECK_NULL_RETURN(container, nullptr);
    return container->GetTaskExecutor();
}
} // namespace OHOS::Ace::NG
