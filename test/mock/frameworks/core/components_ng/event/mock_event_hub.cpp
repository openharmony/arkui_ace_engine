/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 */

#include "core/components_ng/event/event_hub.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/event/focus_hub.h"
#include "core/components_ng/event/gesture_event_hub.h"
#include "core/components_ng/event/input_event_hub.h"
#include "core/components_ng/event/state_style_manager.h"

namespace OHOS::Ace::NG {
EventHub::EventHub() = default;
EventHub::~EventHub() = default;

const RefPtr<GestureEventHub>& EventHub::GetOrCreateGestureEventHub()
{
    if (!gestureEventHub_) {
        gestureEventHub_ = CreateGestureEventHub();
    }
    return gestureEventHub_;
}

RefPtr<GestureEventHub> EventHub::CreateGestureEventHub()
{
    return nullptr;
}

RefPtr<FocusHub> EventHub::GetOrCreateFocusHub(
    FocusType type, bool focusable, FocusStyleType focusStyleType, const std::unique_ptr<FocusPaintParam>& paintParamsPtr)
{
    auto frameNode = GetFrameNode();
    if (!frameNode) {
        return nullptr;
    }
    return frameNode->GetOrCreateFocusHub(type, focusable, focusStyleType, paintParamsPtr);
}

RefPtr<FocusHub> EventHub::GetOrCreateFocusHub(const FocusPattern& focusPattern)
{
    auto frameNode = GetFrameNode();
    if (!frameNode) {
        return nullptr;
    }
    return frameNode->GetOrCreateFocusHub(focusPattern);
}

bool EventHub::IsEnabled() const
{
    return enabled_;
}

void EventHub::SetEnabled(bool enabled)
{
    enabled_ = enabled;
}

void EventHub::SetEnabledInternal(bool enabled)
{
    enabled_ = enabled;
}

void EventHub::FireOnAppear() {}

void EventHub::FireOnDisappear() {}

void EventHub::FireOnAttach() {}

void EventHub::FireOnDetach() {}

void EventHub::AttachHost(const WeakPtr<FrameNode>& host)
{
    host_ = host;
}

RefPtr<FrameNode> EventHub::GetFrameNode() const
{
    return host_.Upgrade();
}

void EventHub::FireDrawCompletedNDKCallback(PipelineContext* pipeline)
{
    (void)pipeline;
}

void EventHub::SetVisibleAreaRatiosAndCallback(
    const VisibleCallbackInfo& callback, const std::vector<double>& ratios, bool isUser)
{
    (void)callback;
    (void)ratios;
    (void)isUser;
}
} // namespace OHOS::Ace::NG
