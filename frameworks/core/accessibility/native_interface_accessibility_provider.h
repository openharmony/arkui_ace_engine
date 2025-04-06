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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_ACCESSIBILITY_NATIVE_INTERFACE_ACCESSIBILITY_HANDLE_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_ACCESSIBILITY_NATIVE_INTERFACE_ACCESSIBILITY_HANDLE_H

#include <functional>
#include <memory>

#include "core/accessibility/accessibility_provider.h"

enum AccessibilityProviderOperatorErrorCode : int32_t {
    OPERATOR_SUCCESS = 0,
    NOT_REGISTERED = -10001,
    COPY_FAILED = -10002,
};

struct ArkUI_AccessibilityProvider {
public:
    ArkUI_AccessibilityProvider() = default;
    virtual ~ArkUI_AccessibilityProvider() {}
    using RegisterCallback = std::function<void(bool)>;

    int32_t FindAccessibilityNodeInfosById(
        const int64_t elementId, const int32_t mode, const int32_t requestId,
        std::vector<ArkUI_AccessibilityElementInfo>& infos);
    int32_t FindAccessibilityNodeInfosByText(
        const int64_t elementId, std::string text, const int32_t requestId,
        std::vector<ArkUI_AccessibilityElementInfo>& infos);
    int32_t FindFocusedAccessibilityNode(
        const int64_t elementId, int32_t focusType, const int32_t requestId,
        ArkUI_AccessibilityElementInfo& elementInfo);
    int32_t FindNextFocusAccessibilityNode(
        const int64_t elementId, int32_t direction, const int32_t requestId,
        ArkUI_AccessibilityElementInfo& elementInfo);
    int32_t ExecuteAccessibilityAction(
        const int64_t elementId, int32_t action, const int32_t requestId,
        const std::map<std::string, std::string>& actionArguments);
    int32_t ClearFocusedAccessibilityNode();
    int32_t GetAccessibilityNodeCursorPosition(
        const int64_t elementId, const int32_t requestId, int32_t &cursorPosition);
    int32_t SendAccessibilityAsyncEvent(
        ArkUI_AccessibilityEventInfo* accessibilityEvent,
        void (*callback)(int32_t errorCode));
    int32_t AccessibilityProviderRegisterCallback(
        ArkUI_AccessibilityProviderCallbacks* callbacks);
    int32_t AccessibilityProviderRegisterCallbackWithInstance(const char* instanceId,
        ArkUI_AccessibilityProviderCallbacksWithInstance* callbacks);
    void SetInnerAccessibilityProvider(
        const OHOS::Ace::WeakPtr<OHOS::Ace::AccessibilityProvider>& accessibilityProvider);
    bool IsRegister();
    void SetRegisterCallback(RegisterCallback callback);

private:
    ArkUI_AccessibilityProviderCallbacks accessibilityProviderCallbacks_ {};
    ArkUI_AccessibilityProviderCallbacksWithInstance accessibilityProviderCallbacksWithInstance_ {};
    OHOS::Ace::WeakPtr<OHOS::Ace::AccessibilityProvider> accessibilityProvider_;
    RegisterCallback registerCallback_;
    std::string instanceId_;
};
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_ACCESSIBILITY_NATIVE_INTERFACE_ACCESSIBILITY_HANDLE_H