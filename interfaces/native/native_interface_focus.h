/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

/**
 * @addtogroup ArkUI_NativeModule
 * @{
 *
 * @brief Provides focus capabilities of ArkUI on the native side, such as focus transfer operaions.
 *
 * @since 16
 */

/**
 * @file native_interface_focus.h
 *
 * @brief Declares the APIs used to control the focus system.
 *
 * @library libace_ndk.z.so
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @since 16
 */

#ifndef ARKUI_NATIVE_INTERFACE_FOCUS_H
#define ARKUI_NATIVE_INTERFACE_FOCUS_H

#include "napi/native_api.h"
#include "native_type.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Determines the priority of key event processing when component cannot handle the key event.
 *
 * @since 16
 */
typedef enum {
    /** Key events are used to move focus. */
    ARKUI_KEY_PROCESSING_MODE_FOCUS_NAVIGATION = 0,
    /** Key events bubble up to ancestors. */
    ARKUI_KEY_PROCESSING_MODE_FOCUS_ANCESTOR_EVENT,
} ArkUI_KeyProcessingMode;

/**
 * @brief Apply focus for a specific node.
 *
 * @param node The node.
 * @return The error code.
 *         {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *         {@link ARKUI_ERROR_CODE_FOCUS_NON_FOCUSABLE} if the node is not focusable.
 *         {@link ARKUI_ERROR_CODE_FOCUS_NON_FOCUSABLE_ANCESTOR} if the node has unfocusable ancestor.
 *         {@link ARKUI_ERROR_CODE_FOCUS_NON_EXISTENT} if the node is not exists.
 * @since 16
 */
ArkUI_ErrorCode OH_ArkUI_FocusRequest(ArkUI_NodeHandle node);

/**
 * @brief Clear current focus to root scope.
 *
 * @param uiContext Indicates the pointer to a UI instance.
 * @since 16
 */
void OH_ArkUI_FocusClear(ArkUI_ContextHandle uiContext);

/**
 * @brief Set the focus active state in current window, the focus node would show its focus box.
 *
 * @param uiContext Indicates the pointer to a UI instance.
 * @param isActive Set the state to be active or inactive.
 * @param isAutoInactive When touch event or mouse-pressed event triggerd,
 *                    "true" indicates to set state to inactive,
 *                    "false" indicates to maintain the state until relative API is called.
 * @since 16
 */
void OH_ArkUI_FocusActivate(ArkUI_ContextHandle uiContext, bool isActive, bool isAutoInactive);

/**
 * @brief Set the focus transfer behaviour when current focus view changes.
 *
 * @param uiContext Indicates the pointer to a UI instance.
 * @param autoTransfer Indicates whether to transfer focus when focus view show.
 * @since 16
 */
void OH_ArkUI_FocusSetAutoTransfer(ArkUI_ContextHandle uiContext, bool autoTransfer);

/**
 * @brief Set the priority of key event processing when component cannot handle the key event.
 *
 * @param uiContext Indicates the pointer to a UI instance.
 * @param mode Indicates the key processing mode.
 * @since 16
 */
void OH_ArkUI_FocusSetKeyProcessingMode(ArkUI_ContextHandle uiContext, ArkUI_KeyProcessingMode mode);

#ifdef __cplusplus
};
#endif

#endif // ARKUI_NATIVE_INTERFACE_FOCUS_H