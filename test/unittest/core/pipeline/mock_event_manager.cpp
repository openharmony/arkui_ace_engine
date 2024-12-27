/*
 * Copyright (c) 2021-2022 Huawei Device Co., Ltd.
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

#include "test/unittest/core/pipeline/common_constants.h"

#include "core/common/event_manager.h"
#include "core/components_ng/event/response_ctrl.h"

namespace OHOS::Ace {
void EventManager::TouchTest(const TouchEvent& touchPoint, const RefPtr<RenderNode>& renderNode,
    const TouchRestrict& touchRestrict, const Offset& offset, float viewScale, bool needAppend)
{}

void EventManager::TouchTest(const TouchEvent& touchPoint, const RefPtr<NG::FrameNode>& frameNode,
    const TouchRestrict& touchRestrict, const Offset& offset, float viewScale, bool needAppend)
{}

void EventManager::TouchTest(
    const AxisEvent& event, const RefPtr<NG::FrameNode>& frameNode, const TouchRestrict& touchRestrict)
{
    SetInstanceId(instanceId_ | TOUCH_TEST_FLAG);
}

void EventManager::HandleGlobalEvent(const TouchEvent& touchPoint, const RefPtr<TextOverlayManager>& textOverlayManager)
{}

void EventManager::HandleGlobalEventNG(const TouchEvent& touchPoint,
    const RefPtr<NG::SelectOverlayManager>& selectOverlayManager, const NG::OffsetF& rootOffset)
{}

void EventManager::HandleOutOfRectCallback(const Point& point, std::vector<RectCallback>& rectCallbackList) {}

void EventManager::TouchTest(
    const AxisEvent& event, const RefPtr<RenderNode>& renderNode, const TouchRestrict& touchRestrict)
{}

void EventManager::FlushTouchEventsBegin(const std::list<TouchEvent>& touchEvents) {}

void EventManager::FlushTouchEventsEnd(const std::list<TouchEvent>& touchEvents) {}

bool EventManager::DispatchTouchEvent(const TouchEvent& point)
{
    SetInstanceId(instanceId_ | DISPATCH_TOUCH_EVENT_TOUCH_EVENT_FLAG);
    return true;
}

bool EventManager::DispatchTouchEvent(const AxisEvent& event)
{
    SetInstanceId(instanceId_ | DISPATCH_TOUCH_EVENT_AXIS_EVENT_FLAG);
    return true;
}

bool EventManager::DispatchTabIndexEventNG(
    const KeyEvent& event, const RefPtr<NG::FrameNode>& mainView)
{
    return !instanceId_;
}

bool EventManager::DispatchKeyEventNG(const KeyEvent& event, const RefPtr<NG::FrameNode>& focusNode)
{
    return false;
}

void EventManager::MouseTest(const MouseEvent& event, const RefPtr<RenderNode>& renderNode) {}

bool EventManager::DispatchMouseEvent(const MouseEvent& event)
{
    return true;
}

void EventManager::DispatchMouseHoverAnimation(const MouseEvent& event) {}

bool EventManager::DispatchMouseHoverEvent(const MouseEvent& event)
{
    return true;
}

void EventManager::MouseTest(
    const MouseEvent& event, const RefPtr<NG::FrameNode>& frameNode, const TouchRestrict& touchRestrict)
{
    SetInstanceId(instanceId_ | MOUSE_TEST_FLAG);
}

bool EventManager::DispatchMouseEventNG(const MouseEvent& event)
{
    SetInstanceId(instanceId_ | DISPATCH_MOUSE_EVENT_NG_FLAG);
    return true;
}

void EventManager::DispatchMouseHoverAnimationNG(const MouseEvent& event)
{
    SetInstanceId(instanceId_ | DISPATCH_MOUSE_HOVER_ANIMATION_NG_FLAG);
}

bool EventManager::DispatchMouseHoverEventNG(const MouseEvent& event)
{
    SetInstanceId(instanceId_ | DISPATCH_MOUSE_HOVER_EVENT_NG_FLAG);
    return true;
}

void EventManager::AxisTest(const AxisEvent& event, const RefPtr<RenderNode>& renderNode) {}

bool EventManager::DispatchAxisEvent(const AxisEvent& event)
{
    SetInstanceId(instanceId_ | DISPATCH_AXIS_EVENT_FLAG);
    return true;
}

void EventManager::AxisTest(const AxisEvent& event, const RefPtr<NG::FrameNode>& frameNode)
{
    SetInstanceId(instanceId_ | AXIS_TEST_FLAG);
}

bool EventManager::DispatchAxisEventNG(const AxisEvent& event)
{
    SetInstanceId(instanceId_ | DISPATCH_AXIS_EVENT_NG_FLAG);
    return true;
}

bool EventManager::DispatchRotationEvent(
    const RotationEvent& event, const RefPtr<RenderNode>& renderNode, const RefPtr<RenderNode>& requestFocusNode)
{
    return true;
}

void EventManager::DispatchKeyboardShortcut(const KeyEvent& event) {}

void EventManager::ClearResults() {}

bool EventManager::HasDifferentDirectionGesture()
{
    return false;
}

EventManager::EventManager() {}

void EventManager::DumpEvent(NG::EventTreeType type, bool hasJson = false) const {}

void AddGestureSnapshot(int32_t finger, int32_t depth, const RefPtr<TouchEventTarget>& target, NG::EventTreeType type)
{}
} // namespace OHOS::Ace
