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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_EVENT_KEY_EVENT_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_EVENT_KEY_EVENT_H

#include <cstdint>

#include "core/event/ace_events.h"

namespace OHOS::Ace {

enum class KeyCode : int32_t {
    UNKNOWN = -1,
    KEYBOARD_HOME = 3,
    KEYBOARD_BACK = 4,
    KEYBOARD_UP = 19,
    KEYBOARD_DOWN = 20,
    KEYBOARD_LEFT = 21,
    KEYBOARD_RIGHT = 22,
    KEYBOARD_CENTER = 23,
    KEYBOARD_A = 29,
    HANDLE_A = 96,
    HANDLE_SELECT = 109,
    KEYBOARD_SHIFT_LEFT = 59,
    KEYBOARD_SHIFT_RIGHT = 60,
    KEYBOARD_TAB = 61,
    KEYBOARD_SPACE = 62,
    KEYBOARD_ENTER = 66,
    KEYBOARD_BACKSPACE = 67,
    KEYBOARD_ESCAPE = 111,
    KEYBOARD_CONTROL_LEFT = 113,
    KEYBOARD_CONTROL_RIGHT = 114,
    KEYBOARD_NUMBER_ENTER = 160,

    TV_CONTROL_BACK = KEYBOARD_BACK,
    TV_CONTROL_UP = KEYBOARD_UP,
    TV_CONTROL_DOWN = KEYBOARD_DOWN,
    TV_CONTROL_LEFT = KEYBOARD_LEFT,
    TV_CONTROL_RIGHT = KEYBOARD_RIGHT,
    TV_CONTROL_ENTER = KEYBOARD_ENTER,
    TV_CONTROL_CENTER = KEYBOARD_CENTER,

    TV_CONTROL_MEDIA_PLAY = 85,
};

enum class KeyAction : int32_t {
    UNKNOWN = -1,
    DOWN = 0,
    UP = 1,
    LONG_PRESS = 2,
    CLICK = 3,
};

const char* KeyToString(int32_t code);

struct KeyEvent final {
    KeyEvent(KeyCode code, KeyAction action, int32_t repeatTime, int64_t timeStamp, int64_t timeStampStart,
        int32_t metaKey, int32_t sourceDevice, int32_t deviceId)
        : code(code), action(action), repeatTime(repeatTime), timeStamp(timeStamp), timeStampStart(timeStampStart),
          key(KeyToString(static_cast<int32_t>(code))), metaKey(metaKey), sourceDevice(sourceDevice), deviceId(deviceId)
    {}
    ~KeyEvent() = default;

    KeyCode code { KeyCode::UNKNOWN };
    KeyAction action { KeyAction::UNKNOWN };
    // When the key is held down for a long period of time, it will be accumulated once in a while.
    // Note that In the long press scene, you will receive a DOWN and an extra LONG_PRESS event. If you only want to
    // identify the click event, you can use CLICK event.
    int32_t repeatTime = 0;
    int64_t timeStamp = 0;
    int64_t timeStampStart = 0;
    const char* key = nullptr;
    int32_t metaKey = 0;
    int32_t sourceDevice = 0;
    int32_t deviceId = 0;
};

class ACE_EXPORT KeyEventInfo : public BaseEventInfo {
    DECLARE_RELATIONSHIP_OF_CLASSES(KeyEventInfo, BaseEventInfo)

public:
    explicit KeyEventInfo(const KeyEvent& event) : BaseEventInfo("keyEvent")
    {
        keyType_ = static_cast<int32_t>(event.action);
        keyCode_ = event.code;
        keyText_ = event.key;
        keySource_ = event.sourceDevice;
        SetDeviceId(event.deviceId);
        metakey_ = event.metaKey;
        std::chrono::microseconds micros(event.timeStamp);
        TimeStamp time(micros);
        SetTimeStamp(time);
    };
    ~KeyEventInfo() override = default;

    int32_t GetKeyType() const
    {
        return keyType_;
    }
    KeyCode GetKeyCode() const
    {
        return keyCode_;
    }
    const char* GetKeyText() const
    {
        return keyText_;
    }
    int32_t GetKeySource() const
    {
        return keySource_;
    }
    int32_t GetMetaKey() const
    {
        return metakey_;
    }

private:
    int32_t keyType_ = 0;
    KeyCode keyCode_{KeyCode::UNKNOWN};
    const char* keyText_ = nullptr;
    int32_t keySource_ = 0;
    int32_t metakey_ = 0;
};

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_EVENT_KEY_EVENT_H
