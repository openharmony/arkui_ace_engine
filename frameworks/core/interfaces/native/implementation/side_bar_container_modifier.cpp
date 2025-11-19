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
constexpr float DEFAULT_MIN_SIDEBAR_WIDTH = 240.0f;
constexpr float DEFAULT_MAX_SIDEBAR_WIDTH = 280.0f;
constexpr float DEFAULT_MIN_CONTENT_LENGTH = 360.0f;
constexpr float DEFAULT_DIVIDER_WIDTH = 1.0f;

std::optional<bool> ProcessBindableShowSideBar(FrameNode* frameNode, const Opt_Union_Boolean_Bindable *value)
{
    std::optional<bool> result;
    Converter::VisitUnionPtr(value,
        [&result](const Ark_Boolean& src) {
            result = Converter::OptConvert<bool>(src);
        },
        [&result, frameNode](const Ark_Bindable_Boolean& src) {
            result = Converter::OptConvert<bool>(src.value);
            WeakPtr<FrameNode> weakNode = AceType::WeakClaim(frameNode);
            auto onEvent = [arkCallback = CallbackHelper(src.onChange), weakNode](bool isShow) {
                PipelineContext::SetCallBackNode(weakNode);
                arkCallback.Invoke(Converter::ArkValue<Ark_Boolean>(isShow));
            };
            SideBarContainerModelStatic::SetOnChangeEvent(frameNode, std::move(onEvent));
        },
        [] {});
    return result;
}

std::optional<Dimension> ProcessBindableSideBarWidth(FrameNode* frameNode, const Opt_Union_Length_Bindable* value)
{
    std::optional<Dimension> result;
    Converter::VisitUnionPtr(value,
        [&result](const Ark_Length& src) {
            result = Converter::OptConvert<Dimension>(src);
        },
        [&result, frameNode](const Ark_Bindable_Arkui_Component_Units_Length& src) {
            result = Converter::OptConvert<Dimension>(src.value);
            // Need to provide callback
        },
        [] {});
    return result;
}
} // namespace
} // namespace OHOS::Ace::NG

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
        [&ret](const Ark_image_PixelMap& value) {
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
    divider.strokeWidth = OptConvert<Dimension>(src.strokeWidth);
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
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    SideBarContainerModelStatic::SetSideBarContainerType(
        frameNode, Converter::OptConvertPtr<SideBarContainerType>(type).value_or(SideBarContainerType::EMBED));
}
} // SideBarContainerInterfaceModifier
namespace SideBarContainerAttributeModifier {
void SetShowSideBarImpl(Ark_NativePointer node,
                        const Opt_Union_Boolean_Bindable* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = ProcessBindableShowSideBar(frameNode, value);
    SideBarContainerModelStatic::SetShowSideBar(frameNode, convValue.value_or(true));
}
void SetControlButtonImpl(Ark_NativePointer node,
                          const Opt_ButtonStyle* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvertPtr<LocalControlButtonStyle>(value);
    if (!convValue) {
        SideBarContainerModelStatic::ResetControlButtonIconInfo(frameNode);
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
void SetShowControlButtonImpl(Ark_NativePointer node,
                              const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    SideBarContainerModelStatic::SetShowControlButton(frameNode, Converter::OptConvertPtr<bool>(value).value_or(true));
}
void SetOnChangeImpl(Ark_NativePointer node,
                     const Opt_Callback_Boolean_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
        SideBarContainerModelStatic::SetOnChange(frameNode, nullptr);
        return;
    }
    auto onEvent = [arkCallback = CallbackHelper(*optValue)](const bool param) {
        auto arkValue = Converter::ArkValue<Ark_Boolean>(param);
        arkCallback.Invoke(arkValue);
    };
    SideBarContainerModelStatic::SetOnChange(frameNode, std::move(onEvent));
}
void SetSideBarWidthImpl(Ark_NativePointer node,
                         const Opt_Union_Length_Bindable* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto width = ProcessBindableSideBarWidth(frameNode, value);
    Validator::ValidateNonNegative(width);
    SideBarContainerModelStatic::SetSideBarWidth(frameNode, width);
}
void SetMinSideBarWidthImpl(Ark_NativePointer node,
                             const Opt_Length* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    if (value->tag == InteropTag::INTEROP_TAG_UNDEFINED) {
        Dimension def(DEFAULT_MIN_SIDEBAR_WIDTH, DimensionUnit::VP);
        SideBarContainerModelStatic::SetMinSideBarWidth(frameNode, def);
        return;
    }
    auto width = Converter::OptConvert<Dimension>(value->value);
    if (!width.has_value()) {
        Dimension def(DEFAULT_MIN_SIDEBAR_WIDTH, DimensionUnit::VP);
        SideBarContainerModelStatic::SetMinSideBarWidth(frameNode, def);
        return;
    }
    if (width->IsNegative()) {
        width->SetValue(DEFAULT_MIN_SIDEBAR_WIDTH);
    }
    SideBarContainerModelStatic::SetMinSideBarWidth(frameNode, width);
}
void SetMaxSideBarWidthImpl(Ark_NativePointer node,
                             const Opt_Length* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    if (value->tag == InteropTag::INTEROP_TAG_UNDEFINED) {
        Dimension def(DEFAULT_MAX_SIDEBAR_WIDTH, DimensionUnit::VP);
        SideBarContainerModelStatic::SetMaxSideBarWidth(frameNode, def);
        return;
    }
    auto width = Converter::OptConvert<Dimension>(value->value);
    if (!width.has_value()) {
        Dimension def(DEFAULT_MIN_SIDEBAR_WIDTH, DimensionUnit::VP);
        SideBarContainerModelStatic::SetMinSideBarWidth(frameNode, def);
        return;
    }
    if (width->IsNegative()) {
        width->SetValue(DEFAULT_MAX_SIDEBAR_WIDTH);
    }
    SideBarContainerModelStatic::SetMaxSideBarWidth(frameNode, width);
}
void SetAutoHideImpl(Ark_NativePointer node,
                     const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvertPtr<bool>(value);
    if (!convValue) {
        SideBarContainerModelStatic::SetAutoHide(frameNode, true);
        return;
    }
    SideBarContainerModelStatic::SetAutoHide(frameNode, *convValue);
}
void SetSideBarPositionImpl(Ark_NativePointer node,
                            const Opt_SideBarPosition* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    SideBarContainerModelStatic::SetSideBarPosition(
        frameNode, Converter::OptConvertPtr<SideBarPosition>(value).value_or(SideBarPosition::START));
}
void SetDividerImpl(Ark_NativePointer node,
                    const Opt_DividerStyle* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    if (value->tag == InteropTag::INTEROP_TAG_UNDEFINED) {
        Dimension def(DEFAULT_DIVIDER_WIDTH, DimensionUnit::VP);
        SideBarContainerModelStatic::SetDividerStrokeWidth(frameNode, def);
        return;
    }
    auto dividerOpt = Converter::Convert<DividerOptions>(value->value);
        if (dividerOpt.strokeWidth.has_value() && dividerOpt.strokeWidth->IsNegative()) {
            dividerOpt.strokeWidth->SetValue(DEFAULT_DIVIDER_WIDTH);
        }
        SideBarContainerModelStatic::SetDividerStrokeWidth(frameNode, dividerOpt.strokeWidth);
        SideBarContainerModelStatic::SetDividerColor(frameNode, dividerOpt.color);
        SideBarContainerModelStatic::SetDividerStartMargin(frameNode, dividerOpt.startMargin);
        SideBarContainerModelStatic::SetDividerEndMargin(frameNode, dividerOpt.endMargin);
}
void SetMinContentWidthImpl(Ark_NativePointer node,
                            const Opt_Dimension* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto width = Converter::OptConvertPtr<Dimension>(value);
    if (width.has_value() && width->IsNegative()) {
        width->SetValue(DEFAULT_MIN_CONTENT_LENGTH);
    } else if (!width.has_value()) {
        width = Dimension(DEFAULT_MIN_CONTENT_LENGTH, DimensionUnit::VP);
    }
    SideBarContainerModelStatic::SetMinContentWidth(frameNode, width);
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
        SideBarContainerAttributeModifier::SetSideBarWidthImpl,
        SideBarContainerAttributeModifier::SetMinSideBarWidthImpl,
        SideBarContainerAttributeModifier::SetMaxSideBarWidthImpl,
        SideBarContainerAttributeModifier::SetAutoHideImpl,
        SideBarContainerAttributeModifier::SetSideBarPositionImpl,
        SideBarContainerAttributeModifier::SetDividerImpl,
        SideBarContainerAttributeModifier::SetMinContentWidthImpl,
    };
    return &ArkUISideBarContainerModifierImpl;
}

}
