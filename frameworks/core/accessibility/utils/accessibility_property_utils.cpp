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
#include "frameworks/core/accessibility/utils/accessibility_property_utils.h"

#include "base/log/log_wrapper.h"
#include "frameworks/core/accessibility/accessibility_manager.h"
#include "frameworks/core/accessibility/node_utils/accessibility_frame_node_utils.h"
#include "frameworks/core/accessibility/static/accessibility_static_utils.h"
#include "frameworks/core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {
namespace {
bool IsSupportControllerType(AccessibilityRoleType controllerByType)
{
    switch (controllerByType) {
        case AccessibilityRoleType::TOGGLER:
        case AccessibilityRoleType::CHECKBOX: // checkbox group?
        case AccessibilityRoleType::RADIO:
            return true;
        default:
            return false;
    }
    return false;
}

std::string GetAceComponentType(AccessibilityRoleType controllerByType)
{
    switch (controllerByType) {
        case AccessibilityRoleType::TOGGLER:
            return V2::TOGGLE_ETS_TAG;
        case AccessibilityRoleType::CHECKBOX: // checkbox group?
            return V2::CHECK_BOX_ETS_TAG;
        case AccessibilityRoleType::RADIO:
            return V2::RADIO_ETS_TAG;
        default:
            return "";
    }
    return "";
}

bool IsNodeOfSupportControllerType(const RefPtr<NG::FrameNode>& node, AccessibilityRoleType controllerByType)
{
    auto accessibilityProperty = node->GetAccessibilityProperty<NG::AccessibilityProperty>();
    CHECK_NULL_RETURN(accessibilityProperty, false);

    if (accessibilityProperty->HasAccessibilityCustomRole()) {
        CHECK_EQUAL_RETURN(
            accessibilityProperty->GetAccessibilityCustomRole(),
            AccessibilityUtils::GetRoleByType(controllerByType),
            true);
    }

    std::string componentType = node->GetTag();
    if (accessibilityProperty->HasAccessibilityRole()) {
        componentType = accessibilityProperty->GetAccessibilityRole();
    }
    auto targetType = GetAceComponentType(controllerByType);
    CHECK_EQUAL_RETURN(targetType, componentType, true);
    return false;
}

bool isNodeOfExtraType(const RefPtr<NG::FrameNode>& node)
{
    return IsNodeOfSupportControllerType(node, AccessibilityRoleType::TOGGLER);
}

bool CheckAndGetController(const RefPtr<FrameNode>& node,
    RefPtr<FrameNode>& controllerNode,
    const AccessibilityRoleType& controllerByType,
    const std::string& controllerByInspector)
{
    if (!controllerByInspector.empty()) {
        FindCondition condition = [controllerByType](const RefPtr<NG::FrameNode>& node) {
            auto accessibilityProperty = node->GetAccessibilityProperty<NG::AccessibilityProperty>();
            CHECK_NULL_RETURN(accessibilityProperty, false);
            return IsNodeOfSupportControllerType(node, controllerByType);
        };
        controllerNode = NG::AccessibilityFrameNodeUtils::GetFramenodeByCondition(node, condition);
        CHECK_NE_RETURN(controllerNode, nullptr, true);
    }

    if (IsSupportControllerType(controllerByType)) {
        FindCondition condition = [controllerByType](const RefPtr<NG::FrameNode>& node) {
            auto accessibilityProperty = node->GetAccessibilityProperty<NG::AccessibilityProperty>();
            CHECK_NULL_RETURN(accessibilityProperty, false);
            return IsNodeOfSupportControllerType(node, controllerByType);
        };
        controllerNode = AccessibilityFrameNodeUtils::GetFramenodeByCondition(node, condition);
        CHECK_NE_RETURN(controllerNode, nullptr, true);
    }
    return false;
}
}

std::string AccessibilityPropertyUtils::GetContent(const RefPtr<AccessibilityProperty>& accessibilityProperty)
{
    CHECK_NULL_RETURN(accessibilityProperty, "");
    if (accessibilityProperty->HasUserTextValue()) {
        return accessibilityProperty->GetUserTextValue();
    }
    return accessibilityProperty->GetGroupText();
}

std::string AccessibilityPropertyUtils::GetAccessibilityText(
    const RefPtr<AccessibilityProperty>& accessibilityProperty)
{
    CHECK_NULL_RETURN(accessibilityProperty, "");
    if (!accessibilityProperty->HasUserTextValue() && accessibilityProperty->GetAccessibilityText().empty() &&
        accessibilityProperty->IsAccessibilityGroup() && accessibilityProperty->IsAccessibilityTextPreferred()) {
        return accessibilityProperty->GetGroupPreferAccessibilityText();
    }
    return accessibilityProperty->GetAccessibilityText();
}

std::string AccessibilityPropertyUtils::GetComponentType(
    const RefPtr<FrameNode>& node, const RefPtr<AccessibilityProperty>& accessibilityProperty)
{
    std::string type;
    CHECK_NULL_RETURN(accessibilityProperty, type);
    CHECK_NULL_RETURN(node, type);
    if (accessibilityProperty->HasAccessibilityRole()) {
        type = accessibilityProperty->GetAccessibilityRole();
    } else {
        type = node->GetTag();
    }
    if (accessibilityProperty->HasAccessibilityCustomRole()) {
        type = accessibilityProperty->GetAccessibilityCustomRole();
    }
    return type;
}

StateControllerType AccessibilityPropertyUtils::CheckAndGetStateController(const RefPtr<FrameNode>& node,
    RefPtr<FrameNode>& controllerNode)
{
    CHECK_NULL_RETURN(node, StateControllerType::CONTROLLER_NONE);
    auto accessibilityProperty = node->GetAccessibilityProperty<NG::AccessibilityProperty>();
    CHECK_NULL_RETURN(accessibilityProperty, StateControllerType::CONTROLLER_NONE);
    CHECK_NE_RETURN(accessibilityProperty->IsAccessibilityGroup(), true, StateControllerType::CONTROLLER_NONE);
    auto groupOptions = accessibilityProperty->GetAccessibilityGroupOptions();
    if (CheckAndGetController(
        node, controllerNode, groupOptions.stateControllerByType, groupOptions.stateControllerByInspector)) {
        if (isNodeOfExtraType(controllerNode)) {
            return StateControllerType::CONTROLLER_CHECK_WITH_EXTRA;
        }
        return StateControllerType::CONTROLLER_CHECK;
    }
    return StateControllerType::CONTROLLER_NONE;
}

ActionControllerType AccessibilityPropertyUtils::CheckAndGetActionController(const RefPtr<FrameNode>& node,
    RefPtr<FrameNode>& controllerNode)
{
    CHECK_NULL_RETURN(node, ActionControllerType::CONTROLLER_NONE);
    auto accessibilityProperty = node->GetAccessibilityProperty<NG::AccessibilityProperty>();
    CHECK_NULL_RETURN(accessibilityProperty, ActionControllerType::CONTROLLER_NONE);
    CHECK_NE_RETURN(accessibilityProperty->IsAccessibilityGroup(), true, ActionControllerType::CONTROLLER_NONE);
    auto groupOptions = accessibilityProperty->GetAccessibilityGroupOptions();
    if (CheckAndGetController(
        node, controllerNode, groupOptions.actionControllerByType, groupOptions.actionControllerByInspector)) {
        return ActionControllerType::CONTROLLER_CLICK;
    }
    return ActionControllerType::CONTROLLER_NONE;
}
} // namespace OHOS::Ace::NG
