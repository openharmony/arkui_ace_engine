/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_BRIDGE_CARD_FRONTEND_FORM_FRONTEND_DELEGATE_DECLARATIVE_H
#define FOUNDATION_ACE_FRAMEWORKS_BRIDGE_CARD_FRONTEND_FORM_FRONTEND_DELEGATE_DECLARATIVE_H

#include <mutex>

#include "frameworks/base/memory/ace_type.h"
#include "frameworks/base/utils/noncopyable.h"
#include "frameworks/base/utils/measure_util.h"
#include "frameworks/bridge/common/accessibility/accessibility_node_manager.h"
#include "frameworks/bridge/declarative_frontend/ng/page_router_manager.h"
#include "frameworks/bridge/declarative_frontend/frontend_delegate_declarative.h"

namespace OHOS::Ace::Framework {
// This is the primary class by which the CardFrontend delegates

using LoadCardCallback = std::function<bool(const std::string&, int64_t cardId, const std::string&)>;
using UpdateCardDataCallback = std::function<void(const std::string&)>;

class ACE_EXPORT FormFrontendDelegateDeclarative : public FrontendDelegateDeclarative {
    DECLARE_ACE_TYPE(FormFrontendDelegateDeclarative, FrontendDelegateDeclarative);
public:
    FormFrontendDelegateDeclarative(const RefPtr<TaskExecutor>& taskExecutor, const LoadJsCallback& loadCallback,
        const JsMessageDispatcherSetterCallback& transferCallback, const EventCallback& asyncEventCallback,
        const EventCallback& syncEventCallback, const UpdatePageCallback& updatePageCallback,
        const ResetStagingPageCallback& resetLoadingPageCallback, const DestroyPageCallback& destroyPageCallback,
        const DestroyApplicationCallback& destroyApplicationCallback,
        const UpdateApplicationStateCallback& updateApplicationStateCallback, const TimerCallback& timerCallback,
        const MediaQueryCallback& mediaQueryCallback, const LayoutInspectorCallback& layoutInspectorCallback,
        const DrawInspectorCallback& drawInspectorCallback,
        const DrawChildrenInspectorCallback& drawChildrenInspectorCallback,
		const RequestAnimationCallback& requestAnimationCallback,
        const JsCallback& jsCallback, const OnWindowDisplayModeChangedCallBack& onWindowDisplayModeChangedCallBack,
        const OnConfigurationUpdatedCallBack& onConfigurationUpdatedCallBack,
        const OnSaveAbilityStateCallBack& onSaveAbilityStateCallBack,
        const OnRestoreAbilityStateCallBack& onRestoreAbilityStateCallBack, const OnNewWantCallBack& onNewWantCallBack,
        const OnMemoryLevelCallBack& onMemoryLevelCallBack,
        const OnStartContinuationCallBack& onStartContinuationCallBack,
        const OnCompleteContinuationCallBack& onCompleteContinuationCallBack,
        const OnRemoteTerminatedCallBack& onRemoteTerminatedCallBack, const OnSaveDataCallBack& onSaveDataCallBack,
        const OnRestoreDataCallBack& onRestoreDataCallBack, const ExternalEventCallback& externalEventCallback) :
            FrontendDelegateDeclarative(taskExecutor, loadCallback, transferCallback, asyncEventCallback,
              syncEventCallback, updatePageCallback,
                resetLoadingPageCallback, destroyPageCallback,
              destroyApplicationCallback,
                updateApplicationStateCallback, timerCallback,
                mediaQueryCallback, layoutInspectorCallback,
				drawInspectorCallback, drawChildrenInspectorCallback,
				requestAnimationCallback,
                jsCallback, onWindowDisplayModeChangedCallBack,
                onConfigurationUpdatedCallBack,
                onSaveAbilityStateCallBack,
              onRestoreAbilityStateCallBack, onNewWantCallBack,
                onMemoryLevelCallBack,
                onStartContinuationCallBack,
              onCompleteContinuationCallBack,
                onRemoteTerminatedCallBack, onSaveDataCallBack,
                onRestoreDataCallBack, externalEventCallback)
    {}

    ~FormFrontendDelegateDeclarative() override;

    UIContentErrorCode RunCard(const std::string& url, const std::string& params, const std::string& profile,
        int64_t cardId, const std::string& entryPoint = "");

    void FireCardEvent(const EventMarker& eventMarker, const std::string& params = "");

    void FireCardAction(const std::string& action);

    void SetLoadCardCallBack(const LoadCardCallback& loadCallback)
    {
        auto pageRouterManager = GetPageRouterManager();
        CHECK_NULL_VOID(pageRouterManager);
        pageRouterManager->SetLoadCardCallback(loadCallback);
    }
    void LoadResourceConfiguration(std::map<std::string, std::string>& mediaResourceFileMap,
        std::unique_ptr<JsonValue>& currentResourceData) override
    {}
    void UpdatePageData(const std::string& dataList)
    {
        std::lock_guard<std::mutex> lock(mutex_);
        if (updateCardData_) {
            updateCardData_(dataList);
        } else {
            cardData_ = dataList;
        }
    }

    void SetUpdateCardDataCallback(UpdateCardDataCallback&& callback)
    {
        std::lock_guard<std::mutex> lock(mutex_);
        updateCardData_ = std::move(callback);
    }

    void UpdatePageDataImmediately()
    {
        std::lock_guard<std::mutex> lock(mutex_);
        if (!cardData_.empty() && updateCardData_) {
            updateCardData_(cardData_);
        }
    }

    void RegisterFont(const std::string& familyName, const std::string& familySrc, const std::string& bundleName = "",
        const std::string& moduleName = "") override;

private:
    UpdateCardDataCallback updateCardData_;
    std::string cardData_;
    mutable std::mutex mutex_;
};
} // namespace OHOS::Ace::Framework

#endif // FOUNDATION_ACE_FRAMEWORKS_BRIDGE_CARD_FRONTEND_FORM_FRONTEND_DELEGATE_DECLARATIVE_H
