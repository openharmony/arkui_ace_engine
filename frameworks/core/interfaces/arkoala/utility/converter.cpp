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

#include "core/interfaces/native/node/node_api.h"
#include "converter.h"

namespace OHOS::Ace::NG::Converter {

constexpr int32_t OFFSET_0 = 0;
constexpr int32_t OFFSET_1 = 1;
constexpr int32_t OFFSET_2 = 2;

void ParseDimension(const Ark_String &string, Ark_Length *result)
{
    char *suffixPtr = nullptr;
    float value = std::strtof(string.chars, &suffixPtr);

    if (!suffixPtr || suffixPtr == string.chars) {
        // not a numeric value
        result->unit = static_cast<Ark_Int32>(DimensionUnit::NONE);
        return;
    }
    result->value = value;

    DimensionUnit unit;
    if (suffixPtr[OFFSET_0] == '\0' || (suffixPtr[OFFSET_0] == 'v' && suffixPtr[OFFSET_1] == 'p')) {
        unit = DimensionUnit::VP;
    } else if (suffixPtr[OFFSET_0] == '%') {
        unit = DimensionUnit::PERCENT;
    } else if (suffixPtr[OFFSET_0] == 'p' && suffixPtr[OFFSET_1] == 'x') {
        unit = DimensionUnit::PX;
    } else if (suffixPtr[OFFSET_0] == 'l' && suffixPtr[OFFSET_1] == 'p' && suffixPtr[OFFSET_2] == 'x') {
        unit = DimensionUnit::LPX;
    } else if (suffixPtr[OFFSET_0] == 'f' && suffixPtr[OFFSET_1] == 'p') {
        unit = DimensionUnit::FP;
    } else {
        unit = DimensionUnit::NONE;
    }
    result->unit = static_cast<Ark_Int32>(unit);
}

uint32_t ColorAlphaAdapt(uint32_t origin)
{
    constexpr uint32_t COLOR_ALPHA_OFFSET = 24;
    constexpr uint32_t COLOR_ALPHA_VALUE = 0xFF000000;

    uint32_t result = origin;
    if ((origin >> COLOR_ALPHA_OFFSET) == 0) {
        result = origin | COLOR_ALPHA_VALUE;
    }
    return result;
}

bool ParseColorFromArkResource(const Ark_Resource &res, Color &result)
{
    constexpr int32_t ERROR_COLOR_ID = -1;

    auto themeConstants = NodeModifier::GetThemeConstants(0, res.bundleName.chars, res.moduleName.chars);
    CHECK_NULL_RETURN(themeConstants, false);

    CHECK_NULL_RETURN(res.id.tag == ARK_TAG_INT32, false);
    auto resId = res.id.i32;
    if (resId == ERROR_COLOR_ID) {
        CHECK_NULL_RETURN(res.params.value.array, false);
        std::string colorName = res.params.value.array[0].chars;
        result = themeConstants->GetColorByName(colorName);
        return true;
    }

    CHECK_NULL_RETURN(res.type.tag == ARK_TAG_INT32, false);
    auto type = res.type.i32;
    if (type == static_cast<int32_t>(NodeModifier::ResourceType::STRING)) {
        auto value = themeConstants->GetString(resId);
        return Color::ParseColorString(value, result);
    }
    if (type == static_cast<int32_t>(NodeModifier::ResourceType::INTEGER)) {
        auto value = themeConstants->GetInt(resId);
        result = Color(ColorAlphaAdapt(value));
        return true;
    }
    if (type == static_cast<int32_t>(NodeModifier::ResourceType::COLOR)) {
        result = themeConstants->GetColor(resId);
        return true;
    }
    return false;
}
} // namespace OHOS::Ace::NG::Converter
