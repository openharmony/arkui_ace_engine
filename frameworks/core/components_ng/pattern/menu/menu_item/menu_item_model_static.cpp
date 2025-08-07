/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "core/components_ng/pattern/menu/menu_item/menu_item_model_static.h"

#include "core/components_ng/pattern/linear_layout/linear_layout_pattern.h"
#include "core/components_ng/pattern/menu/menu_item/menu_item_pattern.h"

namespace OHOS::Ace::NG {

void MenuItemModelStatic::AddChild(FrameNode* frameNode, const RefPtr<NG::UINode>& customNode)
{
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(customNode);
    if (!frameNode->GetChildren().empty()) {
        frameNode->Clean();
    }
    frameNode->AddChild(customNode);
    frameNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
}

void MenuItemModelStatic::DoMountRow(const RefPtr<NG::FrameNode>& menuItem)
{
    CHECK_NULL_VOID(menuItem);
    auto pipeline = PipelineBase::GetCurrentContextSafelyWithCheck();
    CHECK_NULL_VOID(pipeline);
    auto theme = pipeline->GetTheme<SelectTheme>();
    CHECK_NULL_VOID(theme);

    auto leftRow = FrameNode::CreateFrameNode(V2::ROW_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<LinearLayoutPattern>(false));
    CHECK_NULL_VOID(leftRow);
    auto leftRowLayoutProps = leftRow->GetLayoutProperty<LinearLayoutProperty>();
    CHECK_NULL_VOID(leftRowLayoutProps);
    leftRowLayoutProps->UpdateMainAxisAlign(FlexAlign::FLEX_START);
    leftRowLayoutProps->UpdateCrossAxisAlign(FlexAlign::CENTER);
    leftRowLayoutProps->UpdateSpace(theme->GetIconContentPadding());

    leftRow->MountToParent(menuItem);
    auto rightRow = FrameNode::CreateFrameNode(V2::ROW_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<LinearLayoutPattern>(false));
    CHECK_NULL_VOID(rightRow);
    auto rightRowLayoutProps = rightRow->GetLayoutProperty<LinearLayoutProperty>();
    CHECK_NULL_VOID(rightRowLayoutProps);
    rightRowLayoutProps->UpdateMainAxisAlign(FlexAlign::CENTER);
    rightRowLayoutProps->UpdateCrossAxisAlign(FlexAlign::CENTER);
    rightRowLayoutProps->UpdateSpace(theme->GetIconContentPadding());

    rightRow->MountToParent(menuItem);
}

void MenuItemModelStatic::UpdateRadius(const RefPtr<NG::FrameNode>& menuItem)
{
    CHECK_NULL_VOID(menuItem);
    // set border radius
    auto renderContext = menuItem->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    auto pipeline = PipelineBase::GetCurrentContextSafelyWithCheck();
    CHECK_NULL_VOID(pipeline);
    auto theme = pipeline->GetTheme<SelectTheme>();
    CHECK_NULL_VOID(theme);
    BorderRadiusProperty border;
    if (Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_TWELVE)) {
        border.SetRadius(theme->GetMenuDefaultInnerRadius());
    } else {
        border.SetRadius(theme->GetInnerBorderRadius());
    }
    renderContext->UpdateBorderRadius(border);
}

void MenuItemModelStatic::AddRowChild(FrameNode* frameNode, const MenuItemProperties& menuItemProps)
{
    CHECK_NULL_VOID(frameNode);
    auto menuItem = AceType::Claim<FrameNode>(frameNode);
    CHECK_NULL_VOID(menuItem);

    UpdateRadius(menuItem);
    if (menuItem->GetChildren().empty()) {
        DoMountRow(menuItem);
    }
    auto buildFunc = menuItemProps.buildFunc;
    auto pattern = menuItem->GetPattern<MenuItemPattern>();
    CHECK_NULL_VOID(pattern);
    if (buildFunc.has_value()) {
        pattern->SetSubBuilder(buildFunc.value_or(nullptr));
    }
}

void MenuItemModelStatic::UpdateMenuProperty(FrameNode* frameNode, const MenuItemProperties& menuItemProps)
{
    CHECK_NULL_VOID(frameNode);
    auto menuProperty = frameNode->GetLayoutProperty<MenuItemLayoutProperty>();
    CHECK_NULL_VOID(menuProperty);

    menuProperty->UpdateStartIcon(menuItemProps.startIcon.value_or(ImageSourceInfo("")));
    menuProperty->UpdateContent(menuItemProps.content);
    menuProperty->UpdateEndIcon(menuItemProps.endIcon.value_or(ImageSourceInfo("")));
    menuProperty->UpdateLabel(menuItemProps.labelInfo.value_or(""));
    menuProperty->SetStartSymbol(menuItemProps.startApply);
    menuProperty->SetEndSymbol(menuItemProps.endApply);
}

RefPtr<FrameNode> MenuItemModelStatic::CreateFrameNode(int32_t nodeId)
{
    auto frameNode = FrameNode::GetOrCreateFrameNode(
        V2::MENU_ITEM_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<MenuItemPattern>(); });
    return frameNode;
}

void MenuItemModelStatic::SetSelectedChangeEvent(FrameNode* frameNode, std::function<void(bool)>&& selectedChangeEvent)
{
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<MenuItemEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetSelectedChangeEvent(std::move(selectedChangeEvent));
}

void MenuItemModelStatic::SetSelected(FrameNode* frameNode, const std::optional<bool>& isSelected)
{
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<MenuItemPattern>();
    CHECK_NULL_VOID(pattern);
    auto eventHub = frameNode->GetEventHub<MenuItemEventHub>();
    CHECK_NULL_VOID(eventHub);
    if (isSelected.has_value()) {
        pattern->SetSelected(isSelected.value());
        eventHub->SetCurrentUIState(UI_STATE_SELECTED, isSelected.value());
    } else {
        pattern->SetSelected(false);
        eventHub->SetCurrentUIState(UI_STATE_SELECTED, false);
    }
}

void MenuItemModelStatic::SetLabelFontColor(FrameNode* frameNode, const std::optional<Color>& color)
{
    CHECK_NULL_VOID(frameNode);
    if (color.has_value()) {
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(MenuItemLayoutProperty, LabelFontColor, color.value(), frameNode);
    } else {
        ACE_RESET_NODE_LAYOUT_PROPERTY(MenuItemLayoutProperty, LabelFontColor, frameNode);
    }
}

void MenuItemModelStatic::SetFontColor(FrameNode* frameNode, const std::optional<Color>& color)
{
    CHECK_NULL_VOID(frameNode);
    if (color.has_value()) {
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(MenuItemLayoutProperty, FontColor, color.value(), frameNode);
    } else {
        ACE_RESET_NODE_LAYOUT_PROPERTY(MenuItemLayoutProperty, FontColor, frameNode);
    }
}

void MenuItemModelStatic::SetLabelFontSize(FrameNode* frameNode, const std::optional<Dimension>& fontSize)
{
    CHECK_NULL_VOID(frameNode);
    if (fontSize.has_value() && fontSize.value().IsValid()) {
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(MenuItemLayoutProperty, LabelFontSize, fontSize.value(), frameNode);
    } else {
        ACE_RESET_NODE_LAYOUT_PROPERTY(MenuItemLayoutProperty, LabelFontSize, frameNode);
    }
}

void MenuItemModelStatic::SetLabelFontWeight(FrameNode* frameNode, const std::optional<FontWeight>& weight)
{
    CHECK_NULL_VOID(frameNode);
    if (weight.has_value()) {
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(MenuItemLayoutProperty, LabelFontWeight, weight.value(), frameNode);
    } else {
        ACE_RESET_NODE_LAYOUT_PROPERTY(MenuItemLayoutProperty, LabelFontWeight, frameNode);
    }
}

void MenuItemModelStatic::SetLabelFontFamily(FrameNode* frameNode,
    const std::optional<std::vector<std::string>>& families)
{
    CHECK_NULL_VOID(frameNode);
    if (families.has_value()) {
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(MenuItemLayoutProperty, LabelFontFamily, families.value(), frameNode);
    } else {
        ACE_RESET_NODE_LAYOUT_PROPERTY(MenuItemLayoutProperty, LabelFontFamily, frameNode);
    }
}

void MenuItemModelStatic::SetLabelFontStyle(FrameNode* frameNode, const std::optional<Ace::FontStyle>& style)
{
    CHECK_NULL_VOID(frameNode);
    if (style.has_value()) {
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(MenuItemLayoutProperty, LabelItalicFontStyle, style.value(), frameNode);
    } else {
        ACE_RESET_NODE_LAYOUT_PROPERTY(MenuItemLayoutProperty, LabelItalicFontStyle, frameNode);
    }
}

void MenuItemModelStatic::SetFontSize(FrameNode* frameNode, const std::optional<Dimension>& fontSize)
{
    CHECK_NULL_VOID(frameNode);
    if (fontSize.has_value() && fontSize.value().IsValid()) {
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(MenuItemLayoutProperty, FontSize, fontSize.value(), frameNode);
    } else {
        ACE_RESET_NODE_LAYOUT_PROPERTY(MenuItemLayoutProperty, FontSize, frameNode);
    }
}

void MenuItemModelStatic::SetFontWeight(FrameNode* frameNode, const std::optional<FontWeight>& weight)
{
    CHECK_NULL_VOID(frameNode);
    if (weight.has_value()) {
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(MenuItemLayoutProperty, FontWeight, weight.value(), frameNode);
    } else {
        ACE_RESET_NODE_LAYOUT_PROPERTY(MenuItemLayoutProperty, FontWeight, frameNode);
    }
}

void MenuItemModelStatic::SetFontFamily(FrameNode* frameNode, const std::optional<std::vector<std::string>>& families)
{
    CHECK_NULL_VOID(frameNode);
    if (families.has_value()) {
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(MenuItemLayoutProperty, FontFamily, families.value(), frameNode);
    } else {
        ACE_RESET_NODE_LAYOUT_PROPERTY(MenuItemLayoutProperty, FontFamily, frameNode);
    }
}

void MenuItemModelStatic::SetFontStyle(FrameNode* frameNode, const std::optional<Ace::FontStyle>& style)
{
    CHECK_NULL_VOID(frameNode);
    if (style.has_value()) {
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(MenuItemLayoutProperty, ItalicFontStyle, style.value(), frameNode);
    } else {
        ACE_RESET_NODE_LAYOUT_PROPERTY(MenuItemLayoutProperty, ItalicFontStyle, frameNode);
    }
}

void MenuItemModelStatic::SetSelectIcon(FrameNode* frameNode, bool isShow)
{
    CHECK_NULL_VOID(frameNode);
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(MenuItemLayoutProperty, SelectIcon, isShow, frameNode);
}

void MenuItemModelStatic::SetSelectIconSrc(FrameNode* frameNode, const std::optional<std::string>& src)
{
    CHECK_NULL_VOID(frameNode);
    if (src.has_value()) {
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(MenuItemLayoutProperty, SelectIconSrc, src.value(), frameNode);
    } else {
        ACE_RESET_NODE_LAYOUT_PROPERTY(MenuItemLayoutProperty, SelectIconSrc, frameNode);
    }
}

void MenuItemModelStatic::SetSelectIconSymbol(FrameNode* frameNode,
    std::function<void(WeakPtr<NG::FrameNode>)>&& symbolApply)
{
    CHECK_NULL_VOID(frameNode);
    if (symbolApply != nullptr) {
        auto menuProperty = frameNode->GetLayoutProperty<MenuItemLayoutProperty>();
        CHECK_NULL_VOID(menuProperty);
        menuProperty->SetSelectSymbol(symbolApply);
    }
}

void MenuItemModelStatic::SetOnChange(FrameNode* frameNode, std::function<void(bool)>&& onChange)
{
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<MenuItemEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnChange(std::move(onChange));
}
} // namespace OHOS::Ace::NG
