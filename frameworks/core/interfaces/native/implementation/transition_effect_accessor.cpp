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

namespace OHOS::Ace::NG::GeneratedModifier {
namespace TransitionEffectAccessor {
void DestroyPeerImpl(Ark_TransitionEffect peer)
{
    auto peerImpl = reinterpret_cast<TransitionEffectPeerImpl *>(peer);
    if (peerImpl) {
        delete peerImpl;
    }
}
Ark_TransitionEffect Construct0Impl(const Ark_String* type)
{
    return {};
}
Ark_TransitionEffect Construct1Impl(const Ark_Number* effect)
{
    return {};
}
Ark_TransitionEffect Construct2Impl(Ark_TransitionEdge effect)
{
    return {};
}
Ark_TransitionEffect Construct3Impl(const Ark_TranslateOptions* effect)
{
    return {};
}
Ark_TransitionEffect Construct4Impl(const Ark_RotateOptions* effect)
{
    return {};
}
Ark_TransitionEffect Construct5Impl(const Ark_ScaleOptions* effect)
{
    return {};
}
Ark_TransitionEffect Construct6Impl(const Ark_AsymmetricTransitionOption* effect)
{
    return {};
}
Ark_NativePointer GetFinalizerImpl()
{
    return reinterpret_cast<void *>(&DestroyPeerImpl);
}
Ark_TransitionEffect TranslateImpl(const Ark_TranslateOptions* options)
{
    return {};
}
Ark_TransitionEffect RotateImpl(const Ark_RotateOptions* options)
{
    return {};
}
Ark_TransitionEffect ScaleImpl(const Ark_ScaleOptions* options)
{
    return {};
}
Ark_TransitionEffect OpacityImpl(const Ark_Number* alpha)
{
    return {};
}
Ark_TransitionEffect MoveImpl(Ark_TransitionEdge edge)
{
    return {};
}
Ark_TransitionEffect AsymmetricImpl(Ark_TransitionEffect appear,
                                    Ark_TransitionEffect disappear)
{
    return {};
}
Ark_TransitionEffect AnimationImpl(Ark_TransitionEffect peer,
                                   const Ark_AnimateParam* value)
{
    return {};
}
Ark_TransitionEffect CombineImpl(Ark_TransitionEffect peer,
                                 Ark_TransitionEffect transitionEffect)
{
    return {};
}
Ark_TransitionEffect GetIDENTITYImpl()
{
    return {};
}
Ark_TransitionEffect GetOPACITYImpl()
{
    return {};
}
Ark_TransitionEffect GetSLIDEImpl()
{
    return {};
}
Ark_TransitionEffect GetSLIDE_SWITCHImpl()
{
    return {};
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
        TransitionEffectAccessor::GetOPACITYImpl,
        TransitionEffectAccessor::GetSLIDEImpl,
        TransitionEffectAccessor::GetSLIDE_SWITCHImpl,
    };
    return &TransitionEffectAccessorImpl;
}

struct TransitionEffectPeer {
    virtual ~TransitionEffectPeer() = default;
};
}
