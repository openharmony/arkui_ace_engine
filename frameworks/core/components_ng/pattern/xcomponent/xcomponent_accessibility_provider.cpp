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

#include "core/components_ng/pattern/xcomponent/xcomponent_accessibility_provider.h"

#include "base/log/log_wrapper.h"
#include "base/utils/utils.h"
#include "core/components/common/layout/constants.h"
#include "core/components_ng/pattern/xcomponent/xcomponent_pattern.h"

namespace OHOS::Ace::NG {
namespace {
constexpr int32_t SEND_EVENT_FAILED = -1;

ArkUI_AccessibilityProvider* GetAccessbilityProvider(
    const WeakPtr<XComponentPattern>& weakPattern)
{
    auto pattern = weakPattern.Upgrade();
    CHECK_NULL_RETURN(pattern, nullptr);
    return pattern->GetNativeProvider();
}
}
int32_t XComponentAccessibilityProvider::FindAccessibilityNodeInfosById(
    const int64_t elementId, const int32_t mode, const int32_t requestId,
    std::vector<ArkUI_AccessibilityElementInfo>& infos)
{
    int32_t errorCode = 0;
    auto accessbilityProvider = GetAccessbilityProvider(weakPattern_);
    CHECK_NULL_RETURN(accessbilityProvider, errorCode);
    int32_t ret = accessbilityProvider->FindAccessibilityNodeInfosById(
        elementId, mode, requestId, infos);
    CHECK_EQUAL_RETURN(ret, AccessibilityProviderOperatorErrorCode::NOT_REGISTERED, errorCode);
    return ret;
}

int32_t XComponentAccessibilityProvider::FindAccessibilityNodeInfosByText(
    const int64_t elementId, std::string text, const int32_t requestId,
    std::vector<ArkUI_AccessibilityElementInfo>& infos)
{
    int32_t errorCode = 0;
    auto accessbilityProvider = GetAccessbilityProvider(weakPattern_);
    CHECK_NULL_RETURN(accessbilityProvider, errorCode);
    int32_t ret = accessbilityProvider->FindAccessibilityNodeInfosByText(
        elementId, text, requestId, infos);
    CHECK_EQUAL_RETURN(ret, AccessibilityProviderOperatorErrorCode::NOT_REGISTERED, errorCode);
    return ret;
}

int32_t XComponentAccessibilityProvider::FindFocusedAccessibilityNode(
    const int64_t elementId, int32_t focusType, const int32_t requestId,
    ArkUI_AccessibilityElementInfo& info)
{
    int32_t errorCode = 0;
    auto accessbilityProvider = GetAccessbilityProvider(weakPattern_);
    CHECK_NULL_RETURN(accessbilityProvider, errorCode);
    int32_t ret = accessbilityProvider->FindFocusedAccessibilityNode(
        elementId, focusType, requestId, info);
    CHECK_EQUAL_RETURN(ret, AccessibilityProviderOperatorErrorCode::NOT_REGISTERED, errorCode);
    return ret;
}

int32_t XComponentAccessibilityProvider::FindNextFocusAccessibilityNode(
    const int64_t elementId, int32_t direction, const int32_t requestId,
    ArkUI_AccessibilityElementInfo& info)
{
    int32_t errorCode = 0;
    auto accessbilityProvider = GetAccessbilityProvider(weakPattern_);
    CHECK_NULL_RETURN(accessbilityProvider, errorCode);
    int32_t ret = accessbilityProvider->FindNextFocusAccessibilityNode(
        elementId, direction, requestId, info);
    CHECK_EQUAL_RETURN(ret, AccessibilityProviderOperatorErrorCode::NOT_REGISTERED, errorCode);
    return ret;
}

int32_t XComponentAccessibilityProvider::ExecuteAccessibilityAction(
    const int64_t elementId, int32_t action, const int32_t requestId,
    const std::map<std::string, std::string>& actionArguments)
{
    int32_t errorCode = 0;
    auto accessbilityProvider = GetAccessbilityProvider(weakPattern_);
    CHECK_NULL_RETURN(accessbilityProvider, errorCode);
    int32_t ret = accessbilityProvider->ExecuteAccessibilityAction(
        elementId, action, requestId, actionArguments);
    CHECK_EQUAL_RETURN(ret, AccessibilityProviderOperatorErrorCode::NOT_REGISTERED, errorCode);
    return ret;
}

int32_t XComponentAccessibilityProvider::ClearFocusedAccessibilityNode()
{
    int32_t errorCode = 0;
    auto accessbilityProvider = GetAccessbilityProvider(weakPattern_);
    CHECK_NULL_RETURN(accessbilityProvider, errorCode);
    int32_t ret = accessbilityProvider->ClearFocusedAccessibilityNode();
    CHECK_EQUAL_RETURN(ret, AccessibilityProviderOperatorErrorCode::NOT_REGISTERED, errorCode);
    return ret;
}

int32_t XComponentAccessibilityProvider::GetAccessibilityNodeCursorPosition(
    const int64_t elementId, const int32_t requestId, int32_t &cursorPosition)
{
    int32_t errorCode = 0;
    auto accessbilityProvider = GetAccessbilityProvider(weakPattern_);
    CHECK_NULL_RETURN(accessbilityProvider, errorCode);
    int32_t ret = accessbilityProvider->GetAccessibilityNodeCursorPosition(
        elementId, requestId, cursorPosition);
    CHECK_EQUAL_RETURN(ret, AccessibilityProviderOperatorErrorCode::NOT_REGISTERED, errorCode);
    return ret;
}

int32_t XComponentAccessibilityProvider::SendAccessibilityAsyncEvent(
    const ArkUI_AccessibilityEventInfo& accessibilityEvent,
    void (*callback)(int32_t errorCode))
{
    int32_t errorCode = 0;
    auto thirdAccessibilityManager = thirdAccessibilityManager_.lock();
    if (thirdAccessibilityManager == nullptr) {
        if (callback) {
            callback(SEND_EVENT_FAILED);
        }
        return SEND_EVENT_FAILED;
    }

    thirdAccessibilityManager->SendAccessibilityAsyncEvent(
        accessibilityEvent, callback);
    return errorCode;
}

void XComponentAccessibilityProvider::SendThirdAccessibilityProvider(
    const std::weak_ptr<ThirdAccessibilityManager>& thirdAccessibilityManager)
{
    thirdAccessibilityManager_ = thirdAccessibilityManager;
}
} // namespace OHOS::Ace::NG
