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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_XCOMPONENT_XCOMPONENT_ACCESSIBILITY_PROVIDER_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_XCOMPONENT_XCOMPONENT_ACCESSIBILITY_PROVIDER_H

#include "core/accessibility/accessibility_provider.h"

namespace OHOS::Ace::NG {
class XComponentPattern;

class XComponentAccessibilityProvider : public AccessibilityProvider {
    DECLARE_ACE_TYPE(XComponentAccessibilityProvider, AccessibilityProvider);
public:
    XComponentAccessibilityProvider(const WeakPtr<XComponentPattern> &xComponentPattern)
        : weakPattern_(xComponentPattern) {}
    int32_t FindAccessibilityNodeInfosById(
        const int64_t elementId, const int32_t mode, const int32_t requestId,
        std::vector<ArkUI_AccessibilityElementInfo>& infos) override;
    int32_t FindAccessibilityNodeInfosByText(
        const int64_t elementId, std::string text, const int32_t requestId,
        std::vector<ArkUI_AccessibilityElementInfo>& infos) override;
    int32_t FindFocusedAccessibilityNode(
        const int64_t elementId, int32_t focusType, const int32_t requestId,
        ArkUI_AccessibilityElementInfo& elementInfo) override;
    int32_t FindNextFocusAccessibilityNode(
        const int64_t elementId, int32_t direction, const int32_t requestId,
        ArkUI_AccessibilityElementInfo& elementInfo) override;
    int32_t ExecuteAccessibilityAction(
        const int64_t elementId, int32_t action, const int32_t requestId,
        const std::map<std::string, std::string>& actionArguments) override;
    int32_t ClearFocusedAccessibilityNode() override;
    int32_t GetAccessibilityNodeCursorPosition(
        const int64_t elementId, const int32_t requestId, int32_t &cursorPosition) override;
    int32_t SendAccessibilityAsyncEvent(
        const ArkUI_AccessibilityEventInfo& accessibilityEvent,
        void (*callback)(int32_t errorCode)) override;
    void SendThirdAccessibilityProvider(
        const std::weak_ptr<ThirdAccessibilityManager>& thirdAccessibilityManager) override;
private:
    WeakPtr<XComponentPattern> weakPattern_;
    std::weak_ptr<ThirdAccessibilityManager> thirdAccessibilityManager_;
};
} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_XCOMPONENT_XCOMPONENT_ACCESSIBILITY_PROVIDER_H
