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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_NAVROUTER_NAVDESTINATION_PATTERN_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_NAVROUTER_NAVDESTINATION_PATTERN_H

#include "base/memory/referenced.h"
#include "core/components_ng/base/ui_node.h"
#include "core/components_ng/pattern/navigation/navigation_event_hub.h"
#include "core/components_ng/pattern/navigation/navigation_stack.h"
#include "core/components_ng/pattern/navrouter/navdestination_event_hub.h"
#include "core/components_ng/pattern/navrouter/navdestination_group_node.h"
#include "core/components_ng/pattern/navrouter/navdestination_layout_algorithm.h"
#include "core/components_ng/pattern/navrouter/navdestination_layout_property.h"
#include "core/components_ng/pattern/pattern.h"
#include "core/components_ng/syntax/shallow_builder.h"

namespace OHOS::Ace::NG {

class NavDestinationPattern : public Pattern {
    DECLARE_ACE_TYPE(NavDestinationPattern, Pattern);

public:
    explicit NavDestinationPattern(const RefPtr<ShallowBuilder>& shallowBuilder) : shallowBuilder_(shallowBuilder) {}
    NavDestinationPattern() = default;
    ~NavDestinationPattern() override = default;

    bool IsAtomicNode() const override
    {
        return false;
    }

    RefPtr<LayoutProperty> CreateLayoutProperty() override
    {
        return MakeRefPtr<NavDestinationLayoutProperty>();
    }

    RefPtr<LayoutAlgorithm> CreateLayoutAlgorithm() override
    {
        return MakeRefPtr<NavDestinationLayoutAlgorithm>();
    }

    RefPtr<EventHub> CreateEventHub() override
    {
        return MakeRefPtr<NavDestinationEventHub>();
    }

    void OnModifyDone() override;

    const RefPtr<ShallowBuilder>& GetShallowBuilder() const
    {
        return shallowBuilder_;
    }

    void SetName(const std::string& name)
    {
        name_ = name;
    }

    const std::string& GetName()
    {
        return name_;
    }

    void SetNavDestinationNode(const RefPtr<UINode>& navDestinationNode)
    {
        navDestinationNode_ = navDestinationNode;
    }

    const RefPtr<UINode>& GetNavDestinationNode() const
    {
        return navDestinationNode_;
    }

    void ResetNavDestinationNode()
    {
        navDestinationNode_.Reset();
    }

    void SetRouteInfo(const RefPtr<RouteInfo>& routeInfo)
    {
        routeInfo_ = routeInfo;
    }

    const RefPtr<RouteInfo>& GetRouteInfo()
    {
        return routeInfo_;
    }

    FocusPattern GetFocusPattern() const override
    {
        return { FocusType::SCOPE, true };
    }

    void SetIsOnShow(bool isOnShow)
    {
        isOnShow_ = isOnShow;
    }

    void SetIsUnderNavRouter(bool isUnderNavRouter)
    {
        isUnderNavRouter_ = isUnderNavRouter;
    }

    bool GetIsUnderNavRouter()
    {
        return isUnderNavRouter_;
    }

    bool GetIsOnShow()
    {
        return isOnShow_;
    }

private:
    RefPtr<ShallowBuilder> shallowBuilder_;
    std::string name_;
    RefPtr<RouteInfo> routeInfo_;
    RefPtr<UINode> navDestinationNode_;
    bool isOnShow_ = false;
    bool isUnderNavRouter_ = false;
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_NAVROUTER_NAVDESTINATION_PATTERN_H
