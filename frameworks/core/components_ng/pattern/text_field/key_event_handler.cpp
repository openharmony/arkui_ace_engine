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

#include "core/components_ng/pattern/text_field/key_event_handler.h"

#include "core/components_ng/pattern/text_field/text_field_pattern.h"

namespace OHOS::Ace::NG {
bool KeyEventHandler::HandleKeyEvent(const KeyEvent& keyEvent)
{
    auto pattern = DynamicCast<TextFieldPattern>(weakPattern_.Upgrade());
    CHECK_NULL_RETURN(pattern, false);
    if (!pattern->GetCursorVisible()) {
        return false;
    }
    if (keyEvent.action == KeyAction::DOWN) {
        std::string appendElement;
        if (keyEvent.code == KeyCode::KEY_ENTER || keyEvent.code == KeyCode::KEY_NUMPAD_ENTER ||
            keyEvent.code == KeyCode::KEY_DPAD_CENTER) {
            if (pattern->GetKeyboard() != TextInputType::MULTILINE) {
                pattern->PerformAction(pattern->GetTextInputActionValue(TextInputAction::DONE), false);
                return true;
            }
        } else if (HandleShiftPressedEvent(keyEvent)) {
            return true;
        } else if (keyEvent.IsDirectionalKey()) {
            HandleDirectionalKey(keyEvent);
            return true;
        } else if (keyEvent.IsNumberKey()) {
            appendElement = keyEvent.ConvertCodeToString();
        } else if (keyEvent.IsLetterKey()) {
            if (keyEvent.IsKey({ KeyCode::KEY_CTRL_LEFT, KeyCode::KEY_SHIFT_LEFT, KeyCode::KEY_Z }) ||
                keyEvent.IsKey({ KeyCode::KEY_CTRL_LEFT, KeyCode::KEY_SHIFT_RIGHT, KeyCode::KEY_Z }) ||
                keyEvent.IsKey({ KeyCode::KEY_CTRL_RIGHT, KeyCode::KEY_SHIFT_LEFT, KeyCode::KEY_Z }) ||
                keyEvent.IsKey({ KeyCode::KEY_CTRL_RIGHT, KeyCode::KEY_SHIFT_RIGHT, KeyCode::KEY_Z }) ||
                keyEvent.IsKey({ KeyCode::KEY_CTRL_LEFT, KeyCode::KEY_Y }) ||
                keyEvent.IsKey({ KeyCode::KEY_CTRL_RIGHT, KeyCode::KEY_Y })) {
                pattern->HandleOnRedoAction();
            } else if (keyEvent.IsKey({ KeyCode::KEY_CTRL_LEFT, KeyCode::KEY_Z }) ||
                       keyEvent.IsKey({ KeyCode::KEY_CTRL_RIGHT, KeyCode::KEY_Z })) {
                pattern->HandleOnUndoAction();
            } else if (keyEvent.IsKey({ KeyCode::KEY_CTRL_LEFT, KeyCode::KEY_A }) ||
                       keyEvent.IsKey({ KeyCode::KEY_CTRL_RIGHT, KeyCode::KEY_A })) {
                pattern->HandleOnSelectAll();
            } else if (keyEvent.IsKey({ KeyCode::KEY_CTRL_LEFT, KeyCode::KEY_C }) ||
                       keyEvent.IsKey({ KeyCode::KEY_CTRL_RIGHT, KeyCode::KEY_C })) {
                pattern->HandleOnCopy();
            } else if (keyEvent.IsKey({ KeyCode::KEY_CTRL_LEFT, KeyCode::KEY_V }) ||
                       keyEvent.IsKey({ KeyCode::KEY_CTRL_RIGHT, KeyCode::KEY_V })) {
                pattern->HandleOnPaste();
            } else if (keyEvent.IsKey({ KeyCode::KEY_CTRL_LEFT, KeyCode::KEY_X }) ||
                       keyEvent.IsKey({ KeyCode::KEY_CTRL_RIGHT, KeyCode::KEY_X })) {
                pattern->HandleOnCut();
            } else {
                appendElement = keyEvent.ConvertCodeToString();
            }
        }
        if (keyEvent.code == KeyCode::KEY_DEL) {
#if defined(PREVIEW)
            pattern->DeleteForward(TextFieldPattern::GetGraphemeClusterLength(
                pattern->GetEditingValue().GetWideText(), pattern->GetEditingValue().caretPosition));
#else
            pattern->DeleteBackward(TextFieldPattern::GetGraphemeClusterLength(
                pattern->GetEditingValue().GetWideText(), pattern->GetEditingValue().caretPosition, true));
#endif
            return true;
        }
        if (keyEvent.code == KeyCode::KEY_FORWARD_DEL) {
#if defined(PREVIEW)
            pattern->DeleteBackward(TextFieldPattern::GetGraphemeClusterLength(
                pattern->GetEditingValue().GetWideText(), pattern->GetEditingValue().caretPosition, true));
#else
            pattern->DeleteForward(TextFieldPattern::GetGraphemeClusterLength(
                pattern->GetEditingValue().GetWideText(), pattern->GetEditingValue().caretPosition));
#endif
            return true;
        }
        ParseAppendValue(keyEvent.code, appendElement);
        if (!appendElement.empty()) {
            pattern->InsertValue(appendElement);
            return true;
        }
    }
    return false;
}

void KeyEventHandler::ParseAppendValue(KeyCode keycode, std::string& appendElement)
{
    switch (keycode) {
        case KeyCode::KEY_SPACE:
            appendElement = " ";
            break;
        default:
            break;
    }
}

bool KeyEventHandler::HandleDirectionalKey(const KeyEvent& keyEvent)
{
    auto pattern = DynamicCast<TextFieldPattern>(weakPattern_.Upgrade());
    CHECK_NULL_RETURN(pattern, false);
    bool updateSelection = false;
    if (keyEvent.IsKey({ KeyCode::KEY_SHIFT_LEFT, KeyCode::KEY_DPAD_UP }) ||
        keyEvent.IsKey({ KeyCode::KEY_SHIFT_RIGHT, KeyCode::KEY_DPAD_UP })) {
        pattern->HandleSelectionUp();
        updateSelection = true;
    } else if (keyEvent.IsKey({ KeyCode::KEY_SHIFT_LEFT, KeyCode::KEY_DPAD_DOWN }) ||
               keyEvent.IsKey({ KeyCode::KEY_SHIFT_RIGHT, KeyCode::KEY_DPAD_DOWN })) {
        pattern->HandleSelectionDown();
        updateSelection = true;
    } else if (keyEvent.IsKey({ KeyCode::KEY_SHIFT_LEFT, KeyCode::KEY_DPAD_LEFT }) ||
               keyEvent.IsKey({ KeyCode::KEY_SHIFT_RIGHT, KeyCode::KEY_DPAD_LEFT })) {
        pattern->HandleSelectionLeft();
        updateSelection = true;
    } else if (keyEvent.IsKey({ KeyCode::KEY_SHIFT_LEFT, KeyCode::KEY_DPAD_RIGHT }) ||
               keyEvent.IsKey({ KeyCode::KEY_SHIFT_RIGHT, KeyCode::KEY_DPAD_RIGHT })) {
        pattern->HandleSelectionRight();
        updateSelection = true;
    }
    if (updateSelection) {
        return true;
    }
    bool handleDirectionalKey = false;
    switch (keyEvent.code) {
        case KeyCode::KEY_DPAD_UP:
            handleDirectionalKey = pattern->CursorMoveUp();
            break;
        case KeyCode::KEY_DPAD_DOWN:
            handleDirectionalKey = pattern->CursorMoveDown();
            break;
        case KeyCode::KEY_DPAD_LEFT:
            handleDirectionalKey = pattern->CursorMoveLeft();
            break;
        case KeyCode::KEY_DPAD_RIGHT:
            handleDirectionalKey = pattern->CursorMoveRight();
            break;
        default:
            LOGW("Unknown direction");
    }
    return handleDirectionalKey;
}

bool KeyEventHandler::HandleShiftPressedEvent(const KeyEvent& event)
{
    auto pattern = DynamicCast<TextFieldPattern>(weakPattern_.Upgrade());
    CHECK_NULL_RETURN(pattern, false);
    const static size_t maxKeySizes = 2;
    wchar_t keyChar;

    auto iterCode = KEYBOARD_SYMBOLS.find(event.code);
    if (event.pressedCodes.size() == 1 && iterCode != KEYBOARD_SYMBOLS.end()) {
        if (iterCode != KEYBOARD_SYMBOLS.end()) {
            keyChar = iterCode->second;
        } else {
            return false;
        }
    } else if (event.pressedCodes.size() == maxKeySizes && (event.pressedCodes[0] == KeyCode::KEY_SHIFT_LEFT ||
                                                               event.pressedCodes[0] == KeyCode::KEY_SHIFT_RIGHT)) {
        iterCode = SHIFT_KEYBOARD_SYMBOLS.find(event.code);
        if (iterCode != SHIFT_KEYBOARD_SYMBOLS.end()) {
            keyChar = iterCode->second;
        } else if (KeyCode::KEY_A <= event.code && event.code <= KeyCode::KEY_Z) {
            keyChar = static_cast<wchar_t>(event.code) - static_cast<wchar_t>(KeyCode::KEY_A) + UPPER_CASE_A;
        } else if (KeyCode::KEY_0 <= event.code && event.code <= KeyCode::KEY_9) {
            keyChar = NUM_SYMBOLS[static_cast<int32_t>(event.code) - static_cast<int32_t>(KeyCode::KEY_0)];
        } else {
            return false;
        }
    } else {
        return false;
    }
    std::wstring appendElement(1, keyChar);
    pattern->InsertValue(StringUtils::ToString(appendElement));
    return true;
}

} // namespace OHOS::Ace::NG
