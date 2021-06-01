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
#include "core/pipeline/base/element.h"

namespace OHOS::Ace {

class WebClient {
public:
    using ReloadCallback = std::function<bool()>;
    using UpdateUrlCallback = std::function<void(const std::string& url)>;
    WebClient &operator = (const WebClient &) = delete;
    WebClient(const WebClient &) = delete;
    ~WebClient() = default;

    static WebClient& GetInstance()
    {
        static WebClient instance;
        return instance;
    }

    void RegisterReloadCallback(ReloadCallback&& callback)
    {
        reloadCallback_ = callback;
    }

    void RegisterUpdageUrlCallback(UpdateUrlCallback&& callback)
    {
        updateUrlCallback_ = callback;
    }

    void UpdateWebviewUrl(const std::string& url)
    {
        if (updateUrlCallback_) {
            return updateUrlCallback_(url);
        }
    }

    bool ReloadWebview()
    {
        if (reloadCallback_) {
            return reloadCallback_();
        } else {
            return false;
        }
    }

private:
    WebClient() = default;
    ReloadCallback reloadCallback_;
    UpdateUrlCallback updateUrlCallback_;
};

class WebDelegate;
// A component can show HTML5 webpages.
class WebComponent : public RenderComponent {
    DECLARE_ACE_TYPE(WebComponent, RenderComponent);

public:
    using CreatedCallback = std::function<void()>;
    using ReleasedCallback = std::function<void(bool)>;
    using ErrorCallback = std::function<void(const std::string&, const std::string&)>;
    using MethodCall = std::function<void(const std::string&)>;
    using Method = std::string;

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
        src_ = src;
    }

    const std::string& GetSrc() const
    {
        return src_;
    }

    void SetPageStartedEventId(const EventMarker& pageStartedEventId)
    {
        pageStartedEventId_ = pageStartedEventId;
    }

    const EventMarker& GetPageStartedEventId() const
    {
        return pageStartedEventId_;
    }

    void SetPageFinishedEventId(const EventMarker& pageFinishedEventId)
    {
        pageFinishedEventId_ = pageFinishedEventId;
    }

    const EventMarker& GetPageFinishedEventId() const
    {
        return pageFinishedEventId_;
    }

    void SetPageErrorEventId(const EventMarker& pageErrorEventId)
    {
        pageErrorEventId_ = pageErrorEventId;
    }

    const EventMarker& GetPageErrorEventId() const
    {
        return pageErrorEventId_;
    }

    void Reload()
    {
        WebClient::GetInstance().ReloadWebview();
    }

private:
    CreatedCallback createdCallback_ = nullptr;
    ReleasedCallback releasedCallback_ = nullptr;
    ErrorCallback errorCallback_ = nullptr;
    RefPtr<WebDelegate> delegate_;
    EventMarker pageStartedEventId_;
    EventMarker pageFinishedEventId_;
    EventMarker pageErrorEventId_;

    std::string type_;
    std::string src_;
};

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_WEB_WEB_COMPONENT_H
