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

#include <list>
#include <string>
#include <utility>
#include <vector>

#include "base/memory/referenced.h"

namespace OHOS::Accessibility {
    class AccessibilityElementInfo;
}

namespace OHOS::Ace::NG {
class FrameNode;
class UINode;
}

namespace OHOS::Ace::Framework {
struct CommonProperty;

bool IsExtensionComponent(const RefPtr<NG::UINode>& node);
bool IsUIExtensionShowPlaceholder(const RefPtr<NG::UINode>& node);
void GetFrameNodeChildren(
    const RefPtr<NG::UINode>& uiNode,
    std::vector<std::pair<int64_t, int32_t>>& childrenIdInfo,
    const CommonProperty& commonProperty);
void DumpAccessibilityElementInfosTreeNG(
    std::list<Accessibility::AccessibilityElementInfo>& infos, int32_t depth, int64_t accessibilityId, bool isRoot);

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

    static void DumpCustomActionTest(
        const std::vector<std::string>& params,
        const RefPtr<OHOS::Ace::NG::FrameNode>& frameNode);
};
} // OHOS::Ace::Framework
#endif // FOUNDATION_ACE_ADAPTER_OHOS_OSAL_ACCESSIBILITY_ACCESSIBILITY_HIDUMPER_OSAL_H