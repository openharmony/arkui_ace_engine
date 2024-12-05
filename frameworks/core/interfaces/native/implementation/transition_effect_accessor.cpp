/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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

const auto TRANSLATE_TOKEN = "translate";
const auto ROTATE_TOKEN = "rotate";
const auto SCALE_TOKEN = "scale";
const auto OPACITY_TOKEN = "opacity";
const auto MOVE_TOKEN = "move";

void DestroyPeerImpl(TransitionEffectPeer* peer)
{
    CHECK_NULL_VOID(peer);
    peer->handler = nullptr;
    delete peer;
}
TransitionEffectPeer* CtorImpl(const Ark_String* type,
                               const Ark_TransitionEffects* effect)
{
    auto valueText = Converter::Convert<std::string>(*type);
    TransitionEffectPeer* peer = new TransitionEffectPeer();
    auto emptyDimension = Dimension();
    if (valueText == TRANSLATE_TOKEN) {
        auto x = Converter::OptConvert<CalcDimension>(effect->translate.x.value);
        auto y = Converter::OptConvert<CalcDimension>(effect->translate.y.value);
        auto z = Converter::OptConvert<CalcDimension>(effect->translate.z.value);
        TranslateOptions translate(
            x.value_or(emptyDimension),
            y.value_or(emptyDimension),
            z.value_or(emptyDimension));
        peer->handler = new ChainedTranslateEffect(translate);
    } else if (valueText == ROTATE_TOKEN) {
        auto x = Converter::Convert<float>(effect->rotate.x.value);
        auto y = Converter::Convert<float>(effect->rotate.y.value);
        auto z = Converter::Convert<float>(effect->rotate.z.value);
        auto centerX = Converter::OptConvert<CalcDimension>(effect->rotate.centerX.value);
        auto centerY = Converter::OptConvert<CalcDimension>(effect->rotate.centerY.value);
        auto centerZ = Converter::OptConvert<CalcDimension>(effect->rotate.centerZ.value);
        auto perspective = Converter::Convert<float>(effect->rotate.centerZ.value);
        auto angle = Converter::OptConvert<float>(effect->rotate.angle);
        RotateOptions rotate(x, y, z, angle.value_or(0),
            centerX.value_or(emptyDimension),
            centerY.value_or(emptyDimension),
            centerZ.value_or(emptyDimension),
            perspective);
        peer->handler = new ChainedRotateEffect(rotate);
    } else if (valueText == SCALE_TOKEN) {
        auto x = Converter::Convert<float>(effect->scale.x.value);
        auto y = Converter::Convert<float>(effect->scale.y.value);
        auto z = Converter::Convert<float>(effect->scale.z.value);
        auto centerX = Converter::OptConvert<CalcDimension>(effect->scale.centerX.value);
        auto centerY = Converter::OptConvert<CalcDimension>(effect->scale.centerY.value);
        ScaleOptions scale(x, y, z, centerX.value_or(emptyDimension), centerY.value_or(emptyDimension));
        peer->handler = new ChainedScaleEffect(scale);
    } else if (valueText == OPACITY_TOKEN) {
        auto opacity = Converter::Convert<float>(effect->opacity);
        peer->handler = new ChainedOpacityEffect(opacity);
    } else if (valueText == MOVE_TOKEN) {
        auto move = Converter::OptConvert<TransitionEdge>(effect->move);
        peer->handler = new ChainedMoveEffect(move.value_or(TransitionEdge::TOP));
    }
    return peer;
}
Ark_NativePointer GetFinalizerImpl()
{
    return reinterpret_cast<void *>(&DestroyPeerImpl);
}
Ark_NativePointer TranslateImpl(const Ark_TranslateOptions* options)
{
    CHECK_NULL_RETURN(options, nullptr);
    Ark_String type = Converter::ArkValue<Ark_String>(TRANSLATE_TOKEN);
    Ark_TransitionEffects effects {
        .translate = *options
    };
    return CtorImpl(&type, &effects);
}
Ark_NativePointer RotateImpl(const Ark_RotateOptions* options)
{
    CHECK_NULL_RETURN(options, nullptr);
    Ark_String type = Converter::ArkValue<Ark_String>(ROTATE_TOKEN);
    Ark_TransitionEffects effects {
        .rotate = *options
    };
    return CtorImpl(&type, &effects);
}
Ark_NativePointer ScaleImpl(const Ark_ScaleOptions* options)
{
    CHECK_NULL_RETURN(options, nullptr);
    Ark_String type = Converter::ArkValue<Ark_String>(SCALE_TOKEN);
    Ark_TransitionEffects effects {
        .scale = *options
    };
    return CtorImpl(&type, &effects);
}
Ark_NativePointer OpacityImpl(const Ark_Number* alpha)
{
    CHECK_NULL_RETURN(alpha, nullptr);
    Ark_String type = Converter::ArkValue<Ark_String>(OPACITY_TOKEN);
    Ark_TransitionEffects effects {
        .opacity = *alpha
    };
    return CtorImpl(&type, &effects);
}
Ark_NativePointer MoveImpl(Ark_TransitionEdge edge)
{
    Ark_String type = Converter::ArkValue<Ark_String>(MOVE_TOKEN);
    Ark_TransitionEffects effects {
        .move = edge
    };
    return CtorImpl(&type, &effects);
}
Ark_NativePointer AsymmetricImpl(const Ark_TransitionEffect* appear,
                                 const Ark_TransitionEffect* disappear)
{
    CHECK_NULL_RETURN(appear, nullptr);
    CHECK_NULL_RETURN(disappear, nullptr);
    LOGE("TransitionEffectAccessor::AsymmetricImpl Not implemented.");
    return nullptr;
}
Ark_NativePointer AnimationImpl(TransitionEffectPeer* peer,
                                const Ark_AnimateParam* value)
{
    CHECK_NULL_RETURN(peer, nullptr);
    LOGE("TransitionEffectAccessor::AnimationImpl Return value must be TransitionEffect here.");
    return nullptr;
}
Ark_NativePointer CombineImpl(TransitionEffectPeer* peer,
                              const Ark_TransitionEffect* transitionEffect)
{
    CHECK_NULL_RETURN(peer, nullptr);
    LOGE("ransitionEffectAccessor::CombineImpl Return value must be TransitionEffect here.");
    return nullptr;
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
    };
    return &TransitionEffectAccessorImpl;
}

}
