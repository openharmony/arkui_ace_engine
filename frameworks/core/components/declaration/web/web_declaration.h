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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_DECLARATION_WEB_WEB_DECLARATION_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_DECLARATION_WEB_WEB_DECLARATION_H

#include "core/components/declaration/common/declaration.h"
#include "core/components/declaration/web/web_client.h"
#include "frameworks/bridge/common/dom/dom_type.h"

namespace OHOS::Ace {

struct WebAttribute : Attribute {
    std::string src;
    std::string data;
};

struct WebEvent : Event {
    EventMarker pageStartEventId;
    EventMarker pageFinishEventId;
    EventMarker titleReceiveEventId;
    EventMarker geolocationHideEventId;
    EventMarker geolocationShowEventId;
    EventMarker requestFocusEventId;
    EventMarker pageErrorEventId;
    EventMarker httpErrorEventId;
    EventMarker messageEventId;
    EventMarker downloadStartEventId;
    EventMarker renderExitedEventId;
    EventMarker refreshAccessedHistoryId;
    EventMarker resourceLoadId;
    EventMarker scaleChangeId;
    EventMarker permissionRequestId;
    EventMarker searchResultReceiveEventId;
    EventMarker scrollId;
    EventMarker fullScreenExitEventId;
    EventMarker windowExitId;
    EventMarker overScrollId;
    EventMarker nativeEmbedLifecycleChangeId;
    EventMarker nativeEmbedVisibilityChangeId;
    EventMarker nativeEmbedGestureEventId;
    EventMarker renderProcessNotRespondingId;
    EventMarker renderProcessRespondingId;
    EventMarker viewportFitChangedId;
    EventMarker adsBlockedEventId;
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

    void SetWebData(const std::string& data)
    {
        auto& attribute = MaybeResetAttribute<WebAttribute>(AttributeTag::SPECIALIZED_ATTR);
        attribute.data = data;
    }

    const std::string& GetWebData() const
    {
        auto& attribute = static_cast<WebAttribute&>(GetAttribute(AttributeTag::SPECIALIZED_ATTR));
        return attribute.data;
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

    void SetTitleReceiveEventId(const EventMarker& titleReceiveEventId)
    {
        auto& event = MaybeResetEvent<WebEvent>(EventTag::SPECIALIZED_EVENT);
        event.titleReceiveEventId = titleReceiveEventId;
    }

    const EventMarker& GetTitleReceiveEventId() const
    {
        auto& event = static_cast<WebEvent&>(GetEvent(EventTag::SPECIALIZED_EVENT));
        return event.titleReceiveEventId;
    }

    void SetOnFullScreenExitEventId(const EventMarker& fullScreenExitEventId)
    {
        auto& event = MaybeResetEvent<WebEvent>(EventTag::SPECIALIZED_EVENT);
        event.fullScreenExitEventId = fullScreenExitEventId;
    }

    const EventMarker& GetOnFullScreenExitEventId() const
    {
        auto& event = static_cast<WebEvent&>(GetEvent(EventTag::SPECIALIZED_EVENT));
        return event.fullScreenExitEventId;
    }

    void SetGeolocationHideEventId(const EventMarker& geolocationHideEventId)
    {
        auto& event = MaybeResetEvent<WebEvent>(EventTag::SPECIALIZED_EVENT);
        event.geolocationHideEventId = geolocationHideEventId;
    }

    const EventMarker& GetGeolocationHideEventId() const
    {
        auto& event = static_cast<WebEvent&>(GetEvent(EventTag::SPECIALIZED_EVENT));
        return event.geolocationHideEventId;
    }

    void SetGeolocationShowEventId(const EventMarker& geolocationShowEventId)
    {
        auto& event = MaybeResetEvent<WebEvent>(EventTag::SPECIALIZED_EVENT);
        event.geolocationShowEventId = geolocationShowEventId;
    }

    const EventMarker& GetGeolocationShowEventId() const
    {
        auto& event = static_cast<WebEvent&>(GetEvent(EventTag::SPECIALIZED_EVENT));
        return event.geolocationShowEventId;
    }

    void SetDownloadStartEventId(const EventMarker& downloadStartEventId)
    {
        auto& event = MaybeResetEvent<WebEvent>(EventTag::SPECIALIZED_EVENT);
        event.downloadStartEventId = downloadStartEventId;
    }

    const EventMarker& GetDownloadStartEventId() const
    {
        auto& event = static_cast<WebEvent&>(GetEvent(EventTag::SPECIALIZED_EVENT));
        return event.downloadStartEventId;
    }

    void SetRequestFocusEventId(const EventMarker& requestFocusEventId)
    {
        auto& event = MaybeResetEvent<WebEvent>(EventTag::SPECIALIZED_EVENT);
        event.requestFocusEventId = requestFocusEventId;
    }

    const EventMarker& GetRequestFocusEventId() const
    {
        auto& event = static_cast<WebEvent&>(GetEvent(EventTag::SPECIALIZED_EVENT));
        return event.requestFocusEventId;
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

    void SetHttpErrorEventId(const EventMarker& httpErrorEventId)
    {
        auto& event = MaybeResetEvent<WebEvent>(EventTag::SPECIALIZED_EVENT);
        event.httpErrorEventId = httpErrorEventId;
    }

    const EventMarker& GetHttpErrorEventId() const
    {
        auto& event = static_cast<WebEvent&>(GetEvent(EventTag::SPECIALIZED_EVENT));
        return event.httpErrorEventId;
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

    void SetRenderExitedId(const EventMarker& renderExitedEventId)
    {
        auto& event = MaybeResetEvent<WebEvent>(EventTag::SPECIALIZED_EVENT);
        event.renderExitedEventId = renderExitedEventId;
    }

    const EventMarker& GetRenderExitedId() const
    {
        auto& event = static_cast<WebEvent&>(GetEvent(EventTag::SPECIALIZED_EVENT));
        return event.renderExitedEventId;
    }

    void SetRefreshAccessedHistoryId(const EventMarker& refreshAccessedHistoryId)
    {
        auto& event = MaybeResetEvent<WebEvent>(EventTag::SPECIALIZED_EVENT);
        event.refreshAccessedHistoryId = refreshAccessedHistoryId;
    }

    const EventMarker& GetRefreshAccessedHistoryId() const
    {
        auto& event = static_cast<WebEvent&>(GetEvent(EventTag::SPECIALIZED_EVENT));
        return event.refreshAccessedHistoryId;
    }

    void SetResourceLoadId(const EventMarker& resourceLoadId)
    {
        auto& event = MaybeResetEvent<WebEvent>(EventTag::SPECIALIZED_EVENT);
        event.resourceLoadId = resourceLoadId;
    }

    const EventMarker& GetResourceLoadId() const
    {
        auto& event = static_cast<WebEvent&>(GetEvent(EventTag::SPECIALIZED_EVENT));
        return event.resourceLoadId;
    }

    void SetScaleChangeId(const EventMarker& scaleChangeId)
    {
        auto& event = MaybeResetEvent<WebEvent>(EventTag::SPECIALIZED_EVENT);
        event.scaleChangeId = scaleChangeId;
    }

    const EventMarker& GetScaleChangeId() const
    {
        auto& event = static_cast<WebEvent&>(GetEvent(EventTag::SPECIALIZED_EVENT));
        return event.scaleChangeId;
    }

    void SetScrollId(const EventMarker& scrollId)
    {
        auto& event = MaybeResetEvent<WebEvent>(EventTag::SPECIALIZED_EVENT);
        event.scrollId = scrollId;
    }

    const EventMarker& GetScrollId() const
    {
        auto& event = static_cast<WebEvent&>(GetEvent(EventTag::SPECIALIZED_EVENT));
        return event.scrollId;
    }

    void SetPermissionRequestEventId(const EventMarker& permissionRequestId)
    {
        auto& event = MaybeResetEvent<WebEvent>(EventTag::SPECIALIZED_EVENT);
        event.permissionRequestId = permissionRequestId;
    }

    const EventMarker& GetPermissionRequestEventId() const
    {
        auto& event = static_cast<WebEvent&>(GetEvent(EventTag::SPECIALIZED_EVENT));
        return event.permissionRequestId;
    }

    void SetSearchResultReceiveEventId(const EventMarker& searchResultReceiveEventId)
    {
        auto& event = MaybeResetEvent<WebEvent>(EventTag::SPECIALIZED_EVENT);
        event.searchResultReceiveEventId = searchResultReceiveEventId;
    }

    const EventMarker& GetSearchResultReceiveEventId() const
    {
        auto& event = static_cast<WebEvent&>(GetEvent(EventTag::SPECIALIZED_EVENT));
        return event.searchResultReceiveEventId;
    }

    void SetWindowExitEventId(const EventMarker& windowExitId)
    {
        auto& event = MaybeResetEvent<WebEvent>(EventTag::SPECIALIZED_EVENT);
        event.windowExitId = windowExitId;
    }

    const EventMarker& GetWindowExitEventId() const
    {
        auto& event = static_cast<WebEvent&>(GetEvent(EventTag::SPECIALIZED_EVENT));
        return event.windowExitId;
    }

    void SetOverScrollId(const EventMarker& overScrollId)
    {
        auto& event = MaybeResetEvent<WebEvent>(EventTag::SPECIALIZED_EVENT);
        event.overScrollId = overScrollId;
    }

    const EventMarker& GetOverScrollId() const
    {
        auto& event = static_cast<WebEvent&>(GetEvent(EventTag::SPECIALIZED_EVENT));
        return event.overScrollId;
    }

    void SetNativeEmbedLifecycleChangeId(const EventMarker& embedLifecycleChangeId)
    {
        auto& event = MaybeResetEvent<WebEvent>(EventTag::SPECIALIZED_EVENT);
        event.nativeEmbedLifecycleChangeId = embedLifecycleChangeId;
    }

    const EventMarker& GetNativeEmbedLifecycleChangeId() const
    {
        auto& event = static_cast<WebEvent&>(GetEvent(EventTag::SPECIALIZED_EVENT));
        return event.nativeEmbedLifecycleChangeId;
    }

    void SetNativeEmbedVisibilityChangeId(const EventMarker& embedVisibilityChangeId)
    {
        auto& event = MaybeResetEvent<WebEvent>(EventTag::SPECIALIZED_EVENT);
        event.nativeEmbedVisibilityChangeId = embedVisibilityChangeId;
    }

    const EventMarker& GetNativeEmbedVisibilityChangeId() const
    {
        auto& event = static_cast<WebEvent&>(GetEvent(EventTag::SPECIALIZED_EVENT));
        return event.nativeEmbedVisibilityChangeId;
    }
    
    void SetNativeEmbedGestureEventId(const EventMarker& embedGestureEventId)
    {
        auto& event = MaybeResetEvent<WebEvent>(EventTag::SPECIALIZED_EVENT);
        event.nativeEmbedGestureEventId = embedGestureEventId;
    }

    const EventMarker& GetNativeEmbedGestureEventId() const
    {
        auto& event = static_cast<WebEvent&>(GetEvent(EventTag::SPECIALIZED_EVENT));
        return event.nativeEmbedGestureEventId;
    }

    void SetRenderProcessNotRespondingId(const EventMarker& renderProcessNotRespondingId)
    {
        auto& event = MaybeResetEvent<WebEvent>(EventTag::SPECIALIZED_EVENT);
        event.renderProcessNotRespondingId = renderProcessNotRespondingId;
    }

    const EventMarker& GetRenderProcessNotRespondingId() const
    {
        auto& event = static_cast<WebEvent&>(GetEvent(EventTag::SPECIALIZED_EVENT));
        return event.renderProcessNotRespondingId;
    }

    void SetRenderProcessRespondingId(const EventMarker& renderProcessRespondingId)
    {
        auto& event = MaybeResetEvent<WebEvent>(EventTag::SPECIALIZED_EVENT);
        event.renderProcessRespondingId = renderProcessRespondingId;
    }

    const EventMarker& GetRenderProcessRespondingId() const
    {
        auto& event = static_cast<WebEvent&>(GetEvent(EventTag::SPECIALIZED_EVENT));
        return event.renderProcessRespondingId;
    }

    void SetViewportFitChangedId(const EventMarker& viewportFitChangedId)
    {
        auto& event = MaybeResetEvent<WebEvent>(EventTag::SPECIALIZED_EVENT);
        event.viewportFitChangedId = viewportFitChangedId;
    }

    const EventMarker& GetViewportFitChangedId() const
    {
        auto& event = static_cast<WebEvent&>(GetEvent(EventTag::SPECIALIZED_EVENT));
        return event.viewportFitChangedId;
    }

    void SetAdsBlockedEventId(const EventMarker& adsBlockedEventId)
    {
        auto& event = MaybeResetEvent<WebEvent>(EventTag::SPECIALIZED_EVENT);
        event.adsBlockedEventId = adsBlockedEventId;
    }

    const EventMarker& GetAdsBlockedEventId() const
    {
        auto& event = static_cast<WebEvent&>(GetEvent(EventTag::SPECIALIZED_EVENT));
        return event.geolocationShowEventId;
    }

protected:
    void InitSpecialized() override;
    bool SetSpecializedAttr(const std::pair<std::string, std::string>& attr) override;
    bool SetSpecializedEvent(int32_t pageId, const std::string& eventId, const std::string& event) override;
    void CallSpecializedMethod(const std::string& method, const std::string& args) override;
};

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_DECLARATION_WEB_WEB_DECLARATION_H
