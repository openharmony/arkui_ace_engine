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
namespace StepperModifier {
Ark_NativePointer ConstructImpl(Ark_Int32 id,
                                Ark_Int32 flags)
{
    return {};
}
} // StepperModifier
namespace StepperInterfaceModifier {
void SetStepperOptionsImpl(Ark_NativePointer node,
                           const Opt_Literal_Number_index* value)
{
}
} // StepperInterfaceModifier
namespace StepperAttributeModifier {
void OnFinishImpl(Ark_NativePointer node,
                  const Opt_Callback_Void* value)
{
}
void OnSkipImpl(Ark_NativePointer node,
                const Opt_Callback_Void* value)
{
}
void OnChangeImpl(Ark_NativePointer node,
                  const Opt_Callback_Number_Number_Void* value)
{
}
void OnNextImpl(Ark_NativePointer node,
                const Opt_Callback_Number_Number_Void* value)
{
}
void OnPreviousImpl(Ark_NativePointer node,
                    const Opt_Callback_Number_Number_Void* value)
{
}
void _onChangeEvent_indexImpl(Ark_NativePointer node,
                              const Callback_Number_Void* callback)
{
}
} // StepperAttributeModifier
const GENERATED_ArkUIStepperModifier* GetStepperModifier()
{
    static const GENERATED_ArkUIStepperModifier ArkUIStepperModifierImpl {
        StepperModifier::ConstructImpl,
        StepperInterfaceModifier::SetStepperOptionsImpl,
        StepperAttributeModifier::OnFinishImpl,
        StepperAttributeModifier::OnSkipImpl,
        StepperAttributeModifier::OnChangeImpl,
        StepperAttributeModifier::OnNextImpl,
        StepperAttributeModifier::OnPreviousImpl,
        StepperAttributeModifier::_onChangeEvent_indexImpl,
    };
    return &ArkUIStepperModifierImpl;
}

}
