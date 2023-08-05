/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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

#include "accessibility_property.h"

#include "core/components_ng/base/frame_node.h"

namespace OHOS::Ace::NG {
constexpr uint64_t ACTIONS = std::numeric_limits<uint64_t>::max();
std::unordered_set<AceAction> AccessibilityProperty::GetSupportAction() const
{
    static const AceAction allActions[] = {
        AceAction::ACTION_NONE,
        AceAction::GLOBAL_ACTION_BACK,
        AceAction::CUSTOM_ACTION,
        AceAction::ACTION_CLICK,
        AceAction::ACTION_LONG_CLICK,
        AceAction::ACTION_SCROLL_FORWARD,
        AceAction::ACTION_SCROLL_BACKWARD,
        AceAction::ACTION_FOCUS,
        AceAction::ACTION_CLEAR_FOCUS,
        AceAction::ACTION_ACCESSIBILITY_FOCUS,
        AceAction::ACTION_CLEAR_ACCESSIBILITY_FOCUS,
        AceAction::ACTION_NEXT_AT_MOVEMENT_GRANULARITY,
        AceAction::ACTION_PREVIOUS_AT_MOVEMENT_GRANULARITY,
        AceAction::ACTION_SET_TEXT,
        AceAction::ACTION_COPY,
        AceAction::ACTION_PASTE,
        AceAction::ACTION_CUT,
        AceAction::ACTION_SELECT,
        AceAction::ACTION_SET_SELECTION,
        AceAction::ACTION_CLEAR_SELECTION,
    };

    std::unordered_set<AceAction> supportActions;
    if (supportActions_ == 0) {
        return supportActions;
    }

    auto finalSupportActions = supportActions_ & ACTIONS;
    for (auto action : allActions) {
        if ((finalSupportActions & (1UL << static_cast<uint32_t>(action))) != 0) {
            supportActions.emplace(action);
        }
    }
    return supportActions;
}

void GetFrameNodeChildren(const RefPtr<UINode>& uiNode, std::list<RefPtr<FrameNode>>& children)
{
    if (AceType::InstanceOf<FrameNode>(uiNode)) {
        auto frameNode = AceType::DynamicCast<FrameNode>(uiNode);
        if (!frameNode->IsInternal()) {
            children.emplace_back(frameNode);
            return;
        }
    } else {
        for (const auto& frameChild : uiNode->GetChildren()) {
            GetFrameNodeChildren(frameChild, children);
        }
    }
}

std::string AccessibilityProperty::GetAccessibilityText(bool isParentGroup)
{
    std::string text = "";
    auto frameNode = host_.Upgrade();
    CHECK_NULL_RETURN(frameNode, "");
    if (GetAccessibilityLevel() != "yes") {
        return text;
    }
    if (accessibilityText_.has_value()) {
        text = accessibilityText_.value();
    } else {
        text = GetText();
    }
    std::list<RefPtr<FrameNode>> children;
    if ((text.empty() && isParentGroup) || (IsAccessibilityGroup() && text.empty())) {
        for (const auto& item : frameNode->GetChildren()) {
            GetFrameNodeChildren(item, children);
        }
        for (const auto& iter : children) {
            auto frameChild = AceType::DynamicCast<FrameNode>(iter);
            if (frameChild) {
                auto childText =
                    frameChild->GetAccessibilityProperty<AccessibilityProperty>()->GetAccessibilityText(true);
                if (!text.empty() && !childText.empty()) {
                    text += ", ";
                }
                if (!childText.empty()) {
                    text += childText;
                }
            }
        }
    }
    return text;
}
} // namespace OHOS::Ace::NG
