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

#ifndef FOUNDATION_ACE_ADAPTER_OHOS_OSAL_ACCESSIBILITY_FOCUS_MOVE_ACCESSIBILITY_FOCUS_MOVE_OSAL_NODE_H
#define FOUNDATION_ACE_ADAPTER_OHOS_OSAL_ACCESSIBILITY_FOCUS_MOVE_ACCESSIBILITY_FOCUS_MOVE_OSAL_NODE_H

#include "adapter/ohos/osal/accessibility/focus_move/accessibility_focus_accessibility_node_utils.h"
#include "adapter/ohos/osal/accessibility/focus_move/accessibility_focus_move_osal.h"

namespace OHOS::Ace::Framework {
class JsAccessibilityManager;

class FocusStrategyOsalNode : public FocusStrategyOsal {
    DECLARE_ACE_TYPE(FocusStrategyOsalNode, AceType);
public:
    FocusStrategyOsalNode(const RefPtr<JsAccessibilityManager>& jsAccessibilityManager)
        : FocusStrategyOsal(jsAccessibilityManager) {}
    ~FocusStrategyOsalNode() override = default;

    void InvailidElementInfo(Accessibility::AccessibilityElementInfo& info) override;
    bool UpdateOriginNodeInfo(int64_t elementId) override;
    std::shared_ptr<FocusRulesCheckNode> GetCurrentCheckNode() override;
    void UpdateNextFocus(std::shared_ptr<FocusRulesCheckNode>& checkNode) override;
    std::shared_ptr<FocusRulesCheckNode> ChangeToRoot() override;
    bool ChangeToEmbed(
        const std::shared_ptr<FocusRulesCheckNode>& resultNode, Accessibility::AccessibilityElementInfo& info) override;
    bool UpdateElementInfo(
        const std::shared_ptr<FocusRulesCheckNode>& resultNode, Accessibility::AccessibilityElementInfo& info) override;

private:
    WeakPtr<JsAccessibilityManager> jsAccessibilityManager_;
    WeakPtr<AccessibilityNode> node_;
};

} // OHOS::Ace::Framework
#endif // FOUNDATION_ACE_ADAPTER_OHOS_OSAL_ACCESSIBILITY_FOCUS_MOVE_ACCESSIBILITY_FOCUS_MOVE_OSAL_NODE_H
