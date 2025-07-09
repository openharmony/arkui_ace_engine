/*
* Copyright (c) 2025 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_ADAPTER_OHOS_OSAL_ACCESSIBILITY_ACCESSIBILITY_HIDUMPER_OSAL_H
#define FOUNDATION_ACE_ADAPTER_OHOS_OSAL_ACCESSIBILITY_ACCESSIBILITY_HIDUMPER_OSAL_H

#include <string>
#include "accessibility_element_info.h"

#include "core/accessibility/accessibility_utils.h"

namespace OHOS::Accessibility {
    class AccessibilityElementInfo;
}

namespace OHOS::Ace::Framework {
struct ActionTable {
    AceAction aceAction;
    Accessibility::ActionType action;
};

using ToInfoFunc = std::function<void(std::string& input)>;

struct ActionStrTable {
    Accessibility::ActionType action;
    std::string actionStr;
};

enum class ToInfoMode {
    TO_STRING,
    DUMPLOG_ADD,
};

class AccessibilityElementInfoUtils {
public:
    AccessibilityElementInfoUtils() = default;
    ~AccessibilityElementInfoUtils() = default;

    static void ToKeyInfo(
        const Accessibility::AccessibilityElementInfo& accessibilityElementInfo,
        int32_t treeId);
    static void ToCommonInfo(
        const Accessibility::AccessibilityElementInfo& accessibilityElementInfo,
        int32_t treeId);
    static void ToDetailInfo(
        const Accessibility::AccessibilityElementInfo& accessibilityElementInfo,
        int32_t treeId);
};

class AccessibilityManagerHidumper {
public:
    AccessibilityManagerHidumper() = default;
    ~AccessibilityManagerHidumper() = default;

    static AceAction ConvertAccessibilityAction(Accessibility::ActionType accessibilityAction);
    static std::string ConvertActionTypeToString(Accessibility::ActionType action);
};
} // OHOS::Ace::Framework
#endif // FOUNDATION_ACE_ADAPTER_OHOS_OSAL_ACCESSIBILITY_ACCESSIBILITY_HIDUMPER_OSAL_H