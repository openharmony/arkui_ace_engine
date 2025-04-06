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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_NAVROUTER_NAVDESTINATION_EVENT_HUB_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_NAVROUTER_NAVDESTINATION_EVENT_HUB_H

#include "base/memory/ace_type.h"
#include "core/common/recorder/event_recorder.h"
#include "core/components_ng/base/observer_handler.h"
#include "core/components_ng/event/event_hub.h"
#include "core/components_ng/event/gesture_event_hub.h"
#include "core/components_ng/pattern/navrouter/navdestination_context.h"
#include "core/components_ng/pattern/navrouter/navdestination_group_node.h"
#include "core/components_ng/pattern/navigation/nav_bar_event_hub.h"

namespace OHOS::Ace::NG {
using OnStateChangeEvent = std::function<void(bool)>;
using namespace Framework;
class NavDestinationEventHub : public NavBarEventHub {
    DECLARE_ACE_TYPE(NavDestinationEventHub, EventHub)
public:
    void SetOnStateChange(const OnStateChangeEvent& changeEvent)
    {
        onStateChangeEvent_ = changeEvent;
    }

    const OnStateChangeEvent& GetOnStateChange()
    {
        return onStateChangeEvent_;
    }

    void FireChangeEvent(bool isActivated)
    {
        if (isActivated_ != isActivated) {
            if (onStateChangeEvent_) {
                TAG_LOGI(AceLogTag::ACE_NAVIGATION, "navDestination state set to %{public}s.",
                    isActivated ? "Activated" : "Deactivated");
                onStateChangeEvent_(isActivated);
            }
        }
        isActivated_ = isActivated;
    }

    void SetOnShown(const std::function<void()>& onShown)
    {
        onShownEvent_ = onShown;
    }

    void FireOnShownEvent(const std::string& name, const std::string& param);

    void SetOnHidden(const std::function<void()>& onHidden)
    {
        onHiddenEvent_ = onHidden;
    }

    void FireOnHiddenEvent(const std::string& name);

    void SetOnBackPressed(const std::function<bool()>& onBackPressed)
    {
        onBackPressedEvent_ = onBackPressed;
    }

    std::function<bool()> GetOnBackPressedEvent() const
    {
        return onBackPressedEvent_;
    }

    bool FireOnBackPressedEvent();

    void FireOnAppear() override;

    void FireDisappearCallback(const RefPtr<NavDestinationGroupNode>& navDestination)
    {
        TAG_LOGI(AceLogTag::ACE_NAVIGATION,
            "%{public}s lifecycle Respond user onDisappear. navdestinationId:%{public}d, navigationId:%{public}d",
            name_.c_str(), navDestination->GetId(), navDestination->GetNavigationNodeId());
        EventHub::FireOnDisappear();
    }

    void FireOnDisappear() override;

    void SetOnReady(const std::function<void(RefPtr<NavDestinationContext>)>& onReady)
    {
        onReadyEvent_ = onReady;
    }

    std::function<void(RefPtr<NavDestinationContext>)> GetOnReady() const
    {
        return onReadyEvent_;
    }

    void FireOnReady(RefPtr<NavDestinationContext> context)
    {
        if (onReadyEvent_) {
            TAG_LOGI(AceLogTag::ACE_NAVIGATION, "navDestination context is ready.");
            onReadyEvent_(context);
        }
    }

    void AddOnHiddenChange(int32_t id, OnStateChangeEvent&& onHiddenChange)
    {
        onHiddenChange_[id] = std::move(onHiddenChange);
    }

    void FireOnHiddenChange(bool flag)
    {
        for (auto& onHiddenChangeInfo : onHiddenChange_) {
            if (onHiddenChangeInfo.second) {
                auto onHiddenChange = onHiddenChangeInfo.second;
                onHiddenChange(flag);
            }
        }
    }

    void RemoveOnHiddenChange(int32_t id)
    {
        auto iter = onHiddenChange_.find(id);
        if (iter != onHiddenChange_.end()) {
            onHiddenChange_.erase(iter);
        }
    }

    void SetName(const std::string& name)
    {
        name_ = name;
    }

    void SetOnWillAppear(std::function<void()>& willAppear)
    {
        onWillAppear_ = std::move(willAppear);
    }

    void FireOnWillAppear();

    void SetOnWillShow(std::function<void()>& willShow)
    {
        onWillShow_ = std::move(willShow);
    }

    void FireOnWillShow();
    
    void SetOnWillHide(std::function<void()>& willHide)
    {
        onWillHide_ = std::move(willHide);
    }

    void FireOnWillHide();

    void SetOnWillDisAppear(std::function<void()>& willDisAppear)
    {
        onWillDisAppear_ = std::move(willDisAppear);
    }

    void FireOnWillDisAppear();

    NavDestinationState GetState()
    {
        return state_;
    }
    
    void SetState(NavDestinationState state)
    {
        state_ = state;
    }

    void SetOnActive(const std::function<void(int32_t)>& onActive)
    {
        onActive_ = onActive;
    }

    void FireOnActive(int32_t reason);

    void SetOnInactive(const std::function<void(int32_t)>& onInactive)
    {
        onInactive_ = onInactive;
    }

    void FireOnInactive(int32_t reason);

    void SetOnNewParam(NavDestinationOnNewParamCallback&& onNewParamCallback)
    {
        onNewParamCallback_ = onNewParamCallback;
    }

    void FireOnNewParam(napi_value param)
    {
        if (onNewParamCallback_) {
            onNewParamCallback_(param);
        }
    }

private:
    WeakPtr<AceType> GetNavDestinationPattern() const
    {
        auto node = GetFrameNode();
        CHECK_NULL_RETURN(node, nullptr);
        return node->GetPattern();
    }

    void FireAutoSave();

    OnStateChangeEvent onStateChangeEvent_;
    std::function<void()> onShownEvent_;
    std::function<void()> onHiddenEvent_;
    std::function<void()> onWillAppear_;
    std::function<void()> onWillShow_;
    std::function<void()> onWillHide_;
    std::function<void()> onWillDisAppear_;
    std::function<bool()> onBackPressedEvent_;
    std::function<void(int32_t)> onInactive_;
    std::function<void(int32_t)> onActive_;
    NavDestinationOnNewParamCallback onNewParamCallback_;
    std::function<void(RefPtr<NavDestinationContext>)> onReadyEvent_;
    std::unordered_map<int32_t, OnStateChangeEvent> onHiddenChange_;
    std::string name_;
    bool isActivated_ = false;
    NavDestinationState state_;
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_NAVROUTER_NAVDESTINATION_EVENT_HUB_H
