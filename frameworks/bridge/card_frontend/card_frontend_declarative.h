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

#ifndef FOUNDATION_ACE_FRAMEWORKS_BRIDGE_CARD_FRONTEND_CARD_FRONTEND_DECLARATIVE_H
#define FOUNDATION_ACE_FRAMEWORKS_BRIDGE_CARD_FRONTEND_CARD_FRONTEND_DECLARATIVE_H

#include <memory>

#include "base/memory/ace_type.h"
#include "core/common/ace_page.h"
#include "core/common/frontend.h"
#include "frameworks/bridge/card_frontend/card_frontend.h"
#include "frameworks/bridge/card_frontend/card_frontend_delegate_declarative.h"
#include "frameworks/bridge/card_frontend/js_card_parser.h"
#include "frameworks/bridge/common/accessibility/accessibility_node_manager.h"
#include "frameworks/bridge/common/manifest/manifest_parser.h"
#include "frameworks/bridge/common/utils/page_id_pool.h"
#include "frameworks/bridge/declarative_frontend/declarative_frontend.h"
#include "frameworks/bridge/declarative_frontend/ng/page_router_manager.h"
#include "frameworks/bridge/declarative_frontend/ng/declarative_frontend_ng.h"
#include "frameworks/bridge/js_frontend/frontend_delegate_impl.h"

namespace OHOS::Ace {

// class ACE_EXPORT CardFrontendDeclarative : public CardFrontend, public DeclarativeFrontendNG {
//     DECLARE_ACE_TYPE(CardFrontendDeclarative, CardFrontend, DeclarativeFrontendNG);

// class ACE_EXPORT CardFrontendDeclarative : public DeclarativeFrontendNG {
//     DECLARE_ACE_TYPE(CardFrontendDeclarative, DeclarativeFrontendNG);
class ACE_EXPORT CardFrontendDeclarative : public DeclarativeFrontend {
    DECLARE_ACE_TYPE(CardFrontendDeclarative, DeclarativeFrontend);

// class ACE_EXPORT CardFrontendDeclarative : public CardFrontend {
//     DECLARE_ACE_TYPE(CardFrontendDeclarative, CardFrontend);
public:
    // CardFrontendDeclarative() = default;
    // ~CardFrontendDeclarative() override;
    CardFrontendDeclarative() = default;
    // ~CardFrontendDeclarative() override;

    // Card
    // void OnPageLoaded(const RefPtr<Framework::JsAcePage>& page) override;
    // void HandleSurfaceChanged(int32_t width, int32_t height) override;
    // void UpdatePageData(const std::string& dataList) override;
    // void OnMediaFeatureUpdate() override;

    // Card
    void UpdateData(const std::string& dataList);
    void HandleSurfaceChanged(int32_t width, int32_t height);
    void UpdatePageData(const std::string& dataList);
    void OnMediaFeatureUpdate();

    // Frontend
    // bool Initialize(FrontendType type, const RefPtr<TaskExecutor>& taskExecutor) override;
    // void Destroy() override;
    // void AttachPipelineContext(const RefPtr<PipelineBase>& context) override;
    // void SetAssetManager(const RefPtr<AssetManager>& assetManager) override;
    // void OnShow() override
    // {
    //     if (delegate_) {
    //         delegate_->OnPageShow();
    //     }
    // }
    // void OnHide() override
    // {
    //     if (delegate_) {
    //         delegate_->OnPageHide();
    //     }
    // }

    void RunPage(int32_t pageId, const std::string& url, const std::string& params) override;

    void OnSurfaceChanged(int32_t width, int32_t height) override;
    void SetColorMode(ColorMode colorMode) override;
    // void RebuildAllPages() override;

    // eTSCard only
    // RefPtr<NG::PageRouterManager> GetPageRouterManager() const;

    // void SetLoadCardCallBack(WeakPtr<PipelineBase> outSidePipelineContext) override
    void SetLoadCardCallBack(WeakPtr<PipelineBase> outSidePipelineContext)
    {
        const auto& loadCallback = [outSidePipelineContext](const std::string& url, int64_t cardId) -> bool {
            LOGE("Kee loadCallback");
            auto context = outSidePipelineContext.Upgrade();
            if (!context) {
                LOGE("Load card callback failed, host pipeline nullptr");
                return false;
            }

            auto outSidefrontend = AceType::DynamicCast<DeclarativeFrontend>(context->GetFrontend());
            if (!outSidefrontend) {
                LOGE("Load card callback failed, host frontend nullptr");
                return false;
            }

            // Use the same js engine with host pipeline
            auto jsEngine = outSidefrontend->GetJsEngine();
            if (!jsEngine) {
                return false;
            }
            LOGE("Kee loadCallback jsEngine->LoadCard");
            return jsEngine->LoadCard(url, cardId);
        };
        // delegate_->SetLoadCardCallBack(loadCallback);
        auto delegate = AceType::DynamicCast<Framework::CardFrontendDelegateDeclarative>(delegate_);
        if (delegate) {
            LOGE("Kee CardFrontendDeclarative::SetLoadCardCallBack delegate->SetLoadCardCallBack");
            delegate->SetLoadCardCallBack(loadCallback);
        } else {
            LOGE("Kee CardFrontendDeclarative::SetLoadCardCallBack delegate nullptr");
        }
    }

    RefPtr<Framework::CardFrontendDelegateDeclarative> GetDelegate()
    {
        LOGE("Kee CardFrontendDelegateDeclarative GetDelegate");
        return AceType::DynamicCast<Framework::CardFrontendDelegateDeclarative>(delegate_);
    }

    // void SetDelegate(RefPtr<Framework::FrontendDelegate> delegate)
    // {
    //     LOGE("Kee CardFrontendDelegateDeclarative SetDelegate");
    //     delegate_ = AceType::DynamicCast<CardFrontendDelegateDeclarative>(delegate_);
    // }

    std::string GetFormSrcPath(const std::string& uri, const std::string& suffix) const;

    void SetFormSrc(std::string formSrc)
    {
        formSrc_ = formSrc;
    }

    std::string GetFormSrc() const
    {
        return formSrc_;
    }

    void SetRunningCardId(int64_t cardId)
    {
        cardId_ = cardId;
    }

    void ParseManifest() const;

    ColorMode colorMode_ = ColorMode::LIGHT;
    // FrontendType type_ = FrontendType::JS_CARD;
    bool foregroundFrontend_ = false;
    double density_ = 1.0;
    std::string cardHapPath_;

    Framework::PipelineContextHolder holder_;
    RefPtr<AssetManager> assetManager_;
    RefPtr<Framework::ManifestParser> manifestParser_;

    mutable std::once_flag onceFlag_;
    RefPtr<TaskExecutor> taskExecutor_;
    RefPtr<AceEventHandler> eventHandler_;
    Framework::PageIdPool pageIdPool_;
    std::string formSrc_;
    WindowConfig cardWindowConfig_;
    uint64_t cardId_ = 0; // cardId != formId, cardId is the nodeId of component.

private:
    void InitializeDelegate(const RefPtr<TaskExecutor>& taskExecutor);
    // RefPtr<Framework::CardFrontendDelegateDeclarative> delegate_;
};

class CardEventHandlerDeclarative : public AceEventHandler {
public:
    explicit CardEventHandlerDeclarative(const RefPtr<Framework::CardFrontendDelegateDeclarative>& delegate) : delegate_(delegate)
    {
        ACE_DCHECK(delegate_);
    }

    ~CardEventHandlerDeclarative() override = default;

    void HandleAsyncEvent(const EventMarker& eventMarker) override
    {
        LOGI("HandleAsyncEvent cardId: %{public}d, eventId: %{public}s", eventMarker.GetData().pageId,
            eventMarker.GetData().eventId.c_str());
        delegate_->FireCardEvent(eventMarker);
    }

    void HandleAsyncEvent(const EventMarker& eventMarker, int32_t param) override
    {
        LOGW("card event handler does not support this event type!");
    }

    void HandleAsyncEvent(const EventMarker& eventMarker, const BaseEventInfo& info) override
    {
        LOGI("HandleAsyncEvent cardId: %{public}d, eventId: %{public}s", eventMarker.GetData().pageId,
            eventMarker.GetData().eventId.c_str());
        delegate_->FireCardEvent(eventMarker);
    }

    void HandleAsyncEvent(const EventMarker& eventMarker, const KeyEvent& info) override
    {
        LOGW("card event handler does not support this event type!");
    }

    void HandleAsyncEvent(const EventMarker& eventMarker, const std::string& param) override
    {
        LOGI("HandleAsyncEvent cardId: %{public}d, eventId: %{public}s", eventMarker.GetData().pageId,
            eventMarker.GetData().eventId.c_str());
        delegate_->FireCardEvent(eventMarker, param);
    }

    void HandleSyncEvent(const EventMarker& eventMarker, bool& result) override
    {
        LOGW("card event handler does not support this event type!");
    }

    void HandleSyncEvent(const EventMarker& eventMarker, const BaseEventInfo& info, bool& result) override
    {
        LOGW("card event handler does not support this event type!");
    }

    void HandleSyncEvent(const EventMarker& eventMarker, const KeyEvent& info, bool& result) override
    {
        LOGW("card event handler does not support this event type!");
    }

    void HandleSyncEvent(const EventMarker& eventMarker, const std::string& param, std::string& result) override
    {
        LOGW("card event handler does not support this event type!");
    }

    void HandleSyncEvent(const EventMarker& eventMarker, const std::string& componentId, const int32_t nodeId,
        const bool isDestroy) override
    {
        LOGW("card event handler does not support this event type!");
    }

private:
    RefPtr<Framework::CardFrontendDelegateDeclarative> delegate_;
};
} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_BRIDGE_CARD_FRONTEND_CARD_FRONTEND_DECLARATIVE_H
