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
#include "adapter/ohos/osal/accessibility/focus_move/accessibility_focus_move_osal_ng.h"
#include "adapter/ohos/osal/js_accessibility_manager.h"
#include "adapter/ohos/osal/accessibility/focus_move/accessibility_focus_frame_node_utils.h"

#include "frameworks/core/accessibility/node_utils/accessibility_frame_node_utils.h"
#include "frameworks/core/components_ng/base/frame_node.h"
#include "frameworks/core/pipeline_ng/pipeline_context.h"

using namespace OHOS::Accessibility;
using namespace OHOS::AccessibilityConfig;

namespace OHOS::Ace::Framework {
namespace {
void SetNextFocusIdToElementInfo(const RefPtr<NG::UINode>& nextNode, AccessibilityElementInfo& nodeInfo)
{
    CHECK_NULL_VOID(nextNode);
    auto elementId = nextNode->GetAccessibilityId();
    if (nodeInfo.GetBelongTreeId() > 0) {
        AccessibilitySystemAbilityClient::SetSplicElementIdTreeId(nodeInfo.GetBelongTreeId(), elementId);
    }
    nodeInfo.SetAccessibilityNextFocusId(elementId);
}

void SetPrevFocusIdToElementInfo(const RefPtr<NG::UINode>& prevNode, AccessibilityElementInfo& nodeInfo)
{
    CHECK_NULL_VOID(prevNode);
    auto elementId = prevNode->GetAccessibilityId();
    if (nodeInfo.GetBelongTreeId() > 0) {
        AccessibilitySystemAbilityClient::SetSplicElementIdTreeId(nodeInfo.GetBelongTreeId(), elementId);
    }
    nodeInfo.SetAccessibilityPreviousFocusId(elementId);
}
} // namespace

void FocusStrategyOsalNG::InvailidElementInfo(Accessibility::AccessibilityElementInfo& info)
{
    info.SetValidElement(false);
}

bool FocusStrategyOsalNG::UpdateOriginNodeInfo(int64_t elementId)
{
    auto context = context_.Upgrade();
    CHECK_NULL_RETURN(context, false);
    auto ngPipeline = AceType::DynamicCast<NG::PipelineContext>(context);
    CHECK_NULL_RETURN(ngPipeline, false);
    auto rootNode = ngPipeline->GetRootElement();
    CHECK_NULL_RETURN(rootNode, false);
    auto jsAccessibilityManager = jsAccessibilityManager_.Upgrade();
    CHECK_NULL_RETURN(jsAccessibilityManager, false);
    auto node = NG::AccessibilityFrameNodeUtils::GetFramenodeByAccessibilityId(rootNode, elementId);
    CHECK_NULL_RETURN(node, false);

    NG::AccessibilityFrameNodeUtils::UpdateAccessibilityVisibleToRoot(node); // to improve performance
    rootNode_ = rootNode;
    baseNode_ = node;
    return true;
}

std::shared_ptr<FocusRulesCheckNode> FocusStrategyOsalNG::GetCurrentCheckNode()
{
    auto baseNode = baseNode_.Upgrade();
    CHECK_NULL_RETURN(baseNode, nullptr);
    return std::make_shared<FrameNodeRulesCheckNode>(baseNode, baseNode->GetAccessibilityId());
}

void FocusStrategyOsalNG::UpdateNextFocus(std::shared_ptr<FocusRulesCheckNode>& checkNode)
{
    auto context = context_.Upgrade();
    CHECK_NULL_VOID(context);
    auto rootNode = rootNode_.Upgrade();
    CHECK_NULL_VOID(rootNode);
    auto baseNode = baseNode_.Upgrade();
    CHECK_NULL_VOID(baseNode);
    auto jsAccessibilityManager = jsAccessibilityManager_.Upgrade();
    CHECK_NULL_VOID(jsAccessibilityManager);

    std::shared_ptr<FrameNodeRulesCheckNode> checkTarget =
        std::static_pointer_cast<FrameNodeRulesCheckNode>(checkNode);
    CHECK_NULL_VOID(checkTarget);
    auto nextFocusNode = jsAccessibilityManager->GetNextFocusNodeByManager(baseNode, rootNode);
    if (nextFocusNode) {
        checkTarget->SetNextFocusFrameNode(nextFocusNode);
        baseNextNode_ = nextFocusNode;
    }
    auto prevFocusNode = jsAccessibilityManager->GetPrevFocusNodeByManager(baseNode, rootNode, context);
    if (prevFocusNode) {
        checkTarget->SetPrevFocusFrameNode(prevFocusNode);
        basePrevNode_ = prevFocusNode;
    }
}

std::shared_ptr<FocusRulesCheckNode> FocusStrategyOsalNG::ChangeToRoot()
{
    auto rootNode = rootNode_.Upgrade();
    CHECK_NULL_RETURN(rootNode, nullptr);
    return std::make_shared<FrameNodeRulesCheckNode>(rootNode, rootNode->GetAccessibilityId());
}

bool FocusStrategyOsalNG::ChangeToEmbed(
    const std::shared_ptr<FocusRulesCheckNode>& resultNode, Accessibility::AccessibilityElementInfo& info)
{
    CHECK_NULL_RETURN(resultNode, false);
    auto checkTarget = std::static_pointer_cast<FrameNodeRulesCheckNode>(resultNode);
    CHECK_NULL_RETURN(checkTarget, false);
    auto finalNode = checkTarget->GetFrameNode();
    CHECK_NULL_RETURN(finalNode, false);
    auto jsAccessibilityManager = jsAccessibilityManager_.Upgrade();
    CHECK_NULL_RETURN(jsAccessibilityManager, false);
    if (jsAccessibilityManager->CheckAndGetEmbedWebElementInfo(finalNode, info)) {
        return true;
    }
    return false;
}

bool FocusStrategyOsalNG::UpdateElementInfo(
    const std::shared_ptr<FocusRulesCheckNode>& resultNode, Accessibility::AccessibilityElementInfo& info)
{
    CHECK_NULL_RETURN(resultNode, false);
    auto checkTarget = std::static_pointer_cast<FrameNodeRulesCheckNode>(resultNode);
    CHECK_NULL_RETURN(checkTarget, false);
    auto finalNode = checkTarget->GetFrameNode();
    CHECK_NULL_RETURN(finalNode, false);
    auto context = context_.Upgrade();
    CHECK_NULL_RETURN(context, false);
    auto mainContext = mainContext_.Upgrade();
    CHECK_NULL_RETURN(mainContext, false);
    auto rootNode = rootNode_.Upgrade();
    CHECK_NULL_RETURN(rootNode, false);
    auto baseNode = baseNode_.Upgrade();
    CHECK_NULL_RETURN(baseNode, false);
    auto jsAccessibilityManager = jsAccessibilityManager_.Upgrade();
    CHECK_NULL_RETURN(jsAccessibilityManager, false);
    auto ngPipeline = AceType::DynamicCast<NG::PipelineContext>(context);
    CHECK_NULL_RETURN(ngPipeline, false);

    CommonProperty commonProperty;
    jsAccessibilityManager->GenerateCommonProperty(context, commonProperty, mainContext, finalNode);
    jsAccessibilityManager->UpdateAccessibilityElementInfo(finalNode, commonProperty, info, ngPipeline);
    jsAccessibilityManager->UpdateElementInfoTreeId(info);
    auto nextNode = baseNextNode_.Upgrade();
    auto prevNode = basePrevNode_.Upgrade();
    if (baseNode->GetAccessibilityId() != finalNode->GetAccessibilityId()) {
        nextNode = jsAccessibilityManager->GetNextFocusNodeByManager(finalNode, rootNode);
        prevNode = jsAccessibilityManager->GetPrevFocusNodeByManager(finalNode, rootNode, context);
    }
    if (nextNode) {
        SetNextFocusIdToElementInfo(nextNode, info);
    }
    if (prevNode) {
        SetPrevFocusIdToElementInfo(prevNode, info);
    }
    return true;
}
bool FocusStrategyOsalNG::CheckAndGetReadableInfoToRoot(
    const RefPtr<NG::FrameNode>& currentFrameNode, Accessibility::AccessibilityElementInfo& targetInfo)
{
    CHECK_NULL_RETURN(currentFrameNode, false);
    bool isReadable = true;
    auto client = Accessibility::AccessibilitySystemAbilityClient::GetInstance();
    CHECK_NULL_RETURN(client, false);
    auto inputNode = std::make_shared<FrameNodeRulesCheckNode>(
        currentFrameNode, currentFrameNode->GetAccessibilityId());
    std::shared_ptr<FocusRulesCheckNode> checkNode =
        std::static_pointer_cast<FocusRulesCheckNode>(inputNode);
    while (checkNode) {
        auto checkResult = client->CheckNodeIsReadable(checkNode, isReadable);
        CHECK_NE_RETURN(checkResult, Accessibility::RET_OK, false);
        if (isReadable) {
            UpdateOriginNodeInfo(checkNode->GetAccessibilityId());
            UpdateElementInfo(checkNode, targetInfo);
            return true;
        }
        checkNode = checkNode->GetAceParent();
    }
    return false;
}

bool FocusStrategyOsalNG::DetectElementInfoFocusableThroughAncestor(
    const Accessibility::AccessibilityElementInfo& info, const int64_t parentId,
    Accessibility::AccessibilityElementInfo& targetInfo)
{
    auto context = context_.Upgrade();
    CHECK_NULL_RETURN(context, false);
    auto mainContext = mainContext_.Upgrade();
    CHECK_NULL_RETURN(mainContext, false);
    auto ngPipeline = AceType::DynamicCast<NG::PipelineContext>(context);
    CHECK_NULL_RETURN(ngPipeline, false);
    auto rootNode = ngPipeline->GetRootElement();
    CHECK_NULL_RETURN(rootNode, false);
    auto baseNode = NG::AccessibilityFrameNodeUtils::GetFramenodeByAccessibilityId(rootNode, parentId);
    CHECK_NULL_RETURN(baseNode, false);
    auto jsAccessibilityManager = jsAccessibilityManager_.Upgrade();
    CHECK_NULL_RETURN(jsAccessibilityManager, false);
    auto checkNode = std::make_shared<DetectParentRulesCheckNode>(info, baseNode);
    bool isReadable = true;
    auto client = Accessibility::AccessibilitySystemAbilityClient::GetInstance();
    if (!client) {
        targetInfo = info;
        return true;
    }
    auto checkResult = client->CheckNodeIsReadable(checkNode, isReadable);
    if (checkResult != Accessibility::RET_OK) {
        targetInfo = info;
        return true;
    }
    if (!isReadable) {
        return CheckAndGetReadableInfoToRoot(baseNode, targetInfo);
    }
    return isReadable;
}
} // OHOS::Ace::Framework
