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

#include "adapter/ohos/osal/accessibility/focus_move/accessibility_focus_accessibility_node_utils.h"
#include "frameworks/core/accessibility/accessibility_manager.h"

namespace OHOS::Ace::Framework {

AccessibilityNodeRulesCheckNode::AccessibilityNodeRulesCheckNode(
    const WeakPtr<AccessibilityNode>& node, int64_t accessibilityId)
    : FocusRulesCheckNode(accessibilityId), weakNode_(node)
{
}

bool AccessibilityNodeRulesCheckNode::GetPropText(Accessibility::PropValue& value)
{
    auto node = weakNode_.Upgrade();
    CHECK_NULL_RETURN(node, false);
    value.valueType = Accessibility::ValueType::STRING;
    if (node->GetIsPassword()) {
        std::string strStar(node->GetText().size(), '*');
        value.valueStr = strStar;
    } else {
        value.valueStr = node->GetText();
    }
    return true;
}

bool AccessibilityNodeRulesCheckNode::GetPropHintText(Accessibility::PropValue& value)
{
    auto node = weakNode_.Upgrade();
    CHECK_NULL_RETURN(node, false);
    value.valueType = Accessibility::ValueType::STRING;
    value.valueStr = node->GetHintText();
    return true;
}

bool AccessibilityNodeRulesCheckNode::GetPropDesc(Accessibility::PropValue& value)
{
    auto node = weakNode_.Upgrade();
    CHECK_NULL_RETURN(node, false);
    value.valueType = Accessibility::ValueType::STRING;
    value.valueStr = "";
    return true;
}

bool AccessibilityNodeRulesCheckNode::GetPropAccessibilityText(Accessibility::PropValue& value)
{
    auto node = weakNode_.Upgrade();
    CHECK_NULL_RETURN(node, false);
    value.valueType = Accessibility::ValueType::STRING;
    value.valueStr = "";
    return true;
}

bool AccessibilityNodeRulesCheckNode::GetPropType(Accessibility::PropValue& value)
{
    auto node = weakNode_.Upgrade();
    CHECK_NULL_RETURN(node, false);
    value.valueType = Accessibility::ValueType::STRING;
    value.valueStr = node->GetTag();
    return true;
}

bool AccessibilityNodeRulesCheckNode::GetPropAccessibilityLevel(Accessibility::PropValue& value)
{
    auto node = weakNode_.Upgrade();
    CHECK_NULL_RETURN(node, false);
    value.valueType = Accessibility::ValueType::STRING;
    value.valueStr = "auto";
    return true;
}

bool AccessibilityNodeRulesCheckNode::GetPropAccessibilityGroup(Accessibility::PropValue& value)
{
    auto node = weakNode_.Upgrade();
    CHECK_NULL_RETURN(node, false);
    value.valueType = Accessibility::ValueType::BOOL;
    value.valueBool = false;
    return true;
}

bool AccessibilityNodeRulesCheckNode::GetPropIsEnable(Accessibility::PropValue& value)
{
    auto node = weakNode_.Upgrade();
    CHECK_NULL_RETURN(node, false);
    value.valueType = Accessibility::ValueType::BOOL;
    value.valueBool = node->GetEnabledState();
    return true;
}

bool AccessibilityNodeRulesCheckNode::GetPropChildrenCount(Accessibility::PropValue& value)
{
    auto node = weakNode_.Upgrade();
    CHECK_NULL_RETURN(node, false);
    value.valueType = Accessibility::ValueType::NUMBER;
    auto children = node->GetChildList();
    value.valueNum = static_cast<int32_t>(children.size());
    return true;
}

bool AccessibilityNodeRulesCheckNode::GetPropActionNames(Accessibility::PropValue& value)
{
    value.valueType = Accessibility::ValueType::ARRAY;
    auto node = weakNode_.Upgrade();
    CHECK_NULL_RETURN(node, false);
    auto supportAceActions = node->GetSupportAction();
    for (auto& action: supportAceActions) {
        auto findResult = AccessibilityFocusStrategy::aceActionToFocusActionName.find(action);
        if (findResult != AccessibilityFocusStrategy::aceActionToFocusActionName.end()) {
            value.valueArray.insert(findResult->second);
        }
    }
    return true;
}

template<typename T>
std::vector<std::shared_ptr<T>> AccessibilityNodeRulesCheckNode::GetChildrenTemplate()
{
    std::vector<std::shared_ptr<T>> checkNodeChildren;
    auto node = weakNode_.Upgrade();
    CHECK_NULL_RETURN(node, checkNodeChildren);
    auto children = node->GetChildList();
    for (auto& child : children) {
        CHECK_NULL_CONTINUE(child);
        checkNodeChildren.push_back(
            std::make_shared<AccessibilityNodeRulesCheckNode>(child, static_cast<int64_t>(child->GetNodeId())));
    }

    return checkNodeChildren;
}

std::vector<std::shared_ptr<FocusRulesCheckNode>> AccessibilityNodeRulesCheckNode::GetAceChildren()
{
    return GetChildrenTemplate<FocusRulesCheckNode>();
}

std::vector<std::shared_ptr<Accessibility::ReadableRulesNode>> AccessibilityNodeRulesCheckNode::GetChildren()
{
    return GetChildrenTemplate<Accessibility::ReadableRulesNode>();
}

std::shared_ptr<FocusRulesCheckNode> AccessibilityNodeRulesCheckNode::GetAceParent()
{
    auto node = weakNode_.Upgrade();
    CHECK_NULL_RETURN(node, nullptr);
    auto parent = node->GetParentNode();
    CHECK_NULL_RETURN(parent, nullptr);
    auto checkNode =
        std::make_shared<AccessibilityNodeRulesCheckNode>(parent, static_cast<int64_t>(parent->GetNodeId()));
    return checkNode;
}

std::shared_ptr<Accessibility::ReadableRulesNode> AccessibilityNodeRulesCheckNode::GetParent()
{
    return GetAceParent();
}
} // OHOS::Ace::Framework
