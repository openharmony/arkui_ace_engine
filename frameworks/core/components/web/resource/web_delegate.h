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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_WEB_RESOURCE_WEB_DELEGATE_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_WEB_RESOURCE_WEB_DELEGATE_H

#include <list>

#include "core/components/common/layout/constants.h"
#include "core/components/web/resource/web_client_impl.h"
#include "core/components/web/resource/web_resource.h"
#include "core/components/web/web_component.h"
#if !defined(WINDOWS_PLATFORM) and !defined(MAC_PLATFORM) and defined(OHOS_STANDARD_SYSTEM)
#include "webview_helper.h"
#include "window.h"
#endif

namespace OHOS::Ace {

class WebDelegate : public WebResource {
    DECLARE_ACE_TYPE(WebDelegate, WebResource);

public:
    using CreatedCallback = std::function<void()>;
    using ReleasedCallback = std::function<void(bool)>;
    using EventCallback = std::function<void(const std::string&)>;
    using EventCallbackV2 = std::function<void(const std::shared_ptr<BaseEventInfo>&)>;
    enum class State: char {
        WAITINGFORSIZE,
        CREATING,
        CREATED,
        CREATEFAILED,
        RELEASED,
    };

    WebDelegate() = delete;
    ~WebDelegate() override;
    WebDelegate(const WeakPtr<PipelineContext>& context, ErrorCallback&& onError, const std::string& type)
        : WebResource(type, context, std::move(onError)), state_(State::WAITINGFORSIZE)
    {
        ACE_DCHECK(!type.empty());
    }

    void CreatePlatformResource(const Size& size, const Offset& position,
        const WeakPtr<PipelineContext>& context);
    void CreatePluginResource(const Size& size, const Offset& position,
        const WeakPtr<PipelineContext>& context);
    void AddCreatedCallback(const CreatedCallback& createdCallback);
    void RemoveCreatedCallback();
    void AddReleasedCallback(const ReleasedCallback& releasedCallback);
    void SetComponent(const RefPtr<WebComponent>& component);
    void RemoveReleasedCallback();
    void Reload();
    void UpdateUrl(const std::string& url);
#if !defined(WINDOWS_PLATFORM) and !defined(MAC_PLATFORM) and defined(OHOS_STANDARD_SYSTEM)
    void InitOHOSWeb(const WeakPtr<PipelineContext>& context);
    void InitWebViewWithWindow();
    void ShowWebView()
    {
        if (window_) {
            window_->Show();
        }
    }

    void HideWebView()
    {
        if (window_) {
            window_->Hide();
        }
    }
#endif
    void OnPageStarted(const std::string& param);
    void OnPageFinished(const std::string& param);
    void OnRequestFocus();
    void OnPageError(const std::string& param);
    void OnMessage(const std::string& param);
    void OnRouterPush(const std::string& param);
private:
    void InitWebEvent();
    void RegisterWebEvent();
    void ReleasePlatformResource();
    void Stop();
    void UnregisterEvent();
    std::string GetUrlStringParam(const std::string& param, const std::string& name) const;
    void CallWebRouterBack();
    void CallPopPageSuccessPageUrl(const std::string& url);
    void CallIsPagePathInvalid(const bool& isPageInvalid);

    void BindRouterBackMethod();
    void BindPopPageSuccessMethod();
    void BindIsPagePathInvalidMethod();
#if !defined(WINDOWS_PLATFORM) and !defined(MAC_PLATFORM) and defined(OHOS_STANDARD_SYSTEM)
    sptr<Rosen::Window> CreateWindow();
    void LoadUrl(std::string url);
    void ExecuteTypeScript(std::string jscode);
    void LoadDataWithBaseUrl(
        std::string baseUrl, std::string data, std::string mimeType, std::string encoding, std::string historyUrl);
    void SetWebCallBack();
#endif

    RefPtr<WebComponent> webComponent_;
    std::list<CreatedCallback> createdCallbacks_;
    std::list<ReleasedCallback> releasedCallbacks_;
    EventCallback onPageStarted_;
    EventCallback onPageFinished_;
    EventCallback onPageError_;
    EventCallback onMessage_;
    Method reloadMethod_;
    Method updateUrlMethod_;
    Method routerBackMethod_;
    Method changePageUrlMethod_;
    Method isPagePathInvalidMethod_;
    State state_ {State::WAITINGFORSIZE};
#if !defined(WINDOWS_PLATFORM) and !defined(MAC_PLATFORM) and defined(OHOS_STANDARD_SYSTEM)
    std::shared_ptr<WebView> webview_;
    sptr<Rosen::Window> window_;
    bool isCreateWebView_ = false;

    EventCallbackV2 onPageFinishedV2_;
    EventCallbackV2 onRequestFocusV2_;

#endif
};

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_WEB_RESOURCE_WEB_DELEGATE_H
