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
#include "core/interfaces/native/utility/validators.h"
#include "arkoala_api_generated.h"
#include "core/interfaces/native/implementation/letter_spacing_style_peer.h"

namespace OHOS::Ace::NG::GeneratedModifier {
namespace LetterSpacingStyleAccessor {
void DestroyPeerImpl(Ark_LetterSpacingStyle peer)
{
    PeerUtils::DestroyPeer(peer);
}
Ark_LetterSpacingStyle ConstructImpl(const Ark_LengthMetrics* value)
{
    auto peer = PeerUtils::CreatePeer<LetterSpacingStylePeer>();
    std::optional<Dimension> spacing;
    Dimension defaultSpacing = Dimension(0, DimensionUnit::VP);
    if (value) {
        spacing = Converter::OptConvert<Dimension>(*value);
        Validator::ValidateNonPercent(spacing);
    }
    peer->span = AceType::MakeRefPtr<LetterSpacingSpan>(spacing.value_or(defaultSpacing));
    return peer;
}
Ark_NativePointer GetFinalizerImpl()
{
    return reinterpret_cast<void *>(&DestroyPeerImpl);
}
Ark_Float64 GetLetterSpacingImpl(Ark_LetterSpacingStyle peer)
{
    CHECK_NULL_RETURN(peer, {});
    CHECK_NULL_RETURN(peer->span, {});
    auto value = Converter::ArkValue<Ark_Float64>(peer->span->GetLetterSpacing().ConvertToVp());
    return value;
}
} // LetterSpacingStyleAccessor
const GENERATED_ArkUILetterSpacingStyleAccessor* GetLetterSpacingStyleAccessor()
{
    static const GENERATED_ArkUILetterSpacingStyleAccessor LetterSpacingStyleAccessorImpl {
        LetterSpacingStyleAccessor::DestroyPeerImpl,
        LetterSpacingStyleAccessor::ConstructImpl,
        LetterSpacingStyleAccessor::GetFinalizerImpl,
        LetterSpacingStyleAccessor::GetLetterSpacingImpl,
    };
    return &LetterSpacingStyleAccessorImpl;
}

}
