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
namespace AnimationExtenderAccessor {
void DestroyPeerImpl(AnimationExtenderPeer* peer)
{
}
Ark_NativePointer CtorImpl()
{
    return nullptr;
}
Ark_NativePointer GetFinalizerImpl()
{
    return reinterpret_cast<void *>(&DestroyPeerImpl);
}
void SetClipRectImpl(Ark_NativePointer peer,
                     const Ark_Number* left,
                     const Ark_Number* top,
                     const Ark_Number* right,
                     const Ark_Number* bottom)
{
}
void OpenImplicitAnimationImpl(Ark_NativePointer peer,
                               const Ark_AnimateParam* param)
{
}
void CloseImplicitAnimationImpl(Ark_NativePointer node)
{
}
void StartDoubleAnimationImpl(Ark_NativePointer peer,
                              const Ark_DoubleAnimationParam* param)
{
}
} // AnimationExtenderAccessor
const GENERATED_ArkUIAnimationExtenderAccessor* GetAnimationExtenderAccessor()
{
    static const GENERATED_ArkUIAnimationExtenderAccessor AnimationExtenderAccessorImpl {
        AnimationExtenderAccessor::DestroyPeerImpl,
        AnimationExtenderAccessor::CtorImpl,
        AnimationExtenderAccessor::GetFinalizerImpl,
        AnimationExtenderAccessor::SetClipRectImpl,
        AnimationExtenderAccessor::OpenImplicitAnimationImpl,
        AnimationExtenderAccessor::CloseImplicitAnimationImpl,
        AnimationExtenderAccessor::StartDoubleAnimationImpl,
    };
    return &AnimationExtenderAccessorImpl;
}

}
