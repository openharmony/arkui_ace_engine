/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "core/components_ng/pattern/badge/badge_model_ng.h"
#include "core/interfaces/arkoala/utility/converter.h"
#include "core/interfaces/arkoala/generated/interface/node_api.h"
#include "core/components/badge/badge_theme.h"
#include "arkoala_api_generated.h"


namespace OHOS::Ace::NG::Converter {

std::optional<Dimension> ValidateNonNegative(std::optional<Dimension> value, bool isPercentEnabled = false)
{
    if (value.has_value()) {
        bool isValidUnits = value.value().Unit() != DimensionUnit::INVALID;
        bool isPositive = value.value().ConvertToVp() >= 0;
        bool isValidPercent = isPercentEnabled || value.value().Unit() != DimensionUnit::PERCENT;
        if (isPositive && isValidUnits && isValidPercent) {
            return value;
        }
    }
    return std::optional<Dimension>();
}

template<typename T>
BadgeParameters ConvertHelper(const T& src)
{
    BadgeParameters dst;
    Ark_BadgeStyle style = src.style;
    Opt_Union_BadgePosition_Position position = src.position;

    if (position.tag != Ark_Tag::ARK_TAG_UNDEFINED) {
        if (position.value.selector == 0) {
            dst.isPositionXy = false;
            Ark_BadgePosition value0 = position.value.value0;
            dst.isPositionXy = false;
            dst.badgePosition = value0;

        } else if (position.value.selector == 1) {
            dst.isPositionXy = true;
            Ark_Position value1 = position.value.value1;
            dst.badgePositionX = ValidateNonNegative(Converter::OptConvert<Dimension>(value1.x), true);
            dst.badgePositionY = ValidateNonNegative(Converter::OptConvert<Dimension>(value1.y), true);
        }
    }

    dst.badgeColor = Converter::OptConvert<Color>(style.badgeColor);
    dst.badgeTextColor = Converter::OptConvert<Color>(style.color);
    dst.badgeBorderColor = Converter::OptConvert<Color>(style.borderColor);
    dst.badgeFontSize = ValidateNonNegative(Converter::OptConvert<Dimension>(style.fontSize));
    dst.badgeCircleSize = ValidateNonNegative(Converter::OptConvert<Dimension>(style.badgeSize));
    dst.badgeBorderWidth = ValidateNonNegative(Converter::OptConvert<Dimension>(style.borderWidth));
    dst.badgeFontWeight = Converter::OptConvert<FontWeight>(style.fontWeight);
    return dst;
}
template<>
BadgeParameters Convert(const Ark_BadgeParamWithString& src)
{
    BadgeParameters dst = ConvertHelper(src);
    dst.badgeValue = Converter::Convert<std::string>(src.value);
    return dst;
}
template<>
BadgeParameters Convert(const Ark_BadgeParamWithNumber& src)
{
    BadgeParameters dst = ConvertHelper(src);
    dst.badgeCount = Converter::Convert<int>(src.count);
    dst.badgeMaxCount = Converter::OptConvert<int>(src.maxCount);
    return dst;
}

} // namespace OHOS::Ace::NG::Converter

namespace OHOS::Ace::NG::GeneratedModifier {
namespace BadgeInterfaceModifier {

template<typename T>
void SetBadgeParamBase(Ark_NativePointer node, const T* value)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);

    BadgeParameters badgeParameters = Converter::Convert<BadgeParameters>(*value);
    bool isDefaultFontSize = !badgeParameters.badgeFontSize.has_value();
    bool isDefaultBadgeSize = !badgeParameters.badgeCircleSize.has_value();

    BadgeModelNG::SetBadgeParam(frameNode, badgeParameters, isDefaultFontSize, isDefaultBadgeSize);
}

void SetBadgeOptions0Impl(Ark_NativePointer node, const Ark_BadgeParamWithNumber* value)
{
    SetBadgeParamBase(node, value);
}
void SetBadgeOptions1Impl(Ark_NativePointer node, const Ark_BadgeParamWithString* value)
{
    SetBadgeParamBase(node, value);
}
} // namespace BadgeInterfaceModifier
const GENERATED_ArkUIBadgeModifier* GetBadgeModifier()
{
    static const GENERATED_ArkUIBadgeModifier ArkUIBadgeModifierImpl {
        BadgeInterfaceModifier::SetBadgeOptions0Impl,
        BadgeInterfaceModifier::SetBadgeOptions1Impl,
    };
    return &ArkUIBadgeModifierImpl;
}

} // namespace OHOS::Ace::NG::GeneratedModifier
