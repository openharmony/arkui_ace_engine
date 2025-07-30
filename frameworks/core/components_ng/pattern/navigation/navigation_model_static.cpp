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

#include "core/components_ng/pattern/navigation/navigation_model_static.h"

#include "base/i18n/localization.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/divider/divider_layout_property.h"
#include "core/components_ng/pattern/divider/divider_pattern.h"
#include "core/components_ng/pattern/divider/divider_render_property.h"
#include "core/components_ng/pattern/image/image_layout_property.h"
#include "core/components_ng/pattern/image/image_pattern.h"
#include "core/components_ng/pattern/navigation/bar_item_node.h"
#include "core/components_ng/pattern/navigation/bar_item_pattern.h"
#include "core/components_ng/pattern/navigation/nav_bar_layout_property.h"
#include "core/components_ng/pattern/navigation/nav_bar_pattern.h"
#include "core/components_ng/pattern/navigation/navigation_content_pattern.h"
#include "core/components_ng/pattern/navigation/navigation_pattern.h"
#include "core/components_ng/pattern/navigation/navigation_title_util.h"
#include "core/components_ng/pattern/navigation/navigation_toolbar_util.h"
#include "core/components_ng/pattern/navigation/title_bar_node.h"
#include "core/components_ng/pattern/navigation/title_bar_pattern.h"
#include "core/components_ng/pattern/navigation/tool_bar_node.h"
#include "core/components_ng/pattern/navigation/tool_bar_pattern.h"
#include "core/components_ng/pattern/text/text_pattern.h"
#include "frameworks/bridge/common/utils/engine_helper.h"

namespace OHOS::Ace::NG {
namespace {
RefPtr<FrameNode> CreateBarItemTextNode(const std::string& text)
{
    int32_t nodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto textNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, nodeId, AceType::MakeRefPtr<TextPattern>());
    CHECK_NULL_RETURN(textNode, nullptr);
    auto textLayoutProperty = textNode->GetLayoutProperty<TextLayoutProperty>();
    CHECK_NULL_RETURN(textLayoutProperty, nullptr);
    textLayoutProperty->UpdateContent(text);
    textLayoutProperty->UpdateFontSize(TEXT_FONT_SIZE);
    textLayoutProperty->UpdateTextColor(TEXT_COLOR);
    textLayoutProperty->UpdateTextAlign(TextAlign::CENTER);
    return textNode;
}

RefPtr<FrameNode> CreateBarItemIconNode(const std::string& src)
{
    int32_t nodeId = ElementRegister::GetInstance()->MakeUniqueId();
    ImageSourceInfo info(src);
    auto iconNode = FrameNode::CreateFrameNode(V2::IMAGE_ETS_TAG, nodeId, AceType::MakeRefPtr<ImagePattern>());
    CHECK_NULL_RETURN(iconNode, nullptr);
    auto imageLayoutProperty = iconNode->GetLayoutProperty<ImageLayoutProperty>();
    CHECK_NULL_RETURN(imageLayoutProperty, nullptr);
    auto theme = NavigationGetTheme();
    CHECK_NULL_RETURN(theme, nullptr);

    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    auto navigationGroupNode = AceType::DynamicCast<NavigationGroupNode>(frameNode);
    CHECK_NULL_RETURN(navigationGroupNode, nullptr);
    auto hub = navigationGroupNode->GetEventHub<EventHub>();
    CHECK_NULL_RETURN(hub, nullptr);
    if (!hub->IsEnabled()) {
        info.SetFillColor(theme->GetMenuIconColor().BlendOpacity(theme->GetAlphaDisabled()));
    } else {
        info.SetFillColor(theme->GetMenuIconColor());
    }
    imageLayoutProperty->UpdateImageSourceInfo(info);

    auto iconSize = theme->GetMenuIconSize();
    imageLayoutProperty->UpdateUserDefinedIdealSize(CalcSize(CalcLength(iconSize), CalcLength(iconSize)));
    iconNode->MarkModifyDone();
    return iconNode;
}
void UpdateBarItemNodeWithItem(const RefPtr<BarItemNode>& barItemNode, const BarItem& barItem)
{
    if (barItem.text.has_value() && !barItem.text.value().empty() && !barItemNode->IsHideText()) {
        auto textNode = CreateBarItemTextNode(barItem.text.value());
        CHECK_NULL_VOID(textNode);
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
void UpdateOldBarItems(const RefPtr<UINode>& oldBarContainer, const std::vector<BarItem>& newBarItems)
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
            oldBarContainer->RemoveChild(oldBarItems.back());
            oldBarItems.pop_back();
        }
    } else if (prevChildrenSize < newChildrenSize) {
        // if m < n, we add (n - m) children created by info in new item list
        for (int32_t i = 0; i < newChildrenSize - prevChildrenSize; i++) {
            auto nodeId = ElementRegister::GetInstance()->MakeUniqueId();
            auto barItemNode = BarItemNode::GetOrCreateBarItemNode(
                V2::BAR_ITEM_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<BarItemPattern>(); });
            UpdateBarItemNodeWithItem(barItemNode, *newIter);
            oldBarContainer->AddChild(barItemNode);
            newIter++;
        }
    }
    auto container = AceType::DynamicCast<TitleBarNode>(oldBarContainer);
    CHECK_NULL_VOID(container);
    container->MarkModifyDone();
}

void SetNeedResetTitleProperty(const RefPtr<FrameNode>& titleBarNode)
{
    CHECK_NULL_VOID(titleBarNode);
    auto titleBarPattern = titleBarNode->GetPattern<TitleBarPattern>();
    CHECK_NULL_VOID(titleBarPattern);
    titleBarPattern->SetNeedResetMainTitleProperty(true);
    titleBarPattern->SetNeedResetSubTitleProperty(true);
}

void CreateImageBackIcon(const RefPtr<FrameNode>& backButtonNode, NavigationGroupNode* navigationGroupNode)
{
    auto theme = NavigationGetTheme();
    CHECK_NULL_VOID(theme);
    auto backButtonImageNode = FrameNode::CreateFrameNode(V2::BACK_BUTTON_IMAGE_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<ImagePattern>());
    CHECK_NULL_VOID(backButtonImageNode);

    auto backButtonImageLayoutProperty = backButtonImageNode->GetLayoutProperty<ImageLayoutProperty>();
    CHECK_NULL_VOID(backButtonImageLayoutProperty);

    ImageSourceInfo imageSourceInfo;
    auto iconColor = theme->GetBackButtonIconColor();
    auto backReourceId = theme->GetBackResourceId();

    imageSourceInfo.SetResourceId(backReourceId);
    auto navigationEventHub = navigationGroupNode->GetEventHub<EventHub>();
    CHECK_NULL_VOID(navigationEventHub);
    if (!navigationEventHub->IsEnabled()) {
        imageSourceInfo.SetFillColor(iconColor.BlendOpacity(theme->GetAlphaDisabled()));
    } else {
        imageSourceInfo.SetFillColor(iconColor);
    }
    backButtonImageLayoutProperty->UpdateImageSourceInfo(imageSourceInfo);
    backButtonImageLayoutProperty->UpdateMeasureType(MeasureType::MATCH_PARENT);

    backButtonImageNode->MountToParent(backButtonNode);
    backButtonImageNode->MarkModifyDone();
}

void CreateSymbolBackIcon(const RefPtr<FrameNode>& backButtonNode, NavigationGroupNode* navigationGroupNode)
{
    auto theme = NavigationGetTheme();
    CHECK_NULL_VOID(theme);
    auto symbolNode = FrameNode::GetOrCreateFrameNode(V2::SYMBOL_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TextPattern>(); });
    CHECK_NULL_VOID(symbolNode);
    auto symbolProperty = symbolNode->GetLayoutProperty<TextLayoutProperty>();
    CHECK_NULL_VOID(symbolProperty);
    symbolProperty->UpdateSymbolSourceInfo(SymbolSourceInfo(theme->GetBackSymbolId()));
    auto navigationEventHub = navigationGroupNode->GetEventHub<EventHub>();
    CHECK_NULL_VOID(navigationEventHub);
    if (!navigationEventHub->IsEnabled()) {
        symbolProperty->UpdateSymbolColorList(
            { theme->GetBackButtonIconColor().BlendOpacity(theme->GetAlphaDisabled()) });
    } else {
        symbolProperty->UpdateSymbolColorList({ theme->GetBackButtonIconColor() });
    }
    symbolNode->MountToParent(backButtonNode);
    symbolNode->MarkModifyDone();
}
} // namespace
bool NavigationModelStatic::navBarWidthDoubleBind_ = false;

RefPtr<FrameNode> NavigationModelStatic::CreateFrameNode(int32_t nodeId)
{
    auto navigationGroupNode = NavigationRegister::GetInstance()->GetOrCreateGroupNode(
        V2::NAVIGATION_VIEW_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<NavigationPattern>(); });
    // navBar node
    if (!navigationGroupNode->GetNavBarNode()) {
        int32_t navBarNodeId = ElementRegister::GetInstance()->MakeUniqueId();
        auto navBarNode = NavBarNode::GetOrCreateNavBarNode(
            V2::NAVBAR_ETS_TAG, navBarNodeId, []() { return AceType::MakeRefPtr<NavBarPattern>(); });
        auto navBarRenderContext = navBarNode->GetRenderContext();
        CHECK_NULL_RETURN(navBarRenderContext, nullptr);
        navBarRenderContext->UpdateClipEdge(true);
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
        if (!navBarNode->GetContentNode()) {
            int32_t navBarContentNodeId = ElementRegister::GetInstance()->MakeUniqueId();
            auto navBarContentNode = FrameNode::GetOrCreateFrameNode(V2::NAVBAR_CONTENT_ETS_TAG, navBarContentNodeId,
                []() { return AceType::MakeRefPtr<LinearLayoutPattern>(true); });
            auto navBarContentRenderContext = navBarContentNode->GetRenderContext();
            CHECK_NULL_RETURN(navBarContentRenderContext, nullptr);
            navBarContentRenderContext->UpdateClipEdge(true);
            navBarNode->AddChild(navBarContentNode);
            navBarNode->SetContentNode(navBarContentNode);
        }

        // toolBar node
        if (!navBarNode->GetToolBarNode()) {
            int32_t toolBarNodeId = ElementRegister::GetInstance()->MakeUniqueId();
            auto toolBarNode = NavToolbarNode::GetOrCreateToolbarNode(
                V2::TOOL_BAR_ETS_TAG, toolBarNodeId, []() { return AceType::MakeRefPtr<NavToolbarPattern>(); });
            navBarNode->AddChild(toolBarNode);
            navBarNode->SetToolBarNode(toolBarNode);
            navBarNode->SetPreToolBarNode(toolBarNode);
            navBarNode->UpdatePrevToolBarIsCustom(false);
        }
        auto navBarLayoutProperty = navBarNode->GetLayoutProperty<NavBarLayoutProperty>();
        CHECK_NULL_RETURN(navBarLayoutProperty, nullptr);
        navBarLayoutProperty->UpdateTitleMode(NavigationTitleMode::FREE);
    }

    // content node
    if (!navigationGroupNode->GetContentNode()) {
        int32_t contentNodeId = ElementRegister::GetInstance()->MakeUniqueId();
        auto contentNode = FrameNode::GetOrCreateFrameNode(V2::NAVIGATION_CONTENT_ETS_TAG, contentNodeId,
            []() { return AceType::MakeRefPtr<NavigationContentPattern>(); });
        contentNode->GetLayoutProperty()->UpdateAlignment(Alignment::TOP_LEFT);
        contentNode->GetEventHub<EventHub>()->GetOrCreateGestureEventHub()->SetHitTestMode(
            HitTestMode::HTMTRANSPARENT_SELF);
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

        auto dividerLayoutProperty = dividerNode->GetLayoutProperty<DividerLayoutProperty>();
        CHECK_NULL_RETURN(dividerLayoutProperty, nullptr);
        dividerLayoutProperty->UpdateStrokeWidth(DIVIDER_WIDTH);
        dividerLayoutProperty->UpdateVertical(true);
        auto dividerRenderProperty = dividerNode->GetPaintProperty<DividerRenderProperty>();
        CHECK_NULL_RETURN(dividerRenderProperty, nullptr);
    }
    auto navigationLayoutProperty = navigationGroupNode->GetLayoutProperty<NavigationLayoutProperty>();
    if (!navigationLayoutProperty->HasNavigationMode()) {
        navigationLayoutProperty->UpdateNavigationMode(NavigationMode::AUTO);
    }

    auto navigationPattern = navigationGroupNode->GetPattern<NavigationPattern>();
    if (navigationPattern && !navigationPattern->GetUserSetNavBarWidthFlag()) {
        navigationLayoutProperty->UpdateNavBarWidth(DEFAULT_NAV_BAR_WIDTH);
    }
    auto navigationStack = navigationPattern->GetNavigationStack();
    if (!navigationStack) {
        auto navigationStack = AceType::MakeRefPtr<NavigationStack>();
        navigationPattern->SetNavigationStack(std::move(navigationStack));
    }

    return navigationGroupNode;
}

void NavigationModelStatic::SetNavBarWidth(FrameNode* frameNode, const Dimension& value)
{
    CHECK_NULL_VOID(frameNode);
    auto navBarWidth = value.IsNonPositive() ? DEFAULT_NAV_BAR_WIDTH : value;
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(NavigationLayoutProperty, NavBarWidth, navBarWidth, frameNode);
    auto navigationGroupNode = AceType::DynamicCast<NavigationGroupNode>(frameNode);
    CHECK_NULL_VOID(navigationGroupNode);
    auto navigationPattern = navigationGroupNode->GetPattern<NavigationPattern>();
    CHECK_NULL_VOID(navigationPattern);
    if (navBarWidthDoubleBind_ && navigationPattern->GetIsInDividerDrag()) {
        return;
    }
    navigationPattern->SetUserSetNavBarWidthFlag(true);
    if (navigationPattern->GetInitNavBarWidth() != navBarWidth) {
        navigationPattern->SetInitNavBarWidth(navBarWidth);
    }
}

void NavigationModelStatic::SetMinNavBarWidth(FrameNode* frameNode, const Dimension& value)
{
    CHECK_NULL_VOID(frameNode);
    auto navigationGroupNode = AceType::DynamicCast<NavigationGroupNode>(frameNode);
    CHECK_NULL_VOID(navigationGroupNode);
    auto navigationPattern = navigationGroupNode->GetPattern<NavigationPattern>();
    CHECK_NULL_VOID(navigationPattern);
    if (navBarWidthDoubleBind_ && navigationPattern->GetIsInDividerDrag()) {
        return;
    }
    navigationPattern->SetIfNeedInit(true);
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(NavigationLayoutProperty, MinNavBarWidth, value, frameNode);
}

void NavigationModelStatic::SetMaxNavBarWidth(FrameNode* frameNode, const Dimension& value)
{
    CHECK_NULL_VOID(frameNode);
    auto navigationGroupNode = AceType::DynamicCast<NavigationGroupNode>(frameNode);
    CHECK_NULL_VOID(navigationGroupNode);
    auto navigationPattern = navigationGroupNode->GetPattern<NavigationPattern>();
    CHECK_NULL_VOID(navigationPattern);
    if (navBarWidthDoubleBind_ && navigationPattern->GetIsInDividerDrag()) {
        return;
    }
    navigationPattern->SetIfNeedInit(true);
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(NavigationLayoutProperty, MaxNavBarWidth, value, frameNode);
}

void NavigationModelStatic::SetNavBarPosition(FrameNode* frameNode, const std::optional<NG::NavBarPosition>& mode)
{
    CHECK_NULL_VOID(frameNode);
    if (mode) {
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(NavigationLayoutProperty, NavBarPosition, mode.value(), frameNode);
    } else {
        ACE_RESET_NODE_LAYOUT_PROPERTY(NavigationLayoutProperty, NavBarPosition, frameNode);
    }
}

void NavigationModelStatic::SetMinContentWidth(FrameNode* frameNode, const Dimension& value)
{
    CHECK_NULL_VOID(frameNode);
    auto minContentWidth = value.IsNonPositive() ? DEFAULT_MIN_CONTENT_WIDTH : value;
    auto navigationGroupNode = AceType::DynamicCast<NavigationGroupNode>(frameNode);
    CHECK_NULL_VOID(navigationGroupNode);
    auto navigationPattern = navigationGroupNode->GetPattern<NavigationPattern>();
    CHECK_NULL_VOID(navigationPattern);
    navigationPattern->SetIfNeedInit(true);
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(NavigationLayoutProperty, MinContentWidth, minContentWidth, frameNode);
}

void NavigationModelStatic::SetSystemBarStyle(FrameNode* frameNode, const Color& contentColor)
{
    CHECK_NULL_VOID(frameNode);
    auto navigationGroupNode = AceType::DynamicCast<NavigationGroupNode>(frameNode);
    CHECK_NULL_VOID(navigationGroupNode);
    auto pattern = navigationGroupNode->GetPattern<NavigationPattern>();
    CHECK_NULL_VOID(pattern);
    RefPtr<SystemBarStyle> style = SystemBarStyle::CreateStyleFromColor(contentColor.GetValue());
    pattern->SetSystemBarStyle(style);
}

void NavigationModelStatic::SetUsrNavigationMode(FrameNode* frameNode, const std::optional<NavigationMode>& mode)
{
    if (mode) {
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(NavigationLayoutProperty, UsrNavigationMode, mode.value(), frameNode);
    } else {
        ACE_RESET_NODE_LAYOUT_PROPERTY(NavigationLayoutProperty, UsrNavigationMode, frameNode);
    }
}

void NavigationModelStatic::SetBackButtonIcon(FrameNode* frameNode,
    const std::function<void(WeakPtr<NG::FrameNode>)>& symbolApply, const std::string& src,
    const ImageOption& imageOption, RefPtr<PixelMap>& pixMap, const std::vector<std::string>& nameList,
    bool userDefinedAccessibilityText, const std::string& backButtonAccessibilityText)
{
    CHECK_NULL_VOID(frameNode);
    auto navigationGroupNode = AceType::DynamicCast<NavigationGroupNode>(frameNode);
    CHECK_NULL_VOID(navigationGroupNode);

    auto navBarNode = AceType::DynamicCast<NavBarNode>(navigationGroupNode->GetNavBarNode());
    CHECK_NULL_VOID(navBarNode);
    auto titleBarNode = AceType::DynamicCast<TitleBarNode>(navBarNode->GetTitleBarNode());
    CHECK_NULL_VOID(titleBarNode);
    auto titleBarLayoutProperty = titleBarNode->GetLayoutProperty<TitleBarLayoutProperty>();
    CHECK_NULL_VOID(titleBarLayoutProperty);
    ImageSourceInfo imageSourceInfo(src, nameList[0], nameList[1]);
    titleBarLayoutProperty->UpdateImageSource(imageSourceInfo);
    titleBarLayoutProperty->UpdateNoPixMap(imageOption.noPixMap);
    titleBarLayoutProperty->UpdatePixelMap(pixMap);
    titleBarLayoutProperty->SetBackIconSymbol(symbolApply);
    titleBarLayoutProperty->UpdateIsValidImage(imageOption.isValidImage);
    auto backButtonNode = AceType::DynamicCast<FrameNode>(titleBarNode->GetBackButton());
    CHECK_NULL_VOID(backButtonNode);
    if (userDefinedAccessibilityText) {
        NavigationTitleUtil::SetAccessibility(backButtonNode, backButtonAccessibilityText);
    } else {
        std::string message = Localization::GetInstance()->GetEntryLetters("navigation.back");
        NavigationTitleUtil::SetAccessibility(backButtonNode, message);
    }
}

void NavigationModelStatic::SetHideNavBar(FrameNode* frameNode, bool hideNavBar)
{
    auto navigationGroupNode =
        Referenced::Claim<NavigationGroupNode>(AceType::DynamicCast<NavigationGroupNode>(frameNode));
    CHECK_NULL_VOID(navigationGroupNode);
    auto pattern = navigationGroupNode->GetPattern<NavigationPattern>();
    CHECK_NULL_VOID(pattern);
    auto navigationLayoutProperty = navigationGroupNode->GetLayoutProperty<NavigationLayoutProperty>();
    CHECK_NULL_VOID(navigationLayoutProperty);

    auto lastHideNavBarValue = navigationLayoutProperty->GetHideNavBar();
    if (lastHideNavBarValue.has_value()) {
        pattern->SetNavBarVisibilityChange(hideNavBar != lastHideNavBarValue.value());
    } else {
        pattern->SetNavBarVisibilityChange(true);
    }
    auto navBarNode = AceType::DynamicCast<FrameNode>(navigationGroupNode->GetNavBarNode());
    navBarNode->SetJSViewActive(!hideNavBar);
    if (pattern->GetNavBarVisibilityChange()) {
        navBarNode->MarkDirtyNode();
    }
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(NavigationLayoutProperty, HideNavBar, hideNavBar, navigationGroupNode);
}

void NavigationModelStatic::SetHideTitleBar(FrameNode* frameNode, bool hideTitleBar, bool animated)
{
    CHECK_NULL_VOID(frameNode);
    auto navigationGroupNode = AceType::DynamicCast<NavigationGroupNode>(frameNode);
    CHECK_NULL_VOID(navigationGroupNode);
    auto navBarNode = AceType::DynamicCast<NavBarNode>(navigationGroupNode->GetNavBarNode());
    CHECK_NULL_VOID(navBarNode);
    auto navBarLayoutProperty = navBarNode->GetLayoutProperty<NavBarLayoutProperty>();
    CHECK_NULL_VOID(navBarLayoutProperty);
    navBarLayoutProperty->UpdateHideTitleBar(hideTitleBar);
    navBarLayoutProperty->UpdateIsAnimatedTitleBar(animated);
}

void NavigationModelStatic::SetHideBackButton(FrameNode* frameNode, bool hideBackButton)
{
    CHECK_NULL_VOID(frameNode);
    auto navigationGroupNode = AceType::DynamicCast<NavigationGroupNode>(frameNode);
    CHECK_NULL_VOID(navigationGroupNode);
    auto navBarNode = AceType::DynamicCast<NavBarNode>(navigationGroupNode->GetNavBarNode());
    CHECK_NULL_VOID(navBarNode);
    auto navBarLayoutProperty = navBarNode->GetLayoutProperty<NavBarLayoutProperty>();
    CHECK_NULL_VOID(navBarLayoutProperty);
    if (!navBarLayoutProperty->HasHideBackButton() ||
        (hideBackButton != navBarLayoutProperty->GetHideBackButtonValue())) {
        SetNeedResetTitleProperty(AceType::DynamicCast<FrameNode>(navBarNode->GetTitleBarNode()));
    }
    navBarLayoutProperty->UpdateHideBackButton(hideBackButton);
}

void NavigationModelStatic::SetTitleMode(FrameNode* frameNode, NG::NavigationTitleMode mode)
{
    CHECK_NULL_VOID(frameNode);
    auto navigationGroupNode = AceType::DynamicCast<NavigationGroupNode>(frameNode);
    CHECK_NULL_VOID(navigationGroupNode);
    auto navBarNode = AceType::DynamicCast<NavBarNode>(navigationGroupNode->GetNavBarNode());
    CHECK_NULL_VOID(navBarNode);
    auto navBarLayoutProperty = navBarNode->GetLayoutProperty<NavBarLayoutProperty>();
    CHECK_NULL_VOID(navBarLayoutProperty);
    auto titleBarNode = AceType::DynamicCast<TitleBarNode>(navBarNode->GetTitleBarNode());
    CHECK_NULL_VOID(titleBarNode);
    auto titleBarLayoutProperty = titleBarNode->GetLayoutProperty<TitleBarLayoutProperty>();
    CHECK_NULL_VOID(titleBarLayoutProperty);
    const auto& titleHeightProperty = titleBarLayoutProperty->GetTitleHeight();
    if (titleHeightProperty.has_value()) {
        mode = NavigationTitleMode::MINI;
    }
    if (!navBarLayoutProperty->HasTitleMode() || navBarLayoutProperty->GetTitleModeValue() != mode) {
        SetNeedResetTitleProperty(titleBarNode);
    }
    navBarLayoutProperty->UpdateTitleMode(static_cast<NG::NavigationTitleMode>(mode));
    auto backButtonNode = AceType::DynamicCast<FrameNode>(titleBarNode->GetBackButton());
    if (mode != NavigationTitleMode::MINI) {
        // remove back button if any.
        titleBarNode->RemoveChild(backButtonNode);
        titleBarNode->SetBackButton(nullptr);
        return;
    }

    if (backButtonNode != nullptr) {
        return;
    }
    // create back button
    bool result = CreateBackButtonNode(backButtonNode);
    CHECK_NULL_VOID(result);

    if (Container::GreatOrEqualAPIVersion(PlatformVersion::VERSION_TWELVE) && SystemProperties::IsNeedSymbol()) {
        CreateSymbolBackIcon(backButtonNode, navigationGroupNode);
    } else {
        CreateImageBackIcon(backButtonNode, navigationGroupNode);
    }

    // read navigation back button
    std::string message = Localization::GetInstance()->GetEntryLetters("navigation.back");
    NavigationTitleUtil::SetAccessibility(backButtonNode, message);

    backButtonNode->MarkModifyDone();
    titleBarNode->SetBackButton(backButtonNode);
    titleBarNode->AddChild(backButtonNode, 0);
}

void NavigationModelStatic::SetMenuItems(FrameNode* frameNode, std::vector<NG::BarItem>&& menuItems)
{
    auto navigationGroupNode = AceType::DynamicCast<NavigationGroupNode>(frameNode);
    CHECK_NULL_VOID(navigationGroupNode);
    auto navBarNode = AceType::DynamicCast<NavBarNode>(navigationGroupNode->GetNavBarNode());
    CHECK_NULL_VOID(navBarNode);
    // if previous menu is custom, just remove it and create new menu, otherwise update old menu
    if (navBarNode->GetPrevMenuIsCustom().value_or(false)) {
        navBarNode->UpdateMenuNodeOperation(ChildNodeOperation::REPLACE);
    } else {
        if (navBarNode->GetMenu()) {
            navBarNode->UpdateMenuNodeOperation(ChildNodeOperation::REPLACE);
        } else {
            navBarNode->UpdateMenuNodeOperation(ChildNodeOperation::ADD);
        }
    }
    auto navBarPattern = navBarNode->GetPattern<NavBarPattern>();
    CHECK_NULL_VOID(navBarPattern);
    navBarPattern->SetTitleBarMenuItems(menuItems);
    navBarPattern->SetMenuNodeId(ElementRegister::GetInstance()->MakeUniqueId());
    navBarPattern->SetLandscapeMenuNodeId(ElementRegister::GetInstance()->MakeUniqueId());
    navBarNode->UpdatePrevMenuIsCustom(false);
}

void NavigationModelStatic::SetMenuOptions(FrameNode* frameNode, NG::NavigationMenuOptions&& opt)
{
    CHECK_NULL_VOID(frameNode);
    auto navigationGroupNode = AceType::DynamicCast<NavigationGroupNode>(frameNode);
    CHECK_NULL_VOID(navigationGroupNode);
    auto navBarNode = AceType::DynamicCast<NavBarNode>(navigationGroupNode->GetNavBarNode());
    CHECK_NULL_VOID(navBarNode);
    auto navBarPattern = navBarNode->GetPattern<NavBarPattern>();
    CHECK_NULL_VOID(navBarPattern);
    // navBarPattern->SetMenuOptions(std::move(opt));
}

void NavigationModelStatic::SetHideToolBar(FrameNode* frameNode, bool hideToolBar, bool animated)
{
    CHECK_NULL_VOID(frameNode);
    auto navigationGroupNode = AceType::DynamicCast<NavigationGroupNode>(frameNode);
    CHECK_NULL_VOID(navigationGroupNode);
    auto navBarNode = AceType::DynamicCast<NavBarNode>(navigationGroupNode->GetNavBarNode());
    CHECK_NULL_VOID(navBarNode);
    auto navBarLayoutProperty = navBarNode->GetLayoutProperty<NavBarLayoutProperty>();
    CHECK_NULL_VOID(navBarLayoutProperty);
    navBarLayoutProperty->UpdateHideToolBar(hideToolBar);
    navBarLayoutProperty->UpdateIsAnimatedToolBar(animated);
}

void NavigationModelStatic::SetTitlebarOptions(FrameNode* frameNode, NavigationTitlebarOptions&& opt)
{
    auto navigationGroupNode = AceType::DynamicCast<NavigationGroupNode>(frameNode);
    CHECK_NULL_VOID(navigationGroupNode);
    auto navBarNode = AceType::DynamicCast<NavBarNode>(navigationGroupNode->GetNavBarNode());
    CHECK_NULL_VOID(navBarNode);
    auto navBarPattern = navBarNode->GetPattern<NavBarPattern>();
    CHECK_NULL_VOID(navBarPattern);
    navBarPattern->SetTitleBarStyle(opt.brOptions.barStyle);
    auto titleBarNode = AceType::DynamicCast<TitleBarNode>(navBarNode->GetTitleBarNode());
    CHECK_NULL_VOID(titleBarNode);
    auto titleBarPattern = titleBarNode->GetPattern<TitleBarPattern>();
    CHECK_NULL_VOID(titleBarPattern);
    // titleBarPattern->SetTitlebarOptions(std::move(opt));
}

void NavigationModelStatic::SetToolBarItems(FrameNode* frameNode, std::vector<NG::BarItem>&& toolBarItems)
{
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
            return;
        }
        navBarNode->UpdateToolBarNodeOperation(ChildNodeOperation::REPLACE);
    }
    auto toolBarNode = AceType::DynamicCast<NavToolbarNode>(navBarNode->GetPreToolBarNode());
    CHECK_NULL_VOID(toolBarNode);
    auto rowProperty = toolBarNode->GetLayoutProperty<LinearLayoutProperty>();
    CHECK_NULL_VOID(rowProperty);
    rowProperty->UpdateMainAxisAlign(FlexAlign::SPACE_EVENLY);
    for (const auto& toolBarItem : toolBarItems) {
        int32_t barItemNodeId = ElementRegister::GetInstance()->MakeUniqueId();
        auto barItemNode = BarItemNode::GetOrCreateBarItemNode(
            V2::BAR_ITEM_ETS_TAG, barItemNodeId, []() { return AceType::MakeRefPtr<BarItemPattern>(); });
        barItemNode->SetIsHideItemText(toolBarNode->IsHideItemText());
        UpdateBarItemNodeWithItem(barItemNode, toolBarItem);
        toolBarNode->AddChild(barItemNode);
    }
    bool hasValidContent = !toolBarNode->GetChildren().empty();
    toolBarNode->SetHasValidContent(hasValidContent);
    rowProperty->UpdateVisibility(hasValidContent ? VisibleType::VISIBLE : VisibleType::GONE);
    navBarNode->SetToolBarNode(toolBarNode);
    navBarNode->SetPreToolBarNode(toolBarNode);
    navBarNode->UpdatePrevToolBarIsCustom(false);
}

void NavigationModelStatic::SetToolbarConfiguration(FrameNode* frameNode, std::vector<NG::BarItem>&& toolBarItems)
{
    auto navigationGroupNode = AceType::DynamicCast<NavigationGroupNode>(frameNode);
    CHECK_NULL_VOID(navigationGroupNode);
    auto navBarNode = AceType::DynamicCast<NavBarNode>(navigationGroupNode->GetNavBarNode());
    bool enabled = false;
    auto hub = navigationGroupNode->GetEventHub<EventHub>();
    if (hub) {
        enabled = hub->IsEnabled();
    }
    FieldProperty fieldProperty;
    fieldProperty.parentId = navigationGroupNode->GetInspectorId().value_or("");
    fieldProperty.field = NG::NAV_FIELD;
    NavigationToolbarUtil::SetToolbarConfiguration(navBarNode, std::move(toolBarItems), enabled, fieldProperty);
}

void NavigationModelStatic::SetToolbarMorebuttonOptions(FrameNode* frameNode, MoreButtonOptions&& opt)
{
    auto navigationGroupNode = AceType::DynamicCast<NavigationGroupNode>(frameNode);
    CHECK_NULL_VOID(navigationGroupNode);
    auto navBarNode = AceType::DynamicCast<NavBarNode>(navigationGroupNode->GetNavBarNode());
    CHECK_NULL_VOID(navBarNode);
    NavigationToolbarUtil::SetToolbarMoreButtonOptions(navBarNode, std::move(opt));
}

void NavigationModelStatic::SetToolbarOptions(FrameNode* frameNode, NavigationToolbarOptions&& opt)
{
    auto navigationGroupNode = AceType::DynamicCast<NavigationGroupNode>(frameNode);
    CHECK_NULL_VOID(navigationGroupNode);
    auto navBarNode = AceType::DynamicCast<NavBarNode>(navigationGroupNode->GetNavBarNode());
    NavigationToolbarUtil::SetToolbarOptions(navBarNode, std::move(opt));
}

void NavigationModelStatic::ParseCommonTitle(
    FrameNode* frameNode, const NG::NavigationTitleInfo& titleInfo, bool ignoreMainTitle)
{
    if (!titleInfo.hasSubTitle && !titleInfo.hasMainTitle) {
        return;
    }
    auto navigationGroupNode = AceType::DynamicCast<NavigationGroupNode>(frameNode);
    CHECK_NULL_VOID(navigationGroupNode);
    auto navBarNode = AceType::DynamicCast<NavBarNode>(navigationGroupNode->GetNavBarNode());
    CHECK_NULL_VOID(navBarNode);
    auto titleBarNode = AceType::DynamicCast<TitleBarNode>(navBarNode->GetTitleBarNode());
    CHECK_NULL_VOID(titleBarNode);
    auto titleBarPattern = titleBarNode->GetPattern<TitleBarPattern>();
    CHECK_NULL_VOID(titleBarPattern);
    titleBarPattern->SetIsTitleChanged(true);
    if (navBarNode->GetPrevTitleIsCustomValue(false)) {
        titleBarNode->RemoveChild(titleBarNode->GetTitle());
        titleBarNode->SetTitle(nullptr);
        auto titleBarLayoutProperty = titleBarNode->GetLayoutProperty<TitleBarLayoutProperty>();
        CHECK_NULL_VOID(titleBarLayoutProperty);
        if (titleBarLayoutProperty->HasTitleHeight()) {
            titleBarLayoutProperty->ResetTitleHeight();
            navBarNode->GetLayoutProperty<NavBarLayoutProperty>()->ResetTitleMode();
        }
    }
    navBarNode->UpdatePrevTitleIsCustom(false);
    if (titleBarPattern->IsFirstTimeSetSystemTitle()) {
        titleBarPattern->SetIsFirstTimeSetSystemTitle(false);
        titleBarPattern->MarkIsInitialTitle(true);
    }

    // create or update main title
    NavigationTitleUtil::CreateOrUpdateMainTitle(titleBarNode, titleInfo, ignoreMainTitle);

    // create or update subtitle
    NavigationTitleUtil::CreateOrUpdateSubtitle(titleBarNode, titleInfo);
    return;
}

void NavigationModelStatic::SetIgnoreLayoutSafeArea(FrameNode* frameNode, const SafeAreaExpandOpts& opts)
{
    auto navigationGroupNode = AceType::DynamicCast<NavigationGroupNode>(frameNode);
    CHECK_NULL_VOID(navigationGroupNode);
    auto navBarNode = AceType::DynamicCast<NavBarNode>(navigationGroupNode->GetNavBarNode());
    CHECK_NULL_VOID(navBarNode);
    auto navBarLayoutProperty = navBarNode->GetLayoutProperty<NavBarLayoutProperty>();
    CHECK_NULL_VOID(navBarLayoutProperty);
    // navBarLayoutProperty->UpdateIgnoreLayoutSafeArea(opts);
}

bool NavigationModelStatic::CreateBackButtonNode(RefPtr<FrameNode>& backButtonNode)
{
    auto buttonPattern = AceType::MakeRefPtr<NG::ButtonPattern>();
    CHECK_NULL_RETURN(buttonPattern, false);
    auto theme = NavigationGetTheme();
    CHECK_NULL_RETURN(theme, false);
    buttonPattern->SetSkipColorConfigurationUpdate();
    buttonPattern->setComponentButtonType(ComponentButtonType::NAVIGATION);
    if (Container::GreatOrEqualAPIVersion(PlatformVersion::VERSION_TWELVE)) {
        buttonPattern->SetBlendColor(theme->GetBackgroundPressedColor(), theme->GetBackgroundHoverColor());
        buttonPattern->SetFocusBorderColor(theme->GetBackgroundFocusOutlineColor());
        buttonPattern->SetFocusBorderWidth(theme->GetBackgroundFocusOutlineWeight());
    }
    backButtonNode = FrameNode::CreateFrameNode(
        V2::BACK_BUTTON_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), buttonPattern);
    auto focusHub = backButtonNode->GetOrCreateFocusHub();
    CHECK_NULL_RETURN(focusHub, false);
    focusHub->SetFocusDependence(FocusDependence::SELF);
    auto gestureEventHub = backButtonNode->GetOrCreateGestureEventHub();
    CHECK_NULL_RETURN(gestureEventHub, false);
    auto context = PipelineContext::GetCurrentContextSafelyWithCheck();
    auto clickCallback = [weakContext = WeakPtr<PipelineContext>(context)](GestureEvent& /* info */) {
        auto context = weakContext.Upgrade();
        CHECK_NULL_VOID(context);
        bool result = context->OnBackPressed();
        if (!result) {
            auto delegate = EngineHelper::GetCurrentDelegate();
            CHECK_NULL_VOID(delegate);
            delegate->Back("");
        }
    };
    gestureEventHub->AddClickEvent(AceType::MakeRefPtr<ClickEvent>(clickCallback));
    return UpdateBackButtonProperty(backButtonNode);
}

bool NavigationModelStatic::UpdateBackButtonProperty(const RefPtr<FrameNode>& backButtonNode)
{
    auto backButtonLayoutProperty = backButtonNode->GetLayoutProperty<ButtonLayoutProperty>();
    CHECK_NULL_RETURN(backButtonLayoutProperty, false);
    auto renderContext = backButtonNode->GetRenderContext();
    CHECK_NULL_RETURN(renderContext, false);
    auto backButtonWidth = BACK_BUTTON_SIZE;
    auto backButtonHeight = BACK_BUTTON_SIZE;
    auto backButtonRadiusSize = BUTTON_RADIUS_SIZE;
    auto backButtonPadding = BUTTON_PADDING;
    auto backButtonColor = Color::TRANSPARENT;
    auto theme = NavigationGetTheme();
    CHECK_NULL_RETURN(theme, false);
    if (AceApplicationInfo::GetInstance().GreatOrEqualTargetAPIVersion(PlatformVersion::VERSION_TWELVE)) {
        backButtonWidth = theme->GetIconBackgroundWidth();
        backButtonHeight = theme->GetIconBackgroundHeight();
        backButtonRadiusSize = theme->GetCornerRadius();
        backButtonPadding = MENU_BUTTON_PADDING;
        backButtonColor = theme->GetCompBackgroundColor();
    }
    backButtonLayoutProperty->UpdateUserDefinedIdealSize(
        CalcSize(CalcLength(backButtonWidth), CalcLength(backButtonHeight)));
    backButtonLayoutProperty->UpdateBorderRadius(BorderRadiusProperty(backButtonRadiusSize));
    renderContext->UpdateBackgroundColor(backButtonColor);
    PaddingProperty padding;
    padding.SetEdges(CalcLength(backButtonPadding));
    backButtonLayoutProperty->UpdatePadding(padding);
    backButtonLayoutProperty->UpdateType(ButtonType::NORMAL);
    backButtonLayoutProperty->UpdateMeasureType(MeasureType::MATCH_PARENT);
    return true;
}

void NavigationModelStatic::SetCustomMenu(FrameNode* frameNode, const RefPtr<UINode>& customNode)
{
    auto navigationGroupNode = AceType::DynamicCast<NavigationGroupNode>(frameNode);
    CHECK_NULL_VOID(navigationGroupNode);
    auto navBarNode = AceType::DynamicCast<NavBarNode>(navigationGroupNode->GetNavBarNode());
    CHECK_NULL_VOID(navBarNode);
    auto titleBarNode = AceType::DynamicCast<TitleBarNode>(navBarNode->GetTitleBarNode());
    CHECK_NULL_VOID(titleBarNode);
    // if previous menu exists, remove it if their ids are not the same
    // if previous node is not custom, their ids must not be the same
    if (navBarNode->GetMenu()) {
        if (customNode->GetId() == navBarNode->GetMenu()->GetId()) {
            navBarNode->UpdateMenuNodeOperation(ChildNodeOperation::NONE);
            return;
        }
        navBarNode->SetMenu(customNode);
        navBarNode->UpdatePrevMenuIsCustom(true);
        navBarNode->UpdateMenuNodeOperation(ChildNodeOperation::REPLACE);
        navBarNode->MarkDirtyNode();
        navBarNode->MarkModifyDone();
        return;
    }
    navBarNode->SetMenu(customNode);
    navBarNode->UpdatePrevMenuIsCustom(true);
    navBarNode->UpdateMenuNodeOperation(ChildNodeOperation::ADD);
    navBarNode->MarkDirtyNode();
    navBarNode->MarkModifyDone();
}

void NavigationModelStatic::SetIsCustomAnimation(FrameNode* frameNode, bool isCustom)
{
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<NavigationPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetIsCustomAnimation(isCustom);
}
void NavigationModelStatic::SetCustomTransition(FrameNode* frameNode, NavigationTransitionEvent&& customTransition)
{
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<NavigationPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetNavigationTransition(std::move(customTransition));
}

void NavigationModelStatic::SetCustomTitle(FrameNode* frameNode, const RefPtr<UINode>& customNode)
{
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(customNode);
    auto navigationGroupNode = AceType::DynamicCast<NavigationGroupNode>(frameNode);
    CHECK_NULL_VOID(navigationGroupNode);
    auto navBarNode = AceType::DynamicCast<NavBarNode>(navigationGroupNode->GetNavBarNode());
    CHECK_NULL_VOID(navBarNode);
    navBarNode->UpdatePrevTitleIsCustom(true);
    auto titleBarNode = AceType::DynamicCast<TitleBarNode>(navBarNode->GetTitleBarNode());
    CHECK_NULL_VOID(titleBarNode);
    if (!navBarNode->GetPrevTitleIsCustomValue(false)) {
        titleBarNode->RemoveChild(titleBarNode->GetTitle());
        titleBarNode->RemoveChild(titleBarNode->GetSubtitle());
        titleBarNode->SetTitle(nullptr);
        titleBarNode->SetSubtitle(nullptr);
    }
    auto currentTitle = titleBarNode->GetTitle();
    if (currentTitle && customNode->GetId() == currentTitle->GetId()) {
        // do nothing
        return;
    }
    // update custom title
    titleBarNode->RemoveChild(currentTitle);
    titleBarNode->SetTitle(customNode);
    titleBarNode->AddChild(customNode);
    titleBarNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
}

void NavigationModelStatic::SetCustomToolBar(FrameNode* frameNode, const RefPtr<UINode>& customNode)
{
    auto navigationGroupNode = AceType::DynamicCast<NavigationGroupNode>(frameNode);
    CHECK_NULL_VOID(navigationGroupNode);
    auto navBarNode = AceType::DynamicCast<NavBarNode>(navigationGroupNode->GetNavBarNode());
    NavigationToolbarUtil::SetCustomToolBar(navBarNode, customNode);
}

void NavigationModelStatic::SetTitleHeight(FrameNode* frameNode, const Dimension& height, bool isValid)
{
    auto navigationGroupNode = AceType::DynamicCast<NavigationGroupNode>(frameNode);
    CHECK_NULL_VOID(navigationGroupNode);
    auto navBarNode = AceType::DynamicCast<NavBarNode>(navigationGroupNode->GetNavBarNode());
    CHECK_NULL_VOID(navBarNode);
    auto titleBarNode = AceType::DynamicCast<TitleBarNode>(navBarNode->GetTitleBarNode());
    CHECK_NULL_VOID(titleBarNode);
    auto titleBarLayoutProperty = titleBarNode->GetLayoutProperty<TitleBarLayoutProperty>();
    CHECK_NULL_VOID(titleBarLayoutProperty);
    if (!isValid) {
        titleBarLayoutProperty->ResetTitleHeight();
        return;
    }
    titleBarLayoutProperty->UpdateTitleHeight(height);
    auto navBarLayoutProperty = navBarNode->GetLayoutProperty<NavBarLayoutProperty>();
    CHECK_NULL_VOID(navBarLayoutProperty);
    if (!navBarLayoutProperty->HasHideBackButton() || navBarLayoutProperty->GetHideBackButtonValue() != true) {
        auto titleBarPattern = titleBarNode->GetPattern<TitleBarPattern>();
        CHECK_NULL_VOID(titleBarPattern);
        titleBarPattern->SetNeedResetMainTitleProperty(true);
        titleBarPattern->SetNeedResetSubTitleProperty(true);
    }
    navBarLayoutProperty->UpdateHideBackButton(true);
    navBarLayoutProperty->UpdateTitleMode(static_cast<NG::NavigationTitleMode>(NavigationTitleMode::MINI));
}
} // namespace OHOS::Ace::NG