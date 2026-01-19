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

#include "adapter/ohos/osal/accessibility/focus_move/accessibility_focus_frame_node_utils.h"
#include "frameworks/core/accessibility/accessibility_manager.h"
#include "frameworks/core/accessibility/node_utils/accessibility_frame_node_utils.h"
#include "frameworks/core/accessibility/utils/accessibility_property_utils.h"
#include "frameworks/core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::Framework {
namespace {

int32_t GetAccessibilityZIndex(const RefPtr<NG::FrameNode>& node)
{
    CHECK_NULL_RETURN(node, -1);
    auto accessibilityProperty = node->GetAccessibilityProperty<NG::AccessibilityProperty>();
    CHECK_NULL_RETURN(accessibilityProperty, -1);
    return accessibilityProperty->GetAccessibilityZIndex();
}
} // namespace

FrameNodeRulesCheckNode::FrameNodeRulesCheckNode(const RefPtr<NG::FrameNode>& node, int64_t accessibilityId)
    : FocusRulesCheckNode(accessibilityId), weakNode_(node)
{
    std::vector<RefPtr<NG::FrameNode>> pageNodes;
    NG::AccessibilityFrameNodeUtils::GetLastestPageNodes(node, handleParam_.pageNodes);
}

bool FrameNodeRulesCheckNode::GetPropText(Accessibility::PropValue& value)
{
    auto node = weakNode_.Upgrade();
    CHECK_NULL_RETURN(node, false);
    auto accessibilityProperty = node->GetAccessibilityProperty<NG::AccessibilityProperty>();
    CHECK_NULL_RETURN(accessibilityProperty, false);
    value.valueType = Accessibility::ValueType::STRING;
    value.valueStr = NG::AccessibilityPropertyUtils::GetContent(accessibilityProperty);
    return true;
}

bool FrameNodeRulesCheckNode::GetPropHintText(Accessibility::PropValue& value)
{
    auto node = weakNode_.Upgrade();
    CHECK_NULL_RETURN(node, false);
    auto accessibilityProperty = node->GetAccessibilityProperty<NG::AccessibilityProperty>();
    CHECK_NULL_RETURN(accessibilityProperty, false);
    value.valueType = Accessibility::ValueType::STRING;
    value.valueStr = accessibilityProperty->GetHintText();
    return true;
}

bool FrameNodeRulesCheckNode::GetPropDesc(Accessibility::PropValue& value)
{
    auto node = weakNode_.Upgrade();
    CHECK_NULL_RETURN(node, false);
    auto accessibilityProperty = node->GetAccessibilityProperty<NG::AccessibilityProperty>();
    CHECK_NULL_RETURN(accessibilityProperty, false);
    value.valueType = Accessibility::ValueType::STRING;
    value.valueStr = accessibilityProperty->GetAccessibilityDescription();
    return true;
}

bool FrameNodeRulesCheckNode::GetPropAccessibilityText(Accessibility::PropValue& value)
{
    auto node = weakNode_.Upgrade();
    CHECK_NULL_RETURN(node, false);
    auto accessibilityProperty = node->GetAccessibilityProperty<NG::AccessibilityProperty>();
    CHECK_NULL_RETURN(accessibilityProperty, false);
    value.valueType = Accessibility::ValueType::STRING;
    value.valueStr = NG::AccessibilityPropertyUtils::GetAccessibilityText(accessibilityProperty);
    return true;
}

bool FrameNodeRulesCheckNode::GetPropType(Accessibility::PropValue& value)
{
    auto node = weakNode_.Upgrade();
    CHECK_NULL_RETURN(node, false);
    auto accessibilityProperty = node->GetAccessibilityProperty<NG::AccessibilityProperty>();
    CHECK_NULL_RETURN(accessibilityProperty, false);
    value.valueType = Accessibility::ValueType::STRING;
    value.valueStr = NG::AccessibilityPropertyUtils::GetComponentType(node, accessibilityProperty);
    return true;
}

bool FrameNodeRulesCheckNode::GetPropAccessibilityLevel(Accessibility::PropValue& value)
{
    auto node = weakNode_.Upgrade();
    CHECK_NULL_RETURN(node, false);
    auto accessibilityProperty = node->GetAccessibilityProperty<NG::AccessibilityProperty>();
    CHECK_NULL_RETURN(accessibilityProperty, false);
    value.valueType = Accessibility::ValueType::STRING;
    value.valueStr = accessibilityProperty->GetAccessibilityLevel();
    return true;
}

bool FrameNodeRulesCheckNode::GetPropAccessibilityGroup(Accessibility::PropValue& value)
{
    auto node = weakNode_.Upgrade();
    CHECK_NULL_RETURN(node, false);
    auto accessibilityProperty = node->GetAccessibilityProperty<NG::AccessibilityProperty>();
    CHECK_NULL_RETURN(accessibilityProperty, false);
    value.valueType = Accessibility::ValueType::BOOL;
    value.valueBool = accessibilityProperty->IsAccessibilityGroup();
    return true;
}

bool FrameNodeRulesCheckNode::GetPropIsEnable(Accessibility::PropValue& value)
{
    auto node = weakNode_.Upgrade();
    CHECK_NULL_RETURN(node, false);
    value.valueType = Accessibility::ValueType::BOOL;
    value.valueBool = NG::AccessibilityFrameNodeUtils::IsNodeEnabled(node);
    return true;
}

bool FrameNodeRulesCheckNode::GetPropChildrenCount(Accessibility::PropValue& value)
{
    value.valueType = Accessibility::ValueType::NUMBER;
    auto children = GetChildren();
    value.valueNum = children.size();
    return true;
}

bool FrameNodeRulesCheckNode::GetPropActionNames(Accessibility::PropValue& value)
{
    value.valueType = Accessibility::ValueType::ARRAY;
    auto node = weakNode_.Upgrade();
    CHECK_NULL_RETURN(node, false);
    auto accessibilityProperty = node->GetAccessibilityProperty<NG::AccessibilityProperty>();
    CHECK_NULL_RETURN(accessibilityProperty, false);

    std::string accessibilityFocusStr =
        accessibilityProperty->GetAccessibilityFocusState() ? "clearAccessibilityFocus" : "accessibilityFocus";
    value.valueArray.insert(accessibilityFocusStr);

    auto enable = NG::AccessibilityFrameNodeUtils::IsNodeEnabled(node);
    CHECK_EQUAL_RETURN(enable, false, true);
    auto focusHub = node->GetFocusHub();
    if (focusHub && focusHub->IsFocusable()) {
        std::string focusSupportAction = focusHub->IsCurrentFocus() ? "clearFocus" : "focus";
        value.valueArray.insert(focusSupportAction);
    }

    auto eventHub = node->GetEventHub<NG::EventHub>();
    auto getsureEventHub = eventHub ? eventHub->GetGestureEventHub() : nullptr;
    if (getsureEventHub) {
        if (getsureEventHub->IsAccessibilityClickable()) {
            value.valueArray.insert("click");
        }
        if (getsureEventHub->IsAccessibilityLongClickable()) {
            value.valueArray.insert("longClick");
        }
    }

    accessibilityProperty->ResetSupportAction();
    auto supportAceActions = accessibilityProperty->GetSupportAction();
    for (auto& action: supportAceActions) {
        auto findResult = AccessibilityFocusStrategy::aceActionToFocusActionName.find(action);
        if (findResult != AccessibilityFocusStrategy::aceActionToFocusActionName.end()) {
            value.valueArray.insert(findResult->second);
        }
    }
    return true;
}

template<typename T>
std::vector<std::shared_ptr<T>> FrameNodeRulesCheckNode::GetChildrenTemplate()
{
    std::vector<std::shared_ptr<T>> checkNodeChildren;
    auto node = weakNode_.Upgrade();
    CHECK_NULL_RETURN(node, checkNodeChildren);
    auto pipelineContext = node->GetContextRefPtr();
    CHECK_NULL_RETURN(pipelineContext, checkNodeChildren);
    const auto& accessibilityManager = pipelineContext->GetAccessibilityManager();
    CHECK_NULL_RETURN(accessibilityManager, checkNodeChildren);

    std::vector<RefPtr<NG::FrameNode>> children;
    NG::AccessibilityFrameNodeUtils::GetChildrenFromFrameNode(
        node, children, handleParam_, accessibilityManager);

    std::sort(children.begin(), children.end(),
        [](const auto& childA, const auto& childB) {
            return GetAccessibilityZIndex(childA) < GetAccessibilityZIndex(childB);
        });

    for (auto& child : children) {
        checkNodeChildren.push_back(
            std::make_shared<FrameNodeRulesCheckNode>(
                child, child->GetAccessibilityId(), handleParam_));
    }

    return checkNodeChildren;
}

std::vector<std::shared_ptr<FocusRulesCheckNode>> FrameNodeRulesCheckNode::GetAceChildren()
{
    return GetChildrenTemplate<FocusRulesCheckNode>();
}

std::vector<std::shared_ptr<Accessibility::ReadableRulesNode>> FrameNodeRulesCheckNode::GetChildren()
{
    return GetChildrenTemplate<Accessibility::ReadableRulesNode>();
}

std::shared_ptr<FocusRulesCheckNode> FrameNodeRulesCheckNode::GetAceParent()
{
    auto node = weakNode_.Upgrade();
    CHECK_NULL_RETURN(node, nullptr);
    auto parent = node->GetParentFrameNode();
    while (parent) {
        if ((parent->GetTag() != V2::STAGE_ETS_TAG) && (parent->GetTag() != V2::PAGE_ETS_TAG)) {
            break;
        }
        parent = parent->GetParentFrameNode();
    }
    if (!parent && node->IsAccessibilityVirtualNode()) {
        auto weakNode = AceType::DynamicCast<NG::FrameNode>(node->GetVirtualNodeParent());
        parent = weakNode.Upgrade();
    }
    CHECK_NULL_RETURN(parent, nullptr);
    auto checkNode = std::make_shared<FrameNodeRulesCheckNode>(parent, parent->GetAccessibilityId(), handleParam_);
    return checkNode;
}

std::shared_ptr<Accessibility::ReadableRulesNode> FrameNodeRulesCheckNode::GetParent()
{
    return GetAceParent();
}

bool FrameNodeRulesCheckNode::IsModal()
{
    auto node = weakNode_.Upgrade();
    CHECK_NULL_RETURN(node, true); // default value is true, means can not focus in lower component
    auto accessibilityProperty = node->GetAccessibilityProperty<NG::AccessibilityProperty>();
    CHECK_NULL_RETURN(accessibilityProperty, true);
    return accessibilityProperty->IsAccessibilityModal();
}

std::shared_ptr<FocusRulesCheckNode> FrameNodeRulesCheckNode::GetUserNextFocusNode()
{
    auto nextNode = nextNode_.Upgrade();
    CHECK_NULL_RETURN(nextNode, nullptr);
    return std::make_shared<FrameNodeRulesCheckNode>(nextNode, nextNode->GetAccessibilityId(), handleParam_);
}

std::shared_ptr<FocusRulesCheckNode> FrameNodeRulesCheckNode::GetUserPrevFocusNode()
{
    auto prevNode = prevNode_.Upgrade();
    CHECK_NULL_RETURN(prevNode, nullptr);
    return std::make_shared<FrameNodeRulesCheckNode>(prevNode, prevNode->GetAccessibilityId(), handleParam_);
}

bool FrameNodeRulesCheckNode::IsAccessibiltyVisible()
{
    auto node = weakNode_.Upgrade();
    CHECK_NULL_RETURN(node, false);
    NG::AccessibilityFrameNodeUtils::UpdateAccessibilityVisibleToRoot(node);
    return node->GetAccessibilityVisible();
}

bool FrameNodeRulesCheckNode::IsChildTreeContainer()
{
    auto node = weakNode_.Upgrade();
    CHECK_NULL_RETURN(node, false);
    auto accessibilityProperty = node->GetAccessibilityProperty<NG::AccessibilityProperty>();
    CHECK_NULL_RETURN(accessibilityProperty, false);
    return (accessibilityProperty->GetChildTreeId() > 0);
}

bool FrameNodeRulesCheckNode::IsEmbededTarget()
{
    auto node = weakNode_.Upgrade();
    CHECK_NULL_RETURN(node, false);
    auto pipelineContext = node->GetContextRefPtr();
    CHECK_NULL_RETURN(pipelineContext, false);
    const auto& accessibilityManager = pipelineContext->GetAccessibilityManager();
    CHECK_NULL_RETURN(accessibilityManager, false);
    return NG::AccessibilityFrameNodeUtils::IsValidEmbedTarget(node, accessibilityManager);
}

bool FrameNodeRulesCheckNode::IsInChildTree()
{
    auto node = weakNode_.Upgrade();
    CHECK_NULL_RETURN(node, false);
    auto pipelineContext = node->GetContextRefPtr();
    CHECK_NULL_RETURN(pipelineContext, false);
    const auto& accessibilityManager = pipelineContext->GetAccessibilityManager();
    CHECK_NULL_RETURN(accessibilityManager, false);
    return accessibilityManager->GetTreeId() > 0;
}

bool FrameNodeRulesCheckNode::IsHeaderFooterInScroll()
{
    auto node = weakNode_.Upgrade();
    CHECK_NULL_RETURN(node, false);
    auto accessibilityProperty = node->GetAccessibilityProperty<NG::AccessibilityProperty>();
    CHECK_NULL_RETURN(accessibilityProperty, false);
    return accessibilityProperty->IsHeaderOrFooter();
}

bool FrameNodeRulesCheckNode::IsBackward()
{
    auto node = weakNode_.Upgrade();
    CHECK_NULL_RETURN(node, false);
    auto accessibilityProperty = node->GetAccessibilityProperty<NG::AccessibilityProperty>();
    CHECK_NULL_RETURN(accessibilityProperty, false);
    return accessibilityProperty->GetScrollableStatus() != NG::ScrollableStatus::AT_TOP
        && accessibilityProperty->GetScrollableStatus() != NG::ScrollableStatus::AT_BOTH_TOP_BOTTOM;
}

bool FrameNodeRulesCheckNode::IsForward()
{
    auto node = weakNode_.Upgrade();
    CHECK_NULL_RETURN(node, false);
    auto accessibilityProperty = node->GetAccessibilityProperty<NG::AccessibilityProperty>();
    CHECK_NULL_RETURN(accessibilityProperty, false);
    return accessibilityProperty->GetScrollableStatus() != NG::ScrollableStatus::AT_BOTTOM
        && accessibilityProperty->GetScrollableStatus() != NG::ScrollableStatus::AT_BOTH_TOP_BOTTOM;
}

bool DetectParentRulesCheckNode::GetPropText(Accessibility::PropValue& value)
{
    value.valueType = Accessibility::ValueType::STRING;
    value.valueStr = elementInfo_.GetContent();
    return true;
}

bool DetectParentRulesCheckNode::GetPropHintText(Accessibility::PropValue& value)
{
    value.valueType = Accessibility::ValueType::STRING;
    value.valueStr = elementInfo_.GetHint();
    return true;
}

bool DetectParentRulesCheckNode::GetPropDesc(Accessibility::PropValue& value)
{
    value.valueType = Accessibility::ValueType::STRING;
    value.valueStr = elementInfo_.GetDescriptionInfo();
    return true;
}

bool DetectParentRulesCheckNode::GetPropAccessibilityText(Accessibility::PropValue& value)
{
    value.valueType = Accessibility::ValueType::STRING;
    value.valueStr = elementInfo_.GetAccessibilityText();
    return true;
}

bool DetectParentRulesCheckNode::GetPropType(Accessibility::PropValue& value)
{
    value.valueType = Accessibility::ValueType::STRING;
    value.valueStr = elementInfo_.GetComponentType();
    if (!elementInfo_.GetCustomComponentType().empty()) {
        value.valueStr = elementInfo_.GetCustomComponentType();
    }
    return true;
}

bool DetectParentRulesCheckNode::GetPropAccessibilityLevel(Accessibility::PropValue& value)
{
    value.valueType = Accessibility::ValueType::STRING;
    value.valueStr = elementInfo_.GetAccessibilityLevel();
    return true;
}

bool DetectParentRulesCheckNode::GetPropAccessibilityGroup(Accessibility::PropValue& value)
{
    value.valueType = Accessibility::ValueType::BOOL;
    value.valueBool = elementInfo_.GetAccessibilityGroup();
    return true;
}

bool DetectParentRulesCheckNode::GetPropIsEnable(Accessibility::PropValue& value)
{
    value.valueType = Accessibility::ValueType::BOOL;
    value.valueBool = elementInfo_.IsEnabled();
    return true;
}

bool DetectParentRulesCheckNode::GetPropChildrenCount(Accessibility::PropValue& value)
{
    value.valueType = Accessibility::ValueType::NUMBER;
    value.valueNum = 0;
    return true;
}

bool DetectParentRulesCheckNode::GetPropActionNames(Accessibility::PropValue& value)
{
    value.valueType = Accessibility::ValueType::ARRAY;

    auto supportAceActions = elementInfo_.GetActionList();
    for (auto& action: supportAceActions) {
        auto findResult = AccessibilityFocusStrategy::actionToFocusActionName.find(
            static_cast<OHOS::Accessibility::ActionType>(action.GetActionType()));
        if (findResult != AccessibilityFocusStrategy::actionToFocusActionName.end()) {
            value.valueArray.insert(findResult->second);
        }
    }
    return true;
}

std::vector<std::shared_ptr<FocusRulesCheckNode>> DetectParentRulesCheckNode::GetAceChildren()
{
    std::vector<std::shared_ptr<FocusRulesCheckNode>> checkNodeChildren;
    return checkNodeChildren;
}

std::vector<std::shared_ptr<Accessibility::ReadableRulesNode>> DetectParentRulesCheckNode::GetChildren()
{
    std::vector<std::shared_ptr<Accessibility::ReadableRulesNode>> checkNodeChildren;
    auto extraElementInfo = elementInfo_.GetExtraElement();
    auto extraElementInfoValue = extraElementInfo.GetExtraElementInfoValueStr();
    auto hasChildTextStr = extraElementInfoValue.find("childText");
    CHECK_EQUAL_RETURN(hasChildTextStr, extraElementInfoValue.end(), checkNodeChildren);
    checkNodeChildren.push_back(std::make_shared<DetectParentMockChildNode>(-1));
    return checkNodeChildren;
}

std::shared_ptr<FocusRulesCheckNode> DetectParentRulesCheckNode::GetAceParent()
{
    auto customizedParentNode = customizedParentNode_.Upgrade();
    CHECK_NULL_RETURN(customizedParentNode, nullptr);
    auto checkNode =
        std::make_shared<FrameNodeRulesCheckNode>(customizedParentNode, customizedParentNode->GetAccessibilityId());
    return checkNode;
}

std::shared_ptr<Accessibility::ReadableRulesNode> DetectParentRulesCheckNode::GetParent()
{
    return GetAceParent();
}

bool DetectParentMockChildNode::GetPropText(Accessibility::PropValue& value)
{
    value.valueType = Accessibility::ValueType::STRING;
    value.valueStr = "mockText";
    return true;
}

bool DetectParentMockChildNode::GetPropHintText(Accessibility::PropValue& value)
{
    value.valueType = Accessibility::ValueType::STRING;
    value.valueStr = "";
    return true;
}

bool DetectParentMockChildNode::GetPropDesc(Accessibility::PropValue& value)
{
    value.valueType = Accessibility::ValueType::STRING;
    value.valueStr = "";
    return true;
}

bool DetectParentMockChildNode::GetPropAccessibilityText(Accessibility::PropValue& value)
{
    value.valueType = Accessibility::ValueType::STRING;
    value.valueStr = "";
    return true;
}

bool DetectParentMockChildNode::GetPropType(Accessibility::PropValue& value)
{
    value.valueType = Accessibility::ValueType::STRING;
    value.valueStr = "";
    return true;
}

bool DetectParentMockChildNode::GetPropAccessibilityLevel(Accessibility::PropValue& value)
{
    value.valueType = Accessibility::ValueType::STRING;
    value.valueStr = NG::AccessibilityProperty::Level::AUTO;
    return true;
}

bool DetectParentMockChildNode::GetPropAccessibilityGroup(Accessibility::PropValue& value)
{
    value.valueType = Accessibility::ValueType::BOOL;
    value.valueBool = false;
    return true;
}

bool DetectParentMockChildNode::GetPropIsEnable(Accessibility::PropValue& value)
{
    value.valueType = Accessibility::ValueType::BOOL;
    value.valueBool = true;
    return true;
}

bool DetectParentMockChildNode::GetPropChildrenCount(Accessibility::PropValue& value)
{
    value.valueType = Accessibility::ValueType::NUMBER;
    value.valueNum = 0;
    return true;
}

bool DetectParentMockChildNode::GetPropActionNames(Accessibility::PropValue& value)
{
    value.valueType = Accessibility::ValueType::ARRAY;
    value.valueArray.clear();
    return true;
}

std::vector<std::shared_ptr<FocusRulesCheckNode>> DetectParentMockChildNode::GetAceChildren()
{
    std::vector<std::shared_ptr<FocusRulesCheckNode>> checkNodeChildren;
    return checkNodeChildren;
}

std::vector<std::shared_ptr<Accessibility::ReadableRulesNode>> DetectParentMockChildNode::GetChildren()
{
    std::vector<std::shared_ptr<Accessibility::ReadableRulesNode>> checkNodeChildren;
    return checkNodeChildren;
}

std::shared_ptr<FocusRulesCheckNode> DetectParentMockChildNode::GetAceParent()
{
    return nullptr;
}

std::shared_ptr<Accessibility::ReadableRulesNode> DetectParentMockChildNode::GetParent()
{
    return nullptr;
}
} // OHOS::Ace::Framework
