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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMMON_IME_INPUT_METHOD_MANAGER_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMMON_IME_INPUT_METHOD_MANAGER_H

#include "base/memory/referenced.h"
#include "core/components_ng/base/frame_node.h"

namespace OHOS::Ace {
class InputMethodManager final {

public:
    static InputMethodManager* GetInstance();
    void OnFocusNodeChange(const RefPtr<NG::FrameNode>& focusNode);
    void SetWindowFocus(bool windowFocus);
    bool NeedSoftKeyboard() const;
    // Close the keyboard in-process
    void CloseKeyboard();
    void CloseKeyboardInProcess();
    void CloseKeyboardInPipelineDestroy();
    void CloseKeyboard(const RefPtr<NG::FrameNode>& focusNode);
    // Hide the keyboard across processes
    void HideKeyboardAcrossProcesses();
    void ProcessModalPageScene();

private:
    InputMethodManager() = default;
    InputMethodManager(const InputMethodManager&) = delete;
    InputMethodManager& operator=(const InputMethodManager&) = delete;

    void ProcessKeyboardInWindowScene(const RefPtr<NG::FrameNode>& curFocusNode);
    void ProcessKeyboard(const RefPtr<NG::FrameNode>& curFocusNode);

    static std::unique_ptr<InputMethodManager> instance_;
    static std::mutex mtx_;

    std::optional<bool> windowFocus_;
    WeakPtr<NG::FrameNode> curFocusNode_;
    bool lastKeep_ = false;
};
} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMMON_IME_INPUT_METHOD_MANAGER_H