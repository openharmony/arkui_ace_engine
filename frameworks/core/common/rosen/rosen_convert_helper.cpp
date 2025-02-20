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

#include "core/common/container.h"

namespace OHOS::Ace {
MATERIAL_BLUR_STYLE GetRosenBlurStyleValue(const BlurStyleOption& option)
{
    ThemeColorMode colorMode = option.colorMode;
    if (option.colorMode == ThemeColorMode::SYSTEM) {
        colorMode = Container::CurrentColorMode() == ColorMode::DARK ? ThemeColorMode::DARK : ThemeColorMode::LIGHT;
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
} // namespace OHOS::Ace
