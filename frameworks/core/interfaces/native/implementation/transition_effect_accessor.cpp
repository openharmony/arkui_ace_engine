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

void DestroyPeerImpl(TransitionEffectPeer* peer)
{
    CHECK_NULL_VOID(peer);
    peer->handler = nullptr;
    delete peer;
}
TransitionEffectPeer* CtorImpl(const Ark_String* type,
                               const Ark_TransitionEffects* effect)
{
    return new TransitionEffectPeer();
}
Ark_NativePointer GetFinalizerImpl()
{
    return reinterpret_cast<void *>(&DestroyPeerImpl);
}
Ark_NativePointer TranslateImpl(const Ark_TranslateOptions* options)
{
    CHECK_NULL_RETURN(options, 0);
    auto type = Converter::ArkValue<Ark_String>("static");
    Ark_TransitionEffects effects {
        .translate = *options
    };
    return CtorImpl(&type, &effects);
}
Ark_NativePointer RotateImpl(const Ark_RotateOptions* options)
{
    CHECK_NULL_RETURN(options, 0);
    auto type = Converter::ArkValue<Ark_String>("static");
    Ark_TransitionEffects effects {
        .rotate = *options
    };
    return CtorImpl(&type, &effects);
}
Ark_NativePointer ScaleImpl(const Ark_ScaleOptions* options)
{
    CHECK_NULL_RETURN(options, nullptr);
    auto type = Converter::ArkValue<Ark_String>("static");
    Ark_TransitionEffects effects {
        .scale = *options
    };
    return CtorImpl(&type, &effects);
}
Ark_NativePointer OpacityImpl(const Ark_Number* alpha)
{
    CHECK_NULL_RETURN(alpha, nullptr);
    auto type = Converter::ArkValue<Ark_String>("static");
    Ark_TransitionEffects effects {
        .opacity = *alpha
    };
    return CtorImpl(&type, &effects);
}
Ark_NativePointer MoveImpl(Ark_TransitionEdge edge)
{
    auto type = Converter::ArkValue<Ark_String>("static");
    Ark_TransitionEffects effects {
        .move = edge
    };
    return CtorImpl(&type, &effects);
}
Ark_NativePointer AsymmetricImpl(const Ark_TransitionEffect* appear,
                                 const Ark_TransitionEffect* disappear)
{
    LOGE("TransitionEffectAccessor::AsymmetricImpl Not implemented.");
    return 0;
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
