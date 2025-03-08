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

#include "base/log/log.h"

using namespace OHOS::Ace;
namespace {
constexpr int32_t SEND_EVENT_FAILED = -1;
constexpr int32_t SEND_EVENT_SUCCESS = 0;

bool CheckProviderCallback(ArkUI_AccessibilityProviderCallbacks* callbacks)
{
    if (callbacks == nullptr) {
        TAG_LOGW(AceLogTag::ACE_ACCESSIBILITY, "callbacks is null");
        return false;
    }

    bool result = true;
    if (callbacks->findAccessibilityNodeInfosById == nullptr) {
        TAG_LOGW(AceLogTag::ACE_ACCESSIBILITY, "findAccessibilityNodeInfosById is null");
        result = false;
    }

    if (callbacks->findAccessibilityNodeInfosByText == nullptr) {
        TAG_LOGW(AceLogTag::ACE_ACCESSIBILITY, "findAccessibilityNodeInfosByText is null");
        result = false;
    }

    if (callbacks->findFocusedAccessibilityNode == nullptr) {
        TAG_LOGW(AceLogTag::ACE_ACCESSIBILITY, "findFocusedAccessibilityNode is null");
        result = false;
    }

    if (callbacks->findNextFocusAccessibilityNode == nullptr) {
        TAG_LOGW(AceLogTag::ACE_ACCESSIBILITY, "findNextFocusAccessibilityNode is null");
        result = false;
    }

    if (callbacks->executeAccessibilityAction == nullptr) {
        TAG_LOGW(AceLogTag::ACE_ACCESSIBILITY, "executeAccessibilityAction is null");
        result = false;
    }

    if (callbacks->clearFocusedFocusAccessibilityNode == nullptr) {
        TAG_LOGW(AceLogTag::ACE_ACCESSIBILITY, "clearFocusedFocusAccessibilityNode is null");
        result = false;
    }

    if (callbacks->getAccessibilityNodeCursorPosition == nullptr) {
        TAG_LOGW(AceLogTag::ACE_ACCESSIBILITY, "getAccessibilityNodeCursorPosition is null");
        result = false;
    }

    return result;
}
bool CheckProviderCallbackWithInstance(ArkUI_AccessibilityProviderCallbacksWithInstance* callbacks)
{
    if (callbacks == nullptr) {
        TAG_LOGW(AceLogTag::ACE_ACCESSIBILITY, "callbacks is null");
        return false;
    }

    if (callbacks->findAccessibilityNodeInfosById == nullptr) {
        TAG_LOGW(AceLogTag::ACE_ACCESSIBILITY, "findAccessibilityNodeInfosById is null");
        return false;
    }

    if (callbacks->findAccessibilityNodeInfosByText == nullptr) {
        TAG_LOGW(AceLogTag::ACE_ACCESSIBILITY, "findAccessibilityNodeInfosByText is null");
        return false;
    }

    if (callbacks->findFocusedAccessibilityNode == nullptr) {
        TAG_LOGW(AceLogTag::ACE_ACCESSIBILITY, "findFocusedAccessibilityNode is null");
        return false;
    }

    if (callbacks->findNextFocusAccessibilityNode == nullptr) {
        TAG_LOGW(AceLogTag::ACE_ACCESSIBILITY, "findNextFocusAccessibilityNode is null");
        return false;
    }

    if (callbacks->executeAccessibilityAction == nullptr) {
        TAG_LOGW(AceLogTag::ACE_ACCESSIBILITY, "executeAccessibilityAction is null");
        return false;
    }

    if (callbacks->clearFocusedFocusAccessibilityNode == nullptr) {
        TAG_LOGW(AceLogTag::ACE_ACCESSIBILITY, "clearFocusedFocusAccessibilityNode is null");
        return false;
    }

    if (callbacks->getAccessibilityNodeCursorPosition == nullptr) {
        TAG_LOGW(AceLogTag::ACE_ACCESSIBILITY, "getAccessibilityNodeCursorPosition is null");
        return false;
    }

    return true;
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

    accessibilityProviderCallbacks_ = *callbacks;
    if (registerCallback_) {
        registerCallback_(true);
    }
    TAG_LOGI(AceLogTag::ACE_ACCESSIBILITY, "AccessibilityProviderRegisterCallback success");
    return ARKUI_ACCESSIBILITY_NATIVE_RESULT_SUCCESSFUL;
}

int32_t ArkUI_AccessibilityProvider::AccessibilityProviderRegisterCallbackWithInstance(const char* instanceId,
    ArkUI_AccessibilityProviderCallbacksWithInstance* callbacks)
{
    if (!CheckProviderCallbackWithInstance(callbacks)) {
        TAG_LOGW(AceLogTag::ACE_ACCESSIBILITY, "CheckProviderCallbackWithInstance failed.");
        if (registerCallback_) {
            registerCallback_(false);
        }
        return ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER;
    }
    accessibilityProviderCallbacksWithInstance_ = *callbacks;
    if (registerCallback_) {
        registerCallback_(true);
    }
    instanceId_ = instanceId;
    TAG_LOGI(AceLogTag::ACE_ACCESSIBILITY, "AccessibilityProviderRegisterCallbackWithInstance success");
    return ARKUI_ACCESSIBILITY_NATIVE_RESULT_SUCCESSFUL;
}

int32_t ArkUI_AccessibilityProvider::FindAccessibilityNodeInfosById(
    const int64_t elementId, const int32_t mode, const int32_t requestId,
    std::vector<ArkUI_AccessibilityElementInfo>& infos)
{
    ArkUI_AccessibilityElementInfoList* accessibilityElementInfoList
        = new (std::nothrow) ArkUI_AccessibilityElementInfoList();
    if (accessibilityElementInfoList == nullptr) {
        TAG_LOGW(AceLogTag::ACE_ACCESSIBILITY, "info list is null");
        return AccessibilityProviderOperatorErrorCode::NOT_REGISTERED;
    }
    int32_t ret = 0;
    if (accessibilityProviderCallbacksWithInstance_.findAccessibilityNodeInfosById) {
        ret = accessibilityProviderCallbacksWithInstance_.findAccessibilityNodeInfosById(instanceId_.c_str(),
            elementId, static_cast<ArkUI_AccessibilitySearchMode>(mode),
            requestId, accessibilityElementInfoList);
    } else if (accessibilityProviderCallbacks_.findAccessibilityNodeInfosById) {
        ret = accessibilityProviderCallbacks_.findAccessibilityNodeInfosById(
            elementId, static_cast<ArkUI_AccessibilitySearchMode>(mode),
            requestId, accessibilityElementInfoList);
    } else {
        TAG_LOGW(AceLogTag::ACE_ACCESSIBILITY, "findAccessibilityNodeInfosById is null");
        return AccessibilityProviderOperatorErrorCode::NOT_REGISTERED;
    }

    if (!accessibilityElementInfoList->CopyAccessibilityElementInfo(infos)) {
        ret = AccessibilityProviderOperatorErrorCode::COPY_FAILED;
    }

    delete accessibilityElementInfoList;
    accessibilityElementInfoList = nullptr;
    return ret;
}

int32_t ArkUI_AccessibilityProvider::FindAccessibilityNodeInfosByText(
    const int64_t elementId, std::string text, const int32_t requestId,
    std::vector<ArkUI_AccessibilityElementInfo>& infos)
{
    ArkUI_AccessibilityElementInfoList* accessibilityElementInfoList
        = new (std::nothrow) ArkUI_AccessibilityElementInfoList();
    if (accessibilityElementInfoList == nullptr) {
        TAG_LOGW(AceLogTag::ACE_ACCESSIBILITY, "info list is null");
        return AccessibilityProviderOperatorErrorCode::NOT_REGISTERED;
    }
    int32_t ret = 0;
    if (accessibilityProviderCallbacksWithInstance_.findAccessibilityNodeInfosByText) {
        ret = accessibilityProviderCallbacksWithInstance_.findAccessibilityNodeInfosByText(instanceId_.c_str(),
            elementId, text.c_str(), requestId, accessibilityElementInfoList);
    } else if (accessibilityProviderCallbacks_.findAccessibilityNodeInfosByText) {
        ret = accessibilityProviderCallbacks_.findAccessibilityNodeInfosByText(
            elementId, text.c_str(), requestId, accessibilityElementInfoList);
    } else {
        TAG_LOGW(AceLogTag::ACE_ACCESSIBILITY, "findAccessibilityNodeInfosByText is null");
        return AccessibilityProviderOperatorErrorCode::NOT_REGISTERED;
    }

    if (!accessibilityElementInfoList->CopyAccessibilityElementInfo(infos)) {
        ret = AccessibilityProviderOperatorErrorCode::COPY_FAILED;
    }

    delete accessibilityElementInfoList;
    accessibilityElementInfoList = nullptr;
    return ret;
}

int32_t ArkUI_AccessibilityProvider::FindFocusedAccessibilityNode(
    const int64_t elementId, int32_t focusType, const int32_t requestId,
    ArkUI_AccessibilityElementInfo& elementInfo)
{
    if (accessibilityProviderCallbacksWithInstance_.findFocusedAccessibilityNode) {
        return accessibilityProviderCallbacksWithInstance_.findFocusedAccessibilityNode(instanceId_.c_str(),
            elementId, static_cast<ArkUI_AccessibilityFocusType>(focusType), requestId, &elementInfo);
    } else if (accessibilityProviderCallbacks_.findFocusedAccessibilityNode) {
        return accessibilityProviderCallbacks_.findFocusedAccessibilityNode(elementId,
            static_cast<ArkUI_AccessibilityFocusType>(focusType), requestId, &elementInfo);
    } else {
        TAG_LOGW(AceLogTag::ACE_ACCESSIBILITY, "findFocusedAccessibilityNode is null");
        return AccessibilityProviderOperatorErrorCode::NOT_REGISTERED;
    }
}

int32_t ArkUI_AccessibilityProvider::FindNextFocusAccessibilityNode(
    const int64_t elementId, int32_t direction, const int32_t requestId,
    ArkUI_AccessibilityElementInfo& elementInfo)
{
    if (accessibilityProviderCallbacksWithInstance_.findNextFocusAccessibilityNode) {
        return accessibilityProviderCallbacksWithInstance_.findNextFocusAccessibilityNode(instanceId_.c_str(),
            elementId, static_cast<ArkUI_AccessibilityFocusMoveDirection>(direction), requestId, &elementInfo);
    } else if (accessibilityProviderCallbacks_.findNextFocusAccessibilityNode) {
        return accessibilityProviderCallbacks_.findNextFocusAccessibilityNode(elementId,
            static_cast<ArkUI_AccessibilityFocusMoveDirection>(direction), requestId, &elementInfo);
    } else {
        TAG_LOGW(AceLogTag::ACE_ACCESSIBILITY, "findNextFocusAccessibilityNode is null");
        return AccessibilityProviderOperatorErrorCode::NOT_REGISTERED;
    }
}

int32_t ArkUI_AccessibilityProvider::ExecuteAccessibilityAction(
    const int64_t elementId, int32_t action, const int32_t requestId,
    const std::map<std::string, std::string>& actionArguments)
{
    if (accessibilityProviderCallbacksWithInstance_.executeAccessibilityAction) {
        return accessibilityProviderCallbacksWithInstance_.executeAccessibilityAction(instanceId_.c_str(), elementId,
            static_cast<ArkUI_Accessibility_ActionType>(action),
            new ArkUI_AccessibilityActionArguments(actionArguments),
            requestId);
    } else if (accessibilityProviderCallbacks_.executeAccessibilityAction) {
        return accessibilityProviderCallbacks_.executeAccessibilityAction(
            elementId, static_cast<ArkUI_Accessibility_ActionType>(action),
            new ArkUI_AccessibilityActionArguments(actionArguments), requestId);
    } else {
        TAG_LOGW(AceLogTag::ACE_ACCESSIBILITY, "executeAccessibilityAction is null");
        return AccessibilityProviderOperatorErrorCode::NOT_REGISTERED;
    }
}

int32_t ArkUI_AccessibilityProvider::ClearFocusedAccessibilityNode()
{
    if (accessibilityProviderCallbacksWithInstance_.clearFocusedFocusAccessibilityNode) {
        return accessibilityProviderCallbacksWithInstance_.clearFocusedFocusAccessibilityNode(instanceId_.c_str());
    } else if (accessibilityProviderCallbacks_.clearFocusedFocusAccessibilityNode) {
        return accessibilityProviderCallbacks_.clearFocusedFocusAccessibilityNode();
    } else {
        TAG_LOGW(AceLogTag::ACE_ACCESSIBILITY, "clearFocusedFocusAccessibilityNode is null");
        return AccessibilityProviderOperatorErrorCode::NOT_REGISTERED;
    }
}

int32_t ArkUI_AccessibilityProvider::GetAccessibilityNodeCursorPosition(
    const int64_t elementId, const int32_t requestId, int32_t &cursorPosition)
{
    if (accessibilityProviderCallbacksWithInstance_.getAccessibilityNodeCursorPosition) {
        return accessibilityProviderCallbacksWithInstance_.getAccessibilityNodeCursorPosition(instanceId_.c_str(),
            elementId, requestId, &cursorPosition);
    } else if (accessibilityProviderCallbacks_.getAccessibilityNodeCursorPosition) {
        return accessibilityProviderCallbacks_.getAccessibilityNodeCursorPosition(
            elementId, requestId, &cursorPosition);
    } else {
        TAG_LOGW(AceLogTag::ACE_ACCESSIBILITY, "getAccessibilityNodeCursorPosition is null");
        return AccessibilityProviderOperatorErrorCode::NOT_REGISTERED;
    }
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
    return accessibilityProviderCallbacks_.findAccessibilityNodeInfosById != nullptr ||
        accessibilityProviderCallbacksWithInstance_.findAccessibilityNodeInfosById != nullptr;
}

void ArkUI_AccessibilityProvider::SetRegisterCallback(RegisterCallback callback)
{
    registerCallback_ = callback;
}
