/*
 * Copyright (c) 2022-2023 Huawei Device Co., Ltd.
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

#include "core/components_ng/pattern/menu/menu_pattern.h"

#include <stack>

#include "base/log/dump_log.h"
#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"
#include "base/utils/utils.h"
#include "core/components/common/properties/shadow_config.h"
#include "core/components/select/select_theme.h"
#include "core/components_ng/base/ui_node.h"
#include "core/components_ng/pattern/menu/menu_item/menu_item_layout_property.h"
#include "core/components_ng/pattern/menu/menu_item/menu_item_pattern.h"
#include "core/components_ng/pattern/menu/multi_menu_layout_algorithm.h"
#include "core/components_ng/pattern/menu/sub_menu_layout_algorithm.h"
#include "core/components_ng/pattern/menu/wrapper/menu_wrapper_pattern.h"
#include "core/components_ng/pattern/option/option_pattern.h"
#include "core/components_ng/pattern/option/option_view.h"
#include "core/components_ng/pattern/scroll/scroll_pattern.h"
#include "core/components_ng/pattern/text/text_layout_property.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "core/event/touch_event.h"
#include "core/pipeline/pipeline_base.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {
namespace {
void UpdateFontStyle(RefPtr<MenuLayoutProperty>& menuProperty, RefPtr<MenuItemLayoutProperty>& itemProperty,
    RefPtr<MenuItemPattern>& itemPattern, bool& contentChanged, bool& labelChanged)
{
    auto contentNode = itemPattern->GetContentNode();
    CHECK_NULL_VOID(contentNode);
    auto textLayoutProperty = contentNode->GetLayoutProperty<TextLayoutProperty>();
    CHECK_NULL_VOID(textLayoutProperty);
    auto label = itemPattern->GetLabelNode();
    RefPtr<TextLayoutProperty> labelProperty = label ? label->GetLayoutProperty<TextLayoutProperty>() : nullptr;
    if (menuProperty->GetItalicFontStyle().has_value()) {
        if (!itemProperty->GetItalicFontStyle().has_value()) {
            textLayoutProperty->UpdateItalicFontStyle(menuProperty->GetItalicFontStyle().value());
            contentChanged = true;
        }
        if (labelProperty && !itemProperty->GetLabelItalicFontStyle().has_value()) {
            labelProperty->UpdateItalicFontStyle(menuProperty->GetItalicFontStyle().value());
            labelChanged = true;
        }
    }
    if (menuProperty->GetFontFamily().has_value()) {
        if (!itemProperty->GetFontFamily().has_value()) {
            textLayoutProperty->UpdateFontFamily(menuProperty->GetFontFamily().value());
            contentChanged = true;
        }
        if (labelProperty && !itemProperty->GetLabelFontFamily().has_value()) {
            labelProperty->UpdateFontFamily(menuProperty->GetFontFamily().value());
            labelChanged = true;
        }
    }
}

void UpdateMenuItemTextNode(RefPtr<MenuLayoutProperty>& menuProperty, RefPtr<MenuItemLayoutProperty>& itemProperty,
    RefPtr<MenuItemPattern>& itemPattern)
{
    auto contentNode = itemPattern->GetContentNode();
    CHECK_NULL_VOID(contentNode);
    auto textLayoutProperty = contentNode->GetLayoutProperty<TextLayoutProperty>();
    CHECK_NULL_VOID(textLayoutProperty);
    auto label = itemPattern->GetLabelNode();
    RefPtr<TextLayoutProperty> labelProperty = label ? label->GetLayoutProperty<TextLayoutProperty>() : nullptr;
    bool contentChanged = false;
    bool labelChanged = false;
    if (menuProperty->GetFontSize().has_value()) {
        if (!itemProperty->GetFontSize().has_value()) {
            textLayoutProperty->UpdateFontSize(menuProperty->GetFontSize().value());
            contentChanged = true;
        }
        if (labelProperty && !itemProperty->GetLabelFontSize().has_value()) {
            labelProperty->UpdateFontSize(menuProperty->GetFontSize().value());
            labelChanged = true;
        }
    }
    if (menuProperty->GetFontWeight().has_value()) {
        if (!itemProperty->GetFontWeight().has_value()) {
            textLayoutProperty->UpdateFontWeight(menuProperty->GetFontWeight().value());
            contentChanged = true;
        }
        if (labelProperty && !itemProperty->GetLabelFontWeight().has_value()) {
            labelProperty->UpdateFontWeight(menuProperty->GetFontWeight().value());
            labelChanged = true;
        }
    }
    if (menuProperty->GetFontColor().has_value()) {
        if (!itemProperty->GetFontColor().has_value()) {
            textLayoutProperty->UpdateTextColor(menuProperty->GetFontColor().value());
            contentChanged = true;
        }
        if (labelProperty && !itemProperty->GetLabelFontColor().has_value()) {
            labelProperty->UpdateTextColor(menuProperty->GetFontColor().value());
            labelChanged = true;
        }
    }
    UpdateFontStyle(menuProperty, itemProperty, itemPattern, contentChanged, labelChanged);
    if (contentChanged) {
        contentNode->MarkModifyDone();
        contentNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    }
    if (labelChanged) {
        label->MarkModifyDone();
        label->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    }
}
} // namespace

void MenuPattern::OnAttachToFrameNode()
{
    RegisterOnTouch();
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto focusHub = host->GetOrCreateFocusHub();
    CHECK_NULL_VOID(focusHub);
    RegisterOnKeyEvent(focusHub);
    DisableTabInMenu();
    InitTheme(host);
}

void MenuPattern::OnModifyDone()
{
    Pattern::OnModifyDone();
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    UpdateMenuItemChildren(host);

    auto innerMenuCount = GetInnerMenuCount();
    if (innerMenuCount == 1) {
        ResetTheme(host, false);
    } else if (innerMenuCount > 1) {
        // multiple inner menus, reset outer container's shadow for desktop UX
        ResetTheme(host, true);
    }
    auto menuFirstNode = GetFirstInnerMenu();
    if (menuFirstNode) {
        CopyMenuAttr(menuFirstNode);
    }
    SetAccessibilityAction();
}

void InnerMenuPattern::BeforeCreateLayoutWrapper()
{
    RecordItemsAndGroups();

    // determine menu type based on sibling menu count
    auto count = FindSiblingMenuCount();
    if (count > 0) {
        SetType(MenuType::DESKTOP_MENU);
        ApplyDesktopMenuTheme();
    } else {
        SetType(MenuType::MULTI_MENU);
        ApplyMultiMenuTheme();
    }
}

void InnerMenuPattern::OnModifyDone()
{
    Pattern::OnModifyDone();
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    UpdateMenuItemChildren(host);
    SetAccessibilityAction();
}

// close menu on touch up
void MenuPattern::RegisterOnTouch()
{
    CHECK_NULL_VOID_NOLOG(!onTouch_);
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto gesture = host->GetOrCreateGestureEventHub();
    CHECK_NULL_VOID(gesture);
    auto touchTask = [weak = WeakClaim(this)](const TouchEventInfo& info) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID_NOLOG(pattern);
        pattern->OnTouchEvent(info);
    };
    onTouch_ = MakeRefPtr<TouchEventImpl>(std::move(touchTask));
    gesture->AddTouchEvent(onTouch_);
}

void MenuPattern::OnTouchEvent(const TouchEventInfo& info)
{
    if (GetInnerMenuCount() > 0 || IsMultiMenu()) {
        // not click hide menu for multi menu
        return;
    }
    if (!options_.empty()) {
        // not click hide menu for select and bindMenu default option
        return;
    }
    auto touchType = info.GetTouches().front().GetTouchType();
    if (touchType == TouchType::DOWN) {
        lastTouchOffset_ = info.GetTouches().front().GetLocalLocation();
    } else if (touchType == TouchType::UP) {
        auto touchUpOffset = info.GetTouches().front().GetLocalLocation();
        if (lastTouchOffset_.has_value() &&
            (touchUpOffset - lastTouchOffset_.value()).GetDistance() <= DEFAULT_CLICK_DISTANCE) {
            HideMenu(true);
        }
        lastTouchOffset_.reset();
    }
}

void MenuPattern::RegisterOnKeyEvent(const RefPtr<FocusHub>& focusHub)
{
    auto onKeyEvent = [wp = WeakClaim(this)](const KeyEvent& event) -> bool {
        auto pattern = wp.Upgrade();
        CHECK_NULL_RETURN_NOLOG(pattern, false);
        return pattern->OnKeyEvent(event);
    };
    focusHub->SetOnKeyEventInternal(std::move(onKeyEvent));
}

bool MenuPattern::OnKeyEvent(const KeyEvent& event) const
{
    if (event.action != KeyAction::DOWN || IsMultiMenu()) {
        return false;
    }
    if ((event.code == KeyCode::KEY_DPAD_LEFT || event.code == KeyCode::KEY_ESCAPE) &&
        (IsSubMenu() || IsSelectOverlaySubMenu())) {
        auto menuWrapper = GetMenuWrapper();
        CHECK_NULL_RETURN(menuWrapper, true);
        auto wrapperPattern = menuWrapper->GetPattern<MenuWrapperPattern>();
        CHECK_NULL_RETURN(wrapperPattern, true);
        wrapperPattern->HideSubMenu();
        return true;
    }
    return false;
}

void MenuPattern::RemoveParentHoverStyle()
{
    if (!IsSubMenu()) {
        return;
    }
    auto menuItemParent = GetParentMenuItem();
    CHECK_NULL_VOID(menuItemParent);
    auto menuItemPattern = menuItemParent->GetPattern<MenuItemPattern>();
    CHECK_NULL_VOID(menuItemPattern);
    menuItemPattern->SetIsSubMenuShowed(false);

    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto theme = pipeline->GetTheme<SelectTheme>();
    CHECK_NULL_VOID(theme);
    menuItemPattern->SetBgBlendColor(Color::TRANSPARENT);
    menuItemPattern->PlayBgColorAnimation();
}

void MenuPattern::UpdateMenuItemChildren(RefPtr<FrameNode>& host)
{
    auto layoutProperty = GetLayoutProperty<MenuLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    const auto& children = host->GetChildren();
    for (auto child : children) {
        if (child->GetTag() == V2::MENU_ITEM_ETS_TAG) {
            auto itemNode = AceType::DynamicCast<FrameNode>(child);
            CHECK_NULL_VOID(itemNode);
            auto itemProperty = itemNode->GetLayoutProperty<MenuItemLayoutProperty>();
            CHECK_NULL_VOID(itemProperty);
            auto itemPattern = itemNode->GetPattern<MenuItemPattern>();
            CHECK_NULL_VOID(itemPattern);
            UpdateMenuItemTextNode(layoutProperty, itemProperty, itemPattern);
        } else if (child->GetTag() == V2::MENU_ITEM_GROUP_ETS_TAG) {
            auto itemGroupNode = AceType::DynamicCast<FrameNode>(child);
            CHECK_NULL_VOID(itemGroupNode);
            UpdateMenuItemChildren(itemGroupNode);
        } else {
            // do nothing
        }
    }
}

void MenuPattern::UpdateSelectParam(const std::vector<SelectParam>& params)
{
    if (!isSelectMenu_) {
        return;
    }
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    const auto& children = GetOptions();
    auto childCount = children.size();
    auto paramCount = params.size();
    size_t updateCount = std::min(paramCount, childCount);
    auto childIt = children.begin();
    for (size_t i = 0; i < updateCount; i++, childIt++) {
        const auto& childNode = AceType::DynamicCast<FrameNode>(*childIt);
        CHECK_NULL_VOID(childNode);
        if (i == 0) {
            auto props = childNode->GetPaintProperty<OptionPaintProperty>();
            CHECK_NULL_VOID(props);
            props->UpdateNeedDivider(false);
        }
        auto optionPattern = childNode->GetPattern<OptionPattern>();
        CHECK_NULL_VOID(optionPattern);
        optionPattern->UpdateText(params.at(i).first);
        optionPattern->UpdateIcon(params.at(i).second);
        childNode->MarkModifyDone();
        childNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    }
    for (size_t i = updateCount; i < paramCount; i++) {
        auto optionNode = OptionView::CreateSelectOption(params.at(i).first, params.at(i).second, i);
        if (i == 0) {
            auto props = optionNode->GetPaintProperty<OptionPaintProperty>();
            props->UpdateNeedDivider(false);
        }
        MountOption(optionNode);
        optionNode->MarkModifyDone();
        optionNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    }
    for (size_t i = childCount; i > updateCount; i--) {
        RemoveOption();
    }
    host->MarkModifyDone();
    host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
}

void MenuPattern::HideMenu(bool isMenuOnTouch) const
{
    auto wrapper = GetMenuWrapper();
    CHECK_NULL_VOID(wrapper);
    if (wrapper->GetTag() == V2::SELECT_OVERLAY_ETS_TAG) {
        return;
    }
    if (IsContextMenu()) {
        SubwindowManager::GetInstance()->HideMenuNG(wrapper, targetId_);
        return;
    }
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto overlayManager = pipeline->GetOverlayManager();
    CHECK_NULL_VOID(overlayManager);
    overlayManager->HideMenu(wrapper, targetId_, isMenuOnTouch);
    LOGI("MenuPattern closing menu %{public}d", targetId_);
}

void MenuPattern::HideSubMenu()
{
    if (!showedSubMenu_) {
        return;
    }
    auto subMenuPattern = showedSubMenu_->GetPattern<MenuPattern>();
    CHECK_NULL_VOID(subMenuPattern);
    subMenuPattern->RemoveParentHoverStyle();

    auto menuItem = subMenuPattern->GetParentMenuItem();
    CHECK_NULL_VOID(menuItem);
    auto menuItemPattern = menuItem->GetPattern<MenuItemPattern>();
    CHECK_NULL_VOID(menuItemPattern);
    menuItemPattern->SetIsSubMenuShowed(false);
    menuItemPattern->ClearHoverRegions();
    menuItemPattern->ResetWrapperMouseEvent();

    auto wrapper = GetMenuWrapper();
    CHECK_NULL_VOID(wrapper);
    wrapper->RemoveChild(showedSubMenu_);
    wrapper->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF_AND_CHILD);
    showedSubMenu_.Reset();
}

RefPtr<FrameNode> MenuPattern::GetMenuWrapper() const
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, nullptr);
    auto parent = host->GetParent();
    while (parent) {
        if (parent->GetTag() == V2::MENU_WRAPPER_ETS_TAG || parent->GetTag() == V2::SELECT_OVERLAY_ETS_TAG) {
            return AceType::DynamicCast<FrameNode>(parent);
        }
        parent = parent->GetParent();
    }
    return nullptr;
}

// search for inner <Menu> node, once found a <Menu> node, count the number of sibling <Menu>
uint32_t MenuPattern::GetInnerMenuCount() const
{
    if (type_ == MenuType::MULTI_MENU || type_ == MenuType::DESKTOP_MENU) {
        return 0;
    }

    auto host = GetHost();
    CHECK_NULL_RETURN(host, 0);
    auto child = host->GetChildAtIndex(0);
    uint32_t depth = 0;
    while (child && depth < MAX_SEARCH_DEPTH) {
        // found component <Menu>
        if (child->GetTag() == V2::MENU_ETS_TAG) {
            auto parent = child->GetParent();
            CHECK_NULL_RETURN(parent, 0);
            return parent->GetChildren().size();
        }
        child = child->GetChildAtIndex(0);
        ++depth;
    }
    return 0;
}

RefPtr<FrameNode> MenuPattern::GetFirstInnerMenu() const
{
    if (type_ == MenuType::MULTI_MENU || type_ == MenuType::DESKTOP_MENU) {
        return nullptr;
    }

    auto host = GetHost();
    CHECK_NULL_RETURN(host, nullptr);
    uint32_t depth = 0;
    auto child = host->GetChildAtIndex(0);
    while (child && depth < MAX_SEARCH_DEPTH) {
        // found component <Menu>
        if (child->GetTag() == V2::MENU_ETS_TAG) {
            return AceType::DynamicCast<FrameNode>(child);
        }
        child = child->GetChildAtIndex(0);
        ++depth;
    }
    return nullptr;
}

void MenuPattern::CopyMenuAttr(const RefPtr<FrameNode>& menuNode) const
{
    auto pattern = AceType::DynamicCast<MenuPattern>(menuNode->GetPattern());
    CHECK_NULL_VOID(pattern);

    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto rootMenuPattern = AceType::DynamicCast<MenuPattern>(host->GetPattern());
    CHECK_NULL_VOID(rootMenuPattern);

    // copy menu pattern properties to rootMenu
    auto layoutProperty = pattern->GetLayoutProperty<MenuLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    auto rootMenuLayoutProperty = rootMenuPattern->GetLayoutProperty<MenuLayoutProperty>();
    CHECK_NULL_VOID(rootMenuLayoutProperty);
    if (layoutProperty->GetBorderRadius().has_value()) {
        rootMenuLayoutProperty->UpdateBorderRadius(layoutProperty->GetBorderRadiusValue());
    }
}

// mount option on menu
void MenuPattern::MountOption(const RefPtr<FrameNode>& option)
{
    auto column = GetMenuColumn();
    CHECK_NULL_VOID(column);
    auto pattern = option->GetPattern<OptionPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetMenu(GetHost());
    AddOptionNode(option);
    option->MountToParent(column);
}

// remove option from menu
void MenuPattern::RemoveOption()
{
    auto column = GetMenuColumn();
    CHECK_NULL_VOID(column);
    auto endOption = column->GetChildren().back();
    CHECK_NULL_VOID(endOption);
    column->RemoveChild(endOption);
    PopOptionNode();
}

RefPtr<FrameNode> MenuPattern::GetMenuColumn() const
{
    auto menu = GetHost();
    CHECK_NULL_RETURN(menu, nullptr);
    auto scroll = menu->GetChildren().front();
    CHECK_NULL_RETURN(scroll, nullptr);
    auto column = scroll->GetChildren().front();
    return DynamicCast<FrameNode>(column);
}

void MenuPattern::DisableTabInMenu()
{
    if (IsMultiMenu()) {
        // multi menu not has scroll and column
        return;
    }
    // disable tab in menu
    auto column = GetMenuColumn();
    CHECK_NULL_VOID(column);
    auto columnFocusHub = column->GetOrCreateFocusHub();
    CHECK_NULL_VOID(columnFocusHub);

    auto onKeyEvent = [](const KeyEvent& event) -> bool {
        if (event.action != KeyAction::DOWN) {
            return false;
        }
        return event.code == KeyCode::KEY_TAB;
    };
    columnFocusHub->SetOnKeyEventInternal(std::move(onKeyEvent));
}

RefPtr<LayoutAlgorithm> MenuPattern::CreateLayoutAlgorithm()
{
    switch (type_) {
        case MenuType::MULTI_MENU:
        case MenuType::DESKTOP_MENU:
            return MakeRefPtr<MultiMenuLayoutAlgorithm>();
        case MenuType::SUB_MENU:
        case MenuType::SELECT_OVERLAY_SUB_MENU:
            return MakeRefPtr<SubMenuLayoutAlgorithm>();
        default:
            return MakeRefPtr<MenuLayoutAlgorithm>(targetId_, targetTag_);
    }
}

void MenuPattern::ResetTheme(const RefPtr<FrameNode>& host, bool resetForDesktopMenu)
{
    auto renderContext = host->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    auto scroll = DynamicCast<FrameNode>(host->GetFirstChild());
    CHECK_NULL_VOID(scroll);

    renderContext->UpdateBackgroundColor(Color::TRANSPARENT);

    if (resetForDesktopMenu) {
        // DesktopMenu apply shadow on inner Menu node
        renderContext->UpdateBackShadow(ShadowConfig::NoneShadow);
    } else {
        renderContext->UpdateBackShadow(ShadowConfig::DefaultShadowM);
    }
    // to enable inner menu shadow effect for desktopMenu, need to remove clipping from container
    bool clip = !resetForDesktopMenu;
    scroll->GetRenderContext()->SetClipToBounds(clip);

    // move padding from scroll to inner menu
    auto scrollProp = scroll->GetLayoutProperty();
    scrollProp->UpdatePadding(PaddingProperty());
}

void MenuPattern::InitTheme(const RefPtr<FrameNode>& host)
{
    auto renderContext = host->GetRenderContext();
    CHECK_NULL_VOID(renderContext);

    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto theme = pipeline->GetTheme<SelectTheme>();

    auto bgColor = theme->GetBackgroundColor();
    renderContext->UpdateBackgroundColor(bgColor);
    renderContext->UpdateBackShadow(ShadowConfig::DefaultShadowM);
    // make menu round rect
    BorderRadiusProperty borderRadius;
    borderRadius.SetRadius(theme->GetMenuBorderRadius());
    renderContext->UpdateBorderRadius(borderRadius);
}

void InnerMenuPattern::InitTheme(const RefPtr<FrameNode>& host)
{
    MenuPattern::InitTheme(host);
    // inner menu applies shadow in OnModifyDone(), where it can determine if it's a DesktopMenu or a regular menu

    auto layoutProperty = host->GetLayoutProperty();
    if (layoutProperty->GetPaddingProperty()) {
        // if user defined padding exists, skip applying default padding
        return;
    }
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto theme = pipeline->GetTheme<SelectTheme>();
    // apply default padding from theme on inner menu
    PaddingProperty padding;
    padding.SetEdges(CalcLength(theme->GetOutPadding()));
    host->GetLayoutProperty()->UpdatePadding(padding);

    host->GetRenderContext()->SetClipToBounds(true);
}

void MenuPattern::SetAccessibilityAction()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto accessibilityProperty = host->GetAccessibilityProperty<AccessibilityProperty>();
    CHECK_NULL_VOID(accessibilityProperty);
    accessibilityProperty->SetActionScrollForward([weakPtr = WeakClaim(this)]() {
        const auto& pattern = weakPtr.Upgrade();
        auto host = pattern->GetHost();
        CHECK_NULL_VOID(host);
        auto firstChild = DynamicCast<FrameNode>(host->GetChildAtIndex(0));
        CHECK_NULL_VOID(firstChild);
        if (firstChild && firstChild->GetTag() == V2::SCROLL_ETS_TAG) {
            auto scrollPattern = firstChild->GetPattern<ScrollPattern>();
            CHECK_NULL_VOID(scrollPattern);
            scrollPattern->ScrollPage(false, true);
        }
    });

    accessibilityProperty->SetActionScrollBackward([weakPtr = WeakClaim(this)]() {
        const auto& pattern = weakPtr.Upgrade();
        auto host = pattern->GetHost();
        CHECK_NULL_VOID(host);
        auto firstChild = DynamicCast<FrameNode>(host->GetChildAtIndex(0));
        CHECK_NULL_VOID(firstChild);
        if (firstChild && firstChild->GetTag() == V2::SCROLL_ETS_TAG) {
            auto scrollPattern = firstChild->GetPattern<ScrollPattern>();
            CHECK_NULL_VOID(scrollPattern);
            scrollPattern->ScrollPage(true, true);
        }
    });
}

bool MenuPattern::OnDirtyLayoutWrapperSwap(const RefPtr<LayoutWrapper>& dirty, const DirtySwapConfig& config)
{
    if (config.skipMeasure || dirty->SkipMeasureContent()) {
        return false;
    }

    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_RETURN(pipeline, false);
    auto theme = pipeline->GetTheme<SelectTheme>();
    CHECK_NULL_RETURN(theme, false);
    auto renderContext = dirty->GetHostNode()->GetRenderContext();
    CHECK_NULL_RETURN(renderContext, false);

    auto menuProp = DynamicCast<MenuLayoutProperty>(dirty->GetLayoutProperty());
    CHECK_NULL_RETURN(menuProp, false);
    BorderRadiusProperty radius;
    auto defaultRadius = theme->GetMenuBorderRadius();
    radius.SetRadius(defaultRadius);
    if (menuProp->GetBorderRadius().has_value()) {
        auto borderRadius = menuProp->GetBorderRadiusValue();
        auto topRadius =
            borderRadius.radiusTopLeft.value_or(Dimension()) + borderRadius.radiusTopRight.value_or(Dimension());
        auto bottomRadius =
            borderRadius.radiusBottomLeft.value_or(Dimension()) + borderRadius.radiusBottomRight.value_or(Dimension());
        auto menuRadius = std::max(topRadius.ConvertToPx(), bottomRadius.ConvertToPx());
        auto geometryNode = dirty->GetGeometryNode();
        CHECK_NULL_RETURN(geometryNode, false);
        auto idealSize = geometryNode->GetMarginFrameSize();
        if (LessNotEqual(menuRadius, idealSize.Width())) {
            radius = borderRadius;
        }
    }
    renderContext->UpdateBorderRadius(radius);
    return true;
}

RefPtr<MenuPattern> MenuPattern::GetMainMenuPattern() const
{
    auto wrapperFrameNode = GetMenuWrapper();
    CHECK_NULL_RETURN(wrapperFrameNode, nullptr);
    auto mainMenuUINode = wrapperFrameNode->GetChildAtIndex(0);
    CHECK_NULL_RETURN(mainMenuUINode, nullptr);
    auto mainMenuFrameNode = AceType::DynamicCast<FrameNode>(mainMenuUINode);
    return mainMenuFrameNode->GetPattern<MenuPattern>();
}

void InnerMenuPattern::RecordItemsAndGroups()
{
    itemsAndGroups_.clear();
    auto host = GetHost();
    std::stack<RefPtr<UINode>> nodeStack;
    nodeStack.emplace(host);
    bool isMenu = true;

    while (!nodeStack.empty()) {
        auto currentNode = nodeStack.top();
        nodeStack.pop();
        // push items and item groups, skip menu node
        if (!isMenu && AceType::InstanceOf<FrameNode>(currentNode)) {
            itemsAndGroups_.emplace_back(WeakClaim(RawPtr(currentNode)));
            continue;
        }
        isMenu = false;
        // skip other type UiNode, such as ForEachNode
        for (int32_t index = currentNode->GetChildren().size() - 1; index >= 0; index--) {
            nodeStack.push(currentNode->GetChildAtIndex(index));
        }
    }
}

uint32_t InnerMenuPattern::FindSiblingMenuCount()
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, 0);
    auto parent = host->GetParent();
    CHECK_NULL_RETURN(parent, 0);
    auto siblings = parent->GetChildren();
    uint32_t count = 0;
    for (auto&& sibling : siblings) {
        if (sibling->GetTag() == V2::MENU_ETS_TAG && sibling != host) {
            ++count;
        }
    }
    return count;
}

void InnerMenuPattern::ApplyDesktopMenuTheme()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    host->GetRenderContext()->UpdateBackShadow(ShadowConfig::DefaultShadowS);
}

void InnerMenuPattern::ApplyMultiMenuTheme()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    host->GetRenderContext()->UpdateBackShadow(ShadowConfig::NoneShadow);
}

void MenuPattern::OnColorConfigurationUpdate()
{
    auto host = GetHost();
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);

    auto menuTheme = pipeline->GetTheme<SelectTheme>();
    CHECK_NULL_VOID(menuTheme);

    auto menuPattern = host->GetPattern<MenuPattern>();
    CHECK_NULL_VOID(menuPattern);

    auto renderContext = host->GetRenderContext();
    renderContext->UpdateBackgroundColor(menuTheme->GetBackgroundColor());

    auto optionNode = menuPattern->GetOptions();
    for (const auto& child : optionNode) {
        auto optionsPattern = child->GetPattern<OptionPattern>();
        optionsPattern->SetFontColor(menuTheme->GetFontColor());

        child->MarkModifyDone();
        child->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
    }
    host->SetNeedCallChildrenUpdate(false);
}
void MenuPattern::DumpInfo()
{
    DumpLog::GetInstance().AddDesc(
        std::string("MenuType: ").append(std::to_string(static_cast<int32_t>(GetMenuType()))));
}
} // namespace OHOS::Ace::NG
