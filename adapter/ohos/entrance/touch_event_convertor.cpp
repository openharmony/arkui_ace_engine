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

#include "frameworks/core/interfaces/native/node/touch_event_convertor.h"

#include "adapter/ohos/entrance/ace_container.h"
#include "adapter/ohos/entrance/mmi_event_convertor.h"

namespace OHOS::Ace::NG {

TouchEvent ConvertToTouchEvent(const std::shared_ptr<MMI::PointerEvent>& srcPointerEvent)
{
    return Platform::ConvertTouchEvent(srcPointerEvent);
}

void ConvertToMouseEvent(MouseEvent& mouseEvent, const std::shared_ptr<MMI::PointerEvent>& srcPointerEvent)
{
    Platform::ConvertMouseEvent(srcPointerEvent, mouseEvent, Container::Current()->IsSceneBoardWindow());
}

void ConvertToAxisEvent(AxisEvent& event, const std::shared_ptr<MMI::PointerEvent>& srcPointerEvent)
{
    Platform::ConvertAxisEvent(srcPointerEvent, event);
}

void SetClonedPointerEvent(const MMI::PointerEvent* pointerEvent, ArkUITouchEvent* arkUITouchEventCloned)
{
    Platform::SetClonedPointerEvent(pointerEvent, arkUITouchEventCloned);
}

void SetPostPointerEvent(const MMI::PointerEvent* pointerEvent, TouchEvent& touchEvent)
{
    Platform::SetPostPointerEvent(pointerEvent, touchEvent);
}

TouchType GetTouchEventType(const std::shared_ptr<MMI::PointerEvent>& pointerEvent)
{
    return Platform::GetTouchTypeFromPointerEvent(pointerEvent);
}

AxisAction GetAxisEventType(const std::shared_ptr<MMI::PointerEvent>& pointerEvent)
{
    return Platform::GetAxisActionFromPointerEvent(pointerEvent);
}

MouseAction GetMouseEventType(const std::shared_ptr<MMI::PointerEvent>& pointerEvent)
{
    return Platform::GetMouseActionFromPointerEvent(pointerEvent);
}
}