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

#ifndef FOUNDATION_ACE_FRAMEWORKS_BRIDGE_ARKTS_FRONTEND_ARKTS_FRONTEND_H
#define FOUNDATION_ACE_FRAMEWORKS_BRIDGE_ARKTS_FRONTEND_ARKTS_FRONTEND_H

#include <set>
#include <string>
#include <unordered_map>

#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"
#include "base/thread/task_executor.h"
#include "base/utils/noncopyable.h"
#include "core/common/frontend.h"
#include "core/components_ng/base/frame_node.h"
#include "core/pipeline_ng/pipeline_context.h"
#include "frameworks/bridge/common/accessibility/accessibility_node_manager.h"
#include "frameworks/bridge/common/media_query/media_query_info.h"
#include "frameworks/bridge/declarative_frontend/ng/page_router_manager.h"
#include "frameworks/bridge/declarative_frontend/ng/page_router_manager_factory.h"

typedef struct __ani_env ani_env;
typedef class __ani_ref* ani_ref;
typedef class __ani_object* ani_object;
typedef struct __ani_vm ani_vm;
typedef struct __ani_method* ani_method;

namespace OHOS::Ace {
enum class ArkolaMessageType : int32_t {
    DELETE_DETACHED_ROOT = 1,                // destroyUiDetachedRoot
};

using InspectorFunc = std::function<void()>;
using MediaQueryCallback = std::function<void(const std::string& callbackId, const std::string& args)>;
class InspectorEvent : public virtual AceType {
    DECLARE_ACE_TYPE(InspectorEvent, AceType)
public:
    explicit InspectorEvent(InspectorFunc&& callback) : callback_(std::move(callback)) {}
    ~InspectorEvent() override = default;

    void operator()() const
    {
        if (callback_) {
            callback_();
        }
    }
    
private:
    InspectorFunc callback_;
};
/**
 * @brief Proxy class to interact with Koala frontend and static ArkTS runtime.
 *
 */
class ACE_FORCE_EXPORT ArktsFrontend : public Frontend {
    DECLARE_ACE_TYPE(ArktsFrontend, Frontend);

public:
    explicit ArktsFrontend(void* runtime);
    ~ArktsFrontend() override = default;

    void SetMediaQueryCallback(MediaQueryCallback&& mediaQueryCallback)
    {
        mediaQueryCallbacks_ = mediaQueryCallback;
    }
    bool Initialize(FrontendType type, const RefPtr<TaskExecutor>& taskExecutor) override;

    void Destroy() override;

    void AttachPipelineContext(const RefPtr<PipelineBase>& context) override;
    void AttachSubPipelineContext(const RefPtr<PipelineBase>& context) override;

    void SetAssetManager(const RefPtr<AssetManager>& assetManager) override {}

    UIContentErrorCode RunPage(const std::string& url, const std::string& params) override;
    UIContentErrorCode RunPage(
        const std::shared_ptr<std::vector<uint8_t>>& content, const std::string& params) override;

    UIContentErrorCode RunPageByNamedRouter(const std::string& name, const std::string& params) override
    {
        return UIContentErrorCode::NO_ERRORS;
    }

    void ReplacePage(const std::string& url, const std::string& params) override {}

    void PushPage(const std::string& url, const std::string& params) override {}

    void AddPage(const RefPtr<AcePage>& page) override {}

    void* PushExtender(const std::string& url, const std::string& params, bool recoverable,
        std::function<void()>&& finishCallback, void* jsNode) override;
    void PushNamedRouteExtender(
        const PageRouterOptions& options, std::function<void()>&& finishCallback, void* jsNode) override;
    void* ReplaceExtender(const std::string& url, const std::string& params, bool recoverable,
        std::function<void()>&& enterFinishCallback, void* jsNode) override;
    void ReplaceNamedRouteExtender(
        const PageRouterOptions& options, std::function<void()>&& finishCallback, void* jsNode) override;
    void* RunPageExtender(const std::string& url, const std::string& params, bool recoverable,
        std::function<void()>&& finishCallback, void* jsNode) override;
    void BackExtender(const std::string& url, const std::string& params) override;
    void ClearExtender() override;
    void ShowAlertBeforeBackPageExtender(const std::string& url) override;
    void HideAlertBeforeBackPageExtender() override;

    void* CreateDynamicExtender(const std::string& url, bool recoverable) override;
    void* PushDynamicExtender(const std::string& url, const std::string& params, bool recoverable,
        std::function<void()>&& finishCallback, void* pageNode) override;
    void* ReplaceDynamicExtender(const std::string& url, const std::string& params, bool recoverable,
        std::function<void()>&& finishCallback, void* pageNode) override;

    void PushFromDynamicExtender(const std::string& url, const std::string& params, bool recoverable,
        const std::function<void(const std::string&, int32_t)>& callback, uint32_t routerMode) override;
    void ReplaceFromDynamicExtender(const std::string& url, const std::string& params, bool recoverable,
        const std::function<void(const std::string&, int32_t)>& callback, uint32_t routerMode) override;
    void BackFromDynamicExtender(const std::string& url, const std::string& params) override;
    void ClearFromDynamicExtender() override;
    int32_t GetLengthFromDynamicExtender() override;
    std::string GetParamsFromDynamicExtender() override;
    bool GetStateByUrlFromDynamicExtender(const std::string& url, std::vector<RouterStateInfo>& stateArray) override;
    bool GetStateByIndexFromDynamicExtender(int32_t index, RouterStateInfo& state) override;
    bool GetStateFromDynamicExtender(RouterStateInfo& state) override;
    int32_t GetCurrentPageIndex() const override;

    RefPtr<AcePage> GetPage(int32_t /*pageId*/) const override
    {
        return nullptr;
    }

    std::string GetCurrentPageUrl() const override
    {
        return "";
    }

    RefPtr<Framework::RevSourceMap> GetCurrentPageSourceMap() const override
    {
        return nullptr;
    }

    RefPtr<Framework::RevSourceMap> GetFaAppSourceMap() const override
    {
        return nullptr;
    }

    void GetStageSourceMap(std::unordered_map<std::string, RefPtr<Framework::RevSourceMap>>& sourceMap) const override
    {}

    void SendCallbackMessage(const std::string& callbackId, const std::string& data) const override {}
    void SetJsMessageDispatcher(const RefPtr<JsMessageDispatcher>& dispatcher) const override {}
    void TransferComponentResponseData(int32_t callbackId, int32_t code, std::vector<uint8_t>&& data) const override {}
    void TransferJsResponseData(int32_t callbackId, int32_t code, std::vector<uint8_t>&& data) const override {}
    void TransferJsPluginGetError(int32_t callbackId, int32_t errorCode, std::string&& errorMessage) const override {}
    void TransferJsEventData(int32_t callbackId, int32_t code, std::vector<uint8_t>&& data) const override {}
    void LoadPluginJsCode(std::string&& jsCode) const override {}
    void LoadPluginJsByteCode(std::vector<uint8_t>&& jsCode, std::vector<int32_t>&& jsCodeLen) const override {}

    void UpdateState(Frontend::State state) override {}

    bool OnBackPressed() override;
    void OnShow() override;
    void OnHide() override;
    void OnConfigurationUpdated(const std::string& data) override {
        OnMediaQueryUpdate();
    }
    void OnSaveAbilityState(std::string& data) override {}
    void OnRestoreAbilityState(const std::string& data) override {}
    void OnNewWant(const std::string& data) override {}
    void OnActive() override {}
    void OnInactive() override {}
    bool OnStartContinuation() override
    {
        return false;
    }
    void OnCompleteContinuation(int32_t code) override {}
    void OnSaveData(std::string& data) override {}
    void GetPluginsUsed(std::string& data) override {}
    bool OnRestoreData(const std::string& data) override
    {
        return false;
    }
    void OnRemoteTerminated() override {}
    void OnNewRequest(const std::string& data) override {}
    void OnMemoryLevel(const int32_t level) override {}
    void CallRouterBack() override {}
    void OnSurfaceChanged(int32_t width, int32_t height) override {
        if (mediaQueryInfo_->GetIsInit()) {
            mediaQueryInfo_->SetIsInit(false);
        }
        mediaQueryInfo_->EnsureListenerIdValid();
        OnMediaQueryUpdate(true);
    }
    void OnMediaQueryUpdate(bool isSynchronous = false)
    {
        auto containerId = Container::CurrentIdSafely();
        bool isInSubwindow = containerId >= 1000000;
        if (isInSubwindow) {
            return;
        }
        if (mediaQueryInfo_->GetIsInit()) {
            return;
        }

        auto callback = [weak = AceType::WeakClaim(this)] {
            auto frontend = weak.Upgrade();
            if (!frontend) {
                return;
            }
            const auto& info = frontend->mediaQueryInfo_->GetMediaQueryInfo();
            const auto& listenerId = frontend->mediaQueryInfo_->GetListenerId();
            frontend->mediaQueryCallbacks_(listenerId, info);
            frontend->mediaQueryInfo_->ResetListenerId();
        };
        auto container = Container::Current();
        if (container && container->IsUseStageModel() && isSynchronous) {
            callback();
            return;
        }
        taskExecutor_->PostTask(callback, TaskExecutor::TaskType::JS, "ArkUIMediaQueryUpdate");
    }
    
    void OnLayoutCompleted(const std::string& componentId) override
    {
        auto iter = layoutCallbacks_.find(componentId);
        if (iter == layoutCallbacks_.end()) {
            return;
        }
        if (taskExecutor_ == nullptr) {
            return;
        }
        auto&& observer = iter->second;
        taskExecutor_->PostTask(
            [observer] {
                (*observer)();
            }, TaskExecutor::TaskType::JS, "ArkUILayoutCompleted"
        );
    }

    void OnDrawCompleted(const std::string& componentId) override
    {
        auto iter = drawCallbacks_.find(componentId);
        if (iter == drawCallbacks_.end()) {
            return;
        }
        if (taskExecutor_ == nullptr) {
            return;
        }
        auto&& observer = iter->second;
        taskExecutor_->PostTask(
            [observer] {
                (*observer)();
            }, TaskExecutor::TaskType::JS, "ArkUIDrawCompleted"
        );
    }

    void OnDrawChildrenCompleted(const std::string& componentId) override
    {
        auto iter = drawChildrenCallbacks_.find(componentId);
        if (iter == drawChildrenCallbacks_.end()) {
            return;
        }
        if (taskExecutor_ == nullptr) {
            return;
        }
        auto&& observer = iter->second;
        taskExecutor_->PostTask(
            [observer] {
                (*observer)();
            }, TaskExecutor::TaskType::JS, "ArkUIDrawChildrenCompleted"
        );
    }

    void DumpFrontend() const override {}
    std::string GetPagePath() const override
    {
        return "";
    }
    void TriggerGarbageCollection() override {}
    void DumpHeapSnapshot(bool isPrivate) override {}
    void NotifyUIIdle() override {}
    void SetColorMode(ColorMode colorMode) override {}
    void RebuildAllPages() override {}
    void NotifyAppStorage(const std::string& key, const std::string& value) override {}
    bool HandleMessage(void* frameNode, int32_t type, const std::string& param) override;
    napi_value GetContextValue() override;

    RefPtr<AceEventHandler> GetEventHandler() override
    {
        return nullptr;
    }

    bool IsForeground() override
    {
        return foregroundFrontend_;
    }

    RefPtr<AccessibilityManager> GetAccessibilityManager() const override
    {
        return accessibilityManager_;
    }
    WindowConfig& GetWindowConfig() override
    {
        static WindowConfig config;
        return config;
    }

    void NavigatePage(uint8_t type, const PageTarget& target, const std::string& params) override {}

    std::pair<RouterRecoverRecord, UIContentErrorCode> RestoreRouterStack(
        const std::string& contentInfo, ContentInfoType type) override
    {
        return { RouterRecoverRecord(), UIContentErrorCode::NO_ERRORS };
    }
    std::string GetContentInfo(ContentInfoType type) const override
    {
        return "";
    }
    int32_t GetRouterSize() const override
    {
        return 0;
    }

    void FlushReload() override {}
    void HotReload() override {}

    ani_ref GetSharedStorage(int32_t id) override;
    
    void RegisterLayoutInspectorCallback(const RefPtr<InspectorEvent>& layoutFunc, const std::string& componentId)
    {
        layoutCallbacks_[componentId] = layoutFunc;
    }
    
    void RegisterDrawInspectorCallback(const RefPtr<InspectorEvent>& drawFunc, const std::string& componentId)
    {
        drawCallbacks_[componentId] = drawFunc;
    }
    
    void RegisterDrawChildrenInspectorCallback(const RefPtr<InspectorEvent>& drawChildrenFunc,
        const std::string& componentId)
    {
        drawChildrenCallbacks_[componentId] = drawChildrenFunc;
    }

    void UnregisterLayoutInspectorCallback(const std::string& componentId)
    {
        layoutCallbacks_.erase(componentId);
    }
    
    void UnregisterDrawInspectorCallback(const std::string& componentId)
    {
        drawCallbacks_.erase(componentId);
    }

    void UnregisterDrawChildrenInspectorCallback(const std::string& componentId)
    {
        drawChildrenCallbacks_.erase(componentId);
    }

    bool IsDrawChildrenCallbackFuncExist(const std::string& componentId) override
    {
        return drawChildrenCallbacks_.find(componentId) != drawChildrenCallbacks_.end();
    }

    virtual void CallbackMediaQuery(const std::string& callbackId, const std::string& args)
    {
        if (mediaUpdateCallback_) {
            mediaUpdateCallback_(this);
        }
    }

    void RegisterMediaUpdateCallback(std::function<void(ArktsFrontend*)> cb)
    {
        mediaUpdateCallback_ = std::move(cb);
    }

    void UnregisterMediaUpdateCallback()
    {
        mediaUpdateCallback_ = nullptr;
    }

    ani_object GetUIContext(int32_t instanceId) override;

    void SetHostContext(int32_t instanceId, ani_ref* context) override;

    ani_ref* GetHostContext() override;

    RefPtr<NG::PageRouterManager> GetPageRouterManager()
    {
        return pageRouterManager_;
    }

    void* GetEnv() override;
    ani_ref GetApp();
    ani_vm *GetVM() override;
    static void PreloadAceModule(void* aniEnv);
    static void* preloadArkTSRuntime;
    void OpenStateMgmtInterop() override;
    void NotifyArkoalaConfigurationChange(bool isNeedUpdate) override;
    void InitXBarProxy() override;
protected:
    bool LoadNavDestinationPage(const std::string bundleName, const std::string& moduleName,
        const std::string& pageSourceFile, bool isSingleton);
    bool GetNavigationRegisterClassName(const std::string& pageSourceFile, std::string& className);
    bool GetNearestNonBootRuntimeLinker();

    ani_ref linkerRef_ = nullptr;
    RefPtr<TaskExecutor> taskExecutor_;
    RefPtr<NG::PipelineContext> pipeline_;
    ani_vm* vm_ = nullptr;
    ani_ref app_ = nullptr;
    ani_method handleMessageMethod_ = nullptr;
    bool foregroundFrontend_ = false;
    RefPtr<NG::PageRouterManager> pageRouterManager_ = nullptr;

    RefPtr<Framework::AccessibilityNodeManager> accessibilityManager_
        = Framework::AccessibilityNodeManager::Create();

    ACE_DISALLOW_COPY_AND_MOVE(ArktsFrontend);
    
    std::map<std::string, RefPtr<InspectorEvent>> layoutCallbacks_;
    std::map<std::string, RefPtr<InspectorEvent>> drawCallbacks_;
    std::map<std::string, RefPtr<InspectorEvent>> drawChildrenCallbacks_;
    MediaQueryCallback mediaQueryCallbacks_;
    RefPtr<Framework::MediaQueryInfo> mediaQueryInfo_ = AceType::MakeRefPtr<Framework::MediaQueryInfo>();
    std::function<void(ArktsFrontend*)> mediaUpdateCallback_;
};

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_BRIDGE_ARKTS_FRONTEND_ARKTS_FRONTEND_H
