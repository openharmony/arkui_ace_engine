/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
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

#include "core/components_ng/pattern/navigation/navigation_view.h"

#include <cstdint>
#include <iterator>

#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"
#include "base/utils/utils.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/custom/custom_node.h"
#include "core/components_ng/pattern/divider/divider_layout_property.h"
#include "core/components_ng/pattern/divider/divider_pattern.h"
#include "core/components_ng/pattern/divider/divider_render_property.h"
#include "core/components_ng/pattern/image/image_layout_property.h"
#include "core/components_ng/pattern/image/image_pattern.h"
#include "core/components_ng/pattern/linear_layout/linear_layout_pattern.h"
#include "core/components_ng/pattern/navigation/bar_item_event_hub.h"
#include "core/components_ng/pattern/navigation/bar_item_node.h"
#include "core/components_ng/pattern/navigation/bar_item_pattern.h"
#include "core/components_ng/pattern/navigation/nav_bar_layout_property.h"
#include "core/components_ng/pattern/navigation/nav_bar_node.h"
#include "core/components_ng/pattern/navigation/nav_bar_pattern.h"
#include "core/components_ng/pattern/navigation/navigation_group_node.h"
#include "core/components_ng/pattern/navigation/navigation_layout_property.h"
#include "core/components_ng/pattern/navigation/navigation_pattern.h"
#include "core/components_ng/pattern/navigation/title_bar_node.h"
#include "core/components_ng/pattern/navigation/title_bar_pattern.h"
#include "core/components_ng/pattern/navigator/navigator_event_hub.h"
#include "core/components_ng/pattern/navigator/navigator_pattern.h"
#include "core/components_ng/pattern/text/text_layout_property.h"
#include "core/components_ng/pattern/text/text_pattern.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "core/pipeline/base/element_register.h"
#include "core/pipeline_ng/ui_task_scheduler.h"

namespace OHOS::Ace::NG {
namespace {
RefPtr<FrameNode> CreateBarItemTextNode(const std::string& text)
{
    int32_t nodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto textNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, nodeId, AceType::MakeRefPtr<TextPattern>());
    auto textLayoutProperty = textNode->GetLayoutProperty<TextLayoutProperty>();
    CHECK_NULL_RETURN(textLayoutProperty, nullptr);
    textLayoutProperty->UpdateContent(text);
    textLayoutProperty->UpdateFontSize(TEXT_FONT_SIZE);
    textLayoutProperty->UpdateTextColor(TEXT_COLOR);
    return textNode;
}

RefPtr<FrameNode> CreateBarItemIconNode(const std::string& src)
{
    int32_t nodeId = ElementRegister::GetInstance()->MakeUniqueId();
    ImageSourceInfo info(src);
    auto iconNode = FrameNode::CreateFrameNode(V2::IMAGE_ETS_TAG, nodeId, AceType::MakeRefPtr<ImagePattern>());
    auto imageLayoutProperty = iconNode->GetLayoutProperty<ImageLayoutProperty>();
    CHECK_NULL_RETURN(imageLayoutProperty, nullptr);
    imageLayoutProperty->UpdateImageSourceInfo(info);
    imageLayoutProperty->UpdateUserDefinedIdealSize(CalcSize(CalcLength(ICON_SIZE), CalcLength(ICON_SIZE)));
    iconNode->MarkModifyDone();
    return iconNode;
}

void UpdateBarItemNodeWithItem(const RefPtr<BarItemNode>& barItemNode, const BarItem& barItem)
{
    if (barItem.text.has_value() && !barItem.text.value().empty()) {
        auto textNode = CreateBarItemTextNode(barItem.text.value());
        barItemNode->SetTextNode(textNode);
        barItemNode->AddChild(textNode);
    }
    if (barItem.icon.has_value() && !barItem.icon.value().empty()) {
        auto iconNode = CreateBarItemIconNode(barItem.icon.value());
        barItemNode->SetIconNode(iconNode);
        barItemNode->AddChild(iconNode);
    }
    if (barItem.action) {
        auto eventHub = barItemNode->GetEventHub<BarItemEventHub>();
        CHECK_NULL_VOID(eventHub);
        eventHub->SetItemAction(barItem.action);
    }
    auto barItemPattern = barItemNode->GetPattern<BarItemPattern>();
    barItemNode->MarkModifyDone();
}

void UpdateOldBarItems(const RefPtr<UINode>& oldBarContainer, const std::list<BarItem>& newBarItems)
{
    auto oldBarItems = oldBarContainer->GetChildren();
    auto prevChildrenSize = static_cast<int32_t>(oldBarItems.size());
    auto newChildrenSize = static_cast<int32_t>(newBarItems.size());
    auto oldIter = oldBarItems.begin();
    auto newIter = newBarItems.begin();
    // if old container has m items and incoming array has n items
    // we update first min(m, n) items in the old container
    for (int32_t i = 0; i < std::min(prevChildrenSize, newChildrenSize); i++) {
        do {
            auto oldBarItem = AceType::DynamicCast<BarItemNode>(*oldIter);
            BarItem newBarItem = *newIter;
            if (!oldBarItem) {
                break;
            }
            // TODO: fix error for update condition when add or delete child, and update old bar item will not work
            if (newBarItem.text.has_value()) {
                oldBarItem->UpdateText(newBarItem.text.value());
                if (oldBarItem->GetTextNode()) {
                    auto textNode = AceType::DynamicCast<FrameNode>(oldBarItem->GetTextNode());
                    CHECK_NULL_VOID(textNode);
                    auto textLayoutProperty = textNode->GetLayoutProperty<TextLayoutProperty>();
                    CHECK_NULL_VOID(textLayoutProperty);
                    textLayoutProperty->UpdateContent(newBarItem.text.value());
                    textNode->MarkModifyDone();
                } else {
                    auto textNode = CreateBarItemTextNode(newBarItem.text.value());
                    oldBarItem->SetTextNode(textNode);
                    oldBarItem->AddChild(textNode);
                    oldBarItem->MarkModifyDone();
                }
            } else {
                oldBarItem->ResetText();
                if (oldBarItem->GetTextNode()) {
                    auto textNode = AceType::DynamicCast<FrameNode>(oldBarItem->GetTextNode());
                    CHECK_NULL_VOID(textNode);
                    oldBarItem->RemoveChild(textNode);
                }
            }
            if (newBarItem.icon.has_value()) {
                oldBarItem->UpdateIconSrc(newBarItem.icon.value());
                if (oldBarItem->GetIconNode()) {
                    auto iconNode = AceType::DynamicCast<FrameNode>(oldBarItem->GetIconNode());
                    CHECK_NULL_VOID(iconNode);
                    auto imageLayoutProperty = iconNode->GetLayoutProperty<ImageLayoutProperty>();
                    CHECK_NULL_VOID(imageLayoutProperty);
                    imageLayoutProperty->UpdateImageSourceInfo(ImageSourceInfo(newBarItem.icon.value()));
                    iconNode->MarkModifyDone();
                } else {
                    auto iconNode = CreateBarItemIconNode(newBarItem.icon.value());
                    oldBarItem->SetIconNode(iconNode);
                    oldBarItem->AddChild(iconNode);
                    oldBarItem->MarkModifyDone();
                }
            } else {
                oldBarItem->ResetIconSrc();
                if (oldBarItem->GetIconNode()) {
                    auto iconNode = AceType::DynamicCast<FrameNode>(oldBarItem->GetIconNode());
                    CHECK_NULL_VOID(iconNode);
                    oldBarItem->RemoveChild(iconNode);
                }
            }
        } while (false);
        oldIter++;
        newIter++;
    }
    // if m > n, we remove (m - n) children from the back of old container
    if (prevChildrenSize > newChildrenSize) {
        for (int32_t i = 0; i < prevChildrenSize - newChildrenSize; i++) {
            oldBarItems.pop_back();
        }
    } else if (prevChildrenSize < newChildrenSize) {
        // if m < n, we add (n - m) children created by info in new item list
        for (int32_t i = 0; i < newChildrenSize - prevChildrenSize; i++) {
            auto nodeId = ElementRegister::GetInstance()->MakeUniqueId();
            auto barItemNode = AceType::MakeRefPtr<BarItemNode>(V2::BAR_ITEM_ETS_TAG, nodeId);
            barItemNode->InitializePatternAndContext();
            UpdateBarItemNodeWithItem(barItemNode, *newIter);
            oldBarContainer->AddChild(barItemNode);
            newIter++;
            auto container = AceType::DynamicCast<TitleBarNode>(oldBarContainer);
            CHECK_NULL_VOID(container);
            container->MarkModifyDone();
        }
    }
}
} // namespace

void NavigationView::Create()
{
    auto* stack = ViewStackProcessor::GetInstance();
    // navigation node
    int32_t nodeId = stack->ClaimNodeId();
    auto navigationGroupNode = NavigationGroupNode::GetOrCreateGroupNode(
        V2::NAVIGATION_VIEW_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<NavigationPattern>(); });

    // navBar node
    if (!navigationGroupNode->GetNavBarNode()) {
        int32_t navBarNodeId = ElementRegister::GetInstance()->MakeUniqueId();
        auto navBarNode = NavBarNode::GetOrCreateNavBarNode(
            V2::NAVBAR_ETS_TAG, navBarNodeId, []() { return AceType::MakeRefPtr<NavBarPattern>(); });
        navigationGroupNode->AddChild(navBarNode);
        navigationGroupNode->SetNavBarNode(navBarNode);

        // titleBar node
        if (!navBarNode->GetTitleBarNode()) {
            int32_t titleBarNodeId = ElementRegister::GetInstance()->MakeUniqueId();
            auto titleBarNode = TitleBarNode::GetOrCreateTitleBarNode(
                V2::TITLE_BAR_ETS_TAG, titleBarNodeId, []() { return AceType::MakeRefPtr<TitleBarPattern>(); });
            navBarNode->AddChild(titleBarNode);
            navBarNode->SetTitleBarNode(titleBarNode);
        }

        // navBar content node
        if (!navBarNode->GetNavBarContentNode()) {
            int32_t navBarContentNodeId = ElementRegister::GetInstance()->MakeUniqueId();
            auto navBarContentNode = FrameNode::GetOrCreateFrameNode(V2::NAVBAR_CONTENT_ETS_TAG, navBarContentNodeId,
                []() { return AceType::MakeRefPtr<LinearLayoutPattern>(true); });
            navBarNode->AddChild(navBarContentNode);
            navBarNode->SetNavBarContentNode(navBarContentNode);
        }

        // toolBar node
        if (!navBarNode->GetToolBarNode()) {
            int32_t toolBarNodeId = ElementRegister::GetInstance()->MakeUniqueId();
            auto toolBarNode = FrameNode::GetOrCreateFrameNode(
                V2::TOOL_BAR_ETS_TAG, toolBarNodeId, []() { return AceType::MakeRefPtr<LinearLayoutPattern>(false); });
            navBarNode->AddChild(toolBarNode);
            navBarNode->SetToolBarNode(toolBarNode);
            navBarNode->SetPreToolBarNode(toolBarNode);
            navBarNode->UpdatePrevToolBarIsCustom(false);
        }
        auto navBarLayoutProperty = navBarNode->GetLayoutProperty<NavBarLayoutProperty>();
        CHECK_NULL_VOID(navBarLayoutProperty);
        navBarLayoutProperty->UpdateTitleMode(NavigationTitleMode::FREE);
    }

    // content node
    if (!navigationGroupNode->GetContentNode()) {
        int32_t contentNodeId = ElementRegister::GetInstance()->MakeUniqueId();
        auto contentNode = FrameNode::GetOrCreateFrameNode(V2::NAVIGATION_CONTENT_ETS_TAG, contentNodeId,
            []() { return AceType::MakeRefPtr<LinearLayoutPattern>(true); });
        navigationGroupNode->AddChild(contentNode);
        navigationGroupNode->SetContentNode(contentNode);
    }

    // divider node
    if (!navigationGroupNode->GetDividerNode()) {
        int32_t dividerNodeId = ElementRegister::GetInstance()->MakeUniqueId();
        auto dividerNode = FrameNode::GetOrCreateFrameNode(
            V2::DIVIDER_ETS_TAG, dividerNodeId, []() { return AceType::MakeRefPtr<DividerPattern>(); });
        navigationGroupNode->AddChild(dividerNode);
        navigationGroupNode->SetDividerNode(dividerNode);

        auto dividerlayoutProperty = dividerNode->GetLayoutProperty<DividerLayoutProperty>();
        CHECK_NULL_VOID(dividerlayoutProperty);
        dividerlayoutProperty->UpdateStrokeWidth(DIVIDER_WIDTH);
        dividerlayoutProperty->UpdateVertical(true);
        auto dividerRenderProperty = dividerNode->GetPaintProperty<DividerRenderProperty>();
        CHECK_NULL_VOID(dividerRenderProperty);
        dividerRenderProperty->UpdateDividerColor(DIVIDER_COLOR);
    }

    stack->Push(navigationGroupNode);
    auto navigationLayoutProperty = navigationGroupNode->GetLayoutProperty<NavigationLayoutProperty>();
    navigationLayoutProperty->UpdateNavigationMode(NavigationMode::STACK);
}

void NavigationView::SetTitle(const std::string& title)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    auto navigationGroupNode = AceType::DynamicCast<NavigationGroupNode>(frameNode);
    CHECK_NULL_VOID(navigationGroupNode);
    auto navBarNode = AceType::DynamicCast<NavBarNode>(navigationGroupNode->GetNavBarNode());
    CHECK_NULL_VOID(navBarNode);
    do {
        if (!navBarNode->GetTitle()) {
            navBarNode->UpdateTitleNodeOperation(ChildNodeOperation::ADD);
            break;
        }
        // if previous title is not a frame node, we remove it and create a new node
        auto titleNode = AceType::DynamicCast<FrameNode>(navBarNode->GetTitle());
        if (!titleNode) {
            navBarNode->UpdateTitleNodeOperation(ChildNodeOperation::REPLACE);
            break;
        }
        auto titleProperty = titleNode->GetLayoutProperty<TextLayoutProperty>();
        // previous title is not a text node and might be custom, we remove it and create a new node
        if (!titleProperty) {
            navBarNode->UpdateTitleNodeOperation(ChildNodeOperation::REPLACE);
            break;
        }
        // text content is the same, do nothing
        if (titleProperty->GetContentValue() == title) {
            navBarNode->UpdateTitleNodeOperation(ChildNodeOperation::NONE);
            return;
        }
        // update title content only without changing node
        titleProperty->UpdateContent(title);
        navBarNode->UpdateTitleNodeOperation(ChildNodeOperation::NONE);
        return;
    } while (false);
    int32_t titleNodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto titleNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, titleNodeId, AceType::MakeRefPtr<TextPattern>());
    auto textLayoutProperty = titleNode->GetLayoutProperty<TextLayoutProperty>();
    CHECK_NULL_VOID(textLayoutProperty);
    textLayoutProperty->UpdateContent(title);
    textLayoutProperty->UpdateFontSize(TITLE_FONT_SIZE);
    textLayoutProperty->UpdateTextColor(TITLE_COLOR);
    textLayoutProperty->UpdateFontWeight(FontWeight::BOLD);
    navBarNode->SetTitle(titleNode);
    navBarNode->UpdatePrevTitleIsCustom(false);
    navBarNode->MarkModifyDone();
}

void NavigationView::SetCustomTitle(const RefPtr<UINode>& customTitle)
{
    CHECK_NULL_VOID(customTitle);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    auto navigationGroupNode = AceType::DynamicCast<NavigationGroupNode>(frameNode);
    CHECK_NULL_VOID(navigationGroupNode);
    auto navBarNode = AceType::DynamicCast<NavBarNode>(navigationGroupNode->GetNavBarNode());
    CHECK_NULL_VOID(navBarNode);
    if (navBarNode->GetTitle()) {
        if (customTitle->GetId() == navBarNode->GetTitle()->GetId()) {
            navBarNode->UpdateTitleNodeOperation(ChildNodeOperation::NONE);
        } else {
            navBarNode->SetTitle(customTitle);
            navBarNode->UpdateTitleNodeOperation(ChildNodeOperation::REPLACE);
            navBarNode->MarkModifyDone();
        }
        return;
    }
    navBarNode->SetTitle(customTitle);
    navBarNode->UpdateTitleNodeOperation(ChildNodeOperation::ADD);
    navBarNode->UpdatePrevTitleIsCustom(true);
    navBarNode->MarkModifyDone();
}

void NavigationView::SetSubtitle(const std::string& subtitle)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    auto navigationGroupNode = AceType::DynamicCast<NavigationGroupNode>(frameNode);
    CHECK_NULL_VOID(navigationGroupNode);
    auto navBarNode = AceType::DynamicCast<NavBarNode>(navigationGroupNode->GetNavBarNode());
    CHECK_NULL_VOID(navBarNode);
    do {
        if (!navBarNode->GetSubtitle()) {
            navBarNode->UpdateSubtitleNodeOperation(ChildNodeOperation::ADD);
            break;
        }
        auto subtitleNode = AceType::DynamicCast<FrameNode>(navBarNode->GetSubtitle());
        if (!subtitleNode) {
            navBarNode->UpdateSubtitleNodeOperation(ChildNodeOperation::REPLACE);
            break;
        }
        auto subtitleProperty = subtitleNode->GetLayoutProperty<TextLayoutProperty>();
        if (!subtitleProperty) {
            navBarNode->UpdateSubtitleNodeOperation(ChildNodeOperation::REPLACE);
            break;
        }
        if (subtitleProperty->GetContentValue() == subtitle) {
            navBarNode->UpdateSubtitleNodeOperation(ChildNodeOperation::NONE);
            return;
        }
        subtitleProperty->UpdateContent(subtitle);
        navBarNode->UpdateSubtitleNodeOperation(ChildNodeOperation::NONE);
        return;
    } while (false);
    int32_t subtitleNodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto subtitleNode =
        FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, subtitleNodeId, AceType::MakeRefPtr<TextPattern>());
    auto textLayoutProperty = subtitleNode->GetLayoutProperty<TextLayoutProperty>();
    CHECK_NULL_VOID(textLayoutProperty);
    textLayoutProperty->UpdateContent(subtitle);
    textLayoutProperty->UpdateFontSize(SUBTITLE_FONT_SIZE);
    textLayoutProperty->UpdateTextColor(SUBTITLE_COLOR);
    textLayoutProperty->UpdateFontWeight(FontWeight::REGULAR); // ohos_id_text_font_family_regular
    navBarNode->SetSubtitle(subtitleNode);
    navBarNode->MarkModifyDone();
}

void NavigationView::SetMenuItems(std::list<BarItem>&& menuItems)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    auto navigationGroupNode = AceType::DynamicCast<NavigationGroupNode>(frameNode);
    CHECK_NULL_VOID(navigationGroupNode);
    auto navBarNode = AceType::DynamicCast<NavBarNode>(navigationGroupNode->GetNavBarNode());
    CHECK_NULL_VOID(navBarNode);
    // if previous menu is custom, just remove it and create new menu, otherwise update old menu
    if (navBarNode->GetPrevMenuIsCustom().value_or(false)) {
        navBarNode->UpdateMenuNodeOperation(ChildNodeOperation::REPLACE);
    } else {
        if (navBarNode->GetMenu()) {
            auto titleBarNode = AceType::DynamicCast<TitleBarNode>(navBarNode->GetTitleBarNode());
            CHECK_NULL_VOID(titleBarNode);
            UpdateOldBarItems(titleBarNode->GetMenu(), menuItems);
            navBarNode->SetMenu(titleBarNode->GetMenu());
            navBarNode->UpdateMenuNodeOperation(ChildNodeOperation::NONE);
            navBarNode->MarkModifyDone();
            return;
        }
        navBarNode->UpdateMenuNodeOperation(ChildNodeOperation::ADD);
    }
    int32_t menuNodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto menuNode = FrameNode::GetOrCreateFrameNode(
        V2::NAVIGATION_MENU_ETS_TAG, menuNodeId, []() { return AceType::MakeRefPtr<LinearLayoutPattern>(false); });
    auto rowProperty = menuNode->GetLayoutProperty<LinearLayoutProperty>();
    CHECK_NULL_VOID(rowProperty);
    rowProperty->UpdateMainAxisAlign(FlexAlign::FLEX_END);
    for (const auto& menuItem : menuItems) {
        int32_t barItemNodeId = ElementRegister::GetInstance()->MakeUniqueId();
        auto barItemNode = AceType::MakeRefPtr<BarItemNode>(V2::BAR_ITEM_ETS_TAG, barItemNodeId);
        barItemNode->InitializePatternAndContext();
        UpdateBarItemNodeWithItem(barItemNode, menuItem);
        menuNode->AddChild(barItemNode);
    }
    navBarNode->SetMenu(menuNode);
    navBarNode->UpdatePrevMenuIsCustom(false);
    navBarNode->MarkModifyDone();
}

void NavigationView::SetCustomMenu(const RefPtr<UINode>& customMenu)
{
    CHECK_NULL_VOID(customMenu);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    auto navigationGroupNode = AceType::DynamicCast<NavigationGroupNode>(frameNode);
    CHECK_NULL_VOID(navigationGroupNode);
    auto navBarNode = AceType::DynamicCast<NavBarNode>(navigationGroupNode->GetNavBarNode());
    CHECK_NULL_VOID(navBarNode);
    // if previous menu exists, remove it if their ids are not the same
    // if previous node is not custom, their ids must not be the same
    if (navBarNode->GetMenu()) {
        if (customMenu->GetId() == navBarNode->GetMenu()->GetId()) {
            navBarNode->UpdateMenuNodeOperation(ChildNodeOperation::NONE);
            return;
        }
        navBarNode->SetMenu(customMenu);
        navBarNode->UpdatePrevMenuIsCustom(true);
        navBarNode->UpdateMenuNodeOperation(ChildNodeOperation::REPLACE);
        navBarNode->MarkModifyDone();
        return;
    }
    navBarNode->SetMenu(customMenu);
    navBarNode->UpdatePrevMenuIsCustom(true);
    navBarNode->UpdateMenuNodeOperation(ChildNodeOperation::ADD);
    navBarNode->MarkModifyDone();
}

void NavigationView::SetTitleMode(NavigationTitleMode mode)
{
    if (mode != NavigationTitleMode::MINI) {
        return;
    }
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    auto navigationGroupNode = AceType::DynamicCast<NavigationGroupNode>(frameNode);
    CHECK_NULL_VOID(navigationGroupNode);
    auto navBarNode = AceType::DynamicCast<NavBarNode>(navigationGroupNode->GetNavBarNode());
    CHECK_NULL_VOID(navBarNode);
    auto navBarLayoutProperty = navBarNode->GetLayoutProperty<NavBarLayoutProperty>();
    CHECK_NULL_VOID(navBarLayoutProperty);
    bool needAddBackButton = false;
    bool needRemoveBackButton = false;
    do {
        // add back button if current mode is mini and one of the following condition:
        // first create or not first create but previous mode is not mini
        if (navBarLayoutProperty->GetTitleModeValue(NavigationTitleMode::FREE) != NavigationTitleMode::MINI &&
            mode == NavigationTitleMode::MINI) {
            needAddBackButton = true;
            break;
        }
        // remove back button if current mode is not mini and previous mode is mini
        if (navBarLayoutProperty->GetTitleModeValue(NavigationTitleMode::FREE) == NavigationTitleMode::MINI &&
            mode != NavigationTitleMode::MINI) {
            needRemoveBackButton = true;
            break;
        }
    } while (false);
    navBarLayoutProperty->UpdateTitleMode(static_cast<NG::NavigationTitleMode>(mode));
    if (needAddBackButton) {
        // put component inside navigator pattern to trigger back navigation
        auto navigator = FrameNode::CreateFrameNode(V2::NAVIGATOR_ETS_TAG,
            ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<NavigatorPattern>());
        auto hub = navigator->GetEventHub<NavigatorEventHub>();
        CHECK_NULL_VOID(hub);
        hub->SetType(NavigatorType::BACK);
        navigator->MarkModifyDone();

        int32_t backButtonNodeId = ElementRegister::GetInstance()->MakeUniqueId();
        auto backButtonNode =
            FrameNode::CreateFrameNode(V2::BACK_BUTTON_ETS_TAG, backButtonNodeId, AceType::MakeRefPtr<TextPattern>());
        auto textLayoutProperty = backButtonNode->GetLayoutProperty<TextLayoutProperty>();
        CHECK_NULL_VOID(textLayoutProperty);
        textLayoutProperty->UpdateContent(BACK_BUTTON);
        backButtonNode->MountToParent(navigator);

        navBarNode->SetBackButton(navigator);
        navBarNode->UpdateBackButtonNodeOperation(ChildNodeOperation::ADD);
        navBarNode->MarkModifyDone();
        return;
    }
    if (needRemoveBackButton) {
        navBarNode->UpdateBackButtonNodeOperation(ChildNodeOperation::REMOVE);
    }
}

void NavigationView::SetNavBarWidth(const Dimension& value)
{
    ACE_UPDATE_LAYOUT_PROPERTY(NavigationLayoutProperty, NavBarWidth, value);
}

void NavigationView::SetNavigationMode(NavigationMode mode)
{
    ACE_UPDATE_LAYOUT_PROPERTY(NavigationLayoutProperty, NavigationMode, static_cast<NG::NavigationMode>(mode));
}

void NavigationView::SetNavBarPosition(NG::NavBarPosition mode)
{
    ACE_UPDATE_LAYOUT_PROPERTY(NavigationLayoutProperty, NavBarPosition, static_cast<NG::NavBarPosition>(mode));
}

void NavigationView::SetHideNavBar(bool hideNavBar)
{
    ACE_UPDATE_LAYOUT_PROPERTY(NavigationLayoutProperty, HideNavBar, hideNavBar);
}

void NavigationView::SetTitleHeight(const Dimension& height)
{
    ACE_UPDATE_LAYOUT_PROPERTY(NavigationLayoutProperty, TitleBarHeight, height);
}

void NavigationView::SetHideTitleBar(bool hideTitleBar)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    auto navigationGroupNode = AceType::DynamicCast<NavigationGroupNode>(frameNode);
    CHECK_NULL_VOID(navigationGroupNode);
    auto navBarNode = AceType::DynamicCast<NavBarNode>(navigationGroupNode->GetNavBarNode());
    CHECK_NULL_VOID(navBarNode);
    auto navBarLayoutProperty = navBarNode->GetLayoutProperty<NavBarLayoutProperty>();
    CHECK_NULL_VOID(navBarLayoutProperty);
    navBarLayoutProperty->UpdateHideTitleBar(hideTitleBar);
}

void NavigationView::SetHideBackButton(bool hideBackButton)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    auto navigationGroupNode = AceType::DynamicCast<NavigationGroupNode>(frameNode);
    CHECK_NULL_VOID(navigationGroupNode);
    auto navBarNode = AceType::DynamicCast<NavBarNode>(navigationGroupNode->GetNavBarNode());
    CHECK_NULL_VOID(navBarNode);
    auto titleBarNode = AceType::DynamicCast<NavBarNode>(navBarNode->GetTitleBarNode());
    CHECK_NULL_VOID(titleBarNode);
    auto titleBarLayoutProperty = titleBarNode->GetLayoutProperty<TitleBarLayoutProperty>();
    CHECK_NULL_VOID(titleBarLayoutProperty);
    titleBarLayoutProperty->UpdateHideBackButton(hideBackButton);
}

void NavigationView::SetHideToolBar(bool hideToolBar)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    auto navigationGroupNode = AceType::DynamicCast<NavigationGroupNode>(frameNode);
    CHECK_NULL_VOID(navigationGroupNode);
    auto navBarNode = AceType::DynamicCast<NavBarNode>(navigationGroupNode->GetNavBarNode());
    CHECK_NULL_VOID(navBarNode);
    auto navBarLayoutProperty = navBarNode->GetLayoutProperty<NavBarLayoutProperty>();
    CHECK_NULL_VOID(navBarLayoutProperty);
    navBarLayoutProperty->UpdateHideToolBar(hideToolBar);
}

void NavigationView::SetToolBarItems(std::list<BarItem>&& toolBarItems)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    auto navigationGroupNode = AceType::DynamicCast<NavigationGroupNode>(frameNode);
    CHECK_NULL_VOID(navigationGroupNode);
    auto navBarNode = AceType::DynamicCast<NavBarNode>(navigationGroupNode->GetNavBarNode());
    CHECK_NULL_VOID(navBarNode);
    if (navBarNode->GetPrevToolBarIsCustom().value_or(false)) {
        navBarNode->UpdateToolBarNodeOperation(ChildNodeOperation::REPLACE);
    } else {
        if (navBarNode->GetPreToolBarNode() &&
            static_cast<int32_t>(navBarNode->GetPreToolBarNode()->GetChildren().size()) != 0) {
            UpdateOldBarItems(navBarNode->GetPreToolBarNode(), toolBarItems);
            navBarNode->SetToolBarNode(navBarNode->GetPreToolBarNode());
            navBarNode->UpdateToolBarNodeOperation(ChildNodeOperation::NONE);
            navBarNode->MarkModifyDone();
            return;
        }
        navBarNode->UpdateToolBarNodeOperation(ChildNodeOperation::REPLACE);
    }
    int32_t toolBarNodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto toolBarNode = FrameNode::GetOrCreateFrameNode(
        V2::TOOL_BAR_ETS_TAG, toolBarNodeId, []() { return AceType::MakeRefPtr<LinearLayoutPattern>(false); });
    auto rowProperty = toolBarNode->GetLayoutProperty<LinearLayoutProperty>();
    CHECK_NULL_VOID(rowProperty);
    rowProperty->UpdateMainAxisAlign(FlexAlign::SPACE_EVENLY);
    for (const auto& toolBarItem : toolBarItems) {
        int32_t barItemNodeId = ElementRegister::GetInstance()->MakeUniqueId();
        auto barItemNode = AceType::MakeRefPtr<BarItemNode>(V2::BAR_ITEM_ETS_TAG, barItemNodeId);
        barItemNode->InitializePatternAndContext();
        UpdateBarItemNodeWithItem(barItemNode, toolBarItem);
        toolBarNode->AddChild(barItemNode);
    }
    navBarNode->SetToolBarNode(toolBarNode);
    navBarNode->UpdatePrevToolBarIsCustom(false);
    navBarNode->MarkModifyDone();
}

void NavigationView::SetCustomToolBar(const RefPtr<UINode>& customToolBar)
{
    CHECK_NULL_VOID(customToolBar);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    auto navigationGroupNode = AceType::DynamicCast<NavigationGroupNode>(frameNode);
    CHECK_NULL_VOID(navigationGroupNode);
    auto navBarNode = AceType::DynamicCast<NavBarNode>(navigationGroupNode->GetNavBarNode());
    CHECK_NULL_VOID(navBarNode);
    auto layoutProperty = navBarNode->GetLayoutProperty<NavigationLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    if (navBarNode->GetPrevToolBarIsCustom().value_or(false)) {
        if (customToolBar->GetId() == navBarNode->GetToolBarNode()->GetId()) {
            navBarNode->UpdateToolBarNodeOperation(ChildNodeOperation::NONE);
            navBarNode->UpdatePrevToolBarIsCustom(true);
            return;
        }
    }
    navBarNode->UpdateToolBarNodeOperation(ChildNodeOperation::REPLACE);
    navBarNode->SetToolBarNode(customToolBar);
    navBarNode->UpdatePrevToolBarIsCustom(true);
    navBarNode->MarkModifyDone();
}

void NavigationView::SetOnTitleModeChange(std::function<void(NavigationTitleMode)>&& onTitleModeChange)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    auto navigationGroupNode = AceType::DynamicCast<NavigationGroupNode>(frameNode);
    CHECK_NULL_VOID(navigationGroupNode);
    auto eventHub = navigationGroupNode->GetEventHub<NavigationEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnTitleModeChange(std::move(onTitleModeChange));
}

void NavigationView::SetOnNavBarStateChange(std::function<void(bool)>&& onNavBarStateChange)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    auto navigationEventHub = AceType::DynamicCast<NavigationEventHub>(frameNode->GetEventHub<EventHub>());
    CHECK_NULL_VOID(navigationEventHub);
    navigationEventHub->SetOnNavBarStateChange(std::move(onNavBarStateChange));
}

void NavigationView::SetBackButtonIcon(const std::string& src, bool noPixMap, RefPtr<PixelMap>& pixMap)
{
    ImageSourceInfo imageSourceInfo(src);
    ACE_UPDATE_LAYOUT_PROPERTY(NavigationLayoutProperty, NoPixMap, noPixMap);
    ACE_UPDATE_LAYOUT_PROPERTY(NavigationLayoutProperty, ImageSource, imageSourceInfo);
    ACE_UPDATE_LAYOUT_PROPERTY(NavigationLayoutProperty, PixelMap, pixMap);
}

} // namespace OHOS::Ace::NG