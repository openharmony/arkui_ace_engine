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
namespace PanelInterfaceModifier {
void SetPanelOptionsImpl(Ark_NativePointer node,
                         Ark_Boolean show)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::Convert<bool>(show);
    //PanelModelNG::SetSetPanelOptions(frameNode, convValue);
}
} // PanelInterfaceModifier
namespace PanelAttributeModifier {
void ModeImpl(Ark_NativePointer node,
              Ark_PanelMode value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = Converter::Convert<type>(value);
    //auto convValue = Converter::OptConvert<type>(value); // for enums
    //PanelModelNG::SetMode(frameNode, convValue);
}
void TypeImpl(Ark_NativePointer node,
              Ark_PanelType value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = Converter::Convert<type>(value);
    //auto convValue = Converter::OptConvert<type>(value); // for enums
    //PanelModelNG::SetType(frameNode, convValue);
}
void DragBarImpl(Ark_NativePointer node,
                 Ark_Boolean value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::Convert<bool>(value);
    //PanelModelNG::SetDragBar(frameNode, convValue);
}
void CustomHeightImpl(Ark_NativePointer node,
                      const Ark_Union_Dimension_PanelHeight* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //PanelModelNG::SetCustomHeight(frameNode, convValue);
}
void FullHeightImpl(Ark_NativePointer node,
                    const Ark_Union_Number_String* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //PanelModelNG::SetFullHeight(frameNode, convValue);
}
void HalfHeightImpl(Ark_NativePointer node,
                    const Ark_Union_Number_String* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //PanelModelNG::SetHalfHeight(frameNode, convValue);
}
void MiniHeightImpl(Ark_NativePointer node,
                    const Ark_Union_Number_String* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //PanelModelNG::SetMiniHeight(frameNode, convValue);
}
void ShowImpl(Ark_NativePointer node,
              Ark_Boolean value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::Convert<bool>(value);
    //PanelModelNG::SetShow(frameNode, convValue);
}
void BackgroundMaskImpl(Ark_NativePointer node,
                        const Ark_ResourceColor* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //PanelModelNG::SetBackgroundMask(frameNode, convValue);
}
void ShowCloseIconImpl(Ark_NativePointer node,
                       Ark_Boolean value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::Convert<bool>(value);
    //PanelModelNG::SetShowCloseIcon(frameNode, convValue);
}
void OnChangeImpl(Ark_NativePointer node,
                  const Callback_Number_Number_PanelMode_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //PanelModelNG::SetOnChange(frameNode, convValue);
}
void OnHeightChangeImpl(Ark_NativePointer node,
                        const Callback_Number_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //PanelModelNG::SetOnHeightChange(frameNode, convValue);
}
} // PanelAttributeModifier
const GENERATED_ArkUIPanelModifier* GetPanelModifier()
{
    static const GENERATED_ArkUIPanelModifier ArkUIPanelModifierImpl {
        PanelInterfaceModifier::SetPanelOptionsImpl,
        PanelAttributeModifier::ModeImpl,
        PanelAttributeModifier::TypeImpl,
        PanelAttributeModifier::DragBarImpl,
        PanelAttributeModifier::CustomHeightImpl,
        PanelAttributeModifier::FullHeightImpl,
        PanelAttributeModifier::HalfHeightImpl,
        PanelAttributeModifier::MiniHeightImpl,
        PanelAttributeModifier::ShowImpl,
        PanelAttributeModifier::BackgroundMaskImpl,
        PanelAttributeModifier::ShowCloseIconImpl,
        PanelAttributeModifier::OnChangeImpl,
        PanelAttributeModifier::OnHeightChangeImpl,
    };
    return &ArkUIPanelModifierImpl;
}

}
