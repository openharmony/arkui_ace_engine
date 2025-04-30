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
namespace TimePickerModifier {
Ark_NativePointer ConstructImpl(Ark_Int32 id,
                                Ark_Int32 flags)
{
    return {};
}
} // TimePickerModifier
namespace TimePickerInterfaceModifier {
void SetTimePickerOptionsImpl(Ark_NativePointer node,
                              const Opt_TimePickerOptions* options)
{
}
} // TimePickerInterfaceModifier
namespace TimePickerAttributeModifier {
void UseMilitaryTime0Impl(Ark_NativePointer node,
                          const Opt_Boolean* value)
{
}
void UseMilitaryTime1Impl(Ark_NativePointer node,
                          const Opt_Boolean* value)
{
}
void Loop0Impl(Ark_NativePointer node,
               const Opt_Boolean* value)
{
}
void Loop1Impl(Ark_NativePointer node,
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
void DateTimeOptions0Impl(Ark_NativePointer node,
                          const Opt_DateTimeOptions* value)
{
}
void DateTimeOptions1Impl(Ark_NativePointer node,
                          const Opt_DateTimeOptions* value)
{
}
void OnChange0Impl(Ark_NativePointer node,
                   const Opt_Callback_TimePickerResult_Void* value)
{
}
void OnChange1Impl(Ark_NativePointer node,
                   const Opt_OnTimePickerChangeCallback* value)
{
}
void OnEnterSelectedAreaImpl(Ark_NativePointer node,
                             const Opt_Callback_TimePickerResult_Void* value)
{
}
void EnableHapticFeedback0Impl(Ark_NativePointer node,
                               const Opt_Boolean* value)
{
}
void EnableHapticFeedback1Impl(Ark_NativePointer node,
                               const Opt_Boolean* value)
{
}
void DigitalCrownSensitivityImpl(Ark_NativePointer node,
                                 const Opt_CrownSensitivity* value)
{
}
void EnableCascadeImpl(Ark_NativePointer node,
                       const Opt_Boolean* value)
{
}
void _onChangeEvent_selectedImpl(Ark_NativePointer node,
                                 const Callback_Date_Void* callback)
{
}
} // TimePickerAttributeModifier
const GENERATED_ArkUITimePickerModifier* GetTimePickerModifier()
{
    static const GENERATED_ArkUITimePickerModifier ArkUITimePickerModifierImpl {
        TimePickerModifier::ConstructImpl,
        TimePickerInterfaceModifier::SetTimePickerOptionsImpl,
        TimePickerAttributeModifier::UseMilitaryTime0Impl,
        TimePickerAttributeModifier::UseMilitaryTime1Impl,
        TimePickerAttributeModifier::Loop0Impl,
        TimePickerAttributeModifier::Loop1Impl,
        TimePickerAttributeModifier::DisappearTextStyle0Impl,
        TimePickerAttributeModifier::DisappearTextStyle1Impl,
        TimePickerAttributeModifier::TextStyle0Impl,
        TimePickerAttributeModifier::TextStyle1Impl,
        TimePickerAttributeModifier::SelectedTextStyle0Impl,
        TimePickerAttributeModifier::SelectedTextStyle1Impl,
        TimePickerAttributeModifier::DateTimeOptions0Impl,
        TimePickerAttributeModifier::DateTimeOptions1Impl,
        TimePickerAttributeModifier::OnChange0Impl,
        TimePickerAttributeModifier::OnChange1Impl,
        TimePickerAttributeModifier::OnEnterSelectedAreaImpl,
        TimePickerAttributeModifier::EnableHapticFeedback0Impl,
        TimePickerAttributeModifier::EnableHapticFeedback1Impl,
        TimePickerAttributeModifier::DigitalCrownSensitivityImpl,
        TimePickerAttributeModifier::EnableCascadeImpl,
        TimePickerAttributeModifier::_onChangeEvent_selectedImpl,
    };
    return &ArkUITimePickerModifierImpl;
}

}
