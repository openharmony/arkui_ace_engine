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

#ifndef FOUNDATION_ACE_FRAMEWORKS_BRIDGE_KOALA_FRONTEND_KOALA_FRONTEND_H
#define FOUNDATION_ACE_FRAMEWORKS_BRIDGE_KOALA_FRONTEND_KOALA_FRONTEND_H

#include "base/memory/ace_type.h"
#include "base/utils/noncopyable.h"
#include "core/common/frontend.h"

namespace OHOS::Ace {
/**
 * @brief Proxy class to interact with Koala frontend and static ArkTS runtime.
 * 
 */
class ACE_EXPORT KoalaFrontend : public Frontend {
    DECLARE_ACE_TYPE(KoalaFrontend, Frontend);

public:
    KoalaFrontend() = default;
    ~KoalaFrontend() override = default;

    bool Initialize(FrontendType type, const RefPtr<TaskExecutor>& taskExecutor) override
    {
        return true;
    }

    void Destroy() override {}

    void AttachPipelineContext(const RefPtr<PipelineBase>& context) override {}

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

    bool OnBackPressed() override
    {
        return false;
    }
    void OnShow() override {}
    void OnHide() override {}
    void OnConfigurationUpdated(const std::string& data) override {}
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
    void OnSurfaceChanged(int32_t width, int32_t height) override {}
    void OnLayoutCompleted(const std::string& componentId) override {}
    void OnDrawCompleted(const std::string& componentId) override {}

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
        return nullptr;
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

private:
    bool foregroundFrontend_ = false;
    ACE_DISALLOW_COPY_AND_MOVE(KoalaFrontend);
};

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_BRIDGE_KOALA_FRONTEND_KOALA_FRONTEND_H
