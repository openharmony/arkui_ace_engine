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
#include "adapter/ohos/osal/accessibility/focus_move/accessibility_focus_move_osal_third.h"
#include "adapter/ohos/osal/accessibility/focus_move/accessibility_focus_third_node_utils.h"
#include "adapter/ohos/osal/js_third_provider_interaction_operation_utils.h"

#include "adapter/ohos/osal/js_accessibility_manager.h"
#include "frameworks/core/accessibility/accessibility_provider.h"

using namespace OHOS::Accessibility;
using namespace OHOS::AccessibilityConfig;

namespace OHOS::Ace::Framework {

void FocusStrategyOsalThird::InvailidElementInfo(Accessibility::AccessibilityElementInfo& info)
{
    info.SetValidElement(false);
}

bool FocusStrategyOsalThird::UpdateOriginNodeInfo(int64_t elementId)
{
    return JsThirdProviderInteractionOperation::FindNativeInfoById(
        accessibilityProvider_,
        elementId,
        nodeInfo_);
}

std::shared_ptr<FocusRulesCheckNode> FocusStrategyOsalThird::GetCurrentCheckNode()
{
    CHECK_NULL_RETURN(nodeInfo_, nullptr);
    return std::make_shared<ThirdRulesCheckNode>(nodeInfo_, nodeInfo_->GetElementId(), accessibilityProvider_);
}

void FocusStrategyOsalThird::UpdateNextFocus(std::shared_ptr<FocusRulesCheckNode>& checkNode)
{
}

std::shared_ptr<FocusRulesCheckNode> FocusStrategyOsalThird::ChangeToRoot()
{
    auto rootNodeInfo = std::make_shared<ArkUI_AccessibilityElementInfo>();
    if (JsThirdProviderInteractionOperation::FindNativeInfoById(
        accessibilityProvider_, -1, rootNodeInfo)) {
            return std::make_shared<ThirdRulesCheckNode>(
                rootNodeInfo, rootNodeInfo->GetElementId(), accessibilityProvider_);
    }
    return nullptr;
}

bool FocusStrategyOsalThird::ChangeToEmbed(
    const std::shared_ptr<FocusRulesCheckNode>& resultNode, Accessibility::AccessibilityElementInfo& info)
{
    return false;
}

bool FocusStrategyOsalThird::UpdateElementInfo(
    const std::shared_ptr<FocusRulesCheckNode>& resultNode, Accessibility::AccessibilityElementInfo& info)
{
    CHECK_NULL_RETURN(resultNode, false);
    auto checkTarget = std::static_pointer_cast<ThirdRulesCheckNode>(resultNode);
    CHECK_NULL_RETURN(checkTarget, false);
    auto nativeInfo = checkTarget->GetNodeInfo();
    CHECK_NULL_RETURN(nativeInfo, false);
    AccessibilityThirdProviderUtils::TransformAccessibilityElementInfo(*nativeInfo, info);
    JsThirdProviderInteractionOperation::FillNodeConfig(config_, info);
    return true;
}
} // OHOS::Ace::Framework
