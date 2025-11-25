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

#ifndef FOUNDATION_ACE_ADAPTER_OHOS_OSAL_ACCESSIBILITY_FOCUS_MOVE_ACCESSIBILITY_FOCUS_MOVE_OSAL_THIRD_H
#define FOUNDATION_ACE_ADAPTER_OHOS_OSAL_ACCESSIBILITY_FOCUS_MOVE_ACCESSIBILITY_FOCUS_MOVE_OSAL_THIRD_H

#include "adapter/ohos/osal/accessibility/focus_move/accessibility_focus_move_osal.h"
#include "adapter/ohos/osal/js_third_provider_interaction_operation.h"
#include "frameworks/core/accessibility/accessibility_provider.h"

namespace OHOS::Ace::Framework {
class JsAccessibilityManager;

class FocusStrategyOsalThird : public FocusStrategyOsal {
    DECLARE_ACE_TYPE(FocusStrategyOsalThird, AceType);
public:
    FocusStrategyOsalThird(const RefPtr<JsAccessibilityManager>& jsAccessibilityManager,
        const RefPtr<AccessibilityProvider>& accessibilityProvider, const NodeConfig& config)
        : FocusStrategyOsal(jsAccessibilityManager), jsAccessibilityManager_(jsAccessibilityManager),
        accessibilityProvider_(accessibilityProvider), config_(config)
        {}
    ~FocusStrategyOsalThird() override = default;

    void InvailidElementInfo(Accessibility::AccessibilityElementInfo& info) override;
    bool UpdateOriginNodeInfo(int64_t elementId) override;
    std::shared_ptr<FocusRulesCheckNode> GetCurrentCheckNode() override;
    void UpdateNextFocus(std::shared_ptr<FocusRulesCheckNode>& checkNode) override;
    std::shared_ptr<FocusRulesCheckNode> ChangeToRoot() override;
    bool ChangeToEmbed(
        const std::shared_ptr<FocusRulesCheckNode>& resultNode, Accessibility::AccessibilityElementInfo& info) override;
    bool UpdateElementInfo(
        const std::shared_ptr<FocusRulesCheckNode>& resultNode, Accessibility::AccessibilityElementInfo& info) override;
    bool CanSendHoverWithTargetIdByReadableRules(
        int64_t currentId, int64_t& targetId);
private:
    WeakPtr<JsAccessibilityManager> jsAccessibilityManager_;
    WeakPtr<AccessibilityProvider> accessibilityProvider_;
    std::shared_ptr<ArkUI_AccessibilityElementInfo> nodeInfo_ = std::make_shared<ArkUI_AccessibilityElementInfo>();
    NodeConfig config_;
};

} // OHOS::Ace::Framework
#endif // FOUNDATION_ACE_ADAPTER_OHOS_OSAL_ACCESSIBILITY_FOCUS_MOVE_ACCESSIBILITY_FOCUS_MOVE_OSAL_THIRD_H
