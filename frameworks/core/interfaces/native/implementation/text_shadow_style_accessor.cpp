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

#include "core/components_ng/base/frame_node.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/reverse_converter.h"
#include "arkoala_api_generated.h"
#include "text_shadow_style_peer.h"

namespace OHOS::Ace::NG::GeneratedModifier {
namespace TextShadowStyleAccessor {
void DestroyPeerImpl(Ark_TextShadowStyle peer)
{
    delete peer;
}
Ark_TextShadowStyle CtorImpl(const Ark_Union_ShadowOptions_Array_ShadowOptions* value)
{
    RefPtr<OHOS::Ace::TextShadowSpan> span;
    if (value) {
        Converter::VisitUnion(*value,
            [&span](const Array_ShadowOptions& array) {
                auto shadowsOpt = Converter::OptConvert<std::vector<Shadow>>(array);
                if (shadowsOpt) {
                    span = AceType::MakeRefPtr<OHOS::Ace::TextShadowSpan>(shadowsOpt.value());
                }
            },
            [&span](const Ark_ShadowOptions& arkValue) {
                auto shadowOpt = Converter::OptConvert<Shadow>(arkValue);
                std::vector<Shadow> shadows;
                if (shadowOpt) {
                    shadows.push_back(shadowOpt.value());
                }
                span = AceType::MakeRefPtr<OHOS::Ace::TextShadowSpan>(shadows);
            },
            []() {});
    }
    if (!span) {
        span = AceType::MakeRefPtr<OHOS::Ace::TextShadowSpan>();
    }
    return new TextShadowStylePeer{ .span = span };
}
Ark_NativePointer GetFinalizerImpl()
{
    return reinterpret_cast<void *>(&DestroyPeerImpl);
}
Array_ShadowOptions GetTextShadowImpl(Ark_TextShadowStyle peer)
{
    CHECK_NULL_RETURN(peer && peer->span, {});
    return Converter::ArkValue<Array_ShadowOptions>(peer->span->GetTextShadow(), Converter::FC);
}
} // TextShadowStyleAccessor
const GENERATED_ArkUITextShadowStyleAccessor* GetTextShadowStyleAccessor()
{
    static const GENERATED_ArkUITextShadowStyleAccessor TextShadowStyleAccessorImpl {
        TextShadowStyleAccessor::DestroyPeerImpl,
        TextShadowStyleAccessor::CtorImpl,
        TextShadowStyleAccessor::GetFinalizerImpl,
        TextShadowStyleAccessor::GetTextShadowImpl,
    };
    return &TextShadowStyleAccessorImpl;
}
}