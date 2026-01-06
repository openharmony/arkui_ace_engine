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
#include "arkoala_api_generated.h"
#include "transition_effect_peer_impl.h"
#include "core/interfaces/native/utility/reverse_converter.h"

namespace OHOS::Ace::NG::GeneratedModifier {
namespace TransitionEffectAccessor {

const auto IDENTITY_TOKEN = "identity";
const auto SLIDE_SWITCH_TOKEN = "slideswitch";

void DestroyPeerImpl(Ark_TransitionEffect peer)
{
    PeerUtils::DestroyPeer(peer);
}
Ark_TransitionEffect Construct0Impl(const Ark_String* type)
{
    CHECK_NULL_RETURN(type, nullptr);
    auto valueText = Converter::Convert<std::string>(*type);
    TransitionEffectPeer* peer = nullptr;
    if (valueText == IDENTITY_TOKEN) {
        peer = PeerUtils::CreatePeer<TransitionEffectPeer>();
        peer->handler = AceType::MakeRefPtr<ChainedIdentityEffect>();
    } else if (valueText == SLIDE_SWITCH_TOKEN) {
        peer = PeerUtils::CreatePeer<TransitionEffectPeer>();
        peer->handler = AceType::MakeRefPtr<ChainedSlideSwitchEffect>();
    }
    return peer;
}
Ark_TransitionEffect Construct1Impl(const Ark_Float64 effect)
{
    TransitionEffectPeer* peer = PeerUtils::CreatePeer<TransitionEffectPeer>();
    auto opacity = Converter::Convert<float>(effect);
    peer->handler = AceType::MakeRefPtr<ChainedOpacityEffect>(opacity);
    return peer;
}
Ark_TransitionEffect Construct2Impl(Ark_TransitionEdge effect)
{
    TransitionEffectPeer* peer = PeerUtils::CreatePeer<TransitionEffectPeer>();
    auto move = Converter::OptConvert<TransitionEdge>(effect).value_or(TransitionEdge::TOP);
    peer->handler = AceType::MakeRefPtr<ChainedMoveEffect>(move);
    return peer;
}
Ark_TransitionEffect Construct3Impl(const Ark_TranslateOptions* effect)
{
    CHECK_NULL_RETURN(effect, nullptr);
    TransitionEffectPeer* peer = PeerUtils::CreatePeer<TransitionEffectPeer>();
    auto emptyDimension = Dimension();
    auto x = Converter::OptConvert<CalcDimension>(effect->x).value_or(emptyDimension);
    auto y = Converter::OptConvert<CalcDimension>(effect->y).value_or(emptyDimension);
    auto z = Converter::OptConvert<CalcDimension>(effect->z).value_or(emptyDimension);
    TranslateOptions translate(x, y, z);
    peer->handler = AceType::MakeRefPtr<ChainedTranslateEffect>(translate);
    return peer;
}
Ark_TransitionEffect Construct4Impl(const Ark_RotateOptions* effect)
{
    CHECK_NULL_RETURN(effect, nullptr);
    TransitionEffectPeer* peer = PeerUtils::CreatePeer<TransitionEffectPeer>();
    auto emptyDimension = Dimension();
    auto defaultDimension = Dimension(50.0f, DimensionUnit::PERCENT);
    auto x = Converter::OptConvert<float>(effect->x.value).value_or(0);
    auto y = Converter::OptConvert<float>(effect->y.value).value_or(0);
    auto z = Converter::OptConvert<float>(effect->z.value).value_or(0);
    auto centerX = Converter::OptConvert<CalcDimension>(effect->centerX).value_or(defaultDimension);
    auto centerY = Converter::OptConvert<CalcDimension>(effect->centerY).value_or(defaultDimension);
    auto centerZ = Converter::OptConvert<CalcDimension>(effect->centerZ).value_or(emptyDimension);
    auto perspective = Converter::OptConvert<float>(effect->perspective).value_or(0);
    auto angle = Converter::OptConvert<float>(effect->angle).value_or(0);
    RotateOptions rotateOpts(x, y, z, angle, centerX, centerY, centerZ, perspective);
    peer->handler = AceType::MakeRefPtr<ChainedRotateEffect>(rotateOpts);
    return peer;
}
Ark_TransitionEffect Construct5Impl(const Ark_ScaleOptions* effect)
{
    CHECK_NULL_RETURN(effect, nullptr);
    TransitionEffectPeer* peer = PeerUtils::CreatePeer<TransitionEffectPeer>();
    auto emptyDimension = Dimension();
    auto x = Converter::OptConvert<float>(effect->x).value_or(0);
    auto y = Converter::OptConvert<float>(effect->y).value_or(0);
    auto z = Converter::OptConvert<float>(effect->z).value_or(0);
    auto centerX = Converter::OptConvert<CalcDimension>(effect->centerX).value_or(emptyDimension);
    auto centerY = Converter::OptConvert<CalcDimension>(effect->centerY).value_or(emptyDimension);
    ScaleOptions scaleOpts(x, y, z, centerX, centerY);
    peer->handler = AceType::MakeRefPtr<ChainedScaleEffect>(scaleOpts);
    return peer;
}
Ark_TransitionEffect Construct6Impl(const Ark_AsymmetricTransitionOption* effect)
{
    CHECK_NULL_RETURN(effect, nullptr);
    auto app = effect->appear;
    CHECK_NULL_RETURN(app, nullptr);
    auto disapp = effect->disappear;
    CHECK_NULL_RETURN(disapp, nullptr);
    TransitionEffectPeer* peer = PeerUtils::CreatePeer<TransitionEffectPeer>();
    peer->handler = AceType::MakeRefPtr<ChainedAsymmetricEffect>(app->handler, disapp->handler);
    return peer;
}
Ark_NativePointer GetFinalizerImpl()
{
    return reinterpret_cast<void *>(&DestroyPeerImpl);
}
Ark_TransitionEffect TranslateImpl(const Ark_TranslateOptions* options)
{
    return Construct3Impl(options);
}
Ark_TransitionEffect RotateImpl(const Ark_RotateOptions* options)
{
    return Construct4Impl(options);
}
Ark_TransitionEffect ScaleImpl(const Ark_ScaleOptions* options)
{
    return Construct5Impl(options);
}
Ark_TransitionEffect OpacityImpl(const Ark_Float64 alpha)
{
    return Construct1Impl(alpha);
}
Ark_TransitionEffect MoveImpl(Ark_TransitionEdge edge)
{
    return Construct2Impl(edge);
}
Ark_TransitionEffect AsymmetricImpl(Ark_TransitionEffect appear,
                                    Ark_TransitionEffect disappear)
{
    CHECK_NULL_RETURN(appear, nullptr);
    CHECK_NULL_RETURN(disappear, nullptr);
    TransitionEffectPeer* peer = PeerUtils::CreatePeer<TransitionEffectPeer>();
    peer->handler = AceType::MakeRefPtr<ChainedAsymmetricEffect>(appear->handler, disappear->handler);
    return peer;
}
Ark_TransitionEffect AnimationImpl(Ark_TransitionEffect peer,
                                   const Ark_AnimateParam* value)
{
    CHECK_NULL_RETURN(peer, nullptr);
    CHECK_NULL_RETURN(value, nullptr);
    AnimationOption option = Converter::Convert<AnimationOption>(*value);
    auto refOpt = std::make_shared<AnimationOption>(option);
    peer->handler->SetAnimationOption(refOpt);
    return peer;
}
Ark_TransitionEffect CombineImpl(Ark_TransitionEffect peer,
                                 Ark_TransitionEffect transitionEffect)
{
    CHECK_NULL_RETURN(peer, nullptr);
    CHECK_NULL_RETURN(transitionEffect, peer);
    auto lastEffect = peer;
    while (lastEffect->handler->GetNext() != nullptr) {
        lastEffect->handler = lastEffect->handler->GetNext();
    }
    const auto nextPeer = transitionEffect;
    lastEffect->handler->SetNext(nextPeer->handler);
    return peer;
}
Ark_TransitionEffect GetIDENTITYImpl()
{
    TransitionEffectPeer* peer = PeerUtils::CreatePeer<TransitionEffectPeer>();
    peer->handler = AceType::MakeRefPtr<ChainedIdentityEffect>();
    return peer;
}
void SetIDENTITYImpl(Ark_TransitionEffect IDENTITY)
{
}
Ark_TransitionEffect GetOPACITYImpl()
{
    TransitionEffectPeer* peer = PeerUtils::CreatePeer<TransitionEffectPeer>();
    peer->handler = AceType::MakeRefPtr<ChainedOpacityEffect>(0);
    return peer;
}
void SetOPACITYImpl(Ark_TransitionEffect OPACITY)
{
}
Ark_TransitionEffect GetSLIDEImpl()
{
    auto appear = AceType::MakeRefPtr<ChainedMoveEffect>(TransitionEdge::START);
    auto disappear = AceType::MakeRefPtr<ChainedMoveEffect>(TransitionEdge::END);
    TransitionEffectPeer* peer = PeerUtils::CreatePeer<TransitionEffectPeer>();
    peer->handler = AceType::MakeRefPtr<ChainedAsymmetricEffect>(appear, disappear);
    return peer;
}
void SetSLIDEImpl(Ark_TransitionEffect SLIDE)
{
}
Ark_TransitionEffect GetSLIDE_SWITCHImpl()
{
    TransitionEffectPeer* peer = PeerUtils::CreatePeer<TransitionEffectPeer>();
    peer->handler = AceType::MakeRefPtr<ChainedSlideSwitchEffect>();
    return peer;
}
void SetSLIDE_SWITCHImpl(Ark_TransitionEffect SLIDE_SWITCH)
{
}
} // TransitionEffectAccessor
const GENERATED_ArkUITransitionEffectAccessor* GetTransitionEffectAccessor()
{
    static const GENERATED_ArkUITransitionEffectAccessor TransitionEffectAccessorImpl {
        TransitionEffectAccessor::DestroyPeerImpl,
        TransitionEffectAccessor::Construct0Impl,
        TransitionEffectAccessor::Construct1Impl,
        TransitionEffectAccessor::Construct2Impl,
        TransitionEffectAccessor::Construct3Impl,
        TransitionEffectAccessor::Construct4Impl,
        TransitionEffectAccessor::Construct5Impl,
        TransitionEffectAccessor::Construct6Impl,
        TransitionEffectAccessor::GetFinalizerImpl,
        TransitionEffectAccessor::TranslateImpl,
        TransitionEffectAccessor::RotateImpl,
        TransitionEffectAccessor::ScaleImpl,
        TransitionEffectAccessor::OpacityImpl,
        TransitionEffectAccessor::MoveImpl,
        TransitionEffectAccessor::AsymmetricImpl,
        TransitionEffectAccessor::AnimationImpl,
        TransitionEffectAccessor::CombineImpl,
        TransitionEffectAccessor::GetIDENTITYImpl,
        TransitionEffectAccessor::SetIDENTITYImpl,
        TransitionEffectAccessor::GetOPACITYImpl,
        TransitionEffectAccessor::SetOPACITYImpl,
        TransitionEffectAccessor::GetSLIDEImpl,
        TransitionEffectAccessor::SetSLIDEImpl,
        TransitionEffectAccessor::GetSLIDE_SWITCHImpl,
        TransitionEffectAccessor::SetSLIDE_SWITCHImpl,
    };
    return &TransitionEffectAccessorImpl;
}

}
