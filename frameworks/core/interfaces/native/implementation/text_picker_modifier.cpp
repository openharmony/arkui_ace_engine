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
namespace TextPickerModifier {
Ark_NativePointer ConstructImpl(Ark_Int32 id,
                                Ark_Int32 flags)
{
    return {};
}
} // TextPickerModifier
namespace TextPickerInterfaceModifier {
void SetTextPickerOptionsImpl(Ark_NativePointer node,
                              const Opt_TextPickerOptions* options)
{
}
} // TextPickerInterfaceModifier
namespace TextPickerAttributeModifier {
void DefaultPickerItemHeight0Impl(Ark_NativePointer node,
                                  const Opt_Union_Number_String* value)
{
}
void DefaultPickerItemHeight1Impl(Ark_NativePointer node,
                                  const Opt_Union_Number_String* value)
{
}
void CanLoop0Impl(Ark_NativePointer node,
                  const Opt_Boolean* value)
{
}
void CanLoop1Impl(Ark_NativePointer node,
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
void DisableTextStyleAnimationImpl(Ark_NativePointer node,
                                   const Opt_Boolean* value)
{
}
void DefaultTextStyleImpl(Ark_NativePointer node,
                          const Opt_TextPickerTextStyle* value)
{
}
void OnAcceptImpl(Ark_NativePointer node,
                  const Opt_Callback_String_Number_Void* value)
{
}
void OnCancelImpl(Ark_NativePointer node,
                  const Opt_Callback_Void* value)
{
}
void OnChange0Impl(Ark_NativePointer node,
                   const Opt_Type_TextPickerAttribute_onChange_callback* value)
{
}
void OnChange1Impl(Ark_NativePointer node,
                   const Opt_OnTextPickerChangeCallback* value)
{
}
void OnScrollStop0Impl(Ark_NativePointer node,
                       const Opt_TextPickerScrollStopCallback* value)
{
}
void OnScrollStop1Impl(Ark_NativePointer node,
                       const Opt_TextPickerScrollStopCallback* value)
{
}
void OnEnterSelectedAreaImpl(Ark_NativePointer node,
                             const Opt_TextPickerEnterSelectedAreaCallback* value)
{
}
void SelectedIndex0Impl(Ark_NativePointer node,
                        const Opt_Union_Number_Array_Number* value)
{
}
void SelectedIndex1Impl(Ark_NativePointer node,
                        const Opt_Union_Number_Array_Number* value)
{
}
void Divider0Impl(Ark_NativePointer node,
                  const Opt_DividerOptions* value)
{
}
void Divider1Impl(Ark_NativePointer node,
                  const Opt_DividerOptions* value)
{
}
void GradientHeight0Impl(Ark_NativePointer node,
                         const Opt_Length* value)
{
}
void GradientHeight1Impl(Ark_NativePointer node,
                         const Opt_Length* value)
{
}
void EnableHapticFeedbackImpl(Ark_NativePointer node,
                              const Opt_Boolean* value)
{
}
void DigitalCrownSensitivityImpl(Ark_NativePointer node,
                                 const Opt_CrownSensitivity* value)
{
}
void _onChangeEvent_selectedImpl(Ark_NativePointer node,
                                 const Callback_Union_Number_Array_Number_Void* callback)
{
}
void _onChangeEvent_valueImpl(Ark_NativePointer node,
                              const Callback_Union_String_Array_String_Void* callback)
{
}
} // TextPickerAttributeModifier
const GENERATED_ArkUITextPickerModifier* GetTextPickerModifier()
{
    static const GENERATED_ArkUITextPickerModifier ArkUITextPickerModifierImpl {
        TextPickerModifier::ConstructImpl,
        TextPickerInterfaceModifier::SetTextPickerOptionsImpl,
        TextPickerAttributeModifier::DefaultPickerItemHeight0Impl,
        TextPickerAttributeModifier::DefaultPickerItemHeight1Impl,
        TextPickerAttributeModifier::CanLoop0Impl,
        TextPickerAttributeModifier::CanLoop1Impl,
        TextPickerAttributeModifier::DisappearTextStyle0Impl,
        TextPickerAttributeModifier::DisappearTextStyle1Impl,
        TextPickerAttributeModifier::TextStyle0Impl,
        TextPickerAttributeModifier::TextStyle1Impl,
        TextPickerAttributeModifier::SelectedTextStyle0Impl,
        TextPickerAttributeModifier::SelectedTextStyle1Impl,
        TextPickerAttributeModifier::DisableTextStyleAnimationImpl,
        TextPickerAttributeModifier::DefaultTextStyleImpl,
        TextPickerAttributeModifier::OnAcceptImpl,
        TextPickerAttributeModifier::OnCancelImpl,
        TextPickerAttributeModifier::OnChange0Impl,
        TextPickerAttributeModifier::OnChange1Impl,
        TextPickerAttributeModifier::OnScrollStop0Impl,
        TextPickerAttributeModifier::OnScrollStop1Impl,
        TextPickerAttributeModifier::OnEnterSelectedAreaImpl,
        TextPickerAttributeModifier::SelectedIndex0Impl,
        TextPickerAttributeModifier::SelectedIndex1Impl,
        TextPickerAttributeModifier::Divider0Impl,
        TextPickerAttributeModifier::Divider1Impl,
        TextPickerAttributeModifier::GradientHeight0Impl,
        TextPickerAttributeModifier::GradientHeight1Impl,
        TextPickerAttributeModifier::EnableHapticFeedbackImpl,
        TextPickerAttributeModifier::DigitalCrownSensitivityImpl,
        TextPickerAttributeModifier::_onChangeEvent_selectedImpl,
        TextPickerAttributeModifier::_onChangeEvent_valueImpl,
    };
    return &ArkUITextPickerModifierImpl;
}

}
