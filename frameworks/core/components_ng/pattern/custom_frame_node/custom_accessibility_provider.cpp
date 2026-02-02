/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

#include "core/components_ng/pattern/custom_frame_node/custom_accessibility_provider.h"

#include "base/utils/utils.h"
#include "core/accessibility/native_interface_accessibility_impl.h"
#include "core/accessibility/native_interface_accessibility_provider.h"
#include "core/components_ng/pattern/custom_frame_node/custom_pattern.h"

namespace OHOS::Ace::NG {
namespace {
ArkUI_AccessibilityProvider* GetNativeProvider(const WeakPtr<CustomPattern>& weakPattern)
{
    auto pattern = weakPattern.Upgrade();
    CHECK_NULL_RETURN(pattern, nullptr);
    return pattern->GetNativeAccessibilityProvider();
}
} // namespace

int32_t CustomAccessibilityProvider::FindAccessibilityNodeInfosById(
    const int64_t elementId, const int32_t mode, const int32_t requestId,
    std::vector<ArkUI_AccessibilityElementInfo>& infos)
{
    int32_t errorCode = 0;
    auto provider = GetNativeProvider(weakPattern_);
    CHECK_NULL_RETURN(provider, errorCode);
    int32_t ret = provider->FindAccessibilityNodeInfosById(elementId, mode, requestId, infos);
    CHECK_EQUAL_RETURN(ret, AccessibilityProviderOperatorErrorCode::NOT_REGISTERED, errorCode);
    return ret;
}

int32_t CustomAccessibilityProvider::FindAccessibilityNodeInfosByText(
    const int64_t elementId, std::string text, const int32_t requestId,
    std::vector<ArkUI_AccessibilityElementInfo>& infos)
{
    int32_t errorCode = 0;
    auto provider = GetNativeProvider(weakPattern_);
    CHECK_NULL_RETURN(provider, errorCode);
    int32_t ret = provider->FindAccessibilityNodeInfosByText(elementId, text, requestId, infos);
    CHECK_EQUAL_RETURN(ret, AccessibilityProviderOperatorErrorCode::NOT_REGISTERED, errorCode);
    return ret;
}

int32_t CustomAccessibilityProvider::FindFocusedAccessibilityNode(
    const int64_t elementId, int32_t focusType, const int32_t requestId,
    ArkUI_AccessibilityElementInfo& elementInfo)
{
    int32_t errorCode = 0;
    auto provider = GetNativeProvider(weakPattern_);
    CHECK_NULL_RETURN(provider, errorCode);
    int32_t ret = provider->FindFocusedAccessibilityNode(elementId, focusType, requestId, elementInfo);
    CHECK_EQUAL_RETURN(ret, AccessibilityProviderOperatorErrorCode::NOT_REGISTERED, errorCode);
    return ret;
}

int32_t CustomAccessibilityProvider::FindNextFocusAccessibilityNode(
    const int64_t elementId, int32_t direction, const int32_t requestId,
    ArkUI_AccessibilityElementInfo& elementInfo)
{
    int32_t errorCode = 0;
    auto provider = GetNativeProvider(weakPattern_);
    CHECK_NULL_RETURN(provider, errorCode);
    int32_t ret = provider->FindNextFocusAccessibilityNode(elementId, direction, requestId, elementInfo);
    CHECK_EQUAL_RETURN(ret, AccessibilityProviderOperatorErrorCode::NOT_REGISTERED, errorCode);
    return ret;
}

int32_t CustomAccessibilityProvider::ExecuteAccessibilityAction(
    const int64_t elementId, int32_t action, const int32_t requestId,
    const std::map<std::string, std::string>& actionArguments)
{
    int32_t errorCode = 0;
    auto provider = GetNativeProvider(weakPattern_);
    CHECK_NULL_RETURN(provider, errorCode);
    int32_t ret = provider->ExecuteAccessibilityAction(elementId, action, requestId, actionArguments);
    CHECK_EQUAL_RETURN(ret, AccessibilityProviderOperatorErrorCode::NOT_REGISTERED, errorCode);
    return ret;
}

int32_t CustomAccessibilityProvider::ClearFocusedAccessibilityNode()
{
    int32_t errorCode = 0;
    auto provider = GetNativeProvider(weakPattern_);
    CHECK_NULL_RETURN(provider, errorCode);
    int32_t ret = provider->ClearFocusedAccessibilityNode();
    CHECK_EQUAL_RETURN(ret, AccessibilityProviderOperatorErrorCode::NOT_REGISTERED, errorCode);
    return ret;
}

int32_t CustomAccessibilityProvider::GetAccessibilityNodeCursorPosition(
    const int64_t elementId, const int32_t requestId, int32_t &cursorPosition)
{
    int32_t errorCode = 0;
    auto provider = GetNativeProvider(weakPattern_);
    CHECK_NULL_RETURN(provider, errorCode);
    int32_t ret = provider->GetAccessibilityNodeCursorPosition(elementId, requestId, cursorPosition);
    CHECK_EQUAL_RETURN(ret, AccessibilityProviderOperatorErrorCode::NOT_REGISTERED, errorCode);
    return ret;
}

int32_t CustomAccessibilityProvider::SendAccessibilityAsyncEvent(
    const ArkUI_AccessibilityEventInfo& accessibilityEvent,
    void (*callback)(int32_t errorCode))
{
    constexpr int32_t SEND_EVENT_FAILED = -1;
    auto mgr = thirdAccessibilityManager_.lock();
    if (mgr == nullptr) {
        if (callback) {
            callback(SEND_EVENT_FAILED);
        }
        return SEND_EVENT_FAILED;
    }
    mgr->SendAccessibilityAsyncEvent(accessibilityEvent, callback);
    return 0;
}

void CustomAccessibilityProvider::SendThirdAccessibilityProvider(
    const std::weak_ptr<ThirdAccessibilityManager>& thirdAccessibilityManager)
{
    thirdAccessibilityManager_ = thirdAccessibilityManager;
}
} // namespace OHOS::Ace::NG
