/*
 * Copyright (c) 2021-2024 Huawei Device Co., Ltd.
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

#include "core/event/key_event_recognizer.h"

namespace OHOS::Ace {
namespace {

constexpr int32_t LONG_PRESS_DURATION = 1;
constexpr int32_t KEY_INTENTION_OFFSET = 16;
constexpr int32_t KEY_INTENTION_ITEM_MIN_COUNT = 1;
constexpr int32_t KEY_INTENTION_ITEM_MAX_COUNT = 3;

// List Menu key on keyboard.
constexpr int64_t KEY_COMPOSE = 2466;

enum class CtrlKeysBit {
    CTRL = 1,
    SHIFT = 2,
    ALT = 4,
    META = 8,
};
}

const char* KeyCodeToString(int32_t keyCode)
{
    const static std::map<KeyCode, std::string> KEYCODE_TO_STRING = {
        {KeyCode::KEY_FN, "KEYCODE_FN"},
        {KeyCode::KEY_UNKNOWN, "KEYCODE_UNKNOWN"},
        {KeyCode::KEY_HOME, "KEYCODE_HOME"},
        {KeyCode::KEY_BACK, "KEYCODE_BACK"},
        {KeyCode::KEY_CALL, "KEYCODE_CALL"},
        {KeyCode::KEY_ENDCALL, "KEYCODE_ENDCALL"},
        {KeyCode::KEY_CLEAR, "KEYCODE_CLEAR"},
        {KeyCode::KEY_HEADSETHOOK, "KEYCODE_HEADSETHOOK"},
        {KeyCode::KEY_FOCUS, "KEYCODE_FOCUS"},
        {KeyCode::KEY_NOTIFICATION, "KEYCODE_NOTIFICATION"},
        {KeyCode::KEY_SEARCH, "KEYCODE_SEARCH"},
        {KeyCode::KEY_MEDIA_PLAY_PAUSE, "KEYCODE_MEDIA_PLAY_PAUSE"},
        {KeyCode::KEY_MEDIA_STOP, "KEYCODE_MEDIA_STOP"},
        {KeyCode::KEY_MEDIA_NEXT, "KEYCODE_MEDIA_NEXT"},
        {KeyCode::KEY_MEDIA_PREVIOUS, "KEYCODE_MEDIA_PREVIOUS"},
        {KeyCode::KEY_MEDIA_REWIND, "KEYCODE_MEDIA_REWIND"},
        {KeyCode::KEY_MEDIA_FAST_FORWARD, "KEYCODE_MEDIA_FAST_FORWARD"},
        {KeyCode::KEY_VOLUME_UP, "KEYCODE_VOLUME_UP"},
        {KeyCode::KEY_VOLUME_DOWN, "KEYCODE_VOLUME_DOWN"},
        {KeyCode::KEY_POWER, "KEYCODE_POWER"},
        {KeyCode::KEY_CAMERA, "KEYCODE_CAMERA"},
        {KeyCode::KEY_VOICE_ASSISTANT, "KEYCODE_VOICE_ASSISTANT"},
        {KeyCode::KEY_CUSTOM1, "KEYCODE_CUSTOM1"},
        {KeyCode::KEY_VOLUME_MUTE, "KEYCODE_VOLUME_MUTE"},
        {KeyCode::KEY_MUTE, "KEYCODE_MUTE"},
        {KeyCode::KEY_BRIGHTNESS_UP, "KEYCODE_BRIGHTNESS_UP"},
        {KeyCode::KEY_BRIGHTNESS_DOWN, "KEYCODE_BRIGHTNESS_DOWN"},
        {KeyCode::KEY_WEAR_1, "KEYCODE_WEAR_1"},
        {KeyCode::KEY_0, "KEYCODE_0"},
        {KeyCode::KEY_1, "KEYCODE_1"},
        {KeyCode::KEY_2, "KEYCODE_2"},
        {KeyCode::KEY_3, "KEYCODE_3"},
        {KeyCode::KEY_4, "KEYCODE_4"},
        {KeyCode::KEY_5, "KEYCODE_5"},
        {KeyCode::KEY_6, "KEYCODE_6"},
        {KeyCode::KEY_7, "KEYCODE_7"},
        {KeyCode::KEY_8, "KEYCODE_8"},
        {KeyCode::KEY_9, "KEYCODE_9"},
        {KeyCode::KEY_STAR, "KEYCODE_STAR"},
        {KeyCode::KEY_POUND, "KEYCODE_POUND"},
        {KeyCode::KEY_DPAD_UP, "KEYCODE_DPAD_UP"},
        {KeyCode::KEY_DPAD_DOWN, "KEYCODE_DPAD_DOWN"},
        {KeyCode::KEY_DPAD_LEFT, "KEYCODE_DPAD_LEFT"},
        {KeyCode::KEY_DPAD_RIGHT, "KEYCODE_DPAD_RIGHT"},
        {KeyCode::KEY_DPAD_CENTER, "KEYCODE_DPAD_CENTER"},
        {KeyCode::KEY_A, "KEYCODE_A"},
        {KeyCode::KEY_B, "KEYCODE_B"},
        {KeyCode::KEY_C, "KEYCODE_C"},
        {KeyCode::KEY_D, "KEYCODE_D"},
        {KeyCode::KEY_E, "KEYCODE_E"},
        {KeyCode::KEY_F, "KEYCODE_F"},
        {KeyCode::KEY_G, "KEYCODE_G"},
        {KeyCode::KEY_H, "KEYCODE_H"},
        {KeyCode::KEY_I, "KEYCODE_I"},
        {KeyCode::KEY_J, "KEYCODE_J"},
        {KeyCode::KEY_K, "KEYCODE_K"},
        {KeyCode::KEY_L, "KEYCODE_L"},
        {KeyCode::KEY_M, "KEYCODE_M"},
        {KeyCode::KEY_N, "KEYCODE_N"},
        {KeyCode::KEY_O, "KEYCODE_O"},
        {KeyCode::KEY_P, "KEYCODE_P"},
        {KeyCode::KEY_Q, "KEYCODE_Q"},
        {KeyCode::KEY_R, "KEYCODE_R"},
        {KeyCode::KEY_S, "KEYCODE_S"},
        {KeyCode::KEY_T, "KEYCODE_T"},
        {KeyCode::KEY_U, "KEYCODE_U"},
        {KeyCode::KEY_V, "KEYCODE_V"},
        {KeyCode::KEY_W, "KEYCODE_W"},
        {KeyCode::KEY_X, "KEYCODE_X"},
        {KeyCode::KEY_Y, "KEYCODE_Y"},
        {KeyCode::KEY_Z, "KEYCODE_Z"},
        {KeyCode::KEY_COMMA, "KEYCODE_COMMA"},
        {KeyCode::KEY_PERIOD, "KEYCODE_PERIOD"},
        {KeyCode::KEY_ALT_LEFT, "KEYCODE_ALT_LEFT"},
        {KeyCode::KEY_ALT_RIGHT, "KEYCODE_ALT_RIGHT"},
        {KeyCode::KEY_SHIFT_LEFT, "KEYCODE_SHIFT_LEFT"},
        {KeyCode::KEY_SHIFT_RIGHT, "KEYCODE_SHIFT_RIGHT"},
        {KeyCode::KEY_TAB, "KEYCODE_TAB"},
        {KeyCode::KEY_SPACE, "KEYCODE_SPACE"},
        {KeyCode::KEY_SYM, "KEYCODE_SYM"},
        {KeyCode::KEY_EXPLORER, "KEYCODE_EXPLORER"},
        {KeyCode::KEY_ENVELOPE, "KEYCODE_ENVELOPE"},
        {KeyCode::KEY_ENTER, "KEYCODE_ENTER"},
        {KeyCode::KEY_DEL, "KEYCODE_DEL"},
        {KeyCode::KEY_GRAVE, "KEYCODE_GRAVE"},
        {KeyCode::KEY_MINUS, "KEYCODE_MINUS"},
        {KeyCode::KEY_EQUALS, "KEYCODE_EQUALS"},
        {KeyCode::KEY_LEFT_BRACKET, "KEYCODE_LEFT_BRACKET"},
        {KeyCode::KEY_RIGHT_BRACKET, "KEYCODE_RIGHT_BRACKET"},
        {KeyCode::KEY_BACKSLASH, "KEYCODE_BACKSLASH"},
        {KeyCode::KEY_SEMICOLON, "KEYCODE_SEMICOLON"},
        {KeyCode::KEY_APOSTROPHE, "KEYCODE_APOSTROPHE"},
        {KeyCode::KEY_SLASH, "KEYCODE_SLASH"},
        {KeyCode::KEY_AT, "KEYCODE_AT"},
        {KeyCode::KEY_PLUS, "KEYCODE_PLUS"},
        {KeyCode::KEY_MENU, "KEYCODE_MENU"},
        {KeyCode::KEY_PAGE_UP, "KEYCODE_PAGE_UP"},
        {KeyCode::KEY_PAGE_DOWN, "KEYCODE_PAGE_DOWN"},
        {KeyCode::KEY_ESCAPE, "KEYCODE_ESCAPE"},
        {KeyCode::KEY_FORWARD_DEL, "KEYCODE_FORWARD_DEL"},
        {KeyCode::KEY_CTRL_LEFT, "KEYCODE_CTRL_LEFT"},
        {KeyCode::KEY_CTRL_RIGHT, "KEYCODE_CTRL_RIGHT"},
        {KeyCode::KEY_CAPS_LOCK, "KEYCODE_CAPS_LOCK"},
        {KeyCode::KEY_SCROLL_LOCK, "KEYCODE_SCROLL_LOCK"},
        {KeyCode::KEY_META_LEFT, "KEYCODE_META_LEFT"},
        {KeyCode::KEY_META_RIGHT, "KEYCODE_META_RIGHT"},
        {KeyCode::KEY_FUNCTION, "KEYCODE_FUNCTION"},
        {KeyCode::KEY_SYSRQ, "KEYCODE_SYSRQ"},
        {KeyCode::KEY_BREAK, "KEYCODE_BREAK"},
        {KeyCode::KEY_MOVE_HOME, "KEYCODE_MOVE_HOME"},
        {KeyCode::KEY_MOVE_END, "KEYCODE_MOVE_END"},
        {KeyCode::KEY_INSERT, "KEYCODE_INSERT"},
        {KeyCode::KEY_FORWARD, "KEYCODE_FORWARD"},
        {KeyCode::KEY_MEDIA_PLAY, "KEYCODE_MEDIA_PLAY"},
        {KeyCode::KEY_MEDIA_PAUSE, "KEYCODE_MEDIA_PAUSE"},
        {KeyCode::KEY_MEDIA_CLOSE, "KEYCODE_MEDIA_CLOSE"},
        {KeyCode::KEY_MEDIA_EJECT, "KEYCODE_MEDIA_EJECT"},
        {KeyCode::KEY_MEDIA_RECORD, "KEYCODE_MEDIA_RECORD"},
        {KeyCode::KEY_F1, "KEYCODE_F1"},
        {KeyCode::KEY_F2, "KEYCODE_F2"},
        {KeyCode::KEY_F3, "KEYCODE_F3"},
        {KeyCode::KEY_F4, "KEYCODE_F4"},
        {KeyCode::KEY_F5, "KEYCODE_F5"},
        {KeyCode::KEY_F6, "KEYCODE_F6"},
        {KeyCode::KEY_F7, "KEYCODE_F7"},
        {KeyCode::KEY_F8, "KEYCODE_F8"},
        {KeyCode::KEY_F9, "KEYCODE_F9"},
        {KeyCode::KEY_F10, "KEYCODE_F10"},
        {KeyCode::KEY_F11, "KEYCODE_F11"},
        {KeyCode::KEY_F12, "KEYCODE_F12"},
        {KeyCode::KEY_NUM_LOCK, "KEYCODE_NUM_LOCK"},
        {KeyCode::KEY_NUMPAD_0, "KEYCODE_NUMPAD_0"},
        {KeyCode::KEY_NUMPAD_1, "KEYCODE_NUMPAD_1"},
        {KeyCode::KEY_NUMPAD_2, "KEYCODE_NUMPAD_2"},
        {KeyCode::KEY_NUMPAD_3, "KEYCODE_NUMPAD_3"},
        {KeyCode::KEY_NUMPAD_4, "KEYCODE_NUMPAD_4"},
        {KeyCode::KEY_NUMPAD_5, "KEYCODE_NUMPAD_5"},
        {KeyCode::KEY_NUMPAD_6, "KEYCODE_NUMPAD_6"},
        {KeyCode::KEY_NUMPAD_7, "KEYCODE_NUMPAD_7"},
        {KeyCode::KEY_NUMPAD_8, "KEYCODE_NUMPAD_8"},
        {KeyCode::KEY_NUMPAD_9, "KEYCODE_NUMPAD_9"},
        {KeyCode::KEY_NUMPAD_DIVIDE, "KEYCODE_NUMPAD_DIVIDE"},
        {KeyCode::KEY_NUMPAD_MULTIPLY, "KEYCODE_NUMPAD_MULTIPLY"},
        {KeyCode::KEY_NUMPAD_SUBTRACT, "KEYCODE_NUMPAD_SUBTRACT"},
        {KeyCode::KEY_NUMPAD_ADD, "KEYCODE_NUMPAD_ADD"},
        {KeyCode::KEY_NUMPAD_DOT, "KEYCODE_NUMPAD_DOT"},
        {KeyCode::KEY_NUMPAD_COMMA, "KEYCODE_NUMPAD_COMMA"},
        {KeyCode::KEY_NUMPAD_ENTER, "KEYCODE_NUMPAD_ENTER"},
        {KeyCode::KEY_NUMPAD_EQUALS, "KEYCODE_NUMPAD_EQUALS"},
        {KeyCode::KEY_NUMPAD_LEFT_PAREN, "KEYCODE_NUMPAD_LEFT_PAREN"},
        {KeyCode::KEY_NUMPAD_RIGHT_PAREN, "KEYCODE_NUMPAD_RIGHT_PAREN"},
        {KeyCode::KEY_VIRTUAL_MULTITASK, "KEYCODE_VIRTUAL_MULTITASK"},
        {KeyCode::KEY_BUTTON_A, "KEYCODE_BUTTON_A"},
        {KeyCode::KEY_BUTTON_B, "KEYCODE_BUTTON_B"},
        {KeyCode::KEY_BUTTON_C, "KEYCODE_BUTTON_C"},
        {KeyCode::KEY_BUTTON_X, "KEYCODE_BUTTON_X"},
        {KeyCode::KEY_BUTTON_Y, "KEYCODE_BUTTON_Y"},
        {KeyCode::KEY_BUTTON_Z, "KEYCODE_BUTTON_Z"},
        {KeyCode::KEY_BUTTON_L1, "KEYCODE_BUTTON_L1"},
        {KeyCode::KEY_BUTTON_R1, "KEYCODE_BUTTON_R1"},
        {KeyCode::KEY_BUTTON_L2, "KEYCODE_BUTTON_L2"},
        {KeyCode::KEY_BUTTON_R2, "KEYCODE_BUTTON_R2"},
        {KeyCode::KEY_BUTTON_SELECT, "KEYCODE_BUTTON_SELECT"},
        {KeyCode::KEY_BUTTON_START, "KEYCODE_BUTTON_START"},
        {KeyCode::KEY_BUTTON_MODE, "KEYCODE_BUTTON_MODE"},
        {KeyCode::KEY_BUTTON_THUMBL, "KEYCODE_BUTTON_THUMBL"},
        {KeyCode::KEY_BUTTON_THUMBR, "KEYCODE_BUTTON_THUMBR"},
        {KeyCode::KEY_BUTTON_TRIGGER, "KEYCODE_BUTTON_TRIGGER"},
        {KeyCode::KEY_BUTTON_THUMB, "KEYCODE_BUTTON_THUMB"},
        {KeyCode::KEY_BUTTON_THUMB2, "KEYCODE_BUTTON_THUMB2"},
        {KeyCode::KEY_BUTTON_TOP, "KEYCODE_BUTTON_TOP"},
        {KeyCode::KEY_BUTTON_TOP2, "KEYCODE_BUTTON_TOP2"},
        {KeyCode::KEY_BUTTON_PINKIE, "KEYCODE_BUTTON_PINKIE"},
        {KeyCode::KEY_BUTTON_BASE1, "KEYCODE_BUTTON_BASE1"},
        {KeyCode::KEY_BUTTON_BASE2, "KEYCODE_BUTTON_BASE2"},
        {KeyCode::KEY_BUTTON_BASE3, "KEYCODE_BUTTON_BASE3"},
        {KeyCode::KEY_BUTTON_BASE4, "KEYCODE_BUTTON_BASE4"},
        {KeyCode::KEY_BUTTON_BASE5, "KEYCODE_BUTTON_BASE5"},
        {KeyCode::KEY_BUTTON_BASE6, "KEYCODE_BUTTON_BASE6"},
        {KeyCode::KEY_BUTTON_BASE7, "KEYCODE_BUTTON_BASE7"},
        {KeyCode::KEY_BUTTON_BASE8, "KEYCODE_BUTTON_BASE8"},
        {KeyCode::KEY_BUTTON_BASE9, "KEYCODE_BUTTON_BASE9"},
        {KeyCode::KEY_BUTTON_DEAD, "KEYCODE_BUTTON_DEAD"},
        {KeyCode::KEY_SLEEP, "KEYCODE_SLEEP"},
        {KeyCode::KEY_ZENKAKU_HANKAKU, "KEYCODE_ZENKAKU_HANKAKU"},
        {KeyCode::KEY_102ND, "KEYCODE_102ND"},
        {KeyCode::KEY_RO, "KEYCODE_RO"},
        {KeyCode::KEY_KATAKANA, "KEYCODE_KATAKANA"},
        {KeyCode::KEY_HIRAGANA, "KEYCODE_HIRAGANA"},
        {KeyCode::KEY_HENKAN, "KEYCODE_HENKAN"},
        {KeyCode::KEY_KATAKANA_HIRAGANA, "KEYCODE_KATAKANA_HIRAGANA"},
        {KeyCode::KEY_MUHENKAN, "KEYCODE_MUHENKAN"},
        {KeyCode::KEY_LINEFEED, "KEYCODE_LINEFEED"},
        {KeyCode::KEY_MACRO, "KEYCODE_MACRO"},
        {KeyCode::KEY_NUMPAD_PLUSMINUS, "KEYCODE_NUMPAD_PLUSMINUS"},
        {KeyCode::KEY_SCALE, "KEYCODE_SCALE"},
        {KeyCode::KEY_HANGUEL, "KEYCODE_HANGUEL"},
        {KeyCode::KEY_HANJA, "KEYCODE_HANJA"},
        {KeyCode::KEY_YEN, "KEYCODE_YEN"},
        {KeyCode::KEY_STOP, "KEYCODE_STOP"},
        {KeyCode::KEY_AGAIN, "KEYCODE_AGAIN"},
        {KeyCode::KEY_PROPS, "KEYCODE_PROPS"},
        {KeyCode::KEY_UNDO, "KEYCODE_UNDO"},
        {KeyCode::KEY_COPY, "KEYCODE_COPY"},
        {KeyCode::KEY_OPEN, "KEYCODE_OPEN"},
        {KeyCode::KEY_PASTE, "KEYCODE_PASTE"},
        {KeyCode::KEY_FIND, "KEYCODE_FIND"},
        {KeyCode::KEY_CUT, "KEYCODE_CUT"},
        {KeyCode::KEY_HELP, "KEYCODE_HELP"},
        {KeyCode::KEY_CALC, "KEYCODE_CALC"},
        {KeyCode::KEY_FILE, "KEYCODE_FILE"},
        {KeyCode::KEY_BOOKMARKS, "KEYCODE_BOOKMARKS"},
        {KeyCode::KEY_NEXT, "KEYCODE_NEXT"},
        {KeyCode::KEY_PLAYPAUSE, "KEYCODE_PLAYPAUSE"},
        {KeyCode::KEY_PREVIOUS, "KEYCODE_PREVIOUS"},
        {KeyCode::KEY_STOPCD, "KEYCODE_STOPCD"},
        {KeyCode::KEY_CONFIG, "KEYCODE_CONFIG"},
        {KeyCode::KEY_REFRESH, "KEYCODE_REFRESH"},
        {KeyCode::KEY_EXIT, "KEYCODE_EXIT"},
        {KeyCode::KEY_EDIT, "KEYCODE_EDIT"},
        {KeyCode::KEY_SCROLLUP, "KEYCODE_SCROLLUP"},
        {KeyCode::KEY_SCROLLDOWN, "KEYCODE_SCROLLDOWN"},
        {KeyCode::KEY_NEW, "KEYCODE_NEW"},
        {KeyCode::KEY_REDO, "KEYCODE_REDO"},
        {KeyCode::KEY_CLOSE, "KEYCODE_CLOSE"},
        {KeyCode::KEY_PLAY, "KEYCODE_PLAY"},
        {KeyCode::KEY_BASSBOOST, "KEYCODE_BASSBOOST"},
        {KeyCode::KEY_PRINT, "KEYCODE_PRINT"},
        {KeyCode::KEY_CHAT, "KEYCODE_CHAT"},
        {KeyCode::KEY_FINANCE, "KEYCODE_FINANCE"},
        {KeyCode::KEY_CANCEL, "KEYCODE_CANCEL"},
        {KeyCode::KEY_KBDILLUM_TOGGLE, "KEYCODE_KBDILLUM_TOGGLE"},
        {KeyCode::KEY_KBDILLUM_DOWN, "KEYCODE_KBDILLUM_DOWN"},
        {KeyCode::KEY_KBDILLUM_UP, "KEYCODE_KBDILLUM_UP"},
        {KeyCode::KEY_SEND, "KEYCODE_SEND"},
        {KeyCode::KEY_REPLY, "KEYCODE_REPLY"},
        {KeyCode::KEY_FORWARDMAIL, "KEYCODE_FORWARDMAIL"},
        {KeyCode::KEY_SAVE, "KEYCODE_SAVE"},
        {KeyCode::KEY_DOCUMENTS, "KEYCODE_DOCUMENTS"},
        {KeyCode::KEY_VIDEO_NEXT, "KEYCODE_VIDEO_NEXT"},
        {KeyCode::KEY_VIDEO_PREV, "KEYCODE_VIDEO_PREV"},
        {KeyCode::KEY_BRIGHTNESS_CYCLE, "KEYCODE_BRIGHTNESS_CYCLE"},
        {KeyCode::KEY_BRIGHTNESS_ZERO, "KEYCODE_BRIGHTNESS_ZERO"},
        {KeyCode::KEY_DISPLAY_OFF, "KEYCODE_DISPLAY_OFF"},
        {KeyCode::KEY_BTN_MISC, "KEYCODE_BTN_MISC"},
        {KeyCode::KEY_GOTO, "KEYCODE_GOTO"},
        {KeyCode::KEY_INFO, "KEYCODE_INFO"},
        {KeyCode::KEY_PROGRAM, "KEYCODE_PROGRAM"},
        {KeyCode::KEY_PVR, "KEYCODE_PVR"},
        {KeyCode::KEY_SUBTITLE, "KEYCODE_SUBTITLE"},
        {KeyCode::KEY_FULL_SCREEN, "KEYCODE_FULL_SCREEN"},
        {KeyCode::KEY_KEYBOARD, "KEYCODE_KEYBOARD"},
        {KeyCode::KEY_ASPECT_RATIO, "KEYCODE_ASPECT_RATIO"},
        {KeyCode::KEY_PC, "KEYCODE_PC"},
        {KeyCode::KEY_TV, "KEYCODE_TV"},
        {KeyCode::KEY_TV2, "KEYCODE_TV2"},
        {KeyCode::KEY_VCR, "KEYCODE_VCR"},
        {KeyCode::KEY_VCR2, "KEYCODE_VCR2"},
        {KeyCode::KEY_SAT, "KEYCODE_SAT"},
        {KeyCode::KEY_CD, "KEYCODE_CD"},
        {KeyCode::KEY_TAPE, "KEYCODE_TAPE"},
        {KeyCode::KEY_TUNER, "KEYCODE_TUNER"},
        {KeyCode::KEY_PLAYER, "KEYCODE_PLAYER"},
        {KeyCode::KEY_DVD, "KEYCODE_DVD"},
        {KeyCode::KEY_AUDIO, "KEYCODE_AUDIO"},
        {KeyCode::KEY_VIDEO, "KEYCODE_VIDEO"},
        {KeyCode::KEY_MEMO, "KEYCODE_MEMO"},
        {KeyCode::KEY_CALENDAR, "KEYCODE_CALENDAR"},
        {KeyCode::KEY_RED, "KEYCODE_RED"},
        {KeyCode::KEY_GREEN, "KEYCODE_GREEN"},
        {KeyCode::KEY_YELLOW, "KEYCODE_YELLOW"},
        {KeyCode::KEY_BLUE, "KEYCODE_BLUE"},
        {KeyCode::KEY_CHANNELUP, "KEYCODE_CHANNELUP"},
        {KeyCode::KEY_CHANNELDOWN, "KEYCODE_CHANNELDOWN"},
        {KeyCode::KEY_LAST, "KEYCODE_LAST"},
        {KeyCode::KEY_RESTART, "KEYCODE_RESTART"},
        {KeyCode::KEY_SLOW, "KEYCODE_SLOW"},
        {KeyCode::KEY_SHUFFLE, "KEYCODE_SHUFFLE"},
        {KeyCode::KEY_VIDEOPHONE, "KEYCODE_VIDEOPHONE"},
        {KeyCode::KEY_GAMES, "KEYCODE_GAMES"},
        {KeyCode::KEY_ZOOMIN, "KEYCODE_ZOOMIN"},
        {KeyCode::KEY_ZOOMOUT, "KEYCODE_ZOOMOUT"},
        {KeyCode::KEY_ZOOMRESET, "KEYCODE_ZOOMRESET"},
        {KeyCode::KEY_WORDPROCESSOR, "KEYCODE_WORDPROCESSOR"},
        {KeyCode::KEY_EDITOR, "KEYCODE_EDITOR"},
        {KeyCode::KEY_SPREADSHEET, "KEYCODE_SPREADSHEET"},
        {KeyCode::KEY_GRAPHICSEDITOR, "KEYCODE_GRAPHICSEDITOR"},
        {KeyCode::KEY_PRESENTATION, "KEYCODE_PRESENTATION"},
        {KeyCode::KEY_DATABASE, "KEYCODE_DATABASE"},
        {KeyCode::KEY_NEWS, "KEYCODE_NEWS"},
        {KeyCode::KEY_VOICEMAIL, "KEYCODE_VOICEMAIL"},
        {KeyCode::KEY_ADDRESSBOOK, "KEYCODE_ADDRESSBOOK"},
        {KeyCode::KEY_MESSENGER, "KEYCODE_MESSENGER"},
        {KeyCode::KEY_BRIGHTNESS_TOGGLE, "KEYCODE_BRIGHTNESS_TOGGLE"},
        {KeyCode::KEY_SPELLCHECK, "KEYCODE_SPELLCHECK"},
        {KeyCode::KEY_COFFEE, "KEYCODE_COFFEE"},
        {KeyCode::KEY_MEDIA_REPEAT, "KEYCODE_MEDIA_REPEAT"},
        {KeyCode::KEY_IMAGES, "KEYCODE_IMAGES"},
        {KeyCode::KEY_BUTTONCONFIG, "KEYCODE_BUTTONCONFIG"},
        {KeyCode::KEY_TASKMANAGER, "KEYCODE_TASKMANAGER"},
        {KeyCode::KEY_JOURNAL, "KEYCODE_JOURNAL"},
        {KeyCode::KEY_CONTROLPANEL, "KEYCODE_CONTROLPANEL"},
        {KeyCode::KEY_APPSELECT, "KEYCODE_APPSELECT"},
        {KeyCode::KEY_SCREENSAVER, "KEYCODE_SCREENSAVER"},
        {KeyCode::KEY_ASSISTANT, "KEYCODE_ASSISTANT"},
        {KeyCode::KEY_KBD_LAYOUT_NEXT, "KEYCODE_KBD_LAYOUT_NEXT"},
        {KeyCode::KEY_BRIGHTNESS_MIN, "KEYCODE_BRIGHTNESS_MIN"},
        {KeyCode::KEY_BRIGHTNESS_MAX, "KEYCODE_BRIGHTNESS_MAX"},
        {KeyCode::KEY_KBDINPUTASSIST_PREV, "KEYCODE_KBDINPUTASSIST_PREV"},
        {KeyCode::KEY_KBDINPUTASSIST_NEXT, "KEYCODE_KBDINPUTASSIST_NEXT"},
        {KeyCode::KEY_KBDINPUTASSIST_PREVGROUP, "KEYCODE_KBDINPUTASSIST_PREVGROUP"},
        {KeyCode::KEY_KBDINPUTASSIST_NEXTGROUP, "KEYCODE_KBDINPUTASSIST_NEXTGROUP"},
        {KeyCode::KEY_KBDINPUTASSIST_ACCEPT, "KEYCODE_KBDINPUTASSIST_ACCEPT"},
        {KeyCode::KEY_KBDINPUTASSIST_CANCEL, "KEYCODE_KBDINPUTASSIST_CANCEL"},
        {KeyCode::KEY_FRONT, "KEYCODE_FRONT"},
        {KeyCode::KEY_SETUP, "KEYCODE_SETUP"},
        {KeyCode::KEY_WAKEUP, "KEYCODE_WAKEUP"},
        {KeyCode::KEY_SENDFILE, "KEYCODE_SENDFILE"},
        {KeyCode::KEY_DELETEFILE, "KEYCODE_DELETEFILE"},
        {KeyCode::KEY_XFER, "KEYCODE_XFER"},
        {KeyCode::KEY_PROG1, "KEYCODE_PROG1"},
        {KeyCode::KEY_PROG2, "KEYCODE_PROG2"},
        {KeyCode::KEY_MSDOS, "KEYCODE_MSDOS"},
        {KeyCode::KEY_SCREENLOCK, "KEYCODE_SCREENLOCK"},
        {KeyCode::KEY_DIRECTION_ROTATE_DISPLAY, "KEYCODE_DIRECTION_ROTATE_DISPLAY"},
        {KeyCode::KEY_CYCLEWINDOWS, "KEYCODE_CYCLEWINDOWS"},
        {KeyCode::KEY_COMPUTER, "KEYCODE_COMPUTER"},
        {KeyCode::KEY_EJECTCLOSECD, "KEYCODE_EJECTCLOSECD"},
        {KeyCode::KEY_ISO, "KEYCODE_ISO"},
        {KeyCode::KEY_MOVE, "KEYCODE_MOVE"},
        {KeyCode::KEY_F13, "KEYCODE_F13"},
        {KeyCode::KEY_F14, "KEYCODE_F14"},
        {KeyCode::KEY_F15, "KEYCODE_F15"},
        {KeyCode::KEY_F16, "KEYCODE_F16"},
        {KeyCode::KEY_F17, "KEYCODE_F17"},
        {KeyCode::KEY_F18, "KEYCODE_F18"},
        {KeyCode::KEY_F19, "KEYCODE_F19"},
        {KeyCode::KEY_F20, "KEYCODE_F20"},
        {KeyCode::KEY_F21, "KEYCODE_F21"},
        {KeyCode::KEY_F22, "KEYCODE_F22"},
        {KeyCode::KEY_F23, "KEYCODE_F23"},
        {KeyCode::KEY_F24, "KEYCODE_F24"},
        {KeyCode::KEY_PROG3, "KEYCODE_PROG3"},
        {KeyCode::KEY_PROG4, "KEYCODE_PROG4"},
        {KeyCode::KEY_DASHBOARD, "KEYCODE_DASHBOARD"},
        {KeyCode::KEY_SUSPEND, "KEYCODE_SUSPEND"},
        {KeyCode::KEY_HP, "KEYCODE_HP"},
        {KeyCode::KEY_SOUND, "KEYCODE_SOUND"},
        {KeyCode::KEY_QUESTION, "KEYCODE_QUESTION"},
        {KeyCode::KEY_CONNECT, "KEYCODE_CONNECT"},
        {KeyCode::KEY_SPORT, "KEYCODE_SPORT"},
        {KeyCode::KEY_SHOP, "KEYCODE_SHOP"},
        {KeyCode::KEY_ALTERASE, "KEYCODE_ALTERASE"},
        {KeyCode::KEY_SWITCHVIDEOMODE, "KEYCODE_SWITCHVIDEOMODE"},
        {KeyCode::KEY_BATTERY, "KEYCODE_BATTERY"},
        {KeyCode::KEY_BLUETOOTH, "KEYCODE_BLUETOOTH"},
        {KeyCode::KEY_WLAN, "KEYCODE_WLAN"},
        {KeyCode::KEY_UWB, "KEYCODE_UWB"},
        {KeyCode::KEY_WWAN_WIMAX, "KEYCODE_WWAN_WIMAX"},
        {KeyCode::KEY_RFKILL, "KEYCODE_RFKILL"},
        {KeyCode::KEY_CHANNEL, "KEYCODE_CHANNEL"},
        {KeyCode::KEY_BTN_0, "KEYCODE_BTN_0"},
        {KeyCode::KEY_BTN_1, "KEYCODE_BTN_1"},
        {KeyCode::KEY_BTN_2, "KEYCODE_BTN_2"},
        {KeyCode::KEY_BTN_3, "KEYCODE_BTN_3"},
        {KeyCode::KEY_BTN_4, "KEYCODE_BTN_4"},
        {KeyCode::KEY_BTN_5, "KEYCODE_BTN_5"},
        {KeyCode::KEY_BTN_6, "KEYCODE_BTN_6"},
        {KeyCode::KEY_BTN_7, "KEYCODE_BTN_7"},
        {KeyCode::KEY_BTN_8, "KEYCODE_BTN_8"},
        {KeyCode::KEY_BTN_9, "KEYCODE_BTN_9"},
        {KeyCode::KEY_BRL_DOT1, "KEYCODE_BRL_DOT1"},
        {KeyCode::KEY_BRL_DOT2, "KEYCODE_BRL_DOT2"},
        {KeyCode::KEY_BRL_DOT3, "KEYCODE_BRL_DOT3"},
        {KeyCode::KEY_BRL_DOT4, "KEYCODE_BRL_DOT4"},
        {KeyCode::KEY_BRL_DOT5, "KEYCODE_BRL_DOT5"},
        {KeyCode::KEY_BRL_DOT6, "KEYCODE_BRL_DOT6"},
        {KeyCode::KEY_BRL_DOT7, "KEYCODE_BRL_DOT7"},
        {KeyCode::KEY_BRL_DOT8, "KEYCODE_BRL_DOT8"},
        {KeyCode::KEY_BRL_DOT9, "KEYCODE_BRL_DOT9"},
        {KeyCode::KEY_BRL_DOT10, "KEYCODE_BRL_DOT10"},
        {KeyCode::KEY_LEFT_KNOB_ROLL_UP, "KEYCODE_LEFT_KNOB_ROLL_UP"},
        {KeyCode::KEY_LEFT_KNOB_ROLL_DOWN, "KEYCODE_LEFT_KNOB_ROLL_DOWN"},
        {KeyCode::KEY_LEFT_KNOB, "KEYCODE_LEFT_KNOB"},
        {KeyCode::KEY_RIGHT_KNOB_ROLL_UP, "KEYCODE_RIGHT_KNOB_ROLL_UP"},
        {KeyCode::KEY_RIGHT_KNOB_ROLL_DOWN, "KEYCODE_RIGHT_KNOB_ROLL_DOWN"},
        {KeyCode::KEY_RIGHT_KNOB, "KEYCODE_RIGHT_KNOB"},
        {KeyCode::KEY_VOICE_SOURCE_SWITCH, "KEYCODE_VOICE_SOURCE_SWITCH"},
        {KeyCode::KEY_LAUNCHER_MENU, "KEYCODE_LAUNCHER_MENU"},
    };

    auto iter = KEYCODE_TO_STRING.find(static_cast<KeyCode>(keyCode));
    if (iter == KEYCODE_TO_STRING.end()) {
        return "KEYCODE_INVALID";
    }
    return iter->second.c_str();
}

KeyIntention keyItemsTransKeyIntention(const std::vector<KeyCode> &items)
{
    if (items.size() < KEY_INTENTION_ITEM_MIN_COUNT || items.size() > KEY_INTENTION_ITEM_MAX_COUNT) {
        return KeyIntention::INTENTION_UNKNOWN;
    }

    uint64_t keyCodes = 0;
    for (const auto &item : items) {
        keyCodes = (keyCodes << KEY_INTENTION_OFFSET) + static_cast<uint64_t>(item);
    }

    const static std::map<int64_t, KeyIntention> MAP_KEY_INTENTION = {
        {(int64_t)KeyCode::KEY_DPAD_UP, KeyIntention::INTENTION_UP},
        {(int64_t)KeyCode::KEY_DPAD_DOWN, KeyIntention::INTENTION_DOWN},
        {(int64_t)KeyCode::KEY_DPAD_LEFT, KeyIntention::INTENTION_LEFT},
        {(int64_t)KeyCode::KEY_DPAD_RIGHT, KeyIntention::INTENTION_RIGHT},
        {(int64_t)KeyCode::KEY_SPACE, KeyIntention::INTENTION_SELECT},
        {(int64_t)KeyCode::KEY_NUMPAD_ENTER, KeyIntention::INTENTION_SELECT},
        {(int64_t)KeyCode::KEY_ESCAPE, KeyIntention::INTENTION_ESCAPE},
        {((int64_t)KeyCode::KEY_ALT_LEFT << KEY_INTENTION_OFFSET) + (int64_t)KeyCode::KEY_DPAD_LEFT,
            KeyIntention::INTENTION_BACK},
        {((int64_t)KeyCode::KEY_ALT_LEFT << KEY_INTENTION_OFFSET) + (int64_t)KeyCode::KEY_DPAD_RIGHT,
            KeyIntention::INTENTION_FORWARD},
        {((int64_t)KeyCode::KEY_ALT_RIGHT << KEY_INTENTION_OFFSET) + (int64_t)KeyCode::KEY_DPAD_LEFT,
            KeyIntention::INTENTION_BACK},
        {((int64_t)KeyCode::KEY_ALT_RIGHT << KEY_INTENTION_OFFSET) + (int64_t)KeyCode::KEY_DPAD_RIGHT,
            KeyIntention::INTENTION_FORWARD},
        {((int64_t)KeyCode::KEY_SHIFT_LEFT << KEY_INTENTION_OFFSET) + (int64_t)KeyCode::KEY_F10,
            KeyIntention::INTENTION_MENU},
        {((int64_t)KeyCode::KEY_SHIFT_RIGHT << KEY_INTENTION_OFFSET) + (int64_t)KeyCode::KEY_F10,
            KeyIntention::INTENTION_MENU},
        {KEY_COMPOSE, KeyIntention::INTENTION_MENU},
        {(int64_t)KeyCode::KEY_PAGE_UP, KeyIntention::INTENTION_PAGE_UP},
        {(int64_t)KeyCode::KEY_PAGE_DOWN, KeyIntention::INTENTION_PAGE_DOWN},
        {((int64_t)KeyCode::KEY_CTRL_LEFT << KEY_INTENTION_OFFSET) + (int64_t)KeyCode::KEY_PLUS,
            KeyIntention::INTENTION_ZOOM_OUT},
        {((int64_t)KeyCode::KEY_CTRL_RIGHT << KEY_INTENTION_OFFSET) + (int64_t)KeyCode::KEY_PLUS,
            KeyIntention::INTENTION_ZOOM_OUT},
        {((int64_t)KeyCode::KEY_CTRL_LEFT << KEY_INTENTION_OFFSET) + (int64_t)KeyCode::KEY_NUMPAD_ADD,
            KeyIntention::INTENTION_ZOOM_OUT},
        {((int64_t)KeyCode::KEY_CTRL_RIGHT << KEY_INTENTION_OFFSET) + (int64_t)KeyCode::KEY_NUMPAD_ADD,
            KeyIntention::INTENTION_ZOOM_OUT},
        {((int64_t)KeyCode::KEY_CTRL_LEFT << KEY_INTENTION_OFFSET) + (int64_t)KeyCode::KEY_MINUS,
            KeyIntention::INTENTION_ZOOM_IN},
        {((int64_t)KeyCode::KEY_CTRL_RIGHT << KEY_INTENTION_OFFSET) + (int64_t)KeyCode::KEY_MINUS,
            KeyIntention::INTENTION_ZOOM_IN},
        {((int64_t)KeyCode::KEY_CTRL_LEFT << KEY_INTENTION_OFFSET) + (int64_t)KeyCode::KEY_NUMPAD_SUBTRACT,
            KeyIntention::INTENTION_ZOOM_IN},
        {((int64_t)KeyCode::KEY_CTRL_RIGHT << KEY_INTENTION_OFFSET) + (int64_t)KeyCode::KEY_NUMPAD_SUBTRACT,
            KeyIntention::INTENTION_ZOOM_IN},
        {(int64_t)KeyCode::KEY_VOLUME_MUTE, KeyIntention::INTENTION_MEDIA_MUTE},
        {(int64_t)KeyCode::KEY_MUTE, KeyIntention::INTENTION_MEDIA_MUTE},
        {(int64_t)KeyCode::KEY_VOLUME_UP, KeyIntention::INTENTION_VOLUTE_UP},
        {(int64_t)KeyCode::KEY_VOLUME_DOWN, KeyIntention::INTENTION_VOLUTE_DOWN},
        {(int64_t)KeyCode::KEY_APPSELECT, KeyIntention::INTENTION_SELECT},
        {(int64_t)KeyCode::KEY_BACK, KeyIntention::INTENTION_BACK},
        {(int64_t)KeyCode::KEY_MOVE_HOME, KeyIntention::INTENTION_HOME},
    };

    auto iter = MAP_KEY_INTENTION.find(static_cast<int64_t>(keyCodes));
    if (iter == MAP_KEY_INTENTION.end()) {
        return KeyIntention::INTENTION_UNKNOWN;
    }
    return iter->second;
}

std::vector<KeyEvent> KeyEventRecognizer::GetKeyEvents(int32_t keyCode, int32_t keyAction, int32_t repeatTime,
    int64_t timeStamp, int64_t timeStampStart, int32_t metaKey, int32_t keySource, int64_t deviceId,
    std::string msg)
{
    if (timeStamp == 0) {
        timeStamp = clock();
    }
    std::vector<KeyEvent> keyEvents;
    auto event = KeyEvent(static_cast<KeyCode>(keyCode), static_cast<KeyAction>(keyAction), repeatTime,
        timeStamp, deviceId, static_cast<SourceType>(keySource));

    if ((keyCode != static_cast<int32_t>(KeyCode::KEY_UNKNOWN)) &&
        (keyAction == static_cast<int32_t>(KeyAction::DOWN))) {
        clearPressedKey();
        if (static_cast<uint32_t>(metaKey) & static_cast<uint32_t>(CtrlKeysBit::CTRL)) {
            addPressedKey(static_cast<int32_t>(KeyCode::KEY_CTRL_LEFT));
        }
        if (static_cast<uint32_t>(metaKey) & static_cast<uint32_t>(CtrlKeysBit::SHIFT)) {
            addPressedKey(static_cast<int32_t>(KeyCode::KEY_SHIFT_LEFT));
        }
        if (static_cast<uint32_t>(metaKey) & static_cast<uint32_t>(CtrlKeysBit::ALT)) {
            addPressedKey(static_cast<int32_t>(KeyCode::KEY_ALT_LEFT));
        }
        addPressedKey(keyCode);
    }
    auto keyItems = getPressedKeys();
    event.keyIntention = keyItemsTransKeyIntention(keyItems);
    if ((keyCode != static_cast<int32_t>(KeyCode::KEY_UNKNOWN)) &&
        (keyAction == static_cast<int32_t>(KeyAction::UP))) {
        removeReleasedKey(keyCode);
    }
    event.pressedCodes = getPressedKeys();
    event.key = KeyCodeToString(keyCode);
    event.msg = msg;

    keyEvents.emplace_back(event);
    auto result = keyMap_.try_emplace(keyCode, false);
    auto iter = result.first;

    // Recognize long press event.
    if ((keyAction == static_cast<int32_t>(KeyAction::DOWN)) && (repeatTime >= LONG_PRESS_DURATION) &&
        (!iter->second)) {
        iter->second = true;
        keyEvents.emplace_back(KeyEvent(static_cast<KeyCode>(keyCode), KeyAction::LONG_PRESS, repeatTime, timeStamp,
            deviceId, static_cast<SourceType>(keySource)));
    }
    // Recognize click event.
    if (keyAction == static_cast<int32_t>(KeyAction::UP)) {
        if (iter->second) {
            iter->second = false;
        } else {
            keyEvents.emplace_back(KeyEvent(static_cast<KeyCode>(keyCode), KeyAction::CLICK, repeatTime, timeStamp,
                deviceId, static_cast<SourceType>(keySource)));
        }
    }
    return keyEvents;
}

std::vector<KeyCode> KeyEventRecognizer::getPressedKeys() const
{
    std::vector<KeyCode> result;
    for (const auto &item : keys_) {
        result.push_back(static_cast<KeyCode>(item));
    }
    return result;
}

void KeyEventRecognizer::addPressedKey(const int32_t keyCode)
{
    std::vector<KeyCode> pressedkeys = getPressedKeys();
    std::vector<KeyCode>::iterator result = std::find(pressedkeys.begin(),
        pressedkeys.end(), static_cast<KeyCode>(keyCode));
    if (result == pressedkeys.end()) {
        keys_.push_back(keyCode);
    }
}

void KeyEventRecognizer::removeReleasedKey(const int32_t keyCode)
{
    for (auto it = keys_.begin(); it != keys_.end(); ++it) {
        if (*it == keyCode) {
            keys_.erase(it);
            return;
        }
    }
}

void KeyEventRecognizer::clearPressedKey()
{
    keys_.clear();
}
} // namespace OHOS::Ace
