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
#include "core/interfaces/native/utility/ace_engine_types.h"
#include "core/interfaces/native/utility/converter.h"
#include "arkoala_api_generated.h"
#include "core/interfaces/native/utility/peer_utils.h"
#include "digit_indicator_peer_impl.h"

namespace OHOS::Ace::NG::GeneratedModifier {
namespace DigitIndicatorAccessor {
void DestroyPeerImpl(Ark_DigitIndicator peer)
{
    PeerUtils::DestroyPeer(peer);
}
Ark_DigitIndicator ConstructImpl()
{
    auto peer = PeerUtils::CreatePeer<DigitIndicatorPeer>();
    return reinterpret_cast<Ark_DigitIndicator>(peer);
}
Ark_NativePointer GetFinalizerImpl()
{
    return reinterpret_cast<void *>(&DestroyPeerImpl);
}
void FontColorImpl(Ark_DigitIndicator peer,
                   const Opt_ResourceColor* value)
{
    CHECK_NULL_VOID(peer);
    auto optFontColor = Converter::OptConvertPtr<Color>(value);
    peer->SetFontColor(optFontColor);
}
void SelectedFontColorImpl(Ark_DigitIndicator peer,
                           const Opt_ResourceColor* value)
{
    CHECK_NULL_VOID(peer);
    auto optSelectedFontColor = Converter::OptConvertPtr<Color>(value);
    peer->SetSelectedFontColor(optSelectedFontColor);
}
void DigitFontImpl(Ark_DigitIndicator peer,
                   const Opt_Font* value)
{
    CHECK_NULL_VOID(peer);
    auto optDigitFont = Converter::OptConvertPtr<Converter::FontMetaData>(value);
    std::optional<OHOS::Ace::Dimension> fontSize;
    std::optional<OHOS::Ace::FontWeight> fontWeight;
    if (optDigitFont) {
        fontSize = optDigitFont->size;
        fontWeight = optDigitFont->weight;
    }
    peer->SetFontSize(fontSize);
    peer->SetFontWeight(fontWeight);
}
void SelectedDigitFontImpl(Ark_DigitIndicator peer,
                           const Opt_Font* value)
{
    CHECK_NULL_VOID(peer);
    auto optSelectedDigitFont = Converter::OptConvertPtr<Converter::FontMetaData>(value);
    std::optional<OHOS::Ace::Dimension> fontSize;
    std::optional<OHOS::Ace::FontWeight> fontWeight;
    if (optSelectedDigitFont) {
        fontSize = optSelectedDigitFont->size;
        fontWeight = optSelectedDigitFont->weight;
    }
    peer->SetSelectedFontSize(fontSize);
    peer->SetSelectedFontWeight(fontWeight);
}
} // DigitIndicatorAccessor
const GENERATED_ArkUIDigitIndicatorAccessor* GetDigitIndicatorAccessor()
{
    static const GENERATED_ArkUIDigitIndicatorAccessor DigitIndicatorAccessorImpl {
        DigitIndicatorAccessor::DestroyPeerImpl,
        DigitIndicatorAccessor::ConstructImpl,
        DigitIndicatorAccessor::GetFinalizerImpl,
        DigitIndicatorAccessor::FontColorImpl,
        DigitIndicatorAccessor::SelectedFontColorImpl,
        DigitIndicatorAccessor::DigitFontImpl,
        DigitIndicatorAccessor::SelectedDigitFontImpl,
    };
    return &DigitIndicatorAccessorImpl;
}

struct DigitIndicatorPeer {
    virtual ~DigitIndicatorPeer() = default;
};
}