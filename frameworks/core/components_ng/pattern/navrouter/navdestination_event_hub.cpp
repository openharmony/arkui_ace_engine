/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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
#include "frameworks/core/components_ng/pattern/navrouter/navdestination_event_hub.h"

#include "frameworks/core/components_ng/pattern/navrouter/navdestination_pattern.h"
namespace OHOS::Ace::NG {
void NavDestinationEventHub::FireOnDisappear()
{
    auto navDestination = AceType::DynamicCast<NavDestinationGroupNode>(GetFrameNode());
    CHECK_NULL_VOID(navDestination);
    TAG_LOGI(AceLogTag::ACE_NAVIGATION,
        "%{public}s lifecycle change to OnDisappear state. navdestinationId:%{public}d, navigationId:%{public}d",
        name_.c_str(), navDestination->GetId(), navDestination->GetNavigationNodeId());
    if (navDestination->GetIsAnimated()) {
        auto pattern = navDestination->GetPattern<NavDestinationPattern>();
        CHECK_NULL_VOID(pattern);
        state_ = NavDestinationState::ON_DISAPPEAR;
        UIObserverHandler::GetInstance().NotifyNavigationStateChange(pattern, NavDestinationState::ON_DISAPPEAR);
        FireDisappearCallback(navDestination);
        pattern->SetCustomNode(nullptr);
        return;
    }
    auto pipelineContext = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipelineContext);
    pipelineContext->AddAfterLayoutTask([destination = navDestination]() {
        auto eventHub = destination->GetEventHub<NavDestinationEventHub>();
        CHECK_NULL_VOID(eventHub);
        auto pattern = destination->GetPattern<NavDestinationPattern>();
        CHECK_NULL_VOID(pattern);
        eventHub->state_ = NavDestinationState::ON_DISAPPEAR;
        UIObserverHandler::GetInstance().NotifyNavigationStateChange(pattern, NavDestinationState::ON_DISAPPEAR);
        eventHub->FireDisappearCallback(destination);
        pattern->SetCustomNode(nullptr);
    });
}

void NavDestinationEventHub::FireAutoSave()
{
    auto node = GetFrameNode();
    CHECK_NULL_VOID(node);
    if (!node->NeedRequestAutoSave()) {
        return;
    }
    auto container = Container::Current();
    CHECK_NULL_VOID(container);
    container->RequestAutoSave(node);
}

void NavDestinationEventHub::FireOnShownEvent(const std::string& name, const std::string& param)
{
    auto navDestination = AceType::DynamicCast<NavDestinationGroupNode>(GetFrameNode());
    CHECK_NULL_VOID(navDestination);
    TAG_LOGI(AceLogTag::ACE_NAVIGATION,
        "%{public}s lifecycle change to onShown state. navdestinationId:%{public}d, navigationId:%{public}d",
        name_.c_str(), navDestination->GetId(), navDestination->GetNavigationNodeId());
    state_= NavDestinationState::ON_SHOWN;
    UIObserverHandler::GetInstance().NotifyNavigationStateChange(GetNavDestinationPattern(),
        NavDestinationState::ON_SHOWN);
    if (onShownEvent_) {
        auto onShownEvent = onShownEvent_;
        onShownEvent();
    }
    if (!onHiddenChange_.empty()) {
        FireOnHiddenChange(true);
    }
    if (Recorder::EventRecorder::Get().IsPageRecordEnable()) {
        auto host = GetFrameNode();
        CHECK_NULL_VOID(host);
        auto id = host->GetInspectorIdValue("");
        Recorder::EventParamsBuilder builder;
        builder.SetId(id)
            .SetNavDst(name)
            .SetExtra(Recorder::KEY_PAGE_PARAM, param)
            .SetHost(host)
            .SetDescription(host->GetAutoEventParamValue(""));
        Recorder::EventRecorder::Get().OnNavDstShow(std::move(builder));
    }
    auto host = GetFrameNode();
    CHECK_NULL_VOID(host);
    auto pipelineContext = host->GetContext();
    CHECK_NULL_VOID(pipelineContext);
    pipelineContext->GetMemoryManager()->RebuildImageByPage(AceType::DynamicCast<FrameNode>(navDestination));
}

void NavDestinationEventHub::FireOnHiddenEvent(const std::string& name)
{
    auto navDestination = AceType::DynamicCast<NavDestinationGroupNode>(GetFrameNode());
    CHECK_NULL_VOID(navDestination);
    TAG_LOGI(AceLogTag::ACE_NAVIGATION,
        "%{public}s lifecycle change to onHidden state. navdestinationId:%{public}d, navigationId:%{public}d",
        name_.c_str(), navDestination->GetId(), navDestination->GetNavigationNodeId());
    state_ = NavDestinationState::ON_HIDDEN;
    UIObserverHandler::GetInstance().NotifyNavigationStateChange(GetNavDestinationPattern(),
        NavDestinationState::ON_HIDDEN);
    if (onHiddenEvent_) {
        onHiddenEvent_();
    }
    if (!onHiddenChange_.empty()) {
        FireOnHiddenChange(false);
    }
    if (Recorder::EventRecorder::Get().IsPageRecordEnable()) {
        auto host = GetFrameNode();
        CHECK_NULL_VOID(host);
        auto id = host->GetInspectorIdValue("");
        Recorder::EventParamsBuilder builder;
        builder.SetId(id).SetNavDst(name).SetHost(host).SetDescription(host->GetAutoEventParamValue(""));
        Recorder::EventRecorder::Get().OnNavDstHide(std::move(builder));
    }
}

void NavDestinationEventHub::FireOnAppear()
{
    auto navDestination = AceType::DynamicCast<NavDestinationGroupNode>(GetFrameNode());
    CHECK_NULL_VOID(navDestination);
    TAG_LOGI(AceLogTag::ACE_NAVIGATION,
        "%{public}s lifecycle change to onAppear state. navdestinationId:%{public}d, navigationId:%{public}d",
        name_.c_str(), navDestination->GetId(), navDestination->GetNavigationNodeId());
    auto onAppearAction = [weakEventHub = WeakClaim(this)]() {
        auto eventHub = weakEventHub.Upgrade();
        CHECK_NULL_VOID(eventHub);
        eventHub->state_ = NavDestinationState::ON_APPEAR;
        UIObserverHandler::GetInstance().NotifyNavigationStateChange(eventHub->GetNavDestinationPattern(),
            NavDestinationState::ON_APPEAR);
        if (eventHub->onAppear_) {
            auto onAppear = eventHub->onAppear_;
            onAppear();
        }
        if (eventHub->onJSFrameNodeAppear_) {
            auto onJSFrameNodeAppear = eventHub->onJSFrameNodeAppear_;
            onJSFrameNodeAppear();
        }
    };
    // if navdestination is created from recovery, it need trigger onAppear immediately
    if (navDestination && navDestination->NeedAppearFromRecovery()) {
        navDestination->SetNeedAppearFromRecovery(false);
        onAppearAction();
        return;
    }
    if (navDestination && navDestination->IsHomeDestination()) {
        onAppearAction();
        return;
    }
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto navigationManager = pipeline->GetNavigationManager();
    auto pattern = navDestination->GetPattern<NavDestinationPattern>();
    CHECK_NULL_VOID(pattern);
    if (pattern->GetNavigationNode()) {
        navigationManager->AddNavigationUpdateCallback(std::move(onAppearAction));
    } else {
        TAG_LOGI(AceLogTag::ACE_NAVIGATION,
            "%{public}s lifecycle Respond user onAppear. navdestinationId:%{public}d, navigationId:%{public}d",
            name_.c_str(), navDestination->GetId(), navDestination->GetNavigationNodeId());
        EventHub::FireOnAppear();
    }
}

void NavDestinationEventHub::FireOnWillAppear()
{
    auto navDestination = AceType::DynamicCast<NavDestinationGroupNode>(GetFrameNode());
    CHECK_NULL_VOID(navDestination);
    TAG_LOGI(AceLogTag::ACE_NAVIGATION,
        "%{public}s lifecycle change to onWillAppear state. navdestinationId:%{public}d, navigationId:%{public}d",
        name_.c_str(), navDestination->GetId(), navDestination->GetNavigationNodeId());
    state_ = NavDestinationState::ON_WILL_APPEAR;
    UIObserverHandler::GetInstance().NotifyNavigationStateChange(GetNavDestinationPattern(),
        NavDestinationState::ON_WILL_APPEAR);
    if (onWillAppear_) {
        onWillAppear_();
    }
}

void NavDestinationEventHub::FireOnWillShow()
{
    auto navDestination = AceType::DynamicCast<NavDestinationGroupNode>(GetFrameNode());
    CHECK_NULL_VOID(navDestination);
    TAG_LOGI(AceLogTag::ACE_NAVIGATION,
        "%{public}s lifecycle change to onWillShow state. navdestinationId:%{public}d, navigationId:%{public}d",
        name_.c_str(), navDestination->GetId(), navDestination->GetNavigationNodeId());
    state_ = NavDestinationState::ON_WILL_SHOW;
    UIObserverHandler::GetInstance().NotifyNavigationStateChange(GetNavDestinationPattern(),
        NavDestinationState::ON_WILL_SHOW);
    if (onWillShow_) {
        onWillShow_();
    }
}

void NavDestinationEventHub::FireOnWillHide()
{
    auto navDestination = AceType::DynamicCast<NavDestinationGroupNode>(GetFrameNode());
    CHECK_NULL_VOID(navDestination);
    TAG_LOGI(AceLogTag::ACE_NAVIGATION,
        "%{public}s lifecycle change to onWillHide state. navdestinationId:%{public}d, navigationId:%{public}d",
        name_.c_str(), navDestination->GetId(), navDestination->GetNavigationNodeId());
    state_ = NavDestinationState::ON_WILL_HIDE;
    UIObserverHandler::GetInstance().NotifyNavigationStateChange(GetNavDestinationPattern(),
        NavDestinationState::ON_WILL_HIDE);
    if (onWillHide_) {
        onWillHide_();
    }

    FireAutoSave();
}

void NavDestinationEventHub::FireOnWillDisAppear()
{
    auto navDestination = AceType::DynamicCast<NavDestinationGroupNode>(GetFrameNode());
    CHECK_NULL_VOID(navDestination);
    TAG_LOGI(AceLogTag::ACE_NAVIGATION,
        "%{public}s lifecycle change to onWillDisappear state. navdestinationId:%{public}d, navigationId:%{public}d",
        name_.c_str(), navDestination->GetId(), navDestination->GetNavigationNodeId());
    state_ = NavDestinationState::ON_WILL_DISAPPEAR;
    UIObserverHandler::GetInstance().NotifyNavigationStateChange(GetNavDestinationPattern(),
        NavDestinationState::ON_WILL_DISAPPEAR);
    if (onWillDisAppear_) {
        onWillDisAppear_();
    }
}

bool NavDestinationEventHub::FireOnBackPressedEvent()
{
    if (onBackPressedEvent_) {
        TAG_LOGI(AceLogTag::ACE_NAVIGATION, "navDestination backButton press is happening.");
        return onBackPressedEvent_();
    }
    return false;
}

void NavDestinationEventHub::FireOnActive(int32_t reason)
{
    auto navDestination = AceType::DynamicCast<NavDestinationGroupNode>(GetFrameNode());
    CHECK_NULL_VOID(navDestination);
    TAG_LOGI(AceLogTag::ACE_NAVIGATION,
        "%{public}s lifecycle change to onActive state. navdestinationId:%{public}d, navigationId:%{public}d",
        name_.c_str(), navDestination->GetId(), navDestination->GetNavigationNodeId());
    state_ = NavDestinationState::ON_ACTIVE;
    UIObserverHandler::GetInstance().NotifyNavigationStateChange(GetNavDestinationPattern(),
        NavDestinationState::ON_ACTIVE);
    if (onActive_) {
        onActive_(reason);
    }
}

void NavDestinationEventHub::FireOnInactive(int32_t reason)
{
    auto navDestination = AceType::DynamicCast<NavDestinationGroupNode>(GetFrameNode());
    CHECK_NULL_VOID(navDestination);
    TAG_LOGI(AceLogTag::ACE_NAVIGATION,
        "%{public}s lifecycle change to onInactive state. navdestinationId:%{public}d, navigationId:%{public}d",
        name_.c_str(), navDestination->GetId(), navDestination->GetNavigationNodeId());
    state_ = NavDestinationState::ON_INACTIVE;
    UIObserverHandler::GetInstance().NotifyNavigationStateChange(GetNavDestinationPattern(),
        NavDestinationState::ON_INACTIVE);
    if (onInactive_) {
        onInactive_(reason);
    }
}
}