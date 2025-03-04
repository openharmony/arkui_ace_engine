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
namespace CheckboxModifier {
Ark_NativePointer ConstructImpl(Ark_Int32 id,
                                Ark_Int32 flags)
{
    return {};
}
} // CheckboxModifier
namespace CheckboxInterfaceModifier {
void SetCheckboxOptionsImpl(Ark_NativePointer node,
                            const Opt_CheckboxOptions* options)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = options ? Converter::OptConvert<type>(*options) : std::nullopt;
    //CheckboxModelNG::SetSetCheckboxOptions(frameNode, convValue);
}
} // CheckboxInterfaceModifier
namespace CheckboxAttributeModifier {
void Select0Impl(Ark_NativePointer node,
                 Ark_Boolean value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::Convert<bool>(value);
    //CheckboxModelNG::SetSelect0(frameNode, convValue);
}
void Select1Impl(Ark_NativePointer node,
                 const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //CheckboxModelNG::SetSelect1(frameNode, convValue);
}
void SelectedColor0Impl(Ark_NativePointer node,
                        const Ark_ResourceColor* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //CheckboxModelNG::SetSelectedColor0(frameNode, convValue);
}
void SelectedColor1Impl(Ark_NativePointer node,
                        const Opt_ResourceColor* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //CheckboxModelNG::SetSelectedColor1(frameNode, convValue);
}
void Shape0Impl(Ark_NativePointer node,
                Ark_CheckBoxShape value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = Converter::Convert<type>(value);
    //auto convValue = Converter::OptConvert<type>(value); // for enums
    //CheckboxModelNG::SetShape0(frameNode, convValue);
}
void Shape1Impl(Ark_NativePointer node,
                const Opt_CheckBoxShape* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //CheckboxModelNG::SetShape1(frameNode, convValue);
}
void UnselectedColor0Impl(Ark_NativePointer node,
                          const Ark_ResourceColor* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //CheckboxModelNG::SetUnselectedColor0(frameNode, convValue);
}
void UnselectedColor1Impl(Ark_NativePointer node,
                          const Opt_ResourceColor* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //CheckboxModelNG::SetUnselectedColor1(frameNode, convValue);
}
void Mark0Impl(Ark_NativePointer node,
               const Ark_MarkStyle* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //CheckboxModelNG::SetMark0(frameNode, convValue);
}
void Mark1Impl(Ark_NativePointer node,
               const Opt_MarkStyle* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //CheckboxModelNG::SetMark1(frameNode, convValue);
}
void OnChange0Impl(Ark_NativePointer node,
                   const OnCheckboxChangeCallback* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //CheckboxModelNG::SetOnChange0(frameNode, convValue);
}
void OnChange1Impl(Ark_NativePointer node,
                   const Opt_OnCheckboxChangeCallback* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //CheckboxModelNG::SetOnChange1(frameNode, convValue);
}
void ContentModifier0Impl(Ark_NativePointer node,
                          const Ark_CustomObject* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //CheckboxModelNG::SetContentModifier0(frameNode, convValue);
}
void ContentModifier1Impl(Ark_NativePointer node,
                          const Opt_CustomObject* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //CheckboxModelNG::SetContentModifier1(frameNode, convValue);
}
void _onChangeEvent_selectImpl(Ark_NativePointer node,
                               const Callback_Boolean_Void* callback)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(callback);
    //auto convValue = Converter::OptConvert<type_name>(*callback);
    //CheckboxModelNG::Set_onChangeEvent_select(frameNode, convValue);
}
} // CheckboxAttributeModifier
const GENERATED_ArkUICheckboxModifier* GetCheckboxModifier()
{
    static const GENERATED_ArkUICheckboxModifier ArkUICheckboxModifierImpl {
        CheckboxModifier::ConstructImpl,
        CheckboxInterfaceModifier::SetCheckboxOptionsImpl,
        CheckboxAttributeModifier::Select0Impl,
        CheckboxAttributeModifier::Select1Impl,
        CheckboxAttributeModifier::SelectedColor0Impl,
        CheckboxAttributeModifier::SelectedColor1Impl,
        CheckboxAttributeModifier::Shape0Impl,
        CheckboxAttributeModifier::Shape1Impl,
        CheckboxAttributeModifier::UnselectedColor0Impl,
        CheckboxAttributeModifier::UnselectedColor1Impl,
        CheckboxAttributeModifier::Mark0Impl,
        CheckboxAttributeModifier::Mark1Impl,
        CheckboxAttributeModifier::OnChange0Impl,
        CheckboxAttributeModifier::OnChange1Impl,
        CheckboxAttributeModifier::ContentModifier0Impl,
        CheckboxAttributeModifier::ContentModifier1Impl,
        CheckboxAttributeModifier::_onChangeEvent_selectImpl,
    };
    return &ArkUICheckboxModifierImpl;
}

}
