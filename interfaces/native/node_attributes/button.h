/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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
 * @brief ArkUI Button Node type definitions on the native side.
 *
 * @since 12
 */

/**
 * @file button.h
 *
 * @brief Provides button node type definitions for <b>NativeNode</b> APIs.
 *
 * @library libace_ndk.z.so
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @kit ArkUI
 * @since 12
 */

#ifndef ARKUI_NATIVE_NODE_ATTRIBUTES_BUTTON_H
#define ARKUI_NATIVE_NODE_ATTRIBUTES_BUTTON_H

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Enumerates the button types.
 *
 * @since 12
 */
typedef enum {
    /**
     * Normal button (without rounded corners by default).
     * @since 12
     */
    ARKUI_BUTTON_TYPE_NORMAL = 0,
    /**
     * Capsule-type button (the round corner is half of the height by default).
     * @since 12
     */
    ARKUI_BUTTON_TYPE_CAPSULE,
    /**
     * Circle button.
     * @since 12
     */
    ARKUI_BUTTON_TYPE_CIRCLE,
    /**
     * Rounded rectangle button.
     * @since 19
     */
    ARKUI_BUTTON_ROUNDED_RECTANGLE = 8
} ArkUI_ButtonType;

#ifdef __cplusplus
}
#endif

#endif // ARKUI_NATIVE_NODE_ATTRIBUTES_BUTTON_H
/** @} */
