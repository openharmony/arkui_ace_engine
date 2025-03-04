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
namespace CheckboxGroupModifier {
Ark_NativePointer ConstructImpl(Ark_Int32 id,
                                Ark_Int32 flags)
{
    return {};
}
} // CheckboxGroupModifier
namespace CheckboxGroupInterfaceModifier {
void SetCheckboxGroupOptionsImpl(Ark_NativePointer node,
                                 const Opt_CheckboxGroupOptions* options)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = options ? Converter::OptConvert<type>(*options) : std::nullopt;
    //CheckboxGroupModelNG::SetSetCheckboxGroupOptions(frameNode, convValue);
}
} // CheckboxGroupInterfaceModifier
namespace CheckboxGroupAttributeModifier {
void SelectAll0Impl(Ark_NativePointer node,
                    Ark_Boolean value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::Convert<bool>(value);
    //CheckboxGroupModelNG::SetSelectAll0(frameNode, convValue);
}
void SelectAll1Impl(Ark_NativePointer node,
                    const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //CheckboxGroupModelNG::SetSelectAll1(frameNode, convValue);
}
void SelectedColor0Impl(Ark_NativePointer node,
                        const Ark_ResourceColor* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //CheckboxGroupModelNG::SetSelectedColor0(frameNode, convValue);
}
void SelectedColor1Impl(Ark_NativePointer node,
                        const Opt_ResourceColor* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //CheckboxGroupModelNG::SetSelectedColor1(frameNode, convValue);
}
void UnselectedColor0Impl(Ark_NativePointer node,
                          const Ark_ResourceColor* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //CheckboxGroupModelNG::SetUnselectedColor0(frameNode, convValue);
}
void UnselectedColor1Impl(Ark_NativePointer node,
                          const Opt_ResourceColor* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //CheckboxGroupModelNG::SetUnselectedColor1(frameNode, convValue);
}
void Mark0Impl(Ark_NativePointer node,
               const Ark_MarkStyle* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //CheckboxGroupModelNG::SetMark0(frameNode, convValue);
}
void Mark1Impl(Ark_NativePointer node,
               const Opt_MarkStyle* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //CheckboxGroupModelNG::SetMark1(frameNode, convValue);
}
void OnChange0Impl(Ark_NativePointer node,
                   const OnCheckboxGroupChangeCallback* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //CheckboxGroupModelNG::SetOnChange0(frameNode, convValue);
}
void OnChange1Impl(Ark_NativePointer node,
                   const Opt_OnCheckboxGroupChangeCallback* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //CheckboxGroupModelNG::SetOnChange1(frameNode, convValue);
}
void CheckboxShape0Impl(Ark_NativePointer node,
                        Ark_CheckBoxShape value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = Converter::Convert<type>(value);
    //auto convValue = Converter::OptConvert<type>(value); // for enums
    //CheckboxGroupModelNG::SetCheckboxShape0(frameNode, convValue);
}
void CheckboxShape1Impl(Ark_NativePointer node,
                        const Opt_CheckBoxShape* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //CheckboxGroupModelNG::SetCheckboxShape1(frameNode, convValue);
}
void _onChangeEvent_selectAllImpl(Ark_NativePointer node,
                                  const Callback_Boolean_Void* callback)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(callback);
    //auto convValue = Converter::OptConvert<type_name>(*callback);
    //CheckboxGroupModelNG::Set_onChangeEvent_selectAll(frameNode, convValue);
}
} // CheckboxGroupAttributeModifier
const GENERATED_ArkUICheckboxGroupModifier* GetCheckboxGroupModifier()
{
    static const GENERATED_ArkUICheckboxGroupModifier ArkUICheckboxGroupModifierImpl {
        CheckboxGroupModifier::ConstructImpl,
        CheckboxGroupInterfaceModifier::SetCheckboxGroupOptionsImpl,
        CheckboxGroupAttributeModifier::SelectAll0Impl,
        CheckboxGroupAttributeModifier::SelectAll1Impl,
        CheckboxGroupAttributeModifier::SelectedColor0Impl,
        CheckboxGroupAttributeModifier::SelectedColor1Impl,
        CheckboxGroupAttributeModifier::UnselectedColor0Impl,
        CheckboxGroupAttributeModifier::UnselectedColor1Impl,
        CheckboxGroupAttributeModifier::Mark0Impl,
        CheckboxGroupAttributeModifier::Mark1Impl,
        CheckboxGroupAttributeModifier::OnChange0Impl,
        CheckboxGroupAttributeModifier::OnChange1Impl,
        CheckboxGroupAttributeModifier::CheckboxShape0Impl,
        CheckboxGroupAttributeModifier::CheckboxShape1Impl,
        CheckboxGroupAttributeModifier::_onChangeEvent_selectAllImpl,
    };
    return &ArkUICheckboxGroupModifierImpl;
}

}
