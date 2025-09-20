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

bool FrameNodeRulesCheckNode::GetPropText(Accessibility::PropValueStub& value)
{
    auto node = weakNode_.Upgrade();
    CHECK_NULL_RETURN(node, false);
    auto accessibilityProperty = node->GetAccessibilityProperty<NG::AccessibilityProperty>();
    CHECK_NULL_RETURN(accessibilityProperty, false);
    value.valueType = Accessibility::ValueTypeStub::STRING;
    value.valueStr = NG::AccessibilityPropertyUtils::GetContent(accessibilityProperty);
    return true;
}

bool FrameNodeRulesCheckNode::GetPropHintText(Accessibility::PropValueStub& value)
{
    auto node = weakNode_.Upgrade();
    CHECK_NULL_RETURN(node, false);
    auto accessibilityProperty = node->GetAccessibilityProperty<NG::AccessibilityProperty>();
    CHECK_NULL_RETURN(accessibilityProperty, false);
    value.valueType = Accessibility::ValueTypeStub::STRING;
    value.valueStr = accessibilityProperty->GetHintText();
    return true;
}

bool FrameNodeRulesCheckNode::GetPropDesc(Accessibility::PropValueStub& value)
{
    auto node = weakNode_.Upgrade();
    CHECK_NULL_RETURN(node, false);
    auto accessibilityProperty = node->GetAccessibilityProperty<NG::AccessibilityProperty>();
    CHECK_NULL_RETURN(accessibilityProperty, false);
    value.valueType = Accessibility::ValueTypeStub::STRING;
    value.valueStr = accessibilityProperty->GetAccessibilityDescription();
    return true;
}

bool FrameNodeRulesCheckNode::GetPropAccessibilityText(Accessibility::PropValueStub& value)
{
    auto node = weakNode_.Upgrade();
    CHECK_NULL_RETURN(node, false);
    auto accessibilityProperty = node->GetAccessibilityProperty<NG::AccessibilityProperty>();
    CHECK_NULL_RETURN(accessibilityProperty, false);
    value.valueType = Accessibility::ValueTypeStub::STRING;
    value.valueStr = NG::AccessibilityPropertyUtils::GetAccessibilityText(accessibilityProperty);
    return true;
}

bool FrameNodeRulesCheckNode::GetPropType(Accessibility::PropValueStub& value)
{
    auto node = weakNode_.Upgrade();
    CHECK_NULL_RETURN(node, false);
    auto accessibilityProperty = node->GetAccessibilityProperty<NG::AccessibilityProperty>();
    CHECK_NULL_RETURN(accessibilityProperty, false);
    value.valueType = Accessibility::ValueTypeStub::STRING;
    value.valueStr = NG::AccessibilityPropertyUtils::GetComponentType(node, accessibilityProperty);
    return true;
}

bool FrameNodeRulesCheckNode::GetPropAccessibilityLevel(Accessibility::PropValueStub& value)
{
    auto node = weakNode_.Upgrade();
    CHECK_NULL_RETURN(node, false);
    auto accessibilityProperty = node->GetAccessibilityProperty<NG::AccessibilityProperty>();
    CHECK_NULL_RETURN(accessibilityProperty, false);
    value.valueType = Accessibility::ValueTypeStub::STRING;
    value.valueStr = accessibilityProperty->GetAccessibilityLevel();
    return true;
}

bool FrameNodeRulesCheckNode::GetPropAccessibilityGroup(Accessibility::PropValueStub& value)
{
    auto node = weakNode_.Upgrade();
    CHECK_NULL_RETURN(node, false);
    auto accessibilityProperty = node->GetAccessibilityProperty<NG::AccessibilityProperty>();
    CHECK_NULL_RETURN(accessibilityProperty, false);
    value.valueType = Accessibility::ValueTypeStub::BOOL;
    value.valueBool = accessibilityProperty->IsAccessibilityGroup();
    return true;
}

bool FrameNodeRulesCheckNode::GetPropIsEnable(Accessibility::PropValueStub& value)
{
    auto node = weakNode_.Upgrade();
    CHECK_NULL_RETURN(node, false);
    auto accessibilityProperty = node->GetAccessibilityProperty<NG::AccessibilityProperty>();
    CHECK_NULL_RETURN(accessibilityProperty, false);
    value.valueType = Accessibility::ValueTypeStub::BOOL;
    value.valueBool = !accessibilityProperty->IsUserDisabled();
    return true;
}

bool FrameNodeRulesCheckNode::GetPropChildrenCount(Accessibility::PropValueStub& value)
{
    value.valueType = Accessibility::ValueTypeStub::NUMBER;
    auto children = GetChildren();
    value.valueNum = children.size();
    return true;
}

bool FrameNodeRulesCheckNode::GetPropActionNames(Accessibility::PropValueStub& value)
{
    value.valueType = Accessibility::ValueTypeStub::ARRAY;
    auto node = weakNode_.Upgrade();
    CHECK_NULL_RETURN(node, false);
    auto accessibilityProperty = node->GetAccessibilityProperty<NG::AccessibilityProperty>();
    CHECK_NULL_RETURN(accessibilityProperty, false);

    std::string accessibilityFocusStr =
        accessibilityProperty->GetAccessibilityFocusState() ? "clearAccessibilityFocus" : "accessibilityFocus";
    value.valueArray.insert(accessibilityFocusStr);

    CHECK_EQUAL_RETURN(accessibilityProperty->IsUserDisabled(), true, false);
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

std::vector<std::shared_ptr<Accessibility::ReadableRulesNodeStub>> FrameNodeRulesCheckNode::GetChildren()
{
    return GetChildrenTemplate<Accessibility::ReadableRulesNodeStub>();
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

std::shared_ptr<Accessibility::ReadableRulesNodeStub> FrameNodeRulesCheckNode::GetParent()
{
    return GetAceParent();
}

bool FrameNodeRulesCheckNode::IsModalForPopup()
{
#ifdef SUPPORT_ACCESSIBILITY_FOCUS_MOVE
    auto node = weakNode_.Upgrade();
    CHECK_NULL_RETURN(node, false);
    auto accessibilityProperty = node->GetAccessibilityProperty<NG::AccessibilityProperty>();
    CHECK_NULL_RETURN(accessibilityProperty, false);
    return accessibilityProperty->GetAccessibilityIsModal();
#else
    return true;
#endif
}

std::shared_ptr<Accessibility::ReadableRulesNodeStub> FrameNodeRulesCheckNode::GetUserNextFocusNode()
{
    auto nextNode = nextNode_.Upgrade();
    CHECK_NULL_RETURN(nextNode, nullptr);
    return std::make_shared<FrameNodeRulesCheckNode>(nextNode, nextNode->GetAccessibilityId(), handleParam_);
}

std::shared_ptr<Accessibility::ReadableRulesNodeStub> FrameNodeRulesCheckNode::GetUserPrevFocusNode()
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
} // OHOS::Ace::Framework
