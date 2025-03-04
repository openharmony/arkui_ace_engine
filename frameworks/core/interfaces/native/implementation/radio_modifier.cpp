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
namespace RadioModifier {
Ark_NativePointer ConstructImpl(Ark_Int32 id,
                                Ark_Int32 flags)
{
    return {};
}
} // RadioModifier
namespace RadioInterfaceModifier {
void SetRadioOptionsImpl(Ark_NativePointer node,
                         const Ark_RadioOptions* options)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(options);
    //auto convValue = Converter::OptConvert<type_name>(*options);
    //RadioModelNG::SetSetRadioOptions(frameNode, convValue);
}
} // RadioInterfaceModifier
namespace RadioAttributeModifier {
void Checked0Impl(Ark_NativePointer node,
                  Ark_Boolean value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::Convert<bool>(value);
    //RadioModelNG::SetChecked0(frameNode, convValue);
}
void Checked1Impl(Ark_NativePointer node,
                  const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //RadioModelNG::SetChecked1(frameNode, convValue);
}
void OnChange0Impl(Ark_NativePointer node,
                   const Callback_Boolean_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //RadioModelNG::SetOnChange0(frameNode, convValue);
}
void OnChange1Impl(Ark_NativePointer node,
                   const Opt_OnRadioChangeCallback* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //RadioModelNG::SetOnChange1(frameNode, convValue);
}
void RadioStyleImpl(Ark_NativePointer node,
                    const Opt_RadioStyle* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //RadioModelNG::SetRadioStyle(frameNode, convValue);
}
void ContentModifier0Impl(Ark_NativePointer node,
                          const Ark_CustomObject* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //RadioModelNG::SetContentModifier0(frameNode, convValue);
}
void ContentModifier1Impl(Ark_NativePointer node,
                          const Opt_CustomObject* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //RadioModelNG::SetContentModifier1(frameNode, convValue);
}
void _onChangeEvent_checkedImpl(Ark_NativePointer node,
                                const Callback_Boolean_Void* callback)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(callback);
    //auto convValue = Converter::OptConvert<type_name>(*callback);
    //RadioModelNG::Set_onChangeEvent_checked(frameNode, convValue);
}
} // RadioAttributeModifier
const GENERATED_ArkUIRadioModifier* GetRadioModifier()
{
    static const GENERATED_ArkUIRadioModifier ArkUIRadioModifierImpl {
        RadioModifier::ConstructImpl,
        RadioInterfaceModifier::SetRadioOptionsImpl,
        RadioAttributeModifier::Checked0Impl,
        RadioAttributeModifier::Checked1Impl,
        RadioAttributeModifier::OnChange0Impl,
        RadioAttributeModifier::OnChange1Impl,
        RadioAttributeModifier::RadioStyleImpl,
        RadioAttributeModifier::ContentModifier0Impl,
        RadioAttributeModifier::ContentModifier1Impl,
        RadioAttributeModifier::_onChangeEvent_checkedImpl,
    };
    return &ArkUIRadioModifierImpl;
}

}
