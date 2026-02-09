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

#include "cj_badge_ffi.h"

#include "bridge/common/utils/utils.h"
#include "core/common/container.h"
#include "core/components/badge/badge_theme.h"
#include "core/components_ng/pattern/badge/badge_model_ng.h"
#include "bridge/cj_frontend/interfaces/cj_ffi/cj_view_abstract_ffi.h"

using namespace OHOS::Ace;
using namespace OHOS::Ace::Framework;

namespace {
const int ZERO = 0;
const int ONE = 1;
const int TWO = 2;
const int THREE = 3;
const int FOUR = 4;
const int FIVE = 5;
const int SIX = 6;
const int SEVEN = 7;
const int EIGHT = 8;
const int NINE = 9;
const int TEN = 10;
const int ELEVEN = 11;
const int TWELVE = 12;
const int THIRTEEN = 13;

const char* FontWeightIntNumberToStr(int32_t fontWeight)
{
    switch (fontWeight) {
        case ZERO:
            return "bold";
        case ONE:
            return "bolder";
        case TWO:
            return "lighter";
        case THREE:
            return "medium";
        case FOUR:
            return "regular";
        case FIVE:
            return "100";
        case SIX:
            return "200";
        case SEVEN:
            return "300";
        case EIGHT:
            return "400";
        case NINE:
            return "500";
        case TEN:
            return "600";
        case ELEVEN:
            return "700";
        case TWELVE:
            return "800";
        case THIRTEEN:
            return "900";
        default:
            return "400";
    }
}
BadgeParameters CreateBase(CJBadgeStyle style, int32_t position)
{
    BadgeParameters badgeParameters;
    badgeParameters.badgePosition = position;
    badgeParameters.badgeTextColor = Color(style.color);
    badgeParameters.badgeFontSize = Dimension(style.fontSize, DimensionUnit::VP);
    badgeParameters.badgeCircleSize = Dimension(style.badgeSize, DimensionUnit::VP);
    badgeParameters.badgeColor = Color(style.badgeColor);
    return badgeParameters;
}

BadgeParameters CreateBaseV2(CJBadgeStyleV2 style, int32_t position)
{
    BadgeParameters badgeParameters;
    badgeParameters.badgePosition = position;
    badgeParameters.badgeTextColor = Color(style.color);
    badgeParameters.badgeFontSize = Dimension(style.fontSize, DimensionUnit::VP);
    badgeParameters.badgeCircleSize = Dimension(style.badgeSize, DimensionUnit::VP);
    badgeParameters.badgeColor = Color(style.badgeColor);
    badgeParameters.badgeFontWeight = ConvertStrToFontWeight(FontWeightIntNumberToStr(style.fontWeight));
    badgeParameters.badgeBorderColor = Color(style.borderColor);
    badgeParameters.badgeBorderWidth = Dimension(style.borderWidth, DimensionUnit(style.borderWidthUnit));
    return badgeParameters;
}

BadgeParameters CreateBaseV3(CJBadgeStyleV3 style, int32_t position)
{
    BadgeParameters badgeParameters {};
    badgeParameters.badgePosition = position;
    badgeParameters.badgeTextColor = Color(style.color);
    
    auto badgeTheme = GetTheme<BadgeTheme>();
    if (!badgeTheme) {
        return badgeParameters;
    }
    
    auto fontSize = Dimension(style.fontSize, static_cast<DimensionUnit>(style.fontSizeUnit));
    if (fontSize.IsNonNegative() && fontSize.Unit() != DimensionUnit::PERCENT) {
        badgeParameters.badgeFontSize = fontSize;
    } else {
        badgeParameters.badgeFontSize = badgeTheme->GetBadgeFontSize();
    }
    
    auto badgeSize = Dimension(style.badgeSize, static_cast<DimensionUnit>(style.badgeSizeUnit));
    if (badgeSize.IsNonNegative() && badgeSize.Unit() != DimensionUnit::PERCENT) {
        badgeParameters.badgeCircleSize = badgeSize;
    } else {
        badgeParameters.badgeCircleSize = badgeTheme->GetBadgeCircleSize();
    }
    
    badgeParameters.badgeColor = Color(style.badgeColor);
    std::string fontWeight = style.fontWeight;
    badgeParameters.badgeFontWeight = ConvertStrToFontWeight(fontWeight);
    badgeParameters.badgeBorderColor = Color(style.borderColor);
    
    auto borderWidth = Dimension(style.borderWidth, DimensionUnit(style.borderWidthUnit));
    if (borderWidth.IsNonNegative() && borderWidth.Unit() != DimensionUnit::PERCENT) {
        badgeParameters.badgeBorderWidth = borderWidth;
    } else {
        badgeParameters.badgeBorderWidth = badgeTheme->GetBadgeBorderWidth();
    }
    
    auto outerBorderWidth = Dimension(style.outerBorderWidth, DimensionUnit(style.outerBorderWidthUnit));
    if (outerBorderWidth.IsNonNegative() && outerBorderWidth.Unit() != DimensionUnit::PERCENT) {
        badgeParameters.badgeOuterBorderWidth = outerBorderWidth;
    } else {
        badgeParameters.badgeOuterBorderWidth = badgeTheme->GetBadgeOuterBorderWidth();
    }
    
    badgeParameters.badgeOuterBorderColor = Color(style.outerBorderColor);
    badgeParameters.isEnableAutoAvoidance = style.enableAutoAvoidance;
    return badgeParameters;
}
} // namespace

extern "C" {
void FfiOHOSAceFrameworkBadgeCreate(int32_t count, CJBadgeStyle style, int32_t position, int32_t maxCount)
{
    BadgeParameters badgeParameters = CreateBase(style, position);
    badgeParameters.badgeCount = count;
    badgeParameters.badgeMaxCount = maxCount;
    BadgeModel::GetInstance()->Create(badgeParameters);
}

void FfiOHOSAceFrameworkBadgeCreateV2(int32_t count, CJBadgeStyleV2 style, int32_t position, int32_t maxCount)
{
    BadgeParameters badgeParameters = CreateBaseV2(style, position);
    badgeParameters.badgeCount = count;
    badgeParameters.badgeMaxCount = maxCount;
    if (Container::GreatOrEqualAPIVersion(PlatformVersion::VERSION_TWENTY_TWO)) {
        auto frameNode = BadgeModel::GetInstance()->CreateBadgeFrameNode();
        BadgeModel::GetInstance()->SetIsDefault(false, false);
        BadgeModel::GetInstance()->CreateByFrameNode(frameNode, badgeParameters);
    } else {
        BadgeModel::GetInstance()->Create(badgeParameters);
    }
}

void FfiOHOSAceFrameworkBadgeCreateV3(int32_t count, CJBadgeStyleV3 style, int32_t position, int32_t maxCount)
{
    BadgeParameters badgeParameters = CreateBaseV3(style, position);
    badgeParameters.badgeCount = count;
    badgeParameters.badgeMaxCount = maxCount;
    
    auto frameNode = BadgeModel::GetInstance()->CreateBadgeFrameNode();
    BadgeModel::GetInstance()->SetIsDefault(false, false);
    BadgeModel::GetInstance()->CreateByFrameNode(frameNode, badgeParameters);
}

void FfiOHOSAceFrameworkBadgeCreateText(const char* value, CJBadgeStyle style, int32_t position)
{
    BadgeParameters badgeParameters = CreateBase(style, position);
    badgeParameters.badgeValue = value;
    BadgeModel::GetInstance()->Create(badgeParameters);
}

void FfiOHOSAceFrameworkBadgeCreateTextV2(const char* value, CJBadgeStyleV2 style, int32_t position)
{
    BadgeParameters badgeParameters = CreateBaseV2(style, position);
    badgeParameters.badgeValue = value;
    if (Container::GreatOrEqualAPIVersion(PlatformVersion::VERSION_TWENTY_TWO)) {
        auto frameNode = BadgeModel::GetInstance()->CreateBadgeFrameNode();
        BadgeModel::GetInstance()->SetIsDefault(false, false);
        BadgeModel::GetInstance()->CreateByFrameNode(frameNode, badgeParameters);
    } else {
        BadgeModel::GetInstance()->Create(badgeParameters);
    }
}

void FfiOHOSAceFrameworkBadgeCreateTextV3(const char* value, CJBadgeStyleV3 style, int32_t position)
{
    BadgeParameters badgeParameters = CreateBaseV3(style, position);
    badgeParameters.badgeValue = value;

    auto frameNode = BadgeModel::GetInstance()->CreateBadgeFrameNode();
    BadgeModel::GetInstance()->SetIsDefault(false, false);
    BadgeModel::GetInstance()->CreateByFrameNode(frameNode, badgeParameters);
}
}
