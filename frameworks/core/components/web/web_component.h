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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_WEB_WEB_COMPONENT_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_WEB_WEB_COMPONENT_H

#include <string>

#include "base/geometry/size.h"
#include "base/utils/utils.h"
#include "core/components/declaration/common/declaration.h"
#include "core/components_v2/common/common_def.h"
#include "core/components/declaration/web/web_client.h"
#include "core/components/declaration/web/web_declaration.h"
#include "core/focus/focus_node.h"
#include "core/pipeline/base/element.h"

namespace OHOS::Ace {

class WebDelegate;

class WebController : public virtual AceType {
    DECLARE_ACE_TYPE(WebController, AceType);

public:
    using LoadUrlImpl = std::function<void(std::string, const std::map<std::string, std::string>&)>;
    using AccessBackwardImpl = std::function<bool()>;
    using AccessForwardImpl = std::function<bool()>;
    using AccessStepImpl = std::function<bool(int32_t)>;
    using BackwardImpl = std::function<void()>;
    using ForwardImpl = std::function<void()>;
    void LoadUrl(std::string url, std::map<std::string, std::string>& httpHeaders) const
    {
        if (loadUrlImpl_) {
            loadUrlImpl_(url, httpHeaders);
        }
    }

    bool AccessStep(int32_t step)
    {
        if (accessStepImpl_) {
            return accessStepImpl_(step);
        }
        return false;
    }

    bool AccessBackward()
    {
        if (accessBackwardImpl_) {
            return accessBackwardImpl_();
        }
        return false;
    }

    bool AccessForward()
    {
        if (accessForwardImpl_) {
            return accessForwardImpl_();
        }
        return false;
    }

    void Backward()
    {
        LOGI("Start backward.");
        if (backwardImpl_) {
            backwardImpl_();
        }
    }

    void Forward()
    {
        LOGI("Start forward.");
        if (forwardimpl_) {
            forwardimpl_();
        }
    }

    void SetLoadUrlImpl(LoadUrlImpl && loadUrlImpl)
    {
        loadUrlImpl_ = std::move(loadUrlImpl);
    }

    void SetAccessBackwardImpl(AccessBackwardImpl && accessBackwardImpl)
    {
        accessBackwardImpl_ = std::move(accessBackwardImpl);
    }

    void SetAccessForwardImpl(AccessForwardImpl && accessForwardImpl)
    {
        accessForwardImpl_ = std::move(accessForwardImpl);
    }

    void SetAccessStepImpl(AccessStepImpl && accessStepImpl)
    {
        accessStepImpl_ = std::move(accessStepImpl);
    }

    void SetBackwardImpl(BackwardImpl && backwardImpl)
    {
        backwardImpl_ = std::move(backwardImpl);
    }

    void SetForwardImpl(ForwardImpl && forwardImpl)
    {
        forwardimpl_ = std::move(forwardImpl);
    }

    using ExecuteTypeScriptImpl = std::function<void(std::string, std::function<void(std::string)>&&)>;
    void ExecuteTypeScript(std::string jscode, std::function<void(std::string)>&& callback) const
    {
        if (executeTypeScriptImpl_) {
            executeTypeScriptImpl_(jscode, std::move(callback));
        }
    }
    void SetExecuteTypeScriptImpl(ExecuteTypeScriptImpl && executeTypeScriptImpl)
    {
        executeTypeScriptImpl_ = std::move(executeTypeScriptImpl);
    }

    using LoadDataWithBaseUrlImpl = std::function<void(
        std::string, std::string, std::string, std::string, std::string)>;
    void LoadDataWithBaseUrl(std::string baseUrl, std::string data, std::string mimeType, std::string encoding,
        std::string historyUrl) const
    {
        if (loadDataWithBaseUrlImpl_) {
            loadDataWithBaseUrlImpl_(baseUrl, data, mimeType, encoding, historyUrl);
        }
    }

    void SetLoadDataWithBaseUrlImpl(LoadDataWithBaseUrlImpl && loadDataWithBaseUrlImpl)
    {
        loadDataWithBaseUrlImpl_ = std::move(loadDataWithBaseUrlImpl);
    }

    using RefreshImpl = std::function<void()>;
    void Refresh() const
    {
        if (refreshImpl_) {
            refreshImpl_();
        }
    }
    void SetRefreshImpl(RefreshImpl && refreshImpl)
    {
        refreshImpl_ = std::move(refreshImpl);
    }

    using StopLoadingImpl = std::function<void()>;
    void StopLoading() const
    {
        if (stopLoadingImpl_) {
            stopLoadingImpl_();
        }
    }
    void SetStopLoadingImpl(StopLoadingImpl && stopLoadingImpl)
    {
        stopLoadingImpl_ = std::move(stopLoadingImpl);
    }

    using GetHitTestResultImpl = std::function<int()>;
    int GetHitTestResult()
    {
        if (getHitTestResultImpl_) {
            return getHitTestResultImpl_();
        } else {
            return 0;
        }
    }
    void SetGetHitTestResultImpl(GetHitTestResultImpl && getHitTestResultImpl)
    {
        getHitTestResultImpl_ = std::move(getHitTestResultImpl);
    }

    using AddJavascriptInterfaceImpl =
        std::function<void(const std::string&, const std::vector<std::string>&)>;
    void AddJavascriptInterface(const std::string& objectName, const std::vector<std::string>& methodList)
    {
        if (addJavascriptInterfaceImpl_) {
            addJavascriptInterfaceImpl_(objectName, methodList);
        }
    }
    void SetAddJavascriptInterfaceImpl(AddJavascriptInterfaceImpl && addJavascriptInterfaceImpl)
    {
        addJavascriptInterfaceImpl_ = std::move(addJavascriptInterfaceImpl);
    }

    using RemoveJavascriptInterfaceImpl = std::function<void(std::string, const std::vector<std::string>&)>;
    void RemoveJavascriptInterface(std::string objectName, const std::vector<std::string>& methodList)
    {
        if (removeJavascriptInterfaceImpl_) {
            removeJavascriptInterfaceImpl_(objectName, methodList);
        }
    }
    void SetRemoveJavascriptInterfaceImpl(RemoveJavascriptInterfaceImpl && removeJavascriptInterfaceImpl)
    {
        removeJavascriptInterfaceImpl_ = std::move(removeJavascriptInterfaceImpl);
    }

    using RequestFocusImpl = std::function<void()>;
    void RequestFocus()
    {
        if (requestFocusImpl_) {
            return requestFocusImpl_();
        }
    }
    void SetRequestFocusImpl(RequestFocusImpl  && requestFocusImpl)
    {
        requestFocusImpl_ = std::move(requestFocusImpl);
    }

    void Reload() const
    {
        declaration_->webMethod.Reload();
    }

private:
    RefPtr<WebDeclaration> declaration_;
    LoadUrlImpl loadUrlImpl_;
    
    // Forward and Backward
    AccessBackwardImpl accessBackwardImpl_;
    AccessForwardImpl accessForwardImpl_;
    AccessStepImpl accessStepImpl_;
    BackwardImpl backwardImpl_;
    ForwardImpl forwardimpl_;

    ExecuteTypeScriptImpl executeTypeScriptImpl_;
    LoadDataWithBaseUrlImpl loadDataWithBaseUrlImpl_;
    RefreshImpl refreshImpl_;
    StopLoadingImpl stopLoadingImpl_;
    GetHitTestResultImpl getHitTestResultImpl_;
    AddJavascriptInterfaceImpl addJavascriptInterfaceImpl_;
    RemoveJavascriptInterfaceImpl removeJavascriptInterfaceImpl_;
    RequestFocusImpl requestFocusImpl_;
};

// A component can show HTML5 webpages.
class ACE_EXPORT WebComponent : public RenderComponent {
    DECLARE_ACE_TYPE(WebComponent, RenderComponent);

public:
    using CreatedCallback = std::function<void()>;
    using ReleasedCallback = std::function<void(bool)>;
    using ErrorCallback = std::function<void(const std::string&, const std::string&)>;
    using MethodCall = std::function<void(const std::string&)>;
    using Method = std::string;
    ACE_DEFINE_COMPONENT_EVENT(OnPageStart, void(std::string));
    ACE_DEFINE_COMPONENT_EVENT(OnPageFinish, void(std::string));
    ACE_DEFINE_COMPONENT_EVENT(OnError, void(std::string));
    ACE_DEFINE_COMPONENT_EVENT(OnMessage, void(std::string));

    WebComponent() = default;
    explicit WebComponent(const std::string& type);
    ~WebComponent() override = default;

    RefPtr<RenderNode> CreateRenderNode() override;
    RefPtr<Element> CreateElement() override;

    void SetType(const std::string& type)
    {
        type_ = type;
    }

    const std::string& GetType() const
    {
        return type_;
    }

    void SetSrc(const std::string& src)
    {
        declaration_->SetWebSrc(src);
    }

    const std::string& GetSrc() const
    {
        return declaration_->GetWebSrc();
    }

    void SetPageStartedEventId(const EventMarker& pageStartedEventId)
    {
        declaration_->SetPageStartedEventId(pageStartedEventId);
    }

    const EventMarker& GetPageStartedEventId() const
    {
        return declaration_->GetPageStartedEventId();
    }

    void SetPageFinishedEventId(const EventMarker& pageFinishedEventId)
    {
        declaration_->SetPageFinishedEventId(pageFinishedEventId);
    }

    const EventMarker& GetPageFinishedEventId() const
    {
        return declaration_->GetPageFinishedEventId();
    }

    void SetRequestFocusEventId(const EventMarker& requestFocusEventId)
    {
        declaration_->SetRequestFocusEventId(requestFocusEventId);
    }

    const EventMarker& GetRequestFocusEventId() const
    {
        return declaration_->GetRequestFocusEventId();
    }

    void SetDownloadStartEventId(const EventMarker& downloadStartEventId)
    {
        declaration_->SetDownloadStartEventId(downloadStartEventId);
    }

    const EventMarker& GetDownloadStartEventId() const
    {
        return declaration_->GetDownloadStartEventId();
    }

    void SetPageErrorEventId(const EventMarker& pageErrorEventId)
    {
        declaration_->SetPageErrorEventId(pageErrorEventId);
    }

    const EventMarker& GetPageErrorEventId() const
    {
        return declaration_->GetPageErrorEventId();
    }

    void SetMessageEventId(const EventMarker& messageEventId)
    {
        declaration_->SetMessageEventId(messageEventId);
    }

    const EventMarker& GetMessageEventId() const
    {
        return declaration_->GetMessageEventId();
    }

    void SetDeclaration(const RefPtr<WebDeclaration>& declaration)
    {
        if (declaration) {
            declaration_ = declaration;
        }
    }

    RefPtr<WebController> GetController() const
    {
        return webController_;
    }

    void SetWebController(const RefPtr<WebController>& webController)
    {
        webController_ = webController;
    }

    bool GetJsEnabled() const
    {
        return isJsEnabled_;
    }

    void SetJsEnabled(bool isEnabled)
    {
        isJsEnabled_ = isEnabled;
    }

    bool GetContentAccessEnabled() const
    {
        return isContentAccessEnabled_;
    }

    void SetContentAccessEnabled(bool isEnabled)
    {
        isContentAccessEnabled_ = isEnabled;
    }

    bool GetFileAccessEnabled() const
    {
        return isFileAccessEnabled_;
    }

    void SetFileAccessEnabled(bool isEnabled)
    {
        isFileAccessEnabled_ = isEnabled;
    }

    void RequestFocus();

private:
    RefPtr<WebDeclaration> declaration_;
    CreatedCallback createdCallback_ = nullptr;
    ReleasedCallback releasedCallback_ = nullptr;
    ErrorCallback errorCallback_ = nullptr;
    RefPtr<WebDelegate> delegate_;
    RefPtr<WebController> webController_;
    std::string type_;
    bool isJsEnabled_ = true;
    bool isContentAccessEnabled_ = true;
    bool isFileAccessEnabled_ = true;
    WeakPtr<FocusNode> focusElement_;
};

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_WEB_WEB_COMPONENT_H
