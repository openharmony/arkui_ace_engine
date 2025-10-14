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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_ACCESSIBILITY_UTILS_ACCESSIBILITY_PROPERTY_UTILS_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_ACCESSIBILITY_UTILS_ACCESSIBILITY_PROPERTY_UTILS_H

#include "base/memory/ace_type.h"
#include "core/accessibility/accessibility_utils.h"
#include "core/components_ng/base/frame_node.h"

namespace OHOS::Ace::NG {
class AccessibilityProperty;

enum class StateControllerType : int32_t {
    CONTROLLER_NONE = 0,
    CONTROLLER_CHECK = 1,
    CONTROLLER_CHECK_WITH_EXTRA = 2
};

enum class ActionControllerType : int32_t {
    CONTROLLER_NONE = 0,
    CONTROLLER_CLICK = 1
};

class AccessibilityPropertyUtils {
public:
    static std::string GetContent(const RefPtr<AccessibilityProperty>& accessibilityProperty);
    static std::string GetAccessibilityText(const RefPtr<AccessibilityProperty>& accessibilityProperty);
    static std::string GetComponentType(
        const RefPtr<FrameNode>& node, const RefPtr<AccessibilityProperty>& accessibilityProperty);
    static StateControllerType CheckAndGetStateController(
        const RefPtr<FrameNode>& node, RefPtr<FrameNode>& controllerNode);
    static ActionControllerType CheckAndGetActionController(
        const RefPtr<FrameNode>& node, RefPtr<FrameNode>& controllerNode);
    static bool NeedRemoveControllerTextFromGroup(const RefPtr<FrameNode>& controllerNode);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_ACCESSIBILITY_UTILS_ACCESSIBILITY_PROPERTY_UTILS_H
