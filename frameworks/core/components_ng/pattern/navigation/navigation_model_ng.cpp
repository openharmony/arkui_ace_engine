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

#include "core/components_ng/pattern/navigation/navigation_model_ng.h"

#include "base/i18n/localization.h"
#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"
#include "base/utils/utils.h"
#include "core/common/ace_application_info.h"
#include "core/common/force_split/force_split_utils.h"
#include "core/common/resource/resource_parse_utils.h"
#include "core/components/common/properties/alignment.h"
#include "core/components/common/properties/color.h"
#include "core/components/common/properties/shadow.h"
#include "core/components/common/properties/shadow_config.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/button/button_layout_property.h"
#include "core/components_ng/pattern/button/button_pattern.h"
#include "core/components_ng/pattern/custom/custom_node.h"
#include "core/components_ng/pattern/divider/divider_layout_property.h"
#include "core/components_ng/pattern/divider/divider_pattern.h"
#include "core/components_ng/pattern/divider/divider_render_property.h"
#include "core/components_ng/pattern/image/image_layout_property.h"
#include "core/components_ng/pattern/image/image_pattern.h"
#include "core/components_ng/pattern/linear_layout/linear_layout_pattern.h"
#include "core/components_ng/pattern/menu/menu_view.h"
#include "core/components_ng/pattern/navigation/bar_item_event_hub.h"
#include "core/components_ng/pattern/navigation/bar_item_node.h"
#include "core/components_ng/pattern/navigation/bar_item_pattern.h"
#include "core/components_ng/pattern/navigation/nav_bar_layout_property.h"
#include "core/components_ng/pattern/navigation/nav_bar_pattern.h"
#include "core/components_ng/pattern/navigation/navdestination_content_pattern.h"
#include "core/components_ng/pattern/navigation/navigation_content_pattern.h"
#include "core/components_ng/pattern/navigation/navigation_declaration.h"
#include "core/components_ng/pattern/navigation/navigation_drag_bar_pattern.h"
#include "core/components_ng/pattern/navigation/navigation_event_hub.h"
#include "core/components_ng/pattern/navigation/navigation_layout_property.h"
#include "core/components_ng/pattern/navigation/navigation_title_util.h"
#include "core/components_ng/pattern/navigation/navigation_pattern.h"
#include "core/components_ng/pattern/navigation/title_bar_node.h"
#include "core/components_ng/pattern/navigation/title_bar_pattern.h"
#include "core/components_ng/pattern/navigation/navigation_toolbar_util.h"
#include "core/components_ng/pattern/navigation/tool_bar_node.h"
#include "core/components_ng/pattern/navigation/tool_bar_pattern.h"
#include "core/components_ng/pattern/navigator/navigator_event_hub.h"
#include "core/components_ng/pattern/navigator/navigator_pattern.h"
#include "core/components_ng/pattern/navrouter/navdestination_group_node.h"
#include "core/components_ng/pattern/navrouter/navdestination_layout_property.h"
#include "core/components_ng/pattern/navrouter/navrouter_group_node.h"
#include "core/components_ng/pattern/select/select_model.h"
#include "core/components_ng/pattern/text/text_pattern.h"
#include "frameworks/base/system_bar/system_bar_style.h"
#include "frameworks/bridge/common/utils/engine_helper.h"

namespace OHOS::Ace::NG {
namespace {
constexpr int32_t DEFAULT_NAV_BAR_WIDTH_VALUE = 240;

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
    if (barItem.text.has_value() && !barItem.text.value().empty()) {
        auto textNode = CreateBarItemTextNode(barItem.text.value());
        CHECK_NULL_VOID(textNode);
        barItemNode->SetTextNode(textNode);
        if (!barItemNode->IsHideText()) {
            barItemNode->AddChild(textNode);
        }
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
} // namespace
bool NavigationModelNG::navBarWidthDoubleBind_ = false;

void NavigationModelNG::Create(bool useHomeDestination)
{
    TAG_LOGD(AceLogTag::ACE_NAVIGATION, "create navigation and %{public}s HomeNavDestination",
        (useHomeDestination ? "use" : "don't use"));
    auto* stack = ViewStackProcessor::GetInstance();
    // navigation node
    int32_t nodeId = stack->ClaimNodeId();
    ACE_LAYOUT_SCOPED_TRACE("Create[%s][self:%d]", V2::NAVIGATION_VIEW_ETS_TAG, nodeId);
    auto navigationGroupNode = NavigationRegister::GetInstance()->GetOrCreateGroupNode(
        V2::NAVIGATION_VIEW_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<NavigationPattern>(); });
    CHECK_NULL_VOID(navigationGroupNode);
    auto useHomeDest = navigationGroupNode->GetUseHomeDestination();
    if (!useHomeDest.has_value()) {
        useHomeDest = useHomeDestination;
        navigationGroupNode->SetUseHomeDestinatoin(useHomeDestination);
    }
    if (!useHomeDest.value() && !CreateNavBarNodeIfNeeded(navigationGroupNode)) { // navBar node
        return;
    }
    if (!CreatePrimaryContentIfNeeded(navigationGroupNode) || // primaryContent node
        !CreateForceSplitPlaceHolderIfNeeded(navigationGroupNode) || // forcesplit placeHolder node
        !CreateContentNodeIfNeeded(navigationGroupNode) || // content node
        !CreateDividerNodeIfNeeded(navigationGroupNode)) { // divider node
        return;
    }

    stack->Push(navigationGroupNode);
    auto navigationLayoutProperty = navigationGroupNode->GetLayoutProperty<NavigationLayoutProperty>();
    if (!navigationLayoutProperty->HasNavigationMode()) {
        navigationLayoutProperty->UpdateNavigationMode(NavigationMode::AUTO);
    }

    auto navigationPattern = navigationGroupNode->GetPattern<NavigationPattern>();
    if (navigationPattern && !navigationPattern->GetUserSetNavBarWidthFlag()) {
        navigationLayoutProperty->UpdateNavBarWidth(DEFAULT_NAV_BAR_WIDTH);
    }
}

bool NavigationModelNG::CreatePrimaryContentIfNeeded(const RefPtr<NavigationGroupNode>& navigationGroupNode)
{
    CHECK_NULL_RETURN(navigationGroupNode, false);
    auto context = navigationGroupNode->GetContext();
    CHECK_NULL_RETURN(context, false);
    auto manager = context->GetNavigationManager();
    CHECK_NULL_RETURN(manager, false);
    if (!manager->IsForceSplitSupported()) {
        return true;
    }
    if (navigationGroupNode->GetPrimaryContentNode()) {
        return true;
    }
    int32_t contentId = ElementRegister::GetInstance()->MakeUniqueId();
    auto contentNode = FrameNode::GetOrCreateFrameNode(
        V2::PRIMARY_CONTENT_NODE_ETS_TAG, contentId, []() { return AceType::MakeRefPtr<NavigationContentPattern>(); });
    contentNode->GetLayoutProperty()->UpdateAlignment(Alignment::TOP_LEFT);
    contentNode->GetEventHub<EventHub>()->GetOrCreateGestureEventHub()->SetHitTestMode(
        HitTestMode::HTMTRANSPARENT_SELF);
    navigationGroupNode->AddChild(contentNode);
    navigationGroupNode->SetPrimaryContentNode(contentNode);
    return true;
}

bool NavigationModelNG::CreateForceSplitPlaceHolderIfNeeded(const RefPtr<NavigationGroupNode>& navigationGroupNode)
{
    CHECK_NULL_RETURN(navigationGroupNode, false);
    auto context = navigationGroupNode->GetContext();
    CHECK_NULL_RETURN(context, false);
    auto manager = context->GetNavigationManager();
    CHECK_NULL_RETURN(manager, false);
    if (!manager->IsForceSplitSupported() || manager->IsPlaceholderDisabled()) {
        return true;
    }
    if (navigationGroupNode->GetForceSplitPlaceHolderNode()) {
        return true;
    }
    auto phNode = ForceSplitUtils::CreatePlaceHolderNode();
    CHECK_NULL_RETURN(phNode, false);
    navigationGroupNode->AddChild(phNode);
    navigationGroupNode->SetForceSplitPlaceHolderNode(phNode);
    return true;
}

bool NavigationModelNG::CreateNavBarNodeIfNeeded(const RefPtr<NavigationGroupNode>& navigationGroupNode)
{
    if (!navigationGroupNode->GetNavBarNode()) {
        int32_t navBarNodeId = ElementRegister::GetInstance()->MakeUniqueId();
        ACE_LAYOUT_SCOPED_TRACE("Create[%s][self:%d]", V2::NAVBAR_ETS_TAG, navBarNodeId);
        auto navBarNode = NavBarNode::GetOrCreateNavBarNode(
            V2::NAVBAR_ETS_TAG, navBarNodeId, []() { return AceType::MakeRefPtr<NavBarPattern>(); });
        navBarNode->SetJSViewActive(true);
        auto navBarRenderContext = navBarNode->GetRenderContext();
        CHECK_NULL_RETURN(navBarRenderContext, false);
        navBarRenderContext->UpdateClipEdge(true);
        navigationGroupNode->AddChild(navBarNode);
        navigationGroupNode->SetNavBarNode(navBarNode);
        auto navBarPattern = navBarNode->GetPattern<NavBarPattern>();
        CHECK_NULL_RETURN(navBarPattern, false);
        navBarPattern->SetNavigationNode(navigationGroupNode);

        if (!CreateNavBarNodeChildsIfNeeded(navBarNode)) {
            return false;
        }

        auto navBarLayoutProperty = navBarNode->GetLayoutProperty<NavBarLayoutProperty>();
        CHECK_NULL_RETURN(navBarLayoutProperty, false);
        navBarLayoutProperty->UpdateTitleMode(NavigationTitleMode::FREE);
    }

    return true;
}

bool NavigationModelNG::CreateNavBarNodeChildsIfNeeded(const RefPtr<NavBarNode>& navBarNode)
{
    // titleBar node
    if (!navBarNode->GetTitleBarNode()) {
        int32_t titleBarNodeId = ElementRegister::GetInstance()->MakeUniqueId();
        ACE_LAYOUT_SCOPED_TRACE("Create[%s][self:%d]", V2::TITLE_BAR_ETS_TAG, titleBarNodeId);
        auto titleBarNode = TitleBarNode::GetOrCreateTitleBarNode(
            V2::TITLE_BAR_ETS_TAG, titleBarNodeId, []() { return AceType::MakeRefPtr<TitleBarPattern>(); });
        navBarNode->AddChild(titleBarNode);
        navBarNode->SetTitleBarNode(titleBarNode);
    }

    // navBar content node
    if (!navBarNode->GetContentNode()) {
        int32_t navBarContentNodeId = ElementRegister::GetInstance()->MakeUniqueId();
        ACE_LAYOUT_SCOPED_TRACE("Create[%s][self:%d]", V2::NAVBAR_CONTENT_ETS_TAG, navBarContentNodeId);
        auto navBarContentNode = FrameNode::GetOrCreateFrameNode(V2::NAVBAR_CONTENT_ETS_TAG, navBarContentNodeId,
            []() { return AceType::MakeRefPtr<NavDestinationContentPattern>(true); });
        auto navBarContentRenderContext = navBarContentNode->GetRenderContext();
        CHECK_NULL_RETURN(navBarContentRenderContext, false);
        navBarContentRenderContext->UpdateClipEdge(true);
        navBarNode->AddChild(navBarContentNode);
        navBarNode->SetContentNode(navBarContentNode);

        if (Container::GreatOrEqualAPIVersion(PlatformVersion::VERSION_ELEVEN)) {
            SafeAreaExpandOpts opts = { .type = SAFE_AREA_TYPE_SYSTEM | SAFE_AREA_TYPE_CUTOUT,
                .edges = SAFE_AREA_EDGE_ALL };
            navBarContentNode->GetLayoutProperty()->UpdateSafeAreaExpandOpts(opts);
        }
    }

    // toolBar node
    if (!navBarNode->GetToolBarNode()) {
        int32_t toolBarNodeId = ElementRegister::GetInstance()->MakeUniqueId();
        ACE_LAYOUT_SCOPED_TRACE("Create[%s][self:%d]", V2::TOOL_BAR_ETS_TAG, toolBarNodeId);
        auto toolBarNode = NavToolbarNode::GetOrCreateToolbarNode(
            V2::TOOL_BAR_ETS_TAG, toolBarNodeId, []() { return AceType::MakeRefPtr<NavToolbarPattern>(); });
        toolBarNode->MarkModifyDone();
        auto property = toolBarNode->GetLayoutProperty();
        CHECK_NULL_RETURN(property, false);
        property->UpdateVisibility(VisibleType::GONE);
        navBarNode->AddChild(toolBarNode);
        navBarNode->SetToolBarNode(toolBarNode);
        navBarNode->SetPreToolBarNode(toolBarNode);
        navBarNode->UpdatePrevToolBarIsCustom(false);
    }

    return true;
}

bool NavigationModelNG::CreateContentNodeIfNeeded(const RefPtr<NavigationGroupNode>& navigationGroupNode)
{
    if (!navigationGroupNode->GetContentNode()) {
        int32_t contentNodeId = ElementRegister::GetInstance()->MakeUniqueId();
        ACE_LAYOUT_SCOPED_TRACE("Create[%s][self:%d]", V2::NAVIGATION_CONTENT_ETS_TAG, contentNodeId);
        auto contentNode = FrameNode::GetOrCreateFrameNode(V2::NAVIGATION_CONTENT_ETS_TAG, contentNodeId,
            []() { return AceType::MakeRefPtr<NavigationContentPattern>(); });
        contentNode->GetLayoutProperty()->UpdateAlignment(Alignment::TOP_LEFT);
        contentNode->GetEventHub<EventHub>()->GetOrCreateGestureEventHub()->SetHitTestMode(
            HitTestMode::HTMTRANSPARENT_SELF);
        navigationGroupNode->AddChild(contentNode);
        navigationGroupNode->SetContentNode(contentNode);
    }

    return true;
}

bool NavigationModelNG::CreateDividerNodeIfNeeded(const RefPtr<NavigationGroupNode>& navigationGroupNode)
{
    if (!navigationGroupNode->GetDividerNode()) {
        int32_t dividerNodeId = ElementRegister::GetInstance()->MakeUniqueId();
        ACE_LAYOUT_SCOPED_TRACE("Create[%s][self:%d]", V2::DIVIDER_ETS_TAG, dividerNodeId);
        auto dividerNode = FrameNode::GetOrCreateFrameNode(
            V2::DIVIDER_ETS_TAG, dividerNodeId, []() { return AceType::MakeRefPtr<DividerPattern>(); });
        navigationGroupNode->AddChild(dividerNode);
        navigationGroupNode->SetDividerNode(dividerNode);

        if (Container::GreatOrEqualAPIVersion(PlatformVersion::VERSION_ELEVEN)) {
            SafeAreaExpandOpts opts = { .type = SAFE_AREA_TYPE_SYSTEM | SAFE_AREA_TYPE_CUTOUT,
                .edges = SAFE_AREA_EDGE_ALL };
            dividerNode->GetLayoutProperty()->UpdateSafeAreaExpandOpts(opts);
        }

        auto dividerLayoutProperty = dividerNode->GetLayoutProperty<DividerLayoutProperty>();
        CHECK_NULL_RETURN(dividerLayoutProperty, false);
        dividerLayoutProperty->UpdateStrokeWidth(DIVIDER_WIDTH);
        dividerLayoutProperty->UpdateVertical(true);
        auto dividerRenderProperty = dividerNode->GetPaintProperty<DividerRenderProperty>();
        CHECK_NULL_RETURN(dividerRenderProperty, false);
        auto theme = NavigationGetTheme();
        CHECK_NULL_RETURN(theme, false);
        dividerRenderProperty->UpdateDividerColor(Color::TRANSPARENT);
        dividerNode->GetRenderContext()->UpdateBackgroundColor(theme->GetNavigationDividerColor());
    }

    return true;
}

bool NavigationModelNG::ParseCommonTitle(
    bool hasSubTitle, bool hasMainTitle, const std::string& subtitle, const std::string& title, bool ignoreMainTitle)
{
    if (!hasSubTitle && !hasMainTitle) {
        return false;
    }
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    auto navigationGroupNode = AceType::DynamicCast<NavigationGroupNode>(frameNode);
    CHECK_NULL_RETURN(navigationGroupNode, false);
    auto navBarNode = AceType::DynamicCast<NavBarNode>(navigationGroupNode->GetNavBarNode());
    CHECK_NULL_RETURN(navBarNode, false);
    auto titleBarNode = AceType::DynamicCast<TitleBarNode>(navBarNode->GetTitleBarNode());
    CHECK_NULL_RETURN(titleBarNode, false);
    auto titleBarPattern = titleBarNode->GetPattern<TitleBarPattern>();
    CHECK_NULL_RETURN(titleBarPattern, false);
    titleBarPattern->SetIsTitleChanged(true);
    if (navBarNode->GetPrevTitleIsCustomValue(false)) {
        titleBarNode->RemoveChild(titleBarNode->GetTitle());
        titleBarNode->SetTitle(nullptr);
        auto titleBarLayoutProperty = titleBarNode->GetLayoutProperty<TitleBarLayoutProperty>();
        CHECK_NULL_RETURN(titleBarLayoutProperty, false);
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
    do {
        if (ignoreMainTitle) {
            break;
        }
        auto mainTitle = AceType::DynamicCast<FrameNode>(titleBarNode->GetTitle());
        if (!hasMainTitle) {
            // remove main title if any.
            titleBarNode->RemoveChild(mainTitle);
            titleBarNode->SetTitle(nullptr);
            break;
        }

        if (mainTitle) {
            // update main title
            auto textLayoutProperty = mainTitle->GetLayoutProperty<TextLayoutProperty>();
            textLayoutProperty->UpdateMaxLines(hasSubTitle ? 1 : TITLEBAR_MAX_LINES);
            textLayoutProperty->UpdateContent(title);
            break;
        }
        // create and init main title
        mainTitle = FrameNode::CreateFrameNode(
            V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
        auto textLayoutProperty = mainTitle->GetLayoutProperty<TextLayoutProperty>();
        textLayoutProperty->UpdateContent(title);
        titleBarPattern->SetNeedResetMainTitleProperty(true);
        titleBarNode->SetTitle(mainTitle);
        titleBarNode->AddChild(mainTitle);
    } while (false);

    // create or update subtitle
    auto subTitle = AceType::DynamicCast<FrameNode>(titleBarNode->GetSubtitle());
    if (!hasSubTitle) {
        // remove subtitle if any.
        titleBarNode->RemoveChild(subTitle);
        titleBarNode->SetSubtitle(nullptr);
        return true;
    }
    if (subTitle) {
        // update subtitle
        auto textLayoutProperty = subTitle->GetLayoutProperty<TextLayoutProperty>();
        textLayoutProperty->UpdateContent(subtitle);
    } else {
        // create and init subtitle
        subTitle = FrameNode::CreateFrameNode(
            V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
        auto textLayoutProperty = subTitle->GetLayoutProperty<TextLayoutProperty>();
        textLayoutProperty->UpdateContent(subtitle);
        titleBarPattern->SetNeedResetSubTitleProperty(true);
        titleBarNode->SetSubtitle(subTitle);
        titleBarNode->AddChild(subTitle);
    }
    return true;
}

bool NavigationModelNG::ParseCommonTitle(bool hasSubTitle, bool hasMainTitle, const RefPtr<ResourceObject>& subResObj,
    const RefPtr<ResourceObject>& mainResObj)
{
    if (!hasSubTitle && !hasMainTitle) {
        return false;
    }
    std::string subtitle = "";
    std::string title = "";
    if (hasSubTitle) {
        ResourceParseUtils::ParseResString(subResObj, subtitle);
    }
    ResourceParseUtils::ParseResString(mainResObj, title);
    ParseCommonTitle(hasSubTitle, hasMainTitle, subtitle, title);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    auto navigationGroupNode = AceType::DynamicCast<NavigationGroupNode>(frameNode);
    CHECK_NULL_RETURN(navigationGroupNode, false);
    auto navBarNode = AceType::DynamicCast<NavBarNode>(navigationGroupNode->GetNavBarNode());
    CHECK_NULL_RETURN(navBarNode, false);
    auto titleBarNode = AceType::DynamicCast<TitleBarNode>(navBarNode->GetTitleBarNode());
    CHECK_NULL_RETURN(titleBarNode, false);
    UpdateMainTitle(titleBarNode, mainResObj);
    UpdateSubTitle(titleBarNode, subResObj);
    return true;
}

void NavigationModelNG::UpdateMainTitle(
    const RefPtr<NG::TitleBarNode>& titleBarNode, const RefPtr<ResourceObject>& mainResObj)
{
    std::string key = "navigation.title.commonMainTitle";
    auto updateFunc = [this, key, weak = AceType::WeakClaim(AceType::RawPtr(titleBarNode))](
                          const RefPtr<ResourceObject>& mainResObj) mutable {
        auto titleBarNode = weak.Upgrade();
        CHECK_NULL_VOID(titleBarNode);
        auto titleBarPattern = titleBarNode->GetPattern<TitleBarPattern>();
        CHECK_NULL_VOID(titleBarPattern);
        std::string title = titleBarPattern->GetResCacheMapByKey(key);
        if (title.empty()) {
            ResourceParseUtils::ParseResString(mainResObj, title);
            titleBarPattern->AddResCache(key, title);
        }
        auto mainTitle = AceType::DynamicCast<FrameNode>(titleBarNode->GetTitle());
        if (mainTitle) {
            auto textLayoutProperty = mainTitle->GetLayoutProperty<NG::TextLayoutProperty>();
            textLayoutProperty->UpdateContent(title);
            titleBarNode->MarkModifyDone();
            titleBarNode->MarkDirtyNode();
        }
    };
    CHECK_NULL_VOID(titleBarNode);
    auto titleBarPattern = titleBarNode->GetPattern<TitleBarPattern>();
    CHECK_NULL_VOID(titleBarPattern);
    titleBarPattern->AddResObj(key, mainResObj, std::move(updateFunc));
}

void NavigationModelNG::UpdateSubTitle(
    const RefPtr<NG::TitleBarNode>& titleBarNode, const RefPtr<ResourceObject>& resObj)
{
    std::string key = "navigation.title.commonSubTitle";
    auto updateFunc = [key, weak = AceType::WeakClaim(AceType::RawPtr(titleBarNode))](
                          const RefPtr<ResourceObject>& resObj) {
        auto titleBarNode = weak.Upgrade();
        CHECK_NULL_VOID(titleBarNode);
        auto titleBarPattern = titleBarNode->GetPattern<TitleBarPattern>();
        CHECK_NULL_VOID(titleBarPattern);
        std::string subTitleValue = titleBarPattern->GetResCacheMapByKey(key);
        if (subTitleValue.empty()) {
            ResourceParseUtils::ParseResString(resObj, subTitleValue);
            titleBarPattern->AddResCache(key, subTitleValue);
        }
        auto subTitle = AceType::DynamicCast<FrameNode>(titleBarNode->GetSubtitle());
        if (subTitle) {
            auto textLayoutProperty = subTitle->GetLayoutProperty<TextLayoutProperty>();
            textLayoutProperty->UpdateContent(subTitleValue);
            titleBarNode->MarkModifyDone();
            titleBarNode->MarkDirtyNode();
        }
    };
    CHECK_NULL_VOID(titleBarNode);
    auto titleBarPattern = titleBarNode->GetPattern<TitleBarPattern>();
    CHECK_NULL_VOID(titleBarPattern);
    titleBarPattern->AddResObj(key, resObj, std::move(updateFunc));
}

void NavigationModelNG::SetTitle(const std::string& title, bool hasSubTitle) {}

void NavigationModelNG::SetCustomTitle(const RefPtr<AceType>& customNode)
{
    auto customTitle = AceType::DynamicCast<NG::UINode>(customNode);
    CHECK_NULL_VOID(customTitle);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    auto navigationGroupNode = AceType::DynamicCast<NavigationGroupNode>(frameNode);
    CHECK_NULL_VOID(navigationGroupNode);
    auto navBarNode = AceType::DynamicCast<NavBarNode>(navigationGroupNode->GetNavBarNode());
    CHECK_NULL_VOID(navBarNode);
    auto titleBarNode = AceType::DynamicCast<TitleBarNode>(navBarNode->GetTitleBarNode());
    CHECK_NULL_VOID(titleBarNode);

    if (!navBarNode->GetPrevTitleIsCustomValue(false)) {
        titleBarNode->RemoveChild(titleBarNode->GetTitle());
        titleBarNode->RemoveChild(titleBarNode->GetSubtitle());
        titleBarNode->SetTitle(nullptr);
        titleBarNode->SetSubtitle(nullptr);
    }
    navBarNode->UpdatePrevTitleIsCustom(true);

    auto currentTitle = titleBarNode->GetTitle();
    if (currentTitle && customTitle->GetId() == currentTitle->GetId()) {
        // do nothing
        return;
    }
    // update custom title
    titleBarNode->RemoveChild(currentTitle);
    titleBarNode->SetTitle(customTitle);
    titleBarNode->AddChild(customTitle);
    titleBarNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
}

void NavigationModelNG::SetTitleHeight(const Dimension& height, bool isValid)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
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
    SetHideBackButton(true);
    auto navBarLayoutProperty = navBarNode->GetLayoutProperty<NavBarLayoutProperty>();
    CHECK_NULL_VOID(navBarLayoutProperty);
    navBarLayoutProperty->UpdateTitleMode(static_cast<NG::NavigationTitleMode>(NavigationTitleMode::MINI));
}

void NavigationModelNG::SetTitleHeight(const Dimension& height, const RefPtr<ResourceObject>& resObj)
{
    SetTitleHeight(height);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto navigationGroupNode = AceType::DynamicCast<NavigationGroupNode>(frameNode);
    CHECK_NULL_VOID(navigationGroupNode);
    auto navBarNode = AceType::DynamicCast<NavBarNode>(navigationGroupNode->GetNavBarNode());
    CHECK_NULL_VOID(navBarNode);
    auto titleBarNode = AceType::DynamicCast<TitleBarNode>(navBarNode->GetTitleBarNode());
    CHECK_NULL_VOID(titleBarNode);
    auto updateFunc = [this, weak = AceType::WeakClaim(AceType::RawPtr(titleBarNode))](
                          const RefPtr<ResourceObject>& resObj) {
        auto titleBarNode = weak.Upgrade();
        CHECK_NULL_VOID(titleBarNode);
        auto titleBarLayoutProperty = titleBarNode->GetLayoutProperty<TitleBarLayoutProperty>();
        CHECK_NULL_VOID(titleBarLayoutProperty);
        CalcDimension height = ParseTitleHeight(titleBarNode, resObj);
        titleBarLayoutProperty->UpdateTitleHeight(height);
        SetHideBackButton(true);
        titleBarNode->MarkModifyDone();
        titleBarNode->MarkDirtyNode();
    };
    auto titleBarPattern = titleBarNode->GetPattern<TitleBarPattern>();
    CHECK_NULL_VOID(titleBarPattern);
    titleBarPattern->AddResObj("navigation.title.customtitle", resObj, std::move(updateFunc));
}

CalcDimension NavigationModelNG::ParseTitleHeight(
    const RefPtr<NG::TitleBarNode>& titleBarNode, const RefPtr<ResourceObject>& resObj)
{
    CHECK_NULL_RETURN(titleBarNode, Dimension());
    auto titleBarPattern = titleBarNode->GetPattern<TitleBarPattern>();
    CHECK_NULL_RETURN(titleBarPattern, Dimension());
    std::string heightValue;
    std::string key = "navigation.title.customtitle";
    std::string heightString = titleBarPattern->GetResCacheMapByKey(key);
    if (heightString.empty() && ResourceParseUtils::ParseResString(resObj, heightValue)) {
        titleBarPattern->AddResCache(key, heightValue);
    } else {
        heightValue = heightString;
    }
    if (heightValue == NG::TITLE_MAIN_WITH_SUB) {
        return NG::DOUBLE_LINE_TITLEBAR_HEIGHT;
    }
    if (heightValue == NG::TITLE_MAIN) {
        return NG::SINGLE_LINE_TITLEBAR_HEIGHT;
    }

    CalcDimension height;
    if (heightString.empty()) {
        bool isValid = ResourceParseUtils::ParseResDimensionVpNG(resObj, height);
        titleBarPattern->AddResCache(key, height.ToString());
        if (!isValid || height.Value() < 0) {
            return Dimension();
        }
    } else {
        height = StringUtils::StringToCalcDimension(heightString);
    }
    return height;
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

void NavigationModelNG::SetTitleMode(NG::NavigationTitleMode mode)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
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

    if (Container::GreatOrEqualAPIVersion(PlatformVersion::VERSION_TWELVE) &&
        SystemProperties::IsNeedSymbol()) {
        CreateSymbolBackIcon(backButtonNode, navigationGroupNode);
    } else {
        CreateImageBackIcon(backButtonNode, navigationGroupNode);
    }

    //read navigation back button
    auto theme = NavigationGetTheme();
    std::string message = theme ? theme->GetNavigationBack() : "";
    NavigationTitleUtil::SetAccessibility(backButtonNode, message);

    backButtonNode->MarkModifyDone();
    titleBarNode->SetBackButton(backButtonNode);
    titleBarNode->AddChild(backButtonNode, 0);
}

bool NavigationModelNG::CreateBackButtonNode(RefPtr<FrameNode>& backButtonNode)
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
    auto context = PipelineContext::GetCurrentContext();
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

bool NavigationModelNG::UpdateBackButtonProperty(const RefPtr<FrameNode>& backButtonNode)
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

void NavigationModelNG::SetSubtitle(const std::string& subtitle)
{
    ParseCommonTitle(true, false, subtitle, "", true);
}

void NavigationModelNG::SetEnableModeChangeAnimation(bool isEnable)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    auto navigationGroupNode = AceType::DynamicCast<NavigationGroupNode>(frameNode);
    CHECK_NULL_VOID(navigationGroupNode);
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(NavigationLayoutProperty, EnableModeChangeAnimation, isEnable, navigationGroupNode);
}

void NavigationModelNG::SetSplitPlaceholder(const RefPtr<NG::UINode>& splitPlaceholder)
{
    CHECK_NULL_VOID(splitPlaceholder);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    auto navigationGroupNode = AceType::DynamicCast<NavigationGroupNode>(frameNode);
    CHECK_NULL_VOID(navigationGroupNode);
    if (!navigationGroupNode->GetPlaceholderContentNode()) {
        int32_t placeholderContentNodeId = ElementRegister::GetInstance()->MakeUniqueId();
        auto placeholderContentNode = FrameNode::GetOrCreateFrameNode(V2::SPLIT_PLACEHOLDER_CONTENT_ETS_TAG,
            placeholderContentNodeId, []() { return AceType::MakeRefPtr<Pattern>(); });
        placeholderContentNode->GetLayoutProperty()->UpdateAlignment(Alignment::TOP_LEFT);
        SafeAreaExpandOpts opts = { .type = SAFE_AREA_TYPE_SYSTEM | SAFE_AREA_TYPE_CUTOUT,
            .edges = SAFE_AREA_EDGE_ALL };
        placeholderContentNode->GetLayoutProperty()->UpdateSafeAreaExpandOpts(opts);
        const auto& eventHub = placeholderContentNode->GetEventHub<EventHub>();
        if (eventHub) {
            eventHub->SetEnabled(false);
        }
        auto focusHub = placeholderContentNode->GetOrCreateFocusHub();
        if (focusHub) {
            focusHub->SetFocusable(false);
        }
        auto renderContext = placeholderContentNode->GetRenderContext();
        CHECK_NULL_VOID(renderContext);
        renderContext->SetClipToBounds(true);
        renderContext->UpdateZIndex(-1);
        navigationGroupNode->AddChild(placeholderContentNode);
        navigationGroupNode->SetPlaceholderContentNode(placeholderContentNode);
    }
    navigationGroupNode->SetSplitPlaceholder(splitPlaceholder);
}

void NavigationModelNG::ResetSplitPlaceholder()
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    auto navigationGroupNode = AceType::DynamicCast<NavigationGroupNode>(frameNode);
    CHECK_NULL_VOID(navigationGroupNode);
    navigationGroupNode->ResetSplitPlaceholder();
}

void NavigationModelNG::SetHideTitleBar(bool hideTitleBar, bool animated)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    auto navigationGroupNode = AceType::DynamicCast<NavigationGroupNode>(frameNode);
    CHECK_NULL_VOID(navigationGroupNode);
    auto navBarNode = AceType::DynamicCast<NavBarNode>(navigationGroupNode->GetNavBarNode());
    CHECK_NULL_VOID(navBarNode);
    auto navBarLayoutProperty = navBarNode->GetLayoutProperty<NavBarLayoutProperty>();
    CHECK_NULL_VOID(navBarLayoutProperty);
    navBarLayoutProperty->UpdateHideTitleBar(hideTitleBar);
    navBarLayoutProperty->UpdateIsAnimatedTitleBar(animated);
}

void NavigationModelNG::SetHideNavBar(bool hideNavBar)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    RefPtr<NavigationGroupNode> navigationGroupNode =
        Referenced::Claim<NavigationGroupNode>(AceType::DynamicCast<NavigationGroupNode>(frameNode));
    CHECK_NULL_VOID(navigationGroupNode);
    SetHideNavBarInner(navigationGroupNode, hideNavBar);
}

void NavigationModelNG::SetEnableToolBarAdaptation(bool enable)
{
    ACE_UPDATE_LAYOUT_PROPERTY(NavigationLayoutProperty, EnableToolBarAdaptation, enable);
}

void NavigationModelNG::SetBackButtonIcon(const std::function<void(WeakPtr<NG::FrameNode>)>& symbolApply,
    const std::string& src, const ImageOption& imageOption, RefPtr<PixelMap>& pixMap,
    const std::vector<std::string>& nameList, bool userDefinedAccessibilityText,
    const std::string& backButtonAccessibilityText)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    auto navigationGroupNode = AceType::DynamicCast<NavigationGroupNode>(frameNode);
    CHECK_NULL_VOID(navigationGroupNode);

    auto navBarNode = AceType::DynamicCast<NavBarNode>(navigationGroupNode->GetNavBarNode());
    CHECK_NULL_VOID(navBarNode);
    auto titleBarNode = AceType::DynamicCast<TitleBarNode>(navBarNode->GetTitleBarNode());
    CHECK_NULL_VOID(titleBarNode);
    auto titleBarLayoutProperty = titleBarNode->GetLayoutProperty<TitleBarLayoutProperty>();
    CHECK_NULL_VOID(titleBarLayoutProperty);
    ImageSourceInfo imageSourceInfo(src, nameList[0], nameList[1]);
    ACE_UPDATE_LAYOUT_PROPERTY(NavigationLayoutProperty, NoPixMap, imageOption.noPixMap);
    ACE_UPDATE_LAYOUT_PROPERTY(NavigationLayoutProperty, ImageSource, imageSourceInfo);
    ACE_UPDATE_LAYOUT_PROPERTY(NavigationLayoutProperty, PixelMap, pixMap);
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
        auto theme = NavigationGetTheme();
        std::string message = theme ? theme->GetNavigationBack() : "";
        NavigationTitleUtil::SetAccessibility(backButtonNode, message);
    }
}

void NavigationModelNG::SetBackButtonIcon(const std::function<void(WeakPtr<NG::FrameNode>)>& symbolApply,
    const RefPtr<ResourceObject>& resObj, const ImageOption& imageOption, RefPtr<PixelMap>& pixMap,
    const std::vector<std::string>& nameList, bool userDefinedAccessibilityText,
    const std::string& backButtonAccessibilityText)
{
    std::string result;
    ResourceParseUtils::ParseResMedia(resObj, result);
    SetBackButtonIcon(symbolApply, result, imageOption, pixMap, nameList, userDefinedAccessibilityText,
        backButtonAccessibilityText);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto navigationGroupNode = AceType::DynamicCast<NavigationGroupNode>(frameNode);
    CHECK_NULL_VOID(navigationGroupNode);
    auto navBarNode = AceType::DynamicCast<NavBarNode>(navigationGroupNode->GetNavBarNode());
    CHECK_NULL_VOID(navBarNode);
    auto titleBarNode = AceType::DynamicCast<TitleBarNode>(navBarNode->GetTitleBarNode());
    CHECK_NULL_VOID(titleBarNode);
    std::string key = "navigation.backButtonIcon.icon";
    auto updateFunc = [key, nameList, weakTitleBarNode = AceType::WeakClaim(AceType::RawPtr(titleBarNode)),
                          weakFrameNode = AceType::WeakClaim(frameNode)](const RefPtr<ResourceObject>& resObj) {
        auto titleBarNode = weakTitleBarNode.Upgrade();
        CHECK_NULL_VOID(titleBarNode);
        auto titleBarPattern = titleBarNode->GetPattern();
        CHECK_NULL_VOID(titleBarPattern);
        std::string result = titleBarPattern->GetResCacheMapByKey(key);
        if (result.empty()) {
            ResourceParseUtils::ParseResMedia(resObj, result);
            titleBarPattern->AddResCache(key, result);
        }
        ImageSourceInfo imageSourceInfo(result, nameList[0], nameList[1]);
        auto frameNode = weakFrameNode.Upgrade();
        CHECK_NULL_VOID(frameNode);
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(NavigationLayoutProperty, ImageSource, imageSourceInfo, frameNode);
        auto titleBarLayoutProperty = titleBarNode->GetLayoutProperty<TitleBarLayoutProperty>();
        CHECK_NULL_VOID(titleBarLayoutProperty);
        titleBarLayoutProperty->UpdateImageSource(imageSourceInfo);
        titleBarNode->MarkModifyDone();
        titleBarNode->MarkDirtyNode();
    };
    auto titleBarPattern = titleBarNode->GetPattern();
    CHECK_NULL_VOID(titleBarPattern);
    titleBarPattern->AddResObj(key, resObj, std::move(updateFunc));
}

void NavigationModelNG::SetBackButtonIconSrcAndTextRes(const std::function<void(WeakPtr<NG::FrameNode>)>& symbolApply,
    const RefPtr<ResourceObject>& backButtonIconResObj, const ImageOption& imageOption, RefPtr<PixelMap>& pixMap,
    const std::vector<std::string>& nameList, bool userDefinedAccessibilityText,
    const RefPtr<ResourceObject>& backButtonTextResObj)
{
    std::string result;
    ResourceParseUtils::ParseResMedia(backButtonIconResObj, result);
    std::string backButtonAccessibilityText;
    ResourceParseUtils::ParseResMedia(backButtonTextResObj, backButtonAccessibilityText);
    SetBackButtonIcon(symbolApply, result, imageOption, pixMap, nameList, true, backButtonAccessibilityText);

    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto navigationGroupNode = AceType::DynamicCast<NavigationGroupNode>(frameNode);
    CHECK_NULL_VOID(navigationGroupNode);
    auto navBarNode = AceType::DynamicCast<NavBarNode>(navigationGroupNode->GetNavBarNode());
    CHECK_NULL_VOID(navBarNode);
    auto titleBarNode = AceType::DynamicCast<TitleBarNode>(navBarNode->GetTitleBarNode());
    CHECK_NULL_VOID(titleBarNode);
    auto titleBarLayoutProperty = titleBarNode->GetLayoutProperty<TitleBarLayoutProperty>();
    CHECK_NULL_VOID(titleBarLayoutProperty);
    auto titleBarPattern = titleBarNode->GetPattern<TitleBarPattern>();
    CHECK_NULL_VOID(titleBarPattern);
    UpdateBackButtonIcon(nameList, frameNode, backButtonIconResObj);
    UpdateBackButtonIconText(userDefinedAccessibilityText, titleBarNode, backButtonTextResObj);
}

void NavigationModelNG::UpdateBackButtonIcon(const std::vector<std::string>& nameList,
    NG::FrameNode* frameNode, const RefPtr<ResourceObject>& backButtonIconResObj)
{
    CHECK_NULL_VOID(frameNode);
    auto navigationGroupNode = AceType::DynamicCast<NavigationGroupNode>(frameNode);
    CHECK_NULL_VOID(navigationGroupNode);
    auto navBarNode = AceType::DynamicCast<NavBarNode>(navigationGroupNode->GetNavBarNode());
    CHECK_NULL_VOID(navBarNode);
    auto titleBarNode = AceType::DynamicCast<TitleBarNode>(navBarNode->GetTitleBarNode());
    CHECK_NULL_VOID(titleBarNode);
    std::string key = "navigation.backButtonIcon.icon";
    auto updateFunc = [key, nameList, weakFrameNode = AceType::WeakClaim(frameNode),
                          weakTitleBarNode = AceType::WeakClaim(AceType::RawPtr(titleBarNode))](
                          const RefPtr<ResourceObject>& backButtonIconResObj) {
        auto titleBarNode = weakTitleBarNode.Upgrade();
        CHECK_NULL_VOID(titleBarNode);
        auto titleBarPattern = titleBarNode->GetPattern();
        CHECK_NULL_VOID(titleBarPattern);
        std::string result = titleBarPattern->GetResCacheMapByKey(key);
        if (result.empty()) {
            ResourceParseUtils::ParseResMedia(backButtonIconResObj, result);
            titleBarPattern->AddResCache(key, result);
        }
        ImageSourceInfo imageSourceInfo(result, nameList[0], nameList[1]);
        auto frameNode = weakFrameNode.Upgrade();
        CHECK_NULL_VOID(frameNode);
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(NavigationLayoutProperty, ImageSource, imageSourceInfo, frameNode);
        auto titleBarLayoutProperty = titleBarNode->GetLayoutProperty<TitleBarLayoutProperty>();
        CHECK_NULL_VOID(titleBarLayoutProperty);
        titleBarLayoutProperty->UpdateImageSource(imageSourceInfo);
        titleBarNode->MarkModifyDone();
        titleBarNode->MarkDirtyNode();
    };
    auto titleBarPattern = titleBarNode->GetPattern();
    CHECK_NULL_VOID(titleBarPattern);
    titleBarPattern->AddResObj(key, backButtonIconResObj, std::move(updateFunc));
}

void NavigationModelNG::UpdateBackButtonIconText(bool userDefinedAccessibilityText,
    const RefPtr<NG::TitleBarNode>& titleBarNode, const RefPtr<ResourceObject>& backButtonTextResObj)
{
    std::string key = "navigation.backButtonIcon.accessibilityText";
    auto updateFunc = [key, userDefinedAccessibilityText, weak = AceType::WeakClaim(AceType::RawPtr(titleBarNode))](
                          const RefPtr<ResourceObject>& backButtonTextResObj) {
        auto titleBarNode = weak.Upgrade();
        CHECK_NULL_VOID(titleBarNode);
        auto backButtonNode = AceType::DynamicCast<FrameNode>(titleBarNode->GetBackButton());
        CHECK_NULL_VOID(backButtonNode);
        auto titleBarPattern = titleBarNode->GetPattern<TitleBarPattern>();
        CHECK_NULL_VOID(titleBarPattern);
        std::string backButtonAccessibilityText = titleBarPattern->GetResCacheMapByKey(key);
        if (backButtonAccessibilityText.empty()) {
            ResourceParseUtils::ParseResString(backButtonTextResObj, backButtonAccessibilityText);
            titleBarPattern->AddResCache(key, backButtonAccessibilityText);
        }
        if (userDefinedAccessibilityText) {
            NavigationTitleUtil::SetAccessibility(backButtonNode, backButtonAccessibilityText);
        } else {
            std::string message = Localization::GetInstance()->GetEntryLetters("navigation.back");
            NavigationTitleUtil::SetAccessibility(backButtonNode, message);
        }
        titleBarNode->MarkModifyDone();
        titleBarNode->MarkDirtyNode();
    };
    auto titleBarPattern = titleBarNode->GetPattern<TitleBarPattern>();
    CHECK_NULL_VOID(titleBarPattern);
    titleBarPattern->AddResObj(key, backButtonTextResObj, std::move(updateFunc));
}

void NavigationModelNG::SetBackButtonIconTextRes(const std::function<void(WeakPtr<NG::FrameNode>)>& symbolApply,
    const std::string& src, const ImageOption& imageOption, RefPtr<PixelMap>& pixMap,
    const std::vector<std::string>& nameList, bool userDefinedAccessibilityText,
    const RefPtr<ResourceObject>& resObj)
{
    std::string backButtonAccessibilityText;
    ResourceParseUtils::ParseResString(resObj, backButtonAccessibilityText);
    SetBackButtonIcon(symbolApply, src, imageOption, pixMap, nameList, true, backButtonAccessibilityText);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto navigationGroupNode = AceType::DynamicCast<NavigationGroupNode>(frameNode);
    CHECK_NULL_VOID(navigationGroupNode);
    auto navBarNode = AceType::DynamicCast<NavBarNode>(navigationGroupNode->GetNavBarNode());
    CHECK_NULL_VOID(navBarNode);
    auto titleBarNode = AceType::DynamicCast<TitleBarNode>(navBarNode->GetTitleBarNode());
    CHECK_NULL_VOID(titleBarNode);
    std::string key = "navigation.backButtonIcon.accessibilityText";
    auto updateFunc = [key, userDefinedAccessibilityText, weak = AceType::WeakClaim(AceType::RawPtr(titleBarNode))](
                          const RefPtr<ResourceObject>& resObj) {
        auto titleBarNode = weak.Upgrade();
        CHECK_NULL_VOID(titleBarNode);
        auto backButtonNode = AceType::DynamicCast<FrameNode>(titleBarNode->GetBackButton());
        CHECK_NULL_VOID(backButtonNode);
        auto titleBarPattern = titleBarNode->GetPattern<TitleBarPattern>();
        CHECK_NULL_VOID(titleBarPattern);
        std::string backButtonAccessibilityText = titleBarPattern->GetResCacheMapByKey(key);
        if (backButtonAccessibilityText.empty()) {
            ResourceParseUtils::ParseResString(resObj, backButtonAccessibilityText);
            titleBarPattern->AddResCache(key, backButtonAccessibilityText);
        }
        if (userDefinedAccessibilityText) {
            NavigationTitleUtil::SetAccessibility(backButtonNode, backButtonAccessibilityText);
        } else {
            std::string message = Localization::GetInstance()->GetEntryLetters("navigation.back");
            NavigationTitleUtil::SetAccessibility(backButtonNode, message);
        }
        titleBarNode->MarkModifyDone();
        titleBarNode->MarkDirtyNode();
    };
    auto titleBarPattern = titleBarNode->GetPattern<TitleBarPattern>();
    CHECK_NULL_VOID(titleBarPattern);
    titleBarPattern->AddResObj(key, resObj, std::move(updateFunc));
}

void NavigationModelNG::SetHideBackButton(bool hideBackButton)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
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

void NavigationModelNG::SetHideToolBar(bool hideToolBar, bool animated)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    auto navigationGroupNode = AceType::DynamicCast<NavigationGroupNode>(frameNode);
    CHECK_NULL_VOID(navigationGroupNode);
    auto navBarNode = AceType::DynamicCast<NavBarNode>(navigationGroupNode->GetNavBarNode());
    CHECK_NULL_VOID(navBarNode);
    auto navBarLayoutProperty = navBarNode->GetLayoutPropertyPtr<NavBarLayoutProperty>();
    CHECK_NULL_VOID(navBarLayoutProperty);
    navBarLayoutProperty->UpdateHideToolBar(hideToolBar);
    navBarLayoutProperty->UpdateIsAnimatedToolBar(animated);
}

void NavigationModelNG::SetCustomToolBar(const RefPtr<AceType>& customNode)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    auto navigationGroupNode = AceType::DynamicCast<NavigationGroupNode>(frameNode);
    CHECK_NULL_VOID(navigationGroupNode);
    auto navBarNode = AceType::DynamicCast<NavBarNode>(navigationGroupNode->GetNavBarNode());
    NavigationToolbarUtil::SetCustomToolBar(navBarNode, customNode);
}

bool NavigationModelNG::NeedSetItems()
{
    return true;
}

void NavigationModelNG::SetToolBarItems(std::vector<NG::BarItem>&& toolBarItems)
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

void NavigationModelNG::SetToolbarConfiguration(std::vector<NG::BarItem>&& toolBarItems, MoreButtonOptions&& opt)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    auto navigationGroupNode = AceType::DynamicCast<NavigationGroupNode>(frameNode);
    CHECK_NULL_VOID(navigationGroupNode);
    auto navBarNode = AceType::DynamicCast<NavBarNode>(navigationGroupNode->GetNavBarNode());
    auto localOpt = opt;
    NavigationToolbarUtil::SetToolbarMoreButtonOptions(navBarNode, std::move(opt));
    bool enabled = false;
    auto hub = navigationGroupNode->GetEventHub<EventHub>();
    if (hub) {
        enabled = hub->IsEnabled();
    }
    FieldProperty fieldProperty;
    fieldProperty.parentId = navigationGroupNode->GetInspectorId().value_or("");
    fieldProperty.field = NG::NAV_FIELD;
    auto localToolBarItems = toolBarItems;
    NavigationToolbarUtil::SetToolbarConfiguration(navBarNode, std::move(toolBarItems), enabled, fieldProperty);
    if (!SystemProperties::ConfigChangePerform()) {
        return;
    }
    RefPtr<ResourceObject> resObj = AceType::MakeRefPtr<ResourceObject>("", "", -1);
    auto updateFunc = [enabled, fieldProperty, weakNavBarNode = AceType::WeakClaim(AceType::RawPtr(navBarNode)),
                          localToolBarItems, localOpt](const RefPtr<ResourceObject>& resObj) mutable {
        auto navBarNode = weakNavBarNode.Upgrade();
        CHECK_NULL_VOID(navBarNode);
        if (localOpt.bgOptions.blurStyleOption.has_value()) {
            localOpt.bgOptions.blurStyleOption->ReloadResources();
        }
        if (localOpt.bgOptions.effectOption.has_value()) {
            localOpt.bgOptions.effectOption->ReloadResources();
        }
        auto localOptCopy = localOpt;
        NavigationToolbarUtil::SetToolbarMoreButtonOptions(navBarNode, std::move(localOptCopy));
        for (auto& item : localToolBarItems) {
            item.ReloadResources();
        }
        auto toolBarItemCopy = localToolBarItems;
        NavigationToolbarUtil::SetToolbarConfiguration(navBarNode, std::move(toolBarItemCopy), enabled, fieldProperty);
        navBarNode->MarkModifyDone();
        navBarNode->MarkDirtyNode();
    };
    auto pattern = navBarNode->GetPattern();
    CHECK_NULL_VOID(pattern);
    pattern->AddResObj("navigation.toolbarConfiguration", resObj, std::move(updateFunc));
}

void NavigationModelNG::SetToolbarConfiguration(std::vector<NG::BarItem>&& toolBarItems)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
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

void NavigationModelNG::SetMenuItems(std::vector<NG::BarItem>&& menuItems)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    auto navigationGroupNode = AceType::DynamicCast<NavigationGroupNode>(frameNode);
    CHECK_NULL_VOID(navigationGroupNode);
    auto navBarNode = AceType::DynamicCast<NavBarNode>(navigationGroupNode->GetNavBarNode());
    CHECK_NULL_VOID(navBarNode);
    auto titleBarNode = AceType::DynamicCast<TitleBarNode>(navBarNode->GetTitleBarNode());
    CHECK_NULL_VOID(titleBarNode);
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
    if (!SystemProperties::ConfigChangePerform()) {
        return;
    }
    RefPtr<ResourceObject> resObj = AceType::MakeRefPtr<ResourceObject>("", "", -1);
    auto updateFunc = [wekNavBarNode = AceType::WeakClaim(AceType::RawPtr(navBarNode)), menuItems](
                          const RefPtr<ResourceObject>& resObj) mutable {
        for (BarItem& item : menuItems) {
            item.ReloadResources();
        }
        auto navBarNode = wekNavBarNode.Upgrade();
        CHECK_NULL_VOID(navBarNode);
        auto navBarPattern = navBarNode->GetPattern<NavBarPattern>();
        CHECK_NULL_VOID(navBarPattern);
        navBarPattern->SetTitleBarMenuItems(menuItems);
        navBarNode->MarkModifyDone();
        navBarNode->MarkDirtyNode();
    };
    navBarPattern->AddResObj("navigation.menuItems", resObj, std::move(updateFunc));
}

void NavigationModelNG::SetCustomMenu(const RefPtr<AceType>& customNode)
{
    auto customMenu = AceType::DynamicCast<NG::UINode>(customNode);
    CHECK_NULL_VOID(customMenu);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    auto navigationGroupNode = AceType::DynamicCast<NavigationGroupNode>(frameNode);
    CHECK_NULL_VOID(navigationGroupNode);
    auto navBarNode = AceType::DynamicCast<NavBarNode>(navigationGroupNode->GetNavBarNode());
    CHECK_NULL_VOID(navBarNode);
    auto titleBarNode = AceType::DynamicCast<TitleBarNode>(navBarNode->GetTitleBarNode());
    CHECK_NULL_VOID(titleBarNode);
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
        return;
    }
    navBarNode->SetMenu(customMenu);
    navBarNode->UpdatePrevMenuIsCustom(true);
    navBarNode->UpdateMenuNodeOperation(ChildNodeOperation::ADD);
}

void NavigationModelNG::SetOnTitleModeChange(std::function<void(NG::NavigationTitleMode)>&& onTitleModeChange,
    std::function<void(const BaseEventInfo* baseInfo)>&& eventInfo)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    auto navigationGroupNode = AceType::DynamicCast<NavigationGroupNode>(frameNode);
    CHECK_NULL_VOID(navigationGroupNode);
    auto eventHub = navigationGroupNode->GetEventHub<NavigationEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnTitleModeChange(std::move(eventInfo));
}

void NavigationModelNG::SetOnNavBarWidthChangeEvent(OnNavBarWidthChangeEvent event)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<NavigationEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnNavBarWidthChangeEvent(std::move(event));
}

void NavigationModelNG::SetUsrNavigationMode(NavigationMode mode)
{
    ACE_UPDATE_LAYOUT_PROPERTY(NavigationLayoutProperty, UsrNavigationMode, mode);
    SetToolbarNavigationMode(mode);
}

void NavigationModelNG::SetToolbarNavigationMode(NavigationMode mode)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto navigationGroupNode = AceType::DynamicCast<NavigationGroupNode>(frameNode);
    CHECK_NULL_VOID(navigationGroupNode);
    auto pattern = navigationGroupNode->GetPattern<NavigationPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetToolbarManagerNavigationMode(mode);
}

void NavigationModelNG::SetNavBarPosition(NG::NavBarPosition mode)
{
    ACE_UPDATE_LAYOUT_PROPERTY(NavigationLayoutProperty, NavBarPosition, static_cast<NG::NavBarPosition>(mode));
}

void NavigationModelNG::SetNavBarWidth(const Dimension& value, bool isDoubleBind)
{
    ACE_UPDATE_LAYOUT_PROPERTY(NavigationLayoutProperty, NavBarWidth, value);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    auto navigationGroupNode = AceType::DynamicCast<NavigationGroupNode>(frameNode);
    CHECK_NULL_VOID(navigationGroupNode);
    auto navigationPattern = navigationGroupNode->GetPattern<NavigationPattern>();
    CHECK_NULL_VOID(navigationPattern);
    navBarWidthDoubleBind_ = isDoubleBind;
    if (IsDoubleBindBlock(navigationPattern)) {
        return;
    }
    navigationPattern->SetUserSetNavBarWidthFlag(true);
    if (navigationPattern->GetInitNavBarWidth() != value) {
        navigationPattern->SetInitNavBarWidth(value);
    }
}

void NavigationModelNG::SetNavBarWidth(const RefPtr<ResourceObject>& navBarWidthResObj)
{
    CalcDimension navBarWidth;
    ResourceParseUtils::ParseResDimensionVpNG(navBarWidthResObj, navBarWidth);
    if (navBarWidth.Value() <= 0) {
        navBarWidth.SetValue(DEFAULT_NAV_BAR_WIDTH_VALUE);
    }
    SetNavBarWidth(navBarWidth, false);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    std::string key = "navigation.navBarWidth";
    auto updateNavBarWidthFunc = [key, weak = AceType::WeakClaim(frameNode)](const RefPtr<ResourceObject>& resObj) {
        auto frameNode = weak.Upgrade();
        CHECK_NULL_VOID(frameNode);
        auto navigationGroupNode = AceType::DynamicCast<NavigationGroupNode>(frameNode);
        CHECK_NULL_VOID(navigationGroupNode);
        auto navigationPattern = navigationGroupNode->GetPattern<NavigationPattern>();
        CHECK_NULL_VOID(navigationPattern);
        CalcDimension navBarWidth;
        std::string navBarWidthString = navigationPattern->GetResCacheMapByKey(key);
        if (navBarWidthString.empty()) {
            ResourceParseUtils::ParseResDimensionVpNG(resObj, navBarWidth);
            navigationPattern->AddResCache(key, navBarWidth.ToString());
        } else {
            navBarWidth = StringUtils::StringToCalcDimension(navBarWidthString);
        }
        if (navBarWidth.Value() <= 0) {
            navBarWidth.SetValue(DEFAULT_NAV_BAR_WIDTH_VALUE);
        }
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(NavigationLayoutProperty, NavBarWidth, navBarWidth, frameNode);
        navigationPattern->SetUserSetNavBarWidthFlag(true);
        if (navigationPattern->GetInitNavBarWidth() != navBarWidth) {
            navigationPattern->SetInitNavBarWidth(navBarWidth);
        }
        navigationGroupNode->MarkModifyDone();
        navigationGroupNode->MarkDirtyNode();
    };
    auto pattern = frameNode->GetPattern<NavigationPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->AddResObj(key, navBarWidthResObj, std::move(updateNavBarWidthFunc));
}

void NavigationModelNG::SetMinNavBarWidth(const Dimension& value)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto navigationGroupNode = AceType::DynamicCast<NavigationGroupNode>(frameNode);
    CHECK_NULL_VOID(navigationGroupNode);
    auto navigationPattern = navigationGroupNode->GetPattern<NavigationPattern>();
    CHECK_NULL_VOID(navigationPattern);
    if (IsDoubleBindBlock(navigationPattern)) {
        return;
    }
    navigationPattern->SetIfNeedInit(true);
    ACE_UPDATE_LAYOUT_PROPERTY(NavigationLayoutProperty, MinNavBarWidth, value);
}

void NavigationModelNG::SetMinNavBarWidth(const RefPtr<ResourceObject>& minNavBarWidthResObj)
{
    CalcDimension minNavBarWidth;
    ResourceParseUtils::ParseResDimensionVpNG(minNavBarWidthResObj, minNavBarWidth);
    if (LessNotEqual(minNavBarWidth.Value(), 0.0)) {
        minNavBarWidth.SetValue(0);
    }
    SetMinNavBarWidth(minNavBarWidth);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    std::string key = "navigation.navBarWidthRange.minNavBarWidth";
    auto updateMinNavBarWidthFunc = [key, weak = AceType::WeakClaim(frameNode)](const RefPtr<ResourceObject>& resObj) {
        auto frameNode = weak.Upgrade();
        CHECK_NULL_VOID(frameNode);
        auto navigationGroupNode = AceType::DynamicCast<NavigationGroupNode>(frameNode);
        CHECK_NULL_VOID(navigationGroupNode);
        auto navigationPattern = navigationGroupNode->GetPattern<NavigationPattern>();
        CHECK_NULL_VOID(navigationPattern);
        CalcDimension minNavBarWidth;
        std::string minNavBarWidthString = navigationPattern->GetResCacheMapByKey(key);
        if (minNavBarWidthString.empty()) {
            ResourceParseUtils::ParseResDimensionVpNG(resObj, minNavBarWidth);
            navigationPattern->AddResCache(key, minNavBarWidth.ToString());
        } else {
            minNavBarWidth = StringUtils::StringToCalcDimension(minNavBarWidthString);
        }
        if (LessNotEqual(minNavBarWidth.Value(), 0.0)) {
            minNavBarWidth.SetValue(0);
        }
        navigationPattern->SetIfNeedInit(true);
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(NavigationLayoutProperty, MinNavBarWidth, minNavBarWidth, frameNode);
        navigationGroupNode->MarkModifyDone();
        navigationGroupNode->MarkDirtyNode();
    };
    auto pattern = frameNode->GetPattern<NavigationPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->AddResObj(key, minNavBarWidthResObj, std::move(updateMinNavBarWidthFunc));
}

void NavigationModelNG::SetMaxNavBarWidth(const Dimension& value)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto navigationGroupNode = AceType::DynamicCast<NavigationGroupNode>(frameNode);
    CHECK_NULL_VOID(navigationGroupNode);
    auto navigationPattern = navigationGroupNode->GetPattern<NavigationPattern>();
    CHECK_NULL_VOID(navigationPattern);
    if (IsDoubleBindBlock(navigationPattern)) {
        return;
    }
    navigationPattern->SetIfNeedInit(true);
    ACE_UPDATE_LAYOUT_PROPERTY(NavigationLayoutProperty, MaxNavBarWidth, value);
}

void NavigationModelNG::SetMaxNavBarWidth(const RefPtr<ResourceObject>& maxNavBarWidthResObj)
{
    CalcDimension maxNavBarWidth;
    ResourceParseUtils::ParseResDimensionVpNG(maxNavBarWidthResObj, maxNavBarWidth);
    if (LessNotEqual(maxNavBarWidth.Value(), 0.0)) {
        maxNavBarWidth.SetValue(0);
    }
    SetMaxNavBarWidth(maxNavBarWidth);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    std::string key = "navigation.navBarWidthRange.maxNavBarWidth";
    auto updateMaxNavBarWidthFunc = [key, weak = AceType::WeakClaim(frameNode)](const RefPtr<ResourceObject>& resObj) {
        auto frameNode = weak.Upgrade();
        CHECK_NULL_VOID(frameNode);
        auto navigationGroupNode = AceType::DynamicCast<NavigationGroupNode>(frameNode);
        CHECK_NULL_VOID(navigationGroupNode);
        auto navigationPattern = navigationGroupNode->GetPattern<NavigationPattern>();
        CHECK_NULL_VOID(navigationPattern);
        CalcDimension maxNavBarWidth;
        std::string maxNavBarWidthString = navigationPattern->GetResCacheMapByKey(key);
        if (maxNavBarWidthString.empty()) {
            ResourceParseUtils::ParseResDimensionVpNG(resObj, maxNavBarWidth);
            navigationPattern->AddResCache(key, maxNavBarWidth.ToString());
        } else {
            maxNavBarWidth = StringUtils::StringToCalcDimension(maxNavBarWidthString);
        }
        if (LessNotEqual(maxNavBarWidth.Value(), 0.0)) {
            maxNavBarWidth.SetValue(0);
        }
        navigationPattern->SetIfNeedInit(true);
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(NavigationLayoutProperty, MaxNavBarWidth, maxNavBarWidth, frameNode);
        navigationGroupNode->MarkModifyDone();
        navigationGroupNode->MarkDirtyNode();
    };
    auto pattern = frameNode->GetPattern<NavigationPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->AddResObj(key, maxNavBarWidthResObj, std::move(updateMaxNavBarWidthFunc));
}

void NavigationModelNG::SetMinContentWidth(const Dimension& value)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto navigationGroupNode = AceType::DynamicCast<NavigationGroupNode>(frameNode);
    CHECK_NULL_VOID(navigationGroupNode);
    auto navigationPattern = navigationGroupNode->GetPattern<NavigationPattern>();
    CHECK_NULL_VOID(navigationPattern);
    navigationPattern->SetIfNeedInit(true);
    ACE_UPDATE_LAYOUT_PROPERTY(NavigationLayoutProperty, MinContentWidth, value);
}

void NavigationModelNG::SetMinContentWidth(const RefPtr<ResourceObject>& minContentWidthResObj)
{
    CalcDimension minContentWidth;
    ResourceParseUtils::ParseResDimensionVpNG(minContentWidthResObj, minContentWidth);
    if (LessNotEqual(minContentWidth.Value(), 0.0)) {
        minContentWidth = DEFAULT_MIN_CONTENT_WIDTH;
    }
    SetMinContentWidth(minContentWidth);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    std::string key = "navigation.minContentWidth";
    auto updateMinContentWidthFunc = [key, weak = AceType::WeakClaim(frameNode)](const RefPtr<ResourceObject>& resObj) {
        auto frameNode = weak.Upgrade();
        CHECK_NULL_VOID(frameNode);
        auto navigationGroupNode = AceType::DynamicCast<NavigationGroupNode>(frameNode);
        CHECK_NULL_VOID(navigationGroupNode);
        auto navigationPattern = navigationGroupNode->GetPattern<NavigationPattern>();
        CHECK_NULL_VOID(navigationPattern);
        CalcDimension minContentWidth;
        std::string minContentWidthString = navigationPattern->GetResCacheMapByKey(key);
        if (minContentWidthString.empty()) {
            ResourceParseUtils::ParseResDimensionVpNG(resObj, minContentWidth);
            navigationPattern->AddResCache(key, minContentWidth.ToString());
        } else {
            minContentWidth = StringUtils::StringToCalcDimension(minContentWidthString);
        }
        if (LessNotEqual(minContentWidth.Value(), 0.0)) {
            minContentWidth = DEFAULT_MIN_CONTENT_WIDTH;
        }
        navigationPattern->SetIfNeedInit(true);
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(NavigationLayoutProperty, MinContentWidth, minContentWidth, frameNode);
        navigationGroupNode->MarkModifyDone();
        navigationGroupNode->MarkDirtyNode();
    };
    auto pattern = frameNode->GetPattern<NavigationPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->AddResObj(key, minContentWidthResObj, std::move(updateMinContentWidthFunc));
}

void NavigationModelNG::SetOnNavBarStateChange(std::function<void(bool)>&& onNavBarStateChange)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto navigationEventHub = AceType::DynamicCast<NavigationEventHub>(frameNode->GetEventHub<EventHub>());
    CHECK_NULL_VOID(navigationEventHub);
    navigationEventHub->SetOnNavBarStateChange(std::move(onNavBarStateChange));
}

void NavigationModelNG::SetOnNavigationModeChange(std::function<void(NavigationMode)>&& modeChange)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto navigationEventHub = AceType::DynamicCast<NavigationEventHub>(frameNode->GetEventHub<EventHub>());
    CHECK_NULL_VOID(navigationEventHub);
    navigationEventHub->SetOnNavigationModeChange(std::move(modeChange));
}

void NavigationModelNG::SetNavigationMode(NavigationMode mode)
{
    ACE_UPDATE_LAYOUT_PROPERTY(NavigationLayoutProperty, NavigationMode, mode);
    SetToolbarNavigationMode(mode);
}

void NavigationModelNG::SetNavigationStack(const RefPtr<NG::NavigationStack>& navigationStack)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    auto navigationGroupNode = AceType::DynamicCast<NavigationGroupNode>(frameNode);
    CHECK_NULL_VOID(navigationGroupNode);
    auto pattern = navigationGroupNode->GetPattern<NavigationPattern>();
    CHECK_NULL_VOID(pattern);
    const auto& stack = pattern->GetNavigationStack();
    if (stack) {
        stack->UpdateStackInfo(navigationStack);
    } else {
        pattern->SetNavigationStack(navigationStack);
    }
}

void NavigationModelNG::SetNavigationStackWithCreatorAndUpdater(
    std::function<RefPtr<NG::NavigationStack>()> creator, std::function<void(RefPtr<NG::NavigationStack>)> updater)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    auto navigationGroupNode = AceType::DynamicCast<NavigationGroupNode>(frameNode);
    CHECK_NULL_VOID(navigationGroupNode);
    auto pattern = navigationGroupNode->GetPattern<NavigationPattern>();
    CHECK_NULL_VOID(pattern);
    RefPtr<NavigationStack> stack = pattern->GetNavigationStack();
    if (!stack) {
        stack = creator();
        pattern->SetNavigationStack(stack);
    }
    updater(stack);
}

bool NavigationModelNG::UseHomeDestination() const
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    auto navigationGroupNode = AceType::DynamicCast<NavigationGroupNode>(frameNode);
    CHECK_NULL_RETURN(navigationGroupNode, false);
    auto useHomeDest = navigationGroupNode->GetUseHomeDestination();
    return useHomeDest.has_value() && useHomeDest.value();
}

void NavigationModelNG::SetHomePathInfoWithCallback(
    std::function<void(const RefPtr<NavigationStack>&)>&& setHomePathInfoCallback)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    auto navigationGroupNode = AceType::DynamicCast<NavigationGroupNode>(frameNode);
    CHECK_NULL_VOID(navigationGroupNode);
    auto pattern = navigationGroupNode->GetPattern<NavigationPattern>();
    CHECK_NULL_VOID(pattern);
    auto stack = pattern->GetNavigationStack();
    if (setHomePathInfoCallback) {
        setHomePathInfoCallback(stack);
    }
}

void NavigationModelNG::SetNavigationStack()
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    auto navigationGroupNode = AceType::DynamicCast<NavigationGroupNode>(frameNode);
    CHECK_NULL_VOID(navigationGroupNode);
    auto pattern = navigationGroupNode->GetPattern<NavigationPattern>();
    CHECK_NULL_VOID(pattern);
    auto navigationStack = pattern->GetNavigationStack();
    if (!navigationStack) {
        auto navigationStack = AceType::MakeRefPtr<NavigationStack>();
        pattern->SetNavigationStack(navigationStack);
    }
}

void NavigationModelNG::SetNavigationPathInfo(const std::string& moduleName, const std::string& pagePath)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    auto navigationGroupNode = AceType::DynamicCast<NavigationGroupNode>(frameNode);
    CHECK_NULL_VOID(navigationGroupNode);
    navigationGroupNode->SetNavigationPathInfo(moduleName, pagePath);
}

void NavigationModelNG::SetNavigationStackProvided(bool provided)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    auto navigationGroupNode = AceType::DynamicCast<NavigationGroupNode>(frameNode);
    CHECK_NULL_VOID(navigationGroupNode);
    auto pattern = navigationGroupNode->GetPattern<NavigationPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetNavigationStackProvided(provided);
}

void NavigationModelNG::SetNavDestination(std::function<void(std::string)>&& builder)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    auto navigationGroupNode = AceType::DynamicCast<NavigationGroupNode>(frameNode);
    CHECK_NULL_VOID(navigationGroupNode);
    auto pattern = navigationGroupNode->GetPattern<NavigationPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetNavDestination(std::move(builder));
}

RefPtr<NG::NavigationStack> NavigationModelNG::GetNavigationStack()
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    auto navigationGroupNode = AceType::DynamicCast<NavigationGroupNode>(frameNode);
    CHECK_NULL_RETURN(navigationGroupNode, nullptr);
    auto pattern = navigationGroupNode->GetPattern<NavigationPattern>();
    CHECK_NULL_RETURN(pattern, nullptr);
    return pattern->GetNavigationStack();
}

RefPtr<NG::NavigationStack> NavigationModelNG::GetNavigationStack(FrameNode* frameNode)
{
    auto navigationGroupNode = AceType::DynamicCast<NavigationGroupNode>(frameNode);
    CHECK_NULL_RETURN(navigationGroupNode, nullptr);
    auto pattern = navigationGroupNode->GetPattern<NavigationPattern>();
    CHECK_NULL_RETURN(pattern, nullptr);
    return pattern->GetNavigationStack();
}

void NavigationModelNG::SetMenuCount(int32_t menuCount)
{
    return;
}

void NavigationModelNG::SetOnTitleModeChange(FrameNode* frameNode,
    std::function<void(NG::NavigationTitleMode)>&& onTitleModeChange,
    std::function<void(const BaseEventInfo* baseInfo)>&& eventInfo)
{
    auto navigationGroupNode = AceType::DynamicCast<NavigationGroupNode>(frameNode);
    CHECK_NULL_VOID(navigationGroupNode);
    auto eventHub = navigationGroupNode->GetEventHub<NavigationEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnTitleModeChange(std::move(eventInfo));
}

void NavigationModelNG::SetOnNavigationModeChange(FrameNode* frameNode,
    std::function<void(NavigationMode)>&& modeChange)
{
    auto navigationEventHub = AceType::DynamicCast<NavigationEventHub>(frameNode->GetEventHub<EventHub>());
    CHECK_NULL_VOID(navigationEventHub);
    navigationEventHub->SetOnNavigationModeChange(std::move(modeChange));
}

void NavigationModelNG::SetIsCustomAnimation(FrameNode* frameNode, bool isCustom)
{
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<NavigationPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetIsCustomAnimation(isCustom);
}

void NavigationModelNG::SetToolBarItems(FrameNode* frameNode, std::vector<NG::BarItem>&& toolBarItems)
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

void NavigationModelNG::SetOnNavBarStateChange(FrameNode* frameNode, std::function<void(bool)>&& onNavBarStateChange)
{
    CHECK_NULL_VOID(frameNode);
    auto navigationEventHub = AceType::DynamicCast<NavigationEventHub>(frameNode->GetEventHub<EventHub>());
    CHECK_NULL_VOID(navigationEventHub);
    navigationEventHub->SetOnNavBarStateChange(std::move(onNavBarStateChange));
}

void NavigationModelNG::SetHideToolBar(FrameNode* frameNode, bool hideToolBar, bool animated)
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

void NavigationModelNG::ResetResObj(FrameNode* frameNode, NavigationPatternType type, const std::string& key)
{
    if (!SystemProperties::ConfigChangePerform()) {
        return;
    }
    CHECK_NULL_VOID(frameNode);
    auto navigationGroupNode = AceType::DynamicCast<NavigationGroupNode>(frameNode);
    CHECK_NULL_VOID(navigationGroupNode);
    RefPtr<Pattern> pattern = nullptr;
    if (type == NavigationPatternType::NAV_BAR) {
        auto navBarNode = AceType::DynamicCast<NavBarNode>(navigationGroupNode->GetNavBarNode());
        CHECK_NULL_VOID(navBarNode);
        pattern = navBarNode->GetPattern<NavBarPattern>();
    } else if (type == NavigationPatternType::TITLE_BAR) {
        auto navBarNode = AceType::DynamicCast<NavBarNode>(navigationGroupNode->GetNavBarNode());
        CHECK_NULL_VOID(navBarNode);
        auto titleBarNode = AceType::DynamicCast<TitleBarNode>(navBarNode->GetTitleBarNode());
        CHECK_NULL_VOID(titleBarNode);
        pattern = titleBarNode->GetPattern<TitleBarPattern>();
    } else if (type == NavigationPatternType::NAVIGATION) {
        pattern = navigationGroupNode->GetPattern<NavigationPattern>();
    }
    CHECK_NULL_VOID(pattern);
    pattern->RemoveResObj(key);
}

void NavigationModelNG::SetMinContentWidth(FrameNode* frameNode, const Dimension& value)
{
    auto navigationGroupNode = AceType::DynamicCast<NavigationGroupNode>(frameNode);
    CHECK_NULL_VOID(navigationGroupNode);
    auto navigationPattern = navigationGroupNode->GetPattern<NavigationPattern>();
    CHECK_NULL_VOID(navigationPattern);
    navigationPattern->SetIfNeedInit(true);
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(NavigationLayoutProperty, MinContentWidth, value, frameNode);
}

void NavigationModelNG::SetMinContentWidth(FrameNode* frameNode, const RefPtr<ResourceObject>& minContentWidthResObj)
{
    CHECK_NULL_VOID(frameNode);
    CalcDimension minContentWidth;
    ResourceParseUtils::ParseResDimensionVpNG(minContentWidthResObj, minContentWidth);
    if (LessNotEqual(minContentWidth.Value(), 0.0)) {
        minContentWidth = DEFAULT_MIN_CONTENT_WIDTH;
    }
    SetMinContentWidth(frameNode, minContentWidth);
    std::string key = "navigation.minContentWidth";
    auto updateMinContentWidthFunc = [key, weak = AceType::WeakClaim(frameNode)](const RefPtr<ResourceObject>& resObj) {
        auto frameNode = weak.Upgrade();
        CHECK_NULL_VOID(frameNode);
        auto navigationGroupNode = AceType::DynamicCast<NavigationGroupNode>(frameNode);
        CHECK_NULL_VOID(navigationGroupNode);
        auto navigationPattern = navigationGroupNode->GetPattern<NavigationPattern>();
        CHECK_NULL_VOID(navigationPattern);
        CalcDimension minContentWidth;
        std::string minContentWidthString = navigationPattern->GetResCacheMapByKey(key);
        if (minContentWidthString.empty()) {
            ResourceParseUtils::ParseResDimensionVpNG(resObj, minContentWidth);
            navigationPattern->AddResCache(key, minContentWidth.ToString());
        } else {
            minContentWidth = StringUtils::StringToCalcDimension(minContentWidthString);
        }
        if (LessNotEqual(minContentWidth.Value(), 0.0)) {
            minContentWidth = DEFAULT_MIN_CONTENT_WIDTH;
        }
        navigationPattern->SetIfNeedInit(true);
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(NavigationLayoutProperty, MinContentWidth, minContentWidth, frameNode);
        navigationGroupNode->MarkModifyDone();
        navigationGroupNode->MarkDirtyNode();
    };
    auto pattern = frameNode->GetPattern<NavigationPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->AddResObj(key, minContentWidthResObj, std::move(updateMinContentWidthFunc));
}

void NavigationModelNG::SetMinNavBarWidth(FrameNode* frameNode, const Dimension& value)
{
    auto navigationGroupNode = AceType::DynamicCast<NavigationGroupNode>(frameNode);
    CHECK_NULL_VOID(navigationGroupNode);
    auto navigationPattern = navigationGroupNode->GetPattern<NavigationPattern>();
    CHECK_NULL_VOID(navigationPattern);
    if (IsDoubleBindBlock(navigationPattern)) {
        return;
    }
    navigationPattern->SetIfNeedInit(true);
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(NavigationLayoutProperty, MinNavBarWidth, value, frameNode);
}

void NavigationModelNG::SetMinNavBarWidth(FrameNode* frameNode, const RefPtr<ResourceObject>& minNavBarWidthResObj)
{
    CHECK_NULL_VOID(frameNode);
    CalcDimension minNavBarWidth;
    ResourceParseUtils::ParseResDimensionVpNG(minNavBarWidthResObj, minNavBarWidth);
    if (LessNotEqual(minNavBarWidth.Value(), 0.0)) {
        minNavBarWidth.SetValue(0);
    }
    SetMinNavBarWidth(frameNode, minNavBarWidth);
    std::string key = "navigation.navBarWidthRange.minNavBarWidth";
    auto updateMinNavBarWidthFunc = [key, weak = AceType::WeakClaim(frameNode)](const RefPtr<ResourceObject>& resObj) {
        auto frameNode = weak.Upgrade();
        CHECK_NULL_VOID(frameNode);
        auto navigationGroupNode = AceType::DynamicCast<NavigationGroupNode>(frameNode);
        CHECK_NULL_VOID(navigationGroupNode);
        auto navigationPattern = navigationGroupNode->GetPattern<NavigationPattern>();
        CHECK_NULL_VOID(navigationPattern);
        CalcDimension minNavBarWidth;
        std::string minNavBarWidthString = navigationPattern->GetResCacheMapByKey(key);
        if (minNavBarWidthString.empty()) {
            ResourceParseUtils::ParseResDimensionVpNG(resObj, minNavBarWidth);
            navigationPattern->AddResCache(key, minNavBarWidth.ToString());
        } else {
            minNavBarWidth = StringUtils::StringToCalcDimension(minNavBarWidthString);
        }
        if (LessNotEqual(minNavBarWidth.Value(), 0.0)) {
            minNavBarWidth.SetValue(0);
        }
        navigationPattern->SetIfNeedInit(true);
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(NavigationLayoutProperty, MinNavBarWidth, minNavBarWidth, frameNode);
        navigationGroupNode->MarkModifyDone();
        navigationGroupNode->MarkDirtyNode();
    };
    auto pattern = frameNode->GetPattern<NavigationPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->AddResObj(key, minNavBarWidthResObj, std::move(updateMinNavBarWidthFunc));
}

void NavigationModelNG::SetMaxNavBarWidth(FrameNode* frameNode, const Dimension& value)
{
    auto navigationGroupNode = AceType::DynamicCast<NavigationGroupNode>(frameNode);
    CHECK_NULL_VOID(navigationGroupNode);
    auto navigationPattern = navigationGroupNode->GetPattern<NavigationPattern>();
    CHECK_NULL_VOID(navigationPattern);
    if (IsDoubleBindBlock(navigationPattern)) {
        return;
    }
    navigationPattern->SetIfNeedInit(true);
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(NavigationLayoutProperty, MaxNavBarWidth, value, frameNode);
}

void NavigationModelNG::SetMaxNavBarWidth(FrameNode* frameNode, const RefPtr<ResourceObject>& maxNavBarWidthResObj)
{
    CHECK_NULL_VOID(frameNode);
    CalcDimension maxNavBarWidth;
    ResourceParseUtils::ParseResDimensionVpNG(maxNavBarWidthResObj, maxNavBarWidth);
    if (LessNotEqual(maxNavBarWidth.Value(), 0.0)) {
        maxNavBarWidth.SetValue(0);
    }
    SetMaxNavBarWidth(frameNode, maxNavBarWidth);
    std::string key = "navigation.navBarWidthRange.maxNavBarWidth";
    auto updateMaxNavBarWidthFunc = [key, weak = AceType::WeakClaim(frameNode)](const RefPtr<ResourceObject>& resObj) {
        auto frameNode = weak.Upgrade();
        CHECK_NULL_VOID(frameNode);
        auto navigationGroupNode = AceType::DynamicCast<NavigationGroupNode>(frameNode);
        CHECK_NULL_VOID(navigationGroupNode);
        auto navigationPattern = navigationGroupNode->GetPattern<NavigationPattern>();
        CHECK_NULL_VOID(navigationPattern);
        CalcDimension maxNavBarWidth;
        std::string maxNavBarWidthString = navigationPattern->GetResCacheMapByKey(key);
        if (maxNavBarWidthString.empty()) {
            ResourceParseUtils::ParseResDimensionVpNG(resObj, maxNavBarWidth);
            navigationPattern->AddResCache(key, maxNavBarWidth.ToString());
        } else {
            maxNavBarWidth = StringUtils::StringToCalcDimension(maxNavBarWidthString);
        }
        if (LessNotEqual(maxNavBarWidth.Value(), 0.0)) {
            maxNavBarWidth.SetValue(0);
        }
        navigationPattern->SetIfNeedInit(true);
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(NavigationLayoutProperty, MaxNavBarWidth, maxNavBarWidth, frameNode);
        navigationGroupNode->MarkModifyDone();
        navigationGroupNode->MarkDirtyNode();
    };
    auto pattern = frameNode->GetPattern<NavigationPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->AddResObj(key, maxNavBarWidthResObj, std::move(updateMaxNavBarWidthFunc));
}

void NavigationModelNG::SetNavBarWidth(FrameNode* frameNode, const Dimension& value)
{
    CHECK_NULL_VOID(frameNode);
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(NavigationLayoutProperty, NavBarWidth, value, frameNode);
    auto navigationGroupNode = AceType::DynamicCast<NavigationGroupNode>(frameNode);
    CHECK_NULL_VOID(navigationGroupNode);
    auto navigationPattern = navigationGroupNode->GetPattern<NavigationPattern>();
    CHECK_NULL_VOID(navigationPattern);
    if (IsDoubleBindBlock(navigationPattern)) {
        return;
    }
    navigationPattern->SetUserSetNavBarWidthFlag(true);
    if (navigationPattern->GetInitNavBarWidth() != value) {
        navigationPattern->SetInitNavBarWidth(value);
    }
}

void NavigationModelNG::SetNavBarWidth(FrameNode* frameNode, const RefPtr<ResourceObject>& navBarWidthResObj)
{
    CHECK_NULL_VOID(frameNode);
    CalcDimension navBarWidth;
    ResourceParseUtils::ParseResDimensionVpNG(navBarWidthResObj, navBarWidth);
    if (navBarWidth.Value() <= 0) {
        navBarWidth.SetValue(DEFAULT_NAV_BAR_WIDTH_VALUE);
    }
    SetNavBarWidth(frameNode, navBarWidth);
    std::string key = "navigation.navBarWidth";
    auto updateNavBarWidthFunc = [key, weak = AceType::WeakClaim(frameNode)](const RefPtr<ResourceObject>& resObj) {
        auto frameNode = weak.Upgrade();
        CHECK_NULL_VOID(frameNode);
        auto navigationGroupNode = AceType::DynamicCast<NavigationGroupNode>(frameNode);
        CHECK_NULL_VOID(navigationGroupNode);
        auto navigationPattern = navigationGroupNode->GetPattern<NavigationPattern>();
        CHECK_NULL_VOID(navigationPattern);
        CalcDimension navBarWidth;
        std::string navBarWidthString = navigationPattern->GetResCacheMapByKey(key);
        if (navBarWidthString.empty()) {
            ResourceParseUtils::ParseResDimensionVpNG(resObj, navBarWidth);
            navigationPattern->AddResCache(key, navBarWidth.ToString());
        } else {
            navBarWidth = StringUtils::StringToCalcDimension(navBarWidthString);
        }
        if (navBarWidth.Value() <= 0) {
            navBarWidth.SetValue(DEFAULT_NAV_BAR_WIDTH_VALUE);
        }
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(NavigationLayoutProperty, NavBarWidth, navBarWidth, frameNode);
        navigationPattern->SetUserSetNavBarWidthFlag(true);
        if (navigationPattern->GetInitNavBarWidth() != navBarWidth) {
            navigationPattern->SetInitNavBarWidth(navBarWidth);
        }
        navigationGroupNode->MarkModifyDone();
        navigationGroupNode->MarkDirtyNode();
    };
    auto pattern = frameNode->GetPattern<NavigationPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->AddResObj(key, navBarWidthResObj, std::move(updateNavBarWidthFunc));
}

void NavigationModelNG::SetNavBarPosition(FrameNode* frameNode, NG::NavBarPosition mode)
{
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(
        NavigationLayoutProperty, NavBarPosition, static_cast<NG::NavBarPosition>(mode), frameNode);
}

void NavigationModelNG::SetUsrNavigationMode(FrameNode* frameNode, NavigationMode mode)
{
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(NavigationLayoutProperty, UsrNavigationMode, mode, frameNode);
}

void NavigationModelNG::SetBackButtonIcon(FrameNode* frameNode,
    const std::function<void(WeakPtr<NG::FrameNode>)>& symbolApply, const std::string& src,
    const ImageOption& imageOption, RefPtr<PixelMap>& pixMap)
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
    ImageSourceInfo imageSourceInfo(src);
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(NavigationLayoutProperty, NoPixMap, imageOption.noPixMap, frameNode);
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(NavigationLayoutProperty, ImageSource, imageSourceInfo, frameNode);
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(NavigationLayoutProperty, PixelMap, pixMap, frameNode);
    titleBarLayoutProperty->UpdateImageSource(imageSourceInfo);
    titleBarLayoutProperty->UpdateNoPixMap(imageOption.noPixMap);
    titleBarLayoutProperty->UpdatePixelMap(pixMap);
    titleBarLayoutProperty->SetBackIconSymbol(symbolApply);
    titleBarLayoutProperty->UpdateIsValidImage(imageOption.isValidImage);
}

void NavigationModelNG::SetBackButtonIcon(FrameNode* frameNode,
    const std::function<void(WeakPtr<NG::FrameNode>)>& symbolApply, const ImageOption& imageOption,
    RefPtr<PixelMap>& pixMap, const RefPtr<ResourceObject>& backButtonIconResObj)
{
    CHECK_NULL_VOID(frameNode);
    std::string result;
    ResourceParseUtils::ParseResMedia(backButtonIconResObj, result);
    SetBackButtonIcon(frameNode, symbolApply, result, imageOption, pixMap);
    auto navigationGroupNode = AceType::DynamicCast<NavigationGroupNode>(frameNode);
    CHECK_NULL_VOID(navigationGroupNode);
    auto navBarNode = AceType::DynamicCast<NavBarNode>(navigationGroupNode->GetNavBarNode());
    CHECK_NULL_VOID(navBarNode);
    auto titleBarNode = AceType::DynamicCast<TitleBarNode>(navBarNode->GetTitleBarNode());
    CHECK_NULL_VOID(titleBarNode);
    std::string key = "navigation.backButtonIcon.icon";
    auto updateFunc = [key, weakFrameNode = AceType::WeakClaim(frameNode),
                          weakTitleBarNode = AceType::WeakClaim(AceType::RawPtr(titleBarNode))](
                          const RefPtr<ResourceObject>& backButtonIconResObj) {
        auto titleBarNode = weakTitleBarNode.Upgrade();
        CHECK_NULL_VOID(titleBarNode);
        auto pattern = titleBarNode->GetPattern<TitleBarPattern>();
        CHECK_NULL_VOID(pattern);
        std::string result = pattern->GetResCacheMapByKey(key);
        if (result.empty()) {
            ResourceParseUtils::ParseResMedia(backButtonIconResObj, result);
            pattern->AddResCache(key, result);
        }
        ImageSourceInfo imageSourceInfo(result);
        auto frameNode = weakFrameNode.Upgrade();
        CHECK_NULL_VOID(frameNode);
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(NavigationLayoutProperty, ImageSource, imageSourceInfo, frameNode);
        auto titleBarLayoutProperty = titleBarNode->GetLayoutProperty<TitleBarLayoutProperty>();
        CHECK_NULL_VOID(titleBarLayoutProperty);
        titleBarLayoutProperty->UpdateImageSource(imageSourceInfo);
        titleBarNode->MarkModifyDone();
        titleBarNode->MarkDirtyNode();
    };
    auto pattern = titleBarNode->GetPattern<TitleBarPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->AddResObj(key, backButtonIconResObj, std::move(updateFunc));
}

void NavigationModelNG::SetHideNavBarInner(
    const RefPtr<NavigationGroupNode>& navigationGroupNode, bool hideNavBar)
{
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
    auto navBarOrHomeDestNode =
        AceType::DynamicCast<NavDestinationNodeBase>(navigationGroupNode->GetNavBarOrHomeDestinationNode());
    if (navBarOrHomeDestNode) {
        navBarOrHomeDestNode->SetJSViewActive(!hideNavBar);
        if (pattern->GetNavBarVisibilityChange()) {
            navBarOrHomeDestNode->MarkDirtyNode();
        }
    }
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(NavigationLayoutProperty, HideNavBar, hideNavBar, navigationGroupNode);
}

void NavigationModelNG::SetHideNavBar(FrameNode* frameNode, bool hideNavBar)
{
    auto navigationGroupNode =
        Referenced::Claim<NavigationGroupNode>(AceType::DynamicCast<NavigationGroupNode>(frameNode));
    CHECK_NULL_VOID(navigationGroupNode);
    SetHideNavBarInner(navigationGroupNode, hideNavBar);
}

void NavigationModelNG::SetEnableModeChangeAnimation(FrameNode* frameNode, bool isEnable)
{
    auto navigationGroupNode = AceType::DynamicCast<NavigationGroupNode>(frameNode);
    CHECK_NULL_VOID(navigationGroupNode);
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(NavigationLayoutProperty, EnableModeChangeAnimation, isEnable, navigationGroupNode);
}

void NavigationModelNG::SetHideTitleBar(FrameNode* frameNode, bool hideTitleBar, bool animated)
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

void NavigationModelNG::SetSplitPlaceholder(FrameNode* frameNode, FrameNode* splitPlaceholder)
{
    CHECK_NULL_VOID(splitPlaceholder);
    CHECK_NULL_VOID(frameNode);
    auto navigationGroupNode = AceType::DynamicCast<NavigationGroupNode>(frameNode);
    CHECK_NULL_VOID(navigationGroupNode);
    if (!navigationGroupNode->GetPlaceholderContentNode()) {
        int32_t placeholderContentNodeId = ElementRegister::GetInstance()->MakeUniqueId();
        auto placeholderContentNode = FrameNode::GetOrCreateFrameNode(V2::SPLIT_PLACEHOLDER_CONTENT_ETS_TAG,
            placeholderContentNodeId, []() { return AceType::MakeRefPtr<Pattern>(); });
        placeholderContentNode->GetLayoutProperty()->UpdateAlignment(Alignment::TOP_LEFT);
        SafeAreaExpandOpts opts = { .type = SAFE_AREA_TYPE_SYSTEM | SAFE_AREA_TYPE_CUTOUT,
            .edges = SAFE_AREA_EDGE_ALL };
        placeholderContentNode->GetLayoutProperty()->UpdateSafeAreaExpandOpts(opts);
        const auto& eventHub = placeholderContentNode->GetEventHub<EventHub>();
        if (eventHub) {
            eventHub->SetEnabled(false);
        }
        auto focusHub = placeholderContentNode->GetOrCreateFocusHub();
        if (focusHub) {
            focusHub->SetFocusable(false);
        }
        auto renderContext = placeholderContentNode->GetRenderContext();
        CHECK_NULL_VOID(renderContext);
        renderContext->SetClipToBounds(true);
        renderContext->UpdateZIndex(-1);
        navigationGroupNode->AddChild(placeholderContentNode);
        navigationGroupNode->SetPlaceholderContentNode(placeholderContentNode);
    }
    auto splitPlaceholderNode = AceType::Claim<UINode>(splitPlaceholder);
    CHECK_NULL_VOID(splitPlaceholderNode);
    navigationGroupNode->SetSplitPlaceholder(splitPlaceholderNode);
}

void NavigationModelNG::ResetSplitPlaceholder(FrameNode* frameNode)
{
    CHECK_NULL_VOID(frameNode);
    auto navigationGroupNode = AceType::DynamicCast<NavigationGroupNode>(frameNode);
    CHECK_NULL_VOID(navigationGroupNode);
    navigationGroupNode->ResetSplitPlaceholder();
}

void NavigationModelNG::SetSubtitle(FrameNode* frameNode, const std::string& subtitle)
{
    CHECK_NULL_VOID(frameNode);
    auto navigationGroupNode = AceType::DynamicCast<NavigationGroupNode>(frameNode);
    CHECK_NULL_VOID(navigationGroupNode);
    auto navBarNode = AceType::DynamicCast<NavBarNode>(navigationGroupNode->GetNavBarNode());
    CHECK_NULL_VOID(navBarNode);
    auto titleBarNode = AceType::DynamicCast<TitleBarNode>(navBarNode->GetTitleBarNode());
    CHECK_NULL_VOID(titleBarNode);
    auto titleBarPattern = titleBarNode->GetPattern<TitleBarPattern>();
    CHECK_NULL_VOID(titleBarPattern);
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
    // create or update subtitle
    auto subTitle = AceType::DynamicCast<FrameNode>(titleBarNode->GetSubtitle());
    if (subTitle) {
        // update subtitle
        auto textLayoutProperty = subTitle->GetLayoutProperty<TextLayoutProperty>();
        textLayoutProperty->UpdateContent(subtitle);
        auto renderContext = subTitle->GetRenderContext();
        renderContext->UpdateOpacity(1.0);
    } else {
        // create and init subtitle
        subTitle = FrameNode::CreateFrameNode(
            V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
        auto textLayoutProperty = subTitle->GetLayoutProperty<TextLayoutProperty>();
        textLayoutProperty->UpdateContent(subtitle);
        titleBarPattern->SetNeedResetSubTitleProperty(true);
        titleBarNode->SetSubtitle(subTitle);
        titleBarNode->AddChild(subTitle);
    }
}

void NavigationModelNG::SetHideBackButton(FrameNode* frameNode, bool hideBackButton)
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

void NavigationModelNG::SetTitleMode(FrameNode* frameNode, NG::NavigationTitleMode mode)
{
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

    if (Container::GreatOrEqualAPIVersion(PlatformVersion::VERSION_TWELVE) &&
        SystemProperties::IsNeedSymbol()) {
        CreateSymbolBackIcon(backButtonNode, navigationGroupNode);
    } else {
        CreateImageBackIcon(backButtonNode, navigationGroupNode);
    }

    //read navigation back button
    auto theme = NavigationGetTheme();
    std::string message = theme ? theme->GetNavigationBack() : "";
    NavigationTitleUtil::SetAccessibility(backButtonNode, message);

    backButtonNode->MarkModifyDone();
    titleBarNode->SetBackButton(backButtonNode);
    titleBarNode->AddChild(backButtonNode, 0);
}

void NavigationModelNG::SetRecoverable(FrameNode* frameNode, bool recoverable)
{
    auto navigationGroupNode = AceType::DynamicCast<NavigationGroupNode>(frameNode);
    CHECK_NULL_VOID(navigationGroupNode);
    navigationGroupNode->SetRecoverable(recoverable);
}

void NavigationModelNG::SetRecoverable(bool recoverable)
{
    auto navigationGroupNode = AceType::DynamicCast<NavigationGroupNode>(
        ViewStackProcessor::GetInstance()->GetMainFrameNode());
    CHECK_NULL_VOID(navigationGroupNode);
    navigationGroupNode->SetRecoverable(recoverable);
}

void NavigationModelNG::SetEnableDragBar(FrameNode* frameNode, bool enableDragBar)
{
    auto navigationGroupNode = AceType::DynamicCast<NavigationGroupNode>(frameNode);
    CHECK_NULL_VOID(navigationGroupNode);
    auto pattern = navigationGroupNode->GetPattern<NavigationPattern>();
    CHECK_NULL_VOID(pattern);
    DeviceType deviceType = SystemProperties::GetDeviceType();
    if (deviceType == DeviceType::TWO_IN_ONE) {
        enableDragBar = false;
    }
    pattern->SetEnableDragBar(enableDragBar);
}

void NavigationModelNG::SetEnableToolBarAdaptation(FrameNode* frameNode, bool enable)
{
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(NavigationLayoutProperty, EnableToolBarAdaptation, enable, frameNode);
}

void NavigationModelNG::SetEnableDragBar(bool enableDragBar)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<NavigationPattern>();
    CHECK_NULL_VOID(pattern);
    DeviceType deviceType = SystemProperties::GetDeviceType();
    if (deviceType == DeviceType::TWO_IN_ONE) {
        enableDragBar = false;
    }
    pattern->SetEnableDragBar(enableDragBar);
}

void NavigationModelNG::SetIsCustomAnimation(bool isCustom)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<NavigationPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetIsCustomAnimation(isCustom);
}

void NavigationModelNG::SetCustomTransition(NavigationTransitionEvent&& customTransition)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<NavigationPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetNavigationTransition(std::move(customTransition));
}

void NavigationModelNG::ResetResObj(NavigationPatternType type, const std::string& key)
{
    if (!SystemProperties::ConfigChangePerform()) {
        return;
    }
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto navigationGroupNode = AceType::DynamicCast<NavigationGroupNode>(frameNode);
    CHECK_NULL_VOID(navigationGroupNode);
    RefPtr<Pattern> pattern = nullptr;
    if (type == NavigationPatternType::NAV_BAR) {
        auto navBarNode = AceType::DynamicCast<NavBarNode>(navigationGroupNode->GetNavBarNode());
        CHECK_NULL_VOID(navBarNode);
        pattern = navBarNode->GetPattern<NavBarPattern>();
    } else if (type == NavigationPatternType::TITLE_BAR) {
        auto navBarNode = AceType::DynamicCast<NavBarNode>(navigationGroupNode->GetNavBarNode());
        CHECK_NULL_VOID(navBarNode);
        auto titleBarNode = AceType::DynamicCast<TitleBarNode>(navBarNode->GetTitleBarNode());
        CHECK_NULL_VOID(titleBarNode);
        pattern = titleBarNode->GetPattern<TitleBarPattern>();
    } else if (type == NavigationPatternType::NAVIGATION) {
        pattern = navigationGroupNode->GetPattern<NavigationPattern>();
    }
    CHECK_NULL_VOID(pattern);
    pattern->RemoveResObj(key);
}

void NavigationModelNG::SetTitlebarOptions(NavigationTitlebarOptions&& opt)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
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
    titleBarPattern->SetTitlebarOptions(opt);
    if (!SystemProperties::ConfigChangePerform()) {
        return;
    }
    RefPtr<ResourceObject> resObj = AceType::MakeRefPtr<ResourceObject>("", "", -1);
    auto updateFunc = [weakFrameNode = AceType::WeakClaim(frameNode),
                          weakTitleBarPattern = AceType::WeakClaim(AceType::RawPtr(titleBarPattern)),
                          opt](const RefPtr<ResourceObject>& resObj) mutable {
        opt.bgOptions.ReloadResources();
        if (opt.bgOptions.blurStyleOption.has_value()) {
            opt.bgOptions.blurStyleOption->ReloadResources();
        }
        if (opt.bgOptions.effectOption.has_value()) {
            opt.bgOptions.effectOption->ReloadResources();
        }
        auto titleBarPattern = weakTitleBarPattern.Upgrade();
        CHECK_NULL_VOID(titleBarPattern);

        titleBarPattern->SetTitlebarOptions(opt);
        auto frameNode = weakFrameNode.Upgrade();
        auto navigationGroupNode = AceType::DynamicCast<NavigationGroupNode>(frameNode);
        CHECK_NULL_VOID(navigationGroupNode);
        navigationGroupNode->MarkModifyDone();
        navigationGroupNode->MarkDirtyNode();
    };
    auto pattern = navigationGroupNode->GetPattern();
    CHECK_NULL_VOID(pattern);
    pattern->AddResObj("navigation.navigationTitlebarOptions", resObj, std::move(updateFunc));
}

void NavigationModelNG::SetHideItemText(bool isHideItemText)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    auto navigationGroupNode = AceType::DynamicCast<NavigationGroupNode>(frameNode);
    CHECK_NULL_VOID(navigationGroupNode);
    auto navBarNode = AceType::DynamicCast<NavBarNode>(navigationGroupNode->GetNavBarNode());
    NavigationToolbarUtil::SetHideItemText(navBarNode, isHideItemText);
}

void NavigationModelNG::SetToolbarOptions(NavigationToolbarOptions&& opt)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    auto navigationGroupNode = AceType::DynamicCast<NavigationGroupNode>(frameNode);
    CHECK_NULL_VOID(navigationGroupNode);
    auto navBarNode = AceType::DynamicCast<NavBarNode>(navigationGroupNode->GetNavBarNode());
    NavigationToolbarUtil::SetToolbarOptions(navBarNode, std::move(opt));
}

void NavigationModelNG::SetToolbarMorebuttonOptions(MoreButtonOptions&& opt)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto navigationGroupNode = AceType::DynamicCast<NavigationGroupNode>(frameNode);
    CHECK_NULL_VOID(navigationGroupNode);
    auto navBarNode = AceType::DynamicCast<NavBarNode>(navigationGroupNode->GetNavBarNode());
    CHECK_NULL_VOID(navBarNode);
    NavigationToolbarUtil::SetToolbarMoreButtonOptions(navBarNode, std::move(opt));
}

void NavigationModelNG::SetMenuOptions(NavigationMenuOptions&& opt)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto navigationGroupNode = AceType::DynamicCast<NavigationGroupNode>(frameNode);
    CHECK_NULL_VOID(navigationGroupNode);
    auto navBarNode = AceType::DynamicCast<NavBarNode>(navigationGroupNode->GetNavBarNode());
    CHECK_NULL_VOID(navBarNode);
    auto navBarPattern = navBarNode->GetPattern<NavBarPattern>();
    CHECK_NULL_VOID(navBarPattern);
    navBarPattern->SetMenuOptions(opt);
    if (!SystemProperties::ConfigChangePerform()) {
        return;
    }
    RefPtr<ResourceObject> resObj = AceType::MakeRefPtr<ResourceObject>("", "", -1);
    auto updateFunc = [weakFrameNode = AceType::WeakClaim(frameNode),
                          weakNavBarPattern = AceType::WeakClaim(AceType::RawPtr(navBarPattern)),
                          opt](const RefPtr<ResourceObject>& resObj) mutable {
        opt.mbOptions.bgOptions.ReloadResources();
        if (opt.mbOptions.bgOptions.blurStyleOption.has_value()) {
            opt.mbOptions.bgOptions.blurStyleOption->ReloadResources();
        }
        if (opt.mbOptions.bgOptions.effectOption.has_value()) {
            opt.mbOptions.bgOptions.effectOption->ReloadResources();
        }
        auto navBarPattern = weakNavBarPattern.Upgrade();
        CHECK_NULL_VOID(navBarPattern);

        navBarPattern->SetMenuOptions(opt);
        auto frameNode = weakFrameNode.Upgrade();
        auto navigationGroupNode = AceType::DynamicCast<NavigationGroupNode>(frameNode);
        CHECK_NULL_VOID(navigationGroupNode);
        navigationGroupNode->MarkModifyDone();
        navigationGroupNode->MarkDirtyNode();
    };
    navBarPattern->AddResObj("navigation.navigationMenuOptions", resObj, std::move(updateFunc));
}

void NavigationModelNG::SetIgnoreLayoutSafeArea(const NG::IgnoreLayoutSafeAreaOpts& opts)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    auto navigationGroupNode = AceType::DynamicCast<NavigationGroupNode>(frameNode);
    CHECK_NULL_VOID(navigationGroupNode);
    auto navBarNode = AceType::DynamicCast<NavBarNode>(navigationGroupNode->GetNavBarNode());
    CHECK_NULL_VOID(navBarNode);
    auto navBarLayoutProperty = navBarNode->GetLayoutProperty<NavBarLayoutProperty>();
    CHECK_NULL_VOID(navBarLayoutProperty);
    navBarLayoutProperty->UpdateIgnoreLayoutSafeAreaOpts(opts);
    auto content = AceType::DynamicCast<FrameNode>(navBarNode->GetContentNode());
    CHECK_NULL_VOID(content);
    auto contentLayoutProperty = content->GetLayoutProperty();
    CHECK_NULL_VOID(contentLayoutProperty);
    contentLayoutProperty->UpdateIgnoreLayoutSafeAreaOpts(opts);
}

void NavigationModelNG::SetIgnoreLayoutSafeArea(FrameNode* frameNode, const NG::IgnoreLayoutSafeAreaOpts& opts)
{
    auto navigationGroupNode = AceType::DynamicCast<NavigationGroupNode>(frameNode);
    CHECK_NULL_VOID(navigationGroupNode);
    auto navBarNode = AceType::DynamicCast<NavBarNode>(navigationGroupNode->GetNavBarNode());
    CHECK_NULL_VOID(navBarNode);
    auto navBarLayoutProperty = navBarNode->GetLayoutProperty<NavBarLayoutProperty>();
    CHECK_NULL_VOID(navBarLayoutProperty);
    navBarLayoutProperty->UpdateIgnoreLayoutSafeAreaOpts(opts);
    auto content = AceType::DynamicCast<FrameNode>(navBarNode->GetContentNode());
    CHECK_NULL_VOID(content);
    auto contentLayoutProperty = content->GetLayoutProperty();
    CHECK_NULL_VOID(contentLayoutProperty);
    contentLayoutProperty->UpdateIgnoreLayoutSafeAreaOpts(opts);
}

void NavigationModelNG::SetSystemBarStyle(const RefPtr<SystemBarStyle>& style)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    auto navigationGroupNode = AceType::DynamicCast<NavigationGroupNode>(frameNode);
    CHECK_NULL_VOID(navigationGroupNode);
    auto pattern = navigationGroupNode->GetPattern<NavigationPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetSystemBarStyle(style);
}

RefPtr<FrameNode> NavigationModelNG::CreateFrameNode(int32_t nodeId)
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
    SetNavigationStack(AceType::RawPtr(navigationGroupNode));

    return navigationGroupNode;
}

void NavigationModelNG::SetNavigationStack(FrameNode* frameNode)
{
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<NavigationPattern>();
    CHECK_NULL_VOID(pattern);
    auto navigationStack = pattern->GetNavigationStack();
    if (!navigationStack) {
        auto navigationStack = AceType::MakeRefPtr<NavigationStack>();
        pattern->SetNavigationStack(std::move(navigationStack));
    }
}

void NavigationModelNG::ParseCommonTitle(FrameNode* frameNode, const NG::NavigationTitleInfo& titleInfo,
    bool ignoreMainTitle)
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

void NavigationModelNG::ParseCommonTitle(
    FrameNode* frameNode, const RefPtr<ResourceObject>& titleResObj, const RefPtr<ResourceObject>& subtitleResObj)
{
    CHECK_NULL_VOID(frameNode);
    auto navigationGroupNode = AceType::DynamicCast<NavigationGroupNode>(frameNode);
    CHECK_NULL_VOID(navigationGroupNode);
    auto navBarNode = AceType::DynamicCast<NavBarNode>(navigationGroupNode->GetNavBarNode());
    CHECK_NULL_VOID(navBarNode);
    auto titleBarNode = AceType::DynamicCast<TitleBarNode>(navBarNode->GetTitleBarNode());
    CHECK_NULL_VOID(titleBarNode);
    std::string subtitle = "";
    std::string title = "";
    bool hasSubTitle = false;
    bool hasMainTitle = false;

    if (subtitleResObj) {
        hasSubTitle = ResourceParseUtils::ParseResString(subtitleResObj, subtitle);
    }
    hasMainTitle = ResourceParseUtils::ParseResString(titleResObj, title);
    if (!hasSubTitle && !hasMainTitle) {
        return;
    }
    NG::NavigationTitleInfo ngTitleInfo = { hasSubTitle, hasMainTitle, subtitle, title };
    ParseCommonTitle(frameNode, ngTitleInfo);
    UpdateMainTitleInfo(titleBarNode, titleResObj);
    if (subtitleResObj) {
        UpdateSubTitleInfo(titleBarNode, subtitleResObj);
    }
    return;
}

void NavigationModelNG::UpdateMainTitleInfo(
    const RefPtr<NG::TitleBarNode>& titleBarNode, const RefPtr<ResourceObject>& mainResObj)
{
    CHECK_NULL_VOID(titleBarNode);
    std::string key = "navigation.title.commonMainTitle";
    auto updateFunc = [key, weak = AceType::WeakClaim(AceType::RawPtr(titleBarNode))](
                          const RefPtr<ResourceObject>& mainResObj) mutable {
        auto titleBarNode = weak.Upgrade();
        CHECK_NULL_VOID(titleBarNode);
        auto titleBarPattern = titleBarNode->GetPattern<TitleBarPattern>();
        CHECK_NULL_VOID(titleBarPattern);
        std::string title = titleBarPattern->GetResCacheMapByKey(key);
        if (title.empty()) {
            ResourceParseUtils::ParseResString(mainResObj, title);
            titleBarPattern->AddResCache(key, title);
        }
        auto mainTitle = AceType::DynamicCast<FrameNode>(titleBarNode->GetTitle());
        if (mainTitle) {
            auto textLayoutProperty = mainTitle->GetLayoutProperty<NG::TextLayoutProperty>();
            textLayoutProperty->UpdateContent(title);
            titleBarNode->MarkModifyDone();
            titleBarNode->MarkDirtyNode();
        }
    };
    auto titleBarPattern = titleBarNode->GetPattern<TitleBarPattern>();
    CHECK_NULL_VOID(titleBarPattern);
    titleBarPattern->AddResObj(key, mainResObj, std::move(updateFunc));
}

void NavigationModelNG::UpdateSubTitleInfo(
    const RefPtr<NG::TitleBarNode>& titleBarNode, const RefPtr<ResourceObject>& resObj)
{
    CHECK_NULL_VOID(titleBarNode);
    std::string key = "navigation.title.commonSubTitle";
    auto updateFunc = [key, weak = AceType::WeakClaim(AceType::RawPtr(titleBarNode))](
                          const RefPtr<ResourceObject>& resObj) {
        auto titleBarNode = weak.Upgrade();
        CHECK_NULL_VOID(titleBarNode);
        auto titleBarPattern = titleBarNode->GetPattern<TitleBarPattern>();
        CHECK_NULL_VOID(titleBarPattern);
        std::string subTitleValue = titleBarPattern->GetResCacheMapByKey(key);
        if (subTitleValue.empty()) {
            ResourceParseUtils::ParseResString(resObj, subTitleValue);
            titleBarPattern->AddResCache(key, subTitleValue);
        }
        auto subTitleNode = AceType::DynamicCast<FrameNode>(titleBarNode->GetSubtitle());
        if (subTitleNode) {
            auto textLayoutProperty = subTitleNode->GetLayoutProperty<TextLayoutProperty>();
            textLayoutProperty->UpdateContent(subTitleValue);
            titleBarNode->MarkModifyDone();
            titleBarNode->MarkDirtyNode();
        }
    };
    auto titleBarPattern = titleBarNode->GetPattern<TitleBarPattern>();
    CHECK_NULL_VOID(titleBarPattern);
    titleBarPattern->AddResObj(key, resObj, std::move(updateFunc));
}

void NavigationModelNG::SetTitlebarOptions(FrameNode* frameNode, NavigationTitlebarOptions&& opt)
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
    titleBarPattern->SetTitlebarOptions(opt);
}

void NavigationModelNG::SetMenuItems(FrameNode* frameNode, std::vector<NG::BarItem>&& menuItems)
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

void NavigationModelNG::SetMenuItemAction(FrameNode* frameNode, std::function<void()>&& action, uint32_t index)
{
    CHECK_NULL_VOID(action);
    auto navigationGroupNode = AceType::DynamicCast<NavigationGroupNode>(frameNode);
    CHECK_NULL_VOID(navigationGroupNode);
    auto navBarNode = AceType::DynamicCast<NavBarNode>(navigationGroupNode->GetNavBarNode());
    CHECK_NULL_VOID(navBarNode);
    auto navBarPattern = navBarNode->GetPattern<NavBarPattern>();
    CHECK_NULL_VOID(navBarPattern);
    auto menuItems = navBarPattern->GetTitleBarMenuItems();
    if (menuItems.size() > index) {
        menuItems.at(index).action = action;
        navBarPattern->SetTitleBarMenuItems(menuItems);
    }
}

void NavigationModelNG::SetMenuItemSymbol(FrameNode* frameNode,
    std::function<void(WeakPtr<NG::FrameNode>)>&& symbol, uint32_t index)
{
    CHECK_NULL_VOID(symbol);
    auto navigationGroupNode = AceType::DynamicCast<NavigationGroupNode>(frameNode);
    CHECK_NULL_VOID(navigationGroupNode);
    auto navBarNode = AceType::DynamicCast<NavBarNode>(navigationGroupNode->GetNavBarNode());
    CHECK_NULL_VOID(navBarNode);
    auto navBarPattern = navBarNode->GetPattern<NavBarPattern>();
    CHECK_NULL_VOID(navBarPattern);
    auto menuItems = navBarPattern->GetTitleBarMenuItems();
    if (menuItems.size() > index) {
        menuItems.at(index).iconSymbol = symbol;
        navBarPattern->SetTitleBarMenuItems(menuItems);
    }
}

void NavigationModelNG::SetCustomTitle(FrameNode* frameNode, const RefPtr<AceType>& customNode)
{
    auto customTitle = AceType::DynamicCast<NG::UINode>(customNode);
    CHECK_NULL_VOID(customTitle);
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
    if (currentTitle && customTitle->GetId() == currentTitle->GetId()) {
        // do nothing
        return;
    }
    // update custom title
    titleBarNode->RemoveChild(currentTitle);
    titleBarNode->SetTitle(customTitle);
    titleBarNode->AddChild(customTitle);
    titleBarNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
}

RefPtr<FrameNode> NavigationModelNG::GetCustomTitle(FrameNode* frameNode)
{
    auto navigationGroupNode = AceType::DynamicCast<NavigationGroupNode>(frameNode);
    CHECK_NULL_RETURN(navigationGroupNode, nullptr);
    auto navBarNode = AceType::DynamicCast<NavBarNode>(navigationGroupNode->GetNavBarNode());
    CHECK_NULL_RETURN(navBarNode, nullptr);
    navBarNode->UpdatePrevTitleIsCustom(true);
    auto titleBarNode = AceType::DynamicCast<TitleBarNode>(navBarNode->GetTitleBarNode());
    CHECK_NULL_RETURN(titleBarNode, nullptr);
    auto title = AceType::DynamicCast<FrameNode>(titleBarNode->GetTitle());
    return title;
}

void NavigationModelNG::SetTitleHeight(FrameNode* frameNode, const Dimension& height, bool isValid)
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

void NavigationModelNG::SetOnCoordScrollStartAction(FrameNode* frameNode, std::function<void()>&& onCoordScrollStart)
{
    auto navigationGroupNode = AceType::DynamicCast<NavigationGroupNode>(frameNode);
    CHECK_NULL_VOID(navigationGroupNode);
    auto navBarNode = AceType::DynamicCast<NavBarNode>(navigationGroupNode->GetNavBarNode());
    CHECK_NULL_VOID(navBarNode);
    auto navBarPattern = navBarNode->GetPattern<NavBarPattern>();
    CHECK_NULL_VOID(navBarPattern);
    auto navBarEventHub = navBarPattern->GetEventHub<NavBarEventHub>();
    CHECK_NULL_VOID(navBarEventHub);
    navBarEventHub->SetOnCoordScrollStartAction(std::move(onCoordScrollStart));
}

void NavigationModelNG::SetOnCoordScrollUpdateAction(
    FrameNode* frameNode, std::function<void(float, float)>&& onCoordScrollUpdate)
{
    auto navigationGroupNode = AceType::DynamicCast<NavigationGroupNode>(frameNode);
    CHECK_NULL_VOID(navigationGroupNode);
    auto navBarNode = AceType::DynamicCast<NavBarNode>(navigationGroupNode->GetNavBarNode());
    CHECK_NULL_VOID(navBarNode);
    auto navBarPattern = navBarNode->GetPattern<NavBarPattern>();
    CHECK_NULL_VOID(navBarPattern);
    auto navBarEventHub = navBarPattern->GetEventHub<NavBarEventHub>();
    CHECK_NULL_VOID(navBarEventHub);
    navBarEventHub->SetOnCoordScrollUpdateAction(std::move(onCoordScrollUpdate));
}

void NavigationModelNG::SetOnCoordScrollEndAction(FrameNode* frameNode, std::function<void()>&& onCoordScrollEnd)
{
    auto navigationGroupNode = AceType::DynamicCast<NavigationGroupNode>(frameNode);
    CHECK_NULL_VOID(navigationGroupNode);
    auto navBarNode = AceType::DynamicCast<NavBarNode>(navigationGroupNode->GetNavBarNode());
    CHECK_NULL_VOID(navBarNode);
    auto navBarPattern = navBarNode->GetPattern<NavBarPattern>();
    CHECK_NULL_VOID(navBarPattern);
    auto navBarEventHub = navBarPattern->GetEventHub<NavBarEventHub>();
    CHECK_NULL_VOID(navBarEventHub);
    navBarEventHub->SetOnCoordScrollEndAction(std::move(onCoordScrollEnd));
}

void NavigationModelNG::SetSystemBarStyle(FrameNode* frameNode, const RefPtr<SystemBarStyle>& style)
{
    CHECK_NULL_VOID(frameNode);
    auto navigationGroupNode = AceType::DynamicCast<NavigationGroupNode>(frameNode);
    CHECK_NULL_VOID(navigationGroupNode);
    auto pattern = navigationGroupNode->GetPattern<NavigationPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetSystemBarStyle(style);
}

bool NavigationModelNG::IsDoubleBindBlock(const RefPtr<NavigationPattern>& navigationPattern)
{
    return navBarWidthDoubleBind_ && navigationPattern->GetIsInDividerDrag();
}

void NavigationModelNG::SetIsCustomTitleBarSize(FrameNode* frameNode, bool isCustom)
{
    auto navigationGroupNode = AceType::DynamicCast<NavigationGroupNode>(frameNode);
    CHECK_NULL_VOID(navigationGroupNode);
    auto navBarNode = AceType::DynamicCast<NavBarNode>(navigationGroupNode->GetNavBarNode());
    CHECK_NULL_VOID(navBarNode);
    auto titleBarNode = AceType::DynamicCast<TitleBarNode>(navBarNode->GetTitleBarNode());
    CHECK_NULL_VOID(titleBarNode);
    auto titleBarLayoutProperty = titleBarNode->GetLayoutProperty<TitleBarLayoutProperty>();
    CHECK_NULL_VOID(titleBarLayoutProperty);
    titleBarLayoutProperty->UpdateIsCustomTitleBarSize(isCustom);
}

void NavigationModelNG::SetBeforeCreateLayoutWrapperCallBack(
    FrameNode* frameNode, std::function<void()>&& beforeCreateLayoutWrapper)
{
    CHECK_NULL_VOID(beforeCreateLayoutWrapper);
    auto navigationGroupNode = AceType::DynamicCast<NavigationGroupNode>(frameNode);
    CHECK_NULL_VOID(navigationGroupNode);
    auto navBarNode = AceType::DynamicCast<NavBarNode>(navigationGroupNode->GetNavBarNode());
    CHECK_NULL_VOID(navBarNode);
    auto navBarPattern = navBarNode->GetPattern<NavBarPattern>();
    CHECK_NULL_VOID(navBarPattern);
    auto navBarEventHub = navBarPattern->GetEventHub<NavBarEventHub>();
    CHECK_NULL_VOID(navBarEventHub);
    navBarEventHub->SetBeforeCreateLayoutWrapperCallBack(std::move(beforeCreateLayoutWrapper));
}

void NavigationModelNG::SetEnableShowHideWithContentCover(bool isEnable)
{
    NavigationModelNG::SetEnableShowHideWithContentCover(
        ViewStackProcessor::GetInstance()->GetMainFrameNode(), isEnable);
}

void NavigationModelNG::SetEnableShowHideWithContentCover(FrameNode* frameNode, bool isEnable)
{
    auto navigation = AceType::DynamicCast<NavigationGroupNode>(frameNode);
    CHECK_NULL_VOID(navigation);
    auto pattern = navigation->GetPattern<NavigationPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetEnableShowHideWithContentCover(isEnable);
}
} // namespace OHOS::Ace::NG
