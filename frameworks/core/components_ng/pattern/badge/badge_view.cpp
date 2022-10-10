/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
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

#include "core/components_ng/pattern/badge/badge_view.h"

#include "core/components/badge/badge_theme.h"
#include "core/components/common/properties/color.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/view_abstract.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/badge/badge_pattern.h"
#include "core/components_ng/pattern/text/text_pattern.h"
#include "core/components_v2/inspector/inspector_constants.h"

namespace OHOS::Ace::NG {

void BadgeView::Pop()
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    if (frameNode->GetChildren().empty()) {
        return;
    }

    auto lastFrameNode = AceType::DynamicCast<FrameNode>(frameNode->GetChildren().back());
    CHECK_NULL_VOID(lastFrameNode);
    std::string textNodeName("text");
    if (lastFrameNode->GetNodeName() != textNodeName) {
        auto* stack = ViewStackProcessor::GetInstance();
        int32_t textNodeId = (stack == nullptr ? 0 : stack->ClaimNodeId());
        lastFrameNode = FrameNode::GetOrCreateFrameNode(
            V2::TEXT_ETS_TAG, textNodeId, []() { return AceType::MakeRefPtr<TextPattern>(); });
        CHECK_NULL_VOID(lastFrameNode);
        lastFrameNode->MountToParent(frameNode);
        lastFrameNode->SetNodeName(textNodeName);
    }
    auto textLayoutProperty = lastFrameNode->GetLayoutProperty<TextLayoutProperty>();
    CHECK_NULL_VOID(textLayoutProperty);
    auto layoutProperty = frameNode->GetLayoutProperty<BadgeLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    auto badgeCount = layoutProperty->GetBadgeCount();
    auto badgeValue = layoutProperty->GetBadgeValue();
    if (badgeCount.has_value()) {
        auto maxCount = 99;
        auto badgeMaxCount = layoutProperty->GetBadgeMaxCount();
        if (badgeMaxCount.has_value()) {
            maxCount = badgeMaxCount.value();
        }
        if (badgeCount.value() > maxCount) {
            badgeCount.value() = maxCount;
            textLayoutProperty->UpdateContent(std::to_string(badgeCount.value()) + "+");
        } else {
            textLayoutProperty->UpdateContent(std::to_string(badgeCount.value()));
        }
    } else {
        if (!badgeValue.value().empty()) {
            textLayoutProperty->UpdateContent(badgeValue.value());
        } else {
            textLayoutProperty->UpdateContent(" ");
        }
    }

    auto badgeTextColor = layoutProperty->GetBadgeTextColor();
    if (badgeTextColor.has_value()) {
        textLayoutProperty->UpdateTextColor(badgeTextColor.value());
    }
    auto badgeFontSize = layoutProperty->GetBadgeFontSize();
    if (badgeFontSize.has_value()) {
        textLayoutProperty->UpdateFontSize(badgeFontSize.value());
    }
    lastFrameNode->MarkModifyDone();
}

void BadgeView::Create(BadgeParameters& badgeParameters)
{
    auto* stack = ViewStackProcessor::GetInstance();
    int32_t nodeId = (stack == nullptr ? 0 : stack->ClaimNodeId());
    auto frameNode = FrameNode::GetOrCreateFrameNode(
        V2::BADGE_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<BadgePattern>(); });
    ViewStackProcessor::GetInstance()->Push(frameNode);

    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto badgeTheme = pipeline->GetTheme<BadgeTheme>();

    auto layoutProperty = frameNode->GetLayoutProperty<BadgeLayoutProperty>();
    if (badgeParameters.badgeValue.has_value()) {
        layoutProperty->UpdateBadgeValue(badgeParameters.badgeValue.value());
    }
    if (badgeParameters.badgeCount.has_value()) {
        layoutProperty->UpdateBadgeCount(badgeParameters.badgeCount.value());
        if (badgeParameters.badgeMaxCount.has_value()) {
            layoutProperty->UpdateBadgeMaxCount(badgeParameters.badgeMaxCount.value());
        }
    }

    if (badgeParameters.badgePosition.has_value()) {
        BadgeLayoutProperty::BadgePosition badgePosition =
            static_cast<BadgeLayoutProperty::BadgePosition>(badgeParameters.badgePosition.value());
        layoutProperty->SetBadgePosition(badgePosition);
    }

    if (badgeParameters.badgeColor.has_value()) {
        layoutProperty->UpdateBadgeColor(badgeParameters.badgeColor.value());
    } else {
        layoutProperty->UpdateBadgeColor(badgeTheme->GetBadgeColor());
    }

    if (badgeParameters.badgeTextColor.has_value()) {
        layoutProperty->UpdateBadgeTextColor(badgeParameters.badgeTextColor.value());
    } else {
        layoutProperty->UpdateBadgeTextColor(badgeTheme->GetBadgeTextColor());
    }

    if (badgeParameters.badgeFontSize.has_value()) {
        layoutProperty->UpdateBadgeFontSize(badgeParameters.badgeFontSize.value());
    } else {
        layoutProperty->UpdateBadgeFontSize(badgeTheme->GetBadgeFontSize());
    }

    if (badgeParameters.badgeCircleSize.has_value()) {
        layoutProperty->UpdateBadgeCircleSize(badgeParameters.badgeCircleSize.value());
    }
}

} // namespace OHOS::Ace::NG
