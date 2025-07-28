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
#include "core/components_ng/pattern/side_bar/side_bar_container_model_static.h"
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
struct LocalControlButtonStyle {
    std::optional<Dimension> left;
    std::optional<Dimension> top;
    std::optional<Dimension> width;
    std::optional<Dimension> height;
    ControlButtonStyleIcon showIcon;
    ControlButtonStyleIcon hiddenIcon;
    std::optional<ControlButtonStyleIcon> switchIcon;
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

ControlButtonStyleIcon GetIconStyle(const Ark_Union_String_PixelMap_Resource& src)
{
    ControlButtonStyleIcon ret = {};
    Converter::VisitUnion(src,
        [&ret](const Ark_String& value) {
            ret.iconStr = Converter::Convert<std::string>(value);
            ret.isPxMap = false;
        },
        [&ret](const Ark_PixelMap& value) {
            ret.isPxMap = true;
            ret.iconPxMap = Convert<RefPtr<PixelMap>>(value);
        },
        [&ret](const Ark_Resource& value) {
            auto srcStr = Converter::OptConvert<std::string>(value);
            if (srcStr) {
                ret.iconStr = srcStr.value();
                ret.isPxMap = false;
            }
        },
        []() {});
    return ret;
}

template<>
LocalControlButtonStyle Convert(const Ark_ButtonStyle& src)
{
    LocalControlButtonStyle style = {};
    style.left = OptConvert<Dimension>(src.left);
    style.top = OptConvert<Dimension>(src.top);
    style.width = OptConvert<Dimension>(src.width);
    style.height = OptConvert<Dimension>(src.height);
    auto arkIcons = GetOpt(src.icons);
    if (arkIcons.has_value()) {
        auto arkIconsV = arkIcons.value();
        style.showIcon = GetIconStyle(arkIconsV.shown);
        style.hiddenIcon = GetIconStyle(arkIconsV.hidden);
        auto arkIconSwitch = GetOpt(arkIconsV.switching);
        if (arkIconSwitch.has_value()) {
            style.switchIcon = GetIconStyle(arkIconSwitch.value());
        }
    }
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
    auto frameNode = SideBarContainerModelStatic::CreateFrameNode(id);
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
    SideBarContainerModelStatic::SetSideBarContainerType(frameNode, sideBarType);
}
} // SideBarContainerInterfaceModifier
namespace SideBarContainerAttributeModifier {
void ShowSideBarImpl(Ark_NativePointer node,
                     const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvert<bool>(*value);
    if (!convValue) {
        // TODO: Reset value
        return;
    }
    SideBarContainerModelStatic::SetShowSideBar(frameNode, *convValue);
}
void ControlButtonImpl(Ark_NativePointer node,
                       const Opt_ButtonStyle* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvert<LocalControlButtonStyle>(*value);
    if (!convValue) {
        // TODO: Reset value
        return;
    }
    auto style = *convValue;
    if (style.left.has_value()) {
        SideBarContainerModelStatic::SetControlButtonLeft(frameNode, style.left.value());
    }
    if (style.top.has_value()) {
        SideBarContainerModelStatic::SetControlButtonTop(frameNode, style.top.value());
    }
    Validator::ValidateNonNegative(style.width);
    Validator::ValidateNonNegative(style.height);
    SideBarContainerModelStatic::SetControlButtonWidth(frameNode, style.width);
    SideBarContainerModelStatic::SetControlButtonHeight(frameNode, style.height);
    SideBarContainerModelStatic::SetControlButtonShowIconInfo(frameNode, style.showIcon.iconStr,
        style.showIcon.isPxMap, style.showIcon.iconPxMap);
    SideBarContainerModelStatic::SetControlButtonHiddenIconInfo(frameNode, style.hiddenIcon.iconStr,
        style.hiddenIcon.isPxMap, style.hiddenIcon.iconPxMap);
    if (style.switchIcon) {
        auto icon = style.switchIcon.value();
        SideBarContainerModelStatic::SetControlButtonSwitchingIconInfo(frameNode, icon.iconStr,
            icon.isPxMap, icon.iconPxMap);
    }
}
void ShowControlButtonImpl(Ark_NativePointer node,
                           const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvert<bool>(*value);
    if (!convValue) {
        // TODO: Reset value
        return;
    }
    SideBarContainerModelStatic::SetShowControlButton(frameNode, *convValue);
}
void OnChangeImpl(Ark_NativePointer node,
                  const Opt_Callback_Boolean_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
        // TODO: Reset value
        return;
    }
    auto onEvent = [arkCallback = CallbackHelper(*optValue)](const bool param) {
        auto arkValue = Converter::ArkValue<Ark_Boolean>(param);
        arkCallback.Invoke(arkValue);
    };
    SideBarContainerModelStatic::SetOnChange(frameNode, std::move(onEvent));
}
void SideBarWidth0Impl(Ark_NativePointer node,
                       const Opt_Number* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto width = Converter::OptConvert<Dimension>(*value);
    Validator::ValidateNonNegative(width);
    SideBarContainerModelStatic::SetSideBarWidth(frameNode, width);
}
void SideBarWidth1Impl(Ark_NativePointer node,
                       const Opt_Length* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto width = Converter::OptConvert<Dimension>(*value);
    Validator::ValidateNonNegative(width);
    SideBarContainerModelStatic::SetSideBarWidth(frameNode, width);
}
void MinSideBarWidth0Impl(Ark_NativePointer node,
                          const Opt_Number* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto width = Converter::OptConvert<Dimension>(*value);
    Validator::ValidateNonNegative(width);
    SideBarContainerModelStatic::SetMinSideBarWidth(frameNode, width);
}
void MinSideBarWidth1Impl(Ark_NativePointer node,
                          const Opt_Length* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto width = Converter::OptConvert<Dimension>(*value);
    Validator::ValidateNonNegative(width);
    SideBarContainerModelStatic::SetMinSideBarWidth(frameNode, width);
}
void MaxSideBarWidth0Impl(Ark_NativePointer node,
                          const Opt_Number* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto width = Converter::OptConvert<Dimension>(*value);
    Validator::ValidateNonNegative(width);
    SideBarContainerModelStatic::SetMaxSideBarWidth(frameNode, width);
}
void MaxSideBarWidth1Impl(Ark_NativePointer node,
                          const Opt_Length* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto width = Converter::OptConvert<Dimension>(*value);
    Validator::ValidateNonNegative(width);
    SideBarContainerModelStatic::SetMaxSideBarWidth(frameNode, width);
}
void AutoHideImpl(Ark_NativePointer node,
                  const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvert<bool>(*value);
    if (!convValue) {
        // TODO: Reset value
        return;
    }
    SideBarContainerModelStatic::SetAutoHide(frameNode, *convValue);
}
void SideBarPositionImpl(Ark_NativePointer node,
                         const Opt_SideBarPosition* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto pos = Converter::OptConvert<SideBarPosition>(*value);
    SideBarContainerModelStatic::SetSideBarPosition(frameNode, pos);
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
        SideBarContainerModelStatic::SetDividerStrokeWidth(frameNode, divider.strokeWidth);
        if (divider.color.has_value()) {
            SideBarContainerModelStatic::SetDividerColor(frameNode, divider.color.value());
        }
        if (divider.startMargin.has_value()) {
            SideBarContainerModelStatic::SetDividerStartMargin(frameNode, divider.startMargin.value());
        }
        if (divider.endMargin.has_value()) {
            SideBarContainerModelStatic::SetDividerEndMargin(frameNode, divider.endMargin.value());
        }
    }
}
void MinContentWidthImpl(Ark_NativePointer node,
                         const Opt_Length* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto width = Converter::OptConvert<Dimension>(*value);
    Validator::ValidateNonNegative(width);
    SideBarContainerModelStatic::SetMinContentWidth(frameNode, width);
}
void _onChangeEvent_showSideBarImpl(Ark_NativePointer node,
                                    const Callback_Opt_Boolean_Void* callback)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(callback);
    WeakPtr<FrameNode> weakNode = AceType::WeakClaim(frameNode);
    auto onEvent = [arkCallback = CallbackHelper(*callback), weakNode](bool isShow) {
        PipelineContext::SetCallBackNode(weakNode);
        arkCallback.Invoke(Converter::ArkValue<Opt_Boolean>(isShow));
    };
    SideBarContainerModelStatic::SetOnChangeEvent(frameNode, std::move(onEvent));
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
