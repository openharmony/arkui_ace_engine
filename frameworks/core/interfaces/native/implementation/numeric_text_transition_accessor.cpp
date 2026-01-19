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

#include "core/interfaces/native/utility/reverse_converter.h"
#include "core/interfaces/native/implementation/numeric_text_transition_peer_impl.h"

namespace OHOS::Ace::NG::GeneratedModifier {
namespace NumericTextTransitionAccessor {
void DestroyPeerImpl(Ark_NumericTextTransition peer)
{
    PeerUtils::DestroyPeer(peer);
}
Ark_NumericTextTransition ConstructImpl(const Opt_NumericTextTransitionOptions* options)
{
    CHECK_NULL_RETURN(options, nullptr);
    auto arkNumericTextTransitionOptions = Converter::GetOptPtr(options);
    CHECK_NULL_RETURN(arkNumericTextTransitionOptions, nullptr);
    Ark_NumericTextTransitionOptions arkNumericTextTransitionValues = arkNumericTextTransitionOptions.value();
    Opt_FlipDirection optFlipDirection = arkNumericTextTransitionValues.flipDirection;
    auto flipDirection = Converter::OptConvert<OHOS::Ace::TextFlipDirection>(optFlipDirection);
    Opt_Boolean optEnableBlur = arkNumericTextTransitionValues.enableBlur;
    auto enableBlur = Converter::OptConvert<bool>(optEnableBlur);
    auto* peer = PeerUtils::CreatePeer<NumericTextTransitionPeer>(flipDirection.value_or(OHOS::Ace::TextFlipDirection::DOWN),
                                                                   enableBlur.value_or(false));
    return peer;
}
Ark_NativePointer GetFinalizerImpl()
{
    return reinterpret_cast<void *>(&DestroyPeerImpl);
}
Opt_FlipDirection GetFlipDirectionImpl(Ark_NumericTextTransition peer)
{
    auto invalid = Converter::ArkValue<Opt_FlipDirection>();
    CHECK_NULL_RETURN(peer, invalid);
    return Converter::ArkValue<Opt_FlipDirection>(peer->flipDirection);
}
void SetFlipDirectionImpl(Ark_NumericTextTransition peer,
                          const Opt_FlipDirection* flipDirection)
{
    CHECK_NULL_VOID(peer);
    auto stylePeer = reinterpret_cast<NumericTextTransitionPeer*>(peer);
    CHECK_NULL_VOID(stylePeer);
    CHECK_NULL_VOID(flipDirection);
    auto flipDirectionOpt = Converter::OptConvert<TextFlipDirection>(*flipDirection);
    peer->flipDirection = flipDirectionOpt.value();
}
Opt_Boolean GetEnableBlurImpl(Ark_NumericTextTransition peer)
{
    auto invalid = Converter::ArkValue<Opt_Boolean>();
    CHECK_NULL_RETURN(peer, invalid);
    return Converter::ArkValue<Opt_Boolean>(peer->enableBlur);
}
void SetEnableBlurImpl(Ark_NumericTextTransition peer,
                       const Opt_Boolean* enableBlur)
{
    CHECK_NULL_VOID(peer);
    auto stylePeer = reinterpret_cast<NumericTextTransitionPeer*>(peer);
    CHECK_NULL_VOID(stylePeer);
    CHECK_NULL_VOID(enableBlur);
    auto enableBlurOpt = Converter::OptConvert<bool>(*enableBlur);
    peer->enableBlur = enableBlurOpt.value();
}
} // NumericTextTransitionAccessor
const GENERATED_ArkUINumericTextTransitionAccessor* GetNumericTextTransitionAccessor()
{
    static const GENERATED_ArkUINumericTextTransitionAccessor NumericTextTransitionAccessorImpl {
        NumericTextTransitionAccessor::DestroyPeerImpl,
        NumericTextTransitionAccessor::ConstructImpl,
        NumericTextTransitionAccessor::GetFinalizerImpl,
        NumericTextTransitionAccessor::GetFlipDirectionImpl,
        NumericTextTransitionAccessor::SetFlipDirectionImpl,
        NumericTextTransitionAccessor::GetEnableBlurImpl,
        NumericTextTransitionAccessor::SetEnableBlurImpl,
    };
    return &NumericTextTransitionAccessorImpl;
}

}
