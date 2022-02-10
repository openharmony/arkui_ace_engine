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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_WEB_WEB_COMPONENT_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_WEB_WEB_COMPONENT_H

#include <string>

#include "base/geometry/size.h"
#include "base/utils/utils.h"
#include "core/components/declaration/common/declaration.h"
#include "core/components_v2/common/common_def.h"
#include "core/components/declaration/web/web_client.h"
#include "core/components/declaration/web/web_declaration.h"
#include "core/pipeline/base/element.h"

namespace OHOS::Ace {

class WebDelegate;

class WebController : public virtual AceType {
    DECLARE_ACE_TYPE(WebController, AceType);

public:
    using LoadUrlImpl = std::function<void(std::string)>;
    using AccessBackwardImpl = std::function<bool()>;
    using AccessForwardImpl = std::function<bool()>;
    using AccessStepImpl = std::function<bool(int32_t)>;
    void LoadUrl(std::string url) const
    {
        if (loadUrlImpl_) {
            loadUrlImpl_(url);
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

    void SetLoadUrltImpl(LoadUrlImpl && loadUrlImpl)
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

    using ExecuteTypeScriptImpl = std::function<void(std::string)>;
    void ExecuteTypeScript(std::string jscode) const
    {
        if (executeTypeScriptImpl_) {
            executeTypeScriptImpl_(jscode);
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

    void Reload() const
    {
        declaration_->webMethod.Reload();
    }
private:
    RefPtr<WebDeclaration> declaration_;
    LoadUrlImpl loadUrlImpl_;
    AccessBackwardImpl accessBackwardImpl_;
    AccessForwardImpl accessForwardImpl_;
    AccessStepImpl accessStepImpl_;
    ExecuteTypeScriptImpl executeTypeScriptImpl_;
    LoadDataWithBaseUrlImpl loadDataWithBaseUrlImpl_;
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
};

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_WEB_WEB_COMPONENT_H
