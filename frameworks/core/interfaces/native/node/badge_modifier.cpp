/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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
#include "core/interfaces/native/node/badge_modifier.h"

#include "core/components_ng/pattern/badge/badge_data.h"
#include "core/components_ng/pattern/badge/badge_model_ng.h"

namespace OHOS::Ace::NG {
namespace {
void SetBadgeBaseParam(BadgeParameters& badgeParameters, const ArkUIBadgeParam& style)
{
    badgeParameters.isPositionXy = style.isPositionXy;
    if (style.isPositionXy) {
        badgeParameters.badgePositionX =
            Dimension(style.positionX.value, static_cast<DimensionUnit>(style.positionX.units));
        badgeParameters.badgePositionY =
            Dimension(style.positionY.value, static_cast<DimensionUnit>(style.positionY.units));
    } else {
        badgeParameters.badgePosition = style.position;
    }
    badgeParameters.badgeColor = Color(style.badgeColor);
    badgeParameters.badgeTextColor = Color(style.textColor);
    badgeParameters.badgeBorderColor = Color(style.borderColor);
    badgeParameters.badgeFontWeight = static_cast<FontWeight>(style.fontWeight);
    badgeParameters.badgeFontSize = Dimension(style.fontSize.value, static_cast<DimensionUnit>(style.fontSize.units));
    badgeParameters.badgeCircleSize =
        Dimension(style.badgeSize.value, static_cast<DimensionUnit>(style.badgeSize.units));
    badgeParameters.badgeBorderWidth =
        Dimension(style.borderWidth.value, static_cast<DimensionUnit>(style.borderWidth.units));
}
} // namespace

void SetBadgeParamWithNumber(ArkUINodeHandle node, const struct ArkUIBadgeParam* style, ArkUI_Int32 count,
    ArkUI_Bool countHasValue, ArkUI_Int32 maxCount)
{
    CHECK_NULL_VOID(style);
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    BadgeParameters badgeParameters;
    SetBadgeBaseParam(badgeParameters, *style);
    if (countHasValue) {
        badgeParameters.badgeCount = count;
    } else {
        badgeParameters.badgeCount = std::optional<int>();
    }
    badgeParameters.badgeMaxCount = maxCount;
    BadgeModelNG::SetBadgeParam(frameNode, badgeParameters, style->isDefaultFontSize, style->isDefaultBadgeSize);
}

void SetBadgeParamWithString(ArkUINodeHandle node, const struct ArkUIBadgeParam* style, ArkUI_CharPtr value)
{
    CHECK_NULL_VOID(style);
    CHECK_NULL_VOID(value);
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    BadgeParameters badgeParameters;
    SetBadgeBaseParam(badgeParameters, *style);
    badgeParameters.badgeValue = value;
    BadgeModelNG::SetBadgeParam(frameNode, badgeParameters, style->isDefaultFontSize, style->isDefaultBadgeSize);
}

namespace NodeModifier {
const ArkUIBadgeModifier* GetBadgeModifier()
{
    CHECK_INITIALIZED_FIELDS_BEGIN(); // don't move this line
    static const ArkUIBadgeModifier modifier = {
        .setBadgeParameters = nullptr,
        .setBadgeValue = nullptr,
        .setBadgeCount = nullptr,
        .setBadgeMaxCount = nullptr,
        .setBadgeFontWeight = nullptr,
        .setBadgeParamWithNumber = SetBadgeParamWithNumber,
        .setBadgeParamWithString = SetBadgeParamWithString,
    };
    CHECK_INITIALIZED_FIELDS_END(modifier, 0, 0, 0); // don't move this line
    return &modifier;
}
} // namespace NodeModifier
} // namespace OHOS::Ace::NG
