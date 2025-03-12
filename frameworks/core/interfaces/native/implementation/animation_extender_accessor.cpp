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
void SetClipRectImpl(Ark_NativePointer node,
                     Ark_Float32 x,
                     Ark_Float32 y,
                     Ark_Float32 width,
                     Ark_Float32 height)
{
}
void OpenImplicitAnimationImpl(const Ark_AnimateParam* param)
{
}
void CloseImplicitAnimationImpl()
{
}
void StartDoubleAnimationImpl(Ark_NativePointer node,
                              const Ark_DoubleAnimationParam* param)
{
}
void AnimationTranslateImpl(Ark_NativePointer node,
                            const Ark_TranslateOptions* options)
{
}
} // AnimationExtenderAccessor
const GENERATED_ArkUIAnimationExtenderAccessor* GetAnimationExtenderAccessor()
{
    static const GENERATED_ArkUIAnimationExtenderAccessor AnimationExtenderAccessorImpl {
        AnimationExtenderAccessor::SetClipRectImpl,
        AnimationExtenderAccessor::OpenImplicitAnimationImpl,
        AnimationExtenderAccessor::CloseImplicitAnimationImpl,
        AnimationExtenderAccessor::StartDoubleAnimationImpl,
        AnimationExtenderAccessor::AnimationTranslateImpl,
    };
    return &AnimationExtenderAccessorImpl;
}

}
