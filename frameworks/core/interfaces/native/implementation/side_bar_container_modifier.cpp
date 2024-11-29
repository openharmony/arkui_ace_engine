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
namespace SideBarContainerModifier {
Ark_NativePointer ConstructImpl()
{
    return 0;
}
} // SideBarContainerModifier
namespace SideBarContainerInterfaceModifier {
void SetSideBarContainerOptionsImpl(Ark_NativePointer node,
                                    const Opt_SideBarContainerType* type)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = type ? Converter::OptConvert<type>(*type) : std::nullopt;
    //SideBarContainerModelNG::SetSetSideBarContainerOptions(frameNode, convValue);
}
} // SideBarContainerInterfaceModifier
namespace SideBarContainerAttributeModifier {
void ShowSideBarImpl(Ark_NativePointer node,
                     Ark_Boolean value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::Convert<bool>(value);
    //SideBarContainerModelNG::SetShowSideBar(frameNode, convValue);
}
void ControlButtonImpl(Ark_NativePointer node,
                       const Ark_ButtonStyle* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //SideBarContainerModelNG::SetControlButton(frameNode, convValue);
}
void ShowControlButtonImpl(Ark_NativePointer node,
                           Ark_Boolean value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::Convert<bool>(value);
    //SideBarContainerModelNG::SetShowControlButton(frameNode, convValue);
}
void OnChangeImpl(Ark_NativePointer node,
                  const Callback_Boolean_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //SideBarContainerModelNG::SetOnChange(frameNode, convValue);
}
void SideBarWidth0Impl(Ark_NativePointer node,
                       const Ark_Number* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //SideBarContainerModelNG::SetSideBarWidth0(frameNode, convValue);
}
void SideBarWidth1Impl(Ark_NativePointer node,
                       const Ark_Length* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //SideBarContainerModelNG::SetSideBarWidth1(frameNode, convValue);
}
void MinSideBarWidth0Impl(Ark_NativePointer node,
                          const Ark_Number* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //SideBarContainerModelNG::SetMinSideBarWidth0(frameNode, convValue);
}
void MinSideBarWidth1Impl(Ark_NativePointer node,
                          const Ark_Length* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //SideBarContainerModelNG::SetMinSideBarWidth1(frameNode, convValue);
}
void MaxSideBarWidth0Impl(Ark_NativePointer node,
                          const Ark_Number* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //SideBarContainerModelNG::SetMaxSideBarWidth0(frameNode, convValue);
}
void MaxSideBarWidth1Impl(Ark_NativePointer node,
                          const Ark_Length* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //SideBarContainerModelNG::SetMaxSideBarWidth1(frameNode, convValue);
}
void AutoHideImpl(Ark_NativePointer node,
                  Ark_Boolean value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::Convert<bool>(value);
    //SideBarContainerModelNG::SetAutoHide(frameNode, convValue);
}
void SideBarPositionImpl(Ark_NativePointer node,
                         Ark_SideBarPosition value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = Converter::Convert<type>(value);
    //auto convValue = Converter::OptConvert<type>(value); // for enums
    //SideBarContainerModelNG::SetSideBarPosition(frameNode, convValue);
}
void DividerImpl(Ark_NativePointer node,
                 const Ark_Union_DividerStyle_Null* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //SideBarContainerModelNG::SetDivider(frameNode, convValue);
}
void MinContentWidthImpl(Ark_NativePointer node,
                         const Ark_Length* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //SideBarContainerModelNG::SetMinContentWidth(frameNode, convValue);
}
} // SideBarContainerAttributeModifier
const GENERATED_ArkUISideBarContainerModifier* GetSideBarContainerModifier()
{
    static const GENERATED_ArkUISideBarContainerModifier ArkUISideBarContainerModifierImpl {
        SideBarContainerModifier::ConstructImpl,
        SideBarContainerInterfaceModifier::SetSideBarContainerOptionsImpl,
        SideBarContainerAttributeModifier::ShowSideBarImpl,
        SideBarContainerAttributeModifier::ControlButtonImpl,
        SideBarContainerAttributeModifier::ShowControlButtonImpl,
        SideBarContainerAttributeModifier::OnChangeImpl,
        SideBarContainerAttributeModifier::SideBarWidth0Impl,
        SideBarContainerAttributeModifier::SideBarWidth1Impl,
        SideBarContainerAttributeModifier::MinSideBarWidth0Impl,
        SideBarContainerAttributeModifier::MinSideBarWidth1Impl,
        SideBarContainerAttributeModifier::MaxSideBarWidth0Impl,
        SideBarContainerAttributeModifier::MaxSideBarWidth1Impl,
        SideBarContainerAttributeModifier::AutoHideImpl,
        SideBarContainerAttributeModifier::SideBarPositionImpl,
        SideBarContainerAttributeModifier::DividerImpl,
        SideBarContainerAttributeModifier::MinContentWidthImpl,
    };
    return &ArkUISideBarContainerModifierImpl;
}

}
