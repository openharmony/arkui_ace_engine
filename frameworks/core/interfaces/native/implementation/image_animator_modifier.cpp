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
namespace ImageAnimatorModifier {
Ark_NativePointer ConstructImpl(Ark_Int32 id,
                                Ark_Int32 flags)
{
    return {};
}
} // ImageAnimatorModifier
namespace ImageAnimatorInterfaceModifier {
void SetImageAnimatorOptionsImpl(Ark_NativePointer node)
{
}
} // ImageAnimatorInterfaceModifier
namespace ImageAnimatorAttributeModifier {
void ImagesImpl(Ark_NativePointer node,
                const Opt_Array_ImageFrameInfo* value)
{
}
void StateImpl(Ark_NativePointer node,
               const Opt_AnimationStatus* value)
{
}
void DurationImpl(Ark_NativePointer node,
                  const Opt_Number* value)
{
}
void ReverseImpl(Ark_NativePointer node,
                 const Opt_Boolean* value)
{
}
void FixedSizeImpl(Ark_NativePointer node,
                   const Opt_Boolean* value)
{
}
void PreDecodeImpl(Ark_NativePointer node,
                   const Opt_Number* value)
{
}
void FillModeImpl(Ark_NativePointer node,
                  const Opt_FillMode* value)
{
}
void IterationsImpl(Ark_NativePointer node,
                    const Opt_Number* value)
{
}
void MonitorInvisibleAreaImpl(Ark_NativePointer node,
                              const Opt_Boolean* value)
{
}
void OnStartImpl(Ark_NativePointer node,
                 const Opt_Callback_Void* value)
{
}
void OnPauseImpl(Ark_NativePointer node,
                 const Opt_Callback_Void* value)
{
}
void OnRepeatImpl(Ark_NativePointer node,
                  const Opt_Callback_Void* value)
{
}
void OnCancelImpl(Ark_NativePointer node,
                  const Opt_Callback_Void* value)
{
}
void OnFinishImpl(Ark_NativePointer node,
                  const Opt_Callback_Void* value)
{
}
} // ImageAnimatorAttributeModifier
const GENERATED_ArkUIImageAnimatorModifier* GetImageAnimatorModifier()
{
    static const GENERATED_ArkUIImageAnimatorModifier ArkUIImageAnimatorModifierImpl {
        ImageAnimatorModifier::ConstructImpl,
        ImageAnimatorInterfaceModifier::SetImageAnimatorOptionsImpl,
        ImageAnimatorAttributeModifier::ImagesImpl,
        ImageAnimatorAttributeModifier::StateImpl,
        ImageAnimatorAttributeModifier::DurationImpl,
        ImageAnimatorAttributeModifier::ReverseImpl,
        ImageAnimatorAttributeModifier::FixedSizeImpl,
        ImageAnimatorAttributeModifier::PreDecodeImpl,
        ImageAnimatorAttributeModifier::FillModeImpl,
        ImageAnimatorAttributeModifier::IterationsImpl,
        ImageAnimatorAttributeModifier::MonitorInvisibleAreaImpl,
        ImageAnimatorAttributeModifier::OnStartImpl,
        ImageAnimatorAttributeModifier::OnPauseImpl,
        ImageAnimatorAttributeModifier::OnRepeatImpl,
        ImageAnimatorAttributeModifier::OnCancelImpl,
        ImageAnimatorAttributeModifier::OnFinishImpl,
    };
    return &ArkUIImageAnimatorModifierImpl;
}

}
