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
 * @brief Defines embedded component attribute and interface.
 *
 * @since 12
 */

/**
 * @file embedded_component.h
 *
 * @brief Defines embedded component attribute and interface.
 *
 * @library libace_ndk.z.so
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @kit ArkUI
 * @since 12
 */
#ifndef ARKUI_EMBEDDED_COMPONENT_H
#define ARKUI_EMBEDDED_COMPONENT_H

#ifdef __cplusplus
#include <cstdint>
#else
#include <stdint.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif
/**
 * @brief Declares the Ability base want.
 *
 * @since 20
 */
typedef struct AbilityBase_Want AbilityBase_Want;

/**
 * @brief Define the EmbeddedComponentOption for the EmbeddedComponent.
 *
 * @since 20
 */
typedef struct ArkUI_EmbeddedComponentOption ArkUI_EmbeddedComponentOption;

/**
 * @brief Creates an **EmbeddedComponent** option object.
 *
 * @return Pointer to the **EmbeddedComponent** option object.
 * @since 20
 */
ArkUI_EmbeddedComponentOption* OH_ArkUI_EmbeddedComponentOption_Create();

/**
 * @brief Disposes of an **EmbeddedComponent** option object.
 *
 * @param option Pointer to the target **EmbeddedComponent** option object.
 * @since 20
 */
void OH_ArkUI_EmbeddedComponentOption_Dispose(ArkUI_EmbeddedComponentOption* option);

/**
 * @brief Sets the {@link onError} callback for the **EmbeddedComponent** component. This callback is triggered when an
 * error occurs during the running of the **EmbeddedComponent** component.
 *
 * @param option Pointer to the **EmbeddedComponent** option object.
 * @param callback Callback function that will called when error occurs during the running of
 *     the **EmbeddedComponent** component
 * @since 20
 */
void OH_ArkUI_EmbeddedComponentOption_SetOnError(
    ArkUI_EmbeddedComponentOption* option, void (*callback)(int32_t code, const char* name, const char* message));

/**
 * @brief Sets the {@link onTerminated} callback for the **EmbeddedComponent** component. This callback is triggered
 * when the **EmbeddedComponent** component exits properly.
 *
 * @param option Pointer to the **EmbeddedComponent** option object.
 * @param callback Callback function that will called when the **EmbeddedComponent** component exits properly.
 * @since 20
 */
void OH_ArkUI_EmbeddedComponentOption_SetOnTerminated(
    ArkUI_EmbeddedComponentOption* option, void (*callback)(int32_t code, AbilityBase_Want* want));

#ifdef __cplusplus
}
#endif

#endif // ARKUI_EMBEDDED_COMPONENT_H
/** @} */
