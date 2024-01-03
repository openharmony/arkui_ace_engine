/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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
 * @addtogroup OH_ArkUI Native Node
 * @{
 *
 * @brief 提供ArkUI在Native侧的组件类型定义。
 *
 * @since 11
 * @version 1.0
 */

/**
 * @file node_types.h
 *
 * @brief 提供ArkUI在Native侧的类型定义集合。
 *
 * @since 11
 * @version 1.0
 */

#ifndef _ARKUI_NATIVE_NODE_BASIC_TYPES_
#define _ARKUI_NATIVE_NODE_BASIC_TYPES_

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief 提供<b>ArkUI_NodeHandle</b>组件实例对象指针定义.
 *
 * @since 11
 * @version 1.0
 */
typedef struct ArkUI_Node* ArkUI_NodeHandle;

typedef int ArkUI_Bool;
typedef int ArkUI_Int32;
typedef unsigned int ArkUI_Uint32;
typedef long long ArkUI_Int64;
typedef float ArkUI_Float32;
typedef double ArkUI_Float64;

union ArkUI_NodeEventCallbackArg {
    ArkUI_Int32 i32;
    ArkUI_Uint32 u32;
    ArkUI_Float32 f32;
};

/**
 * ToolType
 */
typedef enum {
    /**
     * UNKNOWN
     */
    NODE_TOOL_TYPE_UNKNOWN = 0,

    /**
     * Finger
     */
    NODE_TOOL_TYPE_FINGER = 1,

    /**
     * Pen
     *
     */
    NODE_TOOL_TYPE_PEN = 2,
} ArkUI_NodeToolType;

/**
 * SourceType
 *
 */
typedef enum {
    NODE_SOURCE_TYPE_UNKNOWN = 0,
    /**
     * Touchscreen
     *
     */
    NODE_SOURCE_TYPE_TOUCH_SCREEN = 1,

    /**
     * Stylus
     */
    NODE_SOURCE_TYPE_PEN = 2,

    /**
     * TouchPad
     *
     */
    NODE_SOURCE_TYPE_TOUCH_PAD = 3
} ArkUI_NodeSourceType;

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
    ArkUI_NodeToolType toolType;
} ArkUI_NodeTouchPoint;

typedef enum {
    NODE_ACTION_DOWN = 0,
    NODE_ACTION_UP,
    NODE_ACTION_MOVE,
    NODE_ACTION_CANCEL,
} ArkUI_NodeTouchEventAction;

typedef struct {
    /**
     * Touch action
     */
    ArkUI_NodeTouchEventAction action;
    /** Time stamp of the historical event. */
    ArkUI_Int64 timeStamp;
    /** touch point info of the historical event. */
    ArkUI_NodeTouchPoint actionTouch;
    ArkUI_NodeSourceType sourceType;
} ArkUI_NodeHistoricalTouchPoint;

typedef struct {
    /**
     * Touch action
     *
     */
    ArkUI_NodeTouchEventAction action;

    /** Time stamp of the current event. */
    ArkUI_Int64 timeStamp;

    /**
     * curent action touch point info.
     */
    ArkUI_NodeTouchPoint actionTouch;

    /**
     * @brief 返回此事件发生时所有屏幕接触点信息.
     * @param points 用来接受数据的指针对象.
     * @return 屏幕接触点数量.
     */
    ArkUI_Int32 (*getTouches)(ArkUI_NodeTouchPoint** points);

    /**
     * @brief 返回此事件中的历史点信息。这些是在此事件和上一个事件之间发生的运动.
     * @param points 用来接受数据的指针对象.
     * @return 历史点数量.
     */
    ArkUI_Int32 (*getHistoricalPoints)(ArkUI_NodeHistoricalTouchPoint** historicalPoints);

    ArkUI_NodeSourceType sourceType;

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
} ArkUI_NodeTouchEvent;

#ifdef __cplusplus
};
#endif

#endif // _ARKUI_NATIVE_NODE_BASIC_TYPES_
