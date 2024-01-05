/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#pragma once

#ifdef __cplusplus
extern "C" {
#endif

typedef int ArkUI_Bool;
typedef int ArkUI_Int32;
typedef unsigned int ArkUI_Uint32;
typedef long long ArkUI_Int64;
typedef float ArkUI_Float32;
typedef double ArkUI_Float64;
typedef const char* ArkUI_CharPtr;

typedef void* ArkUINodeHandle;
typedef void* ArkUICanvasHandle;
typedef void* ArkUIPaintHandle;
typedef void* ArkUIFontHandle;
typedef void* ArkUIXComponentControllerHandle;

/**
 * ToolType
 */
typedef enum {
    /**
     * UNKNOWN
     */
    TOOL_TYPE_UNKNOWN = 0,

    /**
     * Finger
     */
    TOOL_TYPE_FINGER = 1,

    /**
     * Pen
     *
     */
    TOOL_TYPE_PEN = 2,
} TouchEventToolType;

/**
 * SourceType
 *
 */
typedef enum {
    SOURCE_TYPE_UNKNOWN = 0,
    /**
     * Touchscreen
     */
    SOURCE_TYPE_TOUCH_SCREEN = 1,

    /**
     * Stylus
     */
    SOURCE_TYPE_PEN = 2,

    /**
     * TouchPad
     */
    SOURCE_TYPE_TOUCH_PAD = 3
} ArkUISourceType;

typedef struct {
    /**
     * Pointer identifier
     */
    ArkUI_Int32 id;

    /**
     * Time stamp when touch is pressed
     */
    ArkUI_Int64 pressedTime;

    /**
     * X coordinate of the touch position on the screen
     *
     */
    ArkUI_Int32 screenX;

    /**
     * Y coordinate of the touch position on the screen
     *
     */
    ArkUI_Int32 screenY;

    /**
     * X coordinate of the touch position in the window
     *
     */
    ArkUI_Int32 windowX;

    /**
     * Y coordinate of the touch position in the window
     *
     */
    ArkUI_Int32 windowY;

    /**
     * X coordinate of the touch position in the node
     *
     */
    ArkUI_Int32 nodeX;

    /**
     * Y coordinate of the touch position in the node
     *
     */
    ArkUI_Int32 nodeY;

    /**
     * Pressure value. The value range is [0.0, 1.0]. The value 0.0 indicates that the pressure is not supported.
     *
     */
    ArkUI_Float64 pressure;

    /**
     * Width of the contact area when touch is pressed
     *
     */
    ArkUI_Int32 contactAreaWidth;

    /**
     * Height of the contact area when touch is pressed
     *
     */
    ArkUI_Int32 contactAreaHeight;

    /**
     * Angle relative to the YZ plane. The value range is [-90, 90]. A positive value indicates a rightward tilt.
     *
     */
    ArkUI_Float64 tiltX;

    /**
     * Angle relative to the XZ plane. The value range is [-90, 90]. A positive value indicates a downward tilt.
     */
    ArkUI_Float64 tiltY;

    /**
     * Center point X of the tool area
     */
    ArkUI_Int32 toolX;

    /**
     * Center point Y of the tool area
     *
     */
    ArkUI_Int32 toolY;

    /**
     * Width of the tool area
     *
     */
    ArkUI_Int32 toolWidth;

    /**
     * Height of the tool area
     *
     */
    ArkUI_Int32 toolHeight;

    /**
     * X coordinate of the input device
     *
     */
    ArkUI_Int32 rawX;

    /**
     * Y coordinate of the input device
     *
     */
    ArkUI_Int32 rawY;

    /**
     * Tool type
     *
     */
    TouchEventToolType toolType;
} ArkUITouchPoint;

typedef enum {
    ACTION_DOWN = 0,
    ACTION_UP,
    ACTION_MOVE,
    ACTION_CANCEL,
} ArkUITouchEventAction;

typedef struct {
    /**
     * Touch action
     */
    ArkUITouchEventAction action;
    /** Time stamp of the historical event. */
    ArkUI_Int64 timeStamp;
    /** touch point info of the historical event. */
    ArkUITouchPoint actionTouch;
    ArkUISourceType sourceType;
} ArkUIHistoricalTouchPoint;

typedef struct {
    /**
     * Touch action
     *
     */
    ArkUITouchEventAction action;

    /** Time stamp of the current event. */
    ArkUI_Int64 timeStamp;

    /**
     * curent action touch point info.
     */
    ArkUITouchPoint actionTouch;

    /**
     * @brief 返回此事件发生时所有屏幕接触点信息.
     *
     */
    ArkUI_Int32 (*getTouches)(ArkUITouchPoint** points);

    /**
     * @brief 返回此事件中的历史点信息。这些是在此事件和上一个事件之间发生的运动.
     *
     */
    ArkUI_Int32 (*getHistoricalPoints)(ArkUIHistoricalTouchPoint** historicalPoints);

    ArkUISourceType sourceType;

    /**
     * @brief 阻止事件进一步向父节点冒泡处理.
     *
     */
    ArkUI_Bool stopPropagation;

    /**
     * @brief 阻止当前节点的默认事件处理行为，允许事件进一步向上冒泡.
     *
     */
    ArkUI_Bool preventDefault;
} ArkUITouchEvent;

#ifdef __cplusplus
};
#endif
