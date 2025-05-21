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
#include "frameworks/core/interfaces/arkoala/arkoala_api.h"

#ifdef __cplusplus
extern "C" {
#endif

ArkUI_KeyEventType OH_ArkUI_KeyEvent_GetType(const ArkUI_UIInputEvent *event)
{
    if (!event) {
        latestEventStatus = ARKUI_ERROR_CODE_PARAM_INVALID;
        return static_cast<ArkUI_KeyEventType>(-1);
    }
    const auto* keyEvent = reinterpret_cast<ArkUIKeyEvent*>(event->inputEvent);
    if (!keyEvent) {
        latestEventStatus = ARKUI_ERROR_CODE_PARAM_INVALID;
        return static_cast<ArkUI_KeyEventType>(-1);
    }
    auto result = static_cast<ArkUI_KeyEventType>(keyEvent->type);
    latestEventStatus =
        event->eventTypeId == C_KEY_EVENT_ID ? ARKUI_ERROR_CODE_NO_ERROR : ARKUI_ERROR_INPUT_EVENT_TYPE_NOT_SUPPORT;
    return result;
}

int32_t OH_ArkUI_KeyEvent_GetKeyCode(const ArkUI_UIInputEvent *event)
{
    if (!event) {
        latestEventStatus = ARKUI_ERROR_CODE_PARAM_INVALID;
        return -1;
    }
    const auto* keyEvent = reinterpret_cast<ArkUIKeyEvent*>(event->inputEvent);
    if (!keyEvent) {
        latestEventStatus = ARKUI_ERROR_CODE_PARAM_INVALID;
        return -1;
    }
    auto result = static_cast<int32_t>(keyEvent->keyCode);
    latestEventStatus =
        event->eventTypeId == C_KEY_EVENT_ID ? ARKUI_ERROR_CODE_NO_ERROR : ARKUI_ERROR_INPUT_EVENT_TYPE_NOT_SUPPORT;
    return result;
}

const char* OH_ArkUI_KeyEvent_GetKeyText(const ArkUI_UIInputEvent *event)
{
    if (!event) {
        latestEventStatus = ARKUI_ERROR_CODE_PARAM_INVALID;
        return nullptr;
    }
    const auto* keyEvent = reinterpret_cast<ArkUIKeyEvent*>(event->inputEvent);
    if (!keyEvent) {
        latestEventStatus = ARKUI_ERROR_CODE_PARAM_INVALID;
        return nullptr;
    }
    latestEventStatus =
        event->eventTypeId == C_KEY_EVENT_ID ? ARKUI_ERROR_CODE_NO_ERROR : ARKUI_ERROR_INPUT_EVENT_TYPE_NOT_SUPPORT;
    return keyEvent->keyText;
}

ArkUI_KeySourceType OH_ArkUI_KeyEvent_GetKeySource(const ArkUI_UIInputEvent *event)
{
    if (!event) {
        latestEventStatus = ARKUI_ERROR_CODE_PARAM_INVALID;
        return static_cast<ArkUI_KeySourceType>(-1);
    }
    const auto* keyEvent = reinterpret_cast<ArkUIKeyEvent*>(event->inputEvent);
    if (!keyEvent) {
        latestEventStatus = ARKUI_ERROR_CODE_PARAM_INVALID;
        return static_cast<ArkUI_KeySourceType>(-1);
    }
    auto result = static_cast<ArkUI_KeySourceType>(keyEvent->keySource);
    latestEventStatus =
        event->eventTypeId == C_KEY_EVENT_ID ? ARKUI_ERROR_CODE_NO_ERROR : ARKUI_ERROR_INPUT_EVENT_TYPE_NOT_SUPPORT;
    return result;
}

void OH_ArkUI_KeyEvent_StopPropagation(const ArkUI_UIInputEvent *event, bool stopPropagation)
{
    if (!event) {
        latestEventStatus = ARKUI_ERROR_CODE_PARAM_INVALID;
        return;
    }
    auto* keyEvent = reinterpret_cast<ArkUIKeyEvent*>(event->inputEvent);
    if (!keyEvent) {
        latestEventStatus = ARKUI_ERROR_CODE_PARAM_INVALID;
        return;
    }
    latestEventStatus =
        event->eventTypeId == C_KEY_EVENT_ID ? ARKUI_ERROR_CODE_NO_ERROR : ARKUI_ERROR_INPUT_EVENT_TYPE_NOT_SUPPORT;
    keyEvent->stopPropagation = stopPropagation;
}

ArkUI_KeyIntension OH_ArkUI_KeyEvent_GetKeyIntensionCode(const ArkUI_UIInputEvent *event)
{
    if (!event) {
        latestEventStatus = ARKUI_ERROR_CODE_PARAM_INVALID;
        return static_cast<ArkUI_KeyIntension>(-1);
    }
    const auto* keyEvent = reinterpret_cast<ArkUIKeyEvent*>(event->inputEvent);
    if (!keyEvent) {
        latestEventStatus = ARKUI_ERROR_CODE_PARAM_INVALID;
        return static_cast<ArkUI_KeyIntension>(-1);
    }
    auto result = static_cast<ArkUI_KeyIntension>(keyEvent->intentionCode);
    latestEventStatus =
        event->eventTypeId == C_KEY_EVENT_ID ? ARKUI_ERROR_CODE_NO_ERROR : ARKUI_ERROR_INPUT_EVENT_TYPE_NOT_SUPPORT;
    return result;
}

uint32_t OH_ArkUI_KeyEvent_GetUnicode(const ArkUI_UIInputEvent *event)
{
    if (!event) {
        latestEventStatus = ARKUI_ERROR_CODE_PARAM_INVALID;
        return 0;
    }
    const auto* keyEvent = reinterpret_cast<ArkUIKeyEvent*>(event->inputEvent);
    if (!keyEvent) {
        latestEventStatus = ARKUI_ERROR_CODE_PARAM_INVALID;
        return 0;
    }
    auto result = static_cast<uint32_t>(keyEvent->unicode);
    latestEventStatus =
        event->eventTypeId == C_KEY_EVENT_ID ? ARKUI_ERROR_CODE_NO_ERROR : ARKUI_ERROR_INPUT_EVENT_TYPE_NOT_SUPPORT;
    return result;
}

void OH_ArkUI_KeyEvent_SetConsumed(const ArkUI_UIInputEvent *event, bool isConsumed)
{
    if (!event) {
        latestEventStatus = ARKUI_ERROR_CODE_PARAM_INVALID;
        return;
    }
    auto* keyEvent = reinterpret_cast<ArkUIKeyEvent*>(event->inputEvent);
    if (!keyEvent) {
        latestEventStatus = ARKUI_ERROR_CODE_PARAM_INVALID;
        return;
    }
    keyEvent->isConsumed = isConsumed;
    if (event->eventTypeId == C_KEY_EVENT_ID && keyEvent->subKind == ON_KEY_EVENT) {
        latestEventStatus = ARKUI_ERROR_CODE_NO_ERROR;
    } else {
        latestEventStatus = ARKUI_ERROR_INPUT_EVENT_TYPE_NOT_SUPPORT;
    }
}

void OH_ArkUI_KeyEvent_Dispatch(ArkUI_NodeHandle node, const ArkUI_UIInputEvent* event)
{
    if (!node || !event) {
        latestEventStatus = ARKUI_ERROR_CODE_PARAM_INVALID;
        return;
    }
    auto* keyEvent = reinterpret_cast<ArkUIKeyEvent*>(event->inputEvent);
    if (!keyEvent) {
        latestEventStatus = ARKUI_ERROR_CODE_PARAM_INVALID;
        return;
    }
    auto fullImpl = OHOS::Ace::NodeModel::GetFullImpl();
    fullImpl->getNodeModifiers()->getCommonModifier()->dispatchKeyEvent(node->uiNodeHandle, keyEvent);
    latestEventStatus =
        event->eventTypeId == C_KEY_EVENT_ID ? ARKUI_ERROR_CODE_NO_ERROR : ARKUI_ERROR_INPUT_EVENT_TYPE_NOT_SUPPORT;
}

ArkUI_ErrorCode OH_ArkUI_KeyEvent_IsNumLockOn(const ArkUI_UIInputEvent* event, bool* state)
{
    if (!event || !state) {
        latestEventStatus = ARKUI_ERROR_CODE_PARAM_INVALID;
        return ARKUI_ERROR_CODE_PARAM_INVALID;
    }
    const auto* keyEvent = reinterpret_cast<ArkUIKeyEvent*>(event->inputEvent);
    if (!keyEvent) {
        latestEventStatus = ARKUI_ERROR_CODE_PARAM_INVALID;
        return ARKUI_ERROR_CODE_PARAM_INVALID;
    }
    *state = keyEvent->isNumLockOn;
    latestEventStatus =
        event->eventTypeId == C_KEY_EVENT_ID ? ARKUI_ERROR_CODE_NO_ERROR : ARKUI_ERROR_INPUT_EVENT_TYPE_NOT_SUPPORT;
    return ARKUI_ERROR_CODE_NO_ERROR;
}

ArkUI_ErrorCode OH_ArkUI_KeyEvent_IsCapsLockOn(const ArkUI_UIInputEvent* event, bool* state)
{
    if (!event || !state) {
        latestEventStatus = ARKUI_ERROR_CODE_PARAM_INVALID;
        return ARKUI_ERROR_CODE_PARAM_INVALID;
    }
    const auto* keyEvent = reinterpret_cast<ArkUIKeyEvent*>(event->inputEvent);
    if (!keyEvent) {
        latestEventStatus = ARKUI_ERROR_CODE_PARAM_INVALID;
        return ARKUI_ERROR_CODE_PARAM_INVALID;
    }
    *state = keyEvent->isCapsLockOn;
    latestEventStatus =
        event->eventTypeId == C_KEY_EVENT_ID ? ARKUI_ERROR_CODE_NO_ERROR : ARKUI_ERROR_INPUT_EVENT_TYPE_NOT_SUPPORT;
    return ARKUI_ERROR_CODE_NO_ERROR;
}

ArkUI_ErrorCode OH_ArkUI_KeyEvent_IsScrollLockOn(const ArkUI_UIInputEvent* event, bool* state)
{
    if (!event || !state) {
        latestEventStatus = ARKUI_ERROR_CODE_PARAM_INVALID;
        return ARKUI_ERROR_CODE_PARAM_INVALID;
    }
    const auto* keyEvent = reinterpret_cast<ArkUIKeyEvent*>(event->inputEvent);
    if (!keyEvent) {
        latestEventStatus = ARKUI_ERROR_CODE_PARAM_INVALID;
        return ARKUI_ERROR_CODE_PARAM_INVALID;
    }
    *state = keyEvent->isScrollLockOn;
    latestEventStatus =
        event->eventTypeId == C_KEY_EVENT_ID ? ARKUI_ERROR_CODE_NO_ERROR : ARKUI_ERROR_INPUT_EVENT_TYPE_NOT_SUPPORT;
    return ARKUI_ERROR_CODE_NO_ERROR;
}
#ifdef __cplusplus
};
#endif