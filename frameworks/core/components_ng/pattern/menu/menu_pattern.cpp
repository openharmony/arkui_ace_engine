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

#include "base/geometry/dimension.h"
#include "base/log/dump_log.h"
#include "base/subwindow/subwindow_manager.h"
#include "core/components/common/layout/grid_system_manager.h"
#include "core/components/common/properties/shadow_config.h"
#include "core/components/container_modal/container_modal_constants.h"
#include "core/components/select/select_theme.h"
#include "core/components/theme/shadow_theme.h"
#include "core/components_ng/base/ui_node.h"
#include "core/components_ng/manager/drag_drop/utils/drag_animation_helper.h"
#include "core/components_ng/pattern/image/image_pattern.h"
#include "core/components_ng/pattern/menu/menu_divider/menu_divider_pattern.h"
#include "core/components_ng/pattern/menu/menu_item/menu_item_layout_property.h"
#include "core/components_ng/pattern/menu/menu_item/menu_item_pattern.h"
#include "core/components_ng/pattern/menu/menu_item_group/menu_item_group_pattern.h"
#include "core/components_ng/pattern/menu/menu_layout_property.h"
#include "core/components_ng/pattern/menu/menu_view.h"
#include "core/components_ng/pattern/menu/multi_menu_layout_algorithm.h"
#include "core/components_ng/pattern/menu/preview/menu_preview_pattern.h"
#include "core/components_ng/pattern/menu/sub_menu_layout_algorithm.h"
#include "core/components_ng/pattern/menu/wrapper/menu_wrapper_pattern.h"
#include "core/components_ng/pattern/scroll/scroll_pattern.h"
#include "core/components_ng/pattern/stack/stack_pattern.h"
#include "core/components_ng/pattern/text/text_layout_property.h"
#include "core/components_ng/property/border_property.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "core/event/touch_event.h"
#include "core/pipeline/pipeline_base.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {
namespace {
constexpr float PAN_MAX_VELOCITY = 2000.0f;
constexpr Dimension MIN_SELECT_MENU_WIDTH = 64.0_vp;
constexpr int32_t COLUMN_NUM = 2;
constexpr int32_t HALF_FOLD_HOVER_DURATION = 1000;
constexpr double MENU_ORIGINAL_SCALE = 0.6f;
constexpr double MAIN_MENU_OPACITY = 0.4f;
constexpr double STACK_MAIN_MENU_DISAPPEAR_DELAY = 150.0f;
constexpr double STACK_MAIN_MENU_APPEAR_DURATION = 150.0f;
constexpr double STACK_SUB_MENU_APPEAR_DELAY = 50.0f;
constexpr double STACK_MENU_APPEAR_DURATION = 400.0f;
constexpr double STACK_MENU_DISAPPEAR_DURATION = 400.0f;
const RefPtr<Curve> CUSTOM_PREVIEW_ANIMATION_CURVE =
    AceType::MakeRefPtr<InterpolatingSpring>(0.0f, 1.0f, 380.0f, 34.0f);
const RefPtr<InterpolatingSpring> MAIN_MENU_ANIMATION_CURVE =
    AceType::MakeRefPtr<InterpolatingSpring>(0.0f, 1.0f, 528.0f, 35.0f);
const RefPtr<InterpolatingSpring> STACK_SUB_MENU_ANIMATION_CURVE =
    AceType::MakeRefPtr<InterpolatingSpring>(0.0f, 1.0f, 228.0f, 26.0f);
const float MINIMUM_AMPLITUDE_RATION = 0.08f;

constexpr double MOUNT_MENU_FINAL_SCALE = 0.95f;
constexpr double SEMI_CIRCLE_ANGEL = 90.0f;
constexpr Dimension PADDING = 4.0_vp;
constexpr double HALF = 2.0;
constexpr Dimension OPTION_MARGIN = 8.0_vp;

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

void ShowMenuOpacityAnimation(const RefPtr<MenuTheme>& menuTheme, const RefPtr<RenderContext>& renderContext,
    int32_t delay)
{
    CHECK_NULL_VOID(menuTheme);
    CHECK_NULL_VOID(renderContext);

    renderContext->UpdateOpacity(0.0);
    AnimationOption option = AnimationOption();
    option.SetCurve(Curves::FRICTION);
    option.SetDuration(menuTheme->GetContextMenuAppearDuration());
    option.SetDelay(delay);
    AnimationUtils::Animate(option, [renderContext]() {
        if (renderContext) {
            renderContext->UpdateOpacity(1.0);
        }
    });
}
} // namespace

void MenuPattern::OnAttachToFrameNode()
{
    RegisterOnTouch();
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    MenuView::RegisterAccessibilityChildActionNotify(host);
    auto focusHub = host->GetOrCreateFocusHub();
    CHECK_NULL_VOID(focusHub);
    RegisterOnKeyEvent(focusHub);
    DisableTabInMenu();
    InitTheme(host);
    auto pipelineContext = host->GetContextWithCheck();
    CHECK_NULL_VOID(pipelineContext);
    auto targetNode = FrameNode::GetFrameNode(targetTag_, targetId_);
    CHECK_NULL_VOID(targetNode);
    auto eventHub = targetNode->GetOrCreateEventHub<EventHub>();
    CHECK_NULL_VOID(eventHub);
    halfFoldHoverCallbackId_ = RegisterHalfFoldHover(targetNode);
    OnAreaChangedFunc onAreaChangedFunc = [menuNodeWk = WeakPtr<FrameNode>(host)](const RectF& /* oldRect */,
                                              const OffsetF& /* oldOrigin */, const RectF& /* rect */,
                                              const OffsetF& /* origin */) {
        auto menuNode = menuNodeWk.Upgrade();
        CHECK_NULL_VOID(menuNode);
        auto menuPattern = menuNode->GetPattern<MenuPattern>();
        CHECK_NULL_VOID(menuPattern);
        auto menuWarpper = menuPattern->GetMenuWrapper();
        CHECK_NULL_VOID(menuWarpper);
        auto warpperPattern = menuWarpper->GetPattern<MenuWrapperPattern>();
        CHECK_NULL_VOID(warpperPattern);
        auto isMenuHide = warpperPattern->IsHide();
        TAG_LOGI(AceLogTag::ACE_MENU, "the area of target node is changed, isMenuHide: %{public}d", isMenuHide);
        if (!isMenuHide) {
            menuNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
        }
    };
    eventHub->AddInnerOnAreaChangedCallback(host->GetId(), std::move(onAreaChangedFunc));

    auto foldStatusChangeCallback = [weak = WeakClaim(this)](FoldStatus foldStatus) {
        TAG_LOGI(AceLogTag::ACE_MENU, "foldStatus is changed: %{public}d", foldStatus);
        auto menuPattern = weak.Upgrade();
        CHECK_NULL_VOID(menuPattern);
        auto menuWrapper = menuPattern->GetMenuWrapper();
        CHECK_NULL_VOID(menuWrapper);
        auto wrapperPattern = menuWrapper->GetPattern<MenuWrapperPattern>();
        CHECK_NULL_VOID(wrapperPattern);
        wrapperPattern->SetHasFoldModeChangedTransition(true);
        SubwindowManager::GetInstance()->HideMenuNG(false);
    };
    foldStatusChangedCallbackId_ =
        pipelineContext->RegisterFoldStatusChangedCallback(std::move(foldStatusChangeCallback));
}

int32_t MenuPattern::RegisterHalfFoldHover(const RefPtr<FrameNode>& menuNode)
{
    // register when hoverMode enabled
    auto pipelineContext = menuNode->GetContext();
    CHECK_NULL_RETURN(pipelineContext, 0);
    int32_t callbackId = pipelineContext->RegisterHalfFoldHoverChangedCallback(
        [weak = WeakClaim(this), pipelineContext](bool isHalfFoldHover) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        auto host = pattern->GetHost();
        CHECK_NULL_VOID(host);
        AnimationOption optionPosition;
        auto motion = AceType::MakeRefPtr<ResponsiveSpringMotion>(0.35f, 1.0f, 0.0f);
        optionPosition.SetDuration(HALF_FOLD_HOVER_DURATION);
        optionPosition.SetCurve(motion);
        auto menuWrapperNode = pattern->GetMenuWrapper();
        CHECK_NULL_VOID(menuWrapperNode);
        auto menuWrapperPattern = menuWrapperNode->GetPattern<MenuWrapperPattern>();
        CHECK_NULL_VOID(menuWrapperPattern);
        if (menuWrapperPattern->GetHoverMode().value_or(false) && pattern->IsSubMenu()) {
            menuWrapperPattern->HideSubMenu();
        }
        pipelineContext->FlushUITasks();
        pipelineContext->Animate(optionPosition, motion, [host, pipelineContext]() {
            host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
            pipelineContext->FlushUITasks();
        });
    });
    return callbackId;
}

void MenuPattern::OnDetachFromFrameNode(FrameNode* frameNode)
{
    CHECK_NULL_VOID(frameNode);
    auto targetNode = FrameNode::GetFrameNode(targetTag_, targetId_);
    CHECK_NULL_VOID(targetNode);
    auto eventHub = targetNode->GetOrCreateEventHub<EventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->RemoveInnerOnAreaChangedCallback(frameNode->GetId());

    if (foldStatusChangedCallbackId_.has_value()) {
        auto pipeline = frameNode->GetContext();
        CHECK_NULL_VOID(pipeline);
        pipeline->UnRegisterFoldStatusChangedCallback(foldStatusChangedCallbackId_.value_or(-1));
    }
}

void MenuPattern::OnModifyDone()
{
    Pattern::OnModifyDone();
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    isNeedDivider_ = false;
    auto uiNode = AceType::DynamicCast<UINode>(host);
    RefPtr<UINode> previousNode = nullptr;
    UpdateMenuItemChildren(uiNode, previousNode);
    RemoveLastNodeDivider(previousNode);
    ResetThemeByInnerMenuCount();
    auto menuWrapperNode = GetMenuWrapper();
    CHECK_NULL_VOID(menuWrapperNode);
    auto menuWrapperPattern = menuWrapperNode->GetPattern<MenuWrapperPattern>();
    CHECK_NULL_VOID(menuWrapperPattern);
    if (!menuWrapperPattern->GetHasCustomRadius()) {
        auto menuFirstNode = GetFirstInnerMenu();
        if (menuFirstNode) {
            CopyMenuAttr(menuFirstNode);
        }
    }

    auto menuLayoutProperty = GetLayoutProperty<MenuLayoutProperty>();
    CHECK_NULL_VOID(menuLayoutProperty);
    if (menuLayoutProperty->GetBorderRadius().has_value()) {
        BorderRadiusProperty borderRadius = menuLayoutProperty->GetBorderRadiusValue();
        UpdateBorderRadius(host, borderRadius);
    }
    auto pipelineContext = host->GetContextRefPtr();
    CHECK_NULL_VOID(pipelineContext);
    auto selecTheme = pipelineContext->GetTheme<SelectTheme>();
    CHECK_NULL_VOID(selecTheme);
    if (selecTheme->GetMenuItemNeedFocus()) {
        UpdateMenuBorderAndBackgroundBlur();
    }
    SetAccessibilityAction();

    if (previewMode_ != MenuPreviewMode::NONE) {
        auto node = host->GetChildren().front();
        CHECK_NULL_VOID(node);
        auto scroll = AceType::DynamicCast<FrameNode>(node);
        CHECK_NULL_VOID(scroll);
        auto hub = scroll->GetOrCreateEventHub<EventHub>();
        CHECK_NULL_VOID(hub);
        auto gestureHub = hub->GetOrCreateGestureEventHub();
        CHECK_NULL_VOID(gestureHub);
        InitPanEvent(gestureHub);
    }
}

void MenuPattern::UpdateMenuBorderAndBackgroundBlur()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto renderContext = host->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    auto context = host->GetContext();
    CHECK_NULL_VOID(context);
    auto theme = context->GetTheme<SelectTheme>();
    CHECK_NULL_VOID(theme);
    if (!renderContext->HasBorderColor()) {
        BorderColorProperty borderColor;
        borderColor.SetColor(theme->GetMenuNormalBorderColor());
        renderContext->UpdateBorderColor(borderColor);
    }
    if (!renderContext->HasBorderWidth()) {
        auto menuLayoutProperty = GetLayoutProperty<MenuLayoutProperty>();
        auto menuBorderWidth = theme->GetMenuNormalBorderWidth();
        BorderWidthProperty borderWidth;
        borderWidth.SetBorderWidth(menuBorderWidth);
        menuLayoutProperty->UpdateBorderWidth(borderWidth);
        renderContext->UpdateBorderWidth(borderWidth);
        auto scroll = DynamicCast<FrameNode>(host->GetFirstChild());
        CHECK_NULL_VOID(scroll);
        auto scrollRenderContext = scroll->GetRenderContext();
        CHECK_NULL_VOID(scrollRenderContext);
        scrollRenderContext->UpdateOffset(OffsetT<Dimension>(menuBorderWidth, menuBorderWidth));
    }
}

void MenuPattern::ResetThemeByInnerMenuCount()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto innerMenuCount = GetInnerMenuCount();
    if (innerMenuCount == 1) {
        ResetTheme(host, false);
    } else if (innerMenuCount > 1) {
        // multiple inner menus, reset outer container's shadow for desktop UX
        ResetTheme(host, true);
    }
}

void MenuPattern::UpdateMenuItemDivider()
{
    if (!isSelectMenu_) {
        return;
    }
    if (options_.empty()) {
        return;
    }
    auto property = GetLayoutProperty<MenuLayoutProperty>();
    CHECK_NULL_VOID(property);
    auto dividerMode = property->GetItemDividerModeValue(DividerMode::FLOATING_ABOVE_MENU);
    RefPtr<FrameNode> previousNode = nullptr;
    RefPtr<FrameNode> lastNode = options_.back();
    for (auto&& option : options_) {
        CHECK_NULL_VOID(option);
        auto props = option->GetPaintProperty<MenuItemPaintProperty>();
        CHECK_NULL_VOID(props);
        auto optionPattern = option->GetPattern<MenuItemPattern>();
        CHECK_NULL_VOID(optionPattern);
        auto frameNode = optionPattern->GetBottomDivider();
        if (!frameNode) {
            continue;
        }
        if (previousNode) {
            auto previousPattern = previousNode->GetPattern<MenuItemPattern>();
            CHECK_NULL_VOID(previousPattern);
            auto previousBottomDivider = previousPattern->GetBottomDivider();
            if (previousBottomDivider) {
                optionPattern->SetTopDivider(previousBottomDivider);
            }
        }
        if (dividerMode == DividerMode::FLOATING_ABOVE_MENU || lastNode == option) {
            optionPattern->RemoveBottomDivider();
        } else {
            optionPattern->AttachBottomDivider();
        }
        auto dividerProperty = frameNode->GetPaintProperty<MenuDividerPaintProperty>();
        CHECK_NULL_VOID(dividerProperty);
        dividerProperty->UpdateHasIcon(props->GetHasIconValue(false));
        previousNode = option;
    }
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
}

RefPtr<FrameNode> CreateMenuScroll(const RefPtr<UINode>& node)
{
    auto scroll = FrameNode::CreateFrameNode(
        V2::SCROLL_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<ScrollPattern>());
    CHECK_NULL_RETURN(scroll, nullptr);
    auto props = scroll->GetLayoutProperty<ScrollLayoutProperty>();
    props->UpdateAxis(Axis::VERTICAL);
    props->UpdateAlignment(Alignment::CENTER_LEFT);
    auto pipeline = scroll->GetContext();
    CHECK_NULL_RETURN(pipeline, nullptr);
    auto theme = pipeline->GetTheme<SelectTheme>();
    CHECK_NULL_RETURN(theme, nullptr);
    auto contentPadding = static_cast<float>(theme->GetMenuPadding().ConvertToPx());
    PaddingProperty padding;
    padding.left = padding.right = padding.top = padding.bottom = CalcLength(contentPadding);
    props->UpdatePadding(padding);
    if (node) {
        node->MountToParent(scroll);
    }
    auto renderContext = scroll->GetRenderContext();
    CHECK_NULL_RETURN(renderContext, nullptr);
    BorderRadiusProperty borderRadius;
    if (Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_TWELVE)) {
        borderRadius.SetRadius(theme->GetMenuDefaultRadius());
    } else {
        borderRadius.SetRadius(theme->GetMenuBorderRadius());
    }
    renderContext->UpdateBorderRadius(borderRadius);
    return scroll;
}

void MenuPattern::FireBuilder()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    host->RemoveChild(builderNode_.Upgrade());
    if (!makeFunc_.has_value()) {
        return;
    }
    auto column = FrameNode::CreateFrameNode(V2::COLUMN_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<LinearLayoutPattern>(true));
    auto scroll = CreateMenuScroll(column);
    CHECK_NULL_VOID(scroll);
    builderNode_ = scroll;
    for (size_t i = 0; i < selectProperties_.size(); i++) {
        auto contentModifierNode = BuildContentModifierNode(i);
        if (contentModifierNode) {
            contentModifierNode->MarkModifyDone();
            contentModifierNode->MountToParent(column);
        }
    }
    auto scrollPattern = scroll->GetPattern<ScrollPattern>();
    CHECK_NULL_VOID(scrollPattern);
    scrollPattern->SetIsSelectScroll(true);
    scroll->MountToParent(host);
    scroll->MarkModifyDone();
    host->MarkModifyDone();
    SetIsSelectMenu(true);
}

RefPtr<FrameNode> MenuPattern::BuildContentModifierNode(int index)
{
    if (!makeFunc_.has_value()) {
        return nullptr;
    }
    auto property = selectProperties_[index];
    MenuItemConfiguration menuItemConfiguration(property.value, property.icon, property.symbolModifier,
        index, property.selected, property.selectEnable);
    return (makeFunc_.value())(menuItemConfiguration);
}

void MenuPattern::UpdateSelectIndex(int32_t index)
{
    for (size_t i = 0; i < selectParams_.size(); i++) {
        selectProperties_[i].selected = index == static_cast<int32_t>(i);
    }
    FireBuilder();
}

void InnerMenuPattern::BeforeCreateLayoutWrapper()
{
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
    ResetNeedDivider();
    auto uiNode = AceType::DynamicCast<UINode>(host);
    RefPtr<UINode> previousNode = nullptr;
    UpdateMenuItemChildren(uiNode, previousNode);
    RemoveLastNodeDivider(previousNode);
    SetAccessibilityAction();
    auto pipelineContext = host->GetContextRefPtr();
    CHECK_NULL_VOID(pipelineContext);
    auto selecTheme = pipelineContext->GetTheme<SelectTheme>();
    CHECK_NULL_VOID(selecTheme);
    if (selecTheme->GetMenuItemNeedFocus()) {
        InitDefaultBorder(host);
    }
}

void InnerMenuPattern::InitDefaultBorder(const RefPtr<FrameNode>& host)
{
    CHECK_NULL_VOID(host);
    auto context = host->GetContextRefPtr();
    CHECK_NULL_VOID(context);
    auto menuTheme = context->GetTheme<NG::MenuTheme>();
    CHECK_NULL_VOID(menuTheme);
    auto renderContext = host->GetRenderContext();
    CHECK_NULL_VOID(renderContext);

    if (!renderContext->HasBorderColor()) {
        BorderColorProperty borderColorProperty;
        borderColorProperty.SetColor(menuTheme->GetBorderColor());
        renderContext->UpdateBorderColor(borderColorProperty);
    }

    if (!renderContext->HasBorderWidth()) {
        auto layoutProperty = host->GetLayoutProperty<MenuLayoutProperty>();
        BorderWidthProperty widthProp;
        widthProp.SetBorderWidth(menuTheme->GetBorderWidth());
        layoutProperty->UpdateBorderWidth(widthProp);
        renderContext->UpdateBorderWidth(widthProp);
    }
}

void MenuPattern::RemoveLastNodeDivider(const RefPtr<UINode>& lastNode)
{
    CHECK_NULL_VOID(lastNode);
    auto lastFrameNode = AceType::DynamicCast<FrameNode>(lastNode);
    CHECK_NULL_VOID(lastFrameNode);
    auto lastPattern = lastFrameNode->GetPattern<MenuItemPattern>();
    CHECK_NULL_VOID(lastPattern);
    lastPattern->RemoveBottomDivider();
}

// close menu on touch up
void MenuPattern::RegisterOnTouch()
{
    CHECK_NULL_VOID(!onTouch_);
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto gesture = host->GetOrCreateGestureEventHub();
    CHECK_NULL_VOID(gesture);
    auto touchTask = [weak = WeakClaim(this)](const TouchEventInfo& info) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        pattern->OnTouchEvent(info);
    };
    onTouch_ = MakeRefPtr<TouchEventImpl>(std::move(touchTask));
    gesture->AddTouchEvent(onTouch_);
}

void MenuPattern::OnTouchEvent(const TouchEventInfo& info)
{
    if (GetInnerMenuCount() > 0 || IsMultiMenu() || IsDesktopMenu()|| IsSelectOverlayCustomMenu()) {
        // not click hide menu for multi menu or select overlay custom menu
        return;
    }
    if (!options_.empty()) {
        // not click hide menu for select and bindMenu default option
        return;
    }
    if (!needHideAfterTouch_) {
        // not click hide menu if needn't hide after touch
        return;
    }
    if (info.GetTouches().empty()) {
        return;
    }
    auto touchType = info.GetTouches().front().GetTouchType();
    if (touchType == TouchType::DOWN) {
        lastTouchOffset_ = info.GetTouches().front().GetLocalLocation();
    } else if (touchType == TouchType::UP) {
        auto touchUpOffset = info.GetTouches().front().GetLocalLocation();
        if (lastTouchOffset_.has_value() &&
            (touchUpOffset - lastTouchOffset_.value()).GetDistance() <= DEFAULT_CLICK_DISTANCE) {
            auto touchGlobalLocation = info.GetTouches().front().GetGlobalLocation();
            auto position = OffsetF(static_cast<float>(touchGlobalLocation.GetX()),
                static_cast<float>(touchGlobalLocation.GetY()));
            TAG_LOGI(AceLogTag::ACE_MENU, "will hide menu, position is %{public}s.", position.ToString().c_str());
            HideMenu(true, position, HideMenuType::MENU_TOUCH_UP);
        }
        lastTouchOffset_.reset();
    }
}

void MenuPattern::RegisterOnKeyEvent(const RefPtr<FocusHub>& focusHub)
{
    auto onKeyEvent = [wp = WeakClaim(this)](const KeyEvent& event) -> bool {
        auto pattern = wp.Upgrade();
        CHECK_NULL_RETURN(pattern, false);
        return pattern->OnKeyEvent(event);
    };
    focusHub->SetOnKeyEventInternal(std::move(onKeyEvent));
}

bool MenuPattern::OnKeyEvent(const KeyEvent& event)
{
    if (event.action != KeyAction::DOWN || IsMultiMenu() || IsDesktopMenu()) {
        return false;
    }
    if ((event.code == KeyCode::KEY_DPAD_LEFT || event.code == KeyCode::KEY_ESCAPE) &&
        (IsSubMenu() || IsSelectOverlaySubMenu())) {
        auto menuWrapper = GetMenuWrapper();
        CHECK_NULL_RETURN(menuWrapper, true);
        auto wrapperPattern = menuWrapper->GetPattern<MenuWrapperPattern>();
        CHECK_NULL_RETURN(wrapperPattern, true);
        RemoveParentHoverStyle();
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
    menuItemPattern->OnHover(false);
}

void MenuPattern::UpdateMenuItemChildren(const RefPtr<UINode>& host, RefPtr<UINode>& previousNode)
{
    CHECK_NULL_VOID(host);
    auto layoutProperty = GetLayoutProperty<MenuLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    const auto& children = host->GetChildren();
    int32_t index = 0;
    for (auto child : children) {
        auto tag = child->GetTag();
        if (tag == V2::MENU_ITEM_ETS_TAG) {
            auto itemNode = AceType::DynamicCast<FrameNode>(child);
            CHECK_NULL_VOID(itemNode);
            auto itemProperty = itemNode->GetLayoutProperty<MenuItemLayoutProperty>();
            CHECK_NULL_VOID(itemProperty);
            auto itemPattern = itemNode->GetPattern<MenuItemPattern>();
            CHECK_NULL_VOID(itemPattern);
            auto expandingMode = layoutProperty->GetExpandingMode().value_or(SubMenuExpandingMode::SIDE);
            if (expandingMode != itemPattern->GetExpandingMode() || IsEmbedded()) {
                auto expandNode = itemPattern->GetHost();
                CHECK_NULL_VOID(expandNode);
                expandNode->MarkModifyDone();
                expandNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
            }
            UpdateMenuItemTextNode(layoutProperty, itemProperty, itemPattern);
            UpdateMenuDividerWithMode(previousNode, child, layoutProperty, index);
            itemPattern->UpdateNeedDivider(isNeedDivider_);
            isNeedDivider_ = true;
            itemPattern->SetIndex(index);
            previousNode = child;
        } else if (tag == V2::MENU_ITEM_GROUP_ETS_TAG) {
            auto childItemNode = AceType::DynamicCast<FrameNode>(child);
            CHECK_NULL_VOID(childItemNode);
            auto pattern = childItemNode->GetPattern<MenuItemGroupPattern>();
            CHECK_NULL_VOID(pattern);
            pattern->ModifyDivider();
            isNeedDivider_ = false;
            AddGroupHeaderDivider(previousNode, child, layoutProperty, index);
            UpdateMenuItemChildren(child, previousNode);
            AddGroupFooterDivider(previousNode, child, layoutProperty, index);
            isNeedDivider_ = false;
            auto accessibilityProperty =
                childItemNode->GetAccessibilityProperty<AccessibilityProperty>();
            CHECK_NULL_VOID(accessibilityProperty);
            accessibilityProperty->SetAccessibilityLevel(AccessibilityProperty::Level::NO_STR);
        } else if (tag == V2::JS_FOR_EACH_ETS_TAG || tag == V2::JS_SYNTAX_ITEM_ETS_TAG
            ||  tag == V2::JS_IF_ELSE_ETS_TAG || tag == V2::JS_REPEAT_ETS_TAG) {
            UpdateMenuItemChildren(child, previousNode);
        }
        index++;
    }
}

void MenuPattern::UpdateMenuDividerWithMode(const RefPtr<UINode>& previousNode, const RefPtr<UINode>& currentNode,
    const RefPtr<MenuLayoutProperty>& property, int32_t& index)
{
    CHECK_NULL_VOID(previousNode);
    CHECK_NULL_VOID(currentNode);
    CHECK_NULL_VOID(property);
    auto currentFrameNode = AceType::DynamicCast<FrameNode>(currentNode);
    CHECK_NULL_VOID(currentFrameNode);
    auto currentPattern = currentFrameNode->GetPattern<MenuItemPattern>();
    CHECK_NULL_VOID(currentPattern);
    auto previousFrameNode = AceType::DynamicCast<FrameNode>(previousNode);
    CHECK_NULL_VOID(previousFrameNode);
    auto itemDividerMode = isNeedDivider_ ? property->GetItemDividerModeValue(DividerMode::FLOATING_ABOVE_MENU)
                                          : property->GetItemGroupDividerModeValue(DividerMode::FLOATING_ABOVE_MENU);
    if (previousFrameNode->GetTag() == V2::MENU_ITEM_GROUP_ETS_TAG) {
        auto previousPattern = previousFrameNode->GetPattern<MenuItemGroupPattern>();
        CHECK_NULL_VOID(previousPattern);
        UpdateDividerProperty(previousPattern->GetBottomDivider(),
            isNeedDivider_ ? property->GetItemDivider() : property->GetItemGroupDivider());
        if (itemDividerMode == DividerMode::FLOATING_ABOVE_MENU) {
            previousPattern->RemoveBottomDivider();
        } else {
            previousPattern->AttachBottomDivider();
            index++;
        }
        currentPattern->SetTopDivider(previousPattern->GetBottomDivider());
    } else {
        auto previousPattern = previousFrameNode->GetPattern<MenuItemPattern>();
        CHECK_NULL_VOID(previousPattern);
        UpdateDividerProperty(previousPattern->GetBottomDivider(),
            isNeedDivider_ ? property->GetItemDivider() : property->GetItemGroupDivider());
        if (itemDividerMode == DividerMode::FLOATING_ABOVE_MENU) {
            previousPattern->RemoveBottomDivider();
        } else {
            previousPattern->AttachBottomDivider();
            index++;
        }
        currentPattern->SetTopDivider(previousPattern->GetBottomDivider());
    }
}

void MenuPattern::AddGroupHeaderDivider(RefPtr<UINode>& previousNode, const RefPtr<UINode>& currentNode,
    const RefPtr<MenuLayoutProperty>& property, int32_t& index)
{
    auto groupNode = AceType::DynamicCast<FrameNode>(currentNode);
    CHECK_NULL_VOID(groupNode);
    auto groupPattern = groupNode->GetPattern<MenuItemGroupPattern>();
    CHECK_NULL_VOID(groupPattern && groupPattern->GetHeader());
    auto itemDividerMode = property->GetItemGroupDividerModeValue(DividerMode::FLOATING_ABOVE_MENU);
    auto previousFrameNode = AceType::DynamicCast<FrameNode>(previousNode);
    CHECK_NULL_VOID(previousFrameNode);
    if (previousFrameNode->GetTag() == V2::MENU_ITEM_GROUP_ETS_TAG) {
        auto previousPattern = previousFrameNode->GetPattern<MenuItemGroupPattern>();
        CHECK_NULL_VOID(previousPattern);
        UpdateDividerProperty(previousPattern->GetBottomDivider(), property->GetItemGroupDivider());
        if (itemDividerMode == DividerMode::FLOATING_ABOVE_MENU) {
            previousPattern->RemoveBottomDivider();
        } else {
            previousPattern->AttachBottomDivider();
            index++;
        }
    } else {
        auto previousPattern = previousFrameNode->GetPattern<MenuItemPattern>();
        CHECK_NULL_VOID(previousPattern);
        UpdateDividerProperty(previousPattern->GetBottomDivider(), property->GetItemGroupDivider());
        if (itemDividerMode == DividerMode::FLOATING_ABOVE_MENU) {
            previousPattern->RemoveBottomDivider();
        } else {
            previousPattern->AttachBottomDivider();
            index++;
        }
    }
    // If the child of the group contains only the header.
    if (groupNode->GetChildren().size() == 1) {
        previousNode = currentNode;
    } else {
        previousNode = nullptr;
    }
}

void MenuPattern::AddGroupFooterDivider(RefPtr<UINode>& previousNode, const RefPtr<UINode>& currentNode,
    const RefPtr<MenuLayoutProperty>& property, int32_t& index)
{
    auto groupNode = AceType::DynamicCast<FrameNode>(currentNode);
    CHECK_NULL_VOID(groupNode);
    auto groupPattern = groupNode->GetPattern<MenuItemGroupPattern>();
    CHECK_NULL_VOID(groupPattern && groupPattern->GetFooter());
    auto parent = groupNode->GetParent();
    CHECK_NULL_VOID(parent);
    auto itemDividerMode = property->GetItemGroupDividerModeValue(DividerMode::FLOATING_ABOVE_MENU);
    // If the child of the group contains only the footer.
    if (groupNode->GetChildren().size() == 1 && previousNode) {
        if (previousNode->GetTag() == V2::MENU_ITEM_GROUP_ETS_TAG) {
            auto previousFrameNode = AceType::DynamicCast<FrameNode>(previousNode);
            CHECK_NULL_VOID(previousFrameNode);
            auto previousPattern = previousFrameNode->GetPattern<MenuItemGroupPattern>();
            CHECK_NULL_VOID(previousPattern);
            UpdateDividerProperty(previousPattern->GetBottomDivider(), property->GetItemGroupDivider());
            if (itemDividerMode == DividerMode::FLOATING_ABOVE_MENU) {
                previousPattern->RemoveBottomDivider();
            } else {
                previousPattern->AttachBottomDivider();
                index++;
            }
        } else {
            auto previousFrameNode = AceType::DynamicCast<FrameNode>(previousNode);
            CHECK_NULL_VOID(previousFrameNode);
            auto previousPattern = previousFrameNode->GetPattern<MenuItemPattern>();
            CHECK_NULL_VOID(previousPattern);
            UpdateDividerProperty(previousPattern->GetBottomDivider(), property->GetItemGroupDivider());
            if (itemDividerMode == DividerMode::FLOATING_ABOVE_MENU) {
                previousPattern->RemoveBottomDivider();
            } else {
                previousPattern->AttachBottomDivider();
                index++;
            }
        }
    }
    // When the group is not the last item of the menu.
    if (parent->GetChildIndex(groupNode) < static_cast<int32_t>(parent->GetChildren().size()) - 1) {
        UpdateDividerProperty(groupPattern->GetBottomDivider(), property->GetItemGroupDivider());
        if (itemDividerMode == DividerMode::FLOATING_ABOVE_MENU) {
            groupPattern->RemoveBottomDivider();
        } else {
            groupPattern->AttachBottomDivider();
            index++;
        }
        previousNode = currentNode;
    } else {
        previousNode = nullptr;
    }
}

void MenuPattern::UpdateDividerProperty(
    const RefPtr<FrameNode>& dividerNode, const std::optional<V2::ItemDivider>& divider)
{
    CHECK_NULL_VOID(dividerNode);
    auto paintProperty = dividerNode->GetPaintProperty<MenuDividerPaintProperty>();
    CHECK_NULL_VOID(paintProperty);
    if (!divider.has_value()) {
        paintProperty->ResetStrokeWidth();
        paintProperty->ResetDividerColor();
        paintProperty->ResetStartMargin();
        paintProperty->ResetEndMargin();
    } else {
        auto value = divider.value();
        paintProperty->UpdateStrokeWidth(value.strokeWidth);
        paintProperty->UpdateDividerColor(value.color);
        paintProperty->UpdateStartMargin(value.startMargin);
        paintProperty->UpdateEndMargin(value.endMargin);
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
            auto props = childNode->GetPaintProperty<MenuItemPaintProperty>();
            CHECK_NULL_VOID(props);
            props->UpdateNeedDivider(false);
            auto focusHub = childNode->GetOrCreateFocusHub();
            CHECK_NULL_VOID(focusHub);
            focusHub->SetIsDefaultFocus(true);
        }
        auto optionPattern = childNode->GetPattern<MenuItemPattern>();
        CHECK_NULL_VOID(optionPattern);
        optionPattern->UpdateText(params.at(i).text);
        optionPattern->UpdateIcon(params.at(i).icon, params.at(i).symbolIcon);
        childNode->MarkModifyDone();
        childNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    }
    for (size_t i = updateCount; i < paramCount; i++) {
        auto optionNode = MenuView::CreateSelectOption(params.at(i), i);
        auto optionPattern = optionNode->GetPattern<MenuItemPattern>();
        CHECK_NULL_VOID(optionPattern);
        optionPattern->SetIsSelectOption(true);
        if (i == 0) {
            auto props = optionNode->GetPaintProperty<MenuItemPaintProperty>();
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

void MenuPattern::UpdateSelectOptionTextByIndex(int32_t index, const std::string& text)
{
    if (!isSelectMenu_) {
        return;
    }
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    const auto& children = GetOptions();
    if (index >= static_cast<int32_t>(children.size())) {
        return;
    }
    auto childIt = children.at(index);
    const auto& childNode = AceType::DynamicCast<FrameNode>(childIt);
    CHECK_NULL_VOID(childNode);
    auto optionPattern = childNode->GetPattern<MenuItemPattern>();
    CHECK_NULL_VOID(optionPattern);
    optionPattern->UpdateText(text);
    childNode->MarkModifyDone();
    childNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    host->MarkModifyDone();
    host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
}

void MenuPattern::UpdateSelectOptionIconByIndex(int32_t index, const std::string& icon)
{
    if (!isSelectMenu_) {
        return;
    }
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    const auto& children = GetOptions();
    if (index >= static_cast<int32_t>(children.size())) {
        return;
    }
    auto childIt = children.at(index);
    const auto& childNode = AceType::DynamicCast<FrameNode>(childIt);
    CHECK_NULL_VOID(childNode);
    auto optionPattern = childNode->GetPattern<MenuItemPattern>();
    CHECK_NULL_VOID(optionPattern);
    optionPattern->UpdateIcon(icon, nullptr);
    childNode->MarkModifyDone();
    childNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    host->MarkModifyDone();
    host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
}

void MenuPattern::HideMenu(bool isMenuOnTouch, OffsetF position, const HideMenuType& reason) const
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto pipeline = host->GetContextWithCheck();
    CHECK_NULL_VOID(pipeline);
    auto theme = pipeline->GetTheme<SelectTheme>();
    CHECK_NULL_VOID(theme);
    auto expandDisplay = theme->GetExpandDisplay();
    auto rootMenuPattern = AceType::DynamicCast<MenuPattern>(host->GetPattern());
    CHECK_NULL_VOID(rootMenuPattern);
    // copy menu pattern properties to rootMenu
    auto layoutProperty = rootMenuPattern->GetLayoutProperty<MenuLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    bool isShowInSubWindow = layoutProperty->GetShowInSubWindowValue(true);
    auto wrapper = GetMenuWrapper();
    CHECK_NULL_VOID(wrapper);
    if (wrapper->GetTag() == V2::SELECT_OVERLAY_ETS_TAG) {
        return;
    }
    if (((IsContextMenu() || (expandDisplay && isShowInSubWindow))) && (targetTag_ != V2::SELECT_ETS_TAG)) {
        TAG_LOGI(AceLogTag::ACE_MENU, "will hide menu, tagetNode id %{public}d. reason %{public}d", targetId_, reason);
        SubwindowManager::GetInstance()->HideMenuNG(wrapper, targetId_);
        return;
    }
    if (targetTag_ == V2::SELECT_ETS_TAG && expandDisplay && layoutProperty->GetShowInSubWindowValue(false)) {
        auto subWindowManager = SubwindowManager::GetInstance();
        CHECK_NULL_VOID(subWindowManager);
        auto containerId = Container::CurrentId();
        auto subwindow = subWindowManager->GetSubwindowByType(containerId, SubwindowType::TYPE_MENU);
        if (subWindowManager->IsSubwindowExist(subwindow)) {
            subWindowManager->ClearMenuNG(containerId, targetId_);
            return;
        }
    }

    if (HideStackExpandMenu(position)) {
        return;
    }

    auto overlayManager = pipeline->GetOverlayManager();
    CHECK_NULL_VOID(overlayManager);
    TAG_LOGI(AceLogTag::ACE_MENU, "will hide menu, tagetNode id %{public}d.", targetId_);
    overlayManager->HideMenu(wrapper, targetId_, isMenuOnTouch, reason);
    overlayManager->EraseMenuInfo(targetId_);
}

bool MenuPattern::HideStackExpandMenu(const OffsetF& position) const
{
    auto wrapper = GetMenuWrapper();
    CHECK_NULL_RETURN(wrapper, false);
    auto outterMenu = wrapper->GetFirstChild();
    CHECK_NULL_RETURN(outterMenu, false);
    auto menuWrapperPattern = wrapper->GetPattern<MenuWrapperPattern>();
    CHECK_NULL_RETURN(menuWrapperPattern, false);
    auto innerMenu = menuWrapperPattern->GetMenuChild(outterMenu);
    CHECK_NULL_RETURN(innerMenu, false);
    auto innerMenuPattern = AceType::DynamicCast<MenuPattern>(innerMenu->GetPattern());
    CHECK_NULL_RETURN(innerMenuPattern, false);
    auto layoutProps = innerMenuPattern->GetLayoutProperty<MenuLayoutProperty>();
    CHECK_NULL_RETURN(layoutProps, false);
    auto expandingMode = layoutProps->GetExpandingMode().value_or(SubMenuExpandingMode::SIDE);
    if (IsSubMenu() && expandingMode == SubMenuExpandingMode::STACK) {
        auto host = GetHost();
        CHECK_NULL_RETURN(host, false);
        auto hostZone = host->GetPaintRectOffset(false, true);
        auto scroll = host->GetFirstChild();
        CHECK_NULL_RETURN(scroll, false);
        auto column = scroll->GetFirstChild();
        CHECK_NULL_RETURN(column, false);
        auto clickAreaNode = AceType::DynamicCast<FrameNode>(column->GetFirstChild());
        CHECK_NULL_RETURN(clickAreaNode, false);
        auto clickAreaZone = clickAreaNode->GetGeometryNode()->GetFrameRect();
        clickAreaZone.SetLeft(hostZone.GetX());
        clickAreaZone.SetTop(hostZone.GetY());
        if (clickAreaZone.IsInRegion(PointF(position.GetX(), position.GetY()))) {
            HideStackMenu();
            return true;
        }
    } else if (expandingMode == SubMenuExpandingMode::STACK) {
        auto host = GetHost();
        CHECK_NULL_RETURN(host, false);
        auto hostZone = host->GetPaintRectOffset(false, true);
        auto clickAreaZone = host->GetGeometryNode()->GetFrameRect();
        clickAreaZone.SetLeft(hostZone.GetX());
        clickAreaZone.SetTop(hostZone.GetY());
        if (clickAreaZone.IsInRegion(PointF(position.GetX(), position.GetY()))) {
            auto wrapperPattern = wrapper->GetPattern<MenuWrapperPattern>();
            CHECK_NULL_RETURN(wrapperPattern, false);
            wrapperPattern->HideSubMenu();
            return true;
        }
    }
    return false;
}

void MenuPattern::HideStackMenu() const
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto wrapper = GetMenuWrapper();
    CHECK_NULL_VOID(wrapper);
    AnimationOption option;
    option.SetOnFinishEvent(
        [weak = WeakClaim(RawPtr(wrapper)), subMenuWk = WeakClaim(RawPtr(host))] {
            auto subMenu = subMenuWk.Upgrade();
            CHECK_NULL_VOID(subMenu);
            auto pipeline = subMenu->GetContextWithCheck();
            CHECK_NULL_VOID(pipeline);
            auto taskExecutor = pipeline->GetTaskExecutor();
            CHECK_NULL_VOID(taskExecutor);
            taskExecutor->PostTask(
                [weak, subMenuWk]() {
                    auto subMenuNode = subMenuWk.Upgrade();
                    CHECK_NULL_VOID(subMenuNode);
                    auto menuWrapper = weak.Upgrade();
                    CHECK_NULL_VOID(menuWrapper);
                    menuWrapper->RemoveChild(subMenuNode);
                    menuWrapper->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF_AND_CHILD);
                },
                TaskExecutor::TaskType::UI, "HideStackMenu");
    });
    auto menuPattern = AceType::DynamicCast<MenuPattern>(host->GetPattern());
    if (menuPattern) {
        menuPattern->RemoveParentHoverStyle();
        auto frameNode = FrameNode::GetFrameNode(menuPattern->GetTargetTag(), menuPattern->GetTargetId());
        CHECK_NULL_VOID(frameNode);
        auto menuItem = frameNode->GetPattern<MenuItemPattern>();
        if (menuItem) {
            menuItem->SetIsSubMenuShowed(false);
        }
    }
    auto menuNode = AceType::DynamicCast<FrameNode>(wrapper->GetFirstChild());
    CHECK_NULL_VOID(menuNode);
    ShowStackMenuDisappearAnimation(menuNode, host, option);
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
    if (type_ == MenuType::MULTI_MENU || type_ == MenuType::DESKTOP_MENU || IsSelectOverlayCustomMenu()) {
        return 0;
    }

    auto host = GetHost();
    CHECK_NULL_RETURN(host, 0);
    auto child = host->GetChildAtIndex(0);
    uint32_t depth = 0;
    while (child && depth < MAX_SEARCH_DEPTH) {
        // found component <Menu>
        if (child->GetTag() == V2::JS_VIEW_ETS_TAG) {
            child = child->GetFrameChildByIndex(0, false);
            if (child && child->GetTag() == V2::JS_VIEW_ETS_TAG) {
                child = child->GetChildAtIndex(0);
                ++depth;
            }
            continue;
        }
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
        if (child->GetTag() == V2::JS_VIEW_ETS_TAG) {
            child = child->GetFrameChildByIndex(0, false);
            if (child && child->GetTag() == V2::JS_VIEW_ETS_TAG) {
                child = child->GetChildAtIndex(0);
                ++depth;
            }
            continue;
        }
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
    auto pattern = option->GetPattern<MenuItemPattern>();
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
    if (IsMultiMenu() || IsDesktopMenu()) {
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
            return MakeRefPtr<MenuLayoutAlgorithm>(targetId_, targetTag_, lastPosition_);
    }
}

bool MenuPattern::GetShadowFromTheme(ShadowStyle shadowStyle, Shadow& shadow)
{
    if (shadowStyle == ShadowStyle::None) {
        return true;
    }
    auto host = GetHost();
    auto pipelineContext = host->GetContextRefPtr();
    CHECK_NULL_RETURN(pipelineContext, false);
    auto colorMode = pipelineContext->GetColorMode();
    auto shadowTheme = pipelineContext->GetTheme<ShadowTheme>();
    CHECK_NULL_RETURN(shadowTheme, false);
    shadow = shadowTheme->GetShadow(shadowStyle, colorMode);
    return true;
}

void MenuPattern::ResetTheme(const RefPtr<FrameNode>& host, bool resetForDesktopMenu)
{
    auto renderContext = host->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    auto scroll = DynamicCast<FrameNode>(host->GetFirstChild());
    CHECK_NULL_VOID(scroll);

    if (resetForDesktopMenu) {
        // DesktopMenu apply shadow on inner Menu node
        Shadow shadow;
        if (GetShadowFromTheme(ShadowStyle::None, shadow)) {
            renderContext->UpdateBackShadow(shadow);
        }
    } else {
        Shadow shadow;
        auto shadowStyle = GetMenuDefaultShadowStyle();
        if (GetShadowFromTheme(shadowStyle, shadow)) {
            renderContext->UpdateBackShadow(shadow);
        }
    }
    // to enable inner menu shadow effect for desktopMenu, need to remove clipping from container
    bool clip = !resetForDesktopMenu;
    scroll->GetRenderContext()->SetClipToBounds(clip);

    // move padding from scroll to inner menu
    auto scrollProp = scroll->GetLayoutProperty();
    scrollProp->UpdatePadding(PaddingProperty());
}

void MenuPattern::ResetScrollTheme(const RefPtr<FrameNode>& host)
{
    auto renderContext = host->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    auto scroll = DynamicCast<FrameNode>(host->GetFirstChild());
    CHECK_NULL_VOID(scroll);
    scroll->GetRenderContext()->UpdateClipEdge(false);
}

void MenuPattern::InitTheme(const RefPtr<FrameNode>& host)
{
    CHECK_NULL_VOID(host);
    auto renderContext = host->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    auto pipeline = host->GetContextWithCheck();
    CHECK_NULL_VOID(pipeline);
    auto theme = pipeline->GetTheme<SelectTheme>();
    CHECK_NULL_VOID(theme);
    auto expandDisplay = theme->GetExpandDisplay();
    expandDisplay_ = expandDisplay;
    if (Container::LessThanAPIVersion(PlatformVersion::VERSION_ELEVEN) || !renderContext->IsUniRenderEnabled()) {
        auto bgColor = theme->GetBackgroundColor();
        renderContext->UpdateBackgroundColor(bgColor);
    }
    Shadow shadow;
    auto defaultShadowStyle = GetMenuDefaultShadowStyle();
    if (GetShadowFromTheme(defaultShadowStyle, shadow)) {
        renderContext->UpdateBackShadow(shadow);
    }
    // make menu round rect
    BorderRadiusProperty borderRadius;
    if (Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_TWELVE)) {
        borderRadius.SetRadius(theme->GetMenuDefaultRadius());
    } else {
        borderRadius.SetRadius(theme->GetMenuBorderRadius());
    }
    renderContext->UpdateBorderRadius(borderRadius);
    renderContext->UpdateOuterBorderRadius(borderRadius);
}

void InnerMenuPattern::InitTheme(const RefPtr<FrameNode>& host)
{
    CHECK_NULL_VOID(host);
    MenuPattern::InitTheme(host);
    // inner menu applies shadow in OnModifyDone(), where it can determine if it's a DesktopMenu or a regular menu

    auto layoutProperty = host->GetLayoutProperty();
    if (layoutProperty->GetPaddingProperty()) {
        // if user defined padding exists, skip applying default padding
        return;
    }
    auto pipeline = host->GetContextWithCheck();
    CHECK_NULL_VOID(pipeline);
    auto theme = pipeline->GetTheme<SelectTheme>();
    CHECK_NULL_VOID(theme);
    // apply default padding from theme on inner menu
    PaddingProperty padding;
    padding.SetEdges(CalcLength(theme->GetMenuPadding()));
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

Offset MenuPattern::GetTransformCenter() const
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, Offset());
    auto geometryNode = host->GetGeometryNode();
    CHECK_NULL_RETURN(geometryNode, Offset());
    auto size = geometryNode->GetFrameSize();
    auto layoutAlgorithmWrapper = host->GetLayoutAlgorithm();
    CHECK_NULL_RETURN(layoutAlgorithmWrapper, Offset());
    auto layoutAlgorithm = AceType::DynamicCast<MenuLayoutAlgorithm>(layoutAlgorithmWrapper->GetLayoutAlgorithm());
    CHECK_NULL_RETURN(layoutAlgorithm, Offset());
    auto placement = layoutAlgorithm->GetPlacement();
    switch (placement) {
        case Placement::BOTTOM_LEFT:
        case Placement::RIGHT_TOP:
            return Offset();
        case Placement::BOTTOM_RIGHT:
        case Placement::LEFT_TOP:
            return Offset(size.Width(), 0.0f);
        case Placement::TOP_LEFT:
        case Placement::RIGHT_BOTTOM:
            return Offset(0.0f, size.Height());
        case Placement::TOP_RIGHT:
        case Placement::LEFT_BOTTOM:
            return Offset(size.Width(), size.Height());
        case Placement::BOTTOM:
            return Offset(size.Width() / 2, 0.0f);
        case Placement::LEFT:
            return Offset(size.Width(), size.Height() / 2);
        case Placement::TOP:
            return Offset(size.Width() / 2, size.Height());
        case Placement::RIGHT:
            return Offset(0.0f, size.Height() / 2);
        default:
            return Offset();
    }
}

RefPtr<FrameNode> MenuPattern::DuplicateMenuNode(const RefPtr<FrameNode>& menuNode, const MenuParam& menuParam)
{
    auto duplicateMenuNode = FrameNode::CreateFrameNode(V2::ROW_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<LinearLayoutPattern>(false));
    CHECK_NULL_RETURN(menuNode, duplicateMenuNode);
    auto menuLayoutProperty = menuNode->GetLayoutProperty<MenuLayoutProperty>();
    CHECK_NULL_RETURN(menuLayoutProperty, duplicateMenuNode);
    if (menuLayoutProperty->GetBorderRadius().has_value()) {
        BorderRadiusProperty borderRadius = menuLayoutProperty->GetBorderRadiusValue();
        UpdateBorderRadius(duplicateMenuNode, borderRadius);
    }
    SetMenuBackGroundStyle(duplicateMenuNode, menuParam);
    return duplicateMenuNode;
}

void MenuPattern::SetMenuBackGroundStyle(const RefPtr<FrameNode>& menuNode, const MenuParam& menuParam)
{
    CHECK_NULL_VOID(menuNode);
    auto renderContext = menuNode->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    BlurStyleOption styleOption;
    if (menuParam.backgroundColor.has_value()) {
        styleOption.blurStyle = BlurStyle::COMPONENT_ULTRA_THICK;
        renderContext->UpdateBackgroundColor(menuParam.backgroundColor.value_or(Color::TRANSPARENT));
    } else {
        styleOption.blurStyle = static_cast<BlurStyle>(
            menuParam.backgroundBlurStyle.value_or(static_cast<int32_t>(BlurStyle::COMPONENT_ULTRA_THICK)));
        renderContext->UpdateBackgroundColor(Color::TRANSPARENT);
    }
    renderContext->UpdateBackBlurStyle(styleOption);
    if (menuParam.backgroundBlurStyleOption.has_value()) {
        BlurStyleOption backgroundBlurStyleOption = menuParam.backgroundBlurStyleOption.value();
        if (renderContext->GetBackgroundEffect().has_value()) {
            renderContext->UpdateBackgroundEffect(std::nullopt);
        }
        renderContext->UpdateBackBlurStyle(backgroundBlurStyleOption);
        if (renderContext->GetBackBlurRadius().has_value()) {
            renderContext->UpdateBackBlurRadius(Dimension());
        }
    }
    if (menuParam.backgroundEffectOption.has_value()) {
        EffectOption backgroundEffectOption = menuParam.backgroundEffectOption.value();
        if (renderContext->GetBackBlurRadius().has_value()) {
            renderContext->UpdateBackBlurRadius(Dimension());
        }
        if (renderContext->GetBackBlurStyle().has_value()) {
            renderContext->UpdateBackBlurStyle(std::nullopt);
        }
        renderContext->UpdateBackgroundEffect(backgroundEffectOption);
    }
}

void MenuPattern::ShowPreviewPositionAnimation(AnimationOption& option, int32_t delay)
{
    auto menuWrapper = GetMenuWrapper();
    CHECK_NULL_VOID(menuWrapper);
    auto menuWrapperPattern = menuWrapper->GetPattern<MenuWrapperPattern>();
    CHECK_NULL_VOID(menuWrapperPattern);

    auto preview = isShowHoverImage_ ? menuWrapperPattern->GetHoverImageFlexNode() : menuWrapperPattern->GetPreview();
    CHECK_NULL_VOID(preview);
    bool isHoverImageTarget = isShowHoverImage_ && preview->GetTag() == V2::FLEX_ETS_TAG;
    auto previewRenderContext = preview->GetRenderContext();
    CHECK_NULL_VOID(previewRenderContext);
    auto previewGeometryNode = preview->GetGeometryNode();
    CHECK_NULL_VOID(previewGeometryNode);
    auto previewPosition = previewGeometryNode->GetFrameOffset();
    OffsetF previewOriginPosition = GetPreviewOriginOffset();

    previewRenderContext->UpdatePosition(
        OffsetT<Dimension>(Dimension(previewOriginPosition.GetX()), Dimension(previewOriginPosition.GetY())));

    if (menuWrapperPattern->GetHoverScaleInterruption()) {
        return;
    }

    if (isHoverImageTarget) {
        option.SetCurve(CUSTOM_PREVIEW_ANIMATION_CURVE);
        option.SetDelay(delay);
    }

    AnimationUtils::Animate(option, [previewRenderContext, previewPosition]() {
        CHECK_NULL_VOID(previewRenderContext);
        previewRenderContext->UpdatePosition(
            OffsetT<Dimension>(Dimension(previewPosition.GetX()), Dimension(previewPosition.GetY())));
    });
}

void MenuPattern::ShowPreviewMenuScaleAnimation(
    const RefPtr<MenuTheme>& menuTheme, AnimationOption& option, int32_t delay)
{
    CHECK_NULL_VOID(menuTheme);
    auto menuWrapper = GetMenuWrapper();
    CHECK_NULL_VOID(menuWrapper);
    auto menuWrapperPattern = menuWrapper->GetPattern<MenuWrapperPattern>();
    CHECK_NULL_VOID(menuWrapperPattern);

    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto renderContext = host->GetRenderContext();
    CHECK_NULL_VOID(renderContext);

    auto menuPosition = host->GetPaintRectOffset(false, true);
    auto menuAnimationScale = menuTheme->GetMenuAnimationScale();
    renderContext->UpdateTransformCenter(DimensionOffset(GetTransformCenter()));
    renderContext->UpdateTransformScale(VectorF(menuAnimationScale, menuAnimationScale));
    renderContext->UpdatePosition(OffsetT<Dimension>(Dimension(originOffset_.GetX()), Dimension(originOffset_.GetY())));

    if (isShowHoverImage_) {
        option.SetCurve(CUSTOM_PREVIEW_ANIMATION_CURVE);
        option.SetDelay(delay);
    }

    AnimationUtils::Animate(option, [renderContext, menuPosition]() {
        CHECK_NULL_VOID(renderContext);
        renderContext->UpdateTransformScale(VectorF(1.0f, 1.0f));
        renderContext->UpdatePosition(
            OffsetT<Dimension>(Dimension(menuPosition.GetX()), Dimension(menuPosition.GetY())));
    });
}

void MenuPattern::ShowPreviewMenuAnimation()
{
    CHECK_NULL_VOID(isFirstShow_ && previewMode_ != MenuPreviewMode::NONE);

    auto menuWrapper = GetMenuWrapper();
    CHECK_NULL_VOID(menuWrapper);
    auto menuWrapperPattern = menuWrapper->GetPattern<MenuWrapperPattern>();
    CHECK_NULL_VOID(menuWrapperPattern && !menuWrapperPattern->IsHide());

    auto pipeline = menuWrapper->GetContextWithCheck();
    CHECK_NULL_VOID(pipeline);
    auto menuTheme = pipeline->GetTheme<NG::MenuTheme>();
    CHECK_NULL_VOID(menuTheme);

    auto springMotionResponse = menuTheme->GetSpringMotionResponse();
    auto springMotionDampingFraction = menuTheme->GetSpringMotionDampingFraction();
    auto isHoverScaleInterrupt = menuWrapperPattern->GetHoverScaleInterruption();
    auto delay = isShowHoverImage_ ? menuTheme->GetHoverImageDelayDuration(isHoverScaleInterrupt) : 0;

    AnimationOption option = AnimationOption();
    auto motion = AceType::MakeRefPtr<ResponsiveSpringMotion>(springMotionResponse, springMotionDampingFraction);
    option.SetCurve(motion);

    auto host = GetHost();
    CHECK_NULL_VOID(host);
    MenuView::CalcHoverScaleInfo(host);
    InitPreviewMenuAnimationInfo(menuTheme);

    // customPreview position animation
    ShowPreviewPositionAnimation(option, delay);

    // menu position and scale animation
    ShowPreviewMenuScaleAnimation(menuTheme, option, delay);

    // image and hoverScale animation
    MenuView::ShowPixelMapAnimation(host);
    ShowMenuOpacityAnimation(menuTheme, host->GetRenderContext(), delay);
    isFirstShow_ = false;
}

void MenuPattern::ShowMenuAppearAnimation()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    if (isMenuShow_ && Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_TWELVE) &&
        previewMode_ == MenuPreviewMode::NONE) {
        auto renderContext = host->GetRenderContext();
        CHECK_NULL_VOID(renderContext);
        auto pipeline = host->GetContext();
        CHECK_NULL_VOID(pipeline);
        auto theme = pipeline->GetTheme<SelectTheme>();
        CHECK_NULL_VOID(theme);
        auto menuPosition = host->GetPaintRectOffset(false, true);
        if (IsSelectOverlayExtensionMenu() && !isExtensionMenuShow_) {
            menuPosition = GetEndOffset();
        }
        if (IsSelectOverlayExtensionMenu()) {
            SetEndOffset(menuPosition);
        }
        renderContext->UpdateTransformScale(VectorF(theme->GetMenuAnimationScale(), theme->GetMenuAnimationScale()));
        renderContext->UpdateOpacity(0.0f);
        AnimationOption option = AnimationOption();
        if (theme->GetMenuAnimationDuration()) {
            option.SetDuration(theme->GetMenuAnimationDuration());
            option.SetCurve(theme->GetMenuAnimationCurve());
            renderContext->UpdateTransformCenter(DimensionOffset(Offset()));
        } else {
            option.SetCurve(MAIN_MENU_ANIMATION_CURVE);
            renderContext->UpdateTransformCenter(DimensionOffset(GetTransformCenter()));
        }
        AnimationUtils::Animate(option, [this, renderContext, menuPosition]() {
            CHECK_NULL_VOID(renderContext);
            if (IsSelectOverlayExtensionMenu()) {
                renderContext->UpdatePosition(
                    OffsetT<Dimension>(Dimension(menuPosition.GetX()), Dimension(menuPosition.GetY())));
            }
            renderContext->UpdateOpacity(1.0f);
            renderContext->UpdateTransformScale(VectorF(1.0f, 1.0f));
        });
        isExtensionMenuShow_ = false;
    }
    isMenuShow_ = false;
}

RefPtr<FrameNode> MenuPattern::GetTitleContentNode(const RefPtr<FrameNode>& subMenuNode) const
{
    auto scroll = subMenuNode->GetFirstChild();
    CHECK_NULL_RETURN(scroll, nullptr);
    auto subInnerMenu = scroll->GetFirstChild();
    CHECK_NULL_RETURN(subInnerMenu, nullptr);
    auto titleNode = DynamicCast<FrameNode>(subInnerMenu->GetFirstChild());
    CHECK_NULL_RETURN(titleNode, nullptr);
    auto titleItemPattern = titleNode->GetPattern<MenuItemPattern>();
    CHECK_NULL_RETURN(titleItemPattern, nullptr);
    return titleItemPattern->GetContentNode();
}

void MenuPattern::ShowStackSubMenuAnimation(const RefPtr<FrameNode>& mainMenu, const RefPtr<FrameNode>& subMenuNode)
{
    auto subMenuContext = subMenuNode->GetRenderContext();
    CHECK_NULL_VOID(subMenuContext);
    subMenuContext->UpdateOpacity(0.0f);
    auto otherMenuItemContext = GetOtherMenuItemContext(subMenuNode);
    for (auto menuItemContext : otherMenuItemContext) {
        menuItemContext->UpdateOpacity(0.0f);
    }
    auto [originOffset, endOffset] = GetMenuOffset(mainMenu, subMenuNode);
    if (originOffset ==  OffsetF()) {
        TAG_LOGW(AceLogTag::ACE_MENU, "not found parent MenuItem when show stack sub menu");
    }
    subMenuContext->UpdatePosition(
        OffsetT<Dimension>(Dimension(originOffset.GetX()), Dimension(originOffset.GetY())));

    AnimationOption translateOption = AnimationOption();
    translateOption.SetCurve(STACK_SUB_MENU_ANIMATION_CURVE);
    translateOption.SetDuration(STACK_MENU_APPEAR_DURATION);
    AnimationUtils::Animate(translateOption, [weak = WeakClaim(RawPtr(subMenuContext)), menuPosition = endOffset]() {
        auto subMenuContextUpgrade = weak.Upgrade();
        CHECK_NULL_VOID(subMenuContextUpgrade);
        subMenuContextUpgrade->UpdatePosition(
            OffsetT<Dimension>(Dimension(menuPosition.GetX()), Dimension(menuPosition.GetY())));
    });
    AnimationOption opacityOption = AnimationOption();
    opacityOption.SetCurve(Curves::FRICTION);
    opacityOption.SetDuration(STACK_MENU_APPEAR_DURATION);
    AnimationUtils::Animate(opacityOption, [weak = WeakClaim(RawPtr(subMenuContext))]() {
        auto subMenuContextUpgrade = weak.Upgrade();
        CHECK_NULL_VOID(subMenuContextUpgrade);
        subMenuContextUpgrade->UpdateOpacity(1.0f);
    });
    AnimationOption contentOpacityOption = AnimationOption();
    contentOpacityOption.SetCurve(Curves::FRICTION);
    contentOpacityOption.SetDelay(STACK_SUB_MENU_APPEAR_DELAY);
    contentOpacityOption.SetDuration(STACK_MENU_APPEAR_DURATION);
    auto titleContentNode = GetTitleContentNode(subMenuNode);
    CHECK_NULL_VOID(titleContentNode);
    AnimationUtils::Animate(contentOpacityOption, [otherMenuItemContext, titleContentNode]() {
        for (auto menuItemContext : otherMenuItemContext) {
            CHECK_NULL_CONTINUE(menuItemContext);
            menuItemContext->UpdateOpacity(1.0f);
        }
        CHECK_NULL_VOID(titleContentNode);
        auto textProperty = titleContentNode->GetLayoutProperty<TextLayoutProperty>();
        CHECK_NULL_VOID(textProperty);
        textProperty->UpdateFontWeight(FontWeight::BOLD);
        titleContentNode->MarkDirtyNode();
    });

    ShowArrowRotateAnimation();
}

void MenuPattern::ShowStackMainMenuAnimation(const RefPtr<FrameNode>& mainMenu, const RefPtr<FrameNode>& subMenuNode,
    const RefPtr<FrameNode>& menuWrapper)
{
    auto menuWrapperPattern = menuWrapper->GetPattern<MenuWrapperPattern>();
    CHECK_NULL_VOID(menuWrapperPattern);
    auto preview = isShowHoverImage_ ? menuWrapperPattern->GetHoverImageFlexNode() : menuWrapperPattern->GetPreview();
    auto subMenuPattern = subMenuNode->GetPattern<MenuPattern>();
    CHECK_NULL_VOID(subMenuPattern);
    float translateYForStack = subMenuPattern->GetTranslateYForStack();
    AnimationOption translateOption = AnimationOption();
    translateOption.SetCurve(STACK_SUB_MENU_ANIMATION_CURVE);
    translateOption.SetDuration(STACK_MAIN_MENU_APPEAR_DURATION);
    AnimationUtils::Animate(translateOption, [mainMenu, translateYForStack, preview]() {
        CHECK_NULL_VOID(mainMenu);
        auto mainMenuOffset = mainMenu->GetPaintRectOffset(false, true);
        auto mainMenuContext = mainMenu->GetRenderContext();
        CHECK_NULL_VOID(mainMenuContext);
        mainMenuContext->UpdateTransformScale(VectorF(MOUNT_MENU_FINAL_SCALE, MOUNT_MENU_FINAL_SCALE));
        if (NearZero(translateYForStack)) {
            return;
        }
        auto mainMenuPattern = mainMenu->GetPattern<MenuPattern>();
        CHECK_NULL_VOID(mainMenuPattern);
        mainMenuPattern->SetOriginMenuYForStack(mainMenuOffset.GetY());
        mainMenuContext->UpdatePosition(
            OffsetT<Dimension>(Dimension(mainMenuOffset.GetX()),
                Dimension(mainMenuOffset.GetY() - translateYForStack)));
        mainMenu->GetGeometryNode()->SetMarginFrameOffset(OffsetF(mainMenuOffset.GetX(),
            mainMenuOffset.GetY() - translateYForStack));

        CHECK_NULL_VOID(preview);
        auto previewFrameOffset = preview->GetGeometryNode()->GetFrameOffset();
        mainMenuPattern->SetOriginPreviewYForStack(previewFrameOffset.GetY());
        auto previewRenderContext = preview->GetRenderContext();
        CHECK_NULL_VOID(previewRenderContext);
        previewRenderContext->UpdatePosition(
            OffsetT<Dimension>(Dimension(previewFrameOffset.GetX()),
                Dimension(previewFrameOffset.GetY() - translateYForStack)));
        preview->GetGeometryNode()->SetMarginFrameOffset(OffsetF(previewFrameOffset.GetX(),
            previewFrameOffset.GetY() - translateYForStack));
    });
    ShowStackMainMenuOpacityAnimation(mainMenu);
}

void MenuPattern::ShowStackMainMenuOpacityAnimation(const RefPtr<FrameNode>& mainMenu)
{
    CHECK_NULL_VOID(mainMenu);
    auto scroll = mainMenu->GetFirstChild();
    CHECK_NULL_VOID(scroll);
    auto innerMenu = scroll->GetFirstChild();
    CHECK_NULL_VOID(innerMenu);
    auto innerMenuFrameNode = DynamicCast<FrameNode>(innerMenu);
    CHECK_NULL_VOID(innerMenuFrameNode);
    auto innerMenuContext = innerMenuFrameNode->GetRenderContext();
    CHECK_NULL_VOID(innerMenuContext);

    AnimationOption opacityOption = AnimationOption();
    opacityOption.SetCurve(Curves::FRICTION);
    opacityOption.SetDuration(STACK_MAIN_MENU_APPEAR_DURATION);
    AnimationUtils::Animate(opacityOption, [innerMenuContext]() {
        if (innerMenuContext) {
            innerMenuContext->UpdateOpacity(MAIN_MENU_OPACITY);
        }
    });
}

void MenuPattern::ShowStackMenuAppearAnimation()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    if (!isSubMenuShow_) {
        return;
    }
    auto menuWrapper = GetMenuWrapper();
    CHECK_NULL_VOID(menuWrapper);
    auto menuWrapperPattern = menuWrapper->GetPattern<MenuWrapperPattern>();
    CHECK_NULL_VOID(menuWrapperPattern);
    auto mainMenu = menuWrapperPattern->GetMenu();
    CHECK_NULL_VOID(mainMenu);
    auto mainMenuAccessibilityProps = mainMenu->GetAccessibilityProperty<AccessibilityProperty>();
    CHECK_NULL_VOID(mainMenuAccessibilityProps);
    mainMenuAccessibilityProps->SetAccessibilityLevel(AccessibilityProperty::Level::NO_HIDE_DESCENDANTS);

    ShowStackMainMenuAnimation(mainMenu, host, menuWrapper);
    ShowStackSubMenuAnimation(mainMenu, host);
    isSubMenuShow_ = false;
}

std::pair<OffsetF, OffsetF> MenuPattern::GetMenuOffset(const RefPtr<FrameNode>& mainMenu,
    const RefPtr<FrameNode>& subMenu, bool isNeedRestoreNodeId) const
{
    CHECK_NULL_RETURN(mainMenu, std::make_pair(OffsetF(), OffsetF()));
    auto scroll = mainMenu->GetFirstChild();
    CHECK_NULL_RETURN(scroll, std::make_pair(OffsetF(), OffsetF()));
    auto innerMenu = scroll->GetFirstChild();
    CHECK_NULL_RETURN(innerMenu, std::make_pair(OffsetF(), OffsetF()));
    auto children = innerMenu->GetChildren();
    MenuItemInfo menuItemInfo;
    for (auto child : children) {
        menuItemInfo = GetInnerMenuOffset(child, subMenu, isNeedRestoreNodeId);
        if (menuItemInfo.isFindTargetId) {
            break;
        }
    }
    return {menuItemInfo.originOffset, menuItemInfo.endOffset};
}

MenuItemInfo MenuPattern::GetInnerMenuOffset(const RefPtr<UINode>& child, const RefPtr<FrameNode>& subMenu,
    bool isNeedRestoreNodeId) const
{
    MenuItemInfo menuItemInfo;
    CHECK_NULL_RETURN(child, menuItemInfo);
    if (child->GetTag() == V2::MENU_ITEM_ETS_TAG) {
        menuItemInfo = GetMenuItemInfo(child, subMenu, isNeedRestoreNodeId);
        if (menuItemInfo.isFindTargetId) {
            return menuItemInfo;
        }
    } else {
        const auto& groupChildren = child->GetChildren();
        for (auto child : groupChildren) {
            menuItemInfo = GetInnerMenuOffset(child, subMenu, isNeedRestoreNodeId);
            if (menuItemInfo.isFindTargetId) {
                return menuItemInfo;
            }
        }
    }
    return menuItemInfo;
}

MenuItemInfo MenuPattern::GetMenuItemInfo(const RefPtr<UINode>& child, const RefPtr<FrameNode>& subMenu,
    bool isNeedRestoreNodeId) const
{
    MenuItemInfo menuItemInfo;
    auto menuItem = AceType::DynamicCast<FrameNode>(child);
    CHECK_NULL_RETURN(menuItem, menuItemInfo);
    if (menuItem->GetTag() == V2::MENU_ITEM_ETS_TAG) {
        auto menuItemPattern = menuItem->GetPattern<MenuItemPattern>();
        CHECK_NULL_RETURN(menuItemPattern, menuItemInfo);
        if (menuItem->GetId() == menuItemPattern->GetClickMenuItemId()) {
            auto host = GetHost();
            CHECK_NULL_RETURN(host, menuItemInfo);
            auto pipeline = host->GetContextWithCheck();
            CHECK_NULL_RETURN(pipeline, menuItemInfo);
            auto isContainerModal = pipeline->GetWindowModal() == WindowModal::CONTAINER_MODAL;
            auto offset = menuItem->GetPaintRectOffset(false, true);
            if (isContainerModal) {
                offset -= OffsetF(0.0f, static_cast<float>(pipeline->GetCustomTitleHeight().ConvertToPx()));
            }
            menuItemInfo.originOffset = offset - OffsetF(PADDING.ConvertToPx(), PADDING.ConvertToPx());
            menuItemInfo.endOffset = OffsetF(menuItemInfo.originOffset.GetX(),
                subMenu->GetPaintRectOffset(false, true).GetY());
            if (isContainerModal) {
                menuItemInfo.endOffset -= OffsetF(0.0f,
                    static_cast<float>(pipeline->GetCustomTitleHeight().ConvertToPx())
                    + static_cast<float>(CONTAINER_BORDER_WIDTH.ConvertToPx()));
            }
            menuItemInfo.isFindTargetId = true;
            if (isNeedRestoreNodeId) {
                menuItemPattern->SetClickMenuItemId(-1);
            }
        }
    }
    return menuItemInfo;
}

RefPtr<FrameNode> MenuPattern::GetFirstMenuItem()
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, nullptr);
    uint32_t depth = 0;
    auto child = host->GetFirstChild();
    while (child && depth < MAX_SEARCH_DEPTH) {
        if (child->GetTag() == V2::MENU_ITEM_ETS_TAG) {
            return AceType::DynamicCast<FrameNode>(child);
        }
        if (child->GetTag() == V2::JS_VIEW_ETS_TAG) {
            child = child->GetFirstChild();
            if (child && child->GetTag() == V2::JS_VIEW_ETS_TAG) {
                child  = child->GetFirstChild();
                ++depth;
            }
            continue;
        }
        child = child->GetFirstChild();
        ++depth;
    }
    return nullptr;
}

RefPtr<FrameNode> MenuPattern::GetLastMenuItem()
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, nullptr);
    uint32_t depth = 0;
    auto child = host->GetLastChild();
    while (child && depth < MAX_SEARCH_DEPTH) {
        if (child->GetTag() == V2::MENU_ITEM_ETS_TAG) {
            return AceType::DynamicCast<FrameNode>(child);
        }
        if (child->GetTag() == V2::JS_VIEW_ETS_TAG) {
            child = child->GetLastChild();
            if (child && child->GetTag() == V2::JS_VIEW_ETS_TAG) {
                child  = child->GetLastChild();
                ++depth;
            }
            continue;
        }
        child = child->GetLastChild();
        ++depth;
    }
    return nullptr;
}

std::pair<float, float> MenuPattern::GetPreviewPositionY()
{
    auto menuWrapper = GetMenuWrapper();
    CHECK_NULL_RETURN(menuWrapper, std::make_pair(0.0f, 0.0f));
    auto menuWrapperPattern = menuWrapper->GetPattern<MenuWrapperPattern>();
    CHECK_NULL_RETURN(menuWrapperPattern, std::make_pair(0.0f, 0.0f));
    auto preview = menuWrapperPattern->GetPreview();
    CHECK_NULL_RETURN(preview, std::make_pair(0.0f, 0.0f));
    auto geometryNode = preview->GetGeometryNode();
    CHECK_NULL_RETURN(geometryNode, std::make_pair(0.0f, 0.0f));
    return {preview->GetPaintRectOffset(false, true).GetY(),
        preview->GetPaintRectOffset(false, true).GetY() + geometryNode->GetMarginFrameSize().Height()};
}

void MenuPattern::ShowArrowRotateAnimation() const
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto subImageNode = GetArrowNode(host);
    CHECK_NULL_VOID(subImageNode);
    auto subImageContext = subImageNode->GetRenderContext();
    CHECK_NULL_VOID(subImageContext);
    subImageContext->UpdateTransformRotate(Vector5F(0.0f, 0.0f, 1.0f, 0.0f, 0.0f));
    AnimationOption option = AnimationOption();
    option.SetCurve(AceType::MakeRefPtr<InterpolatingSpring>(0.0f, 1.0f, 228.0f, 22.0f));
    double arrowRotateDelay = 50.0f;
    double arrowRotateDuration = 400.0f;
    option.SetDelay(arrowRotateDelay);
    option.SetDuration(arrowRotateDuration);
    AnimationUtils::Animate(option, [subImageContext]() {
        if (subImageContext) {
            subImageContext->UpdateTransformRotate(Vector5F(0.0f, 0.0f, 1.0f, SEMI_CIRCLE_ANGEL, 0.0f));
        }
    });
}

void MenuPattern::ShowArrowReverseRotateAnimation() const
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto subImageNode = GetArrowNode(host);
    CHECK_NULL_VOID(subImageNode);
    auto subImageContext = subImageNode->GetRenderContext();
    CHECK_NULL_VOID(subImageContext);
    AnimationOption option = AnimationOption();
    option.SetCurve(AceType::MakeRefPtr<InterpolatingSpring>(0.0f, 1.0f, 228.0f, 22.0f));
    double arrowRotateAnimationDuration = 200.0f;
    option.SetDuration(arrowRotateAnimationDuration);
    AnimationUtils::Animate(option, [subImageContext]() {
        if (subImageContext) {
            subImageContext->UpdateTransformRotate(Vector5F(0.0f, 0.0f, 1.0f, 0.0f, 0.0f));
        }
    });
}

RefPtr<FrameNode> MenuPattern::GetArrowNode(const RefPtr<FrameNode>& host) const
{
    auto scroll = host->GetFirstChild();
    CHECK_NULL_RETURN(scroll, nullptr);
    auto innerMenu = scroll->GetFirstChild();
    CHECK_NULL_RETURN(innerMenu, nullptr);
    auto menuItem = innerMenu->GetFirstChild();
    CHECK_NULL_RETURN(menuItem, nullptr);
    auto rightRow = menuItem->GetChildAtIndex(1);
    CHECK_NULL_RETURN(rightRow, nullptr);
    auto image = AceType::DynamicCast<FrameNode>(rightRow->GetChildren().back());
    return image;
}

std::vector<RefPtr<RenderContext>> MenuPattern::GetOtherMenuItemContext(const RefPtr<FrameNode>& subMenuNode) const
{
    CHECK_NULL_RETURN(subMenuNode, {});
    auto scroll = subMenuNode->GetFirstChild();
    CHECK_NULL_RETURN(scroll, {});
    auto subInnerMenu = scroll->GetFirstChild();
    CHECK_NULL_RETURN(subInnerMenu, {});
    std::vector<RefPtr<RenderContext>> otherMenuItemContext;
    auto children = subInnerMenu->GetChildren();
    if (children.empty()) {
        LOGW("children is empty.");
        return {};
    }
    auto child = children.begin();
    for (advance(child, 1); child != children.end(); ++child) {
        auto menuItem = DynamicCast<FrameNode>(*child);
        CHECK_NULL_RETURN(menuItem, {});
        auto menuItemContext = menuItem->GetRenderContext();
        otherMenuItemContext.emplace_back(menuItemContext);
    }
    return otherMenuItemContext;
}

void MenuPattern::ShowStackSubMenuDisappearAnimation(const RefPtr<FrameNode>& menuNode,
    const RefPtr<FrameNode>& subMenuNode) const
{
    auto titleContentNode = GetTitleContentNode(subMenuNode);
    CHECK_NULL_VOID(titleContentNode);
    auto otherMenuItemContext = GetOtherMenuItemContext(subMenuNode);
    AnimationOption contentOpacityOption = AnimationOption();
    contentOpacityOption.SetCurve(Curves::FRICTION);
    double subMenuDisappearDuration = 200.0f;
    contentOpacityOption.SetDuration(subMenuDisappearDuration);
    AnimationUtils::Animate(contentOpacityOption, [otherMenuItemContext, titleContentNode]() {
        CHECK_NULL_VOID(titleContentNode);
        auto textProperty = titleContentNode->GetLayoutProperty<TextLayoutProperty>();
        CHECK_NULL_VOID(textProperty);
        textProperty->UpdateFontWeight(FontWeight::MEDIUM);
        titleContentNode->MarkDirtyNode();
        for (auto menuItemContext : otherMenuItemContext) {
            menuItemContext->UpdateOpacity(0.0f);
        }
    });

    ShowArrowReverseRotateAnimation();

    auto [originOffset, endOffset] = GetMenuOffset(menuNode, subMenuNode, true);
    auto subMenuPos = subMenuNode->GetPaintRectOffset(false, true);
    auto menuPosition = OffsetF(subMenuPos.GetX(), originOffset.GetY());
    auto subMenuContext = subMenuNode->GetRenderContext();
    CHECK_NULL_VOID(subMenuContext);
    AnimationOption translateOption = AnimationOption();
    translateOption.SetCurve(AceType::MakeRefPtr<InterpolatingSpring>(0.0f, 1.0f, 228.0f, 26.0f));
    translateOption.SetDuration(STACK_MENU_DISAPPEAR_DURATION);
    AnimationUtils::Animate(translateOption, [menuPosition, subMenuContext]() {
        CHECK_NULL_VOID(subMenuContext);
        subMenuContext->UpdatePosition(
            OffsetT<Dimension>(Dimension(menuPosition.GetX()), Dimension(menuPosition.GetY())));
    });
    AnimationOption opacityOption = AnimationOption();
    opacityOption.SetCurve(Curves::FRICTION);
    opacityOption.SetDuration(STACK_MENU_DISAPPEAR_DURATION);
    AnimationUtils::Animate(opacityOption, [subMenuContext]() {
        CHECK_NULL_VOID(subMenuContext);
        subMenuContext->UpdateOpacity(0.0f);
    });
}

void MenuPattern::ShowStackMainMenuDisappearAnimation(const RefPtr<FrameNode>& menuNode,
    const RefPtr<FrameNode>& subMenuNode, AnimationOption& option) const
{
    auto [originOffset, endOffset] = GetMenuOffset(menuNode, subMenuNode, true);
    auto subMenuPos = subMenuNode->GetPaintRectOffset(false, true);
    auto menuPosition = OffsetF(subMenuPos.GetX(), originOffset.GetY());

    option.SetCurve(STACK_SUB_MENU_ANIMATION_CURVE);
    auto menuWrapper = GetMenuWrapper();
    CHECK_NULL_VOID(menuWrapper);
    auto menuWrapperPattern = menuWrapper->GetPattern<MenuWrapperPattern>();
    CHECK_NULL_VOID(menuWrapperPattern);
    auto preview = isShowHoverImage_ ? menuWrapperPattern->GetHoverImageFlexNode() : menuWrapperPattern->GetPreview();
    AnimationUtils::Animate(option, [menuNode, menuPosition, preview]() {
        CHECK_NULL_VOID(menuNode);
        auto menuContext = menuNode->GetRenderContext();
        if (menuContext) {
            menuContext->UpdateTransformScale(VectorF(1.0f, 1.0f));
            auto menuPattern = menuNode->GetPattern<MenuPattern>();
            if (GreatNotEqual(menuPattern->GetOriginMenuYForStack(), 0.0f)) {
                menuContext->UpdatePosition(
                    OffsetT<Dimension>(Dimension(menuPosition.GetX()),
                        Dimension(menuPattern->GetOriginMenuYForStack())));
                menuNode->GetGeometryNode()->SetMarginFrameOffset(OffsetF(menuPosition.GetX(),
                    menuPattern->GetOriginMenuYForStack()));
            }
            if (GreatNotEqual(menuPattern->GetOriginPreviewYForStack(), 0.0f)) {
                CHECK_NULL_VOID(preview);
                auto previewRenderContext = preview->GetRenderContext();
                CHECK_NULL_VOID(previewRenderContext);
                auto previewFrameOffsetX = preview->GetGeometryNode()->GetFrameOffset().GetX();
                previewRenderContext->UpdatePosition(
                    OffsetT<Dimension>(Dimension(previewFrameOffsetX),
                        Dimension(menuPattern->GetOriginPreviewYForStack())));
                preview->GetGeometryNode()->SetMarginFrameOffset(OffsetF(previewFrameOffsetX,
                    menuPattern->GetOriginPreviewYForStack()));
            }
        }
    });

    ShowStackMainMenuDisappearOpacityAnimation(menuNode, option);
}

void MenuPattern::ShowStackMainMenuDisappearOpacityAnimation(const RefPtr<FrameNode>& menuNode,
    AnimationOption& option) const
{
    option.SetCurve(Curves::FRICTION);
    option.SetDelay(STACK_MAIN_MENU_DISAPPEAR_DELAY);
    option.SetDuration(STACK_MENU_DISAPPEAR_DURATION);
    AnimationUtils::Animate(option, [menuNode]() {
        CHECK_NULL_VOID(menuNode);
        auto scroll = menuNode->GetFirstChild();
        CHECK_NULL_VOID(scroll);
        auto innerMenu = scroll->GetFirstChild();
        CHECK_NULL_VOID(innerMenu);
        auto innerMenuFrameNode = DynamicCast<FrameNode>(innerMenu);
        CHECK_NULL_VOID(innerMenuFrameNode);
        auto innerMenuContext = innerMenuFrameNode->GetRenderContext();
        CHECK_NULL_VOID(innerMenuContext);
        innerMenuContext->UpdateOpacity(1.0f);
    }, option.GetOnFinishEvent());
}

void MenuPattern::ShowStackMenuDisappearAnimation(const RefPtr<FrameNode>& menuNode,
    const RefPtr<FrameNode>& subMenuNode, AnimationOption& option) const
{
    CHECK_NULL_VOID(menuNode);
    auto menuNodeAccessibilityProps = menuNode->GetAccessibilityProperty<AccessibilityProperty>();
    CHECK_NULL_VOID(menuNodeAccessibilityProps);
    menuNodeAccessibilityProps->SetAccessibilityLevel(AccessibilityProperty::Level::AUTO);
    CHECK_NULL_VOID(subMenuNode);
    ShowStackSubMenuDisappearAnimation(menuNode, subMenuNode);
    ShowStackMainMenuDisappearAnimation(menuNode, subMenuNode, option);
}

void MenuPattern::ShowMenuDisappearAnimation()
{
    if (!Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_TWELVE)) {
        return;
    }
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto menuContext = host->GetRenderContext();
    MAIN_MENU_ANIMATION_CURVE->UpdateMinimumAmplitudeRatio(MINIMUM_AMPLITUDE_RATION);
    auto menuPosition = GetEndOffset();
    AnimationOption option = AnimationOption();
    option.SetCurve(MAIN_MENU_ANIMATION_CURVE);
    AnimationUtils::Animate(option, [menuContext, menuPosition]() {
        if (menuContext) {
            menuContext->UpdatePosition(
                OffsetT<Dimension>(Dimension(menuPosition.GetX()), Dimension(menuPosition.GetY())));
            menuContext->UpdateTransformScale(VectorF(MENU_ORIGINAL_SCALE, MENU_ORIGINAL_SCALE));
            menuContext->UpdateOpacity(0.0f);
        }
    });
}

void MenuPattern::UpdateClipPath(const RefPtr<LayoutWrapper>& dirty)
{
    auto layoutAlgorithmWrapper = DynamicCast<LayoutAlgorithmWrapper>(dirty->GetLayoutAlgorithm());
    CHECK_NULL_VOID(layoutAlgorithmWrapper);
    auto menuLayoutAlgorithm = DynamicCast<MenuLayoutAlgorithm>(layoutAlgorithmWrapper->GetLayoutAlgorithm());
    CHECK_NULL_VOID(menuLayoutAlgorithm);
    auto clipPath = menuLayoutAlgorithm->GetClipPath();
    auto host = dirty->GetHostNode();
    CHECK_NULL_VOID(host);
    auto paintProperty = host->GetPaintProperty<MenuPaintProperty>();
    CHECK_NULL_VOID(paintProperty);
    paintProperty->UpdateClipPath(clipPath);
}

bool MenuPattern::OnDirtyLayoutWrapperSwap(const RefPtr<LayoutWrapper>& dirty, const DirtySwapConfig& config)
{
    ShowPreviewMenuAnimation();
    ShowMenuAppearAnimation();
    ShowStackMenuAppearAnimation();
    auto host = GetHost();
    CHECK_NULL_RETURN(host, false);
    auto menuPosition = host->GetPaintRectOffset(false, true);
    SetEndOffset(menuPosition);
    if (config.skipMeasure || dirty->SkipMeasureContent()) {
        return false;
    }

    UpdateClipPath(dirty);
    auto pipeline = host->GetContextWithCheck();
    CHECK_NULL_RETURN(pipeline, false);
    auto theme = pipeline->GetTheme<SelectTheme>();
    CHECK_NULL_RETURN(theme, false);
    auto renderContext = dirty->GetHostNode()->GetRenderContext();
    CHECK_NULL_RETURN(renderContext, false);
    renderContext->UpdateClipShape(nullptr);
    renderContext->ResetClipShape();

    auto menuProp = DynamicCast<MenuLayoutProperty>(dirty->GetLayoutProperty());
    CHECK_NULL_RETURN(menuProp, false);
    BorderRadiusProperty radius;
    auto defaultRadius = Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_TWELVE) ?
        theme->GetMenuDefaultRadius() : theme->GetMenuBorderRadius();
    radius.SetRadius(defaultRadius);
    if (menuProp->GetBorderRadius().has_value()) {
        auto borderRadius = menuProp->GetBorderRadiusValue();
        auto geometryNode = dirty->GetGeometryNode();
        CHECK_NULL_RETURN(geometryNode, false);
        auto idealSize = geometryNode->GetMarginFrameSize();
        radius = CalcIdealBorderRadius(borderRadius, idealSize);
        UpdateBorderRadius(dirty->GetHostNode(), radius);
    }
    auto menuWrapper = GetMenuWrapper();
    DragAnimationHelper::ShowGatherAnimationWithMenu(menuWrapper);
    return true;
}

BorderRadiusProperty MenuPattern::CalcIdealBorderRadius(const BorderRadiusProperty& borderRadius, const SizeF& menuSize)
{
    Dimension defaultDimension(0);
    BorderRadiusProperty radius = { defaultDimension, defaultDimension, defaultDimension, defaultDimension };
    auto host = GetHost();
    CHECK_NULL_RETURN(host, radius);
    auto pipeline = host->GetContextWithCheck();
    CHECK_NULL_RETURN(pipeline, radius);
    auto theme = pipeline->GetTheme<SelectTheme>();
    CHECK_NULL_RETURN(theme, radius);
    auto defaultRadius = Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_TWELVE) ?
        theme->GetMenuDefaultRadius() : theme->GetMenuBorderRadius();
    radius.SetRadius(defaultRadius);
    auto radiusTopLeft = borderRadius.radiusTopLeft.value_or(Dimension()).ConvertToPx();
    auto radiusTopRight = borderRadius.radiusTopRight.value_or(Dimension()).ConvertToPx();
    auto radiusBottomLeft = borderRadius.radiusBottomLeft.value_or(Dimension()).ConvertToPx();
    auto radiusBottomRight = borderRadius.radiusBottomRight.value_or(Dimension()).ConvertToPx();
    auto maxRadiusW = std::max(radiusTopLeft + radiusTopRight, radiusBottomLeft + radiusBottomRight);
    auto maxRadiusH = std::max(radiusTopLeft + radiusBottomLeft, radiusTopRight + radiusBottomRight);
    if (Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_TWELVE)) {
        if (LessOrEqual(maxRadiusW, menuSize.Width()) && LessOrEqual(maxRadiusH, menuSize.Height())) {
            radius = borderRadius;
        }
    } else {
        if (LessNotEqual(maxRadiusW, menuSize.Width())) {
            radius = borderRadius;
        }
    }

    return radius;
}

void MenuPattern::UpdateBorderRadius(const RefPtr<FrameNode>& menuNode, const BorderRadiusProperty& borderRadius)
{
    CHECK_NULL_VOID(menuNode);
    auto menuRenderContext = menuNode->GetRenderContext();
    CHECK_NULL_VOID(menuRenderContext);
    menuRenderContext->UpdateBorderRadius(borderRadius);
    if (Container::GreatOrEqualAPIVersion(PlatformVersion::VERSION_ELEVEN)) {
        menuRenderContext->UpdateOuterBorderRadius(borderRadius);
    }
    auto node = menuNode->GetChildren().front();
    CHECK_NULL_VOID(node);
    auto scrollNode = AceType::DynamicCast<FrameNode>(node);
    CHECK_NULL_VOID(scrollNode);
    auto scrollRenderContext = scrollNode->GetRenderContext();
    CHECK_NULL_VOID(scrollRenderContext);
    scrollRenderContext->UpdateBorderRadius(borderRadius);
}

void InnerMenuPattern::UpdateBorderRadius(const RefPtr<FrameNode>& menuNode, const BorderRadiusProperty& borderRadius)
{
    CHECK_NULL_VOID(menuNode);
    auto menuRenderContext = menuNode->GetRenderContext();
    CHECK_NULL_VOID(menuRenderContext);
    menuRenderContext->UpdateBorderRadius(borderRadius);
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
        for (int32_t index = static_cast<int32_t>(currentNode->GetChildren().size()) - 1; index >= 0; index--) {
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
    Shadow shadow;
    if (GetShadowFromTheme(ShadowStyle::OuterDefaultSM, shadow)) {
        host->GetRenderContext()->UpdateBackShadow(shadow);
    }
}

void InnerMenuPattern::ApplyMultiMenuTheme()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    Shadow shadow;
    if (GetShadowFromTheme(ShadowStyle::None, shadow)) {
        host->GetRenderContext()->UpdateBackShadow(shadow);
    }
}

void MenuPattern::OnColorConfigurationUpdate()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto pipeline = host->GetContextWithCheck();
    CHECK_NULL_VOID(pipeline);

    auto menuTheme = pipeline->GetTheme<SelectTheme>();
    CHECK_NULL_VOID(menuTheme);

    auto menuPattern = host->GetPattern<MenuPattern>();
    CHECK_NULL_VOID(menuPattern);

    auto renderContext = host->GetRenderContext();
    if (Container::LessThanAPIVersion(PlatformVersion::VERSION_ELEVEN) || !renderContext->IsUniRenderEnabled()
        || menuTheme->GetMenuBlendBgColor()) {
        if (!isDisableMenuBgColorByUser_) {
            renderContext->UpdateBackgroundColor(menuTheme->GetBackgroundColor());
        }
    } else {
        renderContext->UpdateBackBlurStyle(renderContext->GetBackBlurStyle());
    }

    auto optionNode = menuPattern->GetOptions();
    for (const auto& child : optionNode) {
        auto optionsPattern = child->GetPattern<MenuItemPattern>();
        optionsPattern->SetFontColor(menuTheme->GetFontColor());

        child->MarkModifyDone();
        child->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
    }
    host->SetNeedCallChildrenUpdate(false);

    auto menuLayoutProperty = GetLayoutProperty<MenuLayoutProperty>();
    CHECK_NULL_VOID(menuLayoutProperty);
    if (SystemProperties::ConfigChangePerform() && !menuLayoutProperty->GetFontColorSetByUser().value_or(false)) {
        auto themeFontColor = menuTheme->GetMenuFontColor();
        menuLayoutProperty->UpdateFontColor(themeFontColor);
        host->MarkModifyDone();
        host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    }
}

void MenuPattern::InitPanEvent(const RefPtr<GestureEventHub>& gestureHub)
{
    CHECK_NULL_VOID(gestureHub);
    auto actionEndTask = [weak = WeakClaim(this)](const GestureEvent& info) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        if (pattern->IsMenuScrollable()) {
            return;
        }
        auto offsetX = static_cast<float>(info.GetOffsetX());
        auto offsetY = static_cast<float>(info.GetOffsetY());
        auto offsetPerSecondX = info.GetVelocity().GetOffsetPerSecond().GetX();
        auto offsetPerSecondY = info.GetVelocity().GetOffsetPerSecond().GetY();
        auto velocity =
            static_cast<float>(std::sqrt(offsetPerSecondX * offsetPerSecondX + offsetPerSecondY * offsetPerSecondY));
        pattern->HandleDragEnd(offsetX, offsetY, velocity);
    };
    auto actionScrollEndTask = [weak = WeakClaim(this)](const GestureEvent& info) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        if (pattern->IsMenuScrollable()) {
            return;
        }
        auto offsetX = static_cast<float>(info.GetOffsetX());
        auto offsetY = static_cast<float>(info.GetOffsetY());
        auto offsetPerSecondX = info.GetVelocity().GetOffsetPerSecond().GetX();
        auto offsetPerSecondY = info.GetVelocity().GetOffsetPerSecond().GetY();
        auto velocity =
            static_cast<float>(std::sqrt(offsetPerSecondX * offsetPerSecondX + offsetPerSecondY * offsetPerSecondY));
        pattern->HandleScrollDragEnd(offsetX, offsetY, velocity);
    };
    PanDirection panDirection;
    panDirection.type = PanDirection::ALL;
    auto panEvent = MakeRefPtr<PanEvent>(nullptr, nullptr, std::move(actionEndTask), nullptr);
    PanDistanceMap distanceMap = { { SourceTool::UNKNOWN, DEFAULT_PAN_DISTANCE.ConvertToPx() },
        { SourceTool::PEN, DEFAULT_PEN_PAN_DISTANCE.ConvertToPx() } };
    gestureHub->AddPanEvent(panEvent, panDirection, 1, distanceMap);
    gestureHub->AddPreviewMenuHandleDragEnd(std::move(actionScrollEndTask));
}

void MenuPattern::HandleDragEnd(float offsetX, float offsetY, float velocity)
{
    if ((LessOrEqual(std::abs(offsetY), std::abs(offsetX)) || LessOrEqual(offsetY, 0.0f)) &&
        LessOrEqual(velocity, PAN_MAX_VELOCITY)) {
        return;
    }
    auto menuWrapper = GetMenuWrapper();
    CHECK_NULL_VOID(menuWrapper);
    auto wrapperPattern = menuWrapper->GetPattern<MenuWrapperPattern>();
    CHECK_NULL_VOID(wrapperPattern);
    TAG_LOGI(AceLogTag::ACE_DRAG, "will hide menu.");
    wrapperPattern->HideMenu(HideMenuType::MENU_DRAG_END);
}

void MenuPattern::HandleScrollDragEnd(float offsetX, float offsetY, float velocity)
{
    if ((LessOrEqual(std::abs(offsetY), std::abs(offsetX)) || !NearZero(offsetY)) &&
        LessOrEqual(velocity, PAN_MAX_VELOCITY)) {
        return;
    }
    auto menuWrapper = GetMenuWrapper();
    CHECK_NULL_VOID(menuWrapper);
    auto wrapperPattern = menuWrapper->GetPattern<MenuWrapperPattern>();
    CHECK_NULL_VOID(wrapperPattern);
    TAG_LOGI(AceLogTag::ACE_DRAG, "will hide menu.");
    wrapperPattern->HideMenu(HideMenuType::SCROLL_DRAG_END);
}

void MenuPattern::DumpInfo()
{
    DumpLog::GetInstance().AddDesc(
        std::string("MenuType: ").append(std::to_string(static_cast<int32_t>(GetMenuType()))));
}

float MenuPattern::GetSelectMenuWidth()
{
    auto minSelectWidth = MIN_SELECT_MENU_WIDTH.ConvertToPx();
    RefPtr<GridColumnInfo> columnInfo = GridSystemManager::GetInstance().GetInfoByType(GridColumnType::MENU);
    CHECK_NULL_RETURN(columnInfo, minSelectWidth);
    auto parent = columnInfo->GetParent();
    CHECK_NULL_RETURN(parent, minSelectWidth);
    parent->BuildColumnWidth();
    auto defaultWidth = static_cast<float>(columnInfo->GetWidth(COLUMN_NUM));
    float finalWidth = minSelectWidth;

    if (IsWidthModifiedBySelect()) {
        auto menuLayoutProperty = GetLayoutProperty<MenuLayoutProperty>();
        auto selectmodifiedwidth = menuLayoutProperty->GetSelectMenuModifiedWidth();
        finalWidth = selectmodifiedwidth.value();
    } else {
        finalWidth = defaultWidth;
    }

    if (LessNotEqual(finalWidth, minSelectWidth)) {
        finalWidth = defaultWidth;
    }

    return finalWidth;
}

void MenuPattern::OnItemPressed(const RefPtr<UINode>& parent, int32_t index, bool press, bool hover)
{
    CHECK_NULL_VOID(parent);
    if (parent->GetTag() == V2::MENU_ITEM_GROUP_ETS_TAG) {
        auto pattern = DynamicCast<FrameNode>(parent)->GetPattern<MenuItemGroupPattern>();
        CHECK_NULL_VOID(pattern);
        pattern->OnIntItemPressed(index, press);
    }
    HandleNextPressed(parent, index, press, hover);
    HandlePrevPressed(parent, index, press);
}

void MenuPattern::HandleNextPressed(const RefPtr<UINode>& parent, int32_t index, bool press, bool hover)
{
    CHECK_NULL_VOID(parent);
    RefPtr<UINode> nextNode = nullptr;
    const auto childrenSize = parent->GetChildren().size();
    auto syntaxNode = GetSyntaxNode(parent);
    if (index == static_cast<int32_t>(childrenSize - 1) && syntaxNode) {
        nextNode = GetForEachMenuItem(syntaxNode, true);
    } else if (parent->GetTag() == V2::JS_IF_ELSE_ETS_TAG && index == static_cast<int32_t>(childrenSize - 1)) {
        nextNode = GetOutsideForEachMenuItem(parent, true);
    } else {
        if (index >= static_cast<int32_t>(childrenSize - 1)) {
            return;
        }
        nextNode = parent->GetChildAtIndex(index + 1);
    }
    CHECK_NULL_VOID(nextNode);
    if (nextNode->GetTag() == V2::JS_FOR_EACH_ETS_TAG) {
        nextNode = GetForEachMenuItem(nextNode, true);
    }
    CHECK_NULL_VOID(nextNode);
    if (nextNode->GetTag() == V2::JS_IF_ELSE_ETS_TAG) {
        nextNode = GetIfElseMenuItem(nextNode, true);
    }
    CHECK_NULL_VOID(nextNode);
    if (nextNode->GetTag() == V2::MENU_ITEM_GROUP_ETS_TAG) {
        auto pattern = DynamicCast<FrameNode>(nextNode)->GetPattern<MenuItemGroupPattern>();
        CHECK_NULL_VOID(pattern);
        pattern->OnExtItemPressed(press, true);
    }
    if (nextNode->GetTag() == V2::MENU_ITEM_ETS_TAG) {
        auto props = DynamicCast<FrameNode>(nextNode)->GetPaintProperty<MenuItemPaintProperty>();
        CHECK_NULL_VOID(props);
        // need save needDivider property due to some items shoud not have divide in not pressed state
        hover ? props->UpdateHover(press) : props->UpdatePress(press);
        nextNode->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
    }
}

void MenuPattern::HandlePrevPressed(const RefPtr<UINode>& parent, int32_t index, bool press)
{
    CHECK_NULL_VOID(parent);
    RefPtr<UINode> prevNode = nullptr;
    if (index > 0) {
        prevNode = parent->GetChildAtIndex(index - 1);
        CHECK_NULL_VOID(prevNode);
        if (prevNode->GetTag() == V2::JS_FOR_EACH_ETS_TAG) {
            prevNode = GetForEachMenuItem(prevNode, false);
        }
    } else {
        auto syntaxNode = GetSyntaxNode(parent);
        auto grandParent = parent->GetParent();
        CHECK_NULL_VOID(grandParent);
        if (grandParent->GetChildIndex(parent) == 0 && syntaxNode) {
            prevNode = GetForEachMenuItem(syntaxNode, false);
        }
        bool matchFirstItemInIfElse = parent->GetTag() == V2::MENU_ITEM_GROUP_ETS_TAG &&
            grandParent->GetChildIndex(parent) == 0 &&
            grandParent->GetTag() == V2::JS_IF_ELSE_ETS_TAG;
        if (matchFirstItemInIfElse) { // the first item in first group in ifElse
            prevNode = GetOutsideForEachMenuItem(grandParent, false);
        }
        bool notFirstGroupInMenu = grandParent->GetChildIndex(parent) > 0 &&
            parent->GetTag() == V2::MENU_ITEM_GROUP_ETS_TAG;
        if (notFirstGroupInMenu) {
            prevNode = GetOutsideForEachMenuItem(parent, false);
        }
    }
    CHECK_NULL_VOID(prevNode);
    if (prevNode->GetTag() == V2::JS_IF_ELSE_ETS_TAG) {
        prevNode = GetIfElseMenuItem(prevNode, false);
    }
    CHECK_NULL_VOID(prevNode);
    if (prevNode->GetTag() == V2::MENU_ITEM_GROUP_ETS_TAG) {
        auto preFrameNode = DynamicCast<FrameNode>(prevNode);
        CHECK_NULL_VOID(preFrameNode);
        auto pattern = preFrameNode->GetPattern<MenuItemGroupPattern>();
        CHECK_NULL_VOID(pattern);
        pattern->OnExtItemPressed(press, false);
    }
}

RefPtr<UINode> MenuPattern::GetForEachMenuItem(const RefPtr<UINode>& parent, bool next)
{
    CHECK_NULL_RETURN(parent, nullptr);
    if (parent->GetTag() == V2::JS_FOR_EACH_ETS_TAG) {
        auto nextSyntax = next ? parent->GetFirstChild() : parent->GetLastChild();
        CHECK_NULL_RETURN(nextSyntax, nullptr);
        return next ? nextSyntax->GetFirstChild() : nextSyntax->GetLastChild();
    }
    auto node = GetSyntaxNode(parent);
    CHECK_NULL_RETURN(node, nullptr);
    auto forEachNode = AceType::DynamicCast<UINode>(node->GetParent());
    if (node->GetTag() == V2::JS_SYNTAX_ITEM_ETS_TAG) {
        CHECK_NULL_RETURN(forEachNode, nullptr);
        auto syntIndex = forEachNode->GetChildIndex(node);
        const auto& children = forEachNode->GetChildren();
        if (next) {
            if (syntIndex < static_cast<int32_t>(children.size() - 1)) { // next is inside forEach
                auto nextSyntax = forEachNode->GetChildAtIndex(syntIndex + 1);
                CHECK_NULL_RETURN(nextSyntax, nullptr);
                return nextSyntax->GetFirstChild();
            } else { // next is after forEach
                return GetOutsideForEachMenuItem(forEachNode, true);
            }
        } else {
            if (syntIndex > 0) { // prev is inside forEach
                auto prevSyntax = forEachNode->GetChildAtIndex(syntIndex - 1);
                CHECK_NULL_RETURN(prevSyntax, nullptr);
                return prevSyntax->GetLastChild();
            } else { // prev is before forEach
                return GetOutsideForEachMenuItem(forEachNode, false);
            }
        }
    }
    return nullptr;
}

RefPtr<UINode> MenuPattern::GetOutsideForEachMenuItem(const RefPtr<UINode>& forEachNode, bool next)
{
    auto parentForEachNode = AceType::DynamicCast<UINode>(forEachNode->GetParent());
    CHECK_NULL_RETURN(parentForEachNode, nullptr);
    auto forEachIndex = parentForEachNode->GetChildIndex(forEachNode);
    int32_t shift = next ? 1 : -1;
    const auto& children = parentForEachNode->GetChildren();
    if ((forEachIndex + shift) >= 0 && (forEachIndex + shift) <= static_cast<int32_t>(children.size() - 1)) {
        return parentForEachNode->GetChildAtIndex(forEachIndex + shift);
    } else {
        return nullptr;
    }
}

RefPtr<UINode> MenuPattern::GetSyntaxNode(const RefPtr<UINode>& parent)
{
    CHECK_NULL_RETURN(parent, nullptr);
    auto node = parent;
    while (node) {
        if (node->GetTag() == V2::MENU_ETS_TAG) {
            return nullptr;
        }
        if (node->GetTag() == V2::JS_SYNTAX_ITEM_ETS_TAG) {
            return node;
        }
        node = node->GetParent();
    }
    return nullptr;
}

RefPtr<UINode> MenuPattern::GetIfElseMenuItem(const RefPtr<UINode>& parent, bool next)
{
    CHECK_NULL_RETURN(parent, nullptr);
    auto nextItem = next ? parent->GetFirstChild() : parent->GetLastChild();
    return nextItem;
}

bool MenuPattern::IsMenuScrollable() const
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, false);
    auto firstChild = DynamicCast<FrameNode>(host->GetChildAtIndex(0));
    CHECK_NULL_RETURN(firstChild, false);
    if (firstChild->GetTag() == V2::SCROLL_ETS_TAG) {
        auto scrollPattern = firstChild->GetPattern<ScrollPattern>();
        CHECK_NULL_RETURN(scrollPattern, false);
        return scrollPattern->IsScrollable() && Positive(scrollPattern->GetScrollableDistance());
    }
    return false;
}

void MenuPattern::DumpInfo(std::unique_ptr<JsonValue>& json)
{
    json->Put("MenuType", static_cast<int32_t>(GetMenuType()));
}

OffsetF MenuPattern::GetPreviewMenuAnimationOffset(
    const OffsetF& previewCenter, const SizeF& previewSize, float scale) const
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, OffsetF());
    auto geometryNode = host->GetGeometryNode();
    CHECK_NULL_RETURN(geometryNode, OffsetF());
    auto size = geometryNode->GetFrameSize();
    auto menuPattern = host->GetPattern<MenuPattern>();
    CHECK_NULL_RETURN(menuPattern, OffsetF());
    auto placement = menuPattern->GetLastPlacement().value_or(Placement::NONE);

    auto space = TARGET_SPACE.ConvertToPx();
    auto menuWidth = size.Width();
    auto menuHeight = size.Height();

    auto top = previewCenter.GetY() - previewSize.Height() * scale / HALF;
    auto bottom = previewCenter.GetY() + previewSize.Height() * scale / HALF;
    auto left = previewCenter.GetX() - previewSize.Width() * scale / HALF;
    auto right = previewCenter.GetX() + previewSize.Width() * scale / HALF;

    switch (placement) {
        case Placement::TOP:
            return OffsetF(previewCenter.GetX() - menuWidth / HALF, top - space - menuHeight);
        case Placement::TOP_LEFT:
            return OffsetF(left, top - space - menuHeight);
        case Placement::TOP_RIGHT:
            return OffsetF(right - menuWidth, top - space - menuHeight);
        case Placement::BOTTOM:
            return OffsetF(previewCenter.GetX() - menuWidth / HALF, bottom + space);
        case Placement::BOTTOM_LEFT:
            return OffsetF(left, bottom + space);
        case Placement::BOTTOM_RIGHT:
            return OffsetF(right - menuWidth, bottom + space);
        case Placement::LEFT:
            return OffsetF(left - space - menuWidth, previewCenter.GetY() - menuHeight / HALF);
        case Placement::LEFT_TOP:
            return OffsetF(left - space - menuWidth, top);
        case Placement::LEFT_BOTTOM:
            return OffsetF(left - space - menuWidth, bottom - menuHeight);
        case Placement::RIGHT:
            return OffsetF(right + space, previewCenter.GetY() - menuHeight / HALF);
        case Placement::RIGHT_TOP:
            return OffsetF(right + space, top);
        case Placement::RIGHT_BOTTOM:
            return OffsetF(right + space, bottom - menuHeight);
        default:
            return OffsetF(left, bottom + space);
    }
}

void MenuPattern::InitPreviewMenuAnimationInfo(const RefPtr<MenuTheme>& menuTheme)
{
    CHECK_NULL_VOID(menuTheme);

    auto menuWrapper = GetMenuWrapper();
    CHECK_NULL_VOID(menuWrapper);
    auto menuWrapperPattern = menuWrapper->GetPattern<MenuWrapperPattern>();
    CHECK_NULL_VOID(menuWrapperPattern);
    auto hasTransition = menuWrapperPattern->HasTransitionEffect() || menuWrapperPattern->HasPreviewTransitionEffect();
    if (hasTransition) {
        disappearOffset_ = endOffset_;
        return;
    }

    auto preview = menuWrapperPattern->GetPreview();
    CHECK_NULL_VOID(preview);
    auto previewGeometryNode = preview->GetGeometryNode();
    CHECK_NULL_VOID(previewGeometryNode);
    auto previewSize = previewGeometryNode->GetMarginFrameSize();

    auto scaleBefore = GetPreviewBeforeAnimationScale();
    auto appearScale = LessNotEqual(scaleBefore, 0.0) ? menuTheme->GetPreviewBeforeAnimationScale() : scaleBefore;
    auto disappearScale = 1.0;

    if (previewMode_ == MenuPreviewMode::IMAGE) {
        auto imagePattern = preview->GetPattern<ImagePattern>();
        CHECK_NULL_VOID(imagePattern);
        auto imageRawSize = imagePattern->GetRawImageSize();
        auto isOriginSizeGreater = previewSize.IsPositive() && imageRawSize.IsPositive() && imageRawSize > previewSize;
        if (isOriginSizeGreater) {
            appearScale *= imageRawSize.Width() / previewSize.Width();
        }

        disappearScale = targetSize_.Width() / previewSize.Width();
    }

    OffsetF previewCenter = GetPreviewOriginOffset() + OffsetF(previewSize.Width() / HALF, previewSize.Height() / HALF);
    if (isShowHoverImage_) {
        auto previewPattern = preview->GetPattern<MenuPreviewPattern>();
        CHECK_NULL_VOID(previewPattern);
        appearScale = previewPattern->GetHoverImageScaleTo();
        appearScale = LessOrEqual(appearScale, 0.0) ? menuTheme->GetPreviewBeforeAnimationScale() : appearScale;

        disappearScale = previewPattern->GetHoverImageScaleFrom();
        disappearScale =
            LessNotEqual(disappearScale, 0.0) ? menuTheme->GetPreviewBeforeAnimationScale() : disappearScale;

        previewSize =
            SizeF(previewPattern->GetHoverImageAfterScaleWidth(), previewPattern->GetHoverImageAfterScaleHeight());
        auto clipEndWidth = previewPattern->GetStackAfterScaleActualWidth();
        auto clipEndHeight = previewPattern->GetStackAfterScaleActualHeight();
        previewCenter = GetPreviewOriginOffset() + OffsetF(clipEndWidth / HALF, clipEndHeight / HALF);
    }

    originOffset_ = GetPreviewMenuAnimationOffset(previewCenter, previewSize, appearScale);
    disappearOffset_ = GetPreviewMenuAnimationOffset(previewCenter, previewSize, disappearScale);
}

void MenuPattern::UpdateMenuPathParams(std::optional<MenuPathParams> pathParams)
{
    pathParams_ = pathParams;
    auto wrapperNode = GetMenuWrapper();
    CHECK_NULL_VOID(wrapperNode);
    auto pattern = wrapperNode->GetPattern<MenuWrapperPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->RequestPathRender();
}

void MenuPattern::OnDetachFromMainTree()
{
    auto wrapperNode = GetMenuWrapper();
    CHECK_NULL_VOID(wrapperNode);
    auto pattern = wrapperNode->GetPattern<MenuWrapperPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->RequestPathRender();
}

float MenuPattern::GetSelectMenuWidthFromTheme() const
{
    auto minSelectWidth = MIN_SELECT_MENU_WIDTH.ConvertToPx();
    RefPtr<GridColumnInfo> columnInfo = GridSystemManager::GetInstance().GetInfoByType(GridColumnType::MENU);
    CHECK_NULL_RETURN(columnInfo, minSelectWidth);
    auto parent = columnInfo->GetParent();
    CHECK_NULL_RETURN(parent, minSelectWidth);
    parent->BuildColumnWidth();
    auto defaultWidth = static_cast<float>(columnInfo->GetWidth(COLUMN_NUM));
    auto host = GetHost();
    CHECK_NULL_RETURN(host, minSelectWidth);
    auto context = host->GetContext();
    CHECK_NULL_RETURN(context, minSelectWidth);
    auto theme = context->GetTheme<SelectTheme>();
    CHECK_NULL_RETURN(theme, minSelectWidth);
    float finalWidth = (theme->GetMenuNormalWidth() + OPTION_MARGIN).ConvertToPx();
    if (LessNotEqual(finalWidth, minSelectWidth)) {
        finalWidth = defaultWidth;
    }
    return finalWidth;
}

bool MenuPattern::IsSelectOverlayDefaultModeRightClickMenu()
{
    CHECK_NULL_RETURN(IsSelectOverlayRightClickMenu(), false);
    auto menuWrapper = GetMenuWrapper();
    CHECK_NULL_RETURN(menuWrapper, false);
    auto menuWrapperPattern = menuWrapper->GetPattern<MenuWrapperPattern>();
    CHECK_NULL_RETURN(menuWrapperPattern, false);
    return !menuWrapperPattern->GetIsSelectOverlaySubWindowWrapper();
}
} // namespace OHOS::Ace::NG
