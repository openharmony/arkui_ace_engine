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

#include "core/components_ng/pattern/navigation/nav_bar_pattern.h"

#include <algorithm>
#include <cmath>
#include <cstdint>

#include "base/geometry/dimension.h"
#include "base/i18n/localization.h"
#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"
#include "base/utils/utils.h"
#include "core/components/common/layout/constants.h"
#include "core/components/common/layout/grid_system_manager.h"
#include "core/components_ng/base/view_abstract.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/bubble/bubble_pattern.h"
#include "core/components_ng/pattern/bubble/bubble_view.h"
#include "core/components_ng/pattern/button/button_layout_property.h"
#include "core/components_ng/pattern/button/button_pattern.h"
#include "core/components_ng/pattern/grid/grid_pattern.h"
#include "core/components_ng/pattern/image/image_layout_property.h"
#include "core/components_ng/pattern/image/image_pattern.h"
#include "core/components_ng/pattern/linear_layout/linear_layout_pattern.h"
#include "core/components_ng/pattern/list/list_pattern.h"
#include "core/components_ng/pattern/menu/menu_view.h"
#include "core/components_ng/pattern/navigation/bar_item_event_hub.h"
#include "core/components_ng/pattern/navigation/bar_item_node.h"
#include "core/components_ng/pattern/navigation/bar_item_pattern.h"
#include "core/components_ng/pattern/navigation/nav_bar_layout_property.h"
#include "core/components_ng/pattern/navigation/navigation_declaration.h"
#include "core/components_ng/pattern/navigation/navigation_pattern.h"
#include "core/components_ng/pattern/navigation/title_bar_layout_property.h"
#include "core/components_ng/pattern/navigation/title_bar_node.h"
#include "core/components_ng/pattern/navigation/title_bar_pattern.h"
#include "core/components_ng/pattern/option/option_view.h"
#include "core/components_ng/pattern/scrollable/scrollable_pattern.h"
#include "core/components_ng/pattern/text/text_layout_property.h"
#include "core/components_ng/pattern/text/text_pattern.h"
#include "core/components_ng/property/property.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "core/event/touch_event.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {
namespace {

void UpdateTitleFontSize(const RefPtr<NavBarNode>& hostNode, const Dimension& fontSize)
{
    auto navBarLayoutProperty = hostNode->GetLayoutProperty<NavBarLayoutProperty>();
    CHECK_NULL_VOID(navBarLayoutProperty);
    auto titleNode = AceType::DynamicCast<FrameNode>(hostNode->GetTitle());
    CHECK_NULL_VOID(titleNode);
    auto titleLayoutProperty = titleNode->GetLayoutProperty<TextLayoutProperty>();
    CHECK_NULL_VOID_NOLOG(titleLayoutProperty);
    titleLayoutProperty->UpdateFontSize(fontSize);
    titleNode->MarkModifyDone();
}

RefPtr<FrameNode> CreateBarItemTextNode(const std::string& text)
{
    int32_t nodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto textNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, nodeId, AceType::MakeRefPtr<TextPattern>());
    auto textLayoutProperty = textNode->GetLayoutProperty<TextLayoutProperty>();
    CHECK_NULL_RETURN(textLayoutProperty, nullptr);
    textLayoutProperty->UpdateContent(text);
    textLayoutProperty->UpdateFontSize(TEXT_FONT_SIZE);
    textLayoutProperty->UpdateTextColor(TEXT_COLOR);
    textLayoutProperty->UpdateTextAlign(TextAlign::CENTER);
    return textNode;
}

RefPtr<FrameNode> CreateBarItemIconNode(const std::string& src, const bool isButtonEnabled)
{
    int32_t nodeId = ElementRegister::GetInstance()->MakeUniqueId();
    ImageSourceInfo info(src);
    auto iconNode = FrameNode::CreateFrameNode(V2::IMAGE_ETS_TAG, nodeId, AceType::MakeRefPtr<ImagePattern>());
    auto imageLayoutProperty = iconNode->GetLayoutProperty<ImageLayoutProperty>();
    CHECK_NULL_RETURN(imageLayoutProperty, nullptr);
    auto theme = NavigationGetTheme();
    CHECK_NULL_RETURN(theme, nullptr);

    if (isButtonEnabled) {
        info.SetFillColor(theme->GetMenuIconColor());
    } else {
        info.SetFillColor(theme->GetMenuIconColor().BlendOpacity(theme->GetAlphaDisabled()));
    }

    imageLayoutProperty->UpdateImageSourceInfo(info);

    auto iconSize = theme->GetMenuIconSize();
    imageLayoutProperty->UpdateUserDefinedIdealSize(CalcSize(CalcLength(iconSize), CalcLength(iconSize)));
    iconNode->MarkModifyDone();
    return iconNode;
}

void InitTitleBarButtonEvent(const RefPtr<FrameNode>& buttonNode, bool isMoreButton, const BarItem menuItem = BarItem())
{
    auto eventHub = buttonNode->GetOrCreateInputEventHub();
    CHECK_NULL_VOID(eventHub);

    if (isMoreButton) {
        auto hoverTask = [weakTargetNode = WeakPtr<FrameNode>(buttonNode)](bool isHover) {
            auto targetNode = weakTargetNode.Upgrade();
            CHECK_NULL_VOID(targetNode);
            auto popupParam = AceType::MakeRefPtr<PopupParam>();
            popupParam->SetMessage(Localization::GetInstance()->GetEntryLetters("common.more"));
            popupParam->SetIsShow(isHover);
            popupParam->SetBlockEvent(false);
            ViewAbstract::BindPopup(popupParam, targetNode, nullptr);
        };
        eventHub->AddOnHoverEvent(AceType::MakeRefPtr<InputEvent>(std::move(hoverTask)));
        return;
    }

    if (menuItem.action) {
        auto gestureEventHub = buttonNode->GetOrCreateGestureEventHub();
        CHECK_NULL_VOID(gestureEventHub);
        auto clickCallback = [action = menuItem.action](GestureEvent& info) {
            if (info.GetSourceDevice() == SourceType::KEYBOARD) {
                return;
            }
            action();
        };
        gestureEventHub->AddClickEvent(AceType::MakeRefPtr<ClickEvent>(clickCallback));
    }
}

void UpdateBarItemNodeWithItem(
    const RefPtr<BarItemNode>& barItemNode, const BarItem& barItem, const bool isButtonEnabled)
{
    if (PipelineContext::GetCurrentContext()->GetMinPlatformVersion() <
            static_cast<int32_t>(PlatformVersion::VERSION_TEN) &&
        barItem.text.has_value() && !barItem.text.value().empty()) {
        auto textNode = CreateBarItemTextNode(barItem.text.value());
        barItemNode->SetTextNode(textNode);
        barItemNode->AddChild(textNode);
    }
    if (barItem.icon.has_value() && !barItem.icon.value().empty()) {
        auto iconNode = CreateBarItemIconNode(barItem.icon.value(), isButtonEnabled);
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

void BuildMoreIemNode(const RefPtr<BarItemNode>& barItemNode, const bool isButtonEnabled)
{
    int32_t imageNodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto imageNode = FrameNode::CreateFrameNode(V2::IMAGE_ETS_TAG, imageNodeId, AceType::MakeRefPtr<ImagePattern>());
    auto imageLayoutProperty = imageNode->GetLayoutProperty<ImageLayoutProperty>();
    CHECK_NULL_VOID(imageLayoutProperty);
    auto theme = NavigationGetTheme();
    CHECK_NULL_VOID(theme);

    auto info = ImageSourceInfo("");
    info.SetResourceId(theme->GetMoreResourceId());
    if (isButtonEnabled) {
        info.SetFillColor(theme->GetMenuIconColor());
    } else {
        info.SetFillColor(theme->GetMenuIconColor().BlendOpacity(theme->GetAlphaDisabled()));
    }

    imageLayoutProperty->UpdateImageSourceInfo(info);
    auto iconSize = theme->GetMenuIconSize();
    imageLayoutProperty->UpdateUserDefinedIdealSize(CalcSize(CalcLength(iconSize), CalcLength(iconSize)));
    imageNode->MarkModifyDone();

    barItemNode->SetIsMoreItemNode(true);
    barItemNode->SetIconNode(imageNode);
    barItemNode->AddChild(imageNode);
    barItemNode->MarkModifyDone();
}

void BuildMoreItemNodeAction(
    const RefPtr<FrameNode>& buttonNode, const RefPtr<BarItemNode>& barItemNode, const RefPtr<FrameNode>& barMenuNode)
{
    auto eventHub = barItemNode->GetEventHub<BarItemEventHub>();
    CHECK_NULL_VOID(eventHub);

    auto context = PipelineContext::GetCurrentContext();
    auto clickCallback = [weakContext = WeakPtr<PipelineContext>(context), id = barItemNode->GetId(),
                             weakMenu = WeakPtr<FrameNode>(barMenuNode),
                             weakBarItemNode = WeakPtr<BarItemNode>(barItemNode)]() {
        auto context = weakContext.Upgrade();
        CHECK_NULL_VOID(context);

        auto overlayManager = context->GetOverlayManager();
        CHECK_NULL_VOID(overlayManager);

        auto menu = weakMenu.Upgrade();
        CHECK_NULL_VOID(menu);

        auto barItemNode = weakBarItemNode.Upgrade();
        CHECK_NULL_VOID(barItemNode);

        auto imageNode = barItemNode->GetChildAtIndex(0);
        CHECK_NULL_VOID(imageNode);

        auto imageFrameNode = AceType::DynamicCast<FrameNode>(imageNode);
        CHECK_NULL_VOID(imageFrameNode);
        auto imgOffset = imageFrameNode->GetOffsetRelativeToWindow();
        auto imageSize = imageFrameNode->GetGeometryNode()->GetFrameSize();

        auto menuNode = AceType::DynamicCast<FrameNode>(menu->GetChildAtIndex(0));
        CHECK_NULL_VOID(menuNode);
        auto menuLayoutProperty = menuNode->GetLayoutProperty<MenuLayoutProperty>();
        CHECK_NULL_VOID(menuLayoutProperty);
        menuLayoutProperty->UpdateTargetSize(imageSize);
        auto menuPattern = menuNode->GetPattern<MenuPattern>();
        CHECK_NULL_VOID(menuPattern);
        // navigation menu show like select.
        menuPattern->SetIsSelectMenu(true);

        imgOffset.SetX(imgOffset.GetX());
        imgOffset.SetY(imgOffset.GetY() + imageSize.Height());
        overlayManager->ShowMenu(id, imgOffset, menu);

        barItemNode->SetIsTitleMenuNodeShowing(true);
        auto hidMenuCallback = [weakBarItemNode = WeakPtr<BarItemNode>(barItemNode)]() {
            auto barItemNode = weakBarItemNode.Upgrade();
            CHECK_NULL_VOID(barItemNode);
            barItemNode->SetIsTitleMenuNodeShowing(false);
        };
        overlayManager->RegisterOnHideMenu(hidMenuCallback);
    };
    eventHub->SetItemAction(clickCallback);

    auto gestureEventHub = buttonNode->GetOrCreateGestureEventHub();
    CHECK_NULL_VOID(gestureEventHub);
    auto callback = [action = clickCallback](GestureEvent& info) {
        if (info.GetSourceDevice() == SourceType::KEYBOARD) {
            return;
        }
        action();
    };
    gestureEventHub->AddClickEvent(AceType::MakeRefPtr<ClickEvent>(callback));
}

RefPtr<FrameNode> CreateMenuItems(const int32_t menuNodeId, const std::vector<NG::BarItem>& menuItems,
    RefPtr<NavBarNode> navBarNode, bool isCreateLandscapeMenu)
{
    auto menuNode = FrameNode::GetOrCreateFrameNode(
        V2::NAVIGATION_MENU_ETS_TAG, menuNodeId, []() { return AceType::MakeRefPtr<LinearLayoutPattern>(false); });
    CHECK_NULL_RETURN(menuNode, nullptr);
    menuNode->Clean();
    auto rowProperty = menuNode->GetLayoutProperty<LinearLayoutProperty>();
    CHECK_NULL_RETURN(rowProperty, nullptr);
    rowProperty->UpdateMainAxisAlign(FlexAlign::SPACE_BETWEEN);
    auto theme = NavigationGetTheme();
    auto mostMenuItemCount = theme->GetMostMenuItemCountInBar();
    bool needMoreButton = menuItems.size() > mostMenuItemCount ? true : false;

    auto frameNode = navBarNode->GetParent();
    auto navigationGroupNode = AceType::DynamicCast<NavigationGroupNode>(frameNode);
    CHECK_NULL_RETURN(navigationGroupNode, nullptr);
    auto hub = navigationGroupNode->GetEventHub<EventHub>();
    CHECK_NULL_RETURN(hub, nullptr);
    auto isButtonEnabled = hub->IsEnabled();

    uint32_t count = 0;
    std::vector<OptionParam> params;
    for (const auto& menuItem : menuItems) {
        ++count;
        if (needMoreButton && (count > mostMenuItemCount - 1)) {
            params.push_back({ menuItem.text.value_or(""), menuItem.icon.value_or(""), menuItem.action });
        } else {
            auto buttonPattern = AceType::MakeRefPtr<NG::ButtonPattern>();
            CHECK_NULL_RETURN(buttonPattern, nullptr);
            buttonPattern->setComponentButtonType(ComponentButtonType::NAVIGATION);
            buttonPattern->SetFocusBorderColor(theme->GetToolBarItemFocusColor());
            buttonPattern->SetFocusBorderWidth(theme->GetToolBarItemFocusBorderWidth());
            auto menuItemNode = FrameNode::CreateFrameNode(
                V2::MENU_ITEM_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), buttonPattern);
            CHECK_NULL_RETURN(menuItemNode, nullptr);
            auto menuItemLayoutProperty = menuItemNode->GetLayoutProperty<ButtonLayoutProperty>();
            CHECK_NULL_RETURN(menuItemLayoutProperty, nullptr);
            menuItemLayoutProperty->UpdateUserDefinedIdealSize(
                CalcSize(CalcLength(BACK_BUTTON_SIZE.ConvertToPx()), CalcLength(BACK_BUTTON_SIZE.ConvertToPx())));
            menuItemLayoutProperty->UpdateType(ButtonType::NORMAL);
            menuItemLayoutProperty->UpdateBorderRadius(BorderRadiusProperty(BUTTON_RADIUS));
            auto renderContext = menuItemNode->GetRenderContext();
            CHECK_NULL_RETURN(renderContext, nullptr);
            renderContext->UpdateBackgroundColor(Color::TRANSPARENT);
            InitTitleBarButtonEvent(menuItemNode, false, menuItem);

            PaddingProperty padding;
            padding.left = CalcLength(BUTTON_PADDING.ConvertToPx());
            padding.right = CalcLength(BUTTON_PADDING.ConvertToPx());
            padding.top = CalcLength(BUTTON_PADDING.ConvertToPx());
            padding.bottom = CalcLength(BUTTON_PADDING.ConvertToPx());
            menuItemLayoutProperty->UpdatePadding(padding);

            int32_t barItemNodeId = ElementRegister::GetInstance()->MakeUniqueId();
            auto barItemNode = AceType::MakeRefPtr<BarItemNode>(V2::BAR_ITEM_ETS_TAG, barItemNodeId);
            barItemNode->InitializePatternAndContext();
            UpdateBarItemNodeWithItem(barItemNode, menuItem, isButtonEnabled);
            auto barItemLayoutProperty = barItemNode->GetLayoutProperty();
            CHECK_NULL_RETURN(barItemLayoutProperty, nullptr);
            barItemLayoutProperty->UpdateMeasureType(MeasureType::MATCH_PARENT);

            barItemNode->MountToParent(menuItemNode);
            barItemNode->MarkModifyDone();
            menuItemNode->MarkModifyDone();
            menuNode->AddChild(menuItemNode);
        }
    }

    // build more button
    if (needMoreButton) {
        int32_t barItemNodeId = ElementRegister::GetInstance()->MakeUniqueId();
        auto barItemNode = AceType::MakeRefPtr<BarItemNode>(V2::BAR_ITEM_ETS_TAG, barItemNodeId);
        barItemNode->InitializePatternAndContext();
        auto barItemLayoutProperty = barItemNode->GetLayoutProperty();
        CHECK_NULL_RETURN(barItemLayoutProperty, nullptr);
        barItemLayoutProperty->UpdateMeasureType(MeasureType::MATCH_PARENT);
        BuildMoreIemNode(barItemNode, isButtonEnabled);
        auto barMenuNode =
            MenuView::Create(std::move(params), barItemNodeId, V2::BAR_ITEM_ETS_TAG, MenuType::NAVIGATION_MENU);
        auto buttonPattern = AceType::MakeRefPtr<NG::ButtonPattern>();
        CHECK_NULL_RETURN(buttonPattern, nullptr);
        buttonPattern->setComponentButtonType(ComponentButtonType::NAVIGATION);
        buttonPattern->SetFocusBorderColor(theme->GetToolBarItemFocusColor());
        buttonPattern->SetFocusBorderWidth(theme->GetToolBarItemFocusBorderWidth());
        auto menuItemNode = FrameNode::CreateFrameNode(
            V2::MENU_ITEM_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), buttonPattern);
        CHECK_NULL_RETURN(menuItemNode, nullptr);
        auto menuItemLayoutProperty = menuItemNode->GetLayoutProperty<ButtonLayoutProperty>();
        CHECK_NULL_RETURN(menuItemLayoutProperty, nullptr);
        menuItemLayoutProperty->UpdateUserDefinedIdealSize(
            CalcSize(CalcLength(BACK_BUTTON_SIZE.ConvertToPx()), CalcLength(BACK_BUTTON_SIZE.ConvertToPx())));
        menuItemLayoutProperty->UpdateType(ButtonType::NORMAL);
        menuItemLayoutProperty->UpdateBorderRadius(BorderRadiusProperty(BUTTON_RADIUS));
        auto renderContext = menuItemNode->GetRenderContext();
        CHECK_NULL_RETURN(renderContext, nullptr);
        renderContext->UpdateBackgroundColor(Color::TRANSPARENT);
        BuildMoreItemNodeAction(menuItemNode, barItemNode, barMenuNode);
        InitTitleBarButtonEvent(menuItemNode, true);

        PaddingProperty padding;
        padding.left = CalcLength(BUTTON_PADDING.ConvertToPx());
        padding.right = CalcLength(BUTTON_PADDING.ConvertToPx());
        padding.top = CalcLength(BUTTON_PADDING.ConvertToPx());
        padding.bottom = CalcLength(BUTTON_PADDING.ConvertToPx());
        menuItemLayoutProperty->UpdatePadding(padding);

        barItemNode->MountToParent(menuItemNode);
        barItemNode->MarkModifyDone();
        menuItemNode->MarkModifyDone();
        menuNode->AddChild(menuItemNode);
        isCreateLandscapeMenu ? navBarNode->SetLandscapeMenuNode(barMenuNode) : navBarNode->SetMenuNode(barMenuNode);
    }
    return menuNode;
}

void BuildTitle(const RefPtr<NavBarNode>& navBarNode, const RefPtr<TitleBarNode>& titleBarNode)
{
    CHECK_NULL_VOID_NOLOG(navBarNode->GetTitle());
    auto navBarLayoutProperty = navBarNode->GetLayoutProperty<NavBarLayoutProperty>();
    CHECK_NULL_VOID(navBarLayoutProperty);
    auto theme = NavigationGetTheme();
    CHECK_NULL_VOID(theme);
    if (navBarLayoutProperty->GetTitleModeValue(NavigationTitleMode::FREE) == NavigationTitleMode::MINI) {
        UpdateTitleFontSize(navBarNode, theme->GetTitleFontSize());
    } else {
        UpdateTitleFontSize(navBarNode, theme->GetTitleFontSizeBig());
    }

    if (navBarNode->GetTitleNodeOperationValue(ChildNodeOperation::NONE) == ChildNodeOperation::NONE) {
        return;
    }
    if (navBarNode->GetTitleNodeOperationValue(ChildNodeOperation::NONE) == ChildNodeOperation::REPLACE) {
        titleBarNode->RemoveChild(titleBarNode->GetTitle());
        titleBarNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    }
    titleBarNode->SetTitle(navBarNode->GetTitle());
    titleBarNode->AddChild(titleBarNode->GetTitle());
}

void BuildSubtitle(const RefPtr<NavBarNode>& navBarNode, const RefPtr<TitleBarNode>& titleBarNode)
{
    CHECK_NULL_VOID_NOLOG(navBarNode->GetSubtitle());
    if (navBarNode->GetSubtitleNodeOperationValue(ChildNodeOperation::NONE) == ChildNodeOperation::NONE) {
        return;
    }
    if (navBarNode->GetSubtitleNodeOperationValue(ChildNodeOperation::NONE) == ChildNodeOperation::REPLACE) {
        titleBarNode->RemoveChild(titleBarNode->GetSubtitle());
        titleBarNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    }
    titleBarNode->SetSubtitle(navBarNode->GetSubtitle());
    titleBarNode->AddChild(titleBarNode->GetSubtitle());
}

void BuildMenu(const RefPtr<NavBarNode>& navBarNode, const RefPtr<TitleBarNode>& titleBarNode)
{
    if (navBarNode->GetMenuNodeOperationValue(ChildNodeOperation::NONE) == ChildNodeOperation::REPLACE) {
        titleBarNode->RemoveChild(titleBarNode->GetMenu());
        titleBarNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    }
    if (navBarNode->GetPrevMenuIsCustomValue(false)) {
        if (navBarNode->GetMenuNodeOperationValue(ChildNodeOperation::NONE) == ChildNodeOperation::NONE) {
            return;
        }
        titleBarNode->SetMenu(navBarNode->GetMenu());
        titleBarNode->AddChild(titleBarNode->GetMenu());
    } else {
        auto navBarPattern = navBarNode->GetPattern<NavBarPattern>();
        CHECK_NULL_VOID(navBarPattern);
        auto titleBarMenuItems = navBarPattern->GetTitleBarMenuItems();
        auto toolBarMenuItems = navBarPattern->GetToolBarMenuItems();

        if (navBarPattern->HasMenuNodeId()) {
            auto menuNode = CreateMenuItems(navBarPattern->GetMenuNodeId(), titleBarMenuItems, navBarNode, false);
            CHECK_NULL_VOID(menuNode);
            navBarNode->SetMenu(menuNode);
        }

        titleBarMenuItems.insert(titleBarMenuItems.end(), toolBarMenuItems.begin(), toolBarMenuItems.end());
        auto landscapeMenuNode =
            CreateMenuItems(navBarPattern->GetLandscapeMenuNodeId(), titleBarMenuItems, navBarNode, true);
        CHECK_NULL_VOID(landscapeMenuNode);
        navBarNode->SetLandscapeMenu(landscapeMenuNode);
    }
}

void BuildTitleBar(const RefPtr<NavBarNode>& navBarNode, const RefPtr<TitleBarNode>& titleBarNode,
    RefPtr<NavBarLayoutProperty>& navBarLayoutProperty)
{
    auto titleBarLayoutProperty = titleBarNode->GetLayoutProperty<TitleBarLayoutProperty>();
    CHECK_NULL_VOID(titleBarLayoutProperty);
    do {
        if (!navBarNode->HasBackButtonNodeOperation() ||
            navBarNode->GetBackButtonNodeOperationValue() == ChildNodeOperation::NONE) {
            break;
        }
        if (navBarNode->GetBackButtonNodeOperationValue() == ChildNodeOperation::REMOVE) {
            auto backButtonNode = AceType::DynamicCast<FrameNode>(titleBarNode->GetBackButton());
            CHECK_NULL_VOID(backButtonNode);
            auto backButtonLayoutProperty = backButtonNode->GetLayoutProperty();
            CHECK_NULL_VOID(backButtonLayoutProperty);
            backButtonLayoutProperty->UpdateVisibility(VisibleType::GONE);
            break;
        }
        titleBarNode->SetBackButton(navBarNode->GetBackButton());
        titleBarNode->AddChild(titleBarNode->GetBackButton());
        if (titleBarNode->GetBackButton() && !titleBarLayoutProperty->GetHideBackButtonValue(false)) {
            auto backButtonNode = AceType::DynamicCast<FrameNode>(titleBarNode->GetBackButton());
            CHECK_NULL_VOID(backButtonNode);
            auto backButtonLayoutProperty = backButtonNode->GetLayoutProperty();
            CHECK_NULL_VOID(backButtonLayoutProperty);
            backButtonLayoutProperty->UpdateVisibility(VisibleType::VISIBLE);
            break;
        }
    } while (false);
    BuildTitle(navBarNode, titleBarNode);
    BuildSubtitle(navBarNode, titleBarNode);
    BuildMenu(navBarNode, titleBarNode);
}

void MountTitleBar(const RefPtr<NavBarNode>& hostNode)
{
    auto navBarLayoutProperty = hostNode->GetLayoutProperty<NavBarLayoutProperty>();
    CHECK_NULL_VOID(navBarLayoutProperty);
    auto titleBarNode = AceType::DynamicCast<TitleBarNode>(hostNode->GetTitleBarNode());
    CHECK_NULL_VOID(titleBarNode);
    auto titleBarLayoutProperty = titleBarNode->GetLayoutProperty<TitleBarLayoutProperty>();
    CHECK_NULL_VOID(titleBarLayoutProperty);

    if (!hostNode->GetTitle() && !hostNode->GetSubtitle() && !hostNode->GetMenu() && !hostNode->GetBackButton()) {
        return;
    }
    titleBarLayoutProperty->UpdateTitleMode(navBarLayoutProperty->GetTitleModeValue(NavigationTitleMode::FREE));
    titleBarLayoutProperty->UpdateHideBackButton(navBarLayoutProperty->GetHideBackButtonValue(false));
    BuildTitleBar(hostNode, titleBarNode, navBarLayoutProperty);
    if (navBarLayoutProperty->GetHideTitleBar().value_or(false)) {
        titleBarLayoutProperty->UpdateVisibility(VisibleType::GONE);
    } else {
        titleBarLayoutProperty->UpdateVisibility(VisibleType::VISIBLE);
    }
    titleBarNode->MarkModifyDone();
}

void MountToolBar(const RefPtr<NavBarNode>& hostNode)
{
    CHECK_NULL_VOID_NOLOG(hostNode->GetToolBarNode());
    auto navBarLayoutProperty = hostNode->GetLayoutProperty<NavBarLayoutProperty>();
    CHECK_NULL_VOID(navBarLayoutProperty);
    auto toolBarNode = AceType::DynamicCast<FrameNode>(hostNode->GetToolBarNode());
    CHECK_NULL_VOID(toolBarNode);
    auto toolBarLayoutProperty = toolBarNode->GetLayoutProperty<LayoutProperty>();
    CHECK_NULL_VOID(toolBarLayoutProperty);

    if (hostNode->GetToolBarNodeOperationValue(ChildNodeOperation::NONE) == ChildNodeOperation::REPLACE) {
        hostNode->RemoveChild(hostNode->GetPreToolBarNode());
        hostNode->AddChild(hostNode->GetToolBarNode());
    }

    if (navBarLayoutProperty->GetHideToolBar().value_or(false)) {
        toolBarLayoutProperty->UpdateVisibility(VisibleType::GONE);
    } else {
        toolBarLayoutProperty->UpdateVisibility(VisibleType::VISIBLE);
    }
}
} // namespace

void NavBarPattern::InitPanEvent(const RefPtr<GestureEventHub>& gestureHub)
{
    CHECK_NULL_VOID_NOLOG(!panEvent_);

    auto actionStartTask = [weak = WeakClaim(this)](const GestureEvent& info) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID_NOLOG(pattern);
        pattern->HandleOnDragStart(info.GetOffsetY());
    };

    auto actionUpdateTask = [weak = WeakClaim(this), this](const GestureEvent& info) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID_NOLOG(pattern);
        pattern->HandleOnDragUpdate(info.GetOffsetY());
    };

    auto actionEndTask = [weak = WeakClaim(this)](const GestureEvent& info) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID_NOLOG(pattern);
        pattern->HandleOnDragEnd();
    };

    auto actionCancelTask = [weak = WeakClaim(this)]() {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID_NOLOG(pattern);
        pattern->HandleOnDragEnd();
    };

    if (panEvent_) {
        gestureHub->RemovePanEvent(panEvent_);
    }

    panEvent_ = MakeRefPtr<PanEvent>(
        std::move(actionStartTask), std::move(actionUpdateTask), std::move(actionEndTask), std::move(actionCancelTask));
    PanDirection panDirection = { .type = PanDirection::VERTICAL };
    gestureHub->SetPanEvent(panEvent_, panDirection, DEFAULT_PAN_FINGER, DEFAULT_PAN_DISTANCE);
}

void NavBarPattern::HandleOnDragStart(float offset)
{
    auto hostNode = AceType::DynamicCast<NavBarNode>(GetHost());
    CHECK_NULL_VOID(hostNode);
    auto titleNode = AceType::DynamicCast<TitleBarNode>(hostNode->GetTitleBarNode());
    CHECK_NULL_VOID(titleNode);
    auto titlePattern = titleNode->GetPattern<TitleBarPattern>();
    CHECK_NULL_VOID(titlePattern);
    titlePattern->SetCanOverDrag(false);
    titlePattern->ProcessTittleDragStart(offset);
}

void NavBarPattern::HandleOnDragUpdate(float offset)
{
    auto hostNode = AceType::DynamicCast<NavBarNode>(GetHost());
    CHECK_NULL_VOID(hostNode);
    auto titleNode = AceType::DynamicCast<TitleBarNode>(hostNode->GetTitleBarNode());
    CHECK_NULL_VOID(titleNode);
    auto titlePattern = titleNode->GetPattern<TitleBarPattern>();
    CHECK_NULL_VOID(titlePattern);
    titlePattern->ProcessTittleDragUpdate(offset);
}

void NavBarPattern::HandleOnDragEnd()
{
    auto hostNode = AceType::DynamicCast<NavBarNode>(GetHost());
    CHECK_NULL_VOID(hostNode);
    auto titleNode = AceType::DynamicCast<TitleBarNode>(hostNode->GetTitleBarNode());
    CHECK_NULL_VOID(titleNode);
    auto titlePattern = titleNode->GetPattern<TitleBarPattern>();
    CHECK_NULL_VOID(titlePattern);
    titlePattern->ProcessTittleDragEnd();
}

bool NavBarPattern::GetDraggedDown()
{
    auto hostNode = AceType::DynamicCast<NavBarNode>(GetHost());
    CHECK_NULL_RETURN(hostNode, false);
    auto titleNode = AceType::DynamicCast<TitleBarNode>(hostNode->GetTitleBarNode());
    CHECK_NULL_RETURN(titleNode, false);
    auto titlePattern = titleNode->GetPattern<TitleBarPattern>();
    CHECK_NULL_RETURN(titlePattern, false);
    auto isDraggedDown = titlePattern->IsTitleDraggedDown();
    return isDraggedDown;
}

void NavBarPattern::OnCoordScrollStart()
{
    offset_ = 0.0f;
    auto hostNode = AceType::DynamicCast<NavBarNode>(GetHost());
    CHECK_NULL_VOID(hostNode);
    auto titleNode = AceType::DynamicCast<TitleBarNode>(hostNode->GetTitleBarNode());
    CHECK_NULL_VOID(titleNode);
    auto titlePattern = titleNode->GetPattern<TitleBarPattern>();
    CHECK_NULL_VOID(titlePattern);
    titlePattern->SetCanOverDrag(true);
    titlePattern->ProcessTittleDragStart(offset_);
}

void NavBarPattern::OnCoordScrollUpdate(float offset)
{
    offset_ += offset;
    auto hostNode = AceType::DynamicCast<NavBarNode>(GetHost());
    CHECK_NULL_VOID(hostNode);
    auto titleNode = AceType::DynamicCast<TitleBarNode>(hostNode->GetTitleBarNode());
    CHECK_NULL_VOID(titleNode);
    auto titlePattern = titleNode->GetPattern<TitleBarPattern>();
    CHECK_NULL_VOID(titlePattern);
    titlePattern->ProcessTittleDragUpdate(offset_);
}

void NavBarPattern::OnCoordScrollEnd()
{
    auto hostNode = AceType::DynamicCast<NavBarNode>(GetHost());
    CHECK_NULL_VOID(hostNode);
    auto titleNode = AceType::DynamicCast<TitleBarNode>(hostNode->GetTitleBarNode());
    CHECK_NULL_VOID(titleNode);
    auto titlePattern = titleNode->GetPattern<TitleBarPattern>();
    titlePattern->ProcessTittleDragEnd();
    offset_ = 0.0f;
}

void NavBarPattern::OnScrollStart()
{
    offset_ = 0.0f;
    auto hostNode = AceType::DynamicCast<NavBarNode>(GetHost());
    CHECK_NULL_VOID(hostNode);
    auto titleNode = AceType::DynamicCast<TitleBarNode>(hostNode->GetTitleBarNode());
    CHECK_NULL_VOID(titleNode);
    auto titlePattern = titleNode->GetPattern<TitleBarPattern>();
    CHECK_NULL_VOID(titlePattern);
    titlePattern->SetCanOverDrag(false);
    titlePattern->ProcessTittleDragStart(offset_);
}

void NavBarPattern::OnScrollUpdate(float offset)
{
    offset_ += offset;
    auto hostNode = AceType::DynamicCast<NavBarNode>(GetHost());
    CHECK_NULL_VOID(hostNode);
    auto titleNode = AceType::DynamicCast<TitleBarNode>(hostNode->GetTitleBarNode());
    CHECK_NULL_VOID(titleNode);
    auto titlePattern = titleNode->GetPattern<TitleBarPattern>();
    CHECK_NULL_VOID(titlePattern);
    titlePattern->ProcessTittleDragUpdate(offset_);
    if (GetFullStatus()) {
        StopNavBarMotion();
    }
}

void NavBarPattern::OnScrollEnd()
{
    auto hostNode = AceType::DynamicCast<NavBarNode>(GetHost());
    CHECK_NULL_VOID(hostNode);
    auto titleNode = AceType::DynamicCast<TitleBarNode>(hostNode->GetTitleBarNode());
    CHECK_NULL_VOID(titleNode);
    auto titlePattern = titleNode->GetPattern<TitleBarPattern>();
    titlePattern->ProcessTittleDragEnd();
    offset_ = 0.0f;
}

bool NavBarPattern::GetFullStatus()
{
    auto hostNode = AceType::DynamicCast<NavBarNode>(GetHost());
    CHECK_NULL_RETURN(hostNode, false);
    auto titleNode = AceType::DynamicCast<TitleBarNode>(hostNode->GetTitleBarNode());
    CHECK_NULL_RETURN(titleNode, false);
    auto titlePattern = titleNode->GetPattern<TitleBarPattern>();
    CHECK_NULL_RETURN(titlePattern, false);
    auto isFullStatus = titlePattern->IsTitleFullStatus();
    return isFullStatus;
}

RefPtr<FrameNode> NavBarPattern::FindScrollableChild()
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, nullptr);
    std::queue<RefPtr<FrameNode>> frameNodeQueue;
    frameNodeQueue.push(host);
    while (!frameNodeQueue.empty()) {
        auto size = frameNodeQueue.size();
        while (size > 0) {
            auto node = frameNodeQueue.front();
            CHECK_NULL_RETURN(node, nullptr);
            if ((AceType::InstanceOf<ScrollablePattern>(node->GetPattern())) &&
                ((AceType::InstanceOf<ListPattern>(node->GetPattern())) ||
                    (AceType::InstanceOf<GridPattern>(node->GetPattern())))) {
                return node;
            }
            frameNodeQueue.pop();
            auto children = node->GetChildren();
            for (auto const& child : children) {
                auto childNode = DynamicCast<FrameNode>(child);
                if (childNode) {
                    frameNodeQueue.push(childNode);
                }
            }
            size--;
        }
    }
    return nullptr;
}

void NavBarPattern::OnModifyDone()
{
    Pattern::OnModifyDone();
    auto hostNode = AceType::DynamicCast<NavBarNode>(GetHost());
    CHECK_NULL_VOID(hostNode);
    MountTitleBar(hostNode);
    MountToolBar(hostNode);

    auto context = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(context);
    controller_ = CREATE_ANIMATOR(context);
    auto navBarLayoutProperty = hostNode->GetLayoutProperty<NavBarLayoutProperty>();
    CHECK_NULL_VOID(navBarLayoutProperty);
    isHideToolbar_ = navBarLayoutProperty->GetHideToolBar().value_or(false);
    RegistOritationListener();
    // if current mode is not free, doesn't have animation
    if (navBarLayoutProperty->GetTitleModeValue(NavigationTitleMode::FREE) != NavigationTitleMode::FREE) {
        return;
    }
    auto gesture = hostNode->GetOrCreateGestureEventHub();
    CHECK_NULL_VOID(gesture);
    InitPanEvent(gesture);
}

void NavBarPattern::OnWindowSizeChanged(int32_t width, int32_t height, WindowSizeChangeReason type)
{
    auto navBarNode = AceType::DynamicCast<NavBarNode>(GetHost());
    CHECK_NULL_VOID(navBarNode);
    auto titleBarNode = AceType::DynamicCast<TitleBarNode>(navBarNode->GetTitleBarNode());
    CHECK_NULL_VOID(titleBarNode);
    if (titleBarNode->GetMenu()) {
        auto buttonNode = titleBarNode->GetMenu()->GetLastChild();
        CHECK_NULL_VOID(buttonNode);
        auto barItemNode = buttonNode->GetFirstChild();
        CHECK_NULL_VOID(barItemNode);
        auto barItemFrameNode = AceType::DynamicCast<BarItemNode>(barItemNode);
        CHECK_NULL_VOID(barItemFrameNode);
        if (barItemFrameNode->IsMoreItemNode() && barItemFrameNode->IsTitleMenuNodeShowing()) {
            auto eventHub = barItemFrameNode->GetEventHub<BarItemEventHub>();
            CHECK_NULL_VOID(eventHub);
            eventHub->FireItemAction();
        }
    }
}

void NavBarPattern::RegistOritationListener()
{
    if (isOritationListenerRegisted_) {
        return;
    }
    isOritationListenerRegisted_ = true;
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    pipeline->AddWindowSizeChangeCallback(host->GetId());
}

void NavBarPattern::OnDetachFromFrameNode(FrameNode* frameNode)
{
    CHECK_NULL_VOID(frameNode);
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    pipeline->RemoveWindowSizeChangeCallback(frameNode->GetId());
    isOritationListenerRegisted_ = false;
}

void NavBarPattern::NavBarMotion(double velocity, double friction)
{
    float mainPosition = 0.0f;
    if (!motion_) {
        motion_ = AceType::MakeRefPtr<FrictionMotion>(friction, mainPosition, velocity);
    } else {
        motion_->Reset(friction, mainPosition, velocity);
    }
    motionOffset_ = 0.0f;
    motion_->AddListener([weak = AceType::WeakClaim(this)](double value) {
        auto navBar = weak.Upgrade();
        if (navBar) {
            navBar->OnScrollUpdate(value - navBar->motionOffset_);
            navBar->motionOffset_ = value;
        }
    });
    controller_->ClearStopListeners();
    controller_->AddStopListener([weak = AceType::WeakClaim(this)]() {
        auto navBar = weak.Upgrade();
        if (navBar) {
            navBar->OnScrollEnd();
        }
    });
    OnScrollStart();
    controller_->PlayMotion(motion_);
}
void NavBarPattern::StopNavBarMotion()
{
    if (controller_->IsRunning()) {
        controller_->Stop();
    }
}
} // namespace OHOS::Ace::NG
