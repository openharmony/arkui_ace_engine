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
#include "adapter/ohos/osal/accessibility/focus_move/accessibility_focus_move_osal.h"
#include "adapter/ohos/osal/accessibility/focus_move/accessibility_focus_move_osal_ng.h"
#include "adapter/ohos/osal/accessibility/focus_move/accessibility_focus_move_osal_node.h"
#include "adapter/ohos/osal/js_accessibility_manager.h"

using namespace OHOS::Accessibility;
using namespace OHOS::AccessibilityConfig;

namespace OHOS::Ace::Framework {
AceFocusMoveDetailCondition FocusStrategyOsal::GetAceCondition(
    const Accessibility::AccessibilityFocusMoveParam& param)
{
    AceFocusMoveDetailCondition condition = {.bypassSelf = true, .bypassDescendants = false};

    switch (param.condition) {
        case DetailCondition::BYPASS_SELF:
            condition.bypassSelf = true;
            condition.bypassDescendants = false;
            break;
        case DetailCondition::BYPASS_SELF_DESCENDANTS:
            condition.bypassSelf = true;
            condition.bypassDescendants = true;
            break;
        case DetailCondition::CHECK_SELF:
            condition.bypassSelf = false;
            condition.bypassDescendants = false;
            break;
        case DetailCondition::CHECK_SELF_BYPASS_DESCENDANTS:
            condition.bypassSelf = false;
            condition.bypassDescendants = true;
            break;
        default:
            break;
    }
    return condition;
}

FocusMoveResult FocusStrategyOsal::HandleFocusMoveSearchResult(
    const Accessibility::AccessibilityFocusMoveParam& param,
    const std::shared_ptr<FocusRulesCheckNode>& targetNode,
    AceFocusMoveResult result,
    Accessibility::AccessibilityElementInfo& info)
{
    FocusMoveResult finalResult = FocusMoveResult::SEARCH_FAIL;
    auto finalNode = targetNode;
    bool useFinalNode = true;
    if (result == AceFocusMoveResult::FIND_SUCCESS) {
        finalResult = FocusMoveResult::SEARCH_SUCCESS;
    } else if (result == AceFocusMoveResult::FIND_CHILDTREE) {
        finalResult = ((param.direction == FocusMoveDirection::BACKWARD)
            || (param.direction == FocusMoveDirection::FIND_LAST)) ?
                FocusMoveResult::DOUBLE_CHECK_CHILD_PROPERTY_AND_GET_LAST
                    : FocusMoveResult::DOUBLE_CHECK_CHILD_PROPERTY;
    } else if ((result == AceFocusMoveResult::FIND_FAIL_IN_CHILDTREE)
        && (param.direction != FocusMoveDirection::FIND_LAST)) {
            finalResult = FocusMoveResult::SEARCH_FAIL_IN_CHILDTREE;
            finalNode = ChangeToRoot();
    } else if (result == AceFocusMoveResult::FIND_EMBED_TARGET) {
        finalResult = FocusMoveResult::SEARCH_NEXT;
        if (!ChangeToEmbed(targetNode, info)) {
            finalResult = FocusMoveResult::SEARCH_FAIL;
        }
        useFinalNode = false;
    } else if (result == AceFocusMoveResult::FIND_FAIL_IN_SCROLL) {
        finalResult = FocusMoveResult::SERACH_FAIL_IN_SCROLL;
    }
    if (useFinalNode && finalNode) {
        if (!UpdateElementInfo(finalNode, info)) {
            finalResult = FocusMoveResult::SEARCH_FAIL;
        }
    }
    if (finalResult == FocusMoveResult::SEARCH_FAIL) {
        InvailidElementInfo(info);
    }
    return finalResult;
}

FocusMoveResult FocusStrategyOsal::ExecuteFocusMoveSearch(
    const int64_t elementId,
    const Accessibility::AccessibilityFocusMoveParam& param,
    Accessibility::AccessibilityElementInfo& info)
{
    InvailidElementInfo(info);
    auto accessibilityManager = accessibilityManager_.Upgrade();
    CHECK_NULL_RETURN(accessibilityManager, FocusMoveResult::NOT_SUPPORT);
    AceFocusMoveDetailCondition condition = GetAceCondition(param);
    UpdateOriginNodeInfo(elementId); // get root node, update visible
    auto checkNode = GetCurrentCheckNode();
    UpdateNextFocus(checkNode);
    std::shared_ptr<FocusRulesCheckNode> targetNode;
    AccessibilityFocusStrategy strategy;
    AceFocusMoveResult result = AceFocusMoveResult::FIND_FAIL;
    if (param.direction == FocusMoveDirection::BACKWARD) {
        result = strategy.FindPrevReadableNode(condition, checkNode, targetNode);
    } else if (param.direction == FocusMoveDirection::FORWARD) {
        result = strategy.FindNextReadableNode(condition, checkNode, targetNode);
    } else if (param.direction == FocusMoveDirection::FIND_LAST) {
        result = strategy.FindLastNodeWithoutCheck(condition, checkNode, targetNode);
    } else {
        InvailidElementInfo(info);
        return FocusMoveResult::NOT_SUPPORT;
    }
    return HandleFocusMoveSearchResult(param, targetNode, result, info);
}

void FocusStrategyOsal::ProcessGetScrollAncestor(
    const int64_t elementId,
    const Accessibility::AccessibilityFocusMoveParam& param,
    std::list<Accessibility::AccessibilityElementInfo>& infos)
{
    auto accessibilityManager = accessibilityManager_.Upgrade();
    CHECK_NULL_VOID(accessibilityManager);
    UpdateOriginNodeInfo(elementId); // get root node, update visible
    auto checkNode = GetCurrentCheckNode();
    std::list<std::shared_ptr<FocusRulesCheckNode>> targetNodes;
    AccessibilityFocusStrategy strategy;
    AceFocusMoveDetailCondition condition = {.bypassSelf = true, .bypassDescendants = false};
    if (param.direction == FocusMoveDirection::GET_BACKWARD_SCROLL_ANCESTOR) {
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

bool FocusStrategyOsal::IsProcessGetScrollAncestor(const Accessibility::AccessibilityFocusMoveParam& param)
{
    bool result = false;
    switch (param.direction) {
        case FocusMoveDirection::GET_BACKWARD_SCROLL_ANCESTOR:
        case FocusMoveDirection::GET_FORWARD_SCROLL_ANCESTOR:
        case FocusMoveDirection::GET_SCROLLABLE_ANCESTOR:
            result = true;
            break;
        default:
            break;
    }
    return result;
}

void JsAccessibilityManager::DetectElementInfoFocusableThroughAncestor(
    const Accessibility::AccessibilityElementInfo &info,
    const int64_t parentId, const int32_t requestId,
    Accessibility::AccessibilityElementOperatorCallback &callback, const int32_t windowId)
{
    auto jsAccessibilityManager = AceType::Claim(this);
    auto mainContext = context_.Upgrade();
    auto context = GetPipelineByWindowId(windowId);
    FocusStrategyOsalNG strategy(jsAccessibilityManager, context, mainContext);
    auto result = strategy.DetectElementInfoFocusableThroughAncestor(info, parentId);
    callback.SetDetectElementInfoFocusableThroughAncestorResult(result, requestId);
}

void JsAccessibilityManager::FocusMoveSearchWithCondition(
    const int64_t elementId, const Accessibility::AccessibilityFocusMoveParam param,
    const int32_t requestId, Accessibility::AccessibilityElementOperatorCallback& callback, const int32_t windowId)
{
    Accessibility::AccessibilityElementInfo nodeInfo;
    std::list<Accessibility::AccessibilityElementInfo> infos;
    auto context = GetPipelineByWindowId(windowId);
    if (!context) {
        nodeInfo.SetValidElement(false);
        infos.emplace_back(nodeInfo);
        callback.SetFocusMoveSearchWithConditionResult(infos, FocusMoveResult::SEARCH_FAIL, requestId);
        return;
    }

    if (AceType::InstanceOf<NG::PipelineContext>(context)) {
        if (FocusStrategyOsal::IsProcessGetScrollAncestor(param)) {
            ProcessGetScrollAncestor(elementId, param, context, requestId, callback);
            return;
        }
        auto result = FocusMoveSearchWithConditionNG(elementId, param, context, nodeInfo);
        infos.emplace_back(nodeInfo);
        callback.SetFocusMoveSearchWithConditionResult(infos, result, requestId);
        return;
    }

    if (FocusStrategyOsal::IsProcessGetScrollAncestor(param)) {
        ProcessGetScrollAncestorNode(elementId, param, requestId, callback);
        return;
    }
    FocusMoveSearchAccessibilityNodeWithCondition(elementId, param, requestId, callback);
}

void JsAccessibilityManager::FocusMoveSearchAccessibilityNodeWithCondition(
    const int64_t elementId, const Accessibility::AccessibilityFocusMoveParam param,
    const int32_t requestId, Accessibility::AccessibilityElementOperatorCallback &callback)
{
    Accessibility::AccessibilityElementInfo info;
    std::list<Accessibility::AccessibilityElementInfo> infos;
    auto jsAccessibilityManager = AceType::Claim(this);
    FocusStrategyOsalNode strategy(jsAccessibilityManager);
    auto result = strategy.ExecuteFocusMoveSearch(elementId, param, info);
    infos.emplace_back(info);
    callback.SetFocusMoveSearchWithConditionResult(infos, result, requestId);
}

FocusMoveResult JsAccessibilityManager::FocusMoveSearchWithConditionNG(
    const int64_t elementId, const Accessibility::AccessibilityFocusMoveParam param,
    const RefPtr<PipelineBase>& context, Accessibility::AccessibilityElementInfo& info)
{
    auto jsAccessibilityManager = AceType::Claim(this);
    auto mainContext = context_.Upgrade();
    FocusStrategyOsalNG strategy(jsAccessibilityManager, context, mainContext);
    return strategy.ExecuteFocusMoveSearch(elementId, param, info);
}

void JsAccessibilityManager::ProcessGetScrollAncestor(
    const int64_t elementId, const Accessibility::AccessibilityFocusMoveParam param,
    const RefPtr<PipelineBase>& context, const int32_t requestId,
    Accessibility::AccessibilityElementOperatorCallback& callback)
{
    auto jsAccessibilityManager = AceType::Claim(this);
    auto mainContext = context_.Upgrade();
    FocusStrategyOsalNG strategy(jsAccessibilityManager, context, mainContext);
    std::list<Accessibility::AccessibilityElementInfo> infos;
    strategy.ProcessGetScrollAncestor(elementId, param, infos);
    auto result = FocusMoveResult::SEARCH_SUCCESS;
    if (infos.empty()) {
        Accessibility::AccessibilityElementInfo info;
        info.SetValidElement(false);
        infos.emplace_back(info);
        result = FocusMoveResult::SEARCH_FAIL;
    }
    callback.SetFocusMoveSearchWithConditionResult(infos, result, requestId);
}

void JsAccessibilityManager::ProcessGetScrollAncestorNode(
    const int64_t elementId, const Accessibility::AccessibilityFocusMoveParam param,
    const int32_t requestId, Accessibility::AccessibilityElementOperatorCallback& callback)
{
    auto jsAccessibilityManager = AceType::Claim(this);
    FocusStrategyOsalNode strategy(jsAccessibilityManager);
    std::list<Accessibility::AccessibilityElementInfo> infos;
    strategy.ProcessGetScrollAncestor(elementId, param, infos);
    auto result = FocusMoveResult::SEARCH_SUCCESS;
    if (infos.empty()) {
        Accessibility::AccessibilityElementInfo info;
        info.SetValidElement(false);
        infos.emplace_back(info);
        result = FocusMoveResult::SEARCH_FAIL;
    }
    callback.SetFocusMoveSearchWithConditionResult(infos, result, requestId);
}

bool JsAccessibilityManager::NeedChangeToReadableNode(const RefPtr<NG::FrameNode>& curFrameNode,
    RefPtr<NG::FrameNode>& readableNode)
{
    CHECK_NULL_RETURN(curFrameNode, false);
    auto client = Accessibility::AccessibilitySystemAbilityClient::GetInstance();
    CHECK_NULL_RETURN(client, false);
    bool isScreenReaderRulesEnabled = false;
    auto result = client->IsScreenReaderRulesEnabled(isScreenReaderRulesEnabled);
    CHECK_NE_RETURN(result, Accessibility::RET_OK, false);
    CHECK_NE_RETURN(isScreenReaderRulesEnabled, true, false);
    bool isReadable = false;
    bool isHit = false;
    RefPtr<NG::FrameNode> targetCheckNode = curFrameNode;
    while (targetCheckNode) {
        auto checkNode =
            std::make_shared<FrameNodeRulesCheckNode>(targetCheckNode, targetCheckNode->GetAccessibilityId());
        auto checkResult = client->CheckNodeIsSpecificType(
            checkNode, Accessibility::ReadableSpecificType::ROOT_TYPE, isHit);
        if ((checkResult == Accessibility::RET_OK) && isHit) {
            break;
        }
        checkResult = client->CheckNodeIsReadable(checkNode, isReadable);
        if ((checkResult == Accessibility::RET_OK) && isReadable) {
            readableNode = targetCheckNode;
            return true;
        }
        targetCheckNode = targetCheckNode->GetParentFrameNode();
    }
    // true means using find result to send hover since rlues check enable
    return true;
}
} // OHOS::Ace::Framework
