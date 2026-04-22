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

#include "core/components_ng/relaxed_interaction/utils/relaxed_event_factory.h"

#include "base/log/log_wrapper.h"
#include "core/components_ng/base/frame_node.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {

namespace {
// Touch event constants to avoid magic numbers
constexpr float HALF = 2.0f;

TouchPoint CreateTouchPoint(const PointF& coordinates, TouchType touchType)
{
    TouchPoint touchPoint;
    touchPoint.id = 0;
    touchPoint.downTime = std::chrono::high_resolution_clock::now();
    touchPoint.x = coordinates.GetX();
    touchPoint.y = coordinates.GetY();
    touchPoint.screenX = coordinates.GetX();
    touchPoint.screenY = coordinates.GetY();
    touchPoint.globalDisplayX = coordinates.GetX();
    touchPoint.globalDisplayY = coordinates.GetY();
    touchPoint.isPressed = (touchType == TouchType::DOWN) || (touchType == TouchType::MOVE);
    touchPoint.force = 0;
    touchPoint.sourceTool = SourceTool::FINGER;
    touchPoint.originalId = 0;
    touchPoint.size = 0;
    touchPoint.width = 0;
    touchPoint.height = 0;
    touchPoint.tiltX = 0.0f;
    touchPoint.tiltY = 0.0f;
    touchPoint.rollAngle = 0.0f;
    touchPoint.operatingHand = 0;
    touchPoint.xReverse = 0;
    touchPoint.yReverse = 0;
    return touchPoint;
}

TouchEvent BuildTouchEvent(const TouchPoint& touchPoint, TouchType touchType)
{
    TouchEvent event;
    event.SetId(touchPoint.id)
        .SetX(touchPoint.x)
        .SetY(touchPoint.y)
        .SetScreenX(touchPoint.screenX)
        .SetScreenY(touchPoint.screenY)
        .SetGlobalDisplayX(touchPoint.globalDisplayX)
        .SetGlobalDisplayY(touchPoint.globalDisplayY)
        .SetType(touchType)
        .SetPullType(TouchType::UNKNOWN)
        .SetSize(touchPoint.size)
        .SetForce(touchPoint.force)
        .SetTiltX(touchPoint.tiltX)
        .SetTiltY(touchPoint.tiltY)
        .SetRollAngle(touchPoint.rollAngle)
        .SetSourceType(SourceType::TOUCH)
        .SetSourceTool(touchPoint.sourceTool)
        .SetOriginalId(touchPoint.originalId)
        .SetPressedTime(touchPoint.downTime)
        .SetWidth(touchPoint.width)
        .SetHeight(touchPoint.height)
        .SetOperatingHand(touchPoint.operatingHand)
        .SetXReverse(touchPoint.xReverse)
        .SetYReverse(touchPoint.yReverse)
        .SetTime(touchPoint.downTime)
        .SetIsInjected(true);
    event.SetDeviceId(0);
    return event;
}

Offset CalculateCenter(const RectF& rect)
{
    return Offset((rect.Right() - rect.Left()) / HALF, (rect.Bottom() - rect.Top()) / HALF);
}

Offset CalculateWindowCenter(const RectF& rect)
{
    return Offset((rect.Left() + rect.Right()) / HALF, (rect.Top() + rect.Bottom()) / HALF);
}
} // namespace

TouchEvent RelaxedEventFactory::CreateTouchEvent(const PointF& coordinates, TouchType touchType)
{
    auto touchPoint = CreateTouchPoint(coordinates, touchType);
    auto event = BuildTouchEvent(touchPoint, touchType);
    event.pointers.emplace_back(touchPoint);
    return event;
}

GestureEvent RelaxedEventFactory::CreateClickGestureEvent(const RefPtr<FrameNode>& frameNode)
{
    GestureEvent info;
    auto geometryNode = frameNode->GetGeometryNode();
    if (!geometryNode) {
        TAG_LOGE(AceLogTag::ACE_UIEVENT, "GeometryNode is null");
        return info;
    }
    info.SetTimeStamp(std::chrono::high_resolution_clock::now());
    auto rect = geometryNode->GetFrameRect();
    auto centerToNode = CalculateCenter(rect);
    auto centerToWindow = CalculateWindowCenter(rect);

    info.SetLocalLocation(centerToNode);
    info.SetSourceDevice(SourceType::TOUCH);
    info.SetInputEventType(InputEventType::TOUCH_SCREEN);
    info.SetSourceTool(SourceTool::FINGER);
    info.SetPatternName(frameNode->GetTag().c_str());
    info.SetGlobalLocation(centerToWindow);
    info.SetDeviceId(0);

    auto pipelineContext = frameNode->GetContextRefPtr();
    if (pipelineContext) {
        auto windowOffset = pipelineContext->GetCurrentWindowRect().GetOffset() + centerToWindow;
        auto globalWindowOffset = pipelineContext->GetGlobalDisplayWindowRect().GetOffset() + centerToWindow;
        info.SetScreenLocation(windowOffset).SetGlobalDisplayLocation(globalWindowOffset);
    }

    auto eventHub = frameNode->GetEventHub<EventHub>();
    if (eventHub) {
        auto targetImpl = eventHub->CreateGetEventTargetImpl();
        info.SetTarget(targetImpl().value_or(EventTarget()));
    }
    return info;
}

} // namespace OHOS::Ace::NG
