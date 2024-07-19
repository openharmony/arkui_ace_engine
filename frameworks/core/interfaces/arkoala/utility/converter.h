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
#include "core/components/common/properties/color.h"
#include "arkoala_api_generated.h"
#include "core/interfaces/arkoala/utility/generated/converter_generated.h"

namespace OHOS::Ace::NG::Converter
{
    template<typename To, typename From>
    To Convert(const From& src) = delete;

    template<>
    inline TextOverflow Convert(const Ark_TextOverflow& src) {
        return static_cast<TextOverflow>(src);
    }

    template<>
    inline TextHeightAdaptivePolicy Convert(const Ark_TextHeightAdaptivePolicy& src) {
        return static_cast<TextHeightAdaptivePolicy>(src);
    }

    template<>
    inline Ace::FontStyle Convert(const Ark_FontStyle& src) {
        return static_cast<Ace::FontStyle>(src);
    }

    template<>
    inline Color Convert(const int& src) {
        return Color(src);
    }

    template<>
    inline FontWeight Convert(const Ark_FontWeight& src) {
        return static_cast<FontWeight>(src);
    }

    template<>
    inline FontWeight Convert(const Ark_Number& src) {
        return src.tag == ARK_TAG_FLOAT32 ? static_cast<FontWeight>(src.f32) : static_cast<FontWeight>(src.i32);
    }

    template<>
    inline FontWeight Convert(const Ark_String& src) {
        return Framework::ConvertStrToFontWeight(src.chars);
    }

    template<>
    inline Dimension Convert(const Ark_Number& src) {
        return src.tag == Ark_Tag::ARK_TAG_INT32 ? 
            CalcDimension(src.i32, DimensionUnit::VP) : CalcDimension(src.i32, DimensionUnit::VP);
    }

    template<>
    inline Dimension Convert(const Ark_String& src) {
        char* result;
        return CalcDimension(std::strtod(src.chars, &result), DimensionUnit::VP);
    }

    template<>
    inline Dimension Convert(const Ark_Resource& src) {
        return CalcDimension();
    }

    template<>
    inline Dimension Convert(const Ark_Length& src) {
        return src.type == Ark_Tag::ARK_TAG_INT32 ? CalcDimension(src.value, (DimensionUnit)src.unit) : CalcDimension();
    }

    template<>
    inline int Convert(const Ark_Number& src) {
        return src.tag == ARK_TAG_FLOAT32 ? static_cast<int>(src.f32) : src.i32;
    }

    template<>
    inline float Convert(const Ark_Number& src) {
        return src.tag == ARK_TAG_FLOAT32 ? src.f32 : static_cast<float>(src.i32);
    }

    template<>
    inline int Convert(const Ark_IlluminatedType& src) {
        return static_cast<int>(src);
    }

    template<>
    inline ButtonRole Convert(const Ark_ButtonRole& src) {
        return static_cast<ButtonRole>(src);
    }

    template<>
    inline ButtonType Convert(const Ark_ButtonType& src) {
        return static_cast<ButtonType>(src);
    }

    template<>
    inline ButtonStyleMode Convert(const Ark_ButtonStyleMode& src) {
        return static_cast<ButtonStyleMode>(src);
    }

    template<>
    inline ControlSize Convert(const Ark_ControlSize& src) {
        return static_cast<ControlSize>(src);
    }

    template<>
    inline bool Convert(const Ark_Boolean& src) {
        return static_cast<bool>(src);
    }

    template<>
    inline std::vector<std::string> Convert(const Ark_String& src) {
        return { src.chars };
    }

    template<>
    inline std::vector<std::string> Convert(const Ark_CustomObject& src) {
        return {};
    }

    template<>
    inline Color Convert(const Ark_Number& src) {
        uint32_t value = src.tag == ARK_TAG_FLOAT32 ? static_cast<int>(src.f32) : src.i32;
        if (value <= 0xFFFFFF && value > 0) {
            return Color((unsigned) value + 0xFF000000U);
        }
        return Color(value);
    }

    template<>
    inline Color Convert(const Ark_String& src) {
        return Color::FromString(src.chars);
    }
    
    template<>
    inline Color Convert(const Ark_Resource& src) {
        LOGE("ARKOALA Converter -> Resource support (Color) is not implemented.");
        return Color();
    }

    template<>
    inline Ark_CharPtr Convert(const Ark_Resource& src) {
        LOGE("ARKOALA Converter -> Resource support (String) is not implemented.");
        return "ResUns";
    }

    template<>
    inline std::tuple<Ark_Float32, Ark_Int32> Convert(const Ark_Number& src) {
        Ark_Float32 value = src.tag == ARK_TAG_FLOAT32 ? src.f32 : src.i32;
        return std::make_tuple(value, static_cast<Ark_Int32>(DimensionUnit::VP));
    }

    // Implementation is in cpp
    Color Convert(const Ark_Color& src);
    void ParseDimension(const Ark_String &string, Ark_Length *result);

    template<>
    inline std::tuple<Ark_Float32, Ark_Int32> Convert(const Ark_String& src) {
        Ark_Length value;
        ParseDimension(src, &value);
        return std::make_tuple(value.value, value.unit);
    }

    template<>
    inline Ark_CharPtr Convert(const Ark_String& src) {
        return src.chars;
    }

    template<typename T, typename P>
    void AssignCast(std::optional<T>& dst, const P& src) {
        dst = Convert<T, P>(src);
    }

    template<typename T, typename P>
    void AssignLiteralTo(std::optional<T>& dst, const P& src) {
        AssignCast(dst, src);
    }

    template<typename T, typename P>
    void AssignUnionTo(std::optional<T>& dst, const P& src) {
        AssignLiteralTo(dst, src);
    }

    template<typename T, typename P>
    void AssignOptionalTo(std::optional<T>& dst, const P& src) {
        AssignUnionTo(dst, src);
    }

    template<typename T, typename P>
    void AssignTo(std::optional<T>& dst, const P& src) {
        AssignOptionalTo(dst, src);
    }

    template<typename To, typename From>
    std::optional<To> OptConvert(const From& value) {
        std::optional<To> opt;
        AssignTo(opt, value);
        return std::move(opt);
    }

    template<typename To, typename From>
    To ConvertOrDefault(const From& value, To defaultValue) {
        return OptConvert<To, From>(value).value_or(defaultValue);
    }
} // namespace OHOS::Ace::NG::Converter

#endif  // GENERATED_FOUNDATION_ACE_FRAMEWORKS_CORE_UTILITY_CONVERTER_H