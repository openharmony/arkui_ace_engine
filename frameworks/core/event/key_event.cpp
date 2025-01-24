/*
 * Copyright (c) 2021 Huawei Device Co., Ltd.
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

#include "core/event/key_event.h"

namespace OHOS::Ace {

namespace {

// key : define aosp key event code, value : define ace key string
constexpr int32_t KEYCODE_SIZE = 289;
const char* g_aospKeycode2String[KEYCODE_SIZE] = { "Unknown", "SoftLeft", "SoftRight", "Home", "Back", "Call",
    "EndCall", "Digit0", "Digit1", "Digit2", "Digit3", "Digit4", "Digit5", "Digit6", "Digit7", "Digit8", "Digit9",
    "Star", "Pound", "DpadUp", "DpadDown", "DpadLeft", "DpadRight", "DpadCenter", "VolumeUp", "VolumeDown", "Power",
    "Camera", "Clear", "KeyA", "KeyB", "KeyC", "KeyD", "KeyE", "KeyF", "KeyG", "KeyH", "KeyI", "KeyJ", "KeyK", "KeyL",
    "KeyM", "KeyN", "KeyO", "KeyP", "KeyQ", "KeyR", "KeyS", "KeyT", "KeyU", "KeyV", "KeyW", "KeyX", "KeyY", "KeyZ",
    "Comma", "Period", "AltLeft", "AltRight", "ShiftLeft", "ShiftRight", "Tab", "Space", "Sym", "Explorer", "Envelope",
    "Enter", "Del", "Grave", "Minus", "Equals", "LeftBracket", "RightBracket", "BackSlash", "Semicolon", "Apostrophe",
    "Slash", "At", "Num", "HeadsetHook", "Focus", "Plus", "Menu", "Notification", "Search", "MediaPlayPause",
    "MediaStop", "MediaNext", "MediaPrevious", "MediaRewind", "MediaFastForward", "Mute", "PageUp", "PageDown",
    "PictSymbols", "SwitchCharset", "ButtonA", "ButtonB", "ButtonC", "ButtonX", "ButtonY", "ButtonZ", "ButtonL1",
    "ButtonR1", "ButtonL2", "ButtonR2", "ButtonThumbl", "ButtonThumbr", "ButtonStart", "ButtonSelect", "ButtonMode",
    "Escape", "ForwardDel", "CtrlLeft", "CtrlRight", "CapsLock", "ScrollLock", "MetaLeft", "MetaRight", "Function",
    "SysRq", "Break", "MoveHome", "MoveEnd", "Insert", "Forward", "MediaPlay", "MediaPause", "MediaClose",
    "MediaReject", "MediaRecord", "F1", "F2", "F3", "F4", "F5", "F6", "F7", "F8", "F9", "F10", "F11", "F12", "NumLock",
    "Numpad0", "Numpad1", "Numpad2", "Numpad3", "Numpad4", "Numpad5", "Numpad6", "Numpad7", "Numpad8", "NumPad9",
    "NumpadDivide", "NumpadMultiply", "NumpadSubtract", "NumpadAdd", "NumpadDot", "NumpadComma", "NumpadEnter",
    "NumpadEquals", "NumpadLeftParen", "NumpadRightParen", "VolumeMute", "Info", "ChannelUp", "ChannelDown", "ZoomIn",
    "ZoomOut", "Tv", "Window", "Guide", "Dvr", "BookMark", "Captions", "Settings", "TvPower", "TvInput", "StbPower",
    "StbInput", "AvrPower", "AvrInput", "ProgRed", "ProgGreen", "ProgYellow", "ProgBlue", "AppSwitch", "Button1",
    "Button2", "Button3", "Button4", "Button5", "Button6", "Button7", "Button8", "Button9", "Button10", "Button11",
    "Button12", "Button13", "Button14", "Button15", "Button16", "LanguageSwitch", "MannerMode", "3DMode", "Contacts",
    "Calendar", "Music", "Calculator", "ZenkakuHankaku", "Eisu", "Muhenkan", "Henkan", "KatakanaHiragana", "Yen", "Ro",
    "Kana", "Assist", "BrightnessDown", "BrightnessUp", "MediaAudioTrack", "Sleep", "WakeUp", "Pairing", "MediaTopMenu",
    "Digit11", "Digit12", "LastChannel", "TvDataService", "VoiceAssist", "TvRadioService", "TvTeletext",
    "TvNumberEntry", "TvTerrestrialAnalog", "TvTerrestrialDigital", "TvSatellite", "TvSatelliteBS", "TvSatelliteCS",
    "TvSatelliteService", "TvNetWork", "TvAntennaCable", "TvInputHdmi1", "TvInputHdmi2", "TvInputHdmi3", "TvInputHdmi4",
    "TvInputComposite1", "TvInputComposite2", "TvInputComponent1", "TvInputComponent2", "TvInputVGA1",
    "TvAudioDescription", "TvAudioDescriptionMixUp", "TvAudioDescriptionMixDown", "TvZoomMode", "TvContentsMenu",
    "TvMediaContextMenu", "TvTimerProgramming", "Help", "NavigatePrevious", "NavigateNext", "NavigateIn", "NavigateOut",
    "StemPrimary", "Stem1", "Stem2", "Stem3", "DpadUpLeft", "DpadDownLeft", "DpadUpRight", "DpadDownRight",
    "MediaSkipForward", "MediaSkipBackward", "MediaStepForward", "MediaStepBackward", "SoftSleep", "Cut", "Copy",
    "Paste", "SystemNavigationUp", "SystemNavigationDown", "SystemNavigationLeft", "SystemNavigationRight", "AllApps",
    "Refresh", "ThumbsUp", "ThumbsDown", "ProfileSwitch" };

const std::unordered_map<KeyCode, char> KEYBOARD_SYMBOLS = {
    { KeyCode::KEY_GRAVE, '`' },
    { KeyCode::KEY_MINUS, '-' },
    { KeyCode::KEY_EQUALS, '=' },
    { KeyCode::KEY_LEFT_BRACKET, '[' },
    { KeyCode::KEY_RIGHT_BRACKET, ']' },
    { KeyCode::KEY_BACKSLASH, '\\' },
    { KeyCode::KEY_SEMICOLON, ';' },
    { KeyCode::KEY_APOSTROPHE, '\'' },
    { KeyCode::KEY_COMMA, ',' },
    { KeyCode::KEY_PERIOD, '.' },
    { KeyCode::KEY_SLASH, '/' },
    { KeyCode::KEY_SPACE, ' ' },
    { KeyCode::KEY_NUMPAD_DIVIDE, '/' },
    { KeyCode::KEY_NUMPAD_MULTIPLY, '*' },
    { KeyCode::KEY_NUMPAD_SUBTRACT, '-' },
    { KeyCode::KEY_NUMPAD_ADD, '+' },
    { KeyCode::KEY_NUMPAD_COMMA, ',' },
    { KeyCode::KEY_NUMPAD_EQUALS, '=' },
};

const std::unordered_map<KeyCode, char> SHIFT_KEYBOARD_SYMBOLS = {
    { KeyCode::KEY_GRAVE, '~' },
    { KeyCode::KEY_MINUS, '_' },
    { KeyCode::KEY_EQUALS, '+' },
    { KeyCode::KEY_LEFT_BRACKET, '{' },
    { KeyCode::KEY_RIGHT_BRACKET, '}' },
    { KeyCode::KEY_BACKSLASH, '|' },
    { KeyCode::KEY_SEMICOLON, ':' },
    { KeyCode::KEY_APOSTROPHE, '\"' },
    { KeyCode::KEY_COMMA, '<' },
    { KeyCode::KEY_PERIOD, '>' },
    { KeyCode::KEY_SLASH, '?' },
};

} // namespace



const char* KeyToString(int32_t code)
{
    if (code >= 0 && code < KEYCODE_SIZE) {
        return g_aospKeycode2String[code];
    } else {
        return g_aospKeycode2String[0]; // "UnKnown"
    }
}

std::string KeyEvent::ConvertInputCodeToString() const
{
    static const std::map<KeyCode, std::string> VISIBILITY_CODE = { { KeyCode::KEY_0, "0)" }, { KeyCode::KEY_1, "1!" },
        { KeyCode::KEY_2, "2@" }, { KeyCode::KEY_3, "3#" }, { KeyCode::KEY_4, "4$" }, { KeyCode::KEY_5, "5%" },
        { KeyCode::KEY_6, "6^" }, { KeyCode::KEY_7, "7&" }, { KeyCode::KEY_8, "8*" }, { KeyCode::KEY_9, "9(" },
        { KeyCode::KEY_COMMA, ",<" }, { KeyCode::KEY_PERIOD, ".>" }, { KeyCode::KEY_GRAVE, "`~" },
        { KeyCode::KEY_MINUS, "-_" }, { KeyCode::KEY_EQUALS, "=+" }, { KeyCode::KEY_LEFT_BRACKET, "[{" },
        { KeyCode::KEY_RIGHT_BRACKET, "]}" }, { KeyCode::KEY_BACKSLASH, "\\|" }, { KeyCode::KEY_SEMICOLON, ";:" },
        { KeyCode::KEY_APOSTROPHE, "\'\"" }, { KeyCode::KEY_SLASH, "/?" }, { KeyCode::KEY_AT, "@" },
        { KeyCode::KEY_PLUS, "+=" }, { KeyCode::KEY_NUMPAD_DIVIDE, "/" }, { KeyCode::KEY_NUMPAD_MULTIPLY, "*" },
        { KeyCode::KEY_NUMPAD_SUBTRACT, "-" }, { KeyCode::KEY_NUMPAD_ADD, "+" }, { KeyCode::KEY_NUMPAD_DOT, "." },
        { KeyCode::KEY_NUMPAD_COMMA, "," }, { KeyCode::KEY_NUMPAD_EQUALS, "=" }, { KeyCode::KEY_TAB, "TAB" },
        { KeyCode::KEY_SPACE, " " }, { KeyCode::KEY_ESCAPE, "ESC" }, { KeyCode::KEY_F1, "F1" },
        { KeyCode::KEY_F2, "F2" }, { KeyCode::KEY_F3, "F3" }, { KeyCode::KEY_F4, "F4" }, { KeyCode::KEY_F5, "F5" },
        { KeyCode::KEY_F6, "F6" }, { KeyCode::KEY_F7, "F7" }, { KeyCode::KEY_F8, "F8" }, { KeyCode::KEY_F9, "F9" },
        { KeyCode::KEY_F10, "F10" }, { KeyCode::KEY_F11, "F11" }, { KeyCode::KEY_F12, "F12" },
        { KeyCode::KEY_DPAD_UP, "DPAD_UP" }, { KeyCode::KEY_DPAD_DOWN, "DPAD_DOWN" },
        { KeyCode::KEY_DPAD_LEFT, "DPAD_LEFT" }, { KeyCode::KEY_DPAD_RIGHT, "DPAD_RIGHT" } };
    if (KeyCode::KEY_NUMPAD_0 <= code && code <= KeyCode::KEY_NUMPAD_9) {
        return std::to_string(static_cast<int32_t>(code) - static_cast<int32_t>(KeyCode::KEY_NUMPAD_0));
    }
    if (IsLetterKey()) {
        int32_t codeValue = static_cast<int32_t>(code) - static_cast<int32_t>(KeyCode::KEY_A);
        return std::string(1, static_cast<char>(codeValue + ASCII_START_UPPER_CASE_LETTER));
    }
    auto iter = VISIBILITY_CODE.find(code);
    if (iter != VISIBILITY_CODE.end()) {
        return iter->second;
    }
    return "";
}

std::string KeyEvent::ConvertCodeToString() const
{
    static const std::string NUM_SYMBOLS = ")!@#$%^&*(";

    if (KeyCode::KEY_0 <= code && code <= KeyCode::KEY_9) {
        if (IsShiftWith(code)) {
            return std::string(1, NUM_SYMBOLS[static_cast<int32_t>(code) - static_cast<int32_t>(KeyCode::KEY_0)]);
        }
        return std::to_string(static_cast<int32_t>(code) - static_cast<int32_t>(KeyCode::KEY_0));
    }
    if (numLock) {
        if (KeyCode::KEY_NUMPAD_0 <= code && code <= KeyCode::KEY_NUMPAD_9) {
            return std::to_string(static_cast<int32_t>(code) - static_cast<int32_t>(KeyCode::KEY_NUMPAD_0));
        } else if (code == KeyCode::KEY_NUMPAD_DOT) {
            return std::string(1, '.');
        }
    }
    if (IsLetterKey()) {
        int32_t codeValue = static_cast<int32_t>(code) - static_cast<int32_t>(KeyCode::KEY_A);
        auto shiftWithLetter = IsShiftWith(code);
        if ((shiftWithLetter || enableCapsLock) && !(shiftWithLetter && enableCapsLock)) {
            return std::string(1, static_cast<char>(codeValue + ASCII_START_UPPER_CASE_LETTER));
        }
        return std::string(1, static_cast<char>(codeValue + ASCII_START_LOWER_CASE_LETTER));
    }
    if (IsShiftWith(code)) {
        auto iterCode = SHIFT_KEYBOARD_SYMBOLS.find(code);
        if (iterCode != SHIFT_KEYBOARD_SYMBOLS.end()) {
            return std::string(1, iterCode->second);
        }
    }
    auto iterCode = KEYBOARD_SYMBOLS.find(code);
    if (iterCode != KEYBOARD_SYMBOLS.end()) {
        return std::string(1, iterCode->second);
    }
    return "";
}

void KeyEventInfo::ParseKeyEvent(KeyEvent& keyEvent)
{
    keyEvent.action = GetKeyType();
    keyEvent.code = GetKeyCode();
    keyEvent.key.assign(GetKeyText());
    keyEvent.sourceType = GetKeySource();
    keyEvent.deviceId = GetDeviceId();
    keyEvent.metaKey = GetMetaKey();
    keyEvent.unicode = GetUnicode();
    keyEvent.timeStamp = GetTimeStamp();
    keyEvent.keyIntention = GetKeyIntention();
    keyEvent.pressedCodes = GetPressedKeyCodes();
}

} // namespace OHOS::Ace