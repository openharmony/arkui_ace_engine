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

#ifndef FOUNDATION_ACE_ADAPTER_OHOS_ENTRANCE_MMI_EVENT_CONVERTOR_H
#define FOUNDATION_ACE_ADAPTER_OHOS_ENTRANCE_MMI_EVENT_CONVERTOR_H

#include "key_event.h"
#include "pointer_event.h"
#include "input_manager.h"

#include "base/geometry/ng/offset_t.h"
#include "base/geometry/ng/vector.h"
#include "base/log/log.h"
#include "base/utils/macros.h"
#include "core/event/axis_event.h"
#include "core/event/key_event.h"
#include "core/event/mouse_event.h"
#include "core/event/focus_axis_event.h"
#include "core/event/touch_event.h"
#include "core/event/pointer_event.h"
#ifdef SUPPORT_DIGITAL_CROWN
#include "core/event/crown_event.h"
#endif

namespace OHOS::Ace::Platform {
namespace {
const std::unordered_map<SourceType, int32_t> SOURCE_TYPE_MAP = {
    { SourceType::TOUCH, MMI::PointerEvent::SOURCE_TYPE_TOUCHSCREEN },
    { SourceType::TOUCH_PAD, MMI::PointerEvent::SOURCE_TYPE_TOUCHPAD },
    { SourceType::MOUSE, MMI::PointerEvent::SOURCE_TYPE_MOUSE },
};

const std::unordered_map<TouchType, int32_t> TOUCH_TYPE_MAP = {
    { TouchType::CANCEL, MMI::PointerEvent::POINTER_ACTION_CANCEL },
    { TouchType::DOWN, MMI::PointerEvent::POINTER_ACTION_DOWN },
    { TouchType::MOVE, MMI::PointerEvent::POINTER_ACTION_MOVE },
    { TouchType::UP, MMI::PointerEvent::POINTER_ACTION_UP },
    { TouchType::PULL_DOWN, MMI::PointerEvent::POINTER_ACTION_PULL_DOWN },
    { TouchType::PULL_MOVE, MMI::PointerEvent::POINTER_ACTION_PULL_MOVE },
    { TouchType::PULL_UP, MMI::PointerEvent::POINTER_ACTION_PULL_UP },
    { TouchType::PULL_IN_WINDOW, MMI::PointerEvent::POINTER_ACTION_PULL_IN_WINDOW },
    { TouchType::PULL_OUT_WINDOW, MMI::PointerEvent::POINTER_ACTION_PULL_OUT_WINDOW },
};
} // namespace

template<typename E>
void GetEventDevice(int32_t sourceType, E& event)
{
    switch (sourceType) {
        case OHOS::MMI::PointerEvent::SOURCE_TYPE_TOUCHSCREEN:
            event.sourceType = SourceType::TOUCH;
            break;
        case OHOS::MMI::PointerEvent::SOURCE_TYPE_TOUCHPAD:
            event.sourceType = SourceType::TOUCH_PAD;
            break;
        case OHOS::MMI::PointerEvent::SOURCE_TYPE_MOUSE:
        case OHOS::MMI::PointerEvent::SOURCE_TYPE_JOYSTICK:
            event.sourceType = SourceType::MOUSE;
            break;
        case OHOS::MMI::PointerEvent::SOURCE_TYPE_CROWN:
            event.sourceType = SourceType::CROWN;
            break;
        default:
            event.sourceType = SourceType::NONE;
            break;
    }
}

TouchEvent ConvertTouchEvent(const std::shared_ptr<MMI::PointerEvent>& pointerEvent);

void SetTouchEventType(int32_t orgAction, TouchEvent& event);

// when the event didn't do touchtest, useRealtimeMatrix need to set true to get current matrix.
void CalculatePointerEvent(const std::shared_ptr<MMI::PointerEvent>& point, const RefPtr<NG::FrameNode>& frameNode,
    bool useRealtimeMatrix = false);

#ifdef SUPPORT_DIGITAL_CROWN
void ConvertCrownEvent(const std::shared_ptr<MMI::PointerEvent>& pointerEvent, CrownEvent& event);
#endif

void CalculatePointerEvent(const NG::OffsetF& offsetF, const std::shared_ptr<MMI::PointerEvent>& point,
    const NG::VectorF& scale, int32_t udegree = 0);

void CalculateWindowCoordinate(const NG::OffsetF& offsetF, const std::shared_ptr<MMI::PointerEvent>& point,
    const NG::VectorF& scale, const int32_t udegree = 0);

void ConvertMouseEvent(const std::shared_ptr<MMI::PointerEvent>& pointerEvent,
    MouseEvent& events, bool isScenceBoardWindow);

void ConvertAxisEvent(const std::shared_ptr<MMI::PointerEvent>& pointerEvent, AxisEvent& event);

void ConvertKeyEvent(const std::shared_ptr<MMI::KeyEvent>& keyEvent, KeyEvent& event);

void ConvertFocusAxisEvent(const std::shared_ptr<MMI::PointerEvent>& pointerEvent, NG::FocusAxisEvent& event);

void ConvertPointerEvent(const std::shared_ptr<MMI::PointerEvent>& pointerEvent, DragPointerEvent& event);

void LogPointInfo(const std::shared_ptr<MMI::PointerEvent>& pointerEvent, int32_t instanceId);

void UpdatePointerAction(std::shared_ptr<MMI::PointerEvent>& pointerEvent, const PointerAction action);

bool GetPointerEventToolType(const std::shared_ptr<MMI::PointerEvent>& pointerEvent, int32_t& toolType);

SourceTool GetSourceTool(int32_t orgToolType);
} // namespace OHOS::Ace::Platform

#endif // FOUNDATION_ACE_ADAPTER_OHOS_ENTRANCE_MMI_EVENT_CONVERTOR_H
