/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

#include "theme_ani_modifier.h"

#include <cstdint>
#include <vector>

#include "ui/view/theme/token_colors.h"

#include "core/components_ng/token_theme/token_theme_storage.h"

namespace OHOS::Ace::NG {
void ObtainDefaultColors(std::vector<uint32_t>& defaultColors)
{
    auto basisTheme = TokenThemeStorage::GetInstance()->GetDefaultTheme();
    CHECK_NULL_VOID(basisTheme);
    auto colorsRef = basisTheme->Colors();
    CHECK_NULL_VOID(colorsRef);
    for (auto& color : colorsRef->GetColors()) {
        defaultColors.push_back(color.GetValue());
    }
}

void ObtainSystemColors(std::vector<uint32_t>& systemColors)
{
    auto basisTheme = TokenThemeStorage::GetInstance()->ObtainSystemTheme();
    CHECK_NULL_VOID(basisTheme);
    auto colorsRef = basisTheme->Colors();
    CHECK_NULL_VOID(colorsRef);
    for (auto& color : colorsRef->GetColors()) {
        systemColors.push_back(color.GetValue());
    }
}

int32_t GetTokenColorsSize()
{
    return TokenColors::TOTAL_NUMBER;
}

const ArkUIAniThemeModifier* GetThemeAniModifier()
{
    static const ArkUIAniThemeModifier impl = {
        .obtainDefaultColors = OHOS::Ace::NG::ObtainDefaultColors,
        .obtainSystemColors = OHOS::Ace::NG::ObtainSystemColors,
        .getTokenColorsSize = OHOS::Ace::NG::GetTokenColorsSize
    };
    return &impl;
}
} // namespace OHOS::Ace::NG
