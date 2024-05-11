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
#include "core/components/text/text_theme.h"

namespace OHOS::Ace::NG {
namespace {
constexpr int32_t TOUCH_DURATION = 100;
constexpr int32_t MOUSE_HOVER_DURATION = 250;
constexpr int32_t TYPE_TOUCH = 0;
constexpr int32_t TYPE_HOVER = 1;
constexpr int32_t TYPE_CANCEL = 2;
} // namespace

Color ButtonPattern::GetColorFromType(const RefPtr<ButtonTheme>& theme, const int32_t& type)
{
    if (type == TYPE_TOUCH) {
        return blendClickColor_.value_or(theme->GetClickedColor());
    } else if (type == TYPE_HOVER) {
        return blendHoverColor_.value_or(theme->GetHoverColor());
    } else {
        return Color::TRANSPARENT;
    }
}

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
        ButtonRole buttonRole = layoutProperty->GetButtonRole().value_or(ButtonRole::NORMAL);
        Color fontColor = buttonTheme->GetTextColor(buttonStyle, buttonRole);
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

    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto textTheme = pipeline->GetTheme<TextTheme>();
    CHECK_NULL_VOID(textTheme);
    isTextFadeOut_ = textTheme->GetIsTextFadeout();
    if (isTextFadeOut_) {
        textLayoutProperty->UpdateTextOverflow(TextOverflow::MARQUEE);
        textLayoutProperty->UpdateTextMarqueeFadeout(true);
        textLayoutProperty->UpdateTextMarqueeStart(false);
        textNode->MarkDirtyNode();
    }
}

void ButtonPattern::HandleFocusStyleTask(RefPtr<ButtonLayoutProperty> layoutProperty,
    RefPtr<RenderContext> buttonRenderContext, RefPtr<ButtonTheme> buttonTheme,
    RefPtr<TextLayoutProperty> textLayoutProperty, RefPtr<FrameNode> textNode)
{
    ButtonStyleMode buttonStyle = layoutProperty->GetButtonStyle().value_or(ButtonStyleMode::EMPHASIZE);
    ButtonRole buttonRole = layoutProperty->GetButtonRole().value_or(ButtonRole::NORMAL);
    ControlSize controlSize = layoutProperty->GetControlSize().value_or(ControlSize::NORMAL);
    auto && graphics = buttonRenderContext->GetOrCreateGraphics();
    auto && transform = buttonRenderContext->GetOrCreateTransform();
    CHECK_NULL_VOID(graphics);
    CHECK_NULL_VOID(transform);

    if (buttonStyle != ButtonStyleMode::TEXT) {
        Shadow shadow = Shadow::CreateShadow(static_cast<ShadowStyle>(buttonTheme->GetShadowNormal()));
        if (!graphics->HasBackShadow() || graphics->GetBackShadowValue() == shadow) {
            shadowModify_ = true;
        }
        if (shadowModify_) {
            ShadowStyle shadowStyle = static_cast<ShadowStyle>(buttonTheme->GetShadowFocus());
            buttonRenderContext->UpdateBackShadow(Shadow::CreateShadow(shadowStyle));
        }
    }
    float scaleFocus = buttonTheme->GetScaleFocus();
    VectorF scale(scaleFocus, scaleFocus);
    if (!transform->HasTransformScale() || transform->GetTransformScale() == scale) {
        scaleModify_ = true;
    }
    if (scaleModify_) {
        buttonRenderContext->SetScale(scaleFocus, scaleFocus);
    }
    if (buttonStyle == ButtonStyleMode::TEXT && controlSize == ControlSize::NORMAL) {
        bgColorModify_ = buttonRenderContext->GetBackgroundColor() == buttonTheme->GetBgColor(buttonStyle, buttonRole);
        if (bgColorModify_) {
            buttonRenderContext->UpdateBackgroundColor(buttonTheme->GetTextBackgroundFocus());
        }
    }

    if (buttonStyle != ButtonStyleMode::EMPHASIZE) {
        focusTextColorModify_ =
            textLayoutProperty->GetTextColor() == buttonTheme->GetFocusTextColor(buttonStyle, buttonRole);
        if (focusTextColorModify_) {
            textLayoutProperty->UpdateTextColor(buttonTheme->GetFocusTextColor(buttonStyle, buttonRole));
            textNode->MarkDirtyNode();
        }
    }
    isFocus_ = true;
    if (isTextFadeOut_) {
        textLayoutProperty->UpdateTextMarqueeStart(true);
        textNode->MarkDirtyNode();
    }
}

void ButtonPattern::HandleBlurStyleTask(RefPtr<ButtonLayoutProperty> layoutProperty,
    RefPtr<RenderContext> buttonRenderContext, RefPtr<ButtonTheme> buttonTheme,
    RefPtr<TextLayoutProperty> textLayoutProperty, RefPtr<FrameNode> textNode)
{
    ButtonStyleMode buttonStyle = layoutProperty->GetButtonStyle().value_or(ButtonStyleMode::EMPHASIZE);
    ButtonRole buttonRole = layoutProperty->GetButtonRole().value_or(ButtonRole::NORMAL);

    if (buttonStyle != ButtonStyleMode::TEXT && shadowModify_) {
        ShadowStyle shadowStyle = static_cast<ShadowStyle>(buttonTheme->GetShadowNormal());
        Shadow shadow = Shadow::CreateShadow(shadowStyle);
        buttonRenderContext->UpdateBackShadow(shadow);
        shadowModify_ = false;
    }
    if (scaleModify_) {
        scaleModify_ = false;
        buttonRenderContext->SetScale(1.0f, 1.0f);
    }
    if (bgColorModify_) {
        bgColorModify_ = false;
        buttonRenderContext->UpdateBackgroundColor(buttonTheme->GetBgColor(buttonStyle, buttonRole));
    }
    if (buttonStyle != ButtonStyleMode::EMPHASIZE && focusTextColorModify_) {
        focusTextColorModify_ = false;
        textLayoutProperty->UpdateTextColor(buttonTheme->GetTextColor(buttonStyle, buttonRole));
        textNode->MarkDirtyNode();
    }
    isFocus_ = false;
    if (isTextFadeOut_) {
        textLayoutProperty->UpdateTextMarqueeStart(isHover_);
        textNode->MarkDirtyNode();
    }
}

void ButtonPattern::HandleFocusStatusStyle(RefPtr<ButtonLayoutProperty>& layoutProperty,
    RefPtr<RenderContext>& renderContext, RefPtr<ButtonTheme>& buttonTheme)
{
    CHECK_NULL_VOID(!focusEventInitialized_);
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto textNode = DynamicCast<FrameNode>(host->GetFirstChild());
    CHECK_NULL_VOID(textNode);
    auto textLayoutProperty = textNode->GetLayoutProperty<TextLayoutProperty>();
    CHECK_NULL_VOID(textLayoutProperty);

    auto focusHub = host->GetOrCreateFocusHub();
    auto focusTask = [weak = WeakClaim(this), property = layoutProperty, buttonRenderContext = renderContext,
        theme = buttonTheme, textPorerty = textLayoutProperty, node = textNode]() {
        TAG_LOGD(AceLogTag::ACE_SELECT_COMPONENT, "button handle focus event");
        auto pattern = weak.Upgrade();
        if (pattern) {
            pattern->HandleFocusStyleTask(property, buttonRenderContext, theme, textPorerty, node);
        }
    };
    focusHub->SetOnFocusInternal(focusTask);

    auto blurTask = [weak = WeakClaim(this), property = layoutProperty, buttonRenderContext = renderContext,
        theme = buttonTheme, textPorerty = textLayoutProperty, node = textNode]() {
        TAG_LOGD(AceLogTag::ACE_SELECT_COMPONENT, "button handle blur event");
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        pattern->HandleBlurStyleTask(property, buttonRenderContext, theme, textPorerty, node);
    };
    focusHub->SetOnBlurInternal(blurTask);
}

void ButtonPattern::OnModifyDone()
{
    Pattern::OnModifyDone();
    FireBuilder();
    InitButtonLabel();
    HandleButtonStyle();
    HandleEnabled();
    InitHoverEvent();
    InitTouchEvent();
}

void ButtonPattern::HandleButtonStyle()
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

    HandleBackgroundStyle(layoutProperty, renderContext, buttonTheme);
    HandleBorderStyle(layoutProperty, renderContext, buttonTheme);
    HandleFocusStatusStyle(layoutProperty, renderContext, buttonTheme);
}

void ButtonPattern::HandleBackgroundStyle(RefPtr<ButtonLayoutProperty>& layoutProperty,
    RefPtr<RenderContext>& renderContext, RefPtr<ButtonTheme>& buttonTheme)
{
    ButtonStyleMode buttonStyle = layoutProperty->GetButtonStyle().value_or(ButtonStyleMode::EMPHASIZE);
    ButtonRole buttonRole = layoutProperty->GetButtonRole().value_or(ButtonRole::NORMAL);

    auto && graphics = renderContext->GetOrCreateGraphics();
    CHECK_NULL_VOID(graphics);
    if (buttonStyle != ButtonStyleMode::TEXT && !graphics->HasBackShadow()) {
        ShadowStyle shadowStyle = static_cast<ShadowStyle>(buttonTheme->GetShadowNormal());
        Shadow shadow = Shadow::CreateShadow(shadowStyle);
        renderContext->UpdateBackShadow(shadow);
    }
    if (UseContentModifier()) {
        renderContext->UpdateBackgroundColor(Color::TRANSPARENT);
        renderContext->ResetBackgroundColor();
        return;
    }
    if (!renderContext->HasBackgroundColor()) {
        renderContext->UpdateBackgroundColor(buttonTheme->GetBgColor(buttonStyle, buttonRole));
    }
    themeBgColor_ = buttonTheme->GetBgColor(buttonStyle, buttonRole);
    themeTextColor_ = buttonTheme->GetTextColor(buttonStyle, buttonRole);
}

void ButtonPattern::HandleBorderStyle(RefPtr<ButtonLayoutProperty>& layoutProperty,
    RefPtr<RenderContext>& renderContext, RefPtr<ButtonTheme>& buttonTheme)
{
    if (UseContentModifier()) {
        return;
    }
    ButtonStyleMode buttonStyle = layoutProperty->GetButtonStyle().value_or(ButtonStyleMode::EMPHASIZE);
    if (buttonStyle == ButtonStyleMode::NORMAL) {
        ControlSize controlSize = layoutProperty->GetControlSize().value_or(ControlSize::NORMAL);
        BorderColorProperty borderColor;
        BorderWidthProperty borderWidth;
        Color color =
            (controlSize == ControlSize::NORMAL) ? buttonTheme->GetBorderColor() : buttonTheme->GetBorderColorSmall();
        Dimension width =
            (controlSize == ControlSize::NORMAL) ? buttonTheme->GetBorderWidth() : buttonTheme->GetBorderWidthSmall();
        borderColor.SetColor(color);
        borderWidth.SetBorderWidth(width);
        if (!layoutProperty->GetBorderWidthProperty()) {
            if (!renderContext->HasBorderWidth()) {
                layoutProperty->UpdateBorderWidth(borderWidth);
                renderContext->UpdateBorderWidth(borderWidth);
            }
            if (!renderContext->HasBorderColor()) {
                renderContext->UpdateBorderColor(borderColor);
            }
        }
    }
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
            TAG_LOGD(AceLogTag::ACE_SELECT_COMPONENT, "button touch down");
            buttonPattern->OnTouchDown();
        }
        if (info.GetTouches().front().GetTouchType() == TouchType::UP ||
            info.GetTouches().front().GetTouchType() == TouchType::CANCEL) {
            TAG_LOGD(AceLogTag::ACE_SELECT_COMPONENT, "button touch up");
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
        Recorder::NodeDataCache::Get().PutString(host, inspectorId, text);
    }
}

void ButtonPattern::InitHoverEvent()
{
    if (UseContentModifier()) {
        return;
    }
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
        TAG_LOGD(AceLogTag::ACE_SELECT_COMPONENT, "button handle hover %{public}d", isHover);
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
    isPress_ = true;
    FireBuilder();
    if (UseContentModifier()) {
        return;
    }
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
    isPress_ = false;
    FireBuilder();
    if (UseContentModifier()) {
        return;
    }
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
    if (hoverEffect == HoverEffectType::NONE || hoverEffect == HoverEffectType::SCALE) {
        return;
    }
    if (!isPress_ && (enabled || !isHover)) {
        auto renderContext = host->GetRenderContext();
        CHECK_NULL_VOID(renderContext);
        AnimateTouchAndHover(renderContext, isHover ? TYPE_CANCEL : TYPE_HOVER, isHover ? TYPE_HOVER : TYPE_CANCEL,
            MOUSE_HOVER_DURATION, Curves::FRICTION);
    }
    if (isTextFadeOut_) {
        auto textNode = DynamicCast<FrameNode>(host->GetFirstChild());
        CHECK_NULL_VOID(textNode);
        auto textLayoutProperty = textNode->GetLayoutProperty<TextLayoutProperty>();
        CHECK_NULL_VOID(textLayoutProperty);
        textLayoutProperty->UpdateTextOverflow(TextOverflow::MARQUEE);
        textLayoutProperty->UpdateTextMarqueeFadeout(true);
        if (isHover) {
            textLayoutProperty->UpdateTextMarqueeStart(isHover);
        } else {
            textLayoutProperty->UpdateTextMarqueeStart(isFocus_);
        }
        textNode->MarkDirtyNode();
    }
}

void ButtonPattern::HandleEnabled()
{
    if (UseContentModifier()) {
        return;
    }
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
    TAG_LOGD(AceLogTag::ACE_SELECT_COMPONENT, "button animate touch from %{public}d to %{public}d", typeFrom, typeTo);
    Color blendColorFrom = GetColorFromType(theme, typeFrom);
    Color blendColorTo = GetColorFromType(theme, typeTo);
    renderContext->BlendBgColor(blendColorFrom);
    AnimationOption option = AnimationOption();
    option.SetDuration(duration);
    option.SetCurve(curve);
    AnimationUtils::Animate(option, [renderContext, blendColorTo]() { renderContext->BlendBgColor(blendColorTo); });
}

void ButtonPattern::SetButtonPress(double xPos, double yPos)
{
    CHECK_NULL_VOID(contentModifierNode_);
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto eventHub = host->GetEventHub<EventHub>();
    CHECK_NULL_VOID(eventHub);
    auto enabled = eventHub->IsEnabled();
    if (!enabled) {
        return;
    }
    GestureEvent info;
    std::chrono::microseconds microseconds(GetMicroTickCount());
    TimeStamp time(microseconds);
    info.SetTimeStamp(time);
    auto x = Dimension(xPos, DimensionUnit::VP);
    auto y = Dimension(yPos, DimensionUnit::VP);
    info.SetLocalLocation(Offset(xPos, yPos));
    auto currFrameRect = host->GetRectWithRender();
    auto frameGlobalOffset = currFrameRect.GetOffset();
    auto globalX = Dimension(x.ConvertToPx() + frameGlobalOffset.GetX());
    auto globalY = Dimension(y.ConvertToPx() + frameGlobalOffset.GetY());
    info.SetGlobalLocation(Offset(globalX.ConvertToVp(), globalY.ConvertToVp()));
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto windowOffset = pipeline->GetCurrentWindowRect().GetOffset();
    auto screenX = Dimension(windowOffset.GetX()) + globalX;
    auto screenY = Dimension(windowOffset.GetY()) + globalY;
    info.SetScreenLocation(Offset(screenX.ConvertToVp(), screenY.ConvertToVp()));
    if (clickEventFunc_.has_value()) {
        (clickEventFunc_.value())(info);
    }
}

void ButtonPattern::FireBuilder()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto gestureEventHub = host->GetOrCreateGestureEventHub();
    CHECK_NULL_VOID(gestureEventHub);
    if (!makeFunc_.has_value()) {
        gestureEventHub->SetRedirectClick(false);
        if (nodeId_ == -1) {
            return;
        }
        auto children = host->GetChildren();
        for (const auto& child : children) {
            if (child->GetId() == nodeId_) {
                host->RemoveChildAndReturnIndex(child);
                host->MarkNeedFrameFlushDirty(PROPERTY_UPDATE_MEASURE);
                break;
            }
        }
        return;
    } else {
        gestureEventHub->SetRedirectClick(true);
    }
    if (contentModifierNode_ == BuildContentModifierNode()) {
        return;
    }
    host->RemoveChildAndReturnIndex(contentModifierNode_);
    contentModifierNode_ = BuildContentModifierNode();
    CHECK_NULL_VOID(contentModifierNode_);
    nodeId_ = contentModifierNode_->GetId();
    host->AddChild(contentModifierNode_, 0);
    host->MarkNeedFrameFlushDirty(PROPERTY_UPDATE_MEASURE);
    clickEventFunc_ = gestureEventHub->GetClickEvent();
}

RefPtr<FrameNode> ButtonPattern::BuildContentModifierNode()
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, nullptr);
    auto layoutProperty = GetLayoutProperty<ButtonLayoutProperty>();
    CHECK_NULL_RETURN(layoutProperty, nullptr);
    auto label = layoutProperty->GetLabel().value_or("");
    auto eventHub = host->GetEventHub<EventHub>();
    CHECK_NULL_RETURN(eventHub, nullptr);
    auto enabled = eventHub->IsEnabled();
    ButtonConfiguration buttonConfiguration(label, isPress_, enabled);
    return (makeFunc_.value())(buttonConfiguration);
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
    ButtonRole buttonRole = buttonLayoutProperty->GetButtonRole().value_or(ButtonRole::NORMAL);
    if (renderContext->GetBackgroundColor().value_or(themeBgColor_) == themeBgColor_) {
        auto color = buttonTheme->GetBgColor(buttonStyle, buttonRole);
        renderContext->UpdateBackgroundColor(color);
    }
    auto textNode = DynamicCast<FrameNode>(node->GetFirstChild());
    CHECK_NULL_VOID(textNode);
    auto textLayoutProperty = textNode->GetLayoutProperty<TextLayoutProperty>();
    CHECK_NULL_VOID(textLayoutProperty);
    if (textLayoutProperty->GetTextColor().value_or(themeTextColor_) == themeTextColor_) {
        textLayoutProperty->UpdateTextColor(buttonTheme->GetTextColor(buttonStyle, buttonRole));
        textNode->MarkDirtyNode();
    }
}
} // namespace OHOS::Ace::NG
