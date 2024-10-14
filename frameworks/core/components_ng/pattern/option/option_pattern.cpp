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

#include "core/components_ng/pattern/option/option_pattern.h"

#include "core/components/common/layout/grid_system_manager.h"
#include "core/components_ng/pattern/image/image_pattern.h"
#include "core/components_ng/pattern/option/option_view.h"
#include "core/components_ng/pattern/security_component/security_component_pattern.h"

namespace OHOS::Ace::NG {
namespace {
    constexpr Dimension MIN_OPTION_WIDTH = 56.0_vp;
    constexpr Dimension OPTION_MARGIN = 8.0_vp;
    constexpr int32_t COLUMN_NUM = 2;
    const std::string SYSTEM_RESOURCE_PREFIX = std::string("resource:///");
    // id of system resource start from 0x07000000
    constexpr unsigned long MIN_SYSTEM_RESOURCE_ID = 0x07000000;
    // id of system resource end to 0x07FFFFFF
    constexpr unsigned long MAX_SYSTEM_RESOURCE_ID = 0x07FFFFFF;
} // namespace

void OptionPattern::OnAttachToFrameNode()
{
    RegisterOnKeyEvent();
    RegisterOnClick();
    RegisterOnTouch();
    RegisterOnHover();
}

void OptionPattern::OnModifyDone()
{
    Pattern::OnModifyDone();
    auto context = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(context);
    textTheme_ = context->GetTheme<TextTheme>();
    CHECK_NULL_VOID(textTheme_);
    selectTheme_ = context->GetTheme<SelectTheme>();
    CHECK_NULL_VOID(selectTheme_);

    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto eventHub = host->GetEventHub<OptionEventHub>();
    CHECK_NULL_VOID(eventHub);
    UpdateIconSrc();
    if (!eventHub->IsEnabled()) {
        UpdatePasteFontColor(selectTheme_->GetDisabledMenuFontColor());
        CHECK_NULL_VOID(text_);
        text_->GetRenderContext()->UpdateForegroundColor(selectTheme_->GetDisabledMenuFontColor());
        auto textLayoutProperty = text_->GetLayoutProperty<TextLayoutProperty>();
        CHECK_NULL_VOID(textLayoutProperty);
        textLayoutProperty->UpdateTextColor(selectTheme_->GetDisabledMenuFontColor());
        text_->MarkModifyDone();
        if (icon_) {
            icon_->GetRenderContext()->UpdateOpacity(selectTheme_->GetDisabledFontColorAlpha());
            icon_->MarkModifyDone();
        }
    } else {
        UpdatePasteFontColor(selectTheme_->GetMenuFontColor());
    }
    SetAccessibilityAction();
}

bool OptionPattern::UseDefaultThemeIcon(const ImageSourceInfo& imageSourceInfo)
{
    if (imageSourceInfo.IsSvg()) {
        auto src = imageSourceInfo.GetSrc();
        auto srcId = src.substr(SYSTEM_RESOURCE_PREFIX.size(),
            src.substr(0, src.rfind(".svg")).size() - SYSTEM_RESOURCE_PREFIX.size());
        return (srcId.find("ic_") != std::string::npos)
            || ((std::all_of(srcId.begin(), srcId.end(), ::isdigit))
                && (std::stoul(srcId) >= MIN_SYSTEM_RESOURCE_ID)
                && (std::stoul(srcId) <= MAX_SYSTEM_RESOURCE_ID));
    }
    return false;
}

void OptionPattern::UpdateIconSrc()
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

void OptionPattern::UpdatePasteFontColor(const Color& fontColor)
{
    CHECK_NULL_VOID(pasteButton_);
    auto property = pasteButton_->GetPaintProperty<SecurityComponentPaintProperty>();
    CHECK_NULL_VOID(property);
    property->UpdateFontColor(fontColor);
    pasteButton_->MarkModifyDone();
}

void OptionPattern::OnSelectProcess()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto hub = host->GetEventHub<OptionEventHub>();
    CHECK_NULL_VOID(hub);
    auto JsAction = hub->GetJsCallback();
    if (JsAction) {
        JsAction();
    }
    auto onSelect = hub->GetOnSelect();
    if (onSelect) {
        onSelect(index_);
    }
    host->OnAccessibilityEvent(AccessibilityEventType::SELECTED);
    // hide menu when option is clicked
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto overlayManager = pipeline->GetOverlayManager();
    CHECK_NULL_VOID(overlayManager);
    auto menu = GetMenu().Upgrade();
    CHECK_NULL_VOID(menu);
    auto menuPattern = menu->GetPattern<MenuPattern>();
    CHECK_NULL_VOID(menuPattern);
    if (!blockClick_) {
        menuPattern->HideMenu();
    }
}

void OptionPattern::PlayBgColorAnimation(bool isHoverChange)
{
    AnimationOption option = AnimationOption();
    if (isHoverChange) {
        option.SetDuration(selectTheme_->GetHoverAnimationDuration());
        option.SetCurve(Curves::FRICTION);
    } else {
        option.SetDuration(selectTheme_->GetPressAnimationDuration());
        option.SetCurve(Curves::SHARP);
    }

    AnimationUtils::Animate(option, [weak = WeakClaim(this)]() {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        auto host = pattern->GetHost();
        CHECK_NULL_VOID(host);
        auto renderContext = host->GetRenderContext();
        CHECK_NULL_VOID(renderContext);
        renderContext->BlendBgColor(pattern->GetBgBlendColor());
    });
}

void OptionPattern::RegisterOnClick()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto hub = host->GetEventHub<OptionEventHub>();

    auto event = [weak = WeakClaim(this)](GestureEvent& /* info */) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        pattern->OnSelectProcess();
    };
    auto clickEvent = MakeRefPtr<ClickEvent>(std::move(event));

    auto gestureHub = host->GetOrCreateGestureEventHub();
    CHECK_NULL_VOID(gestureHub);
    gestureHub->AddClickEvent(clickEvent);
}

void OptionPattern::RegisterOnTouch()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto gestureHub = host->GetOrCreateGestureEventHub();
    CHECK_NULL_VOID(gestureHub);

    auto touchCallback = [weak = WeakClaim(this)](const TouchEventInfo& info) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        pattern->OnPress(info);
    };
    auto touchEvent = MakeRefPtr<TouchEventImpl>(std::move(touchCallback));
    gestureHub->AddTouchEvent(touchEvent);
}

void OptionPattern::RegisterOnHover()
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

void OptionPattern::RegisterOnKeyEvent()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto focusHub = host->GetOrCreateFocusHub();
    CHECK_NULL_VOID(focusHub);
    auto onKeyEvent = [wp = WeakClaim(this)](const KeyEvent& event) -> bool {
        auto pattern = wp.Upgrade();
        CHECK_NULL_RETURN(pattern, false);
        return pattern->OnKeyEvent(event);
    };
    focusHub->SetOnKeyEventInternal(std::move(onKeyEvent));
}

bool OptionPattern::OnKeyEvent(const KeyEvent& event)
{
    if (event.action != KeyAction::DOWN) {
        return false;
    }
    if (event.code == KeyCode::KEY_ENTER) {
        OnSelectProcess();
        return true;
    }
    if ((event.code == KeyCode::KEY_MOVE_HOME || event.code == KeyCode::KEY_MOVE_END) && IsSelectOption()) {
        return UpdateOptionFocus(event.code);
    }
    return false;
}

bool OptionPattern::UpdateOptionFocus(KeyCode code)
{
    auto meunNode = GetMenu().Upgrade();
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

void OptionPattern::OnPress(const TouchEventInfo& info)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    const auto& renderContext = host->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    auto props = GetPaintProperty<OptionPaintProperty>();
    CHECK_NULL_VOID(props);
    auto touchType = info.GetTouches().front().GetTouchType();

    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto theme = pipeline->GetTheme<SelectTheme>();
    // enter press status
    if (touchType == TouchType::DOWN) {
        // change background color, update press status
        SetBgBlendColor(theme->GetClickedColor());
        PlayBgColorAnimation(false);

        props->UpdatePress(true);
        host->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
        // disable next option node's divider
        UpdateNextNodeDivider(false);
    } else if (touchType == TouchType::UP || touchType == TouchType::CANCEL) {
        // leave press status
        if (IsHover()) {
            SetBgBlendColor(theme->GetHoverColor());
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

void OptionPattern::OnHover(bool isHover)
{
    SetIsHover(isHover);

    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto renderContext = host->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    auto props = GetPaintProperty<OptionPaintProperty>();
    CHECK_NULL_VOID(props);
    if (isHover) {
        auto pipeline = PipelineContext::GetCurrentContext();
        CHECK_NULL_VOID(pipeline);
        auto theme = pipeline->GetTheme<SelectTheme>();
        auto hoverColor = theme->GetHoverColor();
        SetBgBlendColor(hoverColor);

        props->UpdateHover(true);
        host->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
        UpdateNextNodeDivider(false);
    } else {
        SetBgBlendColor(Color::TRANSPARENT);

        props->UpdateHover(false);
        host->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
        if (!IsSelected()) {
            UpdateNextNodeDivider(true);
        }
    }
    PlayBgColorAnimation();
}

void OptionPattern::UpdateNextNodeDivider(bool needDivider)
{
    auto host = GetHost();
    // find next option node from parent menuNode
    CHECK_NULL_VOID(host);
    auto parent = host->GetParent();
    CHECK_NULL_VOID(parent);
    auto nextNode = parent->GetChildAtIndex(index_ + 1);
    if (nextNode) {
        auto pattern = DynamicCast<FrameNode>(nextNode)->GetPattern<OptionPattern>();
        CHECK_NULL_VOID(pattern);
        if (pattern->IsSelected()) {
            return;
        }
        if (!InstanceOf<FrameNode>(nextNode)) {
            LOGW("next optionNode is not a frameNode! type = %{public}s", nextNode->GetTag().c_str());
            return;
        }
        auto props = DynamicCast<FrameNode>(nextNode)->GetPaintProperty<OptionPaintProperty>();
        CHECK_NULL_VOID(props);
        props->UpdateNeedDivider(needDivider);
        nextNode->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
    }
}

void OptionPattern::SetBgColor(const Color& color)
{
    auto renderContext = GetHost()->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    renderContext->UpdateBackgroundColor(color);
    bgColor_ = color;
}

void OptionPattern::SetFontSize(const Dimension& value)
{
    CHECK_NULL_VOID(text_);
    auto props = text_->GetLayoutProperty<TextLayoutProperty>();
    CHECK_NULL_VOID(props);
    text_->MarkModifyDone();
    CHECK_NULL_VOID(selectTheme_);
    props->UpdateFontSize(value.IsNegative() ? selectTheme_->GetMenuFontSize() : value);
}

void OptionPattern::SetItalicFontStyle(const Ace::FontStyle& value)
{
    CHECK_NULL_VOID(text_);
    auto props = text_->GetLayoutProperty<TextLayoutProperty>();
    CHECK_NULL_VOID(props);
    text_->MarkModifyDone();
    props->UpdateItalicFontStyle(value);
}

void OptionPattern::SetFontWeight(const FontWeight& value)
{
    CHECK_NULL_VOID(text_);
    auto props = text_->GetLayoutProperty<TextLayoutProperty>();
    CHECK_NULL_VOID(props);
    text_->MarkModifyDone();
    props->UpdateFontWeight(value);
}

void OptionPattern::SetFontFamily(const std::vector<std::string>& value)
{
    CHECK_NULL_VOID(text_);
    auto props = text_->GetLayoutProperty<TextLayoutProperty>();
    CHECK_NULL_VOID(props);
    text_->MarkModifyDone();
    props->UpdateFontFamily(value);
}

void OptionPattern::SetFontColor(const Color& color)
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

std::string OptionPattern::InspectorGetFont()
{
    CHECK_NULL_RETURN(text_, "");
    auto props = text_->GetLayoutProperty<TextLayoutProperty>();
    CHECK_NULL_RETURN(props, "");
    return props->InspectorGetTextFont();
}

Color OptionPattern::GetBgColor()
{
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_RETURN(pipeline, Color());
    auto theme = pipeline->GetTheme<SelectTheme>();
    CHECK_NULL_RETURN(theme, Color());
    auto bgColor = Container::GreatOrEqualAPIVersion(PlatformVersion::VERSION_ELEVEN) ? Color::TRANSPARENT
                                                                                      : theme->GetBackgroundColor();
    return bgColor_.value_or(bgColor);
}

Dimension OptionPattern::GetFontSize()
{
    CHECK_NULL_RETURN(text_, Dimension());
    auto props = text_->GetLayoutProperty<TextLayoutProperty>();
    CHECK_NULL_RETURN(props, Dimension());
    CHECK_NULL_RETURN(selectTheme_, Dimension());
    auto defaultSize = selectTheme_->GetMenuFontSize();
    return props->GetFontSizeValue(defaultSize);
}

Ace::FontStyle OptionPattern::GetItalicFontStyle()
{
    CHECK_NULL_RETURN(text_, Ace::FontStyle());
    auto props = text_->GetLayoutProperty<TextLayoutProperty>();
    CHECK_NULL_RETURN(props, Ace::FontStyle());
    auto defaultStyle = textTheme_->GetTextStyle().GetFontStyle();
    return props->GetItalicFontStyleValue(defaultStyle);
}

FontWeight OptionPattern::GetFontWeight()
{
    CHECK_NULL_RETURN(text_, FontWeight());
    auto props = text_->GetLayoutProperty<TextLayoutProperty>();
    CHECK_NULL_RETURN(props, FontWeight());
    auto defaultWeight = textTheme_->GetTextStyle().GetFontWeight();
    return props->GetFontWeightValue(defaultWeight);
}

std::vector<std::string> OptionPattern::GetFontFamily()
{
    CHECK_NULL_RETURN(text_, std::vector<std::string>());
    auto props = text_->GetLayoutProperty<TextLayoutProperty>();
    CHECK_NULL_RETURN(props, std::vector<std::string>());
    auto defaultFamily = textTheme_->GetTextStyle().GetFontFamilies();
    return props->GetFontFamilyValue(defaultFamily);
}

Color OptionPattern::GetFontColor()
{
    CHECK_NULL_RETURN(text_, Color::TRANSPARENT);
    auto props = text_->GetLayoutProperty<TextLayoutProperty>();
    CHECK_NULL_RETURN(props, Color::TRANSPARENT);
    auto defaultColor = selectTheme_->GetMenuFontColor();
    return props->GetTextColorValue(defaultColor);
}

std::string OptionPattern::GetText()
{
    CHECK_NULL_RETURN(text_, std::string());
    auto textProps = text_->GetLayoutProperty<TextLayoutProperty>();
    CHECK_NULL_RETURN(textProps, std::string());
    return textProps->GetContentValue();
}

void OptionPattern::UpdateText(const std::string& content)
{
    CHECK_NULL_VOID(text_);
    auto props = text_->GetLayoutProperty<TextLayoutProperty>();
    CHECK_NULL_VOID(props);
    props->UpdateContent(content);
    text_->MarkModifyDone();
    text_->MarkDirtyNode();
}

void OptionPattern::UpdateIcon(const std::string& src, const std::function<void(WeakPtr<NG::FrameNode>)> symbolIcon)
{
    iconSrc_ = src;
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    RefPtr<FrameNode> row =
        host->GetChildAtIndex(0) ? AceType::DynamicCast<FrameNode>(host->GetChildAtIndex(0)) : nullptr;
    CHECK_NULL_VOID(row);
    if (symbolIcon && (!icon_ || icon_->GetTag() != V2::SYMBOL_ETS_TAG)) {
        icon_ = OptionView::CreateSymbol(symbolIcon, row, icon_);
        row->MarkModifyDone();
        row->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
        return;
    } else if (symbolIcon == nullptr && !src.empty() && (!icon_ || icon_->GetTag() != V2::IMAGE_ETS_TAG)) {
        icon_ = OptionView::CreateIcon(src, row, icon_);
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

void OptionPattern::SetAccessibilityAction()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto accessibilityProperty = host->GetAccessibilityProperty<AccessibilityProperty>();
    CHECK_NULL_VOID(accessibilityProperty);
    accessibilityProperty->SetActionSelect([weakPtr = WeakClaim(this)]() {
        const auto& pattern = weakPtr.Upgrade();
        CHECK_NULL_VOID(pattern);
        pattern->OnSelectProcess();
    });
}

float OptionPattern::GetSelectOptionWidth()
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
        auto optionPatintProperty = optionNode->GetPaintProperty<OptionPaintProperty>();
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
} // namespace OHOS::Ace::NG
