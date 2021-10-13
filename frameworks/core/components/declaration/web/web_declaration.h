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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_DECLARATION_WEB_WEB_DECLARATION_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_DECLARATION_WEB_WEB_DECLARATION_H

#include "core/components/declaration/common/declaration.h"
#include "core/components/declaration/web/web_client.h"
#include "frameworks/bridge/common/dom/dom_type.h"

namespace OHOS::Ace {

struct WebAttribute : Attribute {
    std::string src;
};

struct WebEvent : Event {
    EventMarker pageStartEventId;
    EventMarker pageFinishEventId;
    EventMarker pageErrorEventId;
    EventMarker messageEventId;
};

struct WebMethod : Method {
    void Reload() const
    {
        WebClient::GetInstance().ReloadWebview();
    }
};

class ACE_EXPORT WebDeclaration : public Declaration {
    DECLARE_ACE_TYPE(WebDeclaration, Declaration);

public:
    WebDeclaration() = default;
    ~WebDeclaration() override = default;
    WebMethod webMethod;

    void SetWebSrc(const std::string& src)
    {
        auto& attribute = MaybeResetAttribute<WebAttribute>(AttributeTag::SPECIALIZED_ATTR);
        attribute.src = src;
    }

    const std::string& GetWebSrc() const
    {
        auto& attribute = static_cast<WebAttribute&>(GetAttribute(AttributeTag::SPECIALIZED_ATTR));
        return attribute.src;
    }

    void SetPageStartedEventId(const EventMarker& pageStartedEventId)
    {
        auto& event = MaybeResetEvent<WebEvent>(EventTag::SPECIALIZED_EVENT);
        event.pageStartEventId = pageStartedEventId;
    }

    const EventMarker& GetPageStartedEventId() const
    {
        auto& event = static_cast<WebEvent&>(GetEvent(EventTag::SPECIALIZED_EVENT));
        return event.pageStartEventId;
    }

    void SetPageFinishedEventId(const EventMarker& pageFinishedEventId)
    {
        auto& event = MaybeResetEvent<WebEvent>(EventTag::SPECIALIZED_EVENT);
        event.pageFinishEventId = pageFinishedEventId;
    }

    const EventMarker& GetPageFinishedEventId() const
    {
        auto& event = static_cast<WebEvent&>(GetEvent(EventTag::SPECIALIZED_EVENT));
        return event.pageFinishEventId;
    }

    void SetPageErrorEventId(const EventMarker& pageErrorEventId)
    {
        auto& event = MaybeResetEvent<WebEvent>(EventTag::SPECIALIZED_EVENT);
        event.pageErrorEventId = pageErrorEventId;
    }

    const EventMarker& GetPageErrorEventId() const
    {
        auto& event = static_cast<WebEvent&>(GetEvent(EventTag::SPECIALIZED_EVENT));
        return event.pageErrorEventId;
    }

    void SetMessageEventId(const EventMarker& messageEventId)
    {
        auto& event = MaybeResetEvent<WebEvent>(EventTag::SPECIALIZED_EVENT);
        event.messageEventId = messageEventId;
    }

    const EventMarker& GetMessageEventId() const
    {
        auto& event = static_cast<WebEvent&>(GetEvent(EventTag::SPECIALIZED_EVENT));
        return event.messageEventId;
    }

protected:
    void InitSpecialized() override;
    bool SetSpecializedAttr(const std::pair<std::string, std::string>& attr) override;
    bool SetSpecializedEvent(int32_t pageId, const std::string& eventId, const std::string& event) override;
    void CallSpecializedMethod(const std::string& method, const std::string& args) override;
};

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_DECLARATION_WEB_WEB_DECLARATION_H
