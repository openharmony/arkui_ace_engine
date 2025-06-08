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
#include "core/components_ng/pattern/side_bar/side_bar_container_model_ng.h"
#include "core/interfaces/native/utility/callback_helper.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/reverse_converter.h"
#include "core/interfaces/native/generated/interface/node_api.h"
#include "core/interfaces/native/utility/validators.h"

namespace OHOS::Ace::NG {
namespace {
struct ControlButtonStyleIcon {
    std::string iconStr;
    bool isPxMap;
    RefPtr<PixelMap> iconPxMap;
};
struct ControlButtonStyleIcons {
    ControlButtonStyleIcon showIcon;
    ControlButtonStyleIcon hiddenIcon;
    ControlButtonStyleIcon switchIcon;
};
struct ControlButtonStyle {
    std::optional<Dimension> left;
    std::optional<Dimension> top;
    std::optional<Dimension> width;
    std::optional<Dimension> height;
};
struct DividerOptions {
    std::optional<Dimension> strokeWidth;
    std::optional<Color> color;
    std::optional<Dimension> startMargin;
    std::optional<Dimension> endMargin;
};
}
}

namespace OHOS::Ace::NG::Converter {
template<>
void AssignCast(std::optional<SideBarPosition>& dst, const Ark_SideBarPosition& src)
{
    switch (src) {
        case ARK_SIDE_BAR_POSITION_START: dst = SideBarPosition::START; break;
        case ARK_SIDE_BAR_POSITION_END: dst = SideBarPosition::END; break;
        default: LOGE("SideBarContainerInterfaceModifier::Unexpected enum value in "
            "Ark_SideBarPosition: %{public}d", src);
    }
}

template<>
void AssignCast(std::optional<SideBarContainerType>& dst, const Ark_SideBarContainerType& src)
{
    switch (src) {
        case ARK_SIDE_BAR_CONTAINER_TYPE_EMBED: dst = SideBarContainerType::EMBED; break;
        case ARK_SIDE_BAR_CONTAINER_TYPE_OVERLAY: dst = SideBarContainerType::OVERLAY; break;
        case ARK_SIDE_BAR_CONTAINER_TYPE_AUTO: dst = SideBarContainerType::AUTO; break;
        default: LOGE("SideBarContainerInterfaceModifier::Unexpected enum value in "
            "Ark_SideBarContainerType: %{public}d", src);
    }
}

template<>
ControlButtonStyle Convert(const Ark_ButtonStyle& src)
{
    ControlButtonStyle style;
    style.left = OptConvert<Dimension>(src.left);
    style.top = OptConvert<Dimension>(src.top);
    style.width = OptConvert<Dimension>(src.width);
    style.height = OptConvert<Dimension>(src.height);
    LOGE("SideBarContainerInterfaceModifier::converter "
        "Ark_ButtonStyle -> ControlButtonStyle  is not fully "
        "implemented. Need get style.icons");
    return style;
}

template<>
DividerOptions Convert(const Ark_DividerStyle& src)
{
    DividerOptions divider;
    divider.strokeWidth = Convert<Dimension>(src.strokeWidth);
    Validator::ValidateNonNegative(divider.strokeWidth);
    divider.startMargin = OptConvert<Dimension>(src.startMargin);
    divider.endMargin = OptConvert<Dimension>(src.endMargin);
    divider.color = OptConvert<Color>(src.color);
    return divider;
}

} // namespace OHOS::Ace::NG::Converter

namespace OHOS::Ace::NG::GeneratedModifier {
namespace SideBarContainerModifier {
Ark_NativePointer ConstructImpl(Ark_Int32 id,
                                Ark_Int32 flags)
{
    auto frameNode = SideBarContainerModelNG::CreateFrameNode(id);
    CHECK_NULL_RETURN(frameNode, nullptr);
    frameNode->IncRefCount();
    return AceType::RawPtr(frameNode);
}
} // SideBarContainerModifier
namespace SideBarContainerInterfaceModifier {
void SetSideBarContainerOptionsImpl(Ark_NativePointer node,
                                    const Opt_SideBarContainerType* type)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(type);
    auto sideBarType = Converter::OptConvert<SideBarContainerType>(*type);
    SideBarContainerModelNG::SetSideBarContainerType(frameNode, sideBarType);
}
} // SideBarContainerInterfaceModifier
namespace SideBarContainerAttributeModifier {
void ShowSideBarImpl(Ark_NativePointer node,
                     Ark_Boolean value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    SideBarContainerModelNG::SetShowSideBar(frameNode, Converter::Convert<bool>(value));
}
void ControlButtonImpl(Ark_NativePointer node,
                       const Ark_ButtonStyle* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    ControlButtonStyle style = Converter::Convert<ControlButtonStyle>(*value);
    if (style.left.has_value()) {
        SideBarContainerModelNG::SetControlButtonLeft(frameNode, style.left.value());
    }
    if (style.top.has_value()) {
        SideBarContainerModelNG::SetControlButtonTop(frameNode, style.top.value());
    }
    Validator::ValidateNonNegative(style.width);
    Validator::ValidateNonNegative(style.height);
    SideBarContainerModelNG::SetControlButtonWidth(frameNode, style.width);
    SideBarContainerModelNG::SetControlButtonHeight(frameNode, style.height);
    LOGE("SideBarContainerInterfaceModifier::ControlButtonImpl -> Method is not fully"
            "implemented. Need get style.icons");
}
void ShowControlButtonImpl(Ark_NativePointer node,
                           Ark_Boolean value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    SideBarContainerModelNG::SetShowControlButton(frameNode, Converter::Convert<bool>(value));
}
void OnChangeImpl(Ark_NativePointer node,
                  const Callback_Boolean_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto onEvent = [arkCallback = CallbackHelper(*value)](const bool param) {
        auto arkValue = Converter::ArkValue<Ark_Boolean>(param);
        arkCallback.Invoke(arkValue);
    };
    SideBarContainerModelNG::SetOnChange(frameNode, std::move(onEvent));
}
void SideBarWidth0Impl(Ark_NativePointer node,
                       const Ark_Number* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto width = Converter::OptConvert<Dimension>(*value);
    Validator::ValidateNonNegative(width);
    SideBarContainerModelNG::SetSideBarWidth(frameNode, width);
}
void SideBarWidth1Impl(Ark_NativePointer node,
                       const Ark_Length* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto width = Converter::OptConvert<Dimension>(*value);
    Validator::ValidateNonNegative(width);
    SideBarContainerModelNG::SetSideBarWidth(frameNode, width);
}
void MinSideBarWidth0Impl(Ark_NativePointer node,
                          const Ark_Number* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto width = Converter::OptConvert<Dimension>(*value);
    Validator::ValidateNonNegative(width);
    SideBarContainerModelNG::SetMinSideBarWidth(frameNode, width);
}
void MinSideBarWidth1Impl(Ark_NativePointer node,
                          const Ark_Length* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto width = Converter::OptConvert<Dimension>(*value);
    Validator::ValidateNonNegative(width);
    SideBarContainerModelNG::SetMinSideBarWidth(frameNode, width);
}
void MaxSideBarWidth0Impl(Ark_NativePointer node,
                          const Ark_Number* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto width = Converter::OptConvert<Dimension>(*value);
    Validator::ValidateNonNegative(width);
    SideBarContainerModelNG::SetMaxSideBarWidth(frameNode, width);
}
void MaxSideBarWidth1Impl(Ark_NativePointer node,
                          const Ark_Length* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto width = Converter::OptConvert<Dimension>(*value);
    Validator::ValidateNonNegative(width);
    SideBarContainerModelNG::SetMaxSideBarWidth(frameNode, width);
}
void AutoHideImpl(Ark_NativePointer node,
                  Ark_Boolean value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    SideBarContainerModelNG::SetAutoHide(frameNode, Converter::Convert<bool>(value));
}
void SideBarPositionImpl(Ark_NativePointer node,
                         Ark_SideBarPosition value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto pos = Converter::OptConvert<SideBarPosition>(value);
    SideBarContainerModelNG::SetSideBarPosition(frameNode, pos);
}
void DividerImpl(Ark_NativePointer node,
                 const Opt_DividerStyle* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto dividerOpt = Converter::OptConvert<DividerOptions>(*value);
    if (dividerOpt.has_value()) {
        auto divider = dividerOpt.value();
        SideBarContainerModelNG::SetDividerStrokeWidth(frameNode, divider.strokeWidth);
        if (divider.color.has_value()) {
            SideBarContainerModelNG::SetDividerColor(frameNode, divider.color.value());
        }
        if (divider.startMargin.has_value()) {
            SideBarContainerModelNG::SetDividerStartMargin(frameNode, divider.startMargin.value());
        }
        if (divider.endMargin.has_value()) {
            SideBarContainerModelNG::SetDividerEndMargin(frameNode, divider.endMargin.value());
        }
    }
}
void MinContentWidthImpl(Ark_NativePointer node,
                         const Ark_Length* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto width = Converter::OptConvert<Dimension>(*value);
    Validator::ValidateNonNegative(width);
    SideBarContainerModelNG::SetMinContentWidth(frameNode, width);
}
void _onChangeEvent_showSideBarImpl(Ark_NativePointer node,
                                    const Callback_Boolean_Void* callback)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(callback);
    WeakPtr<FrameNode> weakNode = AceType::WeakClaim(frameNode);
    auto onEvent = [arkCallback = CallbackHelper(*callback), weakNode](bool isShow) {
        PipelineContext::SetCallBackNode(weakNode);
        arkCallback.Invoke(Converter::ArkValue<Ark_Boolean>(isShow));
    };
    SideBarContainerModelNG::SetOnChangeEvent(frameNode, std::move(onEvent));
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
        SideBarContainerAttributeModifier::_onChangeEvent_showSideBarImpl,
    };
    return &ArkUISideBarContainerModifierImpl;
}

}
