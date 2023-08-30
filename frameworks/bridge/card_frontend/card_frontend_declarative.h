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

class ACE_EXPORT CardFrontendDeclarative : public CardFrontend {
    DECLARE_ACE_TYPE(CardFrontendDeclarative, CardFrontend);

public:
    CardFrontendDeclarative() = default;
    ~CardFrontendDeclarative() override;

    // Card
    void OnPageLoaded(const RefPtr<Framework::JsAcePage>& page) override;
    void HandleSurfaceChanged(int32_t width, int32_t height) override;
    void UpdatePageData(const std::string& dataList) override;
    void OnMediaFeatureUpdate() override;

    // Frontend
    bool Initialize(FrontendType type, const RefPtr<TaskExecutor>& taskExecutor) override;
    void Destroy() override;
    void AttachPipelineContext(const RefPtr<PipelineBase>& context) override;
    void SetAssetManager(const RefPtr<AssetManager>& assetManager) override;
    void OnShow() override
    {
        foregroundFrontend_ = true;
        if (delegate_) {
            delegate_->OnPageShow();
        }
    }
    void OnHide() override
    {
        foregroundFrontend_ = false;
        if (delegate_) {
            delegate_->OnPageHide();
        }
    }

    void RunPage(int32_t pageId, const std::string& url, const std::string& params) override;

    void OnSurfaceChanged(int32_t width, int32_t height) override;
    void UpdateData(const std::string& dataList) override;
    void SetColorMode(ColorMode colorMode) override;
    void RebuildAllPages() override;

    // eTSCard only
    RefPtr<NG::PageRouterManager> GetPageRouterManager() const;

    void SetLoadCardCallBack(WeakPtr<PipelineBase> outSidePipelineContext) override
    {
        const auto& loadCallback = [outSidePipelineContext](const std::string& url, int64_t cardId) -> bool {
            auto context = outSidePipelineContext.Upgrade();
            if (!context) {
                LOGE("Load card callback failed, host pipeline nullptr");
                return false;
            }
#ifdef NG_BUILD
            auto outSidefrontend = AceType::DynamicCast<DeclarativeFrontendNG>(context->GetFrontend());
#else
            auto outSidefrontend = AceType::DynamicCast<DeclarativeFrontend>(context->GetFrontend());
#endif
            if (!outSidefrontend) {
                LOGE("Load card callback failed, host frontend nullptr");
                return false;
            }

            // Use the same js engine with host pipeline
            auto jsEngine = outSidefrontend->GetJsEngine();
            if (!jsEngine) {
                return false;
            }

            return jsEngine->LoadCard(url, cardId);
        };
        delegate_->SetLoadCardCallBack(loadCallback);
    }

    RefPtr<Framework::CardFrontendDelegateDeclarative> GetDelegate()
    {
        return delegate_;
    }

private:
    void InitializeDelegate(const RefPtr<TaskExecutor>& taskExecutor);
    RefPtr<Framework::CardFrontendDelegateDeclarative> delegate_;
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
