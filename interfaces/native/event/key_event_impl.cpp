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

#include "interfaces/native/native_key_event.h"
#include "interfaces/native/node/event_converter.h"
#include "interfaces/native/node/node_model.h"
#include "interfaces/native/event/ui_input_event_impl.h"


#ifdef __cplusplus
extern "C" {
#endif

ArkUI_KeyEventType_E OH_ArkUI_KeyEvent_GetType(const ArkUI_UIInputEvent *event)
{
    if (!event) {
        return static_cast<ArkUI_KeyEventType_E>(-1);
    }
    const auto* keyEvent = reinterpret_cast<ArkUIKeyEvent*>(event->inputEvent);
    if (!keyEvent) {
        return static_cast<ArkUI_KeyEventType_E>(-1);
    }
    auto result = static_cast<ArkUI_KeyEventType_E>(keyEvent->type);
    return result;
}

ArkUI_KeyCode_E OH_ArkUI_KeyEvent_GetKeyCode(const ArkUI_UIInputEvent *event)
{
    if (!event) {
        return static_cast<ArkUI_KeyCode_E>(-1);
    }
    const auto* keyEvent = reinterpret_cast<ArkUIKeyEvent*>(event->inputEvent);
    if (!keyEvent) {
        return static_cast<ArkUI_KeyCode_E>(-1);
    }
    auto result = static_cast<ArkUI_KeyCode_E>(keyEvent->keyCode);
    return result;
}

const char* OH_ArkUI_KeyEvent_GetKeyText(const ArkUI_UIInputEvent *event)
{
    if (!event) {
        return nullptr;
    }
    const auto* keyEvent = reinterpret_cast<ArkUIKeyEvent*>(event->inputEvent);
    if (!keyEvent) {
        return nullptr;
    }
    return keyEvent->keyText;
}

ArkUI_KeySourceType_E OH_ArkUI_KeyEvent_GetKeySource(const ArkUI_UIInputEvent *event)
{
    if (!event) {
        return static_cast<ArkUI_KeySourceType_E>(-1);
    }
    const auto* keyEvent = reinterpret_cast<ArkUIKeyEvent*>(event->inputEvent);
    if (!keyEvent) {
        return static_cast<ArkUI_KeySourceType_E>(-1);
    }
    auto result = static_cast<ArkUI_KeySourceType_E>(keyEvent->keySource);
    return result;
}

int32_t OH_ArkUI_KeyEvent_GetDeviceId(const ArkUI_UIInputEvent *event)
{
    if (!event) {
        return -1;
    }
    const auto* keyEvent = reinterpret_cast<ArkUIKeyEvent*>(event->inputEvent);
    if (!keyEvent) {
        return -1;
    }
    auto result = static_cast<int32_t>(keyEvent->deviceId);
    return result;
}

int32_t OH_ArkUI_KeyEvent_GetMetaKey(const ArkUI_UIInputEvent *event)
{
    if (!event) {
        return -1;
    }
    const auto* keyEvent = reinterpret_cast<ArkUIKeyEvent*>(event->inputEvent);
    if (!keyEvent) {
        return -1;
    }
    auto result = static_cast<int32_t>(keyEvent->metaKey);
    return result;
}

uint64_t OH_ArkUI_KeyEvent_GetTimestamp(const ArkUI_UIInputEvent *event)
{
    if (!event) {
        return 0.0;
    }
    const auto* keyEvent = reinterpret_cast<ArkUIKeyEvent*>(event->inputEvent);
    if (!keyEvent) {
        return 0.0;
    }
    auto result = static_cast<uint64_t>(keyEvent->timestamp);
    return result;
}

void OH_ArkUI_KeyEvent_StopPropagation(const ArkUI_UIInputEvent *event, bool stopPropagation)
{
    if (!event) {
        return;
    }
    auto* keyEvent = reinterpret_cast<ArkUIKeyEvent*>(event->inputEvent);
    if (!keyEvent) {
        return;
    }
    keyEvent->stopPropagation = stopPropagation;
}

bool OH_ArkUI_KeyEvent_GetModifierKeyState(const ArkUI_UIInputEvent *event, uint32_t modifierKeys)
{
    if (!event) {
        return ARKUI_ERROR_CODE_PARAM_INVALID;
    }
    const auto* keyEvent = reinterpret_cast<ArkUIKeyEvent*>(event->inputEvent);
    if (!keyEvent) {
        return ARKUI_ERROR_CODE_PARAM_INVALID;
    }
    return modifierKeys == keyEvent->getModifierKeyState;
}

ArkUI_KeyIntension_E OH_ArkUI_KeyEvent_GetKeyIntensionCode(const ArkUI_UIInputEvent *event)
{
    if (!event) {
        return static_cast<ArkUI_KeyIntension_E>(-1);
    }
    const auto* keyEvent = reinterpret_cast<ArkUIKeyEvent*>(event->inputEvent);
    if (!keyEvent) {
        return static_cast<ArkUI_KeyIntension_E>(-1);
    }
    auto result = static_cast<ArkUI_KeyIntension_E>(keyEvent->intentionCode);
    return result;
}

uint32_t OH_ArkUI_KeyEvent_GetUnicode(const ArkUI_UIInputEvent *event)
{
    if (!event) {
        return 0;
    }
    const auto* keyEvent = reinterpret_cast<ArkUIKeyEvent*>(event->inputEvent);
    if (!keyEvent) {
        return 0;
    }
    auto result = static_cast<uint32_t>(keyEvent->unicode);
    return result;
}

void OH_ArkUI_KeyEvent_SetRet(const ArkUI_UIInputEvent *event, bool ret)
{
    if (!event) {
        return;
    }
    auto* keyEvent = reinterpret_cast<ArkUIKeyEvent*>(event->inputEvent);
    if (!keyEvent) {
        return;
    }
    keyEvent->ret = ret;
}
#ifdef __cplusplus
};
#endif