/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

#include "adapter/ohos/osal/accessibility/focus_move/accessibility_focus_virtual_node_utils.h"
#include "adapter/ohos/osal/accessibility/focus_move/accessibility_focus_frame_node_utils.h"
#include "frameworks/core/accessibility/accessibility_manager.h"

namespace OHOS::Ace::Framework {

bool VirtualAccessibilityNodeRulesCheckNode::GetPropText(Accessibility::PropValue& value)
{
    auto node = weakNode_.Upgrade();
    CHECK_NULL_RETURN(node, false);
    value.valueType = Accessibility::ValueType::STRING;
    value.valueStr = node->GetAccessibilityText();
    return true;
}

bool VirtualAccessibilityNodeRulesCheckNode::GetPropHintText(Accessibility::PropValue& value)
{
    auto node = weakNode_.Upgrade();
    CHECK_NULL_RETURN(node, false);
    value.valueType = Accessibility::ValueType::STRING;
    value.valueStr = "";
    return true;
}

bool VirtualAccessibilityNodeRulesCheckNode::GetPropDesc(Accessibility::PropValue& value)
{
    auto node = weakNode_.Upgrade();
    CHECK_NULL_RETURN(node, false);
    value.valueType = Accessibility::ValueType::STRING;
    value.valueStr = "";
    return true;
}

bool VirtualAccessibilityNodeRulesCheckNode::GetPropAccessibilityText(Accessibility::PropValue& value)
{
    auto node = weakNode_.Upgrade();
    CHECK_NULL_RETURN(node, false);
    value.valueType = Accessibility::ValueType::STRING;
    value.valueStr = "";
    return true;
}

bool VirtualAccessibilityNodeRulesCheckNode::GetPropType(Accessibility::PropValue& value)
{
    auto node = weakNode_.Upgrade();
    CHECK_NULL_RETURN(node, false);
    value.valueType = Accessibility::ValueType::STRING;
    value.valueStr = node->GetRole();
    return true;
}

bool VirtualAccessibilityNodeRulesCheckNode::GetPropAccessibilityLevel(Accessibility::PropValue& value)
{
    auto node = weakNode_.Upgrade();
    CHECK_NULL_RETURN(node, false);
    value.valueType = Accessibility::ValueType::STRING;
    value.valueStr = node->GetAccessibilityLevel();
    return true;
}

bool VirtualAccessibilityNodeRulesCheckNode::GetPropAccessibilityGroup(Accessibility::PropValue& value)
{
    auto node = weakNode_.Upgrade();
    CHECK_NULL_RETURN(node, false);
    value.valueType = Accessibility::ValueType::BOOL;
    value.valueBool = node->GetAccessibilityGroup();
    return true;
}

bool VirtualAccessibilityNodeRulesCheckNode::GetPropIsEnable(Accessibility::PropValue& value)
{
    auto node = weakNode_.Upgrade();
    CHECK_NULL_RETURN(node, false);
    value.valueType = Accessibility::ValueType::BOOL;
    value.valueBool = node->GetEnabled();
    return true;
}

bool VirtualAccessibilityNodeRulesCheckNode::GetPropChildrenCount(Accessibility::PropValue& value)
{
    auto node = weakNode_.Upgrade();
    CHECK_NULL_RETURN(node, false);
    value.valueType = Accessibility::ValueType::NUMBER;
    value.valueNum = static_cast<int32_t>(node->GetChildCount());
    return true;
}

bool VirtualAccessibilityNodeRulesCheckNode::GetPropActionNames(Accessibility::PropValue& value)
{
    value.valueType = Accessibility::ValueType::ARRAY;
    auto node = weakNode_.Upgrade();
    CHECK_NULL_RETURN(node, false);
    std::string accessibilityFocusStr = "accessibilityFocus";
    value.valueArray.insert(accessibilityFocusStr);
    return true;
}

template<typename T>
std::vector<std::shared_ptr<T>> VirtualAccessibilityNodeRulesCheckNode::GetChildrenTemplate()
{
    std::vector<std::shared_ptr<T>> checkNodeChildren;
    auto node = weakNode_.Upgrade();
    CHECK_NULL_RETURN(node, checkNodeChildren);
    const auto& children = node->GetChildren();
    auto hostNode = hostFrameNode_.Upgrade();
    CHECK_NULL_RETURN(hostNode, checkNodeChildren);
    auto containerId = NG::VirtualNodeContainerIdManager::GetInstance().GetContainerId(hostNode);
    for (auto& child : children) {
        CHECK_NULL_CONTINUE(child);
        auto virtualNodeId = NG::VirtualNodeContainerIdManager::EncodeVirtualNodeAccessibilityId(
            containerId, child->GetNodeId());
        checkNodeChildren.push_back(
            std::make_shared<VirtualAccessibilityNodeRulesCheckNode>(child, virtualNodeId, hostFrameNode_));
    }

    return checkNodeChildren;
}

std::vector<std::shared_ptr<FocusRulesCheckNode>> VirtualAccessibilityNodeRulesCheckNode::GetAceChildren()
{
    return GetChildrenTemplate<FocusRulesCheckNode>();
}

std::vector<std::shared_ptr<Accessibility::ReadableRulesNode>> VirtualAccessibilityNodeRulesCheckNode::GetChildren()
{
    return GetChildrenTemplate<Accessibility::ReadableRulesNode>();
}

std::shared_ptr<FocusRulesCheckNode> VirtualAccessibilityNodeRulesCheckNode::GetAceParent()
{
    auto node = weakNode_.Upgrade();
    CHECK_NULL_RETURN(node, nullptr);
    auto hostNode = hostFrameNode_.Upgrade();
    CHECK_NULL_RETURN(hostNode, nullptr);
    auto parent = node->GetParent();
    if (parent) {
        auto containerId = NG::VirtualNodeContainerIdManager::GetInstance().GetContainerId(hostNode);
        auto virtualNodeId = NG::VirtualNodeContainerIdManager::EncodeVirtualNodeAccessibilityId(
            containerId, parent->GetNodeId());
        return std::make_shared<VirtualAccessibilityNodeRulesCheckNode>(parent, virtualNodeId, hostFrameNode_);
    }

    return std::make_shared<FrameNodeRulesCheckNode>(hostNode, hostNode->GetAccessibilityId());
}

std::shared_ptr<Accessibility::ReadableRulesNode> VirtualAccessibilityNodeRulesCheckNode::GetParent()
{
    return GetAceParent();
}
} // OHOS::Ace::Framework