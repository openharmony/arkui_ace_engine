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

#include "core/components_ng/pattern/navigation/navigation_toolbar_util.h"

#include "base/i18n/localization.h"
#include "core/common/agingadapation/aging_adapation_dialog_theme.h"
#include "core/common/agingadapation/aging_adapation_dialog_util.h"
#include "core/common/container.h"
#include "core/components_ng/base/view_abstract.h"
#include "core/components_ng/pattern/bubble/bubble_pattern.h"
#include "core/components_ng/pattern/button/button_layout_property.h"
#include "core/components_ng/pattern/button/button_pattern.h"
#include "core/components_ng/pattern/divider/divider_pattern.h"
#include "core/components_ng/pattern/grid/grid_pattern.h"
#include "core/components_ng/pattern/image/image_layout_property.h"
#include "core/components_ng/pattern/image/image_pattern.h"
#include "core/components_ng/pattern/menu/menu_view.h"
#include "core/components_ng/pattern/menu/wrapper/menu_wrapper_pattern.h"
#include "core/components_ng/pattern/navigation/bar_item_event_hub.h"
#include "core/components_ng/pattern/navigation/bar_item_pattern.h"
#include "core/components_ng/pattern/navigation/navigation_title_util.h"
#include "core/components_ng/pattern/navigation/nav_bar_pattern.h"
#include "core/components_ng/pattern/navigation/navdestination_pattern_base.h"
#include "core/components_ng/pattern/navigation/title_bar_node.h"
#include "core/components_ng/pattern/navigation/title_bar_pattern.h"
#include "core/components_ng/pattern/navigation/tool_bar_node.h"
#include "core/components_ng/pattern/navigation/tool_bar_pattern.h"
#include "core/components_ng/pattern/text/text_pattern.h"

namespace OHOS::Ace::NG {

namespace {
void AddSafeIntervalBetweenToolbarItem(
    MarginProperty& margin, uint32_t count, size_t toolbarItemSize, bool needMoreButton)
{
    auto theme = NavigationGetTheme();
    CHECK_NULL_VOID(theme);
    if (count == ONE_TOOLBAR_ITEM && toolbarItemSize != ONE_TOOLBAR_ITEM) {
        margin.right = CalcLength(theme->GetToolbarItemMargin());
    } else if (!needMoreButton && (count == toolbarItemSize) && (toolbarItemSize != ONE_TOOLBAR_ITEM)) {
        margin.left = CalcLength(theme->GetToolbarItemMargin());
    } else if (toolbarItemSize == ONE_TOOLBAR_ITEM) {
        margin.left = CalcLength(theme->GetToolbarItemSpecialMargin());
        margin.right = CalcLength(theme->GetToolbarItemSpecialMargin());
    } else {
        margin.left = CalcLength(theme->GetToolbarItemMargin());
        margin.right = CalcLength(theme->GetToolbarItemMargin());
    }
}

RefPtr<FrameNode> CreateToolbarItemTextNode(const std::string& text)
{
    int32_t nodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto textNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, nodeId, AceType::MakeRefPtr<TextPattern>());
    auto textLayoutProperty = textNode->GetLayoutProperty<TextLayoutProperty>();
    CHECK_NULL_RETURN(textLayoutProperty, nullptr);
    auto theme = NavigationGetTheme();
    CHECK_NULL_RETURN(theme, nullptr);
    textLayoutProperty->UpdateContent(text);
    textLayoutProperty->UpdateFontSize(theme->GetToolBarItemFontSize());
    textLayoutProperty->UpdateTextColor(theme->GetToolBarItemFontColor());
    textLayoutProperty->UpdateTextAlign(TextAlign::CENTER);
    textLayoutProperty->UpdateFontWeight(FontWeight::MEDIUM);
    textLayoutProperty->UpdateAdaptMinFontSize(theme->GetToolBarItemMinFontSize());
    textLayoutProperty->UpdateAdaptMaxFontSize(theme->GetToolBarItemFontSize());
    textLayoutProperty->UpdateMaxLines(theme->GetToolbarItemTextMaxLines());
    textLayoutProperty->UpdateTextOverflow(TextOverflow::ELLIPSIS);
    textLayoutProperty->UpdateHeightAdaptivePolicy(TextHeightAdaptivePolicy::MIN_FONT_SIZE_FIRST);

    textLayoutProperty->UpdateUserDefinedIdealSize(CalcSize(CalcLength(1.0, DimensionUnit::PERCENT), std::nullopt));
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

RefPtr<FrameNode> CreateToolbarItemIconNode(const BarItem& barItem)
{
    auto theme = NavigationGetTheme();
    CHECK_NULL_RETURN(theme, nullptr);
    if (barItem.iconSymbol.has_value() && barItem.iconSymbol.value() != nullptr) {
        auto iconNode = FrameNode::GetOrCreateFrameNode(V2::SYMBOL_ETS_TAG,
            ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TextPattern>(); });
        CHECK_NULL_RETURN(iconNode, nullptr);
        auto symbolProperty = iconNode->GetLayoutProperty<TextLayoutProperty>();
        CHECK_NULL_RETURN(symbolProperty, nullptr);
        symbolProperty->UpdateSymbolColorList({ theme->GetToolbarIconColor() });
        barItem.iconSymbol.value()(AccessibilityManager::WeakClaim(AccessibilityManager::RawPtr(iconNode)));
        symbolProperty->UpdateFontSize(theme->GetToolbarIconSize());
        UpdateSymbolEffect(symbolProperty, false);
        iconNode->MarkModifyDone();
        return iconNode;
    }
    int32_t nodeId = ElementRegister::GetInstance()->MakeUniqueId();
    ImageSourceInfo info(barItem.icon.value());
    auto iconNode = FrameNode::CreateFrameNode(V2::IMAGE_ETS_TAG, nodeId, AceType::MakeRefPtr<ImagePattern>());
    auto imageLayoutProperty = iconNode->GetLayoutProperty<ImageLayoutProperty>();
    CHECK_NULL_RETURN(imageLayoutProperty, nullptr);

    info.SetFillColor(theme->GetToolbarIconColor());
    imageLayoutProperty->UpdateImageSourceInfo(info);

    auto iconSize = theme->GetToolbarIconSize();
    imageLayoutProperty->UpdateUserDefinedIdealSize(CalcSize(CalcLength(iconSize), CalcLength(iconSize)));

    iconNode->MarkModifyDone();
    return iconNode;
}

void RegisterToolbarHotZoneEvent(const RefPtr<FrameNode>& buttonNode, const RefPtr<BarItemNode>& barItemNode)
{
    auto gestureEventHub = buttonNode->GetOrCreateGestureEventHub();
    CHECK_NULL_VOID(gestureEventHub);
    auto clickCallback = [weakNode = WeakPtr<BarItemNode>(barItemNode)](GestureEvent& info) {
        if (info.GetSourceDevice() == SourceType::KEYBOARD) {
            return;
        }
        auto barItemNode = weakNode.Upgrade();
        auto eventHub = barItemNode->GetEventHub<BarItemEventHub>();
        CHECK_NULL_VOID(eventHub);
        auto pattern = barItemNode->GetPattern<BarItemPattern>();
        CHECK_NULL_VOID(pattern);
        eventHub->FireItemAction();
        pattern->UpdateBarItemActiveStatusResource();
    };
    gestureEventHub->AddClickEvent(AceType::MakeRefPtr<ClickEvent>(clickCallback));
}

void UpdateBarItemPattern(const RefPtr<BarItemNode>& barItemNode, const BarItem& barItem)
{
    auto theme = NavigationGetTheme();
    CHECK_NULL_VOID(theme);
    auto barItemPattern = barItemNode->GetPattern<BarItemPattern>();
    CHECK_NULL_VOID(barItemPattern);
    if (barItem.status == NG::NavToolbarItemStatus::ACTIVE &&
        ((barItem.activeIcon.has_value() && !barItem.activeIcon.value().empty()) ||
            (barItem.activeIconSymbol.has_value() && barItem.activeIconSymbol.value() != nullptr)) &&
        ((barItem.icon.has_value() && !barItem.icon.value().empty()) ||
            (barItem.iconSymbol.has_value() && barItem.iconSymbol.value() != nullptr))) {
        if (barItem.iconSymbol.has_value() && barItem.iconSymbol.value() != nullptr) {
            barItemPattern->SetInitialIconSymbol(barItem.iconSymbol.value());
        } else if (barItem.icon.has_value()) {
            ImageSourceInfo initialIconInfo(barItem.icon.value());
            initialIconInfo.SetFillColor(theme->GetToolbarIconColor());
            barItemPattern->SetInitialIconImageSourceInfo(initialIconInfo);
        }

        if (barItem.activeIconSymbol.has_value() && barItem.activeIconSymbol.value() != nullptr) {
            barItemPattern->SetActiveIconSymbol(barItem.activeIconSymbol.value());
        } else if (barItem.activeIcon.has_value()) {
            ImageSourceInfo activeIconInfo(barItem.activeIcon.value());
            activeIconInfo.SetFillColor(theme->GetToolbarActiveIconColor());
            barItemPattern->SetActiveIconImageSourceInfo(activeIconInfo);
        }
        barItemPattern->SetToolbarItemStatus(barItem.status);
        barItemPattern->SetCurrentIconStatus(NG::ToolbarIconStatus::INITIAL);
        barItemPattern->UpdateBarItemActiveStatusResource();
    }
}

void UpdateToolbarItemNodeWithConfiguration(
    const RefPtr<BarItemNode>& barItemNode, const BarItem& barItem,
    const RefPtr<FrameNode>& buttonNode, bool enableStatus)
{
    barItemNode->SetBarItemUsedInToolbarConfiguration(true);
    if (barItem.text.has_value() && !barItem.text.value().empty()) {
        auto textNode = CreateToolbarItemTextNode(barItem.text.value());
        barItemNode->SetTextNode(textNode);
        barItemNode->AddChild(textNode);
    }
    if ((barItem.icon.has_value() && !barItem.icon.value().empty())
        || (barItem.iconSymbol.has_value() && barItem.iconSymbol.value() != nullptr)) {
        auto iconNode = CreateToolbarItemIconNode(barItem);
        barItemNode->SetIconNode(iconNode);
        barItemNode->AddChild(iconNode);
    }
    if (barItem.action) {
        auto eventHub = barItemNode->GetEventHub<BarItemEventHub>();
        CHECK_NULL_VOID(eventHub);
        eventHub->SetItemAction(barItem.action);
        RegisterToolbarHotZoneEvent(buttonNode, barItemNode);
    }

    auto theme = NavigationGetTheme();
    CHECK_NULL_VOID(theme);
    if (barItem.status == NG::NavToolbarItemStatus::DISABLED || !enableStatus) {
        auto renderContext = barItemNode->GetRenderContext();
        CHECK_NULL_VOID(renderContext);
        renderContext->UpdateOpacity(theme->GetToolbarItemDisabledAlpha());

        auto itemEventHub = barItemNode->GetEventHub<BarItemEventHub>();
        CHECK_NULL_VOID(itemEventHub);
        itemEventHub->SetEnabled(false);
        auto itemFocusHub = barItemNode->GetFocusHub();
        CHECK_NULL_VOID(itemFocusHub);
        itemFocusHub->SetEnabled(false);

        auto buttonEventHub = buttonNode->GetEventHub<ButtonEventHub>();
        CHECK_NULL_VOID(buttonEventHub);
        buttonEventHub->SetEnabled(false);
        auto buttonFocusHub = buttonNode->GetFocusHub();
        CHECK_NULL_VOID(buttonFocusHub);
        buttonFocusHub->SetEnabled(false);
    }

    UpdateBarItemPattern(barItemNode, barItem);
    barItemNode->MarkModifyDone();
}

void BuildSymbolToolbarMoreItemNode(const RefPtr<BarItemNode>& barItemNode, bool enabled)
{
    auto theme = NavigationGetTheme();
    CHECK_NULL_VOID(theme);
    auto renderContext = barItemNode->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    if (!enabled) {
        renderContext->UpdateOpacity(theme->GetToolbarItemDisabledAlpha());
    }

    auto symbolNode = FrameNode::GetOrCreateFrameNode(V2::SYMBOL_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TextPattern>(); });
    CHECK_NULL_VOID(symbolNode);
    auto symbolProperty = symbolNode->GetLayoutProperty<TextLayoutProperty>();
    CHECK_NULL_VOID(symbolProperty);
    symbolProperty->UpdateSymbolSourceInfo(SymbolSourceInfo(theme->GetMoreSymbolId()));
    symbolProperty->UpdateFontSize(theme->GetToolbarIconSize());
    symbolProperty->UpdateSymbolColorList({ theme->GetToolbarIconColor() });
    symbolNode->MarkModifyDone();
    barItemNode->SetIconNode(symbolNode);
    barItemNode->SetIsMoreItemNode(true);
    barItemNode->AddChild(symbolNode);
}

void BuildImageToolbarMoreItemNode(const RefPtr<BarItemNode>& barItemNode, bool enabled)
{
    auto theme = NavigationGetTheme();
    CHECK_NULL_VOID(theme);

    int32_t imageNodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto imageNode = FrameNode::CreateFrameNode(V2::IMAGE_ETS_TAG, imageNodeId, AceType::MakeRefPtr<ImagePattern>());
    auto imageLayoutProperty = imageNode->GetLayoutProperty<ImageLayoutProperty>();
    CHECK_NULL_VOID(imageLayoutProperty);
    auto info = ImageSourceInfo("");
    info.SetResourceId(theme->GetMoreResourceId());
    if (!enabled) {
        auto renderContext = barItemNode->GetRenderContext();
        CHECK_NULL_VOID(renderContext);
        renderContext->UpdateOpacity(theme->GetToolbarItemDisabledAlpha());
    } else {
        info.SetFillColor(theme->GetToolbarIconColor());
    }
    imageLayoutProperty->UpdateImageSourceInfo(info);
    auto iconSize = theme->GetToolbarIconSize();
    imageLayoutProperty->UpdateUserDefinedIdealSize(CalcSize(CalcLength(iconSize), CalcLength(iconSize)));
    imageNode->MarkModifyDone();
    barItemNode->SetIconNode(imageNode);
    barItemNode->AddChild(imageNode);
}

RefPtr<FrameNode> CreateToolbarItemsContainerNode(const RefPtr<FrameNode>& toolBarNode)
{
    int32_t containerNodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto containerNode = FrameNode::GetOrCreateFrameNode(
        V2::TOOL_BAR_ETS_TAG, containerNodeId, []() { return AceType::MakeRefPtr<LinearLayoutPattern>(false); });
    CHECK_NULL_RETURN(containerNode, nullptr);
    auto containerRowProperty = containerNode->GetLayoutProperty<LinearLayoutProperty>();
    CHECK_NULL_RETURN(containerRowProperty, nullptr);
    containerRowProperty->UpdateMainAxisAlign(FlexAlign::SPACE_EVENLY);
    toolBarNode->AddChild(containerNode);
    return containerNode;
}

RefPtr<FrameNode> CreateToolbarItemInContainer(
    const BarItem& toolBarItem, size_t toolbarItemSize, uint32_t count, bool needMoreButton, bool enableStatus)
{
    auto theme = NavigationGetTheme();
    CHECK_NULL_RETURN(theme, nullptr);
    auto buttonPattern = AceType::MakeRefPtr<ButtonPattern>();
    CHECK_NULL_RETURN(buttonPattern, nullptr);
    buttonPattern->setComponentButtonType(ComponentButtonType::NAVIGATION);
    buttonPattern->SetFocusBorderColor(theme->GetToolBarItemFocusColor());
    buttonPattern->SetFocusBorderWidth(theme->GetToolBarItemFocusBorderWidth());
    auto toolBarItemNode = FrameNode::CreateFrameNode(
        V2::MENU_ITEM_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), buttonPattern);
    CHECK_NULL_RETURN(toolBarItemNode, nullptr);
    auto toolBarItemLayoutProperty = toolBarItemNode->GetLayoutProperty<ButtonLayoutProperty>();
    CHECK_NULL_RETURN(toolBarItemLayoutProperty, nullptr);
    toolBarItemLayoutProperty->UpdateUserDefinedIdealSize(
        CalcSize(std::nullopt, CalcLength(theme->GetToolbarItemHeigth())));
    toolBarItemLayoutProperty->UpdateType(ButtonType::NORMAL);
    toolBarItemLayoutProperty->UpdateBorderRadius(theme->GetToolBarItemBorderRadius());
    auto renderContext = toolBarItemNode->GetRenderContext();
    CHECK_NULL_RETURN(renderContext, nullptr);
    renderContext->UpdateBackgroundColor(Color::TRANSPARENT);
    MarginProperty margin;
    AddSafeIntervalBetweenToolbarItem(margin, count, toolbarItemSize, needMoreButton);
    toolBarItemLayoutProperty->UpdateMargin(margin);

    PaddingProperty padding;
    padding.left = CalcLength(theme->GetToolbarItemLeftOrRightPadding());
    padding.right = CalcLength(theme->GetToolbarItemLeftOrRightPadding());
    padding.top = CalcLength(theme->GetToolbarItemTopPadding());
    padding.bottom = CalcLength(theme->GetToolbarItemBottomPadding());
    toolBarItemLayoutProperty->UpdatePadding(padding);

    int32_t barItemNodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto barItemNode = BarItemNode::GetOrCreateBarItemNode(
        V2::BAR_ITEM_ETS_TAG, barItemNodeId, []() { return AceType::MakeRefPtr<BarItemPattern>(); });
    UpdateToolbarItemNodeWithConfiguration(barItemNode, toolBarItem, toolBarItemNode, enableStatus);
    auto barItemLayoutProperty = barItemNode->GetLayoutProperty();
    CHECK_NULL_RETURN(barItemLayoutProperty, nullptr);
    barItemLayoutProperty->UpdateMeasureType(MeasureType::MATCH_PARENT);

    barItemNode->MountToParent(toolBarItemNode);
    toolBarItemNode->MarkModifyDone();
    return toolBarItemNode;
}

void BuildToolbarMoreItemNode(const RefPtr<BarItemNode>& barItemNode, bool enabled)
{
    if (AceApplicationInfo::GetInstance().GreatOrEqualTargetAPIVersion(PlatformVersion::VERSION_TWELVE)) {
        BuildSymbolToolbarMoreItemNode(barItemNode, enabled);
    } else {
        BuildImageToolbarMoreItemNode(barItemNode, enabled);
    }
    auto textNode = CreateToolbarItemTextNode(Localization::GetInstance()->GetEntryLetters("common.more"));
    CHECK_NULL_VOID(textNode);
    barItemNode->SetTextNode(textNode);
    barItemNode->SetBarItemUsedInToolbarConfiguration(true);
    barItemNode->AddChild(textNode);
    barItemNode->MarkModifyDone();
}

RefPtr<FrameNode> CreateToolbarMoreMenuNode(const RefPtr<BarItemNode>& barItemNode)
{
    auto theme = NavigationGetTheme();
    CHECK_NULL_RETURN(theme, nullptr);
    auto buttonPattern = AceType::MakeRefPtr<ButtonPattern>();
    CHECK_NULL_RETURN(buttonPattern, nullptr);
    buttonPattern->setComponentButtonType(ComponentButtonType::NAVIGATION);
    buttonPattern->SetFocusBorderColor(theme->GetToolBarItemFocusColor());
    buttonPattern->SetFocusBorderWidth(theme->GetToolBarItemFocusBorderWidth());
    auto toolBarItemNode = FrameNode::CreateFrameNode(
        V2::MENU_ITEM_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), buttonPattern);
    CHECK_NULL_RETURN(toolBarItemNode, nullptr);
    auto menuItemLayoutProperty = toolBarItemNode->GetLayoutProperty<ButtonLayoutProperty>();
    CHECK_NULL_RETURN(menuItemLayoutProperty, nullptr);
    menuItemLayoutProperty->UpdateUserDefinedIdealSize(
        CalcSize(std::nullopt, CalcLength(theme->GetToolbarItemHeigth())));
    menuItemLayoutProperty->UpdateType(ButtonType::NORMAL);
    menuItemLayoutProperty->UpdateBorderRadius(theme->GetToolBarItemBorderRadius());

    auto renderContext = toolBarItemNode->GetRenderContext();
    CHECK_NULL_RETURN(renderContext, nullptr);
    renderContext->UpdateBackgroundColor(Color::TRANSPARENT);

    MarginProperty menuButtonMargin;
    menuButtonMargin.left = CalcLength(theme->GetToolbarItemMargin());
    menuItemLayoutProperty->UpdateMargin(menuButtonMargin);

    PaddingProperty padding;
    padding.left = CalcLength(theme->GetToolbarItemLeftOrRightPadding());
    padding.right = CalcLength(theme->GetToolbarItemLeftOrRightPadding());
    padding.top = CalcLength(theme->GetToolbarItemTopPadding());
    padding.bottom = CalcLength(theme->GetToolbarItemBottomPadding());
    menuItemLayoutProperty->UpdatePadding(padding);

    barItemNode->MountToParent(toolBarItemNode);
    barItemNode->MarkModifyDone();
    toolBarItemNode->MarkModifyDone();
    return toolBarItemNode;
}

void BuildToolbarMoreMenuNodeAction(
    const RefPtr<BarItemNode>& barItemNode, const RefPtr<FrameNode>& barMenuNode, const RefPtr<FrameNode>& buttonNode)
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
        menuPattern->SetIsSelectMenu(true);

        bool isRightToLeft = AceApplicationInfo::GetInstance().IsRightToLeft();
        if (isRightToLeft) {
            imgOffset.SetX(imgOffset.GetX() + imageSize.Width());
        } else {
            imgOffset.SetX(imgOffset.GetX());
        }
        imgOffset.SetY(imgOffset.GetY() - imageSize.Height());
        overlayManager->ShowMenu(id, imgOffset, menu);
    };
    eventHub->SetItemAction(clickCallback);
    RegisterToolbarHotZoneEvent(buttonNode, barItemNode);
}

bool CreateToolbarItemNodeAndMenuNode(bool enabled, std::vector<OptionParam>&& params,
    const FieldProperty& fieldProperty, RefPtr<FrameNode>& barMenuNodeOut, const RefPtr<FrameNode>& containerNode)
{
    int32_t barItemNodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto barItemNode = BarItemNode::GetOrCreateBarItemNode(
        V2::BAR_ITEM_ETS_TAG, barItemNodeId, []() { return AceType::MakeRefPtr<BarItemPattern>(); });
    auto barItemLayoutProperty = barItemNode->GetLayoutProperty();
    CHECK_NULL_RETURN(barItemLayoutProperty, false);
    barItemLayoutProperty->UpdateMeasureType(MeasureType::MATCH_PARENT);
    BuildToolbarMoreItemNode(barItemNode, enabled);
    MenuParam menuParam;
    menuParam.isShowInSubWindow = false;
    auto barMenuNode = MenuView::Create(
        std::move(params), barItemNodeId, V2::BAR_ITEM_ETS_TAG, MenuType::NAVIGATION_MENU, menuParam);
    auto toolBarItemNode = CreateToolbarMoreMenuNode(barItemNode);
    CHECK_NULL_RETURN(toolBarItemNode, false);
    BuildToolbarMoreMenuNodeAction(barItemNode, barMenuNode, toolBarItemNode);

    // set Navigation/NavDestination toolBar "more" button InspectorId
    NavigationTitleUtil::SetInnerChildId(toolBarItemNode, fieldProperty.field,
        containerNode->GetTag(), "More", fieldProperty.parentId);
    containerNode->AddChild(toolBarItemNode);
    barMenuNodeOut = barMenuNode;
    return true;
}

bool BuildToolBarItems(const RefPtr<NavToolbarNode>& toolBarNode, const std::vector<NG::BarItem>& toolBarItems,
    const FieldProperty& fieldProperty, bool enabled, RefPtr<FrameNode>& barMenuNodeOut)
{
    CHECK_NULL_RETURN(toolBarNode, false);
    auto rowProperty = toolBarNode->GetLayoutProperty();
    CHECK_NULL_RETURN(rowProperty, false);
    auto containerNode = CreateToolbarItemsContainerNode(toolBarNode);
    CHECK_NULL_RETURN(containerNode, false);
    toolBarNode->SetToolbarContainerNode(containerNode);
    bool needMoreButton = toolBarItems.size() > MAXIMUM_TOOLBAR_ITEMS_IN_BAR;
    uint32_t count = 0;
    std::vector<OptionParam> params;
    auto theme = NavigationGetTheme();
    CHECK_NULL_RETURN(theme, false);
    OptionParam param;
    for (const auto& toolBarItem : toolBarItems) {
        ++count;
        if (needMoreButton && (count > MAXIMUM_TOOLBAR_ITEMS_IN_BAR - 1)) {
            param = { toolBarItem.text.value_or(""), toolBarItem.icon.value_or(""), toolBarItem.action,
                toolBarItem.iconSymbol.value_or(nullptr) };
            param.SetSymbolUserDefinedIdealFontSize(theme->GetToolbarIconSize());
            params.push_back(param);
        } else {
            auto toolBarItemNode = CreateToolbarItemInContainer(
                toolBarItem, toolBarItems.size(), count, needMoreButton, enabled);
            CHECK_NULL_RETURN(toolBarItemNode, false);

            // set Navigation/NavDestination toolBar menuItem InspectorId
            std::string toolBarItemId = toolBarItemNode->GetTag() + std::to_string(count);
            NavigationTitleUtil::SetInnerChildId(toolBarItemNode, fieldProperty.field,
                containerNode->GetTag(), toolBarItemId, fieldProperty.parentId);

            containerNode->AddChild(toolBarItemNode);
        }
    }
    bool hasValidContent = !containerNode->GetChildren().empty();
    toolBarNode->SetHasValidContent(hasValidContent);
    rowProperty->UpdateVisibility(hasValidContent ? VisibleType::VISIBLE : VisibleType::GONE);
    if (!needMoreButton) {
        return true;
    }
    return CreateToolbarItemNodeAndMenuNode(enabled, std::move(params), fieldProperty,
        barMenuNodeOut, containerNode);;
}
} //namespace

void NavigationToolbarUtil::CreateToolBarDividerNode(const RefPtr<NavDestinationNodeBase>& nodeBase)
{
    int32_t dividerNodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto dividerNode = FrameNode::GetOrCreateFrameNode(
        V2::DIVIDER_ETS_TAG, dividerNodeId, []() { return AceType::MakeRefPtr<DividerPattern>(); });
    nodeBase->AddChild(dividerNode);
    auto dividerLayoutProperty = dividerNode->GetLayoutProperty<DividerLayoutProperty>();
    CHECK_NULL_VOID(dividerLayoutProperty);
    auto theme = NavigationGetTheme();
    CHECK_NULL_VOID(theme);
    dividerLayoutProperty->UpdateStrokeWidth(theme->GetToolBarDividerWidth());
    dividerLayoutProperty->UpdateVertical(false);
    auto dividerRenderProperty = dividerNode->GetPaintProperty<DividerRenderProperty>();
    CHECK_NULL_VOID(dividerRenderProperty);
    dividerRenderProperty->UpdateDividerColor(theme->GetToolBarDividerColor());
    nodeBase->SetToolBarDividerNode(dividerNode);
}

void NavigationToolbarUtil::SetToolbarConfiguration(const RefPtr<NavDestinationNodeBase>& nodeBase,
    std::vector<NG::BarItem>&& toolBarItems, bool enabled, const FieldProperty& fieldProperty)
{
    CHECK_NULL_VOID(nodeBase);
    if (nodeBase->GetPrevToolBarIsCustom().value_or(false)) {
        nodeBase->UpdateToolBarNodeOperation(ChildNodeOperation::REPLACE);
    } else {
        auto toolbarNode = AceType::DynamicCast<NavToolbarNode>(nodeBase->GetPreToolBarNode());
        auto containerNode = toolbarNode->GetToolbarContainerNode();
        if (toolbarNode && containerNode) {
            nodeBase->UpdateToolBarNodeOperation(ChildNodeOperation::REPLACE);
            auto preToolbarNode = nodeBase->GetPreToolBarNode();
            preToolbarNode->RemoveChild(containerNode);
            nodeBase->RemoveChild(nodeBase->GetToolBarDividerNode());
        } else {
            nodeBase->UpdateToolBarNodeOperation(ChildNodeOperation::ADD);
        }
    }
    auto toolBarNode = AceType::DynamicCast<NavToolbarNode>(nodeBase->GetPreToolBarNode());
    CHECK_NULL_VOID(toolBarNode);
    toolBarNode->SetIsUseNewToolbar(true);
    auto rowProperty = toolBarNode->GetLayoutProperty<LinearLayoutProperty>();
    CHECK_NULL_VOID(rowProperty);
    rowProperty->UpdateMainAxisAlign(FlexAlign::CENTER);
    if ((Container::LessThanAPIVersion(PlatformVersion::VERSION_ELEVEN) ||
        !SystemProperties::GetNavigationBlurEnabled()) && !nodeBase->GetToolBarDividerNode()) {
        NavigationToolbarUtil::CreateToolBarDividerNode(nodeBase);
    }
    bool needMoreButton = toolBarItems.size() > MAXIMUM_TOOLBAR_ITEMS_IN_BAR;
    RefPtr<FrameNode> barMenuNode = nullptr;
    if (!BuildToolBarItems(toolBarNode, toolBarItems, fieldProperty, enabled, barMenuNode)) {
        return;
    }
    if (needMoreButton) {
        nodeBase->SetToolbarMenuNode(barMenuNode);
    }
    nodeBase->SetToolBarNode(toolBarNode);
    nodeBase->SetPreToolBarNode(toolBarNode);
    nodeBase->UpdatePrevToolBarIsCustom(false);
    nodeBase->SetIsUseToolbarConfiguration(true);
    auto navDestinationPatternBase = nodeBase->GetPattern<NavDestinationPatternBase>();
    CHECK_NULL_VOID(navDestinationPatternBase);
    navDestinationPatternBase->SetToolBarMenuItems(toolBarItems);
}

void NavigationToolbarUtil::SetCustomToolBar(
    const RefPtr<NavDestinationNodeBase>& nodeBase, const RefPtr<AceType>& customNode)
{
    CHECK_NULL_VOID(nodeBase);
    auto customToolBar = AceType::DynamicCast<NG::UINode>(customNode);
    CHECK_NULL_VOID(customToolBar);
    if (nodeBase->GetPrevToolBarIsCustom().value_or(false)) {
        if (customToolBar->GetId() == nodeBase->GetToolBarNode()->GetId()) {
            nodeBase->UpdateToolBarNodeOperation(ChildNodeOperation::NONE);
            nodeBase->UpdatePrevToolBarIsCustom(true);
            return;
        }
    }
    nodeBase->UpdateToolBarNodeOperation(ChildNodeOperation::REPLACE);
    auto toolBarNode = AceType::DynamicCast<NavToolbarNode>(nodeBase->GetToolBarNode());
    CHECK_NULL_VOID(toolBarNode);
    toolBarNode->Clean();
    customToolBar->MountToParent(toolBarNode);
    nodeBase->UpdatePrevToolBarIsCustom(true);
    toolBarNode->SetHasValidContent(true);
    auto property = toolBarNode->GetLayoutProperty();
    CHECK_NULL_VOID(property);
    property->UpdateVisibility(VisibleType::VISIBLE);
}

void NavigationToolbarUtil::SetToolbarOptions(
    const RefPtr<NavDestinationNodeBase>& nodeBase, NavigationToolbarOptions&& opt)
{
    CHECK_NULL_VOID(nodeBase);
    auto navDestinationPatternBase = nodeBase->GetPattern<NavDestinationPatternBase>();
    CHECK_NULL_VOID(navDestinationPatternBase);
    navDestinationPatternBase->SetToolBarStyle(opt.brOptions.barStyle);
    auto toolBarNode = AceType::DynamicCast<NavToolbarNode>(nodeBase->GetToolBarNode());
    CHECK_NULL_VOID(toolBarNode);
    auto toolBarPattern = toolBarNode->GetPattern<NavToolbarPattern>();
    CHECK_NULL_VOID(toolBarPattern);
    toolBarPattern->SetToolbarOptions(std::move(opt));
}

void NavigationToolbarUtil::MountToolBar(
    const RefPtr<NavDestinationNodeBase>& nodeBase, bool& needRunToolBarAnimation)
{
    needRunToolBarAnimation = false;
    CHECK_NULL_VOID(nodeBase);
    auto toolbarNode = nodeBase->GetToolBarNode();
    CHECK_NULL_VOID(toolbarNode);
    auto navDestinationPatternBase = nodeBase->GetPattern<NavDestinationPatternBase>();
    CHECK_NULL_VOID(navDestinationPatternBase);
    auto propertyBase = nodeBase->GetLayoutProperty<NavDestinationLayoutPropertyBase>();
    CHECK_NULL_VOID(propertyBase);
    auto toolBarNode = AceType::DynamicCast<NavToolbarNode>(toolbarNode);
    CHECK_NULL_VOID(toolBarNode);
    auto toolBarLayoutProperty = toolBarNode->GetLayoutProperty<LayoutProperty>();
    CHECK_NULL_VOID(toolBarLayoutProperty);
    auto divider = AceType::DynamicCast<FrameNode>(nodeBase->GetToolBarDividerNode());

    if (nodeBase->GetToolBarNodeOperationValue(ChildNodeOperation::NONE) == ChildNodeOperation::REPLACE) {
        nodeBase->RemoveChild(nodeBase->GetPreToolBarNode());
        nodeBase->AddChild(toolbarNode);
    }

    bool hideToolBar = propertyBase->GetHideToolBarValue(false);
    auto currhideToolBar = navDestinationPatternBase->GetCurrHideToolBar();
    /**
     * if toolbar is the first time to hide/display, doesn't require animation or isn't currently being animated and the
     * hidden/display status hasn't changed.
     */
    if (!currhideToolBar.has_value() || !propertyBase->GetIsAnimatedToolBarValue(false) ||
        (navDestinationPatternBase->GetToolBarAnimationCount() <= 0 && currhideToolBar.value() == hideToolBar)) {
        navDestinationPatternBase->SetCurrHideToolBar(hideToolBar);
        navDestinationPatternBase->HideOrShowToolBarImmediately(nodeBase, hideToolBar);
        return;
    }
    toolBarNode->MarkModifyDone();
    toolBarNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF_AND_CHILD);

    navDestinationPatternBase->SetCurrHideToolBar(hideToolBar);
    needRunToolBarAnimation = true;
}
} // namespace OHOS::Ace::NG