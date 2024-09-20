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

#ifndef GENERATED_FOUNDATION_ACE_FRAMEWORKS_CORE_UTILITY_CONVERTER_H
#define GENERATED_FOUNDATION_ACE_FRAMEWORKS_CORE_UTILITY_CONVERTER_H

#pragma once

#include <cstdint>
#include <optional>
#include <vector>
#include <string>

#include "bridge/common/utils/utils.h"
#include "base/geometry/calc_dimension.h"
#include "base/geometry/dimension.h"
#include "core/components/common/layout/constants.h"
#include "core/components/common/properties/color.h"
#include "core/components/common/properties/text_style.h"
#include "core/components_ng/pattern/scrollable/scrollable_properties.h"
#include "core/components_ng/pattern/text_field/text_field_model.h"
#include "core/components_ng/property/calc_length.h"
#include "core/components_ng/property/measure_property.h"
#include "core/image/image_source_info.h"
#include "core/interfaces/native/node/node_api.h"
#include "arkoala_api_generated.h"
#include "core/interfaces/arkoala/utility/generated/converter_generated.h"
#include "ace_engine_types.h"

namespace OHOS::Ace::NG {
    template<typename T>
    std::optional<int32_t> EnumToInt(const std::optional<T>& src)
    {
        return src ? std::optional(static_cast<int32_t>(src.value())) : std::nullopt;
    }
} // namespace OHOS::Ace::NG

namespace OHOS::Ace::NG::Converter {
     //Allow conversion for Ark_Xxx type to same Ark_Xxx type
    template<typename T>
    void AssignTo(T& dst, const T& src)
    {
        dst = src;
    }

    template<typename T, typename... Types>
    void AssignTo(std::variant<Types...>& dst, const T& src)
    {
        dst = src;
    }

    template<typename To, typename From>
    To Convert(const From& src)
    {
        To result;
        AssignTo(result, src);
        return result;
    }

    template<typename T, typename P>
    void AssignCast(std::optional<T>& dst, const P& src)
    {
        dst = Convert<T, P>(src);
    }

    template<typename T, typename P>
    void AssignLiteralTo(std::optional<T>& dst, const P& src)
    {
        AssignCast(dst, src);
    }

    template<typename T, typename P>
    void AssignUnionTo(std::optional<T>& dst, const P& src)
    {
        AssignCast(dst, src);
    }

    template<typename T, typename P>
    void AssignOptionalTo(std::optional<T>& dst, const P& src)
    {
        AssignUnionTo(dst, src);
    }

    template<typename T, typename P>
    void AssignTo(std::optional<T>& dst, const P& src)
    {
        AssignOptionalTo(dst, src);
    }

    template<typename To, typename From>
    std::optional<To> OptConvert(const From& value)
    {
        std::optional<To> opt;
        AssignTo(opt, value);
        return std::move(opt);
    }

    template<typename To, typename From>
    To ConvertOrDefault(const From& value, To defaultValue)
    {
        return OptConvert<To, From>(value).value_or(defaultValue);
    }

    // Base converters
    template<>
    inline bool Convert(const Ark_Boolean& src)
    {
        return static_cast<bool>(src);
    }

    template<>
    inline std::string Convert(const Ark_String& src)
    {
        if (src.chars == nullptr) {
            return "";
        }
        return src.chars;
    }

    template<>
    inline Ark_CharPtr Convert(const Ark_String& src)
    {
        return src.chars;
    }

    template<>
    inline std::vector<std::string> Convert(const Ark_String& src)
    {
        return { Convert<std::string>(src) };
    }

    template<>
    inline int Convert(const Ark_Number& src)
    {
        return src.tag == ARK_TAG_FLOAT32 ? static_cast<int>(src.f32) : src.i32;
    }

    template<>
    inline float Convert(const Ark_Number& src)
    {
        return src.tag == ARK_TAG_FLOAT32 ? src.f32 : static_cast<float>(src.i32);
    }

    // Implementation is in cpp
    Ark_TouchObject ConvertTouchInfo(OHOS::Ace::TouchLocationInfo &info);

    // Converter implementations
    template<>
    inline TextOverflow Convert(const Ark_TextOverflow& src)
    {
        return static_cast<TextOverflow>(src);
    }

    template<>
    inline TextHeightAdaptivePolicy Convert(const Ark_TextHeightAdaptivePolicy& src)
    {
        return static_cast<TextHeightAdaptivePolicy>(src);
    }

    template<>
    inline Ace::FontStyle Convert(const Ark_FontStyle& src)
    {
        return static_cast<Ace::FontStyle>(src);
    }

    template<>
    inline FontWeight Convert(const Ark_String& src)
    {
        return Framework::ConvertStrToFontWeight(src.chars);
    }

    template<>
    inline Dimension Convert(const Ark_String& src)
    {
        return Dimension::FromString(src.chars);
    }

    template<>
    inline void AssignTo(std::optional<FontWeight>& dst, const Ark_Number& src)
    {
        auto str = std::to_string(Convert<int>(src));
        if (auto [parseOk, val] = StringUtils::ParseFontWeight(str); parseOk) {
            dst = val;
        } else {
            dst.reset();
        }
    }

    template<>
    inline void AssignTo(std::optional<FontWeight>& dst, const Ark_String& src)
    {
        if (auto [parseOk, val] = StringUtils::ParseFontWeight(src.chars); parseOk) {
            dst = val;
        } else {
            dst.reset();
        }
    }

    template<>
    inline Dimension Convert(const Ark_Resource& src)
    {
        return Dimension();
    }

    template<>
    inline Dimension Convert(const Ark_Length& src)
    {
        return src.type == Ark_Tag::ARK_TAG_RESOURCE ?
               Dimension() : Dimension(src.value, static_cast<DimensionUnit>(src.unit));
    }

    template<>
    inline Dimension Convert(const Ark_Number& src)
    {
        return Dimension(Converter::Convert<float>(src), DimensionUnit::VP);
    }

    template<>
    inline int Convert(const Ark_IlluminatedType& src)
    {
        return static_cast<int>(src);
    }

    template<>
    inline ImageInterpolation Convert(const Ark_ImageInterpolation& src)
    {
        return static_cast<ImageInterpolation>(src);
    }

    template<>
    inline DynamicRangeMode Convert(const Ark_DynamicRangeMode& src)
    {
        return static_cast<DynamicRangeMode>(src);
    }

    template<>
    inline ImageRenderMode Convert(const Ark_ImageRenderMode& src)
    {
        return static_cast<ImageRenderMode>(src);
    }

    template<>
    inline ImageRepeat Convert(const Ark_ImageRepeat& src)
    {
        return static_cast<ImageRepeat>(src);
    }

    template<>
    inline ImageFit Convert(const Ark_ImageFit& src)
    {
        return static_cast<ImageFit>(src);
    }

    template<>
    inline std::vector<std::string> Convert(const Ark_Resource& src)
    {
        return {};
    }

    template<>
    inline std::vector<std::string> Convert(const Ark_CustomObject& src)
    {
        return {};
    }

    template<>
    inline Color Convert(const Ark_Number& src)
    {
        uint32_t value = Convert<int>(src);
        if (value <= 0xFFFFFF && value > 0) {
            return Color((unsigned) value + 0xFF000000U);
        }
        return Color(value);
    }

    template<>
    inline Color Convert(const Ark_String& src)
    {
        return Color::FromString(src.chars);
    }

    bool ParseColorFromArkResource(const Ark_Resource &res, Color &result);

    template<>
    inline Color Convert(const Ark_Resource& src)
    {
        Color color;
        if (!ParseColorFromArkResource(src, color)) {
            LOGE("ARKOALA Converter -> Resource support (Color) failed.");
        }
        return color;
    }

    template<>
    inline Ark_CharPtr Convert(const Ark_Resource& src)
    {
        LOGE("ARKOALA Converter -> Resource support (String) is not implemented.");
        return "ResUns";
    }

    template<>
    inline float Convert(const Ark_Resource& src)
    {
        LOGE("ARKOALA Converter -> Resource support (float) is not implemented.");
        return 1.0f;
    }

    template<>
    inline CalcLength Convert(const Ark_Length& src)
    {
        if (src.type == Ark_Tag::ARK_TAG_RESOURCE) {
            LOGE("Convert [Ark_Length] to [CalcLength] is not supported.");
            return CalcLength();
        }
        auto unit = static_cast<OHOS::Ace::DimensionUnit>(src.unit);
        auto value = src.value;
        if (unit == OHOS::Ace::DimensionUnit::PERCENT) {
            value /= 100.0f; // percent is normalized [0..1]
        }
        return CalcLength(value, unit);
    }

    template<>
    inline EdgesParam Convert(const Ark_Edges& src)
    {
        EdgesParam edges;
        edges.left = OptConvert<Dimension>(src.left);
        edges.top = OptConvert<Dimension>(src.top);
        edges.right = OptConvert<Dimension>(src.right);
        edges.bottom = OptConvert<Dimension>(src.bottom);
        return edges;
    }

    template<>
    inline PaddingProperty Convert(const Ark_Length& src)
    {
        PaddingProperty padding;
        auto value = OptConvert<CalcLength>(src);
        padding.left = value;
        padding.top = value;
        padding.right = value;
        padding.bottom = value;
        return padding;
    }

    template<>
    inline PaddingProperty Convert(const Ark_LocalizedPadding& src)
    {
        LOGE("Convert [Ark_LocalizedPadding] to [PaddingProperty] is not supported.");
        PaddingProperty padding;
        return padding;
    }

    struct ImageResource {
        uint32_t type;
        std::string bundleName;
        std::string moduleName;
        int32_t id;
        std::vector<std::string> params;
    };

    ImageSourceInfo Convert(Ark_NativePointer node, const Type_ImageInterface_setImageOptions_Arg0& value);
    ImageSourceInfo Convert(Ark_NativePointer node, const Type_ImageAttribute_alt_Arg0& value);
    template<> std::string Convert(const Ark_Resource& resource);
    ImageResource Convert(const Ark_Resource& value);

    template<>
    inline RadioStyle Convert(const Ark_RadioStyle& src)
    {
        RadioStyle style;
        style.checkedBackgroundColor = Converter::OptConvert<Color>(src.checkedBackgroundColor);
        style.uncheckedBorderColor = Converter::OptConvert<Color>(src.uncheckedBorderColor);
        style.indicatorColor = Converter::OptConvert<Color>(src.indicatorColor);
        return style;
    }

    template<>
    inline Dimension Convert(const Ark_CustomObject& src)
    {
        LOGE("Convert [Ark_CustomObject] to [Dimension] is not supported");
        return Dimension();
    }

    template<>
    inline FontMetaData Convert(const Ark_Font& src)
    {
        return {
            OptConvert<Dimension>(src.size),
            OptConvert<FontWeight>(src.weight),
        };
    }

    template<>
    inline ArkCaretStyle Convert(const Ark_CaretStyle& src)
    {
        ArkCaretStyle caretStyle;
        caretStyle.color = OptConvert<Color>(src.color);
        caretStyle.width = OptConvert<Dimension>(src.width);
        return caretStyle;
    }

    template<> Font Convert(const Ark_Font& src);

    template<>
    inline TextDecorationOptions Convert(const Ark_TextDecorationOptions& src)
    {
        TextDecorationOptions options;
        options.textDecoration = OptConvert<TextDecoration>(src.type);
        options.color = OptConvert<Color>(src.color);
        options.textDecorationStyle = OptConvert<TextDecorationStyle>(src.style);
        return options;
    }

    // Enums specializations
    template<> void AssignCast(std::optional<Alignment>& dst, const Ark_Alignment& src);
    template<> void AssignCast(std::optional<ButtonRole>& dst, const Ark_ButtonRole& src);
    template<> void AssignCast(std::optional<ControlSize>& dst, const Ark_ControlSize& src);
    template<> void AssignCast(std::optional<ButtonType>& dst, const Ark_ButtonType& src);
    template<> void AssignCast(std::optional<ButtonStyleMode>& dst, const Ark_ButtonStyleMode& src);
    template<> void AssignCast(std::optional<Color>& dst, const enum Ark_Color& src);
    template<> void AssignCast(std::optional<FontWeight>& dst, const Ark_FontWeight& src);
    template<> void AssignCast(std::optional<ForegroundColorStrategy>& dst, const Ark_ColoringStrategy& src);
    template<> void AssignCast(std::optional<LineCap>& dst, const Ark_LineCapStyle& src);
    template<> void AssignCast(std::optional<ShadowColorStrategy>& dst, const Ark_ColoringStrategy& src);
    template<> void AssignCast(std::optional<ScrollState>& dst, const Ark_ScrollState& src);
    template<> void AssignCast(std::optional<FlexDirection>& dst, const Ark_GridDirection& src);
    template<> void AssignCast(std::optional<EdgeEffect>& dst, const Ark_EdgeEffect& src);
    template<> void AssignCast(std::optional<TextDecorationStyle>& dst, const Ark_TextDecorationStyle& src);
    template<> void AssignCast(std::optional<TextDecoration>& dst, const Ark_TextDecorationType& src);
    template<> void AssignCast(std::optional<TextAlign>& dst, const Ark_TextAlign& src);
    template<> void AssignCast(std::optional<TextInputAction>& dst, const Ark_EnterKeyType& src);
    template<> void AssignCast(std::optional<TextInputType>& dst, const Ark_TextAreaType& src);
    template<> void AssignCast(std::optional<TextDeleteDirection>& dst, const Ark_TextDeleteDirection& src);
    template<> void AssignCast(std::optional<CopyOptions>& dst, const Ark_CopyOptions& src);
    template<> void AssignCast(std::optional<TextContentType>& dst, const Ark_ContentType& src);

    template<>
    inline ItemDragInfo Convert(const Ark_ItemDragInfo& src)
    {
        ItemDragInfo itemDragInfo;
        itemDragInfo.SetX(Convert<float>(src.x));
        itemDragInfo.SetY(Convert<float>(src.y));
        return itemDragInfo;
    }
} // namespace OHOS::Ace::NG::Converter

#endif  // GENERATED_FOUNDATION_ACE_FRAMEWORKS_CORE_UTILITY_CONVERTER_H
