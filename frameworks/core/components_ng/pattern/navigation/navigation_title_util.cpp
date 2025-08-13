/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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

#include "core/components_ng/pattern/navigation/navigation_title_util.h"

#include "base/i18n/localization.h"
#include "base/subwindow/subwindow_manager.h"
#include "base/utils/system_properties.h"
#include "base/utils/utf_helper.h"
#include "core/common/agingadapation/aging_adapation_dialog_theme.h"
#include "core/common/agingadapation/aging_adapation_dialog_util.h"
#include "core/common/container.h"
#include "core/components_ng/base/view_abstract.h"
#include "core/components_ng/pattern/bubble/bubble_pattern.h"
#include "core/components_ng/pattern/button/button_layout_property.h"
#include "core/components_ng/pattern/button/button_pattern.h"
#include "core/components_ng/pattern/grid/grid_pattern.h"
#include "core/components_ng/pattern/image/image_layout_property.h"
#include "core/components_ng/pattern/image/image_pattern.h"
#include "core/components_ng/pattern/menu/menu_view.h"
#include "core/components_ng/pattern/menu/wrapper/menu_wrapper_pattern.h"
#include "core/components_ng/pattern/navigation/bar_item_event_hub.h"
#include "core/components_ng/pattern/navigation/bar_item_pattern.h"
#include "core/components_ng/pattern/navigation/nav_bar_pattern.h"
#include "core/components_ng/pattern/navigation/navdestination_node_base.h"
#include "core/components_ng/pattern/navigation/navdestination_pattern_base.h"
#include "core/components_ng/pattern/navigation/navigation_pattern.h"
#include "core/components_ng/pattern/navigation/title_bar_node.h"
#include "core/components_ng/pattern/navigation/title_bar_pattern.h"
#include "core/components_ng/pattern/navigation/tool_bar_node.h"
#include "core/components_ng/pattern/text/text_pattern.h"

namespace OHOS::Ace::NG {
namespace {
constexpr Dimension TITLEBAR_VERTICAL_PADDING = 56.0_vp;
constexpr int32_t TITLEBAR_OPACITY_ANIMATION_DURATION = 120;
constexpr int32_t DEFAULT_ANIMATION_DURATION = 450;
const RefPtr<CubicCurve> TITLEBAR_OPACITY_ANIMATION_CURVE = AceType::MakeRefPtr<CubicCurve>(0.4, 0.0, 0.4, 1.0);
}

bool NavigationTitleUtil::BuildMoreButton(bool isButtonEnabled, const RefPtr<NavigationBarTheme>& theme,
    const RefPtr<NavDestinationNodeBase>& nodeBase, const RefPtr<FrameNode>& menuNode,
    std::vector<OptionParam>&& params, const std::string& field, const std::string& parentId,
    bool isCreateLandscapeMenu)
{
    auto barItemNode = CreateBarItemNode(isButtonEnabled, theme);
    CHECK_NULL_RETURN(barItemNode, false);
    auto menuItemNode = CreateMenuItemButton(theme);
    CHECK_NULL_RETURN(menuItemNode, false);
    CHECK_NULL_RETURN(nodeBase, false);
    auto navDestinationPattern = nodeBase->GetPattern<NavDestinationPattern>();
    CHECK_NULL_RETURN(navDestinationPattern, false);
    MenuParam menuParam;
    menuParam.isShowInSubWindow = false;
    menuParam.placement = Placement::BOTTOM_RIGHT;
    if (SystemProperties::GetDeviceType() == DeviceType::TWO_IN_ONE) {
        menuParam.isShowInSubWindow = true;
    }
    NavigationMenuOptions menuOptions = navDestinationPattern->GetMenuOptions();
    if (menuOptions.mbOptions.bgOptions.blurStyleOption.has_value()) {
        menuParam.backgroundBlurStyleOption = menuOptions.mbOptions.bgOptions.blurStyleOption.value();
    }
    if (menuOptions.mbOptions.bgOptions.effectOption.has_value()) {
        menuParam.backgroundEffectOption = menuOptions.mbOptions.bgOptions.effectOption.value();
    }
    auto barMenuNode = MenuView::Create(
        std::move(params), menuItemNode->GetId(), menuItemNode->GetTag(), MenuType::NAVIGATION_MENU, menuParam);
    BuildMoreItemNodeAction(menuItemNode, barItemNode, barMenuNode, menuParam);
    auto iconNode = AceType::DynamicCast<FrameNode>(barItemNode->GetChildren().front());
    InitTitleBarButtonEvent(menuItemNode, iconNode, true);

    // read navdestination "more" button
    std::string message = theme ? theme->GetMoreMessage() : "";
    SetAccessibility(menuItemNode, message);

    // set navdestination titleBar "more" button inspectorId
    SetInnerChildId(menuItemNode, field, menuNode->GetTag(), "More", parentId);

    barItemNode->MountToParent(menuItemNode);
    barItemNode->MarkModifyDone();
    menuItemNode->MarkModifyDone();
    CHECK_NULL_RETURN(menuNode, false);
    menuNode->AddChild(menuItemNode);
    if (isCreateLandscapeMenu) {
        nodeBase->SetLandscapeMenuNode(barMenuNode);
    } else {
        nodeBase->SetMenuNode(barMenuNode);
    }
    return true;
}

RefPtr<FrameNode> NavigationTitleUtil::CreateMenuItems(const int32_t menuNodeId,
    const std::vector<NG::BarItem>& menuItems, const RefPtr<NavDestinationNodeBase>& navDestinationNodeBase,
    bool isButtonEnabled, const std::string& field, const std::string& parentId, bool isCreateLandscapeMenu)
{
    auto menuNode = FrameNode::GetOrCreateFrameNode(
        V2::NAVIGATION_MENU_ETS_TAG, menuNodeId, []() { return AceType::MakeRefPtr<LinearLayoutPattern>(false); });
    CHECK_NULL_RETURN(menuNode, nullptr);
    menuNode->Clean();
    menuNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    auto rowProperty = menuNode->GetLayoutProperty<LinearLayoutProperty>();
    CHECK_NULL_RETURN(rowProperty, nullptr);
    rowProperty->UpdateMainAxisAlign(FlexAlign::SPACE_BETWEEN);
    auto theme = NavigationGetTheme(navDestinationNodeBase->GetThemeScopeId());
    CHECK_NULL_RETURN(theme, nullptr);
    auto mostMenuItemCount = GetOrInitMaxMenuNums(theme, navDestinationNodeBase);
    bool needMoreButton = menuItems.size() > mostMenuItemCount;

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
            auto menuItemNode = CreateMenuItemNode(theme, menuItem, isButtonEnabled);
            CHECK_NULL_RETURN(menuItemNode, nullptr);

            // set titleBar menuitem inspectorId
            std::string menuItemId = menuItemNode->GetTag() + std::to_string(count);
            NavigationTitleUtil::SetInnerChildId(menuItemNode, field, menuNode->GetTag(), menuItemId, parentId);

            // read menu button
            SetAccessibility(menuItemNode, menuItem.text.value_or(""));
            menuNode->AddChild(menuItemNode);
        }
    }

    // build more button
    if (needMoreButton) {
        bool buildMoreButtonResult = BuildMoreButton(isButtonEnabled, theme, navDestinationNodeBase,
            menuNode, std::move(params), field, parentId, isCreateLandscapeMenu);
        if (!buildMoreButtonResult) {
            TAG_LOGI(AceLogTag::ACE_NAVIGATION, "build more button node failed");
            return nullptr;
        }
    }
    auto titleBarNode = AceType::DynamicCast<TitleBarNode>(navDestinationNodeBase->GetTitleBarNode());
    CHECK_NULL_RETURN(titleBarNode, nullptr);
    auto titleBarPattern = titleBarNode->GetPattern<TitleBarPattern>();
    CHECK_NULL_RETURN(titleBarPattern, nullptr);
    titleBarPattern->InitMenuDragAndLongPressEvent(menuNode, menuItems);
    return menuNode;
}

uint32_t NavigationTitleUtil::GetOrInitMaxMenuNums(
    const RefPtr<NavigationBarTheme>& theme, const RefPtr<NavDestinationNodeBase>& navDestinationNodeBase)
{
    auto patternBase = navDestinationNodeBase->GetPattern<NavDestinationPatternBase>();
    CHECK_NULL_RETURN(patternBase, 0);
    auto navDesMaxNum = patternBase->GetMaxMenuNum();
    auto mostMenuItemCount =
        navDesMaxNum < 0 ? theme->GetMostMenuItemCountInBar() : static_cast<uint32_t>(navDesMaxNum);
    mostMenuItemCount = SystemProperties::GetDeviceOrientation() == DeviceOrientation::LANDSCAPE ? MAX_MENU_NUM_LARGE
                                                                                                 : mostMenuItemCount;
    patternBase->SetMaxMenuNum(mostMenuItemCount);
    return mostMenuItemCount;
}

void NavigationTitleUtil::BuildMoreItemNodeAction(const RefPtr<FrameNode>& buttonNode,
    const RefPtr<BarItemNode>& barItemNode, const RefPtr<FrameNode>& barMenuNode, const MenuParam& menuParam)
{
    auto eventHub = barItemNode->GetOrCreateEventHub<BarItemEventHub>();
    CHECK_NULL_VOID(eventHub);

    auto context = PipelineContext::GetCurrentContext();
    auto clickCallback = [weakContext = WeakPtr<PipelineContext>(context), 
                            id = barItemNode->GetId(),
                            param = menuParam,
                            weakMenu = WeakPtr<FrameNode>(barMenuNode),
                            weakBarItemNode = WeakPtr<BarItemNode>(barItemNode)]() {
        auto context = weakContext.Upgrade();
        CHECK_NULL_VOID(context);

        auto overlayManager = context->GetOverlayManager();
        CHECK_NULL_VOID(overlayManager);

        auto menu = weakMenu.Upgrade();
        CHECK_NULL_VOID(menu);

        auto barItemNode = weakBarItemNode.Upgrade();
        OffsetF offset(0.0f, 0.0f);
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

RefPtr<FrameNode> NavigationTitleUtil::CreateMenuItemNode(
    const RefPtr<NavigationBarTheme>& theme, const BarItem& menuItem, bool isButtonEnabled)
{
    auto menuItemNode = CreateMenuItemButton(theme);
    CHECK_NULL_RETURN(menuItemNode, nullptr);

    int32_t barItemNodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto barItemNode = BarItemNode::GetOrCreateBarItemNode(
        V2::BAR_ITEM_ETS_TAG, barItemNodeId, []() { return AceType::MakeRefPtr<BarItemPattern>(); });
    UpdateBarItemNodeWithItem(barItemNode, menuItem, isButtonEnabled, theme);
    auto iconNode = AceType::DynamicCast<FrameNode>(barItemNode->GetChildren().front());
    InitTitleBarButtonEvent(menuItemNode, iconNode, false, menuItem, menuItem.isEnabled.value_or(true));
    auto barItemLayoutProperty = barItemNode->GetLayoutProperty();
    CHECK_NULL_RETURN(barItemLayoutProperty, nullptr);
    barItemLayoutProperty->UpdateMeasureType(MeasureType::MATCH_PARENT);

    barItemNode->MountToParent(menuItemNode);
    barItemNode->MarkModifyDone();
    menuItemNode->MarkModifyDone();
    return menuItemNode;
}

RefPtr<FrameNode> NavigationTitleUtil::CreateMenuItemButton(const RefPtr<NavigationBarTheme>& theme)
{
    auto buttonPattern = AceType::MakeRefPtr<NG::ButtonPattern>();
    CHECK_NULL_RETURN(buttonPattern, nullptr);
    buttonPattern->setComponentButtonType(ComponentButtonType::NAVIGATION);
    if (AceApplicationInfo::GetInstance().GreatOrEqualTargetAPIVersion(PlatformVersion::VERSION_TWELVE)) {
        buttonPattern->SetBlendColor(theme->GetBackgroundPressedColor(), theme->GetBackgroundHoverColor());
        buttonPattern->SetFocusBorderColor(theme->GetBackgroundFocusOutlineColor());
        buttonPattern->SetFocusBorderWidth(theme->GetBackgroundFocusOutlineWeight());
    } else {
        buttonPattern->SetFocusBorderColor(theme->GetToolBarItemFocusColor());
        buttonPattern->SetFocusBorderWidth(theme->GetToolBarItemFocusBorderWidth());
    }
    auto menuItemNode = FrameNode::CreateFrameNode(
        V2::MENU_ITEM_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), buttonPattern);
    CHECK_NULL_RETURN(menuItemNode, nullptr);
    auto focusHub = menuItemNode->GetOrCreateFocusHub();
    CHECK_NULL_RETURN(focusHub, nullptr);
    focusHub->SetFocusDependence(FocusDependence::SELF);
    auto menuItemLayoutProperty = menuItemNode->GetLayoutProperty<ButtonLayoutProperty>();
    CHECK_NULL_RETURN(menuItemLayoutProperty, nullptr);
    menuItemLayoutProperty->UpdateType(ButtonType::NORMAL);
    auto renderContext = menuItemNode->GetRenderContext();
    CHECK_NULL_RETURN(renderContext, nullptr);
    if (AceApplicationInfo::GetInstance().GreatOrEqualTargetAPIVersion(PlatformVersion::VERSION_TWELVE)) {
        auto iconBackgroundWidth = theme->GetIconBackgroundWidth();
        auto iconBackgroundHeight = theme->GetIconBackgroundHeight();
        menuItemLayoutProperty->UpdateUserDefinedIdealSize(
            CalcSize(CalcLength(iconBackgroundWidth), CalcLength(iconBackgroundHeight)));
        menuItemLayoutProperty->UpdateBorderRadius(BorderRadiusProperty(theme->GetCornerRadius()));
        renderContext->UpdateBackgroundColor(theme->GetCompBackgroundColor());
        PaddingProperty padding;
        padding.SetEdges(CalcLength(MENU_BUTTON_PADDING));
        menuItemLayoutProperty->UpdatePadding(padding);
        MarginProperty margin;
        margin.right = CalcLength(theme->GetCompPadding());
        margin.end = CalcLength(theme->GetCompPadding());
        menuItemLayoutProperty->UpdateMargin(margin);
    } else {
        menuItemLayoutProperty->UpdateUserDefinedIdealSize(
            CalcSize(CalcLength(BACK_BUTTON_SIZE), CalcLength(BACK_BUTTON_SIZE)));
        menuItemLayoutProperty->UpdateBorderRadius(BorderRadiusProperty(BUTTON_RADIUS_SIZE));
        renderContext->UpdateBackgroundColor(Color::TRANSPARENT);
        PaddingProperty padding;
        padding.SetEdges(CalcLength(BUTTON_PADDING));
        menuItemLayoutProperty->UpdatePadding(padding);
    }
    return menuItemNode;
}

RefPtr<FrameNode> NavigationTitleUtil::CreateBarItemTextNode(const std::string& text)
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

void UpdateSymbolEffect(RefPtr<TextLayoutProperty> symbolProperty, bool isActive)
{
    CHECK_NULL_VOID(symbolProperty);
    auto symbolEffectOptions = SymbolEffectOptions(SymbolEffectType::BOUNCE);
    symbolEffectOptions.SetIsTxtActive(isActive);
    symbolEffectOptions.SetIsTxtActiveSource(0);
    symbolProperty->UpdateSymbolEffectOptions(symbolEffectOptions);
}

RefPtr<FrameNode> NavigationTitleUtil::CreateBarItemIconNode(
    const BarItem& barItem, const bool isButtonEnabled, const RefPtr<NavigationBarTheme>& theme)
{
    CHECK_NULL_RETURN(theme, nullptr);

    Color iconColor = theme->GetMenuIconColor();
    double iconOpacity = theme->GetAlphaDisabled();
    auto iconWidth = theme->GetMenuIconSize();
    auto iconHeight = theme->GetMenuIconSize();
    if (AceApplicationInfo::GetInstance().GreatOrEqualTargetAPIVersion(PlatformVersion::VERSION_TWELVE)) {
        iconColor = theme->GetIconColor();
        iconOpacity = theme->GetIconDisableAlpha();
        iconWidth = theme->GetIconWidth();
        iconHeight = theme->GetIconHeight();
    }

    if (barItem.iconSymbol.has_value() && barItem.iconSymbol.value() != nullptr) {
        auto iconNode = FrameNode::GetOrCreateFrameNode(V2::SYMBOL_ETS_TAG,
            ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TextPattern>(); });
        CHECK_NULL_RETURN(iconNode, nullptr);
        auto symbolProperty = iconNode->GetLayoutProperty<TextLayoutProperty>();
        CHECK_NULL_RETURN(symbolProperty, nullptr);
        if (isButtonEnabled) {
            symbolProperty->UpdateSymbolColorList({ iconColor });
        } else {
            symbolProperty->UpdateSymbolColorList({ iconColor.BlendOpacity(iconOpacity) });
        }
        barItem.iconSymbol.value()(AccessibilityManager::WeakClaim(AccessibilityManager::RawPtr(iconNode)));
        UpdateSymbolEffect(symbolProperty, false);
        symbolProperty->UpdateFontSize(iconWidth);
        iconNode->MarkModifyDone();
        return iconNode;
    }
    int32_t nodeId = ElementRegister::GetInstance()->MakeUniqueId();
    ImageSourceInfo info(barItem.icon.value());
    auto iconNode = FrameNode::CreateFrameNode(V2::IMAGE_ETS_TAG, nodeId, AceType::MakeRefPtr<ImagePattern>());
    auto imageLayoutProperty = iconNode->GetLayoutProperty<ImageLayoutProperty>();
    CHECK_NULL_RETURN(imageLayoutProperty, nullptr);
    if (isButtonEnabled) {
        info.SetFillColor(iconColor);
    } else {
        info.SetFillColor(iconColor.BlendOpacity(iconOpacity));
    }
    imageLayoutProperty->UpdateImageSourceInfo(info);
    imageLayoutProperty->UpdateUserDefinedIdealSize(CalcSize(CalcLength(iconWidth), CalcLength(iconHeight)));
    iconNode->MarkModifyDone();
    return iconNode;
}

void NavigationTitleUtil::InitTitleBarButtonEvent(const RefPtr<FrameNode>& buttonNode,
    const RefPtr<FrameNode>& iconNode, bool isMoreButton, const BarItem& menuItem, bool isButtonEnabled)
{
    auto eventHub = buttonNode->GetOrCreateInputEventHub();
    CHECK_NULL_VOID(eventHub);

    if (isMoreButton) {
        auto hoverTask = [weakTargetNode = WeakPtr<FrameNode>(buttonNode)](bool isHover) {
            auto targetNode = weakTargetNode.Upgrade();
            CHECK_NULL_VOID(targetNode);
            auto popupParam = AceType::MakeRefPtr<PopupParam>();
            auto theme = NavigationGetTheme();
            CHECK_NULL_VOID(theme);
            popupParam->SetMessage(theme->GetMoreMessage());
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
        auto clickCallback = [action = menuItem.action, weakNode = WeakPtr<FrameNode>(iconNode)](GestureEvent& info) {
            if (info.GetSourceDevice() == SourceType::KEYBOARD) {
                return;
            }
            if (action) {
                action();
            }
            auto symbol = weakNode.Upgrade();
            CHECK_NULL_VOID(symbol);
            if (symbol->GetTag() == V2::SYMBOL_ETS_TAG) {
                auto symbolProperty = symbol->GetLayoutProperty<TextLayoutProperty>();
                CHECK_NULL_VOID(symbolProperty);
                auto symbolEffectOptions = symbolProperty->GetSymbolEffectOptionsValue(SymbolEffectOptions());
                symbolEffectOptions.SetEffectType(SymbolEffectType::BOUNCE);
                symbolEffectOptions.SetIsTxtActive(true);
                symbolEffectOptions.SetIsTxtActiveSource(0);
                symbolProperty->UpdateSymbolEffectOptions(symbolEffectOptions);
                symbol->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
            }
        };
        gestureEventHub->AddClickEvent(AceType::MakeRefPtr<ClickEvent>(clickCallback));
    }

    auto buttonEvent = buttonNode->GetOrCreateEventHub<ButtonEventHub>();
    CHECK_NULL_VOID(buttonEvent);
    buttonEvent->SetEnabled(isButtonEnabled);
    auto focusHub = buttonNode->GetFocusHub();
    CHECK_NULL_VOID(focusHub);
    focusHub->SetEnabled(isButtonEnabled);
}

void NavigationTitleUtil::UpdateBarItemNodeWithItem(const RefPtr<BarItemNode>& barItemNode, const BarItem& barItem,
    const bool isButtonEnabled, const RefPtr<NavigationBarTheme>& theme)
{
    if (Container::LessThanAPIVersion(PlatformVersion::VERSION_TEN) && barItem.text.has_value() &&
        !barItem.text.value().empty()) {
        auto textNode = CreateBarItemTextNode(barItem.text.value());
        barItemNode->SetTextNode(textNode);
        barItemNode->AddChild(textNode);
    }
    if ((barItem.icon.has_value()) || (barItem.iconSymbol.has_value() && barItem.iconSymbol.value() != nullptr)) {
        auto iconNode = CreateBarItemIconNode(barItem, isButtonEnabled, theme);
        barItemNode->SetIconNode(iconNode);
        barItemNode->AddChild(iconNode);
    }
    if (barItem.action) {
        auto eventHub = barItemNode->GetOrCreateEventHub<BarItemEventHub>();
        CHECK_NULL_VOID(eventHub);
        eventHub->SetItemAction(barItem.action);
    }
    auto barItemPattern = barItemNode->GetPattern<BarItemPattern>();
    barItemNode->MarkModifyDone();
}

void BuildImageMoreItemNode(
    const RefPtr<BarItemNode>& barItemNode, bool isButtonEnabled, const RefPtr<NavigationBarTheme>& theme)
{
    int32_t imageNodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto imageNode = FrameNode::CreateFrameNode(V2::IMAGE_ETS_TAG, imageNodeId, AceType::MakeRefPtr<ImagePattern>());
    CHECK_NULL_VOID(imageNode);
    auto imageLayoutProperty = imageNode->GetLayoutProperty<ImageLayoutProperty>();
    CHECK_NULL_VOID(imageLayoutProperty);
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

void BuildSymbolMoreItemNode(
    const RefPtr<BarItemNode>& barItemNode, bool isButtonEnabled, const RefPtr<NavigationBarTheme>& theme)
{
    CHECK_NULL_VOID(theme);
    auto iconSize = theme->GetMenuIconSize();
    auto symbolNode = FrameNode::GetOrCreateFrameNode(V2::SYMBOL_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TextPattern>(); });
    CHECK_NULL_VOID(symbolNode);
    auto symbolProperty = symbolNode->GetLayoutProperty<TextLayoutProperty>();
    CHECK_NULL_VOID(symbolProperty);
    symbolProperty->UpdateSymbolSourceInfo(SymbolSourceInfo(theme->GetMoreSymbolId()));
    symbolProperty->UpdateFontSize(iconSize);
    if (isButtonEnabled) {
        symbolProperty->UpdateSymbolColorList({ theme->GetMenuIconColor() });
    } else {
        symbolProperty->UpdateSymbolColorList({ theme->GetMenuIconColor().BlendOpacity(theme->GetAlphaDisabled()) });
    }
    symbolNode->MarkModifyDone();
    barItemNode->SetIsMoreItemNode(true);
    barItemNode->SetIconNode(symbolNode);
    barItemNode->AddChild(symbolNode);
    barItemNode->MarkModifyDone();
}

void NavigationTitleUtil::BuildMoreIemNode(
    const RefPtr<BarItemNode>& barItemNode, bool isButtonEnabled, const RefPtr<NavigationBarTheme>& theme)
{
    if (AceApplicationInfo::GetInstance().GreatOrEqualTargetAPIVersion(PlatformVersion::VERSION_TWELVE) &&
        SystemProperties::IsNeedSymbol()) {
        BuildSymbolMoreItemNode(barItemNode, isButtonEnabled, theme);
    } else {
        BuildImageMoreItemNode(barItemNode, isButtonEnabled, theme);
    }
}

RefPtr<BarItemNode> NavigationTitleUtil::CreateBarItemNode(
    bool isButtonEnabled, const RefPtr<NavigationBarTheme>& theme)
{
    int32_t barItemNodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto barItemNode = BarItemNode::GetOrCreateBarItemNode(
        V2::BAR_ITEM_ETS_TAG, barItemNodeId, []() { return AceType::MakeRefPtr<BarItemPattern>(); });
    auto barItemLayoutProperty = barItemNode->GetLayoutProperty();
    CHECK_NULL_RETURN(barItemLayoutProperty, nullptr);
    barItemLayoutProperty->UpdateMeasureType(MeasureType::MATCH_PARENT);
    BuildMoreIemNode(barItemNode, isButtonEnabled, theme);
    return barItemNode;
}

RefPtr<FrameNode> NavigationTitleUtil::CreatePopupDialogNode(
    const RefPtr<FrameNode> targetNode, const std::vector<NG::BarItem>& menuItems, int32_t index, int32_t themeScopeId)
{
    CHECK_NULL_RETURN(targetNode, nullptr);
    RefPtr<BarItemNode> barItemNode = AceType::DynamicCast<BarItemNode>(targetNode->GetFirstChild());
    CHECK_NULL_RETURN(barItemNode, nullptr);
    auto accessibilityProperty = targetNode->GetAccessibilityProperty<AccessibilityProperty>();
    CHECK_NULL_RETURN(accessibilityProperty, nullptr);
    ImageSourceInfo imageSourceInfo;
    std::string message;
    RefPtr<FrameNode> dialogNode;
    if (barItemNode->IsMoreItemNode()) {
        auto theme = NavigationGetTheme();
        CHECK_NULL_RETURN(theme, nullptr);
        message = theme->GetMoreMessage();
        if (message.empty()) {
            message = accessibilityProperty->GetAccessibilityText();
        }
        if (AceApplicationInfo::GetInstance().GreatOrEqualTargetAPIVersion(PlatformVersion::VERSION_TWELVE)) {
            auto symbolNode = AceType::DynamicCast<FrameNode>(barItemNode->GetFirstChild());
            CHECK_NULL_RETURN(symbolNode, nullptr);
            dialogNode = AgingAdapationDialogUtil::ShowLongPressDialog(message, symbolNode);
            return dialogNode;
        }
        imageSourceInfo.SetResourceId(theme->GetMoreResourceId());
        dialogNode = AgingAdapationDialogUtil::ShowLongPressDialog(message, imageSourceInfo, themeScopeId);
        return dialogNode;
    }
    if (index < 0 || index >= static_cast<int32_t>(menuItems.size())) {
        return nullptr;
    }
    auto menuItem = menuItems.at(index);
    if (menuItem.text.has_value() && !menuItem.text.value().empty()) {
        message = menuItem.text.value();
    } else {
        message = accessibilityProperty->GetAccessibilityText();
    }
    if (menuItem.iconSymbol.has_value() && menuItem.iconSymbol.value() != nullptr) {
        return CreateSymbolDialog(message, barItemNode, themeScopeId);
    }
    if (menuItem.icon.has_value() && !menuItem.icon.value().empty()) {
        imageSourceInfo = ImageSourceInfo(menuItem.icon.value());
    }
    dialogNode = AgingAdapationDialogUtil::ShowLongPressDialog(message, imageSourceInfo, themeScopeId);
    return dialogNode;
}

RefPtr<FrameNode> NavigationTitleUtil::CreateSymbolDialog(
    const std::string& message, const RefPtr<FrameNode>& targetNode, int32_t themeScopeId)
{
    auto barItemNode = AceType::DynamicCast<BarItemNode>(targetNode);
    CHECK_NULL_RETURN(barItemNode, nullptr);
    auto iconNode = AceType::DynamicCast<FrameNode>(barItemNode->GetIconNode());
    CHECK_NULL_RETURN(iconNode, nullptr);
    return AgingAdapationDialogUtil::ShowLongPressDialog(message, iconNode);
}

void NavigationTitleUtil::SetAccessibility(const RefPtr<FrameNode>& node, const std::string& message)
{
    CHECK_NULL_VOID(node);
    auto accessibilityProperty = node->GetAccessibilityProperty<NG::AccessibilityProperty>();
    CHECK_NULL_VOID(accessibilityProperty);
    accessibilityProperty->SetAccessibilityText(message);
    accessibilityProperty->SetAccessibilityGroup(true);
}

std::string NavigationTitleUtil::GetTitleString(const RefPtr<TitleBarNode>& titleBarNode, bool isCustom)
{
    if (isCustom) {
        return "";
    }
    CHECK_NULL_RETURN(titleBarNode, "");
    auto title = AceType::DynamicCast<FrameNode>(titleBarNode->GetTitle());
    CHECK_NULL_RETURN(title, "");
    if (title->GetTag() != V2::TEXT_ETS_TAG) {
        return "";
    }
    auto textLayoutProperty = title->GetLayoutProperty<TextLayoutProperty>();
    CHECK_NULL_RETURN(textLayoutProperty, "");
    return UtfUtils::Str16ToStr8(textLayoutProperty->GetContentValue(u""));
}

std::string NavigationTitleUtil::GetSubtitleString(const RefPtr<TitleBarNode>& titleBarNode)
{
    CHECK_NULL_RETURN(titleBarNode, "");
    auto subtitle = AceType::DynamicCast<FrameNode>(titleBarNode->GetSubtitle());
    CHECK_NULL_RETURN(subtitle, "");
    if (subtitle->GetTag() != V2::TEXT_ETS_TAG) {
        return "";
    }
    auto textLayoutProperty = subtitle->GetLayoutProperty<TextLayoutProperty>();
    CHECK_NULL_RETURN(textLayoutProperty, "");
    return UtfUtils::Str16ToStr8(textLayoutProperty->GetContentValue(u""));
}

float NavigationTitleUtil::ParseCalcDimensionToPx(const std::optional<CalcDimension>& value, const float titleBarWidth)
{
    float result = 0.0f;
    if (value.value().Unit() == DimensionUnit::PERCENT) {
        result = value.value().Value() * titleBarWidth;
    } else {
        result = value.value().ConvertToPx();
    }
    return result;
}

void NavigationTitleUtil::CreateOrUpdateMainTitle(const RefPtr<TitleBarNode>& titleBarNode,
    const NG::NavigationTitleInfo& titleInfo, bool ignoreMainTitle)
{
    CHECK_NULL_VOID(titleBarNode);
    if (ignoreMainTitle) {
        return;
    }
    auto mainTitle = AceType::DynamicCast<FrameNode>(titleBarNode->GetTitle());
    if (!titleInfo.hasMainTitle) {
        // remove main title if any.
        titleBarNode->RemoveChild(mainTitle);
        titleBarNode->SetTitle(nullptr);
        return;
    }

    if (mainTitle) {
        // update main title
        auto textLayoutProperty = mainTitle->GetLayoutProperty<TextLayoutProperty>();
        CHECK_NULL_VOID(textLayoutProperty);
        textLayoutProperty->UpdateMaxLines(titleInfo.hasSubTitle ? 1 : TITLEBAR_MAX_LINES);
        textLayoutProperty->UpdateContent(titleInfo.title);
        return;
    }
    // create and init main title
    mainTitle = FrameNode::CreateFrameNode(
        V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    auto textLayoutProperty = mainTitle->GetLayoutProperty<TextLayoutProperty>();
    CHECK_NULL_VOID(textLayoutProperty);
    textLayoutProperty->UpdateContent(titleInfo.title);
    auto titleBarPattern = titleBarNode->GetPattern<TitleBarPattern>();
    CHECK_NULL_VOID(titleBarPattern);
    titleBarPattern->SetNeedResetMainTitleProperty(true);
    titleBarNode->SetTitle(mainTitle);
    titleBarNode->AddChild(mainTitle);
}

void NavigationTitleUtil::CreateOrUpdateSubtitle(const RefPtr<TitleBarNode>& titleBarNode,
    const NG::NavigationTitleInfo& titleInfo)
{
    CHECK_NULL_VOID(titleBarNode);
    auto subTitle = AceType::DynamicCast<FrameNode>(titleBarNode->GetSubtitle());
    if (!titleInfo.hasSubTitle) {
        // remove subtitle if any.
        titleBarNode->RemoveChild(subTitle);
        titleBarNode->SetSubtitle(nullptr);
        return;
    }
    if (subTitle) {
        // update subtitle
        auto textLayoutProperty = subTitle->GetLayoutProperty<TextLayoutProperty>();
        CHECK_NULL_VOID(textLayoutProperty);
        textLayoutProperty->UpdateContent(titleInfo.subtitle);
        auto renderContext = subTitle->GetRenderContext();
        CHECK_NULL_VOID(renderContext);
        renderContext->UpdateOpacity(1.0);
        return;
    }
    // create and init subtitle
    subTitle = FrameNode::CreateFrameNode(
        V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    auto textLayoutProperty = subTitle->GetLayoutProperty<TextLayoutProperty>();
    CHECK_NULL_VOID(textLayoutProperty);
    textLayoutProperty->UpdateContent(titleInfo.subtitle);
    auto titleBarPattern = titleBarNode->GetPattern<TitleBarPattern>();
    CHECK_NULL_VOID(titleBarPattern);
    titleBarPattern->SetNeedResetSubTitleProperty(true);
    titleBarNode->SetSubtitle(subTitle);
    titleBarNode->AddChild(subTitle);
}

void NavigationTitleUtil::CreateOrUpdateDestinationMainTitle(const RefPtr<TitleBarNode>& titleBarNode,
    const NG::NavigationTitleInfo& titleInfo)
{
    CHECK_NULL_VOID(titleBarNode);
    auto mainTitle = AceType::DynamicCast<FrameNode>(titleBarNode->GetTitle());
    if (!titleInfo.hasMainTitle) {
        // remove main title if any.
        titleBarNode->RemoveChild(mainTitle);
        titleBarNode->SetTitle(nullptr);
        return;
    }
    if (mainTitle) {
        // update main title
        auto textLayoutProperty = mainTitle->GetLayoutProperty<TextLayoutProperty>();
        CHECK_NULL_VOID(textLayoutProperty);
        textLayoutProperty->UpdateMaxLines(titleInfo.hasSubTitle ? 1 : TITLEBAR_MAX_LINES);
        if (AceApplicationInfo::GetInstance().GreatOrEqualTargetAPIVersion(PlatformVersion::VERSION_TWELVE)) {
            textLayoutProperty->UpdateHeightAdaptivePolicy(titleInfo.hasSubTitle ?
            TextHeightAdaptivePolicy::MAX_LINES_FIRST : TextHeightAdaptivePolicy::MIN_FONT_SIZE_FIRST);
        }
        textLayoutProperty->UpdateContent(titleInfo.title);
        textLayoutProperty->UpdateMaxFontScale(STANDARD_FONT_SCALE);
        return;
    }
    // create and init main title
    mainTitle = FrameNode::CreateFrameNode(
        V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    auto textLayoutProperty = mainTitle->GetLayoutProperty<TextLayoutProperty>();
    CHECK_NULL_VOID(textLayoutProperty);
    textLayoutProperty->UpdateContent(titleInfo.title);
    auto titleBarPattern = titleBarNode->GetPattern<TitleBarPattern>();
    CHECK_NULL_VOID(titleBarPattern);
    titleBarPattern->SetNeedResetMainTitleProperty(true);
    titleBarNode->SetTitle(mainTitle);
    titleBarNode->AddChild(mainTitle);
}

void NavigationTitleUtil::CreateOrUpdateDestinationSubtitle(const RefPtr<TitleBarNode>& titleBarNode,
    const NG::NavigationTitleInfo& titleInfo)
{
    CHECK_NULL_VOID(titleBarNode);
    auto subTitle = AceType::DynamicCast<FrameNode>(titleBarNode->GetSubtitle());
    if (!titleInfo.hasSubTitle) {
        // remove subtitle if any.
        titleBarNode->RemoveChild(subTitle);
        titleBarNode->SetSubtitle(nullptr);
        return;
    }
    if (subTitle) {
        // update subtitle
        auto textLayoutProperty = subTitle->GetLayoutProperty<TextLayoutProperty>();
        CHECK_NULL_VOID(textLayoutProperty);
        textLayoutProperty->UpdateContent(titleInfo.subtitle);
        textLayoutProperty->UpdateMaxFontScale(STANDARD_FONT_SCALE);
        return;
    }
    // create and init subtitle
    subTitle = FrameNode::CreateFrameNode(
        V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    auto textLayoutProperty = subTitle->GetLayoutProperty<TextLayoutProperty>();
    CHECK_NULL_VOID(textLayoutProperty);
    textLayoutProperty->UpdateContent(titleInfo.subtitle);
    auto titleBarPattern = titleBarNode->GetPattern<TitleBarPattern>();
    CHECK_NULL_VOID(titleBarPattern);
    titleBarPattern->SetNeedResetSubTitleProperty(true);
    titleBarNode->SetSubtitle(subTitle);
    titleBarNode->AddChild(subTitle);
}

void NavigationTitleUtil::FoldStatusChangedAnimation(const RefPtr<FrameNode>& host)
{
    CHECK_NULL_VOID(host);
    auto pipelineContext = host->GetContext();
    CHECK_NULL_VOID(pipelineContext);
    auto titleBar = AceType::DynamicCast<TitleBarNode>(host);
    CHECK_NULL_VOID(titleBar);
    auto pattern = titleBar->GetPattern<TitleBarPattern>();
    CHECK_NULL_VOID(pattern);

    if (!pipelineContext->IsHoverModeChange() || !IsNeedHoverModeAction(titleBar)) {
        // Since only expanded to hover or hover to expanded need this animation.
        return;
    }

    AnimationOption option;
    option.SetCurve(TITLEBAR_OPACITY_ANIMATION_CURVE);
    auto renderNodeContext = host->GetRenderContext();
    CHECK_NULL_VOID(renderNodeContext);
    option.SetDuration(TITLEBAR_OPACITY_ANIMATION_DURATION);
    renderNodeContext->UpdateOpacity(1.0f);
    option.SetOnFinishEvent([weakRenderNodeContext = WeakPtr<RenderContext>(renderNodeContext),
                                weakHost = WeakPtr<FrameNode>(host)]() {
        auto host = weakHost.Upgrade();
        CHECK_NULL_VOID(host);
        auto renderContext = weakRenderNodeContext.Upgrade();
        CHECK_NULL_VOID(renderContext);
        AnimationOption finishOption;
        finishOption.SetDuration(TITLEBAR_OPACITY_ANIMATION_DURATION);
        finishOption.SetCurve(TITLEBAR_OPACITY_ANIMATION_CURVE);
        auto parent = AceType::DynamicCast<FrameNode>(host->GetParent());
        CHECK_NULL_VOID(parent);
        parent->MarkDirtyNode(PROPERTY_UPDATE_LAYOUT);
        AnimationUtils::Animate(
            finishOption, [weakRenderNodeContext = WeakPtr<RenderContext>(renderContext)]() {
                auto renderNodeContext = weakRenderNodeContext.Upgrade();
                CHECK_NULL_VOID(renderNodeContext);
                renderNodeContext->UpdateOpacity(1.0f);
            }, nullptr /* finishCallback*/, nullptr /* repeatCallback */, host->GetContextRefPtr());
    });
    AnimationUtils::Animate(
        option,
        [weakRenderNodeContext = WeakPtr<RenderContext>(renderNodeContext)]() {
            auto renderContext = weakRenderNodeContext.Upgrade();
            CHECK_NULL_VOID(renderContext);
            renderContext->UpdateOpacity(0.0f);
        },
        option.GetOnFinishEvent(), nullptr /* repeatCallback */, titleBar->GetContextRefPtr());
}

bool NavigationTitleUtil::IsNeedHoverModeAction(const RefPtr<TitleBarNode>& titleBarNode)
{
    CHECK_NULL_RETURN(titleBarNode, false);
    auto pattern = titleBarNode->GetPattern<TitleBarPattern>();
    CHECK_NULL_RETURN(pattern, false);
    auto options = pattern->GetTitleBarOptions();
    auto titleBarLayoutProperty = titleBarNode->GetLayoutProperty<TitleBarLayoutProperty>();
    CHECK_NULL_RETURN(titleBarLayoutProperty, false);
    auto parentType = titleBarLayoutProperty->GetTitleBarParentTypeValue(TitleBarParentType::NAVBAR);
    if (parentType == TitleBarParentType::NAVBAR &&
        titleBarLayoutProperty->GetTitleModeValue(NavigationTitleMode::MINI) == NavigationTitleMode::FREE) {
        return false;
    }
    if (!options.enableHoverMode || options.brOptions.barStyle == NG::BarStyle::STANDARD) {
        return false;
    }
    RefPtr<NavigationGroupNode> navigationGroupNode;
    if (parentType == TitleBarParentType::NAVBAR) {
        auto navBarNode = AceType::DynamicCast<NavBarNode>(titleBarNode->GetParent());
        CHECK_NULL_RETURN(navBarNode, false);
        navigationGroupNode = AceType::DynamicCast<NavigationGroupNode>(navBarNode->GetParent());
    } else {
        auto navDestination = AceType::DynamicCast<NavDestinationGroupNode>(titleBarNode->GetParent());
        CHECK_NULL_RETURN(navDestination, false);
        auto navDestinationPattern = navDestination->GetPattern<NavDestinationPattern>();
        CHECK_NULL_RETURN(navDestinationPattern, false);
        navigationGroupNode = AceType::DynamicCast<NavigationGroupNode>(navDestinationPattern->GetNavigationNode());
    }
    CHECK_NULL_RETURN(navigationGroupNode, false);
    auto navigationPattern = AceType::DynamicCast<NavigationPattern>(navigationGroupNode->GetPattern());
    CHECK_NULL_RETURN(navigationPattern, false);
    auto pageNode = navigationPattern->GetNavBasePageNode();
    CHECK_NULL_RETURN(pageNode, false);
    auto foldCreaseRects = pattern->GetFoldCreaseRects();
    auto parentNode = AceType::DynamicCast<FrameNode>(titleBarNode->GetParent());
    CHECK_NULL_RETURN(parentNode, false);
    bool isParentFullPage = pageNode->GetGeometryNode()->GetFrameSize().Height()
        == parentNode->GetGeometryNode()->GetFrameSize().Height();
    return !foldCreaseRects.empty() && isParentFullPage;
}

float NavigationTitleUtil::CalculateTitlebarOffset(const RefPtr<UINode>& titleBarNode)
{
    CHECK_NULL_RETURN(titleBarNode, 0.0f);
    auto titleBar = AceType::DynamicCast<TitleBarNode>(titleBarNode);
    CHECK_NULL_RETURN(titleBar, 0.0f);
    if (!IsNeedHoverModeAction(titleBar)) {
        return 0.0f;
    }
    auto pattern = titleBar->GetPattern<TitleBarPattern>();
    CHECK_NULL_RETURN(pattern, false);
    auto foldCreaseRects = pattern->GetFoldCreaseRects();
    auto pipelineContext = titleBar->GetContext();
    CHECK_NULL_RETURN(pipelineContext, 0.0f);
    if (!pipelineContext->IsHalfFoldHoverStatus()) {
        return 0.0f;
    }
    auto safeArea = pipelineContext->GetSafeAreaWithoutProcess();
    auto length = safeArea.top_.Length();
    auto foldCrease = foldCreaseRects.front();
    
    // offsetY = The Y of the foldCrease + Adapt vertical displacement of hover state - the height of the status bar.
    return foldCrease.GetOffset().GetY() + TITLEBAR_VERTICAL_PADDING.ConvertToPx() - length;
}

void NavigationTitleUtil::UpdateTitleOrToolBarTranslateYAndOpacity(const RefPtr<NavDestinationNodeBase>& nodeBase,
    const RefPtr<FrameNode>& barNode, float translate, bool isTitle)
{
    CHECK_NULL_VOID(nodeBase);
    CHECK_NULL_VOID(barNode);
    auto renderContext = barNode->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    auto option = renderContext->GetTransformTranslateValue(TranslateOptions(0.0f, 0.0f, 0.0f));
    option.y = CalcDimension(translate, DimensionUnit::PX);
    renderContext->UpdateTransformTranslate(option);
    auto barHeight = renderContext->GetPaintRectWithoutTransform().Height();
    float opacity = 1.0f;
    if (!NearZero(barHeight)) {
        opacity = 1.0f - std::clamp(std::abs(translate) / barHeight, 0.0f, 1.0f);
    }
    renderContext->UpdateOpacity(opacity);
    if (isTitle) {
        return;
    }
    auto divider = AceType::DynamicCast<FrameNode>(nodeBase->GetToolBarDividerNode());
    CHECK_NULL_VOID(divider);
    auto dividerRenderContext = divider->GetRenderContext();
    CHECK_NULL_VOID(dividerRenderContext);
    dividerRenderContext->UpdateTransformTranslate(option);
    dividerRenderContext->UpdateOpacity(opacity);
}

bool NavigationTitleUtil::IsTitleBarHasOffsetY(const RefPtr<FrameNode>& titleBarNode)
{
    return titleBarNode && titleBarNode->IsVisible() && !NearZero(CalculateTitlebarOffset(titleBarNode));
}

bool NavigationTitleUtil::SetTitleAnimationElapsedTime(AnimationOption& option, const RefPtr<FrameNode>& pushEnterNode)
{
    auto pushEnterNavDestination = AceType::DynamicCast<NavDestinationGroupNode>(pushEnterNode);
    CHECK_NULL_RETURN(pushEnterNavDestination, false);
    if (pushEnterNavDestination->IsTitleConsumedElapsedTime() ||
        pushEnterNavDestination->GetSystemTransitionType() != NavigationSystemTransitionType::TITLE) {
        return false;
    }
    auto elapsedTime = pushEnterNavDestination->GetTitleAnimationElapsedTime();
    if (elapsedTime <= 0 || elapsedTime > DEFAULT_ANIMATION_DURATION) {
        return false;
    }
    TAG_LOGI(AceLogTag::ACE_NAVIGATION,
        "will skip %{public}d ms animation for enter push NavDestination node", elapsedTime);
    // elapsed time is the TIME to skip
    option.SetDelay(option.GetDelay() - elapsedTime);
    pushEnterNavDestination->MarkTitleConsumedElapsedTime();
    return true;
}
} // namespace OHOS::Ace::NG
