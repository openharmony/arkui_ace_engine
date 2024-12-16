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
 * @brief Provides the general key event APIs of ArkUI on the native side.
 *
 * @since 14
 */

/**
 * @file native_key_event.h
 *
 * @brief Declares the APIs related to native key events.
 *
 * @library libace_ndk.z.so
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @kit ArkUI
 * @since 14
 */

#ifndef ARKUI_NATIVE_KEY_EVENT_H
#define ARKUI_NATIVE_KEY_EVENT_H

#include <stdint.h>

#include "native_type.h"
#include "ui_input_event.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Defines an enum for the key codes in key events.
 *
 * @since 14
 */
typedef enum {
    /** Unknown (or unrecognized) key **/
    ARKUI_KEYCODE_UNKNOWN = -1,
    /** Function (Fn) key **/
    ARKUI_KEYCODE_FN = 0,
    /** Volume Up key **/
    ARKUI_KEYCODE_VOLUME_UP = 16,
    /** Volume Down key **/
    ARKUI_KEYCODE_VOLUME_DOWN = 17,
    /** Power key **/
    ARKUI_KEYCODE_POWER = 18,
    /** Shutter key **/
    ARKUI_KEYCODE_CAMERA = 19,
    /** Speaker Mute key **/
    ARKUI_KEYCODE_VOLUME_MUTE = 22,
    /** Mute key **/
    ARKUI_KEYCODE_MUTE = 23,
    /** Brightness Up key **/
    ARKUI_KEYCODE_BRIGHTNESS_UP = 40,
    /** Brightness Down key **/
    ARKUI_KEYCODE_BRIGHTNESS_DOWN = 41,
    /** Key 0 **/
    ARKUI_KEYCODE_0 = 2000,
    /** Key 1 **/
    ARKUI_KEYCODE_1 = 2001,
    /** Key 2 **/
    ARKUI_KEYCODE_2 = 2002,
    /** Key 3 **/
    ARKUI_KEYCODE_3 = 2003,
    /** Key 4 **/
    ARKUI_KEYCODE_4 = 2004,
    /** Key 5 **/
    ARKUI_KEYCODE_5 = 2005,
    /** Key 6 **/
    ARKUI_KEYCODE_6 = 2006,
    /** Key 7 **/
    ARKUI_KEYCODE_7 = 2007,
    /** Key 8 **/
    ARKUI_KEYCODE_8 = 2008,
    /** Key 9 **/
    ARKUI_KEYCODE_9 = 2009,
    /** Key + **/
    ARKUI_KEYCODE_STAR = 2010,
    /** Key # **/
    ARKUI_KEYCODE_POUND = 2011,
     /** Up key on D-pad **/
    ARKUI_KEYCODE_DPAD_UP = 2012,
    /** Down key on D-pad **/
    ARKUI_KEYCODE_DPAD_DOWN = 2013,
    /** Left key on D-pad **/
    ARKUI_KEYCODE_DPAD_LEFT = 2014,
    /** Right key on D-pad **/
    ARKUI_KEYCODE_DPAD_RIGHT = 2015,
    /** OK key on D-pad **/
    ARKUI_KEYCODE_DPAD_CENTER = 2016,
    /** Key A **/
    ARKUI_KEYCODE_A = 2017,
    /** Key B **/
    ARKUI_KEYCODE_B = 2018,
    /** Key C **/
    ARKUI_KEYCODE_C = 2019,
    /** Key D **/
    ARKUI_KEYCODE_D = 2020,
    /** Key E **/
    ARKUI_KEYCODE_E = 2021,
    /** Key F **/
    ARKUI_KEYCODE_F = 2022,
    /** Key G **/
    ARKUI_KEYCODE_G = 2023,
    /** Key H **/
    ARKUI_KEYCODE_H = 2024,
    /** Key I **/
    ARKUI_KEYCODE_I = 2025,
    /** Key J **/
    ARKUI_KEYCODE_J = 2026,
    /** Key K **/
    ARKUI_KEYCODE_K = 2027,
    /** Key L **/
    ARKUI_KEYCODE_L = 2028,
    /** Key M **/
    ARKUI_KEYCODE_M = 2029,
    /** Key N **/
    ARKUI_KEYCODE_N = 2030,
    /** Key O **/
    ARKUI_KEYCODE_O = 2031,
    /** Key P **/
    ARKUI_KEYCODE_P = 2032,
    /** Key R **/
    ARKUI_KEYCODE_Q = 2033,
    /** Key R **/
    ARKUI_KEYCODE_R = 2034,
    /** Key S **/
    ARKUI_KEYCODE_S = 2035,
    /** Key T **/
    ARKUI_KEYCODE_T = 2036,
    /** Key U **/
    ARKUI_KEYCODE_U = 2037,
    /** Key V **/
    ARKUI_KEYCODE_V = 2038,
    /** Key W **/
    ARKUI_KEYCODE_W = 2039,
    /** Key X **/
    ARKUI_KEYCODE_X = 2040,
    /** Key Y **/
    ARKUI_KEYCODE_Y = 2041,
    /** Key Z **/
    ARKUI_KEYCODE_Z = 2042,
    /** Key # **/
    ARKUI_KEYCODE_COMMA = 2043,
    /** Key # **/
    ARKUI_KEYCODE_PERIOD = 2044,
    /** Left Alt key **/
    ARKUI_KEYCODE_ALT_LEFT = 2045,
    /** Right Alt key **/
    ARKUI_KEYCODE_ALT_RIGHT = 2046,
    /** Left Shift key **/
    ARKUI_KEYCODE_SHIFT_LEFT = 2047,
    /** Right Shift key **/
    ARKUI_KEYCODE_SHIFT_RIGHT = 2048,
    /** Tab key **/
    ARKUI_KEYCODE_TAB = 2049,
    /** Space key **/
    ARKUI_KEYCODE_SPACE = 2050,
    /** Symbol key **/
    ARKUI_KEYCODE_SYM = 2051,
    /** Explorer key, used to start the explorer application **/
    ARKUI_KEYCODE_EXPLORER = 2052,
    /** Email key, used to start the email application **/
    ARKUI_KEYCODE_ENVELOPE = 2053,
    /** Enter key **/
    ARKUI_KEYCODE_ENTER = 2054,
    /** Backspace key **/
    ARKUI_KEYCODE_DEL = 2055,
    /** Key ` **/
    ARKUI_KEYCODE_GRAVE = 2056,
    /** Key - **/
    ARKUI_KEYCODE_MINUS = 2057,
    /** Key = **/
    ARKUI_KEYCODE_EQUALS = 2058,
    /** Key [ **/
    ARKUI_KEYCODE_LEFT_BRACKET = 2059,
    /** Key ]**/
    ARKUI_KEYCODE_RIGHT_BRACKET = 2060,
    /** Key \\ **/
    ARKUI_KEYCODE_BACKSLASH = 2061,
    /** Key ; **/
    ARKUI_KEYCODE_SEMICOLON = 2062,
    /** Key ' **/
    ARKUI_KEYCODE_APOSTROPHE = 2063,
    /** Key / **/
    ARKUI_KEYCODE_SLASH = 2064,
    /** Key @ **/
    ARKUI_KEYCODE_AT = 2065,
    /** Key + **/
    ARKUI_KEYCODE_PLUS = 2066,
    /** Menu key **/
    ARKUI_KEYCODE_MENU = 2067,
    /** Page Up key **/
    ARKUI_KEYCODE_PAGE_UP = 2068,
    /** Page Down key **/
    ARKUI_KEYCODE_PAGE_DOWN = 2069,
    /** ESC key **/
    ARKUI_KEYCODE_ESCAPE = 2070,
    /** Delete key **/
    ARKUI_KEYCODE_FORWARD_DEL = 2071,
    /** Left Ctrl key **/
    ARKUI_KEYCODE_CTRL_LEFT = 2072,
    /** Right Ctrl key **/
    ARKUI_KEYCODE_CTRL_RIGHT = 2073,
    /** Caps Lock key **/
    ARKUI_KEYCODE_CAPS_LOCK = 2074,
    /** Scroll Lock key **/
    ARKUI_KEYCODE_SCROLL_LOCK = 2075,
    /** Left Meta key **/
    ARKUI_KEYCODE_META_LEFT = 2076,
    /** Right Meta key **/
    ARKUI_KEYCODE_META_RIGHT = 2077,
    /** Function key **/
    ARKUI_KEYCODE_FUNCTION = 2078,
    /** System Request/Print Screen key **/
    ARKUI_KEYCODE_SYSRQ = 2079,
    /** Break/Pause key **/
    ARKUI_KEYCODE_BREAK = 2080,
    /** Move to Home key **/
    ARKUI_KEYCODE_MOVE_HOME = 2081,
    /** Move to End key **/
    ARKUI_KEYCODE_MOVE_END = 2082,
    /** Insert key **/
    ARKUI_KEYCODE_INSERT = 2083,
    /** Forward key **/
    ARKUI_KEYCODE_FORWARD = 2084,
    /** Play key **/
    ARKUI_KEYCODE_MEDIA_PLAY = 2085,
    /** Pause key **/
    ARKUI_KEYCODE_MEDIA_PAUSE = 2086,
    /** Close key **/
    ARKUI_KEYCODE_MEDIA_CLOSE = 2087,
    /** Eject key **/
    ARKUI_KEYCODE_MEDIA_EJECT = 2088,
    /** Record key **/
    ARKUI_KEYCODE_MEDIA_RECORD = 2089,
    /** F1 key **/
    ARKUI_KEYCODE_F1 = 2090,
    /** F2 key **/
    ARKUI_KEYCODE_F2 = 2091,
    /** F3 key **/
    ARKUI_KEYCODE_F3 = 2092,
    /** F4 key **/
    ARKUI_KEYCODE_F4 = 2093,
    /** F5 key **/
    ARKUI_KEYCODE_F5 = 2094,
    /** F6 key **/
    ARKUI_KEYCODE_F6 = 2095,
    /** F7 key **/
    ARKUI_KEYCODE_F7 = 2096,
    /** F8 key **/
    ARKUI_KEYCODE_F8 = 2097,
    /** F9 key **/
    ARKUI_KEYCODE_F9 = 2098,
    /** F10 key **/
    ARKUI_KEYCODE_F10 = 2099,
    /** F11 key **/
    ARKUI_KEYCODE_F11 = 2100,
    /** F12 key **/
    ARKUI_KEYCODE_F12 = 2101,
    /** Number Lock key on numeric keypad **/
    ARKUI_KEYCODE_NUM_LOCK = 2102,
    /** Key 0 on numeric keypad **/
    ARKUI_KEYCODE_NUMPAD_0 = 2103,
    /** Key 1 on numeric keypad **/
    ARKUI_KEYCODE_NUMPAD_1 = 2104,
    /** Key 2 on numeric keypad **/
    ARKUI_KEYCODE_NUMPAD_2 = 2105,
    /** Key 3 on numeric keypad **/
    ARKUI_KEYCODE_NUMPAD_3 = 2106,
    /** Key 4 on numeric keypad **/
    ARKUI_KEYCODE_NUMPAD_4 = 2107,
    /** Key 5 on numeric keypad **/
    ARKUI_KEYCODE_NUMPAD_5 = 2108,
    /** Key 6 on numeric keypad **/
    ARKUI_KEYCODE_NUMPAD_6 = 2109,
    /** Key 7 on numeric keypad **/
    ARKUI_KEYCODE_NUMPAD_7 = 2110,
    /** Key 8 on numeric keypad **/
    ARKUI_KEYCODE_NUMPAD_8 = 2111,
    /** Key 9 on numeric keypad **/
    ARKUI_KEYCODE_NUMPAD_9 = 2112,
    /** Key / on numeric keypad **/
    ARKUI_KEYCODE_NUMPAD_DIVIDE = 2113,
    /** Key ) on numeric keypad **/
    ARKUI_KEYCODE_NUMPAD_MULTIPLY = 2114,
    /** Key - on numeric keypad **/
    ARKUI_KEYCODE_NUMPAD_SUBTRACT = 2115,
    /** Key + on numeric keypad **/
    ARKUI_KEYCODE_NUMPAD_ADD = 2116,
    /** Key . on numeric keypad **/
    ARKUI_KEYCODE_NUMPAD_DOT = 2117,
    /** Key , on numeric keypad **/
    ARKUI_KEYCODE_NUMPAD_COMMA = 2118,
    /** Enter key on numeric keypad **/
    ARKUI_KEYCODE_NUMPAD_ENTER = 2119,
    /** Key = on numeric keypad **/
    ARKUI_KEYCODE_NUMPAD_EQUALS = 2120,
    /** Key ( on numeric keypad **/
    ARKUI_KEYCODE_NUMPAD_LEFT_PAREN = 2121,
    /** Key ) on numeric keypad **/
    ARKUI_KEYCODE_NUMPAD_RIGHT_PAREN = 2122,
} ArkUI_KeyCode;

/**
 * @brief Defines an enum for the key event types.
 *
 * @since 14
 */
typedef enum {
    /** Unknown type **/
    ARKUI_KEY_EVENT_UNKNOWN = -1,
    /** Pressing of a key **/
    ARKUI_KEY_EVENT_DOWN = 0,
    /** Release of a key **/
    ARKUI_KEY_EVENT_UP = 1,
    /** Long press of a key **/
    ARKUI_KEY_EVENT_LONG_PRESS = 2,
    /** Click of a key **/
    ARKUI_KEY_EVENT_CLICK = 3,
} ArkUI_KeyEventType;

/**
 * @brief Defines an enum for the types of devices that trigger a key event.
 *
 * @since 14
 */
typedef enum {
    /** Unknown type **/
    ARKUI_KEY_SOURCE_UNKNOWN = 0,
    /** Mouse **/
    ARKUI_KEY_SOURCE_TYPE_MOUSE = 1,
    /** Keyboard **/
    ARKUI_KEY_SOURCE_TYPE_KEYBOARD = 4,
} ArkUI_KeySourceType;

/**
 * @brief Defines an enum for key intentions.
 *
 * @since 14
 */
typedef enum {
    /** Unknown intention **/
    ARKUI_KEY_INTENSION_UNKNOWN = -1,
    /**Upward**/
    ARKUI_KEY_INTENSION_UP = 1,
    /** Downward **/
    ARKUI_KEY_INTENSION_DOWN = 2,
    /** Leftward **/
    ARKUI_KEY_INTENSION_LEFT = 3,
    /** Rightward **/
    ARKUI_KEY_INTENSION_RIGHT = 4,
    /** Select **/
    ARKUI_KEY_INTENSION_SELECT = 5,
    /** Escape **/
    ARKUI_KEY_INTENSION_ESCAPE = 6,
    /** Back**/
    ARKUI_KEY_INTENSION_BACK = 7,
    /** Forward **/
    ARKUI_KEY_INTENSION_FORWARD = 8,
    /** Menu **/
    ARKUI_KEY_INTENSION_MENU = 9,
    /** Home **/
    ARKUI_KEY_INTENSION_HOME = 10,
    /** Page up **/
    ARKUI_KEY_INTENSION_PAGE_UP = 11,
    /** Page down **/
    ARKUI_KEY_INTENSION_PAGE_DOWN = 12,
    /** Zoom out **/
    ARKUI_KEY_INTENSION_ZOOM_OUT = 13,
    /** Zoom in **/
    ARKUI_KEY_INTENSION_ZOOM_IN = 14,

    /** Play or pause **/
    ARKUI_KEY_INTENTION_MEDIA_PLAY_PAUSE = 100,
    /** Fast-forward **/
    ARKUI_KEY_INTENTION_MEDIA_FAST_FORWARD = 101,
    /** Fast playback **/
    ARKUI_KEY_INTENTION_MEDIA_FAST_PLAYBACK = 103,
    /** Play next **/
    ARKUI_KEY_INTENTION_MEDIA_NEXT = 104,
    /** Play previous **/
    ARKUI_KEY_INTENTION_MEDIA_PREVIOUS = 105,
    /** Mute **/
    ARKUI_KEY_INTENTION_MEDIA_MUTE = 106,
    /** Volume up **/
    ARKUI_KEY_INTENTION_VOLUME_UP = 107,
    /** Volume down **/
    ARKUI_KEY_INTENTION_VOLUME_DOWN = 108,

    /** Answer a call **/
    ARKUI_KEY_INTENTION_CALL = 200,
    /** Camera **/
    ARKUI_KEY_INTENTION_CAMERA = 300,
} ArkUI_KeyIntension;

/**
 * @brief Obtains the type of a key event.
 *
 * @param event Pointer to an <b>ArkUI_UIInputEvent</b> object.
 * @return Returns the key event type.
 * @since 14
 */
ArkUI_KeyEventType OH_ArkUI_KeyEvent_GetType(const ArkUI_UIInputEvent* event);

/**
 * @brief Obtains the key code from a key event.
 *
 * @param event Pointer to an <b>ArkUI_UIInputEvent</b> object.
 * @return Returns the key code.
 * @since 14
 */
int32_t OH_ArkUI_KeyEvent_GetKeyCode(const ArkUI_UIInputEvent* event);

/**
 * @brief Obtains the key value from a key event.
 *
 * @param event Pointer to an <b>ArkUI_UIInputEvent</b> object.
 * @return Returns the key value.
 * @since 14
 */
const char *OH_ArkUI_KeyEvent_GetKeyText(const ArkUI_UIInputEvent* event);

/**
 * @brief Obtains the type of device that triggers a key event.
 *
 * @param event Pointer to an <b>ArkUI_UIInputEvent</b> object.
 * @return Returns the device type.
 * @since 14
 */
ArkUI_KeySourceType OH_ArkUI_KeyEvent_GetKeySource(const ArkUI_UIInputEvent* event);

/**
 * @brief Prevents a key event from bubbling up.
 *
 * @param event Pointer to an <b>ArkUI_UIInputEvent</b> object.
 * @param stopPropagation Whether to stop event propagation.
 * @since 14
 */
void OH_ArkUI_KeyEvent_StopPropagation(const ArkUI_UIInputEvent* event, bool stopPropagation);

/**
 * @brief Obtains the intention code associated with a key event.
 *
 * @param event Pointer to an <b>ArkUI_UIInputEvent</b> object.
 * @return Returns the intention code associated with the key event.
 * @since 14
 */
ArkUI_KeyIntension OH_ArkUI_KeyEvent_GetKeyIntensionCode(const ArkUI_UIInputEvent* event);

/**
 * @brief Obtains the Unicode value associated with a key event.
 * Non-space basic Latin characters in the 0x0021-0x007E range are supported. Characters with a value of 0 are not
 * supported. In the case of key combination, this API returns the Unicode value of the key corresponding to the key
 * event.
 *
 * @param event Pointer to an <b>ArkUI_UIInputEvent</b> object.
 * @return Returns the Unicode value.
 * @since 14
 */
uint32_t OH_ArkUI_KeyEvent_GetUnicode(const ArkUI_UIInputEvent* event);

/**
 * @brief Sets whether a key event is consumed in the key event callback.
 *
 * @param event Pointer to an <b>ArkUI_UIInputEvent</b> object.
 * @param isConsumed Whether the event is consumed.
 * @since 14
 */
void OH_ArkUI_KeyEvent_SetConsumed(const ArkUI_UIInputEvent* event, bool isConsumed);
#ifdef __cplusplus
};
#endif

#endif // ARKUI_NATIVE_KEY_EVENT_H
/** @} */