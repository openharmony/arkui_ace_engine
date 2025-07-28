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
#include "core/components_ng/pattern/tabs/tab_content_model_static.h"
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
void ValidatePaddingProperty(std::optional<PaddingProperty>& opt)
{
    if (!opt.has_value()) {
        return;
    }
    Validator::ValidateNonNegative(opt->left);
    Validator::ValidateNonPercent(opt->left);
    Validator::ValidateNonNegative(opt->top);
    Validator::ValidateNonPercent(opt->top);
    Validator::ValidateNonNegative(opt->right);
    Validator::ValidateNonPercent(opt->right);
    Validator::ValidateNonNegative(opt->bottom);
    Validator::ValidateNonPercent(opt->bottom);
    Validator::ValidateNonNegative(opt->start);
    Validator::ValidateNonPercent(opt->start);
    Validator::ValidateNonNegative(opt->end);
    Validator::ValidateNonPercent(opt->end);
}
} // namespace Validator

auto g_setSubTabBarStyle = [](FrameNode* frameNode, const Ark_SubTabBarStyle& style) {
    // content
    std::optional<std::string> content = std::nullopt;
    Converter::VisitUnion(style._content,
        [&content](const Ark_String& arkContent) {
            content = Converter::OptConvert<std::string>(arkContent);
        },
        [&content](const Ark_Resource& arkContent) {
            content = Converter::OptConvert<std::string>(arkContent);
        },
        [](const Ark_ComponentContent& arkContent) {
            LOGE("TabContentAttributeModifier.TabBar1Impl content (type Ark_ComponentContent) is not supported yet.");
        },
        []() {}
    );

    // indicator
    TabContentModelStatic::SetIndicator(frameNode, Converter::OptConvert<IndicatorStyle>(style._indicator));
    // selectedMode
    TabContentModelStatic::SetSelectedMode(frameNode, Converter::OptConvert<SelectedMode>(style._selectedMode));
    // board
    TabContentModelStatic::SetBoard(frameNode, Converter::OptConvert<BoardStyle>(style._board));
    // labelStyle
    TabContentModelStatic::SetLabelStyle(frameNode, Converter::OptConvert<LabelStyle>(style._labelStyle));
    // padding
    std::optional<PaddingProperty> optPadding;
    bool useLocalizedPadding = false;
    Converter::VisitUnion(style._padding,
        [&optPadding](const Ark_Union_Padding_Dimension& arkPadding) {
            optPadding = Converter::OptConvert<PaddingProperty>(arkPadding);
        },
        [&optPadding, &useLocalizedPadding](const Ark_LocalizedPadding& arkLocalizedPadding) {
            optPadding = Converter::OptConvert<PaddingProperty>(arkLocalizedPadding);
            useLocalizedPadding = true;
        },
        []() {}
    );
    Validator::ValidatePaddingProperty(optPadding);
    TabContentModelStatic::SetPadding(frameNode, optPadding);
    TabContentModelStatic::SetUseLocalizedPadding(frameNode, useLocalizedPadding);
    // id
    auto id = Converter::OptConvert<std::string>(style._id);
    TabContentModelStatic::SetId(frameNode, id);

    TabContentModelStatic::SetTabBarStyle(frameNode, TabBarStyle::SUBTABBATSTYLE);
    TabContentModelStatic::SetTabBar(frameNode, content, std::nullopt, nullptr);
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
    TabContentModelStatic::SetLayoutMode(frameNode, Converter::OptConvert<LayoutMode>(style._layoutMode));
    // padding
    std::optional<PaddingProperty> optPadding;
    bool useLocalizedPadding = false;
    Converter::VisitUnion(style._padding,
        [&optPadding](const Ark_Padding& arkPadding) {
            optPadding = Converter::OptConvert<PaddingProperty>(arkPadding);
        },
        [&optPadding](const Ark_Length& arkLength) {
            optPadding = Converter::OptConvert<PaddingProperty>(arkLength);
        },
        [&optPadding, &useLocalizedPadding](const Ark_LocalizedPadding& arkLocalizedPadding) {
            optPadding = Converter::OptConvert<PaddingProperty>(arkLocalizedPadding);
            useLocalizedPadding = true;
        },
        []() {}
    );
    Validator::ValidatePaddingProperty(optPadding);
    TabContentModelStatic::SetPadding(frameNode, optPadding);
    TabContentModelStatic::SetUseLocalizedPadding(frameNode, useLocalizedPadding);
    // verticalAlign
    TabContentModelStatic::SetVerticalAlign(frameNode, Converter::OptConvert<FlexAlign>(style._verticalAlign));
    // symmetricExtensible
    TabContentModelStatic::SetSymmetricExtensible(frameNode, Converter::OptConvert<bool>(style._symmetricExtensible));
    // labelStyle
    TabContentModelStatic::SetLabelStyle(frameNode, Converter::OptConvert<LabelStyle>(style._labelStyle));
    // iconStyle
    TabContentModelStatic::SetIconStyle(frameNode, Converter::OptConvert<IconStyle>(style._iconStyle));
    // id
    auto id = Converter::OptConvert<std::string>(style._id);
    TabContentModelStatic::SetId(frameNode, id);

    TabContentModelStatic::SetTabBarStyle(frameNode, TabBarStyle::BOTTOMTABBATSTYLE);
    TabContentModelStatic::SetTabBar(frameNode, text, icon, nullptr);
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

template<>
void AssignCast(std::optional<IndicatorStyle>& dst, const Ark_SubTabBarIndicatorStyle& src)
{
    dst = IndicatorStyle();
    auto pipeline = PipelineBase::GetCurrentContextSafelyWithCheck();
    CHECK_NULL_VOID(pipeline);
    auto tabTheme = pipeline->GetTheme<TabTheme>();
    if (tabTheme) {
        dst->color = tabTheme->GetActiveIndicatorColor();
        dst->height = tabTheme->GetActiveIndicatorWidth();
        dst->marginTop = tabTheme->GetSubTabIndicatorGap();
    }
    std::optional<Color> color = Converter::OptConvert<Color>(src.color);
    if (color) {
        dst->color = color.value();
    }
    std::optional<Dimension> height = Converter::OptConvert<Dimension>(src.height);
    Validator::ValidateNonNegative(height);
    Validator::ValidateNonPercent(height);
    if (height) {
        dst->height = height.value();
    }
    std::optional<Dimension> width = Converter::OptConvert<Dimension>(src.width);
    Validator::ValidateNonNegative(width);
    Validator::ValidateNonPercent(width);
    if (width) {
        dst->width = width.value();
    }
    std::optional<Dimension> borderRadius = Converter::OptConvert<Dimension>(src.borderRadius);
    Validator::ValidateNonNegative(borderRadius);
    Validator::ValidateNonPercent(borderRadius);
    if (borderRadius) {
        dst->borderRadius = borderRadius.value();
    }
    std::optional<Dimension> marginTop = Converter::OptConvert<Dimension>(src.marginTop);
    Validator::ValidateNonNegative(marginTop);
    Validator::ValidateNonPercent(marginTop);
    if (marginTop) {
        dst->marginTop = marginTop.value();
    }
}

template<>
void AssignCast(std::optional<LabelStyle>& dst, const Ark_TabBarLabelStyle& src)
{
    dst = LabelStyle();
    dst->textOverflow = Converter::OptConvert<TextOverflow>(src.overflow);
    auto maxLines = Converter::OptConvert<int32_t>(src.maxLines);
    if (maxLines) {
        maxLines = std::max(maxLines.value(), 1);
    }
    dst->maxLines = maxLines;
    dst->heightAdaptivePolicy =
        Converter::OptConvert<TextHeightAdaptivePolicy>(src.heightAdaptivePolicy);
    auto minFontSize = Converter::OptConvert<Dimension>(src.minFontSize);
    Validator::ValidateNonNegative(minFontSize);
    Validator::ValidateNonPercent(minFontSize);
    dst->minFontSize = minFontSize;
    auto maxFontSize = Converter::OptConvert<Dimension>(src.maxFontSize);
    Validator::ValidateNonNegative(maxFontSize);
    Validator::ValidateNonPercent(maxFontSize);
    dst->maxFontSize = maxFontSize;
    auto labelFont = Converter::OptConvert<Font>(src.font);
    if (labelFont) {
        dst->fontSize = labelFont->fontSize;
        dst->fontStyle = labelFont->fontStyle;
        dst->fontWeight = labelFont->fontWeight;
        if (labelFont->fontFamilies.size() > 0) {
            dst->fontFamily = labelFont->fontFamilies;
        }
    }
    dst->unselectedColor = Converter::OptConvert<Color>(src.unselectedColor);
    dst->selectedColor = Converter::OptConvert<Color>(src.selectedColor);
}
} // namespace Converter
} // namespace OHOS::Ace::NG

namespace OHOS::Ace::NG::GeneratedModifier {
namespace TabContentModifier {
Ark_NativePointer ConstructImpl(Ark_Int32 id,
                                Ark_Int32 flags)
{
    auto frameNode = TabContentModelStatic::CreateFrameNode(id);
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
                 const Opt_Union_String_Resource_CustomBuilder_TabBarOptions* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    std::optional<std::string> label = std::nullopt;
    std::optional<std::string> icon = std::nullopt;
    TabBarBuilderFunc builder = nullptr;
    auto options = Converter::OptConvert<TabBarOptionsVariant>(*value);
    if (auto arkText = std::get_if<Ark_String>(&options.value()); arkText) {
        label = Converter::Convert<std::string>(*arkText);
        TabContentModelStatic::SetTabBarStyle(frameNode, TabBarStyle::NOSTYLE);
        TabContentModelStatic::SetTabBar(frameNode, label, icon, std::move(builder));
    } else if (auto arkText = std::get_if<Ark_Resource>(&options.value()); arkText) {
        label = Converter::OptConvert<std::string>(*arkText);
        TabContentModelStatic::SetTabBarStyle(frameNode, TabBarStyle::NOSTYLE);
        TabContentModelStatic::SetTabBar(frameNode, label, icon, std::move(builder));
    } else if (auto arkText = std::get_if<CustomNodeBuilder>(&options.value()); arkText) {
        CallbackHelper(*arkText).BuildAsync([frameNode](const RefPtr<UINode>& uiNode) {
            auto builder = [frameNode, uiNode]() {
                ViewStackProcessor::GetInstance()->Push(uiNode);
            };
            TabContentModelStatic::SetTabBarStyle(frameNode, TabBarStyle::NOSTYLE);
            TabContentModelStatic::SetTabBar(frameNode, std::nullopt, std::nullopt, std::move(builder));
            }, node);
    } else if (auto iconLabel = std::get_if<Ark_TabBarOptions>(&options.value()); iconLabel) {
        if (auto tabBarOptions = Converter::OptConvert<TabBarOptions>(*iconLabel); tabBarOptions) {
            label = tabBarOptions->text;
            icon = tabBarOptions->icon;
        }
        TabContentModelStatic::SetTabBarStyle(frameNode, TabBarStyle::NOSTYLE);
        TabContentModelStatic::SetTabBar(frameNode, label, icon, std::move(builder));
    } else {
        LOGE("ARKOALA TabContentAttributeModifier.TabBar0Impl unknown value format.");
        TabContentModelStatic::SetTabBarStyle(frameNode, TabBarStyle::NOSTYLE);
        TabContentModelStatic::SetTabBar(frameNode, label, icon, std::move(builder));
    }
}
void TabBar1Impl(Ark_NativePointer node,
                 const Opt_Union_SubTabBarStyle_BottomTabBarStyle* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
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
void TabBar2Impl(Ark_NativePointer node,
                 const Opt_Type_TabContentAttribute_tabBar_content* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    Converter::VisitUnion(*value,
        [](const Ark_ComponentContent& arkContent) {
            LOGE("TabContentAttributeModifier.TabBar2Impl type Ark_ComponentContent is not supported yet.");
        },
        [frameNode](const Ark_SubTabBarStyle& style) {
            g_setSubTabBarStyle(frameNode, style);
        },
        [frameNode](const Ark_BottomTabBarStyle& style) {
            g_setBottomTabBarStyle(frameNode, style);
        },
        [frameNode](const Ark_String& arkContent) {
            auto text = Converter::OptConvert<std::string>(arkContent);
            TabContentModelStatic::SetTabBarStyle(frameNode, TabBarStyle::NOSTYLE);
            TabContentModelStatic::SetTabBar(frameNode, text, std::nullopt, nullptr);
        },
        [frameNode](const Ark_Resource& arkContent) {
            auto text = Converter::OptConvert<std::string>(arkContent);
            TabContentModelStatic::SetTabBarStyle(frameNode, TabBarStyle::NOSTYLE);
            TabContentModelStatic::SetTabBar(frameNode, text, std::nullopt, nullptr);
        },
        [frameNode](const CustomNodeBuilder& arkBuilder) {
            auto builder = [callback = CallbackHelper(arkBuilder), frameNode]() {
                auto builderNode = callback.BuildSync(frameNode);
                NG::ViewStackProcessor::GetInstance()->Push(builderNode);
            };
            TabContentModelStatic::SetTabBarStyle(frameNode, TabBarStyle::NOSTYLE);
            TabContentModelStatic::SetTabBar(frameNode, std::nullopt, std::nullopt, std::move(builder));
        },
        [frameNode](const Ark_TabBarOptions& arkTabBarOptions) {
            std::optional<std::string> label;
            std::optional<std::string> icon;
            if (auto tabBarOptions = Converter::OptConvert<TabBarOptions>(arkTabBarOptions)) {
                label = tabBarOptions->text;
                icon = tabBarOptions->icon;
            }
            TabContentModelStatic::SetTabBarStyle(frameNode, TabBarStyle::NOSTYLE);
            TabContentModelStatic::SetTabBar(frameNode, label, icon, nullptr);
        },
        []() {}
    );
}
void OnWillShowImpl(Ark_NativePointer node,
                    const Opt_VoidCallback* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
        TabContentModelStatic::SetOnWillShow(frameNode, nullptr);
        return;
    }
    auto onWillShow = [arkCallback = CallbackHelper(*optValue)]() -> void {
        arkCallback.Invoke();
    };
    TabContentModelStatic::SetOnWillShow(frameNode, std::move(onWillShow));
}
void OnWillHideImpl(Ark_NativePointer node,
                    const Opt_VoidCallback* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
        TabContentModelStatic::SetOnWillHide(frameNode, nullptr);
        return;
    }
    auto onWillHide = [arkCallback = CallbackHelper(*optValue)]() -> void {
        arkCallback.Invoke();
    };
    TabContentModelStatic::SetOnWillHide(frameNode, std::move(onWillHide));
}
} // TabContentAttributeModifier
const GENERATED_ArkUITabContentModifier* GetTabContentModifier()
{
    static const GENERATED_ArkUITabContentModifier ArkUITabContentModifierImpl {
        TabContentModifier::ConstructImpl,
        TabContentInterfaceModifier::SetTabContentOptionsImpl,
        TabContentAttributeModifier::TabBar0Impl,
        TabContentAttributeModifier::TabBar1Impl,
        TabContentAttributeModifier::TabBar2Impl,
        TabContentAttributeModifier::OnWillShowImpl,
        TabContentAttributeModifier::OnWillHideImpl,
    };
    return &ArkUITabContentModifierImpl;
}

}
