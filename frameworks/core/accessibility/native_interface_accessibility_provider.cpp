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

#include "core/accessibility/native_interface_accessibility_provider.h"

using namespace OHOS::Ace;
namespace {
constexpr int32_t NOT_REGISTERED = -1;
constexpr int32_t COPY_FAILED = -2;
constexpr int32_t SEND_EVENT_FAILED = -1;
constexpr int32_t SEND_EVENT_SUCCESS = 0;

bool CheckProviderCallback(ArkUI_AccessibilityProviderCallbacks* callbacks)
{
    if (callbacks == nullptr) {
        TAG_LOGW(AceLogTag::ACE_ACCESSIBILITY, "callbacks is null");
        return false;
    }

    bool result = true;
    if (callbacks->FindAccessibilityNodeInfosById == nullptr) {
        TAG_LOGW(AceLogTag::ACE_ACCESSIBILITY, "FindAccessibilityNodeInfosById is null");
        result = false;
    }

    if (callbacks->FindAccessibilityNodeInfosByText == nullptr) {
        TAG_LOGW(AceLogTag::ACE_ACCESSIBILITY, "FindAccessibilityNodeInfosByText is null");
        result = false;
    }

    if (callbacks->FindFocusedAccessibilityNode == nullptr) {
        TAG_LOGW(AceLogTag::ACE_ACCESSIBILITY, "FindFocusedAccessibilityNode is null");
        result = false;
    }

    if (callbacks->FindNextFocusAccessibilityNode == nullptr) {
        TAG_LOGW(AceLogTag::ACE_ACCESSIBILITY, "FindNextFocusAccessibilityNode is null");
        result = false;
    }

    if (callbacks->ExecuteAccessibilityAction == nullptr) {
        TAG_LOGW(AceLogTag::ACE_ACCESSIBILITY, "ExecuteAccessibilityAction is null");
        result = false;
    }

    if (callbacks->ClearFocusedFocusAccessibilityNode == nullptr) {
        TAG_LOGW(AceLogTag::ACE_ACCESSIBILITY, "ClearFocusedFocusAccessibilityNode is null");
        result = false;
    }

    if (callbacks->GetAccessibilityNodeCursorPosition == nullptr) {
        TAG_LOGW(AceLogTag::ACE_ACCESSIBILITY, "GetAccessibilityNodeCursorPosition is null");
        result = false;
    }

    return result;
}
}
int32_t ArkUI_AccessibilityProvider::AccessibilityProviderRegisterCallback(
    ArkUI_AccessibilityProviderCallbacks* callbacks)
{
    if (!CheckProviderCallback(callbacks)) {
        TAG_LOGW(AceLogTag::ACE_ACCESSIBILITY, "CheckProviderCallback failed.");
        if (registerCallback_) {
            registerCallback_(false);
        }
        return ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER;
    }

    accessibilityProviderCallbacks_ = callbacks;
    if (registerCallback_) {
        registerCallback_(true);
    }
    TAG_LOGI(AceLogTag::ACE_ACCESSIBILITY, "AccessibilityProviderRegisterCallback success");
    return ARKUI_ACCESSIBILITY_NATIVE_RESULT_SUCCESSFUL;
}

int32_t ArkUI_AccessibilityProvider::FindAccessibilityNodeInfosById(
    const int64_t elementId, const int32_t mode, const int32_t requestId,
    std::vector<ArkUI_AccessibilityElementInfo>& infos)
{
    if (!accessibilityProviderCallbacks_ ||
        !accessibilityProviderCallbacks_->FindAccessibilityNodeInfosById) {
        TAG_LOGW(AceLogTag::ACE_ACCESSIBILITY, "FindAccessibilityNodeInfosById is null");
        return NOT_REGISTERED;
    }

    ArkUI_AccessibilityElementInfoList* accessibilityElementInfoList
        = new (std::nothrow) ArkUI_AccessibilityElementInfoList();
    int32_t ret = accessibilityProviderCallbacks_->FindAccessibilityNodeInfosById(
        elementId, static_cast<ArkUI_AccessibilitySearchMode>(mode),
        requestId, accessibilityElementInfoList);
    if (!accessibilityElementInfoList->CopyAccessibilityElementInfo(infos)) {
        ret = COPY_FAILED;
    }

    delete accessibilityElementInfoList;
    accessibilityElementInfoList = nullptr;
    return ret;
}

int32_t ArkUI_AccessibilityProvider::FindAccessibilityNodeInfosByText(
    const int64_t elementId, std::string text, const int32_t requestId,
    std::vector<ArkUI_AccessibilityElementInfo>& infos)
{
    if (!accessibilityProviderCallbacks_ ||
        !accessibilityProviderCallbacks_->FindAccessibilityNodeInfosByText) {
        TAG_LOGW(AceLogTag::ACE_ACCESSIBILITY, "FindAccessibilityNodeInfosByText is null");
        return NOT_REGISTERED;
    }

    ArkUI_AccessibilityElementInfoList* accessibilityElementInfoList
        = new (std::nothrow) ArkUI_AccessibilityElementInfoList();
    int32_t ret = accessibilityProviderCallbacks_->FindAccessibilityNodeInfosByText(
        elementId, text.c_str(), requestId, accessibilityElementInfoList);
    if (!accessibilityElementInfoList->CopyAccessibilityElementInfo(infos)) {
        ret = COPY_FAILED;
    }

    delete accessibilityElementInfoList;
    accessibilityElementInfoList = nullptr;
    return ret;
}

int32_t ArkUI_AccessibilityProvider::FindFocusedAccessibilityNode(
    const int64_t elementId, int32_t focusType, const int32_t requestId,
    ArkUI_AccessibilityElementInfo& elementInfo)
{
    if (!accessibilityProviderCallbacks_ ||
        !accessibilityProviderCallbacks_->FindFocusedAccessibilityNode) {
        TAG_LOGW(AceLogTag::ACE_ACCESSIBILITY, "FindFocusedAccessibilityNode is null");
        return NOT_REGISTERED;
    }

    return accessibilityProviderCallbacks_->FindFocusedAccessibilityNode(elementId,
        static_cast<ArkUI_AccessibilityFocusType>(focusType), requestId, &elementInfo);
}

int32_t ArkUI_AccessibilityProvider::FindNextFocusAccessibilityNode(
    const int64_t elementId, int32_t direction, const int32_t requestId,
    ArkUI_AccessibilityElementInfo& elementInfo)
{
    if (!accessibilityProviderCallbacks_ ||
        !accessibilityProviderCallbacks_->FindNextFocusAccessibilityNode) {
        TAG_LOGW(AceLogTag::ACE_ACCESSIBILITY, "FindNextFocusAccessibilityNode is null");
        return NOT_REGISTERED;
    }

    return accessibilityProviderCallbacks_->FindNextFocusAccessibilityNode(elementId,
        static_cast<ArkUI_AccessibilityFocusMoveDirection>(direction), requestId, &elementInfo);
}

int32_t ArkUI_AccessibilityProvider::ExecuteAccessibilityAction(
    const int64_t elementId, int32_t action, const int32_t requestId,
    const std::map<std::string, std::string>& actionArguments)
{
    if (!accessibilityProviderCallbacks_ ||
        !accessibilityProviderCallbacks_->ExecuteAccessibilityAction) {
        TAG_LOGW(AceLogTag::ACE_ACCESSIBILITY, "ExecuteAccessibilityAction is null");
        return NOT_REGISTERED;
    }

    return accessibilityProviderCallbacks_->ExecuteAccessibilityAction(
        elementId,
        static_cast<ArkUI_Accessibility_ActionType>(action),
        new ArkUI_AccessibilityActionArguments(actionArguments),
        requestId);
    return NOT_REGISTERED;
}

int32_t ArkUI_AccessibilityProvider::ClearFocusedAccessibilityNode()
{
    if (!accessibilityProviderCallbacks_ ||
        !accessibilityProviderCallbacks_->ClearFocusedFocusAccessibilityNode) {
        TAG_LOGW(AceLogTag::ACE_ACCESSIBILITY, "ClearFocusedAccessibilityNode is null");
        return NOT_REGISTERED;
    }

    return accessibilityProviderCallbacks_->ClearFocusedFocusAccessibilityNode();
}

int32_t ArkUI_AccessibilityProvider::GetAccessibilityNodeCursorPosition(
    const int64_t elementId, const int32_t requestId, int32_t &cursorPosition)
{
    if (!accessibilityProviderCallbacks_ ||
        !accessibilityProviderCallbacks_->GetAccessibilityNodeCursorPosition) {
        TAG_LOGW(AceLogTag::ACE_ACCESSIBILITY, "GetAccessibilityNodeCursorPosition is null");
        return NOT_REGISTERED;
    }

    return accessibilityProviderCallbacks_->GetAccessibilityNodeCursorPosition(
        elementId, requestId, &cursorPosition);
}

int32_t ArkUI_AccessibilityProvider::SendAccessibilityAsyncEvent(
    ArkUI_AccessibilityEventInfo* accessibilityEvent,
    void (*callback)(int32_t errorCode))
{
    if (accessibilityEvent == nullptr) {
        TAG_LOGW(AceLogTag::ACE_ACCESSIBILITY, "accessibilityEvent is null");
        if (callback) {
            callback(SEND_EVENT_FAILED);
        }
        return SEND_EVENT_FAILED;
    }

    auto accessibilityProvider = accessibilityProvider_.Upgrade();
    if (accessibilityProvider == nullptr) {
        TAG_LOGW(AceLogTag::ACE_ACCESSIBILITY, "accessibilityProvider is null");
        if (callback) {
            callback(SEND_EVENT_FAILED);
        }
        return SEND_EVENT_FAILED;
    }

    accessibilityProvider->SendAccessibilityAsyncEvent(*accessibilityEvent, callback);
    return SEND_EVENT_SUCCESS;
}

void ArkUI_AccessibilityProvider::SetInnerAccessibilityProvider(
    const OHOS::Ace::WeakPtr<OHOS::Ace::AccessibilityProvider>& accessibilityProvider)
{
    accessibilityProvider_ = accessibilityProvider;
}

bool ArkUI_AccessibilityProvider::IsRegister()
{
    return accessibilityProviderCallbacks_ != nullptr;
}

void ArkUI_AccessibilityProvider::SetRegisterCallback(RegisterCallback callback)
{
    registerCallback_ = callback;
}
