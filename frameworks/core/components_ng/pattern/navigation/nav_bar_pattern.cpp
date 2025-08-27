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

#include "base/i18n/localization.h"
#include "base/subwindow/subwindow_manager.h"
#include "base/utils/system_properties.h"
#include "core/components_ng/pattern/image/image_layout_property.h"
#include "core/components_ng/pattern/image/image_pattern.h"
#include "core/components_ng/pattern/menu/menu_view.h"
#include "core/components_ng/pattern/menu/wrapper/menu_wrapper_pattern.h"
#include "core/components_ng/pattern/navigation/navigation_pattern.h"
#include "core/components_ng/pattern/navigation/navigation_title_util.h"
#include "core/components_ng/pattern/navigation/navigation_toolbar_util.h"
#include "core/components_ng/pattern/navigation/title_bar_pattern.h"
#include "core/components_ng/pattern/navigation/tool_bar_node.h"

namespace OHOS::Ace::NG {
namespace {
// titlebar ZINDEX
constexpr static int32_t DEFAULT_TITLEBAR_ZINDEX = 2;
void BuildMoreItemNodeAction(const RefPtr<FrameNode>& buttonNode, const RefPtr<BarItemNode>& barItemNode,
    const RefPtr<FrameNode>& barMenuNode, const RefPtr<NavBarNode>& navBarNode, const MenuParam& menuParam)
{
    auto eventHub = barItemNode->GetEventHub<BarItemEventHub>();
    CHECK_NULL_VOID(eventHub);

    auto context = PipelineContext::GetCurrentContext();
    auto clickCallback = [weakContext = WeakPtr<PipelineContext>(context),
                            id = barItemNode->GetId(),
                            param = menuParam,
                            weakMenu = WeakPtr<FrameNode>(barMenuNode),
                            weakBarItemNode = WeakPtr<BarItemNode>(barItemNode),
                            weakNavBarNode = WeakPtr<NavBarNode>(navBarNode)]() {
        auto context = weakContext.Upgrade();
        CHECK_NULL_VOID(context);

        auto overlayManager = context->GetOverlayManager();
        CHECK_NULL_VOID(overlayManager);

        auto menu = weakMenu.Upgrade();
        CHECK_NULL_VOID(menu);

        auto barItemNode = weakBarItemNode.Upgrade();
        CHECK_NULL_VOID(barItemNode);

        auto menuNode = AceType::DynamicCast<FrameNode>(menu->GetChildAtIndex(0));
        CHECK_NULL_VOID(menuNode);

        auto menuPattern = menuNode->GetPattern<MenuPattern>();
        CHECK_NULL_VOID(menuPattern);

        auto navBarNode = weakNavBarNode.Upgrade();
        CHECK_NULL_VOID(navBarNode);

        auto navBarPattern = navBarNode->GetPattern<NavBarPattern>();
        CHECK_NULL_VOID(navBarPattern);

        // navigation menu show like select.
        menuPattern->SetIsSelectMenu(true);
        OffsetF offset(0.0f, 0.0f);
        if (AceApplicationInfo::GetInstance().GreatOrEqualTargetAPIVersion(PlatformVersion::VERSION_TWELVE)) {
            auto symbol = AceType::DynamicCast<FrameNode>(barItemNode->GetChildren().front());
            CHECK_NULL_VOID(symbol);
            auto symbolProperty = symbol->GetLayoutProperty<TextLayoutProperty>();
            CHECK_NULL_VOID(symbolProperty);
            auto symbolEffectOptions = symbolProperty->GetSymbolEffectOptionsValue(SymbolEffectOptions());
            symbolEffectOptions.SetEffectType(SymbolEffectType::BOUNCE);
            symbolEffectOptions.SetIsTxtActive(true);
            symbolEffectOptions.SetIsTxtActiveSource(0);
            symbolProperty->UpdateSymbolEffectOptions(symbolEffectOptions);
            symbol->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
        } else {
            offset = navBarPattern->GetShowMenuOffset(barItemNode, menuNode);
        }

        if (param.isShowInSubWindow) {
            auto wrapperPattern = menu->GetPattern<MenuWrapperPattern>();
            if (wrapperPattern && wrapperPattern->GetMenuStatus() == MenuStatus::ON_HIDE_ANIMATION) {
                //if on hide animation, avoid displaying the menu again 
                return;
            }
            SubwindowManager::GetInstance()->ShowMenuNG(menu, param, barItemNode, offset);
            return;
        }
        overlayManager->ShowMenu(id, offset, menu);
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
    const RefPtr<NavBarNode>& navBarNode, bool isCreateLandscapeMenu)
{
    auto menuNode = FrameNode::GetOrCreateFrameNode(
        V2::NAVIGATION_MENU_ETS_TAG, menuNodeId, []() { return AceType::MakeRefPtr<LinearLayoutPattern>(false); });
    CHECK_NULL_RETURN(menuNode, nullptr);
    menuNode->Clean();
    menuNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    auto rowProperty = menuNode->GetLayoutProperty<LinearLayoutProperty>();
    CHECK_NULL_RETURN(rowProperty, nullptr);
    rowProperty->UpdateMainAxisAlign(FlexAlign::SPACE_BETWEEN);
    CHECK_NULL_RETURN(navBarNode, nullptr);
    auto frameNode = navBarNode->GetParent();
    CHECK_NULL_RETURN(frameNode, nullptr);
    auto theme = NavigationGetTheme(frameNode->GetThemeScopeId());
    CHECK_NULL_RETURN(theme, nullptr);
    auto navBarPattern = AceType::DynamicCast<NavBarPattern>(navBarNode->GetPattern());
    auto navBarMaxNum = navBarPattern->GetMaxMenuNum();
    auto mostMenuItemCount =
        navBarMaxNum < 0 ? theme->GetMostMenuItemCountInBar() : static_cast<uint32_t>(navBarMaxNum);
    mostMenuItemCount = SystemProperties::GetDeviceOrientation() == DeviceOrientation::LANDSCAPE ? MAX_MENU_NUM_LARGE
                                                                                                  : mostMenuItemCount;
    navBarPattern->SetMaxMenuNum(mostMenuItemCount);
    bool needMoreButton = menuItems.size() > mostMenuItemCount;

    auto navigationGroupNode = AceType::DynamicCast<NavigationGroupNode>(frameNode);
    CHECK_NULL_RETURN(navigationGroupNode, nullptr);
    auto hub = navigationGroupNode->GetEventHub<EventHub>();
    CHECK_NULL_RETURN(hub, nullptr);
    auto isButtonEnabled = hub->IsEnabled();

    std::string parentId = navigationGroupNode->GetInspectorId().value_or("");
    int32_t count = 0;
    std::vector<OptionParam> params;
    OptionParam param;
    for (const auto& menuItem : menuItems) {
        ++count;
        if (needMoreButton && (count > static_cast<int32_t>(mostMenuItemCount) - 1)) {
            param = { menuItem.text.value_or(""), menuItem.icon.value_or(""), menuItem.isEnabled.value_or(true),
                menuItem.action, menuItem.iconSymbol.value_or(nullptr) };
            param.SetSymbolUserDefinedIdealFontSize(theme->GetMenuIconSize());
            params.push_back(param);
        } else {
            auto menuItemNode = NavigationTitleUtil::CreateMenuItemButton(theme);
            int32_t barItemNodeId = ElementRegister::GetInstance()->MakeUniqueId();
            auto barItemNode = BarItemNode::GetOrCreateBarItemNode(
                V2::BAR_ITEM_ETS_TAG, barItemNodeId, []() { return AceType::MakeRefPtr<BarItemPattern>(); });
            NavigationTitleUtil::UpdateBarItemNodeWithItem(barItemNode, menuItem, isButtonEnabled, theme);
            auto barItemLayoutProperty = barItemNode->GetLayoutProperty();
            CHECK_NULL_RETURN(barItemLayoutProperty, nullptr);
            barItemLayoutProperty->UpdateMeasureType(MeasureType::MATCH_PARENT);

            auto iconNode = AceType::DynamicCast<FrameNode>(barItemNode->GetChildren().front());
            NavigationTitleUtil::InitTitleBarButtonEvent(
                menuItemNode, iconNode, false, menuItem, menuItem.isEnabled.value_or(true));

            // read navigation menu button
            NavigationTitleUtil::SetAccessibility(menuItemNode, menuItem.text.value_or(""));

            // set navigation titleBar menu inspectorId
            std::string menuItemValue = menuItemNode->GetTag() + std::to_string(count);
            // Field field;
            NavigationTitleUtil::SetInnerChildId(menuItemNode, NG::NAV_FIELD,
                menuNode->GetTag(), menuItemValue, parentId);

            barItemNode->MountToParent(menuItemNode);
            barItemNode->MarkModifyDone();
            menuItemNode->MarkModifyDone();
            menuNode->AddChild(menuItemNode);
        }
    }

    // build more button
    if (needMoreButton) {
        int32_t barItemNodeId = ElementRegister::GetInstance()->MakeUniqueId();
        auto barItemNode = BarItemNode::GetOrCreateBarItemNode(
            V2::BAR_ITEM_ETS_TAG, barItemNodeId, []() { return AceType::MakeRefPtr<BarItemPattern>(); });
        auto barItemLayoutProperty = barItemNode->GetLayoutProperty();
        CHECK_NULL_RETURN(barItemLayoutProperty, nullptr);
        barItemLayoutProperty->UpdateMeasureType(MeasureType::MATCH_PARENT);
        NavigationTitleUtil::BuildMoreIemNode(barItemNode, isButtonEnabled, theme);
        auto menuItemNode = NavigationTitleUtil::CreateMenuItemButton(theme);
        MenuParam menuParam;
        menuParam.isShowInSubWindow = false;
        if (SystemProperties::GetDeviceType() == DeviceType::TWO_IN_ONE) {
            menuParam.isShowInSubWindow = true;
        }
        auto targetId = barItemNode->GetId();
        auto targetTag = barItemNode->GetTag();
        if (AceApplicationInfo::GetInstance().GreatOrEqualTargetAPIVersion(PlatformVersion::VERSION_TWELVE)) {
            menuParam.placement = Placement::BOTTOM_RIGHT;
            targetId = menuItemNode->GetId();
            targetTag = menuItemNode->GetTag();
        }
        NavigationMenuOptions menuOptions = navBarPattern->GetMenuOptions();
        if (menuOptions.mbOptions.bgOptions.blurStyleOption.has_value()) {
            menuParam.backgroundBlurStyleOption = menuOptions.mbOptions.bgOptions.blurStyleOption.value();
        }
        if (menuOptions.mbOptions.bgOptions.effectOption.has_value()) {
            menuParam.backgroundEffectOption = menuOptions.mbOptions.bgOptions.effectOption.value();
        }
        auto barMenuNode = MenuView::Create(
            std::move(params), targetId, targetTag, MenuType::NAVIGATION_MENU, menuParam);
        BuildMoreItemNodeAction(menuItemNode, barItemNode, barMenuNode, navBarNode, menuParam);
        auto iconNode = AceType::DynamicCast<FrameNode>(barItemNode->GetChildren().front());
        NavigationTitleUtil::InitTitleBarButtonEvent(menuItemNode, iconNode, true);

        // read navigation "more" button
        std::string message  = theme->GetMoreMessage();
        NavigationTitleUtil::SetAccessibility(menuItemNode, message);

        // set navigation titleBar "more" button inspectorId
        NavigationTitleUtil::SetInnerChildId(menuItemNode, NG::NAV_FIELD, menuNode->GetTag(), "More", parentId);

        barItemNode->MountToParent(menuItemNode);
        barItemNode->MarkModifyDone();
        menuItemNode->MarkModifyDone();
        menuNode->AddChild(menuItemNode);
        isCreateLandscapeMenu ? navBarNode->SetLandscapeMenuNode(barMenuNode) : navBarNode->SetMenuNode(barMenuNode);
    }
    auto titleBarNode = AceType::DynamicCast<TitleBarNode>(navBarNode->GetTitleBarNode());
    CHECK_NULL_RETURN(titleBarNode, nullptr);
    auto titlePattern = titleBarNode->GetPattern<TitleBarPattern>();
    CHECK_NULL_RETURN(titlePattern, nullptr);
    titlePattern->InitMenuDragAndLongPressEvent(menuNode, menuItems);
    return menuNode;
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
        navBarNode->UpdateMenuNodeOperation(ChildNodeOperation::NONE);
    } else {
        navBarNode->UpdateMenuNodeOperation(ChildNodeOperation::NONE);
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

void BuildTitleBar(const RefPtr<NavBarNode>& navBarNode, const RefPtr<TitleBarNode>& titleBarNode)
{
    auto titleBarLayoutProperty = titleBarNode->GetLayoutProperty<TitleBarLayoutProperty>();
    CHECK_NULL_VOID(titleBarLayoutProperty);

    // Update back button visibility
    auto backButtonNode = AceType::DynamicCast<FrameNode>(titleBarNode->GetBackButton());
    if (backButtonNode) {
        auto backButtonLayoutProperty = backButtonNode->GetLayoutProperty();
        CHECK_NULL_VOID(backButtonLayoutProperty);
        backButtonLayoutProperty->UpdateVisibility(
            titleBarLayoutProperty->GetHideBackButtonValue(false) ? VisibleType::GONE : VisibleType::VISIBLE);
    }

    // update main title
    auto mainTitleNode = AceType::DynamicCast<FrameNode>(titleBarNode->GetTitle());
    if (mainTitleNode && !navBarNode->GetPrevTitleIsCustomValue(false)) {
        auto textLayoutProperty = mainTitleNode->GetLayoutProperty<TextLayoutProperty>();
        CHECK_NULL_VOID(textLayoutProperty);
        auto theme = NavigationGetTheme();
        CHECK_NULL_VOID(theme);
        if (titleBarLayoutProperty->GetTitleModeValue(NavigationTitleMode::FREE) == NavigationTitleMode::MINI) {
            textLayoutProperty->UpdateFontSize(theme->GetTitleFontSize());
        } else {
            textLayoutProperty->UpdateFontSize(theme->GetTitleFontSizeBig());
        }
        mainTitleNode->MarkModifyDone();
    }

    // update menu
    BuildMenu(navBarNode, titleBarNode);
}
} // namespace

void NavBarPattern::MountTitleBar(
    const RefPtr<FrameNode>& host, bool& needRunTitleBarAnimation)
{
    needRunTitleBarAnimation = false;
    auto hostNode = AceType::DynamicCast<NavBarNode>(host);
    CHECK_NULL_VOID(hostNode);
    auto navBarLayoutProperty = hostNode->GetLayoutProperty<NavBarLayoutProperty>();
    CHECK_NULL_VOID(navBarLayoutProperty);
    auto titleBarNode = AceType::DynamicCast<TitleBarNode>(hostNode->GetTitleBarNode());
    CHECK_NULL_VOID(titleBarNode);
    auto titleBarLayoutProperty = titleBarNode->GetLayoutProperty<TitleBarLayoutProperty>();
    CHECK_NULL_VOID(titleBarLayoutProperty);
    auto navBarPattern = AceType::DynamicCast<NavBarPattern>(hostNode->GetPattern());
    auto hasCustomMenu = hostNode->GetPrevMenuIsCustomValue(false) && hostNode->GetMenu();
    // menu is not consume menu, menu item and tool bar menus need all empty
    auto hideMenu = !hostNode->GetPrevMenuIsCustomValue(false) && navBarPattern->GetTitleBarMenuItems().empty() &&
                    navBarPattern->GetToolBarMenuItems().empty();
    if (!titleBarNode->GetTitle() && !titleBarNode->GetSubtitle() && !titleBarNode->GetBackButton() && !hasCustomMenu &&
        hideMenu) {
        titleBarLayoutProperty->UpdateVisibility(VisibleType::GONE);
        return;
    }
    titleBarLayoutProperty->UpdateTitleMode(navBarLayoutProperty->GetTitleModeValue(NavigationTitleMode::FREE));
    titleBarLayoutProperty->UpdateHideBackButton(navBarLayoutProperty->GetHideBackButtonValue(false));
    BuildTitleBar(hostNode, titleBarNode);
    bool hideTitleBar = navBarLayoutProperty->GetHideTitleBarValue(false);
    // At the initial state, animation is not required.
    if (!currHideTitleBar_.has_value() ||
        !navBarLayoutProperty->GetIsAnimatedTitleBarValue(false)) {
        currHideTitleBar_ = hideTitleBar;
        HideOrShowTitleBarImmediately(hostNode, hideTitleBar);
        return;
    }
    titleBarNode->MarkModifyDone();
    titleBarNode->MarkDirtyNode();

    // Animation is needed only when the status changed.
    needRunTitleBarAnimation = currHideTitleBar_.value() != hideTitleBar;
    currHideTitleBar_ = hideTitleBar;
}

OffsetF NavBarPattern::GetShowMenuOffset(const RefPtr<BarItemNode>& barItemNode, const RefPtr<FrameNode>& menuNode)
{
    auto imageNode = barItemNode->GetChildAtIndex(0);
    CHECK_NULL_RETURN(imageNode, OffsetF(0.0f, 0.0f));

    auto imageFrameNode = AceType::DynamicCast<FrameNode>(imageNode);
    CHECK_NULL_RETURN(imageFrameNode, OffsetF(0.0f, 0.0f));
    auto imgOffset = imageFrameNode->GetOffsetRelativeToWindow();
    auto imageSize = imageFrameNode->GetGeometryNode()->GetFrameSize();

    auto menuLayoutProperty = menuNode->GetLayoutProperty<MenuLayoutProperty>();
    CHECK_NULL_RETURN(menuLayoutProperty, OffsetF(0.0f, 0.0f));
    menuLayoutProperty->UpdateTargetSize(imageSize);

    bool isRightToLeft = AceApplicationInfo::GetInstance().IsRightToLeft();
    if (isRightToLeft) {
        imgOffset.SetX(imgOffset.GetX() + imageSize.Width());
    }
    imgOffset.SetY(imgOffset.GetY() + imageSize.Height());
    return imgOffset;
}

void NavBarPattern::OnAttachToFrameNode()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    NavDestinationPatternBase::InitOnTouchEvent(host);
    auto pipelineContext = host->GetContextWithCheck();
    CHECK_NULL_VOID(pipelineContext);
    pipelineContext->AddWindowSizeChangeCallback(host->GetId());

    auto theme = NavigationGetTheme();
    CHECK_NULL_VOID(theme);
    if (theme && theme->GetNavBarUnfocusEffectEnable()) {
        pipelineContext->AddWindowFocusChangedCallback(host->GetId());
    }
    if (Container::GreatOrEqualAPIVersion(PlatformVersion::VERSION_ELEVEN)) {
        SafeAreaExpandOpts opts = { .type = SAFE_AREA_TYPE_SYSTEM | SAFE_AREA_TYPE_CUTOUT,
            .edges = SAFE_AREA_EDGE_ALL };
        host->GetLayoutProperty()->UpdateSafeAreaExpandOpts(opts);
    }
}

void NavBarPattern::OnCoordScrollStart()
{
    if (isHideTitlebar_ || titleMode_ != NavigationTitleMode::FREE) {
        auto eventHub = GetEventHub<NavBarEventHub>();
        CHECK_NULL_VOID(eventHub);
        eventHub->FireOnCoordScrollStartAction();
        return;
    }
    auto hostNode = AceType::DynamicCast<NavBarNode>(GetHost());
    CHECK_NULL_VOID(hostNode);
    auto titleNode = AceType::DynamicCast<TitleBarNode>(hostNode->GetTitleBarNode());
    CHECK_NULL_VOID(titleNode);
    auto titlePattern = titleNode->GetPattern<TitleBarPattern>();
    CHECK_NULL_VOID(titlePattern);
    titlePattern->OnCoordScrollStart();
}

float NavBarPattern::OnCoordScrollUpdate(float offset, float currentOffset)
{
    if (isHideTitlebar_ || titleMode_ != NavigationTitleMode::FREE) {
        auto eventHub = GetEventHub<NavBarEventHub>();
        CHECK_NULL_RETURN(eventHub, 0.0f);
        eventHub->FireOnCoordScrollUpdateAction(offset, currentOffset);
        return 0.0f;
    }
    auto hostNode = AceType::DynamicCast<NavBarNode>(GetHost());
    CHECK_NULL_RETURN(hostNode, 0.0f);
    auto titleNode = AceType::DynamicCast<TitleBarNode>(hostNode->GetTitleBarNode());
    CHECK_NULL_RETURN(titleNode, 0.0f);
    auto titlePattern = titleNode->GetPattern<TitleBarPattern>();
    CHECK_NULL_RETURN(titlePattern, 0.0f);
    return titlePattern->OnCoordScrollUpdate(offset);
}

void NavBarPattern::OnCoordScrollEnd()
{
    TAG_LOGI(AceLogTag::ACE_NAVIGATION, "OnCoordScroll end");
    if (titleMode_ != NavigationTitleMode::FREE) {
        TAG_LOGI(AceLogTag::ACE_NAVIGATION, "titleMode_ is not free");
        auto eventHub = GetEventHub<NavBarEventHub>();
        CHECK_NULL_VOID(eventHub);
        eventHub->FireOnCoordScrollEndAction();
        return;
    }
    auto hostNode = AceType::DynamicCast<NavBarNode>(GetHost());
    CHECK_NULL_VOID(hostNode);
    auto titleNode = AceType::DynamicCast<TitleBarNode>(hostNode->GetTitleBarNode());
    CHECK_NULL_VOID(titleNode);
    auto titlePattern = titleNode->GetPattern<TitleBarPattern>();
    titlePattern->OnCoordScrollEnd();
}

void NavBarPattern::OnModifyDone()
{
    Pattern::OnModifyDone();
    auto hostNode = AceType::DynamicCast<NavBarNode>(GetHost());
    CHECK_NULL_VOID(hostNode);
    auto titleBarNode = AceType::DynamicCast<TitleBarNode>(hostNode->GetTitleBarNode());
    CHECK_NULL_VOID(titleBarNode);
    auto titleBarRenderContext = titleBarNode->GetRenderContext();
    CHECK_NULL_VOID(titleBarRenderContext);
    // set the titlebar to float on the top
    titleBarRenderContext->UpdateZIndex(DEFAULT_TITLEBAR_ZINDEX);
    bool needRunTitleBarAnimation = false;
    MountTitleBar(hostNode, needRunTitleBarAnimation);
    bool needRunToolBarAnimation = false;
    NavigationToolbarUtil::MountToolBar(hostNode, needRunToolBarAnimation);
    HandleTitleBarAndToolBarAnimation(
        hostNode, needRunTitleBarAnimation, needRunToolBarAnimation);
    UpdateHideBarProperty();
    ExpandContentSafeAreaIfNeeded();
    auto navBarLayoutProperty = hostNode->GetLayoutProperty<NavBarLayoutProperty>();
    CHECK_NULL_VOID(navBarLayoutProperty);
    titleMode_ = navBarLayoutProperty->GetTitleModeValue(NavigationTitleMode::FREE);

    auto parent = hostNode->GetParent();
    CHECK_NULL_VOID(parent);
    titleBarNode->SetInnerParentId(parent->GetInspectorId().value_or(""));
    auto layoutPolicy = navBarLayoutProperty->GetLayoutPolicyProperty();
    if (layoutPolicy.has_value()) {
        auto content = AceType::DynamicCast<FrameNode>(hostNode->GetContentNode());
        CHECK_NULL_VOID(content);
        content->GetLayoutProperty()->UpdateLayoutPolicyProperty(
            layoutPolicy.value().widthLayoutPolicy_.value_or(LayoutCalPolicy::NO_MATCH), true);
        content->GetLayoutProperty()->UpdateLayoutPolicyProperty(
            layoutPolicy.value().heightLayoutPolicy_.value_or(LayoutCalPolicy::NO_MATCH), false);
    }
}

void NavBarPattern::OnWindowSizeChanged(int32_t width, int32_t height, WindowSizeChangeReason type)
{
    auto navBarNode = AceType::DynamicCast<NavBarNode>(GetHost());
    CHECK_NULL_VOID(navBarNode);
    if (preWidth_.has_value() && preWidth_.value() != width) {
        AbortBarAnimation();
    }
    preWidth_ = width;
    // change menu num in landscape and orientation
    do {
        if (navBarNode->GetPrevMenuIsCustomValue(false)) {
            break;
        }
        auto targetNum = SystemProperties::GetDeviceOrientation() == DeviceOrientation::LANDSCAPE ? MAX_MENU_NUM_LARGE
                                                                                                  : MAX_MENU_NUM_SMALL;
        if (targetNum == maxMenuNums_) {
            break;
        }
        maxMenuNums_ = targetNum;
        auto titleBarNode = AceType::DynamicCast<TitleBarNode>(navBarNode->GetTitleBarNode());
        CHECK_NULL_VOID(titleBarNode);
        BuildMenu(navBarNode, titleBarNode);
        titleBarNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF_AND_CHILD);
    } while (0);
}

void NavBarPattern::OnDetachFromFrameNode(FrameNode* frameNode)
{
    CHECK_NULL_VOID(frameNode);
    auto pipeline = frameNode->GetContextWithCheck();
    CHECK_NULL_VOID(pipeline);
    pipeline->RemoveWindowSizeChangeCallback(frameNode->GetId());
    NavDestinationPatternBase::RemoveOnTouchEvent(frameNode);
}

bool NavBarPattern::CanCoordScrollUp(float offset) const
{
    auto hostNode = AceType::DynamicCast<NavBarNode>(GetHost());
    CHECK_NULL_RETURN(hostNode, false);
    auto titleNode = AceType::DynamicCast<TitleBarNode>(hostNode->GetTitleBarNode());
    CHECK_NULL_RETURN(titleNode, false);
    auto titlePattern = titleNode->GetPattern<TitleBarPattern>();
    CHECK_NULL_RETURN(titlePattern, false);
    return (Negative(offset) && !titlePattern->IsCurrentMinTitle()) || IsNeedHandleScroll();
}

float NavBarPattern::GetTitleBarHeightLessThanMaxBarHeight() const
{
    auto hostNode = AceType::DynamicCast<NavBarNode>(GetHost());
    CHECK_NULL_RETURN(hostNode, 0.f);
    auto titleBarNode = AceType::DynamicCast<TitleBarNode>(hostNode->GetTitleBarNode());
    CHECK_NULL_RETURN(titleBarNode, 0.f);
    auto titlePattern = titleBarNode->GetPattern<TitleBarPattern>();
    CHECK_NULL_RETURN(titlePattern, 0.f);
    return titlePattern->GetTitleBarHeightLessThanMaxBarHeight();
}

bool NavBarPattern::OnDirtyLayoutWrapperSwap(const RefPtr<LayoutWrapper>& dirty, const DirtySwapConfig& config)
{
    auto hostNode = AceType::DynamicCast<NavBarNode>(GetHost());
    CHECK_NULL_RETURN(hostNode, false);
    hostNode->AdjustRenderContextIfNeeded();
    return false;
}

void NavBarPattern::BeforeCreateLayoutWrapper()
{
    auto eventHub = GetEventHub<NavBarEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->FireBeforeCreateLayoutWrapperCallBack();
}
} // namespace OHOS::Ace::NG
