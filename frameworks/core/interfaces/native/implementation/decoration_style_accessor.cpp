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

#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/reverse_converter.h"
#include "arkoala_api_generated.h"
#include "core/interfaces/native/implementation/decoration_style_peer.h"

namespace OHOS::Ace::NG::GeneratedModifier {
namespace DecorationStyleAccessor {
void DestroyPeerImpl(Ark_DecorationStyle peer)
{
    delete peer;
}
Ark_DecorationStyle CtorImpl(const Ark_DecorationStyleInterface* value)
{
    // RefPtr<DecorationSpan> span;
    // if (value) {
    //     auto aceTypeOpt = Converter::OptConvert<TextDecoration>(value->type);
    //     auto aceColorOpt = Converter::OptConvert<Color>(value->color);
    //     auto aceStyleOpt = Converter::OptConvert<TextDecorationStyle>(value->style);
    //     span = AceType::MakeRefPtr<DecorationSpan>(aceTypeOpt.value_or(TextDecoration::NONE),
    //         aceColorOpt, aceStyleOpt);
    // } else {
    //     span = AceType::MakeRefPtr<DecorationSpan>();
    // }
    // return new DecorationStylePeer{ .span = span };
    return nullptr;
}
Ark_NativePointer GetFinalizerImpl()
{
    return reinterpret_cast<void *>(&DestroyPeerImpl);
}
Ark_TextDecorationType GetTypeImpl(Ark_DecorationStyle peer)
{
    auto invalidValue = static_cast<Ark_TextDecorationType>(-1);
    CHECK_NULL_RETURN(peer, invalidValue);
    CHECK_NULL_RETURN(peer->span, invalidValue);
    return invalidValue;
}
Opt_ResourceColor GetColorImpl(Ark_DecorationStyle peer)
{
    auto invalidValue = Converter::ArkValue<Opt_ResourceColor>();
    CHECK_NULL_RETURN(peer && peer->span, invalidValue);
    auto color = peer->span->GetColor();
    return Converter::ArkUnion<Opt_ResourceColor, Ark_String>(color, Converter::FC);
}
Opt_TextDecorationStyle GetStyleImpl(Ark_DecorationStyle peer)
{
    auto invalidValue = Converter::ArkValue<Opt_TextDecorationStyle>();
    CHECK_NULL_RETURN(peer, invalidValue);
    CHECK_NULL_RETURN(peer->span, invalidValue);
    auto optValue = peer->span->GetTextDecorationStyle();
    return Converter::ArkValue<Opt_TextDecorationStyle>(optValue);
}
} // DecorationStyleAccessor
const GENERATED_ArkUIDecorationStyleAccessor* GetDecorationStyleAccessor()
{
    static const GENERATED_ArkUIDecorationStyleAccessor DecorationStyleAccessorImpl {
        DecorationStyleAccessor::DestroyPeerImpl,
        DecorationStyleAccessor::CtorImpl,
        DecorationStyleAccessor::GetFinalizerImpl,
        DecorationStyleAccessor::GetTypeImpl,
        DecorationStyleAccessor::GetColorImpl,
        DecorationStyleAccessor::GetStyleImpl,
    };
    return &DecorationStyleAccessorImpl;
}

}
