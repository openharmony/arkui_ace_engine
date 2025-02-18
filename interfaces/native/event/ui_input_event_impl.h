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

typedef enum {
    AXIS_EVENT_ID = 0, // defined in ace_engine/frameworks/core/event/axis_event.h
    TOUCH_EVENT_ID = 1, // defined in ace_engine/frameworks/core/event/touch_event.h
    C_TOUCH_EVENT_ID = 2, // defined in ace_engine/frameworks/core/interfaces/arkoala/arkoala_api.h
    C_MOUSE_EVENT_ID = 3, // defined in ace_engine/frameworks/core/interfaces/arkoala/arkoala_api.h
    C_AXIS_EVENT_ID = 4, // defined in ace_engine/frameworks/core/interfaces/arkoala/arkoala_api.h
    C_KEY_EVENT_ID = 5, // defined in ace_engine/frameworks/core/interfaces/arkoala/arkoala_api.h
    C_FOCUS_AXIS_EVENT_ID = 6, // defined in ace_engine/frameworks/core/interfaces/arkoala/arkoala_api.h
} ArkUIEventTypeId;

struct ArkUI_UIInputEvent {
    ArkUI_UIInputEvent_Type inputType;
    ArkUIEventTypeId eventTypeId;
    void* inputEvent;
};

#ifdef __cplusplus
};
#endif
#endif // ARKUI_NATIVE_EVENT_UI_INPUT_EVENT_IMPL_H