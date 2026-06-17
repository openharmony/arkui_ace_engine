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

#include "ui/view/components/badge.h"

#include "interfaces/inner_api/ace_kit/src/view/frame_node_impl.h"
#include "ui/base/referenced.h"

#include "core/components_ng/pattern/badge/badge_data.h"
#include "core/components_ng/pattern/badge/badge_model_ng.h"
#include "core/interfaces/native/node/badge_modifier.h"
#include "core/common/resource/resource_parse_utils.h"
#include "core/components/badge/badge_theme.h"

namespace OHOS::Ace::Kit {

namespace {
void SetBadgeBaseParam(BadgeParameters& badgeParameters, BadgeParametersKit& kitParameters)
{
    badgeParameters.badgeValue = kitParameters.badgeValue;
    badgeParameters.badgeCount = kitParameters.badgeCount;
    badgeParameters.badgeMaxCount = kitParameters.badgeMaxCount;
    badgeParameters.isPositionXy = kitParameters.isPositionXy;
    badgeParameters.badgeColor = kitParameters.badgeColor;
    badgeParameters.badgeTextColor = kitParameters.badgeTextColor;
    badgeParameters.badgeBorderColor = kitParameters.badgeBorderColor;
    badgeParameters.badgeOuterBorderColor = kitParameters.badgeOuterBorderColor;
    badgeParameters.badgeFontSize = kitParameters.badgeFontSize;
    badgeParameters.badgeCircleSize = kitParameters.badgeCircleSize;
    badgeParameters.badgeBorderWidth = kitParameters.badgeBorderWidth;
    badgeParameters.badgeOuterBorderWidth = kitParameters.badgeOuterBorderWidth;
    if (kitParameters.badgeFontWeight.has_value()) {
        badgeParameters.badgeFontWeight = static_cast<FontWeight>(kitParameters.badgeFontWeight.value());
    }
    badgeParameters.isEnableAutoAvoidance = kitParameters.isEnableAutoAvoidance;

    badgeParameters.resourceBadgeValueObject = kitParameters.resourceBadgeValueObject;
    badgeParameters.resourceColorObject = kitParameters.resourceColorObject;
    badgeParameters.resourceBadgeColorObject = kitParameters.resourceBadgeColorObject;
    badgeParameters.resourceBorderColorObject = kitParameters.resourceBorderColorObject;
    badgeParameters.resourceOuterBorderColorObject = kitParameters.resourceOuterBorderColorObject;
    badgeParameters.resourceFontWeightObject = kitParameters.resourceFontWeightObject;
    badgeParameters.resourceBadgeSizeObject = kitParameters.resourceBadgeSizeObject;
    badgeParameters.resourceFontSizeObject = kitParameters.resourceFontSizeObject;
    badgeParameters.resourceBorderWidthObject = kitParameters.resourceBorderWidthObject;
    badgeParameters.resourceOuterBorderWidthObject = kitParameters.resourceOuterBorderWidthObject;

    if (badgeParameters.isPositionXy) {
        badgeParameters.badgePositionX = kitParameters.badgePositionX;
        badgeParameters.badgePositionY = kitParameters.badgePositionY;
        badgeParameters.resourceBadgePositionXObject = kitParameters.resourceBadgePositionXObject;
        badgeParameters.resourceBadgePositionYObject = kitParameters.resourceBadgePositionYObject;
    } else {
        badgeParameters.badgePosition = kitParameters.badgePosition;
    }
}

RefPtr<NG::FrameNode> GetFrameNode(const RefPtr<FrameNode>& node)
{
    auto frameNodeImpl = AceType::DynamicCast<FrameNodeImpl>(node);
    CHECK_NULL_RETURN(frameNodeImpl, nullptr);
    auto aceFrameNode = frameNodeImpl->GetAceNode();
    CHECK_NULL_RETURN(aceFrameNode, nullptr);
    return aceFrameNode;
}
} // namespace

Badge::Badge(const RefPtr<FrameNode>& node)
{
    node_ = node;
}

Badge::~Badge() = default;

RefPtr<Badge> Badge::Create(const RefPtr<FrameNode>& node)
{
    return Referenced::MakeRefPtr<Badge>(node);
}

void Badge::SetBadgeParams(BadgeParametersKit& badgeParameters, bool isDefaultFontSize,
    bool isDefaultBadgeSize)
{
    auto badgeNode = GetFrameNode(node_);
    CHECK_NULL_VOID(badgeNode);
    BadgeParameters param;
    SetBadgeBaseParam(param, badgeParameters);
    auto badgeModifier = NG::NodeModifier::GetBadgeCustomModifier();
    CHECK_NULL_VOID(badgeModifier);
    badgeModifier->setBadgeParam(badgeNode.GetRawPtr(), param, isDefaultFontSize, isDefaultBadgeSize);
    if (SystemProperties::ConfigChangePerform()) {
        UpdateBadgeUserFlags(badgeParameters);
        if (badgeParameters.resourceBadgeColorObject) {
            HandleBadgeColor(badgeParameters.resourceBadgeColorObject);
        }
        if (badgeParameters.resourceColorObject) {
            HandleBadgeTextColor(badgeParameters.resourceColorObject);
        }
    }
}

void Badge::UpdateBadgeUserFlags(BadgeParametersKit& badgeParameters)
{
    auto badgeNode = GetFrameNode(node_);
    CHECK_NULL_VOID(badgeNode);
    auto badgeLayoutProperty = badgeNode->GetLayoutPropertyPtr<NG::BadgeLayoutProperty>();
    CHECK_NULL_VOID(badgeLayoutProperty);
    badgeLayoutProperty->UpdateBadgePositionXByuser(badgeParameters.badgePositionX ||
        badgeParameters.resourceBadgePositionXObject);
    badgeLayoutProperty->UpdateBadgePositionYByuser(badgeParameters.badgePositionY ||
        badgeParameters.resourceBadgePositionYObject);
    badgeLayoutProperty->UpdateBadgeTextColorByuser(badgeParameters.badgeTextColor ||
        badgeParameters.resourceColorObject);
    badgeLayoutProperty->UpdateBadgeFontSizeByuser(badgeParameters.badgeFontSize ||
        badgeParameters.resourceFontSizeObject);
    badgeLayoutProperty->UpdateBadgeCircleSizeByuser(badgeParameters.badgeCircleSize ||
        badgeParameters.resourceBadgeSizeObject);
    badgeLayoutProperty->UpdateBadgeColorByuser(badgeParameters.badgeColor ||
        badgeParameters.resourceBadgeColorObject);
    badgeLayoutProperty->UpdateBadgeBorderWidthByuser(badgeParameters.badgeBorderWidth ||
        badgeParameters.resourceBorderWidthObject);
    badgeLayoutProperty->UpdateBadgeBorderColorByuser(badgeParameters.badgeBorderColor ||
        badgeParameters.resourceBorderColorObject);
    badgeLayoutProperty->UpdateBadgeOuterBorderWidthByuser(badgeParameters.badgeOuterBorderWidth ||
        badgeParameters.resourceOuterBorderWidthObject);
    badgeLayoutProperty->UpdateBadgeOuterBorderColorByuser(badgeParameters.badgeOuterBorderColor ||
        badgeParameters.resourceOuterBorderColorObject);
}

void Badge::HandleBadgeColor(const RefPtr<ResourceObject>& resourceObject)
{
    auto badgeNode = GetFrameNode(node_);
    CHECK_NULL_VOID(badgeNode);
    auto badgePattern = badgeNode->GetPattern<NG::BadgePattern>();
    CHECK_NULL_VOID(badgePattern);
    const std::string key = "badge.Color";
    badgePattern->RemoveResObj(key);
    if (!resourceObject) {
        return;
    }
    auto updateFunc = [weakPattern = AceType::WeakClaim(AceType::RawPtr(badgePattern)),
        weakNode = AceType::WeakClaim(AceType::RawPtr(badgeNode))](
        const RefPtr<ResourceObject>& resObj, bool isFirstLoad = false) {
        auto badgePattern = weakPattern.Upgrade();
        CHECK_NULL_VOID(badgePattern);
        auto frameNode = weakNode.Upgrade();
        CHECK_NULL_VOID(frameNode);
        Color result;
        bool state = ResourceParseUtils::ParseResColor(resObj, result);
        if (!state) {
            auto badgeTheme = frameNode->GetTheme<BadgeTheme>(true);
            result = badgeTheme->GetBadgeColor();
        }
        auto customModifier = NG::NodeModifier::GetBadgeCustomModifier();
        if (customModifier) {
            customModifier->updateBadgeColor(badgePattern, result, isFirstLoad);
        }
    };
    badgePattern->AddResObj("badge.Color", resourceObject, std::move(updateFunc));
}

void Badge::HandleBadgeTextColor(const RefPtr<ResourceObject>& resourceObject)
{
    auto badgeNode = GetFrameNode(node_);
    CHECK_NULL_VOID(badgeNode);
    auto badgePattern = badgeNode->GetPattern<NG::BadgePattern>();
    CHECK_NULL_VOID(badgePattern);
    const std::string key = "badge.textColor";
    badgePattern->RemoveResObj(key);
    if (!resourceObject) {
        return;
    }
    auto updateFunc = [weakPattern = AceType::WeakClaim(AceType::RawPtr(badgePattern)),
        weakNode = AceType::WeakClaim(AceType::RawPtr(badgeNode))](
        const RefPtr<ResourceObject>& resObj, bool isFirstLoad = false) {
        auto badgePattern = weakPattern.Upgrade();
        CHECK_NULL_VOID(badgePattern);
        auto frameNode = weakNode.Upgrade();
        CHECK_NULL_VOID(frameNode);
        Color result;
        bool state = ResourceParseUtils::ParseResColor(resObj, result);
        if (!state) {
            auto badgeTheme = frameNode->GetTheme<BadgeTheme>(true);
            result = badgeTheme->GetBadgeTextColor();
        }
        auto customModifier = NG::NodeModifier::GetBadgeCustomModifier();
        if (customModifier) {
            customModifier->updateColor(badgePattern, result, isFirstLoad);
        }
    };
    badgePattern->AddResObj("badge.textColor", resourceObject, std::move(updateFunc));
}

} // namespace OHOS::Ace::Kit
