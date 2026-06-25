/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_ADAPTER_OHOS_OSAL_ACCESSIBILITY_FOCUS_MOVE_ACCESSIBILITY_FOCUS_VIRTUAL_NODE_UTILS_H
#define FOUNDATION_ACE_ADAPTER_OHOS_OSAL_ACCESSIBILITY_FOCUS_MOVE_ACCESSIBILITY_FOCUS_VIRTUAL_NODE_UTILS_H

#pragma once
#include <string>
#include <list>

#include "base/memory/ace_type.h"
#include "base/utils/macros.h"
#include "hilog/log.h"
#include "adapter/ohos/osal/accessibility/focus_move/accessibility_focus_strategy.h"
#include "frameworks/core/accessibility/accessibility_utils.h"
#include "frameworks/core/accessibility/utils/accessibility_manager_utils.h"

namespace OHOS::Ace::Framework {

class VirtualAccessibilityNodeRulesCheckNode : public FocusRulesCheckNode {
public:
    VirtualAccessibilityNodeRulesCheckNode(
        const RefPtr<NG::VirtualAccessibilityNode>& node,
        int64_t accessibilityId,
        const WeakPtr<NG::FrameNode>& hostFrameNode = nullptr)
        : FocusRulesCheckNode(accessibilityId), weakNode_(node), hostFrameNode_(hostFrameNode)
    {
    }

    ~VirtualAccessibilityNodeRulesCheckNode() override = default;

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

    bool IsVirtualNode() override
    {
        return true;
    }

    RefPtr<NG::VirtualAccessibilityNode> GetAccessibilityNode()
    {
        return weakNode_.Upgrade();
    }

    RefPtr<NG::FrameNode> GetHostFrameNode()
    {
        return hostFrameNode_.Upgrade();
    }

private:
    template<typename T>
    std::vector<std::shared_ptr<T>> GetChildrenTemplate();
    WeakPtr<NG::VirtualAccessibilityNode> weakNode_;
    WeakPtr<NG::FrameNode> hostFrameNode_;
};

} // namespace OHOS::Ace::Framework

#endif