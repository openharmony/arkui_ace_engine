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
#include "core/interfaces/native/ani/frame_node_peer_impl.h"
#include "core/interfaces/native/implementation/bottom_tab_bar_style_peer.h"
#include "core/interfaces/native/implementation/sub_tab_bar_style_peer.h"
#include "core/interfaces/native/utility/converter.h"
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

void TabbarAddTabBarItem(const WeakPtr<NG::FrameNode>& weakNode)
{
    auto contentNode = weakNode.Upgrade();
    CHECK_NULL_VOID(contentNode);
    TabContentModelStatic::AddTabBarItem(contentNode, DEFAULT_NODE_SLOT, true);
}

void SetTabBarCustomBuilder(FrameNode* frameNode, const CustomNodeBuilder& arkBuilder)
{
    auto weakNode = AceType::WeakClaim(frameNode);
    auto arkNode = reinterpret_cast<Ark_NativePointer>(frameNode);
    CallbackHelper(arkBuilder)
        .BuildAsync([weakNode](const RefPtr<UINode>& uiNode) {
            auto contentNode = weakNode.Upgrade();
            CHECK_NULL_VOID(contentNode);
            auto builder = [weakUINode = WeakPtr<UINode>(uiNode)]() {
                auto uiNode = weakUINode.Upgrade();
                CHECK_NULL_VOID(uiNode);
                ViewStackProcessor::GetInstance()->Push(uiNode);
            };
            auto contentNodePtr = AceType::RawPtr(contentNode);
            TabContentModelStatic::SetTabBarStyle(contentNodePtr, TabBarStyle::NOSTYLE);
            TabContentModelStatic::SetTabBar(contentNodePtr, std::nullopt, std::nullopt, std::move(builder));
            TabContentModelStatic::AddTabBarItem(contentNode, DEFAULT_NODE_SLOT, true);
        },
        arkNode);
}
} // namespace

auto g_setSubTabBarStyle = [](FrameNode* frameNode, const Ark_SubTabBarStyle& style) {
    TabContentModelStatic::SetIndicator(frameNode, style->indicator);
    TabContentModelStatic::SetSelectedMode(frameNode, style->selectedMode);
    TabContentModelStatic::SetBoard(frameNode, style->board);
    TabContentModelStatic::SetLabelStyle(frameNode, style->labelStyle);
    TabContentModelStatic::SetPadding(frameNode, style->padding);
    TabContentModelStatic::SetUseLocalizedPadding(frameNode, style->useLocalizedPadding);
    TabContentModelStatic::SetId(frameNode, style->id);
    TabContentModelStatic::SetTabBarStyle(frameNode, TabBarStyle::SUBTABBATSTYLE);
    TabContentModelStatic::SetTabBar(frameNode, style->content, std::nullopt, nullptr);
    TabbarAddTabBarItem(AceType::WeakClaim(frameNode));
};

auto g_setBottomTabBarStyle = [](FrameNode* frameNode, const Ark_BottomTabBarStyle& style) {
    TabContentModelStatic::SetLayoutMode(frameNode, style->layoutMode);
    TabContentModelStatic::SetPadding(frameNode, style->padding);
    TabContentModelStatic::SetUseLocalizedPadding(frameNode, style->useLocalizedPadding);
    TabContentModelStatic::SetVerticalAlign(frameNode, style->verticalAlign);
    TabContentModelStatic::SetSymmetricExtensible(frameNode, style->symmetricExtensible);
    TabContentModelStatic::SetLabelStyle(frameNode, style->labelStyle);
    TabContentModelStatic::SetIconStyle(frameNode, style->iconStyle);
    TabContentModelStatic::SetId(frameNode, style->id);
    TabContentModelStatic::SetTabBarStyle(frameNode, TabBarStyle::BOTTOMTABBATSTYLE);
    TabContentModelStatic::SetTabBar(frameNode, style->text, style->icon, nullptr);
    TabbarAddTabBarItem(AceType::WeakClaim(frameNode));
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
void SetTabBarImpl(Ark_NativePointer node,
                   const Opt_Union_ComponentContent_SubTabBarStyle_BottomTabBarStyle_String_Resource_CustomNodeBuilder_TabBarOptions* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    Converter::VisitUnion(
        *value,
        [frameNode](const Ark_ComponentContent& arkContent) {
            auto contentPeer = reinterpret_cast<FrameNodePeer*>(arkContent);
            CHECK_NULL_VOID(contentPeer);
            auto contentNode = FrameNodePeer::GetFrameNodeByPeer(contentPeer);
            CHECK_NULL_VOID(contentNode);
            TabContentModelStatic::SetTabBarStyle(frameNode, TabBarStyle::NOSTYLE);
            TabContentModelStatic::SetTabBar(frameNode, std::nullopt, std::nullopt, nullptr);
            TabContentModelStatic::SetTabBarWithContent(frameNode, contentNode);
        },
        [frameNode](const Ark_SubTabBarStyle& style) { g_setSubTabBarStyle(frameNode, style); },
        [frameNode](const Ark_BottomTabBarStyle& style) { g_setBottomTabBarStyle(frameNode, style); },
        [frameNode](const Ark_String& arkContent) {
            auto text = Converter::OptConvert<std::string>(arkContent);
            TabContentModelStatic::SetTabBarStyle(frameNode, TabBarStyle::NOSTYLE);
            TabContentModelStatic::SetTabBar(frameNode, text, std::nullopt, nullptr);
            TabbarAddTabBarItem(AceType::WeakClaim(frameNode));
        },
        [frameNode](const Ark_Resource& arkContent) {
            auto text = Converter::OptConvert<std::string>(arkContent);
            TabContentModelStatic::SetTabBarStyle(frameNode, TabBarStyle::NOSTYLE);
            TabContentModelStatic::SetTabBar(frameNode, text, std::nullopt, nullptr);
            TabbarAddTabBarItem(AceType::WeakClaim(frameNode));
        },
        [frameNode](const CustomNodeBuilder& arkBuilder) {
            SetTabBarCustomBuilder(frameNode, arkBuilder);
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
            TabbarAddTabBarItem(AceType::WeakClaim(frameNode));
        },
        [frameNode]() {
            TabContentModelStatic::SetTabBarStyle(frameNode, TabBarStyle::NOSTYLE);
            TabContentModelStatic::SetTabBar(frameNode, std::nullopt, std::nullopt, nullptr);
            TabbarAddTabBarItem(AceType::WeakClaim(frameNode));
        });
}
void SetOnWillShowImpl(Ark_NativePointer node,
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
void SetOnWillHideImpl(Ark_NativePointer node,
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
        TabContentAttributeModifier::SetTabBarImpl,
        TabContentAttributeModifier::SetOnWillShowImpl,
        TabContentAttributeModifier::SetOnWillHideImpl,
    };
    return &ArkUITabContentModifierImpl;
}

}
