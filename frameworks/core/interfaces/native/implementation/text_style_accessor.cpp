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
#include "core/interfaces/native/implementation/text_style_peer.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/reverse_converter.h"
#include "core/interfaces/native/utility/validators.h"
#include "arkoala_api_generated.h"

namespace OHOS::Ace::NG::GeneratedModifier {
namespace TextStyleAccessor {
void DestroyPeerImpl(Ark_TextStyle peer)
{
    PeerUtils::DestroyPeer(peer);
}
Ark_TextStyle ConstructImpl(const Opt_TextStyleInterface* value)
{
    auto peer = PeerUtils::CreatePeer<TextStylePeer>();
    Font font {};

    auto options = Converter::OptConvertPtr<Ark_TextStyleInterface>(value);
    if (options) {
        auto context = PipelineBase::GetCurrentContextSafely();
        CHECK_NULL_RETURN(context, nullptr);
        auto theme = context->GetTheme<TextTheme>();
        CHECK_NULL_RETURN(theme, nullptr);
        font.fontColor = Converter::OptConvert<Color>(options->fontColor);
        if (!font.fontColor) {
            font.fontColor = theme->GetTextStyle().GetTextColor();
        }
        if (auto optFontSize = Converter::GetOpt(options->fontSize); optFontSize) {
            font.fontSize = Converter::Convert<Dimension>(optFontSize.value());
            Validator::ValidateNonNegative(font.fontSize);
            Validator::ValidateNonPercent(font.fontSize);
            if (!font.fontSize) {
                font.fontSize = theme->GetTextStyle().GetFontSize();
            }
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
        font.fontStyle = Converter::OptConvert<Ace::FontStyle>(options->fontStyle);
    }
    peer->span = Referenced::MakeRefPtr<FontSpan>(font);

    return peer;
}
Ark_NativePointer GetFinalizerImpl()
{
    return reinterpret_cast<void *>(&DestroyPeerImpl);
}
Opt_ResourceColor GetFontColorImpl(Ark_TextStyle peer)
{
    auto invalidValue = Converter::ArkValue<Opt_ResourceColor>();
    CHECK_NULL_RETURN(peer && peer->span, invalidValue);
    auto color = peer->span->GetFont().fontColor;
    return Converter::ArkUnion<Opt_ResourceColor, Ark_String>(color, Converter::FC);
}
Opt_String GetFontFamilyImpl(Ark_TextStyle peer)
{
    auto invalidValue = Converter::ArkValue<Opt_String>();
    CHECK_NULL_RETURN(peer, invalidValue);
    CHECK_NULL_RETURN(peer->span, invalidValue);
    if (!peer->span->GetFont().fontFamiliesNG.has_value()) {
        return invalidValue;
    }
    auto fontFamilies = peer->span->GetFont().fontFamiliesNG.value();
    auto retStr = std::accumulate(fontFamilies.begin(), fontFamilies.end(), std::string());
    return Converter::ArkValue<Opt_String>(retStr, Converter::FC);
}
Opt_Float64 GetFontSizeImpl(Ark_TextStyle peer)
{
    auto invalidValue = Converter::ArkValue<Opt_Float64>();
    CHECK_NULL_RETURN(peer, invalidValue);
    CHECK_NULL_RETURN(peer->span, invalidValue);
    if (!peer->span->GetFont().fontSize.has_value()) {
        return invalidValue;
    }
    auto ret = peer->span->GetFont().fontSize.value().ConvertToVp();
    return Converter::ArkValue<Opt_Float64>(ret);
}
Opt_Int32 GetFontWeightImpl(Ark_TextStyle peer)
{
    auto invalidValue = Converter::ArkValue<Opt_Int32>();
    CHECK_NULL_RETURN(peer, invalidValue);
    CHECK_NULL_RETURN(peer->span, invalidValue);
    return Converter::ArkValue<Opt_Int32>(EnumToInt(peer->span->GetFont().fontWeight));
}
Opt_FontStyle GetFontStyleImpl(Ark_TextStyle peer)
{
    auto invalidValue = Converter::ArkValue<Opt_FontStyle>();
    CHECK_NULL_RETURN(peer, invalidValue);
    CHECK_NULL_RETURN(peer->span, invalidValue);
    return Converter::ArkValue<Opt_FontStyle>(peer->span->GetFont().fontStyle);
}
} // TextStyleAccessor
const GENERATED_ArkUITextStyleAccessor* GetTextStyleAccessor()
{
    static const GENERATED_ArkUITextStyleAccessor TextStyleAccessorImpl {
        TextStyleAccessor::DestroyPeerImpl,
        TextStyleAccessor::ConstructImpl,
        TextStyleAccessor::GetFinalizerImpl,
        TextStyleAccessor::GetFontColorImpl,
        TextStyleAccessor::GetFontFamilyImpl,
        TextStyleAccessor::GetFontSizeImpl,
        TextStyleAccessor::GetFontWeightImpl,
        TextStyleAccessor::GetFontStyleImpl,
    };
    return &TextStyleAccessorImpl;
}

}
