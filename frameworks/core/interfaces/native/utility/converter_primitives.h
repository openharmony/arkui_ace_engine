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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_INTERFACES_NATIVE_UTILITY_CONVERTER_PRIMITIVES_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_INTERFACES_NATIVE_UTILITY_CONVERTER_PRIMITIVES_H

#include <optional>
#include <string>

#include "arkoala_api_generated.h"
#include "base/utils/utf_helper.h"
#include "core/components/common/layout/constants.h"

namespace OHOS::Ace::NG::Converter {
inline std::string ConvertArkString(const Ark_String& src)
{
    if (src.chars == nullptr || src.length == 0) {
        return "";
    }
    constexpr uint16_t utf16Bom = 0xFEFF;
    const char16_t* data = reinterpret_cast<const char16_t*>(src.chars);
    if (src.length >= sizeof(data[0]) && data[0] == utf16Bom) {
        ++data;
        return UtfUtils::Str16ToStr8(std::u16string(data, src.length - sizeof(data[0])));
    }
    return std::string(src.chars, src.length);
}

inline std::optional<PresetFillType> ConvertArkPresetFillType(const Ark_PresetFillType& src)
{
    switch (src) {
        case ARK_PRESET_FILL_TYPE_BREAKPOINT_DEFAULT:
            return PresetFillType::BREAKPOINT_DEFAULT;
        case ARK_PRESET_FILL_TYPE_BREAKPOINT_SM1MD2LG3:
            return PresetFillType::BREAKPOINT_SM1MD2LG3;
        case ARK_PRESET_FILL_TYPE_BREAKPOINT_SM2MD3LG5:
            return PresetFillType::BREAKPOINT_SM2MD3LG5;
        default:
            return std::nullopt;
    }
}

inline std::optional<PresetFillType> ConvertArkPresetFillType(const Opt_PresetFillType& src)
{
    if (src.tag == INTEROP_TAG_UNDEFINED) {
        return std::nullopt;
    }
    return ConvertArkPresetFillType(src.value);
}
} // namespace OHOS::Ace::NG::Converter

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_INTERFACES_NATIVE_UTILITY_CONVERTER_PRIMITIVES_H
