/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 */

#include <memory>
#include <mutex>

#include "core/common/ime/input_method_manager.h"

namespace OHOS::Ace {
std::unique_ptr<InputMethodManager> InputMethodManager::instance_ = nullptr;
std::mutex InputMethodManager::mtx_;

InputMethodManager* InputMethodManager::GetInstance()
{
    if (instance_ == nullptr) {
        std::lock_guard<std::mutex> lock(mtx_);
        if (instance_ == nullptr) {
            instance_.reset(new InputMethodManager);
        }
    }
    return instance_.get();
}

void InputMethodManager::OnFocusNodeChange(const RefPtr<NG::FrameNode>& focusNode, FocusReason focusReason)
{
    (void)focusNode;
    (void)focusReason;
}

void InputMethodManager::ManageFocusNode(const RefPtr<NG::FrameNode>& focusNode, FocusReason focusReason, bool saveKeyboard)
{
    (void)focusNode;
    (void)focusReason;
    (void)saveKeyboard;
}

void InputMethodManager::ProcessKeyboardInWindowScene(const RefPtr<NG::FrameNode>& curFocusNode)
{
    (void)curFocusNode;
}

void InputMethodManager::ProcessKeyboard(const RefPtr<NG::FrameNode>& curFocusNode)
{
    (void)curFocusNode;
}

void InputMethodManager::SetWindowFocus(bool windowFocus)
{
    (void)windowFocus;
}

bool InputMethodManager::NeedSoftKeyboard() const
{
    return false;
}

void InputMethodManager::CloseKeyboard(bool disableNeedToRequestKeyboard)
{
    (void)disableNeedToRequestKeyboard;
}

void InputMethodManager::CloseKeyboardInProcess() {}

void InputMethodManager::CloseKeyboardInPipelineDestroy() {}

void InputMethodManager::CloseKeyboard(const RefPtr<NG::FrameNode>& focusNode)
{
    (void)focusNode;
}

void InputMethodManager::CloseCustomKeyboard(bool isUIExtension)
{
    (void)isUIExtension;
}

void InputMethodManager::HideKeyboardAcrossProcesses() {}

void InputMethodManager::ProcessModalPageScene() {}
} // namespace OHOS::Ace
