/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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

#include "core/components_ng/pattern/menu/menu_item/menu_item_model_ng.h"

#include "base/geometry/dimension.h"
#include "base/utils/utils.h"
#include "core/components/select/select_theme.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/linear_layout/linear_layout_pattern.h"
#include "core/components_ng/pattern/menu/menu_item/menu_item_layout_property.h"
#include "core/components_ng/pattern/menu/menu_item/menu_item_pattern.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "core/pipeline/pipeline_base.h"

namespace OHOS::Ace::NG {
void MenuItemModelNG::Create(const RefPtr<UINode>& customNode)
{
    CHECK_NULL_VOID(customNode);
    auto* stack = ViewStackProcessor::GetInstance();
    int32_t nodeId = stack->ClaimNodeId();
    auto menuItem = FrameNode::GetOrCreateFrameNode(
        V2::MENU_ITEM_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<CustomMenuItemPattern>(); });
    CHECK_NULL_VOID(menuItem);
    stack->Push(menuItem);

    auto layoutProps = menuItem->GetLayoutProperty();
    CHECK_NULL_VOID(layoutProps);
    layoutProps->UpdateAlignment(Alignment::CENTER_LEFT);
    // set border radius
    auto renderContext = menuItem->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto theme = pipeline->GetTheme<SelectTheme>();
    CHECK_NULL_VOID(theme);
    BorderRadiusProperty border;
    border.SetRadius(theme->GetInnerBorderRadius());
    renderContext->UpdateBorderRadius(border);

    menuItem->AddChild(customNode);
}

/*
 * The structure of menu item is designed as follows :
 * |--menu_item
 *   |--left_row
 *     |--icon
 *     |--content
 *   |--right_row
 *     |--label
 *     |--end_icon
 */
void MenuItemModelNG::Create(const MenuItemProperties& menuItemProps)
{
    auto* stack = ViewStackProcessor::GetInstance();
    int32_t nodeId = stack->ClaimNodeId();
    auto menuItem = FrameNode::GetOrCreateFrameNode(
        V2::MENU_ITEM_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<MenuItemPattern>(); });
    CHECK_NULL_VOID(menuItem);
    stack->Push(menuItem);

    // set border radius
    auto renderContext = menuItem->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto theme = pipeline->GetTheme<SelectTheme>();
    CHECK_NULL_VOID(theme);
    BorderRadiusProperty border;
    border.SetRadius(theme->GetInnerBorderRadius());
    renderContext->UpdateBorderRadius(border);

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
    auto buildFunc = menuItemProps.buildFunc;
    if (buildFunc.has_value()) {
        auto pattern = menuItem->GetPattern<MenuItemPattern>();
        CHECK_NULL_VOID(pattern);
        pattern->SetSubBuilder(buildFunc.value_or(nullptr));
    }

    auto menuProperty = menuItem->GetLayoutProperty<MenuItemLayoutProperty>();
    CHECK_NULL_VOID(menuProperty);
    menuProperty->UpdateStartIcon(menuItemProps.startIcon.value_or(""));
    menuProperty->UpdateContent(menuItemProps.content);
    menuProperty->UpdateEndIcon(menuItemProps.endIcon.value_or(""));
    menuProperty->UpdateLabel(menuItemProps.labelInfo.value_or(""));
}

void MenuItemModelNG::SetSelected(bool isSelected)
{
    auto pattern = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<MenuItemPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetSelected(isSelected);
}

void MenuItemModelNG::SetSelectIcon(bool isShow)
{
    ACE_UPDATE_LAYOUT_PROPERTY(MenuItemLayoutProperty, SelectIcon, isShow);
}

void MenuItemModelNG::SetSelectIconSrc(const std::string& src)
{
    ACE_UPDATE_LAYOUT_PROPERTY(MenuItemLayoutProperty, SelectIconSrc, src);
}

void MenuItemModelNG::SetOnChange(std::function<void(bool)>&& onChange)
{
    auto eventHub = ViewStackProcessor::GetInstance()->GetMainFrameNodeEventHub<MenuItemEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnChange(onChange);
}

void MenuItemModelNG::SetFontSize(const Dimension& fontSize)
{
    if (fontSize.IsValid()) {
        ACE_UPDATE_LAYOUT_PROPERTY(MenuItemLayoutProperty, FontSize, fontSize);
    } else {
        LOGW("FontSize value is not valid");
        ACE_RESET_LAYOUT_PROPERTY(MenuItemLayoutProperty, FontSize);
    }
}

void MenuItemModelNG::SetFontWeight(FontWeight weight)
{
    ACE_UPDATE_LAYOUT_PROPERTY(MenuItemLayoutProperty, FontWeight, weight);
}

void MenuItemModelNG::SetFontStyle(Ace::FontStyle style)
{
    ACE_UPDATE_LAYOUT_PROPERTY(MenuItemLayoutProperty, ItalicFontStyle, style);
}

void MenuItemModelNG::SetFontColor(const std::optional<Color>& color)
{
    if (color.has_value()) {
        ACE_UPDATE_LAYOUT_PROPERTY(MenuItemLayoutProperty, FontColor, color.value());
    } else {
        ACE_RESET_LAYOUT_PROPERTY(MenuItemLayoutProperty, FontColor);
    }
}

void MenuItemModelNG::SetLabelFontSize(const Dimension& fontSize)
{
    if (fontSize.IsValid()) {
        ACE_UPDATE_LAYOUT_PROPERTY(MenuItemLayoutProperty, LabelFontSize, fontSize);
    } else {
        LOGW("FontSize value is not valid");
        ACE_RESET_LAYOUT_PROPERTY(MenuItemLayoutProperty, LabelFontSize);
    }
}

void MenuItemModelNG::SetLabelFontWeight(FontWeight weight)
{
    ACE_UPDATE_LAYOUT_PROPERTY(MenuItemLayoutProperty, LabelFontWeight, weight);
}

void MenuItemModelNG::SetLabelFontStyle(Ace::FontStyle style)
{
    ACE_UPDATE_LAYOUT_PROPERTY(MenuItemLayoutProperty, LabelItalicFontStyle, style);
}

void MenuItemModelNG::SetLabelFontColor(const std::optional<Color>& color)
{
    if (color.has_value()) {
        ACE_UPDATE_LAYOUT_PROPERTY(MenuItemLayoutProperty, LabelFontColor, color.value());
    } else {
        ACE_RESET_LAYOUT_PROPERTY(MenuItemLayoutProperty, LabelFontColor);
    }
}

void MenuItemModelNG::SetSelectedChangeEvent(std::function<void(bool)>&& selectedChangeEvent)
{
    auto eventHub = ViewStackProcessor::GetInstance()->GetMainFrameNodeEventHub<MenuItemEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetSelectedChangeEvent(selectedChangeEvent);
}
} // namespace OHOS::Ace::NG
