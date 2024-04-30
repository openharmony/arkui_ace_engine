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
#include "core/components_ng/pattern/menu/menu_item/menu_item_model_ng.h"

#include <memory>
#include <optional>

#include "base/geometry/ng/offset_t.h"
#include "base/log/log.h"
#include "base/memory/ace_type.h"
#include "base/utils/utils.h"
#include "base/utils/system_properties.h"
#include "core/common/recorder/event_recorder.h"
#include "core/common/recorder/node_data_cache.h"
#include "core/components/common/properties/shadow_config.h"
#include "core/components/select/select_theme.h"
#include "core/components/theme/icon_theme.h"
#include "core/components/theme/shadow_theme.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/image/image_pattern.h"
#include "core/components_ng/pattern/menu/menu_item/menu_item_event_hub.h"
#include "core/components_ng/pattern/menu/menu_layout_property.h"
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
        textProperty->UpdateFontWeight(FontWeight::REGULAR);
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
    std::vector<std::string> emptyFontfamily;
    if (fontFamilies.has_value()) {
        textProperty->UpdateFontFamily(fontFamilies.value());
    } else if (menuProperty && menuProperty->GetFontFamily().has_value()) {
        textProperty->UpdateFontFamily(menuProperty->GetFontFamily().value());
    } else {
        textProperty->UpdateFontFamily(emptyFontfamily);
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

    RefPtr<FrameNode> rightRow =
        host->GetChildAtIndex(1) ? AceType::DynamicCast<FrameNode>(host->GetChildAtIndex(1)) : nullptr;
    CHECK_NULL_VOID(rightRow);
    UpdateText(rightRow, menuProperty, true);
    UpdateIcon(rightRow, false);
    AddExpandIcon(rightRow, menuProperty);
    if (IsDisabled()) {
        UpdateDisabledStyle();
    }
    SetAccessibilityAction();

    host->GetRenderContext()->SetClipToBounds(true);

    InitFocusEvent();
    RegisterOnKeyEvent();
    RegisterOnTouch();
    RegisterOnHover();
    RegisterOnClick();

    auto layoutProp = host->GetLayoutProperty();
    CHECK_NULL_VOID(layoutProp);
    if (!layoutProp->GetMarginProperty()) {
        auto pipeline = PipelineBase::GetCurrentContext();
        CHECK_NULL_VOID(pipeline);
        auto theme = pipeline->GetTheme<SelectTheme>();
        CHECK_NULL_VOID(theme);
        MarginProperty margin;
        auto defaultMargin = CalcLength(Dimension(0.0_vp));
        auto verticalMargin = CalcLength(theme->GetMenuItemTopBottomMargin());
        margin.SetEdges(defaultMargin, defaultMargin, verticalMargin, verticalMargin);
        layoutProp->UpdateMargin(margin);
    }
}

void MenuItemPattern::InitFocusEvent()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto focusHub = host->GetOrCreateFocusHub();
    CHECK_NULL_VOID(focusHub);
    auto focusTask = [weak = WeakClaim(this)]() {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        pattern->HandleFocusEvent();
    };
    focusHub->SetOnFocusInternal(focusTask);

    auto blurTask = [weak = WeakClaim(this)]() {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        pattern->HandleBlurEvent();
    };
    focusHub->SetOnBlurInternal(blurTask);
}

bool GetShadowFromTheme(ShadowStyle shadowStyle, Shadow& shadow)
{
    auto colorMode = SystemProperties::GetColorMode();
    if (shadowStyle == ShadowStyle::None) {
        return true;
    }

    auto pipelineContext = PipelineContext::GetCurrentContext();
    CHECK_NULL_RETURN(pipelineContext, false);

    auto shadowTheme = pipelineContext->GetTheme<ShadowTheme>();
    CHECK_NULL_RETURN(shadowTheme, false);

    shadow = shadowTheme->GetShadow(shadowStyle, colorMode);
    return true;
}

void MenuItemPattern::HandleFocusEvent()
{
    isFocused_ = true;
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto renderContext = host->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto theme = pipeline->GetTheme<SelectTheme>();
    CHECK_NULL_VOID(theme);

    if (!renderContext->HasBackgroundColor()) {
        renderContext->UpdateBackgroundColor(theme->GetMenuItemFocusedBgColor());
        isFocusBGColorSet_ = true;
    }
    if (!renderContext->HasBackShadow()) {
        ShadowStyle shadowStyle = static_cast<ShadowStyle>(theme->GetMenuItemFocusedShadowStyle());
        if (shadowStyle != ShadowStyle::None) {
            Shadow shadow;
            if (!GetShadowFromTheme(shadowStyle, shadow)) {
                shadow = Shadow::CreateShadow(shadowStyle);
            }
            renderContext->UpdateBackShadow(shadow);
            isFocusShadowSet_ = true;
        }
    }

    RefPtr<FrameNode> leftRow =
        host->GetChildAtIndex(0) ? AceType::DynamicCast<FrameNode>(host->GetChildAtIndex(0)) : nullptr;
    CHECK_NULL_VOID(leftRow);
    auto menuNode = GetMenu();
    auto menuProperty = menuNode ? menuNode->GetLayoutProperty<MenuLayoutProperty>() : nullptr;
    UpdateText(leftRow, menuProperty, false);
}

void MenuItemPattern::HandleBlurEvent()
{
    isFocused_ = false;
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto renderContext = host->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto theme = pipeline->GetTheme<SelectTheme>();
    CHECK_NULL_VOID(theme);
    if (isFocusBGColorSet_) {
        renderContext->ResetBackgroundColor();
        renderContext->SetBackgroundColor(theme->GetBackgroundColor().GetValue());
        isFocusBGColorSet_ = false;
    }
    if (isFocusShadowSet_) {
        renderContext->ResetBackShadow();
        renderContext->SetShadowRadius(0.0f);
        isFocusShadowSet_ = false;
    }

    RefPtr<FrameNode> leftRow =
        host->GetChildAtIndex(0) ? AceType::DynamicCast<FrameNode>(host->GetChildAtIndex(0)) : nullptr;
    CHECK_NULL_VOID(leftRow);
    auto menuNode = GetMenu();
    auto menuProperty = menuNode ? menuNode->GetLayoutProperty<MenuLayoutProperty>() : nullptr;
    UpdateText(leftRow, menuProperty, false);
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
                return menuNode;
            }
        }
        parent = parent->GetParent();
    }
    return menuNode;
}

RefPtr<MenuPattern> MenuItemPattern::GetMenuPattern(bool needTopMenu)
{
    auto menu = GetMenu(true);
    if (!menu) {
        return nullptr;
    }
    return menu->GetPattern<MenuPattern>();
}

void MenuItemPattern::ShowSubMenu()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto buildFunc = GetSubBuilder();
    if (!buildFunc || isSubMenuShowed_) {
        return;
    }
    // Hide SubMenu of parent Menu node
    auto parentMenu = GetMenu();
    CHECK_NULL_VOID(parentMenu);
    // parentMenu no need focus
    auto menuNode = GetMenu(true);
    CHECK_NULL_VOID(menuNode);
    auto layoutProps = parentMenu->GetLayoutProperty<MenuLayoutProperty>();
    CHECK_NULL_VOID(layoutProps);

    auto itemProps = host->GetLayoutProperty<MenuItemLayoutProperty>();
    CHECK_NULL_VOID(itemProps);
    auto hasFurtherExpand = itemProps->GetHasFurtherExpand().value_or(true);
    auto expandingMode = layoutProps->GetExpandingMode().value_or(SubMenuExpandingMode::SIDE);
    if (expandingMode == SubMenuExpandingMode::EMBEDDED) {
        ShowEmbeddedSubMenu(hasFurtherExpand);
        return;
    }

    auto menuPattern = menuNode->GetPattern<MenuPattern>();
    CHECK_NULL_VOID(menuPattern);
    menuPattern->FocusViewHide();
    auto parentMenuPattern = parentMenu->GetPattern<MenuPattern>();
    CHECK_NULL_VOID(parentMenuPattern);
    HideSubMenu();
    isSubMenuShowed_ = true;
    buildFunc();
    auto customNode = NG::ViewStackProcessor::GetInstance()->Finish();
    bool isSelectOverlayMenu = IsSelectOverlayMenu();
    MenuParam param;
    param.isShowInSubWindow = layoutProps->GetShowInSubWindowValue(false);
    auto focusMenuRenderContext = menuNode->GetRenderContext();
    CHECK_NULL_VOID(focusMenuRenderContext);
    if (focusMenuRenderContext->GetBackBlurStyle().has_value()) {
        auto focusMenuBlurStyle = focusMenuRenderContext->GetBackBlurStyle();
        param.backgroundBlurStyle = static_cast<int>(focusMenuBlurStyle->blurStyle);
    }
    param.type = isSelectOverlayMenu ? MenuType::SELECT_OVERLAY_SUB_MENU : MenuType::SUB_MENU;
    ParseMenuRadius(param);
    auto subMenu = MenuView::Create(
        expandingMode == SubMenuExpandingMode::STACK ? BuildStackSubMenu(customNode) : customNode,
        host->GetId(), host->GetTag(), param);
    CHECK_NULL_VOID(subMenu);
    ShowSubMenuHelper(subMenu);
    parentMenuPattern->SetShowedSubMenu(subMenu);
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
    subMenu->MountToParent(menuWrapper);
    OffsetF offset = GetSubMenuPosition(host);
    auto menuProps = subMenu->GetLayoutProperty<MenuLayoutProperty>();
    CHECK_NULL_VOID(menuProps);
    menuProps->UpdateMenuOffset(offset);
    menuWrapper->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF_AND_CHILD);
    RegisterWrapperMouseEvent();
    // select overlay menu no need focus
    if (!isSelectOverlayMenu) {
        menuPattern->FocusViewShow();
    }
}

void MenuItemPattern::ShowEmbeddedSubMenu(bool hasFurtherExpand)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    if (!hasFurtherExpand) {
        CloseMenu();
        return;
    }
    isExpanded_ = !isExpanded_;
    UpdateExpandableArea();
    host->MarkModifyDone();
    host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
}

void MenuItemPattern::HideSubMenu()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto parentMenu = GetMenu();
    CHECK_NULL_VOID(parentMenu);
    auto parentMenuPattern = parentMenu->GetPattern<MenuPattern>();
    CHECK_NULL_VOID(parentMenuPattern);

    auto showedSubMenu = parentMenuPattern->GetShowedSubMenu();
    if (showedSubMenu) {
        auto showedSubMenuPattern = showedSubMenu->GetPattern<MenuPattern>();
        CHECK_NULL_VOID(showedSubMenuPattern);
        auto showedMenuItem = showedSubMenuPattern->GetParentMenuItem();
        CHECK_NULL_VOID(showedMenuItem);
        if (showedMenuItem->GetId() != host->GetId()) {
            parentMenuPattern->HideSubMenu();
        }
    }
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
    menuWrapperPattern->HideMenu();
}

void MenuItemPattern::RegisterOnClick()
{
    if (onClickEventSet_) return;

    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto event = [weak = WeakClaim(this)](GestureEvent& /* info */) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        auto host = pattern->GetHost();
        CHECK_NULL_VOID(host);
        auto hub = host->GetEventHub<MenuItemEventHub>();
        CHECK_NULL_VOID(hub);
        auto onChange = hub->GetOnChange();
        auto selectedChangeEvent = hub->GetSelectedChangeEvent();
        pattern->SetChange();
        if (selectedChangeEvent) {
            LOGI("trigger onChangeEvent");
            selectedChangeEvent(pattern->IsSelected());
        }
        if (onChange) {
            LOGI("trigger onChange");
            onChange(pattern->IsSelected());
            pattern->RecordChangeEvent();
        }
        host->OnAccessibilityEvent(AccessibilityEventType::SELECTED);

        if (pattern->GetSubBuilder() != nullptr) {
            pattern->ShowSubMenu();
            return;
        }
        // hide menu when menu item is clicked
        pattern->CloseMenu();
    };
    auto clickEvent = MakeRefPtr<ClickEvent>(std::move(event));

    auto clickableArea = GetClickableArea();
    CHECK_NULL_VOID(clickableArea);
    auto gestureHub = clickableArea->GetOrCreateGestureEventHub();
    CHECK_NULL_VOID(gestureHub);
    gestureHub->AddClickEvent(clickEvent);
    onClickEventSet_ = true;
}

void MenuItemPattern::RegisterOnTouch()
{
    if (onTouchEventSet_) return;

    auto clickableArea = GetClickableArea();
    CHECK_NULL_VOID(clickableArea);
    auto gestureHub = clickableArea->GetOrCreateGestureEventHub();
    CHECK_NULL_VOID(gestureHub);

    auto touchCallback = [weak = WeakClaim(this)](const TouchEventInfo& info) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        pattern->OnTouch(info);
    };
    auto onTouch = MakeRefPtr<TouchEventImpl>(std::move(touchCallback));
    gestureHub->AddTouchEvent(onTouch);
    onTouchEventSet_ = true;
}

void MenuItemPattern::RegisterOnHover()
{
    if (onHoverEventSet_) return;

    auto clickableArea = GetClickableArea();
    CHECK_NULL_VOID(clickableArea);
    auto inputHub = clickableArea->GetOrCreateInputEventHub();
    CHECK_NULL_VOID(inputHub);
    auto mouseTask = [weak = WeakClaim(this)](bool isHover) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        pattern->OnHover(isHover);
    };
    auto onHover = MakeRefPtr<InputEvent>(std::move(mouseTask));
    inputHub->AddOnHoverEvent(onHover);
    onHoverEventSet_ = true;
}

void MenuItemPattern::RegisterOnKeyEvent()
{
    if (onKeyEventSet_) return;
    
    auto clickableArea = GetClickableArea();
    CHECK_NULL_VOID(clickableArea);
    auto focusHub = clickableArea->GetOrCreateFocusHub();
    CHECK_NULL_VOID(focusHub);
    auto onKeyEvent = [wp = WeakClaim(this)](const KeyEvent& event) -> bool {
        auto pattern = wp.Upgrade();
        CHECK_NULL_RETURN(pattern, false);
        return pattern->OnKeyEvent(event);
    };
    focusHub->SetOnKeyEventInternal(std::move(onKeyEvent));
    onKeyEventSet_ = true;
}

void MenuItemPattern::OnTouch(const TouchEventInfo& info)
{
    // change menu item paint props on press
    auto touchType = info.GetTouches().front().GetTouchType();
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto theme = pipeline->GetTheme<SelectTheme>();
    CHECK_NULL_VOID(theme);

    if (touchType == TouchType::DOWN) {
        // change background color, update press status
        SetBgBlendColor(GetSubBuilder() ? theme->GetHoverColor() : theme->GetClickedColor());
    } else if (touchType == TouchType::UP) {
        SetBgBlendColor(isHovered_ ? theme->GetHoverColor() : Color::TRANSPARENT);
    } else {
        return;
    }
    PlayBgColorAnimation(false);
    auto host = GetHost();
    CHECK_NULL_VOID(host);
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
    } else if (touchType == TouchType::UP) {
        auto touchUpOffset = info.GetTouches().front().GetLocalLocation();
        if (lastTouchOffset_ && (touchUpOffset - *lastTouchOffset_).GetDistance() <= DEFAULT_CLICK_DISTANCE) {
            CloseMenu();
        }
        lastTouchOffset_.reset();
    }
}

void MenuItemPattern::OnHover(bool isHover)
{
    isHovered_ = isHover;
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto theme = pipeline->GetTheme<SelectTheme>();
    CHECK_NULL_VOID(theme);

    if (isHover || isSubMenuShowed_) {
        // keep hover color when subMenu showed
        SetBgBlendColor(theme->GetHoverColor());
        ShowSubMenu();
    } else {
        SetBgBlendColor(Color::TRANSPARENT);
    }
    PlayBgColorAnimation();
    auto host = GetHost();
    CHECK_NULL_VOID(host);
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
        ShowSubMenu();
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
{    // show menu at left top point of targetNode
    auto frameSize = targetNode->GetGeometryNode()->GetMarginFrameSize();
    OffsetF position = targetNode->GetPaintRectOffset() + OffsetF(frameSize.Width(), 0.0);
    return position;
}


void MenuItemPattern::AddHoverRegions(const OffsetF& topLeftPoint, const OffsetF& bottomRightPoint)
{
    TouchRegion hoverRegion = TouchRegion(
        Offset(topLeftPoint.GetX(), topLeftPoint.GetY()), Offset(bottomRightPoint.GetX(), bottomRightPoint.GetY()));
    hoverRegions_.emplace_back(hoverRegion);
    LOGI("MenuItemPattern::AddHoverRegions hoverRegion is %{public}s to %{public}s", topLeftPoint.ToString().c_str(),
        bottomRightPoint.ToString().c_str());
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

void MenuItemPattern::AddSelectIcon(RefPtr<FrameNode>& row)
{
    auto itemProperty = GetLayoutProperty<MenuItemLayoutProperty>();
    CHECK_NULL_VOID(itemProperty);
    if (!itemProperty->GetSelectIcon().value_or(false)) {
        if (selectIcon_) {
            row->RemoveChildAtIndex(0);
            selectIcon_ = nullptr;
            row->MarkModifyDone();
            row->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
        }
        return;
    }
    if (!selectIcon_) {
        selectIcon_ = FrameNode::CreateFrameNode(
            V2::IMAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<ImagePattern>());
        CHECK_NULL_VOID(selectIcon_);
    }
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto iconTheme = pipeline->GetTheme<IconTheme>();
    CHECK_NULL_VOID(iconTheme);
    auto userIcon = itemProperty->GetSelectIconSrc().value_or("");
    auto iconPath = userIcon.empty() ? iconTheme->GetIconPath(InternalResource::ResourceId::MENU_OK_SVG) : userIcon;
    auto selectTheme = pipeline->GetTheme<SelectTheme>();
    CHECK_NULL_VOID(selectTheme);
    ImageSourceInfo imageSourceInfo;
    imageSourceInfo.SetSrc(iconPath);
    if (userIcon.empty()) {
        imageSourceInfo.SetFillColor(selectTheme->GetMenuIconColor());
    }
    auto props = selectIcon_->GetLayoutProperty<ImageLayoutProperty>();
    CHECK_NULL_VOID(props);
    props->UpdateImageSourceInfo(imageSourceInfo);
    UpdateIconSrc(selectIcon_, selectTheme->GetIconSideLength(), selectTheme->GetIconSideLength(),
        selectTheme->GetMenuIconColor(), userIcon.empty());

    auto renderContext = selectIcon_->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    renderContext->SetVisible(isSelected_);

    selectIcon_->MountToParent(row, 0);
    selectIcon_->MarkModifyDone();
    selectIcon_->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
}

void MenuItemPattern::AddExpandIcon(RefPtr<FrameNode>& column, RefPtr<MenuLayoutProperty>& menuProperty)
{
    CHECK_NULL_VOID(menuProperty);
    auto expandingMode = menuProperty->GetExpandingMode().value_or(SubMenuExpandingMode::SIDE);
    auto canExpand = GetSubBuilder() != nullptr
        && (expandingMode == SubMenuExpandingMode::EMBEDDED
            || expandingMode == SubMenuExpandingMode::STACK);
    if (!canExpand) {
        if (expandIcon_) {
            column->RemoveChild(expandIcon_);
            expandIcon_ = nullptr;
            column->MarkModifyDone();
            column->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
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
        expandingMode == SubMenuExpandingMode::STACK
            ? InternalResource::ResourceId::IC_PUBLIC_ARROW_RIGHT_SVG
            : isExpanded_
                ? InternalResource::ResourceId::IC_PUBLIC_ARROW_UP_SVG
                : InternalResource::ResourceId::IC_PUBLIC_ARROW_DOWN_SVG);
    auto selectTheme = pipeline->GetTheme<SelectTheme>();
    CHECK_NULL_VOID(selectTheme);
    ImageSourceInfo imageSourceInfo(iconPath);
    auto props = expandIcon_->GetLayoutProperty<ImageLayoutProperty>();
    CHECK_NULL_VOID(props);
    props->UpdateImageSourceInfo(imageSourceInfo);
    UpdateIconSrc(expandIcon_, selectTheme->GetIconSideLength(), selectTheme->GetIconSideLength(),
        selectTheme->GetMenuIconColor(), true);

    auto expandIconIndex = column->GetChildren().size();
    expandIcon_->MountToParent(column, expandIconIndex);
    expandIcon_->MarkModifyDone();
    expandIcon_->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
}

void MenuItemPattern::UpdateExpandableArea()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    RefPtr<FrameNode> expandableArea =
        host->GetChildAtIndex(EXPANDABLE_AREA_VIEW_INDEX)
            ? AceType::DynamicCast<FrameNode>(host->GetChildAtIndex(EXPANDABLE_AREA_VIEW_INDEX))
            : nullptr;
    CHECK_NULL_VOID(expandableArea);

    if (!isExpanded_) {
        for (auto item : expandableItems_) {
            expandableArea->RemoveChild(item);
        }
        expandableArea->MarkModifyDone();
        expandableArea->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
        return;
    }

    auto buildFunc = GetSubBuilder();
    if (buildFunc != nullptr) {
        buildFunc();
        auto menu = NG::ViewStackProcessor::GetInstance()->Finish();
        CHECK_NULL_VOID(menu);

        if (menu->GetTag() == V2::MENU_ETS_TAG) {
            if (expandableItems_.size() == 0) {
                BuildEmbeddedMenuItems(menu);
            }
            for (auto item : expandableItems_) {
                item->MountToParent(expandableArea);
            }
        }
    }
    expandableArea->MarkModifyDone();
    expandableArea->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
}

void MenuItemPattern::BuildEmbeddedMenuItems(RefPtr<UINode>& node, bool needNextLevel)
{
    auto children = node->GetChildren();
    if (children.empty()) return;

    for (auto child : children) {
        if (child->GetTag() == V2::MENU_ITEM_GROUP_ETS_TAG) {
            if (!needNextLevel) return;
            BuildEmbeddedMenuItems(child, false);
        } else if (child->GetTag() == V2::MENU_ITEM_ETS_TAG) {
            auto childItem = AceType::DynamicCast<FrameNode>(child);
            auto props = childItem->GetLayoutProperty<MenuItemLayoutProperty>();

            auto oldEventHub = childItem->GetEventHub<MenuItemEventHub>();
            auto onChange = oldEventHub->GetOnChange();
            auto isSelected = oldEventHub->GetCurrentUIState() == UI_STATE_SELECTED;

            MenuItemProperties menuItemProps;
            auto model = new NG::MenuItemModelNG();
            model->Create(menuItemProps);
            auto stack = ViewStackProcessor::GetInstance();
            auto eventHub = stack->GetMainFrameNodeEventHub<MenuItemEventHub>();
            CHECK_NULL_VOID(eventHub);
            eventHub->SetOnChange(onChange);

            auto item = AceType::DynamicCast<FrameNode>(stack->Finish());
            auto newProps = AceType::DynamicCast<MenuItemLayoutProperty>(props->Clone());
            newProps->UpdateHasFurtherExpand(false);
            item->SetLayoutProperty(newProps);

            auto pattern = item->GetPattern<MenuItemPattern>();
            pattern->SetSelected(isSelected);
            eventHub->SetCurrentUIState(UI_STATE_SELECTED, isSelected);
            expandableItems_.push_back(item);
        }
    }
}

RefPtr<UINode> MenuItemPattern::BuildStackSubMenu(RefPtr<UINode>& node)
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, node);
    auto layoutProperty = GetLayoutProperty<MenuItemLayoutProperty>();
    CHECK_NULL_RETURN(layoutProperty, node);
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_RETURN(pipeline, node);
    auto iconTheme = pipeline->GetTheme<IconTheme>();
    CHECK_NULL_RETURN(iconTheme, node);
    auto selectTheme = pipeline->GetTheme<SelectTheme>();
    CHECK_NULL_RETURN(selectTheme, node);
    auto iconPath = iconTheme->GetIconPath(InternalResource::ResourceId::IC_PUBLIC_ARROW_DOWN_SVG);
    ImageSourceInfo imageSourceInfo;
    imageSourceInfo.SetSrc(iconPath);
    imageSourceInfo.SetFillColor(selectTheme->GetMenuIconColor());
    auto content = layoutProperty->GetContent().value_or(layoutProperty->GetLabel().value_or(""));

    MenuItemProperties menuItemProps;
    menuItemProps.content = content;
    menuItemProps.endIcon = imageSourceInfo;
    auto model = new NG::MenuItemModelNG();
    model->Create(menuItemProps);
    auto stack = ViewStackProcessor::GetInstance();

    auto titleItem = AceType::DynamicCast<FrameNode>(stack->Finish());
    auto columnNode = FrameNode::CreateFrameNode(V2::COLUMN_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<LinearLayoutPattern>(true));
    auto columnProperty = columnNode->GetLayoutProperty<LinearLayoutProperty>();
    columnProperty->UpdateMeasureType(MeasureType::MATCH_PARENT_CROSS_AXIS);
    columnProperty->UpdateCrossAxisAlign(FlexAlign::STRETCH);

    auto pattern = titleItem->GetPattern<MenuItemPattern>();
    CHECK_NULL_RETURN(pattern, node);
    titleItem->MountToParent(columnNode);

    if (node->GetTag() == V2::MENU_ETS_TAG) {
        if (expandableItems_.size() == 0) {
            BuildEmbeddedMenuItems(node);
        }
        for (auto item : expandableItems_) {
            item->MountToParent(columnNode);
        }
    }

    return AceType::DynamicCast<NG::UINode>(columnNode);
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
    auto itemProperty = GetLayoutProperty<MenuItemLayoutProperty>();
    CHECK_NULL_VOID(itemProperty);
    ImageSourceInfo defaultImageSourceInfo;
    auto iconSrc = isStart ? itemProperty->GetStartIcon().value_or(defaultImageSourceInfo)
                           : itemProperty->GetEndIcon().value_or(defaultImageSourceInfo);
    auto& iconNode = isStart ? startIcon_ : endIcon_;
    if (iconSrc.GetSrc().empty()) {
        row->RemoveChild(iconNode); // it's safe even if iconNode is nullptr
        iconNode = nullptr;
        row->MarkModifyDone();
        row->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
        return;
    }

    if (!iconNode) {
        iconNode = FrameNode::CreateFrameNode(
            V2::IMAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<ImagePattern>());
        CHECK_NULL_VOID(iconNode);
    }
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto selectTheme = pipeline->GetTheme<SelectTheme>();
    CHECK_NULL_VOID(selectTheme);
    auto iconWidth = isStart ? selectTheme->GetIconSideLength() : selectTheme->GetEndIconWidth();
    auto iconHeight = isStart ? selectTheme->GetIconSideLength() : selectTheme->GetEndIconHeight();
    ImageSourceInfo imageSourceInfo(iconSrc);
    auto props = iconNode->GetLayoutProperty<ImageLayoutProperty>();
    CHECK_NULL_VOID(props);
    props->UpdateImageSourceInfo(imageSourceInfo);
    UpdateIconSrc(iconNode, iconWidth, iconHeight, selectTheme->GetMenuIconColor(), false);

    iconNode->MountToParent(row, ((isStart && selectIcon_) || (!isStart && label_)) ? 1 : 0);
    iconNode->MarkModifyDone();
    iconNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
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

    UpdateFont(menuProperty, theme, isLabel);

    textProperty->UpdateContent(content);
    textProperty->UpdateMaxLines(1);
    textProperty->UpdateTextOverflow(TextOverflow::ELLIPSIS);
    TextAlign textAlign = static_cast<TextAlign>(theme->GetMenuItemContentAlign());
    textProperty->UpdateTextAlign(isLabel ? TextAlign::CENTER : textAlign);
    node->MountToParent(row, isLabel ? 0 : DEFAULT_NODE_SLOT);
    node->MarkModifyDone();
    node->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
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
    if (!isLabel && !itemProperty->HasFontColor() && isFocused_) {
        fontColor = theme->GetMenuItemFocusedTextColor();
    }
    auto menuItemNode = GetHost();
    UpdateFontColor(
        node, menuProperty, fontColor, isLabel ? theme->GetSecondaryFontColor() : theme->GetMenuFontColor());
    if (!isLabel) {
        auto menuItemRenderContext = menuItemNode->GetRenderContext();
        CHECK_NULL_VOID(menuItemRenderContext);
        auto renderContext = node->GetRenderContext();
        CHECK_NULL_VOID(renderContext);
        if (menuItemRenderContext->HasForegroundColor()) {
            renderContext->UpdateForegroundColor(menuItemRenderContext->GetForegroundColorValue());
        }
    }
    auto fontFamily = isLabel ? itemProperty->GetLabelFontFamily() : itemProperty->GetFontFamily();
    UpdateFontFamily(textProperty, menuProperty, fontFamily);
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
        content_->GetRenderContext()->UpdateForegroundColor(theme->GetDisabledMenuFontColor());
        auto textLayoutProperty = content_->GetLayoutProperty<TextLayoutProperty>();
        CHECK_NULL_VOID(textLayoutProperty);
        textLayoutProperty->UpdateTextColor(theme->GetDisabledMenuFontColor());
        content_->MarkModifyDone();
    }
    if (label_) {
        label_->GetRenderContext()->UpdateForegroundColor(theme->GetDisabledMenuFontColor());
        auto labelTextLayoutProperty = label_->GetLayoutProperty<TextLayoutProperty>();
        CHECK_NULL_VOID(labelTextLayoutProperty);
        labelTextLayoutProperty->UpdateTextColor(theme->GetDisabledMenuFontColor());
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
            pattern->ShowSubMenu();
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
} // namespace OHOS::Ace::NG
