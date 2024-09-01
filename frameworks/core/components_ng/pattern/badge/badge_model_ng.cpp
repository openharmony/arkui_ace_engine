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

#include "core/components_ng/pattern/badge/badge_model_ng.h"

#include "core/components/badge/badge_theme.h"
#include "core/components_ng/pattern/badge/badge_pattern.h"
#include "core/components_ng/pattern/text/text_pattern.h"

namespace OHOS::Ace::NG {
void BadgeModelNG::Create(BadgeParameters& badgeParameters)
{
    auto* stack = ViewStackProcessor::GetInstance();
    int32_t nodeId = (stack == nullptr ? 0 : stack->ClaimNodeId());
    ACE_LAYOUT_SCOPED_TRACE("Create[%s][self:%d]", V2::BADGE_ETS_TAG, nodeId);
    auto frameNode = FrameNode::GetOrCreateFrameNode(
        V2::BADGE_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<BadgePattern>(); });
    ViewStackProcessor::GetInstance()->Push(frameNode);

    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto badgeTheme = pipeline->GetTheme<BadgeTheme>();

    auto layoutProperty = frameNode->GetLayoutProperty<BadgeLayoutProperty>();
    layoutProperty->SetIsDefault(isDefaultFontSize_, isDefaultBadgeSize_);
    
    if (badgeParameters.badgeValue.has_value()) {
        layoutProperty->UpdateBadgeValue(badgeParameters.badgeValue.value());
    }
    if (badgeParameters.badgeCount.has_value()) {
        layoutProperty->UpdateBadgeCount(badgeParameters.badgeCount.value());
    }
    if (badgeParameters.badgeMaxCount.has_value()) {
        layoutProperty->UpdateBadgeMaxCount(badgeParameters.badgeMaxCount.value());
    } else {
        layoutProperty->UpdateBadgeMaxCount(badgeTheme->GetMaxCount());
    }

    if (badgeParameters.badgePosition.has_value()) {
        auto badgePosition = static_cast<BadgePosition>(badgeParameters.badgePosition.value());
        layoutProperty->UpdateBadgePosition(badgePosition);
    } else {
        layoutProperty->UpdateBadgePosition(badgeTheme->GetBadgePosition());
    }
    if (badgeParameters.badgePositionX.has_value()) {
        layoutProperty->UpdateBadgePositionX(badgeParameters.badgePositionX.value());
    } else {
        layoutProperty->UpdateBadgePositionX(badgeTheme->GetBadgePositionX());
    }
    if (badgeParameters.badgePositionY.has_value()) {
        layoutProperty->UpdateBadgePositionY(badgeParameters.badgePositionY.value());
    } else {
        layoutProperty->UpdateBadgePositionY(badgeTheme->GetBadgePositionY());
    }
    if (badgeParameters.isPositionXy.has_value()) {
        layoutProperty->UpdateIsPositionXy(badgeParameters.isPositionXy.value());
    } else {
        layoutProperty->UpdateIsPositionXy(badgeTheme->GetIsPositionXy());
    }
    UpdateBadgeStyle(badgeParameters, frameNode);
}

void BadgeModelNG::UpdateBadgeStyle(BadgeParameters& badgeParameters, const RefPtr<FrameNode>& frameNode)
{
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto badgeTheme = pipeline->GetTheme<BadgeTheme>();
    auto layoutProperty = frameNode->GetLayoutProperty<BadgeLayoutProperty>();
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
    }
    if (badgeParameters.badgeCircleSize.has_value()) {
        layoutProperty->UpdateBadgeCircleSize(badgeParameters.badgeCircleSize.value());
    }
    if (badgeParameters.badgeBorderColor.has_value()) {
        layoutProperty->UpdateBadgeBorderColor(badgeParameters.badgeBorderColor.value());
    } else {
        layoutProperty->UpdateBadgeBorderColor(badgeTheme->GetBadgeBorderColor());
    }
    if (badgeParameters.badgeBorderWidth.has_value()) {
        layoutProperty->UpdateBadgeBorderWidth(badgeParameters.badgeBorderWidth.value());
    } else {
        layoutProperty->UpdateBadgeBorderWidth(badgeTheme->GetBadgeBorderWidth());
    }
    if (badgeParameters.badgeFontWeight.has_value()) {
        layoutProperty->UpdateBadgeFontWeight(badgeParameters.badgeFontWeight.value());
    } else {
        layoutProperty->UpdateBadgeFontWeight(FontWeight::NORMAL);
    }
}

RefPtr<FrameNode> BadgeModelNG::CreateFrameNode(int32_t nodeId)
{
    auto frameNode = FrameNode::CreateFrameNode(V2::BADGE_ETS_TAG, nodeId, AceType::MakeRefPtr<BadgePattern>());
    CHECK_NULL_RETURN(frameNode, nullptr);
    return frameNode;
}

void BadgeModelNG::SetBadgeParam(
    FrameNode* frameNode, BadgeParameters& badgeParameters, bool isDefaultFontSize, bool isDefaultBadgeSize)
{
    CHECK_NULL_VOID(frameNode);
    auto pipeline = frameNode->GetContextRefPtr();
    CHECK_NULL_VOID(pipeline);
    auto badgeTheme = pipeline->GetTheme<BadgeTheme>();
    CHECK_NULL_VOID(badgeTheme);
    auto layoutProperty = frameNode->GetLayoutProperty<BadgeLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    layoutProperty->SetIsDefault(isDefaultFontSize, isDefaultBadgeSize);
    if (badgeParameters.badgeValue.has_value()) {
        layoutProperty->UpdateBadgeValue(badgeParameters.badgeValue.value());
    } else {
        layoutProperty->ResetBadgeValue();
    }
    if (badgeParameters.badgeCount.has_value()) {
        layoutProperty->UpdateBadgeCount(badgeParameters.badgeCount.value());
    }
    if (badgeParameters.badgeMaxCount.has_value()) {
        layoutProperty->UpdateBadgeMaxCount(badgeParameters.badgeMaxCount.value());
    } else {
        layoutProperty->UpdateBadgeMaxCount(badgeTheme->GetMaxCount());
    }

    if (badgeParameters.badgePosition.has_value()) {
        auto badgePosition = static_cast<BadgePosition>(badgeParameters.badgePosition.value());
        layoutProperty->UpdateBadgePosition(badgePosition);
    } else {
        layoutProperty->UpdateBadgePosition(badgeTheme->GetBadgePosition());
    }
    if (badgeParameters.badgePositionX.has_value()) {
        layoutProperty->UpdateBadgePositionX(badgeParameters.badgePositionX.value());
    } else {
        layoutProperty->UpdateBadgePositionX(badgeTheme->GetBadgePositionX());
    }
    if (badgeParameters.badgePositionY.has_value()) {
        layoutProperty->UpdateBadgePositionY(badgeParameters.badgePositionY.value());
    } else {
        layoutProperty->UpdateBadgePositionY(badgeTheme->GetBadgePositionY());
    }
    if (badgeParameters.isPositionXy.has_value()) {
        layoutProperty->UpdateIsPositionXy(badgeParameters.isPositionXy.value());
    } else {
        layoutProperty->UpdateIsPositionXy(badgeTheme->GetIsPositionXy());
    }
    UpdateBadgeStyle(badgeParameters, AceType::Claim(frameNode));
}
} // namespace OHOS::Ace::NG
