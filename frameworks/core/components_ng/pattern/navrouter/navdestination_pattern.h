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
#include "base/utils/utils.h"
#include "core/components_ng/base/ui_node.h"
#include "core/components_ng/pattern/navigation/navigation_event_hub.h"
#include "core/components_ng/pattern/navigation/navigation_stack.h"
#include "core/components_ng/pattern/navrouter/navdestination_context.h"
#include "core/components_ng/pattern/navrouter/navdestination_event_hub.h"
#include "core/components_ng/pattern/navrouter/navdestination_group_node.h"
#include "core/components_ng/pattern/navrouter/navdestination_layout_algorithm.h"
#include "core/components_ng/pattern/navrouter/navdestination_layout_property.h"
#include "core/components_ng/pattern/pattern.h"
#include "core/components_ng/syntax/shallow_builder.h"
#include "core/components_v2/inspector/inspector_constants.h"

namespace OHOS::Ace::NG {

class NavDestinationPattern : public Pattern, public FocusView {
    DECLARE_ACE_TYPE(NavDestinationPattern, Pattern, FocusView);

public:
    explicit NavDestinationPattern(const RefPtr<ShallowBuilder>& shallowBuilder);
    NavDestinationPattern();
    ~NavDestinationPattern() override;

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
        auto layout = MakeRefPtr<NavDestinationLayoutAlgorithm>();
        layout->SetIsShown(isOnShow_);
        return layout;
    }

    RefPtr<EventHub> CreateEventHub() override
    {
        return MakeRefPtr<NavDestinationEventHub>();
    }

    void OnActive() override;

    void OnModifyDone() override;

    const RefPtr<ShallowBuilder>& GetShallowBuilder() const
    {
        return shallowBuilder_;
    }

    void SetName(const std::string& name)
    {
        name_ = name;
        auto eventHub = GetEventHub<NavDestinationEventHub>();
        CHECK_NULL_VOID(eventHub);
        eventHub->SetName(name);
    }

    const std::string& GetName()
    {
        return name_;
    }

    void SetNavPathInfo(const RefPtr<NavPathInfo>& pathInfo)
    {
        if (navDestinationContext_) {
            navDestinationContext_->SetNavPathInfo(pathInfo);
        }
    }

    RefPtr<NavPathInfo> GetNavPathInfo() const
    {
        return navDestinationContext_ ? navDestinationContext_->GetNavPathInfo() : nullptr;
    }

    void SetNavigationStack(const WeakPtr<NavigationStack>& stack)
    {
        if (navDestinationContext_) {
            navDestinationContext_->SetNavigationStack(stack);
        }
    }

    WeakPtr<NavigationStack> GetNavigationStack() const
    {
        return navDestinationContext_ ? navDestinationContext_->GetNavigationStack() : nullptr;
    }

    void SetIndex(int32_t index)
    {
        if (navDestinationContext_) {
            navDestinationContext_->SetIndex(index);
        }
    }

    void SetNavDestinationContext(const RefPtr<NavDestinationContext>& context)
    {
        navDestinationContext_ = context;
        if (navDestinationContext_) {
            navDestinationContext_->SetNavDestinationId(navDestinationId_);
        }
    }

    RefPtr<NavDestinationContext> GetNavDestinationContext() const
    {
        return navDestinationContext_;
    }

    void SetCustomNode(const RefPtr<UINode>& customNode)
    {
        customNode_ = customNode;
    }

    RefPtr<UINode> GetCustomNode()
    {
        return customNode_;
    }

    FocusPattern GetFocusPattern() const override
    {
        return { FocusType::SCOPE, true };
    }

    std::list<int32_t> GetRouteOfFirstScope() override
    {
        return { 2, 0 };
    }

    std::string GetEntryFocusViewName() override
    {
        /*
        |-> Any FocusView (entry focus view)
          |-> NavDestination
        */
        return ENTRY_ANY_FOCUSVIEW;
    }

    void SetIsOnShow(bool isOnShow)
    {
        isOnShow_ = isOnShow;
    }

    bool GetIsOnShow()
    {
        return isOnShow_;
    }

    bool GetBackButtonState();

    RefPtr<UINode> GetNavigationNode()
    {
        return navigationNode_.Upgrade();
    }

    void DumpInfo() override;

    uint64_t GetNavDestinationId() const
    {
        return navDestinationId_;
    }

    void SetNavigationNode(const RefPtr<UINode>& navigationNode)
    {
        navigationNode_ = AceType::WeakClaim(RawPtr(navigationNode));
    }
    
    void OnDetachFromMainTree() override
    {
        auto weak = AceType::WeakClaim(this);
        UIObserverHandler::GetInstance().NotifyNavigationStateChange(weak, NavDestinationState::ON_DISAPPEAR);
    }

private:
    void UpdateNameIfNeeded(RefPtr<NavDestinationGroupNode>& hostNode);
    void UpdateBackgroundColorIfNeeded(RefPtr<NavDestinationGroupNode>& hostNode);
    void UpdateTitlebarVisibility(RefPtr<NavDestinationGroupNode>& hostNode);

    RefPtr<ShallowBuilder> shallowBuilder_;
    std::string name_;
    RefPtr<NavDestinationContext> navDestinationContext_;
    RefPtr<UINode> customNode_;
    WeakPtr<UINode> navigationNode_;
    bool isOnShow_ = false;
    uint64_t navDestinationId_ = 0;
    void OnAttachToFrameNode() override;
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_NAVROUTER_NAVDESTINATION_PATTERN_H
