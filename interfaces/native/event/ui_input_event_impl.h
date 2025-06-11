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
#ifndef ARKUI_NATIVE_EVENT_UI_INPUT_EVENT_IMPL_H
#define ARKUI_NATIVE_EVENT_UI_INPUT_EVENT_IMPL_H
#pragma once

#include "interfaces/native/ui_input_event.h"

#ifdef __cplusplus
extern "C" {
#endif

extern thread_local ArkUI_ErrorCode g_latestEventStatus;
extern thread_local ArkUI_ErrorCode g_scenarioSupportCheckResult;

typedef enum {
    AXIS_EVENT_ID = 0, // defined in ace_engine/frameworks/core/event/axis_event.h
    TOUCH_EVENT_ID = 1, // defined in ace_engine/frameworks/core/event/touch_event.h
    C_TOUCH_EVENT_ID = 2, // defined in ace_engine/frameworks/core/interfaces/arkoala/arkoala_api.h
    C_MOUSE_EVENT_ID = 3, // defined in ace_engine/frameworks/core/interfaces/arkoala/arkoala_api.h
    C_AXIS_EVENT_ID = 4, // defined in ace_engine/frameworks/core/interfaces/arkoala/arkoala_api.h
    C_KEY_EVENT_ID = 5, // defined in ace_engine/frameworks/core/interfaces/arkoala/arkoala_api.h
    C_FOCUS_AXIS_EVENT_ID = 6, // defined in ace_engine/frameworks/core/interfaces/arkoala/arkoala_api.h
    C_CLICK_EVENT_ID = 7, // defined in ace_engine/frameworks/core/interfaces/arkoala/arkoala_api.h
    C_HOVER_EVENT_ID = 8, // defined in ace_engine/frameworks/core/interfaces/arkoala/arkoala_api.h
} ArkUIEventTypeId;

struct ArkUI_UIInputEvent {
    ArkUI_UIInputEvent_Type inputType;
    ArkUIEventTypeId eventTypeId;
    void* inputEvent;
    bool isCloned = false;
    int32_t apiVersion = 0;
};

typedef enum {
    S_UNKNOWN = 0,                       // unknown scenario
    S_NODE_TOUCH_EVENT = 1 << 0,         // 0x00000001 callback of NODE_TOUCH_EVENT
    S_NODE_ON_TOUCH_INTERCEPT = 1 << 1,  // 0x00000002 callback of NODE_ON_TOUCH_INTERCEPT
    S_NODE_ON_MOUSE = 1 << 2,            // 0x00000004 callback of NODE_ON_MOUSE
    S_NODE_ON_KEY_EVENT = 1 << 3,        // 0x00000008 callback of NODE_ON_KEY_EVENT
    S_NODE_ON_KEY_PRE_IME = 1 << 4,      // 0x00000010 callback of NODE_ON_KEY_PRE_IME
    S_NODE_ON_FOCUS_AXIS = 1 << 5,       // 0x00000020 callback of NODE_ON_FOCUS_AXIS
    S_NODE_DISPATCH_KEY_EVENT = 1 << 6,  // 0x00000040 callback of NODE_DISPATCH_KEY_EVENT
    S_NODE_ON_AXIS = 1 << 7,             // 0x00000080 callback of NODE_ON_AXIS
    S_NODE_ON_CLICK_EVENT = 1 << 8,      // 0x00000100 callback of NODE_ON_CLICK_EVENT
    S_NODE_ON_HOVER_EVENT = 1 << 9,      // 0x00000200 callback of NODE_ON_HOVER_EVENT
    S_NODE_ON_HOVER_MOVE = 1 << 10,      // 0x00000400 callback of NODE_ON_HOVER_MOVE
    S_GESTURE_TOUCH_EVENT = 1 << 11,     // 0x00000800 gesture triggered by touch
    S_GESTURE_AXIS_EVENT = 1 << 12,      // 0x00001000 gesture triggered by axis
    S_GESTURE_MOUSE_EVENT = 1 << 13,     // 0x00002000 gesutre triggered by mouse
    S_GESTURE_CLICK_EVENT = 1 << 14,     // 0x00004000 click or tap gesture triggered by keyboard
    S_NXC_ON_TOUCH_INTERCEPT = 1 << 15,  // 0x00008000 nativeXComponent OnTouchIntercept
    S_NXC_DISPATCH_AXIS_EVENT = 1 << 16, // 0x00010000 nativeXComponent UIAxisEventCallback
    S_ALL_C_MOUSE_EVENT = S_NODE_ON_MOUSE | S_GESTURE_MOUSE_EVENT, // 0x00002004 2 scenarios give c mouse event
    S_ALL_C_TOUCH_EVENT = S_NODE_TOUCH_EVENT | S_NODE_ON_TOUCH_INTERCEPT |
                          S_NODE_ON_HOVER_EVENT, // 0x00000203 3 scenarios give c touch event
    S_ALL_C_KEY_EVENT = S_NODE_ON_KEY_EVENT | S_NODE_ON_KEY_PRE_IME |
                        S_NODE_DISPATCH_KEY_EVENT, // 0x00000058 3 scenarios give c key event
} ArkUIEventScenario;

ArkUI_ErrorCode CheckIsSupportedScenario(int32_t scenarioExpr, const ArkUI_UIInputEvent* event);

inline void CheckSupportedScenarioAndResetEventStatus(int32_t scenarioExpr, const ArkUI_UIInputEvent* event)
{
    g_scenarioSupportCheckResult = CheckIsSupportedScenario(scenarioExpr, event);
    g_latestEventStatus = ARKUI_ERROR_CODE_NO_ERROR;
}

#define RETURN_RET_WITH_STATUS_CHECK(ret, errorCode)                                                                \
    do {                                                                                                            \
        g_latestEventStatus =                                                                                       \
            g_scenarioSupportCheckResult == ARKUI_ERROR_CODE_NO_ERROR ? (errorCode) : g_scenarioSupportCheckResult; \
        return ret;                                                                                                 \
    } while (0)

#define RETURN_WITH_STATUS_CHECK(errorCode)                                                                         \
    do {                                                                                                            \
        g_latestEventStatus =                                                                                       \
            g_scenarioSupportCheckResult == ARKUI_ERROR_CODE_NO_ERROR ? (errorCode) : g_scenarioSupportCheckResult; \
        return;                                                                                                     \
    } while (0)

#ifdef __cplusplus
};
#endif
#endif // ARKUI_NATIVE_EVENT_UI_INPUT_EVENT_IMPL_H