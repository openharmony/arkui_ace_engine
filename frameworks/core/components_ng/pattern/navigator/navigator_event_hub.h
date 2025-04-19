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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_NAVIGATOR_NAVIGATOR_EVENT_HUB_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_NAVIGATOR_NAVIGATOR_EVENT_HUB_H

#include "core/components/navigator/navigator_type.h"
#include "core/components_ng/event/event_hub.h"

namespace OHOS::Ace::NG {
class InspectorFilter;

class NavigatorEventHub : public EventHub {
    DECLARE_ACE_TYPE(NavigatorEventHub, EventHub)

public:
    NavigatorEventHub() = default;
    ~NavigatorEventHub() override = default;

    void SetUrl(const std::string& url)
    {
        url_ = url;
    }

    std::string GetUrl()
    {
        return url_;
    }

    void SetParams(const std::string& params)
    {
        params_ = params;
    }

    std::string GetParams()
    {
        return params_;
    }

    void SetActive(bool active);
    bool GetActive() const
    {
        return active_;
    }

    void SetType(NavigatorType type)
    {
        type_ = type;
    }

    NavigatorType GetType()
    {
        return type_;
    }

    void NavigatePage();

    std::string GetNavigatorType() const;
    void ToJsonValue(std::unique_ptr<JsonValue>& json, const InspectorFilter& filter) const override;

private:
    std::string url_;
    std::string params_;
    NavigatorType type_ = NavigatorType::PUSH;
    // navigate page if active_
    bool active_ = false;

    ACE_DISALLOW_COPY_AND_MOVE(NavigatorEventHub);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_NAVIGATOR_NAVIGATOR_EVENT_HUB_H
