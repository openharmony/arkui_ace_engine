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
namespace AnimatorInterfaceModifier {
void SetAnimatorOptionsImpl(Ark_NativePointer node,
                            const Ark_String* value)
{
}
} // AnimatorInterfaceModifier
namespace AnimatorAttributeModifier {
void StateImpl(Ark_NativePointer node,
               enum Ark_AnimationStatus value)
{
}
void DurationImpl(Ark_NativePointer node,
                  const Ark_Number* value)
{
}
void CurveImpl(Ark_NativePointer node,
               enum Ark_Curve value)
{
}
void DelayImpl(Ark_NativePointer node,
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
void PlayModeImpl(Ark_NativePointer node,
                  enum Ark_PlayMode value)
{
}
void MotionImpl(Ark_NativePointer node,
                const Type_AnimatorAttribute_motion_Arg0* value)
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
void OnFrameImpl(Ark_NativePointer node,
                 Ark_Function event)
{
}
} // AnimatorAttributeModifier
const GENERATED_ArkUIAnimatorModifier* GetAnimatorModifier()
{
    static const GENERATED_ArkUIAnimatorModifier ArkUIAnimatorModifierImpl {
        AnimatorInterfaceModifier::SetAnimatorOptionsImpl,
        AnimatorAttributeModifier::StateImpl,
        AnimatorAttributeModifier::DurationImpl,
        AnimatorAttributeModifier::CurveImpl,
        AnimatorAttributeModifier::DelayImpl,
        AnimatorAttributeModifier::FillModeImpl,
        AnimatorAttributeModifier::IterationsImpl,
        AnimatorAttributeModifier::PlayModeImpl,
        AnimatorAttributeModifier::MotionImpl,
        AnimatorAttributeModifier::OnStartImpl,
        AnimatorAttributeModifier::OnPauseImpl,
        AnimatorAttributeModifier::OnRepeatImpl,
        AnimatorAttributeModifier::OnCancelImpl,
        AnimatorAttributeModifier::OnFinishImpl,
        AnimatorAttributeModifier::OnFrameImpl,
    };
    return &ArkUIAnimatorModifierImpl;
}

}
