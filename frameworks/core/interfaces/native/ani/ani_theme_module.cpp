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

#include "core/interfaces/native/ani/ani_theme_module.h"

#include <cstdint>

#include "bridge/arkts_frontend/arkts_ani_utils.h"
#include "core/common/resource/resource_manager.h"
#include "core/components_ng/token_theme/token_theme_storage.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {
void AniThemeModule::UpdateColorMode(int32_t colorMode)
{
    ColorMode colorModeValue = MapAniColorModeToColorMode(colorMode);
    if (colorModeValue != ColorMode::COLOR_MODE_UNDEFINED) {
#if defined(ANDROID_PLATFORM) || defined(IOS_PLATFORM)
        UpdateColorModeForThemeConstants(colorModeValue);
#else
        ResourceManager::GetInstance().UpdateColorMode(colorModeValue);
#endif
        auto pipelineContext = NG::PipelineContext::GetCurrentContext();
        pipelineContext->SetLocalColorMode(colorModeValue);
    }
}

void AniThemeModule::RestoreColorMode()
{
    auto pipelineContext = NG::PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipelineContext);
    pipelineContext->SetLocalColorMode(ColorMode::COLOR_MODE_UNDEFINED);

    auto colorModeValue = pipelineContext->GetColorMode();
#if defined(ANDROID_PLATFORM) || defined(IOS_PLATFORM)
    UpdateColorModeForThemeConstants(colorModeValue);
#else
    ResourceManager::GetInstance().UpdateColorMode(colorModeValue);
#endif
}

#if defined(ANDROID_PLATFORM) || defined(IOS_PLATFORM)
void AniThemeModule::UpdateColorModeForThemeConstants(const ColorMode& colorMode)
{
    auto container = Container::Current();
    CHECK_NULL_VOID(container);
    auto resConfig = container->GetResourceConfiguration();
    resConfig.SetColorMode(colorMode);

    auto themeManager = PipelineBase::CurrentThemeManager();
    CHECK_NULL_VOID(themeManager);
    auto themeConstants = themeManager->GetThemeConstants();
    CHECK_NULL_VOID(themeConstants);
    themeConstants->UpdateConfig(resConfig);
}
#endif

ColorMode AniThemeModule::MapAniColorModeToColorMode(int32_t aniColorMode)
{
    switch (aniColorMode) {
        case 1: // 1 is the ThemeColorMode.LIGHT
            return ColorMode::LIGHT;
        case 2: // 2 is the ThemeColorMode.DARK
            return ColorMode::DARK;
        default:
            return ColorMode::COLOR_MODE_UNDEFINED;
    }
    return ColorMode::COLOR_MODE_UNDEFINED;
}

void AniThemeModule::ConvertToColorArray(
    const Array_ResourceColor& colorArray, std::vector<uint32_t>& colors)
{
    auto basisTheme = TokenThemeStorage::GetInstance()->ObtainSystemTheme();
    for (int i = 0; i < colorArray.length; i++) {
        // type ResourceColor = number | string | Resource
        auto value = colorArray.array[i];
        Color color;
        bool isColorAvailable = false;
        const auto convColor = Converter::OptConvert<Color>(value);
        if (!convColor.has_value()) {
            if (basisTheme) {
                color = basisTheme->Colors()->GetByIndex(i);
                isColorAvailable = true;
            }
        } else {
            color = convColor.value();
            isColorAvailable = true;
        }
        colors.push_back(color.GetValue());
    }
}
} // namespace OHOS::Ace::NG
