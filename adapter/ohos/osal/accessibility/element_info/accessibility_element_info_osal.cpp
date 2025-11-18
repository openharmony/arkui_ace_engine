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

#include "adapter/ohos/osal/js_accessibility_manager.h"
#include "frameworks/core/accessibility/utils/accessibility_property_utils.h"
#include "frameworks/core/accessibility/node_utils/accessibility_frame_node_utils.h"

using namespace OHOS::Accessibility;
using namespace OHOS::AccessibilityConfig;

namespace OHOS::Ace::Framework {

namespace {
void UpdateCheckedSelectedElementInfo(const RefPtr<NG::AccessibilityProperty>& accessibilityProperty,
    AccessibilityElementInfo& nodeInfo, bool isEnable)
{
    if (accessibilityProperty->HasUserCheckedType()) {
        nodeInfo.SetChecked(accessibilityProperty->GetUserCheckedType());
    } else {
        nodeInfo.SetChecked(accessibilityProperty->IsChecked());
    }
    if (accessibilityProperty->HasUserSelected()) {
        nodeInfo.SetSelected(accessibilityProperty->IsUserSelected());
    } else {
        nodeInfo.SetSelected(accessibilityProperty->IsSelected());
    }

    if (isEnable) {
        if (accessibilityProperty->HasUserCheckable()) {
            nodeInfo.SetCheckable(accessibilityProperty->IsUserCheckable());
        } else {
            nodeInfo.SetCheckable(accessibilityProperty->IsCheckable());
        }
    }
}

void RemoveControllerTextFromGroup(const RefPtr<NG::FrameNode>& controllerNode,
    const RefPtr<NG::AccessibilityProperty>& accessibilityProperty,
    AccessibilityElementInfo& nodeInfo)
{
    CHECK_NULL_VOID(controllerNode);
    CHECK_NULL_VOID(accessibilityProperty);
    if (!NG::AccessibilityPropertyUtils::NeedRemoveControllerTextFromGroup(controllerNode)) {
        return;
    }
    auto content = nodeInfo.GetContent();
    CHECK_EQUAL_VOID(content.empty(), true);
    auto text = accessibilityProperty->GetText();
    CHECK_EQUAL_VOID(text.empty(), true);
    size_t pos = content.find(text);
    if (pos != std::string::npos) {
        content.erase(pos, text.length());
        nodeInfo.SetContent(content);
    }
}
} // namespace

void JsAccessibilityManager::CheckStateTakeOver(const RefPtr<NG::FrameNode>& node, AccessibilityElementInfo& nodeInfo)
{
    CHECK_NULL_VOID(node);
    RefPtr<NG::FrameNode> controllerNode;
    auto controllerType = NG::AccessibilityPropertyUtils::CheckAndGetStateController(node, controllerNode);
    CHECK_EQUAL_VOID(controllerType, NG::StateControllerType::CONTROLLER_NONE);
    CHECK_NULL_VOID(controllerNode);
    auto accessibilityProperty = controllerNode->GetAccessibilityProperty<NG::AccessibilityProperty>();
    CHECK_NULL_VOID(accessibilityProperty);
    if ((controllerType == NG::StateControllerType::CONTROLLER_CHECK)
        || (controllerType == NG::StateControllerType::CONTROLLER_CHECK_WITH_EXTRA)) {
        UpdateCheckedSelectedElementInfo(accessibilityProperty, nodeInfo, nodeInfo.IsEnabled());
        auto controllerNodeTag = controllerNode->GetTag();
        if (accessibilityProperty->HasAccessibilityRole()) {
            controllerNodeTag = accessibilityProperty->GetAccessibilityRole();
        }
        if (accessibilityProperty->HasAccessibilityCustomRole()) {
            controllerNodeTag = accessibilityProperty->GetAccessibilityCustomRole();
        }
        nodeInfo.SetCustomComponentType(controllerNodeTag);
        nodeInfo.SetDescriptionInfo(accessibilityProperty->GetAccessibilityDescription());
        RemoveControllerTextFromGroup(controllerNode, accessibilityProperty, nodeInfo);
    }
    if (controllerType == NG::StateControllerType::CONTROLLER_CHECK_WITH_EXTRA) {
        ExtraElementInfo extraElementInfo = nodeInfo.GetExtraElement();
        accessibilityProperty->GetAllExtraElementInfo(extraElementInfo);
        nodeInfo.SetExtraElement(extraElementInfo);
    }
}

void JsAccessibilityManager::CheckActionTakeOver(const RefPtr<NG::FrameNode>& node, AccessibilityElementInfo& nodeInfo)
{
    CHECK_NULL_VOID(node);
    RefPtr<NG::FrameNode> controllerNode;
    auto controllerType = NG::AccessibilityPropertyUtils::CheckAndGetActionController(node, controllerNode);
    CHECK_NE_VOID(controllerType, NG::ActionControllerType::CONTROLLER_CLICK);
    CHECK_NULL_VOID(controllerNode);
    auto accessibilityProperty = controllerNode->GetAccessibilityProperty<NG::AccessibilityProperty>();
    CHECK_NULL_VOID(accessibilityProperty);
    auto eventHub = controllerNode->GetEventHub<NG::EventHub>();
    CHECK_NULL_VOID(eventHub);
    auto gestureEventHub = eventHub->GetGestureEventHub();
    CHECK_NULL_VOID(gestureEventHub);
    CHECK_NE_VOID(gestureEventHub->IsAccessibilityClickable(), true);
    nodeInfo.SetClickable(gestureEventHub->IsAccessibilityClickable());

    AccessibleAction action(ACCESSIBILITY_ACTION_CLICK, "ace");
    auto actionlist = nodeInfo.GetActionList();
    auto find = std::find_if(actionlist.begin(), actionlist.end(),
        [](AccessibleAction& actionIt) { return actionIt.GetActionType() == ACCESSIBILITY_ACTION_CLICK; });
    if (find == actionlist.end()) {
        nodeInfo.AddAction(action);
    }
}

void JsAccessibilityManager::UpdateUserAccessibilityElementInfo(
    const RefPtr<NG::AccessibilityProperty>& accessibilityProperty, AccessibilityElementInfo& nodeInfo)
{
    CHECK_NULL_VOID(accessibilityProperty);
    if (accessibilityProperty->HasUserDisabled()) {
        nodeInfo.SetEnabled(!accessibilityProperty->IsUserDisabled());
    }
    UpdateCheckedSelectedElementInfo(accessibilityProperty, nodeInfo, nodeInfo.IsEnabled());
}

void JsAccessibilityManager::UpdateHasChildText(
    const RefPtr<NG::FrameNode>& node, AccessibilityElementInfo& nodeInfo)
{
    CHECK_NULL_VOID(node);
    CHECK_EQUAL_VOID(AceApplicationInfo::GetInstance().IsAccessibilityScreenReadEnabled(), false);
    auto belongTreeId = nodeInfo.GetBelongTreeId();
    if (belongTreeId <= 0) {
        return;
    }

    NG::FindCondition condition = [](const RefPtr<NG::FrameNode>& node) {
        CHECK_NULL_RETURN(node, false);
        auto accessibilityProperty = node->GetAccessibilityProperty<NG::AccessibilityProperty>();
        CHECK_NULL_RETURN(accessibilityProperty, false);
        auto hasText = !NG::AccessibilityPropertyUtils::GetContent(accessibilityProperty).empty();
        auto hasHint = !accessibilityProperty->GetHintText().empty();
        auto hasAccessibilityText =
            !NG::AccessibilityPropertyUtils::GetAccessibilityText(accessibilityProperty).empty();
        auto hasAccessibilityDescription = !accessibilityProperty->GetAccessibilityDescription().empty();
        return hasText || hasHint || hasAccessibilityText || hasAccessibilityDescription;
    };
    auto childNode = NG::AccessibilityFrameNodeUtils::GetFramenodeByCondition(node, condition);
    CHECK_NULL_VOID(childNode);
    ExtraElementInfo extraElementInfo = nodeInfo.GetExtraElement();
    extraElementInfo.SetExtraElementInfo("childText", "true"); // flag for child tree scene
    nodeInfo.SetExtraElement(extraElementInfo);
}
} // namespace OHOS::Ace::Framework