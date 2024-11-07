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

#include "core/components_ng/base/frame_node.h"
#include "core/interfaces/arkoala/utility/converter.h"
#include "arkoala_api_generated.h"

namespace OHOS::Ace::NG::GeneratedModifier {
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
void CheckedImpl(Ark_NativePointer node,
                 Ark_Boolean value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::Convert<bool>(value);
    //RadioModelNG::SetChecked(frameNode, convValue);
}
void OnChangeImpl(Ark_NativePointer node,
                  const Ark_Callback_Boolean_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //RadioModelNG::SetOnChange(frameNode, convValue);
}
void RadioStyleImpl(Ark_NativePointer node,
                    const Opt_RadioStyle* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //RadioModelNG::SetRadioStyle(frameNode, convValue);
}
void ContentModifierImpl(Ark_NativePointer node,
                         const Ark_CustomObject* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //RadioModelNG::SetContentModifier(frameNode, convValue);
}
} // RadioAttributeModifier
const GENERATED_ArkUIRadioModifier* GetRadioModifier()
{
    static const GENERATED_ArkUIRadioModifier ArkUIRadioModifierImpl {
        RadioInterfaceModifier::SetRadioOptionsImpl,
        RadioAttributeModifier::CheckedImpl,
        RadioAttributeModifier::OnChangeImpl,
        RadioAttributeModifier::RadioStyleImpl,
        RadioAttributeModifier::ContentModifierImpl,
    };
    return &ArkUIRadioModifierImpl;
}

}
