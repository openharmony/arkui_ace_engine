/*
 * Copyright (c) 2021 Huawei Device Co., Ltd.
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
 * @addtogroup ACE
 * @{
 *
 * @brief Provides functions to set and obtain data and callbacks of xcomponent.
 *
 * @since 7
 * @version 1.0
 */

/**
 * @file native_interface_xcomponent.h
 *
 * @brief Declares APIs to get data from native xcomponent.
 *
 * @since 7
 * @version 1.0
 */

#ifndef _NATIVE_INTERFACE_XCOMPONENT_H_
#define _NATIVE_INTERFACE_XCOMPONENT_H_

#define NATIVE_XCOMPONENT_OBJ ("__NATIVE_XCOMPONENT_OBJ__")
#define XCOMPONENT_ID_LEN_MAX (128)

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Enumerates the returned value type.
 *
 * @since 7
 * @version 1.0
 */
enum {
    /* Success result */
    XCOMPONENT_RESULT_SUCCESS = 0,
    /* Failed result */
    XCOMPONENT_RESULT_FAILED = -1,
    /* Invalid parameters */
    XCOMPONENT_RESULT_BAD_PARAMETER = -2,
};

enum TouchInfoType {
    DOWN = 0,
    UP,
    MOVE,
    CANCEL,
    UNKNOWN,
};

struct TouchInfo {
    // Point ID of contact between the finger and the screen.
    int32_t id;
    // Horizontal distance of the touch point relative to the upper left corner of screen.
    float x;
    // Vertical distance of the touch point relative to the upper left corner of screen.
    float y;
    // Touch type of the touch event.
    TouchInfoType type;
    // Contacted surface size of encircling the user and the touch screen.
    double size;
    // Pressure of finger squeezing the touch screen.
    float force;
    // Device Id.
    int64_t deviceId;
    // Timestamp of the touch event.
    long long timeStamp;
};

/**
 * @brief Defines the <b>NativeXComponent</b> object, which is usually accessed via pointers.
 *
 * @since 7
 * @version 1.0
 */
typedef struct NativeXComponent NativeXComponent;

/**
 * @brief Defines the <b>NativeXComponentCallback</b> struct, which holding the surface lifecycle callbacks.
 *
 * @since 7
 * @version 1.0
 */
typedef struct NativeXComponentCallback {
    /* Called when the native surface is created or recreated. */
    void (*OnSurfaceCreated)(NativeXComponent* component, void* window);
    /* Called when the native surface is changed. */
    void (*OnSurfaceChanged)(NativeXComponent* component, void* window);
    /* Called when the native surface is destroyed. */
    void (*OnSurfaceDestroyed)(NativeXComponent* component, void* window);
    /* Called when touch event is triggered. */
    void (*DispatchTouchEvent)(NativeXComponent* component, void* window);
} NativeXComponentCallback;

/**
 * @brief Obtains the id of the xcomponent.
 *
 * @param component Indicates the pointer to this <b>NativeXComponent</b> instance.
 * @param id Indicates the char buffer to keep the ID of the xcomponent.
 *        Notice that a null-terminator will be append to the char buffer, so the size of the
 *        char buffer should be at least as large as the size of the real id length plus 1.
 *        The size of the char buffer is recommend to be [XCOMPONENT_ID_LEN_MAX + 1]
 * @param size is an in-out param.
 *        [in] Indicates the length of the id char buffer (including null-terminator).
 *             The referenced value of 'size' should be in the range (0, XCOMPONENT_ID_LEN_MAX + 1]
 *        [out] Receives the length of the id (not include null-terminator).
 * @return Returns the execution result.
 * @since 7
 * @version 1.0
 */
int32_t OH_NativeXComponent_GetXComponentId(NativeXComponent* component, char* id, uint64_t* size);

/**
 * @brief Obtains the native window handler.
 *
 * @param component Indicates the pointer to this <b>NativeXComponent</b> instance.
 * @param window Indicates the pointer to keep the native window handler.
 * @return Returns the execution result.
 * @since 7
 * @version 1.0
 */
int32_t OH_NativeXComponent_GetNativeWindow(NativeXComponent* component, void** window);

/**
 * @brief Obtains the size of the xcomponent.
 *
 * @param component Indicates the pointer to this <b>NativeXComponent</b> instance.
 * @param window Indicates the native window handler.
 * @param width Indicates pointer to the width of the xcomponent.
 * @param height Indicates pointer to the height of the xcomponent.
 * @return Returns the execution result.
 * @since 7
 * @version 1.0
 */
int32_t OH_NativeXComponent_GetXComponentSize(NativeXComponent* component, const void* window,
                                              uint64_t* width, uint64_t* height);

/**
 * @brief Obtains the offset of the xcomponent.
 *
 * @param component Indicates the pointer to this <b>NativeXComponent</b> instance.
 * @param window Indicates the native window handler.
 * @param x Indicates pointer to the horizontal coordinate of xcomponent relative to upper left corner of screen.
 * @param y Indicates pointer to the vertical coordinate of xcomponent relative to upper left corner of screen.
 * @return Returns the execution result.
 * @since 7
 * @version 1.0
 */
int32_t OH_NativeXComponent_GetXComponentOffset(NativeXComponent* component, const void* window, double* x, double* y);

/**
 * @brief Obtains the information of touch event.
 *
 * @param component Indicates the pointer to this <b>NativeXComponent</b> instance.
 * @param window Indicates the native window handler.
 * @param touchInfo Indicates pointer to the current touch information.
 * @return Returns the execution result.
 * @since 7
 * @version 1.0
 */
int32_t OH_NativeXComponent_GetTouchInfo(NativeXComponent* component, const void* window, TouchInfo* touchInfo);

/**
 * @brief Set the callback to the xcomponent.
 *
 * @param component Indicates the pointer to this <b>NativeXComponent</b> instance.
 * @param callback Indicates the callbacks of the native surface lifecycle.
 * @return Returns the execution result.
 * @since 7
 * @version 1.0
 */
int32_t OH_NativeXComponent_RegisterCallback(NativeXComponent* component, NativeXComponentCallback* callback);

#ifdef __cplusplus
};
#endif
#endif // _NATIVE_INTERFACE_XCOMPONENT_H_
