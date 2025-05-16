/*
 * Copyright (c) 2021-2023 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_DECLARATIVE_FRONTEND_H
#define FOUNDATION_ACE_FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_DECLARATIVE_FRONTEND_H

#include <string>
#include <map>
#include <unordered_map>

#include "base/memory/ace_type.h"
#include "base/utils/noncopyable.h"
#include "base/utils/string_utils.h"
#include "bridge/declarative_frontend/ng/page_router_manager.h"
#include "core/common/ace_page.h"
#include "core/common/container.h"
#include "core/common/frontend.h"
#include "core/common/js_message_dispatcher.h"
#include "core/pipeline_ng/ui_task_scheduler.h"
#include "frameworks/bridge/declarative_frontend/frontend_delegate_declarative.h"
#include "frameworks/bridge/js_frontend/engine/common/js_engine.h"

namespace OHOS::Ace {

// DeclarativeFrontend is the unique entrance from ACE backend to frontend.
// The relationship between AceActivity, AceContainer and DeclarativeFrontend is 1:1:1.
// So DeclarativeFrontend would be responsible for below things:
// - Create and initialize JS engine.
// - Load pages of a JS app, and parse the manifest.json before loading main page.
// - Maintain the page stack of JS app by FrontendDelegateDeclarative.
// - Lifecycle of JS app (also AceActivity).
class ACE_EXPORT DeclarativeFrontend : public Frontend {
    DECLARE_ACE_TYPE(DeclarativeFrontend, Frontend);

public:
    DeclarativeFrontend() = default;
    ~DeclarativeFrontend() override;

    bool Initialize(FrontendType type, const RefPtr<TaskExecutor>& taskExecutor) override;

    void Destroy() override;

    void AttachPipelineContext(const RefPtr<PipelineBase>& context) override;

    void SetAssetManager(const RefPtr<AssetManager>& assetManager) override;

    UIContentErrorCode RunPage(const std::string& url, const std::string& params) override;
    UIContentErrorCode RunPage(
        const std::shared_ptr<std::vector<uint8_t>>& content, const std::string& params) override;

    UIContentErrorCode RunPageByNamedRouter(const std::string& name, const std::string& params) override;

    UIContentErrorCode RunIntentPage() override;

    UIContentErrorCode SetRouterIntentInfo(const std::string& intentInfoSerialized, bool isColdStart,
        const std::function<void()>&& loadPageCallback) override;

    void ReplacePage(const std::string& url, const std::string& params) override;

    void PushPage(const std::string& url, const std::string& params) override;

    // Js frontend manages all pages self.
    void AddPage(const RefPtr<AcePage>& page) override {}

    RefPtr<AcePage> GetPage(int32_t /*pageId*/) const override
    {
        return nullptr;
    }

    std::string GetCurrentPageUrl() const override;

    // Get the currently running JS page information in NG structure.
    RefPtr<Framework::RevSourceMap> GetCurrentPageSourceMap() const override;

    // Get the currently running JS page information in NG structure.
    RefPtr<Framework::RevSourceMap> GetFaAppSourceMap() const override;

    void GetStageSourceMap(
        std::unordered_map<std::string, RefPtr<Framework::RevSourceMap>>& sourceMap) const override;

    RefPtr<NG::PageRouterManager> GetPageRouterManager() const;

    void SendCallbackMessage(const std::string& callbackId, const std::string& data) const override;
    // platform channel.
    void SetJsMessageDispatcher(const RefPtr<JsMessageDispatcher>& dispatcher) const override;
    void TransferComponentResponseData(int32_t callbackId, int32_t code, std::vector<uint8_t>&& data) const override;
    void TransferJsResponseData(int32_t callbackId, int32_t code, std::vector<uint8_t>&& data) const override;
    napi_value GetContextValue() override;
    napi_value GetFrameNodeValueByNodeId(int32_t nodeId) override;
#if defined(PREVIEW)
    void SetPkgNameList(const std::map<std::string, std::string>& map)
    {
        pkgNameMap_ = map;
    }

    void SetPkgAliasList(const std::map<std::string, std::string>& map)
    {
        pkgAliasMap_ = map;
    }

    void SetpkgContextInfoList(const std::map<std::string, std::vector<std::vector<std::string>>>& map)
    {
        pkgContextInfoMap_ = map;
    }

    void SetPagePath(const std::string& pagePath)
    {
        if (delegate_) {
            delegate_->SetPagePath(pagePath);
        }
    }
    void RunNativeEngineLoop() override
    {
        if (jsEngine_) {
            jsEngine_->RunNativeEngineLoop();
        }
    }

    void TransferJsResponseDataPreview(int32_t callbackId, int32_t code, ResponseData responseData) const;
    RefPtr<Component> GetNewComponentWithJsCode(const std::string& jsCode, const std::string& viewID);
    void InitializeModuleSearcher(const std::string& bundleName, const std::string& moduleName,
                                  const std::string& assetPath, bool isBundle)
    {
        if (jsEngine_) {
            jsEngine_->InitializeModuleSearcher(bundleName, moduleName, assetPath, isBundle);
        }
    }
#endif
    void TransferJsPluginGetError(int32_t callbackId, int32_t errorCode, std::string&& errorMessage) const override;
    void TransferJsEventData(int32_t callbackId, int32_t code, std::vector<uint8_t>&& data) const override;
    void LoadPluginJsCode(std::string&& jsCode) const override;
    void LoadPluginJsByteCode(std::vector<uint8_t>&& jsCode, std::vector<int32_t>&& jsCodeLen) const override;

    // application lifecycle.
    void UpdateState(Frontend::State state) override;

    // page lifecycle.
    bool OnBackPressed() override;
    void OnShow() override;
    void OnHide() override;
    void OnConfigurationUpdated(const std::string& data) override;
    void OnSaveAbilityState(std::string& data) override;
    void OnRestoreAbilityState(const std::string& data) override;
    void OnNewWant(const std::string& data) override;
    void OnActive() override;
    void OnInactive() override;
    bool OnStartContinuation() override;
    void OnCompleteContinuation(int32_t code) override;
    void OnSaveData(std::string& data) override;
    void GetPluginsUsed(std::string& data) override;
    bool OnRestoreData(const std::string& data) override;
    void OnRemoteTerminated() override;
    void OnNewRequest(const std::string& data) override;
    void OnMemoryLevel(const int32_t level) override;
    void CallRouterBack() override;
    void OnSurfaceChanged(int32_t width, int32_t height) override;
    void OnLayoutCompleted(const std::string& componentId) override;
    void OnDrawCompleted(const std::string& componentId) override;
    void OnDrawChildrenCompleted(const std::string& componentId) override;
    bool IsDrawChildrenCallbackFuncExist(const std::string& componentId) override;
    void DumpFrontend() const override;
    std::string GetPagePath() const override;
    void TriggerGarbageCollection() override;
    void DumpHeapSnapshot(bool isPrivate) override;
    void NotifyUIIdle() override;
    void SetColorMode(ColorMode colorMode) override;
    void RebuildAllPages() override;
    void NotifyAppStorage(const std::string& key, const std::string& value) override;
    RefPtr<AceEventHandler> GetEventHandler() override
    {
        return handler_;
    }

    // judge frontend is foreground frontend.
    bool IsForeground() override
    {
        return foregroundFrontend_;
    }

    RefPtr<AccessibilityManager> GetAccessibilityManager() const override;
    WindowConfig& GetWindowConfig() override;

    // navigator component call router
    void NavigatePage(uint8_t type, const PageTarget& target, const std::string& params) override;

    // restore
    std::pair<RouterRecoverRecord, UIContentErrorCode> RestoreRouterStack(
        const std::string& contentInfo, ContentInfoType type) override;
    std::string GetContentInfo(ContentInfoType type) const override;
    int32_t GetRouterSize() const override;

    void OnWindowDisplayModeChanged(bool isShownInMultiWindow, const std::string& data);

    void SetJsEngine(const RefPtr<Framework::JsEngine>& jsEngine)
    {
        jsEngine_ = jsEngine;
    }

    void SetNeedDebugBreakPoint(bool value)
    {
        if (jsEngine_) {
            jsEngine_->SetNeedDebugBreakPoint(value);
        }
    }

    void SetDebugVersion(bool value)
    {
        if (jsEngine_) {
            jsEngine_->SetDebugVersion(value);
        }
    }

    void SetInstanceName(const std::string& name)
    {
        if (jsEngine_) {
            jsEngine_->SetInstanceName(name);
        }
    }

    void SetPageProfile(const std::string& pageProfile)
    {
        pageProfile_ = pageProfile;
    }

    void MarkIsSubWindow(bool isSubWindow)
    {
        isSubWindow_ = isSubWindow;
    }

    RefPtr<Framework::JsEngine> GetJsEngine()
    {
        return jsEngine_;
    }

    void AttachSubPipelineContext(const RefPtr<PipelineBase>& context);

    void FlushReload() override;
    void HotReload() override;

    RefPtr<Framework::FrontendDelegate> GetDelegate() const
    {
        return AceType::DynamicCast<Framework::FrontendDelegate>(delegate_);
    }

    std::string GetPagePathByUrl(const std::string& url) const override;

protected:
    bool isFormRender_ = false;
    RefPtr<Framework::FrontendDelegateDeclarative> delegate_;

private:
    void InitializeFrontendDelegate(const RefPtr<TaskExecutor>& taskExecutor);

    RefPtr<AceEventHandler> handler_;
    RefPtr<Framework::JsEngine> jsEngine_;
    RefPtr<AccessibilityManager> accessibilityManager_;
    std::string pageProfile_;
#if defined(PREVIEW)
    std::map<std::string, std::string> pkgNameMap_;
    std::map<std::string, std::string> pkgAliasMap_;
    std::map<std::string, std::vector<std::vector<std::string>>> pkgContextInfoMap_;
#endif
    bool foregroundFrontend_ = false;
    bool isSubWindow_ = false;

    ACE_DISALLOW_COPY_AND_MOVE(DeclarativeFrontend);
};

class DeclarativeEventHandler : public AceEventHandler {
public:
    explicit DeclarativeEventHandler(const RefPtr<Framework::FrontendDelegateDeclarative>& delegate)
        : delegate_(delegate)
    {
        ACE_DCHECK(delegate_);
    }
    DeclarativeEventHandler() {}

    ~DeclarativeEventHandler() override = default;

    void HandleAsyncEvent(const EventMarker& eventMarker) override;

    void HandleAsyncEvent(const EventMarker& eventMarker, int32_t param) override;

    void HandleAsyncEvent(const EventMarker& eventMarker, const BaseEventInfo& info) override;

    void HandleAsyncEvent(const EventMarker& eventMarker, const std::shared_ptr<BaseEventInfo>& info) override;

    void HandleAsyncEvent(const EventMarker& eventMarker, const KeyEvent& info) override;

    void HandleAsyncEvent(const EventMarker& eventMarker, const std::string& param) override;

    void HandleSyncEvent(const EventMarker& eventMarker, bool& result) override;

    void HandleSyncEvent(const EventMarker& eventMarker, const BaseEventInfo& info, bool& result) override;

    void HandleSyncEvent(const EventMarker& eventMarker, const KeyEvent& info, bool& result) override;

    void HandleSyncEvent(const EventMarker& eventMarker, const std::string& param, std::string& result) override;

    void HandleSyncEvent(const EventMarker& eventMarker, const std::shared_ptr<BaseEventInfo>& info) override;

    void HandleSyncEvent(const EventMarker& eventMarker, const std::string& componentId, const int32_t nodeId,
        const bool isDestroy) override;

private:
    RefPtr<Framework::FrontendDelegateDeclarative> delegate_;
};

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_DECLARATIVE_FRONTEND_H
