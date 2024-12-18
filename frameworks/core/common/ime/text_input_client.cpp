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

#include "core/pipeline_ng/pipeline_context.h"

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
// actions
#if defined(MAC_PLATFORM)
    { KeyComb(KeyCode::KEY_A, KEY_META), &tic::HandleOnSelectAll },
    { KeyComb(KeyCode::KEY_C, KEY_META), [](tic* c) -> void { c->HandleOnCopy(true); }  },
    { KeyComb(KeyCode::KEY_D, KEY_META), [](tic* c) -> void { c->HandleOnDelete(true); } },
    { KeyComb(KeyCode::KEY_V, KEY_META), &tic::HandleOnPaste },
    { KeyComb(KeyCode::KEY_X, KEY_META), &tic::HandleOnCut },
    { KeyComb(KeyCode::KEY_Y, KEY_META), &tic::HandleOnRedoAction },
    { KeyComb(KeyCode::KEY_Z, KEY_META), &tic::HandleOnUndoAction },
    { KeyComb(KeyCode::KEY_Z, KEY_META | KEY_SHIFT), &tic::HandleOnRedoAction },
#else
    { KeyComb(KeyCode::KEY_A, KEY_CTRL), &tic::HandleOnSelectAll },
    { KeyComb(KeyCode::KEY_C, KEY_CTRL), [](tic* c) -> void { c->HandleOnCopy(true); } },
    { KeyComb(KeyCode::KEY_D, KEY_CTRL), [](tic* c) -> void { c->HandleOnDelete(true); } },
    { KeyComb(KeyCode::KEY_V, KEY_CTRL), &tic::HandleOnPaste },
    { KeyComb(KeyCode::KEY_X, KEY_CTRL), &tic::HandleOnCut },
    { KeyComb(KeyCode::KEY_Y, KEY_CTRL), &tic::HandleOnRedoAction },
    { KeyComb(KeyCode::KEY_Z, KEY_CTRL), &tic::HandleOnUndoAction },
    { KeyComb(KeyCode::KEY_Z, KEY_CTRL | KEY_SHIFT), &tic::HandleOnRedoAction },
#endif
    { KeyComb(KeyCode::KEY_DEL), [](tic* c) -> void { c->HandleOnDelete(true); } },
    { KeyComb(KeyCode::KEY_FORWARD_DEL), [](tic* c) -> void { c->HandleOnDelete(false); } },
    { KeyComb(KeyCode::KEY_DEL, KEY_CTRL), [](tic* c) -> void { c->HandleOnDeleteComb(true); } },
    { KeyComb(KeyCode::KEY_FORWARD_DEL, KEY_CTRL), [](tic* c) -> void { c->HandleOnDeleteComb(false); } },
    { KeyComb(KeyCode::KEY_INSERT, KEY_CTRL), [](tic* c) -> void { c->HandleOnCopy(true); } },
    { KeyComb(KeyCode::KEY_INSERT, KEY_SHIFT), &tic::HandleOnPaste },
    { KeyComb(KeyCode::KEY_PASTE), &tic::HandleOnPaste },
    { KeyComb(KeyCode::KEY_F10, KEY_SHIFT), &tic::HandleOnShowMenu },
    { KeyComb(KeyCode::KEY_MENU), &tic::HandleOnShowMenu },
    { KeyComb(KeyCode::KEY_ENTER), &tic::HandleOnEnter },
    { KeyComb(KeyCode::KEY_NUMPAD_ENTER), &tic::HandleOnEnter },
    { KeyComb(KeyCode::KEY_DPAD_CENTER), &tic::HandleOnEnter },
    { KeyComb(KeyCode::KEY_ENTER, KEY_CTRL), &tic::HandleOnEnter },
    { KeyComb(KeyCode::KEY_NUMPAD_ENTER, KEY_CTRL), &tic::HandleOnEnter },
    { KeyComb(KeyCode::KEY_DPAD_CENTER, KEY_CTRL), &tic::HandleOnEnter },
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
        [](tic* c) -> void { c->HandleSelect(CaretMoveIntent::LeftWord); } },
    { KeyComb(KeyCode::KEY_DPAD_RIGHT, KEY_CTRL | KEY_SHIFT),
        [](tic* c) -> void { c->HandleSelect(CaretMoveIntent::RightWord); } },
    { KeyComb(KeyCode::KEY_DPAD_UP, KEY_CTRL | KEY_SHIFT),
        [](tic* c) -> void { c->CursorMove(CaretMoveIntent::ParagraghBegin); } },
    { KeyComb(KeyCode::KEY_DPAD_DOWN, KEY_CTRL | KEY_SHIFT),
        [](tic* c) -> void { c->CursorMove(CaretMoveIntent::ParagraghEnd); } },
    { KeyComb(KeyCode::KEY_MOVE_HOME, KEY_CTRL | KEY_SHIFT),
        [](tic* c) -> void { c->CursorMove(CaretMoveIntent::Home); } },
    { KeyComb(KeyCode::KEY_MOVE_END, KEY_CTRL | KEY_SHIFT),
        [](tic* c) -> void { c->CursorMove(CaretMoveIntent::End); } },
    { KeyComb(KeyCode::KEY_B, KEY_CTRL), [](tic* c) -> void { c->HandleSelectFontStyle(KeyCode::KEY_B); } },
    { KeyComb(KeyCode::KEY_I, KEY_CTRL), [](tic* c) -> void { c->HandleSelectFontStyle(KeyCode::KEY_I); } },
    { KeyComb(KeyCode::KEY_U, KEY_CTRL), [](tic* c) -> void { c->HandleSelectFontStyle(KeyCode::KEY_U); } },
    // when numLock off, KEY_NUMPAD_0 perform as KEY_INSERT
    { KeyComb(KeyCode::KEY_NUMPAD_0, KEY_CTRL), [](tic* c) -> void { c->HandleOnCopy(true); } },
    { KeyComb(KeyCode::KEY_NUMPAD_0, KEY_SHIFT), &tic::HandleOnPaste },
    // when numLock off, KEY_NUMPAD_1 perform as KEY_MOVE_END
    { KeyComb(KeyCode::KEY_NUMPAD_1), [](tic* c) -> void { c->CursorMove(CaretMoveIntent::LineEnd); } },
    { KeyComb(KeyCode::KEY_NUMPAD_1, KEY_CTRL), [](tic* c) -> void { c->CursorMove(CaretMoveIntent::End); } },
    { KeyComb(KeyCode::KEY_NUMPAD_1, KEY_SHIFT), [](tic* c) -> void { c->HandleSelect(CaretMoveIntent::LineEnd); } },
    { KeyComb(KeyCode::KEY_NUMPAD_1, KEY_CTRL | KEY_SHIFT),
        [](tic* c) -> void { c->CursorMove(CaretMoveIntent::End); } },
    // when numLock off, KEY_NUMPAD_2 perform as KEY_DPAD_DOWN
    { KeyComb(KeyCode::KEY_NUMPAD_2), [](tic* c) -> void { c->CursorMove(CaretMoveIntent::Down); } },
    { KeyComb(KeyCode::KEY_NUMPAD_2, KEY_CTRL), [](tic* c) -> void { c->CursorMove(CaretMoveIntent::ParagraghEnd); } },
    { KeyComb(KeyCode::KEY_NUMPAD_2, KEY_SHIFT), [](tic* c) -> void { c->HandleSelect(CaretMoveIntent::Down); } },
    { KeyComb(KeyCode::KEY_NUMPAD_2, KEY_CTRL | KEY_SHIFT),
        [](tic* c) -> void { c->CursorMove(CaretMoveIntent::ParagraghEnd); } },
    // when numLock off, KEY_NUMPAD_3 perform as KEY_PAGE_DOWN
    // when numLock off, KEY_NUMPAD_4 perform as KEY_DPAD_LEFT
    { KeyComb(KeyCode::KEY_NUMPAD_4), [](tic* c) -> void { c->CursorMove(CaretMoveIntent::Left); } },
    { KeyComb(KeyCode::KEY_NUMPAD_4, KEY_CTRL), [](tic* c) -> void { c->CursorMove(CaretMoveIntent::LeftWord); } },
    { KeyComb(KeyCode::KEY_NUMPAD_4, KEY_SHIFT), [](tic* c) -> void { c->HandleSelect(CaretMoveIntent::Left); } },
    { KeyComb(KeyCode::KEY_NUMPAD_4, KEY_CTRL | KEY_SHIFT),
        [](tic* c) -> void { c->HandleSelect(CaretMoveIntent::LeftWord); } },
    // when numLock off, KEY_NUMPAD_5 perform as none
    // when numLock off, KEY_NUMPAD_6 perform as KEY_DPAD_RIGHT
    { KeyComb(KeyCode::KEY_NUMPAD_6), [](tic* c) -> void { c->CursorMove(CaretMoveIntent::Right); } },
    { KeyComb(KeyCode::KEY_NUMPAD_6, KEY_CTRL), [](tic* c) -> void { c->CursorMove(CaretMoveIntent::RightWord); } },
    { KeyComb(KeyCode::KEY_NUMPAD_6, KEY_SHIFT), [](tic* c) -> void { c->HandleSelect(CaretMoveIntent::Right); } },
    { KeyComb(KeyCode::KEY_NUMPAD_6, KEY_CTRL | KEY_SHIFT),
        [](tic* c) -> void { c->HandleSelect(CaretMoveIntent::RightWord); } },
    // when numLock off, KEY_NUMPAD_7 perform as KEY_MOVE_HOME
    { KeyComb(KeyCode::KEY_NUMPAD_7), [](tic* c) -> void { c->CursorMove(CaretMoveIntent::LineBegin); } },
    { KeyComb(KeyCode::KEY_NUMPAD_7, KEY_CTRL), [](tic* c) -> void { c->CursorMove(CaretMoveIntent::Home); } },
    { KeyComb(KeyCode::KEY_NUMPAD_7, KEY_SHIFT), [](tic* c) -> void { c->HandleSelect(CaretMoveIntent::LineBegin); } },
    { KeyComb(KeyCode::KEY_NUMPAD_7, KEY_CTRL | KEY_SHIFT),
        [](tic* c) -> void { c->CursorMove(CaretMoveIntent::Home); } },
    // when numLock off, KEY_NUMPAD_8 perform as KEY_DPAD_UP
    { KeyComb(KeyCode::KEY_NUMPAD_8), [](tic* c) -> void { c->CursorMove(CaretMoveIntent::Up); } },
    { KeyComb(KeyCode::KEY_NUMPAD_8, KEY_CTRL),
        [](tic* c) -> void { c->CursorMove(CaretMoveIntent::ParagraghBegin); } },
    { KeyComb(KeyCode::KEY_NUMPAD_8, KEY_SHIFT), [](tic* c) -> void { c->HandleSelect(CaretMoveIntent::Up); } },
    { KeyComb(KeyCode::KEY_NUMPAD_8, KEY_CTRL | KEY_SHIFT),
        [](tic* c) -> void { c->CursorMove(CaretMoveIntent::ParagraghBegin); } },
    // when numLock off, KEY_NUMPAD_9 perform as KEY_PAGE_UP
    // when numLock off, KEY_NUMPAD_DOT perform as KEY_FORWARD_DEL
    { KeyComb(KeyCode::KEY_NUMPAD_DOT), [](tic* c) -> void { c->HandleOnDelete(false); } },
    { KeyComb(KeyCode::KEY_NUMPAD_DOT, KEY_CTRL), [](tic* c) -> void { c->HandleOnDeleteComb(false); } },
};

void TextInputClient::NotifyKeyboardHeight(uint32_t height)
{
    auto pipeline = NG::PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto manager = pipeline->GetSafeAreaManager();
    CHECK_NULL_VOID(manager);
    manager->SetkeyboardHeightConsideringUIExtension(height);
}

bool TextInputClient::HandleKeyEvent(const KeyEvent& keyEvent)
{
    UpdateShiftFlag(keyEvent);
    if (keyEvent.action != KeyAction::DOWN) {
        return false;
    }
    uint32_t ctrlFlag =
        (keyEvent.HasKey(KeyCode::KEY_CTRL_LEFT) || keyEvent.HasKey(KeyCode::KEY_CTRL_RIGHT) ? KEY_CTRL : KEY_NULL);
    bool vFlag = keyEvent.HasKey(KeyCode::KEY_V);
    if (!keyEvent.msg.empty() && ctrlFlag == KEY_CTRL && vFlag) {
        InsertValue(keyEvent.msg);
        return true;
    }
    uint32_t modKeyFlags =
        (keyEvent.HasKey(KeyCode::KEY_ALT_LEFT) || keyEvent.HasKey(KeyCode::KEY_ALT_RIGHT) ? KEY_ALT : KEY_NULL) |
        (keyEvent.HasKey(KeyCode::KEY_SHIFT_LEFT) || keyEvent.HasKey(KeyCode::KEY_SHIFT_RIGHT) ? KEY_SHIFT : KEY_NULL) |
        (keyEvent.HasKey(KeyCode::KEY_CTRL_LEFT) || keyEvent.HasKey(KeyCode::KEY_CTRL_RIGHT) ? KEY_CTRL : KEY_NULL) |
        (keyEvent.HasKey(KeyCode::KEY_META_LEFT) || keyEvent.HasKey(KeyCode::KEY_META_RIGHT) ? KEY_META : KEY_NULL);
    if (modKeyFlags == KEY_NULL || modKeyFlags == KEY_SHIFT) {
        auto value = keyEvent.ConvertCodeToString();
        if (value != "") {
            InsertValue(value, true);
            return true;
        }
    }
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
