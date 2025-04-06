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

#include "adapter/ohos/entrance/global_pipeline_context_manager.h"

#include "bridge/declarative_frontend/declarative_frontend.h"
#include "bridge/declarative_frontend/ng/declarative_frontend_ng.h"
#include "core/common/asset_manager_impl.h"
#include "core/common/task_executor_impl.h"
#include "core/common/window.h"
#include "core/components_ng/render/adapter/rosen_window.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace {
void WindowLifeCycle::AfterDestroyed()
{
    auto globalPipelineManager = GlobalPipelineContextManager::GetInstance();
    auto globalPipelineContext = globalPipelineManager->RemoveGlobalPipelineContext(name_);
    auto modalPageNode = globalPipelineManager->RemoveModalPageNode(name_);
    globalPipelineManager->RemoveSessionId(name_);
    if (modalPageNode) {
        auto parentNode = modalPageNode->GetParent();
        if (parentNode) {
            parentNode->RemoveChild(modalPageNode);
        }
        modalPageNode->MountToParent(globalPipelineContext->GetRootElement());
    }
    CHECK_NULL_VOID(globalPipelineContext);
    globalPipelineContext->Destroy();
    globalPipelineContext.Reset();
}

GlobalPipelineContextManager* GlobalPipelineContextManager::GetInstance()
{
    static GlobalPipelineContextManager instance;
    return &instance;
}

RefPtr<NG::PipelineContext> GlobalPipelineContextManager::GetGlobalPipelineContext(const std::string& name) const
{
    auto iter = globalContextMap_.find(name);
    if (iter == globalContextMap_.end()) {
        return nullptr;
    }
    return iter->second;
}

RefPtr<NG::PipelineContext> GlobalPipelineContextManager::CreateGlobalPipelineContext(
    const std::string& name, const sptr<OHOS::Rosen::Window>& rsWindow, FrontendType frontendType, int32_t instanceId)
{
    // taskExecutor
    auto taskExecutor = Referenced::MakeRefPtr<TaskExecutorImpl>();
    taskExecutor->InitPlatformThread(true); // useCurrentEventRunner true: 复用taskExecutor
    taskExecutor->InitOtherThreads(threadModelImpl_.get());
    if (frontendType != FrontendType::DECLARATIVE_JS && frontendType != FrontendType::ETS_CARD) {
        taskExecutor->InitJsThread();
    }

    // assetManager
    auto assetManagerImpl = Referenced::MakeRefPtr<AssetManagerImpl>();

    // frontend
#ifdef NG_BUILD
    auto frontend = AceType::MakeRefPtr<DeclarativeFrontendNG>();
    auto declarativeFrontend = AceType::DynamicCast<DeclarativeFrontendNG>(frontend);
#else
    auto frontend = AceType::MakeRefPtr<DeclarativeFrontend>();
    auto declarativeFrontend = AceType::DynamicCast<DeclarativeFrontend>(frontend);
#endif

    auto window = std::make_shared<NG::RosenWindow>(rsWindow, taskExecutor, instanceId);
    auto pipelineContext =
        AceType::MakeRefPtr<NG::PipelineContext>(window, taskExecutor, assetManagerImpl, nullptr, frontend, instanceId);
    AddGlobalPipelineContext(name, pipelineContext);

    auto windowLifeCycle = sptr<WindowLifeCycle>::MakeSptr(name);
    rsWindow->RegisterLifeCycleListener(windowLifeCycle);

    return pipelineContext;
}

void GlobalPipelineContextManager::AddGlobalPipelineContext(
    const std::string& name, const RefPtr<NG::PipelineContext>& pipelineContext)
{
    auto iter = globalContextMap_.find(name);
    if (iter != globalContextMap_.end()) {
        LOGW("There already exists a global Pipeline Context with the same name!");
        iter->second = pipelineContext;
        return;
    }
    globalContextMap_.emplace(name, pipelineContext);
}

RefPtr<NG::PipelineContext> GlobalPipelineContextManager::RemoveGlobalPipelineContext(const std::string& name)
{
    auto iter = globalContextMap_.find(name);
    if (iter == globalContextMap_.end()) {
        return nullptr;
    }
    auto pipeline = iter->second;
    globalContextMap_.erase(name);
    return pipeline;
}

RefPtr<NG::FrameNode> GlobalPipelineContextManager::RemoveModalPageNode(const std::string& name)
{
    auto iter = modalPageMap_.find(name);
    if (iter == modalPageMap_.end()) {
        return nullptr;
    }
    auto modalPage = iter->second;
    modalPageMap_.erase(name);
    return modalPage;
}

RefPtr<NG::FrameNode> GlobalPipelineContextManager::GetModalPageNode(const std::string& name)
{
    auto iter = modalPageMap_.find(name);
    if (iter == modalPageMap_.end()) {
        return nullptr;
    }
    return iter->second;
}

void GlobalPipelineContextManager::ProcessModalPageNode(const std::string& name, int32_t instanceId)
{
    auto globalPipelineContext = GetGlobalPipelineContext(name);
    auto pipelineContext = NG::PipelineContext::GetContextByContainerId(instanceId);
    if (!globalPipelineContext || !pipelineContext) {
        LOGE("ProcessModalPageNode globalPipelineContext or pipelineContext invalid %{public}d", instanceId);
        return;
    }
    if (modalPageMap_.find(name) == modalPageMap_.end()) {
        auto globalOverlayManager = globalPipelineContext->GetOverlayManager();
        CHECK_NULL_VOID(globalOverlayManager);
        auto modalPageNode = globalOverlayManager->GetModalStackTop();
        CHECK_NULL_VOID(modalPageNode);
        auto globalParent = modalPageNode->GetParent();
        if (globalParent) {
            globalParent->RemoveChild(modalPageNode);
            globalParent->RebuildRenderContextTree();
        }
        modalPageMap_.emplace(name, modalPageNode);
    }
    auto rootNode = pipelineContext->GetRootElement();
    CHECK_NULL_VOID(rootNode);
    auto modalPageNode = modalPageMap_[name];
    CHECK_NULL_VOID(modalPageNode);
    modalPageNode->MountToParent(rootNode);
    rootNode->RebuildRenderContextTree();
    rootNode->MarkDirtyNode(NG::PROPERTY_UPDATE_MEASURE);
}

void GlobalPipelineContextManager::RegisterSessionId(const std::string& name, int32_t sessionId)
{
    auto iter = sessionIdMap_.find(name);
    if (iter != sessionIdMap_.end()) {
        LOGW("The sessionId %{public}d with the name %{public}s already exists", sessionId, name.c_str());
        return;
    }
    sessionIdMap_.emplace(name, sessionId);
}

std::string GlobalPipelineContextManager::GetUecNameBySessionId(int32_t sessionId)
{
    for (const auto& pair : sessionIdMap_) {
        if (pair.second == sessionId) {
            return pair.first;
        }
    }
    LOGW("The sessionId %{public}d does not exist", sessionId);
    return "";
}

int32_t GlobalPipelineContextManager::GetSessionId(const std::string& name)
{
    auto iter = sessionIdMap_.find(name);
    if (iter == sessionIdMap_.end()) {
        LOGW("The sessionId with the name %{public}s does not exist", name.c_str());
        return 0;
    }
    return iter->second;
}

void GlobalPipelineContextManager::RemoveSessionId(const std::string& name)
{
    auto iter = sessionIdMap_.find(name);
    if (iter == sessionIdMap_.end()) {
        return;
    }
    sessionIdMap_.erase(name);
}

GlobalPipelineContextManager::GlobalPipelineContextManager()
{
    threadModelImpl_ = ThreadModelImpl::CreateThreadModel(false, false, !SystemProperties::GetRosenBackendEnabled());
}
} // namespace OHOS::Ace
