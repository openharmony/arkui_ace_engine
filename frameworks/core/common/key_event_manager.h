/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMMON_KEY_EVENT_MANAGER_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMMON_KEY_EVENT_MANAGER_H

#include <list>

#include "core/components/common/layout/constants.h"
#include "core/event/key_event.h"
#include "core/event/focus_axis_event.h"

namespace OHOS::Ace {
namespace NG {
class FrameNode;
class FocusView;

class KeyEventManager : public virtual AceType {
    DECLARE_ACE_TYPE(KeyEventManager, AceType);

public:
    KeyEventManager() = default;
    ~KeyEventManager() override = default;

    void AddKeyboardShortcutNode(const WeakPtr<NG::FrameNode>& node);
    void DelKeyboardShortcutNode(int32_t nodeId);
    uint8_t GetKeyboardShortcutKeys(const std::vector<ModifierKey>& keys);
    bool IsSameKeyboardShortcutNode(const std::string& value, uint8_t keys);
    bool DispatchKeyboardShortcut(const KeyEvent& event);
    void ReDispatch(KeyEvent& keyEvent);
    void SetIsKeyConsumed(bool value);
    void SetPressedKeyCodes(const std::vector<KeyCode>& pressedKeyCodes)
    {
        pressedKeyCodes_ = pressedKeyCodes;
    }
    bool IsTabJustTriggerOnKeyEvent() const
    {
        return isTabJustTriggerOnKeyEvent_;
    }
    // to be obsoleted
    bool IsKeyInPressed(KeyCode tarCode) const
    {
        return std::any_of(pressedKeyCodes_.begin(), pressedKeyCodes_.end(),
            [tarCode](const KeyCode& code) { return code == tarCode; });
    }

protected:
    virtual int32_t GetInstanceId() = 0;

    bool OnKeyEvent(const KeyEvent& event);
    bool OnFocusAxisEvent(const FocusAxisEvent& event);

private:
    // Distribute the key event to the corresponding root node. If the root node is not processed, return false and the
    // platform will handle it.
    bool DispatchKeyEventNG(const KeyEvent& event, const RefPtr<NG::FrameNode>& focusNode);
    bool DispatchTabIndexEventNG(const KeyEvent& event, const RefPtr<NG::FrameNode>& mainView);
    bool TriggerKeyEventDispatch(const KeyEvent& event);
    bool IsSystemKeyboardShortcut(const KeyEvent& event);
    bool DispatchTabKey(const KeyEvent& event, const RefPtr<FocusView>& curFocusView);
    bool IsSkipShortcutAndFocusMove();

    bool isKeyConsumed_ = false;
    bool isTabJustTriggerOnKeyEvent_ = false;
    std::list<WeakPtr<NG::FrameNode>> keyboardShortcutNode_;
    std::vector<KeyCode> pressedKeyCodes_;
};
} // namespace NG
} // namespace OHOS::Ace
#endif