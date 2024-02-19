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
 * @brief Provides UI capabilities of ArkUI on the native side, such as UI
 * component creation and destruction, tree node operations, attribute setting,
 * and event listening.
 *
 * @since 12
 */

/**
 * @file native_event.h
 *
 * @brief Provides the event type definitions of ArkUI on the native side.
 *
 * @library libace_ndk.z.so
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @since 12
 */

#ifndef ARKUI_NATIVE_EVENT
#define ARKUI_NATIVE_EVENT

#include <stdbool.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Enumerates the tool types of the touch event.
 *
 * @since 12
 */
typedef enum {
    /** Unknown tool type. */
    NODE_TOOL_TYPE_UNKNOWN = -1,

    /** Finger. */
    NODE_TOOL_TYPE_FINGER = 0,

    /** Stylus. */
    NODE_TOOL_TYPE_STYLUS = 1,
} ArkUI_NodeToolType;

/**
 * @brief Enumerates the source types of the touch event.
 *
 * @since 12
 */
typedef enum {
    /** Unknown source type. */
    NODE_SOURCE_TYPE_UNKNOWN = -1,
    /** Touchscreen. */
    NODE_SOURCE_TYPE_TOUCH_SCREEN = 0,
    /** Stylus. */
    NODE_SOURCE_TYPE_STYLUS = 1,
    /** Touchpad. */
    NODE_SOURCE_TYPE_TOUCHPAD = 2,
} ArkUI_NodeSourceType;

/**
 * @brief Defines the data structure of the touch point information of the
 * touch event.
 *
 * @since 12
 */
typedef struct {
    /** ID of the touch event. */
    int32_t id;

    /** Timestamp when a finger is pressed, in μs. */
    int64_t pressedTime;

    /** X coordinate of the touch point on the screen. */
    int32_t screenX;

    /** Y coordinate of the touch point on the screen. */
    int32_t screenY;

    /** X coordinate of the touch point in the window. */
    int32_t windowX;

    /** Y coordinate of the touch point in the window. */
    int32_t windowY;

    /** X coordinate of the touch point in the component that triggers the event. */
    int32_t nodeX;

    /** Y coordinate of the touch point in the component that triggers the event. */
    int32_t nodeY;

    /** Pressure value. The value range is [0.0, 1.0]. The value 0.0 indicates
        that the pressure is not supported. */
    double pressure;

    /** Width of the touch area. */
    int32_t contactAreaWidth;

    /** Height of the touch area. */
    int32_t contactAreaHeight;

    /** Angle relative to the YZ plane. The value range is [-90, 90]. A positive value indicates a rightward tilt. */
    double tiltX;

    /** Angle relative to the XZ plane. The value range is [-90, 90]. A positive value indicates a downward tilt. */
    double tiltY;

    /** X coordinate of the center point of the tool area. */
    int32_t toolX;

    /** Y coordinate of the center point of the tool area. */
    int32_t toolY;

    /** Width of the tool area. */
    int32_t toolWidth;

    /** Height of the tool area. */
    int32_t toolHeight;

    /** X coordinate of the input device. */
    int32_t rawX;

    /** Y coordinate of the input device. */
    int32_t rawY;

    /** Tool type. */
    ArkUI_NodeToolType toolType;
} ArkUI_NodeTouchPoint;

/**
 * @brief Enumerates touch event types.
 *
 * @since 12
 */
typedef enum {
    /** Cancellation of touch. */
    NODE_ACTION_CANCEL = 0,
    /** Pressing of a touch point. */
    NODE_ACTION_DOWN = 1,
    /** Moving of a touch point. */
    NODE_ACTION_MOVE = 2,
    /** Lifting of a touch point. */
    NODE_ACTION_UP = 3,
} ArkUI_NodeTouchEventAction;

/**
 * @brief Defines the data structure of the historical point information.
 *
 * @since 12
 */
typedef struct {
    /** Touch event type. */
    ArkUI_NodeTouchEventAction action;
    /** Timestamp of the historical touch event, in μs. */
    int64_t timeStamp;
    /** Source type of the historical touch event. */
    ArkUI_NodeTouchPoint actionTouch;
    /** Source type of the historical touch event. */
    ArkUI_NodeSourceType sourceType;
} ArkUI_NodeHistoricalTouchPoint;

/**
 * @brief Defines the data structure of the touch event.
 *
 * @since 12
 */
typedef struct {
    /** Touch event type. */
    ArkUI_NodeTouchEventAction action;

    /** Timestamp of the touch event, in μs. */
    int64_t timeStamp;

    /** Touch point information of the touch event. */
    ArkUI_NodeTouchPoint actionTouch;

    /**
     * @brief Returns information about all touch points when this event occurs.
     * @param points Indicates the pointer to the object that receives data.
     * @return Returns the number of elements in the touch point information array.
     * @note
     * When this function is called, ArkUI creates a heap memory object of the touch point information array and
     * returns the pointer to the pointer. You need to call <b>delete[]</b> to manually free the memory when the
     * object is not in use.
     */
    int32_t (*getTouches)(ArkUI_NodeTouchPoint** points);

    /**
     * @brief Returns the historical point information of this event, which covers actions that occur between
     * this event and the previous event.
     * @param historicalPoints Indicates the pointer to the object that receives data.
     * @return Returns the number of elements in the historical touch point information array.
     * @note
     * When this function is called, ArkUI creates a heap memory object of the historical touch point information array
     * and returns the pointer to the pointer. You need to call <b>delete[]</b> to manually free the memory
     * when the object is not in use.
     */
    int32_t (*getHistoricalPoints)(ArkUI_NodeHistoricalTouchPoint** historicalPoints);

    /** Source type of the touch event. */
    ArkUI_NodeSourceType sourceType;

    /** Whether to prevent propagation of the event to the parent node. */
    bool stopPropagation;

    /** Whether to prevent the default event processing behavior of the current node and allow propagation of the event. */
    bool preventDefault;
} ArkUI_NodeTouchEvent;

#ifdef __cplusplus
};
#endif

#endif // ARKUI_NATIVE_EVENT
/** @} */
