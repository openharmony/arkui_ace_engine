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
namespace DatePickerModifier {
Ark_NativePointer ConstructImpl(Ark_Int32 id,
                                Ark_Int32 flags)
{
    return {};
}
} // DatePickerModifier
namespace DatePickerInterfaceModifier {
void SetDatePickerOptionsImpl(Ark_NativePointer node,
                              const Opt_DatePickerOptions* options)
{
}
} // DatePickerInterfaceModifier
namespace DatePickerAttributeModifier {
void Lunar0Impl(Ark_NativePointer node,
                const Opt_Boolean* value)
{
}
void Lunar1Impl(Ark_NativePointer node,
                const Opt_Boolean* value)
{
}
void DisappearTextStyle0Impl(Ark_NativePointer node,
                             const Opt_PickerTextStyle* value)
{
}
void DisappearTextStyle1Impl(Ark_NativePointer node,
                             const Opt_PickerTextStyle* value)
{
}
void TextStyle0Impl(Ark_NativePointer node,
                    const Opt_PickerTextStyle* value)
{
}
void TextStyle1Impl(Ark_NativePointer node,
                    const Opt_PickerTextStyle* value)
{
}
void SelectedTextStyle0Impl(Ark_NativePointer node,
                            const Opt_PickerTextStyle* value)
{
}
void SelectedTextStyle1Impl(Ark_NativePointer node,
                            const Opt_PickerTextStyle* value)
{
}
void OnChangeImpl(Ark_NativePointer node,
                  const Opt_Callback_DatePickerResult_Void* value)
{
}
void OnDateChange0Impl(Ark_NativePointer node,
                       const Opt_Callback_Date_Void* value)
{
}
void OnDateChange1Impl(Ark_NativePointer node,
                       const Opt_Callback_Date_Void* value)
{
}
void DigitalCrownSensitivityImpl(Ark_NativePointer node,
                                 const Opt_CrownSensitivity* value)
{
}
void EnableHapticFeedbackImpl(Ark_NativePointer node,
                              const Opt_Boolean* value)
{
}
void _onChangeEvent_selectedImpl(Ark_NativePointer node,
                                 const Callback_Date_Void* callback)
{
}
} // DatePickerAttributeModifier
const GENERATED_ArkUIDatePickerModifier* GetDatePickerModifier()
{
    static const GENERATED_ArkUIDatePickerModifier ArkUIDatePickerModifierImpl {
        DatePickerModifier::ConstructImpl,
        DatePickerInterfaceModifier::SetDatePickerOptionsImpl,
        DatePickerAttributeModifier::Lunar0Impl,
        DatePickerAttributeModifier::Lunar1Impl,
        DatePickerAttributeModifier::DisappearTextStyle0Impl,
        DatePickerAttributeModifier::DisappearTextStyle1Impl,
        DatePickerAttributeModifier::TextStyle0Impl,
        DatePickerAttributeModifier::TextStyle1Impl,
        DatePickerAttributeModifier::SelectedTextStyle0Impl,
        DatePickerAttributeModifier::SelectedTextStyle1Impl,
        DatePickerAttributeModifier::OnChangeImpl,
        DatePickerAttributeModifier::OnDateChange0Impl,
        DatePickerAttributeModifier::OnDateChange1Impl,
        DatePickerAttributeModifier::DigitalCrownSensitivityImpl,
        DatePickerAttributeModifier::EnableHapticFeedbackImpl,
        DatePickerAttributeModifier::_onChangeEvent_selectedImpl,
    };
    return &ArkUIDatePickerModifierImpl;
}

}
