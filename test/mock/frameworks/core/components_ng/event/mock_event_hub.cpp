/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/event/event_hub.h"
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

RefPtr<FocusHub> EventHub::GetOrCreateFocusHub(FocusType type, bool focusable, FocusStyleType focusStyleType,
    const std::unique_ptr<FocusPaintParam>& paintParamsPtr)
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

bool EventHub::HasOnAreaChanged() const
{
    return false;
}
VisibleCallbackInfo& EventHub::GetVisibleAreaCallback(bool)
{
    static VisibleCallbackInfo info;
    return info;
}
void EventHub::SetDefaultOnDragStart(OnDragStartFunc&&) {}
} // namespace OHOS::Ace::NG
