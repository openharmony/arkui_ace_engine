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
const auto TRANSLATE_TOKEN = "translate";
const auto ROTATE_TOKEN = "rotate";
const auto SCALE_TOKEN = "scale";
const auto OPACITY_TOKEN = "opacity";
const auto MOVE_TOKEN = "move";
const auto ASYMMETRIC_TOKEN = "asymmetric";

void DestroyPeerImpl(Ark_TransitionEffect peer)
{
    PeerUtils::DestroyPeer(peer);
}
RefPtr<OHOS::Ace::NG::ChainedRotateEffect> HandleRotate(const Ark_RotateOptions& rotate)
{
    auto emptyDimension = Dimension();
    auto x = Converter::Convert<float>(rotate.x.value);
    auto y = Converter::Convert<float>(rotate.y.value);
    auto z = Converter::Convert<float>(rotate.z.value);
    auto centerX = Converter::OptConvert<CalcDimension>(rotate.centerX.value);
    auto centerY = Converter::OptConvert<CalcDimension>(rotate.centerY.value);
    auto centerZ = Converter::OptConvert<CalcDimension>(rotate.centerZ.value);
    auto perspective = Converter::Convert<float>(rotate.perspective.value);
    auto angle = Converter::OptConvert<float>(rotate.angle);
    RotateOptions rotateOpts(x, y, z, angle.value_or(0),
        centerX.value_or(emptyDimension),
        centerY.value_or(emptyDimension),
        centerZ.value_or(emptyDimension), perspective);
    return AceType::MakeRefPtr<ChainedRotateEffect>(rotateOpts);
}
RefPtr<OHOS::Ace::NG::ChainedScaleEffect> HandleScale(const Ark_ScaleOptions& scale)
{
    auto emptyDimension = Dimension();
    auto x = Converter::Convert<float>(scale.x.value);
    auto y = Converter::Convert<float>(scale.y.value);
    auto z = Converter::Convert<float>(scale.z.value);
    auto centerX = Converter::OptConvert<CalcDimension>(scale.centerX.value);
    auto centerY = Converter::OptConvert<CalcDimension>(scale.centerY.value);
    ScaleOptions scaleOpts(x, y, z, centerX.value_or(emptyDimension), centerY.value_or(emptyDimension));
    return AceType::MakeRefPtr<ChainedScaleEffect>(scaleOpts);
}
Ark_TransitionEffect CtorImpl(const Ark_String* type)
{
    CHECK_NULL_RETURN(type, nullptr);
    auto valueText = Converter::Convert<std::string>(*type);
    TransitionEffectPeer* peer = PeerUtils::CreatePeer<TransitionEffectPeer>();
#ifdef WRONG_GEN
    auto emptyDimension = Dimension();
    if (valueText == TRANSLATE_TOKEN) {
        auto x = Converter::OptConvert<CalcDimension>(effect->translate.x.value);
        auto y = Converter::OptConvert<CalcDimension>(effect->translate.y.value);
        auto z = Converter::OptConvert<CalcDimension>(effect->translate.z.value);
        TranslateOptions translate(x.value_or(emptyDimension), y.value_or(emptyDimension), z.value_or(emptyDimension));
        peer->handler = AceType::MakeRefPtr<ChainedTranslateEffect>(translate);
    } else if (valueText == IDENTITY_TOKEN) {
        peer->handler = AceType::MakeRefPtr<ChainedIdentityEffect>();
    } else if (valueText == SLIDE_SWITCH_TOKEN) {
        peer->handler = AceType::MakeRefPtr<ChainedSlideSwitchEffect>();
    } else if (valueText == ROTATE_TOKEN) {
        peer->handler = HandleRotate(*effect);
    } else if (valueText == SCALE_TOKEN) {
        peer->handler = HandleScale(*effect);
    } else if (valueText == OPACITY_TOKEN) {
        auto opacity = Converter::Convert<float>(effect->opacity);
        peer->handler = AceType::MakeRefPtr<ChainedOpacityEffect>(opacity);
    } else if (valueText == MOVE_TOKEN) {
        auto move = Converter::OptConvert<TransitionEdge>(effect->move);
        peer->handler = AceType::MakeRefPtr<ChainedMoveEffect>(move.value_or(TransitionEdge::TOP));
    } else if (valueText == ASYMMETRIC_TOKEN) {
        CHECK_NULL_RETURN(effect, nullptr);
        auto app = effect->asymmetric.appear;
        CHECK_NULL_RETURN(app, nullptr);
        auto disapp = effect->asymmetric.disappear;
        CHECK_NULL_RETURN(disapp, nullptr);
        peer->handler = AceType::MakeRefPtr<ChainedAsymmetricEffect>(app->handler, disapp->handler);
    }
#endif
    return peer;
}
Ark_NativePointer GetFinalizerImpl()
{
    return reinterpret_cast<void *>(&DestroyPeerImpl);
}
Ark_TransitionEffect TranslateImpl(const Ark_TranslateOptions* options)
{
    CHECK_NULL_RETURN(options, nullptr);
    Ark_String type = Converter::ArkValue<Ark_String>(TRANSLATE_TOKEN, Converter::FC);
    return CtorImpl(&type);
}
Ark_TransitionEffect RotateImpl(const Ark_RotateOptions* options)
{
    CHECK_NULL_RETURN(options, nullptr);
    Ark_String type = Converter::ArkValue<Ark_String>(ROTATE_TOKEN, Converter::FC);
    return CtorImpl(&type);
}
Ark_TransitionEffect ScaleImpl(const Ark_ScaleOptions* options)
{
    CHECK_NULL_RETURN(options, nullptr);
    Ark_String type = Converter::ArkValue<Ark_String>(SCALE_TOKEN, Converter::FC);
    return CtorImpl(&type);
}
Ark_TransitionEffect OpacityImpl(const Ark_Number* alpha)
{
    CHECK_NULL_RETURN(alpha, nullptr);
    Ark_String type = Converter::ArkValue<Ark_String>(OPACITY_TOKEN, Converter::FC);
    return CtorImpl(&type);
}
Ark_TransitionEffect MoveImpl(Ark_TransitionEdge edge)
{
    Ark_String type = Converter::ArkValue<Ark_String>(MOVE_TOKEN, Converter::FC);
    return CtorImpl(&type);
}
Ark_TransitionEffect AsymmetricImpl(Ark_TransitionEffect appear,
                                    Ark_TransitionEffect disappear)
{
    CHECK_NULL_RETURN(appear, nullptr);
    CHECK_NULL_RETURN(disappear, nullptr);

    Ark_String type = Converter::ArkValue<Ark_String>(ASYMMETRIC_TOKEN, Converter::FC);
    return CtorImpl(&type);
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
        TransitionEffectAccessor::CtorImpl,
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
