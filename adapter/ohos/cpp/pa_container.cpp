/*
 * Copyright (c) 2021 Huawei Device Co., Ltd.
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

#include "adapter/common/cpp/file_asset_provider.h"
#include "adapter/ohos/cpp/ace_application_info.h"
#include "adapter/ohos/cpp/pa_container.h"
#include "base/log/ace_trace.h"
#include "base/log/event_report.h"
#include "base/log/log.h"
#include "base/utils/system_properties.h"
#include "base/utils/utils.h"
#include "base/watch_dog/watch_dog.h"
#include "core/common/ace_engine.h"
#include "core/common/platform_window.h"
#include "core/common/text_field_manager.h"
#include "core/common/window.h"

#include "frameworks/bridge/pa_backend/engine/common/js_backend_engine_loader.h"
#include "frameworks/bridge/pa_backend/pa_backend.h"

#include "flutter/lib/ui/ui_dart_state.h"

#include "adapter/common/cpp/flutter_asset_manager.h"
#include "adapter/common/cpp/flutter_task_executor.h"

namespace OHOS::Ace::Platform {
PaContainer::PaContainer(int32_t instanceId, BackendType type, void* paAbility,
    std::unique_ptr<PlatformEventCallback> callback) : instanceId_(instanceId), type_(type),
    paAbility_(paAbility)
{
    ACE_DCHECK(callback);
    auto flutterTaskExecutor = Referenced::MakeRefPtr<FlutterTaskExecutor>();
    flutterTaskExecutor->InitPlatformThread();
    flutterTaskExecutor->InitJsThread();
    taskExecutor_ = flutterTaskExecutor;

    InitializeBackend();

    platformEventCallback_ = std::move(callback);
}

void PaContainer::InitializeBackend()
{
    // create backend
    backend_ = Backend::Create();
    auto paBackend = AceType::DynamicCast<PaBackend>(backend_);

    // set JS engine，init in JS thread
    paBackend->SetJsEngine(Framework::JsBackendEngineLoader::Get().CreateJsBackendEngine(instanceId_));
    paBackend->SetAbility(paAbility_);

    ACE_DCHECK(backend_);
    backend_->Initialize(type_, taskExecutor_);
}

RefPtr<PaContainer> PaContainer::GetContainer(int32_t instanceId)
{
    auto container = AceEngine::Get().GetContainer(instanceId);
    if (container != nullptr) {
        auto aceContainer = AceType::DynamicCast<PaContainer>(container);
        return aceContainer;
    } else {
        return nullptr;
    }
}

void PaContainer::CreateContainer(int32_t instanceId, BackendType type, void* paAbility,
    std::unique_ptr<PlatformEventCallback> callback)
{
    auto aceContainer = AceType::MakeRefPtr<PaContainer>(instanceId, type, paAbility,
        std::move(callback));
    AceEngine::Get().AddContainer(instanceId, aceContainer);

    auto back = aceContainer->GetBackend();
    if (back) {
        back->UpdateState(Backend::State::ON_CREATE);
        back->SetJsMessageDispatcher(aceContainer);
    }
}

bool PaContainer::RunPa(int32_t instanceId, const std::string &content, const std::string &params)
{
    auto container = AceEngine::Get().GetContainer(instanceId);
    if (!container) {
        return false;
    }
    auto aceContainer = AceType::DynamicCast<PaContainer>(container);
    auto back = aceContainer->GetBackend();
    if (back) {
        auto paBackend = AceType::DynamicCast<PaBackend>(back);
        paBackend->RunPa(content, params);
        return true;
    }
    return false;
}

void PaContainer::DestroyContainer(int32_t instanceId)
{
    LOGI("DestroyContainer with id %{private}d", instanceId);
    auto container = AceEngine::Get().GetContainer(instanceId);
    if (!container) {
        LOGE("no AceContainer with id %{private}d", instanceId);
        return;
    }
    auto aceContainer = AceType::DynamicCast<PaContainer>(container);
    auto back = aceContainer->GetBackend();
    if (back) {
        back->UpdateState(Backend::State::ON_DESTROY);
    }
    return;
}

void PaContainer::AddAssetPath(
    int32_t instanceId, const std::string &packagePath, const std::vector<std::string> &paths)
{
    auto container = AceType::DynamicCast<PaContainer>(AceEngine::Get().GetContainer(instanceId));
    if (!container) {
        return;
    }

    AceEngine::Get().SetPackagePath(packagePath);
    for (auto path : paths) {
        AceEngine::Get().SetAssetBasePath(path);
    }

    RefPtr<FlutterAssetManager> flutterAssetManager;
    if (container->assetManager_) {
        flutterAssetManager = AceType::DynamicCast<FlutterAssetManager>(container->assetManager_);
    } else {
        flutterAssetManager = Referenced::MakeRefPtr<FlutterAssetManager>();
        container->assetManager_ = flutterAssetManager;
        AceType::DynamicCast<PaBackend>(container->GetBackend())->SetAssetManager(flutterAssetManager);
    }
    if (flutterAssetManager && !packagePath.empty()) {
        auto assetProvider = std::make_unique<FileAssetProvider>();
        if (assetProvider->Initialize(packagePath, paths)) {
            LOGI("Push AssetProvider to queue.");
            flutterAssetManager->PushBack(std::move(assetProvider));
        }
    }
}

void PaContainer::Dispatch(
    const std::string& group, std::vector<uint8_t>&& data, int32_t id, bool replyToComponent) const
{
    return;
}

void PaContainer::DispatchPluginError(int32_t callbackId, int32_t errorCode, std::string&& errorMessage) const
{
    return;
}

bool PaContainer::Dump(const std::vector<std::string> &params)
{
    return false;
}
} // namespace OHOS::Ace::Platform
