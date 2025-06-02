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
    CheckSupportedScenarioAndResetEventStatus(S_ALL_C_KEY_EVENT, event);
    if (!event) {
        RETURN_RET_WITH_STATUS_CHECK(static_cast<ArkUI_KeyEventType>(-1), ARKUI_ERROR_CODE_PARAM_INVALID);
    }
    const auto* keyEvent = reinterpret_cast<ArkUIKeyEvent*>(event->inputEvent);
    if (!keyEvent) {
        RETURN_RET_WITH_STATUS_CHECK(static_cast<ArkUI_KeyEventType>(-1), ARKUI_ERROR_CODE_PARAM_INVALID);
    }
    auto result = static_cast<ArkUI_KeyEventType>(keyEvent->type);
    RETURN_RET_WITH_STATUS_CHECK(result, ARKUI_ERROR_CODE_NO_ERROR);
}

int32_t OH_ArkUI_KeyEvent_GetKeyCode(const ArkUI_UIInputEvent *event)
{
    CheckSupportedScenarioAndResetEventStatus(S_ALL_C_KEY_EVENT, event);
    if (!event) {
        RETURN_RET_WITH_STATUS_CHECK(-1, ARKUI_ERROR_CODE_PARAM_INVALID);
    }
    const auto* keyEvent = reinterpret_cast<ArkUIKeyEvent*>(event->inputEvent);
    if (!keyEvent) {
        RETURN_RET_WITH_STATUS_CHECK(-1, ARKUI_ERROR_CODE_PARAM_INVALID);
    }
    auto result = static_cast<int32_t>(keyEvent->keyCode);
    RETURN_RET_WITH_STATUS_CHECK(result, ARKUI_ERROR_CODE_NO_ERROR);
}

const char* OH_ArkUI_KeyEvent_GetKeyText(const ArkUI_UIInputEvent *event)
{
    CheckSupportedScenarioAndResetEventStatus(S_ALL_C_KEY_EVENT, event);
    if (!event) {
        RETURN_RET_WITH_STATUS_CHECK(nullptr, ARKUI_ERROR_CODE_PARAM_INVALID);
    }
    const auto* keyEvent = reinterpret_cast<ArkUIKeyEvent*>(event->inputEvent);
    if (!keyEvent) {
        RETURN_RET_WITH_STATUS_CHECK(nullptr, ARKUI_ERROR_CODE_PARAM_INVALID);
    }
    RETURN_RET_WITH_STATUS_CHECK(keyEvent->keyText, ARKUI_ERROR_CODE_NO_ERROR);
}

ArkUI_KeySourceType OH_ArkUI_KeyEvent_GetKeySource(const ArkUI_UIInputEvent *event)
{
    CheckSupportedScenarioAndResetEventStatus(S_ALL_C_KEY_EVENT, event);
    if (!event) {
        RETURN_RET_WITH_STATUS_CHECK(static_cast<ArkUI_KeySourceType>(-1), ARKUI_ERROR_CODE_PARAM_INVALID);
    }
    const auto* keyEvent = reinterpret_cast<ArkUIKeyEvent*>(event->inputEvent);
    if (!keyEvent) {
        RETURN_RET_WITH_STATUS_CHECK(static_cast<ArkUI_KeySourceType>(-1), ARKUI_ERROR_CODE_PARAM_INVALID);
    }
    auto result = static_cast<ArkUI_KeySourceType>(keyEvent->keySource);
    RETURN_RET_WITH_STATUS_CHECK(result, ARKUI_ERROR_CODE_NO_ERROR);
}

void OH_ArkUI_KeyEvent_StopPropagation(const ArkUI_UIInputEvent *event, bool stopPropagation)
{
    CheckSupportedScenarioAndResetEventStatus(S_ALL_C_KEY_EVENT, event);
    if (!event) {
        RETURN_WITH_STATUS_CHECK(ARKUI_ERROR_CODE_PARAM_INVALID);
    }
    auto* keyEvent = reinterpret_cast<ArkUIKeyEvent*>(event->inputEvent);
    if (!keyEvent) {
        RETURN_WITH_STATUS_CHECK(ARKUI_ERROR_CODE_PARAM_INVALID);
    }
    keyEvent->stopPropagation = stopPropagation;
    RETURN_WITH_STATUS_CHECK(ARKUI_ERROR_CODE_NO_ERROR);
}

ArkUI_KeyIntension OH_ArkUI_KeyEvent_GetKeyIntensionCode(const ArkUI_UIInputEvent *event)
{
    CheckSupportedScenarioAndResetEventStatus(S_ALL_C_KEY_EVENT, event);
    if (!event) {
        RETURN_RET_WITH_STATUS_CHECK(static_cast<ArkUI_KeyIntension>(-1), ARKUI_ERROR_CODE_PARAM_INVALID);
    }
    const auto* keyEvent = reinterpret_cast<ArkUIKeyEvent*>(event->inputEvent);
    if (!keyEvent) {
        RETURN_RET_WITH_STATUS_CHECK(static_cast<ArkUI_KeyIntension>(-1), ARKUI_ERROR_CODE_PARAM_INVALID);
    }
    auto result = static_cast<ArkUI_KeyIntension>(keyEvent->intentionCode);
    RETURN_RET_WITH_STATUS_CHECK(result, ARKUI_ERROR_CODE_NO_ERROR);
}

uint32_t OH_ArkUI_KeyEvent_GetUnicode(const ArkUI_UIInputEvent *event)
{
    CheckSupportedScenarioAndResetEventStatus(S_ALL_C_KEY_EVENT, event);
    if (!event) {
        RETURN_RET_WITH_STATUS_CHECK(0, ARKUI_ERROR_CODE_PARAM_INVALID);
    }
    const auto* keyEvent = reinterpret_cast<ArkUIKeyEvent*>(event->inputEvent);
    if (!keyEvent) {
        RETURN_RET_WITH_STATUS_CHECK(0, ARKUI_ERROR_CODE_PARAM_INVALID);
    }
    auto result = static_cast<uint32_t>(keyEvent->unicode);
    RETURN_RET_WITH_STATUS_CHECK(result, ARKUI_ERROR_CODE_NO_ERROR);
}

void OH_ArkUI_KeyEvent_SetConsumed(const ArkUI_UIInputEvent *event, bool isConsumed)
{
    CheckSupportedScenarioAndResetEventStatus(S_NODE_ON_KEY_EVENT, event);
    if (!event) {
        RETURN_WITH_STATUS_CHECK(ARKUI_ERROR_CODE_PARAM_INVALID);
    }
    auto* keyEvent = reinterpret_cast<ArkUIKeyEvent*>(event->inputEvent);
    if (!keyEvent) {
        RETURN_WITH_STATUS_CHECK(ARKUI_ERROR_CODE_PARAM_INVALID);
    }
    keyEvent->isConsumed = isConsumed;
    RETURN_WITH_STATUS_CHECK(ARKUI_ERROR_CODE_NO_ERROR);
}

void OH_ArkUI_KeyEvent_Dispatch(ArkUI_NodeHandle node, const ArkUI_UIInputEvent* event)
{
    CheckSupportedScenarioAndResetEventStatus(S_ALL_C_KEY_EVENT, event);
    if (!node || !event) {
        RETURN_WITH_STATUS_CHECK(ARKUI_ERROR_CODE_PARAM_INVALID);
    }
    auto* keyEvent = reinterpret_cast<ArkUIKeyEvent*>(event->inputEvent);
    if (!keyEvent) {
        RETURN_WITH_STATUS_CHECK(ARKUI_ERROR_CODE_PARAM_INVALID);
    }
    auto fullImpl = OHOS::Ace::NodeModel::GetFullImpl();
    fullImpl->getNodeModifiers()->getCommonModifier()->dispatchKeyEvent(node->uiNodeHandle, keyEvent);
    RETURN_WITH_STATUS_CHECK(ARKUI_ERROR_CODE_NO_ERROR);
}

ArkUI_ErrorCode OH_ArkUI_KeyEvent_IsNumLockOn(const ArkUI_UIInputEvent* event, bool* state)
{
    CheckSupportedScenarioAndResetEventStatus(S_ALL_C_KEY_EVENT, event);
    if (!event || !state) {
        RETURN_RET_WITH_STATUS_CHECK(ARKUI_ERROR_CODE_PARAM_INVALID, ARKUI_ERROR_CODE_PARAM_INVALID);
    }
    const auto* keyEvent = reinterpret_cast<ArkUIKeyEvent*>(event->inputEvent);
    if (!keyEvent) {
        RETURN_RET_WITH_STATUS_CHECK(ARKUI_ERROR_CODE_PARAM_INVALID, ARKUI_ERROR_CODE_PARAM_INVALID);
    }
    *state = keyEvent->isNumLockOn;
    RETURN_RET_WITH_STATUS_CHECK(ARKUI_ERROR_CODE_NO_ERROR, ARKUI_ERROR_CODE_NO_ERROR);
}

ArkUI_ErrorCode OH_ArkUI_KeyEvent_IsCapsLockOn(const ArkUI_UIInputEvent* event, bool* state)
{
    CheckSupportedScenarioAndResetEventStatus(S_ALL_C_KEY_EVENT, event);
    if (!event || !state) {
        RETURN_RET_WITH_STATUS_CHECK(ARKUI_ERROR_CODE_PARAM_INVALID, ARKUI_ERROR_CODE_PARAM_INVALID);
    }
    const auto* keyEvent = reinterpret_cast<ArkUIKeyEvent*>(event->inputEvent);
    if (!keyEvent) {
        RETURN_RET_WITH_STATUS_CHECK(ARKUI_ERROR_CODE_PARAM_INVALID, ARKUI_ERROR_CODE_PARAM_INVALID);
    }
    *state = keyEvent->isCapsLockOn;
    RETURN_RET_WITH_STATUS_CHECK(ARKUI_ERROR_CODE_NO_ERROR, ARKUI_ERROR_CODE_NO_ERROR);
}

ArkUI_ErrorCode OH_ArkUI_KeyEvent_IsScrollLockOn(const ArkUI_UIInputEvent* event, bool* state)
{
    CheckSupportedScenarioAndResetEventStatus(S_ALL_C_KEY_EVENT, event);
    if (!event || !state) {
        RETURN_RET_WITH_STATUS_CHECK(ARKUI_ERROR_CODE_PARAM_INVALID, ARKUI_ERROR_CODE_PARAM_INVALID);
    }
    const auto* keyEvent = reinterpret_cast<ArkUIKeyEvent*>(event->inputEvent);
    if (!keyEvent) {
        RETURN_RET_WITH_STATUS_CHECK(ARKUI_ERROR_CODE_PARAM_INVALID, ARKUI_ERROR_CODE_PARAM_INVALID);
    }
    *state = keyEvent->isScrollLockOn;
    RETURN_RET_WITH_STATUS_CHECK(ARKUI_ERROR_CODE_NO_ERROR, ARKUI_ERROR_CODE_NO_ERROR);
}
#ifdef __cplusplus
};
#endif