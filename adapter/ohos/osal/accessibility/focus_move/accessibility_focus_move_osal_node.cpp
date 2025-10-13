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
#include "adapter/ohos/osal/accessibility/focus_move/accessibility_focus_move_osal_node.h"
#include "adapter/ohos/osal/js_accessibility_manager.h"
#include "adapter/ohos/osal/accessibility/focus_move/accessibility_focus_accessibility_node_utils.h"

using namespace OHOS::Accessibility;
using namespace OHOS::AccessibilityConfig;

namespace OHOS::Ace::Framework {

void FocusStrategyOsalNode::InvailidElementInfo(Accessibility::AccessibilityElementInfo& info)
{
    info.SetValidElement(false);
}

bool FocusStrategyOsalNode::UpdateOriginNodeInfo(int64_t elementId)
{
    auto jsAccessibilityManager = jsAccessibilityManager_.Upgrade();
    CHECK_NULL_RETURN(jsAccessibilityManager, false);
    auto node = jsAccessibilityManager->GetAccessibilityNodeFromPage(elementId);
    CHECK_NULL_RETURN(node, false);
    node_ = node;
    return true;
}

std::shared_ptr<FocusRulesCheckNode> FocusStrategyOsalNode::GetCurrentCheckNode()
{
    auto node = node_.Upgrade();
    CHECK_NULL_RETURN(node, nullptr);
    return std::make_shared<AccessibilityNodeRulesCheckNode>(
        node, static_cast<int64_t>(node->GetNodeId()));
}

void FocusStrategyOsalNode::UpdateNextFocus(std::shared_ptr<FocusRulesCheckNode>& checkNode)
{
}

std::shared_ptr<FocusRulesCheckNode> FocusStrategyOsalNode::ChangeToRoot()
{
    return nullptr;
}

bool FocusStrategyOsalNode::ChangeToEmbed(
    const std::shared_ptr<FocusRulesCheckNode>& resultNode, Accessibility::AccessibilityElementInfo& info)
{
    return false;
}

bool FocusStrategyOsalNode::UpdateElementInfo(
    const std::shared_ptr<FocusRulesCheckNode>& resultNode, Accessibility::AccessibilityElementInfo& info)
{
    CHECK_NULL_RETURN(resultNode, false);
    auto checkTarget = std::static_pointer_cast<AccessibilityNodeRulesCheckNode>(resultNode);
    CHECK_NULL_RETURN(checkTarget, false);
    auto finalNode = checkTarget->GetAccessibilityNode();
    CHECK_NULL_RETURN(finalNode, false);
    auto jsAccessibilityManager = jsAccessibilityManager_.Upgrade();
    CHECK_NULL_RETURN(jsAccessibilityManager, false);
    jsAccessibilityManager->UpdateAccessibilityNodeInfo(
        finalNode, info, jsAccessibilityManager, jsAccessibilityManager->GetWindowId());
    return true;
}
} // OHOS::Ace::Framework
