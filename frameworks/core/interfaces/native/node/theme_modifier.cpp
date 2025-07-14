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

#include "core/interfaces/native/node/theme_modifier.h"

#include "core/components/common/properties/color.h"
#include "core/components_ng/syntax/with_theme_node.h"
#include "core/components_ng/token_theme/token_theme.h"
#include "core/components_ng/token_theme/token_theme_storage.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {
namespace ThemeModifier {
namespace {
ColorMode MapNumberToColorMode(int32_t number)
{
    switch (number) {
        case 1: // 1 is the ThemeColorMode.LIGHT
            return ColorMode::LIGHT;
        case 2: // 2 is the ThemeColorMode.DARK
            return ColorMode::DARK;
        default:
            return ColorMode::COLOR_MODE_UNDEFINED;
    }
    return ColorMode::COLOR_MODE_UNDEFINED;
}

RefPtr<TokenColors> ConvertColorArrayToTokenColors(const ArkUI_Uint32* colorsArray)
{
    std::vector<Color> colors;
    colors.reserve(TokenColors::TOTAL_NUMBER);
    for (int i = 0; i < TokenColors::TOTAL_NUMBER; i++) {
        colors.push_back(Color(colorsArray[i]));
    }
    auto themeColors = AceType::MakeRefPtr<TokenColors>();
    themeColors->SetColors(std::move(colors));
    return themeColors;
}

std::vector<RefPtr<ResourceObject>> ConvertResObjArray(const void* resObjs)
{
    auto resourceObjs = *(static_cast<const std::vector<RefPtr<ResourceObject>>*>(resObjs));
    return resourceObjs;
}
} // namespace

ArkUINodeHandle CreateWithThemeNode(ArkUI_Int32 id)
{
    TAG_LOGD(AceLogTag::ACE_DEFAULT_DOMAIN, "WithTheme CreateWithThemeNode id:%{public}d", id);
    auto withThemeNode = WithThemeNode::CreateWithThemeNode(id);
    withThemeNode->IncRefCount();
    return reinterpret_cast<ArkUINodeHandle>(OHOS::Ace::AceType::RawPtr(withThemeNode));
}

ArkUINodeHandle GetWithThemeNode(ArkUI_Int32 id)
{
    auto withThemeNode = WithThemeNode::GetWithThemeNode(id);
    return reinterpret_cast<ArkUINodeHandle>(OHOS::Ace::AceType::RawPtr(withThemeNode));
}

ArkUINodeHandle CreateTheme(ArkUI_Int32 themeId, const ArkUI_Uint32* colors, const ArkUI_Uint32* darkColors,
    ArkUI_Int32 colorMode, const void* lightResObjs, const void* darkResObjs)
{
    auto theme = TokenThemeStorage::GetInstance()->CacheGet(themeId);
    if (!theme) {
        TAG_LOGD(AceLogTag::ACE_DEFAULT_DOMAIN, "WithTheme CreateTheme themeId:%{public}d colorMode num:%{public}d",
            themeId, colorMode);
        ColorMode themeScopeColorMode = MapNumberToColorMode(colorMode);
        auto themeColors = ConvertColorArrayToTokenColors(colors);
        auto themeDarkColors = ConvertColorArrayToTokenColors(darkColors);
        theme = AceType::MakeRefPtr<TokenTheme>(themeId);
        theme->SetColors(themeColors);
        theme->SetDarkColors(themeDarkColors);
        theme->SetColorMode(themeScopeColorMode);
        auto lightResourceObjs = ConvertResObjArray(lightResObjs);
        auto darkResourceObjs = ConvertResObjArray(darkResObjs);
        theme->SetResObjs(std::move(lightResourceObjs));
        theme->SetDarkResObjs(std::move(darkResourceObjs));
        TokenThemeStorage::GetInstance()->CacheSet(theme);
    }
    return reinterpret_cast<ArkUINodeHandle>(OHOS::Ace::AceType::RawPtr(theme));
}

void CreateThemeScope(ArkUINodeHandle node, ArkUINodeHandle theme)
{
    RefPtr<WithThemeNode> withThemeNode = AceType::Claim(reinterpret_cast<WithThemeNode*>(node));
    CHECK_NULL_VOID(withThemeNode);
    RefPtr<TokenTheme> tokenTheme = AceType::Claim(reinterpret_cast<TokenTheme*>(theme));
    CHECK_NULL_VOID(tokenTheme);
    TokenThemeStorage::GetInstance()->StoreThemeScope(withThemeNode->GetId(), tokenTheme->GetId());
    TAG_LOGD(AceLogTag::ACE_DEFAULT_DOMAIN, "WithTheme CreateThemeScope and notify node:%{public}d theme:%{public}d",
        withThemeNode->GetId(), tokenTheme->GetId());
    withThemeNode->NotifyThemeScopeUpdate();
}

void SetDefaultTheme(const ArkUI_Uint32* colors, ArkUI_Bool isDark)
{
    TAG_LOGD(AceLogTag::ACE_DEFAULT_DOMAIN, "WithTheme SetDefaultTheme isDark:%{public}d", isDark);
    auto themeColors = ConvertColorArrayToTokenColors(colors);
    auto theme = AceType::MakeRefPtr<TokenTheme>(0);
    if (isDark) {
        theme->SetDarkColors(themeColors);
    } else {
        theme->SetColors(themeColors);
    }
    auto colorMode = isDark ? ColorMode::DARK : ColorMode::LIGHT;
    TokenThemeStorage::GetInstance()->SetDefaultTheme(theme, colorMode);

    // global notify if required
    auto pipelineContext = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipelineContext);
    auto sysColorMode = pipelineContext->GetColorMode();
    if (sysColorMode != colorMode) {
        return;
    }
    auto rootNode = pipelineContext->GetRootElement();
    CHECK_NULL_VOID(rootNode);
    rootNode->UpdateThemeScopeUpdate(0); // 0 means default theme scope id
}

void RemoveFromCache(ArkUI_Int32 themeId)
{
    TokenThemeStorage::GetInstance()->CacheRemove(themeId);
}

void SetOnThemeScopeDestroy(ArkUINodeHandle node, void* callback)
{
    RefPtr<WithThemeNode> withThemeNode = AceType::Claim(reinterpret_cast<WithThemeNode*>(node));
    if (callback && withThemeNode) {
        auto cb = reinterpret_cast<std::function<void()>*>(callback);
        withThemeNode->SetOnThemeScopeDestroy(std::move(*cb));
    }
}

ArkUI_Int32 GetThemeScopeId(ArkUINodeHandle node)
{
    auto ui_node = reinterpret_cast<UINode*>(node);
    CHECK_NULL_RETURN(ui_node, 0);
    return ui_node->GetThemeScopeId();
}
} // namespace ThemeModifier
namespace NodeModifier {
const ArkUIThemeModifier* GetThemeModifier()
{
    CHECK_INITIALIZED_FIELDS_BEGIN(); // don't move this line
    static const ArkUIThemeModifier modifier = {
        .createWithThemeNode = ThemeModifier::CreateWithThemeNode,
        .getWithThemeNode = ThemeModifier::GetWithThemeNode,
        .createTheme = ThemeModifier::CreateTheme,
        .createThemeScope = ThemeModifier::CreateThemeScope,
        .setDefaultTheme = ThemeModifier::SetDefaultTheme,
        .removeFromCache = ThemeModifier::RemoveFromCache,
        .setOnThemeScopeDestroy = ThemeModifier::SetOnThemeScopeDestroy,
        .getThemeScopeId = ThemeModifier::GetThemeScopeId,
    };
    CHECK_INITIALIZED_FIELDS_END(modifier, 0, 0, 0); // don't move this line
    return &modifier;
}
} // namespace NodeModifier
} // namespace OHOS::Ace::NG