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
    ARKUI_KEYCODE_KEY_UNKNOWN = -1,
    /** Function (Fn) key **/
    ARKUI_KEYCODE_KEY_FN = 0,
    /** Function (Home) key **/
    ARKUI_KEYCODE_KEY_HOME = 1,
    /** Back key **/
    ARKUI_KEYCODE_KEY_BACK = 2,
    /** Play/Pause key **/
    ARKUI_KEYCODE_KEY_MEDIA_PLAY_PAUSE = 10,
    /** Stop key **/
    ARKUI_KEYCODE_KEY_MEDIA_STOP = 11,
    /** Next key **/
    ARKUI_KEYCODE_KEY_MEDIA_NEXT = 12,
    /** Previous key **/
    ARKUI_KEYCODE_KEY_MEDIA_PREVIOUS = 13,
    /** Rewind key **/
    ARKUI_KEYCODE_KEY_MEDIA_REWIND = 14,
    /** Fast Forward key **/
    ARKUI_KEYCODE_KEY_MEDIA_FAST_FORWARD = 15,
    /** Volume Up key **/
    ARKUI_KEYCODE_KEY_VOLUME_UP = 16,
    /** Volume Down key **/
    ARKUI_KEYCODE_KEY_VOLUME_DOWN = 17,
    /** Power key **/
    ARKUI_KEYCODE_KEY_POWER = 18,
    /** Shutter key **/
    ARKUI_KEYCODE_KEY_CAMERA = 19,
    /** Speaker Mute key **/
    ARKUI_KEYCODE_KEY_VOLUME_MUTE = 22,

    /** Mute key **/
    ARKUI_KEYCODE_KEY_MUTE = 23,
    /** Brightness Up key **/
    ARKUI_KEYCODE_KEY_BRIGHTNESS_UP = 40,
    /** Brightness Down key **/
    ARKUI_KEYCODE_KEY_BRIGHTNESS_DOWN = 41,
    /** Key 0 **/
    ARKUI_KEYCODE_KEY_0 = 2000,
    /** Key 1 **/
    ARKUI_KEYCODE_KEY_1 = 2001,
    /** Key 2 **/
    ARKUI_KEYCODE_KEY_2 = 2002,
    /** Key 3 **/
    ARKUI_KEYCODE_KEY_3 = 2003,
    /** Key 4 **/
    ARKUI_KEYCODE_KEY_4 = 2004,
    /** Key 5 **/
    ARKUI_KEYCODE_KEY_5 = 2005,
    /** Key 6 **/
    ARKUI_KEYCODE_KEY_6 = 2006,
    /** Key 7 **/
    ARKUI_KEYCODE_KEY_7 = 2007,
    /** Key 8 **/
    ARKUI_KEYCODE_KEY_8 = 2008,
    /** Key 9 **/
    ARKUI_KEYCODE_KEY_9 = 2009,
    /** Key + **/
    ARKUI_KEYCODE_KEY_STAR = 2010,
    /** Key # **/
    ARKUI_KEYCODE_KEY_POUND = 2011,
     /** Up key on D-pad **/
    ARKUI_KEYCODE_KEY_DPAD_UP = 2012,
    /** Down key on D-pad **/
    ARKUI_KEYCODE_KEY_DPAD_DOWN = 2013,
    /** Left key on D-pad **/
    ARKUI_KEYCODE_KEY_DPAD_LEFT = 2014,
    /** Right key on D-pad **/
    ARKUI_KEYCODE_KEY_DPAD_RIGHT = 2015,
    /** OK key on D-pad **/
    ARKUI_KEYCODE_KEY_DPAD_CENTER = 2016,
    /** Key A **/
    ARKUI_KEYCODE_KEY_A = 2017,
    /** Key B **/
    ARKUI_KEYCODE_KEY_B = 2018,
    /** Key C **/
    ARKUI_KEYCODE_KEY_C = 2019,
    /** Key D **/
    ARKUI_KEYCODE_KEY_D = 2020,
    /** Key E **/
    ARKUI_KEYCODE_KEY_E = 2021,
    /** Key F **/
    ARKUI_KEYCODE_KEY_F = 2022,
    /** Key G **/
    ARKUI_KEYCODE_KEY_G = 2023,
    /** Key H **/
    ARKUI_KEYCODE_KEY_H = 2024,
    /** Key I **/
    ARKUI_KEYCODE_KEY_I = 2025,
    /** Key J **/
    ARKUI_KEYCODE_KEY_J = 2026,
    /** Key K **/
    ARKUI_KEYCODE_KEY_K = 2027,
    /** Key L **/
    ARKUI_KEYCODE_KEY_L = 2028,
    /** Key M **/
    ARKUI_KEYCODE_KEY_M = 2029,
    /** Key N **/
    ARKUI_KEYCODE_KEY_N = 2030,
    /** Key O **/
    ARKUI_KEYCODE_KEY_O = 2031,
    /** Key P **/
    ARKUI_KEYCODE_KEY_P = 2032,
    /** Key R **/
    ARKUI_KEYCODE_KEY_Q = 2033,
    /** Key R **/
    ARKUI_KEYCODE_KEY_R = 2034,
    /** Key S **/
    ARKUI_KEYCODE_KEY_S = 2035,
    /** Key T **/
    ARKUI_KEYCODE_KEY_T = 2036,
    /** Key U **/
    ARKUI_KEYCODE_KEY_U = 2037,
    /** Key V **/
    ARKUI_KEYCODE_KEY_V = 2038,
    /** Key W **/
    ARKUI_KEYCODE_KEY_W = 2039,
    /** Key X **/
    ARKUI_KEYCODE_KEY_X = 2040,
    /** Key Y **/
    ARKUI_KEYCODE_KEY_Y = 2041,
    /** Key Z **/
    ARKUI_KEYCODE_KEY_Z = 2042,
    /** Key # **/
    ARKUI_KEYCODE_KEY_COMMA = 2043,
    /** Key # **/
    ARKUI_KEYCODE_KEY_PERIOD = 2044,
    /** Left Alt key **/
    ARKUI_KEYCODE_KEY_ALT_LEFT = 2045,
    /** Right Alt key **/
    ARKUI_KEYCODE_KEY_ALT_RIGHT = 2046,
    /** Left Shift key **/
    ARKUI_KEYCODE_KEY_SHIFT_LEFT = 2047,
    /** Right Shift key **/
    ARKUI_KEYCODE_KEY_SHIFT_RIGHT = 2048,
    /** Tab key **/
    ARKUI_KEYCODE_KEY_TAB = 2049,
    /** Space key **/
    ARKUI_KEYCODE_KEY_SPACE = 2050,
    /** Symbol key **/
    ARKUI_KEYCODE_KEY_SYM = 2051,
    /** Explorer key, used to start the explorer application **/
    ARKUI_KEYCODE_KEY_EXPLORER = 2052,
    /** Email key, used to start the email application **/
    ARKUI_KEYCODE_KEY_ENVELOPE = 2053,
    /** Enter key **/
    ARKUI_KEYCODE_KEY_ENTER = 2054,
    /** Backspace key **/
    ARKUI_KEYCODE_KEY_DEL = 2055,
    /** Key ` **/
    ARKUI_KEYCODE_KEY_GRAVE = 2056,
    /** Key - **/
    ARKUI_KEYCODE_KEY_MINUS = 2057,
    /** Key = **/
    ARKUI_KEYCODE_KEY_EQUALS = 2058,
    /** Key [ **/
    ARKUI_KEYCODE_KEY_LEFT_BRACKET = 2059,
    /** Key ]**/
    ARKUI_KEYCODE_KEY_RIGHT_BRACKET = 2060,
    /** Key \\ **/
    ARKUI_KEYCODE_KEY_BACKSLASH = 2061,
    /** Key ; **/
    ARKUI_KEYCODE_KEY_SEMICOLON = 2062,
    /** Key ' **/
    ARKUI_KEYCODE_KEY_APOSTROPHE = 2063,
    /** Key / **/
    ARKUI_KEYCODE_KEY_SLASH = 2064,
    /** Key @ **/
    ARKUI_KEYCODE_KEY_AT = 2065,
    /** Key + **/
    ARKUI_KEYCODE_KEY_PLUS = 2066,
    /** Menu key **/
    ARKUI_KEYCODE_KEY_MENU = 2067,
    /** Page Up key **/
    ARKUI_KEYCODE_KEY_PAGE_UP = 2068,
    /** Page Down key **/
    ARKUI_KEYCODE_KEY_PAGE_DOWN = 2069,
    /** ESC key **/
    ARKUI_KEYCODE_KEY_ESCAPE = 2070,
    /** Delete key **/
    ARKUI_KEYCODE_KEY_FORWARD_DEL = 2071,
    /** Left Ctrl key **/
    ARKUI_KEYCODE_KEY_CTRL_LEFT = 2072,
    /** Right Ctrl key **/
    ARKUI_KEYCODE_KEY_CTRL_RIGHT = 2073,
    /** Caps Lock key **/
    ARKUI_KEYCODE_KEY_CAPS_LOCK = 2074,
    /** Scroll Lock key **/
    ARKUI_KEYCODE_KEY_SCROLL_LOCK = 2075,
    /** Left Meta key **/
    ARKUI_KEYCODE_KEY_META_LEFT = 2076,
    /** Right Meta key **/
    ARKUI_KEYCODE_KEY_META_RIGHT = 2077,
    /** Function key **/
    ARKUI_KEYCODE_KEY_FUNCTION = 2078,
    /** System Request/Print Screen key **/
    ARKUI_KEYCODE_KEY_SYSRQ = 2079,
    /** Break/Pause key **/
    ARKUI_KEYCODE_KEY_BREAK = 2080,
    /** Move to Home key **/
    ARKUI_KEYCODE_KEY_MOVE_HOME = 2081,
    /** Move to End key **/
    ARKUI_KEYCODE_KEY_MOVE_END = 2082,
    /** Insert key **/
    ARKUI_KEYCODE_KEY_INSERT = 2083,
    /** Forward key **/
    ARKUI_KEYCODE_KEY_FORWARD = 2084,
    /** Play key **/
    ARKUI_KEYCODE_KEY_MEDIA_PLAY = 2085,
    /** Pause key **/
    ARKUI_KEYCODE_KEY_MEDIA_PAUSE = 2086,
    /** Close key **/
    ARKUI_KEYCODE_KEY_MEDIA_CLOSE = 2087,
    /** Eject key **/
    ARKUI_KEYCODE_KEY_MEDIA_EJECT = 2088,
    /** Record key **/
    ARKUI_KEYCODE_KEY_MEDIA_RECORD = 2089,
    /** F1 key **/
    ARKUI_KEYCODE_KEY_F1 = 2090,
    /** F2 key **/
    ARKUI_KEYCODE_KEY_F2 = 2091,
    /** F3 key **/
    ARKUI_KEYCODE_KEY_F3 = 2092,
    /** F4 key **/
    ARKUI_KEYCODE_KEY_F4 = 2093,
    /** F5 key **/
    ARKUI_KEYCODE_KEY_F5 = 2094,
    /** F6 key **/
    ARKUI_KEYCODE_KEY_F6 = 2095,
    /** F7 key **/
    ARKUI_KEYCODE_KEY_F7 = 2096,
    /** F8 key **/
    ARKUI_KEYCODE_KEY_F8 = 2097,
    /** F9 key **/
    ARKUI_KEYCODE_KEY_F9 = 2098,
    /** F10 key **/
    ARKUI_KEYCODE_KEY_F10 = 2099,
    /** F11 key **/
    ARKUI_KEYCODE_KEY_F11 = 2100,
    /** F12 key **/
    ARKUI_KEYCODE_KEY_F12 = 2101,
    /** Number Lock key on numeric keypad **/
    ARKUI_KEYCODE_KEY_NUM_LOCK = 2102,
    /** Key 0 on numeric keypad **/
    ARKUI_KEYCODE_KEY_NUMPAD_0 = 2103,
    /** Key 1 on numeric keypad **/
    ARKUI_KEYCODE_KEY_NUMPAD_1 = 2104,
    /** Key 2 on numeric keypad **/
    ARKUI_KEYCODE_KEY_NUMPAD_2 = 2105,
    /** Key 3 on numeric keypad **/
    ARKUI_KEYCODE_KEY_NUMPAD_3 = 2106,
    /** Key 4 on numeric keypad **/
    ARKUI_KEYCODE_KEY_NUMPAD_4 = 2107,
    /** Key 5 on numeric keypad **/
    ARKUI_KEYCODE_KEY_NUMPAD_5 = 2108,
    /** Key 6 on numeric keypad **/
    ARKUI_KEYCODE_KEY_NUMPAD_6 = 2109,
    /** Key 7 on numeric keypad **/
    ARKUI_KEYCODE_KEY_NUMPAD_7 = 2110,
    /** Key 8 on numeric keypad **/
    ARKUI_KEYCODE_KEY_NUMPAD_8 = 2111,
    /** Key 9 on numeric keypad **/
    ARKUI_KEYCODE_KEY_NUMPAD_9 = 2112,
    /** Key / on numeric keypad **/
    ARKUI_KEYCODE_KEY_NUMPAD_DIVIDE = 2113,
    /** Key ) on numeric keypad **/
    ARKUI_KEYCODE_KEY_NUMPAD_MULTIPLY = 2114,
    /** Key - on numeric keypad **/
    ARKUI_KEYCODE_KEY_NUMPAD_SUBTRACT = 2115,
    /** Key + on numeric keypad **/
    ARKUI_KEYCODE_KEY_NUMPAD_ADD = 2116,
    /** Key . on numeric keypad **/
    ARKUI_KEYCODE_KEY_NUMPAD_DOT = 2117,
    /** Key , on numeric keypad **/
    ARKUI_KEYCODE_KEY_NUMPAD_COMMA = 2118,
    /** Enter key on numeric keypad **/
    ARKUI_KEYCODE_KEY_NUMPAD_ENTER = 2119,
    /** Key = on numeric keypad **/
    ARKUI_KEYCODE_KEY_NUMPAD_EQUALS = 2120,
    /** Key ( on numeric keypad **/
    ARKUI_KEYCODE_KEY_NUMPAD_LEFT_PAREN = 2121,
    /** Key ) on numeric keypad **/
    ARKUI_KEYCODE_KEY_NUMPAD_RIGHT_PAREN = 2122,

    /** Multi-task key **/
    ARKUI_KEYCODE_KEY_VIRTUAL_MULTITASK = 2210,
    /** Sleep key **/
    ARKUI_KEYCODE_KEY_SLEEP = 2600,
    /** Zenkaku/Hankaku key **/
    ARKUI_KEYCODE_KEY_ZENKAKU_HANKAKU = 2601,
    /** 102nd key **/
    ARKUI_KEYCODE_KEY_102ND = 2602,
    /** Ro key **/
    ARKUI_KEYCODE_KEY_RO = 2603,
    /** Katakana key **/
    ARKUI_KEYCODE_KEY_KATAKANA = 2604,
    /** Hiragana key **/
    ARKUI_KEYCODE_KEY_HIRAGANA = 2605,
    /** Henkan key **/
    ARKUI_KEYCODE_KEY_HENKAN = 2606,
    /** Katakana/Hiragana key **/
    ARKUI_KEYCODE_KEY_KATAKANA_HIRAGANA = 2607,
    /** Muhenkan key **/
    ARKUI_KEYCODE_KEY_MUHENKAN = 2608,
    /** Linefeed key **/
    ARKUI_KEYCODE_KEY_LINEFEED = 2609,
    /** Macro key **/
    ARKUI_KEYCODE_KEY_MACRO = 2610,
    /** Plus/Minus key on the numeric keypad **/
    ARKUI_KEYCODE_KEY_NUMPAD_PLUSMINUS = 2611,
    /** Scale key **/
    ARKUI_KEYCODE_KEY_SCALE = 2612,
    /** Hanguel key **/
    ARKUI_KEYCODE_KEY_HANGUEL = 2613,
    /** Hanja key **/
    ARKUI_KEYCODE_KEY_HANJA = 2614,
    /** Yen key **/
    ARKUI_KEYCODE_KEY_YEN = 2615,
    /** Stop key **/
    ARKUI_KEYCODE_KEY_STOP = 2616,
    /** Again key **/
    ARKUI_KEYCODE_KEY_AGAIN = 2617,
    /** Props key **/
    ARKUI_KEYCODE_KEY_PROPS = 2618,
    /** Undo key **/
    ARKUI_KEYCODE_KEY_UNDO = 2619,
    /** Copy key **/
    ARKUI_KEYCODE_KEY_COPY = 2620,
    /** Open key **/
    ARKUI_KEYCODE_KEY_OPEN = 2621,
    /** Paste key **/
    ARKUI_KEYCODE_KEY_PASTE = 2622,
    /** Find key **/
    ARKUI_KEYCODE_KEY_FIND = 2623,
    /** Cut key **/
    ARKUI_KEYCODE_KEY_CUT = 2624,
    /** Help key **/
    ARKUI_KEYCODE_KEY_HELP = 2625,
    /** Calc key, used to start the calculator application **/
    ARKUI_KEYCODE_KEY_CALC = 2626,
    /** File key **/
    ARKUI_KEYCODE_KEY_FILE = 2627,
    /** Bookmarks key **/
    ARKUI_KEYCODE_KEY_BOOKMARKS = 2628,
    /** Next key **/
    ARKUI_KEYCODE_KEY_NEXT = 2629,
    /** Play/Pause key **/
    ARKUI_KEYCODE_KEY_PLAYPAUSE = 2630,
    /** Previous key **/
    ARKUI_KEYCODE_KEY_PREVIOUS = 2631,
    /** Stop CD key **/
    ARKUI_KEYCODE_KEY_STOPCD = 2632,
    /** Config key **/
    ARKUI_KEYCODE_KEY_CONFIG = 2634,
    /** Refresh key **/
    ARKUI_KEYCODE_KEY_REFRESH = 2635,
    /** Exit key **/
    ARKUI_KEYCODE_KEY_EXIT = 2636,
    /** Edit key **/
    ARKUI_KEYCODE_KEY_EDIT = 2637,
    /** Scroll Up key **/
    ARKUI_KEYCODE_KEY_SCROLLUP = 2638,
    /** Scroll Down key **/
    ARKUI_KEYCODE_KEY_SCROLLDOWN = 2639,
    /** New key **/
    ARKUI_KEYCODE_KEY_NEW = 2640,
    /** Redo key **/
    ARKUI_KEYCODE_KEY_REDO = 2641,
    /** Close key **/
    ARKUI_KEYCODE_KEY_CLOSE = 2642,
    /** Play key **/
    ARKUI_KEYCODE_KEY_PLAY = 2643,
    /** Bass Boost key **/
    ARKUI_KEYCODE_KEY_BASSBOOST = 2644,
    /** Print key **/
    ARKUI_KEYCODE_KEY_PRINT = 2645,
    /** Chat key **/
    ARKUI_KEYCODE_KEY_CHAT = 2646,
    /** Finance key **/
    ARKUI_KEYCODE_KEY_FINANCE = 2647,
    /** Cancel key **/
    ARKUI_KEYCODE_KEY_CANCEL = 2648,
    /** Keyboard Illumination Toggle key **/
    ARKUI_KEYCODE_KEY_KBDILLUM_TOGGLE = 2649,
    /** Keyboard Illumination Up key **/
    ARKUI_KEYCODE_KEY_KBDILLUM_DOWN = 2650,
    /** Keyboard Illumination Down key **/
    ARKUI_KEYCODE_KEY_KBDILLUM_UP = 2651,
    /** Send key **/
    ARKUI_KEYCODE_KEY_SEND = 2652,
    /** Reply key **/
    ARKUI_KEYCODE_KEY_REPLY = 2653,
    /** Forward Mail key **/
    ARKUI_KEYCODE_KEY_FORWARDMAIL = 2654,
    /** Save key **/
    ARKUI_KEYCODE_KEY_SAVE = 2655,
    /** Documents key **/
    ARKUI_KEYCODE_KEY_DOCUMENTS = 2656,
    /** Next Video key **/
    ARKUI_KEYCODE_KEY_VIDEO_NEXT = 2657,
    /** Previous Video key **/
    ARKUI_KEYCODE_KEY_VIDEO_PREV = 2658,
    /** Brightness Cycle key **/
    ARKUI_KEYCODE_KEY_BRIGHTNESS_CYCLE = 2659,
    /** Brightness Zero key **/
    ARKUI_KEYCODE_KEY_BRIGHTNESS_ZERO = 2660,
    /** Display Off key **/
    ARKUI_KEYCODE_KEY_DISPLAY_OFF = 2661,
    /** Misc Button key **/
    ARKUI_KEYCODE_KEY_BTN_MISC = 2662,
    /** Goto key **/
    ARKUI_KEYCODE_KEY_GOTO = 2663,
    /** Info key **/
    ARKUI_KEYCODE_KEY_INFO = 2664,
    /** Program key **/
    ARKUI_KEYCODE_KEY_PROGRAM = 2665,
    /** PVR key **/
    ARKUI_KEYCODE_KEY_PVR = 2666,
    /** Subtitle key **/
    ARKUI_KEYCODE_KEY_SUBTITLE = 2667,
    /** Full Screen key **/
    ARKUI_KEYCODE_KEY_FULL_SCREEN = 2668,
    /** Keyboard **/
    ARKUI_KEYCODE_KEY_KEYBOARD = 2669,
    /** Aspect Ratio key **/
    ARKUI_KEYCODE_KEY_ASPECT_RATIO = 2670,
    /** Port Control key **/
    ARKUI_KEYCODE_KEY_PC = 2671,
    /** TV key **/
    ARKUI_KEYCODE_KEY_TV = 2672,
    /** TV key 2 **/
    ARKUI_KEYCODE_KEY_TV2 = 2673,
    /** VCR key 1 **/
    ARKUI_KEYCODE_KEY_VCR = 2674,
    /** VCR key 2 **/
    ARKUI_KEYCODE_KEY_VCR2 = 2675,
    /** SAT key **/
    ARKUI_KEYCODE_KEY_SAT = 2676,
    /** CD key **/
    ARKUI_KEYCODE_KEY_CD = 2677,
    /** Tape key **/
    ARKUI_KEYCODE_KEY_TAPE = 2678,
    /** Tuner key **/
    ARKUI_KEYCODE_KEY_TUNER = 2679,
    /** Player key **/
    ARKUI_KEYCODE_KEY_PLAYER = 2680,
    /** DVD key **/
    ARKUI_KEYCODE_KEY_DVD = 2681,
    /** Audio key **/
    ARKUI_KEYCODE_KEY_AUDIO = 2682,
    /** Video key **/
    ARKUI_KEYCODE_KEY_VIDEO = 2683,
    /** Memo key **/
    ARKUI_KEYCODE_KEY_MEMO = 2684,
    /** Calendar key **/
    ARKUI_KEYCODE_KEY_CALENDAR = 2685,
    /** Red indicator **/
    ARKUI_KEYCODE_KEY_RED = 2686,
    /** Green indicator **/
    ARKUI_KEYCODE_KEY_GREEN = 2687,
    /** Yellow indicator **/
    ARKUI_KEYCODE_KEY_YELLOW = 2688,
    /** Blue indicator **/
    ARKUI_KEYCODE_KEY_BLUE = 2689,
    /** Channel Up key **/
    ARKUI_KEYCODE_KEY_CHANNELUP = 2690,
    /** Channel Down key **/
    ARKUI_KEYCODE_KEY_CHANNELDOWN = 2691,
    /** Last key **/
    ARKUI_KEYCODE_KEY_LAST = 2692,
    /** Restart key **/
    ARKUI_KEYCODE_KEY_RESTART = 2693,
    /** Slow key **/
    ARKUI_KEYCODE_KEY_SLOW = 2694,
    /** Shuffle key **/
    ARKUI_KEYCODE_KEY_SHUFFLE = 2695,
    /** Videophone key **/
    ARKUI_KEYCODE_KEY_VIDEOPHONE = 2696,
    /** Games key **/
    ARKUI_KEYCODE_KEY_GAMES = 2697,
    /** Zoom In key **/
    ARKUI_KEYCODE_KEY_ZOOMIN = 2698,
    /** Zoom Out key **/
    ARKUI_KEYCODE_KEY_ZOOMOUT = 2699,
    /** Zoom Reset key **/
    ARKUI_KEYCODE_KEY_ZOOMRESET = 2700,
    /** Word Processor key **/
    ARKUI_KEYCODE_KEY_WORDPROCESSOR = 2701,
    /** Editor key **/
    ARKUI_KEYCODE_KEY_EDITOR = 2702,
    /** Spreadsheet key **/
    ARKUI_KEYCODE_KEY_SPREADSHEET = 2703,
    /** Graphics Editor key **/
    ARKUI_KEYCODE_KEY_GRAPHICSEDITOR = 2704,
    /** Presentation key **/
    ARKUI_KEYCODE_KEY_PRESENTATION = 2705,
    /** Database key **/
    ARKUI_KEYCODE_KEY_DATABASE = 2706,
    /** News key **/
    ARKUI_KEYCODE_KEY_NEWS = 2707,
    /** Voice mailbox **/
    ARKUI_KEYCODE_KEY_VOICEMAIL = 2708,
    /** Address book key **/
    ARKUI_KEYCODE_KEY_ADDRESSBOOK = 2709,
    /** Messenger key **/
    ARKUI_KEYCODE_KEY_MESSENGER = 2710,
    /** Brightness Toggle key **/
    ARKUI_KEYCODE_KEY_BRIGHTNESS_TOGGLE = 2711,
    /** Media Repeat key **/
    ARKUI_KEYCODE_KEY_SPELLCHECK = 2712,
    /** Coffee key, used to launch screen lock or screen saver **/
    ARKUI_KEYCODE_KEY_COFFEE = 2713,
    /** Media Repeat key **/
    ARKUI_KEYCODE_KEY_MEDIA_REPEAT = 2714,
    /** Images key **/
    ARKUI_KEYCODE_KEY_IMAGES = 2715,
    /** Button Configuration key **/
    ARKUI_KEYCODE_KEY_BUTTONCONFIG = 2716,
    /** Task Manager key **/
    ARKUI_KEYCODE_KEY_TASKMANAGER = 2717,
    /** Log key **/
    ARKUI_KEYCODE_KEY_JOURNAL = 2718,
    /** Control Panel key **/
    ARKUI_KEYCODE_KEY_CONTROLPANEL = 2719,
    /** App Select key **/
    ARKUI_KEYCODE_KEY_APPSELECT = 2720,
    /** Screen Saver key **/
    ARKUI_KEYCODE_KEY_SCREENSAVER = 2721,
    /** Assistant key **/
    ARKUI_KEYCODE_KEY_ASSISTANT = 2722,
    /** Next Keyboard Layout key **/
    ARKUI_KEYCODE_KEY_KBD_LAYOUT_NEXT = 2723,
    /** Min Brightness key **/
    ARKUI_KEYCODE_KEY_BRIGHTNESS_MIN = 2724,
    /** Max Brightness key **/
    ARKUI_KEYCODE_KEY_BRIGHTNESS_MAX = 2725,
    /** Keyboard Input-assisted Previous key **/
    ARKUI_KEYCODE_KEY_KBDINPUTASSIST_PREV = 2726,
    /** Keyboard Input-assisted Next key **/
    ARKUI_KEYCODE_KEY_KBDINPUTASSIST_NEXT = 2727,
    /** Keyboard Input-assisted Previous key **/
    ARKUI_KEYCODE_KEY_KBDINPUTASSIST_PREVGROUP = 2728,
    /** Keyboard Input-assisted Next key **/
    ARKUI_KEYCODE_KEY_KBDINPUTASSIST_NEXTGROUP = 2729,
    /** Assist_Accept key **/
    ARKUI_KEYCODE_KEY_KBDINPUTASSIST_ACCEPT = 2730,
    /** Assist_Cancel key **/
    ARKUI_KEYCODE_KEY_KBDINPUTASSIST_CANCEL = 2731,
    /** Front key, used to launch the windshield defogger **/
    ARKUI_KEYCODE_KEY_FRONT = 2800,
    /** Setup key **/
    ARKUI_KEYCODE_KEY_SETUP = 2801,
    /** Wakeup key **/
    ARKUI_KEYCODE_KEY_WAKEUP = 2802,
    /** Send File key **/
    ARKUI_KEYCODE_KEY_SENDFILE = 2803,
    /** Delete File key **/
    ARKUI_KEYCODE_KEY_DELETEFILE = 2804,
    /** XFER key, used to start file transfer **/
    ARKUI_KEYCODE_KEY_XFER = 2805,
    /** Program key 1 **/
    ARKUI_KEYCODE_KEY_PROG1 = 2806,
    /** Program key 2 **/
    ARKUI_KEYCODE_KEY_PROG2 = 2807,
    /** MS-DOS key **/
    ARKUI_KEYCODE_KEY_MSDOS = 2808,
    /** Screen Lock key **/
    ARKUI_KEYCODE_KEY_SCREENLOCK = 2809,
    /** Directional Rotation Display key **/
    ARKUI_KEYCODE_KEY_DIRECTION_ROTATE_DISPLAY = 2810,
    /** Windows Cycle key **/
    ARKUI_KEYCODE_KEY_CYCLEWINDOWS = 2811,
    /** Key **/
    ARKUI_KEYCODE_KEY_COMPUTER = 2812,
    /** Eject CD key **/
    ARKUI_KEYCODE_KEY_EJECTCLOSECD = 2813,
    /** ISO key **/
    ARKUI_KEYCODE_KEY_ISO = 2814,
    /** Move key **/
    ARKUI_KEYCODE_KEY_MOVE = 2815,
    /** F13 key **/
    ARKUI_KEYCODE_KEY_F13 = 2816,
    /** F14 key **/
    ARKUI_KEYCODE_KEY_F14 = 2817,
    /** F15 key **/
    ARKUI_KEYCODE_KEY_F15 = 2818,
    /** F16 key **/
    ARKUI_KEYCODE_KEY_F16 = 2819,
    /** F17 key **/
    ARKUI_KEYCODE_KEY_F17 = 2820,
    /** F18 key **/
    ARKUI_KEYCODE_KEY_F18 = 2821,
    /** F19 key **/
    ARKUI_KEYCODE_KEY_F19 = 2822,
    /** F20 key **/
    ARKUI_KEYCODE_KEY_F20 = 2823,
    /** F21 key **/
    ARKUI_KEYCODE_KEY_F21 = 2824,
    /** F22 key **/
    ARKUI_KEYCODE_KEY_F22 = 2825,
    /** F23 key **/
    ARKUI_KEYCODE_KEY_F23 = 2826,
    /** F24 key **/
    ARKUI_KEYCODE_KEY_F24 = 2827,
    /** Program key 3 **/
    ARKUI_KEYCODE_KEY_PROG3 = 2828,
    /** Program key 4 **/
    ARKUI_KEYCODE_KEY_PROG4 = 2829,
    /** Dashboard **/
    ARKUI_KEYCODE_KEY_DASHBOARD = 2830,
    /** Suspend key **/
    ARKUI_KEYCODE_KEY_SUSPEND = 2831,
    /** HP key **/
    ARKUI_KEYCODE_KEY_HP = 2832,
    /** Sound key **/
    ARKUI_KEYCODE_KEY_SOUND = 2833,
    /** Question key **/
    ARKUI_KEYCODE_KEY_QUESTION = 2834,
    /** Connect key **/
    ARKUI_KEYCODE_KEY_CONNECT = 2836,
    /** Sport key **/
    ARKUI_KEYCODE_KEY_SPORT = 2837,
    /** Shop key **/
    ARKUI_KEYCODE_KEY_SHOP = 2838,
    /** Alternate key **/
    ARKUI_KEYCODE_KEY_ALTERASE = 2839,
    /** Switch Video Mode key (monitor, LCD, and TV, etc.) **/
    ARKUI_KEYCODE_KEY_SWITCHVIDEOMODE = 2841,
    /** Battery key **/
    ARKUI_KEYCODE_KEY_BATTERY = 2842,
    /** Bluetooth key **/
    ARKUI_KEYCODE_KEY_BLUETOOTH = 2843,
    /** WLAN key **/
    ARKUI_KEYCODE_KEY_WLAN = 2844,
    /** Ultra-wideband key **/
    ARKUI_KEYCODE_KEY_UWB = 2845,
    /** WWAN WiMAX key **/
    ARKUI_KEYCODE_KEY_WWAN_WIMAX = 2846,
    /** RF Kill key **/
    ARKUI_KEYCODE_KEY_RFKILL = 2847,
    /** Channel key **/
    ARKUI_KEYCODE_KEY_CHANNEL = 3001,
    /** Button 0 **/
    ARKUI_KEYCODE_KEY_BTN_0 = 3100,
    /** Button 1 **/
    ARKUI_KEYCODE_KEY_BTN_1 = 3101,
    /** Button 2 **/
    ARKUI_KEYCODE_KEY_BTN_2 = 3102,
    /** Button 3 **/
    ARKUI_KEYCODE_KEY_BTN_3 = 3103,
    /** Button 4 **/
    ARKUI_KEYCODE_KEY_BTN_4 = 3104,
    /** Button 5 **/
    ARKUI_KEYCODE_KEY_BTN_5 = 3105,
    /** Button 6 **/
    ARKUI_KEYCODE_KEY_BTN_6 = 3106,
    /** Button 7 **/
    ARKUI_KEYCODE_KEY_BTN_7 = 3107,
    /** Button 8 **/
    ARKUI_KEYCODE_KEY_BTN_8 = 3108,
    /** Button 9 **/
    ARKUI_KEYCODE_KEY_BTN_9 = 3109,
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
    /** Touchscreen **/
    ARKUI_KEY_SOURCE_TYPE_TOUCH = 2,
    /** Touchpad **/
    ARKUI_KEY_SOURCE_TYPE_TOUCH_PAD = 3,
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
    /** Rewind **/
    ARKUI_KEY_INTENTION_MEDIA_FAST_REWIND = 102,
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
    /** End a call **/
    ARKUI_KEY_INTENTION_ENDCALL = 201,
    /** Reject a call **/
    ARKUI_KEY_INTENTION_REJECTCALL = 202,
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
ArkUI_KeyCode OH_ArkUI_KeyEvent_GetKeyCode(const ArkUI_UIInputEvent* event);

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
 * @brief Obtains the ID of device that triggers a key event.
 *
 * @param event Pointer to an <b>ArkUI_UIInputEvent</b> object.
 * @return Returns the device ID.
 * @since 14
 */
int32_t OH_ArkUI_KeyEvent_GetDeviceId(const ArkUI_UIInputEvent* event);

/**
 * @brief Obtains the state of the meta key (that is, the <b>WIN</b> key on the Windows keyboard or the <b>Command</b>
 *        key on the Mac keyboard) when a key event occurs.
 *
 * @param event Pointer to an <b>ArkUI_UIInputEvent</b> object.
 * @return Returns the state of the meta key. The value <b>1</b> means that the key is pressed, and <b>0</b> means the
 *         opposite.
 * @since 14
 */
int32_t OH_ArkUI_KeyEvent_GetMetaKey(const ArkUI_UIInputEvent* event);

/**
 * @brief Obtains the timestamp of a key event. It is the interval between the time when the event is triggered and the
 *        time when the system starts, in nanoseconds.
 *
 * @param event Pointer to an <b>ArkUI_UIInputEvent</b> object.
 * @return Returns the event timestamp, in nanoseconds.
 * @since 14
 */
uint64_t OH_ArkUI_KeyEvent_GetTimestamp(const ArkUI_UIInputEvent* event);

/**
 * @brief Prevents a key event from bubbling up.
 *
 * @param event Pointer to an <b>ArkUI_UIInputEvent</b> object.
 * @param stopPropagation Whether to stop event propagation.
 * @since 14
 */
void OH_ArkUI_KeyEvent_StopPropagation(const ArkUI_UIInputEvent* event, bool stopPropagation);

/**
 * @brief Obtains the pressed status of modifier keys from a key event.
 * The following modifier keys are supported: Ctrl, Alt, Shift, Fn. However, the <b>Fn</b> key on external keyboards
 * is not supported.
 *
 * @param event Pointer to an <b>ArkUI_UIInputEvent</b> object.
 * @param modifierKeys Modifier keys to check, which must be created using {@link ArkUI_ModifierKeyName}.
 * @return Returns whether the pressed status of the modifier keys.
 * @since 14
 */
bool OH_ArkUI_KeyEvent_GetModifierKeyState(const ArkUI_UIInputEvent* event, uint32_t modifierKeys);

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