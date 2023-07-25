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

#include <memory>

#include "base/geometry/ng/offset_t.h"
#include "base/memory/ace_type.h"
#include "base/utils/utils.h"
#include "core/components/select/select_theme.h"
#include "core/components/theme/icon_theme.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/image/image_pattern.h"
#include "core/components_ng/pattern/menu/menu_item/menu_item_event_hub.h"
#include "core/components_ng/pattern/menu/menu_view.h"
#include "core/components_ng/pattern/menu/wrapper/menu_wrapper_pattern.h"
#include "core/components_ng/pattern/text/text_layout_property.h"
#include "core/components_ng/pattern/text/text_pattern.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "core/pipeline/pipeline_base.h"

namespace OHOS::Ace::NG {
namespace {
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

void UpdateFontColor(RefPtr<TextLayoutProperty>& textProperty, RefPtr<MenuLayoutProperty>& menuProperty,
    const std::optional<Color>& fontColor, const Color& defaultFontColor)
{
    if (fontColor.has_value()) {
        textProperty->UpdateTextColor(fontColor.value());
    } else if (menuProperty && menuProperty->GetFontColor().has_value()) {
        textProperty->UpdateTextColor(menuProperty->GetFontColor().value());
    } else {
        textProperty->UpdateTextColor(defaultFontColor);
    }
}

void UpdateIconSrc(RefPtr<FrameNode>& node, const std::string& src, const Dimension& horizontalSize,
    const Dimension& verticalSize, const Color& color)
{
    ImageSourceInfo imageSourceInfo;
    imageSourceInfo.SetSrc(src);
    imageSourceInfo.SetFillColor(color);

    auto props = node->GetLayoutProperty<ImageLayoutProperty>();
    CHECK_NULL_VOID(props);
    props->UpdateImageSourceInfo(imageSourceInfo);
    props->UpdateAlignment(Alignment::CENTER);
    CalcSize idealSize = { CalcLength(horizontalSize), CalcLength(verticalSize) };
    MeasureProperty layoutConstraint;
    layoutConstraint.selfIdealSize = idealSize;
    props->UpdateCalcLayoutProperty(layoutConstraint);

    auto iconRenderProperty = node->GetPaintProperty<ImageRenderProperty>();
    CHECK_NULL_VOID(iconRenderProperty);
    iconRenderProperty->UpdateSvgFillColor(color);
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
    if (IsDisabled()) {
        UpdateDisabledStyle();
    }
    SetAccessibilityAction();
}

RefPtr<FrameNode> MenuItemPattern::GetMenuWrapper()
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, nullptr);
    auto parent = host->GetParent();
    while (parent) {
        if (parent->GetTag() == V2::MENU_WRAPPER_ETS_TAG) {
            return AceType::DynamicCast<FrameNode>(parent);
        }
        parent = parent->GetParent();
    }
    return nullptr;
}

RefPtr<FrameNode> MenuItemPattern::GetMenu()
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, nullptr);
    auto parent = host->GetParent();
    while (parent) {
        if (parent->GetTag() == V2::MENU_ETS_TAG) {
            return AceType::DynamicCast<FrameNode>(parent);
        }
        parent = parent->GetParent();
    }
    return nullptr;
}

void MenuItemPattern::ShowSubMenu()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    LOGI("MenuItemPattern::ShowSubMenu menu item id is %{public}d", host->GetId());
    auto buildFunc = GetSubBuilder();
    if (!buildFunc || isSubMenuShowed_) {
        return;
    }

    // Hide SubMenu of parent Menu node
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

    isSubMenuShowed_ = true;

    NG::ScopedViewStackProcessor builderViewStackProcessor;
    buildFunc();
    auto customNode = NG::ViewStackProcessor::GetInstance()->Finish();
    auto subMenu = MenuView::Create(customNode, host->GetId(), host->GetTag(), MenuType::SUB_MENU);
    CHECK_NULL_VOID(subMenu);
    auto menuPattern = subMenu->GetPattern<MenuPattern>();
    CHECK_NULL_VOID(menuPattern);
    menuPattern->SetParentMenuItem(host);
    subMenuId_ = subMenu->GetId();
    AddSelfHoverRegion(host);

    auto menuWrapper = GetMenuWrapper();
    CHECK_NULL_VOID(menuWrapper);
    auto menuWrapperPattern = menuWrapper->GetPattern<MenuWrapperPattern>();
    CHECK_NULL_VOID(menuWrapperPattern);
    menuWrapperPattern->AddSubMenuId(host->GetId());
    subMenu->MountToParent(menuWrapper);

    OffsetF offset = GetSubMenuPostion(host);
    auto menuProps = subMenu->GetLayoutProperty<MenuLayoutProperty>();
    CHECK_NULL_VOID(menuProps);
    menuProps->UpdateMenuOffset(offset);
    menuWrapper->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF_AND_CHILD);
    RegisterWrapperMouseEvent();

    auto focusHub = subMenu->GetOrCreateFocusHub();
    CHECK_NULL_VOID(focusHub);
    focusHub->RequestFocus();
    parentMenuPattern->SetShowedSubMenu(subMenu);
}

void MenuItemPattern::CloseMenu()
{
    auto menuWrapper = GetMenuWrapper();
    CHECK_NULL_VOID(menuWrapper);
    auto menuWrapperPattern = menuWrapper->GetPattern<MenuWrapperPattern>();
    CHECK_NULL_VOID(menuWrapperPattern);
    menuWrapperPattern->HideMenu();
}

void MenuItemPattern::RegisterOnClick()
{
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

    auto gestureHub = host->GetOrCreateGestureEventHub();
    CHECK_NULL_VOID(gestureHub);
    gestureHub->AddClickEvent(clickEvent);
}

void MenuItemPattern::RegisterOnTouch()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto gestureHub = host->GetOrCreateGestureEventHub();
    CHECK_NULL_VOID(gestureHub);

    auto touchCallback = [weak = WeakClaim(this)](const TouchEventInfo& info) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        pattern->OnTouch(info);
    };
    auto touchEvent = MakeRefPtr<TouchEventImpl>(std::move(touchCallback));
    gestureHub->AddTouchEvent(touchEvent);
}

void MenuItemPattern::RegisterOnHover()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto inputHub = host->GetOrCreateInputEventHub();
    CHECK_NULL_VOID(inputHub);
    auto mouseTask = [weak = WeakClaim(this)](bool isHover) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        pattern->OnHover(isHover);
    };
    auto mouseEvent = MakeRefPtr<InputEvent>(std::move(mouseTask));
    inputHub->AddOnHoverEvent(mouseEvent);
}

void MenuItemPattern::RegisterOnKeyEvent()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto focusHub = host->GetOrCreateFocusHub();
    CHECK_NULL_VOID(focusHub);
    auto onKeyEvent = [wp = WeakClaim(this)](const KeyEvent& event) -> bool {
        auto pattern = wp.Upgrade();
        CHECK_NULL_RETURN_NOLOG(pattern, false);
        return pattern->OnKeyEvent(event);
    };
    focusHub->SetOnKeyEventInternal(std::move(onKeyEvent));
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

OffsetF MenuItemPattern::GetSubMenuPostion(const RefPtr<FrameNode>& targetNode)
{
    // show menu at left top point of targetNode
    OffsetF position;
    auto frameSize = targetNode->GetGeometryNode()->GetMarginFrameSize();
    position = targetNode->GetPaintRectOffset() + OffsetF(frameSize.Width(), 0.0);
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
        CHECK_NULL_VOID_NOLOG(pattern);
        auto host = pattern->GetHost();
        CHECK_NULL_VOID_NOLOG(host);
        auto renderContext = host->GetRenderContext();
        CHECK_NULL_VOID_NOLOG(renderContext);
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
    UpdateIconSrc(selectIcon_, iconPath, selectTheme->GetIconSideLength(), selectTheme->GetIconSideLength(),
        selectTheme->GetMenuIconColor());

    auto renderContext = selectIcon_->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    renderContext->SetVisible(isSelected_);

    selectIcon_->MountToParent(row, 0);
    selectIcon_->MarkModifyDone();
    selectIcon_->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
}

void MenuItemPattern::UpdateIcon(RefPtr<FrameNode>& row, bool isStart)
{
    auto itemProperty = GetLayoutProperty<MenuItemLayoutProperty>();
    CHECK_NULL_VOID(itemProperty);
    auto iconSrc = isStart ? itemProperty->GetStartIcon().value_or("") : itemProperty->GetEndIcon().value_or("");
    auto& iconNode = isStart ? startIcon_ : endIcon_;
    if (iconSrc.empty()) {
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
    UpdateIconSrc(iconNode, iconSrc, iconWidth, iconHeight, selectTheme->GetMenuIconColor());

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
    auto fontSize = isLabel ? itemProperty->GetLabelFontSize() : itemProperty->GetFontSize();
    UpdateFontSize(textProperty, menuProperty, fontSize, theme->GetMenuFontSize());
    auto fontWeight = isLabel ? itemProperty->GetLabelFontWeight() : itemProperty->GetFontWeight();
    UpdateFontWeight(textProperty, menuProperty, fontWeight);
    auto fontStyle = isLabel ? itemProperty->GetLabelItalicFontStyle() : itemProperty->GetItalicFontStyle();
    UpdateFontStyle(textProperty, menuProperty, fontStyle);
    auto fontColor = isLabel ? itemProperty->GetLabelFontColor() : itemProperty->GetFontColor();
    UpdateFontColor(
        textProperty, menuProperty, fontColor, isLabel ? theme->GetSecondaryFontColor() : theme->GetMenuFontColor());
    textProperty->UpdateContent(content);
    textProperty->UpdateMaxLines(1);
    textProperty->UpdateTextOverflow(TextOverflow::ELLIPSIS);
    node->MountToParent(row, isLabel ? 0 : DEFAULT_NODE_SLOT);
    node->MarkModifyDone();
    node->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
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
}

bool MenuItemPattern::IsDisabled()
{
    auto eventHub = GetHost()->GetEventHub<MenuItemEventHub>();
    CHECK_NULL_RETURN(eventHub, true);
    return !eventHub->IsEnabled();
}

void MenuItemPattern::UpdateDisabledStyle()
{
    CHECK_NULL_VOID(content_);
    auto context = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(context);
    auto theme = context->GetTheme<SelectTheme>();
    CHECK_NULL_VOID(theme);
    content_->GetRenderContext()->UpdateForegroundColor(theme->GetDisabledMenuFontColor());
    content_->MarkModifyDone();
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
        }

        if (pattern->GetSubBuilder() != nullptr) {
            pattern->ShowSubMenu();
            return;
        }

        pattern->CloseMenu();
    });
}
} // namespace OHOS::Ace::NG
