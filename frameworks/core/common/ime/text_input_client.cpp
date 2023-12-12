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

#include "core/common/ime/text_input_client.h"

#include <cstdint>
#include <functional>
#include <map>

#include "base/log/log_wrapper.h"
#include "core/event/key_event.h"

namespace OHOS::Ace {
namespace {
using tic = TextInputClient; // give it a shorter name to maintain a good code layout
}

// Here declares function keys which can be handled by TextInputClient.
std::map<KeyComb, std::function<bool(TextInputClient*)>> TextInputClient::functionKeys_ = {
    { KeyComb(KeyCode::KEY_ESCAPE), &tic::HandleOnEscape },
    { KeyComb(KeyCode::KEY_TAB), [](tic* c) -> bool { return c->HandleOnTab(false); } },
    { KeyComb(KeyCode::KEY_TAB, KEY_SHIFT), [](tic* c) -> bool { return c->HandleOnTab(true); } },
};

// Here declares keyboard shortcuts which should be handled and consumed by TextInputClient.
std::map<KeyComb, std::function<void(TextInputClient*)>> TextInputClient::keyboardShortCuts_ = {
// action combinations
#if defined(MAC_PLATFORM)
    { KeyComb(KeyCode::KEY_A, KEY_META), &tic::HandleOnSelectAll },
    { KeyComb(KeyCode::KEY_C, KEY_META), &tic::HandleOnCopy },
    { KeyComb(KeyCode::KEY_D, KEY_META), &tic::HandleOnDelete },
    { KeyComb(KeyCode::KEY_V, KEY_META), &tic::HandleOnPaste },
    { KeyComb(KeyCode::KEY_X, KEY_META), &tic::HandleOnCut },
    { KeyComb(KeyCode::KEY_Y, KEY_META), &tic::HandleOnRedoAction },
    { KeyComb(KeyCode::KEY_Z, KEY_META), &tic::HandleOnUndoAction },
    { KeyComb(KeyCode::KEY_Z, KEY_META | KEY_SHIFT), &tic::HandleOnRedoAction },
#else
    { KeyComb(KeyCode::KEY_A, KEY_CTRL), &tic::HandleOnSelectAll },
    { KeyComb(KeyCode::KEY_C, KEY_CTRL), &tic::HandleOnCopy },
    { KeyComb(KeyCode::KEY_D, KEY_CTRL), &tic::HandleOnDelete },
    { KeyComb(KeyCode::KEY_V, KEY_CTRL), &tic::HandleOnPaste },
    { KeyComb(KeyCode::KEY_X, KEY_CTRL), &tic::HandleOnCut },
    { KeyComb(KeyCode::KEY_Y, KEY_CTRL), &tic::HandleOnRedoAction },
    { KeyComb(KeyCode::KEY_Z, KEY_CTRL), &tic::HandleOnUndoAction },
    { KeyComb(KeyCode::KEY_Z, KEY_CTRL | KEY_SHIFT), &tic::HandleOnRedoAction },
#endif
    { KeyComb(KeyCode::KEY_INSERT, KEY_CTRL), &tic::HandleOnCopy },
    { KeyComb(KeyCode::KEY_INSERT, KEY_CTRL), &tic::HandleOnPaste },
    // caret move keys
    { KeyComb(KeyCode::KEY_DPAD_LEFT), [](tic* c) -> void { c->CursorMove(CaretMoveIntent::Left); } },
    { KeyComb(KeyCode::KEY_DPAD_RIGHT), [](tic* c) -> void { c->CursorMove(CaretMoveIntent::Right); } },
    { KeyComb(KeyCode::KEY_DPAD_UP), [](tic* c) -> void { c->CursorMove(CaretMoveIntent::Up); } },
    { KeyComb(KeyCode::KEY_DPAD_DOWN), [](tic* c) -> void { c->CursorMove(CaretMoveIntent::Down); } },
    { KeyComb(KeyCode::KEY_MOVE_HOME), [](tic* c) -> void { c->CursorMove(CaretMoveIntent::LineBegin); } },
    { KeyComb(KeyCode::KEY_MOVE_END), [](tic* c) -> void { c->CursorMove(CaretMoveIntent::LineEnd); } },
    { KeyComb(KeyCode::KEY_DPAD_LEFT, KEY_CTRL), [](tic* c) -> void { c->CursorMove(CaretMoveIntent::LeftWord); } },
    { KeyComb(KeyCode::KEY_DPAD_RIGHT, KEY_CTRL), [](tic* c) -> void { c->CursorMove(CaretMoveIntent::RightWord); } },
    { KeyComb(KeyCode::KEY_DPAD_UP, KEY_CTRL), [](tic* c) -> void { c->CursorMove(CaretMoveIntent::ParagraghBegin); } },
    { KeyComb(KeyCode::KEY_DPAD_DOWN, KEY_CTRL), [](tic* c) -> void { c->CursorMove(CaretMoveIntent::ParagraghEnd); } },
    { KeyComb(KeyCode::KEY_MOVE_HOME, KEY_CTRL), [](tic* c) -> void { c->CursorMove(CaretMoveIntent::Home); } },
    { KeyComb(KeyCode::KEY_MOVE_END, KEY_CTRL), [](tic* c) -> void { c->CursorMove(CaretMoveIntent::End); } },
    // select key combinations
    { KeyComb(KeyCode::KEY_DPAD_LEFT, KEY_SHIFT), [](tic* c) -> void { c->HandleSelect(CaretMoveIntent::Left); } },
    { KeyComb(KeyCode::KEY_DPAD_RIGHT, KEY_SHIFT), [](tic* c) -> void { c->HandleSelect(CaretMoveIntent::Right); } },
    { KeyComb(KeyCode::KEY_DPAD_UP, KEY_SHIFT), [](tic* c) -> void { c->HandleSelect(CaretMoveIntent::Up); } },
    { KeyComb(KeyCode::KEY_DPAD_DOWN, KEY_SHIFT), [](tic* c) -> void { c->HandleSelect(CaretMoveIntent::Down); } },
    { KeyComb(KeyCode::KEY_MOVE_HOME, KEY_SHIFT), [](tic* c) -> void { c->HandleSelect(CaretMoveIntent::LineBegin); } },
    { KeyComb(KeyCode::KEY_MOVE_END, KEY_SHIFT), [](tic* c) -> void { c->HandleSelect(CaretMoveIntent::LineEnd); } },
    { KeyComb(KeyCode::KEY_DPAD_LEFT, KEY_CTRL | KEY_SHIFT),
        [](tic* c) -> void { c->CursorMove(CaretMoveIntent::LeftWord); } },
    { KeyComb(KeyCode::KEY_DPAD_RIGHT, KEY_CTRL | KEY_SHIFT),
        [](tic* c) -> void { c->CursorMove(CaretMoveIntent::RightWord); } },
    { KeyComb(KeyCode::KEY_DPAD_UP, KEY_CTRL | KEY_SHIFT),
        [](tic* c) -> void { c->CursorMove(CaretMoveIntent::ParagraghBegin); } },
    { KeyComb(KeyCode::KEY_DPAD_DOWN, KEY_CTRL | KEY_SHIFT),
        [](tic* c) -> void { c->CursorMove(CaretMoveIntent::ParagraghEnd); } },
    { KeyComb(KeyCode::KEY_MOVE_HOME, KEY_CTRL | KEY_SHIFT),
        [](tic* c) -> void { c->CursorMove(CaretMoveIntent::Home); } },
    { KeyComb(KeyCode::KEY_MOVE_END, KEY_CTRL | KEY_SHIFT),
        [](tic* c) -> void { c->CursorMove(CaretMoveIntent::End); } },
};

bool TextInputClient::HandleKeyEvent(const KeyEvent& keyEvent)
{
    if (keyEvent.action != KeyAction::DOWN) {
        return false;
    }
    uint32_t modKeyFlags =
        (keyEvent.HasKey(KeyCode::KEY_ALT_LEFT) || keyEvent.HasKey(KeyCode::KEY_ALT_RIGHT) ? KEY_ALT : KEY_NULL) |
        (keyEvent.HasKey(KeyCode::KEY_SHIFT_LEFT) || keyEvent.HasKey(KeyCode::KEY_SHIFT_RIGHT) ? KEY_SHIFT : KEY_NULL) |
        (keyEvent.HasKey(KeyCode::KEY_CTRL_LEFT) || keyEvent.HasKey(KeyCode::KEY_CTRL_RIGHT) ? KEY_CTRL : KEY_NULL) |
        (keyEvent.HasKey(KeyCode::KEY_META_LEFT) || keyEvent.HasKey(KeyCode::KEY_META_RIGHT) ? KEY_META : KEY_NULL);
    auto iterFunctionKeys = functionKeys_.find(KeyComb(keyEvent.code, modKeyFlags));
    if (iterFunctionKeys != functionKeys_.end()) {
        return iterFunctionKeys->second(this);
    }
    auto iterKeyboardShortCuts = keyboardShortCuts_.find(KeyComb(keyEvent.code, modKeyFlags));
    if (iterKeyboardShortCuts != keyboardShortCuts_.end()) {
        iterKeyboardShortCuts->second(this);
        return true;
    }
    return false;
}
} // namespace OHOS::Ace
