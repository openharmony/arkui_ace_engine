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
#include "adapter/ohos/osal/accessibility/focus_move/accessibility_focus_move_osal.h"


using namespace OHOS::Accessibility;
using namespace OHOS::AccessibilityConfig;

namespace OHOS::Ace::Framework {
AceFocusMoveDetailCondition FocusStrategyOsal::GetAceCondition(
    const Accessibility::AccessibilityFocusMoveParamStub& param)
{
    AceFocusMoveDetailCondition condition = {.bypassSelf = true, .bypassDescendants = false};

    switch (param.condition) {
        case DetailConditionStub::BYPASS_SELF:
            condition.bypassSelf = true;
            condition.bypassDescendants = false;
            break;
        case DetailConditionStub::BYPASS_SELF_DESCENDANTS:
            condition.bypassSelf = true;
            condition.bypassDescendants = true;
            break;
        case DetailConditionStub::CHECK_SELF:
            condition.bypassSelf = false;
            condition.bypassDescendants = false;
            break;
        case DetailConditionStub::CHECK_SELF_BYPASS_DESCENDANTS:
            condition.bypassSelf = false;
            condition.bypassDescendants = true;
            break;
        default:
            break;
    }
    return condition;
}

FocusMoveResultStub FocusStrategyOsal::HandleFocusMoveSearchResult(
    const Accessibility::AccessibilityFocusMoveParamStub& param,
    const std::shared_ptr<FocusRulesCheckNode>& targetNode,
    AceFocusMoveResult result,
    Accessibility::AccessibilityElementInfo& info)
{
    FocusMoveResultStub finalResult = FocusMoveResultStub::SEARCH_FAIL;
    auto finalNode = targetNode;
    bool useFinalNode = true;
    if (result == AceFocusMoveResult::FIND_SUCCESS) {
        finalResult = FocusMoveResultStub::SEARCH_SUCCESS;
    } else if (result == AceFocusMoveResult::FIND_CHILDTREE) {
        finalResult = ((param.direction == FocusMoveDirectionStub::BACKWARD)
            || (param.direction == FocusMoveDirectionStub::FIND_LAST)) ?
                FocusMoveResultStub::DOUBLE_CHECK_CHILD_PROPERTY_AND_GET_LAST
                    : FocusMoveResultStub::DOUBLE_CHECK_CHILD_PROPERTY;
    } else if ((result == AceFocusMoveResult::FIND_FAIL_IN_CHILDTREE)
        && (param.direction == FocusMoveDirectionStub::BACKWARD)) {
            finalResult = FocusMoveResultStub::SEARCH_FAIL_IN_CHILDTREE;
            finalNode = ChangeToRoot();
    } else if (result == AceFocusMoveResult::FIND_EMBED_TARGET) {
        finalResult = FocusMoveResultStub::SEARCH_NEXT;
        if (!ChangeToEmbed(targetNode, info)) {
            finalResult = FocusMoveResultStub::SEARCH_FAIL;
        }
        useFinalNode = false;
    } else if (result == AceFocusMoveResult::FIND_FAIL_IN_SCROLL) {
        finalResult = FocusMoveResultStub::SERAH_FAIL_IN_SCROLL;
    }
    if (useFinalNode && finalNode) {
        if (!UpdateElementInfo(finalNode, info)) {
            finalResult = FocusMoveResultStub::SEARCH_FAIL;
        }
    }
    if (finalResult == FocusMoveResultStub::SEARCH_FAIL) {
        InvailidElementInfo(info);
    }
    return finalResult;
}

FocusMoveResultStub FocusStrategyOsal::ExecuteFocusMoveSearch(
    const int64_t elementId,
    const Accessibility::AccessibilityFocusMoveParamStub& param,
    Accessibility::AccessibilityElementInfo& info)
{
    InvailidElementInfo(info);
    auto accessibilityManager = accessibilityManager_.Upgrade();
    CHECK_NULL_RETURN(accessibilityManager, FocusMoveResultStub::NOT_SUPPORT);
    AceFocusMoveDetailCondition condition = GetAceCondition(param);
    UpdateOriginNodeInfo(elementId); // get root node, update visible
    auto checkNode = GetCurrentCheckNode();
    UpdateNextFocus(checkNode);
    std::shared_ptr<FocusRulesCheckNode> targetNode;
    AccessibilityFocusStrategy strategy;
    AceFocusMoveResult result = AceFocusMoveResult::FIND_FAIL;
    if (param.direction == FocusMoveDirectionStub::BACKWARD) {
        result = strategy.FindPrevReadableNode(condition, checkNode, targetNode);
    } else if (param.direction == FocusMoveDirectionStub::FORWARD) {
        result = strategy.FindNextReadableNode(condition, checkNode, targetNode);
    } else if (param.direction == FocusMoveDirectionStub::FIND_LAST) {
        result = strategy.FindLastNodeWithoutCheck(condition, checkNode, targetNode);
    } else {
        InvailidElementInfo(info);
        return FocusMoveResultStub::NOT_SUPPORT;
    }
    return HandleFocusMoveSearchResult(param, targetNode, result, info);
}

void FocusStrategyOsal::ProcessGetScrollAncestor(
    const int64_t elementId,
    const Accessibility::AccessibilityFocusMoveParamStub& param,
    std::list<Accessibility::AccessibilityElementInfo>& infos)
{
    auto accessibilityManager = accessibilityManager_.Upgrade();
    CHECK_NULL_VOID(accessibilityManager);
    UpdateOriginNodeInfo(elementId); // get root node, update visible
    auto checkNode = GetCurrentCheckNode();
    std::list<std::shared_ptr<FocusRulesCheckNode>> targetNodes;
    AccessibilityFocusStrategy strategy;
    AceFocusMoveDetailCondition condition = {.bypassSelf = true, .bypassDescendants = false};
    if (param.direction == FocusMoveDirectionStub::GET_BACKWARD_SCROLL_ANCESTOR) {
        strategy.FindBackwardScrollAncestor(condition, checkNode, targetNodes);
    } else {
        strategy.FindForwardScrollAncestor(condition, checkNode, targetNodes);
    }
    for (auto& bastTarget : targetNodes) {
        Accessibility::AccessibilityElementInfo info;
        if (!UpdateElementInfo(bastTarget, info)) {
            continue;
        }
        infos.emplace_back(info);
    }
}

bool FocusStrategyOsal::IsProcessGetScrollAncestor(const Accessibility::AccessibilityFocusMoveParamStub& param)
{
    bool result = false;
    switch (param.direction) {
        case FocusMoveDirectionStub::GET_BACKWARD_SCROLL_ANCESTOR:
        case FocusMoveDirectionStub::GET_FORWARD_SCROLL_ANCESTOR:
        case FocusMoveDirectionStub::GET_SCROLLABLE_ANCESTOR:
            result = true;
            break;
        default:
            break;
    }
    return result;
}
} // OHOS::Ace::Framework
