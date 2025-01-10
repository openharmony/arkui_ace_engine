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
#include "core/components/common/layout/grid_system_manager.h"
#include "core/components/common/properties/shadow_config.h"
#include "core/components/select/select_theme.h"
#include "core/components/theme/shadow_theme.h"
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
#include "core/components_ng/pattern/security_component/security_component_pattern.h"
#include "core/components_ng/pattern/text/text_layout_property.h"
#include "core/components_ng/pattern/text/text_pattern.h"
#include "core/components_ng/property/border_property.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "core/pipeline/pipeline_base.h"

namespace OHOS::Ace::NG {
namespace {
const Color ITEM_FILL_COLOR = Color::TRANSPARENT;
// default clicked & hover color for background blend when theme is null(value from SelectTheme)
const Color DEFAULT_CLICKED_COLOR(0x19000000);
const Color DEFAULT_HOVER_COLOR(0x0c000000);
constexpr double VELOCITY = 0.0f;
constexpr double MASS = 1.0f;
constexpr double STIFFNESS = 328.0f;
constexpr double DAMPING = 33.0f;
constexpr double SEMI_CIRCLE_ANGEL = 180.0f;
constexpr float OPACITY_EFFECT = 0.99;
const std::string SYSTEM_RESOURCE_PREFIX = std::string("resource:///");
// id of system resource start from 0x07000000
constexpr uint64_t MIN_SYSTEM_RESOURCE_ID = 0x07000000;
// id of system resource end to 0x07FFFFFF
constexpr uint64_t MAX_SYSTEM_RESOURCE_ID = 0x07FFFFFF;
constexpr Dimension MIN_OPTION_WIDTH = 56.0_vp;
constexpr Dimension OPTION_MARGIN = 8.0_vp;
constexpr int32_t COLUMN_NUM = 2;
constexpr Dimension BORDER_DEFAULT_WIDTH = 0.0_vp;

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
    InitFocusPadding();
    RegisterOnKeyEvent();
    RegisterOnClick();
    RegisterOnTouch();
    RegisterOnHover();
}

void CustomMenuItemPattern::OnAttachToFrameNode()
{
    InitFocusPadding();
    RegisterOnKeyEvent();
    RegisterOnTouch();
}

void MenuItemPattern::InitFocusPadding()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto context = host->GetContextRefPtr();
    CHECK_NULL_VOID(context);
    auto selectTheme = context->GetTheme<SelectTheme>();
    CHECK_NULL_VOID(selectTheme);
    focusPadding_ = selectTheme->GetOptionFocusedBoxPadding();
}

void MenuItemPattern::OnModifyDone()
{
    Pattern::OnModifyDone();
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    if (isOptionPattern_) {
        OptionOnModifyDone(host);
    } else {
        NeedFocusEvent();
        SetThemeProps(host);
        InitTextFadeOut();
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

        auto renderContext = host->GetRenderContext();
        if (renderContext) {
            renderContext->SetClipToBounds(focusPadding_ == 0.0_vp);
        }
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
}

void MenuItemPattern::SetThemeProps(const RefPtr<FrameNode>& host)
{
    CHECK_NULL_VOID(host);
    auto layoutProp = host->GetLayoutProperty();
    CHECK_NULL_VOID(layoutProp);
    if (!layoutProp->GetMarginProperty()) {
        auto context = host->GetContextRefPtr();
        CHECK_NULL_VOID(context);
        auto selectTheme = context->GetTheme<SelectTheme>();
        CHECK_NULL_VOID(selectTheme);
        MarginProperty margin;
        auto horizontalMargin = CalcLength(selectTheme->GetMenuItemLeftRightMargin());
        auto verticalMargin = CalcLength(selectTheme->GetMenuItemTopBottomMargin());
        margin.SetEdges(horizontalMargin, horizontalMargin, verticalMargin, verticalMargin);
        layoutProp->UpdateMargin(margin);
    }
}

void MenuItemPattern::InitTextFadeOut()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto context = host->GetContextRefPtr();
    CHECK_NULL_VOID(context);
    auto textTheme = context->GetTheme<TextTheme>();
    CHECK_NULL_VOID(textTheme);
    isTextFadeOut_ = textTheme->GetIsTextFadeout();
}

void MenuItemPattern::NeedFocusEvent()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto context = host->GetContextRefPtr();
    CHECK_NULL_VOID(context);
    auto selectTheme = context->GetTheme<SelectTheme>();
    CHECK_NULL_VOID(selectTheme);
    auto menuNeedFocus = selectTheme->GetMenuNeedFocus();
    if (menuNeedFocus) {
        InitFocusEvent();
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
        if (pattern->IsOptionPattern()) {
            pattern->OptionHandleFocusEvent();
        } else {
            pattern->HandleFocusEvent();
            pattern->UpdateTextMarquee(pattern->isFocused_);
        }
    };
    focusHub->SetOnFocusInternal(focusTask);

    auto blurTask = [weak = WeakClaim(this)]() {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        if (pattern->IsOptionPattern()) {
            pattern->OptionHandleBlurEvent();
        } else {
            pattern->HandleBlurEvent();
            pattern->UpdateTextMarquee(pattern->isHovered_);
        }
    };
    focusHub->SetOnBlurInternal(blurTask);
}

bool MenuItemPattern::GetShadowFromTheme(ShadowStyle shadowStyle, Shadow& shadow)
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, false);
    auto context = host->GetContextRefPtr();
    CHECK_NULL_RETURN(context, false);
    auto shadowTheme = context->GetTheme<ShadowTheme>();
    CHECK_NULL_RETURN(shadowTheme, false);
    auto colorMode = SystemProperties::GetColorMode();
    shadow = shadowTheme->GetShadow(shadowStyle, colorMode);
    return true;
}

void MenuItemPattern::OptionHandleFocusEvent()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto pipeline = host->GetContextRefPtr();
    CHECK_NULL_VOID(pipeline);
    if (pipeline->GetIsFocusActive()) {
        SetFocusStyle();
    }

    if (!isFocusActiveUpdateEvent_) {
        isFocusActiveUpdateEvent_ = [weak = WeakClaim(this)](bool isFocusActive) {
            auto pattern = weak.Upgrade();
            CHECK_NULL_VOID(pattern);
            isFocusActive ? pattern->SetFocusStyle() : pattern->ClearFocusStyle();
        };
    }

    pipeline->AddIsFocusActiveUpdateEvent(GetHost(), isFocusActiveUpdateEvent_);
}

void MenuItemPattern::OptionHandleBlurEvent()
{
    ClearFocusStyle();
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto pipeline = host->GetContextRefPtr();
    CHECK_NULL_VOID(pipeline);
    pipeline->RemoveIsFocusActiveUpdateEvent(GetHost());
}

void MenuItemPattern::SetFocusStyle()
{
    CHECK_NULL_VOID(selectTheme_);
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto renderContext = host->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    auto&& graphics = renderContext->GetOrCreateGraphics();
    CHECK_NULL_VOID(graphics);
    if (!selectTheme_->GetoptionApplyFocusedStyle()) {
        return;
    }

    Shadow shadow = Shadow::CreateShadow(static_cast<ShadowStyle>(NONE_SHADOW_VALUE));
    if (!graphics->HasBackShadow() || graphics->GetBackShadowValue() == shadow) {
        ShadowStyle shadowStyle = static_cast<ShadowStyle>(selectTheme_->GetOptionFocusedShadow());
        renderContext->UpdateBackShadow(Shadow::CreateShadow(shadowStyle));
        isFocusShadowSet_ = true;
    }

    if (!isOptionBgColorSetByUser_ && !isBGColorSetByUser_) {
        renderContext->UpdateBackgroundColor(selectTheme_->GetOptionFocusedBackgroundColor());
    }
    if (!isOptionFontColorSetByUser_ && !isTextColorSetByUser_) {
        SetFontColor(selectTheme_->GetOptionFocusedFontColor());
    }
    text_->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
}

void MenuItemPattern::ClearFocusStyle()
{
    CHECK_NULL_VOID(selectTheme_);
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto renderContext = host->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    if (!selectTheme_->GetoptionApplyFocusedStyle()) {
        return;
    }
    if (!isBGColorSetByUser_) {
        renderContext->UpdateBackgroundColor(rowSelected_ == index_ ? selectTheme_->GetSelectedColor() :
            (isOptionBgColorSetByUser_ ? optionBgColor_.value() : Color::TRANSPARENT));
    } else {
        renderContext->UpdateBackgroundColor(rowSelected_ == index_ ? bgColor_.value() :
            (isOptionBgColorSetByUser_ ? optionBgColor_.value() : Color::TRANSPARENT));
    }
    if (isFocusShadowSet_) {
        renderContext->ResetBackShadow();
        renderContext->SetShadowRadius(0.0f);
        isFocusShadowSet_ = false;
    }
    if (!isTextColorSetByUser_) {
        SetFontColor(rowSelected_ == index_ ? selectTheme_->GetSelectedColorText() :
            (isOptionFontColorSetByUser_ ? optionFontColor_.value() : selectTheme_->GetMenuFontColor()));
    } else {
        SetFontColor(rowSelected_ == index_ ? selectFontColor_.value() :
            (isOptionFontColorSetByUser_ ? optionFontColor_.value() : selectTheme_->GetMenuFontColor()));
    }
    text_->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
}

void MenuItemPattern::HandleFocusEvent()
{
    isFocused_ = true;
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto renderContext = host->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    auto context = host->GetContextRefPtr();
    CHECK_NULL_VOID(context);
    auto selectTheme = context->GetTheme<SelectTheme>();
    CHECK_NULL_VOID(selectTheme);

    if (!renderContext->HasBackgroundColor()) {
        renderContext->UpdateBackgroundColor(selectTheme->GetMenuItemFocusedBgColor());
        isFocusBGColorSet_ = true;
    }
    if (!renderContext->HasBackShadow()) {
        ShadowStyle shadowStyle = static_cast<ShadowStyle>(selectTheme->GetMenuItemFocusedShadowStyle());
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
    if (isFocusBGColorSet_) {
        renderContext->ResetBackgroundColor();
        renderContext->SetBackgroundColor(Color::TRANSPARENT.GetValue());
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
        .SetDescription(host->GetAutoEventParamValue(""))
        .SetHost(host);
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

void MenuItemPattern::CleanParentMenuItemBgColor()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto menu = GetMenu(true);
    CHECK_NULL_VOID(menu);
    auto menuPattern = menu->GetPattern<MenuPattern>();
    CHECK_NULL_VOID(menuPattern);
    SetBgBlendColor(Color::TRANSPARENT);
    auto props = GetPaintProperty<MenuItemPaintProperty>();
    CHECK_NULL_VOID(props);
    props->UpdateHover(false);
    props->UpdatePress(false);
    auto parentNode = host->GetParent();
    CHECK_NULL_VOID(parentNode);
    auto parent = AceType::DynamicCast<UINode>(parentNode);
    CHECK_NULL_VOID(parent);
    menuPattern->OnItemPressed(parent, index_, false, false);
    PlayBgColorAnimation();
    host->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
}

void MenuItemPattern::ShowSubMenu(ShowSubMenuType type)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto menuNode = GetMenu(true);
    CHECK_NULL_VOID(menuNode);
    auto menuPattern = menuNode->GetPattern<MenuPattern>();
    CHECK_NULL_VOID(menuPattern);
    auto customNode = BuildSubMenuCustomNode();
    CHECK_NULL_VOID(customNode);
    UpdateSubmenuExpandingMode(customNode);
    if (expandingMode_ == SubMenuExpandingMode::EMBEDDED) {
        auto frameNode = GetSubMenu(customNode);
        CHECK_NULL_VOID(frameNode);
        OnExpandChanged(frameNode);
        return;
    }

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
        CHECK_NULL_VOID(focusMenuBlurStyle);
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
    if (type == ShowSubMenuType::LONG_PRESS && expandingMode_ == SubMenuExpandingMode::STACK) {
        CleanParentMenuItemBgColor();
    }
    SendSubMenuOpenToAccessibility(subMenu, type);
}

void MenuItemPattern::SendSubMenuOpenToAccessibility(RefPtr<FrameNode>& subMenu, ShowSubMenuType type)
{
    CHECK_NULL_VOID(subMenu);
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

RefPtr<FrameNode> MenuItemPattern::GetSubMenu(RefPtr<UINode>& customNode)
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
    if (!frameNode) {
        TAG_LOGW(AceLogTag::ACE_MENU, "subMenu has no Menu node");
    }
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
    CHECK_NULL_VOID(subMenu);
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
    auto menuNode = GetMenu(true);
    CHECK_NULL_VOID(menuNode);
    auto menuPattern = menuNode->GetPattern<MenuPattern>();
    CHECK_NULL_VOID(menuPattern);
    isExpanded_ = !isExpanded_;
    if (isExpanded_) {
        embeddedMenu_ = expandableNode;
        ShowEmbeddedExpandMenu(embeddedMenu_);
        menuPattern->SetShowedSubMenu(embeddedMenu_);
    } else {
        HideEmbeddedExpandMenu(embeddedMenu_);
        embeddedMenu_ = nullptr;
        menuPattern->SetShowedSubMenu(nullptr);
    }
}

Offset GetTransformCenter(SizeF size, Placement placement)
{
    if (placement == Placement::TOP) {
        return Offset(size.Width() / 2.0f, size.Height());
    }
    if (placement == Placement::TOP_LEFT) {
        return Offset(0.0f, size.Height());
    }
    if (placement == Placement::TOP_RIGHT) {
        return Offset(size.Width(), size.Height());
    }
    return Offset();
}

void MenuItemPattern::UpdatePreviewPosition(SizeF oldMenuSize, SizeF menuSize)
{
    auto menuWrapper = GetMenuWrapper();
    CHECK_NULL_VOID(menuWrapper);
    auto menuWrapperPattern = menuWrapper->GetPattern<MenuWrapperPattern>();
    CHECK_NULL_VOID(menuWrapperPattern);

    auto topMenu = menuWrapperPattern->GetMenu();
    CHECK_NULL_VOID(topMenu);
    auto menuPattern = topMenu->GetPattern<MenuPattern>();
    CHECK_NULL_VOID(menuPattern && menuPattern->GetPreviewMode() != MenuPreviewMode::NONE);

    auto placement = menuPattern->GetLastPlacement().value_or(Placement::NONE);
    auto isTopMenuBottomPreview =
        placement == Placement::TOP || placement == Placement::TOP_LEFT || placement == Placement::TOP_RIGHT;

    auto offsetY = menuSize.Height() - oldMenuSize.Height();
    CHECK_NULL_VOID(isTopMenuBottomPreview && !NearZero(offsetY));

    auto preview = AceType::DynamicCast<FrameNode>(menuWrapper->GetChildAtIndex(1));
    CHECK_NULL_VOID(preview);
    auto tag = preview->GetTag();
    auto isPreview = tag == V2::IMAGE_ETS_TAG || tag == V2::MENU_PREVIEW_ETS_TAG || tag == V2::FLEX_ETS_TAG;
    CHECK_NULL_VOID(isPreview);

    auto renderContext = preview->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    auto previewGeometryNode = preview->GetGeometryNode();
    CHECK_NULL_VOID(previewGeometryNode);

    auto offset = previewGeometryNode->GetFrameOffset();
    offset.AddY(offsetY);

    previewGeometryNode->SetFrameOffset(offset);
    renderContext->UpdatePosition(OffsetT<Dimension>(Dimension(offset.GetX()), Dimension(offset.GetY())));
    menuWrapperPattern->SetPreviewDisappearStartOffset(offset);

    auto pipeline = topMenu->GetContext();
    CHECK_NULL_VOID(pipeline);
    auto menuTheme = pipeline->GetTheme<NG::MenuTheme>();
    CHECK_NULL_VOID(menuTheme);
    menuPattern->InitPreviewMenuAnimationInfo(menuTheme);
    auto menuRenderContext = topMenu->GetRenderContext();
    CHECK_NULL_VOID(menuRenderContext);
    menuRenderContext->UpdateTransformCenter(DimensionOffset(GetTransformCenter(menuSize, placement)));
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
    AnimationUtils::Animate(option, [weak = WeakClaim(this), expandableNodeWk = WeakClaim(RawPtr(expandableNode))]() {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        auto expandableNode = expandableNodeWk.Upgrade();
        CHECK_NULL_VOID(expandableNode);
        pattern->SetShowEmbeddedMenuParams(expandableNode);
    });
}

void MenuItemPattern::SetShowEmbeddedMenuParams(const RefPtr<FrameNode>& expandableNode)
{
    CHECK_NULL_VOID(expandableNode);
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto rightRow = AceType::DynamicCast<FrameNode>(host->GetChildAtIndex(1));
    CHECK_NULL_VOID(rightRow);
    auto imageNode = AceType::DynamicCast<FrameNode>(rightRow->GetChildren().back());
    CHECK_NULL_VOID(imageNode);
    expandableNode->MountToParent(host, EXPANDABLE_AREA_VIEW_INDEX);
    auto imageContext = imageNode->GetRenderContext();
    CHECK_NULL_VOID(imageContext);
    imageContext->UpdateTransformRotate(Vector5F(0.0f, 0.0f, 1.0f, SEMI_CIRCLE_ANGEL, 0.0f));
    expandableNode->MarkModifyDone();
    expandableNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);

    auto menuItemPattern = host->GetPattern<MenuItemPattern>();
    CHECK_NULL_VOID(menuItemPattern);
    auto menuWrapper = menuItemPattern->GetMenuWrapper();
    CHECK_NULL_VOID(menuWrapper);
    auto menuWrapperPattern = menuWrapper->GetPattern<MenuWrapperPattern>();
    CHECK_NULL_VOID(menuWrapperPattern);

    auto topMenu = menuWrapperPattern->GetMenu();
    CHECK_NULL_VOID(topMenu);
    auto menuGeometryNode = topMenu->GetGeometryNode();
    CHECK_NULL_VOID(menuGeometryNode);
    auto oldMenuSize = menuGeometryNode->GetFrameSize();

    auto pipeline = host->GetContextWithCheck();
    CHECK_NULL_VOID(pipeline);
    pipeline->FlushUITasks();
    auto expandableAreaFrameSize = expandableNode->GetGeometryNode()->GetFrameSize();
    auto expandableAreaContext = expandableNode->GetRenderContext();
    CHECK_NULL_VOID(expandableAreaContext);
    expandableAreaContext->ClipWithRRect(
        RectF(0.0f, 0.0f, expandableAreaFrameSize.Width(), expandableAreaFrameSize.Height()),
        RadiusF(EdgeF(0.0f, 0.0f)));
    menuItemPattern->UpdatePreviewPosition(oldMenuSize, menuGeometryNode->GetFrameSize());
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

    AnimationUtils::Animate(option, [host, expandableNode, menuWrapperPattern]() {
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

        CHECK_NULL_VOID(menuWrapperPattern);
        auto topMenu = menuWrapperPattern->GetMenu();
        CHECK_NULL_VOID(topMenu);
        auto menuGeometryNode = topMenu->GetGeometryNode();
        CHECK_NULL_VOID(menuGeometryNode);
        auto oldMenuSize = menuGeometryNode->GetFrameSize();

        auto pipeline = PipelineContext::GetCurrentContext();
        CHECK_NULL_VOID(pipeline);
        pipeline->FlushUITasks();

        auto menuItemPattern = host->GetPattern<MenuItemPattern>();
        CHECK_NULL_VOID(menuItemPattern);
        menuItemPattern->UpdatePreviewPosition(oldMenuSize, menuGeometryNode->GetFrameSize());
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
            pattern->IsOptionPattern() ? pattern->OnSelectProcess() : pattern->OnClick();
        };
        onClickEvent_ = MakeRefPtr<ClickEvent>(std::move(event));
    }
    auto gestureHub = host->GetOrCreateGestureEventHub();
    CHECK_NULL_VOID(gestureHub);
    if (!isOptionPattern_ && expandingMode_ == SubMenuExpandingMode::EMBEDDED && clickableArea_) {
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
            pattern->IsOptionPattern() ? pattern->OnPress(info) : pattern->OnTouch(info);
        };
        onTouchEvent_ = MakeRefPtr<TouchEventImpl>(std::move(touchCallback));
    }
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto gestureHub = host->GetOrCreateGestureEventHub();
    CHECK_NULL_VOID(gestureHub);
    if (!isOptionPattern_ && expandingMode_ == SubMenuExpandingMode::EMBEDDED && clickableArea_) {
        auto clickableAreaGestureHub = clickableArea_->GetOrCreateGestureEventHub();
        CHECK_NULL_VOID(clickableAreaGestureHub);
        gestureHub->RemoveTouchEvent(onTouchEvent_);
        clickableAreaGestureHub->AddTouchEvent(onTouchEvent_);
    } else if (!onTouchEventSet_) {
        gestureHub->AddTouchEvent(onTouchEvent_);
        onTouchEventSet_ = true;
    }
}

void MenuItemPattern::UpdateTextMarquee(bool isMarqueeStart)
{
    CHECK_NULL_VOID(content_ && isTextFadeOut_);
    auto textLayoutProperty = content_->GetLayoutProperty<TextLayoutProperty>();
    CHECK_NULL_VOID(textLayoutProperty);
    if (textLayoutProperty) {
        textLayoutProperty->UpdateTextOverflow(TextOverflow::MARQUEE);
        textLayoutProperty->UpdateTextMarqueeFadeout(true);
        textLayoutProperty->UpdateTextMarqueeStart(isMarqueeStart);
        textLayoutProperty->UpdateTextMarqueeStartPolicy(MarqueeStartPolicy::DEFAULT);
        content_->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    }
}

void MenuItemPattern::RegisterOnHover()
{
    if (!onHoverEvent_) {
        auto mouseTask = [weak = WeakClaim(this)](bool isHover) {
            auto pattern = weak.Upgrade();
            CHECK_NULL_VOID(pattern);
            pattern->OnHover(isHover);
            pattern->UpdateTextMarquee(isHover || pattern->isFocused_);
        };
        onHoverEvent_ = MakeRefPtr<InputEvent>(std::move(mouseTask));
    }
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto inputHub = host->GetOrCreateInputEventHub();
    CHECK_NULL_VOID(inputHub);
    if (!isOptionPattern_ && expandingMode_ == SubMenuExpandingMode::EMBEDDED && clickableArea_) {
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
    if (!isOptionPattern_ && expandingMode_ == SubMenuExpandingMode::EMBEDDED && clickableArea_) {
        auto clickableAreaFocusHub = clickableArea_->GetOrCreateFocusHub();
        CHECK_NULL_VOID(clickableAreaFocusHub);
        focusHub->SetOnKeyEventInternal(nullptr);
        clickableAreaFocusHub->SetOnKeyEventInternal(event);
    } else if (!onKeyEventSet_) {
        focusHub->SetOnKeyEventInternal(event);
        onKeyEventSet_ = true;
    }
}

bool MenuItemPattern::OnClick()
{
    TAG_LOGD(AceLogTag::ACE_MENU, "MenuItem index:%{public}d receive click event", index_);
    auto host = GetHost();
    CHECK_NULL_RETURN(host, false);
    if (onClickAIMenuItem_) {
        onClickAIMenuItem_();
    }
    auto menuWrapper = GetMenuWrapper();
    auto menuWrapperPattern = menuWrapper ? menuWrapper->GetPattern<MenuWrapperPattern>() : nullptr;
    auto hasSubMenu = menuWrapperPattern ? menuWrapperPattern->HasStackSubMenu() : false;
    if (expandingMode_ == SubMenuExpandingMode::STACK && !IsSubMenu() && hasSubMenu) {
        return true;
    }
    if (expandingMode_ == SubMenuExpandingMode::STACK && IsStackSubmenuHeader()) {
        menuWrapperPattern->HideSubMenu();
        return true;
    }
    auto hub = host->GetEventHub<MenuItemEventHub>();
    CHECK_NULL_RETURN(hub, false);
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
    auto menuNode = GetMenu();
    CHECK_NULL_RETURN(menuNode, false);
    auto menuPattern = menuNode->GetPattern<MenuPattern>();
    CHECK_NULL_RETURN(menuPattern, false);
    auto lastSelectedItem = menuPattern->GetLastSelectedItem();
    if (lastSelectedItem && lastSelectedItem != host) {
        auto pattern = lastSelectedItem->GetPattern<MenuItemPattern>();
        CHECK_NULL_RETURN(pattern, false);
        pattern->SetChange();
    }
    menuPattern->SetLastSelectedItem(host);
    if (GetSubBuilder() != nullptr && (expandingMode_ == SubMenuExpandingMode::SIDE ||
        (expandingMode_ == SubMenuExpandingMode::STACK && !IsSubMenu() && !hasSubMenu) ||
        (expandingMode_ == SubMenuExpandingMode::EMBEDDED && !IsEmbedded()))) {
        ShowSubMenu(ShowSubMenuType::CLICK);
        return true;
    }
    // hide menu when menu item is clicked
    CloseMenu();
    return true;
}

void MenuItemPattern::OnTouch(const TouchEventInfo& info)
{
    TAG_LOGD(AceLogTag::ACE_MENU, "MenuItem index:%{public}d receive touch event", index_);
    auto menuWrapper = GetMenuWrapper();
    // When menu wrapper exists, the pressed state is handed over to the menu wrapper
    if (menuWrapper && menuWrapper->GetTag() == V2::MENU_WRAPPER_ETS_TAG) {
        return;
    }
    // change menu item paint props on press
    const auto& touches = info.GetTouches();
    CHECK_EQUAL_VOID(touches.empty(), true);
    auto touchType = touches.front().GetTouchType();
    if (touchType == TouchType::DOWN) {
        // change background color, update press status
        NotifyPressStatus(true);
        UpdateTextMarquee(false);
    } else if (touchType == TouchType::UP) {
        NotifyPressStatus(false);
        UpdateTextMarquee(true);
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
    TAG_LOGD(AceLogTag::ACE_MENU, "Custom MenuItem receive touch event");
    const auto& touches = info.GetTouches();
    CHECK_EQUAL_VOID(touches.empty(), true);
    auto touchType = touches.front().GetTouchType();

    // close menu when touch up
    // can't use onClick because that conflicts with interactions developers might set to the customNode
    // recognize gesture as click if touch up position is close to last touch down position
    if (touchType == TouchType::DOWN) {
        lastTouchOffset_ = std::make_unique<Offset>(touches.front().GetLocalLocation());
    } else if (touchType == TouchType::UP) {
        auto touchUpOffset = touches.front().GetLocalLocation();
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
    SetIsHover(isHover);
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto theme = pipeline->GetTheme<SelectTheme>();
    CHECK_NULL_VOID(theme);
    if (isOptionPattern_) {
        SetBgBlendColor(isHover ? theme->GetHoverColor() : Color::TRANSPARENT);
        auto props = GetPaintProperty<MenuItemPaintProperty>();
        CHECK_NULL_VOID(props);
        props->UpdateHover(isHover);
        host->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
        if (isHover || !IsSelected()) {
            UpdateNextNodeDivider(!isHover);
        }
        PlayBgColorAnimation();
    } else {
        auto menu = GetMenu(false);
        CHECK_NULL_VOID(menu);
        auto menuPattern = menu->GetPattern<MenuPattern>();
        CHECK_NULL_VOID(menuPattern);
        auto props = GetPaintProperty<MenuItemPaintProperty>();
        CHECK_NULL_VOID(props);
        auto parent = AceType::DynamicCast<UINode>(host->GetParent());
        SetBgBlendColor(isHover || isSubMenuShowed_ ? theme->GetHoverColor() : Color::TRANSPARENT);
        props->UpdateHover(isHover || isSubMenuShowed_);
        if (isHover || isSubMenuShowed_) {
            ShowSubMenu(ShowSubMenuType::HOVER);
        }
        menuPattern->OnItemPressed(parent, index_, isHover || isSubMenuShowed_, true);
        PlayBgColorAnimation();
        host->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
    }
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
        isOptionPattern_ ? OnSelectProcess() : focusHub->OnClick(event);
        return true;
    }
    if (!isOptionPattern_ && event.code == KeyCode::KEY_DPAD_RIGHT && GetSubBuilder() && !isSubMenuShowed_) {
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
    if (isOptionPattern_
        && (event.code == KeyCode::KEY_MOVE_HOME || event.code == KeyCode::KEY_MOVE_END) && IsSelectOption()) {
        return UpdateOptionFocus(event.code);
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
        if (pattern->IsOptionPattern()) {
            auto host = pattern->GetHost();
            CHECK_NULL_VOID(host);
            auto renderContext = host->GetRenderContext();
            CHECK_NULL_VOID(renderContext);
            renderContext->BlendBgColor(pattern->GetBgBlendColor());
        } else {
            auto clickableArea = pattern->GetClickableArea();
            CHECK_NULL_VOID(clickableArea);
            auto renderContext = clickableArea->GetRenderContext();
            CHECK_NULL_VOID(renderContext);
            renderContext->BlendBgColor(pattern->GetBgBlendColor());
        }
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
        Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_TWELVE) && SystemProperties::IsNeedSymbol()) {
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
        Ace::NG::UpdateIconSrc(selectIcon, selectTheme->GetIconSideLength(), selectTheme->GetIconSideLength(),
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
        Ace::NG::UpdateIconSrc(selectIcon, selectTheme->GetIconSideLength(), selectTheme->GetIconSideLength(),
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
            Container::LessThanAPITargetVersion(PlatformVersion::VERSION_TWELVE) || !SystemProperties::IsNeedSymbol()) {
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
    Ace::NG::UpdateIconSrc(expandIcon_, selectTheme->GetIconSideLength(), selectTheme->GetIconSideLength(),
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
        auto hostAccessibilityProperty = host->GetAccessibilityProperty<AccessibilityProperty>();
        CHECK_NULL_VOID(hostAccessibilityProperty);
        hostAccessibilityProperty->SetAccessibilityLevel(AccessibilityProperty::Level::NO_STR);
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
        Ace::NG::UpdateIconSrc(iconNode, iconWidth, iconHeight, selectTheme->GetMenuIconColor(), useDefaultThemeIcon);
    }
}

bool MenuItemPattern::UseDefaultThemeIcon(const ImageSourceInfo& imageSourceInfo)
{
    if (imageSourceInfo.IsSvg()) {
        auto src = imageSourceInfo.GetSrc();
        auto srcId = src.substr(SYSTEM_RESOURCE_PREFIX.size(),
            src.substr(0, src.rfind(".svg")).size() - SYSTEM_RESOURCE_PREFIX.size());
        if ((srcId.find("ohos_") != std::string::npos) || (srcId.find("public_") != std::string::npos)) {
            return true;
        }
        uint64_t parsedSrcId = StringUtils::StringToLongUint(srcId);
        return (parsedSrcId != 0
            && (parsedSrcId >= MIN_SYSTEM_RESOURCE_ID)
            && (parsedSrcId <= MAX_SYSTEM_RESOURCE_ID));
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
        Ace::NG::UpdateIconSrc(iconNode, iconWidth, iconHeight, selectTheme->GetMenuIconColor(), false);
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
    CHECK_NULL_VOID(node);
    auto textProperty = node->GetLayoutProperty<TextLayoutProperty>();
    CHECK_NULL_VOID(textProperty);
    auto renderContext = node->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    renderContext->UpdateClipEdge(isTextFadeOut_);
    auto context = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(context);
    auto theme = context->GetTheme<SelectTheme>();
    CHECK_NULL_VOID(theme);
    auto layoutDirection = textProperty->GetNonAutoLayoutDirection();
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
    }
    textProperty->UpdateTextAlign(textAlign);
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
    if (isTextFadeOut_) {
        textProperty->UpdateMaxLines(1);
        textProperty->UpdateTextOverflow(TextOverflow::MARQUEE);
        textProperty->UpdateTextMarqueeStartPolicy(MarqueeStartPolicy::DEFAULT);
        textProperty->UpdateTextMarqueeFadeout(true);
        textProperty->UpdateTextMarqueeStart(false);
    }
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
        if (pattern->IsOptionPattern()) {
            pattern->OnSelectProcess();
        } else {
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
        }
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
    } else {
        eventHub->SetCurrentUIState(UI_STATE_SELECTED, isSelected);
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
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto context = host->GetContext();
    CHECK_NULL_VOID(context);
    auto selectTheme = context->GetTheme<SelectTheme>();
    CHECK_NULL_VOID(selectTheme);
    auto hasDivider = divider.has_value();
    auto isDefaultShowDivider = selectTheme->GetDefaultShowDivider();
    if (hasDivider || isDefaultShowDivider) {
        auto paintProperty = host->GetPaintProperty<MenuItemPaintProperty>();
        CHECK_NULL_VOID(paintProperty);
        auto strokeWidth = hasDivider ? divider->strokeWidth : selectTheme->GetDefaultDividerWidth();
        auto startMargin = hasDivider ? divider->startMargin : selectTheme->GetDefaultDividerStartMargin();
        auto endMargin = hasDivider ? divider->endMargin : selectTheme->GetDefaultDividerEndMargin();
        auto color = hasDivider ? divider->color : selectTheme->GetLineColor();
        paintProperty->UpdateStrokeWidth(strokeWidth);
        paintProperty->UpdateStartMargin(startMargin);
        paintProperty->UpdateEndMargin(endMargin);
        paintProperty->UpdateDividerColor(color);
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

void MenuItemPattern::SetBgColor(const Color& color)
{
    auto renderContext = GetHost()->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    renderContext->UpdateBackgroundColor(color);
    bgColor_ = color;
}

void MenuItemPattern::SetFontColor(const Color& color)
{
    CHECK_NULL_VOID(text_);
    auto props = text_->GetLayoutProperty<TextLayoutProperty>();
    CHECK_NULL_VOID(props);
    text_->MarkModifyDone();
    props->UpdateTextColor(color);
    auto context = text_->GetRenderContext();
    CHECK_NULL_VOID(context);
    context->UpdateForegroundColor(color);
    context->UpdateForegroundColorFlag(false);
    context->ResetForegroundColorStrategy();
}

void MenuItemPattern::SetFontSize(const Dimension& value)
{
    CHECK_NULL_VOID(text_);
    auto props = text_->GetLayoutProperty<TextLayoutProperty>();
    CHECK_NULL_VOID(props);
    text_->MarkModifyDone();
    CHECK_NULL_VOID(selectTheme_);
    props->UpdateFontSize(value.IsNegative() ? selectTheme_->GetMenuFontSize() : value);
}

void MenuItemPattern::SetFontWeight(const FontWeight& value)
{
    CHECK_NULL_VOID(text_);
    auto props = text_->GetLayoutProperty<TextLayoutProperty>();
    CHECK_NULL_VOID(props);
    text_->MarkModifyDone();
    props->UpdateFontWeight(value);
}

void MenuItemPattern::SetFontFamily(const std::vector<std::string>& value)
{
    CHECK_NULL_VOID(text_);
    auto props = text_->GetLayoutProperty<TextLayoutProperty>();
    CHECK_NULL_VOID(props);
    text_->MarkModifyDone();
    props->UpdateFontFamily(value);
}

void MenuItemPattern::SetItalicFontStyle(const Ace::FontStyle& value)
{
    CHECK_NULL_VOID(text_);
    auto props = text_->GetLayoutProperty<TextLayoutProperty>();
    CHECK_NULL_VOID(props);
    text_->MarkModifyDone();
    props->UpdateItalicFontStyle(value);
}

void MenuItemPattern::SetBorderColor(const Color& color)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto renderContext = host->GetRenderContext();
    CHECK_NULL_VOID(renderContext);

    BorderColorProperty borderColor;
    borderColor.SetColor(color);
    renderContext->UpdateBorderColor(borderColor);
}

void MenuItemPattern::SetBorderWidth(const Dimension& value)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto renderContext = host->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    BorderWidthProperty borderWidth;
    borderWidth.SetBorderWidth(value);
    auto layoutProp = host->GetLayoutProperty();
    CHECK_NULL_VOID(layoutProp);
    layoutProp->UpdateBorderWidth(borderWidth);
    renderContext->UpdateBorderWidth(borderWidth);
}

Color MenuItemPattern::GetBorderColor() const
{
    return Color::TRANSPARENT;
}

Dimension MenuItemPattern::GetBorderWidth() const
{
    return BORDER_DEFAULT_WIDTH;
}

void MenuItemPattern::UpdateIconSrc()
{
    if (icon_ == nullptr || iconSrc_.empty()) {
        return;
    }
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto selectTheme = pipeline->GetTheme<SelectTheme>();
    CHECK_NULL_VOID(selectTheme);
    ImageSourceInfo imageSourceInfo(iconSrc_);
    bool useDefaultIcon = UseDefaultThemeIcon(imageSourceInfo);
    if (useDefaultIcon) {
        auto iconRenderProperty = icon_->GetPaintProperty<ImageRenderProperty>();
        CHECK_NULL_VOID(iconRenderProperty);
        iconRenderProperty->UpdateSvgFillColor(selectTheme->GetMenuIconColor());
    }
}

void MenuItemPattern::UpdateNextNodeDivider(bool needDivider)
{
    auto host = GetHost();
    // find next option node from parent menuNode
    CHECK_NULL_VOID(host);
    auto parent = host->GetParent();
    CHECK_NULL_VOID(parent);
    auto nextNode = parent->GetChildAtIndex(index_ + 1);
    if (nextNode) {
        auto pattern = DynamicCast<FrameNode>(nextNode)->GetPattern<MenuItemPattern>();
        CHECK_NULL_VOID(pattern);
        if (pattern->IsSelected()) {
            return;
        }
        if (!InstanceOf<FrameNode>(nextNode)) {
            LOGW("next optionNode is not a frameNode! type = %{public}s", nextNode->GetTag().c_str());
            return;
        }
        auto props = DynamicCast<FrameNode>(nextNode)->GetPaintProperty<MenuItemPaintProperty>();
        CHECK_NULL_VOID(props);
        props->UpdateNeedDivider(needDivider);
        nextNode->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
    }
}

void MenuItemPattern::UpdateText(const std::string& content)
{
    CHECK_NULL_VOID(text_);
    auto props = text_->GetLayoutProperty<TextLayoutProperty>();
    CHECK_NULL_VOID(props);
    props->UpdateContent(content);
    text_->MarkModifyDone();
    text_->MarkDirtyNode();
}

void MenuItemPattern::UpdateIcon(const std::string& src, const std::function<void(WeakPtr<NG::FrameNode>)> symbolIcon)
{
    iconSrc_ = src;
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    RefPtr<FrameNode> row =
        host->GetChildAtIndex(0) ? AceType::DynamicCast<FrameNode>(host->GetChildAtIndex(0)) : nullptr;
    CHECK_NULL_VOID(row);
    if (symbolIcon && (!icon_ || icon_->GetTag() != V2::SYMBOL_ETS_TAG)) {
        icon_ = MenuView::CreateSymbol(symbolIcon, row, icon_);
        row->MarkModifyDone();
        row->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
        return;
    } else if (symbolIcon == nullptr && !src.empty() && (!icon_ || icon_->GetTag() != V2::IMAGE_ETS_TAG)) {
        icon_ = MenuView::CreateIcon(src, row, icon_);
        row->MarkModifyDone();
        row->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
        return;
    } else if (icon_) {
        if (symbolIcon != nullptr) {
            symbolIcon(AccessibilityManager::WeakClaim(AccessibilityManager::RawPtr(icon_)));
            icon_->MarkModifyDone();
            icon_->MarkDirtyNode();
            return;
        } else if (!src.empty()) {
            auto props = icon_->GetLayoutProperty<ImageLayoutProperty>();
            CHECK_NULL_VOID(props);
            auto imageSrcInfo = props->GetImageSourceInfo();
            CHECK_NULL_VOID(imageSrcInfo);
            imageSrcInfo->SetSrc(src);
            props->UpdateImageSourceInfo(imageSrcInfo.value());
            icon_->MarkModifyDone();
            icon_->MarkDirtyNode();
            return;
        }
    }
  
    row->RemoveChild(icon_); // it's safe even if icon_ is nullptr
    row->MarkModifyDone();
    row->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    icon_ = nullptr;
}

Ace::FontStyle MenuItemPattern::GetItalicFontStyle()
{
    CHECK_NULL_RETURN(text_, Ace::FontStyle());
    auto props = text_->GetLayoutProperty<TextLayoutProperty>();
    CHECK_NULL_RETURN(props, Ace::FontStyle());
    auto defaultStyle = textTheme_->GetTextStyle().GetFontStyle();
    return props->GetItalicFontStyleValue(defaultStyle);
}

Color MenuItemPattern::GetBgColor()
{
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_RETURN(pipeline, Color());
    auto theme = pipeline->GetTheme<SelectTheme>();
    CHECK_NULL_RETURN(theme, Color());
    auto bgColor = Container::GreatOrEqualAPIVersion(PlatformVersion::VERSION_ELEVEN) ? Color::TRANSPARENT
                                                                                      : theme->GetBackgroundColor();
    return bgColor_.value_or(bgColor);
}

Color MenuItemPattern::GetFontColor()
{
    CHECK_NULL_RETURN(text_, Color::TRANSPARENT);
    auto props = text_->GetLayoutProperty<TextLayoutProperty>();
    CHECK_NULL_RETURN(props, Color::TRANSPARENT);
    auto defaultColor = selectTheme_->GetMenuFontColor();
    return props->GetTextColorValue(defaultColor);
}

Dimension MenuItemPattern::GetFontSize()
{
    CHECK_NULL_RETURN(text_, Dimension());
    auto props = text_->GetLayoutProperty<TextLayoutProperty>();
    CHECK_NULL_RETURN(props, Dimension());
    CHECK_NULL_RETURN(selectTheme_, Dimension());
    auto defaultSize = selectTheme_->GetMenuFontSize();
    return props->GetFontSizeValue(defaultSize);
}

float MenuItemPattern::GetSelectOptionWidth()
{
    RefPtr<GridColumnInfo> columnInfo = GridSystemManager::GetInstance().GetInfoByType(GridColumnType::MENU);
    auto parent = columnInfo->GetParent();
    CHECK_NULL_RETURN(parent, MIN_OPTION_WIDTH.ConvertToPx());
    parent->BuildColumnWidth();
    auto defaultWidth = static_cast<float>(columnInfo->GetWidth(COLUMN_NUM)) - OPTION_MARGIN.ConvertToPx();
    auto optionNode = GetHost();
    CHECK_NULL_RETURN(optionNode, MIN_OPTION_WIDTH.ConvertToPx());
    float finalWidth = MIN_OPTION_WIDTH.ConvertToPx();
    
    if (IsWidthModifiedBySelect()) {
        auto optionPatintProperty = optionNode->GetPaintProperty<MenuItemPaintProperty>();
        CHECK_NULL_RETURN(optionPatintProperty, MIN_OPTION_WIDTH.ConvertToPx());
        auto selectmodifiedwidth = optionPatintProperty->GetSelectModifiedWidth();
        finalWidth = selectmodifiedwidth.value();
    } else {
        finalWidth = defaultWidth;
    }
    
    if (finalWidth < MIN_OPTION_WIDTH.ConvertToPx()) {
        finalWidth = defaultWidth;
    }

    return finalWidth;
}

FontWeight MenuItemPattern::GetFontWeight()
{
    CHECK_NULL_RETURN(text_, FontWeight());
    auto props = text_->GetLayoutProperty<TextLayoutProperty>();
    CHECK_NULL_RETURN(props, FontWeight());
    auto defaultWeight = textTheme_->GetTextStyle().GetFontWeight();
    return props->GetFontWeightValue(defaultWeight);
}

std::vector<std::string> MenuItemPattern::GetFontFamily()
{
    CHECK_NULL_RETURN(text_, std::vector<std::string>());
    auto props = text_->GetLayoutProperty<TextLayoutProperty>();
    CHECK_NULL_RETURN(props, std::vector<std::string>());
    auto defaultFamily = textTheme_->GetTextStyle().GetFontFamilies();
    return props->GetFontFamilyValue(defaultFamily);
}

std::string MenuItemPattern::GetText()
{
    CHECK_NULL_RETURN(text_, std::string());
    auto textProps = text_->GetLayoutProperty<TextLayoutProperty>();
    CHECK_NULL_RETURN(textProps, std::string());
    return UtfUtils::Str16ToStr8(textProps->GetContentValue());
}

std::string MenuItemPattern::InspectorGetFont()
{
    CHECK_NULL_RETURN(text_, "");
    auto props = text_->GetLayoutProperty<TextLayoutProperty>();
    CHECK_NULL_RETURN(props, "");
    return props->InspectorGetTextFont();
}

void MenuItemPattern::OnPress(const TouchEventInfo& info)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    const auto& renderContext = host->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    auto props = GetPaintProperty<MenuItemPaintProperty>();
    CHECK_NULL_VOID(props);
    const auto& touches = info.GetTouches();
    CHECK_EQUAL_VOID(touches.empty(), true);
    auto touchType = touches.front().GetTouchType();

    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto theme = pipeline->GetTheme<SelectTheme>();
    // enter press status
    if (touchType == TouchType::DOWN) {
        // change background color, update press status
        SetBgBlendColor(theme ? theme->GetClickedColor() : DEFAULT_CLICKED_COLOR);
        PlayBgColorAnimation(false);

        props->UpdatePress(true);
        host->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
        // disable next option node's divider
        UpdateNextNodeDivider(false);
    } else if (touchType == TouchType::UP || touchType == TouchType::CANCEL) {
        // leave press status
        if (IsHover()) {
            SetBgBlendColor(theme ? theme->GetHoverColor() : DEFAULT_HOVER_COLOR);
        } else {
            SetBgBlendColor(Color::TRANSPARENT);
        }
        PlayBgColorAnimation(false);

        props->UpdatePress(false);
        host->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
        if (!IsSelected()) {
            UpdateNextNodeDivider(true);
        }
    }
}

bool MenuItemPattern::OnSelectProcess()
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, false);
    auto hub = host->GetEventHub<MenuItemEventHub>();
    CHECK_NULL_RETURN(hub, false);
    auto JsAction = hub->GetJsCallback();
    if (JsAction) {
        JsAction();
    }
    ClearFocusStyle();
    auto onSelect = hub->GetOnSelect();
    if (onSelect) {
        onSelect(index_);
    }
    host->OnAccessibilityEvent(AccessibilityEventType::SELECTED);
    // hide menu when option is clicked
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_RETURN(pipeline, false);
    auto overlayManager = pipeline->GetOverlayManager();
    CHECK_NULL_RETURN(overlayManager, false);
    auto menu = GetMenuWeak().Upgrade();
    CHECK_NULL_RETURN(menu, false);
    auto menuPattern = menu->GetPattern<MenuPattern>();
    CHECK_NULL_RETURN(menuPattern, false);
    if (!blockClick_) {
        menuPattern->HideMenu();
    }
    return true;
}

bool MenuItemPattern::UpdateOptionFocus(KeyCode code)
{
    auto meunNode = GetMenuWeak().Upgrade();
    CHECK_NULL_RETURN(meunNode, false);
    auto menuPattern = meunNode->GetPattern<MenuPattern>();
    CHECK_NULL_RETURN(menuPattern, false);
    auto options = menuPattern->GetOptions();
    if (!options.empty()) {
        auto optionNode = (code == KeyCode::KEY_MOVE_HOME) ? options.front() : options.back();
        auto eventHub = optionNode->GetOrCreateFocusHub();
        eventHub->RequestFocusImmediately();
        return true;
    }
    return false;
}

void MenuItemPattern::UpdatePasteFontColor(const Color& fontColor)
{
    CHECK_NULL_VOID(pasteButton_);
    auto property = pasteButton_->GetPaintProperty<SecurityComponentPaintProperty>();
    CHECK_NULL_VOID(property);
    property->UpdateFontColor(fontColor);
    pasteButton_->MarkModifyDone();
}

void MenuItemPattern::OptionOnModifyDone(const RefPtr<FrameNode>& host)
{
    auto context = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(context);
    textTheme_ = context->GetTheme<TextTheme>();
    CHECK_NULL_VOID(textTheme_);
    selectTheme_ = context->GetTheme<SelectTheme>();
    CHECK_NULL_VOID(selectTheme_);

    auto eventHub = host->GetEventHub<MenuItemEventHub>();
    CHECK_NULL_VOID(eventHub);
    UpdateIconSrc();
    if (!eventHub->IsEnabled()) {
        UpdatePasteDisabledOpacity(selectTheme_->GetDisabledFontColorAlpha());

        CHECK_NULL_VOID(text_);
        auto textRenderContext = text_->GetRenderContext();
        CHECK_NULL_VOID(textRenderContext);
        textRenderContext->UpdateOpacity(selectTheme_->GetDisabledFontColorAlpha());
        text_->MarkModifyDone();
        if (icon_) {
            icon_->GetRenderContext()->UpdateOpacity(selectTheme_->GetDisabledFontColorAlpha());
            icon_->MarkModifyDone();
        }
    } else {
        UpdatePasteFontColor(selectTheme_->GetMenuFontColor());
    }
    SetAccessibilityAction();
    InitFocusEvent();
}

void MenuItemPattern::UpdatePasteDisabledOpacity(const double disabledColorAlpha)
{
    CHECK_NULL_VOID(pasteButton_);
    auto pasteButtonRenderContext = pasteButton_->GetRenderContext();
    CHECK_NULL_VOID(pasteButtonRenderContext);
    pasteButtonRenderContext->UpdateOpacity(disabledColorAlpha);
    pasteButton_->MarkModifyDone();
}
} // namespace OHOS::Ace::NG
