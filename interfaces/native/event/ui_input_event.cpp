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

#include "interfaces/native/ui_input_event.h"

#include "core/event/touch_event.h"
#include "frameworks/base/utils/type_definition.h"
#include "frameworks/core/event/axis_event.h"

#ifdef __cplusplus
extern "C" {
#endif

int32_t OH_ArkUI_UIInputEvent_GetType(const ArkUI_UIInputEvent* event)
{
    const auto* uiEvent = static_cast<const OHOS::Ace::UIInputEvent*>(event);
    if (!uiEvent) {
        LOGE("The parameter of OH_ArkUI_UIInputEvent_GetType is invalid");
        return 0;
    }
    return uiEvent->eventType;
}

int64_t OH_ArkUI_UIInputEvent_GetEventTime(const ArkUI_UIInputEvent* event)
{
    const auto* uiEvent = static_cast<const OHOS::Ace::UIInputEvent*>(event);
    if (!uiEvent) {
        LOGE("The parameter of OH_ArkUI_UIInputEvent_GetEventTime is invalid");
        return 0;
    }
    return uiEvent->time.time_since_epoch().count();
}

float OH_ArkUI_PointerEvent_GetX(const ArkUI_UIInputEvent* event)
{
    const auto* uiEvent = static_cast<const OHOS::Ace::UIInputEvent*>(event);
    if (!uiEvent) {
        LOGE("The parameter of OH_ArkUI_PointerEvent_GetX is invalid");
        return 0.0f;
    }
    auto type = uiEvent->eventType;
    switch (type) {
        case ARKUI_UIINPUTEVENT_TYPE_UNKNOWN:
            break;
        case ARKUI_UIINPUTEVENT_TYPE_TOUCH: {
            const auto* touchEvent = static_cast<const OHOS::Ace::TouchEvent*>(event);
            if (touchEvent) {
                return touchEvent->localX;
            }
            break;
        }
        case ARKUI_UIINPUTEVENT_TYPE_AXIS: {
            const auto* axisEvent = static_cast<const OHOS::Ace::AxisEvent*>(event);
            if (axisEvent) {
                return axisEvent->localX;
            }
            break;
        }
        default:
            break;
    }
    LOGE("The parameter of OH_ArkUI_PointerEvent_GetX is invalid");
    return 0.0f;
}

float OH_ArkUI_PointerEvent_GetY(const ArkUI_UIInputEvent* event)
{
    const auto* uiEvent = static_cast<const OHOS::Ace::UIInputEvent*>(event);
    if (!uiEvent) {
        LOGE("The parameter of OH_ArkUI_PointerEvent_GetY is invalid");
        return 0.0f;
    }
    auto type = uiEvent->eventType;
    switch (type) {
        case ARKUI_UIINPUTEVENT_TYPE_UNKNOWN:
            break;
        case ARKUI_UIINPUTEVENT_TYPE_TOUCH: {
            const auto* touchEvent = static_cast<const OHOS::Ace::TouchEvent*>(event);
            if (touchEvent) {
                return touchEvent->localY;
            }
            break;
        }
        case ARKUI_UIINPUTEVENT_TYPE_AXIS: {
            const auto* axisEvent = static_cast<const OHOS::Ace::AxisEvent*>(event);
            if (axisEvent) {
                return axisEvent->localY;
            }
            break;
        }
        default:
            break;
    }
    LOGE("The parameter of OH_ArkUI_PointerEvent_GetY is invalid");
    return 0.0f;
}

float OH_ArkUI_PointerEvent_GetWindowX(const ArkUI_UIInputEvent* event)
{
    const auto* uiEvent = static_cast<const OHOS::Ace::UIInputEvent*>(event);
    if (!uiEvent) {
        LOGE("The parameter of OH_ArkUI_PointerEvent_GetWindowX is invalid");
        return 0.0f;
    }
    auto type = uiEvent->eventType;
    switch (type) {
        case ARKUI_UIINPUTEVENT_TYPE_UNKNOWN:
            break;
        case ARKUI_UIINPUTEVENT_TYPE_TOUCH: {
            const auto* touchEvent = static_cast<const OHOS::Ace::TouchEvent*>(event);
            if (touchEvent) {
                return touchEvent->x;
            }
            break;
        }
        case ARKUI_UIINPUTEVENT_TYPE_AXIS: {
            const auto* axisEvent = static_cast<const OHOS::Ace::AxisEvent*>(event);
            if (axisEvent) {
                return axisEvent->x;
            }
            break;
        }
        default:
            break;
    }
    LOGE("The parameter of OH_ArkUI_PointerEvent_GetWindowX is invalid");
    return 0.0f;
}

float OH_ArkUI_PointerEvent_GetWindowY(const ArkUI_UIInputEvent* event)
{
    const auto* uiEvent = static_cast<const OHOS::Ace::UIInputEvent*>(event);
    if (!uiEvent) {
        LOGE("The parameter of OH_ArkUI_PointerEvent_GetWindowY is invalid");
        return 0.0f;
    }
    auto type = uiEvent->eventType;
    switch (type) {
        case ARKUI_UIINPUTEVENT_TYPE_UNKNOWN:
            break;
        case ARKUI_UIINPUTEVENT_TYPE_TOUCH: {
            const auto* touchEvent = static_cast<const OHOS::Ace::TouchEvent*>(event);
            if (touchEvent) {
                return touchEvent->y;
            }
            break;
        }
        case ARKUI_UIINPUTEVENT_TYPE_AXIS: {
            const auto* axisEvent = static_cast<const OHOS::Ace::AxisEvent*>(event);
            if (axisEvent) {
                return axisEvent->y;
            }
            break;
        }
        default:
            break;
    }
    LOGE("The parameter of OH_ArkUI_PointerEvent_GetWindowY is invalid");
    return 0.0f;
}

float OH_ArkUI_PointerEvent_GetDisplayX(const ArkUI_UIInputEvent* event)
{
    const auto* uiEvent = static_cast<const OHOS::Ace::UIInputEvent*>(event);
    if (!uiEvent) {
        LOGE("The parameter of OH_ArkUI_PointerEvent_GetDisplayX is invalid");
        return 0.0f;
    }
    auto type = uiEvent->eventType;
    switch (type) {
        case ARKUI_UIINPUTEVENT_TYPE_UNKNOWN:
            break;
        case ARKUI_UIINPUTEVENT_TYPE_TOUCH: {
            const auto* touchEvent = static_cast<const OHOS::Ace::TouchEvent*>(event);
            if (touchEvent) {
                return touchEvent->screenX;
            }
            break;
        }
        case ARKUI_UIINPUTEVENT_TYPE_AXIS: {
            const auto* axisEvent = static_cast<const OHOS::Ace::AxisEvent*>(event);
            if (axisEvent) {
                return axisEvent->screenX;
            }
            break;
        }
        default:
            break;
    }
    LOGE("The parameter of OH_ArkUI_PointerEvent_GetDisplayX is invalid");
    return 0.0f;
}

float OH_ArkUI_PointerEvent_GetDisplayY(const ArkUI_UIInputEvent* event)
{
    const auto* uiEvent = static_cast<const OHOS::Ace::UIInputEvent*>(event);
    if (!uiEvent) {
        LOGE("The parameter of OH_ArkUI_PointerEvent_GetDisplayY is invalid");
        return 0.0f;
    }
    auto type = uiEvent->eventType;
    switch (type) {
        case ARKUI_UIINPUTEVENT_TYPE_UNKNOWN:
            break;
        case ARKUI_UIINPUTEVENT_TYPE_TOUCH: {
            const auto* touchEvent = static_cast<const OHOS::Ace::TouchEvent*>(event);
            if (touchEvent) {
                return touchEvent->screenY;
            }
            break;
        }
        case ARKUI_UIINPUTEVENT_TYPE_AXIS: {
            const auto* axisEvent = static_cast<const OHOS::Ace::AxisEvent*>(event);
            if (axisEvent) {
                return axisEvent->screenY;
            }
            break;
        }
        default:
            break;
    }
    LOGE("The parameter of OH_ArkUI_PointerEvent_GetDisplayY is invalid");
    return 0.0f;
}

double OH_ArkUI_AxisEvent_GetVerticalAxisValue(const ArkUI_UIInputEvent* event)
{
    const auto* axisEvent = static_cast<const OHOS::Ace::AxisEvent*>(event);
    if (!axisEvent) {
        LOGE("The parameter of OH_ArkUI_AxisEvent_GetVerticalAxisValue is invalid");
        return 0.0;
    }
    return axisEvent->verticalAxis;
}

double OH_ArkUI_AxisEvent_GetHorizontalAxisValue(const ArkUI_UIInputEvent* event)
{
    const auto* axisEvent = static_cast<const OHOS::Ace::AxisEvent*>(event);
    if (!axisEvent) {
        LOGE("The parameter of OH_ArkUI_AxisEvent_GetHorizontalAxisValue is invalid");
        return 0.0;
    }
    return axisEvent->horizontalAxis;
}

double OH_ArkUI_AxisEvent_GetPinchAxisScaleValue(const ArkUI_UIInputEvent* event)
{
    const auto* axisEvent = static_cast<const OHOS::Ace::AxisEvent*>(event);
    if (!axisEvent) {
        LOGE("The parameter of OH_ArkUI_AxisEvent_GetPinchAxisScaleValue is invalid");
        return 0.0;
    }
    return axisEvent->pinchAxisScale;
}

#ifdef __cplusplus
};
#endif
