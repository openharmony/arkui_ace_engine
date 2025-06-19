/*
 * Copyright (c) 2024-2025 Huawei Device Co., Ltd.
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
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/generated/interface/node_api.h"
#include "core/components/badge/badge_theme.h"
#include "core/interfaces/native/utility/validators.h"
#include "core/components_ng/base/frame_node.h"
#include "core/interfaces/native/utility/converter.h"
#include "arkoala_api_generated.h"

namespace OHOS::Ace::NG {
namespace {
    using UnionBadgeOptions = std::variant<Ark_BadgePosition, Ark_Position>;
struct Position {
    std::optional<int> badgePosition;
    std::optional<bool> isPositionXy = false;
    std::optional<Dimension> badgePositionX;
    std::optional<Dimension> badgePositionY;
};
struct Style {
    std::optional<Color> badgeColor;
    std::optional<Color> badgeTextColor;
    std::optional<Color> badgeBorderColor;
    std::optional<Dimension> badgeFontSize;
    std::optional<Dimension> badgeCircleSize;
    std::optional<Dimension> badgeBorderWidth;
    std::optional<FontWeight> badgeFontWeight;
};
}

namespace Converter {
template<>
void AssignCast(std::optional<Position>& dst, const Ark_Position& src)
{
    dst->isPositionXy = true;
    dst->badgePositionX = Converter::OptConvert<Dimension>(src.x);
    dst->badgePositionY = Converter::OptConvert<Dimension>(src.y);
    Validator::ValidateNonNegative(dst->badgePositionX);
    Validator::ValidateNonNegative(dst->badgePositionY);
}

template<>
void AssignCast(std::optional<Position>& dst, const Ark_BadgePosition& src)
{
    switch (src) {
        case ARK_BADGE_POSITION_RIGHT_TOP:
        case ARK_BADGE_POSITION_RIGHT:
        case ARK_BADGE_POSITION_LEFT:
            dst->isPositionXy = false;
            dst->badgePosition = src;
            break;
        default: LOGE("Unexpected enum value in Ark_BadgePosition: %{public}d", src);
    }
}

template<>
Style Convert(const Ark_BadgeStyle& src)
{
    Style dst;
    dst.badgeColor = Converter::OptConvert<Color>(src.badgeColor);
    dst.badgeTextColor = Converter::OptConvert<Color>(src.color);
    dst.badgeBorderColor = Converter::OptConvert<Color>(src.borderColor);
    dst.badgeFontSize = Converter::OptConvert<Dimension>(src.fontSize);
    dst.badgeCircleSize = Converter::OptConvert<Dimension>(src.badgeSize);
    dst.badgeBorderWidth = Converter::OptConvert<Dimension>(src.borderWidth);
    dst.badgeFontWeight = Converter::OptConvert<FontWeight>(src.fontWeight);
    Validator::ValidateNonNegative(dst.badgeFontSize);
    Validator::ValidateNonNegative(dst.badgeCircleSize);
    Validator::ValidateNonNegative(dst.badgeBorderWidth);
    Validator::ValidateNonPercent(dst.badgeFontSize);
    Validator::ValidateNonPercent(dst.badgeCircleSize);
    Validator::ValidateNonPercent(dst.badgeBorderWidth);
    return dst;
}

template<typename T>
BadgeParameters ConverterHelper(const T& src)
{
    BadgeParameters dst;
    auto position = Converter::OptConvert<Position>(src.position);
    Style style = Converter::Convert<Style>(src.style);

    dst.isPositionXy = position->isPositionXy;
    dst.badgePositionX = position->badgePositionX;
    dst.badgePositionY = position->badgePositionY;
    dst.badgePosition = position->badgePosition;

    dst.badgeColor = style.badgeColor;
    dst.badgeTextColor = style.badgeTextColor;
    dst.badgeBorderColor = style.badgeBorderColor;
    dst.badgeFontSize = style.badgeFontSize;
    dst.badgeCircleSize = style.badgeCircleSize;
    dst.badgeBorderWidth = style.badgeBorderWidth;
    dst.badgeFontWeight = style.badgeFontWeight;
    return dst;
}

template<>
BadgeParameters Convert(const Ark_BadgeParamWithString& src)
{
    BadgeParameters dst = ConverterHelper(src);
    dst.badgeValue = Converter::Convert<std::string>(src.value);
    return dst;
}

template<>
BadgeParameters Convert(const Ark_BadgeParamWithNumber& src)
{
    BadgeParameters dst = ConverterHelper(src);
    dst.badgeCount = Converter::Convert<int>(src.count);
    dst.badgeMaxCount = Converter::OptConvert<int>(src.maxCount);
    return dst;
}
} // namespace OHOS::Ace::NG::Converter
} // namespace OHOS::Ace::NG

namespace OHOS::Ace::NG::GeneratedModifier {
namespace BadgeModifier {
Ark_NativePointer ConstructImpl(Ark_Int32 id,
                                Ark_Int32 flags)
{
    auto frameNode = BadgeModelNG::CreateFrameNode(id);
    CHECK_NULL_RETURN(frameNode, nullptr);
    frameNode->IncRefCount();
    return AceType::RawPtr(frameNode);
}
} // BadgeModifier
namespace BadgeInterfaceModifier {
template<typename T>
void SetBadgeParamBase(Ark_NativePointer node, const T* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);

    BadgeParameters badgeParameters = Converter::Convert<BadgeParameters>(*value);
    bool isDefaultFontSize = !badgeParameters.badgeFontSize.has_value();
    bool isDefaultBadgeSize = !badgeParameters.badgeCircleSize.has_value();

    BadgeModelNG::SetBadgeParam(frameNode, badgeParameters, isDefaultFontSize, isDefaultBadgeSize);
}

void SetBadgeOptions0Impl(Ark_NativePointer node,
                          const Ark_BadgeParamWithNumber* value)
{
    SetBadgeParamBase(node, value);
}
void SetBadgeOptions1Impl(Ark_NativePointer node,
                          const Ark_BadgeParamWithString* value)
{
    SetBadgeParamBase(node, value);
}
} // BadgeInterfaceModifier
const GENERATED_ArkUIBadgeModifier* GetBadgeModifier()
{
    static const GENERATED_ArkUIBadgeModifier ArkUIBadgeModifierImpl {
        BadgeModifier::ConstructImpl,
        BadgeInterfaceModifier::SetBadgeOptions0Impl,
        BadgeInterfaceModifier::SetBadgeOptions1Impl,
    };
    return &ArkUIBadgeModifierImpl;
}

}
