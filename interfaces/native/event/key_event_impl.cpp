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

void OH_ArkUI_KeyEvent_Dispatch(ArkUI_NodeHandle node, const ArkUI_UIInputEvent* event)
{
    if (!node || !event) {
        return;
    }
    auto* keyEvent = reinterpret_cast<ArkUIKeyEvent*>(event->inputEvent);
    if (!keyEvent) {
        return;
    }
    auto fullImpl = OHOS::Ace::NodeModel::GetFullImpl();
    fullImpl->getNodeModifiers()->getCommonModifier()->dispatchKeyEvent(node->uiNodeHandle, keyEvent);
}

ArkUI_ErrorCode OH_ArkUI_KeyEvent_IsNumLockOn(const ArkUI_UIInputEvent* event, bool* state)
{
    if (!event || !state) {
        return ARKUI_ERROR_CODE_PARAM_INVALID;
    }
    const auto* keyEvent = reinterpret_cast<ArkUIKeyEvent*>(event->inputEvent);
    if (!keyEvent) {
        return ARKUI_ERROR_CODE_PARAM_INVALID;
    }
    *state = keyEvent->isNumLockOn;
    return ARKUI_ERROR_CODE_NO_ERROR;
}

ArkUI_ErrorCode OH_ArkUI_KeyEvent_IsCapsLockOn(const ArkUI_UIInputEvent* event, bool* state)
{
    if (!event || !state) {
        return ARKUI_ERROR_CODE_PARAM_INVALID;
    }
    const auto* keyEvent = reinterpret_cast<ArkUIKeyEvent*>(event->inputEvent);
    if (!keyEvent) {
        return ARKUI_ERROR_CODE_PARAM_INVALID;
    }
    *state = keyEvent->isCapsLockOn;
    return ARKUI_ERROR_CODE_NO_ERROR;
}

ArkUI_ErrorCode OH_ArkUI_KeyEvent_IsScrollLockOn(const ArkUI_UIInputEvent* event, bool* state)
{
    if (!event || !state) {
        return ARKUI_ERROR_CODE_PARAM_INVALID;
    }
    const auto* keyEvent = reinterpret_cast<ArkUIKeyEvent*>(event->inputEvent);
    if (!keyEvent) {
        return ARKUI_ERROR_CODE_PARAM_INVALID;
    }
    *state = keyEvent->isScrollLockOn;
    return ARKUI_ERROR_CODE_NO_ERROR;
}
#ifdef __cplusplus
};
#endif