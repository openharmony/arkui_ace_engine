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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_WEB_WEB_EVENT_HUB_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_WEB_WEB_EVENT_HUB_H

#include "base/memory/ace_type.h"
#include "base/utils/noncopyable.h"
#include "core/components_ng/event/event_hub.h"

#define ACE_WEB_EVENT_PROPERTY(name)                                                                           \
public:                                                                                                        \
    void Set##name##Event(std::function<void(const std::shared_ptr<BaseEventInfo>& info)>&& prop##name##Event) \
    {                                                                                                          \
        prop##name##Event_ = std::move(prop##name##Event);                                                     \
    }                                                                                                          \
                                                                                                               \
    const std::function<void(const std::shared_ptr<BaseEventInfo>& info)>& Get##name##Event() const            \
    {                                                                                                          \
        return prop##name##Event_;                                                                             \
    }                                                                                                          \
    void Fire##name##Event(const std::shared_ptr<BaseEventInfo>& info) const                                   \
    {                                                                                                          \
        if (prop##name##Event_) {                                                                              \
            prop##name##Event_(info);                                                                          \
        }                                                                                                      \
    }                                                                                                          \
                                                                                                               \
private:                                                                                                       \
    std::function<void(const std::shared_ptr<BaseEventInfo>& info)> prop##name##Event_;

namespace OHOS::Ace::NG {
class WebEventHub : public EventHub {
    DECLARE_ACE_TYPE(WebEventHub, EventHub)

public:
    WebEventHub() = default;
    ~WebEventHub() override = default;

    using OnConsoleImpl = std::function<bool(const std::shared_ptr<BaseEventInfo>& info)>;
    void SetOnConsoleEvent(OnConsoleImpl&& OnConsoleImpl)
    {
        onConsoleImpl_ = std::move(OnConsoleImpl);
    }

    const OnConsoleImpl& GetOnConsoleEvent() const
    {
        return onConsoleImpl_;
    }

    bool FireOnConsole(const std::shared_ptr<BaseEventInfo>& info)
    {
        if (onConsoleImpl_) {
            return onConsoleImpl_(info);
        }
        return false;
    }

    ACE_WEB_EVENT_PROPERTY(OnPageStarted);
    ACE_WEB_EVENT_PROPERTY(OnPageFinished);
    ACE_WEB_EVENT_PROPERTY(OnTitleReceive);
    ACE_WEB_EVENT_PROPERTY(OnGeolocationHide);
    ACE_WEB_EVENT_PROPERTY(OnGeolocationShow);
    ACE_WEB_EVENT_PROPERTY(OnErrorReceive);
    ACE_WEB_EVENT_PROPERTY(OnHttpErrorReceive);

private:
    OnConsoleImpl onConsoleImpl_;

    ACE_DISALLOW_COPY_AND_MOVE(WebEventHub);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_WEB_WEB_EVENT_HUB_H