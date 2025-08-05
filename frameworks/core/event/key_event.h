/*
 * Copyright (c) 2021-2023 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_EVENT_KEY_EVENT_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_EVENT_KEY_EVENT_H

#include <map>

#include "core/event/ace_events.h"
#include "core/event/focus_axis_event.h"
#include "core/event/non_pointer_event.h"

namespace OHOS::MMI {
class KeyEvent;
}

namespace OHOS::Ace {
enum class ModifierKeyName {
    /** Ctrl. */
    ModifierKeyCtrl = 1 << 0,
    /** Shift. */
    ModifierKeyShift = 1 << 1,
    /** Alt. */
    ModifierKeyAlt = 1 << 2,
    /** Fn. */
    ModifierKeyFn = 1 << 3,
};

uint64_t CalculateModifierKeyState(const std::vector<OHOS::Ace::KeyCode>& status);

enum class KeyCode : int32_t {
    KEY_UNKNOWN = -1,
    KEY_FN = 0, // New
    KEY_HOME = 1,
    KEY_BACK = 2,
    KEY_CALL = 3,
    KEY_ENDCALL = 4,
    KEY_CLEAR = 5,
    KEY_HEADSETHOOK = 6,
    KEY_FOCUS = 7,
    KEY_NOTIFICATION = 8,
    KEY_SEARCH = 9,
    KEY_MEDIA_PLAY_PAUSE = 10,
    KEY_MEDIA_STOP = 11,
    KEY_MEDIA_NEXT = 12,
    KEY_MEDIA_PREVIOUS = 13,
    KEY_MEDIA_REWIND = 14,
    KEY_MEDIA_FAST_FORWARD = 15,
    KEY_VOLUME_UP = 16,
    KEY_VOLUME_DOWN = 17,
    KEY_POWER = 18,
    KEY_CAMERA = 19,
    KEY_VOICE_ASSISTANT = 20,
    KEY_CUSTOM1 = 21,
    KEY_VOLUME_MUTE = 22, // New
    KEY_MUTE = 23,        // New
    KEY_BRIGHTNESS_UP = 40,
    KEY_BRIGHTNESS_DOWN = 41,
    KEY_WEAR_1 = 1001,
    KEY_0 = 2000,
    KEY_1 = 2001,
    KEY_2 = 2002,
    KEY_3 = 2003,
    KEY_4 = 2004,
    KEY_5 = 2005,
    KEY_6 = 2006,
    KEY_7 = 2007,
    KEY_8 = 2008,
    KEY_9 = 2009,
    KEY_STAR = 2010,
    KEY_POUND = 2011,
    KEY_DPAD_UP = 2012,
    KEY_DPAD_DOWN = 2013,
    KEY_DPAD_LEFT = 2014,
    KEY_DPAD_RIGHT = 2015,
    KEY_DPAD_CENTER = 2016,
    KEY_A = 2017,
    KEY_B = 2018,
    KEY_C = 2019,
    KEY_D = 2020,
    KEY_E = 2021,
    KEY_F = 2022,
    KEY_G = 2023,
    KEY_H = 2024,
    KEY_I = 2025,
    KEY_J = 2026,
    KEY_K = 2027,
    KEY_L = 2028,
    KEY_M = 2029,
    KEY_N = 2030,
    KEY_O = 2031,
    KEY_P = 2032,
    KEY_Q = 2033,
    KEY_R = 2034,
    KEY_S = 2035,
    KEY_T = 2036,
    KEY_U = 2037,
    KEY_V = 2038,
    KEY_W = 2039,
    KEY_X = 2040,
    KEY_Y = 2041,
    KEY_Z = 2042,
    KEY_COMMA = 2043,
    KEY_PERIOD = 2044,
    KEY_ALT_LEFT = 2045,
    KEY_ALT_RIGHT = 2046,
    KEY_SHIFT_LEFT = 2047,
    KEY_SHIFT_RIGHT = 2048,
    KEY_TAB = 2049,
    KEY_SPACE = 2050,
    KEY_SYM = 2051,
    KEY_EXPLORER = 2052,
    KEY_ENVELOPE = 2053,
    KEY_ENTER = 2054,
    KEY_DEL = 2055,
    KEY_GRAVE = 2056,
    KEY_MINUS = 2057,
    KEY_EQUALS = 2058,
    KEY_LEFT_BRACKET = 2059,
    KEY_RIGHT_BRACKET = 2060,
    KEY_BACKSLASH = 2061,
    KEY_SEMICOLON = 2062,
    KEY_APOSTROPHE = 2063,
    KEY_SLASH = 2064,
    KEY_AT = 2065,
    KEY_PLUS = 2066,
    KEY_MENU = 2067,
    KEY_PAGE_UP = 2068,
    KEY_PAGE_DOWN = 2069,
    KEY_ESCAPE = 2070,
    KEY_FORWARD_DEL = 2071,
    KEY_CTRL_LEFT = 2072,
    KEY_CTRL_RIGHT = 2073,
    KEY_CAPS_LOCK = 2074,
    KEY_SCROLL_LOCK = 2075,
    KEY_META_LEFT = 2076,
    KEY_META_RIGHT = 2077,
    KEY_FUNCTION = 2078,
    KEY_SYSRQ = 2079,
    KEY_BREAK = 2080,
    KEY_MOVE_HOME = 2081,
    KEY_MOVE_END = 2082,
    KEY_INSERT = 2083,
    KEY_FORWARD = 2084,
    KEY_MEDIA_PLAY = 2085,
    KEY_MEDIA_PAUSE = 2086,
    KEY_MEDIA_CLOSE = 2087,
    KEY_MEDIA_EJECT = 2088,
    KEY_MEDIA_RECORD = 2089,
    KEY_F1 = 2090,
    KEY_F2 = 2091,
    KEY_F3 = 2092,
    KEY_F4 = 2093,
    KEY_F5 = 2094,
    KEY_F6 = 2095,
    KEY_F7 = 2096,
    KEY_F8 = 2097,
    KEY_F9 = 2098,
    KEY_F10 = 2099,
    KEY_F11 = 2100,
    KEY_F12 = 2101,
    KEY_NUM_LOCK = 2102,
    KEY_NUMPAD_0 = 2103,
    KEY_NUMPAD_1 = 2104,
    KEY_NUMPAD_2 = 2105,
    KEY_NUMPAD_3 = 2106,
    KEY_NUMPAD_4 = 2107,
    KEY_NUMPAD_5 = 2108,
    KEY_NUMPAD_6 = 2109,
    KEY_NUMPAD_7 = 2110,
    KEY_NUMPAD_8 = 2111,
    KEY_NUMPAD_9 = 2112,
    KEY_NUMPAD_DIVIDE = 2113,
    KEY_NUMPAD_MULTIPLY = 2114,
    KEY_NUMPAD_SUBTRACT = 2115,
    KEY_NUMPAD_ADD = 2116,
    KEY_NUMPAD_DOT = 2117,
    KEY_NUMPAD_COMMA = 2118,
    KEY_NUMPAD_ENTER = 2119,
    KEY_NUMPAD_EQUALS = 2120,
    KEY_NUMPAD_LEFT_PAREN = 2121,
    KEY_NUMPAD_RIGHT_PAREN = 2122,
    // New Start
    KEY_VIRTUAL_MULTITASK = 2210,
    KEY_BUTTON_A = 2301,
    KEY_BUTTON_B = 2302,
    KEY_BUTTON_C = 2303,
    KEY_BUTTON_X = 2304,
    KEY_BUTTON_Y = 2305,
    KEY_BUTTON_Z = 2306,
    KEY_BUTTON_L1 = 2307,
    KEY_BUTTON_R1 = 2308,
    KEY_BUTTON_L2 = 2309,
    KEY_BUTTON_R2 = 2310,
    KEY_BUTTON_SELECT = 2311,
    KEY_BUTTON_START = 2312,
    KEY_BUTTON_MODE = 2313,
    KEY_BUTTON_THUMBL = 2314,
    KEY_BUTTON_THUMBR = 2315,
    KEY_BUTTON_TRIGGER = 2401,
    KEY_BUTTON_THUMB = 2402,
    KEY_BUTTON_THUMB2 = 2403,
    KEY_BUTTON_TOP = 2404,
    KEY_BUTTON_TOP2 = 2405,
    KEY_BUTTON_PINKIE = 2406,
    KEY_BUTTON_BASE1 = 2407,
    KEY_BUTTON_BASE2 = 2408,
    KEY_BUTTON_BASE3 = 2409,
    KEY_BUTTON_BASE4 = 2410,
    KEY_BUTTON_BASE5 = 2411,
    KEY_BUTTON_BASE6 = 2412,
    KEY_BUTTON_BASE7 = 2413,
    KEY_BUTTON_BASE8 = 2414,
    KEY_BUTTON_BASE9 = 2415,
    KEY_BUTTON_DEAD = 2416,
    KEY_SLEEP = 2600,
    KEY_ZENKAKU_HANKAKU = 2601,
    KEY_102ND = 2602,
    KEY_RO = 2603,
    KEY_KATAKANA = 2604,
    KEY_HIRAGANA = 2605,
    KEY_HENKAN = 2606,
    KEY_KATAKANA_HIRAGANA = 2607,
    KEY_MUHENKAN = 2608,
    KEY_LINEFEED = 2609,
    KEY_MACRO = 2610,
    KEY_NUMPAD_PLUSMINUS = 2611,
    KEY_SCALE = 2612,
    KEY_HANGUEL = 2613,
    KEY_HANJA = 2614,
    KEY_YEN = 2615,
    KEY_STOP = 2616,
    KEY_AGAIN = 2617,
    KEY_PROPS = 2618,
    KEY_UNDO = 2619,
    KEY_COPY = 2620,
    KEY_OPEN = 2621,
    KEY_PASTE = 2622,
    KEY_FIND = 2623,
    KEY_CUT = 2624,
    KEY_HELP = 2625,
    KEY_CALC = 2626,
    KEY_FILE = 2627,
    KEY_BOOKMARKS = 2628,
    KEY_NEXT = 2629,
    KEY_PLAYPAUSE = 2630,
    KEY_PREVIOUS = 2631,
    KEY_STOPCD = 2632,
    KEY_CONFIG = 2634,
    KEY_REFRESH = 2635,
    KEY_EXIT = 2636,
    KEY_EDIT = 2637,
    KEY_SCROLLUP = 2638,
    KEY_SCROLLDOWN = 2639,
    KEY_NEW = 2640,
    KEY_REDO = 2641,
    KEY_CLOSE = 2642,
    KEY_PLAY = 2643,
    KEY_BASSBOOST = 2644,
    KEY_PRINT = 2645,
    KEY_CHAT = 2646,
    KEY_FINANCE = 2647,
    KEY_CANCEL = 2648,
    KEY_KBDILLUM_TOGGLE = 2649,
    KEY_KBDILLUM_DOWN = 2650,
    KEY_KBDILLUM_UP = 2651,
    KEY_SEND = 2652,
    KEY_REPLY = 2653,
    KEY_FORWARDMAIL = 2654,
    KEY_SAVE = 2655,
    KEY_DOCUMENTS = 2656,
    KEY_VIDEO_NEXT = 2657,
    KEY_VIDEO_PREV = 2658,
    KEY_BRIGHTNESS_CYCLE = 2659,
    KEY_BRIGHTNESS_ZERO = 2660,
    KEY_DISPLAY_OFF = 2661,
    KEY_BTN_MISC = 2662,
    KEY_GOTO = 2663,
    KEY_INFO = 2664,
    KEY_PROGRAM = 2665,
    KEY_PVR = 2666,
    KEY_SUBTITLE = 2667,
    KEY_FULL_SCREEN = 2668,
    KEY_KEYBOARD = 2669,
    KEY_ASPECT_RATIO = 2670,
    KEY_PC = 2671,
    KEY_TV = 2672,
    KEY_TV2 = 2673,
    KEY_VCR = 2674,
    KEY_VCR2 = 2675,
    KEY_SAT = 2676,
    KEY_CD = 2677,
    KEY_TAPE = 2678,
    KEY_TUNER = 2679,
    KEY_PLAYER = 2680,
    KEY_DVD = 2681,
    KEY_AUDIO = 2682,
    KEY_VIDEO = 2683,
    KEY_MEMO = 2684,
    KEY_CALENDAR = 2685,
    KEY_RED = 2686,
    KEY_GREEN = 2687,
    KEY_YELLOW = 2688,
    KEY_BLUE = 2689,
    KEY_CHANNELUP = 2690,
    KEY_CHANNELDOWN = 2691,
    KEY_LAST = 2692,
    KEY_RESTART = 2693,
    KEY_SLOW = 2694,
    KEY_SHUFFLE = 2695,
    KEY_VIDEOPHONE = 2696,
    KEY_GAMES = 2697,
    KEY_ZOOMIN = 2698,
    KEY_ZOOMOUT = 2699,
    KEY_ZOOMRESET = 2700,
    KEY_WORDPROCESSOR = 2701,
    KEY_EDITOR = 2702,
    KEY_SPREADSHEET = 2703,
    KEY_GRAPHICSEDITOR = 2704,
    KEY_PRESENTATION = 2705,
    KEY_DATABASE = 2706,
    KEY_NEWS = 2707,
    KEY_VOICEMAIL = 2708,
    KEY_ADDRESSBOOK = 2709,
    KEY_MESSENGER = 2710,
    KEY_BRIGHTNESS_TOGGLE = 2711,
    KEY_SPELLCHECK = 2712,
    KEY_COFFEE = 2713,
    KEY_MEDIA_REPEAT = 2714,
    KEY_IMAGES = 2715,
    KEY_BUTTONCONFIG = 2716,
    KEY_TASKMANAGER = 2717,
    KEY_JOURNAL = 2718,
    KEY_CONTROLPANEL = 2719,
    KEY_APPSELECT = 2720,
    KEY_SCREENSAVER = 2721,
    KEY_ASSISTANT = 2722,
    KEY_KBD_LAYOUT_NEXT = 2723,
    KEY_BRIGHTNESS_MIN = 2724,
    KEY_BRIGHTNESS_MAX = 2725,
    KEY_KBDINPUTASSIST_PREV = 2726,
    KEY_KBDINPUTASSIST_NEXT = 2727,
    KEY_KBDINPUTASSIST_PREVGROUP = 2728,
    KEY_KBDINPUTASSIST_NEXTGROUP = 2729,
    KEY_KBDINPUTASSIST_ACCEPT = 2730,
    KEY_KBDINPUTASSIST_CANCEL = 2731,
    KEY_FRONT = 2800,
    KEY_SETUP = 2801,
    KEY_WAKEUP = 2802,
    KEY_SENDFILE = 2803,
    KEY_DELETEFILE = 2804,
    KEY_XFER = 2805,
    KEY_PROG1 = 2806,
    KEY_PROG2 = 2807,
    KEY_MSDOS = 2808,
    KEY_SCREENLOCK = 2809,
    KEY_DIRECTION_ROTATE_DISPLAY = 2810,
    KEY_CYCLEWINDOWS = 2811,
    KEY_COMPUTER = 2812,
    KEY_EJECTCLOSECD = 2813,
    KEY_ISO = 2814,
    KEY_MOVE = 2815,
    KEY_F13 = 2816,
    KEY_F14 = 2817,
    KEY_F15 = 2818,
    KEY_F16 = 2819,
    KEY_F17 = 2820,
    KEY_F18 = 2821,
    KEY_F19 = 2822,
    KEY_F20 = 2823,
    KEY_F21 = 2824,
    KEY_F22 = 2825,
    KEY_F23 = 2826,
    KEY_F24 = 2827,
    KEY_PROG3 = 2828,
    KEY_PROG4 = 2829,
    KEY_DASHBOARD = 2830,
    KEY_SUSPEND = 2831,
    KEY_HP = 2832,
    KEY_SOUND = 2833,
    KEY_QUESTION = 2834,
    KEY_CONNECT = 2836,
    KEY_SPORT = 2837,
    KEY_SHOP = 2838,
    KEY_ALTERASE = 2839,
    KEY_SWITCHVIDEOMODE = 2841,
    KEY_BATTERY = 2842,
    KEY_BLUETOOTH = 2843,
    KEY_WLAN = 2844,
    KEY_UWB = 2845,
    KEY_WWAN_WIMAX = 2846,
    KEY_RFKILL = 2847,
    KEY_CHANNEL = 3001,
    KEY_BTN_0 = 3100,
    KEY_BTN_1 = 3101,
    KEY_BTN_2 = 3102,
    KEY_BTN_3 = 3103,
    KEY_BTN_4 = 3104,
    KEY_BTN_5 = 3105,
    KEY_BTN_6 = 3106,
    KEY_BTN_7 = 3107,
    KEY_BTN_8 = 3108,
    KEY_BTN_9 = 3109,
    KEY_BRL_DOT1 = 3201,
    KEY_BRL_DOT2 = 3202,
    KEY_BRL_DOT3 = 3203,
    KEY_BRL_DOT4 = 3204,
    KEY_BRL_DOT5 = 3205,
    KEY_BRL_DOT6 = 3206,
    KEY_BRL_DOT7 = 3207,
    KEY_BRL_DOT8 = 3208,
    KEY_BRL_DOT9 = 3209,
    KEY_BRL_DOT10 = 3210,
    // New End
    KEY_LEFT_KNOB_ROLL_UP = 10001,
    KEY_LEFT_KNOB_ROLL_DOWN = 10002,
    KEY_LEFT_KNOB = 10003,
    KEY_RIGHT_KNOB_ROLL_UP = 10004,
    KEY_RIGHT_KNOB_ROLL_DOWN = 10005,
    KEY_RIGHT_KNOB = 10006,
    KEY_VOICE_SOURCE_SWITCH = 10007,
    KEY_LAUNCHER_MENU = 10008,

    TV_CONTROL_BACK = KEY_BACK,
    TV_CONTROL_UP = KEY_DPAD_UP,
    TV_CONTROL_DOWN = KEY_DPAD_DOWN,
    TV_CONTROL_LEFT = KEY_DPAD_LEFT,
    TV_CONTROL_RIGHT = KEY_DPAD_RIGHT,
    TV_CONTROL_CENTER = KEY_DPAD_CENTER,
    TV_CONTROL_ENTER = KEY_ENTER,
    TV_CONTROL_MEDIA_PLAY = KEY_MEDIA_PLAY,
};

enum class KeyAction : int32_t {
    UNKNOWN = -1,
    DOWN = 0,
    UP = 1,
    LONG_PRESS = 2,
    CLICK = 3,
};

constexpr int32_t ASCII_START_UPPER_CASE_LETTER = 65;
constexpr int32_t ASCII_START_LOWER_CASE_LETTER = 97;

ACE_FORCE_EXPORT const char* KeyToString(int32_t code);

struct KeyEvent final : public NonPointerEvent {
    KeyEvent()
    {
        eventType = UIInputEventType::KEY;
    }
    KeyEvent(KeyCode code, KeyAction action, std::vector<KeyCode> pressedCodes, int32_t repeatTimeStamp,
        TimeStamp timeStamp, int32_t metaKey, int64_t deviceIdNum, SourceType source, std::vector<uint8_t> enhanceData)
        : code(code), action(action), pressedCodes(std::move(pressedCodes)), timeStamp(timeStamp), metaKey(metaKey),
          enhanceData(enhanceData)
    {
        repeatTime = repeatTimeStamp;
        deviceId = deviceIdNum;
        sourceType = source;
        eventType = UIInputEventType::KEY;
    }
    KeyEvent(KeyCode code, KeyAction action, int32_t repeatTime = 0, int64_t timeStamp = 0, int64_t deviceId = 0,
        SourceType sourceType = SourceType::KEYBOARD)
    {
        std::vector<KeyCode> pCodes;
        std::vector<uint8_t> enhanceData;
        std::chrono::milliseconds milliseconds(timeStamp);
        TimeStamp time(milliseconds);
        new (this) KeyEvent(code, action, pCodes, repeatTime, time, 0, deviceId, sourceType, enhanceData);
    }
    ~KeyEvent() = default;

    void SetTimeStamp(int64_t timeInt)
    {
        std::chrono::milliseconds milliseconds(timeInt);
        TimeStamp time(milliseconds);
        timeStamp = time;
    }

    bool HasKey(KeyCode expectCode) const
    {
        auto curPressedCode = pressedCodes.rbegin();
        while (curPressedCode != pressedCodes.rend()) {
            if (expectCode == *curPressedCode) {
                return true;
            }
            ++curPressedCode;
        }
        return false;
    }

    bool IsExactlyKey(const std::vector<KeyCode>& expectCodes) const
    {
        auto pressedKeysCnt = pressedCodes.size();
        if (std::find(pressedCodes.begin(), pressedCodes.end(), KeyCode::KEY_FN) != pressedCodes.end()) {
            --pressedKeysCnt;
        }
        return (expectCodes.size() != pressedKeysCnt) ? false : IsKey(expectCodes);
    }

    bool IsKey(const std::vector<KeyCode>& expectCodes) const
    {
        if (expectCodes.size() > pressedCodes.size() || pressedCodes.empty()) {
            return false;
        }
        auto curExpectCode = expectCodes.crbegin();
        auto curPressedCode = pressedCodes.crbegin();
        while (curExpectCode != expectCodes.crend()) {
            if (*curExpectCode != *curPressedCode) {
                return false;
            }
            ++curExpectCode;
            ++curPressedCode;
        }
        return true;
    }

    bool IsCtrlWith(KeyCode expectCodes) const
    {
        return IsKey({ KeyCode::KEY_CTRL_LEFT, expectCodes }) || IsKey({ KeyCode::KEY_CTRL_RIGHT, expectCodes });
    }
    bool IsShiftWith(KeyCode expectCodes) const
    {
        return (HasKey(KeyCode::KEY_SHIFT_LEFT) || HasKey(KeyCode::KEY_SHIFT_RIGHT)) && HasKey(expectCodes);
    }
    bool IsExactlyShiftWith(KeyCode expectCodes) const
    {
        return IsExactlyKey({ KeyCode::KEY_SHIFT_LEFT, expectCodes }) ||
            IsExactlyKey({ KeyCode::KEY_SHIFT_RIGHT, expectCodes });
    }
    bool IsNumberKey() const
    {
        return ((KeyCode::KEY_0 <= code && code <= KeyCode::KEY_9) ||
                (KeyCode::KEY_NUMPAD_0 <= code && code <= KeyCode::KEY_NUMPAD_9));
    }
    bool IsDirectionalKey() const
    {
        return KeyCode::KEY_DPAD_UP <= code && code <= KeyCode::KEY_DPAD_RIGHT;
    }
    bool IsLetterKey() const
    {
        return (KeyCode::KEY_A <= code && code <= KeyCode::KEY_Z);
    }
    bool IsCombinationKey() const
    {
        return pressedCodes.size() > 1;
    }
    bool IsFunctionKey() const
    {
        return (KeyCode::KEY_F1 <= code && code <= KeyCode::KEY_F12) ||
               (KeyCode::KEY_DPAD_UP <= code && code <= KeyCode::KEY_DPAD_RIGHT) || KeyCode::KEY_TAB == code;
    }
    bool IsEscapeKey() const
    {
        return KeyCode::KEY_ESCAPE == code;
    }
    bool IsPreIme() const
    {
        return isPreIme;
    }

    std::string ConvertInputCodeToString() const;
    std::string ConvertCodeToString() const;

    KeyCode code { KeyCode::KEY_UNKNOWN };
    std::string key;
    KeyAction action { KeyAction::UNKNOWN };
    std::vector<KeyCode> pressedCodes;
    // When the key is held down for a long period of time, it will be accumulated once in a while.
    // Note that In the long press scene, you will receive a DOWN and an extra LONG_PRESS event. If you only want to
    // identify the click event, you can use CLICK event.
    TimeStamp timeStamp;
    int32_t metaKey = 0;
    KeyIntention keyIntention { KeyIntention::INTENTION_UNKNOWN };
    bool enableCapsLock = false;
    bool isPreIme = false;
    bool isRedispatch = false;
    bool numLock = false;
    bool scrollLock = false;
    uint32_t unicode = 0;
    std::vector<uint8_t> enhanceData;
    std::shared_ptr<MMI::KeyEvent> rawKeyEvent;
    std::string msg = "";
    std::optional<bool> activeMark;
    int32_t targetDisplayId = 0;

    std::string ToString() const
    {
        std::stringstream ss;
        ss << "code=" << static_cast<int32_t>(code) << ", ";
        ss << "action=" << static_cast<int32_t>(action) << ", ";
        ss << "pressedCodes=[";
        std::for_each(pressedCodes.begin(), pressedCodes.end(),
            [&ss](const KeyCode& code) { ss << static_cast<int32_t>(code) << ", "; });
        ss << "]" << ", ";
        ss << "isPreIme = " << isPreIme;
        return ss.str();
    }
};

class ACE_EXPORT KeyEventInfo : public BaseEventInfo {
    DECLARE_RELATIONSHIP_OF_CLASSES(KeyEventInfo, BaseEventInfo)

public:
    explicit KeyEventInfo(const KeyEvent& event) : BaseEventInfo("keyEvent")
    {
        keyCode_ = event.code;
        keyText_ = event.key;
        keyType_ = event.action;
        keySource_ = event.sourceType;
        keyIntention_ = event.keyIntention;
        metaKey_ = event.metaKey;
        SetDeviceId(event.deviceId);
        SetTimeStamp(event.timeStamp);
        keyMsg_ = event.msg;
        SetPressedKeyCodes(event.pressedCodes);
        unicode_ = event.unicode;
        numLock_ = event.numLock;
        capsLock_ = event.enableCapsLock;
        scrollLock_ = event.scrollLock;
        targetDisplayId_ = event.targetDisplayId;
    };
    ~KeyEventInfo() override = default;

    KeyAction GetKeyType() const
    {
        return keyType_;
    }
    KeyCode GetKeyCode() const
    {
        return keyCode_;
    }
    const std::string& GetKeyText() const
    {
        return keyText_;
    }
    int32_t GetMetaKey() const
    {
        return metaKey_;
    }
    SourceType GetKeySource() const
    {
        return keySource_;
    }
    KeyIntention GetKeyIntention() const
    {
        return keyIntention_;
    }

    void SetMetaKey(int32_t metaKey)
    {
        metaKey_ = metaKey;
    }

    uint32_t GetUnicode() const
    {
        return unicode_;
    }

    bool GetNumLock() const
    {
        return numLock_;
    }

    bool GetCapsLock() const
    {
        return capsLock_;
    }

    bool GetScrollLock() const
    {
        return scrollLock_;
    }

    void ParseKeyEvent(KeyEvent& keyEvent);

private:
    KeyCode keyCode_ = KeyCode::KEY_UNKNOWN;
    std::string keyText_ = "";
    KeyAction keyType_ = KeyAction::UNKNOWN;
    int32_t metaKey_ = 0;
    SourceType keySource_ = SourceType::NONE;
    KeyIntention keyIntention_ = KeyIntention::INTENTION_UNKNOWN;
    std::string keyMsg_ = "";
    uint32_t unicode_ = 0;
    bool numLock_= false;
    bool capsLock_ = false;
    bool scrollLock_ = false;
};

enum class BlurReason : int32_t {
    FOCUS_SWITCH = 0,
    WINDOW_BLUR = 1,
    FRAME_DESTROY = 2, // frame node detached from main tree
    VIEW_SWITCH = 3,
    CLEAR_FOCUS = 4, // User api clearFocus triggered
    BACK_TO_TABSTOP = 5,
};

enum class FocusReason : int32_t {
    DEFAULT = 0,
    FOCUS_TRAVEL = 1,
    FOCUS_TOUCH = 2,
    WINDOW_FOCUS = 3,
    VIEW_SWITCH = 4,
};

using OnKeyEventFunc = std::function<bool(const KeyEvent&)>;
using OnKeyCallbackFunc = std::function<void(KeyEventInfo&)>;
using OnKeyConsumeFunc = std::function<bool(KeyEventInfo&)>;
using OnFocusFunc = std::function<void()>;
using OnClearFocusStateFunc = std::function<void()>;
using OnPaintFocusStateFunc = std::function<bool()>;
using OnBlurFunc = std::function<void()>;
using OnBlurReasonFunc = std::function<void(BlurReason reason)>;
using OnPreFocusFunc = std::function<void()>;
using OnKeyEventDispatchFunc = std::function<bool(KeyEventInfo&)>;
using OnFocusAxisEventFunc = std::function<void(NG::FocusAxisEventInfo&)>;
} // namespace OHOS::Ace
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_EVENT_KEY_EVENT_H
