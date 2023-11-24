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

#include "core/common/rosen/rosen_convert_helper.h"

#include "base/utils/system_properties.h"

namespace OHOS::Ace {
namespace {
int32_t GetKeyOfBlurStyle(BlurStyle style, ThemeColorMode colorMode)
{
    constexpr static int32_t shiftNumber = 8; // can hold 2^8 blurStyle enums
    return (static_cast<int32_t>(colorMode) << shiftNumber) + static_cast<int32_t>(style);
}
} // namespace
MATERIAL_BLUR_STYLE GetRosenBlurStyleValue(const BlurStyleOption& option)
{
    ThemeColorMode colorMode = option.colorMode;
    if (option.colorMode == ThemeColorMode::SYSTEM) {
        colorMode = SystemProperties::GetColorMode() == ColorMode::DARK ? ThemeColorMode::DARK : ThemeColorMode::LIGHT;
    }
    const static std::map<std::pair<BlurStyle, ThemeColorMode>, MATERIAL_BLUR_STYLE> mp = {
        { { BlurStyle::THIN, ThemeColorMode::LIGHT }, MATERIAL_BLUR_STYLE::STYLE_CARD_THIN_LIGHT },
        { { BlurStyle::THIN, ThemeColorMode::DARK }, MATERIAL_BLUR_STYLE::STYLE_CARD_THIN_DARK },
        { { BlurStyle::REGULAR, ThemeColorMode::LIGHT }, MATERIAL_BLUR_STYLE::STYLE_CARD_LIGHT },
        { { BlurStyle::REGULAR, ThemeColorMode::DARK }, MATERIAL_BLUR_STYLE::STYLE_CARD_DARK },
        { { BlurStyle::THICK, ThemeColorMode::LIGHT }, MATERIAL_BLUR_STYLE::STYLE_CARD_THICK_LIGHT },
        { { BlurStyle::THICK, ThemeColorMode::DARK }, MATERIAL_BLUR_STYLE::STYLE_CARD_THICK_DARK },
        { { BlurStyle::BACKGROUND_THIN, ThemeColorMode::LIGHT }, MATERIAL_BLUR_STYLE::STYLE_BACKGROUND_SMALL_LIGHT },
        { { BlurStyle::BACKGROUND_THIN, ThemeColorMode::DARK }, MATERIAL_BLUR_STYLE::STYLE_BACKGROUND_SMALL_DARK },
        { { BlurStyle::BACKGROUND_REGULAR, ThemeColorMode::LIGHT },
            MATERIAL_BLUR_STYLE::STYLE_BACKGROUND_MEDIUM_LIGHT },
        { { BlurStyle::BACKGROUND_REGULAR, ThemeColorMode::DARK }, MATERIAL_BLUR_STYLE::STYLE_BACKGROUND_MEDIUM_DARK },
        { { BlurStyle::BACKGROUND_THICK, ThemeColorMode::LIGHT }, MATERIAL_BLUR_STYLE::STYLE_BACKGROUND_LARGE_LIGHT },
        { { BlurStyle::BACKGROUND_THICK, ThemeColorMode::DARK }, MATERIAL_BLUR_STYLE::STYLE_BACKGROUND_LARGE_DARK },
        { { BlurStyle::BACKGROUND_ULTRA_THICK, ThemeColorMode::LIGHT },
            MATERIAL_BLUR_STYLE::STYLE_BACKGROUND_XLARGE_LIGHT },
        { { BlurStyle::BACKGROUND_ULTRA_THICK, ThemeColorMode::DARK },
            MATERIAL_BLUR_STYLE::STYLE_BACKGROUND_XLARGE_DARK },
    };
    auto iter = mp.find({ option.blurStyle, colorMode });
    return iter != mp.end() ? iter->second : MATERIAL_BLUR_STYLE::NO_MATERIAL;
}

std::optional<BlurParameter> GetBlurParameter(BlurStyle style, ThemeColorMode colorMode)
{
    const static std::unordered_map<int32_t, BlurParameter> blurParams = {
        { GetKeyOfBlurStyle(BlurStyle::THIN, ThemeColorMode::LIGHT),
            BlurParameter { 23.0f, 1.05f, 1.05f, Color(0x33ffffff) } },
        { GetKeyOfBlurStyle(BlurStyle::REGULAR, ThemeColorMode::LIGHT),
            BlurParameter { 50.0f, 1.8f, 1.2f, Color(0x99fafafa) } },
        { GetKeyOfBlurStyle(BlurStyle::THICK, ThemeColorMode::LIGHT),
            BlurParameter { 57.0f, 1.2f, 1.1f, Color(0x8cffffff) } },
        { GetKeyOfBlurStyle(BlurStyle::THIN, ThemeColorMode::DARK),
            BlurParameter { 75.0f, 1.35f, 1.0f, Color(0x6b1a1a1a) } },
        { GetKeyOfBlurStyle(BlurStyle::REGULAR, ThemeColorMode::DARK),
            BlurParameter { 50.0f, 2.15f, 1.0f, Color(0xd11f1f1f) } },
        { GetKeyOfBlurStyle(BlurStyle::THICK, ThemeColorMode::DARK),
            BlurParameter { 75.0f, 2.15f, 1.0f, Color(0xd11f1f1f) } },
        { GetKeyOfBlurStyle(BlurStyle::BACKGROUND_THIN, ThemeColorMode::LIGHT),
            BlurParameter { 23.0f, 1.05f, 1.0f, Color(0x33808080) } },
        { GetKeyOfBlurStyle(BlurStyle::BACKGROUND_REGULAR, ThemeColorMode::LIGHT),
            BlurParameter { 29.0f, 1.1f, 1.0f, Color(0x33808080) } },
        { GetKeyOfBlurStyle(BlurStyle::BACKGROUND_THICK, ThemeColorMode::LIGHT),
            BlurParameter { 57.0f, 1.2f, 1.0f, Color(0x33808080) } },
        { GetKeyOfBlurStyle(BlurStyle::BACKGROUND_ULTRA_THICK, ThemeColorMode::LIGHT),
            BlurParameter { 120.0f, 1.3f, 1.0f, Color(0x4c666666) } },
        { GetKeyOfBlurStyle(BlurStyle::BACKGROUND_THIN, ThemeColorMode::DARK),
            BlurParameter { 15.0f, 1.1f, 1.0f, Color(0x800d0d0d) } },
        { GetKeyOfBlurStyle(BlurStyle::BACKGROUND_REGULAR, ThemeColorMode::DARK),
            BlurParameter { 55.0f, 1.15f, 1.0f, Color(0x800d0d0d) } },
        { GetKeyOfBlurStyle(BlurStyle::BACKGROUND_THICK, ThemeColorMode::DARK),
            BlurParameter { 75.0f, 1.5f, 1.0f, Color(0x800d0d0d) } },
        { GetKeyOfBlurStyle(BlurStyle::BACKGROUND_ULTRA_THICK, ThemeColorMode::DARK),
            BlurParameter { 130.0f, 1.3f, 1.0f, Color(0x800d0d0d) } },
        { GetKeyOfBlurStyle(BlurStyle::COMPONENT_ULTRA_THIN, ThemeColorMode::LIGHT),
            BlurParameter { 120.0f, 1.1f, 1.2f, Color(0x19ffffff) } },
        { GetKeyOfBlurStyle(BlurStyle::COMPONENT_THIN, ThemeColorMode::LIGHT),
            BlurParameter { 80.0f, 1.4f, 1.2f, Color(0x66ffffff) } },
        { GetKeyOfBlurStyle(BlurStyle::COMPONENT_REGULAR, ThemeColorMode::LIGHT),
            BlurParameter { 120.0f, 1.6f, 1.2f, Color(0x99ffffff) } },
        { GetKeyOfBlurStyle(BlurStyle::COMPONENT_THICK, ThemeColorMode::LIGHT),
            BlurParameter { 80.0f, 1.8f, 1.0f, Color(0xccf1f3f5) } },
        { GetKeyOfBlurStyle(BlurStyle::COMPONENT_ULTRA_THICK, ThemeColorMode::LIGHT),
            BlurParameter { 80.0f, 1.9f, 1.0f, Color(0xe5ffffff) } },
        { GetKeyOfBlurStyle(BlurStyle::COMPONENT_ULTRA_THIN, ThemeColorMode::DARK),
            BlurParameter { 200.0f, 1.0f, 1.0f, Color(0x19000000) } },
        { GetKeyOfBlurStyle(BlurStyle::COMPONENT_THIN, ThemeColorMode::DARK),
            BlurParameter { 200.0f, 1.0f, 1.0f, Color(0x33000000) } },
        { GetKeyOfBlurStyle(BlurStyle::COMPONENT_REGULAR, ThemeColorMode::DARK),
            BlurParameter { 200.0f, 1.0f, 1.0f, Color(0x66000000) } },
        { GetKeyOfBlurStyle(BlurStyle::COMPONENT_THICK, ThemeColorMode::DARK),
            BlurParameter { 80.0f, 1.3f, 1.0f, Color(0x66000000) } },
        { GetKeyOfBlurStyle(BlurStyle::COMPONENT_ULTRA_THICK, ThemeColorMode::DARK),
            BlurParameter { 80.0f, 1.5f, 1.0f, Color(0xe52e3033) } },
    };
    auto iter = blurParams.find(GetKeyOfBlurStyle(style, colorMode));
    return iter != blurParams.end() ? std::optional<BlurParameter>(iter->second) : std::nullopt;
}
} // namespace OHOS::Ace
