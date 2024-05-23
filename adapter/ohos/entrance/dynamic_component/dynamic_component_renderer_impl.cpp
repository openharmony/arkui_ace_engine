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

#include "adapter/ohos/entrance/ace_container.h"
#include "adapter/ohos/entrance/dynamic_component/uv_task_wrapper_impl.h"
#include "adapter/ohos/entrance/ui_content_impl.h"
#include "base/thread/task_executor.h"
#include "base/utils/utils.h"
#include "bridge/card_frontend/form_frontend_declarative.h"
#include "core/common/container.h"
#include "core/common/container_scope.h"
#include "core/components_ng/pattern/stage/page_pattern.h"
#include "core/components_ng/pattern/ui_extension/isolated_pattern.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {
namespace {
constexpr int32_t WORKER_ERROR = 10002;
constexpr char PARAM_NAME_RESTRICTED_WORKER_ERROR[] = "restrictedWorkerError";
constexpr char PARAM_MSG_RESTRICTED_WORKER_ERROR[] = "Run not in restricted worker thread";
}
DynamicComponentRendererImpl::DynamicComponentRendererImpl(
    const RefPtr<FrameNode>& host, const std::string& hapPath,
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
        TAG_LOGW(AceLogTag::ACE_ISOLATED_COMPONENT,
            "DynamicComponent should run in restricted worker thread");
        FireOnErrorCallback(
            WORKER_ERROR, PARAM_NAME_RESTRICTED_WORKER_ERROR, PARAM_MSG_RESTRICTED_WORKER_ERROR);
        return;
    }

    auto napiEnv = reinterpret_cast<napi_env>(runtime_);
    auto uvTaskWrapper = std::make_shared<UVTaskWrapperImpl>(napiEnv);
    uvTaskWrapper->Call([weak = WeakClaim(this)]() {
        auto renderer = weak.Upgrade();
        CHECK_NULL_VOID(renderer);
        renderer->InitUiContent();
    });
}

void DynamicComponentRendererImpl::InitUiContent()
{
    rendererDumpInfo_.ReSet();
    // create UI Content
    TAG_LOGI(AceLogTag::ACE_ISOLATED_COMPONENT, "create dynamic UI Content");
    uiContent_ = UIContent::Create(nullptr, runtime_, true);
    CHECK_NULL_VOID(uiContent_);
    rendererDumpInfo_.createUiContenTime = GetCurrentTimestamp();

    uiContent_->InitializeDynamic(hapPath_, abcPath_, entryPoint_);
    ContainerScope scope(uiContent_->GetInstanceId());
    RegisterErrorEventHandler();
    RegisterSizeChangedCallback();
    RegisterConfigChangedCallback();
    AttachRenderContext();
    rendererDumpInfo_.limitedWorkerInitTime = GetCurrentTimestamp();
    TAG_LOGI(AceLogTag::ACE_ISOLATED_COMPONENT, "foreground dynamic UI content");
    uiContent_->Foreground();
    std::function<void()> contentReadyCallback;
    {
        std::lock_guard<std::mutex> lock(contentReadyMutex_);
        contentReady_ = true;
        if (contentReadyCallback_) {
            contentReadyCallback = std::move(contentReadyCallback_);
        }
    }
    if (contentReadyCallback) {
        contentReadyCallback();
    }
    rendererDumpInfo_.loadAbcTime = GetCurrentTimestamp();
}

void DynamicComponentRendererImpl::RegisterErrorEventHandler()
{
    CHECK_NULL_VOID(uiContent_);
    auto errorEventHandler = [weak = WeakClaim(this)](const std::string& code, const std::string& msg) {
        auto renderer = weak.Upgrade();
        if (renderer) {
            renderer->FireOnErrorCallback(WORKER_ERROR, code, msg);
        }
    };
    uiContent_->SetErrorEventHandler(errorEventHandler);
}

void DynamicComponentRendererImpl::FireOnErrorCallback(
    int32_t code, const std::string& name, const std::string& msg)
{
    auto isolatedHost = host_.Upgrade();
    CHECK_NULL_VOID(isolatedHost);
    auto pattern = AceType::DynamicCast<IsolatedPattern>(isolatedHost->GetPattern());
    CHECK_NULL_VOID(pattern);
    pattern->FireOnErrorCallbackOnUI(code, name, msg);
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
        TAG_LOGD(AceLogTag::ACE_ISOLATED_COMPONENT, "page size callback: wh(%{public}f,%{public}f)", width, height);
        if (!NearEqual(renderer->contentSize_.Width(), width) || !NearEqual(renderer->contentSize_.Height(), height)) {
            renderer->contentSize_.SetSizeT(size);
            TAG_LOGI(AceLogTag::ACE_ISOLATED_COMPONENT, "dynamic card size: wh(%{public}f,%{public}f)", width, height);
            auto hostTaskExecutor = renderer->GetHostTaskExecutor();
            CHECK_NULL_VOID(hostTaskExecutor);
            hostTaskExecutor->PostTask(
                [hostWeak = renderer->host_, hostInstanceId = renderer->hostInstanceId_, width, height]() {
                    ContainerScope scope(hostInstanceId);
                    auto host = hostWeak.Upgrade();
                    CHECK_NULL_VOID(host);
                    auto pattern = AceType::DynamicCast<IsolatedPattern>(host->GetPattern());
                    CHECK_NULL_VOID(pattern);
                    pattern->OnSizeChanged(width, height);
                },
                TaskExecutor::TaskType::UI, "ArkUIDynamicComponentSizeChanged");
        }
    };
    pagePattern->SetDynamicPageSizeCallback(std::move(dynamicPageSizeCallback));
}

RefPtr<Platform::AceContainer> DynamicComponentRendererImpl::GetAceConainer(int32_t instanceId)
{
    auto container = Container::GetContainer(instanceId);
    CHECK_NULL_RETURN(container, nullptr);
    return DynamicCast<Platform::AceContainer>(container);
}

void DynamicComponentRendererImpl::RegisterConfigChangedCallback()
{
    auto hostExecutor = GetHostTaskExecutor();
    CHECK_NULL_VOID(hostExecutor);
    hostExecutor->PostTask(
        [hostInstanceId = hostInstanceId_, subInstanceId = uiContent_->GetInstanceId()]() {
            auto configChangedCallback = [subInstanceId](
                                             const Platform::ParsedConfig& config, const std::string& configuration) {
                auto subContainer = Container::GetContainer(subInstanceId);
                CHECK_NULL_VOID(subContainer);
                subContainer->GetTaskExecutor()->PostTask(
                    [subInstanceId, config, configuration]() {
                        auto subContainer = GetAceConainer(subInstanceId);
                        CHECK_NULL_VOID(subContainer);
                        ContainerScope scope(subInstanceId);
                        subContainer->UpdateConfiguration(config, configuration);
                    },
                    TaskExecutor::TaskType::UI, "ArkUIDynamicComponentConfigurationChanged");
            };

            auto hostContainer = GetAceConainer(hostInstanceId);
            CHECK_NULL_VOID(hostContainer);
            hostContainer->AddOnConfigurationChange(subInstanceId, configChangedCallback);
        },
        TaskExecutor::TaskType::UI, "ArkUIDynamicComponentConfigurationChanged");
}

void DynamicComponentRendererImpl::UnRegisterConfigChangedCallback()
{
    auto container = Container::GetContainer(hostInstanceId_);
    CHECK_NULL_VOID(container);
    auto aceContainer = DynamicCast<Platform::AceContainer>(container);
    CHECK_NULL_VOID(aceContainer);
    aceContainer->RemoveOnConfigurationChange(uiContent_->GetInstanceId());
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

            pipeline->SetAppBgColor(Color::TRANSPARENT);
            renderContext->SetClipToFrame(true);
            renderContext->SetClipToBounds(true);

            TAG_LOGI(AceLogTag::ACE_ISOLATED_COMPONENT, "add render context of dynamic component for '%{public}d'",
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
        TaskExecutor::TaskType::UI, "ArkUIDynamicComponentAttachRenderContext");
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
        TaskExecutor::TaskType::UI, "ArkUIDynamicComponentProcessPointer");
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
        TaskExecutor::TaskType::UI, "ArkUIDynamicComponentProcessKey");
}

void DynamicComponentRendererImpl::UpdateViewportConfig(const ViewportConfig& config,
    Rosen::WindowSizeChangeReason reason, const std::shared_ptr<Rosen::RSTransaction>& rsTransaction)
{
    CHECK_NULL_VOID(uiContent_);
    int32_t width = config.Width();
    int32_t height = config.Height();
    contentSize_.SetWidth(width);
    contentSize_.SetHeight(height);
    if (width == 0 || height == 0) {
        auto defaultDisplay = Rosen::DisplayManager::GetInstance().GetDefaultDisplay();
        if (defaultDisplay) {
            if (width == 0) {
                width = defaultDisplay->GetWidth();
            }
            if (height == 0) {
                height = defaultDisplay->GetHeight();
            }
            TAG_LOGI(AceLogTag::ACE_ISOLATED_COMPONENT, "set adaptive size (%{public}d, %{public}d) for DC(%{public}d)",
                width, height, uiContent_->GetInstanceId());
        }
    }
    ViewportConfig vpConfig(width, height, config.Density());
    vpConfig.SetPosition(config.Left(), config.Top());
    vpConfig.SetOrientation(config.Orientation());

    auto task = [weak = WeakClaim(this), vpConfig, reason, rsTransaction]() {
        auto renderer = weak.Upgrade();
        CHECK_NULL_VOID(renderer);
        auto uiContent = renderer->uiContent_;
        CHECK_NULL_VOID(uiContent);
        ContainerScope scope(uiContent->GetInstanceId());
        auto width = vpConfig.Width();
        auto height = vpConfig.Height();
        uiContent->SetFormWidth(width);
        uiContent->SetFormHeight(height);
        uiContent->OnFormSurfaceChange(width, height);
        uiContent->UpdateViewportConfig(vpConfig, reason, rsTransaction);
    };
    bool contentReady = false;
    {
        std::lock_guard<std::mutex> lock(contentReadyMutex_);
        contentReady = contentReady_;
        if (!contentReady) {
            contentReadyCallback_ = std::move(task);
        }
    }
    if (contentReady) {
        auto taskExecutor = GetTaskExecutor();
        CHECK_NULL_VOID(taskExecutor);
        taskExecutor->PostTask(
            std::move(task), TaskExecutor::TaskType::UI, "ArkUIDynamicComponentUpdateViewportConfig");
    }
}

void DynamicComponentRendererImpl::DestroyContent()
{
    UnRegisterConfigChangedCallback();
    auto taskExecutor = GetTaskExecutor();
    CHECK_NULL_VOID(taskExecutor);
    taskExecutor->PostTask(
        [uiContent = uiContent_]() {
            ContainerScope scope(uiContent->GetInstanceId());
            TAG_LOGI(AceLogTag::ACE_ISOLATED_COMPONENT, "destroy dynamic UI content");
            uiContent->Destroy();
        },
        TaskExecutor::TaskType::UI, "ArkUIDynamicComponentDestroy");
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

void DynamicComponentRendererImpl::Dump(RendererDumpInfo &rendererDumpInfo)
{
    rendererDumpInfo = rendererDumpInfo_;
}
} // namespace OHOS::Ace::NG
