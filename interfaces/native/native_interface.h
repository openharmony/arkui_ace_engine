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

/**
 * @addtogroup ArkUI_NativeModule
 * @{
 *
 * @brief Provides UI capabilities of ArkUI on the native side, such as UI component creation and destruction,
 * tree node operations, attribute setting, and event listening.
 *
 * @since 12
 */

/**
 * @file native_interface.h
 *
 * @brief Provides a unified entry for the native module APIs.
 *
 * @library libace_ndk.z.so
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @since 12
 */

#ifndef ARKUI_NATIVE_INTERFACE_H
#define ARKUI_NATIVE_INTERFACE_H

#include <stdint.h>

#include "native_type.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Defines the native API types.
 *
 * @since 12
 */
typedef enum {
    /** API related to UI components. For details, see the struct definition in <arkui/native_node.h>. */
    ARKUI_NATIVE_NODE,
    /** API related to dialog boxes. For details, see the struct definition in <arkui/native_dialog.h>. */
    ARKUI_NATIVE_DIALOG,
    /** API related to gestures. For details, see the struct definition in <arkui/native_gesture.h>. */
    ARKUI_NATIVE_GESTURE,
    /** API related to animations. For details, see the struct definition in <arkui/native_animate.h>.*/
    ARKUI_NATIVE_ANIMATE,
    /**
     * API related to supported multi thread UI components.
     * For details, see the struct definition in <arkui/native_node.h>.
     * @since 20
     */
    ARKUI_MULTI_THREAD_NATIVE_NODE,
} ArkUI_NativeAPIVariantKind;

/**
 * @brief Obtains the native API set of a specified type.
 *
 * @param type Indicates the type of the native API set provided by ArkUI, for example, <b>ARKUI_NATIVE_NODE</b>
 * and <b>ARKUI_NATIVE_GESTURE</b>.
 * @param sturctName Indicates the name of a native struct defined in the corresponding header file, for example,
 * <b>ArkUI_NativeNodeAPI_1</b> in <arkui/native_node.h>.
 * @return Returns the pointer to the abstract native API, which can be used after being converted into a specific type.
 * @code {.cpp}
 * #include<arkui/native_interface.h>
 * #include<arkui/native_node.h>
 * #include<arkui/native_gesture.h>
 *
 * auto* anyNativeAPI = OH_ArkUI_QueryModuleInterfaceByName(ARKUI_NATIVE_NODE, "ArkUI_NativeNodeAPI_1");
 * if (anyNativeAPI) {
 *     auto nativeNodeApi = reinterpret_cast<ArkUI_NativeNodeAPI_1*>(anyNativeAPI);
 * }
 * auto anyGestureAPI = OH_ArkUI_QueryModuleInterface(ARKUI_NATIVE_GESTURE, "ArkUI_NativeGestureAPI_1");
 * if (anyNativeAPI) {
 *     auto basicGestureApi = reinterpret_cast<ArkUI_NativeGestureAPI_1*>(anyGestureAPI);
 * }
 * @endcode
 *
 * @since 12
 */
void* OH_ArkUI_QueryModuleInterfaceByName(ArkUI_NativeAPIVariantKind type, const char* structName);

/**
 * @brief Obtains the macro function corresponding to a struct pointer based on the struct type.
 *
 * @code {.cpp}
 * #include<arkui/native_interface.h>
 * #include<arkui/native_node.h>
 *
 * ArkUI_NativeNodeAPI_1* nativeNodeApi = nullptr;
 * OH_ArkUI_GetModuleInterface(ARKUI_NATIVE_NODE, ArkUI_NativeNodeAPI_1, nativeNodeApi);
 * @endcode
 *
 * @since 12
 */
#define OH_ArkUI_GetModuleInterface(nativeAPIVariantKind, structType, structPtr)                     \
    do {                                                                                             \
        void* anyNativeAPI = OH_ArkUI_QueryModuleInterfaceByName(nativeAPIVariantKind, #structType); \
        if (anyNativeAPI) {                                                                          \
            structPtr = (structType*)(anyNativeAPI);                                                 \
        }                                                                                            \
    } while (0)


/**
 * @brief Retrieves the latest error message, which includes the error code, method name, and error cause.
 * When other interfaces return an error code, they save the corresponding error message,
 * and this interface can retrieve the currently stored error message.
 * The information returned by this interface may evolve with versions and is intended solely for
 * output to aid in analysis and troubleshooting. It should not be used for logical decisions.
 *
 * The returned string is a thread-local string created by the system. Different threads maintain
 * independent error messages, and other threads do not overwrite the current thread's result.
 * The pointer remains valid until the current thread records another error or exits. The caller must
 * not modify its content. If any editing is required, create a copy of the string content yourself.
 * No memory deallocation is required by the caller.
 *
 * @return Returns the most recent error message.
 * @since 26.0.0
 */
const char* OH_ArkUI_NativeModule_GetErrorMessage();

/**
 * @brief Defines the runtime check types for ArkUI C APIs.
 *
 * Each check type corresponds to a specific improper usage scenario of ArkUI C APIs,
 * such as cross-thread calls or accessing disposed nodes.
 * Use {@link OH_ArkUI_NativeModule_SetRuntimeCheckMode} to independently configure a runtime check mode
 * for each check type. The configured mode determines the behavior upon check failure.
 * For available modes, see {@link OH_ArkUI_NativeModule_RuntimeCheckMode}.
 *
 * @since 26.2.0
 */
typedef enum {
    /**
     * @brief Checks whether UI-thread-only C APIs are called from a non-UI thread.
     * Reserved in this release: the configuration is accepted but no detection point consumes it.
     *
     * @since 26.2.0
     */
    OH_ARKUI_NATIVEMODULE_CHECK_TYPE_UI_THREAD = 0,
    /**
     * @brief Checks whether the ArkUI_NodeHandle passed to a C API has already been disposed.
     *
     * @since 26.2.0
     */
    OH_ARKUI_NATIVEMODULE_CHECK_TYPE_NODE_DISPOSED = 1,
} OH_ArkUI_NativeModule_RuntimeCheckType;

/**
 * @brief Defines the runtime check modes for ArkUI C APIs.
 *
 * Each check type can be independently configured to use DISABLED, LOG, or CRASH.
 * For {@link OH_ARKUI_NATIVEMODULE_CHECK_TYPE_NODE_DISPOSED}, the default mode depends on the application's
 * build type: debug builds default to {@link OH_ARKUI_NATIVEMODULE_CHECK_MODE_CRASH}, and release builds
 * default to {@link OH_ARKUI_NATIVEMODULE_CHECK_MODE_DISABLED}.
 * {@link OH_ARKUI_NATIVEMODULE_CHECK_TYPE_UI_THREAD} is reserved in this release and defaults to
 * {@link OH_ARKUI_NATIVEMODULE_CHECK_MODE_DISABLED}.
 *
 * @since 26.2.0
 */
typedef enum {
    /**
     * @brief Disables the specified runtime check. The C API behavior is the same as before the check was introduced.
     *
     * @since 26.2.0
     */
    OH_ARKUI_NATIVEMODULE_CHECK_MODE_DISABLED = 0,
    /**
     * @brief Prints diagnostic logs, including check type, API name, cause, and native stack trace.
     * The checked API continues to run; its return value and side effects are not changed.
     *
     * @since 26.2.0
     */
    OH_ARKUI_NATIVEMODULE_CHECK_MODE_LOG = 1,
    /**
     * @brief Prints diagnostic logs and immediately terminates the application.
     *
     * @since 26.2.0
     */
    OH_ARKUI_NATIVEMODULE_CHECK_MODE_CRASH = 2,
} OH_ArkUI_NativeModule_RuntimeCheckMode;

/**
 * @brief Sets the process-level runtime check mode for ArkUI C APIs.
 *
 * This function configures the behavior of a specific runtime check type when misuse is detected.
 * The setting is process-level and remains in effect until the next successful call for the same check type.
 *
 * <b>Thread requirement:</b> This function must be called on the UI thread.
 * Calling it from any other thread immediately terminates the application without returning.
 * The thread check is performed before parameter validation and is independent of the configured modes.
 *
 * <b>Default behavior:</b> If this function is not called for a specific check type, its default mode applies.
 * For defaults and the reserved UI thread check, see {@link OH_ArkUI_NativeModule_RuntimeCheckMode}.
 *
 * @param checkType [in] Specifies the runtime check type to configure.
 *     The value is an enum value from {@link OH_ArkUI_NativeModule_RuntimeCheckType}.
 * @param mode [in] Specifies the runtime check mode.
 *     The value is an enum value from {@link OH_ArkUI_NativeModule_RuntimeCheckMode}.
 * @return Return value:
 *     <ul><li>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the setting is updated successfully.
 *     </li><li>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if checkType or mode is invalid.</li></ul>
 *     When an invalid parameter error is returned, the previous setting is retained.
 * @since 26.2.0
 */
ArkUI_ErrorCode OH_ArkUI_NativeModule_SetRuntimeCheckMode(
    OH_ArkUI_NativeModule_RuntimeCheckType checkType, OH_ArkUI_NativeModule_RuntimeCheckMode mode);
#ifdef __cplusplus
};
#endif

#endif // ARKUI_NATIVE_INTERFACE_H
/** @} */
