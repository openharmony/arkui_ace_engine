/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 */

#include "core/common/key_event_manager.h"

namespace OHOS::Ace::NG {
void KeyEventManager::AddKeyboardShortcutNode(const WeakPtr<FrameNode>& node)
{
    (void)node;
}

void KeyEventManager::DelKeyboardShortcutNode(int32_t nodeId)
{
    (void)nodeId;
}

uint8_t KeyEventManager::GetKeyboardShortcutKeys(const std::vector<ModifierKey>& keys)
{
    (void)keys;
    return 0;
}

bool KeyEventManager::IsSameKeyboardShortcutNode(const std::string& value, uint8_t keys)
{
    (void)value;
    (void)keys;
    return false;
}

bool KeyEventManager::DispatchKeyboardShortcut(const KeyEvent& event)
{
    (void)event;
    return false;
}

void KeyEventManager::ReDispatch(KeyEvent& keyEvent)
{
    (void)keyEvent;
}

bool KeyEventManager::RemoveOverlayByESC(const KeyEvent& keyEvent)
{
    (void)keyEvent;
    return false;
}

void KeyEventManager::SetIsKeyConsumed(bool value)
{
    isKeyConsumed_ = value;
}

bool KeyEventManager::OnKeyEvent(const KeyEvent& event)
{
    if (event.action != KeyAction::DOWN) {
        return false;
    }
    if (event.code != KeyCode::KEY_TAB) {
        return false;
    }
    return event.HasKey(KeyCode::KEY_TAB);
}

bool KeyEventManager::OnFocusAxisEvent(const FocusAxisEvent& event)
{
    (void)event;
    return false;
}

bool KeyEventManager::OnCrownEvent(const CrownEvent& event)
{
    (void)event;
    return false;
}

bool KeyEventManager::DispatchKeyEventNG(const KeyEvent& event, const RefPtr<FrameNode>& focusNode)
{
    (void)event;
    (void)focusNode;
    return false;
}

bool KeyEventManager::DispatchTabIndexEventNG(const KeyEvent& event, const RefPtr<FrameNode>& mainView)
{
    (void)event;
    (void)mainView;
    return false;
}

bool KeyEventManager::TriggerKeyEventDispatch(const KeyEvent& event)
{
    (void)event;
    return false;
}

bool KeyEventManager::IsSystemKeyboardShortcut(const KeyEvent& event)
{
    (void)event;
    return false;
}

bool KeyEventManager::DispatchTabKey(const KeyEvent& event, const RefPtr<FocusView>& curFocusView)
{
    (void)event;
    (void)curFocusView;
    return false;
}

bool KeyEventManager::IsSkipShortcutAndFocusMove()
{
    return false;
}
} // namespace OHOS::Ace::NG
