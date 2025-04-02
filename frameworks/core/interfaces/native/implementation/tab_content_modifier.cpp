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

#include "base/utils/string_utils.h"
#include "core/components/common/properties/color.h"
#include "core/components_ng/pattern/tabs/tab_content_model_ng.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/generated/interface/node_api.h"
#include "core/interfaces/native/utility/validators.h"
#include "core/interfaces/native/utility/callback_helper.h"

namespace OHOS::Ace::NG {
namespace {
    struct TabBarOptions {
        std::optional<std::string> text;
        std::optional<std::string> icon;
    };

    using TabBarOptionsVariant = std::variant<
        Ark_String,
        Ark_Resource,
        CustomNodeBuilder,
        Ark_TabBarOptions
    >;
} // namespace

namespace Validator {
void ValidatePaddingProperty(PaddingProperty& opt)
{
    Validator::ValidateNonNegative(opt.left);
    Validator::ValidateNonPercent(opt.left);
    Validator::ValidateNonNegative(opt.top);
    Validator::ValidateNonPercent(opt.top);
    Validator::ValidateNonNegative(opt.right);
    Validator::ValidateNonPercent(opt.right);
    Validator::ValidateNonNegative(opt.bottom);
    Validator::ValidateNonPercent(opt.bottom);
    Validator::ValidateNonNegative(opt.start);
    Validator::ValidateNonPercent(opt.start);
    Validator::ValidateNonNegative(opt.end);
    Validator::ValidateNonPercent(opt.end);
}
} // namespace Validator

auto g_setSubTabBarStyle = [](FrameNode* frameNode, const Ark_SubTabBarStyle& style) {
    // content
    std::optional<std::string> content = std::nullopt;
    LOGE("TabContentAttributeModifier.TabBar1Impl content is not supported yet.");

    // indicator
    auto indicator = Converter::OptConvert<Ark_IndicatorStyle>(style._indicator);
    if (indicator) {
        LOGE("TabContentAttributeModifier.TabBar1Impl indicator style is not supported yet.");
    }
    // selectedMode
    // TabContentModelNG::SetSelectedMode(frameNode, Converter::OptConvert<SelectedMode>(style._selectedMode));
    // board
    // TabContentModelNG::SetBoard(frameNode, Converter::OptConvert<BoardStyle>(style._board));
    // labelStyle
    auto labelStyle = Converter::OptConvert<Ark_LabelStyle>(style._labelStyle);
    if (labelStyle) {
        LOGE("TabContentAttributeModifier.TabBar1Impl labelStyle is not supported yet.");
    }
    // padding
    auto paddingProperty = Converter::OptConvert<PaddingProperty>(style._padding).value_or(PaddingProperty());
    Validator::ValidatePaddingProperty(paddingProperty);
    bool useLocalizedPadding = false;
    if (paddingProperty.start) {
        paddingProperty.left = paddingProperty.start;
        useLocalizedPadding = true;
    }
    if (paddingProperty.end) {
        paddingProperty.right = paddingProperty.end;
        useLocalizedPadding = true;
    }
    // TabContentModelNG::SetPadding(frameNode, paddingProperty, true);
    // TabContentModelNG::SetUseLocalizedPadding(frameNode, useLocalizedPadding);
    // id
    auto id = Converter::OptConvert<std::string>(style._id);
    // TabContentModelNG::SetId(frameNode, id);

    // TabContentModelNG::SetTabBarStyle(frameNode, TabBarStyle::SUBTABBATSTYLE);
    // TabContentModelNG::SetTabBar(frameNode, content, std::nullopt, nullptr);
};

auto g_setBottomTabBarStyle = [](FrameNode* frameNode, const Ark_BottomTabBarStyle& style) {
    // text
    std::optional<std::string> text = Converter::OptConvert<std::string>(style._text);
    // icon
    std::optional<std::string> icon = std::nullopt;
    Converter::VisitUnion(style._icon,
        [&icon](const Ark_ResourceStr& arkIcon) {
            icon = Converter::OptConvert<std::string>(arkIcon);
        },
        [](const Ark_TabBarSymbol& arkTabBarSymbol) {
            LOGE("TabContentAttributeModifier.TabBar1Impl tabBarSymbol is not supported yet.");
        },
        []() {}
    );
    // layoutMode
    // TabContentModelNG::SetLayoutMode(frameNode, Converter::OptConvert<LayoutMode>(style._layoutMode));
    // padding
    auto paddingProperty = Converter::OptConvert<PaddingProperty>(style._padding).value_or(PaddingProperty());
    Validator::ValidatePaddingProperty(paddingProperty);
    bool useLocalizedPadding = false;
    if (paddingProperty.start) {
        paddingProperty.left = paddingProperty.start;
        useLocalizedPadding = true;
    }
    if (paddingProperty.end) {
        paddingProperty.right = paddingProperty.end;
        useLocalizedPadding = true;
    }
    // TabContentModelNG::SetPadding(frameNode, paddingProperty, true);
    // TabContentModelNG::SetUseLocalizedPadding(frameNode, useLocalizedPadding);
    // verticalAlign
    // TabContentModelNG::SetVerticalAlign(frameNode, Converter::OptConvert<FlexAlign>(style._verticalAlign));
    // symmetricExtensible
    // TabContentModelNG::SetSymmetricExtensible(frameNode, Converter::OptConvert<bool>(style._symmetricExtensible));
    // labelStyle
    auto labelStyle = Converter::OptConvert<Ark_LabelStyle>(style._labelStyle);
    if (labelStyle) {
        LOGE("TabContentAttributeModifier.TabBar1Impl labelStyle is not supported yet.");
    }
    // iconStyle
    // TabContentModelNG::SetIconStyle(frameNode, Converter::OptConvert<IconStyle>(style._iconStyle));
    // id
    auto id = Converter::OptConvert<std::string>(style._id);
    // TabContentModelNG::SetId(frameNode, id);

    // TabContentModelNG::SetTabBarStyle(frameNode, TabBarStyle::BOTTOMTABBATSTYLE);
    // TabContentModelNG::SetTabBar(frameNode, text, icon, nullptr);
};

namespace Converter {
template<>
TabBarOptions Convert(const Ark_TabBarOptions& src)
{
    TabBarOptions options;
    options.text = OptConvert<std::string>(src.text);
    options.icon = OptConvert<std::string>(src.icon);
    return options;
}

template<>
IconStyle Convert(const Ark_TabBarIconStyle& src)
{
    IconStyle iconStyle;
    auto selectedColor = OptConvert<Color>(src.selectedColor);
    if (selectedColor) {
        iconStyle.selectedColor = selectedColor.value();
    }
    auto unselectedColor = OptConvert<Color>(src.unselectedColor);
    if (unselectedColor) {
        iconStyle.unselectedColor = unselectedColor.value();
    }
    return iconStyle;
}

template<>
void AssignCast(std::optional<SelectedMode>& dst, const Ark_SelectedMode& src)
{
    switch (src) {
        case ARK_SELECTED_MODE_INDICATOR: dst = SelectedMode::INDICATOR; break;
        case ARK_SELECTED_MODE_BOARD: dst = SelectedMode::BOARD; break;
        default: LOGE("Unexpected enum value in Ark_SelectedMode: %{public}d", src);
    }
}

template<>
void AssignCast(std::optional<BoardStyle>& dst, const Ark_BoardStyle& src)
{
    std::optional<Dimension> borderRadius = Converter::OptConvert<Dimension>(src.borderRadius);
    Validator::ValidateNonNegative(borderRadius);
    Validator::ValidateNonPercent(borderRadius);
    if (borderRadius) {
        dst = BoardStyle();
        dst->borderRadius = borderRadius.value();
    }
}

template<>
void AssignCast(std::optional<LayoutMode>& dst, const Ark_LayoutMode& src)
{
    switch (src) {
        case ARK_LAYOUT_MODE_AUTO: dst = LayoutMode::AUTO; break;
        case ARK_LAYOUT_MODE_VERTICAL: dst = LayoutMode::VERTICAL; break;
        case ARK_LAYOUT_MODE_HORIZONTAL: dst = LayoutMode::HORIZONTAL; break;
        default: LOGE("Unexpected enum value in Ark_LayoutMode: %{public}d", src);
    }
}
} // namespace Converter
} // namespace OHOS::Ace::NG

namespace OHOS::Ace::NG::GeneratedModifier {
namespace TabContentModifier {
Ark_NativePointer ConstructImpl(Ark_Int32 id,
                                Ark_Int32 flags)
{
    auto frameNode = TabContentModelNG::CreateFrameNode(id);
    frameNode->IncRefCount();
    return AceType::RawPtr(frameNode);
}
} // TabContentModifier
namespace TabContentInterfaceModifier {
void SetTabContentOptionsImpl(Ark_NativePointer node)
{
    // keep it empty because TabContent doesn`t have any options
}
} // TabContentInterfaceModifier
namespace TabContentAttributeModifier {
void TabBar0Impl(Ark_NativePointer node,
                 const Ark_Union_String_Resource_CustomBuilder_TabBarOptions* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    std::optional<std::string> label = std::nullopt;
    std::optional<std::string> icon = std::nullopt;
    TabBarBuilderFunc builder = nullptr;
    auto options = Converter::OptConvert<TabBarOptionsVariant>(*value);
    if (auto arkText = std::get_if<Ark_String>(&options.value()); arkText) {
        label = Converter::Convert<std::string>(*arkText);
    } else if (auto arkText = std::get_if<Ark_Resource>(&options.value()); arkText) {
        label = Converter::OptConvert<std::string>(*arkText);
    } else if (auto arkText = std::get_if<CustomNodeBuilder>(&options.value()); arkText) {
        builder = [callback = CallbackHelper(*arkText), node]() {
            auto builderNode = callback.BuildSync(node);
            NG::ViewStackProcessor::GetInstance()->Push(builderNode);
        };
    } else if (auto iconLabel = std::get_if<Ark_TabBarOptions>(&options.value()); iconLabel) {
        if (auto tabBarOptions = Converter::OptConvert<TabBarOptions>(*iconLabel); tabBarOptions) {
            label = tabBarOptions->text;
            icon = tabBarOptions->icon;
        }
    } else {
        LOGE("ARKOALA TabContentAttributeModifier.TabBar0Impl unknown value format.");
    }
    // TabContentModelNG::SetTabBar(frameNode, label, icon, std::move(builder));
}
void TabBar1Impl(Ark_NativePointer node,
                 const Ark_Union_SubTabBarStyle_BottomTabBarStyle* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    Converter::VisitUnion(*value,
        [frameNode](const Ark_SubTabBarStyle& style) {
            g_setSubTabBarStyle(frameNode, style);
        },
        [frameNode](const Ark_BottomTabBarStyle& style) {
            g_setBottomTabBarStyle(frameNode, style);
        },
        []() {}
    );
}
void OnWillShowImpl(Ark_NativePointer node,
                    const VoidCallback* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto onWillShow = [arkCallback = CallbackHelper(*value)]() -> void {
        arkCallback.Invoke();
    };
    TabContentModelNG::SetOnWillShow(frameNode, std::move(onWillShow));
}
void OnWillHideImpl(Ark_NativePointer node,
                    const VoidCallback* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto onWillHide = [arkCallback = CallbackHelper(*value)]() -> void {
        arkCallback.Invoke();
    };
    TabContentModelNG::SetOnWillHide(frameNode, std::move(onWillHide));
}
} // TabContentAttributeModifier
const GENERATED_ArkUITabContentModifier* GetTabContentModifier()
{
    static const GENERATED_ArkUITabContentModifier ArkUITabContentModifierImpl {
        TabContentModifier::ConstructImpl,
        TabContentInterfaceModifier::SetTabContentOptionsImpl,
        TabContentAttributeModifier::TabBar0Impl,
        TabContentAttributeModifier::TabBar1Impl,
        TabContentAttributeModifier::OnWillShowImpl,
        TabContentAttributeModifier::OnWillHideImpl,
    };
    return &ArkUITabContentModifierImpl;
}

}
