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

#include "core/event/key_event_transfer.h"

#include <ctime>

#include "base/log/log.h"
#include "core/event/keyboardCode.h"

namespace OHOS::Ace {
namespace {
constexpr int32_t LETTER_CODE_DIFF = 1988;
constexpr int32_t CTRL_CODE_DIFF = 1959;
constexpr int32_t DIRECTION_CODE_DIFF = 1993;
constexpr int32_t KEY_ACTION_DOWN = 2;
constexpr int32_t KEY_ACTION_UP = 3;
} // namespace

KeyEvent KeyEventTransfer::GetKeyEvent(int32_t keyCode, int32_t keyAction, int32_t repeatTime, int64_t timeStamp,
    int64_t timeStampStart, int32_t metaKey, int32_t keySource, int32_t deviceId)
{
    if (timeStamp == 0) {
        timeStamp = clock();
        timeStampStart = timeStamp;
    }
    KeyCode keyCode_ = KeyCode::UNKNOWN;
    KeyAction keyAction_ = KeyAction::UNKNOWN;
    if (keyAction == KEY_ACTION_DOWN) {
        keyAction_ = KeyAction::DOWN;
    } else if (keyAction == KEY_ACTION_UP) {
        keyAction_ = KeyAction::UP;
    } else {
        keyAction_ = KeyAction::UNKNOWN;
    }
    if (keyCode >= static_cast<int32_t>(keyboardCode::LETTER_CODE_START) &&
        keyCode <= static_cast<int32_t>(keyboardCode::LETTER_CODE_END)) {
        keyCode_ = static_cast<KeyCode>(keyCode - LETTER_CODE_DIFF);
    } else if ((keyCode == static_cast<int32_t>(keyboardCode::LEFT_CTRL_CODE)) ||
               (keyCode == static_cast<int32_t>(keyboardCode::RIGHT_CTRL_CODE))) {
        keyCode_ = static_cast<KeyCode>(keyCode - CTRL_CODE_DIFF);
    } else if (keyCode >= (static_cast<int32_t>(keyboardCode::DIRECTION_CODE_START)) &&
               (keyCode <= static_cast<int32_t>(keyboardCode::DIRECTION_CODE_END))) {
        keyCode_ = static_cast<KeyCode>(keyCode - DIRECTION_CODE_DIFF);
    } else if ((keyCode == (static_cast<int32_t>(keyboardCode::ENTER_CODE))) ||
               (keyCode == (static_cast<int32_t>(keyboardCode::ENTER_NUMPAD_CODE)))) {
        keyCode_ = static_cast<KeyCode>(keyCode - LETTER_CODE_DIFF);
    } else if ((keyCode == static_cast<int32_t>(keyboardCode::LEFT_SHIFT_CODE)) ||
               (keyCode == static_cast<int32_t>(keyboardCode::RIGHT_SHIFT_CODE))) {
        keyCode_ = static_cast<KeyCode>(keyCode - LETTER_CODE_DIFF);
    } else {
        keyCode_ = static_cast<KeyCode>(keyCode - LETTER_CODE_DIFF);
        if (keyCode < 0) {
            keyCode_ = KeyCode::UNKNOWN;
        }
    }
    return KeyEvent(keyCode_, keyAction_, repeatTime, timeStamp, timeStampStart, metaKey, keySource, deviceId);
}
} // namespace OHOS::Ace