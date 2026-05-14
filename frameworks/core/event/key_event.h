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
#include "core/event/key_code.h"
#include "core/event/non_pointer_event.h"

namespace OHOS::MMI {
class KeyEvent;
}

namespace OHOS::Ace::NG {
class FocusAxisEventInfo;
}

namespace OHOS::Ace {

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
    ACE_FORCE_EXPORT std::string ConvertCodeToString() const;

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
    bool isFalsifyCancel = false;
    bool isRedispatch = false;
    bool numLock = false;
    bool scrollLock = false;
    uint32_t unicode = 0;
    std::vector<uint8_t> enhanceData;
    std::shared_ptr<MMI::KeyEvent> rawKeyEvent;

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
    std::string msg = "";
    std::optional<bool> activeMark;
    int32_t targetDisplayId = 0;
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
        SetPressedKeyCodes(event.pressedCodes);
        keyMsg_ = event.msg;
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
    int32_t GetJsKeyType() const
    {
        return keyType_ == KeyAction::CANCEL ? static_cast<int32_t>(KeyAction::CLICK) : static_cast<int32_t>(keyType_);
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

    void SetKeyType(KeyAction keyType)
    {
        keyType_ = keyType;
    }

    void SetKeyCode(KeyCode keyCode)
    {
        keyCode_ = keyCode;
    }

    void SetKeyText(const std::string& keyText)
    {
        keyText_ = keyText;
    }

    void SetKeySource(SourceType keySource)
    {
        keySource_ = keySource;
    }

    void SetKeyIntention(KeyIntention keyIntention)
    {
        keyIntention_ = keyIntention;
    }

    void SetUnicode(uint32_t unicode)
    {
        unicode_ = unicode;
    }

    void SetNumLock(bool numLock)
    {
        numLock_ = numLock;
    }

    void SetCapsLock(bool capsLock)
    {
        capsLock_ = capsLock;
    }

    void SetScrollLock(bool scrollLock)
    {
        scrollLock_ = scrollLock;
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

    size_t GetSize() const
    {
        static constexpr size_t KEY_EVENT_INFO_SIZE = 480;
        return KEY_EVENT_INFO_SIZE;
    }

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
