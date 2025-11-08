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

#include "adapter/ohos/osal/accessibility/focus_move/accessibility_focus_third_node_utils.h"
#include "adapter/ohos/osal/js_third_provider_interaction_operation.h"
#include "frameworks/core/accessibility/accessibility_manager.h"
#include "frameworks/core/accessibility/accessibility_provider.h"

namespace OHOS::Ace::Framework {

ThirdRulesCheckNode::ThirdRulesCheckNode(std::shared_ptr<ArkUI_AccessibilityElementInfo> nodeInfo,
    int64_t accessibilityId,
    const WeakPtr<AccessibilityProvider>& accessibilityProvider)
    : FocusRulesCheckNode(accessibilityId), nodeInfo_(std::move(nodeInfo)),
    accessibilityProvider_(accessibilityProvider)
{
}

bool ThirdRulesCheckNode::GetPropText(Accessibility::PropValue& value)
{
    CHECK_NULL_RETURN(nodeInfo_, false);
    value.valueType = Accessibility::ValueType::STRING;
    value.valueStr = nodeInfo_->GetContents();
    return true;
}

bool ThirdRulesCheckNode::GetPropHintText(Accessibility::PropValue& value)
{
    CHECK_NULL_RETURN(nodeInfo_, false);
    value.valueType = Accessibility::ValueType::STRING;
    value.valueStr = nodeInfo_->GetHintText();
    return true;
}

bool ThirdRulesCheckNode::GetPropDesc(Accessibility::PropValue& value)
{
    CHECK_NULL_RETURN(nodeInfo_, false);
    value.valueType = Accessibility::ValueType::STRING;
    value.valueStr = nodeInfo_->GetAccessibilityDescription();
    return true;
}

bool ThirdRulesCheckNode::GetPropAccessibilityText(Accessibility::PropValue& value)
{
    CHECK_NULL_RETURN(nodeInfo_, false);
    value.valueType = Accessibility::ValueType::STRING;
    value.valueStr = nodeInfo_->GetAccessibilityText();
    return true;
}

bool ThirdRulesCheckNode::GetPropType(Accessibility::PropValue& value)
{
    CHECK_NULL_RETURN(nodeInfo_, false);
    value.valueType = Accessibility::ValueType::STRING;
    value.valueStr = nodeInfo_->GetComponentType();
    return true;
}

bool ThirdRulesCheckNode::GetPropAccessibilityLevel(Accessibility::PropValue& value)
{
    CHECK_NULL_RETURN(nodeInfo_, false);
    value.valueType = Accessibility::ValueType::STRING;
    value.valueStr = nodeInfo_->GetAccessibilityLevel();
    return true;
}

bool ThirdRulesCheckNode::GetPropAccessibilityGroup(Accessibility::PropValue& value)
{
    CHECK_NULL_RETURN(nodeInfo_, false);
    value.valueType = Accessibility::ValueType::BOOL;
    value.valueBool = nodeInfo_->GetAccessibilityGroup();
    return true;
}

bool ThirdRulesCheckNode::GetPropIsEnable(Accessibility::PropValue& value)
{
    CHECK_NULL_RETURN(nodeInfo_, false);
    value.valueType = Accessibility::ValueType::BOOL;
    value.valueBool = nodeInfo_->IsEnabled();
    return true;
}

bool ThirdRulesCheckNode::GetPropChildrenCount(Accessibility::PropValue& value)
{
    CHECK_NULL_RETURN(nodeInfo_, false);
    value.valueType = Accessibility::ValueType::NUMBER;
    auto children = nodeInfo_->GetChildNodeIds();
    value.valueNum = static_cast<int32_t>(children.size());
    return true;
}

bool ThirdRulesCheckNode::GetPropActionNames(Accessibility::PropValue& value)
{
    value.valueType = Accessibility::ValueType::ARRAY;
    CHECK_NULL_RETURN(nodeInfo_, false);
    auto supportAceActions = nodeInfo_->GetOperationActions();
    for (auto& action: supportAceActions) {
        auto findResult = AccessibilityFocusStrategy::actionToFocusActionName.find(
            static_cast<OHOS::Accessibility::ActionType>(action.actionType));
        if (findResult != AccessibilityFocusStrategy::actionToFocusActionName.end()) {
            value.valueArray.insert(findResult->second);
        }
    }
    return true;
}

template<typename T>
std::vector<std::shared_ptr<T>> ThirdRulesCheckNode::GetChildrenTemplate()
{
    std::vector<std::shared_ptr<T>> checkNodeChildren;
    CHECK_NULL_RETURN(nodeInfo_, checkNodeChildren);
    auto childrenIds = nodeInfo_->GetChildNodeIds();
    for (auto& childId : childrenIds) {
        if (childId == -1) {
            continue;
        }
        if (childId == Accessibility::AccessibilityElementInfo::ROOT_PARENT_ID) {
            continue;
        }
        auto child = std::make_shared<ArkUI_AccessibilityElementInfo>();
        if (JsThirdProviderInteractionOperation::FindNativeInfoById(accessibilityProvider_, childId, child)) {
            auto childCheckNode = std::make_shared<ThirdRulesCheckNode>(
                child, child->GetElementId(), accessibilityProvider_);
            checkNodeChildren.push_back(childCheckNode);
        }
    }
    return checkNodeChildren;
}

std::vector<std::shared_ptr<FocusRulesCheckNode>> ThirdRulesCheckNode::GetAceChildren()
{
    return GetChildrenTemplate<FocusRulesCheckNode>();
}

std::vector<std::shared_ptr<Accessibility::ReadableRulesNode>> ThirdRulesCheckNode::GetChildren()
{
    return GetChildrenTemplate<Accessibility::ReadableRulesNode>();
}

std::shared_ptr<FocusRulesCheckNode> ThirdRulesCheckNode::GetAceParent()
{
    CHECK_NULL_RETURN(nodeInfo_, nullptr);
    auto parentId = nodeInfo_->GetParentId();
    if ((parentId == -1) || (parentId == Accessibility::AccessibilityElementInfo::ROOT_PARENT_ID)) {
        return nullptr;
    }
    auto parent = std::make_shared<ArkUI_AccessibilityElementInfo>();
    if (JsThirdProviderInteractionOperation::FindNativeInfoById(accessibilityProvider_, parentId, parent)) {
        auto parentCheckNode = std::make_shared<ThirdRulesCheckNode>(
            parent, parent->GetElementId(), accessibilityProvider_);
        return parentCheckNode;
    }
    return nullptr;
}

std::shared_ptr<Accessibility::ReadableRulesNode> ThirdRulesCheckNode::GetParent()
{
    return GetAceParent();
}
} // OHOS::Ace::Framework
