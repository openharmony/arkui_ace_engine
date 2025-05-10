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

#ifndef FOUNDATION_ACE_FRAMEWORKS_BRIDGE_CARD_FRONTEND_CARD_FRONTEND_H
#define FOUNDATION_ACE_FRAMEWORKS_BRIDGE_CARD_FRONTEND_CARD_FRONTEND_H

#include <memory>

#include "base/memory/ace_type.h"
#include "core/common/ace_page.h"
#include "core/common/frontend.h"
#include "frameworks/bridge/card_frontend/card_frontend_delegate.h"
#include "frameworks/bridge/card_frontend/js_card_parser.h"
#include "frameworks/bridge/common/accessibility/accessibility_node_manager.h"
#include "frameworks/bridge/common/manifest/manifest_parser.h"
#include "frameworks/bridge/common/utils/page_id_pool.h"
#include "frameworks/bridge/js_frontend/frontend_delegate_impl.h"

namespace OHOS::Ace {
class ACE_EXPORT CardFrontend : public Frontend {
    DECLARE_ACE_TYPE(CardFrontend, Frontend);

public:
    using OnFormVisibleCallback = std::function<void()>;

    CardFrontend() = default;
    ~CardFrontend() override;

    virtual void SetLoadCardCallBack(WeakPtr<PipelineBase> outSidePipelineContext) {}
    virtual void UpdateData(const std::string& dataList);
    virtual void OnPageLoaded(const RefPtr<Framework::JsAcePage>& page);
    virtual void HandleSurfaceChanged(int32_t width, int32_t height);
    virtual void UpdatePageData(const std::string& dataList);
    virtual void OnMediaFeatureUpdate();
    std::string GetFormSrcPath(const std::string& uri, const std::string& suffix) const;

    bool Initialize(FrontendType type, const RefPtr<TaskExecutor>& taskExecutor) override;

    void Destroy() override;

    void AttachPipelineContext(const RefPtr<PipelineBase>& context) override;
    void SetAssetManager(const RefPtr<AssetManager>& assetManager) override;

    UIContentErrorCode RunPage(const std::string& url, const std::string& params) override;
    void ReplacePage(const std::string& url, const std::string& params) override {}
    void PushPage(const std::string& url, const std::string& params) override {}
    void AddPage(const RefPtr<AcePage>& page) override {}
    RefPtr<AcePage> GetPage(int32_t pageId) const override;
    void TriggerGarbageCollection() override {}

    void SendCallbackMessage(const std::string& callbackId, const std::string& data) const override {}
    // platform channel.
    void SetJsMessageDispatcher(const RefPtr<JsMessageDispatcher>& dispatcher) const override {}
    void TransferComponentResponseData(int32_t callbackId, int32_t code, std::vector<uint8_t>&& data) const override {}
    void TransferJsResponseData(int32_t callbackId, int32_t code, std::vector<uint8_t>&& data) const override {}
    void TransferJsEventData(int32_t callbackId, int32_t code, std::vector<uint8_t>&& data) const override {}
    void TransferJsPluginGetError(int32_t callbackId, int32_t errorCode, std::string&& errorMessage) const override {}

    void LoadPluginJsCode(std::string&& jsCode) const override {}
    void LoadPluginJsByteCode(std::vector<uint8_t>&& jsCode, std::vector<int32_t>&& jsCodeLen) const override {}

    // application lifecycle.
    void UpdateState(Frontend::State state) override {}

    // page lifecycle.
    bool OnBackPressed() override
    {
        return false;
    }

    void OnSaveAbilityState(std::string& data) override {}

    void OnRestoreAbilityState(const std::string& data) override {}

    void OnShow() override
    {
        foregroundFrontend_ = true;
    }
    void OnHide() override
    {
        foregroundFrontend_ = false;
    }

    void OnActive() override {}
    void OnInactive() override {}
    bool OnStartContinuation() override
    {
        return false;
    }
    void OnCompleteContinuation(int32_t code) override {}
    void OnMemoryLevel(const int32_t level) override {}
    void OnSaveData(std::string& data) override {}
    bool OnRestoreData(const std::string& data) override
    {
        return false;
    }
    void OnRemoteTerminated() override {}
    void OnNewRequest(const std::string& data) override {}
    void OnNewWant(const std::string& data) override {}
    void CallRouterBack() override {}
    void OnSurfaceChanged(int32_t width, int32_t height) override;
    void OnLayoutCompleted(const std::string& componentId) override {}
    void OnDrawCompleted(const std::string& componentId) override {}
    void OnDrawChildrenCompleted(const std::string& componentId) override {}
    bool IsDrawChildrenCallbackFuncExist(const std::string& componentId) override {
        return false;
    }
    void DumpFrontend() const override {}
    std::string GetPagePath() const override
    {
        return "";
    }
    WindowConfig& GetWindowConfig() override;
    void SetColorMode(ColorMode colorMode) override;
    void RebuildAllPages() override;

    RefPtr<AceEventHandler> GetEventHandler() override
    {
        return eventHandler_;
    }

    // judge frontend is foreground frontend.
    bool IsForeground() override
    {
        return foregroundFrontend_;
    }

    RefPtr<AccessibilityManager> GetAccessibilityManager() const override
    {
        if (!delegate_) {
            return nullptr;
        }
        return delegate_->GetJsAccessibilityManager();
    }

    void SetDensity(double density)
    {
        density_ = density;
    }

    void ResetPageLoadState()
    {
        pageLoaded_ = false;
    }

    void SetCardHapPath(const std::string& path)
    {
        cardHapPath_ = path;
    }

    std::string GetFormSrc() const
    {
        return formSrc_;
    }

    void SetFormSrc(std::string formSrc)
    {
        formSrc_ = formSrc;
    }

    WindowConfig& GetCardWindowConfig()
    {
        return cardWindowConfig_;
    }

    void SetCardWindowConfig(WindowConfig cardWindowConfig)
    {
        cardWindowConfig_ = cardWindowConfig;
    }

    void SetRunningCardId(int64_t cardId)
    {
        cardId_ = cardId;
    }

    void AddFormVisiableCallback(const OnFormVisibleCallback& callback)
    {
        if (callback) {
            onFormVisibleCallback_ = callback;
        }
    }

    void FireFormVisiableCallback() const
    {
        if (onFormVisibleCallback_) {
            onFormVisibleCallback_();
        }
    }

protected:
    void ParseManifest() const;

    ColorMode colorMode_ = ColorMode::LIGHT;
    bool foregroundFrontend_ = false;
    bool pageLoaded_ = false;
    double density_ = 1.0;
    std::string cardHapPath_;

    Framework::PipelineContextHolder holder_;
    RefPtr<AssetManager> assetManager_;
    RefPtr<Framework::ManifestParser> manifestParser_;
    OnFormVisibleCallback onFormVisibleCallback_;

    mutable std::once_flag onceFlag_;
    RefPtr<AceEventHandler> eventHandler_;
    Framework::PageIdPool pageIdPool_;
    std::string formSrc_;
    WindowConfig cardWindowConfig_;
    uint64_t cardId_ = 0; // cardId != formId, cardId is the nodeId of component.

private:
    RefPtr<Framework::CardFrontendDelegate> delegate_;
    void LoadPage(const std::string& urlPath, const std::string& params);
    void ParsePage(const RefPtr<PipelineBase>& context, const std::string& pageContent, const std::string& params,
        const RefPtr<Framework::JsAcePage>& page);

    RefPtr<Framework::JsCardParser> parseJsCard_;
};

class CardEventHandler : public AceEventHandler {
public:
    explicit CardEventHandler(const RefPtr<Framework::CardFrontendDelegate>& delegate) : delegate_(delegate)
    {
        ACE_DCHECK(delegate_);
    }

    ~CardEventHandler() override = default;

    void HandleAsyncEvent(const EventMarker& eventMarker) override
    {
        delegate_->FireCardEvent(eventMarker);
    }

    void HandleAsyncEvent(const EventMarker& eventMarker, int32_t param) override {}

    void HandleAsyncEvent(const EventMarker& eventMarker, const BaseEventInfo& info) override
    {
        delegate_->FireCardEvent(eventMarker);
    }

    void HandleAsyncEvent(const EventMarker& eventMarker, const KeyEvent& info) override {}

    void HandleAsyncEvent(const EventMarker& eventMarker, const std::string& param) override
    {
        delegate_->FireCardEvent(eventMarker, param);
    }

    void HandleSyncEvent(const EventMarker& eventMarker, bool& result) override {}

    void HandleSyncEvent(const EventMarker& eventMarker, const BaseEventInfo& info, bool& result) override {}

    void HandleSyncEvent(const EventMarker& eventMarker, const KeyEvent& info, bool& result) override {}

    void HandleSyncEvent(const EventMarker& eventMarker, const std::string& param, std::string& result) override {}

    void HandleSyncEvent(const EventMarker& eventMarker, const std::string& componentId, const int32_t nodeId,
        const bool isDestroy) override
    {}

private:
    RefPtr<Framework::CardFrontendDelegate> delegate_;
};
} // namespace OHOS::Ace
#endif // FOUNDATION_ACE_FRAMEWORKS_BRIDGE_CARD_FRONTEND_CARD_FRONTEND_H
