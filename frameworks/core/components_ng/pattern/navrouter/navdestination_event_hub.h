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
        UIObserverHandler::GetInstance().NotifyNavigationStateChange(GetNavDestinationPattern(),
                                                                     NavDestinationState::ON_SHOWN);
        if (onShownEvent_) {
            auto onShownEvent = onShownEvent_;
            onShownEvent();
        }
        if (Recorder::EventRecorder::Get().IsPageRecordEnable()) {
            auto host = GetFrameNode();
            CHECK_NULL_VOID(host);
            auto id = host->GetInspectorIdValue("");
            Recorder::EventParamsBuilder builder;
            builder.SetId(id).SetText(name).SetExtra(Recorder::KEY_PAGE_PARAM, param);
            Recorder::EventRecorder::Get().OnNavDstShow(std::move(builder));
        }
    }

    void SetOnHidden(const std::function<void()>& onHidden)
    {
        onHiddenEvent_ = onHidden;
    }

    void FireOnHiddenEvent(const std::string& name) const
    {
        UIObserverHandler::GetInstance().NotifyNavigationStateChange(GetNavDestinationPattern(),
                                                                     NavDestinationState::ON_HIDDEN);
        if (onHiddenEvent_) {
            onHiddenEvent_();
        }
        if (Recorder::EventRecorder::Get().IsPageRecordEnable()) {
            auto host = GetFrameNode();
            CHECK_NULL_VOID(host);
            auto id = host->GetInspectorIdValue("");
            Recorder::EventParamsBuilder builder;
            builder.SetId(id).SetText(name);
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
        if (onBackPressedEvent_) {
            return onBackPressedEvent_();
        }
        return false;
    }

private:
    WeakPtr<AceType> GetNavDestinationPattern() const
    {
        auto node = GetFrameNode();
        CHECK_NULL_RETURN(node, nullptr);
        return node->GetPattern();
    }

    OnStateChangeEvent onStateChangeEvent_;
    std::function<void()> onShownEvent_;
    std::function<void()> onHiddenEvent_;
    std::function<bool()> onBackPressedEvent_;

    bool isActivated_ = false;
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_NAVROUTER_NAVDESTINATION_EVENT_HUB_H
