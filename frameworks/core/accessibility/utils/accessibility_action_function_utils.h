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

#ifndef FOUNDATION_ACE_FRAMEWORKS_COMPONENTS_NG_PROPERTIES_ACCESSIBILITY_ACTION_FUNCTION_UTILS_H
#define FOUNDATION_ACE_FRAMEWORKS_COMPONENTS_NG_PROPERTIES_ACCESSIBILITY_ACTION_FUNCTION_UTILS_H

#include "base/memory/ace_type.h"
#include "core/accessibility/accessibility_utils.h"
#include "core/components_ng/base/ui_node.h"

namespace OHOS::Accessibility {
}

namespace OHOS::Ace::NG {
class FrameNode;
class accessibilityProperty;

class AccessibilityFunctionUtils {
public:
    template <typename T>
    static bool CheckCurrentHasFunc(T& ptr, const RefPtr<FrameNode>& node)
    {
        ptr = nullptr;
        CHECK_NULL_RETURN(node, false);
        auto accessibilityProperty = node->GetAccessibilityProperty<NG::AccessibilityProperty>();
        CHECK_NULL_RETURN(accessibilityProperty, false);
        ptr = accessibilityProperty->GetFunc();
        CHECK_NULL_RETURN(ptr, false);
        return true;
    }

    template <typename T>
    static bool CheckAncestorHasFunc(T& ptr, const RefPtr<FrameNode>& node, RefPtr<FrameNode>& parentNode)
    {
        ptr = nullptr;
        CHECK_NULL_RETURN(node, false);
        parentNode = node->GetParentFrameNode();
        while (parentNode) {
            if (AccessibilityFunctionUtils::CheckCurrentHasFunc(ptr, parentNode)) {
                return true;
            }
            parentNode = parentNode->GetParentFrameNode();
        }
        return false;
    }

    static AccessibilityActionResult HandleNotifyChildAction(const RefPtr<FrameNode>& node, NotifyChildActionType type)
    {
        auto result = AccessibilityActionResult::ACTION_OK;
        CHECK_NULL_RETURN(node, result);
        RefPtr<FrameNode> parentNode = nullptr;
        ActionNotifyChildAction func = nullptr;
        if (CheckAncestorHasFunc(func, node, parentNode)) {
            if (func) {
                result = func(type);
            }
        }
        if (result == AccessibilityActionResult::ACTION_RISE) {
            result = HandleNotifyChildAction(parentNode, type);
        }
        return result;
    }
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_COMPONENTS_NG_PROPERTIES_ACCESSIBILITY_ACTION_FUNCTION_UTILS_H
