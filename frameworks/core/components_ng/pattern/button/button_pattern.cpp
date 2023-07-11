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
#include "core/components/button/button_theme.h"
#include "core/components/common/layout/constants.h"
#include "core/components/common/properties/color.h"
#include "core/components_ng/pattern/button/button_event_hub.h"
#include "core/components_ng/pattern/button/toggle_button_pattern.h"
#include "core/components_ng/pattern/text/text_layout_property.h"
#include "core/components_ng/property/property.h"
#include "core/pipeline/pipeline_base.h"

namespace OHOS::Ace::NG {
namespace {
constexpr float HOVER_OPACITY = 0.05f;
constexpr float TOUCH_OPACITY = 0.1f;
constexpr int32_t HOVER_TO_TOUCH_DURATION = 100;
constexpr int32_t TOUCH_DURATION = 250;
} // namespace

void ButtonPattern::OnAttachToFrameNode()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    SetDefaultAttributes(host, pipeline);
    auto renderContext = host->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    auto buttonTheme = pipeline->GetTheme<ButtonTheme>();
    CHECK_NULL_VOID(buttonTheme);
    clickedColor_ = buttonTheme->GetClickedColor();
}

void ButtonPattern::SetDefaultAttributes(const RefPtr<FrameNode>& buttonNode, const RefPtr<PipelineBase>& pipeline)
{
    auto renderContext = buttonNode->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    auto buttonLayoutProperty = buttonNode->GetLayoutProperty<ButtonLayoutProperty>();
    CHECK_NULL_VOID(buttonLayoutProperty);
    auto buttonTheme = pipeline->GetTheme<ButtonTheme>();
    CHECK_NULL_VOID(buttonTheme);

    // Init button default style
    buttonLayoutProperty->UpdateType(ButtonType::CAPSULE);
    renderContext->UpdateBackgroundColor(buttonTheme->GetBgColor());
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
        LOGI("No label, no need to initialize label.");
        focusHub->SetFocusType(FocusType::SCOPE);
        return;
    }
    focusHub->SetFocusType(FocusType::NODE);
    auto textNode = DynamicCast<FrameNode>(host->GetFirstChild());
    CHECK_NULL_VOID(textNode);
    auto textLayoutProperty = textNode->GetLayoutProperty<TextLayoutProperty>();
    CHECK_NULL_VOID(textLayoutProperty);
    UpdateTextLayoutProperty(layoutProperty, textLayoutProperty);
    textNode->MarkModifyDone();
    textNode->MarkDirtyNode();
}

void ButtonPattern::OnModifyDone()
{
    Pattern::OnModifyDone();
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    InitButtonLabel();
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

void ButtonPattern::InitHoverEvent()
{
    if (hoverListener_) {
        return;
    }
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto eventHub = host->GetEventHub<ButtonEventHub>();
    auto inputHub = eventHub->GetOrCreateInputEventHub();
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
        AnimateTouchAndHover(renderContext, isHover_ ? HOVER_OPACITY : 0.0f, TOUCH_OPACITY,
            isHover_ ? HOVER_TO_TOUCH_DURATION : TOUCH_DURATION, isHover_ ? Curves::SHARP : Curves::FRICTION);
    }
}

void ButtonPattern::OnTouchUp()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto buttonEventHub = GetEventHub<ButtonEventHub>();
    CHECK_NULL_VOID(buttonEventHub);
    if (buttonEventHub->GetStateEffect()) {
        auto renderContext = host->GetRenderContext();
        if (isSetClickedColor_) {
            renderContext->UpdateBackgroundColor(backgroundColor_);
            return;
        }
        AnimateTouchAndHover(renderContext, TOUCH_OPACITY, isHover_ ? HOVER_OPACITY : 0.0,
            isHover_ ? HOVER_TO_TOUCH_DURATION : TOUCH_DURATION, isHover_ ? Curves::SHARP : Curves::FRICTION);
    }
}

void ButtonPattern::HandleHoverEvent(bool isHover)
{
    isHover_ = isHover;
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto renderContext = host->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    renderContext->AnimateHoverEffectBoard(isHover);
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
    auto backgroundColor = renderContext->GetBackgroundColor().value_or(theme->GetBgColor());
    if (!enabled) {
        renderContext->OnBackgroundColorUpdate(backgroundColor.BlendOpacity(alpha));
    } else {
        renderContext->OnBackgroundColorUpdate(backgroundColor);
    }
}

void ButtonPattern::AnimateTouchAndHover(RefPtr<RenderContext>& renderContext, float startOpacity, float endOpacity,
    int32_t duration, const RefPtr<Curve>& curve)
{
    if (startOpacity > endOpacity) {
        auto host = GetHost();
        CHECK_NULL_VOID(host);
        auto toggleButtonPattern = host->GetPattern<ToggleButtonPattern>();
        if (toggleButtonPattern) {
            toggleButtonPattern->OnClick();
        }
    }
    Color touchColorFrom = Color::FromRGBO(0, 0, 0, startOpacity);
    Color touchColorTo = Color::FromRGBO(0, 0, 0, endOpacity);
    Color highlightStart = renderContext->GetBackgroundColor().value_or(Color::TRANSPARENT).BlendColor(touchColorFrom);
    Color highlightEnd = renderContext->GetBackgroundColor().value_or(Color::TRANSPARENT).BlendColor(touchColorTo);
    renderContext->OnBackgroundColorUpdate(highlightStart);
    AnimationOption option = AnimationOption();
    option.SetDuration(duration);
    option.SetCurve(curve);
    AnimationUtils::Animate(
        option, [renderContext, highlightEnd]() { renderContext->OnBackgroundColorUpdate(highlightEnd); });
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
    auto color = buttonTheme->GetBgColor();
    renderContext->UpdateBackgroundColor(color);
    auto textNode = DynamicCast<FrameNode>(node->GetFirstChild());
    CHECK_NULL_VOID(textNode);
    auto textLayoutProperty = textNode->GetLayoutProperty<TextLayoutProperty>();
    CHECK_NULL_VOID(textLayoutProperty);
    auto textStyle = buttonTheme->GetTextStyle();
    textLayoutProperty->UpdateTextColor(textStyle.GetTextColor());
    textNode->MarkDirtyNode();
}
} // namespace OHOS::Ace::NG
