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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_NAVROUTER_NAVROUTER_PATTERN_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_NAVROUTER_NAVROUTER_PATTERN_H

#include "core/components_ng/pattern/navigation/navigation_declaration.h"
#include "core/components_ng/pattern/navigation/navigation_stack.h"
#include "core/components_ng/pattern/navrouter/navrouter_event_hub.h"
#include "core/components_ng/pattern/pattern.h"

namespace OHOS::Ace::NG {

class ACE_EXPORT NavRouterPattern : public Pattern {
    DECLARE_ACE_TYPE(NavRouterPattern, Pattern);

public:
    NavRouterPattern() = default;
    ~NavRouterPattern() override = default;

    bool IsAtomicNode() const override
    {
        return false;
    }

    RefPtr<EventHub> CreateEventHub() override
    {
        return MakeRefPtr<NavRouterEventHub>();
    }

    void OnModifyDone() override;

    void SetRouteInfo(const RefPtr<RouteInfo>& routeInfo)
    {
        routeInfo_ = routeInfo;
    }

    const RefPtr<RouteInfo>& GetRouteInfo()
    {
        return routeInfo_;
    }

    void SetNavRouteMode(NavRouteMode mode)
    {
        mode_ = mode;
    }

    NavRouteMode GetNavRouteMode()
    {
        return mode_;
    }

private:
    RefPtr<ClickEvent> clickListener_;
    RefPtr<RouteInfo> routeInfo_;
    NavRouteMode mode_ = NavRouteMode::PUSH_WITH_RECREATE;
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_NAVROUTER_NAVROUTER_PATTERN_H
