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

ArkUI_KeyEventType OH_ArkUI_KeyEvent_GetType(const ArkUI_UIInputEvent *event)
{
    if (!event) {
        return static_cast<ArkUI_KeyEventType>(-1);
    }
    const auto* keyEvent = reinterpret_cast<ArkUIKeyEvent*>(event->inputEvent);
    if (!keyEvent) {
        return static_cast<ArkUI_KeyEventType>(-1);
    }
    auto result = static_cast<ArkUI_KeyEventType>(keyEvent->type);
    return result;
}

int32_t OH_ArkUI_KeyEvent_GetKeyCode(const ArkUI_UIInputEvent *event)
{
    if (!event) {
        return -1;
    }
    const auto* keyEvent = reinterpret_cast<ArkUIKeyEvent*>(event->inputEvent);
    if (!keyEvent) {
        return -1;
    }
    auto result = static_cast<int32_t>(keyEvent->keyCode);
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

ArkUI_KeySourceType OH_ArkUI_KeyEvent_GetKeySource(const ArkUI_UIInputEvent *event)
{
    if (!event) {
        return static_cast<ArkUI_KeySourceType>(-1);
    }
    const auto* keyEvent = reinterpret_cast<ArkUIKeyEvent*>(event->inputEvent);
    if (!keyEvent) {
        return static_cast<ArkUI_KeySourceType>(-1);
    }
    auto result = static_cast<ArkUI_KeySourceType>(keyEvent->keySource);
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
        return false;
    }
    const auto* keyEvent = reinterpret_cast<ArkUIKeyEvent*>(event->inputEvent);
    if (!keyEvent) {
        return false;
    }
    return modifierKeys == keyEvent->getModifierKeyState;
}

ArkUI_KeyIntension OH_ArkUI_KeyEvent_GetKeyIntensionCode(const ArkUI_UIInputEvent *event)
{
    if (!event) {
        return static_cast<ArkUI_KeyIntension>(-1);
    }
    const auto* keyEvent = reinterpret_cast<ArkUIKeyEvent*>(event->inputEvent);
    if (!keyEvent) {
        return static_cast<ArkUI_KeyIntension>(-1);
    }
    auto result = static_cast<ArkUI_KeyIntension>(keyEvent->intentionCode);
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

void OH_ArkUI_KeyEvent_SetConsumed(const ArkUI_UIInputEvent *event, bool isConsumed)
{
    if (!event) {
        return;
    }
    auto* keyEvent = reinterpret_cast<ArkUIKeyEvent*>(event->inputEvent);
    if (!keyEvent) {
        return;
    }
    keyEvent->isConsumed = isConsumed;
}
#ifdef __cplusplus
};
#endif