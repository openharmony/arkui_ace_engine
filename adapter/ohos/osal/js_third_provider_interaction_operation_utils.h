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

#ifndef FOUNDATION_ACE_FRAMEWORKS_BRIDGE_COMMON_ACCESSIBILITY_JS_THIRD_PROVIDER_INTERATION_OPERATION_UTILS_H
#define FOUNDATION_ACE_FRAMEWORKS_BRIDGE_COMMON_ACCESSIBILITY_JS_THIRD_PROVIDER_INTERATION_OPERATION_UTILS_H

#include "accessibility_element_info.h"
#include "accessibility_event_info.h"
#include "base/utils/utils.h"
#include "frameworks/core/accessibility/native_interface_accessibility_impl.h"

namespace OHOS::Ace::Framework {
class AccessibilityThirdProviderUtils {
public:
    AccessibilityThirdProviderUtils() = default;
    ~AccessibilityThirdProviderUtils() = default;
    static void TransformAccessibilityElementInfo(const ArkUI_AccessibilityElementInfo& nativeInfo,
        OHOS::Accessibility::AccessibilityElementInfo& accessibilityElementInfo);

    static void TransformAccessbilityEventInfo(
        const ArkUI_AccessibilityEventInfo& nativeEventInfo,
        OHOS::Accessibility::AccessibilityEventInfo& accessibilityEventInfo);
private:
    static void TransformAccessibilityElementInfoBasic(const ArkUI_AccessibilityElementInfo& nativeInfo,
        OHOS::Accessibility::AccessibilityElementInfo& accessibilityElementInfo);
};
} // namespace OHOS::Ace::Framework
#endif // FOUNDATION_ACE_FRAMEWORKS_BRIDGE_COMMON_ACCESSIBILITY_JS_THIRD_PROVIDER_INTERATION_OPERATION_UTILS_H