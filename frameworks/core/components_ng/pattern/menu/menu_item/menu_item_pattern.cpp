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

#include "core/components_ng/pattern/menu/menu_item/menu_item_pattern.h"

#include "menu_item_model.h"

#include "core/common/recorder/node_data_cache.h"
#include "core/components/common/properties/shadow_config.h"
#include "core/components/select/select_theme.h"
#include "core/components/text/text_theme.h"
#include "core/components/theme/icon_theme.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/image/image_pattern.h"
#include "core/components_ng/pattern/menu/menu_item/menu_item_event_hub.h"
#include "core/components_ng/pattern/menu/menu_item/menu_item_model_ng.h"
#include "core/components_ng/pattern/menu/menu_layout_property.h"
#include "core/components_ng/pattern/menu/menu_pattern.h"
#include "core/components_ng/pattern/menu/menu_theme.h"
#include "core/components_ng/pattern/menu/menu_view.h"
#include "core/components_ng/pattern/menu/wrapper/menu_wrapper_pattern.h"
#include "core/components_ng/pattern/text/text_layout_property.h"
#include "core/components_ng/pattern/text/text_pattern.h"
#include "core/components_ng/property/border_property.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "core/pipeline/pipeline_base.h"

namespace OHOS::Ace::NG {
namespace {
const Color ITEM_FILL_COLOR = Color::TRANSPARENT;
constexpr double VELOCITY = 0.0f;
constexpr double MASS = 1.0f;
constexpr double STIFFNESS = 328.0f;
constexpr double DAMPING = 33.0f;
constexpr double SEMI_CIRCLE_ANGEL = 180.0f;
constexpr float OPACITY_EFFECT = 0.99;
const std::string SYSTEM_RESOURCE_PREFIX = std::string("resource:///");
// id of system resource start from 0x07000000
constexpr unsigned long MIN_SYSTEM_RESOURCE_ID = 0x07000000;
// id of system resource end to 0x07FFFFFF
constexpr unsigned long MAX_SYSTEM_RESOURCE_ID = 0x07FFFFFF;

void UpdateFontSize(RefPtr<TextLayoutProperty>& textProperty, RefPtr<MenuLayoutProperty>& menuProperty,
    const std::optional<Dimension>& fontSize, const Dimension& defaultFontSize)
{
    if (fontSize.has_value()) {
        textProperty->UpdateFontSize(fontSize.value());
    } else if (menuProperty && menuProperty->GetFontSize().has_value()) {
        textProperty->UpdateFontSize(menuProperty->GetFontSize().value());
    } else {
        textProperty->UpdateFontSize(defaultFontSize);
    }
}

void UpdateFontWeight(RefPtr<TextLayoutProperty>& textProperty, RefPtr<MenuLayoutProperty>& menuProperty,
    const std::optional<FontWeight>& fontWeight)
{
    if (fontWeight.has_value()) {
        textProperty->UpdateFontWeight(fontWeight.value());
    } else if (menuProperty && menuProperty->GetFontWeight().has_value()) {
        textProperty->UpdateFontWeight(menuProperty->GetFontWeight().value());
    } else {
        if (Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_TWELVE)) {
            textProperty->UpdateFontWeight(FontWeight::MEDIUM);
        } else {
            textProperty->UpdateFontWeight(FontWeight::REGULAR);
        }
    }
}

void UpdateFontStyle(RefPtr<TextLayoutProperty>& textProperty, RefPtr<MenuLayoutProperty>& menuProperty,
    const std::optional<Ace::FontStyle>& fontStyle)
{
    if (fontStyle.has_value()) {
        textProperty->UpdateItalicFontStyle(fontStyle.value());
    } else if (menuProperty && menuProperty->GetItalicFontStyle().has_value()) {
        textProperty->UpdateItalicFontStyle(menuProperty->GetItalicFontStyle().value());
    } else {
        textProperty->UpdateItalicFontStyle(Ace::FontStyle::NORMAL);
    }
}

void UpdateFontColor(const RefPtr<FrameNode>& textNode, RefPtr<MenuLayoutProperty>& menuProperty,
    const std::optional<Color>& fontColor, const Color& defaultFontColor)
{
    auto textProperty = textNode ? textNode->GetLayoutProperty<TextLayoutProperty>() : nullptr;
    CHECK_NULL_VOID(textProperty);
    auto renderContext = textNode->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    if (fontColor.has_value()) {
        textProperty->UpdateTextColor(fontColor.value());
    } else if (menuProperty && menuProperty->GetFontColor().has_value()) {
        textProperty->UpdateTextColor(menuProperty->GetFontColor().value());
    } else {
        textProperty->UpdateTextColor(defaultFontColor);
    }
}

void UpdateFontFamily(RefPtr<TextLayoutProperty>& textProperty, RefPtr<MenuLayoutProperty>& menuProperty,
    const std::optional<std::vector<std::string>>& fontFamilies)
{
    if (fontFamilies.has_value()) {
        textProperty->UpdateFontFamily(fontFamilies.value());
    } else if (menuProperty && menuProperty->GetFontFamily().has_value()) {
        textProperty->UpdateFontFamily(menuProperty->GetFontFamily().value());
    }
}

void UpdateIconSrc(RefPtr<FrameNode>& node, const Dimension& horizontalSize,
    const Dimension& verticalSize, const Color& color, const bool& useDefaultIcon)
{
    auto props = node->GetLayoutProperty<ImageLayoutProperty>();
    CHECK_NULL_VOID(props);
    props->UpdateAlignment(Alignment::CENTER);
    CalcSize idealSize = { CalcLength(horizontalSize), CalcLength(verticalSize) };
    MeasureProperty layoutConstraint;
    layoutConstraint.selfIdealSize = idealSize;
    props->UpdateCalcLayoutProperty(layoutConstraint);
    if (useDefaultIcon) {
        auto iconRenderProperty = node->GetPaintProperty<ImageRenderProperty>();
        CHECK_NULL_VOID(iconRenderProperty);
        iconRenderProperty->UpdateSvgFillColor(color);
    }
}
} // namespace

void MenuItemPattern::OnMountToParentDone()
{
    UpdateTextNodes();
}

void MenuItemPattern::OnAttachToFrameNode()
{
    RegisterOnKeyEvent();
    RegisterOnClick();
    RegisterOnTouch();
    RegisterOnHover();
}

void CustomMenuItemPattern::OnAttachToFrameNode()
{
    RegisterOnKeyEvent();
    RegisterOnTouch();
}

void MenuItemPattern::OnModifyDone()
{
    Pattern::OnModifyDone();
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    RefPtr<FrameNode> leftRow =
        host->GetChildAtIndex(0) ? AceType::DynamicCast<FrameNode>(host->GetChildAtIndex(0)) : nullptr;
    CHECK_NULL_VOID(leftRow);
    AddSelectIcon(leftRow);
    UpdateIcon(leftRow, true);
    auto menuNode = GetMenu();
    auto menuProperty = menuNode ? menuNode->GetLayoutProperty<MenuLayoutProperty>() : nullptr;
    UpdateText(leftRow, menuProperty, false);

    if (menuProperty) {
        expandingMode_ = menuProperty->GetExpandingMode().value_or(SubMenuExpandingMode::SIDE);
        expandingModeSet_ = true;
    }

    RefPtr<FrameNode> rightRow =
        host->GetChildAtIndex(1) ? AceType::DynamicCast<FrameNode>(host->GetChildAtIndex(1)) : nullptr;
    CHECK_NULL_VOID(rightRow);
    UpdateText(rightRow, menuProperty, true);
    UpdateIcon(rightRow, false);
    AddExpandIcon(rightRow);
    AddClickableArea();
    if (IsDisabled()) {
        UpdateDisabledStyle();
    }
    SetAccessibilityAction();

    host->GetRenderContext()->SetClipToBounds(true);
    if (!longPressEvent_ && Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_TWELVE)) {
        InitLongPressEvent();
    }
    if (expandingModeSet_) {
        RegisterOnKeyEvent();
        RegisterOnTouch();
        RegisterOnHover();
        RegisterOnClick();
    }
}

void MenuItemPattern::OnAfterModifyDone()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto inspectorId = host->GetInspectorId().value_or("");
    if (inspectorId.empty()) {
        return;
    }
    auto itemProperty = GetLayoutProperty<MenuItemLayoutProperty>();
    CHECK_NULL_VOID(itemProperty);
    auto content = itemProperty->GetContent().value_or("");
    Recorder::NodeDataCache::Get().PutMultiple(host, inspectorId, content, isSelected_);
}

void MenuItemPattern::RecordChangeEvent() const
{
    if (!Recorder::EventRecorder::Get().IsComponentRecordEnable()) {
        return;
    }
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto inspectorId = host->GetInspectorId().value_or("");
    auto itemProperty = GetLayoutProperty<MenuItemLayoutProperty>();
    CHECK_NULL_VOID(itemProperty);
    auto content = itemProperty->GetContent().value_or("");
    Recorder::EventParamsBuilder builder;
    builder.SetId(inspectorId)
        .SetType(host->GetTag())
        .SetChecked(isSelected_)
        .SetText(content)
        .SetDescription(host->GetAutoEventParamValue(""));
    Recorder::EventRecorder::Get().OnChange(std::move(builder));
    Recorder::NodeDataCache::Get().PutMultiple(host, inspectorId, content, isSelected_);
}

RefPtr<FrameNode> MenuItemPattern::GetMenuWrapper()
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

RefPtr<FrameNode> MenuItemPattern::GetMenu(bool needTopMenu)
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, nullptr);
    auto parent = host->GetParent();
    RefPtr<FrameNode> menuNode = nullptr;
    while (parent) {
        if (parent->GetTag() == V2::MENU_ETS_TAG) {
            menuNode = AceType::DynamicCast<FrameNode>(parent);
            if (!needTopMenu) {
                // innner menu
                return menuNode;
            }
        }
        parent = parent->GetParent();
    }
    // outter menu
    return menuNode;
}

RefPtr<MenuPattern> MenuItemPattern::GetMenuPattern(bool needTopMenu)
{
    auto menu = GetMenu(needTopMenu);
    if (!menu) {
        return nullptr;
    }
    return menu->GetPattern<MenuPattern>();
}

void MenuItemPattern::ShowSubMenu(ShowSubMenuType type)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto menuNode = GetMenu(true);
    CHECK_NULL_VOID(menuNode);
    auto customNode = BuildSubMenuCustomNode();
    CHECK_NULL_VOID(customNode);
    UpdateSubmenuExpandingMode(customNode);
    if (expandingMode_ == SubMenuExpandingMode::EMBEDDED) {
        auto frameNode = AceType::DynamicCast<FrameNode>(customNode);
        OnExpandChanged(frameNode);
        return;
    }

    auto menuPattern = menuNode->GetPattern<MenuPattern>();
    CHECK_NULL_VOID(menuPattern);
    menuPattern->FocusViewHide();
    HideSubMenu();
    isSubMenuShowed_ = true;
    bool isSelectOverlayMenu = IsSelectOverlayMenu();
    MenuParam param;
    auto outterMenuLayoutProps = menuNode->GetLayoutProperty<MenuLayoutProperty>();
    CHECK_NULL_VOID(outterMenuLayoutProps);
    param.isShowInSubWindow = outterMenuLayoutProps->GetShowInSubWindowValue(false);
    auto focusMenuRenderContext = menuNode->GetRenderContext();
    CHECK_NULL_VOID(focusMenuRenderContext);
    if (focusMenuRenderContext->GetBackBlurStyle().has_value()) {
        auto focusMenuBlurStyle = focusMenuRenderContext->GetBackBlurStyle();
        param.backgroundBlurStyle = static_cast<int>(focusMenuBlurStyle->blurStyle);
    }
    param.type = isSelectOverlayMenu ? MenuType::SELECT_OVERLAY_SUB_MENU : MenuType::SUB_MENU;
    ParseMenuRadius(param);
    auto subMenu = MenuView::Create(customNode, host->GetId(), host->GetTag(), param);
    CHECK_NULL_VOID(subMenu);
    ShowSubMenuHelper(subMenu);
    menuPattern->SetShowedSubMenu(subMenu);
    auto subMenuPattern = subMenu->GetPattern<MenuPattern>();
    CHECK_NULL_VOID(subMenuPattern);
    if (type == ShowSubMenuType::KEY_DPAD_RIGHT) {
        subMenuPattern->SetIsViewRootScopeFocused(false);
    }
    auto accessibilityProperty = subMenu->GetAccessibilityProperty<MenuAccessibilityProperty>();
    CHECK_NULL_VOID(accessibilityProperty);
    accessibilityProperty->SetAccessibilityIsShow(true);
    subMenu->OnAccessibilityEvent(AccessibilityEventType::PAGE_OPEN);
    TAG_LOGI(AceLogTag::ACE_OVERLAY, "show sub menu, open type %{public}d", type);
}

RefPtr<UINode> MenuItemPattern::BuildSubMenuCustomNode()
{
    auto menuWrapper = GetMenuWrapper();
    CHECK_NULL_RETURN(menuWrapper, nullptr);
    auto menuWrapperPattern = menuWrapper->GetPattern<MenuWrapperPattern>();
    CHECK_NULL_RETURN(menuWrapperPattern, nullptr);
    auto hasSubMenu = menuWrapperPattern->HasStackSubMenu();
    auto buildFunc = GetSubBuilder();
    if (!buildFunc || isSubMenuShowed_ || IsEmbedded() ||
        (expandingMode_ == SubMenuExpandingMode::STACK && hasSubMenu)) {
        return nullptr;
    }

    NG::ScopedViewStackProcessor builderViewStackProcessor;
    buildFunc();
    return NG::ViewStackProcessor::GetInstance()->Finish();
}

RefPtr<FrameNode> GetSubMenu(RefPtr<UINode>& customNode)
{
    CHECK_NULL_RETURN(customNode, nullptr);
    if (customNode->GetTag() == V2::MENU_ETS_TAG) {
        auto frameNode = AceType::DynamicCast<FrameNode>(customNode);
        CHECK_NULL_RETURN(frameNode, nullptr);
        return frameNode;
    }
    uint32_t depth = 0;
    auto child = customNode->GetFrameChildByIndex(0, false);
    while (child && depth < MAX_SEARCH_DEPTH) {
        if (child->GetTag() == V2::JS_VIEW_ETS_TAG) {
            child = child->GetFrameChildByIndex(0, false);
            if (child && child->GetTag() == V2::JS_VIEW_ETS_TAG) {
                child  = child->GetChildAtIndex(0);
                ++depth;
            }
            continue;
        }
        if (child->GetTag() == V2::MENU_ETS_TAG) {
            return AceType::DynamicCast<FrameNode>(child);
        }
        child  = child->GetChildAtIndex(0);
        ++depth;
    }
    return nullptr;
}

void MenuItemPattern::UpdateSubmenuExpandingMode(RefPtr<UINode>& customNode)
{
    auto frameNode = GetSubMenu(customNode);
    CHECK_NULL_VOID(frameNode);
    if (frameNode->GetTag() == V2::MENU_ETS_TAG) {
        auto props = frameNode->GetLayoutProperty<MenuLayoutProperty>();
        CHECK_NULL_VOID(props);
        auto pattern = frameNode->GetPattern<MenuPattern>();
        CHECK_NULL_VOID(pattern);
        props->UpdateExpandingMode(expandingMode_);
        if (expandingMode_ == SubMenuExpandingMode::STACK) {
            AddStackSubMenuHeader(frameNode);
            pattern->SetIsStackSubmenu();
        } else if (expandingMode_ == SubMenuExpandingMode::EMBEDDED) {
            pattern->SetIsEmbedded();
            return;
        }
        frameNode->MarkModifyDone();
        frameNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF_AND_CHILD);
    }
}

void MenuItemPattern::ShowSubMenuHelper(const RefPtr<FrameNode>& subMenu)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    bool isSelectOverlayMenu = IsSelectOverlayMenu();
    auto menuPattern = subMenu->GetPattern<MenuPattern>();
    CHECK_NULL_VOID(menuPattern);
    menuPattern->SetParentMenuItem(host);
    subMenuId_ = subMenu->GetId();
    AddSelfHoverRegion(host);
    auto menuWrapper = GetMenuWrapper();
    CHECK_NULL_VOID(menuWrapper);
    if (Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_TWELVE) &&
        expandingMode_ == SubMenuExpandingMode::STACK) {
        SetClickMenuItemId(host->GetId());
        subMenu->MountToParent(menuWrapper);
        menuWrapper->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF_AND_CHILD);
        menuPattern->SetSubMenuShow();
        RegisterWrapperMouseEvent();
    } else {
        subMenu->MountToParent(menuWrapper);
        OffsetF offset = GetSubMenuPosition(host);
        auto menuProps = subMenu->GetLayoutProperty<MenuLayoutProperty>();
        CHECK_NULL_VOID(menuProps);
        menuProps->UpdateMenuOffset(offset);
        menuWrapper->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF_AND_CHILD);
        RegisterWrapperMouseEvent();
    }
    // select overlay menu no need focus
    if (!isSelectOverlayMenu) {
        menuPattern->FocusViewShow();
    }
}

void MenuItemPattern::HideSubMenu()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto menuWrapper = GetMenuWrapper();
    CHECK_NULL_VOID(menuWrapper);
    auto menuWrapperPattern = menuWrapper->GetPattern<MenuWrapperPattern>();
    CHECK_NULL_VOID(menuWrapperPattern);
    auto showedSubMenu = menuWrapperPattern->GetShowedSubMenu();
    if (showedSubMenu) {
        auto showedSubMenuPattern = showedSubMenu->GetPattern<MenuPattern>();
        CHECK_NULL_VOID(showedSubMenuPattern);
        auto showedMenuItem = showedSubMenuPattern->GetParentMenuItem();
        CHECK_NULL_VOID(showedMenuItem);
        if (showedMenuItem->GetId() != host->GetId()) {
            auto outterMenu = GetMenu(true);
            CHECK_NULL_VOID(outterMenu);
            auto outterMenuPattern = outterMenu->GetPattern<MenuPattern>();
            CHECK_NULL_VOID(outterMenuPattern);
            outterMenuPattern->HideSubMenu();
        }
    }
}

void MenuItemPattern::OnExpandChanged(const RefPtr<FrameNode>& expandableNode)
{
    CHECK_NULL_VOID(expandableNode);
    isExpanded_ = !isExpanded_;
    if (isExpanded_) {
        embeddedMenu_ = expandableNode;
        ShowEmbeddedExpandMenu(embeddedMenu_);
    } else {
        HideEmbeddedExpandMenu(embeddedMenu_);
        embeddedMenu_ = nullptr;
    }
}

void MenuItemPattern::ShowEmbeddedExpandMenu(const RefPtr<FrameNode>& expandableNode)
{
    CHECK_NULL_VOID(expandableNode);
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto menuWrapper = GetMenuWrapper();
    CHECK_NULL_VOID(menuWrapper);
    auto menuWrapperPattern = menuWrapper->GetPattern<MenuWrapperPattern>();
    CHECK_NULL_VOID(menuWrapperPattern);
    menuWrapperPattern->IncreaseEmbeddedSubMenuCount();
    auto rightRow = AceType::DynamicCast<FrameNode>(host->GetChildAtIndex(1));
    CHECK_NULL_VOID(rightRow);
    auto imageNode = AceType::DynamicCast<FrameNode>(rightRow->GetChildren().back());
    CHECK_NULL_VOID(imageNode);
    auto imageContext = imageNode->GetRenderContext();
    CHECK_NULL_VOID(imageContext);
    imageContext->UpdateTransformRotate(Vector5F(0.0f, 0.0f, 1.0f, 0.0f, 0.0f));

    auto expandableAreaContext = expandableNode->GetRenderContext();
    CHECK_NULL_VOID(expandableAreaContext);
    expandableAreaContext->UpdateBackShadow(ShadowConfig::NoneShadow);
    auto itemSize = host->GetGeometryNode()->GetFrameSize();
    expandableAreaContext->ClipWithRRect(RectF(0.0f, 0.0f, itemSize.Width(), 0.0f),
        RadiusF(EdgeF(0.0f, 0.0f)));

    AnimationOption option = AnimationOption();
    auto rotateOption = AceType::MakeRefPtr<InterpolatingSpring>(VELOCITY, MASS, STIFFNESS, DAMPING);
    option.SetCurve(rotateOption);
    AnimationUtils::Animate(option, [host, rightRow, expandableNode, expandableAreaContext, imageContext]() {
        expandableNode->MountToParent(host, EXPANDABLE_AREA_VIEW_INDEX);
        imageContext->UpdateTransformRotate(Vector5F(0.0f, 0.0f, 1.0f, SEMI_CIRCLE_ANGEL, 0.0f));
        expandableNode->MarkModifyDone();
        expandableNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);

        auto pipeline = PipelineContext::GetCurrentContext();
        CHECK_NULL_VOID(pipeline);
        pipeline->FlushUITasks();
        auto expandableAreaFrameSize = expandableNode->GetGeometryNode()->GetFrameSize();
        expandableAreaContext->ClipWithRRect(RectF(0.0f, 0.0f, expandableAreaFrameSize.Width(),
            expandableAreaFrameSize.Height()), RadiusF(EdgeF(0.0f, 0.0f)));
    });
}

void MenuItemPattern::HideEmbeddedExpandMenu(const RefPtr<FrameNode>& expandableNode)
{
    CHECK_NULL_VOID(expandableNode);
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto menuWrapper = GetMenuWrapper();
    CHECK_NULL_VOID(menuWrapper);
    auto menuWrapperPattern = menuWrapper->GetPattern<MenuWrapperPattern>();
    CHECK_NULL_VOID(menuWrapperPattern);
    menuWrapperPattern->DecreaseEmbeddedSubMenuCount();
    auto expandableAreaContext = expandableNode->GetRenderContext();
    CHECK_NULL_VOID(expandableAreaContext);

    AnimationOption option = AnimationOption();
    auto rotateOption = AceType::MakeRefPtr<InterpolatingSpring>(VELOCITY, MASS, STIFFNESS, DAMPING);
    option.SetCurve(rotateOption);
    RefPtr<ChainedTransitionEffect> opacity = AceType::MakeRefPtr<ChainedOpacityEffect>(OPACITY_EFFECT);
    expandableAreaContext->UpdateChainedTransition(opacity);

    AnimationUtils::Animate(option, [this, host, expandableNode]() {
        host->RemoveChild(expandableNode, true);
        host->MarkModifyDone();
        host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
        auto rightRow = AceType::DynamicCast<FrameNode>(host->GetChildAtIndex(1));
        CHECK_NULL_VOID(rightRow);
        auto imageNode = AceType::DynamicCast<FrameNode>(rightRow->GetChildren().back());
        CHECK_NULL_VOID(imageNode);
        auto imageContext = imageNode->GetRenderContext();
        CHECK_NULL_VOID(imageContext);
        imageContext->UpdateTransformRotate(Vector5F(0.0f, 0.0f, 1.0f, 0.0f, 0.0f));
        auto pipeline = PipelineContext::GetCurrentContext();
        CHECK_NULL_VOID(pipeline);
        pipeline->FlushUITasks();
    });
}

void MenuItemPattern::CloseMenu()
{
    // no need close for selection menu
    if (IsSelectOverlayMenu()) {
        return;
    }
    auto menuWrapper = GetMenuWrapper();
    CHECK_NULL_VOID(menuWrapper);
    auto menuWrapperPattern = menuWrapper->GetPattern<MenuWrapperPattern>();
    CHECK_NULL_VOID(menuWrapperPattern);
    menuWrapperPattern->UpdateMenuAnimation(menuWrapper);
    TAG_LOGI(AceLogTag::ACE_MENU, "will hide menu.");
    menuWrapperPattern->HideMenu();
}

void MenuItemPattern::RegisterOnClick()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    if (!onClickEvent_) {
        auto event = [weak = WeakClaim(this)](GestureEvent& /* info */) {
            auto pattern = weak.Upgrade();
            CHECK_NULL_VOID(pattern);
            pattern->OnClick();
        };
        onClickEvent_ = MakeRefPtr<ClickEvent>(std::move(event));
    }
    auto gestureHub = host->GetOrCreateGestureEventHub();
    CHECK_NULL_VOID(gestureHub);
    if (expandingMode_ == SubMenuExpandingMode::EMBEDDED && clickableArea_) {
        auto clickableAreaGestureHub = clickableArea_->GetOrCreateGestureEventHub();
        CHECK_NULL_VOID(clickableAreaGestureHub);
        gestureHub->RemoveClickEvent(onClickEvent_);
        clickableAreaGestureHub->AddClickEvent(onClickEvent_);
    } else if (!onClickEventSet_) {
        gestureHub->AddClickEvent(onClickEvent_);
        onClickEventSet_ = true;
    }
}

void MenuItemPattern::RegisterOnTouch()
{
    if (!onTouchEvent_) {
        auto touchCallback = [weak = WeakClaim(this)](const TouchEventInfo& info) {
            auto pattern = weak.Upgrade();
            CHECK_NULL_VOID(pattern);
            pattern->OnTouch(info);
        };
        onTouchEvent_ = MakeRefPtr<TouchEventImpl>(std::move(touchCallback));
    }
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto gestureHub = host->GetOrCreateGestureEventHub();
    CHECK_NULL_VOID(gestureHub);
    if (expandingMode_ == SubMenuExpandingMode::EMBEDDED && clickableArea_) {
        auto clickableAreaGestureHub = clickableArea_->GetOrCreateGestureEventHub();
        CHECK_NULL_VOID(clickableAreaGestureHub);
        gestureHub->RemoveTouchEvent(onTouchEvent_);
        clickableAreaGestureHub->AddTouchEvent(onTouchEvent_);
    } else if (!onTouchEventSet_) {
        gestureHub->AddTouchEvent(onTouchEvent_);
        onTouchEventSet_ = true;
    }
}

void MenuItemPattern::RegisterOnHover()
{
    if (!onHoverEvent_) {
        auto mouseTask = [weak = WeakClaim(this)](bool isHover) {
            auto pattern = weak.Upgrade();
            CHECK_NULL_VOID(pattern);
            pattern->OnHover(isHover);
        };
        onHoverEvent_ = MakeRefPtr<InputEvent>(std::move(mouseTask));
    }
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto inputHub = host->GetOrCreateInputEventHub();
    CHECK_NULL_VOID(inputHub);
    if (expandingMode_ == SubMenuExpandingMode::EMBEDDED && clickableArea_) {
        auto clickableAreaInputHub = clickableArea_->GetOrCreateInputEventHub();
        CHECK_NULL_VOID(clickableAreaInputHub);
        inputHub->RemoveOnHoverEvent(onHoverEvent_);
        clickableAreaInputHub->AddOnHoverEvent(onHoverEvent_);
    } else if (!onHoverEventSet_) {
        inputHub->AddOnHoverEvent(onHoverEvent_);
        onHoverEventSet_ = true;
    }
}

void MenuItemPattern::RegisterOnKeyEvent()
{
    auto onKeyEvent = [wp = WeakClaim(this)](const KeyEvent& event) -> bool {
        auto pattern = wp.Upgrade();
        CHECK_NULL_RETURN(pattern, false);
        return pattern->OnKeyEvent(event);
    };
    auto event = std::move(onKeyEvent);
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto focusHub = host->GetOrCreateFocusHub();
    CHECK_NULL_VOID(focusHub);
    if (expandingMode_ == SubMenuExpandingMode::EMBEDDED && clickableArea_) {
        auto clickableAreaFocusHub = clickableArea_->GetOrCreateFocusHub();
        CHECK_NULL_VOID(clickableAreaFocusHub);
        focusHub->SetOnKeyEventInternal(nullptr);
        clickableAreaFocusHub->SetOnKeyEventInternal(event);
    } else if (!onKeyEventSet_) {
        focusHub->SetOnKeyEventInternal(event);
        onKeyEventSet_ = true;
    }
}

void MenuItemPattern::OnClick()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    if (onClickAIMenuItem_) {
        onClickAIMenuItem_();
    }
    auto menuWrapper = GetMenuWrapper();
    auto menuWrapperPattern = menuWrapper ? menuWrapper->GetPattern<MenuWrapperPattern>() : nullptr;
    auto hasSubMenu = menuWrapperPattern ? menuWrapperPattern->HasStackSubMenu() : false;
    if (expandingMode_ == SubMenuExpandingMode::STACK && !IsSubMenu() && hasSubMenu) {
        return;
    }
    if (expandingMode_ == SubMenuExpandingMode::STACK && IsStackSubmenuHeader()) {
        menuWrapperPattern->HideSubMenu();
        return;
    }
    auto hub = host->GetEventHub<MenuItemEventHub>();
    CHECK_NULL_VOID(hub);
    auto onChange = hub->GetOnChange();
    auto selectedChangeEvent = hub->GetSelectedChangeEvent();
    SetChange();
    if (selectedChangeEvent) {
        selectedChangeEvent(IsSelected());
    }
    if (onChange) {
        onChange(IsSelected());
        RecordChangeEvent();
    }
    host->OnAccessibilityEvent(AccessibilityEventType::SELECTED);
    auto menuNode = GetMenu();
    CHECK_NULL_VOID(menuNode);
    auto menuPattern = menuNode->GetPattern<MenuPattern>();
    CHECK_NULL_VOID(menuPattern);
    auto lastSelectedItem = menuPattern->GetLastSelectedItem();
    if (lastSelectedItem && lastSelectedItem != host) {
        auto pattern = lastSelectedItem->GetPattern<MenuItemPattern>();
        CHECK_NULL_VOID(pattern);
        pattern->SetChange();
    }
    menuPattern->SetLastSelectedItem(host);
    if (GetSubBuilder() != nullptr && (expandingMode_ == SubMenuExpandingMode::SIDE ||
        (expandingMode_ == SubMenuExpandingMode::STACK && !IsSubMenu() && !hasSubMenu) ||
        (expandingMode_ == SubMenuExpandingMode::EMBEDDED && !IsEmbedded()))) {
        ShowSubMenu(ShowSubMenuType::CLICK);
        return;
    }
    // hide menu when menu item is clicked
    CloseMenu();
}

void MenuItemPattern::OnTouch(const TouchEventInfo& info)
{
    // change menu item paint props on press
    auto touchType = info.GetTouches().front().GetTouchType();
    if (touchType == TouchType::DOWN) {
        // change background color, update press status
        NotifyPressStatus(true);
    } else if (touchType == TouchType::UP) {
        NotifyPressStatus(false);
    }
}

void MenuItemPattern::NotifyPressStatus(bool isPress)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto pipeline = host->GetContext();
    CHECK_NULL_VOID(pipeline);
    auto theme = pipeline->GetTheme<SelectTheme>();
    CHECK_NULL_VOID(theme);
    auto props = GetPaintProperty<MenuItemPaintProperty>();
    CHECK_NULL_VOID(props);
    auto menu = GetMenu();
    CHECK_NULL_VOID(menu);
    auto menuPattern = menu->GetPattern<MenuPattern>();
    CHECK_NULL_VOID(menuPattern);
    auto parent = AceType::DynamicCast<UINode>(host->GetParent());
    auto menuWrapper = GetMenuWrapper();
    auto menuWrapperPattern = menuWrapper ? menuWrapper->GetPattern<MenuWrapperPattern>() : nullptr;

    // do not change color for stacked level-1 menu items if level-2 is shown
    auto canChangeColor = !(expandingMode_ == SubMenuExpandingMode::STACK
        && menuWrapperPattern && menuWrapperPattern->HasStackSubMenu() && !IsSubMenu());
    if (!canChangeColor) return;

    if (isPress) {
        // change background color, update press status
        SetBgBlendColor(GetSubBuilder() ? theme->GetHoverColor() : theme->GetClickedColor());
        if (menuWrapperPattern) {
            menuWrapperPattern->SetLastTouchItem(host);
        }
        props->UpdatePress(true);
        menuPattern->OnItemPressed(parent, index_, true);
    } else {
        SetBgBlendColor(isHovered_ ? theme->GetHoverColor() : Color::TRANSPARENT);
        props->UpdatePress(false);
        menuPattern->OnItemPressed(parent, index_, false);
    }
    PlayBgColorAnimation(false);
    host->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
}

void CustomMenuItemPattern::OnTouch(const TouchEventInfo& info)
{
    auto touchType = info.GetTouches().front().GetTouchType();

    // close menu when touch up
    // can't use onClick because that conflicts with interactions developers might set to the customNode
    // recognize gesture as click if touch up position is close to last touch down position
    if (touchType == TouchType::DOWN) {
        lastTouchOffset_ = std::make_unique<Offset>(info.GetTouches().front().GetLocalLocation());
        auto menuWrapper = GetMenuWrapper();
        CHECK_NULL_VOID(menuWrapper);
        auto menuWrapperPattern = menuWrapper->GetPattern<MenuWrapperPattern>();
        CHECK_NULL_VOID(menuWrapperPattern);
        auto host = GetHost();
        CHECK_NULL_VOID(host);
        menuWrapperPattern->SetLastTouchItem(host);
    } else if (touchType == TouchType::UP) {
        auto touchUpOffset = info.GetTouches().front().GetLocalLocation();
        if (lastTouchOffset_ && (touchUpOffset - *lastTouchOffset_).GetDistance() <= DEFAULT_CLICK_DISTANCE) {
            if (Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_TWELVE)) {
                HandleOnChange();
            }
            CloseMenu();
        }
        lastTouchOffset_.reset();
    }
}

void CustomMenuItemPattern::HandleOnChange()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto hub = host->GetEventHub<MenuItemEventHub>();
    CHECK_NULL_VOID(hub);
    auto onChange = hub->GetOnChange();
    auto selectedChangeEvent = hub->GetSelectedChangeEvent();
    SetChange();
    if (selectedChangeEvent) {
        TAG_LOGI(AceLogTag::ACE_MENU, "trigger selectedChangeEvent");
        selectedChangeEvent(IsSelected());
    }
    if (onChange) {
        TAG_LOGI(AceLogTag::ACE_MENU, "trigger onChange");
        onChange(IsSelected());
    }
}

void MenuItemPattern::OnHover(bool isHover)
{
    isHovered_ = isHover;
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto theme = pipeline->GetTheme<SelectTheme>();
    CHECK_NULL_VOID(theme);
    auto props = GetPaintProperty<MenuItemPaintProperty>();
    CHECK_NULL_VOID(props);
    auto menu = GetMenu(false);
    CHECK_NULL_VOID(menu);
    auto menuPattern = menu->GetPattern<MenuPattern>();
    CHECK_NULL_VOID(menuPattern);
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto parent = AceType::DynamicCast<UINode>(host->GetParent());

    if (isHover || isSubMenuShowed_) {
        // keep hover color when subMenu showed
        SetBgBlendColor(theme->GetHoverColor());
        ShowSubMenu(ShowSubMenuType::HOVER);
        props->UpdateHover(true);
        menuPattern->OnItemPressed(parent, index_, true, true);
    } else {
        SetBgBlendColor(Color::TRANSPARENT);
        props->UpdateHover(false);
        menuPattern->OnItemPressed(parent, index_, false, true);
    }
    PlayBgColorAnimation();
    host->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
}

void MenuItemPattern::OnVisibleChange(bool isVisible)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto parentNode = host->GetParent();
    CHECK_NULL_VOID(parentNode);
    if (parentNode->GetTag() == V2::MENU_ITEM_GROUP_ETS_TAG) {
        parentNode->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
    }
}

bool MenuItemPattern::OnKeyEvent(const KeyEvent& event)
{
    if (event.action != KeyAction::DOWN) {
        return false;
    }
    auto host = GetHost();
    CHECK_NULL_RETURN(host, false);
    auto focusHub = host->GetOrCreateFocusHub();
    CHECK_NULL_RETURN(focusHub, false);
    if (event.code == KeyCode::KEY_ENTER) {
        focusHub->OnClick(event);
        return true;
    }
    if (event.code == KeyCode::KEY_DPAD_RIGHT && GetSubBuilder() && !isSubMenuShowed_) {
        auto pipeline = PipelineBase::GetCurrentContext();
        CHECK_NULL_RETURN(pipeline, false);
        auto theme = pipeline->GetTheme<SelectTheme>();
        CHECK_NULL_RETURN(theme, false);
        SetBgBlendColor(theme->GetHoverColor());
        PlayBgColorAnimation();
        host->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
        ShowSubMenu(ShowSubMenuType::KEY_DPAD_RIGHT);
        return true;
    }
    return false;
}

bool CustomMenuItemPattern::OnKeyEvent(const KeyEvent& event)
{
    if (event.action != KeyAction::DOWN) {
        return false;
    }
    auto host = GetHost();
    CHECK_NULL_RETURN(host, false);
    auto focusHub = host->GetOrCreateFocusHub();
    CHECK_NULL_RETURN(focusHub, false);
    if (event.code == KeyCode::KEY_ENTER || event.code == KeyCode::KEY_SPACE) {
        focusHub->OnClick(event);
        CloseMenu();
        return true;
    }
    return false;
}

void MenuItemPattern::InitLongPressEvent()
{
    auto gesture = GetHost()->GetOrCreateGestureEventHub();
    CHECK_NULL_VOID(gesture);
    auto longPressCallback = [weak = WeakClaim(this)](GestureEvent& info) {
        auto itemPattern = weak.Upgrade();
        auto menuWrapper = itemPattern->GetMenuWrapper();
        CHECK_NULL_VOID(menuWrapper);
        auto menuWrapperPattern = menuWrapper->GetPattern<MenuWrapperPattern>();
        CHECK_NULL_VOID(menuWrapperPattern);
        auto topLevelMenuPattern = itemPattern->GetMenuPattern(true);
        CHECK_NULL_VOID(topLevelMenuPattern);
        if (itemPattern && itemPattern->GetSubBuilder() != nullptr &&
            menuWrapperPattern->GetPreviewMode() == MenuPreviewMode::NONE &&
            !(topLevelMenuPattern->IsSelectOverlayCustomMenu())) {
            itemPattern->ShowSubMenu(ShowSubMenuType::LONG_PRESS);
        }
    };
    longPressEvent_ = MakeRefPtr<LongPressEvent>(std::move(longPressCallback));
    gesture->SetLongPressEvent(longPressEvent_);
}

void MenuItemPattern::RegisterWrapperMouseEvent()
{
    auto menuWrapper = GetMenuWrapper();
    if (menuWrapper && !wrapperMouseEvent_) {
        auto inputHub = menuWrapper->GetOrCreateInputEventHub();
        CHECK_NULL_VOID(inputHub);
        auto menuWrapperPattern = menuWrapper->GetPattern<MenuWrapperPattern>();
        CHECK_NULL_VOID(menuWrapperPattern);

        auto mouseTask = [weak = WeakClaim(this), menuWrapperPattern](MouseInfo& info) {
            auto pattern = weak.Upgrade();
            CHECK_NULL_VOID(pattern);
            if (menuWrapperPattern) {
                menuWrapperPattern->HandleMouseEvent(info, pattern);
            }
        };
        wrapperMouseEvent_ = MakeRefPtr<InputEvent>(std::move(mouseTask));
        inputHub->AddOnMouseEvent(wrapperMouseEvent_);
    }
}

void MenuItemPattern::AddSelfHoverRegion(const RefPtr<FrameNode>& targetNode)
{
    OffsetF topLeftPoint;
    OffsetF bottomRightPoint;
    auto frameSize = targetNode->GetGeometryNode()->GetMarginFrameSize();
    topLeftPoint = targetNode->GetPaintRectOffset();
    bottomRightPoint = targetNode->GetPaintRectOffset() + OffsetF(frameSize.Width(), frameSize.Height());
    AddHoverRegions(topLeftPoint, bottomRightPoint);
}

OffsetF MenuItemPattern::GetSubMenuPosition(const RefPtr<FrameNode>& targetNode)
{ // show menu at left top point of targetNode
    auto frameSize = targetNode->GetGeometryNode()->GetMarginFrameSize();
    OffsetF position = targetNode->GetPaintRectOffset() + OffsetF(frameSize.Width(), 0.0);
    return position;
}

void MenuItemPattern::AddHoverRegions(const OffsetF& topLeftPoint, const OffsetF& bottomRightPoint)
{
    TouchRegion hoverRegion = TouchRegion(
        Offset(topLeftPoint.GetX(), topLeftPoint.GetY()), Offset(bottomRightPoint.GetX(), bottomRightPoint.GetY()));
    hoverRegions_.emplace_back(hoverRegion);
}

bool MenuItemPattern::IsInHoverRegions(double x, double y)
{
    for (auto hoverRegion : hoverRegions_) {
        if (hoverRegion.ContainsInRegion(x, y)) {
            return true;
        }
    }
    return false;
}

void MenuItemPattern::PlayBgColorAnimation(bool isHoverChange)
{
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto theme = pipeline->GetTheme<SelectTheme>();
    CHECK_NULL_VOID(theme);
    AnimationOption option;
    if (isHoverChange) {
        option.SetDuration(theme->GetHoverAnimationDuration());
        option.SetCurve(Curves::FRICTION);
    } else {
        option.SetDuration(theme->GetPressAnimationDuration());
        option.SetCurve(Curves::SHARP);
    }

    AnimationUtils::Animate(option, [weak = WeakClaim(this)]() {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        auto clickableArea = pattern->GetClickableArea();
        CHECK_NULL_VOID(clickableArea);
        auto renderContext = clickableArea->GetRenderContext();
        CHECK_NULL_VOID(renderContext);
        renderContext->BlendBgColor(pattern->GetBgBlendColor());
    });
}

void MenuItemPattern::UpdateImageNode(RefPtr<FrameNode>& row, RefPtr<FrameNode>& selectIcon)
{
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto itemProperty = GetLayoutProperty<MenuItemLayoutProperty>();
    CHECK_NULL_VOID(itemProperty);
    auto symbol = itemProperty->GetSelectSymbol();
    if (itemProperty->GetSelectIconSrc().value_or("").empty() &&
        Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_TWELVE)) {
        // iamge -> symbol
        row->RemoveChild(selectIcon);
        selectIcon = FrameNode::GetOrCreateFrameNode(V2::SYMBOL_ETS_TAG,
            ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TextPattern>(); });
        auto selectTheme = pipeline->GetTheme<SelectTheme>();
        CHECK_NULL_VOID(selectTheme);
        auto props = selectIcon->GetLayoutProperty<TextLayoutProperty>();
        CHECK_NULL_VOID(props);
        props->UpdateFontSize(selectTheme->GetEndIconWidth());
        props->UpdateSymbolColorList({ selectTheme->GetMenuIconColor() });
        symbol(AccessibilityManager::WeakClaim(AccessibilityManager::RawPtr(selectIcon)));
    } else {
        // image -> image
        auto iconTheme = pipeline->GetTheme<IconTheme>();
        CHECK_NULL_VOID(iconTheme);
        auto userIcon = itemProperty->GetSelectIconSrc().value_or("");
        auto iconPath = userIcon.empty() ? iconTheme->GetIconPath(InternalResource::ResourceId::MENU_OK_SVG) : userIcon;
        auto selectTheme = pipeline->GetTheme<SelectTheme>();
        CHECK_NULL_VOID(selectTheme);
        ImageSourceInfo imageSourceInfo;
        imageSourceInfo.SetSrc(iconPath);
        auto props = selectIcon->GetLayoutProperty<ImageLayoutProperty>();
        CHECK_NULL_VOID(props);
        props->UpdateImageSourceInfo(imageSourceInfo);
        UpdateIconSrc(selectIcon, selectTheme->GetIconSideLength(), selectTheme->GetIconSideLength(),
            selectTheme->GetMenuIconColor(), userIcon.empty());
    }
}

void MenuItemPattern::UpdateSymbolNode(RefPtr<FrameNode>& row, RefPtr<FrameNode>& selectIcon)
{
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto props = selectIcon->GetLayoutProperty<TextLayoutProperty>();
    CHECK_NULL_VOID(props);
    auto itemProperty = GetLayoutProperty<MenuItemLayoutProperty>();
    CHECK_NULL_VOID(itemProperty);
    auto selectTheme = pipeline->GetTheme<SelectTheme>();
    CHECK_NULL_VOID(selectTheme);
    auto symbol = itemProperty->GetSelectSymbol();
    if (itemProperty->GetSelectIconSrc().value_or("").empty()) {
        // symbol -> symbol
        props->UpdateFontSize(selectTheme->GetEndIconWidth());
        props->UpdateSymbolColorList({ selectTheme->GetMenuIconColor() });
        if (symbol) {
            symbol(AccessibilityManager::WeakClaim(AccessibilityManager::RawPtr(selectIcon)));
        } else {
            auto menuTheme = pipeline->GetTheme<MenuTheme>();
            CHECK_NULL_VOID(menuTheme);
            uint32_t symbolId = menuTheme->GetSymbolId();
            props->UpdateSymbolSourceInfo(SymbolSourceInfo(symbolId));
        }
    } else {
        // symbol -> image
        row->RemoveChild(selectIcon);
        selectIcon = FrameNode::CreateFrameNode(
            V2::IMAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<ImagePattern>());
        ImageSourceInfo imageSourceInfo;
        auto userIcon = itemProperty->GetSelectIconSrc().value_or("");
        imageSourceInfo.SetSrc(userIcon);
        auto props = selectIcon->GetLayoutProperty<ImageLayoutProperty>();
        CHECK_NULL_VOID(props);
        props->UpdateImageSourceInfo(imageSourceInfo);
        UpdateIconSrc(selectIcon, selectTheme->GetIconSideLength(), selectTheme->GetIconSideLength(),
            selectTheme->GetMenuIconColor(), userIcon.empty());
    }
}

void MenuItemPattern::AddSelectIcon(RefPtr<FrameNode>& row)
{
    auto itemProperty = GetLayoutProperty<MenuItemLayoutProperty>();
    CHECK_NULL_VOID(itemProperty);
    if (!itemProperty->GetSelectIcon().value_or(false)) {
        if (selectIcon_) {
            row->RemoveChildAtIndex(0);
            selectIcon_ = nullptr;
            itemProperty->SetSelectSymbol(nullptr);
            row->MarkModifyDone();
            row->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
        }
        return;
    }
    if (!selectIcon_) {
        if (!itemProperty->GetSelectIconSrc().value_or("").empty() ||
            Container::LessThanAPITargetVersion(PlatformVersion::VERSION_TWELVE)) {
            selectIcon_ = FrameNode::CreateFrameNode(
                V2::IMAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<ImagePattern>());
        } else {
            selectIcon_ = FrameNode::GetOrCreateFrameNode(V2::SYMBOL_ETS_TAG,
                ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TextPattern>(); });
        }
    }
    if (selectIcon_->GetTag() == V2::IMAGE_ETS_TAG) {
        UpdateImageNode(row, selectIcon_);
    } else {
        UpdateSymbolNode(row, selectIcon_);
    }
    auto renderContext = selectIcon_->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    renderContext->SetVisible(isSelected_);

    selectIcon_->MountToParent(row, 0);
    selectIcon_->MarkModifyDone();
    selectIcon_->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
}

void MenuItemPattern::AddExpandIcon(RefPtr<FrameNode>& row)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto menuNode = GetMenu();
    auto menuPattern = menuNode ? menuNode->GetPattern<MenuPattern>() : nullptr;
    auto menuProperty = menuNode ? menuNode->GetLayoutProperty<MenuLayoutProperty>() : nullptr;
    CHECK_NULL_VOID(menuProperty);
    auto canExpand = GetSubBuilder() != nullptr && menuPattern
        && !menuPattern->IsEmbedded() && !menuPattern->IsStackSubmenu()
        && (expandingMode_ == SubMenuExpandingMode::EMBEDDED || expandingMode_ == SubMenuExpandingMode::STACK);
    if (!canExpand) {
        if (expandIcon_) {
            row->RemoveChild(expandIcon_);
            expandIcon_ = nullptr;
            row->MarkModifyDone();
            row->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
        }
        return;
    }
    if (!expandIcon_) {
        expandIcon_ = FrameNode::CreateFrameNode(
            V2::IMAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<ImagePattern>());
        CHECK_NULL_VOID(expandIcon_);
    }
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto iconTheme = pipeline->GetTheme<IconTheme>();
    CHECK_NULL_VOID(iconTheme);
    auto iconPath = iconTheme->GetIconPath(
        expandingMode_ == SubMenuExpandingMode::STACK
            ? InternalResource::ResourceId::IC_PUBLIC_ARROW_RIGHT_SVG
            : InternalResource::ResourceId::IC_PUBLIC_ARROW_DOWN_SVG);
    auto selectTheme = pipeline->GetTheme<SelectTheme>();
    CHECK_NULL_VOID(selectTheme);
    ImageSourceInfo imageSourceInfo(iconPath);
    auto props = expandIcon_->GetLayoutProperty<ImageLayoutProperty>();
    CHECK_NULL_VOID(props);
    props->UpdateImageSourceInfo(imageSourceInfo);
    UpdateIconSrc(expandIcon_, selectTheme->GetIconSideLength(), selectTheme->GetIconSideLength(),
        selectTheme->GetMenuIconColor(), true);

    auto expandIconIndex = row->GetChildren().size();
    expandIcon_->MountToParent(row, expandIconIndex);
    expandIcon_->MarkModifyDone();
    expandIcon_->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
}

void MenuItemPattern::AddClickableArea()
{
    if (expandingMode_ == SubMenuExpandingMode::EMBEDDED && GetSubBuilder() != nullptr && !IsEmbedded() &&
        !clickableArea_) {
        auto host = GetHost();
        CHECK_NULL_VOID(host);
        auto clickableArea = FrameNode::CreateFrameNode(V2::ROW_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
            AceType::MakeRefPtr<LinearLayoutPattern>(false));
        CHECK_NULL_VOID(clickableArea);
        auto pipeline = PipelineBase::GetCurrentContext();
        CHECK_NULL_VOID(pipeline);
        auto theme = pipeline->GetTheme<SelectTheme>();
        CHECK_NULL_VOID(theme);
        BorderRadiusProperty border;
        if (Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_TWELVE)) {
            border.SetRadius(theme->GetMenuDefaultInnerRadius());
        } else {
            border.SetRadius(theme->GetInnerBorderRadius());
        }
        auto clickableContext = clickableArea->GetRenderContext();
        CHECK_NULL_VOID(clickableContext);
        clickableContext->UpdateBorderRadius(border);
        auto menuProperty = host->GetLayoutProperty<MenuItemLayoutProperty>();
        CHECK_NULL_VOID(menuProperty);
        std::string content = menuProperty->GetContent().value_or("");
        std::string label = menuProperty->GetLabel().value_or("");
        auto accessibilityProperty = clickableArea->GetAccessibilityProperty<AccessibilityProperty>();
        CHECK_NULL_VOID(accessibilityProperty);
        accessibilityProperty->SetAccessibilityText(content + "," + label);
        clickableArea_ = clickableArea;
        clickableArea_->MountToParent(host, CLICKABLE_AREA_VIEW_INDEX);
    }
}

void MenuItemPattern::AddStackSubMenuHeader(RefPtr<FrameNode>& menuNode)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto layoutProperty = GetLayoutProperty<MenuItemLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto iconTheme = pipeline->GetTheme<IconTheme>();
    CHECK_NULL_VOID(iconTheme);
    auto selectTheme = pipeline->GetTheme<SelectTheme>();
    CHECK_NULL_VOID(selectTheme);
    auto iconPath = iconTheme->GetIconPath(InternalResource::ResourceId::IC_PUBLIC_ARROW_RIGHT_SVG);
    ImageSourceInfo imageSourceInfo;
    imageSourceInfo.SetSrc(iconPath);
    imageSourceInfo.SetFillColor(selectTheme->GetMenuIconColor());
    auto content = layoutProperty->GetContent().value_or(layoutProperty->GetLabel().value_or(""));

    MenuItemProperties menuItemProps;
    menuItemProps.content = content;
    menuItemProps.endIcon = imageSourceInfo;
    MenuItemModelNG menuItemModel;
    menuItemModel.Create(menuItemProps);
    auto stack = ViewStackProcessor::GetInstance();

    auto titleItem = AceType::DynamicCast<FrameNode>(stack->Finish());
    auto pattern = titleItem->GetPattern<MenuItemPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetIsStackSubmenuHeader();
    titleItem->MountToParent(menuNode, 0);
}

RefPtr<FrameNode> MenuItemPattern::GetClickableArea()
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, nullptr);
    auto clickableArea = host->GetChildAtIndex(CLICKABLE_AREA_VIEW_INDEX);
    CHECK_NULL_RETURN(clickableArea, host);
    auto clickableAreaNode = AceType::DynamicCast<FrameNode>(clickableArea);
    CHECK_NULL_RETURN(clickableAreaNode, host);
    return clickableAreaNode;
}

void MenuItemPattern::UpdateIcon(RefPtr<FrameNode>& row, bool isStart)
{
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto selectTheme = pipeline->GetTheme<SelectTheme>();
    CHECK_NULL_VOID(selectTheme);
    auto itemProperty = GetLayoutProperty<MenuItemLayoutProperty>();
    CHECK_NULL_VOID(itemProperty);
    ImageSourceInfo defaultImageSourceInfo;
    auto iconSrc = isStart ? itemProperty->GetStartIcon().value_or(defaultImageSourceInfo)
                           : itemProperty->GetEndIcon().value_or(defaultImageSourceInfo);
    auto symbol = isStart ? itemProperty->GetStartSymbol() : itemProperty->GetEndSymbol();
    auto& iconNode = isStart ? startIcon_ : endIcon_;
    if (iconSrc.GetSrc().empty() && symbol == nullptr) {
        row->RemoveChild(iconNode); // it's safe even if iconNode is nullptr
        iconNode = nullptr;
        if (isStart) {
            itemProperty->SetStartSymbol(nullptr);
        } else {
            itemProperty->SetEndSymbol(nullptr);
        }
        row->MarkModifyDone();
        row->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
        return;
    }
    if (!iconNode) {
        if (symbol) {
            iconNode = FrameNode::GetOrCreateFrameNode(V2::SYMBOL_ETS_TAG,
                ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TextPattern>(); });
        } else {
            iconNode = FrameNode::CreateFrameNode(
                V2::IMAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<ImagePattern>());
        }
        CHECK_NULL_VOID(iconNode);
    }
    if (iconNode->GetTag() == V2::IMAGE_ETS_TAG) {
        UpdateImageIcon(row, iconNode, iconSrc, symbol, isStart);
    } else {
        UpdateSymbolIcon(row, iconNode, iconSrc, symbol, isStart);
    }
    iconNode->MountToParent(row, ((isStart && selectIcon_) || (!isStart && label_)) ? 1 : 0);
    iconNode->MarkModifyDone();
    iconNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
}

void MenuItemPattern::UpdateImageIcon(RefPtr<FrameNode>& row, RefPtr<FrameNode>& iconNode, ImageSourceInfo& iconSrc,
    std::function<void(WeakPtr<NG::FrameNode>)>& symbol, bool isStart)
{
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto itemProperty = GetLayoutProperty<MenuItemLayoutProperty>();
    CHECK_NULL_VOID(itemProperty);
    auto selectTheme = pipeline->GetTheme<SelectTheme>();
    CHECK_NULL_VOID(selectTheme);
    if (symbol) {
        // iamge -> symbol
        row->RemoveChild(iconNode);
        iconNode = FrameNode::GetOrCreateFrameNode(V2::SYMBOL_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
            []() { return AceType::MakeRefPtr<TextPattern>(); });

        auto props = iconNode->GetLayoutProperty<TextLayoutProperty>();
        CHECK_NULL_VOID(props);
        props->UpdateFontSize(selectTheme->GetEndIconWidth());
        props->UpdateSymbolColorList({ selectTheme->GetMenuIconColor() });
        symbol(AccessibilityManager::WeakClaim(AccessibilityManager::RawPtr(iconNode)));
    } else {
        // image -> image
        auto iconWidth = isStart ? selectTheme->GetIconSideLength() : selectTheme->GetEndIconWidth();
        auto iconHeight = isStart ? selectTheme->GetIconSideLength() : selectTheme->GetEndIconHeight();
        ImageSourceInfo imageSourceInfo(iconSrc);
        auto props = iconNode->GetLayoutProperty<ImageLayoutProperty>();
        CHECK_NULL_VOID(props);
        props->UpdateImageSourceInfo(imageSourceInfo);
        bool useDefaultThemeIcon = UseDefaultThemeIcon(imageSourceInfo);
        UpdateIconSrc(iconNode, iconWidth, iconHeight, selectTheme->GetMenuIconColor(), useDefaultThemeIcon);
    }
}

bool MenuItemPattern::UseDefaultThemeIcon(const ImageSourceInfo& imageSourceInfo)
{
    if (imageSourceInfo.IsSvg()) {
        auto src = imageSourceInfo.GetSrc();
        auto srcId = src.substr(SYSTEM_RESOURCE_PREFIX.size(),
            src.substr(0, src.rfind(".svg")).size() - SYSTEM_RESOURCE_PREFIX.size());
        return (srcId.find("ohos_") != std::string::npos)
            || ((std::all_of(srcId.begin(), srcId.end(), ::isdigit))
                && (std::stoul(srcId) >= MIN_SYSTEM_RESOURCE_ID)
                && (std::stoul(srcId) <= MAX_SYSTEM_RESOURCE_ID));
    }
    return false;
}

void MenuItemPattern::UpdateSymbolIcon(RefPtr<FrameNode>& row, RefPtr<FrameNode>& iconNode, ImageSourceInfo& iconSrc,
    std::function<void(WeakPtr<NG::FrameNode>)>& symbol, bool isStart)
{
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto props = iconNode->GetLayoutProperty<TextLayoutProperty>();
    CHECK_NULL_VOID(props);
    auto itemProperty = GetLayoutProperty<MenuItemLayoutProperty>();
    CHECK_NULL_VOID(itemProperty);
    auto selectTheme = pipeline->GetTheme<SelectTheme>();
    CHECK_NULL_VOID(selectTheme);
    if (symbol) {
        // symbol -> symbol
        props->UpdateFontSize(selectTheme->GetEndIconWidth());
        props->UpdateSymbolColorList({ selectTheme->GetMenuIconColor() });
        symbol(AccessibilityManager::WeakClaim(AccessibilityManager::RawPtr(iconNode)));
    } else {
        // symbol -> image
        row->RemoveChild(iconNode);
        iconNode = FrameNode::CreateFrameNode(
            V2::IMAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<ImagePattern>());
        auto iconWidth = isStart ? selectTheme->GetIconSideLength() : selectTheme->GetEndIconWidth();
        auto iconHeight = isStart ? selectTheme->GetIconSideLength() : selectTheme->GetEndIconHeight();
        ImageSourceInfo imageSourceInfo(iconSrc);
        auto props = iconNode->GetLayoutProperty<ImageLayoutProperty>();
        CHECK_NULL_VOID(props);
        props->UpdateImageSourceInfo(imageSourceInfo);
        UpdateIconSrc(iconNode, iconWidth, iconHeight, selectTheme->GetMenuIconColor(), false);
    }
}

void MenuItemPattern::UpdateText(RefPtr<FrameNode>& row, RefPtr<MenuLayoutProperty>& menuProperty, bool isLabel)
{
    auto itemProperty = GetLayoutProperty<MenuItemLayoutProperty>();
    CHECK_NULL_VOID(itemProperty);
    auto content = isLabel ? itemProperty->GetLabel().value_or("") : itemProperty->GetContent().value_or("");
    auto& node = isLabel ? label_ : content_;
    if (content.empty()) {
        (void)row->RemoveChild(node); // it's safe even if node is nullptr
        node = nullptr;
        row->MarkModifyDone();
        row->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
        return;
    }

    if (!node) {
        node = FrameNode::CreateFrameNode(
            V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    }
    auto textProperty = node ? node->GetLayoutProperty<TextLayoutProperty>() : nullptr;
    CHECK_NULL_VOID(textProperty);
    auto renderContext = node->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    renderContext->UpdateClipEdge(false);
    auto context = PipelineBase::GetCurrentContext();
    auto theme = context ? context->GetTheme<SelectTheme>() : nullptr;
    CHECK_NULL_VOID(theme);
    auto layoutDirection = itemProperty->GetNonAutoLayoutDirection();
    TextAlign textAlign = static_cast<TextAlign>(theme->GetMenuItemContentAlign());
    if (layoutDirection == TextDirection::RTL) {
        if (textAlign == TextAlign::LEFT) {
            textAlign = TextAlign::RIGHT;
        } else if (textAlign == TextAlign::RIGHT) {
            textAlign = TextAlign::LEFT;
        } else if (textAlign == TextAlign::START) {
            textAlign = TextAlign::END;
        } else if (textAlign == TextAlign::END) {
            textAlign = TextAlign::START;
        }
        textProperty->UpdateTextAlign(textAlign);
    } else {
        if (AceApplicationInfo::GetInstance().IsRightToLeft()) {
            textProperty->UpdateTextAlign(textAlign);
        }
    }
    UpdateFont(menuProperty, theme, isLabel);
    textProperty->UpdateContent(content);
    UpdateTextOverflow(textProperty, theme);
    node->MountToParent(row, isLabel ? 0 : DEFAULT_NODE_SLOT);
    node->MarkModifyDone();
    node->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
}

void MenuItemPattern::UpdateTextOverflow(RefPtr<TextLayoutProperty>& textProperty,
    RefPtr<SelectTheme>& theme)
{
    if (theme && Container::GreatOrEqualAPIVersion(PlatformVersion::VERSION_THIRTEEN)) {
        if (theme->GetExpandDisplay()) {
            textProperty->UpdateTextOverflow(TextOverflow::ELLIPSIS);
            textProperty->UpdateMaxLines(1);
        } else {
            textProperty->UpdateMaxLines(std::numeric_limits<int32_t>::max());
        }
    } else {
        textProperty->UpdateTextOverflow(TextOverflow::ELLIPSIS);
        textProperty->UpdateMaxLines(1);
    }
    UpdateMaxLinesFromTheme(textProperty);
}

void MenuItemPattern::UpdateFont(RefPtr<MenuLayoutProperty>& menuProperty, RefPtr<SelectTheme>& theme, bool isLabel)
{
    auto itemProperty = GetLayoutProperty<MenuItemLayoutProperty>();
    CHECK_NULL_VOID(itemProperty);
    auto& node = isLabel ? label_ : content_;
    auto textProperty = node ? node->GetLayoutProperty<TextLayoutProperty>() : nullptr;
    CHECK_NULL_VOID(textProperty);

    auto fontSize = isLabel ? itemProperty->GetLabelFontSize() : itemProperty->GetFontSize();
    UpdateFontSize(textProperty, menuProperty, fontSize, theme->GetMenuFontSize());
    auto fontWeight = isLabel ? itemProperty->GetLabelFontWeight() : itemProperty->GetFontWeight();
    UpdateFontWeight(textProperty, menuProperty, fontWeight);
    auto fontStyle = isLabel ? itemProperty->GetLabelItalicFontStyle() : itemProperty->GetItalicFontStyle();
    UpdateFontStyle(textProperty, menuProperty, fontStyle);
    auto fontColor = isLabel ? itemProperty->GetLabelFontColor() : itemProperty->GetFontColor();
    auto menuItemNode = GetHost();
    UpdateFontColor(
        node, menuProperty, fontColor, isLabel ? theme->GetSecondaryFontColor() : theme->GetMenuFontColor());
    if (!isLabel) {
        auto menuItemRenderContext = menuItemNode->GetRenderContext();
        CHECK_NULL_VOID(menuItemRenderContext);
        auto renderContext = node->GetRenderContext();
        CHECK_NULL_VOID(renderContext);
        if (menuItemRenderContext->HasForegroundColor()) {
            textProperty->UpdateTextColor(menuItemRenderContext->GetForegroundColorValue());
            renderContext->UpdateForegroundColor(menuItemRenderContext->GetForegroundColorValue());
        }
    }
    auto fontFamily = isLabel ? itemProperty->GetLabelFontFamily() : itemProperty->GetFontFamily();
    UpdateFontFamily(textProperty, menuProperty, fontFamily);
}

void MenuItemPattern::UpdateMaxLinesFromTheme(RefPtr<TextLayoutProperty>& textProperty)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto pipeline = host->GetContext();
    CHECK_NULL_VOID(pipeline);
    auto menuTheme = pipeline->GetTheme<NG::MenuTheme>();
    CHECK_NULL_VOID(menuTheme);
    auto fontScale = pipeline->GetFontScale();
    if (NearEqual(fontScale, menuTheme->GetBigFontSizeScale()) ||
        NearEqual(fontScale, menuTheme->GetLargeFontSizeScale()) ||
        NearEqual(fontScale, menuTheme->GetMaxFontSizeScale())) {
        textProperty->UpdateMaxLines(menuTheme->GetTextMaxLines());
    }
}

void MenuItemPattern::UpdateTextNodes()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto menuNode = GetMenu();
    CHECK_NULL_VOID(menuNode);
    auto menuProperty = menuNode->GetLayoutProperty<MenuLayoutProperty>();
    RefPtr<FrameNode> leftRow =
        host->GetChildAtIndex(0) ? AceType::DynamicCast<FrameNode>(host->GetChildAtIndex(0)) : nullptr;
    CHECK_NULL_VOID(leftRow);
    UpdateText(leftRow, menuProperty, false);
    RefPtr<FrameNode> rightRow =
        host->GetChildAtIndex(1) ? AceType::DynamicCast<FrameNode>(host->GetChildAtIndex(1)) : nullptr;
    CHECK_NULL_VOID(rightRow);
    UpdateText(rightRow, menuProperty, true);
    if (IsDisabled()) {
        UpdateDisabledStyle();
    }
    host->MarkModifyDone();
    host->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
}

bool MenuItemPattern::IsDisabled()
{
    auto eventHub = GetHost()->GetEventHub<MenuItemEventHub>();
    CHECK_NULL_RETURN(eventHub, true);
    return !eventHub->IsEnabled();
}

void MenuItemPattern::UpdateDisabledStyle()
{
    auto context = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(context);
    auto theme = context->GetTheme<SelectTheme>();
    CHECK_NULL_VOID(theme);
    if (content_) {
        content_->GetRenderContext()->UpdateOpacity(theme->GetDisabledFontColorAlpha());
        content_->MarkModifyDone();
    }
    if (label_) {
        label_->GetRenderContext()->UpdateOpacity(theme->GetDisabledFontColorAlpha());
        label_->MarkModifyDone();
    }
    if (startIcon_) {
        startIcon_->GetRenderContext()->UpdateOpacity(theme->GetDisabledFontColorAlpha());
        startIcon_->MarkModifyDone();
    }
    if (endIcon_) {
        endIcon_->GetRenderContext()->UpdateOpacity(theme->GetDisabledFontColorAlpha());
        endIcon_->MarkModifyDone();
    }
}

void MenuItemPattern::SetAccessibilityAction()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto accessibilityProperty = host->GetAccessibilityProperty<AccessibilityProperty>();
    CHECK_NULL_VOID(accessibilityProperty);
    accessibilityProperty->SetActionSelect([weakPtr = WeakClaim(this)]() {
        const auto& pattern = weakPtr.Upgrade();
        CHECK_NULL_VOID(pattern);
        auto host = pattern->GetHost();
        CHECK_NULL_VOID(host);
        auto hub = host->GetEventHub<MenuItemEventHub>();
        CHECK_NULL_VOID(hub);
        auto onChange = hub->GetOnChange();
        auto selectedChangeEvent = hub->GetSelectedChangeEvent();
        pattern->SetChange();
        if (selectedChangeEvent) {
            selectedChangeEvent(pattern->IsSelected());
        }
        if (onChange) {
            onChange(pattern->IsSelected());
            pattern->RecordChangeEvent();
        }
        auto context = host->GetRenderContext();
        CHECK_NULL_VOID(context);
        pattern->MarkIsSelected(pattern->IsSelected());
        context->OnMouseSelectUpdate(pattern->IsSelected(), ITEM_FILL_COLOR, ITEM_FILL_COLOR);
        if (pattern->GetSubBuilder() != nullptr) {
            pattern->ShowSubMenu(ShowSubMenuType::ACTION);
            return;
        }

        pattern->CloseMenu();
    });
}

void MenuItemPattern::MarkIsSelected(bool isSelected)
{
    if (isSelected_ == isSelected) {
        return;
    }
    isSelected_ = isSelected;
    auto eventHub = GetEventHub<MenuItemEventHub>();
    CHECK_NULL_VOID(eventHub);
    auto onChange = eventHub->GetOnChange();
    auto selectedChangeEvent = eventHub->GetSelectedChangeEvent();
    if (selectedChangeEvent) {
        selectedChangeEvent(isSelected);
    }
    if (onChange) {
        onChange(isSelected);
    }
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    if (isSelected) {
        eventHub->SetCurrentUIState(UI_STATE_SELECTED, isSelected);
        host->OnAccessibilityEvent(AccessibilityEventType::SELECTED);
    } else {
        eventHub->SetCurrentUIState(UI_STATE_SELECTED, isSelected);
        host->OnAccessibilityEvent(AccessibilityEventType::CHANGE);
    }
}

bool MenuItemPattern::IsSelectOverlayMenu()
{
    auto topLevelMenuPattern = GetMenuPattern(true);
    if (!topLevelMenuPattern) {
        return false;
    }
    return topLevelMenuPattern->IsSelectOverlayExtensionMenu() || topLevelMenuPattern->IsSelectOverlayCustomMenu() ||
           topLevelMenuPattern->IsSelectOverlaySubMenu();
}

void MenuItemPattern::ParseMenuRadius(MenuParam& param)
{
    auto menuWrapperNode = GetMenuWrapper();
    CHECK_NULL_VOID(menuWrapperNode);
    auto menuWrapperPattern = menuWrapperNode->GetPattern<MenuWrapperPattern>();
    CHECK_NULL_VOID(menuWrapperPattern);

    if (menuWrapperPattern->GetHasCustomRadius()) {
        auto outterMenuNode = GetMenu(true);
        CHECK_NULL_VOID(outterMenuNode);
        auto menuLayoutProp = outterMenuNode->GetLayoutProperty<MenuLayoutProperty>();
        CHECK_NULL_VOID(menuLayoutProp);
        if (menuLayoutProp->GetBorderRadius().has_value()) {
            BorderRadiusProperty borderRadius = menuLayoutProp->GetBorderRadiusValue();
            param.borderRadius = std::make_optional(borderRadius);
        }
    }
}

bool MenuItemPattern::IsSubMenu()
{
    auto topLevelMenuPattern = GetMenuPattern(true);
    if (!topLevelMenuPattern) {
        return false;
    }
    return topLevelMenuPattern->IsSubMenu();
}

bool MenuItemPattern::IsEmbedded()
{
    auto parentMenuPattern = GetMenuPattern();
    return parentMenuPattern ? parentMenuPattern->IsEmbedded() : false;
}

void MenuItemPattern::ModifyDivider()
{
    auto menu = GetMenu();
    CHECK_NULL_VOID(menu);
    auto menuProperty = menu->GetLayoutProperty<MenuLayoutProperty>();
    CHECK_NULL_VOID(menuProperty);
    auto divider = menuProperty->GetItemDivider();
    if (divider.has_value()) {
        auto host = GetHost();
        CHECK_NULL_VOID(host);
        auto paintProperty = host->GetPaintProperty<MenuItemPaintProperty>();
        CHECK_NULL_VOID(paintProperty);
        paintProperty->UpdateStrokeWidth(divider->strokeWidth);
        paintProperty->UpdateStartMargin(divider->startMargin);
        paintProperty->UpdateEndMargin(divider->endMargin);
        paintProperty->UpdateDividerColor(divider->color);
        host->MarkModifyDone();
        host->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
    }
}

void MenuItemPattern::UpdateNeedDivider(bool need)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto paintProperty = host->GetPaintProperty<MenuItemPaintProperty>();
    CHECK_NULL_VOID(paintProperty);
    paintProperty->UpdateNeedDivider(need);
    if (need) {
        ModifyDivider();
    }
}

float MenuItemPattern::GetDividerStroke()
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, 0.0f);
    auto props = host->GetPaintProperty<MenuItemPaintProperty>();
    CHECK_NULL_RETURN(props, 0.0f);
    return props->GetStrokeWidth().value_or(Dimension(0.0f, DimensionUnit::PX)).ConvertToPx();
}

RefPtr<FrameNode> MenuItemPattern::FindTouchedEmbeddedMenuItem(const OffsetF& position)
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, nullptr);
    if (expandingMode_ != SubMenuExpandingMode::EMBEDDED || !isExpanded_
        || embeddedMenu_ == nullptr || embeddedMenu_->GetTag() != V2::MENU_ETS_TAG) {
        return host;
    }
    CHECK_NULL_RETURN(clickableArea_, host);
    auto clickableAreaOffset = clickableArea_->GetPaintRectOffset();
    auto clickableAreaSize = clickableArea_->GetGeometryNode()->GetFrameSize();
    auto clickableAreaZone = RectF(clickableAreaOffset.GetX(), clickableAreaOffset.GetY(),
        clickableAreaSize.Width(), clickableAreaSize.Height());
    if (clickableAreaZone.IsInRegion(PointF(position.GetX(), position.GetY()))) {
        return host;
    }
    RefPtr<FrameNode> menuItem = nullptr;
    for (const auto& child : embeddedMenu_->GetChildren()) {
        if (child->GetTag() == V2::MENU_ITEM_ETS_TAG) {
            menuItem = AceType::DynamicCast<FrameNode>(child);
        }
        if (menuItem) {
            auto menuItemOffset = menuItem->GetPaintRectOffset();
            auto menuItemSize = menuItem->GetGeometryNode()->GetFrameSize();
            auto menuItemZone = RectF(menuItemOffset.GetX(), menuItemOffset.GetY(),
                menuItemSize.Width(), menuItemSize.Height());
            if (menuItemZone.IsInRegion(PointF(position.GetX(), position.GetY()))) {
                break;
            } else {
                menuItem = nullptr;
            }
        }
    }
    return menuItem;
}
} // namespace OHOS::Ace::NG
