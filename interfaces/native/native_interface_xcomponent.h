/*
 * Copyright (c) 2021-2022 Huawei Device Co., Ltd.
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
 * @addtogroup OH_NativeXComponent Native XComponent
 * @{
 *
 * @brief Describes the surface and touch event held by the ArkUI XComponent, which can be used for the EGL/OpenGL ES\n
 *        and media data input and displayed on the ArkUI XComponent.
 *
 * @since 8
 * @version 1.0
 */

/**
 * @file native_interface_xcomponent.h
 *
 * @brief Declares APIs for accessing a Native XComponent.
 *
 * @since 8
 * @version 1.0
 */

#ifndef _NATIVE_INTERFACE_XCOMPONENT_H_
#define _NATIVE_INTERFACE_XCOMPONENT_H_

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Enumerates the API access states.
 *
 * @since 8
 * @version 1.0
 */
enum {
    /** Successful. */
    OH_NATIVEXCOMPONENT_RESULT_SUCCESS = 0,
    /** Failed. */
    OH_NATIVEXCOMPONENT_RESULT_FAILED = -1,
    /** Invalid parameters. */
    OH_NATIVEXCOMPONENT_RESULT_BAD_PARAMETER = -2,
};

enum OH_NativeXComponent_TouchEventType {
    /** Trigger a touch event when a finger is pressed. */
    OH_NATIVEXCOMPONENT_DOWN = 0,
    /** Trigger a touch event when a finger is lifted. */
    OH_NATIVEXCOMPONENT_UP,
    /** Trigger a touch event when a finger moves on the screen in pressed state. */
    OH_NATIVEXCOMPONENT_MOVE,
    /** Trigger an event when a touch event is canceled. */
    OH_NATIVEXCOMPONENT_CANCEL,
    /** Invalid touch type. */
    OH_NATIVEXCOMPONENT_UNKNOWN,
};

enum OH_NativeXComponent_MouseEventAction {
    OH_NATIVEXCOMPONENT_NONE = 0,
    OH_NATIVEXCOMPONENT_PRESS,
    OH_NATIVEXCOMPONENT_RELEASE,
    OH_NATIVEXCOMPONENT_HOVER,
    OH_NATIVEXCOMPONENT_HOVER_ENTER,
    OH_NATIVEXCOMPONENT_HOVER_MOVE,
    OH_NATIVEXCOMPONENT_HOVER_EXIT,
};

enum OH_NativeXComponent_MouseEventButton {
    OH_NATIVEXCOMPONENT_NONE_BUTTON = 0,
    OH_NATIVEXCOMPONENT_LEFT_BUTTON = 1,
    OH_NATIVEXCOMPONENT_RIGHT_BUTTON = 2,
    OH_NATIVEXCOMPONENT_MIDDLE_BUTTON = 4,
    OH_NATIVEXCOMPONENT_BACK_BUTTON = 8,
    OH_NATIVEXCOMPONENT_FORWARD_BUTTON = 16,
};

enum OH_NativeXComponent_SourceType : int32_t  {
    OH_NATIVEXCOMPONENT_SOURCETYPE_NONE = 0,
    OH_NATIVEXCOMPONENT_SOURCETYPE_MOUSE = 1,
    OH_NATIVEXCOMPONENT_SOURCETYPE_TOUCH = 2,
    OH_NATIVEXCOMPONENT_SOURCETYPE_TOUCH_PAD = 3,
    OH_NATIVEXCOMPONENT_SOURCETYPE_KEYBOARD = 4,
};

#define OH_NATIVE_XCOMPONENT_OBJ ("__NATIVE_XCOMPONENT_OBJ__")
const uint32_t OH_XCOMPONENT_ID_LEN_MAX = 128;
const uint32_t OH_MAX_TOUCH_POINTS_NUMBER = 10;

struct OH_NativeXComponent_TouchPoint {
    /** Unique identifier of a finger. */
    int32_t id = 0;
    /** X coordinate of the touch point relative to the left edge of the screen. */
    float screenX = 0.0;
    /** Y coordinate of the touch point relative to the upper edge of the screen. */
    float screenY = 0.0;
    /** X coordinate of the touch point relative to the left edge of the element to touch. */
    float x = 0.0;
    /** Y coordinate of the touch point relative to the upper edge of the element to touch. */
    float y = 0.0;
    /** Touch type of the touch event. */
    OH_NativeXComponent_TouchEventType type = OH_NativeXComponent_TouchEventType::OH_NATIVEXCOMPONENT_UNKNOWN;
    /** Contact area between the finger pad and the screen. */
    double size = 0.0;
    /** Pressure of the current touch event. */
    float force = 0.0;
    /** Timestamp of the current touch event. */
    int64_t timeStamp = 0;
    /** Whether the current point is pressed. */
    bool isPressed = false;
};

// Represents the touch point information.
struct OH_NativeXComponent_TouchEvent {
    /** Unique identifier of a finger. */
    int32_t id = 0;
    /** X coordinate of the touch point relative to the left edge of the screen. */
    float screenX = 0.0;
    /** Y coordinate of the touch point relative to the upper edge of the screen. */
    float screenY = 0.0;
    /** X coordinate of the touch point relative to the left edge of the element to touch. */
    float x = 0.0;
    /** Y coordinate of the touch point relative to the upper edge of the element to touch. */
    float y = 0.0;
    /** Touch type of the touch event. */
    OH_NativeXComponent_TouchEventType type = OH_NativeXComponent_TouchEventType::OH_NATIVEXCOMPONENT_UNKNOWN;
    /** Contact area between the finger pad and the screen. */
    double size = 0.0;
    /** Pressure of the current touch event. */
    float force = 0.0;
    /** ID of the device where the current touch event is generated. */
    int64_t deviceId = 0;
    /** Timestamp of the current touch event. */
    int64_t timeStamp = 0;
    /** Array of the current touch points. */
    OH_NativeXComponent_TouchPoint touchPoints[OH_MAX_TOUCH_POINTS_NUMBER];
    /** Number of current touch points. */
    uint32_t numPoints = 0;
};

// Represents the mouse point information.
struct OH_NativeXComponent_MouseEvent {
    /** X coordinate of the mouse point relative to the left edge of the element to mouse. */
    float x = 0.0;
    /** Y coordinate of the mouse point relative to the upper edge of the element to mouse. */
    float y = 0.0;
    float z = 0.0;
    float deltaX = 0.0f;
    float deltaY = 0.0f;
    float deltaZ = 0.0f;
    float scrollX = 0.0f;
    float scrollY = 0.0f;
    float scrollZ = 0.0f;
    /** X coordinate of the mouse point relative to the left edge of the screen. */
    float screenX = 0.0;
    /** Y coordinate of the mouse point relative to the upper edge of the screen. */
    float screenY = 0.0;
    OH_NativeXComponent_MouseEventAction action = OH_NativeXComponent_MouseEventAction::OH_NATIVEXCOMPONENT_NONE;
    OH_NativeXComponent_MouseEventButton button = OH_NativeXComponent_MouseEventButton::OH_NATIVEXCOMPONENT_NONE_BUTTON;
    int32_t pressedButtons = 0; // combined by MouseButtons
    int64_t time = 0;
    int64_t deviceId = 0;
    OH_NativeXComponent_SourceType sourceType = OH_NativeXComponent_SourceType::OH_NATIVEXCOMPONENT_SOURCETYPE_NONE;
};

/**
 * @brief Provides an encapsulated <b>OH_NativeXComponent</b> instance.
 *
 * @since 8
 * @version 1.0
 */
typedef struct OH_NativeXComponent OH_NativeXComponent;

/**
 * @brief Registers the surface lifecycle and touch event callbacks.
 *
 * @since 8
 * @version 1.0
 */
typedef struct OH_NativeXComponent_Callback {
    /** Called when the surface is created. */
    void (*OnSurfaceCreated)(OH_NativeXComponent* component, void* window);
    /**
     * Called when the surface is changed.\n
     * This API is defined but not implemented in OpenHarmony 3.1 Release. It will be available for use in\n
     * OpenHarmony 3.1 MR.
     */
    void (*OnSurfaceChanged)(OH_NativeXComponent* component, void* window);
    /** Called when the surface is destroyed. */
    void (*OnSurfaceDestroyed)(OH_NativeXComponent* component, void* window);
    /** Called when a touch event is triggered. */
    void (*DispatchTouchEvent)(OH_NativeXComponent* component, void* window);
    /** Called when a mouse event is triggered. */
    void (*DispatchMouseEvent)(OH_NativeXComponent* component, void* window);
} OH_NativeXComponent_Callback;

/**
 * @brief Obtains the ID of the ArkUI XComponent.
 *
 * @param component Indicates the pointer to this <b>OH_NativeXComponent</b> instance.
 * @param id Indicates the char buffer to keep the ID of this <b>OH_NativeXComponent</b> instance.\n
 *        Notice that a null-terminator will be appended to the char buffer, so the size of the\n
 *        char buffer should be at least as large as the size of the real id length plus 1.\n
 *        It is recommended that the size of the char buffer be [OH_XCOMPONENT_ID_LEN_MAX + 1].
 * @param size Indicates the pointer to the length of <b>id</b>, which you can set and receive.
 * @return Returns the status code of the execution.
 * @since 8
 * @version 1.0
 */
int32_t OH_NativeXComponent_GetXComponentId(OH_NativeXComponent* component, char* id, uint64_t* size);

/**
 * @brief Obtains the size of the surface held by the ArkUI XComponent.
 *
 * @param component Indicates the pointer to this <b>OH_NativeXComponent</b> instance.
 * @param window Indicates the native window handler.
 * @param width Indicates the pointer to the width of the current surface.
 * @param height Indicates the pointer to the height of the current surface.
 * @return Returns the status code of the execution.
 * @since 8
 * @version 1.0
 */
int32_t OH_NativeXComponent_GetXComponentSize(
    OH_NativeXComponent* component, const void* window, uint64_t* width, uint64_t* height);

/**
 * @brief Obtains the offset of the surface held by the ArkUI XComponent.
 *
 * @param component Indicates the pointer to this <b>OH_NativeXComponent</b> instance.
 * @param window Indicates the native window handler.
 * @param x Indicates the pointer to the x coordinate of the current surface.
 * @param y Indicates the pointer to the y coordinate of the current surface.
 * @return Returns the status code of the execution.
 * @since 8
 * @version 1.0
 */
int32_t OH_NativeXComponent_GetXComponentOffset(
    OH_NativeXComponent* component, const void* window, double* x, double* y);

/**
 * @brief Obtains the touch event dispatched by the ArkUI XComponent.
 *
 * @param component Indicates the pointer to this <b>OH_NativeXComponent</b> instance.
 * @param window Indicates the native window handler.
 * @param touchEvent Indicates the pointer to the current touch event.
 * @return Returns the status code of the execution.
 * @since 8
 * @version 1.0
 */
int32_t OH_NativeXComponent_GetTouchEvent(
    OH_NativeXComponent* component, const void* window, OH_NativeXComponent_TouchEvent* touchEvent);

/**
 * @brief Obtains the mouse event dispatched by the ArkUI XComponent.
 *
 * @param component Indicates the pointer to this <b>OH_NativeXComponent</b> instance.
 * @param window Indicates the native window handler.
 * @param mouseEvent Indicates the pointer to the current mouse event.
 * @return Returns the status code of the execution.
 * @since 8
 * @version 1.0
 */
int32_t OH_NativeXComponent_GetMouseEvent(
    OH_NativeXComponent* component, const void* window, OH_NativeXComponent_MouseEvent* mouseEvent);

/**
 * @brief Registers a callback for this <b>OH_NativeXComponent</b> instance.
 *
 * @param component Indicates the pointer to this <b>OH_NativeXComponent</b> instance.
 * @param callback Indicates the pointer to a surface lifecycle and touch event callback.
 * @return Returns the status code of the execution.
 * @since 8
 * @version 1.0
 */
int32_t OH_NativeXComponent_RegisterCallback(OH_NativeXComponent* component, OH_NativeXComponent_Callback* callback);

#ifdef __cplusplus
};
#endif
#endif // _NATIVE_INTERFACE_XCOMPONENT_H_
