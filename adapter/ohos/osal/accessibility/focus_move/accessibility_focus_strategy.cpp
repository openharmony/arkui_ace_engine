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
#include "frameworks/core/components_ng/property/accessibility_property.h"

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
    const std::shared_ptr<FocusRulesCheckNode>& currentNode, const std::list<std::string>& scrollActionNames)
{
    CHECK_NULL_RETURN(currentNode, false);
    Accessibility::PropValue value;
    if (!currentNode->GetPropActionNames(value)) {
        return false;
    }
    bool find = false;
    for (auto& scrollActionName : scrollActionNames) {
        auto findResult = value.valueArray.find(scrollActionName);
        if (findResult == value.valueArray.end()) {
            continue;
        }
        find = true;
        break;
    }
    CHECK_EQUAL_RETURN(find, false, false);
#if !defined(ACE_UNITTEST)
    bool isHit = false;
    auto client = Accessibility::AccessibilitySystemAbilityClient::GetInstance();
    CHECK_NULL_RETURN(client, false);
    auto checkResult = client->CheckNodeIsSpecificType(
        currentNode, Accessibility::ReadableSpecificType::IGNORE_SCROLL_TYPE, isHit);
    CHECK_NE_RETURN(checkResult, Accessibility::RET_OK, false);
    return !isHit;
#else
    return true;
#endif
}

bool IsSupportScrollForward(const std::shared_ptr<FocusRulesCheckNode>& currentNode)
{
    std::list<std::string> scrollActionNames;
    scrollActionNames.emplace_back("scrollForward");
    return IsSupportScroll(currentNode, scrollActionNames);
}

bool IsSupportScrollBackward(const std::shared_ptr<FocusRulesCheckNode>& currentNode)
{
    std::list<std::string> scrollActionNames;
    scrollActionNames.emplace_back("scrollBackward");
    return IsSupportScroll(currentNode, scrollActionNames);
}

bool IsSupportScrollForwardAndBackward(const std::shared_ptr<FocusRulesCheckNode>& currentNode)
{
    std::list<std::string> scrollActionNames;
    scrollActionNames.emplace_back("scrollForward");
    scrollActionNames.emplace_back("scrollBackward");
    return IsSupportScroll(currentNode, scrollActionNames);
}

const std::map<CheckSupportScrollAction,
    std::function<bool(const std::shared_ptr<FocusRulesCheckNode>& currentNode)>> supportScrollActionFuncs = {
    { CheckSupportScrollAction::FIND_FORWARD, IsSupportScrollForward },
    { CheckSupportScrollAction::FIND_BACKWARD, IsSupportScrollBackward },
    { CheckSupportScrollAction::FIND_ANY, IsSupportScrollForwardAndBackward },
};

bool CheckIsLevelHideDescendants(const std::shared_ptr<FocusRulesCheckNode>& currentNode)
{
    CHECK_NULL_RETURN(currentNode, false);
    Accessibility::PropValue value;
    auto result = currentNode->GetPropAccessibilityLevel(value);
    CHECK_EQUAL_RETURN(result, false, false);
    return value.valueStr == NG::AccessibilityProperty::Level::NO_HIDE_DESCENDANTS;
}

bool NoNeedSearchChild(const std::shared_ptr<FocusRulesCheckNode>& currentNode)
{
    CHECK_NULL_RETURN(currentNode, true);
    // level is HideDescendants means no need search child
    return CheckIsLevelHideDescendants(currentNode) || !currentNode->IsAccessibiltyVisible();
}

bool CheckNodeAvailable(const std::shared_ptr<FocusRulesCheckNode>& currentNode)
{
    CHECK_NULL_RETURN(currentNode, false);
    bool isAvailable = false;
    auto client = Accessibility::AccessibilitySystemAbilityClient::GetInstance();
    CHECK_NULL_RETURN(client, false);
    auto checkResult = client->CheckNodeIsSpecificType(
        currentNode, Accessibility::ReadableSpecificType::AVAILABLE_TYPE, isAvailable);
    CHECK_NE_RETURN(checkResult, Accessibility::RET_OK, false);
    return isAvailable;
}
} // namespace

bool AccessibilityFocusStrategy::IsForceSupportScrollType(
    const std::shared_ptr<FocusRulesCheckNode>& currentNode)
{
    CHECK_NULL_RETURN(currentNode, false);
    bool isHit = false;
    auto client = Accessibility::AccessibilitySystemAbilityClient::GetInstance();
    CHECK_NULL_RETURN(client, false);
    auto checkResult = client->CheckNodeIsSpecificType(
        currentNode, Accessibility::ReadableSpecificType::SCROLLABLE_TYPE, isHit);
    CHECK_NE_RETURN(checkResult, Accessibility::RET_OK, false);
    return isHit;
}

AceFocusMoveResult AccessibilityFocusStrategy::FindScrollAncestor(
    AceFocusMoveDetailCondition condition,
    const std::shared_ptr<FocusRulesCheckNode>& currentNode,
    std::list<std::shared_ptr<FocusRulesCheckNode>>& targetNodes,
    CheckSupportScrollAction checkAction,
    bool checkType)
{
    CHECK_NULL_RETURN(currentNode, AceFocusMoveResult::FIND_FAIL);
    auto supportScrollActionFunc = supportScrollActionFuncs.find(checkAction);
    CHECK_EQUAL_RETURN(supportScrollActionFunc, supportScrollActionFuncs.end(), AceFocusMoveResult::FIND_FAIL);
    auto parent = currentNode->GetAceParent();
    while (parent) {
        if (parent->IsAccessibiltyVisible()) {
            if (supportScrollActionFunc->second(parent)) {
                targetNodes.emplace_back(parent);
            } else if (checkType && IsForceSupportScrollType(parent)) {
                targetNodes.emplace_back(parent);
            }
        }
        parent = parent->GetAceParent();
    }
    return AceFocusMoveResult::FIND_SUCCESS;
}

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

std::string AccessibilityFocusStrategy::GetChildrenIdsStr(
    const std::vector<std::shared_ptr<FocusRulesCheckNode>>& children)
{
    std::string printStr;
    printStr.append("size ").append(std::to_string(children.size())).append(": ");
    for (const auto& node : children) {
        CHECK_NULL_CONTINUE(node);
        printStr.append(std::to_string(node->GetAccessibilityId())).append(" ");
    }
    return printStr;
}

bool AccessibilityFocusStrategy::CanAccessibilityFocus(const std::shared_ptr<FocusRulesCheckNode>& currentNode)
{
    CHECK_NULL_RETURN(currentNode, false);
    if (!currentNode->IsAccessibiltyVisible()) {
        return false;
    }
    bool isReadable = false;
    auto client = Accessibility::AccessibilitySystemAbilityClient::GetInstance();
    CHECK_NULL_RETURN(client, false);
    auto checkResult = client->CheckNodeIsReadable(currentNode, isReadable);
    CHECK_NE_RETURN(checkResult, Accessibility::RET_OK, false);
    return isReadable;
}

std::shared_ptr<FocusRulesCheckNode> AccessibilityFocusStrategy::GetParentNodeStopByRootType(
    const std::shared_ptr<FocusRulesCheckNode>& currentNode, bool& hitRootType)
{
    hitRootType = false;
    CHECK_NULL_RETURN(currentNode, nullptr);
    bool isHit = false;
    auto client = Accessibility::AccessibilitySystemAbilityClient::GetInstance();
    CHECK_NULL_RETURN(client, nullptr);
    auto checkResult = client->CheckNodeIsSpecificType(
        currentNode, Accessibility::ReadableSpecificType::ROOT_TYPE, isHit);
    CHECK_NE_RETURN(checkResult, Accessibility::RET_OK, nullptr);
    hitRootType = isHit;
    CHECK_EQUAL_RETURN(isHit, true, nullptr);
    auto parent = currentNode->GetAceParent();
    return parent;
}

AceFocusMoveResult AccessibilityFocusStrategy::FindNextReadableNodeBySelfAndSameLevel(
    AceFocusMoveDetailCondition condition,
    const std::shared_ptr<FocusRulesCheckNode>& currentNode,
    const std::vector<std::shared_ptr<FocusRulesCheckNode>>& sameLevelNodes,
    std::shared_ptr<FocusRulesCheckNode>& targetNode)
{
    CHECK_NULL_RETURN(currentNode, AceFocusMoveResult::FIND_FAIL);
    // 1. check self's focusable when not bypass self
    if (!condition.bypassSelf && CanAccessibilityFocus(currentNode)) {
        targetNode = currentNode;
        HILOG_INFO_FOCUS("== result: check self Id %{public}" PRId64 " focusable", currentNode->GetAccessibilityId());
        return AceFocusMoveResult::FIND_SUCCESS;
    }

    HILOG_INFO_FOCUS("== check Id %{public}" PRId64 " not focusable or bypass %{public}d",
        currentNode->GetAccessibilityId(), condition.bypassSelf);
    // 1.1 hit childtree container and return it only when bypassDescendants not set
    if (currentNode->IsChildTreeContainer() && !condition.bypassDescendants) {
        targetNode = currentNode; // need to continue operation to search in childtree container
        return AceFocusMoveResult::FIND_CHILDTREE;
    }

    std::vector<std::shared_ptr<FocusRulesCheckNode>> children = currentNode->GetAceChildren();
    HILOG_INFO_FOCUS("== %{public}" PRId64 " not focusable or bypass %{public}d",
        currentNode->GetAccessibilityId(), condition.bypassSelf);
    HILOG_INFO_FOCUS("input node childs %{public}s", GetChildrenIdsStr(children).c_str());
    // 2. need firstly search children of currentNode when currentNode is visible and bypassDescendants not set
    if (!condition.bypassDescendants && !children.empty() && !NoNeedSearchChild(currentNode)) {
        AceFocusMoveDetailCondition nextLevelCondition = {.bypassSelf = false, .bypassDescendants = false};
        auto result = FindNextReadableNodeBySelfAndSameLevel(nextLevelCondition,
            children.front(), children, targetNode);
        CHECK_NE_RETURN(result, AceFocusMoveResult::FIND_FAIL, result);
    } else {
        HILOG_INFO_FOCUS("result: %{public}" PRId64
            " SearchSelfAndSameLevel not search child by mode %{public}d or child size %{public}zu",
            currentNode->GetAccessibilityId(), condition.bypassDescendants, children.size());
    }

    HILOG_INFO_FOCUS("== %{public}" PRId64 " start search same level brother", currentNode->GetAccessibilityId());
    HILOG_INFO_FOCUS("same level brothers %{public}s", GetChildrenIdsStr(sameLevelNodes).c_str());
    // 3. need search right subtree at the same level when currenNode and it's descendants are unfocusable
    auto brotherIt = std::find_if(sameLevelNodes.begin(), sameLevelNodes.end(),
        [accessibilityId = currentNode->GetAccessibilityId()](const std::shared_ptr<FocusRulesCheckNode>& node) {
            return node->GetAccessibilityId() == accessibilityId;
        });
    if (brotherIt != sameLevelNodes.end()) {
        if ((++brotherIt) != sameLevelNodes.end()) {
            CHECK_NULL_RETURN(*brotherIt, AceFocusMoveResult::FIND_FAIL);
            HILOG_INFO_FOCUS("=== search same level brother %{public}" PRId64, (*brotherIt)->GetAccessibilityId());
            AceFocusMoveDetailCondition sameLevelCondition = {.bypassSelf = false, .bypassDescendants = false};
            auto result = FindNextReadableNodeBySelfAndSameLevel(sameLevelCondition,
                *brotherIt, sameLevelNodes, targetNode);
            CHECK_NE_RETURN(result, AceFocusMoveResult::FIND_FAIL, result);
        } else {
            HILOG_INFO_FOCUS("there is no right node at the same level");
        }
    } else {
        HILOG_INFO_FOCUS("same level cannot find checked ID %{public}" PRId64, currentNode->GetAccessibilityId());
    }
    return AceFocusMoveResult::FIND_FAIL;
}

AceFocusMoveResult AccessibilityFocusStrategy::FindNextReadableNodeToHigherLevel(
    std::shared_ptr<FocusRulesCheckNode>& parent,
    std::shared_ptr<FocusRulesCheckNode>& targetNode)
{
    std::vector<std::shared_ptr<FocusRulesCheckNode>> sameLevelNodes;
    while (parent) {
        // embededTarget can not find higher node
        if (parent->IsEmbededTarget()) {
            HILOG_INFO_FOCUS("result: Input node is Embeded, but self and children cannot find focusable");
            targetNode = parent;
            return AceFocusMoveResult::FIND_EMBED_TARGET;
        }
        // git parent's brother nodes. the parent's children is already checked unfocusable
        bool hitRootType = false;
        auto higherParent = GetParentNodeStopByRootType(parent, hitRootType);
        if (!higherParent) {
            CHECK_EQUAL_RETURN(hitRootType, true, AceFocusMoveResult::FIND_FAIL_IN_ROOT_TYPE);
            break;
        }
        sameLevelNodes = higherParent->GetAceChildren();
        HILOG_INFO_FOCUS("higherParent %{public}" PRId64 " childs %{public}s, already checked %{public}" PRId64,
            higherParent->GetAccessibilityId(), GetChildrenIdsStr(sameLevelNodes).c_str(),
            parent->GetAccessibilityId());
        auto brotherIt = std::find_if(sameLevelNodes.begin(), sameLevelNodes.end(),
            [accessibilityId = parent->GetAccessibilityId()](const std::shared_ptr<FocusRulesCheckNode>& node) {
                return node->GetAccessibilityId() == accessibilityId;
            });
        if (brotherIt != sameLevelNodes.end()) {
            if ((++brotherIt) != sameLevelNodes.end()) {
                CHECK_NULL_RETURN(*brotherIt, AceFocusMoveResult::FIND_FAIL);
                HILOG_INFO_FOCUS("--- search same level brother %{public}" PRId64, (*brotherIt)->GetAccessibilityId());
                AceFocusMoveDetailCondition sameLevelCondition = {.bypassSelf = false, .bypassDescendants = false};
                auto result = FindNextReadableNodeBySelfAndSameLevel(sameLevelCondition,
                    *brotherIt, sameLevelNodes, targetNode);
                CHECK_NE_RETURN(result, AceFocusMoveResult::FIND_FAIL, result);
            } else {
                HILOG_INFO_FOCUS("there is no right node at the same level");
            }
        } else {
            HILOG_INFO_FOCUS("same level cannot find alaread checked ID %{public}" PRId64,
                parent->GetAccessibilityId());
        }
        // need check node whether in scroll container
        if (IsSupportScrollForward(higherParent)) {
            HILOG_INFO_FOCUS("result: search fail in scroll forward container");
            targetNode = higherParent;
            return AceFocusMoveResult::FIND_FAIL_IN_SCROLL;
        }
        parent = higherParent;
    }
    return AceFocusMoveResult::FIND_FAIL;
}

AceFocusMoveResult AccessibilityFocusStrategy::FindNextReadableNode(
    AceFocusMoveDetailCondition condition,
    const std::shared_ptr<FocusRulesCheckNode>& currentNode,
    std::shared_ptr<FocusRulesCheckNode>& targetNode)
{
    CHECK_NULL_RETURN(currentNode, AceFocusMoveResult::FIND_FAIL);
    HILOG_INFO_FOCUS("-- FindNextReadableNode Main Entry Id %{public}" PRId64
        " bypassSelf %{public}d bypassDescentants %{public}d", currentNode->GetAccessibilityId(),
        condition.bypassSelf, condition.bypassDescendants);
    CHECK_EQUAL_RETURN(CheckNodeAvailable(currentNode), false, AceFocusMoveResult::FIND_FAIL_LOST_NODE);
    // no need to check parent in find next proccess due to forward traversal algorithm
    bool hitRootType = false;
    auto parent = GetParentNodeStopByRootType(currentNode, hitRootType);
    std::vector<std::shared_ptr<FocusRulesCheckNode>> sameLevelNodes;
    if (parent) {
        sameLevelNodes = parent->GetAceChildren();
    }

    HILOG_INFO_FOCUS("--- check input id %{public}" PRId64
        "and sameLevel. ParentId %{public}" PRId64, currentNode->GetAccessibilityId(),
        parent? parent->GetAccessibilityId() : -1);
    // detect currentNode, currentNode's children, and samelevel nodes of currentNode
    auto result = FindNextReadableNodeBySelfAndSameLevel(condition, currentNode, sameLevelNodes, targetNode);
    if (result != AceFocusMoveResult::FIND_FAIL) {
        HILOG_INFO_FOCUS("result: get result %{public}d find Id %{public}" PRId64 " by input Id self and sameLevel",
            result, targetNode? targetNode->GetAccessibilityId() : -1);
        return result;
    }
    // embededTarget can not find higher node
    if (currentNode->IsEmbededTarget()) {
        HILOG_INFO_FOCUS("result: Input node is Embeded, but self and children cannot find focusable");
        targetNode = currentNode;
        return AceFocusMoveResult::FIND_EMBED_TARGET;
    }
    // need check node whether in scroll container
    if (IsSupportScrollForward(parent)) {
        HILOG_INFO_FOCUS("result: search fail in scroll forward container");
        targetNode = parent;
        return AceFocusMoveResult::FIND_FAIL_IN_SCROLL;
    }
    HILOG_INFO_FOCUS("--- check input id fail, start find higher level");
    result = FindNextReadableNodeToHigherLevel(parent, targetNode);
    CHECK_NE_RETURN(result, AceFocusMoveResult::FIND_FAIL, result);
    auto isInChildTree = currentNode->IsInChildTree();
    HILOG_INFO_FOCUS("result: handled in ChildTree %{public}d", isInChildTree);
    return isInChildTree ? AceFocusMoveResult::FIND_FAIL_IN_CHILDTREE : AceFocusMoveResult::FIND_FAIL;
}

AceFocusMoveResult AccessibilityFocusStrategy::FindPrevReadableNodeByChildAndSelf(
    const std::shared_ptr<FocusRulesCheckNode>& currentNode,
    std::shared_ptr<FocusRulesCheckNode>& targetNode)
{
    CHECK_NULL_RETURN(currentNode, AceFocusMoveResult::FIND_FAIL);
    // query in the reverse order of pre-order traversal, i.e., right-left-root
    HILOG_INFO_FOCUS("== check id %{public}" PRId64, currentNode->GetAccessibilityId());
    if (!NoNeedSearchChild(currentNode)) {
        std::vector<std::shared_ptr<FocusRulesCheckNode>> children = currentNode->GetAceChildren();
        HILOG_INFO_FOCUS("=== check child firstly %{public}s", GetChildrenIdsStr(children).c_str());
        for (auto childIt = children.rbegin(); childIt != children.rend(); ++ childIt) {
            auto result = FindPrevReadableNodeByChildAndSelf(*childIt, targetNode);
            CHECK_NE_RETURN(result, AceFocusMoveResult::FIND_FAIL, result);
        }
    } else {
        HILOG_INFO_FOCUS("=== not check child");
    }

    HILOG_INFO_FOCUS("=== check self Id %{public}" PRId64, currentNode->GetAccessibilityId());
    // hit childtree container should return
    if (currentNode->IsChildTreeContainer()) {
        targetNode = currentNode;
        HILOG_INFO_FOCUS("result: find ChildTreeContainer");
        return AceFocusMoveResult::FIND_CHILDTREE;
    }
    // check self after check children in processs of finding prev
    if (CanAccessibilityFocus(currentNode)) {
        targetNode = currentNode;
        HILOG_INFO_FOCUS("result: find focusable %{public}" PRId64, currentNode->GetAccessibilityId());
        return AceFocusMoveResult::FIND_SUCCESS;
    }
    return AceFocusMoveResult::FIND_FAIL;
}

AceFocusMoveResult AccessibilityFocusStrategy::CheckParentEarlyStop(
    const std::shared_ptr<FocusRulesCheckNode>& parent,
    std::shared_ptr<FocusRulesCheckNode>& targetNode)
{
    CHECK_NULL_RETURN(parent, AceFocusMoveResult::FIND_SUCCESS);
    if (IsSupportScrollBackward(parent)) {
        HILOG_INFO_FOCUS("result: search fail in scroll backward container"); // check in scroll container
        targetNode = parent;
        return AceFocusMoveResult::FIND_FAIL_IN_SCROLL;
    }
    if (parent->IsChildTreeContainer()) {  // childtree container need to search it's children firstly
        targetNode = parent;
        HILOG_INFO_FOCUS("result: find ChildTreeContainer");
        return AceFocusMoveResult::FIND_CHILDTREE;
    }
    return AceFocusMoveResult::FIND_SUCCESS;
}

AceFocusMoveResult AccessibilityFocusStrategy::FindPrevReadableNodeToHigherLevel(
    const std::shared_ptr<FocusRulesCheckNode>& currentNode,
    std::shared_ptr<FocusRulesCheckNode>& targetNode)
{
    CHECK_NULL_RETURN(currentNode, AceFocusMoveResult::FIND_FAIL);
    std::vector<std::shared_ptr<FocusRulesCheckNode>> sameLevelNodes;
    auto oldCurrent = currentNode;
    bool hitRootType = false;
    auto parent = GetParentNodeStopByRootType(oldCurrent, hitRootType);
    CHECK_EQUAL_RETURN(hitRootType, true, AceFocusMoveResult::FIND_FAIL_IN_ROOT_TYPE);
    while (parent) {
        sameLevelNodes = parent->GetAceChildren();
        HILOG_INFO_FOCUS("--- FindPrev old Id %{public}" PRId64 " start check left brothers. parent %{public}" PRId64
            " samelevelnodes %{public}s",
            oldCurrent->GetAccessibilityId(), parent->GetAccessibilityId(), GetChildrenIdsStr(sameLevelNodes).c_str());
         // 2.1 find oldcurrent's left subtree
        auto currentIt = std::find_if(sameLevelNodes.begin(), sameLevelNodes.end(),
            [accessibilityId = oldCurrent->GetAccessibilityId()](const std::shared_ptr<FocusRulesCheckNode>& node) {
                return node->GetAccessibilityId() == accessibilityId;
            });
        if (currentIt != sameLevelNodes.end()) {
            auto currentRightIt = std::make_reverse_iterator(currentIt);
            for (; currentRightIt != sameLevelNodes.rend(); ++currentRightIt) {
                CHECK_NULL_RETURN(*currentRightIt, AceFocusMoveResult::FIND_FAIL);
                HILOG_INFO_FOCUS("---- check left brother %{public}" PRId64, (*currentRightIt)->GetAccessibilityId());
                auto result = FindPrevReadableNodeByChildAndSelf(*currentRightIt, targetNode);
                CHECK_NE_RETURN(result, AceFocusMoveResult::FIND_FAIL, result);
            }
        }
        // 2.2 the same level is checked， should check parent
        auto checkEarlyStopResult = CheckParentEarlyStop(parent, targetNode);
        CHECK_NE_RETURN(checkEarlyStopResult, AceFocusMoveResult::FIND_SUCCESS, checkEarlyStopResult);
        if (CanAccessibilityFocus(parent)) {
            targetNode = parent;
            HILOG_INFO_FOCUS("result: parent %{public}" PRId64 " is focusable", parent->GetAccessibilityId());
            return AceFocusMoveResult::FIND_SUCCESS;
        }
        // 3. to higher level
        oldCurrent = parent;
        parent = GetParentNodeStopByRootType(oldCurrent, hitRootType);
        CHECK_EQUAL_RETURN(hitRootType, true, AceFocusMoveResult::FIND_FAIL_IN_ROOT_TYPE);
        if (parent && parent->IsEmbededTarget()) {   // embededTarget can not find higher node
            HILOG_INFO_FOCUS("result: find higher Embeded");
            targetNode = parent;
            return AceFocusMoveResult::FIND_EMBED_TARGET;
        }
    }
    return AceFocusMoveResult::FIND_FAIL;
}
AceFocusMoveResult AccessibilityFocusStrategy::FindPrevReadableNode(
    AceFocusMoveDetailCondition condition,
    const std::shared_ptr<FocusRulesCheckNode>& currentNode,
    std::shared_ptr<FocusRulesCheckNode>& targetNode)
{
    CHECK_NULL_RETURN(currentNode, AceFocusMoveResult::FIND_FAIL);
    HILOG_INFO_FOCUS("-- FindPrevReadableNode Main Entry Id %{public}" PRId64
        " bypassSelf %{public}d bypassDescentants %{public}d", currentNode->GetAccessibilityId(),
        condition.bypassSelf, condition.bypassDescendants);
    CHECK_EQUAL_RETURN(CheckNodeAvailable(currentNode), false, AceFocusMoveResult::FIND_FAIL_LOST_NODE);
    // 1 check self when !condition.bypassSelf
    // 1.1 hit childtree container, should firstly check whether need search in childtree.
    if (currentNode->IsChildTreeContainer() && !condition.bypassDescendants && !condition.bypassSelf) {
        targetNode = currentNode;
        return AceFocusMoveResult::FIND_CHILDTREE;
    }
    // 1.2 need to check self when condition is check self
    if (!condition.bypassSelf && CanAccessibilityFocus(currentNode)) {
        targetNode = currentNode;
        HILOG_INFO_FOCUS("result: check self focusable");
        return AceFocusMoveResult::FIND_SUCCESS;
    }
    // 1.3 embededTarget can not find higher node
    if (currentNode->IsEmbededTarget()) {
        HILOG_INFO_FOCUS("result: Input node is Embeded");
        targetNode = currentNode;
        return AceFocusMoveResult::FIND_EMBED_TARGET;
    }

    // 2 need to check left subtree after current node checked
    auto result = FindPrevReadableNodeToHigherLevel(currentNode, targetNode);
    CHECK_NE_RETURN(result, AceFocusMoveResult::FIND_FAIL, result);
    // 4. cannot find focusable
    auto isInChildTree = currentNode->IsInChildTree();
    HILOG_INFO_FOCUS("result: handled in ChildTree %{public}d", isInChildTree);
    return isInChildTree ? AceFocusMoveResult::FIND_FAIL_IN_CHILDTREE : AceFocusMoveResult::FIND_FAIL;
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
    return FindScrollAncestor(condition,
        currentNode, targetNodes, CheckSupportScrollAction::FIND_FORWARD, false);
}

AceFocusMoveResult AccessibilityFocusStrategy::FindBackwardScrollAncestor(
    AceFocusMoveDetailCondition condition,
    const std::shared_ptr<FocusRulesCheckNode>& currentNode,
    std::list<std::shared_ptr<FocusRulesCheckNode>>& targetNodes)
{
    return FindScrollAncestor(condition,
        currentNode, targetNodes, CheckSupportScrollAction::FIND_BACKWARD, false);
}

AceFocusMoveResult AccessibilityFocusStrategy::FindAnyScrollAncestor(
    AceFocusMoveDetailCondition condition,
    const std::shared_ptr<FocusRulesCheckNode>& currentNode,
    std::list<std::shared_ptr<FocusRulesCheckNode>>& targetNodes)
{
    return FindScrollAncestor(condition,
        currentNode, targetNodes, CheckSupportScrollAction::FIND_ANY, true);
}
} // OHOS::Ace::Framework
