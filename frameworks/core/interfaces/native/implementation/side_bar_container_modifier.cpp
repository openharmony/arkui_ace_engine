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
namespace SideBarContainerModifier {
Ark_NativePointer ConstructImpl(Ark_Int32 id,
                                Ark_Int32 flags)
{
    return {};
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
void SetShowSideBarImpl(Ark_NativePointer node,
                        const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //SideBarContainerModelNG::SetSetShowSideBar(frameNode, convValue);
}
void SetControlButtonImpl(Ark_NativePointer node,
                          const Opt_ButtonStyle* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //SideBarContainerModelNG::SetSetControlButton(frameNode, convValue);
}
void SetShowControlButtonImpl(Ark_NativePointer node,
                              const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //SideBarContainerModelNG::SetSetShowControlButton(frameNode, convValue);
}
void SetOnChangeImpl(Ark_NativePointer node,
                     const Opt_Callback_Boolean_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //SideBarContainerModelNG::SetSetOnChange(frameNode, convValue);
}
void SetSideBarWidth0Impl(Ark_NativePointer node,
                          const Opt_Number* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //SideBarContainerModelNG::SetSetSideBarWidth0(frameNode, convValue);
}
void SetMinSideBarWidth0Impl(Ark_NativePointer node,
                             const Opt_Number* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //SideBarContainerModelNG::SetSetMinSideBarWidth0(frameNode, convValue);
}
void SetMaxSideBarWidth0Impl(Ark_NativePointer node,
                             const Opt_Number* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //SideBarContainerModelNG::SetSetMaxSideBarWidth0(frameNode, convValue);
}
void SetSideBarWidth1Impl(Ark_NativePointer node,
                          const Opt_Length* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //SideBarContainerModelNG::SetSetSideBarWidth1(frameNode, convValue);
}
void SetMinSideBarWidth1Impl(Ark_NativePointer node,
                             const Opt_Length* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //SideBarContainerModelNG::SetSetMinSideBarWidth1(frameNode, convValue);
}
void SetMaxSideBarWidth1Impl(Ark_NativePointer node,
                             const Opt_Length* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //SideBarContainerModelNG::SetSetMaxSideBarWidth1(frameNode, convValue);
}
void SetAutoHideImpl(Ark_NativePointer node,
                     const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //SideBarContainerModelNG::SetSetAutoHide(frameNode, convValue);
}
void SetSideBarPositionImpl(Ark_NativePointer node,
                            const Opt_SideBarPosition* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //SideBarContainerModelNG::SetSetSideBarPosition(frameNode, convValue);
}
void SetDividerImpl(Ark_NativePointer node,
                    const Opt_DividerStyle* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //SideBarContainerModelNG::SetSetDivider(frameNode, convValue);
}
void SetMinContentWidthImpl(Ark_NativePointer node,
                            const Opt_Dimension* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //SideBarContainerModelNG::SetSetMinContentWidth(frameNode, convValue);
}
} // SideBarContainerAttributeModifier
const GENERATED_ArkUISideBarContainerModifier* GetSideBarContainerModifier()
{
    static const GENERATED_ArkUISideBarContainerModifier ArkUISideBarContainerModifierImpl {
        SideBarContainerModifier::ConstructImpl,
        SideBarContainerInterfaceModifier::SetSideBarContainerOptionsImpl,
        SideBarContainerAttributeModifier::SetShowSideBarImpl,
        SideBarContainerAttributeModifier::SetControlButtonImpl,
        SideBarContainerAttributeModifier::SetShowControlButtonImpl,
        SideBarContainerAttributeModifier::SetOnChangeImpl,
        SideBarContainerAttributeModifier::SetSideBarWidth0Impl,
        SideBarContainerAttributeModifier::SetMinSideBarWidth0Impl,
        SideBarContainerAttributeModifier::SetMaxSideBarWidth0Impl,
        SideBarContainerAttributeModifier::SetSideBarWidth1Impl,
        SideBarContainerAttributeModifier::SetMinSideBarWidth1Impl,
        SideBarContainerAttributeModifier::SetMaxSideBarWidth1Impl,
        SideBarContainerAttributeModifier::SetAutoHideImpl,
        SideBarContainerAttributeModifier::SetSideBarPositionImpl,
        SideBarContainerAttributeModifier::SetDividerImpl,
        SideBarContainerAttributeModifier::SetMinContentWidthImpl,
    };
    return &ArkUISideBarContainerModifierImpl;
}

}
