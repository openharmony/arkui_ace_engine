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
 * @brief ArkUI Checkbox Node type definitions on the native side.
 *
 * @since 12
 */

/**
 * @file checkbox.h
 *
 * @brief Provides checkbox node type definitions for <b>NativeNode</b> APIs.
 *
 * @library libace_ndk.z.so
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @kit ArkUI
 * @since 12
 */

#ifndef ARKUI_NATIVE_NODE_ATTRIBUTES_CHECKBOX_H
#define ARKUI_NATIVE_NODE_ATTRIBUTES_CHECKBOX_H

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Enumerates the shapes of the check box.
 *
 * @since 12
 */
typedef enum {
    /**
     * Circle.
     * @since 12
     */
    ArkUI_CHECKBOX_SHAPE_CIRCLE = 0,
    /**
     * Rounded square.
     * @since 12
     */
    ArkUI_CHECKBOX_SHAPE_ROUNDED_SQUARE,
} ArkUI_CheckboxShape;

#ifdef __cplusplus
}
#endif

#endif // ARKUI_NATIVE_NODE_ATTRIBUTES_CHECKBOX_H
/** @} */
