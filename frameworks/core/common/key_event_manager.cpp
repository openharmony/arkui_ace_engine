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
#include "key_event_manager.h"

#include "base/input_manager/input_manager.h"
#include "base/ressched/ressched_report.h"
#include "core/common/container.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/overlay/sheet_manager.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {
namespace {
constexpr uint8_t KEYS_MAX_VALUE = 3;

enum CtrlKeysBit : uint8_t {
    CTRL = 1,
    SHIFT = 2,
    ALT = 4,
};

RefPtr<NG::PipelineContext> GetPipelineContext(int32_t instanceId)
{
    auto container = Container::GetContainer(instanceId);
    CHECK_NULL_RETURN(container, nullptr);
    return AceType::DynamicCast<NG::PipelineContext>(container->GetPipelineContext());
}

RefPtr<FocusManager> GetFocusManager(int32_t instanceId)
{
    auto pipeline = GetPipelineContext(instanceId);
    CHECK_NULL_RETURN(pipeline, nullptr);
    return pipeline->GetOrCreateFocusManager();
}

RefPtr<OverlayManager> GetOverlayManager(int32_t instanceId)
{
    auto pipeline = GetPipelineContext(instanceId);
    CHECK_NULL_RETURN(pipeline, nullptr);
    return pipeline->GetOverlayManager();
}

RefPtr<DragDropManager> GetDragDropManager(int32_t instanceId)
{
    auto pipeline = GetPipelineContext(instanceId);
    CHECK_NULL_RETURN(pipeline, nullptr);
    return pipeline->GetDragDropManager();
}
} // namespace

void KeyEventManager::AddKeyboardShortcutNode(const WeakPtr<FrameNode>& node)
{
    auto frameNode = node.Upgrade();
    CHECK_NULL_VOID(frameNode);
    auto iter = keyboardShortcutNode_.begin();
    while (iter != keyboardShortcutNode_.end()) {
        auto keyboardShortcutNode = (*iter).Upgrade();
        if (!keyboardShortcutNode) {
            keyboardShortcutNode_.erase(iter++);
            continue;
        }
        if (keyboardShortcutNode->GetId() == frameNode->GetId()) {
            return;
        }
        ++iter;
    }
    keyboardShortcutNode_.emplace_back(node);
}

uint8_t KeyEventManager::GetKeyboardShortcutKeys(const std::vector<ModifierKey>& keys)
{
    uint8_t keyValue = 0;
    uint8_t ctrlTimes = 0;
    uint8_t shiftTimes = 0;
    uint8_t altTimes = 0;
    if (keys.size() > KEYS_MAX_VALUE) {
        return 0;
    }
    for (const auto& key : keys) {
        switch (static_cast<uint8_t>(key)) {
            case static_cast<uint8_t>(ModifierKey::CTRL): {
                keyValue |= CtrlKeysBit::CTRL;
                ++ctrlTimes;
                break;
            }
            case static_cast<uint8_t>(ModifierKey::SHIFT): {
                keyValue |= CtrlKeysBit::SHIFT;
                ++shiftTimes;
                break;
            }
            case static_cast<uint8_t>(ModifierKey::ALT): {
                keyValue |= CtrlKeysBit::ALT;
                ++altTimes;
                break;
            }
            default:
                keyValue |= 0;
        }
    }
    if (ctrlTimes > 1 || shiftTimes > 1 || altTimes > 1) {
        return 0;
    }
    return keyValue;
}

bool KeyEventManager::IsSystemKeyboardShortcut(const KeyEvent& event)
{
    static std::vector<HotKey> systemHotKeys;
    static std::once_flag initFlag;

    std::call_once(initFlag, []() {
        std::vector<HotKey> initHotKeys;
        InputManager::GetSystemHotkeys(systemHotKeys);
    });
    if (systemHotKeys.empty()) {
        return false;
    }

    for (const auto& [prekey, finalkey] : systemHotKeys) {
        if (static_cast<int32_t>(event.code) != finalkey || (event.pressedCodes.size() != prekey.size() + 1)) {
            continue;
        }
        bool matchPreKey = std::all_of(event.pressedCodes.begin(), event.pressedCodes.end(),
            [&prekeySet = prekey, keycode = event.code](const KeyCode& item) {
                return (item == keycode) ? true : prekeySet.count(static_cast<int32_t>(item)) != 0;
            });
        if (matchPreKey) {
            TAG_LOGI(AceLogTag::ACE_KEYBOARD, "Match system hot key. Cannot trigger keyboard shortcut.");
            return true;
        }
    }
    return false;
}

bool KeyEventManager::IsSameKeyboardShortcutNode(const std::string& value, uint8_t keys)
{
    for (auto& weakNode : keyboardShortcutNode_) {
        auto frameNode = weakNode.Upgrade();
        if (!frameNode) {
            continue;
        }
        auto eventHub = frameNode->GetEventHub<EventHub>();
        if (!eventHub) {
            continue;
        }
        auto keyboardShortcuts = eventHub->GetKeyboardShortcut();
        for (auto& keyboardShortcut : keyboardShortcuts) {
            if (keyboardShortcut.value == value && keyboardShortcut.keys == keys) {
                return true;
            }
        }
    }
    return false;
}

void AddKeyboardShortcutSingleKey(
    uint8_t keys, std::vector<std::vector<KeyCode>>& keyCodes, std::vector<uint8_t>& permutation)
{
    uint8_t index = 0;
    std::vector<KeyCode> keyCode1;
    std::vector<KeyCode> keyCode2;
    if (keys & CtrlKeysBit::CTRL) {
        keyCode1.emplace_back(KeyCode::KEY_CTRL_LEFT);
        keyCode2.emplace_back(KeyCode::KEY_CTRL_RIGHT);
        permutation.emplace_back(++index);
    }
    if (keys & CtrlKeysBit::SHIFT) {
        keyCode1.emplace_back(KeyCode::KEY_SHIFT_LEFT);
        keyCode2.emplace_back(KeyCode::KEY_SHIFT_RIGHT);
        permutation.emplace_back(++index);
    }
    if (keys & CtrlKeysBit::ALT) {
        keyCode1.emplace_back(KeyCode::KEY_ALT_LEFT);
        keyCode2.emplace_back(KeyCode::KEY_ALT_RIGHT);
        permutation.emplace_back(++index);
    }
    keyCodes.emplace_back(keyCode1);
    keyCodes.emplace_back(keyCode2);
}

void AddKeyboardShortcutDoubleKeysWithCtrlShift(
    uint8_t keys, std::vector<std::vector<KeyCode>>& keyCodes, std::vector<uint8_t>& permutation)
{
    uint8_t index = 0;
    std::vector<KeyCode> keyCode1;
    std::vector<KeyCode> keyCode2;
    std::vector<KeyCode> keyCode3;
    std::vector<KeyCode> keyCode4;

    keyCode1.emplace_back(KeyCode::KEY_CTRL_LEFT);
    keyCode2.emplace_back(KeyCode::KEY_CTRL_LEFT);
    keyCode3.emplace_back(KeyCode::KEY_CTRL_RIGHT);
    keyCode4.emplace_back(KeyCode::KEY_CTRL_RIGHT);
    permutation.emplace_back(++index);

    keyCode1.emplace_back(KeyCode::KEY_SHIFT_LEFT);
    keyCode2.emplace_back(KeyCode::KEY_SHIFT_RIGHT);
    keyCode3.emplace_back(KeyCode::KEY_SHIFT_LEFT);
    keyCode4.emplace_back(KeyCode::KEY_SHIFT_RIGHT);
    permutation.emplace_back(++index);

    keyCodes.emplace_back(keyCode1);
    keyCodes.emplace_back(keyCode2);
    keyCodes.emplace_back(keyCode3);
    keyCodes.emplace_back(keyCode4);
}

void AddKeyboardShortcutDoubleKeysWithCtrlAlt(
    uint8_t keys, std::vector<std::vector<KeyCode>>& keyCodes, std::vector<uint8_t>& permutation)
{
    uint8_t index = 0;
    std::vector<KeyCode> keyCode1;
    std::vector<KeyCode> keyCode2;
    std::vector<KeyCode> keyCode3;
    std::vector<KeyCode> keyCode4;

    keyCode1.emplace_back(KeyCode::KEY_CTRL_LEFT);
    keyCode2.emplace_back(KeyCode::KEY_CTRL_LEFT);
    keyCode3.emplace_back(KeyCode::KEY_CTRL_RIGHT);
    keyCode4.emplace_back(KeyCode::KEY_CTRL_RIGHT);
    permutation.emplace_back(++index);

    keyCode1.emplace_back(KeyCode::KEY_ALT_LEFT);
    keyCode2.emplace_back(KeyCode::KEY_ALT_RIGHT);
    keyCode3.emplace_back(KeyCode::KEY_ALT_LEFT);
    keyCode4.emplace_back(KeyCode::KEY_ALT_RIGHT);
    permutation.emplace_back(++index);

    keyCodes.emplace_back(keyCode1);
    keyCodes.emplace_back(keyCode2);
    keyCodes.emplace_back(keyCode3);
    keyCodes.emplace_back(keyCode4);
}

void AddKeyboardShortcutDoubleKeysWithShiftAlt(
    uint8_t keys, std::vector<std::vector<KeyCode>>& keyCodes, std::vector<uint8_t>& permutation)
{
    uint8_t index = 0;
    std::vector<KeyCode> keyCode1;
    std::vector<KeyCode> keyCode2;
    std::vector<KeyCode> keyCode3;
    std::vector<KeyCode> keyCode4;

    keyCode1.emplace_back(KeyCode::KEY_SHIFT_LEFT);
    keyCode2.emplace_back(KeyCode::KEY_SHIFT_LEFT);
    keyCode3.emplace_back(KeyCode::KEY_SHIFT_RIGHT);
    keyCode4.emplace_back(KeyCode::KEY_SHIFT_RIGHT);
    permutation.emplace_back(++index);

    keyCode1.emplace_back(KeyCode::KEY_ALT_LEFT);
    keyCode2.emplace_back(KeyCode::KEY_ALT_RIGHT);
    keyCode3.emplace_back(KeyCode::KEY_ALT_LEFT);
    keyCode4.emplace_back(KeyCode::KEY_ALT_RIGHT);
    permutation.emplace_back(++index);

    keyCodes.emplace_back(keyCode1);
    keyCodes.emplace_back(keyCode2);
    keyCodes.emplace_back(keyCode3);
    keyCodes.emplace_back(keyCode4);
}

void AddKeyboardShortcutDoubleKeys(
    uint8_t keys, std::vector<std::vector<KeyCode>>& keyCodes, std::vector<uint8_t>& permutation)
{
    if (keys == CtrlKeysBit::CTRL + CtrlKeysBit::SHIFT) {
        AddKeyboardShortcutDoubleKeysWithCtrlShift(keys, keyCodes, permutation);
    }
    if (keys == CtrlKeysBit::CTRL + CtrlKeysBit::ALT) {
        AddKeyboardShortcutDoubleKeysWithCtrlAlt(keys, keyCodes, permutation);
    }
    if (keys == CtrlKeysBit::SHIFT + CtrlKeysBit::ALT) {
        AddKeyboardShortcutDoubleKeysWithShiftAlt(keys, keyCodes, permutation);
    }
}

void AddKeyboardShortcutTripleKeys(
    uint8_t keys, std::vector<std::vector<KeyCode>>& keyCodes, std::vector<uint8_t>& permutation)
{
    uint8_t index = 0;
    std::vector<KeyCode> keyCode1;
    std::vector<KeyCode> keyCode2;
    std::vector<KeyCode> keyCode3;
    std::vector<KeyCode> keyCode4;
    std::vector<KeyCode> keyCode5;
    std::vector<KeyCode> keyCode6;
    std::vector<KeyCode> keyCode7;
    std::vector<KeyCode> keyCode8;

    keyCode1.emplace_back(KeyCode::KEY_CTRL_LEFT);
    keyCode2.emplace_back(KeyCode::KEY_CTRL_LEFT);
    keyCode3.emplace_back(KeyCode::KEY_CTRL_LEFT);
    keyCode4.emplace_back(KeyCode::KEY_CTRL_LEFT);
    keyCode5.emplace_back(KeyCode::KEY_CTRL_RIGHT);
    keyCode6.emplace_back(KeyCode::KEY_CTRL_RIGHT);
    keyCode7.emplace_back(KeyCode::KEY_CTRL_RIGHT);
    keyCode8.emplace_back(KeyCode::KEY_CTRL_RIGHT);
    permutation.emplace_back(++index);

    keyCode1.emplace_back(KeyCode::KEY_SHIFT_LEFT);
    keyCode2.emplace_back(KeyCode::KEY_SHIFT_LEFT);
    keyCode3.emplace_back(KeyCode::KEY_SHIFT_RIGHT);
    keyCode4.emplace_back(KeyCode::KEY_SHIFT_RIGHT);
    keyCode5.emplace_back(KeyCode::KEY_SHIFT_LEFT);
    keyCode6.emplace_back(KeyCode::KEY_SHIFT_LEFT);
    keyCode7.emplace_back(KeyCode::KEY_SHIFT_RIGHT);
    keyCode8.emplace_back(KeyCode::KEY_SHIFT_RIGHT);
    permutation.emplace_back(++index);

    keyCode1.emplace_back(KeyCode::KEY_ALT_LEFT);
    keyCode2.emplace_back(KeyCode::KEY_ALT_RIGHT);
    keyCode3.emplace_back(KeyCode::KEY_ALT_LEFT);
    keyCode4.emplace_back(KeyCode::KEY_ALT_RIGHT);
    keyCode5.emplace_back(KeyCode::KEY_ALT_LEFT);
    keyCode6.emplace_back(KeyCode::KEY_ALT_RIGHT);
    keyCode7.emplace_back(KeyCode::KEY_ALT_LEFT);
    keyCode8.emplace_back(KeyCode::KEY_ALT_RIGHT);
    permutation.emplace_back(++index);

    keyCodes.emplace_back(keyCode1);
    keyCodes.emplace_back(keyCode2);
    keyCodes.emplace_back(keyCode3);
    keyCodes.emplace_back(keyCode4);
    keyCodes.emplace_back(keyCode5);
    keyCodes.emplace_back(keyCode6);
    keyCodes.emplace_back(keyCode7);
    keyCodes.emplace_back(keyCode8);
}

void AddKeyboardShortcutKeys(
    uint8_t keys, std::vector<std::vector<KeyCode>>& keyCodes, std::vector<uint8_t>& permutation)
{
    // single FunctionKey
    if (keys == 0) {
        keyCodes.emplace_back(std::vector<KeyCode>());
    }
    // single key
    if (keys == CtrlKeysBit::CTRL || keys == CtrlKeysBit::SHIFT || keys == CtrlKeysBit::ALT) {
        TAG_LOGI(AceLogTag::ACE_KEYBOARD, "AddKeyboardShortcutKeys single key");
        AddKeyboardShortcutSingleKey(keys, keyCodes, permutation);
    }
    // double keys
    if (keys == CtrlKeysBit::CTRL + CtrlKeysBit::SHIFT || keys == CtrlKeysBit::CTRL + CtrlKeysBit::ALT ||
        keys == CtrlKeysBit::SHIFT + CtrlKeysBit::ALT) {
        TAG_LOGI(AceLogTag::ACE_KEYBOARD, "AddKeyboardShortcutKeys double keys");
        AddKeyboardShortcutDoubleKeys(keys, keyCodes, permutation);
    }
    // triple keys
    if (keys == CtrlKeysBit::CTRL + CtrlKeysBit::SHIFT + CtrlKeysBit::ALT) {
        TAG_LOGI(AceLogTag::ACE_KEYBOARD, "AddKeyboardShortcutKeys triple keys");
        AddKeyboardShortcutTripleKeys(keys, keyCodes, permutation);
    }
}

bool TriggerKeyboardShortcut(const KeyEvent& event, const std::vector<KeyboardShortcut>& keyboardShortcuts,
    const WeakPtr<FrameNode>& node, const RefPtr<EventHub>& eventHub)
{
    CHECK_NULL_RETURN(eventHub, false);
    for (auto& keyboardShortcut : keyboardShortcuts) {
        if (keyboardShortcut.value.empty()) {
            continue;
        }

        std::vector<std::vector<KeyCode>> keyCodes;
        std::vector<uint8_t> permutation;
        AddKeyboardShortcutKeys(keyboardShortcut.keys, keyCodes, permutation);
        if (event.IsFunctionKey() || event.IsEscapeKey()) {
            if (event.ConvertInputCodeToString() != keyboardShortcut.value) {
                continue;
            }
        } else if (event.ConvertInputCodeToString().find(keyboardShortcut.value) == std::string::npos) {
            continue;
        }
        // Handle left and right the keys problem.
        std::vector<uint8_t> perm;
        for (auto& keyCode : keyCodes) {
            perm.assign(permutation.begin(), permutation.end());
            // Handle the keys order problem.
            do {
                keyCode.emplace_back(event.code);
                if (!event.IsExactlyKey(keyCode)) {
                    keyCode.pop_back();
                    std::next_permutation(keyCode.begin(), keyCode.end());
                    continue;
                }

                if (keyboardShortcut.onKeyboardShortcutAction) {
                    keyboardShortcut.onKeyboardShortcutAction();
                    TAG_LOGI(AceLogTag::ACE_KEYBOARD, "TriggerKeyboardShortcut :%{public}d action done.",
                        static_cast<int32_t>(event.pressedCodes.size()));
                    return true;
                } else {
                    auto gestureEventHub = eventHub->GetGestureEventHub();
                    if (gestureEventHub && gestureEventHub->IsClickable()) {
                        gestureEventHub->KeyBoardShortCutClick(event, node);
                        TAG_LOGI(AceLogTag::ACE_KEYBOARD, "TriggerKeyboardShortcut :%{public}d click done.",
                            static_cast<int32_t>(event.pressedCodes.size()));
                        return true;
                    }
                }
                keyCode.pop_back();
                std::next_permutation(keyCode.begin(), keyCode.end());
            } while (std::next_permutation(perm.begin(), perm.end()));
            perm.clear();
        }
        keyCodes.clear();
        permutation.clear();
    }
    return false;
}

bool KeyEventManager::DispatchKeyboardShortcut(const KeyEvent& event)
{
    auto container = Container::GetContainer(GetInstanceId());
    if (container && container->GetUIContentType() == UIContentType::SECURITY_UI_EXTENSION) {
        TAG_LOGD(AceLogTag::ACE_KEYBOARD, "Do not dispatch keyboard shortcut because in security UEC");
        return false;
    }
    if (event.action != KeyAction::DOWN) {
        return false;
    }
    if (keyboardShortcutNode_.empty() || IsSystemKeyboardShortcut(event)) {
        return false;
    }
    for (auto& node : keyboardShortcutNode_) {
        auto frameNode = node.Upgrade();
        if (!frameNode || !(frameNode->IsActive())) {
            continue;
        }
        auto eventHub = frameNode->GetEventHub<EventHub>();
        if (!eventHub || !(eventHub->IsEnabled())) {
            continue;
        }

        auto keyboardShortcuts = eventHub->GetKeyboardShortcut();
        if (TriggerKeyboardShortcut(event, keyboardShortcuts, node, eventHub)) {
            return true;
        }
    }
    return false;
}

void KeyEventManager::DelKeyboardShortcutNode(int32_t nodeId)
{
    auto iter = keyboardShortcutNode_.begin();
    while (iter != keyboardShortcutNode_.end()) {
        auto frameNode = (*iter).Upgrade();
        if (!frameNode) {
            iter = keyboardShortcutNode_.erase(iter);
            continue;
        }
        if (frameNode->GetId() == nodeId) {
            keyboardShortcutNode_.erase(iter);
            break;
        }
        ++iter;
    }
}

bool KeyEventManager::DispatchTabIndexEventNG(const KeyEvent& event, const RefPtr<FrameNode>& mainView)
{
    CHECK_NULL_RETURN(mainView, false);
    TAG_LOGD(AceLogTag::ACE_FOCUS,
        "Dispatch tab index event: code:%{private}d/action:%{public}d on node: %{public}s/%{public}d.", event.code,
        event.action, mainView->GetTag().c_str(), mainView->GetId());
    auto mainViewFocusHub = mainView->GetFocusHub();
    CHECK_NULL_RETURN(mainViewFocusHub, false);
    if (mainViewFocusHub->HandleFocusByTabIndex(event)) {
        TAG_LOGD(AceLogTag::ACE_FOCUS,
            "Tab index handled the key event: code:" SEC_PLD(%{private}d) "/action:%{public}d",
            SEC_PARAM(event.code), event.action);
        return true;
    }
    return false;
}

bool KeyEventManager::DispatchKeyEventNG(const KeyEvent& event, const RefPtr<FrameNode>& focusNode)
{
    if (!focusNode) {
        TAG_LOGD(AceLogTag::ACE_FOCUS,
            "Cannot dispatch key event: code:" SEC_PLD(%{private}d)
            "/action:%{public}d/isPreIme:%{public}d on node: nullptr",
            SEC_PARAM(event.code), event.action, event.isPreIme);
        return false;
    }
    TAG_LOGD(AceLogTag::ACE_FOCUS,
        "Dispatch key event: code:" SEC_PLD(%{private}d)
        "/action:%{public}d/isPreIme:%{public}d on node: %{public}s/%{public}d.",
        SEC_PARAM(event.code), event.action, event.isPreIme, focusNode->GetTag().c_str(), focusNode->GetId());
    isKeyConsumed_ = false;
    auto focusNodeHub = focusNode->GetFocusHub();
    CHECK_NULL_RETURN(focusNodeHub, false);
    if (focusNodeHub->HandleEvent(event)) {
        TAG_LOGI(AceLogTag::ACE_FOCUS, "Focus system handled the key event: code:" SEC_PLD(%{private}d)
            "/action:%{public}d", SEC_PARAM(event.code), event.action);
        return true;
    }
    if (!isKeyConsumed_) {
        TAG_LOGD(AceLogTag::ACE_FOCUS, "Focus system do not handled the key event: code:"
            SEC_PLD(%{private}d) "/action:%{public}d", SEC_PARAM(event.code), event.action);
    }
    return isKeyConsumed_;
}

void KeyEventManager::SetIsKeyConsumed(bool value)
{
    // Once consumed, isKeyConsumed_ keeps true
    if (!isKeyConsumed_ && value) {
        isKeyConsumed_ = true;
    }
}

bool KeyEventManager::OnKeyEvent(const KeyEvent& event)
{
    SetPressedKeyCodes(event.pressedCodes);

    // onKeyPreIme
    if (event.isPreIme) {
        ResSchedReport::GetInstance().OnKeyEvent(event);
        if (TriggerKeyEventDispatch(event)) {
            return true;
        }
        if (!IsSkipShortcutAndFocusMove()) {
            return DispatchKeyboardShortcut(event);
        } else {
            TAG_LOGD(AceLogTag::ACE_KEYBOARD, "Do not dispatch keyboard shortcut because Web is current focus");
        }
        return false;
    }

    // process drag cancel
    if (event.code == KeyCode::KEY_ESCAPE) {
        auto dragDropMgr = GetDragDropManager(GetInstanceId());
        if (dragDropMgr && dragDropMgr->IsMSDPDragging()) {
            return true;
        }
    }

    // OnKeyEvent
    if (TriggerKeyEventDispatch(event)) {
        return true;
    }

    // process exit overlay
    if (event.code == KeyCode::KEY_ESCAPE && event.action == KeyAction::DOWN) {
        auto overlayManager = GetOverlayManager(GetInstanceId());
        CHECK_NULL_RETURN(overlayManager, false);
        auto currentContainer = Container::Current();
        CHECK_NULL_RETURN(currentContainer, false);
        if (currentContainer->IsSubContainer() || currentContainer->IsDialogContainer()) {
            return overlayManager->RemoveOverlayInSubwindow();
        } else {
            return overlayManager->RemoveOverlay(false) || SheetManager::GetInstance().RemoveSheetByESC();
        }
    }
    return false;
}

bool KeyEventManager::OnFocusAxisEvent(const FocusAxisEvent& event)
{
    auto container = Container::GetContainer(GetInstanceId());
    CHECK_NULL_RETURN(container, false);
    auto pipeline = DynamicCast<NG::PipelineContext>(container->GetPipelineContext());
    CHECK_NULL_RETURN(pipeline, false);
    auto rootNode = pipeline->GetRootElement();
    CHECK_NULL_RETURN(rootNode, false);
    auto focusNodeHub = rootNode->GetFocusHub();
    CHECK_NULL_RETURN(focusNodeHub, false);
    focusNodeHub->HandleEvent(event);
    return true;
}

bool KeyEventManager::OnCrownEvent(const CrownEvent& event)
{
    auto container = Container::GetContainer(GetInstanceId());
    CHECK_NULL_RETURN(container, false);
    auto pipeline = DynamicCast<NG::PipelineContext>(container->GetPipelineContext());
    CHECK_NULL_RETURN(pipeline, false);
    auto rootNode = pipeline->GetRootElement();
    CHECK_NULL_RETURN(rootNode, false);
    auto focusNodeHub = rootNode->GetFocusHub();
    CHECK_NULL_RETURN(focusNodeHub, false);
    focusNodeHub->HandleEvent(event);
    return true;
}

bool KeyEventManager::TriggerKeyEventDispatch(const KeyEvent& event)
{
    auto focusManager = GetFocusManager(GetInstanceId());
    auto curFocusView = focusManager ? focusManager->GetLastFocusView().Upgrade() : nullptr;
    auto curEntryFocusView = curFocusView ? curFocusView->GetEntryFocusView() : nullptr;
    auto curEntryFocusViewFrame = curEntryFocusView ? curEntryFocusView->GetFrameNode() : nullptr;
    if (event.isPreIme) {
        return DispatchKeyEventNG(event, curEntryFocusViewFrame);
    }

    if (IsSkipShortcutAndFocusMove()) {
        TAG_LOGD(AceLogTag::ACE_FOCUS, "Skip dispatching tab key because Web is current focus");
    } else if (DispatchTabKey(event, curFocusView)) {
        return true;
    }
    return DispatchKeyEventNG(event, curEntryFocusViewFrame) || isTabJustTriggerOnKeyEvent_;
}

bool KeyEventManager::IsSkipShortcutAndFocusMove()
{
    auto focusManager = GetFocusManager(GetInstanceId());
    CHECK_NULL_RETURN(focusManager, false);

    // Web component will NOT dispatch shortcut during the first event dispatch process.
    // Web component will NOT trigger focus move during the third event dispatch process.
    auto focusHub = focusManager->GetCurrentFocus();
    auto curFrameNode = focusHub ? focusHub->GetFrameNode() : nullptr;
    CHECK_NULL_RETURN(curFrameNode, false);
    return curFrameNode->GetTag() == V2::WEB_ETS_TAG;
}

bool KeyEventManager::DispatchTabKey(const KeyEvent& event, const RefPtr<FocusView>& curFocusView)
{
    auto focusManager = GetFocusManager(GetInstanceId());
    CHECK_NULL_RETURN(focusManager, false);
    isTabJustTriggerOnKeyEvent_ = focusManager->HandleKeyForExtendOrActivateFocus(event, curFocusView);
    auto curEntryFocusView = curFocusView ? curFocusView->GetEntryFocusView() : nullptr;
    auto curEntryFocusViewFrame = curEntryFocusView ? curEntryFocusView->GetFrameNode() : nullptr;
    if (DispatchTabIndexEventNG(event, curEntryFocusViewFrame)) {
        return true;
    }
    return false;
}

void KeyEventManager::ReDispatch(KeyEvent& keyEvent)
{
    // Set keyEvent coming from Redispatch
    keyEvent.isRedispatch = true;

    if (DispatchKeyboardShortcut(keyEvent)) {
        return;
    }
    auto focusManager = GetFocusManager(GetInstanceId());
    auto curFocusView = focusManager ? focusManager->GetLastFocusView().Upgrade() : nullptr;
    auto curEntryFocusView = curFocusView ? curFocusView->GetEntryFocusView() : nullptr;
    auto curEntryFocusViewFrame = curEntryFocusView ? curEntryFocusView->GetFrameNode() : nullptr;
    if (DispatchTabKey(keyEvent, curFocusView)) {
        return;
    }
    DispatchKeyEventNG(keyEvent, curEntryFocusViewFrame);
}
} // namespace OHOS::Ace::NG