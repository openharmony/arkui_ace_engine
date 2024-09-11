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

#include "arkoala_api_generated.h"

namespace OHOS::Ace::NG::GeneratedModifier {
namespace ImageAnimatorInterfaceModifier {
void SetImageAnimatorOptionsImpl(Ark_NativePointer node)
{
}
} // ImageAnimatorInterfaceModifier
namespace ImageAnimatorAttributeModifier {
void ImagesImpl(Ark_NativePointer node,
                const Array_ImageFrameInfo* value)
{
}
void StateImpl(Ark_NativePointer node,
               enum Ark_AnimationStatus value)
{
}
void DurationImpl(Ark_NativePointer node,
                  const Ark_Number* value)
{
}
void ReverseImpl(Ark_NativePointer node,
                 Ark_Boolean value)
{
}
void FixedSizeImpl(Ark_NativePointer node,
                   Ark_Boolean value)
{
}
void PreDecodeImpl(Ark_NativePointer node,
                   const Ark_Number* value)
{
}
void FillModeImpl(Ark_NativePointer node,
                  enum Ark_FillMode value)
{
}
void IterationsImpl(Ark_NativePointer node,
                    const Ark_Number* value)
{
}
void OnStartImpl(Ark_NativePointer node,
                 Ark_Function event)
{
}
void OnPauseImpl(Ark_NativePointer node,
                 Ark_Function event)
{
}
void OnRepeatImpl(Ark_NativePointer node,
                  Ark_Function event)
{
}
void OnCancelImpl(Ark_NativePointer node,
                  Ark_Function event)
{
}
void OnFinishImpl(Ark_NativePointer node,
                  Ark_Function event)
{
}
} // ImageAnimatorAttributeModifier
const GENERATED_ArkUIImageAnimatorModifier* GetImageAnimatorModifier()
{
    static const GENERATED_ArkUIImageAnimatorModifier ArkUIImageAnimatorModifierImpl {
        ImageAnimatorInterfaceModifier::SetImageAnimatorOptionsImpl,
        ImageAnimatorAttributeModifier::ImagesImpl,
        ImageAnimatorAttributeModifier::StateImpl,
        ImageAnimatorAttributeModifier::DurationImpl,
        ImageAnimatorAttributeModifier::ReverseImpl,
        ImageAnimatorAttributeModifier::FixedSizeImpl,
        ImageAnimatorAttributeModifier::PreDecodeImpl,
        ImageAnimatorAttributeModifier::FillModeImpl,
        ImageAnimatorAttributeModifier::IterationsImpl,
        ImageAnimatorAttributeModifier::OnStartImpl,
        ImageAnimatorAttributeModifier::OnPauseImpl,
        ImageAnimatorAttributeModifier::OnRepeatImpl,
        ImageAnimatorAttributeModifier::OnCancelImpl,
        ImageAnimatorAttributeModifier::OnFinishImpl,
    };
    return &ArkUIImageAnimatorModifierImpl;
}

}
