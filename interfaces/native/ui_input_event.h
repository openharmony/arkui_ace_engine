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
 * @addtogroup ArkUI_EventModule
 * @{
 *
 * @brief Declares the UI input event capabilities provided by ArkUI on the native side.
 *
 * @since 12
 */

/**
 * @file ui_input_event.h
 *
 * @brief Provides ArkUI event definitions on the native side.
 *
 * @library libace_ndk.z.so
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @since 12
 */

#ifndef _ARKUI_UI_INPUT_EVENT_H_
#define _ARKUI_UI_INPUT_EVENT_H_

#include "native_type.h"
#ifdef __cplusplus
#include <cstdint>
#else
#include <stdint.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Defines the UI input event.
 *
 * @since 12
 */
typedef struct ArkUI_UIInputEvent ArkUI_UIInputEvent;

/**
 * @brief Enumerates the UI input event types.
 *
 * @since 12
 */
typedef enum {
    ARKUI_UIINPUTEVENT_TYPE_UNKNOWN = 0,
    ARKUI_UIINPUTEVENT_TYPE_TOUCH = 1,
    ARKUI_UIINPUTEVENT_TYPE_AXIS = 2,
    ARKUI_UIINPUTEVENT_TYPE_MOUSE = 3,
    ARKUI_UIINPUTEVENT_TYPE_KEY = 4,
} ArkUI_UIInputEvent_Type;

/**
 * @brief Defines the action code of the input event.
 *
 * @since 12
 */
enum {
    /** Cancellation of touch. */
    UI_TOUCH_EVENT_ACTION_CANCEL = 0,
    /** Pressing of a touch point. */
    UI_TOUCH_EVENT_ACTION_DOWN = 1,
    /** Moving of a touch point. */
    UI_TOUCH_EVENT_ACTION_MOVE = 2,
    /** Lifting of a touch point. */
    UI_TOUCH_EVENT_ACTION_UP = 3,
};

/**
 * @brief Defines the tool type of the touch event.
 *
 * @since 12
 */
enum {
    /** Unknown tool type. */
    UI_INPUT_EVENT_TOOL_TYPE_UNKNOWN = 0,

    /** Finger. */
    UI_INPUT_EVENT_TOOL_TYPE_FINGER = 1,

    /** Pen. */
    UI_INPUT_EVENT_TOOL_TYPE_PEN = 2,

    /** Mouse. */
    UI_INPUT_EVENT_TOOL_TYPE_MOUSE = 3,

    /** TouchPad. */
    UI_INPUT_EVENT_TOOL_TYPE_TOUCHPAD = 4,

    /** JoyStick. */
    UI_INPUT_EVENT_TOOL_TYPE_JOYSTICK = 5,
};

/**
 * @brief Defines the source type of the touch event.
 *
 * @since 12
 */
enum {
    /** Unknown source type. */
    UI_INPUT_EVENT_SOURCE_TYPE_UNKNOWN = 0,
    /** Mouse. */
    UI_INPUT_EVENTT_SOURCE_TYPE_MOUSE = 1,
    /** Touchscreen. */
    UI_INPUT_EVENTT_SOURCE_TYPE_TOUCH_SCREEN = 2,
};

/**
 * @brief Enumerates the hit test modes.
 *
 * @since 12
 */
typedef enum {
    /** Both the node and its child node respond to the hit test of a touch event, but its sibling node is blocked from
     *  the hit test.
     */
    HTM_DEFAULT = 0,

    /** The node responds to the hit test of a touch event, but its child node and sibling node are blocked from the hit
     *  test.
     */
    HTM_BLOCK,

    /** Both the node and its child node respond to the hit test of a touch event, and its sibling node is also
     *  considered during the hit test.
     */
    HTM_TRANSPARENT,

    /** The node does not respond to the hit test of a touch event, but its child node and sibling node are considered
     *  during the hit test.
     */
    HTM_NONE,
} HitTestMode;

/**
 * @brief 定义鼠标事件的Action Code。
 *
 * @since 12
 */
enum {
    /** 无效行为 */
    UI_MOUSE_EVENT_ACTION_UNKNOWN = 0,
    /** 鼠标按键按下。 */
    UI_MOUSE_EVENT_ACTION_PRESS = 1,
    /** 鼠标按键松开。 */
    UI_MOUSE_EVENT_ACTION_RELEASE = 2,
    /** 鼠标移动。 */
    UI_MOUSE_EVENT_ACTION_MOVE = 3,
    /** 鼠标按键被取消。 */
    UI_MOUSE_EVENT_ACTION_CANCEL = 13,
};

/**
 * @brief 定义鼠标事件的按键类型。
 *
 * @since 12
 */
enum {
    /** 无按键。 */
    UI_MOUSE_EVENT_BUTTON_NONE = 0,
    /** 鼠标左键。 */
    UI_MOUSE_EVENT_BUTTON_LEFT = 1,
    /** 鼠标右键。 */
    UI_MOUSE_EVENT_BUTTON_RIGHT = 2,
    /** 鼠标中键。 */
    UI_MOUSE_EVENT_BUTTON_MIDDLE = 3,
    /** 鼠标左侧后退键。 */
    UI_MOUSE_EVENT_BUTTON_BACK = 4,
    /** 鼠标左侧前进键。 */
    UI_MOUSE_EVENT_BUTTON_FORWARD = 5,
};

/**
 * @brief Defines an enum for modifier keys.
 *
 * @since 12
 */
typedef enum {
    /** Ctrl. */
    ARKUI_MODIFIER_KEY_CTRL = 1 << 0,
    /** Shift. */
    ARKUI_MODIFIER_KEY_SHIFT = 1 << 1,
    /** Alt. */
    ARKUI_MODIFIER_KEY_ALT = 1 << 2,
    /** Fn. */
    ARKUI_MODIFIER_KEY_FN = 1 << 3,
} ArkUI_ModifierKeyName;

/**
 * @brief Defines an enum for the axis types for focus axis events.
 *
 * @since 15
 */
enum {
    /** ABS_X. */
    UI_FOCUS_AXIS_EVENT_ABS_X = 0,
    /** ABS_Y. */
    UI_FOCUS_AXIS_EVENT_ABS_Y = 1,
    /** ABS_Z. */
    UI_FOCUS_AXIS_EVENT_ABS_Z = 2,
    /** ABS_RZ. */
    UI_FOCUS_AXIS_EVENT_ABS_RZ = 3,
    /** ABS_GAS. */
    UI_FOCUS_AXIS_EVENT_ABS_GAS = 4,
    /** ABS_BRAKE. */
    UI_FOCUS_AXIS_EVENT_ABS_BRAKE = 5,
    /** ABS_HAT0X. */
    UI_FOCUS_AXIS_EVENT_ABS_HAT0X = 6,
    /** ABS_HAT0Y. */
    UI_FOCUS_AXIS_EVENT_ABS_HAT0Y = 7,
};

/**
 * @brief Enumerates the action types for axis events.
 *
 * @since 15
 */
enum {
    /** The axis event is abnormal. */
    UI_AXIS_EVENT_ACTION_NONE = 0,
    /** The axis event begins. */
    UI_AXIS_EVENT_ACTION_BEGIN = 1,
    /** The axis event is updated. */
    UI_AXIS_EVENT_ACTION_UPDATE = 2,
    /** The axis event ends. */
    UI_AXIS_EVENT_ACTION_END = 3,
    /** The axis event is canceled. */
    UI_AXIS_EVENT_ACTION_CANCEL = 4,
};

/**
 * @brief Defines interaction hand for touch event.
 *
 * @since 15
 */
typedef enum {
    /** UnKnown. */
    ARKUI_EVENT_HAND_NONE = 0,
    /** Left hand. */
    ARKUI_EVENT_HAND_LEFT = 1,
    /** Right hand. */
    ARKUI_EVENT_HAND_RIGHT = 2,
} ArkUI_InteractionHand;

/**
 * @brief Obtains the type of this UI input event.
 *
 * @param event Indicates the pointer to the current UI input event.
 * @return Returns the type of the current UI input event; returns <b>0</b> if any parameter error occurs.
 * @since 12
 */
int32_t OH_ArkUI_UIInputEvent_GetType(const ArkUI_UIInputEvent* event);

/**
 * @brief Obtains the action type of this UI input event.
 *
 * @param event Indicates the pointer to the current UI input event.
 * @return Returns the action type of the current UI input event; returns <b>0</b> if any parameter error occurs.
 * @since 12
 */
int32_t OH_ArkUI_UIInputEvent_GetAction(const ArkUI_UIInputEvent* event);

/**
 * @brief Obtains the source type of this UI input event.
 *
 * @param event Indicates the pointer to the current UI input event.
 * @return Returns the source type of the current UI input event.
 * @since 12
 */
int32_t OH_ArkUI_UIInputEvent_GetSourceType(const ArkUI_UIInputEvent* event);

/**
 * @brief Obtains the tool type of this UI input event.
 *
 * @param event Indicates the pointer to the current UI input event.
 * @return Returns the tool type of the current UI input event.
 * @since 12
 */
int32_t OH_ArkUI_UIInputEvent_GetToolType(const ArkUI_UIInputEvent* event);

/**
 * @brief Obtains the time when this UI input event occurs.
 *
 * @param event Indicates the pointer to the current UI input event.
 * @return Returns the time when the UI input event occurs; returns <b>0</b> if any parameter error occurs.
 * @since 12
 */
int64_t OH_ArkUI_UIInputEvent_GetEventTime(const ArkUI_UIInputEvent* event);

/**
 * @brief Obtains the number of touch points from a directional input event (such as a touch event, mouse event,
 * or axis event).
 *
 * @param event Indicates the pointer to the current UI input event.
 * @return Returns the number of touch points for the directional input event.
 * @since 12
 */
uint32_t OH_ArkUI_PointerEvent_GetPointerCount(const ArkUI_UIInputEvent* event);

/**
 * @brief Obtains the ID of a touch point from a directional input event (such as a touch event, mouse event,
 * or axis event).
 *
 * @param event Indicates the pointer to the current UI input event.
 * @param pointerIndex Indicates the index of the target touch point in the multi-touch data list.
 * @return Returns the ID of the corresponding touch point.
 * @since 12
 */
int32_t OH_ArkUI_PointerEvent_GetPointerId(const ArkUI_UIInputEvent* event, uint32_t pointerIndex);

/**
 * @brief Obtains the X coordinate relative to the upper left corner of the current component from a directional
 * input event (such as a touch event, mouse event, or axis event).
 *
 * @param event Indicates the pointer to the directional input event.
 * @return Returns the X coordinate relative to the upper left corner of the current component;
 * returns <b>0</b> if any parameter error occurs.
 * @since 12
 */
float OH_ArkUI_PointerEvent_GetX(const ArkUI_UIInputEvent* event);

/**
 * @brief Obtains the X coordinate of a specific touch point relative to the upper left corner of the current component
 * from a directional input event (such as a touch event, mouse event, or axis event).
 *
 * @param event Indicates the pointer to the current UI input event.
 * @param pointerIndex Indicates the index of the target touch point in the multi-touch data list.
 * @return Returns the X coordinate relative to the upper left corner of the current component;
 * returns <b>0.0f</b> if any parameter error occurs.
 * @since 12
 */
float OH_ArkUI_PointerEvent_GetXByIndex(const ArkUI_UIInputEvent* event, uint32_t pointerIndex);

/**
 * @brief Obtains the Y coordinate relative to the upper left corner of the current component from a directional
 * input event (such as a touch event, mouse event, or axis event).
 *
 * @param event Indicates the pointer to the UI input event.
 * @return Returns the Y coordinate relative to the upper left corner of the current component;
 * returns <b>0</b> if any parameter error occurs.
 * @since 12
 */
float OH_ArkUI_PointerEvent_GetY(const ArkUI_UIInputEvent* event);

/**
 * @brief Obtains the Y coordinate of a specific touch point relative to the upper left corner of the current component
 * from a directional input event (such as a touch event, mouse event, or axis event).
 *
 * @param event Indicates the pointer to the current UI input event.
 * @param pointerIndex Indicates the index of the target touch point in the multi-touch data list.
 * @return Returns the Y coordinate relative to the upper left corner of the current component;
 * returns <b>0.0f</b> if any parameter error occurs.
 * @since 12
 */
float OH_ArkUI_PointerEvent_GetYByIndex(const ArkUI_UIInputEvent* event, uint32_t pointerIndex);

/**
 * @brief Obtains the X coordinate relative to the upper left corner of the current application window from a
 * directional input event (such as a touch event, mouse event, or axis event).
 *
 * @param event Indicates the pointer to the UI input event.
 * @return Returns the X coordinate relative to the upper left corner of the current application window;
 * returns <b>0</b> if any parameter error occurs.
 * @since 12
 */
float OH_ArkUI_PointerEvent_GetWindowX(const ArkUI_UIInputEvent* event);

/**
 * @brief Obtains the X coordinate of a specific touch point relative to the upper left corner of the current
 * application window from a directional input event (such as a touch event, mouse event, or axis event).
 *
 * @param event Indicates the pointer to the current UI input event.
 * @param pointerIndex Indicates the index of the target touch point in the multi-touch data list.
 * @return Returns the X coordinate relative to the upper left corner of the current application window;
 * returns <b>0.0f</b> if any parameter error occurs.
 * @since 12
 */
float OH_ArkUI_PointerEvent_GetWindowXByIndex(const ArkUI_UIInputEvent* event, uint32_t pointerIndex);

/**
 * @brief Obtains the Y coordinate relative to the upper left corner of the current application window from a
 * directional input event (such as a touch event, mouse event, or axis event).
 *
 * @param event Indicates the pointer to the UI input event.
 * @return Returns the Y coordinate relative to the upper left corner of the current application window;
 * returns <b>0</b> if any parameter error occurs.
 * @since 12
 */
float OH_ArkUI_PointerEvent_GetWindowY(const ArkUI_UIInputEvent* event);

/**
 * @brief Obtains the Y coordinate of a specific touch point relative to the upper left corner of the current
 * application window from a directional input event (such as a touch event, mouse event, or axis event).
 *
 * @param event Indicates the pointer to the current UI input event.
 * @param pointerIndex Indicates the index of the target touch point in the multi-touch data list.
 * @return Returns the Y coordinate relative to the upper left corner of the current application window;
 * returns <b>0.0f</b> if any parameter error occurs.
 * @since 12
 */
float OH_ArkUI_PointerEvent_GetWindowYByIndex(const ArkUI_UIInputEvent* event, uint32_t pointerIndex);

/**
 * @brief Obtains the X coordinate relative to the upper left corner of the current screen from a directional input
 * event (such as a touch event, mouse event, or axis event).
 *
 * @param event Indicates the pointer to the UI input event.
 * @return Returns the X coordinate relative to the upper left corner of the current screen;
 * returns <b>0</b> if any parameter error occurs.
 * @since 12
 */
float OH_ArkUI_PointerEvent_GetDisplayX(const ArkUI_UIInputEvent* event);

/**
 * @brief Obtains the X coordinate of a specific touch point relative to the upper left corner of the current screen
 * from a directional input event (such as a touch event, mouse event, or axis event).
 *
 * @param event Indicates the pointer to the current UI input event.
 * @param pointerIndex Indicates the index of the target touch point in the multi-touch data list.
 * @return Returns the X coordinate relative to the upper left corner of the current screen;
 * returns <b>0.0f</b> if any parameter error occurs.
 * @since 12
 */
float OH_ArkUI_PointerEvent_GetDisplayXByIndex(const ArkUI_UIInputEvent* event, uint32_t pointerIndex);

/**
 * @brief Obtains the Y coordinate relative to the upper left corner of the current screen from a directional input
 * event (such as a touch event, mouse event, or axis event).
 *
 * @param event Indicates the pointer to the UI input event.
 * @return Returns the Y coordinate relative to the upper left corner of the current screen;
 * returns <b>0</b> if any parameter error occurs.
 * @since 12
 */
float OH_ArkUI_PointerEvent_GetDisplayY(const ArkUI_UIInputEvent* event);

/**
 * @brief Obtains the Y coordinate of a specific touch point relative to the upper left corner of the current screen
 * from a directional input event (such as a touch event, mouse event, or axis event).
 *
 * @param event Indicates the pointer to the current UI input event.
 * @param pointerIndex Indicates the index of the target touch point in the multi-touch data list.
 * @return Returns the Y coordinate relative to the upper left corner of the current screen;
 * returns <b>0.0f</b> if any parameter error occurs.
 * @since 12
 */
float OH_ArkUI_PointerEvent_GetDisplayYByIndex(const ArkUI_UIInputEvent* event, uint32_t pointerIndex);

/**
 * @brief Obtains the pressure applied to the touchscreen from a directional input event (for example, a touch event).
 *
 * @param event Indicates the pointer to the current UI input event.
 * @param pointerIndex Indicates the index of the target touch point in the multi-touch data list.
 * @return Returns the pressure applied to the touchscreen; returns <b>0.0f</b> if any parameter error occurs.
 * @since 12
 */
float OH_ArkUI_PointerEvent_GetPressure(const ArkUI_UIInputEvent* event, uint32_t pointerIndex);

/**
 * @brief Obtains the angle relative to the YZ plane from a directional input event (for example, a touch event).
 * The value range is [-90, 90]. A positive value indicates a rightward tilt.
 *
 * @param event Indicates the pointer to the current UI input event.
 * @param pointerIndex Indicates the index of the target touch point in the multi-touch data list.
 * @return Returns the angle relative to the YZ plane.
 * @since 12
 */
float OH_ArkUI_PointerEvent_GetTiltX(const ArkUI_UIInputEvent* event, uint32_t pointerIndex);

/**
 * @brief Obtains the angle relative to the XZ plane from a directional input event (for example, a touch event).
 * The value range is [-90, 90]. A positive value indicates a downward tilt.
 *
 * @param event Indicates the pointer to the current UI input event.
 * @param pointerIndex Indicates the index of the target touch point in the multi-touch data list.
 * @return Returns the angle relative to the XZ plane.
 * @since 12
 */
float OH_ArkUI_PointerEvent_GetTiltY(const ArkUI_UIInputEvent* event, uint32_t pointerIndex);

/**
 * @brief Obtains the rotation angle of the stylus around the z-axis from a UI input event.
 *
 * @param event Pointer to the UI input event.
 * @param rollAngle Rotation angle of the stylus around the z-axis.
 * @return Returns the result code.
 *         Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *         Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 * @since 17
 */
int32_t OH_ArkUI_PointerEvent_GetRollAngle(const ArkUI_UIInputEvent* event, double* rollAngle);

/**
 * @brief Obtains the interaction hand of a touch point.
 *
 * @param event Indicates the pointer to the current UI input event.
 * @param hand Indicates the interaction hand of a touch point.
 * @return Returns the result code.
 *         Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *         Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.
 * @since 15
 */
int32_t OH_ArkUI_PointerEvent_GetInteractionHand(const ArkUI_UIInputEvent *event, ArkUI_InteractionHand *hand);

/**
 * @brief Obtains the interaction hand of a touch point.
 *
 * @param event Indicates the pointer to the current UI input event.
 * @param pointerIndex Indicates the index of the target touch point in the multi-touch data list.
 * @param hand Indicates the interaction hand of a touch point.
 * @return Returns the result code.
 *         Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *         Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.
 * @since 15
 */
int32_t OH_ArkUI_PointerEvent_GetInteractionHandByIndex(
    const ArkUI_UIInputEvent *event, int32_t pointerIndex, ArkUI_InteractionHand *hand);

/**
 * @brief Obtains the width of the touch area from a directional input event (for example, a touch event).
 *
 * @param event Indicates the pointer to the current UI input event.
 * @param pointerIndex Indicates the index of the target touch point in the multi-touch data list.
 * @return Returns the width of the touch area.
 * @since 12
 */
float OH_ArkUI_PointerEvent_GetTouchAreaWidth(const ArkUI_UIInputEvent* event, uint32_t pointerIndex);

/**
 * @brief Obtains the height of the touch area from a directional input event (for example, a touch event).
 *
 * @param event Indicates the pointer to the current UI input event.
 * @param pointerIndex Indicates the index of the target touch point in the multi-touch data list.
 * @return Returns the height of the touch area.
 * @since 12
 */
float OH_ArkUI_PointerEvent_GetTouchAreaHeight(const ArkUI_UIInputEvent* event, uint32_t pointerIndex);

/**
 * @brief Obtains the ID of a touch point which info has been changed.
 *
 * @param event Indicates the changed pointer to the current UI input event.
 * @param pointerIndex Indicates the index of the changed touch point in the multi-touch data list.
 * @return Returns the result code.
 *         Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *         Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 * @since 15
 */
int32_t OH_ArkUI_PointerEvent_GetChangedPointerId(const ArkUI_UIInputEvent* event, uint32_t* pointerIndex);

/**
 * @brief Obtains the number of historical events from a directional input event (such as a touch event, mouse event,
 * or axis event).
 *
 * @param event Indicates the pointer to the current UI input event.
 * @return Returns the number of historical events.
 * @since 12
 */
uint32_t OH_ArkUI_PointerEvent_GetHistorySize(const ArkUI_UIInputEvent* event);

/**
 * @brief Obtains the occurrence time of a historical event from a directional input event (such as a touch event,
 * mouse event, or axis event).
 *
 * @param event Indicates the pointer to the current UI input event.
 * @param historyIndex Indicates the index of the target historical event.
 * @return Returns the time when the UI input event occurs; returns <b>0</b> if any parameter error occurs.
 * @since 12
 */
int64_t OH_ArkUI_PointerEvent_GetHistoryEventTime(const ArkUI_UIInputEvent* event, uint32_t historyIndex);

/**
 * @brief Obtains the number of touch points in a specific historical event from a directional input event (such as
 * a touch event, mouse event, or axis event).
 *
 * @param event Indicates the pointer to the current UI input event.
 * @param historyIndex Indicates the index of the target historical event.
 * @return Returns the number of touch points in the specified historical event
 * @since 12
 */
uint32_t OH_ArkUI_PointerEvent_GetHistoryPointerCount(const ArkUI_UIInputEvent* event, uint32_t historyIndex);

/**
 * @brief Obtains the ID of a touch point in a specific historical event from a directional input event (such as
 * a touch event, mouse event, or axis event).
 *
 * @param event Indicates the pointer to the current UI input event.
 * @param pointerIndex Indicates the index of the target touch point in the multi-touch data list.
 * @param historyIndex Indicates the index of the target historical event.
 * @return Returns the ID of the corresponding touch point in the specified historical event.
 * @since 12
 */
int32_t OH_ArkUI_PointerEvent_GetHistoryPointerId(
    const ArkUI_UIInputEvent* event, uint32_t pointerIndex, uint32_t historyIndex);

/**
 * @brief Obtains the X coordinate of a specific touch point in a historical event relative to the upper left corner
 * of the current component from a directional input event (such as a touch event, mouse event, or axis event).
 *
 * @param event Indicates the pointer to the current UI input event.
 * @param pointerIndex Indicates the index of the target touch point in the multi-touch data list.
 * @param historyIndex Indicates the index of the target historical event.
 * @return Returns the X coordinate relative to the upper left corner of the current component;
 * returns <b>0.0f</b> if any parameter error occurs.
 * @since 12
 */
float OH_ArkUI_PointerEvent_GetHistoryX(const ArkUI_UIInputEvent* event, uint32_t pointerIndex, uint32_t historyIndex);

/**
 * @brief Obtains the Y coordinate of a specific touch point in a historical event relative to the upper left corner
 * of the current component from a directional input event (such as a touch event, mouse event, or axis event).
 *
 * @param event Indicates the pointer to the current UI input event.
 * @param pointerIndex Indicates the index of the target touch point in the multi-touch data list.
 * @param historyIndex Indicates the index of the target historical event.
 * @return Returns the Y coordinate relative to the upper left corner of the current component;
 * returns <b>0.0f</b> if any parameter error occurs.
 * @since 12
 */
float OH_ArkUI_PointerEvent_GetHistoryY(const ArkUI_UIInputEvent* event, uint32_t pointerIndex, uint32_t historyIndex);

/**
 * @brief Obtains the X coordinate of a specific touch point in a historical event relative to the upper left corner
 * of the current application window from a directional input event (such as a touch event, mouse event, or axis event).
 *
 * @param event Indicates the pointer to the current UI input event.
 * @param pointerIndex Indicates the index of the target touch point in the multi-touch data list.
 * @param historyIndex Indicates the index of the target historical event.
 * @return Returns the X coordinate relative to the upper left corner of the current application window;
 * returns <b>0.0f</b> if any parameter error occurs.
 * @since 12
 */
float OH_ArkUI_PointerEvent_GetHistoryWindowX(
    const ArkUI_UIInputEvent* event, uint32_t pointerIndex, uint32_t historyIndex);

/**
 * @brief Obtains the Y coordinate of a specific touch point in a historical event relative to the upper left corner
 * of the current application window from a directional input event (such as a touch event, mouse event, or axis event).
 *
 * @param event Indicates the pointer to the current UI input event.
 * @param pointerIndex Indicates the index of the target touch point in the multi-touch data list.
 * @param historyIndex Indicates the index of the target historical event.
 * @return Returns the Y coordinate relative to the upper left corner of the current application window;
 * returns <b>0.0f</b> if any parameter error occurs.
 * @since 12
 */
float OH_ArkUI_PointerEvent_GetHistoryWindowY(
    const ArkUI_UIInputEvent* event, uint32_t pointerIndex, uint32_t historyIndex);

/**
 * @brief Obtains the X coordinate of a specific touch point in a historical event relative to the upper left corner
 * of the current screen from a directional input event (such as a touch event, mouse event, or axis event).
 *
 * @param event Indicates the pointer to the current UI input event.
 * @param pointerIndex Indicates the index of the target touch point in the multi-touch data list.
 * @param historyIndex Indicates the index of the target historical event.
 * @return Returns the X coordinate relative to the upper left corner of the current screen;
 * returns <b>0.0f</b> if any parameter error occurs.
 * @since 12
 */
float OH_ArkUI_PointerEvent_GetHistoryDisplayX(
    const ArkUI_UIInputEvent* event, uint32_t pointerIndex, uint32_t historyIndex);

/**
 * @brief Obtains the Y coordinate of a specific touch point in a historical event relative to the upper left corner
 * of the current screen from a directional input event (such as a touch event, mouse event, or axis event).
 *
 * @param event Indicates the pointer to the current UI input event.
 * @param pointerIndex Indicates the index of the target touch point in the multi-touch data list.
 * @param historyIndex Indicates the index of the target historical event.
 * @return Returns the Y coordinate relative to the upper left corner of the current screen;
 * returns <b>0.0f</b> if any parameter error occurs.
 * @since 12
 */
float OH_ArkUI_PointerEvent_GetHistoryDisplayY(
    const ArkUI_UIInputEvent* event, uint32_t pointerIndex, uint32_t historyIndex);

/**
 * @brief Obtains the pressure applied to the touchscreen in a specific historical event from a directional input event
 * (for example, a touch event)..
 *
 * @param event Indicates the pointer to the current UI input event.
 * @param pointerIndex Indicates the index of the target touch point in the multi-touch data list.
 * @param historyIndex Indicates the index of the target historical event.
 * @return Returns the pressure applied to the touchscreen; returns <b>0.0f</b> if any parameter error occurs.
 * @since 12
 */
float OH_ArkUI_PointerEvent_GetHistoryPressure(
    const ArkUI_UIInputEvent* event, uint32_t pointerIndex, uint32_t historyIndex);

/**
 * @brief Obtains the angle relative to the YZ plane in a specific historical event from a directional input event
 * (for example, a touch event). The value range is [-90, 90]. A positive value indicates a rightward tilt.
 *
 * @param event Indicates the pointer to the current UI input event.
 * @param pointerIndex Indicates the index of the target touch point in the multi-touch data list.
 * @param historyIndex Indicates the index of the target historical event.
 * @return Returns the angle relative to the YZ plane.
 * @since 12
 */
float OH_ArkUI_PointerEvent_GetHistoryTiltX(
    const ArkUI_UIInputEvent* event, uint32_t pointerIndex, uint32_t historyIndex);

/**
 * @brief Obtains the angle relative to the XZ plane in a specific historical event from a directional input event
 * (for example, a touch event). The value range is [-90, 90]. A positive value indicates a downward tilt.
 *
 * @param event Indicates the pointer to the current UI input event.
 * @param pointerIndex Indicates the index of the target touch point in the multi-touch data list.
 * @param historyIndex Indicates the index of the target historical event.
 * @return Returns the angle relative to the XZ plane.
 * @since 12
 */
float OH_ArkUI_PointerEvent_GetHistoryTiltY(
    const ArkUI_UIInputEvent* event, uint32_t pointerIndex, uint32_t historyIndex);

/**
 * @brief Obtains the width of the touch area in a specific historical event from a directional input event
 * (for example, a touch event).
 *
 * @param event Indicates the pointer to the current UI input event.
 * @param pointerIndex Indicates the index of the target touch point in the multi-touch data list.
 * @param historyIndex Indicates the index of the target historical event.
 * @return Returns the width of the touch area.
 * @since 12
 */
float OH_ArkUI_PointerEvent_GetHistoryTouchAreaWidth(
    const ArkUI_UIInputEvent* event, uint32_t pointerIndex, uint32_t historyIndex);

/**
 * @brief Obtains the height of the touch area in a specific historical event from a directional input event
 * (for example, a touch event).
 *
 * @param event Indicates the pointer to the current UI input event.
 * @param pointerIndex Indicates the index of the target touch point in the multi-touch data list.
 * @param historyIndex Indicates the index of the target historical event.
 * @return Returns the height of the touch area.
 * @since 12
 */
float OH_ArkUI_PointerEvent_GetHistoryTouchAreaHeight(
    const ArkUI_UIInputEvent* event, uint32_t pointerIndex, uint32_t historyIndex);

/**
 * @brief Obtains the value of the vertical scroll axis for this axis event.
 *
 * @param event Indicates the pointer to the UI input event.
 * @return Returns the value of the vertical scroll axis of the current axis event;
 * returns <b>0</b> if any parameter error occurs.
 * @since 12
 */
double OH_ArkUI_AxisEvent_GetVerticalAxisValue(const ArkUI_UIInputEvent* event);

/**
 * @brief Obtains the value of the horizontal scroll axis for this axis event.
 *
 * @param event Indicates the pointer to the UI input event.
 * @return Returns the value of the horizontal scroll axis of the current axis event;
 * returns <b>0</b> if any parameter error occurs.
 * @since 12
 */
double OH_ArkUI_AxisEvent_GetHorizontalAxisValue(const ArkUI_UIInputEvent* event);

/**
 * @brief Obtains the scale value of the pinch axis for this axis event.
 *
 * @param event Indicates the pointer to the UI input event.
 * @return Returns the scale value of the pinch axis of the current axis event;
 * returns <b>0</b> if any parameter error occurs.
 * @since 12
 */
double OH_ArkUI_AxisEvent_GetPinchAxisScaleValue(const ArkUI_UIInputEvent* event);

/**
 * @brief Obtains the action type of the current axis event.
 *
 * @param event Indicates the pointer to the current UI input event.
 * @return Returns the action type of the current axis event.
 * @since 15
 */
int32_t OH_ArkUI_AxisEvent_GetAxisAction(const ArkUI_UIInputEvent* event);

/**
 * @brief Sets how the component behaves during hit testing.
 *
 * @param event Indicates the pointer to the current UI input event.
 * @param mode Indicates how the component behaves during hit testing. The parameter type is {@link HitTestMode}.
 * @return Returns the status code of the execution.
 * @since 12
 */
int32_t OH_ArkUI_PointerEvent_SetInterceptHitTestMode(const ArkUI_UIInputEvent* event, HitTestMode mode);

/**
 * @brief 获取鼠标事件的按键类型的值。
 *
 * @param event 表示指向当前UI输入事件的指针。
 * @return 返回鼠标按键类型，1为左键，2为右键，3为中键，4为后退键，5为前进键。
 * @since 12
 */
int32_t OH_ArkUI_MouseEvent_GetMouseButton(const ArkUI_UIInputEvent* event);

/**
 * @brief 获取鼠标事件的鼠标动作类型的值。
 *
 * @param event 表示指向当前UI输入事件的指针。
 * @return 返回鼠标动作类型，1表示按键按下，2表示按键松开，3表示鼠标移动。
 * @since 12
 */
int32_t OH_ArkUI_MouseEvent_GetMouseAction(const ArkUI_UIInputEvent* event);

/**
 * @brief Sets whether to prevent event bubbling.
 *
 * @param event Indicates the pointer to the current UI input event.
 * @param stopPropagation Indicates whether the event is prevented from bubbling.
 * @return Returns the status code of the execution. If 0 is returned, the setting is successful.
 *         If 401 is returned, the execution fails.
 *         The possible cause of the failure is that the event parameter is abnormal, such as a null pointer.
 * @since 12
 */
int32_t OH_ArkUI_PointerEvent_SetStopPropagation(const ArkUI_UIInputEvent* event, bool stopPropagation);

/**
 * @brief Obtains the ID of device that triggers UI input event.
 *
 * @param event Pointer to an <b>ArkUI_UIInputEvent</b> object.
 * @return Returns the device ID.
 * @since 14
 */
int32_t OH_ArkUI_UIInputEvent_GetDeviceId(const ArkUI_UIInputEvent* event);

/**
 * @brief Obtains all keys that are pressed from UI input event. Only supports key events currently.
 *
 * @param event Pointer to an <b>ArkUI_UIInputEvent</b> object.
 * @param pressedKeyCodes Array of all keys that are pressed. You need to allocate the memory space.
 * @param length Length of the passed pressedKeyCodes array (when used as an input parameter);
 *               number of the keys pressed (when used as an output parameter).
 * @return return Returns the result code.
 *         Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *         Returns {@link ARKUI_ERROR_CODE_BUFFER_SIZE_NOT_ENOUGH} if the giving buffer is not enough.
 *         Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 * @since 14
 */
int32_t OH_ArkUI_UIInputEvent_GetPressedKeys(
    const ArkUI_UIInputEvent* event, int32_t* pressedKeyCodes, int32_t* length);

/**
 * @brief Obtains the axis value of a focus axis event.
 *
 * @param event Pointer to an <b>ArkUI_UIInputEvent</b> object.
 * @param axis Axis type of the focus axis event.
 * @return Returns the axis value of the focus axis event; returns <b>0.0</b> if any parameter error occurs.
 * @since 15
 */
double OH_ArkUI_FocusAxisEvent_GetAxisValue(const ArkUI_UIInputEvent* event, int32_t axis);

/**
 * @brief Sets whether to prevent a focus axis event from bubbling up.
 *
 * @param event Indicates the pointer to the current UI input event.
 * @param stopPropagation Indicates whether to stop event propagation.
 * @return Returns the result code.
 *         Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *         Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 * @since 15
 */
int32_t OH_ArkUI_FocusAxisEvent_SetStopPropagation(const ArkUI_UIInputEvent* event, bool stopPropagation);

/**
* @brief Obtains the width of the component hit by an event.
*
* @param event Pointer to an <b>ArkUI_UIInputEvent</b> object.
* @return Returns the width of the component hit by the event; returns <b>0.0f</b> if any parameter error occurs.
* @since 17
*/
float OH_ArkUI_UIInputEvent_GetEventTargetWidth(const ArkUI_UIInputEvent* event);

/**
* @brief Obtains the height of the component hit by an event.
*
* @param event Pointer to an <b>ArkUI_UIInputEvent</b> object.
* @return Returns the height of the component hit by the event; returns <b>0.0f</b> if any parameter error occurs.
* @since 17
*/
float OH_ArkUI_UIInputEvent_GetEventTargetHeight(const ArkUI_UIInputEvent* event);

/**
* @brief Obtains the X coordinate of the component hit by an event.
*
* @param event Pointer to an <b>ArkUI_UIInputEvent</b> object.
* @return Returns the X coordinate of the component hit by the event; returns <b>0.0f</b> if any parameter error occurs.
* @since 17
*/
float OH_ArkUI_UIInputEvent_GetEventTargetPositionX(const ArkUI_UIInputEvent* event);

/**
* @brief Obtains the Y coordinate of the component hit by an event.
*
* @param event Pointer to an <b>ArkUI_UIInputEvent</b> object.
* @return Returns the Y coordinate of the component hit by the event;
*         returns <b>0.0f</b> if any parameter error occurs.
* @since 17
*/
float OH_ArkUI_UIInputEvent_GetEventTargetPositionY(const ArkUI_UIInputEvent* event);

/**
* @brief Obtains the global X coordinate of the component hit by an event.
*
* @param event Pointer to an <b>ArkUI_UIInputEvent</b> object.
* @return Returns the global X coordinate of the component hit by the event;
*         returns <b>0.0f</b> if any parameter error occurs.
* @since 17
*/
float OH_ArkUI_UIInputEvent_GetEventTargetGlobalPositionX(const ArkUI_UIInputEvent* event);

/**
* @brief Obtains the global Y coordinate of the component hit by an event.
*
* @param event Pointer to an <b>ArkUI_UIInputEvent</b> object.
* @return Returns the global Y coordinate of the component hit by the event;
*         returns <b>0.0f</b> if any parameter error occurs.
* @since 17
*/
float OH_ArkUI_UIInputEvent_GetEventTargetGlobalPositionY(const ArkUI_UIInputEvent* event);

/**
* @brief Checks whether the cursor is hovering over this component.
*
* @param event Pointer to an <b>ArkUI_UIInputEvent</b> object.
* @return Returns <b>true</b> if the cursor is hovering over the current component.
*         Returns <b>false</b> if the cursor is not hovering over the current component.
* @since 17
*/
bool OH_ArkUI_HoverEvent_IsHovered(const ArkUI_UIInputEvent* event);

/**
 * @brief Obtains the state of the modifier keys in a UI input event.
 *
 * @param event Pointer to an <b>ArkUI_UIInputEvent</b> object.
 * @param keys Pointer to a variable where the current combination of pressed modifier keys will be returned.
 *        The application can use bitwise operations to determine the state of each modifier key.
 * @return Returns the result code.
 *         Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *         Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 * @since 17
 */
int32_t OH_ArkUI_UIInputEvent_GetModifierKeyStates(const ArkUI_UIInputEvent* event, uint64_t* keys);

/**
 * @brief Obtains the pressed time of a specific touch point.
 *
 * @param event Indicates the pointer to the current UI input event.
 * @param pointerIndex Indicates the index of the target touch point in the multi-touch data list.
 * @return Returns the pressed time of a specific touch point; returns <b>0</b> if any parameter error occurs.
 * @since 15
 */
int64_t OH_ArkUI_PointerEvent_GetPressedTimeByIndex(const ArkUI_UIInputEvent* event, uint32_t pointerIndex);

/**
 * @brief Obtains the X axis offset relative to the previous reported mouse pointer position. When the mouse pointer is
 * at the edge of the screen, the value may be less than the difference of the X coordinate reported twice.
 *
 * @param event Indicates the pointer to the current UI input event.
 * @return Returns the X axis offset relative to the previous reported mouse pointer position;
 * returns <b>0.0f</b> if any parameter error occurs.
 * @since 15
 */
float OH_ArkUI_MouseEvent_GetRawDeltaX(const ArkUI_UIInputEvent* event);

/**
 * @brief Obtains the Y axis offset relative to the previous reported mouse pointer position. When the mouse pointer is
 * at the edge of the screen, the value may be less than the difference of the Y coordinate reported twice.
 *
 * @param event Indicates the pointer to the current UI input event.
 * @return Returns the Y axis offset relative to the previous reported mouse pointer position;
 * returns <b>0.0f</b> if any parameter error occurs.
 * @since 15
 */
float OH_ArkUI_MouseEvent_GetRawDeltaY(const ArkUI_UIInputEvent* event);

/**
 * @brief Obtains the pressed buttons from the mouse event.
 *
 * @param event Pointer to an <b>ArkUI_UIInputEvent</b> object.
 * @param pressedButtons Indicates the list of the pressed buttons.You need to create a int array first.
 * @param length Length of the passed pressedButtons array (when used as an input parameter);
 *               number of the buttons pressed (when used as an output parameter).
 * @return Returns the result code.
 *         Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *         Returns {@link ARKUI_ERROR_CODE_BUFFER_SIZE_ERROR} if the giving buffer is not enough.
 * @since 15
 */
int32_t OH_ArkUI_MouseEvent_GetPressedButtons(
    const ArkUI_UIInputEvent* event, int32_t* pressedButtons, int32_t* length);

/**
 * @brief Obtains the screen ID on which the UI input event occurred.
 *
 * @param event Pointer to an <b>ArkUI_UIInputEvent</b> object.
 * @return Returns the screen ID; returns <b>0</b> if any parameter error occurs.
 * @since 15
 */
int32_t OH_ArkUI_UIInputEvent_GetTargetDisplayId(const ArkUI_UIInputEvent* event);

/**
 * @brief Sets whether to enable axis event propagation.
 *
 * @param event Pointer to the UI input event.
 * @param propagation Whether to enable event propagation.
 * @return Returns the result code.
 *         Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *         Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 * @since 17
 */
int32_t OH_ArkUI_AxisEvent_SetPropagation(const ArkUI_UIInputEvent* event, bool propagation);

/**
 * @brief Obtains the scroll step configuration of the mouse wheel axis event.
 *
 * @param event Pointer to the UI input event.
 * @return Returns the scroll step configuration of the mouse wheel axis event.
 * @since 17
 */
int32_t OH_ArkUI_AxisEvent_GetScrollStep(const ArkUI_UIInputEvent* event);

/**
 * @brief Create cloned pointer event from the original pointer event.
 *
 * @param event Pointer to an <b>ArkUI_UIInputEvent</b> object.
 * @param clonedEvent Pointer to an <b>ArkUI_UIInputEvent</b> pointer.
 * @return Returns the result code.
 *          Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *          Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 * @since 15
 */
int32_t OH_ArkUI_PointerEvent_CreateClonedEvent(const ArkUI_UIInputEvent* event, ArkUI_UIInputEvent** clonedEvent);

/**
 * @brief Destroy the cloned pointer event.
 *
 * @param event Pointer to an <b>ArkUI_UIInputEvent</b> object.
 * @return Returns the result code.
 *          Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *          Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 *          Returns {@link ARKUI_ERROR_CODE_NON_CLONED_POINTER_EVENT} if the event is not the cloned pointer event.
 * @since 15
 */
int32_t OH_ArkUI_PointerEvent_DestroyClonedEvent(const ArkUI_UIInputEvent* event);

/**
 * @brief Set the position relative to the upper left corner of the current component from a cloned directional
 * input event.
 *
 * @param event Pointer to an <b>ArkUI_UIInputEvent</b> object.
 * @param x The X coordinate relative to the upper left corner of the current component, in px.
 * @param y The Y coordinate relative to the upper left corner of the current component, in px.
 * @return Returns the result code.
 *          Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *          Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 *          Returns {@link ARKUI_ERROR_CODE_NON_CLONED_POINTER_EVENT} if the event is not the cloned pointer event.
 * @since 15
 */
int32_t OH_ArkUI_PointerEvent_SetClonedEventLocalPosition(const ArkUI_UIInputEvent* event, float x, float y);

/**
 * @brief Set the position of a specific touch point relative to the upper left corner of the current component
 * from a cloned directional input event.
 *
 * @param event Pointer to an <b>ArkUI_UIInputEvent</b> object.
 * @param x The X coordinate relative to the upper left corner of the current component, in px.
 * @param y The Y coordinate relative to the upper left corner of the current component, in px.
 * @param pointerIndex Indicates the index of the target touch point in the multi-touch data list.
 * @return Returns the result code.
 *          Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *          Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 *          Returns {@link ARKUI_ERROR_CODE_NON_CLONED_POINTER_EVENT} if the event is not the cloned pointer event.
 * @since 15
 */
int32_t OH_ArkUI_PointerEvent_SetClonedEventLocalPositionByIndex(
    const ArkUI_UIInputEvent* event, float x, float y, int32_t pointerIndex);

/**
 * @brief Set the action type of the cloned pointer event.
 *
 * @param event Pointer to an <b>ArkUI_UIInputEvent</b> object.
 * @param actionType The action type of pointer event.
 * @return Returns the result code.
 *          Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *          Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 *          Returns {@link ARKUI_ERROR_CODE_NON_CLONED_POINTER_EVENT} if the event is not the cloned pointer event.
 * @since 15
 */
int32_t OH_ArkUI_PointerEvent_SetClonedEventActionType(const ArkUI_UIInputEvent* event, int32_t actionType);

/**
 * @brief Set the ID of the touch point that triggers the current cloned pointer event.
 *
 * @param event Pointer to an <b>ArkUI_UIInputEvent</b> object.
 * @param fingerId The ID of the touch point that triggers the current pointer event.
 * @return Returns the result code.
 *          Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *          Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 *          Returns {@link ARKUI_ERROR_CODE_NON_CLONED_POINTER_EVENT} if the event is not the cloned pointer event.
 * @since 15
 */
int32_t OH_ArkUI_PointerEvent_SetClonedEventChangedFingerId(const ArkUI_UIInputEvent* event, int32_t fingerId);

/**
 * @brief Set the ID of a touch point from a cloned directional input event.
 *
 * @param event Pointer to an <b>ArkUI_UIInputEvent</b> object.
 * @param fingerId The ID of the touch point.
 * @param pointerIndex Indicates the index of the target touch point in the multi-touch data list.
 * @return Returns the result code.
 *          Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *          Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 *          Returns {@link ARKUI_ERROR_CODE_NON_CLONED_POINTER_EVENT} if the event is not the cloned pointer event.
 * @since 15
 */
int32_t OH_ArkUI_PointerEvent_SetClonedEventFingerIdByIndex(
    const ArkUI_UIInputEvent* event, int32_t fingerId, int32_t pointerIndex);

/**
 * @brief Post a cloned event to a specific node.
 *
 * @param node Target node.
 * @param event Pointer to an <b>ArkUI_UIInputEvent</b> object.
 * @return Returns the result code.
 *          Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *          Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 *          Returns {@link ARKUI_ERROR_CODE_NON_CLONED_POINTER_EVENT} if the event is not the cloned pointer event.
 *          Returns {@link ARKUI_ERROR_CODE_POST_CLONED_COMPONENT_STATUS_ABNORMAL }
 *          if the component status abnormal.
 *          Returns {@link ARKUI_ERROR_CODE_POST_CLONED_NO_COMPONENT_HIT_TO_RESPOND_TO_THE_EVENT }
 *          if no component hit to respond to the event.
 * @since 15
 */
int32_t OH_ArkUI_PointerEvent_PostClonedEvent(ArkUI_NodeHandle node, const ArkUI_UIInputEvent* event);

/**
 * @brief Obtains the result code of the most recent API call related to an <b>ArkUI_UIInputEvent</b> object.
 * This API is typically unnecessary for normal operations, but can be used to verify ambiguous return values
 * (for example, when <b>0.0</b> might be either a valid float result or an error).
 *      float x = OH_ArkUI_PointerEvent_GetX(event);
 *      if (ARKUI_ERROR_CODE_NO_ERROR != OH_Arkui_UIInputEvent_GetlatestStatus()) {
 *          // error
 *          return;
 *      }
 * The system automatically clears the previous status before each API call related to an <b>ArkUI_UIInputEvent</b>
 * object, ensuring that this API always returns the latest execution status.
 *
 * @return Result code of the most recent API call related to the <b>ArkUI_UIInputEvent</b> object.
 * @since 20
 */
ArkUI_ErrorCode OH_ArkUI_UIInputEvent_GetLatestStatus();

#ifdef __cplusplus
};
#endif

#endif // _ARKUI_UI_INPUT_EVENT_H_
/** @} */
