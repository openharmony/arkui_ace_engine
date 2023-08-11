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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_TEXT_FIELD_KEYEVENT_HANDLER_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_TEXT_FIELD_KEYEVENT_HANDLER_H

#include <algorithm>
#include <functional>
#include <string>
#include <unordered_map>

#include "base/utils/string_utils.h"
#include "core/components_ng/pattern/pattern.h"
#include "core/event/key_event.h"

namespace OHOS::Ace::NG {
const wchar_t UPPER_CASE_A = L'A';
const wchar_t LOWER_CASE_A = L'a';
const wchar_t CASE_0 = L'0';
const std::wstring NUM_SYMBOLS = L")!@#$%^&*(";
const std::unordered_map<KeyCode, wchar_t> KEYBOARD_SYMBOLS = {
    { KeyCode::KEY_GRAVE, L'`' },
    { KeyCode::KEY_MINUS, L'-' },
    { KeyCode::KEY_EQUALS, L'=' },
    { KeyCode::KEY_LEFT_BRACKET, L'[' },
    { KeyCode::KEY_RIGHT_BRACKET, L']' },
    { KeyCode::KEY_BACKSLASH, L'\\' },
    { KeyCode::KEY_SEMICOLON, L';' },
    { KeyCode::KEY_APOSTROPHE, L'\'' },
    { KeyCode::KEY_COMMA, L',' },
    { KeyCode::KEY_PERIOD, L'.' },
    { KeyCode::KEY_SLASH, L'/' },
    { KeyCode::KEY_SPACE, L' ' },
    { KeyCode::KEY_NUMPAD_DIVIDE, L'/' },
    { KeyCode::KEY_NUMPAD_MULTIPLY, L'*' },
    { KeyCode::KEY_NUMPAD_SUBTRACT, L'-' },
    { KeyCode::KEY_NUMPAD_ADD, L'+' },
    { KeyCode::KEY_NUMPAD_DOT, L'.' },
    { KeyCode::KEY_NUMPAD_COMMA, L',' },
    { KeyCode::KEY_NUMPAD_EQUALS, L'=' },
};

static const std::unordered_map<KeyCode, wchar_t> SHIFT_KEYBOARD_SYMBOLS = {
    { KeyCode::KEY_GRAVE, L'~' },
    { KeyCode::KEY_MINUS, L'_' },
    { KeyCode::KEY_EQUALS, L'+' },
    { KeyCode::KEY_LEFT_BRACKET, L'{' },
    { KeyCode::KEY_RIGHT_BRACKET, L'}' },
    { KeyCode::KEY_BACKSLASH, L'|' },
    { KeyCode::KEY_SEMICOLON, L':' },
    { KeyCode::KEY_APOSTROPHE, L'\"' },
    { KeyCode::KEY_COMMA, L'<' },
    { KeyCode::KEY_PERIOD, L'>' },
    { KeyCode::KEY_SLASH, L'?' },
};

class KeyEventHandler : public AceType {
    DECLARE_ACE_TYPE(KeyEventHandler, AceType)

public:
    KeyEventHandler() = default;
    ~KeyEventHandler() = default;

    void UpdateWeakPattern(const WeakPtr<Pattern>& pattern)
    {
        weakPattern_ = pattern;
    }

    void ClearClient()
    {
        weakPattern_ = nullptr;
    }

    bool HandleKeyEvent(const KeyEvent& keyEvent);

private:
    bool HandleShiftPressedEvent(const KeyEvent& event);
    bool HandleDirectionalKey(const KeyEvent& keyEvent);
    bool HandleDirectionalMoveKey(const KeyEvent& keyEvent);
    void ParseAppendValue(KeyCode keycode, std::string& appendElement);
    bool IsCtrlShiftWith(const KeyEvent& keyEvent, const KeyCode expectCode);
    WeakPtr<Pattern> weakPattern_;
    ACE_DISALLOW_COPY_AND_MOVE(KeyEventHandler);
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_TEXT_FIELD_KEYEVENT_HANDLER_H