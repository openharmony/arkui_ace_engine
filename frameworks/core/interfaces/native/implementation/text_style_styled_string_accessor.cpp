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

#include <numeric>

#include "core/components/text/text_theme.h"
#include "core/components_ng/base/frame_node.h"
#include "core/interfaces/native/implementation/text_style_styled_string_peer.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/reverse_converter.h"
#include "core/interfaces/native/utility/validators.h"
#include "arkoala_api_generated.h"

namespace OHOS::Ace::NG::GeneratedModifier {
namespace TextStyle_styled_stringAccessor {
void DestroyPeerImpl(Ark_TextStyle_styled_string peer)
{
    delete peer;
}
Ark_TextStyle_styled_string CtorImpl(const Opt_TextStyleInterface* value)
{
    Font font;

    auto options = value ? Converter::OptConvert<Ark_TextStyleInterface>(*value) : std::nullopt;
    if (options) {
        auto context = PipelineBase::GetCurrentContextSafely();
        CHECK_NULL_RETURN(context, nullptr);
        auto theme = context->GetTheme<TextTheme>();
        CHECK_NULL_RETURN(theme, nullptr);
        font.fontColor = Converter::OptConvert<Color>(options->fontColor);
        if (!font.fontColor) {
            font.fontColor = theme->GetTextStyle().GetTextColor();
        }
        font.fontSize = Converter::OptConvert<Dimension>(options->fontSize);
        Validator::ValidateNonNegative(font.fontSize);
        if (!font.fontSize) {
            font.fontSize = theme->GetTextStyle().GetFontSize();
        }
        font.fontWeight = Converter::OptConvert<FontWeight>(options->fontWeight);
        if (!font.fontWeight) {
            font.fontWeight = theme->GetTextStyle().GetFontWeight();
        }
        std::vector<std::string> fontFamilies;
        auto fontFamily = Converter::OptConvert<std::string>(options->fontFamily);
        if (fontFamily) {
            fontFamilies.push_back(*fontFamily);
        } else {
            fontFamilies = theme->GetTextStyle().GetFontFamilies();
        }
        font.fontFamiliesNG = fontFamilies;
        font.fontStyle = Converter::OptConvert<Ace::FontStyle>(options->fontStyle).value_or(Ace::FontStyle::NORMAL);
    }
    auto peer = new TextStyle_styled_stringPeer();
    peer->span = Referenced::MakeRefPtr<FontSpan>(font);

    return peer;
}
Ark_NativePointer GetFinalizerImpl()
{
    return reinterpret_cast<void *>(&DestroyPeerImpl);
}
Ark_ResourceColor GetFontColorImpl(Ark_TextStyle_styled_string peer)
{
    Ark_ResourceColor invalidValue = {};
    CHECK_NULL_RETURN(peer && peer->span, invalidValue);
    auto color = peer->span->GetFont().fontColor;
    auto value = Converter::ArkUnion<Opt_ResourceColor, Ark_String>(color, Converter::FC);
    return Converter::GetOpt(value).value_or(invalidValue);
}
Ark_String GetFontFamilyImpl(Ark_TextStyle_styled_string peer)
{
    std::string retStr = "";
    CHECK_NULL_RETURN(peer, Converter::ArkValue<Ark_String>(retStr, Converter::FC));
    CHECK_NULL_RETURN(peer->span, Converter::ArkValue<Ark_String>(retStr, Converter::FC));
    if (!peer->span->GetFont().fontFamiliesNG.has_value()) {
        return Converter::ArkValue<Ark_String>(retStr, Converter::FC);
    }
    auto fontFamilies = peer->span->GetFont().fontFamiliesNG.value();
    retStr = std::accumulate(fontFamilies.begin(), fontFamilies.end(), std::string());
    return Converter::ArkValue<Ark_String>(retStr, Converter::FC);
}
Ark_Number GetFontSizeImpl(Ark_TextStyle_styled_string peer)
{
    CHECK_NULL_RETURN(peer, Converter::ArkValue<Ark_Number>(0));
    CHECK_NULL_RETURN(peer->span, Converter::ArkValue<Ark_Number>(0));
    if (!peer->span->GetFont().fontSize.has_value()) {
        return Converter::ArkValue<Ark_Number>(0);
    }
    auto ret = peer->span->GetFont().fontSize.value().ConvertToVp();
    return Converter::ArkValue<Ark_Number>(ret);
}
Ark_Number GetFontWeightImpl(Ark_TextStyle_styled_string peer)
{
    CHECK_NULL_RETURN(peer, Converter::ArkValue<Ark_Number>(0));
    CHECK_NULL_RETURN(peer->span, Converter::ArkValue<Ark_Number>(0));
    if (!peer->span->GetFont().fontWeight.has_value()) {
        return Converter::ArkValue<Ark_Number>(0);
    }
    auto ret = static_cast<int32_t>(peer->span->GetFont().fontWeight.value());
    return Converter::ArkValue<Ark_Number>(ret);
}
Ark_FontStyle GetFontStyleImpl(Ark_TextStyle_styled_string peer)
{
    CHECK_NULL_RETURN(peer, Ark_FontStyle::ARK_FONT_STYLE_NORMAL);
    CHECK_NULL_RETURN(peer->span, Ark_FontStyle::ARK_FONT_STYLE_NORMAL);
    if (!peer->span->GetFont().fontStyle.has_value()) {
        return Ark_FontStyle::ARK_FONT_STYLE_NORMAL;
    }
    return Converter::ArkValue<Ark_FontStyle>(peer->span->GetFont().fontStyle.value());
}
} // TextStyle_styled_stringAccessor
const GENERATED_ArkUITextStyle_styled_stringAccessor* GetTextStyle_styled_stringAccessor()
{
    static const GENERATED_ArkUITextStyle_styled_stringAccessor TextStyle_styled_stringAccessorImpl {
        TextStyle_styled_stringAccessor::DestroyPeerImpl,
        TextStyle_styled_stringAccessor::CtorImpl,
        TextStyle_styled_stringAccessor::GetFinalizerImpl,
        TextStyle_styled_stringAccessor::GetFontColorImpl,
        TextStyle_styled_stringAccessor::GetFontFamilyImpl,
        TextStyle_styled_stringAccessor::GetFontSizeImpl,
        TextStyle_styled_stringAccessor::GetFontWeightImpl,
        TextStyle_styled_stringAccessor::GetFontStyleImpl,
    };
    return &TextStyle_styled_stringAccessorImpl;
}
}
