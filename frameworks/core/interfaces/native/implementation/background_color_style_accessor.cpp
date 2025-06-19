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
#include "background_color_style_peer.h"

namespace OHOS::Ace::NG {
namespace GeneratedModifier {
namespace BackgroundColorStyleAccessor {
void DestroyPeerImpl(Ark_BackgroundColorStyle peer)
{
    delete peer;
}
Ark_BackgroundColorStyle CtorImpl(const Ark_TextBackgroundStyle* textBackgroundStyle)
{
    TextBackgroundStyle style;
    if (textBackgroundStyle) {
        style = Converter::Convert<TextBackgroundStyle>(*textBackgroundStyle);
    }
    auto span = AceType::MakeRefPtr<OHOS::Ace::BackgroundColorSpan>(style);
    return new BackgroundColorStylePeer{ .span = span };
}
Ark_NativePointer GetFinalizerImpl()
{
    return reinterpret_cast<void *>(&DestroyPeerImpl);
}
Ark_TextBackgroundStyle GetTextBackgroundStyleImpl(Ark_BackgroundColorStyle peer)
{
    auto textBgStyleInvalid = TextBackgroundStyle();
    Ark_TextBackgroundStyle invalidValue =
        Converter::ArkValue<Ark_TextBackgroundStyle>(textBgStyleInvalid, Converter::FC);
    CHECK_NULL_RETURN(peer && peer->span, invalidValue);
    auto textBgStyle = peer->span->GetBackgroundColor();
    return Converter::ArkValue<Ark_TextBackgroundStyle>(textBgStyle, Converter::FC);
}
} // BackgroundColorStyleAccessor
const GENERATED_ArkUIBackgroundColorStyleAccessor* GetBackgroundColorStyleAccessor()
{
    static const GENERATED_ArkUIBackgroundColorStyleAccessor BackgroundColorStyleAccessorImpl {
        BackgroundColorStyleAccessor::DestroyPeerImpl,
        BackgroundColorStyleAccessor::CtorImpl,
        BackgroundColorStyleAccessor::GetFinalizerImpl,
        BackgroundColorStyleAccessor::GetTextBackgroundStyleImpl,
    };
    return &BackgroundColorStyleAccessorImpl;
}
}
}
