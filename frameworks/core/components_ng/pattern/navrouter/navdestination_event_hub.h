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

namespace OHOS::Ace::NG {
using OnStateChangeEvent = std::function<void(bool)>;
using namespace Framework;
class NavDestinationEventHub : public EventHub {
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

    void FireOnShownEvent(const std::string& name, const std::string& param) const
    {
        TAG_LOGI(AceLogTag::ACE_NAVIGATION, "%{public}s lifecycle chang to shown state.", name_.c_str());
        UIObserverHandler::GetInstance().NotifyNavigationStateChange(GetNavDestinationPattern(),
                                                                     NavDestinationState::ON_SHOWN);
        if (onShownEvent_) {
            auto onShownEvent = onShownEvent_;
            onShownEvent();
        }
        if (onHiddenChange_) {
            onHiddenChange_(true);
        }
        if (Recorder::EventRecorder::Get().IsPageRecordEnable()) {
            auto host = GetFrameNode();
            CHECK_NULL_VOID(host);
            auto id = host->GetInspectorIdValue("");
            Recorder::EventParamsBuilder builder;
            builder.SetId(id)
                .SetText(name)
                .SetExtra(Recorder::KEY_PAGE_PARAM, param)
                .SetDescription(host->GetAutoEventParamValue(""));
            Recorder::EventRecorder::Get().OnNavDstShow(std::move(builder));
        }
    }

    void SetOnHidden(const std::function<void()>& onHidden)
    {
        onHiddenEvent_ = onHidden;
    }

    void FireOnHiddenEvent(const std::string& name) const
    {
        TAG_LOGI(AceLogTag::ACE_NAVIGATION, "%{public}s lifecycle chang to hidden state.", name_.c_str());
        UIObserverHandler::GetInstance().NotifyNavigationStateChange(GetNavDestinationPattern(),
                                                                     NavDestinationState::ON_HIDDEN);
        if (onHiddenEvent_) {
            onHiddenEvent_();
        }
        if (onHiddenChange_) {
            onHiddenChange_(false);
        }

        if (Recorder::EventRecorder::Get().IsPageRecordEnable()) {
            auto host = GetFrameNode();
            CHECK_NULL_VOID(host);
            auto id = host->GetInspectorIdValue("");
            Recorder::EventParamsBuilder builder;
            builder.SetId(id).SetText(name).SetDescription(host->GetAutoEventParamValue(""));
            Recorder::EventRecorder::Get().OnNavDstHide(std::move(builder));
        }
    }

    void SetOnBackPressed(const std::function<bool()>& onBackPressed)
    {
        onBackPressedEvent_ = onBackPressed;
    }

    std::function<bool()> GetOnBackPressedEvent() const
    {
        return onBackPressedEvent_;
    }

    bool FireOnBackPressedEvent()
    {
        UIObserverHandler::GetInstance().NotifyNavigationStateChange(GetNavDestinationPattern(),
                                                                     NavDestinationState::ON_BACKPRESS);
        if (onBackPressedEvent_) {
            TAG_LOGI(AceLogTag::ACE_NAVIGATION, "navDestination backButton press is happening.");
            return onBackPressedEvent_();
        }
        return false;
    }

    void FireOnAppear() override
    {
        TAG_LOGI(AceLogTag::ACE_NAVIGATION, "%{public}s lifecycle change to appear state", name_.c_str());
        UIObserverHandler::GetInstance().NotifyNavigationStateChange(GetNavDestinationPattern(),
                                                                     NavDestinationState::ON_APPEAR);
        auto pipeline = PipelineContext::GetCurrentContext();
        CHECK_NULL_VOID(pipeline);
        auto navigationManager = pipeline->GetNavigationManager();
        navigationManager->AddNavigationUpdateCallback([weakEventHub = WeakClaim(this)]() {
            auto eventHub = weakEventHub.Upgrade();
            CHECK_NULL_VOID(eventHub);
            if (eventHub->onAppear_) {
                auto onAppear = eventHub->onAppear_;
                onAppear();
            }

            if (eventHub->onJSFrameNodeAppear_) {
                auto onJSFrameNodeAppear = eventHub->onJSFrameNodeAppear_;
                onJSFrameNodeAppear();
            }
        });
    }

    void FireDisappearCallback()
    {
        TAG_LOGI(AceLogTag::ACE_NAVIGATION, "%{public}s lifecycle chang to disappear state.", name_.c_str());
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

    void SetOnHiddenChange(std::function<void(bool)>&& onHiddenChange)
    {
        onHiddenChange_ = std::move(onHiddenChange);
    }

    void SetName(const std::string& name)
    {
        name_ = name;
    }

    void SetOnWillAppear(std::function<void()>& willAppear)
    {
        onWillAppear_ = std::move(willAppear);
    }

    void FireOnWillAppear()
    {
        TAG_LOGI(AceLogTag::ACE_NAVIGATION, "%{public}s lifecycle change to will appear state", name_.c_str());
        UIObserverHandler::GetInstance().NotifyNavigationStateChange(GetNavDestinationPattern(),
                                                                     NavDestinationState::ON_WILL_APPEAR);
        if (onWillAppear_) {
            onWillAppear_();
        }
    }

    void SetOnWillShow(std::function<void()>& willShow)
    {
        onWillShow_ = std::move(willShow);
    }

    void FireOnWillShow()
    {
        TAG_LOGI(AceLogTag::ACE_NAVIGATION, "%{public}s lifecycle change to will show state", name_.c_str());
        UIObserverHandler::GetInstance().NotifyNavigationStateChange(GetNavDestinationPattern(),
                                                                     NavDestinationState::ON_WILL_SHOW);
        if (onWillShow_) {
            onWillShow_();
        }
    }

    void SetOnWillHide(std::function<void()>& willHide)
    {
        onWillHide_ = std::move(willHide);
    }

    void FireOnWillHide()
    {
        TAG_LOGI(AceLogTag::ACE_NAVIGATION, "%{public}s lifecycle change to will hide state", name_.c_str());
        UIObserverHandler::GetInstance().NotifyNavigationStateChange(GetNavDestinationPattern(),
                                                                     NavDestinationState::ON_WILL_HIDE);
        if (onWillHide_) {
            onWillHide_();
        }

        FireAutoSave();
    }

    void SetOnWillDisAppear(std::function<void()>& willDisAppear)
    {
        onWillDisAppear_ = std::move(willDisAppear);
    }

    void FireOnWillDisAppear()
    {
        TAG_LOGI(AceLogTag::ACE_NAVIGATION, "%{public}s lifecycle change to will disappear state", name_.c_str());
        UIObserverHandler::GetInstance().NotifyNavigationStateChange(GetNavDestinationPattern(),
                                                                     NavDestinationState::ON_WILL_DISAPPEAR);
        if (onWillDisAppear_) {
            onWillDisAppear_();
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
    std::function<void(RefPtr<NavDestinationContext>)> onReadyEvent_;
    std::function<void(bool)> onHiddenChange_;
    std::string name_;
    bool isActivated_ = false;
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_NAVROUTER_NAVDESTINATION_EVENT_HUB_H
