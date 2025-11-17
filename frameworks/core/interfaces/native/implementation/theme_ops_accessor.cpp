/*
 * Copyright (c) 2024-2025 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "arkoala_api_generated.h"

#include "core/components_ng/base/frame_node.h"
#if !defined(PREVIEW) && !defined(ARKUI_CAPI_UNITTEST)
#include "core/interfaces/native/ani/ani_theme.h"
#include "core/interfaces/native/ani/ani_theme_module.h"
#endif
#include "core/interfaces/native/node/theme_modifier.h"
#include "core/interfaces/native/utility/callback_helper.h"
#include "core/interfaces/native/utility/converter.h"

namespace OHOS::Ace::NG::GeneratedModifier {
namespace ThemeOpsAccessor {
void SendThemeToNativeImpl(const Array_ResourceColor* colorArray, Ark_Int32 elmtId)
{
#if !defined(PREVIEW) && !defined(ARKUI_CAPI_UNITTEST)
    CHECK_NULL_VOID(colorArray);
    std::vector<Ark_ResourceColor> colorArrayVec;
    for (int32_t i = 0; i < colorArray->length; i++) {
        colorArrayVec.push_back(colorArray->array[i]);
    }
    auto colors = AceType::MakeRefPtr<AniThemeColors>();
    colors->SetColors(colorArrayVec);

    auto themeScopeId = static_cast<int32_t>(elmtId);

    AniTheme aniTheme;
    aniTheme.SetColors(colors);
    AniThemeScope::AddAniTheme(themeScopeId, aniTheme);

    // save the current theme when Theme was created by WithTheme container
    if (AniThemeScope::isCurrentThemeDefault || themeScopeId > 0) {
        std::optional<NG::AniTheme> themeOpt = std::make_optional(AniThemeScope::GetAniTheme(themeScopeId));
        AniThemeScope::aniCurrentTheme.swap(themeOpt);
    }
#endif
}
void SetDefaultThemeImpl(const Array_ResourceColor* colorArray, Ark_Boolean isDark)
{
#if !defined(PREVIEW) && !defined(ARKUI_CAPI_UNITTEST)
    CHECK_NULL_VOID(colorArray);
    std::vector<Ark_ResourceColor> colorArrayVec;
    for (int32_t i = 0; i < colorArray->length; i++) {
        colorArrayVec.push_back(colorArray->array[i]);
    }
    auto isDarkValue = static_cast<bool>(isDark);
    std::vector<uint32_t> colors;
    std::vector<RefPtr<ResourceObject>> resObjs;
    AniThemeModule::ConvertToColorArray(colorArrayVec, colors, resObjs);
    NodeModifier::GetThemeModifier()->setDefaultTheme(colors.data(), isDarkValue, static_cast<void*>(&resObjs));
#endif
}
void CreateAndBindThemeImpl(Ark_Int32 themeScopeId, Ark_Int32 themeId, const Array_ResourceColor* colorArray,
    Ark_ThemeColorMode colorMode, const Callback_Void* onThemeScopeDestroy)
{
#if !defined(PREVIEW) && !defined(ARKUI_CAPI_UNITTEST)
    CHECK_NULL_VOID(colorArray);
    std::vector<Ark_ResourceColor> colorArrayVec;
    for (int32_t i = 0; i < colorArray->length; i++) {
        colorArrayVec.push_back(colorArray->array[i]);
    }

    int32_t colorModeValue = static_cast<int32_t>(colorMode);

    std::vector<uint32_t> colors;
    std::vector<RefPtr<ResourceObject>> resObjs;
    AniThemeModule::ConvertToColorArray(colorArrayVec, colors, resObjs);

    auto themeModifier = NodeModifier::GetThemeModifier();
    auto theme = themeModifier->createTheme(themeId, colors.data(), colors.data(), colorModeValue,
        static_cast<void*>(&resObjs), static_cast<void*>(&resObjs));
    CHECK_NULL_VOID(theme);
    ArkUINodeHandle node = themeModifier->getWithThemeNode(themeScopeId);
    if (!node) {
        node = AniThemeModule::CreateWithThemeNode(themeScopeId);
    }
    themeModifier->createThemeScope(node, theme);

    CHECK_NULL_VOID(onThemeScopeDestroy);
    std::function<void()> func = [callback = CallbackHelper(*onThemeScopeDestroy),
                                     instanceId = Container::CurrentIdSafely()]() -> void {
        ContainerScope scope(instanceId);
        callback.InvokeSync();
    };
    themeModifier->setOnThemeScopeDestroy(node, reinterpret_cast<void*>(&func));
#endif
}
void ApplyThemeScopeIdToNodeImpl(Ark_NativePointer ptr,
                                 Ark_Int32 themeScopeId)
{
    auto frameNode = reinterpret_cast<FrameNode *>(ptr);
    CHECK_NULL_VOID(frameNode);
    frameNode->SetThemeScopeId(themeScopeId);
}
} // ThemeOpsAccessor
const GENERATED_ArkUIThemeOpsAccessor* GetThemeOpsAccessor()
{
    static const GENERATED_ArkUIThemeOpsAccessor ThemeOpsAccessorImpl {
        ThemeOpsAccessor::SendThemeToNativeImpl,
        ThemeOpsAccessor::SetDefaultThemeImpl,
        ThemeOpsAccessor::CreateAndBindThemeImpl,
        ThemeOpsAccessor::ApplyThemeScopeIdToNodeImpl,
    };
    return &ThemeOpsAccessorImpl;
}

} // namespace OHOS::Ace::NG::GeneratedModifier
