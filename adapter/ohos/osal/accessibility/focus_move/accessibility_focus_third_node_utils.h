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

#ifndef FOUNDATION_ACE_ADAPTER_OHOS_OSAL_ACCESSIBILITY_FOCUS_MOVE_ACCESSIBILITY_FOCUS_THIRD_NODE_UTILS_H
#define FOUNDATION_ACE_ADAPTER_OHOS_OSAL_ACCESSIBILITY_FOCUS_MOVE_ACCESSIBILITY_FOCUS_THIRD_NODE_UTILS_H

#include "adapter/ohos/osal/accessibility/focus_move/accessibility_focus_strategy.h"
#include "frameworks/core/accessibility/native_interface_accessibility_impl.h"

namespace OHOS::Ace {
class AccessibilityProvider;
}

namespace OHOS::Ace::Framework {

class ThirdRulesCheckNode : public FocusRulesCheckNode {
public:
    ThirdRulesCheckNode(std::shared_ptr<ArkUI_AccessibilityElementInfo> nodeInfo,
        int64_t accessibilityId,
        const WeakPtr<AccessibilityProvider>& accessibilityProvider);

    ~ThirdRulesCheckNode() override = default;

    bool GetPropText(Accessibility::PropValue& value) override;

    bool GetPropHintText(Accessibility::PropValue& value) override;

    bool GetPropDesc(Accessibility::PropValue& value) override;

    bool GetPropAccessibilityText(Accessibility::PropValue& value) override;

    bool GetPropType(Accessibility::PropValue& value) override;

    bool GetPropAccessibilityLevel(Accessibility::PropValue& value) override;

    bool GetPropAccessibilityGroup(Accessibility::PropValue& value) override;

    bool GetPropIsEnable(Accessibility::PropValue& value) override;

    bool GetPropChildrenCount(Accessibility::PropValue& value) override;

    bool GetPropActionNames(Accessibility::PropValue& value) override;

    std::vector<std::shared_ptr<Accessibility::ReadableRulesNode>> GetChildren() override;

    std::shared_ptr<Accessibility::ReadableRulesNode> GetParent() override;

    std::vector<std::shared_ptr<FocusRulesCheckNode>> GetAceChildren() override;

    std::shared_ptr<FocusRulesCheckNode> GetAceParent() override;

    bool IsInChildTree() override
    {
        return true;
    }

    std::shared_ptr<ArkUI_AccessibilityElementInfo>& GetNodeInfo()
    {
        return nodeInfo_;
    }

private:
    template<typename T>
    std::vector<std::shared_ptr<T>> GetChildrenTemplate();
    std::shared_ptr<ArkUI_AccessibilityElementInfo> nodeInfo_;
    WeakPtr<AccessibilityProvider> accessibilityProvider_;
};
} // OHOS::Ace::Framework
#endif // FOUNDATION_ACE_ADAPTER_OHOS_OSAL_ACCESSIBILITY_FOCUS_MOVE_ACCESSIBILITY_FOCUS_THIRD_NODE_UTILS_H
