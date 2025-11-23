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

#include "core/components/theme/ui_material_theme.h"

#include "core/components/theme/shadow_theme.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace {

namespace {
constexpr Color MATERIAL_SEMI_TRANSPARENT_COLOR_LIGHT(0xF2F1F3F5);
constexpr Color MATERIAL_SEMI_TRANSPARENT_COLOR_DARK(0xF2303131);
constexpr float MATERIAL_SEMI_TRANSPARENT_BORDER_ALPHA { 0.1f };
constexpr Dimension MATERIAL_SEMI_TRANSPARENT_BORDER_WIDTH(1.0f, DimensionUnit::VP);
constexpr ShadowStyle MATERIAL_SEMI_TRANSPARENT_SHADOW_STYLE { ShadowStyle::OuterDefaultSM };
} // namespace

RefPtr<UiMaterialTheme> UiMaterialTheme::Builder::Build(const RefPtr<ThemeConstants>& themeConstants) const
{
    RefPtr<UiMaterialTheme> theme = AceType::MakeRefPtr<UiMaterialTheme>();
    CHECK_NULL_RETURN(themeConstants, theme);
    theme->SetInstanceId(Container::CurrentId());
    return theme;
}

void UiMaterialTheme::SetInstanceId(int32_t instanceId)
{
    instanceId_ = instanceId;
}

bool UiMaterialTheme::ParseUiMaterialParam(
    MaterialType type, NG::PipelineContext* pipeline, ColorMode colorMode, UiMaterialParam& result)
{
    if (type == MaterialType::SEMI_TRANSPARENT) {
        auto themeManager = pipeline->GetThemeManager();
        CHECK_NULL_RETURN(themeManager, false);
        auto themeConstants = themeManager->GetThemeConstants();
        CHECK_NULL_RETURN(themeConstants, false);
        auto shadowTheme = pipeline->GetTheme<ShadowTheme>();
        CHECK_NULL_RETURN(shadowTheme, false);
        auto resId = TokenColors::GetSystemColorResIdByIndex(TokenColors::COMP_FOREGROUND_PRIMARY);
        auto color = themeConstants->GetColor(resId);
        color = color.ChangeOpacity(MATERIAL_SEMI_TRANSPARENT_BORDER_ALPHA);
        result.borderColor.SetColor(color);
        result.borderWidth.SetBorderWidth(MATERIAL_SEMI_TRANSPARENT_BORDER_WIDTH);
        result.backgroundColor =
            colorMode == ColorMode::DARK ? MATERIAL_SEMI_TRANSPARENT_COLOR_DARK : MATERIAL_SEMI_TRANSPARENT_COLOR_LIGHT;
        result.shadow = shadowTheme->GetShadow(MATERIAL_SEMI_TRANSPARENT_SHADOW_STYLE, colorMode);
        return true;
    }
    // MaterialType::NONE
    result.backgroundColor = Color::TRANSPARENT;
    result.borderColor.SetColor(Color::TRANSPARENT);
    result.borderWidth.SetBorderWidth(Dimension(0));
    return true;
}

uint32_t UiMaterialTheme::GetKeyOfUiMaterial(MaterialType type, ColorMode colorMode)
{
    return (static_cast<uint32_t>(colorMode) << 16) + static_cast<uint32_t>(type); // can hold 2^16 blurStyle enums
}

std::optional<UiMaterialParam> UiMaterialTheme::GetUiMaterialParam(MaterialType type, NG::PipelineContext* pipeline)
{
    if (type > MaterialType::MAX || type < MaterialType::NONE || !pipeline) {
        return std::nullopt;
    }
    auto colorMode = MaterialUtils::GetResourceColorMode(pipeline);
    auto key = GetKeyOfUiMaterial(type, colorMode);
    auto iter = materialParams_.find(key);
    if (iter != materialParams_.end()) {
        return std::optional<UiMaterialParam>(iter->second);
    }
    UiMaterialParam param;
    auto success = ParseUiMaterialParam(type, pipeline, colorMode, param);
    if (success) {
        materialParams_.emplace(key, param);
        return param;
    }
    return std::nullopt;
}
} // namespace OHOS::Ace
