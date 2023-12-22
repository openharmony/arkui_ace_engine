/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_NAVIGATION_TRANSITION_PROXY_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_NAVIGATION_TRANSITION_PROXY_H

#include "base/memory/ace_type.h"
#include "frameworks/core/components_ng/pattern/navigation/navigation_declaration.h"
#include "frameworks/core/components_ng/pattern/navrouter/navdestination_group_node.h"
#include "frameworks/core/components_ng/pattern/navrouter/navdestination_pattern.h"
namespace OHOS::Ace::NG {

using namespace Framework;
class NavigationTransitionProxy : public AceType {
    DECLARE_ACE_TYPE(NavigationTransitionProxy, AceType);

public:
    NavContentInfo GetPreDestination() const
    {
        return preNavInfo_;
    }

    NavContentInfo GetTopDestination() const
    {
        return topNavInfo_;
    }

    void SetPreDestination(const RefPtr<NavDestinationGroupNode>& preDestination)
    {
        if (!preDestination) {
            preNavInfo_.index = -1;
            return;
        }
        preNavInfo_.index = preDestination->GetIndex();
        preNavInfo_.mode = preDestination->GetNavDestinationMode();
        auto pattern = AceType::DynamicCast<NavDestinationPattern>(preDestination->GetPattern());
        CHECK_NULL_VOID(pattern);
        preNavInfo_.name = pattern->GetName();
    }

    void SetTopDestination(const RefPtr<NavDestinationGroupNode>& topDestination)
    {
        if (!topDestination) {
            topNavInfo_.index = -1;
            return;
        }
        topNavInfo_.index = topDestination->GetIndex();
        topNavInfo_.mode = topDestination->GetNavDestinationMode();
        auto pattern = AceType::DynamicCast<NavDestinationPattern>(topDestination->GetPattern());
        CHECK_NULL_VOID(pattern);
        topNavInfo_.name = pattern->GetName();
    }

    void SetFinishTransitionEvent(std::function<void(bool)>&& event)
    {
        finishCallback_ = std::move(event);
    }

    void FireFinishCallback()
    {
        if (hasFinished_ || !finishCallback_) {
            return;
        }
        finishCallback_(isSuccess_);
    }

    void SetIsSuccess(bool isSuccess)
    {
        isSuccess_ = isSuccess;
    }

    void SetIsFinished(bool isFinished)
    {
        hasFinished_ = isFinished;
    }

    bool GetIsFinished() const
    {
        return hasFinished_;
    }

    void SetNavigationOperation(NavigationOperation operation)
    {
        operation_ = operation;
    }

private:
    NavContentInfo preNavInfo_;
    NavContentInfo topNavInfo_;
    std::function<void(bool)> finishCallback_;
    NavigationOperation operation_;
    bool hasFinished_ = false;
    bool isSuccess_ = false;
};

struct NavigationTransition {
    int32_t timeout = 1000;
    std::function<void(const RefPtr<NavigationTransitionProxy>&)> transition;
    std::function<void(bool)> endCallback;
    bool isValid = true;
};
} // namespace OHOS::Ace::NG
#endif