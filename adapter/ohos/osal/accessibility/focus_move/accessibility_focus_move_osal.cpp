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

FocusMoveResultType FocusStrategyOsal::HandleFocusMoveSearchResult(
    const Accessibility::AccessibilityFocusMoveParam& param,
    const std::shared_ptr<FocusRulesCheckNode>& targetNode,
    AceFocusMoveResult result,
    Accessibility::AccessibilityElementInfo& info)
{
    FocusMoveResultType finalResult = FocusMoveResultType::SEARCH_FAIL;
    auto finalNode = targetNode;
    bool useFinalNode = true;
    if (result == AceFocusMoveResult::FIND_SUCCESS) {
        finalResult = FocusMoveResultType::SEARCH_SUCCESS;
    } else if (result == AceFocusMoveResult::FIND_CHILDTREE) {
        finalResult = ((param.direction == FocusMoveDirection::BACKWARD)
            || (param.direction == FocusMoveDirection::FIND_LAST)) ?
                FocusMoveResultType::DOUBLE_CHECK_CHILD_PROPERTY_AND_GET_LAST
                    : FocusMoveResultType::DOUBLE_CHECK_CHILD_PROPERTY;
    } else if ((result == AceFocusMoveResult::FIND_FAIL_IN_CHILDTREE)
        && (param.direction != FocusMoveDirection::FIND_LAST)) {
            finalResult = FocusMoveResultType::SEARCH_FAIL_IN_CHILDTREE;
            finalNode = ChangeToRoot();
    } else if (result == AceFocusMoveResult::FIND_EMBED_TARGET) {
        finalResult = FocusMoveResultType::SEARCH_NEXT;
        if (!ChangeToEmbed(targetNode, info)) {
            finalResult = FocusMoveResultType::SEARCH_FAIL;
        }
        useFinalNode = false;
    } else if (result == AceFocusMoveResult::FIND_FAIL_IN_SCROLL) {
        finalResult = FocusMoveResultType::SEARCH_FAIL_IN_SCROLL;
    } else if (result == AceFocusMoveResult::FIND_FAIL_LOST_NODE) {
        finalResult = FocusMoveResultType::SEARCH_FAIL_LOST_NODE;
    }
    if (useFinalNode && finalNode) {
        if (!UpdateElementInfo(finalNode, info)) {
            finalResult = FocusMoveResultType::SEARCH_FAIL;
        }
    }
    if (finalResult == FocusMoveResultType::SEARCH_FAIL) {
        InvailidElementInfo(info);
    }
    return finalResult;
}

FocusMoveResult FocusStrategyOsal::ExecuteFocusMoveSearch(
    const int64_t elementId,
    const Accessibility::AccessibilityFocusMoveParam& param,
    Accessibility::AccessibilityElementInfo& info)
{
    FocusMoveResult errorResult = {
        .resultType = FocusMoveResultType::NOT_SUPPORT,
        .nowLevelBelongTreeId = -1,
        .parentWindowId = 0,
        .changeToNewInfo = false,
        .needTerminate = false,
    };

    InvailidElementInfo(info);
    auto accessibilityManager = accessibilityManager_.Upgrade();
    CHECK_NULL_RETURN(accessibilityManager, errorResult);
    AceFocusMoveDetailCondition condition = GetAceCondition(param);
    UpdateOriginNodeInfo(elementId); // get root node, update visible
    auto checkNode = GetCurrentCheckNode();
    errorResult.resultType = FocusMoveResultType::SEARCH_FAIL_LOST_NODE;
    errorResult.needTerminate = true;
    CHECK_NULL_RETURN(checkNode, errorResult);
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
        errorResult.resultType = FocusMoveResultType::NOT_SUPPORT;
        return errorResult;
    }
    FocusMoveResult finalResult = {
        .resultType = FocusMoveResultType::SEARCH_FAIL,
        .nowLevelBelongTreeId = -1,
        .parentWindowId = 0,
        .changeToNewInfo = false,
        .needTerminate = false,
    };
    finalResult.resultType = HandleFocusMoveSearchResult(param, targetNode, result, info);
    return finalResult;
}

FocusMoveResult FocusStrategyOsal::ProcessGetScrollAncestor(
    const int64_t elementId,
    const Accessibility::AccessibilityFocusMoveParam& param,
    std::list<Accessibility::AccessibilityElementInfo>& infos)
{
    FocusMoveResult errorResult = {
        .resultType = FocusMoveResultType::SEARCH_FAIL,
        .nowLevelBelongTreeId = -1,
        .parentWindowId = 0,
        .changeToNewInfo = false,
        .needTerminate = false,
    };
    auto accessibilityManager = accessibilityManager_.Upgrade();
    CHECK_NULL_RETURN(accessibilityManager, errorResult);
    UpdateOriginNodeInfo(elementId); // get root node, update visible
    auto checkNode = GetCurrentCheckNode();
    errorResult.resultType = FocusMoveResultType::SEARCH_FAIL_LOST_NODE;
    errorResult.needTerminate = true;
    CHECK_NULL_RETURN(checkNode, errorResult);
    std::list<std::shared_ptr<FocusRulesCheckNode>> targetNodes;
    AccessibilityFocusStrategy strategy;
    AceFocusMoveDetailCondition condition = {.bypassSelf = true, .bypassDescendants = false};
    if (param.direction == FocusMoveDirection::GET_BACKWARD_SCROLL_ANCESTOR) {
        strategy.FindBackwardScrollAncestor(condition, checkNode, targetNodes);
    } else if (param.direction == FocusMoveDirection::GET_FORWARD_SCROLL_ANCESTOR) {
        strategy.FindForwardScrollAncestor(condition, checkNode, targetNodes);
    } else {
        strategy.FindAnyScrollAncestor(condition, checkNode, targetNodes);
    }
    for (auto& bastTarget : targetNodes) {
        Accessibility::AccessibilityElementInfo info;
        if (!UpdateElementInfo(bastTarget, info)) {
            continue;
        }
        infos.emplace_back(info);
    }
    FocusMoveResult finalResult = {
        .resultType = FocusMoveResultType::SEARCH_FAIL,
        .nowLevelBelongTreeId = -1,
        .parentWindowId = 0,
        .changeToNewInfo = false,
        .needTerminate = false,
    };
    finalResult.resultType = infos.empty() ? FocusMoveResultType::SEARCH_FAIL : FocusMoveResultType::SEARCH_SUCCESS;
    return finalResult;
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

bool FocusStrategyOsal::IsProcessDetectFocusable(const Accessibility::AccessibilityFocusMoveParam& param)
{
    bool result = false;
    switch (param.direction) {
        case FocusMoveDirection::DETECT_FOCUSABLE_IN_FOCUS_MOVE:
        case FocusMoveDirection::DETECT_FOCUSABLE_IN_HOVER:
            result = true;
            break;
        default:
            break;
    }
    return result;
}

void JsAccessibilityManager::DetectElementInfoFocusableThroughAncestor(
    const Accessibility::AccessibilityElementInfo& info,
    const Accessibility::AccessibilityFocusMoveParam param, const int32_t requestId,
    Accessibility::AccessibilityElementOperatorCallback &callback, const int32_t windowId)
{
    auto jsAccessibilityManager = AceType::Claim(this);
    auto mainContext = context_.Upgrade();
    auto context = GetPipelineByWindowId(windowId);
    FocusStrategyOsalNG strategy(jsAccessibilityManager, context, mainContext);
    std::list<Accessibility::AccessibilityElementInfo> targetInfos;
    auto result = strategy.DetectElementInfoFocusableThroughAncestor(info, param, targetInfos, windowId);
    HILOG_INFO_FOCUS("detect result %{public}d requestId %{public}d nowLevelBelongTreeId %{public}d \
        parentWindowId %{public}d changeToNewInfo %{public}d needTerminate %{public}d",
        result.resultType, requestId, result.nowLevelBelongTreeId,
        result.parentWindowId, result.changeToNewInfo, result.needTerminate);
    callback.SetFocusMoveSearchWithConditionResult(targetInfos, result, requestId);
}

void JsAccessibilityManager::FocusMoveSearchWithConditionForNode(
    const AccessibilityElementInfo& info, const Accessibility::AccessibilityFocusMoveParam param,
    const int32_t requestId, Accessibility::AccessibilityElementOperatorCallback& callback, const int32_t windowId)
{
    FocusMoveResult errorResult = {
        .resultType = FocusMoveResultType::SEARCH_FAIL,
        .nowLevelBelongTreeId = -1,
        .parentWindowId = 0,
        .changeToNewInfo = false,
        .needTerminate = true,
    };
    auto elementId = info.GetAccessibilityId();
    int64_t splitElementId = AccessibilityElementInfo::UNDEFINED_ACCESSIBILITY_ID;
    int32_t splitTreeId = AccessibilityElementInfo::UNDEFINED_TREE_ID;
    AccessibilitySystemAbilityClient::GetTreeIdAndElementIdBySplitElementId(elementId, splitElementId, splitTreeId);
    if (FocusStrategyOsal::IsProcessGetScrollAncestor(param)) {
        ProcessGetScrollAncestorNode(splitElementId, param, requestId, callback);
        return;
    }
    Accessibility::AccessibilityElementInfo nodeInfo;
    std::list<Accessibility::AccessibilityElementInfo> infos;
    if (FocusStrategyOsal::IsProcessDetectFocusable(param)) {
        nodeInfo.SetValidElement(false);
        infos.emplace_back(nodeInfo);
        callback.SetFocusMoveSearchWithConditionResult(infos, errorResult, requestId);
        return;
    }
    FocusMoveSearchAccessibilityNodeWithCondition(splitElementId, param, requestId, callback);
}

void JsAccessibilityManager::FocusMoveSearchWithCondition(
    const AccessibilityElementInfo& info, const Accessibility::AccessibilityFocusMoveParam param,
    const int32_t requestId, Accessibility::AccessibilityElementOperatorCallback& callback, const int32_t windowId)
{
    FocusMoveResult errorResult = {
        .resultType = FocusMoveResultType::SEARCH_FAIL,
        .nowLevelBelongTreeId = -1,
        .parentWindowId = 0,
        .changeToNewInfo = false,
        .needTerminate = true,
    };
    Accessibility::AccessibilityElementInfo nodeInfo;
    std::list<Accessibility::AccessibilityElementInfo> infos;
    auto context = GetPipelineByWindowId(windowId);
    if (!context) {
        nodeInfo.SetValidElement(false);
        infos.emplace_back(nodeInfo);
        callback.SetFocusMoveSearchWithConditionResult(infos, errorResult, requestId);
        return;
    }
    auto elementId = info.GetAccessibilityId();
    int64_t splitElementId = AccessibilityElementInfo::UNDEFINED_ACCESSIBILITY_ID;
    int32_t splitTreeId = AccessibilityElementInfo::UNDEFINED_TREE_ID;
    AccessibilitySystemAbilityClient::GetTreeIdAndElementIdBySplitElementId(elementId, splitElementId, splitTreeId);

    if (AceType::InstanceOf<NG::PipelineContext>(context)) {
        if (FocusStrategyOsal::IsProcessGetScrollAncestor(param)) {
            if (param.detectParent) {
                splitElementId = AccessibilityElementInfo::UNDEFINED_ACCESSIBILITY_ID;
                splitTreeId = AccessibilityElementInfo::UNDEFINED_TREE_ID;
                AccessibilitySystemAbilityClient::GetTreeIdAndElementIdBySplitElementId(
                    param.parentId, splitElementId, splitTreeId);
            }
            ProcessGetScrollAncestor(splitElementId, param, context, requestId, callback);
            return;
        }

        if (FocusStrategyOsal::IsProcessDetectFocusable(param)) {
            DetectElementInfoFocusableThroughAncestor(info, param, requestId, callback, windowId);
            return;
        }
        auto result = FocusMoveSearchWithConditionNG(splitElementId, param, context, nodeInfo);
        infos.emplace_back(nodeInfo);
        HILOG_INFO_FOCUS("focus move search result id %{public}" PRId64 ", "
            "ret %{public}d requestID %{public}d",
            nodeInfo.GetAccessibilityId(), result.resultType, requestId);
        callback.SetFocusMoveSearchWithConditionResult(infos, result, requestId);
        return;
    }

    FocusMoveSearchWithConditionForNode(info, param, requestId, callback, windowId);
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
    auto result = strategy.ProcessGetScrollAncestor(elementId, param, infos);
    HILOG_INFO_FOCUS("focus move search get scroll result  %{public}d requestID %{public}d",
        result.resultType, requestId);
    callback.SetFocusMoveSearchWithConditionResult(infos, result, requestId);
}

void JsAccessibilityManager::ProcessGetScrollAncestorNode(
    const int64_t elementId, const Accessibility::AccessibilityFocusMoveParam param,
    const int32_t requestId, Accessibility::AccessibilityElementOperatorCallback& callback)
{
    auto jsAccessibilityManager = AceType::Claim(this);
    FocusStrategyOsalNode strategy(jsAccessibilityManager);
    std::list<Accessibility::AccessibilityElementInfo> infos;
    auto result = strategy.ProcessGetScrollAncestor(elementId, param, infos);
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
    // if cannot find in childtree, need to continue to find readable in parent process
    auto context = curFrameNode->GetContextRefPtr();
    CHECK_NULL_RETURN(context, true);
    const auto& accessibilityManager = context->GetAccessibilityManager();
    CHECK_NULL_RETURN(accessibilityManager, true);
    CHECK_EQUAL_RETURN(accessibilityManager->GetTreeId(), 0, true);
    auto ngPipeline = AceType::DynamicCast<NG::PipelineContext>(context);
    CHECK_NULL_RETURN(ngPipeline, true);
    readableNode = ngPipeline->GetRootElement();
    return true;
}
} // OHOS::Ace::Framework
