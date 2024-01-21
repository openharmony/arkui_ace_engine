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

#include "core/components_ng/pattern/button/button_pattern.h"

#include "base/utils/utils.h"
#include "core/common/recorder/node_data_cache.h"
#include "core/components/button/button_theme.h"
#include "core/components/common/layout/constants.h"
#include "core/components/common/properties/color.h"
#include "core/components_ng/pattern/button/button_event_hub.h"
#include "core/components_ng/pattern/button/toggle_button_pattern.h"
#include "core/components_ng/pattern/text/text_layout_property.h"
#include "core/components_ng/property/property.h"
#include "core/event/mouse_event.h"
#include "core/pipeline/pipeline_base.h"

namespace OHOS::Ace::NG {
namespace {
constexpr int32_t TOUCH_DURATION = 100;
constexpr int32_t MOUSE_HOVER_DURATION = 250;
constexpr int32_t TYPE_TOUCH = 0;
constexpr int32_t TYPE_HOVER = 1;
constexpr int32_t TYPE_CANCEL = 2;

Color GetColorFromType(const RefPtr<ButtonTheme>& theme, const int32_t& type)
{
    if (type == TYPE_TOUCH) {
        return theme->GetClickedColor();
    } else if (type == TYPE_HOVER) {
        return theme->GetHoverColor();
    } else {
        return Color::TRANSPARENT;
    }
}
} // namespace

void ButtonPattern::OnAttachToFrameNode()
{
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto buttonTheme = pipeline->GetTheme<ButtonTheme>();
    CHECK_NULL_VOID(buttonTheme);
    clickedColor_ = buttonTheme->GetClickedColor();
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto renderContext = host->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    renderContext->SetAlphaOffscreen(true);
}

void ButtonPattern::UpdateTextLayoutProperty(
    RefPtr<ButtonLayoutProperty>& layoutProperty, RefPtr<TextLayoutProperty>& textLayoutProperty)
{
    CHECK_NULL_VOID(layoutProperty);
    CHECK_NULL_VOID(textLayoutProperty);

    auto label = layoutProperty->GetLabelValue("");
    textLayoutProperty->UpdateContent(label);
    if (layoutProperty->GetFontSize().has_value()) {
        textLayoutProperty->UpdateFontSize(layoutProperty->GetFontSize().value());
    }
    if (layoutProperty->GetFontWeight().has_value()) {
        textLayoutProperty->UpdateFontWeight(layoutProperty->GetFontWeight().value());
    }
    if (layoutProperty->GetFontColor().has_value()) {
        textLayoutProperty->UpdateTextColor(layoutProperty->GetFontColor().value());
    }
    if (layoutProperty->GetFontStyle().has_value()) {
        textLayoutProperty->UpdateItalicFontStyle(layoutProperty->GetFontStyle().value());
    }
    if (layoutProperty->GetFontFamily().has_value()) {
        textLayoutProperty->UpdateFontFamily(layoutProperty->GetFontFamily().value());
    }
    if (layoutProperty->GetTextOverflow().has_value()) {
        textLayoutProperty->UpdateTextOverflow(layoutProperty->GetTextOverflow().value());
    }
    if (layoutProperty->GetMaxLines().has_value()) {
        textLayoutProperty->UpdateMaxLines(layoutProperty->GetMaxLines().value());
    }
    if (layoutProperty->GetMinFontSize().has_value()) {
        textLayoutProperty->UpdateAdaptMinFontSize(layoutProperty->GetMinFontSize().value());
    }
    if (layoutProperty->GetMaxFontSize().has_value()) {
        textLayoutProperty->UpdateAdaptMaxFontSize(layoutProperty->GetMaxFontSize().value());
    }
    if (layoutProperty->GetHeightAdaptivePolicy().has_value()) {
        textLayoutProperty->UpdateHeightAdaptivePolicy(layoutProperty->GetHeightAdaptivePolicy().value());
    }
    // update text style defined by buttonStyle and control size
    UpdateTextStyle(layoutProperty, textLayoutProperty);
}

void ButtonPattern::UpdateTextStyle(
    RefPtr<ButtonLayoutProperty>& layoutProperty, RefPtr<TextLayoutProperty>& textLayoutProperty)
{
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto buttonTheme = pipeline->GetTheme<ButtonTheme>();
    CHECK_NULL_VOID(buttonTheme);
    if (!textLayoutProperty->HasTextColor()) {
        ButtonStyleMode buttonStyle = layoutProperty->GetButtonStyle().value_or(ButtonStyleMode::EMPHASIZE);
        Color fontColor = buttonTheme->GetTextColor(buttonStyle);
        textLayoutProperty->UpdateTextColor(fontColor);
    }
    if (!textLayoutProperty->HasFontSize()) {
        ControlSize controlSize = layoutProperty->GetControlSize().value_or(ControlSize::NORMAL);
        Dimension fontSize = buttonTheme->GetTextSize(controlSize);
        textLayoutProperty->UpdateFontSize(fontSize);
    }
}

bool ButtonPattern::IsNeedToHandleHoverOpacity()
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, false);
    auto inputEventHub = host->GetOrCreateInputEventHub();
    auto hoverEffect = inputEventHub->GetHoverEffect();
    return isHover_ && hoverEffect != HoverEffectType::BOARD && hoverEffect != HoverEffectType::SCALE &&
           hoverEffect != HoverEffectType::NONE;
}

void ButtonPattern::InitButtonLabel()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto focusHub = host->GetFocusHub();
    CHECK_NULL_VOID(focusHub);
    auto layoutProperty = GetLayoutProperty<ButtonLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    if (!layoutProperty->GetLabel().has_value()) {
        focusHub->SetFocusType(FocusType::SCOPE);
        return;
    }
    focusHub->SetFocusType(FocusType::NODE);
    auto textNode = DynamicCast<FrameNode>(host->GetFirstChild());
    CHECK_NULL_VOID(textNode);
    auto textLayoutProperty = textNode->GetLayoutProperty<TextLayoutProperty>();
    CHECK_NULL_VOID(textLayoutProperty);
    UpdateTextLayoutProperty(layoutProperty, textLayoutProperty);
    auto buttonRenderContext = host->GetRenderContext();
    CHECK_NULL_VOID(buttonRenderContext);
    auto textRenderContext = textNode->GetRenderContext();
    CHECK_NULL_VOID(textRenderContext);
    textRenderContext->UpdateClipEdge(buttonRenderContext->GetClipEdgeValue(true));
    textNode->MarkModifyDone();
    textNode->MarkDirtyNode();
}

void ButtonPattern::OnModifyDone()
{
    Pattern::OnModifyDone();
    InitButtonLabel();
    HandleBackgroundColor();
    HandleEnabled();
    InitHoverEvent();
    InitTouchEvent();
}

void ButtonPattern::InitTouchEvent()
{
    if (touchListener_) {
        return;
    }
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto gesture = host->GetOrCreateGestureEventHub();
    CHECK_NULL_VOID(gesture);
    auto touchCallback = [weak = WeakClaim(this)](const TouchEventInfo& info) {
        auto buttonPattern = weak.Upgrade();
        CHECK_NULL_VOID(buttonPattern);
        if (info.GetTouches().front().GetTouchType() == TouchType::DOWN) {
            buttonPattern->OnTouchDown();
        }
        if (info.GetTouches().front().GetTouchType() == TouchType::UP ||
            info.GetTouches().front().GetTouchType() == TouchType::CANCEL) {
            buttonPattern->OnTouchUp();
        }
    };
    touchListener_ = MakeRefPtr<TouchEventImpl>(std::move(touchCallback));
    gesture->AddTouchEvent(touchListener_);
}

void ButtonPattern::OnAfterModifyDone()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto inspectorId = host->GetInspectorId().value_or("");
    if (!inspectorId.empty()) {
        auto text = host->GetAccessibilityProperty<NG::AccessibilityProperty>()->GetText();
        Recorder::NodeDataCache::Get().PutString(inspectorId, text);
    }
}

void ButtonPattern::InitHoverEvent()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto eventHub = host->GetEventHub<ButtonEventHub>();
    auto inputHub = eventHub->GetOrCreateInputEventHub();
    auto hoverEffect = inputHub->GetHoverEffect();
    inputHub->SetHoverEffect(hoverEffect == HoverEffectType::BOARD ? HoverEffectType::AUTO : hoverEffect);
    if (hoverListener_) {
        return;
    }
    auto hoverTask = [weak = WeakClaim(this)](bool isHover) {
        auto pattern = weak.Upgrade();
        if (pattern) {
            pattern->HandleHoverEvent(isHover);
        }
    };

    hoverListener_ = MakeRefPtr<InputEvent>(std::move(hoverTask));
    inputHub->AddOnHoverEvent(hoverListener_);
}

void ButtonPattern::OnTouchDown()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto buttonEventHub = GetEventHub<ButtonEventHub>();
    CHECK_NULL_VOID(buttonEventHub);
    if (buttonEventHub->GetStateEffect()) {
        auto renderContext = host->GetRenderContext();
        CHECK_NULL_VOID(renderContext);
        backgroundColor_ = renderContext->GetBackgroundColor().value_or(Color::TRANSPARENT);
        if (isSetClickedColor_) {
            // for user self-defined
            renderContext->UpdateBackgroundColor(clickedColor_);
            return;
        }
        // for system default
        auto isNeedToHandleHoverOpacity = IsNeedToHandleHoverOpacity();
        AnimateTouchAndHover(renderContext, isNeedToHandleHoverOpacity ? TYPE_HOVER : TYPE_CANCEL, TYPE_TOUCH,
            TOUCH_DURATION, isNeedToHandleHoverOpacity ? Curves::SHARP : Curves::FRICTION);
    }
}

void ButtonPattern::OnTouchUp()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto buttonEventHub = GetEventHub<ButtonEventHub>();
    CHECK_NULL_VOID(buttonEventHub);
    auto toggleButtonPattern = host->GetPattern<ToggleButtonPattern>();
    if (toggleButtonPattern) {
        toggleButtonPattern->OnClick();
    }
    if (buttonEventHub->GetStateEffect()) {
        auto renderContext = host->GetRenderContext();
        if (isSetClickedColor_) {
            renderContext->UpdateBackgroundColor(backgroundColor_);
            return;
        }
        if (buttonEventHub->IsEnabled()) {
            auto isNeedToHandleHoverOpacity = IsNeedToHandleHoverOpacity();
            AnimateTouchAndHover(renderContext, TYPE_TOUCH, isNeedToHandleHoverOpacity ? TYPE_HOVER : TYPE_CANCEL,
                TOUCH_DURATION, isNeedToHandleHoverOpacity ? Curves::SHARP : Curves::FRICTION);
        } else {
            AnimateTouchAndHover(renderContext, TYPE_TOUCH, TYPE_CANCEL, TOUCH_DURATION, Curves::FRICTION);
        }
    }
}

void ButtonPattern::HandleHoverEvent(bool isHover)
{
    isHover_ = isHover;
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto eventHub = host->GetEventHub<EventHub>();
    CHECK_NULL_VOID(eventHub);
    auto enabled = eventHub->IsEnabled();
    auto inputEventHub = host->GetOrCreateInputEventHub();
    auto hoverEffect = inputEventHub->GetHoverEffect();
    if (enabled && hoverEffect != HoverEffectType::NONE && hoverEffect != HoverEffectType::SCALE) {
        auto renderContext = host->GetRenderContext();
        CHECK_NULL_VOID(renderContext);
        AnimateTouchAndHover(renderContext, isHover ? TYPE_CANCEL : TYPE_HOVER, isHover ? TYPE_HOVER : TYPE_CANCEL,
            MOUSE_HOVER_DURATION, Curves::FRICTION);
    }
}

void ButtonPattern::HandleBackgroundColor()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto renderContext = host->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    auto layoutProperty = GetLayoutProperty<ButtonLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    auto buttonTheme = pipeline->GetTheme<ButtonTheme>();
    CHECK_NULL_VOID(buttonTheme);
    ButtonStyleMode buttonStyle = layoutProperty->GetButtonStyle().value_or(ButtonStyleMode::EMPHASIZE);
    if (!renderContext->HasBackgroundColor()) {
        renderContext->UpdateBackgroundColor(buttonTheme->GetBgColor(buttonStyle));
    }
    themeBgColor_ = buttonTheme->GetBgColor(buttonStyle);
    themeTextColor_ = buttonTheme->GetTextColor(buttonStyle);
}

void ButtonPattern::HandleEnabled()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto eventHub = host->GetEventHub<EventHub>();
    CHECK_NULL_VOID(eventHub);
    auto enabled = eventHub->IsEnabled();
    auto renderContext = host->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto theme = pipeline->GetTheme<ButtonTheme>();
    CHECK_NULL_VOID(theme);
    auto alpha = theme->GetBgDisabledAlpha();
    auto originalOpacity = renderContext->GetOpacityValue(1.0);
    renderContext->OnOpacityUpdate(enabled ? originalOpacity : alpha * originalOpacity);
}

void ButtonPattern::AnimateTouchAndHover(RefPtr<RenderContext>& renderContext, int32_t typeFrom, int32_t typeTo,
    int32_t duration, const RefPtr<Curve>& curve)
{
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto theme = pipeline->GetTheme<ButtonTheme>();
    CHECK_NULL_VOID(theme);
    Color blendColorFrom = GetColorFromType(theme, typeFrom);
    Color blendColorTo = GetColorFromType(theme, typeTo);
    renderContext->BlendBgColor(blendColorFrom);
    AnimationOption option = AnimationOption();
    option.SetDuration(duration);
    option.SetCurve(curve);
    AnimationUtils::Animate(option, [renderContext, blendColorTo]() { renderContext->BlendBgColor(blendColorTo); });
}

void ButtonPattern::OnColorConfigurationUpdate()
{
    auto node = GetHost();
    if (isColorUpdateFlag_) {
        node->SetNeedCallChildrenUpdate(false);
        return;
    }
    node->SetNeedCallChildrenUpdate(false);
    auto pipeline = PipelineBase::GetCurrentContext();
    auto buttonTheme = pipeline->GetTheme<ButtonTheme>();
    auto renderContext = node->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    auto buttonLayoutProperty = node->GetLayoutProperty<ButtonLayoutProperty>();
    CHECK_NULL_VOID(buttonLayoutProperty);
    ButtonStyleMode buttonStyle = buttonLayoutProperty->GetButtonStyle().value_or(ButtonStyleMode::EMPHASIZE);
    if (renderContext->GetBackgroundColor().value_or(themeBgColor_) == themeBgColor_) {
        auto color = buttonTheme->GetBgColor(buttonStyle);
        renderContext->UpdateBackgroundColor(color);
    }
    auto textNode = DynamicCast<FrameNode>(node->GetFirstChild());
    CHECK_NULL_VOID(textNode);
    auto textLayoutProperty = textNode->GetLayoutProperty<TextLayoutProperty>();
    CHECK_NULL_VOID(textLayoutProperty);
    if (textLayoutProperty->GetTextColor().value_or(themeTextColor_) == themeTextColor_) {
        textLayoutProperty->UpdateTextColor(buttonTheme->GetTextColor(buttonStyle));
        textNode->MarkDirtyNode();
    }
}
} // namespace OHOS::Ace::NG
