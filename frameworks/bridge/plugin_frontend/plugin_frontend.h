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

#ifndef FOUNDATION_ACE_FRAMEWORKS_BRIDGE_PLUGIN_FRONTEND_PLUGIN_FRONTEND_H
#define FOUNDATION_ACE_FRAMEWORKS_BRIDGE_PLUGIN_FRONTEND_PLUGIN_FRONTEND_H

#include <string>
#include <unordered_map>

#include "base/memory/ace_type.h"
#include "base/utils/string_utils.h"
#include "core/common/ace_page.h"
#include "core/common/container.h"
#include "core/common/frontend.h"
#include "core/common/js_message_dispatcher.h"
#include "frameworks/bridge/js_frontend/engine/common/js_engine.h"
#include "frameworks/bridge/plugin_frontend/plugin_frontend_delegate.h"

namespace OHOS::Ace {
// PluginFrontend is the unique entrance from ACE backend to frontend.
// The relationship between AceActivity, AceContainer and PluginFrontend is 1:1:1.
// So PluginFrontend would be responsible for below things:
// - Create and initialize QuickJS engine.
// - Load pages of a JS app, and parse the manifest.json before loading main page.
// - Maintain the page stack of JS app by PluginFrontendDelegate.
// - Lifecycle of JS app (also AceActivity).
class PluginFrontend : public Frontend {
    DECLARE_ACE_TYPE(PluginFrontend, Frontend);

public:
    using onPluginUpdateWithValueParams = std::function<void(const std::string&)>;

    PluginFrontend() = default;
    ~PluginFrontend() override;

    bool Initialize(FrontendType type, const RefPtr<TaskExecutor>& taskExecutor) override;

    void Destroy() override;

    void AttachPipelineContext(const RefPtr<PipelineBase>& context) override;

    void SetAssetManager(const RefPtr<AssetManager>& assetManager) override;

    UIContentErrorCode RunPage(const std::string& url, const std::string& params) override;

    void ReplacePage(const std::string& url, const std::string& params) override;

    void PushPage(const std::string& url, const std::string& params) override;

    // Js frontend manages all pages self.
    void AddPage(const RefPtr<AcePage>& page) override {}

    RefPtr<AcePage> GetPage(int32_t pageId) const override
    {
        return nullptr;
    }

    void TriggerGarbageCollection() override;

    void SendCallbackMessage(const std::string& callbackId, const std::string& data) const override;
    // platform channel.
    void SetJsMessageDispatcher(const RefPtr<JsMessageDispatcher>& dispatcher) const override;
    void TransferComponentResponseData(int32_t callbackId, int32_t code,
        std::vector<uint8_t>&& data) const override;
    void TransferJsResponseData(int32_t callbackId, int32_t code, std::vector<uint8_t>&& data) const override;
#if defined(PREVIEW)
    void TransferJsResponseDataPreview(int32_t callbackId, int32_t code, ResponseData responseData) const;
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
    void SetColorMode(ColorMode colorMode) override;
    void CallRouterBack() override;
    void NotifyAppStorage(const std::string& key, const std::string& value) override;

    void OnSurfaceChanged(int32_t width, int32_t height) override;

    void OnLayoutCompleted(const std::string& componentId) override;
    void OnDrawCompleted(const std::string& componentId) override;
    void OnDrawChildrenCompleted(const std::string& componentId) override;
    bool IsDrawChildrenCallbackFuncExist(const std::string& componentId) override;

    void DumpFrontend() const override;
    std::string GetPagePath() const override;

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

    virtual void SetPluginBundleName(const std::string& pluginBundleName)
    {
        if (jsEngine_) {
            jsEngine_->SetPluginBundleName(pluginBundleName);
        }
    }

    virtual void SetPluginModuleName(const std::string& pluginModuleName)
    {
        if (jsEngine_) {
            jsEngine_->SetPluginModuleName(pluginModuleName);
        }
    }

    void MarkIsSubWindow(bool isSubWindow)
    {
        isSubWindow_ = isSubWindow;
    }

    void RebuildAllPages() override;

    void SetDensity(double density)
    {
        density_ = density;
    }

    void ResetPageLoadState()
    {
        pageLoaded_ = false;
    }

    void UpdatePlugin(const std::string& content);

    void SetDeclarativeOnUpdateWithValueParamsCallback(onPluginUpdateWithValueParams&& callback)
    {
        if (delegate_) {
            delegate_->SetDeclarativeOnUpdateWithValueParamsCallback(std::move(callback));
        }
    }

    void FireDeclarativeOnUpdateWithValueParamsCallback(const std::string& params) const
    {
        if (delegate_) {
            delegate_->FireDeclarativeOnUpdateWithValueParamsCallback(params);
        }
    }

private:
    void InitializeFrontendDelegate(const RefPtr<TaskExecutor>& taskExecutor);

    RefPtr<Framework::PluginFrontendDelegate> delegate_;
    RefPtr<AceEventHandler> handler_;
    RefPtr<Framework::JsEngine> jsEngine_;
    RefPtr<AccessibilityManager> accessibilityManager_;
    bool foregroundFrontend_ = false;
    bool isSubWindow_ = false;
    bool pageLoaded_ = false;
    double density_ = 1.0;
};

class PluginEventHandler : public AceEventHandler {
public:
    explicit PluginEventHandler(const RefPtr<Framework::PluginFrontendDelegate>& delegate) : delegate_(delegate)
    {
        ACE_DCHECK(delegate_);
    }
    PluginEventHandler() {}

    ~PluginEventHandler() override = default;

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
    RefPtr<Framework::PluginFrontendDelegate> delegate_;
};
} // namespace OHOS::Ace
#endif // FOUNDATION_ACE_FRAMEWORKS_BRIDGE_PLUGIN_FRONTEND_PLUGIN_FRONTEND_H
