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

#ifndef FOUNDATION_ACE_FRAMEWORKS_BRIDGE_PA_BACKEND_BACKEND_DELEGATE_IMPL_H
#define FOUNDATION_ACE_FRAMEWORKS_BRIDGE_PA_BACKEND_BACKEND_DELEGATE_IMPL_H

#include <future>
#include <mutex>
#include <unordered_map>

#include "base/memory/ace_type.h"
#include "base/thread/cancelable_callback.h"
#include "core/common/js_message_dispatcher.h"
#include "core/pipeline/pipeline_context.h"
#include "core/common/backend.h"
#include "frameworks/bridge/common/accessibility/accessibility_node_manager.h"
#if !defined(WINDOWS_PLATFORM) and !defined(MAC_PLATFORM)
#include "frameworks/bridge/common/accessibility/js_accessibility_manager.h"
#else
#include "frameworks/bridge/common/inspector/js_inspector_manager.h"
#endif
#include "frameworks/bridge/common/manifest/manifest_parser.h"
#include "frameworks/bridge/pa_backend/backend_delegate.h"

namespace OHOS::Ace::Framework {
using LoadJsCallback = std::function<void(const std::string&)>;
using JsMessageDispatcherSetterCallback = std::function<void(const RefPtr<JsMessageDispatcher>&)>;
using EventCallback = std::function<void(const std::string &, const std::string &)>;
using DestroyApplicationCallback = std::function<void(const std::string &packageName)>;

struct BackendDelegateImplBuilder {
    RefPtr<TaskExecutor> taskExecutor;
    LoadJsCallback loadCallback;
    EventCallback asyncEventCallback;
    EventCallback syncEventCallback;
    JsMessageDispatcherSetterCallback transferCallback;
    DestroyApplicationCallback destroyApplicationCallback;
    void* ability;
    BackendType type;
};

class BackendDelegateImpl : public BackendDelegate {
    DECLARE_ACE_TYPE(BackendDelegateImpl, BackendDelegate);

public:
    explicit BackendDelegateImpl(const BackendDelegateImplBuilder& builder);
    ~BackendDelegateImpl() override = default;

    void SetAssetManager(const RefPtr<AssetManager>& assetManager);

    // JsBackend delegate functions.
    void RunPa(const std::string &url, const std::string &params);
    void SetJsMessageDispatcher(const RefPtr<JsMessageDispatcher>& dispatcher) const;

    // BackendDelegate overrides.
    void PostJsTask(std::function<void()>&& task) override;

    RefPtr<PipelineContext> GetPipelineContext();

    SingleTaskExecutor GetAnimationJsTask() override;

    void AddTaskObserver(std::function<void()> &&task) override;
    void RemoveTaskObserver() override;

    void* GetAbility() override
    {
        return ability_;
    }

    BackendType GetType() override
    {
        return type_;
    }

    bool GetAssetContent(const std::string &url, std::string &content) override;
    bool GetAssetContent(const std::string &url, std::vector<uint8_t> &content) override;

    // JsEventHandler delegate functions.
    void FireAsyncEvent(const std::string &eventId, const std::string &param, const std::string &jsonArgs);
    bool FireSyncEvent(const std::string &eventId, const std::string &param, const std::string &jsonArgs);
    void FireSyncEvent(
        const std::string &eventId, const std::string &param, const std::string &jsonArgs, std::string &result);

    // special JsEventHandler
    void OnApplicationDestroy(const std::string &packageName);

private:
    void LoadPa(const std::string &url, const std::string &params);

    void ParseManifest();

    std::atomic<uint64_t> pageIdPool_ = 0;
    int32_t callbackCnt_ = 0;
    bool isRouteStackFull_ = false;
    bool isStagingPageExist_ = false;
    std::unordered_map<int32_t, std::string> jsCallBackResult_;

    LoadJsCallback loadJs_;
    JsMessageDispatcherSetterCallback dispatcherCallback_;

    EventCallback asyncEvent_;
    EventCallback syncEvent_;

    DestroyApplicationCallback destroyApplication_;

    RefPtr<Framework::ManifestParser> manifestParser_;
    void* ability_;
    BackendType type_ = BackendType::SERVICE;

    RefPtr<TaskExecutor> taskExecutor_;
    RefPtr<AssetManager> assetManager_;

    mutable std::mutex mutex_;
    mutable std::once_flag onceFlag_;

    std::mutex LoadPaMutex_;
    std::condition_variable condition_;
};
} // namespace OHOS::Ace::Framework
#endif // FOUNDATION_ACE_FRAMEWORKS_BRIDGE_PA_BACKEND_BACKEND_DELEGATE_IMPL_H
