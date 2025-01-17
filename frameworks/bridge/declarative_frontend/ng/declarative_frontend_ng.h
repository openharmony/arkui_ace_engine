/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_DECLARATIVE_FRONTEND_NG_H
#define FOUNDATION_ACE_FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_DECLARATIVE_FRONTEND_NG_H

#include <string>

#include "base/memory/ace_type.h"
#include "base/utils/string_utils.h"
#include "core/common/ace_page.h"
#include "core/common/container.h"
#include "core/common/frontend.h"
#include "core/pipeline/pipeline_base.h"
#include "frameworks/bridge/declarative_frontend/ng/frontend_delegate_declarative_ng.h"
#include "frameworks/bridge/js_frontend/engine/common/js_engine.h"

namespace OHOS::Ace {

class DeclarativeFrontendNG : public Frontend {
    DECLARE_ACE_TYPE(DeclarativeFrontendNG, Frontend);

public:
    DeclarativeFrontendNG() = default;
    ~DeclarativeFrontendNG() override;

    bool Initialize(FrontendType type, const RefPtr<TaskExecutor>& taskExecutor) override;

    void Destroy() override;

    void AttachPipelineContext(const RefPtr<PipelineBase>& context) override;

    void SetAssetManager(const RefPtr<AssetManager>& assetManager) override;

    UIContentErrorCode RunPage(const std::string& url, const std::string& params) override;
    UIContentErrorCode RunPage(
        const std::shared_ptr<std::vector<uint8_t>>& content, const std::string& params) override;
    UIContentErrorCode RunPageByNamedRouter(const std::string& name, const std::string& params) override;

    void ReplacePage(const std::string& url, const std::string& params) override;

    void PushPage(const std::string& url, const std::string& params) override;

    // Js frontend manages all pages self.
    void AddPage(const RefPtr<AcePage>& page) override {}

    RefPtr<AcePage> GetPage(int32_t pageId) const override
    {
        return nullptr;
    }

    void SendCallbackMessage(const std::string& callbackId, const std::string& data) const override {}

    // platform channel.
    void SetJsMessageDispatcher(const RefPtr<JsMessageDispatcher>& dispatcher) const override {}
    void TransferComponentResponseData(int32_t callbackId, int32_t code, std::vector<uint8_t>&& data) const override {}
    void TransferJsResponseData(int32_t callbackId, int32_t code, std::vector<uint8_t>&& data) const override {}
    napi_value GetContextValue() override;
    napi_value GetFrameNodeValueByNodeId(int32_t nodeId) override;
    
#if defined(PREVIEW)
    void RunNativeEngineLoop() override
    {
        if (jsEngine_) {
            jsEngine_->RunNativeEngineLoop();
        }
    }
#endif
    void TransferJsPluginGetError(int32_t callbackId, int32_t errorCode, std::string&& errorMessage) const override {}
    void TransferJsEventData(int32_t callbackId, int32_t code, std::vector<uint8_t>&& data) const override {}
    void LoadPluginJsCode(std::string&& jsCode) const override {}
    void LoadPluginJsByteCode(std::vector<uint8_t>&& jsCode, std::vector<int32_t>&& jsCodeLen) const override {}

    // application lifecycle.
    void UpdateState(Frontend::State state) override;

    // page lifecycle.
    bool OnBackPressed() override;
    void OnShow() override;
    void OnHide() override;
    void OnConfigurationUpdated(const std::string& data) override;
    void OnActive() override;
    void OnSaveAbilityState(std::string& data) override {}
    void OnRestoreAbilityState(const std::string& data) override {}
    void OnNewWant(const std::string& data) override {}
    void OnInactive() override {}
    bool OnStartContinuation() override;
    void OnCompleteContinuation(int32_t code) override;
    void OnSaveData(std::string& data) override;
    bool OnRestoreData(const std::string& data) override;
    void OnRemoteTerminated() override;
    void OnNewRequest(const std::string& data) override {}
    void OnMemoryLevel(const int32_t level) override {}
    void CallRouterBack() override;
    void OnSurfaceChanged(int32_t width, int32_t height) override;

    void OnLayoutCompleted(const std::string& componentId) override;
    void OnDrawCompleted(const std::string& componentId) override;

    void DumpFrontend() const override;
    std::string GetPagePath() const override;
    void TriggerGarbageCollection() override;
    void DumpHeapSnapshot(bool isPrivate) override;
    void NotifyUIIdle() override;
    void SetColorMode(ColorMode colorMode) override;
    void RebuildAllPages() override;
    void NotifyAppStorage(const std::string& key, const std::string& value) override;

    RefPtr<NG::PageRouterManager> GetPageRouterManager() const;

    RefPtr<AceEventHandler> GetEventHandler() override
    {
        return nullptr;
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

    std::string GetCurrentPageUrl() const override;

private:
    void InitializeDelegate(const RefPtr<TaskExecutor>& taskExecutor);

    RefPtr<Framework::JsEngine> jsEngine_;
    RefPtr<Framework::FrontendDelegateDeclarativeNG> delegate_;
    RefPtr<AccessibilityManager> accessibilityManager_;

    std::string pageProfile_;
    bool foregroundFrontend_ = false;
    bool isSubWindow_ = false;
};

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_DECLARATIVE_FRONTEND_H
