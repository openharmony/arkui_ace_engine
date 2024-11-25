/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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

#ifndef POINTER_EVENT_H
#define POINTER_EVENT_H

#include <array>
#include <list>
#include <memory>
#include <set>
#include <unordered_map>
#include <vector>

namespace OHOS {
namespace MMI {
class PointerEvent {
public:
    /**
     * Indicates an unknown pointer action. It is usually used as initial value.
     *
     * @since 9
     */
    static constexpr int32_t POINTER_ACTION_UNKNOWN = 0;

    /**
     * Indicates a pointer action that has been canceled.
     *
     * @since 9
     */
    static constexpr int32_t POINTER_ACTION_CANCEL = 1;

    /**
     * Indicates a pointer action representing that a finger is pressed on a touchscreen or touchpad.
     *
     * @since 9
     */
    static constexpr int32_t POINTER_ACTION_DOWN = 2;

    /**
     * Indicates a pointer action representing that a finger moves on a touchscreen or touchpad or a mouse
     * pointer moves.
     *
     * @since 9
     */
    static constexpr int32_t POINTER_ACTION_MOVE = 3;

    /**
     * Indicates a pointer action representing that a finger leaves the touchscreen or touchpad.
     *
     * @since 9
     */
    static constexpr int32_t POINTER_ACTION_UP = 4;

    /**
     * Indicates the start action of the axis event related to the pointer.
     *
     * @since 9
     */
    static constexpr int32_t POINTER_ACTION_AXIS_BEGIN = 5;

    /**
     * Indicates the update action of the axis event related to the pointer.
     *
     * @since 9
     */
    static constexpr int32_t POINTER_ACTION_AXIS_UPDATE = 6;

    /**
     * Indicates the end action of the axis event related to the pointer.
     *
     * @since 9
     */
    static constexpr int32_t POINTER_ACTION_AXIS_END = 7;

    /**
     * Indicates a pointer action representing that a button is pressed.
     *
     * @since 9
     */
    static constexpr int32_t POINTER_ACTION_BUTTON_DOWN = 8;

    /**
     * Indicates a pointer action representing that a button is released.
     *
     * @since 9
     */
    static constexpr int32_t POINTER_ACTION_BUTTON_UP = 9;

    /**
     * Indicates that the pointer enters the window.
     *
     * @since 9
     */
    static constexpr int32_t POINTER_ACTION_ENTER_WINDOW = 10;

    /**
     * Indicates that the pointer leaves the window.
     *
     * @since 9
     */
    static constexpr int32_t POINTER_ACTION_LEAVE_WINDOW = 11;

    static constexpr int32_t POINTER_ACTION_PULL_DOWN = 12;

    static constexpr int32_t POINTER_ACTION_PULL_MOVE = 13;

    static constexpr int32_t POINTER_ACTION_PULL_UP = 14;

    static constexpr int32_t POINTER_ACTION_PULL_IN_WINDOW = 15;

    static constexpr int32_t POINTER_ACTION_PULL_OUT_WINDOW = 16;

    /**
     * Indicates that the fingers swipe up in touch pad.
     *
     * @since 9
     */
    static constexpr int32_t POINTER_ACTION_SWIPE_BEGIN = 17;

    static constexpr int32_t POINTER_ACTION_SWIPE_UPDATE = 18;

    static constexpr int32_t POINTER_ACTION_SWIPE_END = 19;

    /**
     * Indicates that the fingers rotate in touch pad.
     *
     * @since 11
     */
    static constexpr int32_t POINTER_ACTION_ROTATE_BEGIN = 20;

    static constexpr int32_t POINTER_ACTION_ROTATE_UPDATE = 21;

    static constexpr int32_t POINTER_ACTION_ROTATE_END = 22;

    static constexpr int32_t POINTER_ACTION_TRIPTAP = 23;

    static constexpr int32_t POINTER_ACTION_QUADTAP = 24;

    /**
     * Indicates that the hover action.
     *
     * @since 11
     */
    static constexpr int32_t POINTER_ACTION_HOVER_MOVE = 25;

    static constexpr int32_t POINTER_ACTION_HOVER_ENTER = 26;

    static constexpr int32_t POINTER_ACTION_HOVER_EXIT = 27;

    /**
     * Indicates that the fingerprint action.
     *
     * @since 12
     */
    static constexpr int32_t POINTER_ACTION_FINGERPRINT_DOWN = 28;

    static constexpr int32_t POINTER_ACTION_FINGERPRINT_UP = 29;

    static constexpr int32_t POINTER_ACTION_FINGERPRINT_SLIDE = 30;

    static constexpr int32_t POINTER_ACTION_FINGERPRINT_RETOUCH = 31;

    static constexpr int32_t POINTER_ACTION_FINGERPRINT_CLICK = 32;

    static constexpr int32_t POINTER_ACTION_HOVER_CANCEL = 33;

    static constexpr int32_t POINTER_ACTION_FINGERPRINT_CANCEL = 34;

    /**
     * Indicates that the pen proximity action.
     *
     * @since 12
     */
    static constexpr int32_t POINTER_ACTION_PROXIMITY_IN = 35;

    static constexpr int32_t POINTER_ACTION_PROXIMITY_OUT = 36;

    /**
     * 表示触屏手势动作
     *
     * @since 12
     */
    static constexpr int32_t TOUCH_ACTION_SWIPE_DOWN = 100;

    static constexpr int32_t TOUCH_ACTION_SWIPE_UP = 101;

    static constexpr int32_t TOUCH_ACTION_SWIPE_RIGHT = 102;

    static constexpr int32_t TOUCH_ACTION_SWIPE_LEFT = 103;

    static constexpr int32_t TOUCH_ACTION_PINCH_OPENED = 104;

    static constexpr int32_t TOUCH_ACTION_PINCH_CLOSEED = 105;

    static constexpr int32_t TOUCH_ACTION_GESTURE_END = 106;

    enum AxisType {
        /**
         * Indicates an unknown axis type. It is generally used as the initial value.
         *
         * @since 9
         */
        AXIS_TYPE_UNKNOWN,

        /**
         * Indicates the vertical scroll axis. When you scroll the mouse wheel or make certain gestures on the touchpad,
         * the status of the vertical scroll axis changes.
         *
         * @since 9
         */
        AXIS_TYPE_SCROLL_VERTICAL,

        /**
         * Indicates the horizontal scroll axis.
         * When you scroll the mouse wheel or make certain gestures on the touchpad,
         * the status of the horizontal scroll axis changes.
         *
         * @since 9
         */
        AXIS_TYPE_SCROLL_HORIZONTAL,

        /**
         * Indicates the pinch axis, which is used to describe a pinch gesture on the touchscreen or touchpad.
         *
         * @since 9
         */
        AXIS_TYPE_PINCH,

        /**
         * Indicates the rotate axis, which is used to describe a rotate gesture on the touchpad.
         *
         * @since 11
         */
        AXIS_TYPE_ROTATE,

        /**
         * Indicates the x axis. The status of the x axis changes when you operate the joystick.
         *
         * @since 9
         */
        AXIS_TYPE_ABS_X,

        /**
         * Indicates the y axis. The status of the y axis changes when you operate the joystick.
         *
         * @since 9
         */
        AXIS_TYPE_ABS_Y,

        /**
         * Indicates the z axis. The status of the z axis changes when you operate the joystick.
         *
         * @since 9
         */
        AXIS_TYPE_ABS_Z,

        /**
         * Indicates the rz axis. The status of the rz axis changes when you operate the joystick.
         *
         * @since 9
         */
        AXIS_TYPE_ABS_RZ,

        /**
         * Indicates the gas axis. The status of the gas axis changes when you operate the joystick.
         *
         * @since 9
         */
        AXIS_TYPE_ABS_GAS,

        /**
         * Indicates the brake axis. The status of the brake axis changes when you operate the joystick.
         *
         * @since 9
         */
        AXIS_TYPE_ABS_BRAKE,

        /**
         * Indicates the hat0x axis. The status of the hat0x axis changes when you operate the joystick.
         *
         * @since 9
         */
        AXIS_TYPE_ABS_HAT0X,

        /**
         * Indicates the hat0y axis. The status of the hat0y axis changes when you operate the joystick.
         *
         * @since 9
         */
        AXIS_TYPE_ABS_HAT0Y,

        /**
         * Indicates the throttle axis. The status of the throttle axis changes when you operate the joystick.
         *
         * @since 9
         */
        AXIS_TYPE_ABS_THROTTLE,

        /**
         * Indicates the maximum number of defined axis types.
         *
         * @since 9
         */
        AXIS_TYPE_MAX
    };

    /**
     * Indicates an unknown input source type. It is usually used as the initial value.
     *
     * @since 9
     */
    static constexpr int32_t SOURCE_TYPE_UNKNOWN = 0;

    /**
     * Indicates that the input source generates events similar to mouse cursor movement,
     * button press and release, and wheel scrolling.
     *
     * @since 9
     */
    static constexpr int32_t SOURCE_TYPE_MOUSE = 1;

    /**
     * Indicates that the input source generates a touchscreen multi-touch event.
     *
     * @since 9
     */
    static constexpr int32_t SOURCE_TYPE_TOUCHSCREEN = 2;

    /**
     * Indicates that the input source generates a touchpad multi-touch event.
     *
     * @since 9
     */
    static constexpr int32_t SOURCE_TYPE_TOUCHPAD = 3;

    /**
     * Indicates joystick-like events generated by the input source, such as button pressing, button lifting,
     * and wheel scrolling.
     *
     * @since 9
     */
    static constexpr int32_t SOURCE_TYPE_JOYSTICK = 4;

    /**
     * Indicates that the input source generates a fingerprint event.
     *
     * @since 12
     */
    static constexpr int32_t SOURCE_TYPE_FINGERPRINT = 5;

    /**
     * Indicates that the input source generates a crown event.
     *
     * @since 12
     */
    static constexpr int32_t SOURCE_TYPE_CROWN = 6;

    /**
     * Indicates an invalid button ID.
     *
     * @since 9
     */
    static constexpr int32_t BUTTON_NONE = -1;

    /**
     * Indicates the left button on a mouse.
     *
     * @since 9
     */
    static constexpr int32_t MOUSE_BUTTON_LEFT = 0;

    /**
     * Indicates the right button on a mouse.
     *
     * @since 9
     */
    static constexpr int32_t MOUSE_BUTTON_RIGHT = 1;

    /**
     * Indicates the middle button on a mouse.
     *
     * @since 9
     */
    static constexpr int32_t MOUSE_BUTTON_MIDDLE = 2;

    /**
     * Indicates the side button on a mouse.
     *
     * @since 9
     */
    static constexpr int32_t MOUSE_BUTTON_SIDE = 3;

    /**
     * Indicates the extra button on a mouse.
     *
     * @since 9
     */
    static constexpr int32_t MOUSE_BUTTON_EXTRA = 4;

    /**
     * Indicates the forward button on a mouse.
     *
     * @since 9
     */
    static constexpr int32_t MOUSE_BUTTON_FORWARD = 5;

    /**
     * Indicates the back button on a mouse.
     *
     * @since 9
     */
    static constexpr int32_t MOUSE_BUTTON_BACK = 6;

    /**
     * Indicates the task button on a mouse.
     *
     * @since 9
     */
    static constexpr int32_t MOUSE_BUTTON_TASK = 7;

    /**
     * Indicates a finger.
     *
     * @since 9
     */
    static constexpr int32_t TOOL_TYPE_FINGER = 0;

    /**
     * Indicates a stylus.
     *
     * @since 9
     */
    static constexpr int32_t TOOL_TYPE_PEN = 1;

    /**
     * Indicates an eraser.
     *
     * @since 9
     */
    static constexpr int32_t TOOL_TYPE_RUBBER = 2;

    /**
     * Indicates a brush.
     *
     * @since 9
     */
    static constexpr int32_t TOOL_TYPE_BRUSH = 3;

    /**
     * Indicates a pencil.
     *
     * @since 9
     */
    static constexpr int32_t TOOL_TYPE_PENCIL = 4;

    /**
     * Indicates an air brush.
     *
     * @since 9
     */
    static constexpr int32_t TOOL_TYPE_AIRBRUSH = 5;

    /**
     * Indicates a mouse.
     *
     * @since 9
     */
    static constexpr int32_t TOOL_TYPE_MOUSE = 6;

    /**
     * Indicates a lens.
     *
     * @since 9
     */
    static constexpr int32_t TOOL_TYPE_LENS = 7;

    /**
     * Indicates a knuckle.
     *
     * @since 11
     */
    static constexpr int32_t TOOL_TYPE_KNUCKLE = 8;

    /**
     * Indicates a touchpad.
     *
     * @since 9
     */
    static constexpr int32_t TOOL_TYPE_TOUCHPAD = 9;

    /**
     * Indicates a palm.
     *
     * @since 10
     */
    static constexpr int32_t TOOL_TYPE_PALM = 10;

    /**
     * Indicates the TL2 key on the joystick.
     *
     * @since 9
     */
    static constexpr int32_t JOYSTICK_BUTTON_TL2 = 0;

    /**
     * Indicates the TR2 key on the joystick.
     *
     * @since 9
     */
    static constexpr int32_t JOYSTICK_BUTTON_TR2 = 1;

    /**
     * Indicates the TL key on the joystick.
     *
     * @since 9
     */
    static constexpr int32_t JOYSTICK_BUTTON_TL = 2;

    /**
     * Indicates the TR key on the joystick.
     *
     * @since 9
     */
    static constexpr int32_t JOYSTICK_BUTTON_TR = 3;

    /**
     * Indicates the WEST key on the joystick.
     *
     * @since 9
     */
    static constexpr int32_t JOYSTICK_BUTTON_WEST = 4;

    /**
     * Indicates the SOUTH key on the joystick.
     *
     * @since 9
     */
    static constexpr int32_t JOYSTICK_BUTTON_SOUTH = 5;

    /**
     * Indicates the NORTH key on the joystick.
     *
     * @since 9
     */
    static constexpr int32_t JOYSTICK_BUTTON_NORTH = 6;

    /**
     * Indicates the EAST key on the joystick.
     *
     * @since 9
     */
    static constexpr int32_t JOYSTICK_BUTTON_EAST = 7;

    /**
     * Indicates the START key on the joystick.
     *
     * @since 9
     */
    static constexpr int32_t JOYSTICK_BUTTON_START = 8;

    /**
     * Indicates the SELECT key on the joystick.
     *
     * @since 9
     */
    static constexpr int32_t JOYSTICK_BUTTON_SELECT = 9;

    /**
     * Indicates the HOMEPAGE key on the joystick.
     *
     * @since 9
     */
    static constexpr int32_t JOYSTICK_BUTTON_HOMEPAGE = 10;

    /**
     * Indicates the THUMBL key on the joystick.
     *
     * @since 9
     */
    static constexpr int32_t JOYSTICK_BUTTON_THUMBL = 11;

    /**
     * Indicates the THUMBR key on the joystick.
     *
     * @since 9
     */
    static constexpr int32_t JOYSTICK_BUTTON_THUMBR = 12;

    /**
     * Indicates the TRIGGER key on the joystick.
     *
     * @since 9
     */
    static constexpr int32_t JOYSTICK_BUTTON_TRIGGER = 13;

    /**
     * Indicates the THUMB key on the joystick.
     *
     * @since 9
     */
    static constexpr int32_t JOYSTICK_BUTTON_THUMB = 14;

    /**
     * Indicates the THUMB2 key on the joystick.
     *
     * @since 9
     */
    static constexpr int32_t JOYSTICK_BUTTON_THUMB2 = 15;

    /**
     * Indicates the TOP key on the joystick.
     *
     * @since 9
     */
    static constexpr int32_t JOYSTICK_BUTTON_TOP = 16;

    /**
     * Indicates the TOP2 key on the joystick.
     *
     * @since 9
     */
    static constexpr int32_t JOYSTICK_BUTTON_TOP2 = 17;

    /**
     * Indicates the PINKIE key on the joystick.
     *
     * @since 9
     */
    static constexpr int32_t JOYSTICK_BUTTON_PINKIE = 18;

    /**
     * Indicates the BASE key on the joystick.
     *
     * @since 9
     */
    static constexpr int32_t JOYSTICK_BUTTON_BASE = 19;

    /**
     * Indicates the BASE2 key on the joystick.
     *
     * @since 9
     */
    static constexpr int32_t JOYSTICK_BUTTON_BASE2 = 20;

    /**
     * Indicates the BASE3 key on the joystick.
     *
     * @since 9
     */
    static constexpr int32_t JOYSTICK_BUTTON_BASE3 = 21;

    /**
     * Indicates the BASE4 key on the joystick.
     *
     * @since 9
     */
    static constexpr int32_t JOYSTICK_BUTTON_BASE4 = 22;

    /**
     * Indicates the BASE5 key on the joystick.
     *
     * @since 9
     */
    static constexpr int32_t JOYSTICK_BUTTON_BASE5 = 23;

    /**
     * Indicates the BASE6 key on the joystick.
     *
     * @since 9
     */
    static constexpr int32_t JOYSTICK_BUTTON_BASE6 = 24;

    /**
     * Indicates the DEAD key on the joystick.
     *
     * @since 9
     */
    static constexpr int32_t JOYSTICK_BUTTON_DEAD = 25;

    /**
     * Indicates the C key on the joystick.
     *
     * @since 9
     */
    static constexpr int32_t JOYSTICK_BUTTON_C = 26;

    /**
     * Indicates the Z key on the joystick.
     *
     * @since 9
     */
    static constexpr int32_t JOYSTICK_BUTTON_Z = 27;

    /**
     * Indicates the MODE key on the joystick.
     *
     * @since 9
     */
    static constexpr int32_t JOYSTICK_BUTTON_MODE = 28;

    enum AxisEventType {
        /**
         * Indicates an unknown axis events.
         *
         * @since 12
         */
        AXIS_EVENT_TYPE_UNKNOWN = -1,
        /**
         * Indicates two-finger pinch events. The axis value can be AXIS_TYPE_PINCH or AXIS_TYPE_ROTATE.
         *
         * @since 12
         */
        AXIS_EVENT_TYPE_PINCH = 1,
        /**
         * Indicates scroll axis events. The axis value can be AXIS_TYPE_SCROLL_VERTICAL or AXIS_TYPE_SCROLL_HORIZONTAL.
         * Wherein, the value of AXIS_TYPE_SCROLL_HORIZONTAL is 0 for a mouse wheel event.
         *
         * @since 12
         */
        AXIS_EVENT_TYPE_SCROLL = 2,
    };

public:
    class PointerItem {
    public:
        PointerItem();
        ~PointerItem();

    public:
        /**
         * @brief Obtains the ID of the pointer in this event.
         * @return Returns the pointer ID.
         * @since 9
         */
        int32_t GetPointerId() const;

        /**
         * @brief Sets the ID of the pointer in this event.
         * @param pointerId Indicates the pointer ID to set.
         * @return void
         * @since 9
         */
        void SetPointerId(int32_t pointerId);

        /**
         * @brief Obtains the origin id of the pointer in this event.
         * @return Returns the pointer id.
         * @since 12
         */
        int32_t GetOriginPointerId() const;

        /**
         * @brief Sets the origin id of the pointer in this event.
         * @param pointerId Indicates the pointer id to set.
         * @return void
         * @since 12
         */
        void SetOriginPointerId(int32_t originPointerId);

        /**
         * @brief Obtains the time when the pointer is pressed.
         * @return Returns the time.
         * @since 9
         */
        int64_t GetDownTime() const;

        /**
         * @brief Sets the time when the pointer is pressed.
         * @param downTime Indicates the time to set.
         * @return void
         * @since 9
         */
        void SetDownTime(int64_t downTime);

        /**
         * @brief Checks whether the pointer is pressed.
         * @return Returns <b>true</b> if the pointer is pressed; returns <b>false</b> otherwise.
         * @since 9
         */
        bool IsPressed() const;

        /**
         * @brief Sets whether to enable the pressed state for the pointer.
         * @param pressed Specifies whether to set the pressed state for the pointer.
         * The value <b>true</b> means to set the pressed state for the pointer, and the
         * value <b>false</b> means the opposite.
         * @return void
         * @since 9
         */
        void SetPressed(bool pressed);

        /**
         * @brief Obtains the x coordinate relative to the upper left corner of the screen.
         * For a touchpad input event, the value is the absolute x coordinate on the touchpad.
         * For other pointer input events, the value is the x coordinate on the target screen.
         * @return Returns the x coordinate.
         * @since 9
         */
        int32_t GetDisplayX() const;
        double GetDisplayXPos() const;

        /**
         * @brief Sets the x coordinate relative to the upper left corner of the screen.
         * @param displayX Indicates the x coordinate to set.
         * @return void
         * @since 9
         */
        void SetDisplayX(int32_t displayX);
        void SetDisplayXPos(double displayX);

        /**
         * @brief Obtains the y coordinate relative to the upper left corner of the screen.
         * For a touchpad input event, the value is the absolute y coordinate on the touchpad.
         * For other pointer input events, the value is the y coordinate on the target screen.
         * @return Returns the y coordinate.
         * @since 9
         */
        int32_t GetDisplayY() const;
        double GetDisplayYPos() const;

        /**
         * @brief Sets the y coordinate relative to the upper left corner of the screen.
         * @param displayY Indicates the y coordinate to set.
         * @return void
         * @since 9
         */
        void SetDisplayY(int32_t displayY);
        void SetDisplayYPos(double displayY);

        /**
         * @brief Obtains the x coordinate of the active window.
         * @return Returns the x coordinate.
         * @since 9
         */
        int32_t GetWindowX() const;
        double GetWindowXPos() const;

        /**
         * @brief Sets the x coordinate of the active window.
         * @param x Indicates the x coordinate to set.
         * @return void
         * @since 9
         */
        void SetWindowX(int32_t x);
        void SetWindowXPos(double x);

        /**
         * @brief Obtains the y coordinate of the active window.
         * @return Returns the y coordinate.
         * @since 9
         */
        int32_t GetWindowY() const;
        double GetWindowYPos() const;

        /**
         * @brief Sets the y coordinate of the active window.
         * @param y Indicates the y coordinate to set.
         * @return void
         * @since 9
         */
        void SetWindowY(int32_t y);
        void SetWindowYPos(double y);

        /**
         * @brief Obtains the width of the pressed area.
         * @return Returns the width.
         * @since 9
         */
        int32_t GetWidth() const;

        /**
         * @brief Sets the width of the pressed area.
         * @param width Indicates the width to set.
         * @return void
         * @since 9
         */
        void SetWidth(int32_t width);

        /**
         * @brief Obtains the height of the pressed area.
         * @return Returns the height.
         * @since 9
         */
        int32_t GetHeight() const;

        /**
         * @brief Sets the height of the pressed area.
         * @param height Indicates the height to set.
         * @return void
         * @since 9
         */
        void SetHeight(int32_t height);

        /**
         * @brief Obtains the X coordinate of the tool area's center point relative to the
         * upper left corner of the screen.
         * @return Returns the X coordinate.
         * @since 9
         */
        int32_t GetToolDisplayX() const;

        /**
         * @brief Sets the X coordinate of the tool area's center point relative to the
         * upper left corner of the screen.
         * @param x Indicates the X coordinate.
         * @return void
         * @since 9
         */
        void SetToolDisplayX(int32_t displayX);

        /**
         * @brief Obtains the Y coordinate of the tool area's center point relative to the
         * upper left corner of the screen.
         * @return Returns the Y coordinate.
         * @since 9
         */
        int32_t GetToolDisplayY() const;

        /**
         * @brief Sets the Y coordinate of the tool area's center point relative to the
         * upper left corner of the screen.
         * @param y Indicates the Y coordinate.
         * @return void
         * @since 9
         */
        void SetToolDisplayY(int32_t displayY);

        /**
         * @brief Obtains the X coordinate of the tool area's center point relative to the
         * upper left corner of the window.
         * @return Returns the X coordinate.
         * @since 9
         */
        int32_t GetToolWindowX() const;

        /**
         * @brief Sets the X coordinate of the tool area's center point relative to the
         * upper left corner of the window.
         * @param x Indicates the X coordinate.
         * @return void
         * @since 9
         */
        void SetToolWindowX(int32_t x);

        /**
         * @brief Obtains the Y coordinate of the tool area's center point relative to the
         * upper left corner of the window.
         * @return Returns the Y coordinate.
         * @since 9
         */
        int32_t GetToolWindowY() const;

        /**
         * @brief Sets the Y coordinate of the tool area's center point relative to the
         * upper left corner of the window.
         * @param y Indicates the Y coordinate.
         * @return void
         * @since 9
         */
        void SetToolWindowY(int32_t y);

        /**
         * @brief Obtains the width of the tool area.
         * @return Returns the width of the tool area.
         * @since 9
         */
        int32_t GetToolWidth() const;

        /**
         * @brief Sets the width of the tool area.
         * @param width Indicates the width of the tool area.
         * @return void
         * @since 9
         */
        void SetToolWidth(int32_t width);

        /**
         * @brief Obtains the height of the tool area.
         * @return Returns the height of the tool area.
         * @since 9
         */
        int32_t GetToolHeight() const;

        /**
         * @brief Sets the height of the tool area.
         * @param height Indicates the height of the tool area.
         * @return void
         * @since 9
         */
        void SetToolHeight(int32_t height);

        /**
         * @brief Obtains the tilt angle of the x axis.
         * @return Returns the tilt angle of the x axis.
         * @since 9
         */
        double GetTiltX() const;

        /**
         * @brief Sets the tilt angle of the x axis.
         * @param tiltX Indicates the tilt angle to set.
         * @return void
         * @since 9
         */
        void SetTiltX(double tiltX);

        /**
         * @brief Obtains the tilt angle of the y axis.
         * @return Returns the tilt angle of the y axis.
         * @since 9
         */
        double GetTiltY() const;

        /**
         * @brief Sets the tilt angle of the y axis.
         * @param tiltY Indicates the tilt angle to set.
         * @return void
         * @since 9
         */
        void SetTiltY(double tiltY);

        /**
         * @brief Obtains the pressure in this event.
         * @return Returns the pressure.
         * @since 9
         */
        double GetPressure() const;

        /**
         * @brief Sets the pressure for this event.
         * @param pressure Indicates the pressure to set.
         * @return void
         * @since 9
         */
        void SetPressure(double pressure);

        /**
         * @brief Obtains the moveflag in this event.
         * @return Returns the moveflag.
         * @since 12
         */
        int32_t GetMoveFlag() const;

        /**
         * @brief Sets the moveflag for this event.
         * @param moveflag Indicates the moveflag to set.
         * @return void
         * @since 12
         */
        void SetMoveFlag(int32_t moveFlag);

        /**
         * @brief Obtains the long axis of the touch point area.
         * @return Returns the long axis of the touch point area.
         * @since 9
         */
        int32_t GetLongAxis() const;

        /**
         * @brief Sets the long axis of the touch point area.
         * @param longAxis Indicates the long axis of the touch point area.
         * @return void
         * @since 9
         */
        void SetLongAxis(int32_t longAxis);

        /**
         * @brief Obtains the short axis of the touch point area.
         * @return Returns the short axis of the touch point area.
         * @since 9
         */
        int32_t GetShortAxis() const;

        /**
         * @brief Sets the short axis of the touch point area.
         * @param shortAxis Indicates the short axis of the touch point area.
         * @return void
         * @since 9
         */
        void SetShortAxis(int32_t shortAxis);

        /**
         * @brief Obtains the ID of the current device.
         * @return Returns the device ID.
         * @since 9
         */
        int32_t GetDeviceId() const;

        /**
         * @brief Sets the ID for the current device.
         * @param deviceId Indicates the device ID to set.
         * @return void
         * @since 9
         */
        void SetDeviceId(int32_t deviceId);

        /**
         * @brief Obtains the tool type.
         * @return Returns the tool type.
         * @since 9
         */
        int32_t GetToolType() const;

        /**
         * @brief Sets the tool type.
         * @param toolType Indicates the tool type to set.
         * @return void
         * @since 9
         */
        void SetToolType(int32_t toolType);

        /**
         * @brief Obtains the ID of the window corresponding to the finger touch position.
         * @return Returns the ID of the target window.
         * @since 9
         */
        int32_t GetTargetWindowId() const;

        /**
         * @brief Sets the ID of the window corresponding to the finger touch position.
         * @param windowId Indicates the ID of the target window.
         * @return void
         * @since 9
         */
        void SetTargetWindowId(int32_t windowId);

        /**
         * @brief Obtains the raw X coordinate.
         * @return Returns the raw X coordinate.
         * @since 9
         */
        int32_t GetRawDx() const;

        /**
         * @brief Sets the raw X coordinate.
         * @param rawDx Indicates the raw X coordinate to set.
         * @return void
         * @since 9
         */

        void SetRawDx(int32_t rawDx);
        /**
         * @brief Obtains the raw Y coordinate.
         * @return Returns the raw Y coordinate.
         * @since 9
         */
        int32_t GetRawDy() const;

        /**
         * @brief Sets the raw Y coordinate.
         * @param rawDy Indicates the raw Y coordinate to set.
         * @return void
         * @since 9
         */
        void SetRawDy(int32_t rawDy);

         /**
         * @brief Sets the raw X coordinate of the tool area's center point relative to the
         * upper left corner of the screen.
         * @param rawDisplayX Indicates the raw X coordinate to set.
         * @return void
         * @since 12
         */
        void SetRawDisplayX(int32_t rawDisplayX);
 
        /**
         * @brief Obtains the raw X coordinate relative to the upper left corner of the screen.
         * @return Returns the raw X coordinate.
         * @since 12
         */
        int32_t GetRawDisplayX() const;
 
        /**
         * @brief Sets the raw Y coordinate of the tool area's center point relative to the
         * upper left corner of the screen.
         * @param rawDisplayY Indicates the raw Y coordinate to set.
         * @return void
         * @since 12
         */
 
        void SetRawDisplayY(int32_t rawDisplayY);
        /**
         * @brief Obtains the raw Y coordinate relative to the upper left corner of the screen..
         * @return Returns the raw Y coordinate.
         * @since 12
         */
        int32_t GetRawDisplayY() const;
    private:
        int32_t pointerId_ { -1 };
        bool pressed_ { false };
        int32_t displayX_ {};
        int32_t displayY_ {};
        int32_t windowX_ {};
        int32_t windowY_ {};
        double displayXPos_ {};
        double displayYPos_ {};
        double windowXPos_ {};
        double windowYPos_ {};
        int32_t width_ {};
        int32_t height_ {};
        double tiltX_ {};
        double tiltY_ {};
        int32_t toolDisplayX_ {};
        int32_t toolDisplayY_ {};
        int32_t toolWindowX_ {};
        int32_t toolWindowY_ {};
        int32_t toolWidth_ {};
        int32_t toolHeight_ {};
        double pressure_ {};
        int32_t moveFlag_ { -1 };
        int32_t longAxis_ {};
        int32_t shortAxis_ {};
        int32_t deviceId_ {};
        int64_t downTime_ {};
        int32_t toolType_ {};
        int32_t targetWindowId_ { -1 };
        int32_t originPointerId_ { 0 };
        int32_t rawDx_ {};
        int32_t rawDy_ {};
        int32_t rawDisplayX_ {};
        int32_t rawDisplayY_ {};
    };

public:
    /**
     * @brief Copy constructor function for PointerEvent
     * @since 9
     */
    PointerEvent(const PointerEvent& other);

    /**
     * Virtual destructor of PointerEvent
     *
     * @since 9
     */
    virtual ~PointerEvent();

    PointerEvent& operator=(const PointerEvent& other) = delete;

    /**
     * @brief Create PointerEvent object
     * @since 9
     */
    static std::shared_ptr<PointerEvent> Create();

    /**
     * @brief Obtains the pointer action in this event.
     * @return Returns the pointer action.
     * @since 9
     */
    int32_t GetPointerAction() const;

    /**
     * @brief Sets a pointer action for this event.
     * @param pointerAction Indicates the pointer action to set.
     * @return void
     * @since 9
     */
    void SetPointerAction(int32_t pointerAction);

    /**
     * @brief Dumps the action of this pointer input event as a string.
     * @return Returns the pointer to the string.
     * @since 9
     */
    const char* DumpPointerAction() const;

    /**
     * @brief Obtains the pointer ID in this event.
     * @return Returns the pointer ID.
     * @since 9
     */
    int32_t GetPointerId() const;

    /**
     * @brief Sets an ID for the pointer in this event.
     * @param pointerId Indicates the pointer ID to set.
     * @return void
     * @since 9
     */
    void SetPointerId(int32_t pointerId);

    /**
     * @brief Obtains the pointer item of a specified pointer ID.
     * @param pointerId Indicates the pointer ID.
     * @param pointerItem Indicates the item used to receive the data of the pointer.
     * @return Returns <b>true</b> if the data of the pointer with the specified ID exists;
     * returns <b>false</b> otherwise.
     * @since 9
     */
    bool GetPointerItem(int32_t pointerId, PointerItem &pointerItem);

    /**
     * @brief Adds a pointer item.
     * @param pointerItem Indicates the pointer item to add.
     * @return void
     * @since 9
     */
    void AddPointerItem(PointerItem &pointerItem);

    /**
     * @brief Removes a pointer item based on the pointer ID.
     * @param pointerId Indicates the ID of the pointer from which the pointer item is to be removed.
     * @return void
     * @since 9
     */
    void RemovePointerItem(int32_t pointerId);

    /**
     * @brief All of the pointer items is be removed.
     * @return void
     * @since 9
     */
    void RemoveAllPointerItems();

    /**
     * @brief Return all the pointerItems.
     * @return Returns pointers_.
     * @since 9
     */
    std::list<PointerItem> GetAllPointerItems() const;

    /**
     * @brief Updates a pointer item based on the pointer ID.
     * @param pointerId Indicates the ID of the pointer from which the pointer item is to be updated.
     * @param pointerItem Indicates the pointer item to update.
     * @return void
     * @since 9
     */
    void UpdatePointerItem(int32_t pointerId, PointerItem &pointerItem);

    /**
     * @brief Obtains the set of pressed buttons.
     * @return Returns the pressed buttons.
     * @since 9
     */
    std::set<int32_t> GetPressedButtons() const;

    /**
     * @brief Checks whether a specified button is being pressed.
     * @param buttonId Indicates the button ID.
     * @return Returns <b>true</b> if the button is being pressed; returns <b>false</b> otherwise.
     * @since 9
     */
    bool IsButtonPressed(int32_t buttonId) const;

    /**
     * @brief Sets the pressed state for a button.
     * @param buttonId Indicates the button ID of the button to be set in the pressed state.
     * @return void
     * @since 9
     */
    void SetButtonPressed(int32_t buttonId);

    /**
     * @brief Deletes a released button.
     * @param buttonId Indicates the button ID of the button.
     * @return void
     * @since 9
     */
    void DeleteReleaseButton(int32_t buttonId);

    /**
     * @brief Clears the button in the pressed state.
     * @return void
     * @since 9
     */
    void ClearButtonPressed();

    int32_t GetPointerCount() const;

    /**
     * @brief Obtains all pointers in this event.
     * @return Returns all the pointer IDs.
     * @since 9
     */
    std::vector<int32_t> GetPointerIds() const;

    /**
     * @brief Obtains the source type of this event.
     * @return Returns the source type.
     * @since 9
     */
    int32_t GetSourceType() const;

    /**
     * @brief Sets the source type for this event.
     * @param sourceType Indicates the source type to set.
     * @return void
     * @since 9
     */
    void SetSourceType(int32_t sourceType);

    /**
     * @brief Dumps the source type of this pointer input event as a string.
     * @return Returns the pointer to the string.
     * @since 9
     */
    const char* DumpSourceType() const;

    /**
     * @brief Obtains the button ID in this event.
     * @return Returns the button ID.
     * @since 9
     */
    int32_t GetButtonId() const;

    /**
     * @brief Sets the button ID for this event.
     * @param buttonId Indicates the button ID to set.
     * @return void
     * @since 9
     */
    void SetButtonId(int32_t buttonId);

    /**
     * @brief Obtains the finger count in this event.
     * @return Returns the finger count.
     * @since 9
     */
    int32_t GetFingerCount() const;

    /**
     * @brief Sets the finger count for this event.
     * @param fingerCount Indicates the finger count to set.
     * @return void
     * @since 9
     */
    void SetFingerCount(int32_t fingerCount);

    /**
     * @brief Obtains the zOrder in this event, inject to windows whose zOrder less than the target zOrder.
     * @return Returns the zOrder.
     * @since 9
     */
    float GetZOrder() const;

    /**
     * @brief Sets the zOrder for this event, inject to windows whose zOrder less than the target zOrder.
     * @param fingerCount Indicates the zOrder to set.
     * @return void
     * @since 9
     */
    void SetZOrder(float zOrder);

    /**
     * @brief Obtains the axis value.
     * @param axis Indicates the axis type.
     * @return Returns the axis value.
     * @since 9
     */
    double GetAxisValue(AxisType axis) const;

    /**
     * @brief Sets the axis value.
     * @param axis Indicates the axis type.
     * @param axisValue Indicates the axis value to set.
     * @return void
     * @since 9
     */
    void SetAxisValue(AxisType axis, double axisValue);

    /**
     * @brief Clear the axis value of PointerEvent when a mouse event is received.
     * @return void
     * @since 9
     */
    void ClearAxisValue();
    void ClearAxisStatus(AxisType axis);

    /**
     * @brief Checks whether this event contains a specified axis type.
     * @param axis Indicates the axis type.
     * @return Returns <b>true</b> if the event contains the specified axis type; returns <b>false</b> otherwise.
     * @since 9
     */
    bool HasAxis(AxisType axis) const;

    /**
     * @brief Obtains all axis of this event.
     * @return Returns all the axis, Each bit indicates an axis.
     * @since 9
     */
    uint32_t GetAxes() const;

    /**
     * @brief Obtains the axis value velocity.
     * @return Returns the axis value velocity.
     * @since 12
     */
    double GetVelocity() const;

    /**
     * @brief Sets the axis value velocity.
     * @param velocity Indicates the axis value velocity.
     * @return void
     * @since 12
     */
    void SetVelocity(double velocity);

    /**
     * @brief Set the front keys in the key combination.
     * @param pressedKeys Indicates the front keys to set.
     * @return void.
     * @since 9
     */
    void SetPressedKeys(const std::vector<int32_t> pressedKeys);

    /**
     * @brief Obtains the set of pressed keys.
     * @return Returns the pressed keys.
     * @since 9
     */
    std::vector<int32_t> GetPressedKeys() const;

    /**
     * @brief Checks whether this input event is valid.
     * @return Returns <b>true</b> if the input event is valid; returns <b>false</b> otherwise.
     * @since 9
     */
    bool IsValid() const;

    /**
     * @brief 设置buffer值.
     * @param buffer 表示该事件所携带的buffer值.
     * @return void.
     * @since 9
     */
    void SetBuffer(std::vector<uint8_t> buffer);

    /**
     * @brief 清空buffer值.
     * @param void.
     * @return void.
     * @since 9
     */
    void ClearBuffer();

    /**
     * @brief 获取buffer值.
     * @return Returns buffer.
     * @since 9
     */
    std::vector<uint8_t> GetBuffer() const;

#ifdef OHOS_BUILD_ENABLE_SECURITY_COMPONENT
    /**
     * @brief Set the enhance data.
     * @return void.
     * @since 10
     */
    void SetEnhanceData(const std::vector<uint8_t>& enhanceData);
    /**
     * @brief Obtains the enhance data.
     * @return Returns the enhance data.
     * @since 10
     */
    std::vector<uint8_t> GetEnhanceData() const;
#endif // OHOS_BUILD_ENABLE_SECURITY_COMPONENT
public:
    /**
     * @brief Checks whether the axes set represented by <b>axes</b> contains a specified type of axis.
     * @param axes Indicates the set of axes. Each bit indicates an axis.
     * @param axis Indicates the type of the axis to check.
     * @return Returns <b>true</b> if the axes set contains the specified axis type; returns <b>false</b> otherwise.
     * @since 9
     */
    static bool HasAxis(uint32_t axes, AxisType axis);

public:
    /**
     * @brief The number of times the input event is dispatched.
     * @return Return the event dispatch times.
     * @since 12
     */
    int32_t GetDispatchTimes() const;

    /**
     * @brief The number of times the same input event was distributed to multiple different windows.
     * @return void
     * @since 12
     */
    void SetDispatchTimes(int32_t dispatchTimes);

    /**
     * @brief Get the originPointerAction for pointerEvent
     * @return originPointerAction
     * @since 12
     */
    int32_t GetOriginPointerAction() const;

    /**
     * @brief Set the originPointerAction for pointerEvent
     * @return void
     * @since 12
     */
    void SetOriginPointerAction(int32_t pointerAction);

    /**
     * @brief Obtains the axis event type.
     * @return Returns the axis event type.
     * @since 12
     */
    int32_t GetAxisEventType() const;

    /**
     * @brief Sets axis event type.
     * @param axisEventType Indicates the axis event type to set.
     * @return void
     * @since 12
     */
    void SetAxisEventType(int32_t axisEventType);

    /**
     * @brief Obtains the drag id.
     * @return Returns the drag id.
     * @since 12
     */
    int32_t GetPullId() const;

    /**
     * @brief Sets drag id.
     * @param pullId Indicates the drag id to set.
     * @return void
     * @since 12
     */
    void SetPullId(int32_t pullId);

#ifdef OHOS_BUILD_ENABLE_FINGERPRINT
    /**
     * @brief Set the fingerprint distance X.
     * @param X Indicates the distance X.
     * @return void.
     * @since 12
     */
    void SetFingerprintDistanceX(double x);

    /**
     * @brief Set the fingerprint distance Y.
     * @param Y Indicates the distance Y.
     * @return void.
     * @since 12
     */
    void SetFingerprintDistanceY(double y);

    /**
     * @brief Get the fingerprint distance X.
     * @return distance X.
     * @since 12
     */
    double GetFingerprintDistanceX() const;

    /**
     * @brief Get the fingerprint distance Y.
     * @return distance Y.
     * @since 12
     */
    double GetFingerprintDistanceY() const;
#endif // OHOS_BUILD_ENABLE_FINGERPRINT

protected:
    /**
     * @brief Constructs an input event object by using the specified input event type. Generally, this method
     * is used to construct a base class object when constructing a derived class object.
     * @since 9
     */
    explicit PointerEvent(int32_t eventType);

private:
    bool IsValidCheckMouseFunc() const;
    bool IsValidCheckMouse() const;
    bool IsValidCheckTouchFunc() const;
    bool IsValidCheckTouch() const;

private:
    int32_t pointerId_ { -1 };
    std::list<PointerItem> pointers_;
    std::set<int32_t> pressedButtons_;
    int32_t sourceType_ { SOURCE_TYPE_UNKNOWN };
    int32_t pointerAction_ { POINTER_ACTION_UNKNOWN };
    int32_t originPointerAction_ { POINTER_ACTION_UNKNOWN };
    int32_t buttonId_ { BUTTON_NONE };
    int32_t fingerCount_ { 0 };
    int32_t pullId_ { -1 };
    float zOrder_ { -1.0f };
    uint32_t axes_ { 0U };
    std::array<double, AXIS_TYPE_MAX> axisValues_ {};
    double velocity_ { 0.0 };
    std::vector<int32_t> pressedKeys_;
    std::vector<uint8_t> buffer_;
    int32_t axisEventType_ { AXIS_EVENT_TYPE_UNKNOWN };
#ifdef OHOS_BUILD_ENABLE_FINGERPRINT
    double fingerprintDistanceX_ { 0.0 };
    double fingerprintDistanceY_ { 0.0 };
#endif // OHOS_BUILD_ENABLE_FINGERPRINT
    int32_t dispatchTimes_ { 0 };
#ifdef OHOS_BUILD_ENABLE_SECURITY_COMPONENT
    std::vector<uint8_t> enhanceData_;
#endif // OHOS_BUILD_ENABLE_SECURITY_COMPONENT
#ifdef OHOS_BUILD_ENABLE_ANCO
    bool ancoDeal_ { false };
#endif // OHOS_BUILD_ENABLE_ANCO
};

inline bool PointerEvent::HasAxis(AxisType axis) const
{
    return HasAxis(axes_, axis);
}

inline uint32_t PointerEvent::GetAxes() const
{
    return axes_;
}
} // namespace MMI
} // namespace OHOS
#endif // POINTER_EVENT_H
