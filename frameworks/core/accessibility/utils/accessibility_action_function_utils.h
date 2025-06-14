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
    static bool CheckCurrentHasFunc(ActionNotifyChildAction& ptr, const RefPtr<FrameNode>& node)
    {
        ptr = nullptr;
        CHECK_NULL_RETURN(node, false);
        auto accessibilityProperty = node->GetAccessibilityProperty<NG::AccessibilityProperty>();
        CHECK_NULL_RETURN(accessibilityProperty, false);
        ptr = accessibilityProperty->GetNotifyChildActionFunc();
        CHECK_NULL_RETURN(ptr, false);
        return true;
    }

    static bool CheckCurrentHasFunc(ActionAccessibilityActionIntercept& ptr, const RefPtr<FrameNode>& node)
    {
        ptr = nullptr;
        CHECK_NULL_RETURN(node, false);
        auto accessibilityProperty = node->GetAccessibilityProperty<NG::AccessibilityProperty>();
        CHECK_NULL_RETURN(accessibilityProperty, false);
        ptr = accessibilityProperty->GetAccessibilityActionInterceptFunc();
        CHECK_NULL_RETURN(ptr, false);
        return true;
    }

    static bool CheckCurrentHasFunc(ActionSecurityClickAction& ptr, const RefPtr<FrameNode>& node)
    {
        ptr = nullptr;
        CHECK_NULL_RETURN(node, false);
        auto accessibilityProperty = node->GetAccessibilityProperty<NG::AccessibilityProperty>();
        CHECK_NULL_RETURN(accessibilityProperty, false);
        ptr = accessibilityProperty->GetSecurityClickActionFunc();
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
        RefPtr<FrameNode> childNode = node;
        ActionNotifyChildAction func = nullptr;
        while (CheckAncestorHasFunc(func, childNode, parentNode)) {
            if (func) {
                result = func(node, type);
            }
            if (result != AccessibilityActionResult::ACTION_RISE) {
                break;
            }
            childNode = parentNode;
        }
        return result;
    }

    static AccessibilityActionInterceptResult HandleAccessibilityActionIntercept(const RefPtr<FrameNode>& node,
        AccessibilityInterfaceAction action)
    {
        auto result = AccessibilityActionInterceptResult::ACTION_CONTINUE;
        CHECK_NULL_RETURN(node, result);

        ActionAccessibilityActionIntercept func = nullptr;
        auto currentHasFunc = CheckCurrentHasFunc(func, node);
        CHECK_EQUAL_RETURN(currentHasFunc, false, result);
        CHECK_NULL_RETURN(func, result);
        result = func(action);
        if (result != AccessibilityActionInterceptResult::ACTION_RISE) {
            return result;
        }

        RefPtr<FrameNode> parentNode = nullptr;
        if (CheckAncestorHasFunc(func, node, parentNode)) {
            return HandleAccessibilityActionIntercept(parentNode, action);
        } else {
            return AccessibilityActionInterceptResult::ACTION_CONTINUE;
        }
    }

    static bool HandleClickBySecComponent(const RefPtr<FrameNode>& node, const SecCompEnhanceEvent& secEvent)
    {
        CHECK_NULL_RETURN(node, false);
        ActionSecurityClickAction func = nullptr;
        if (!CheckCurrentHasFunc(func, node)) {
            return false;
        }
        CHECK_NULL_RETURN(func, false);
        func(secEvent);
        return true;
    }
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_COMPONENTS_NG_PROPERTIES_ACCESSIBILITY_ACTION_FUNCTION_UTILS_H
