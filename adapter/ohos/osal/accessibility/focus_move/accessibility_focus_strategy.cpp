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
#include "accessibility_focus_strategy.h"
#include "accessibility_config.h"
#include "accessibility_element_operator.h"
#include "frameworks/core/accessibility/accessibility_manager.h"

namespace OHOS::Ace::Framework {

namespace {
std::shared_ptr<FocusRulesCheckNode> GetLastChildNode(
    const std::shared_ptr<FocusRulesCheckNode>& currentNode)
{
    std::vector<std::shared_ptr<FocusRulesCheckNode>> children { currentNode };
    std::shared_ptr<FocusRulesCheckNode> checkNode;
    while (!children.empty()) {
        checkNode = children.back();
        children.clear();
        if (checkNode && checkNode->IsChildTreeContainer()) {
            break;
        }
        children = checkNode->GetAceChildren();
    }
    return checkNode;
}

bool IsSupportScroll(
    const std::shared_ptr<FocusRulesCheckNode>& currentNode, const std::string& scrollActionName)
{
    CHECK_NULL_RETURN(currentNode, false);
    Accessibility::PropValueStub value;
    if (!currentNode->GetPropActionNames(value)) {
        return false;
    }

    auto findResult = value.valueArray.find(scrollActionName);
    if (findResult == value.valueArray.end()) {
        return false;
    }
#ifdef SUPPORT_ACCESSIBILITY_FOCUS_MOVE
    bool isHit = false;
    auto client = Accessibility::AccessibilitySystemAbilityClient::GetInstance();
    CHECK_NULL_RETURN(client, false);
    auto checkResult = client->CheckNodeIsSpecificType(
        currentNode, Accessibility::ReadbleSpecificType::IGNORE_SCROLL_TYPE, isHit);
    CHECK_NE_RETURN(checkResult, Accessibility::RET_OK, false);
    return !isHit;
#else
    return true;
#endif
}

AceFocusMoveResult FindScrollAncestor(
    AceFocusMoveDetailCondition condition,
    const std::shared_ptr<FocusRulesCheckNode>& currentNode,
    std::list<std::shared_ptr<FocusRulesCheckNode>>& targetNodes,
    std::string scrollActionName)
{
    CHECK_NULL_RETURN(currentNode, AceFocusMoveResult::FIND_FAIL);
    auto parent = currentNode->GetAceParent();
    while (parent) {
        if (parent->IsAccessibiltyVisible()) {
            if (IsSupportScroll(parent, scrollActionName)) {
                targetNodes.emplace_back(parent);
            }
        }
        parent = parent->GetAceParent();
    }
    return AceFocusMoveResult::FIND_SUCCESS;
}
} // namespace

const std::map<AceAction, std::string> AccessibilityFocusStrategy::aceActionToFocusActionName = {
    { AceAction::ACTION_CLICK, "click" },
    { AceAction::ACTION_LONG_CLICK, "longClick" },
    { AceAction::ACTION_SCROLL_FORWARD, "scrollForward" },
    { AceAction::ACTION_SCROLL_BACKWARD, "scrollBackward" },
    { AceAction::ACTION_FOCUS, "focus" },
    { AceAction::ACTION_CLEAR_FOCUS, "clearFocus" },
    { AceAction::ACTION_ACCESSIBILITY_FOCUS, "accessibilityFocus" },
    { AceAction::ACTION_CLEAR_ACCESSIBILITY_FOCUS, "clearAccessibilityFocus" },
    { AceAction::ACTION_SET_TEXT, "setText" },
    { AceAction::ACTION_COPY, "copy" },
    { AceAction::ACTION_PASTE, "paste" },
    { AceAction::ACTION_CUT, "cut" },
    { AceAction::ACTION_SELECT, "select" },
    { AceAction::ACTION_SET_SELECTION, "setSelection" },
    { AceAction::ACTION_CLEAR_SELECTION, "clearSelection" },
    { AceAction::ACTION_SET_CURSOR_POSITION, "setCursorPosition" },
    { AceAction::ACTION_EXEC_SUB_COMPONENT, "spanClick" },
    { AceAction::ACTION_NEXT_HTML_ITEM, "nextHtmlItem" },
    { AceAction::ACTION_PREVIOUS_HTML_ITEM, "previoustHtmlItem" },
};

const std::map<OHOS::Accessibility::ActionType, std::string> AccessibilityFocusStrategy::actionToFocusActionName = {
    { OHOS::Accessibility::ActionType::ACCESSIBILITY_ACTION_CLICK, "click" },
    { OHOS::Accessibility::ActionType::ACCESSIBILITY_ACTION_LONG_CLICK, "longClick" },
    { OHOS::Accessibility::ActionType::ACCESSIBILITY_ACTION_SCROLL_FORWARD, "scrollForward" },
    { OHOS::Accessibility::ActionType::ACCESSIBILITY_ACTION_SCROLL_BACKWARD, "scrollBackward" },
    { OHOS::Accessibility::ActionType::ACCESSIBILITY_ACTION_FOCUS, "focus" },
    { OHOS::Accessibility::ActionType::ACCESSIBILITY_ACTION_CLEAR_FOCUS, "clearFocus" },
    { OHOS::Accessibility::ActionType::ACCESSIBILITY_ACTION_ACCESSIBILITY_FOCUS, "accessibilityFocus" },
    { OHOS::Accessibility::ActionType::ACCESSIBILITY_ACTION_CLEAR_ACCESSIBILITY_FOCUS, "clearAccessibilityFocus" },
    { OHOS::Accessibility::ActionType::ACCESSIBILITY_ACTION_SET_TEXT, "setText" },
    { OHOS::Accessibility::ActionType::ACCESSIBILITY_ACTION_COPY, "copy" },
    { OHOS::Accessibility::ActionType::ACCESSIBILITY_ACTION_PASTE, "paste" },
    { OHOS::Accessibility::ActionType::ACCESSIBILITY_ACTION_CUT, "cut" },
    { OHOS::Accessibility::ActionType::ACCESSIBILITY_ACTION_SELECT, "select" },
    { OHOS::Accessibility::ActionType::ACCESSIBILITY_ACTION_SET_SELECTION, "setSelection" },
    { OHOS::Accessibility::ActionType::ACCESSIBILITY_ACTION_CLEAR_SELECTION, "clearSelection" },
    { OHOS::Accessibility::ActionType::ACCESSIBILITY_ACTION_SET_CURSOR_POSITION, "setCursorPosition" },
    { OHOS::Accessibility::ActionType::ACCESSIBILITY_ACTION_SPAN_CLICK, "spanClick" },
    { OHOS::Accessibility::ActionType::ACCESSIBILITY_ACTION_NEXT_HTML_ITEM, "nextHtmlItem" },
    { OHOS::Accessibility::ActionType::ACCESSIBILITY_ACTION_PREVIOUS_HTML_ITEM, "previoustHtmlItem" },
};

bool AccessibilityFocusStrategy::CanAccessibilityFocus(const std::shared_ptr<FocusRulesCheckNode>& currentNode)
{
    CHECK_NULL_RETURN(currentNode, false);
    if (!currentNode->IsAccessibiltyVisible()) {
        return false;
    }
#ifdef SUPPORT_ACCESSIBILITY_FOCUS_MOVE
    bool isReadable = false;
    auto client = Accessibility::AccessibilitySystemAbilityClient::GetInstance();
    CHECK_NULL_RETURN(client, false);
    auto checkResult = client->CheckNodeIsReadable(currentNode, isReadable);
    CHECK_NE_RETURN(checkResult, Accessibility::RET_OK, false);
    return isReadable;
#else
    return false;
#endif
}

std::shared_ptr<FocusRulesCheckNode> AccessibilityFocusStrategy::GetParentNodeStopByRootType(
    const std::shared_ptr<FocusRulesCheckNode>& currentNode)
{
    CHECK_NULL_RETURN(currentNode, nullptr);
#ifdef SUPPORT_ACCESSIBILITY_FOCUS_MOVE
    bool isHit = false;
    auto client = Accessibility::AccessibilitySystemAbilityClient::GetInstance();
    CHECK_NULL_RETURN(client, nullptr);
    auto checkResult = client->CheckNodeIsSpecificType(
        currentNode, Accessibility::ReadbleSpecificType::ROOT_TYPE, isHit);
    CHECK_NE_RETURN(checkResult, Accessibility::RET_OK, nullptr);
    CHECK_EQUAL_RETURN(isHit, true, nullptr);
#endif
    auto parent = currentNode->GetAceParent();
    return parent;
}

AceFocusMoveResult AccessibilityFocusStrategy::FindNextReadableNodeBySelfAndSameLevel(
    AceFocusMoveDetailCondition condition,
    const std::shared_ptr<FocusRulesCheckNode>& currentNode,
    const std::vector<std::shared_ptr<FocusRulesCheckNode>>& samenLevelNodes,
    std::shared_ptr<FocusRulesCheckNode>& targetNode)
{
    return AceFocusMoveResult::FIND_FAIL;
}

AceFocusMoveResult AccessibilityFocusStrategy::FindNextReadableNode(
    AceFocusMoveDetailCondition condition,
    const std::shared_ptr<FocusRulesCheckNode>& currentNode,
    std::shared_ptr<FocusRulesCheckNode>& targetNode)
{
    return AceFocusMoveResult::FIND_FAIL;
}

AceFocusMoveResult FindPrevReadableNodeByChildAndSelf(
    const std::shared_ptr<FocusRulesCheckNode>& currentNode,
    std::shared_ptr<FocusRulesCheckNode>& targetNode)
{
    return AceFocusMoveResult::FIND_FAIL;
}

AceFocusMoveResult AccessibilityFocusStrategy::FindPrevReadableNode(
    AceFocusMoveDetailCondition condition,
    const std::shared_ptr<FocusRulesCheckNode>& currentNode,
    std::shared_ptr<FocusRulesCheckNode>& targetNode)
{
    return AceFocusMoveResult::FIND_FAIL;
}

AceFocusMoveResult AccessibilityFocusStrategy::FindLastNodeWithoutCheck(
    AceFocusMoveDetailCondition condition,
    const std::shared_ptr<FocusRulesCheckNode>& currentNode,
    std::shared_ptr<FocusRulesCheckNode>& targetNode)
{
    CHECK_NULL_RETURN(currentNode, AceFocusMoveResult::FIND_FAIL);
    targetNode = GetLastChildNode(currentNode);
    CHECK_NULL_RETURN(targetNode, AceFocusMoveResult::FIND_FAIL);

    if (targetNode->IsChildTreeContainer()) {
        HILOG_INFO_FOCUS("get childTreeContainer when get last");
        return AceFocusMoveResult::FIND_CHILDTREE;
    }
    return AceFocusMoveResult::FIND_SUCCESS;
}

AceFocusMoveResult AccessibilityFocusStrategy::FindForwardScrollAncestor(
    AceFocusMoveDetailCondition condition,
    const std::shared_ptr<FocusRulesCheckNode>& currentNode,
    std::list<std::shared_ptr<FocusRulesCheckNode>>& targetNodes)
{
    return FindScrollAncestor(condition, currentNode, targetNodes, "scrollForward");
}

AceFocusMoveResult AccessibilityFocusStrategy::FindBackwardScrollAncestor(
    AceFocusMoveDetailCondition condition,
    const std::shared_ptr<FocusRulesCheckNode>& currentNode,
    std::list<std::shared_ptr<FocusRulesCheckNode>>& targetNodes)
{
    return FindScrollAncestor(condition, currentNode, targetNodes, "scrollBackward");
}
} // OHOS::Ace::Framework
