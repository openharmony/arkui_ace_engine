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

#include "ui/resource/resource_object.h"

#include "core/common/resource/resource_manager.h"
#include "core/components_ng/token_theme/token_theme_storage.h"
#include "core/interfaces/native/node/theme_modifier.h"
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
        auto container = Container::Current();
        CHECK_NULL_VOID(container);
        ResourceManager::GetInstance().UpdateColorMode(
            container->GetBundleName(), container->GetModuleName(), container->GetInstanceId(), colorModeValue);
#endif
        auto pipelineContext = NG::PipelineContext::GetCurrentContextSafely();
        CHECK_NULL_VOID(pipelineContext);
        pipelineContext->SetLocalColorMode(colorModeValue);
    }
}

void AniThemeModule::RestoreColorMode()
{
    auto pipelineContext = NG::PipelineContext::GetCurrentContextSafely();
    CHECK_NULL_VOID(pipelineContext);
    pipelineContext->SetLocalColorMode(ColorMode::COLOR_MODE_UNDEFINED);

    auto colorModeValue = pipelineContext->GetColorMode();
#if defined(ANDROID_PLATFORM) || defined(IOS_PLATFORM)
    UpdateColorModeForThemeConstants(colorModeValue);
#else
    auto container = Container::GetContainer(pipelineContext->GetInstanceId());
    CHECK_NULL_VOID(container);
    ResourceManager::GetInstance().UpdateColorMode(
        container->GetBundleName(), container->GetModuleName(), container->GetInstanceId(), colorModeValue);
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

void AniThemeModule::ConvertToColorArray(const std::vector<Ark_ResourceColor>& colorArray,
    std::vector<uint32_t>& colors, std::vector<RefPtr<ResourceObject>>& resObjs)
{
    auto basisTheme = TokenThemeStorage::GetInstance()->ObtainSystemTheme();
    for (size_t i = 0; i < colorArray.size(); i++) {
        // type ResourceColor = number | string | Resource
        auto value = colorArray[i];
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
        resObjs.push_back(ConvertToResObj(value));
    }
}

ArkUINodeHandle AniThemeModule::CreateWithThemeNode(int32_t themeScopeId)
{
    auto themeModifier = NodeModifier::GetThemeModifier();
    auto node = themeModifier->createWithThemeNode(themeScopeId);
    return node;
}

RefPtr<ResourceObject> AniThemeModule::ConvertToResObj(const Ark_ResourceColor& color)
{
    if (color.selector != 3) { // 3 mean the color is Resource.
        return nullptr;
    }
    auto resource = color.value3;
    auto id = resource.id;
    auto type = Converter::OptConvert<int32_t>(resource.type).value_or(0);
    auto bundleName = Converter::Convert<std::string>(resource.bundleName);
    auto moduleName = Converter::Convert<std::string>(resource.moduleName);

    std::vector<ResourceObjectParams> params;
    if (resource.params.tag != INTEROP_TAG_UNDEFINED) {
        for (int i = 0; i < resource.params.value.length; i++) {
            auto paramObj = resource.params.value.array[i];
            if (paramObj.selector == 0) {
                ResourceObjectParams param { .value = std::make_optional(paramObj.value0.chars),
                    .type = ResourceObjectParamType::STRING };
                params.emplace_back(param);
            } else if (paramObj.selector == 1) {
                ResourceObjectParams param { .value = std::to_string(paramObj.value1),
                    .type = ResourceObjectParamType::INT };
                params.emplace_back(param);
            } else if (paramObj.selector == 2) {
                ResourceObjectParams param { .value = std::to_string(paramObj.value2),
                    .type = ResourceObjectParamType::INT };
                params.emplace_back(param);
            } else if (paramObj.selector == 3) {
                ResourceObjectParams param { .value = std::to_string(paramObj.value3),
                    .type = ResourceObjectParamType::FLOAT };
                params.emplace_back(param);
            }
        }
    }

    return AceType::MakeRefPtr<ResourceObject>(id, type, params, bundleName, moduleName, Container::CurrentIdSafely());
}
} // namespace OHOS::Ace::NG
