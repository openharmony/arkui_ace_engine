/*
 * Copyright (c) 2022-2025 Huawei Device Co., Ltd.
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

#include "base/log/dump_log.h"
#include "core/components_ng/pattern/progress/progress_pattern.h"

#include "core/components/progress/progress_theme.h"
#include "core/components/theme/app_theme.h"
#include "core/components/theme/shadow_theme.h"
#include "core/components_ng/base/inspector_filter.h"
#include "core/components_ng/pattern/progress/progress_layout_algorithm.h"
#include "core/components_ng/pattern/text/text_layout_property.h"
#include "core/components_ng/pattern/text/text_pattern.h"
#include "core/pipeline/pipeline_base.h"
#include "interfaces/inner_api/ui_session/ui_session_manager.h"

namespace OHOS::Ace::NG {
namespace {
constexpr float PROGRESS_DEFAULT_VALUE = 0.0f;
constexpr float PROGRESS_MAX_VALUE = 100.0f;
}
bool ProgressPattern::OnDirtyLayoutWrapperSwap(const RefPtr<LayoutWrapper>& dirty, const DirtySwapConfig& config)
{
    if (config.skipMeasure || dirty->SkipMeasureContent()) {
        return false;
    }
    auto layoutAlgorithmWrapper = DynamicCast<LayoutAlgorithmWrapper>(dirty->GetLayoutAlgorithm());
    CHECK_NULL_RETURN(layoutAlgorithmWrapper, false);
    auto progressLayoutAlgorithm = DynamicCast<ProgressLayoutAlgorithm>(layoutAlgorithmWrapper->GetLayoutAlgorithm());
    CHECK_NULL_RETURN(progressLayoutAlgorithm, false);
    strokeWidth_ = progressLayoutAlgorithm->GetStrokeWidth();
    return true;
}

void ProgressPattern::OnAttachToFrameNode()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    host->GetRenderContext()->SetClipToFrame(true);
}

void ProgressPattern::InitAnimatableProperty(ProgressAnimatableProperty& progressAnimatableProperty)
{
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto progressTheme = pipeline->GetTheme<ProgressTheme>(GetThemeScopeId());
    CHECK_NULL_VOID(progressTheme);
    auto progressLayoutProperty = GetLayoutProperty<ProgressLayoutProperty>();
    CHECK_NULL_VOID(progressLayoutProperty);
    auto paintProperty = GetPaintProperty<ProgressPaintProperty>();
    CHECK_NULL_VOID(paintProperty);
    InitColorProperty(progressAnimatableProperty, progressTheme, paintProperty);
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto geometryNode = host->GetGeometryNode();
    CHECK_NULL_VOID(geometryNode);
    auto contentSize = geometryNode->GetContentSize();
    CalculateStrokeWidth(contentSize);
    auto strokeRadius = static_cast<float>(
        paintProperty->GetStrokeRadiusValue(Dimension(strokeWidth_ / 2, DimensionUnit::VP)).ConvertToPx());
    strokeRadius = std::min(strokeWidth_ / 2, strokeRadius);
    auto smoothEffect = paintProperty->GetEnableSmoothEffectValue(true);
    if (!smoothEffect) {
        auto value = paintProperty->GetValueValue(PROGRESS_DEFAULT_VALUE);
        progressAnimatableProperty.value = value;
    }
    progressAnimatableProperty.strokeWidth = strokeWidth_;
    progressAnimatableProperty.strokeRadius = strokeRadius;

    capsuleFocusScale_ = progressTheme->GetCapsuleFocusScale();
    defaultTextColor_ = progressTheme->GetTextColor();
    focusedTextColor_ = progressTheme->GetCapsuleTextFocusedColor();
    focusShadowStyle_ = static_cast<ShadowStyle>(progressTheme->GetCapsuleFocusedShadowStyle());
}

void ProgressPattern::InitColorProperty(ProgressAnimatableProperty& progressAnimatableProperty,
    const RefPtr<ProgressTheme>& progressTheme, const RefPtr<ProgressPaintProperty>& paintProperty)
{
    auto color = progressTheme->GetTrackSelectedColor();
    auto bgColor = progressTheme->GetTrackBgColor();
    if (progressType_ == ProgressType::CAPSULE) {
        color = progressTheme->GetCapsuleSelectColor();
        bgColor = progressTheme->GetCapsuleBgColor();
    } else if (progressType_ == ProgressType::RING) {
        bgColor = progressTheme->GetRingProgressBgColor();
    } else if (progressType_ == ProgressType::SCALE) {
        color = progressTheme->GetScaleTrackSelectedColor();
    }
    color = paintProperty->GetColor().value_or(color);
    bgColor = paintProperty->GetBackgroundColor().value_or(bgColor);
    auto borderColor = paintProperty->GetBorderColor().value_or(progressTheme->GetBorderColor());

    progressAnimatableProperty.color = color;
    progressAnimatableProperty.bgColor = bgColor;
    progressAnimatableProperty.borderColor = borderColor;

    if (paintProperty->HasGradientColor()) {
        progressAnimatableProperty.ringProgressColor = paintProperty->GetGradientColorValue();
    } else {
        progressAnimatableProperty.ringProgressColor = convertGradient(color);
    }
}

void ProgressPattern::CalculateStrokeWidth(const SizeF& contentSize)
{
    auto length = std::min(contentSize.Width(), contentSize.Height());
    auto radius = length / 2;
    switch (progressType_) {
        case ProgressType::LINEAR:
            strokeWidth_ = std::min(strokeWidth_, length);
            break;
        case ProgressType::RING:
        case ProgressType::SCALE:
            if (strokeWidth_ >= radius) {
                strokeWidth_ = radius / 2;
            }
            break;
        default:
            break;
    }
}

void ProgressPattern::ToJsonValue(std::unique_ptr<JsonValue>& json, const InspectorFilter& filter) const
{
    /* no fixed attr below, just return */
    if (filter.IsFastFilter()) {
        ToJsonValueForRingStyleOptions(json, filter);
        ToJsonValueForLinearStyleOptions(json, filter);
        ToJsonValueForCapsuleStyleOptions(json, filter);
        return;
    }
    auto layoutProperty = GetLayoutProperty<ProgressLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    auto paintProperty = GetPaintProperty<ProgressPaintProperty>();
    CHECK_NULL_VOID(paintProperty);
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto theme = pipeline->GetTheme<ProgressTheme>(GetThemeScopeId());
    CHECK_NULL_VOID(theme);
    auto jsonValue = JsonUtil::Create(true);
    jsonValue->Put("strokeWidth", layoutProperty->GetStrokeWidthValue(theme->GetTrackThickness()).ToString().c_str());
    jsonValue->Put("scaleCount", std::to_string(paintProperty->GetScaleCountValue(theme->GetScaleNumber())).c_str());
    jsonValue->Put("scaleWidth", paintProperty->GetScaleWidthValue(theme->GetScaleWidth()).ToString().c_str());
    json->PutExtAttr("style", jsonValue->ToString().c_str(), filter);
    ToJsonValueForRingStyleOptions(json, filter);
    ToJsonValueForLinearStyleOptions(json, filter);
    ToJsonValueForCapsuleStyleOptions(json, filter);
    json->PutExtAttr("enableSmoothEffect",
        paintProperty->GetEnableSmoothEffectValue(true) ? "true" : "false", filter);
    json->PutExtAttr("privacySensitive", paintProperty->GetIsSensitive().value_or(false)? "true": "false", filter);
}

void ProgressPattern::InitFocusEvent()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto focusHub = host->GetOrCreateFocusHub();
    auto focusTask = [weak = WeakClaim(this)](FocusReason reason) {
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

void ProgressPattern::HandleFocusEvent()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto pipeline = host->GetContext();
    CHECK_NULL_VOID(pipeline);
    if (pipeline->GetIsFocusActive()) {
        SetFocusStyle();
    }
    AddIsFocusActiveUpdateEvent();
}

void ProgressPattern::HandleBlurEvent()
{
    ClearFocusStyle();
    RemoveIsFocusActiveUpdateEvent();
}

static bool GetShadowFromTheme(ShadowStyle shadowStyle, Shadow& shadow)
{
    if (shadowStyle == ShadowStyle::None) {
        return true;
    }
    auto pipelineContext = PipelineContext::GetCurrentContext();
    CHECK_NULL_RETURN(pipelineContext, false);

    auto shadowTheme = pipelineContext->GetTheme<ShadowTheme>();
    CHECK_NULL_RETURN(shadowTheme, false);

    auto colorMode = pipelineContext->GetColorMode();
    shadow = shadowTheme->GetShadow(shadowStyle, colorMode);
    return true;
}

void ProgressPattern::SetFocusStyle()
{
    CHECK_NULL_VOID(progressModifier_);
    progressModifier_->SetIsFocused(true);

    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto renderContext = host->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    auto& transform = renderContext->GetOrCreateTransform();
    CHECK_NULL_VOID(transform);

    if (!transform->HasTransformScale()) {
        renderContext->SetScale(capsuleFocusScale_, capsuleFocusScale_);
        isFocusScaleSet_ = true;
    }

    auto paintProperty = host->GetPaintProperty<ProgressPaintProperty>();
    CHECK_NULL_VOID(paintProperty);
    if (paintProperty->GetTextColorValue(defaultTextColor_) == defaultTextColor_) {
        SetTextColor(focusedTextColor_);
        isFocusTextColorSet_ = true;
    }

    if (!renderContext->HasBackShadow() && focusShadowStyle_ != ShadowStyle::None
        && !renderContext->HasBorderRadius()) {
        Shadow shadow;
        if (!GetShadowFromTheme(focusShadowStyle_, shadow)) {
            shadow = Shadow::CreateShadow(focusShadowStyle_);
        }
        renderContext->UpdateBackShadow(shadow);
        isFocusShadowSet_ = true;
    }

    host->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
}

void ProgressPattern::ClearFocusStyle()
{
    CHECK_NULL_VOID(progressModifier_);
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto renderContext = host->GetRenderContext();
    CHECK_NULL_VOID(renderContext);

    if (isFocusScaleSet_) {
        renderContext->SetScale(1.0f, 1.0f);
        isFocusScaleSet_ = false;
    }

    if (isFocusTextColorSet_) {
        SetTextColor(defaultTextColor_);
        isFocusTextColorSet_ = false;
    }

    if (isFocusShadowSet_) {
        renderContext->ResetBackShadow();
        renderContext->SetShadowRadius(0.0f);
        renderContext->ResetBorderRadius();
        isFocusShadowSet_ = false;
    }

    progressModifier_->SetIsFocused(false);
    host->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
}

void ProgressPattern::AddIsFocusActiveUpdateEvent()
{
    if (!isFocusActiveUpdateEvent_) {
        isFocusActiveUpdateEvent_ = [weak = WeakClaim(this)](bool isFocusAcitve) {
            auto pattern = weak.Upgrade();
            CHECK_NULL_VOID(pattern);
            isFocusAcitve ? pattern->SetFocusStyle() : pattern->ClearFocusStyle();
        };
    }

    auto pipline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipline);
    pipline->AddIsFocusActiveUpdateEvent(GetHost(), isFocusActiveUpdateEvent_);
}

void ProgressPattern::RemoveIsFocusActiveUpdateEvent()
{
    auto pipline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipline);
    pipline->RemoveIsFocusActiveUpdateEvent(GetHost());
}

void ProgressPattern::InitHoverEvent()
{
    if (hoverEvent_) {
        return;
    }
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto eventHub = host->GetOrCreateEventHub<EventHub>();
    CHECK_NULL_VOID(eventHub);
    auto inputHub = eventHub->GetOrCreateInputEventHub();

    auto hoverEventHandler = [weak = WeakClaim(this)](bool isHover) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        pattern->OnHover(isHover);
    };
    hoverEvent_ = MakeRefPtr<InputEvent>(std::move(hoverEventHandler));
    inputHub->AddOnHoverEvent(hoverEvent_);
}

void ProgressPattern::RemoveHoverEvent()
{
    if (hoverEvent_) {
        auto host = GetHost();
        CHECK_NULL_VOID(host);
        auto eventHub = host->GetOrCreateEventHub<EventHub>();
        CHECK_NULL_VOID(eventHub);
        auto inputHub = eventHub->GetOrCreateInputEventHub();
        inputHub->RemoveOnHoverEvent(hoverEvent_);
        hoverEvent_ = nullptr;
    }
}

void ProgressPattern::OnHover(bool isHover)
{
    CHECK_NULL_VOID(progressModifier_);
    auto host = GetHost();
    CHECK_NULL_VOID(host);

    progressModifier_->SetIsHovered(isHover);
    host->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
}

void ProgressPattern::SetTextColor(const Color& color)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto textHost = AceType::DynamicCast<FrameNode>(host->GetChildAtIndex(0));
    CHECK_NULL_VOID(textHost);
    auto textLayoutProperty = textHost->GetLayoutProperty<TextLayoutProperty>();
    CHECK_NULL_VOID(textLayoutProperty);

    textLayoutProperty->UpdateTextColor(color);
    textHost->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
}

void ProgressPattern::InitTouchEvent()
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
        buttonPattern->OnPress(info);
    };
    touchListener_ = MakeRefPtr<TouchEventImpl>(std::move(touchCallback));
    gesture->AddTouchEvent(touchListener_);
}

void ProgressPattern::RemoveTouchEvent()
{
    if (touchListener_) {
        auto host = GetHost();
        CHECK_NULL_VOID(host);
        auto gesture = host->GetOrCreateGestureEventHub();
        CHECK_NULL_VOID(gesture);
        gesture->RemoveTouchEvent(touchListener_);
        touchListener_ = nullptr;
    }
}
void ProgressPattern::HandleEnabled()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto eventHub = host->GetOrCreateEventHub<EventHub>();
    CHECK_NULL_VOID(eventHub);
    auto enabled = eventHub->IsEnabled();
    auto renderContext = host->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto theme = pipeline->GetTheme<ProgressTheme>(GetThemeScopeId());
    CHECK_NULL_VOID(theme);
    auto alpha = theme->GetProgressDisable();
    auto originalOpacity = renderContext->GetOpacityValue(1.0);
    renderContext->OnOpacityUpdate(enabled ? originalOpacity : alpha * originalOpacity);
}

void ProgressPattern::OnPress(const TouchEventInfo& info)
{
    auto touchType = info.GetTouches().front().GetTouchType();
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto theme = pipeline->GetTheme<ProgressTheme>(GetThemeScopeId());
    CHECK_NULL_VOID(theme);
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto paintProperty = host->GetPaintProperty<ProgressPaintProperty>();
    CHECK_NULL_VOID(paintProperty);
    auto textHost = AceType::DynamicCast<FrameNode>(host->GetChildAtIndex(0));
    CHECK_NULL_VOID(textHost);
    auto textLayoutProperty = textHost->GetLayoutProperty<TextLayoutProperty>();
    CHECK_NULL_VOID(textLayoutProperty);
    CHECK_NULL_VOID(progressModifier_);

    if (touchType == TouchType::DOWN) {
        progressModifier_->SetIsPressed(true);
        fontColor_ = textLayoutProperty->GetTextColor().value_or(theme->GetTextColor());
        backgroundColorOptional_ = paintProperty->GetBackgroundColor();
        selectColorOptional_ = paintProperty->GetColor();
        borderColorOptional_ = paintProperty->GetBorderColor();
        fontColor_ = textLayoutProperty->GetTextColor().value_or(theme->GetTextColor());
        Color touchEffect = theme->GetClickEffect();
        Color touchFontColorDown = fontColor_.BlendColor(touchEffect);
        textLayoutProperty->UpdateTextColor(touchFontColorDown);
    } else if (touchType == TouchType::UP || touchType == TouchType::CANCEL) {
        progressModifier_->SetIsPressed(false);
        if (backgroundColorOptional_) {
            paintProperty->UpdateBackgroundColor(backgroundColorOptional_.value());
        } else {
            paintProperty->ResetBackgroundColor();
        }
        if (selectColorOptional_) {
            paintProperty->UpdateColor(selectColorOptional_.value());
        } else {
            paintProperty->ResetColor();
        }
        if (borderColorOptional_) {
            paintProperty->UpdateBorderColor(borderColorOptional_.value());
        } else {
            paintProperty->ResetBorderColor();
        }
        textLayoutProperty->UpdateTextColor(fontColor_);
    }
    textHost->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    host->MarkDirtyNode();
}

void ProgressPattern::InitOnKeyEvent(const RefPtr<FocusHub>& focusHub)
{
    auto getInnerPaintRectCallback = [wp = WeakClaim(this)](RoundRect& paintRect) {
        auto pattern = wp.Upgrade();
        CHECK_NULL_VOID(pattern);
        pattern->GetInnerFocusPaintRect(paintRect);
    };
    focusHub->SetInnerFocusPaintRectCallback(getInnerPaintRectCallback);
}

void ProgressPattern::GetInnerFocusPaintRect(RoundRect& paintRect)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    const auto& content = host->GetGeometryNode()->GetContent();
    CHECK_NULL_VOID(content);
    auto contentOffset = content->GetRect().GetOffset();
    auto contentSize = content->GetRect().GetSize();
    auto currentContext = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(currentContext);
    auto appTheme = currentContext->GetTheme<AppTheme>();
    CHECK_NULL_VOID(appTheme);
    auto paintWidth = appTheme->GetFocusWidthVp();
    auto focusPadding = appTheme->GetFocusOutPaddingVp();
    auto focusDistance = paintWidth / 2 + focusPadding;
    auto focusRadius = GetBorderRadiusValues() + static_cast<float>(focusDistance.ConvertToPx());
    paintRect.SetRect(RectF(contentOffset.GetX() - focusDistance.ConvertToPx(),
        contentOffset.GetY() - focusDistance.ConvertToPx(), contentSize.Width() + 2 * focusDistance.ConvertToPx(),
        contentSize.Height() + 2 * focusDistance.ConvertToPx()));
    paintRect.SetCornerRadius(focusRadius);
    if (isFocusShadowSet_) {
        auto host = GetHost();
        CHECK_NULL_VOID(host);
        auto renderContext = host->GetRenderContext();
        CHECK_NULL_VOID(renderContext);
        renderContext->UpdateBorderRadius(BorderRadiusProperty(Dimension(focusRadius)));
    }
}

void ProgressPattern::OnModifyDone()
{
    Pattern::OnModifyDone();
    FireBuilder();
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto progressLayoutProperty = GetLayoutProperty<ProgressLayoutProperty>();
    CHECK_NULL_VOID(progressLayoutProperty);
    if (progressLayoutProperty->GetType() == ProgressType::CAPSULE) {
        auto hub = host->GetOrCreateEventHub<EventHub>();
        HandleEnabled();
        InitTouchEvent();
        InitHoverEvent();
        InitFocusEvent();
        auto focusHub = hub->GetFocusHub();
        CHECK_NULL_VOID(focusHub);
        InitOnKeyEvent(focusHub);
    } else {
        RemoveTouchEvent();
        RemoveHoverEvent();
    }

    if (progressLayoutProperty->GetType() == ProgressType::RING && !progressLayoutProperty->GetPaddingProperty()) {
        auto pipeline = host->GetContext();
        CHECK_NULL_VOID(pipeline);
        auto theme = pipeline->GetTheme<ProgressTheme>(GetThemeScopeId());
        CHECK_NULL_VOID(theme);
        PaddingProperty padding;
        padding.SetEdges(CalcLength(theme->GetRingDefaultPadding()));
        progressLayoutProperty->UpdatePadding(padding);
    }
    OnAccessibilityEvent();
    ReportProgressEvent();
}

void ProgressPattern::DumpInfo()
{
    auto layoutProperty = GetLayoutProperty<ProgressLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto theme = pipeline->GetTheme<ProgressTheme>();
    CHECK_NULL_VOID(theme);
    auto paintProperty = GetPaintProperty<ProgressPaintProperty>();
    CHECK_NULL_VOID(paintProperty);
    
    auto value = paintProperty->GetValueValue(PROGRESS_DEFAULT_VALUE);
    auto maxValue = paintProperty->GetMaxValue().value_or(PROGRESS_MAX_VALUE);
    auto jsonValue = JsonUtil::Create(true);
    auto color = paintProperty->GetColor().value_or(theme->GetCapsuleSelectColor());
    jsonValue->Put("strokeWidth", layoutProperty->GetStrokeWidthValue(theme->GetTrackThickness()).ToString().c_str());
    jsonValue->Put("scaleCount", std::to_string(paintProperty->GetScaleCountValue(theme->GetScaleNumber())).c_str());
    jsonValue->Put("scaleWidth", paintProperty->GetScaleWidthValue(theme->GetScaleWidth()).ToString().c_str());
    DumpLog::GetInstance().AddDesc(std::string("value:").append(std::to_string(value)));
    DumpLog::GetInstance().AddDesc(std::string("maxValue:").append(std::to_string(maxValue)));
    DumpLog::GetInstance().AddDesc(std::string("color:").append(color.ToString()));
    DumpLog::GetInstance().AddDesc(std::string("style:").append(jsonValue->ToString()));
    DumpLog::GetInstance().AddDesc(
        std::string("EnableSmoothEffect: ")
            .append(paintProperty->GetEnableSmoothEffectValue(true) ? "true" : "false"));
}

void ProgressPattern::OnLanguageConfigurationUpdate()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto progressLayoutProperty = GetLayoutProperty<ProgressLayoutProperty>();
    CHECK_NULL_VOID(progressLayoutProperty);
    bool isRtl = progressLayoutProperty->GetNonAutoLayoutDirection() == TextDirection::RTL;
    if (isRightToLeft_ == isRtl) {
        return;
    }
    CHECK_NULL_VOID(progressModifier_);
    progressModifier_->SetIsRightToLeft(isRtl);
    host->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
    isRightToLeft_ = isRtl;
}

void ProgressPattern::OnVisibleChange(bool isVisible)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    visibilityProp_ = isVisible;
    host->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
}

void ProgressPattern::ToJsonValueForCapsuleStyleOptions(
    std::unique_ptr<JsonValue>& json, const InspectorFilter& filter) const
{
    /* no fixed attr below, just return */
    if (filter.IsFastFilter()) {
        return;
    }
    auto paintProperty = GetPaintProperty<ProgressPaintProperty>();
    CHECK_NULL_VOID(paintProperty);
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto progressTheme = pipeline->GetTheme<ProgressTheme>();
    CHECK_NULL_VOID(progressTheme);
    auto capsuleStyle = JsonUtil::Create(true);
    auto font = JsonUtil::Create(true);
    capsuleStyle->Put("borderWidth",
        (paintProperty->GetBorderWidth().value_or(progressTheme->GetBorderWidth())).ToString().c_str());
    capsuleStyle->Put("borderColor",
        (paintProperty->GetBorderColor().value_or(progressTheme->GetBorderColor())).ColorToString().c_str());
    capsuleStyle->Put("fontColor",
        (paintProperty->GetTextColor().value_or(progressTheme->GetTextColor())).ColorToString().c_str());
    capsuleStyle->Put("content", (paintProperty->GetText().value_or("")).c_str());
    capsuleStyle->Put("enableScanEffect", (paintProperty->GetEnableScanEffect().value_or(false)) ? "true" : "false");
    capsuleStyle->Put("showDefaultPercentage",
        (paintProperty->GetEnableShowText().value_or(false)) ? "true" : "false");
    font->Put("size", (paintProperty->GetTextSize().value_or(progressTheme->GetTextSize())).ToString().c_str());
    font->Put("style", paintProperty->GetItalicFontStyle().value_or(Ace::FontStyle::NORMAL) == Ace::FontStyle::NORMAL ?
        "FontStyle.Normal" : "FontStyle.Italic");
    font->Put("weight",
        V2::ConvertWrapFontWeightToStirng(paintProperty->GetFontWeight().value_or(FontWeight::NORMAL)).c_str());
    std::vector<std::string> defaultFamily = { "Sans" };
    std::vector<std::string> fontFamilyVector = paintProperty->GetFontFamily().value_or(defaultFamily);
    if (fontFamilyVector.empty()) {
        fontFamilyVector = defaultFamily;
    }
    std::string fontFamily = fontFamilyVector.at(0);
    for (uint32_t i = 1; i < fontFamilyVector.size(); ++i) {
        fontFamily += ',' + fontFamilyVector.at(i);
    }
    font->Put("family", fontFamily.c_str());
    capsuleStyle->Put("font", font);
    capsuleStyle->Put("borderRadius", (Dimension(GetBorderRadiusValues(), DimensionUnit::PX)).ToString().c_str());

    json->PutExtAttr("capsuleStyle", capsuleStyle, filter);
}

float ProgressPattern::GetBorderRadiusValues() const
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, -1);
    auto geometryNode = host->GetGeometryNode();
    CHECK_NULL_RETURN(geometryNode, -1);
    auto contentSize = geometryNode->GetContentSize();
    constexpr float HALF = 2.0f;
    float contentMinHalf = std::min(contentSize.Height(), contentSize.Width()) / HALF;
    auto paintProperty = GetPaintProperty<ProgressPaintProperty>();
    CHECK_NULL_RETURN(paintProperty, -1);
    auto borderRadiusRet = static_cast<float>(
        paintProperty->GetBorderRadiusValue(Dimension(contentMinHalf, DimensionUnit::PX)).ConvertToPx());
    return std::min(contentMinHalf, borderRadiusRet);
}

void ProgressPattern::ToJsonValueForRingStyleOptions(std::unique_ptr<JsonValue>& json,
    const InspectorFilter& filter) const
{
    /* no fixed attr below, just return */
    if (filter.IsFastFilter()) {
        return;
    }
    auto layoutProperty = GetLayoutProperty<ProgressLayoutProperty>();
    auto paintProperty = GetPaintProperty<ProgressPaintProperty>();
    auto pipeline = PipelineBase::GetCurrentContext();
    auto theme = pipeline->GetTheme<ProgressTheme>(GetThemeScopeId());

    auto jsonValue = JsonUtil::Create(true);
    jsonValue->Put("strokeWidth", layoutProperty->GetStrokeWidthValue(theme->GetTrackThickness()).ToString().c_str());
    jsonValue->Put("enableScanEffect", (paintProperty->GetEnableRingScanEffect().value_or(false)) ? "true" : "false");
    jsonValue->Put("shadow", paintProperty->GetPaintShadowValue(false) ? "true" : "false");
    jsonValue->Put("status",
        ConvertProgressStatusToString(paintProperty->GetProgressStatusValue(ProgressStatus::PROGRESSING)).c_str());
    json->PutExtAttr("ringStyle", jsonValue, filter);
}

void ProgressPattern::ToJsonValueForLinearStyleOptions(
    std::unique_ptr<JsonValue>& json, const InspectorFilter& filter) const
{
    /* no fixed attr below, just return */
    if (filter.IsFastFilter()) {
        return;
    }
    auto layoutProperty = GetLayoutProperty<ProgressLayoutProperty>();
    auto paintProperty = GetPaintProperty<ProgressPaintProperty>();
    auto pipeline = PipelineBase::GetCurrentContext();
    auto theme = pipeline->GetTheme<ProgressTheme>(GetThemeScopeId());

    auto jsonValue = JsonUtil::Create(true);
    auto strokeWidth = layoutProperty->GetStrokeWidthValue(theme->GetTrackThickness());
    jsonValue->Put("strokeWidth", strokeWidth.ToString().c_str());
    auto strokeRadius = paintProperty->GetStrokeRadiusValue(strokeWidth / 2);
    strokeRadius = std::min(strokeWidth / 2, strokeRadius);
    jsonValue->Put("strokeRadius", strokeRadius.ToString().c_str());
    jsonValue->Put("enableScanEffect", (paintProperty->GetEnableLinearScanEffect().value_or(false)) ? "true" : "false");
    json->PutExtAttr("linearStyle", jsonValue, filter);
}

std::string ProgressPattern::ConvertProgressStatusToString(const ProgressStatus status)
{
    std::string str;

    switch (status) {
        case ProgressStatus::LOADING:
            str = "ProgressStatus.LOADING";
            break;
        case ProgressStatus::PROGRESSING:
        default:
            str = "ProgressStatus.PROGRESSING";
            break;
    }

    return str;
}

void ProgressPattern::ObscureText(bool isSensitive)
{
    auto frameNode = GetHost();
    CHECK_NULL_VOID(frameNode);
    auto textHost = AceType::DynamicCast<FrameNode>(frameNode->GetChildAtIndex(0));
    CHECK_NULL_VOID(textHost);
    auto textPattern = textHost->GetPattern<TextPattern>();
    CHECK_NULL_VOID(textPattern);
    textPattern->OnSensitiveStyleChange(isSensitive);
    textHost->SetPrivacySensitive(isSensitive);
    textHost->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
}

void ProgressPattern::OnSensitiveStyleChange(bool isSensitive)
{
    auto frameNode = GetHost();
    CHECK_NULL_VOID(frameNode);
    auto progressPaintProperty = frameNode->GetPaintProperty<NG::ProgressPaintProperty>();
    CHECK_NULL_VOID(progressPaintProperty);
    progressPaintProperty->UpdateIsSensitive(isSensitive);
    ObscureText(isSensitive);
    frameNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
}

void ProgressPattern::FireBuilder()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    if (!makeFunc_.has_value()) {
        CHECK_NULL_VOID(contentModifierNode_);
        host->RemoveChildAndReturnIndex(contentModifierNode_);
        contentModifierNode_ = nullptr;
        host->GetRenderContext()->SetClipToFrame(true);
        host->MarkNeedFrameFlushDirty(PROPERTY_UPDATE_MEASURE);
        return;
    }
    auto node = BuildContentModifierNode();
    if (contentModifierNode_ == node) {
        return;
    }
    host->GetRenderContext()->SetClipToFrame(false);
    host->RemoveChildAndReturnIndex(contentModifierNode_);
    contentModifierNode_ = node;
    CHECK_NULL_VOID(contentModifierNode_);
    host->AddChild(contentModifierNode_, 0);
    host->MarkNeedFrameFlushDirty(PROPERTY_UPDATE_MEASURE);
}

RefPtr<FrameNode> ProgressPattern::BuildContentModifierNode()
{
    if (!makeFunc_.has_value()) {
        return nullptr;
    }
    auto renderProperty = GetPaintProperty<ProgressPaintProperty>();
    CHECK_NULL_RETURN(renderProperty, nullptr);
    auto value = renderProperty->GetValue().value_or(PROGRESS_DEFAULT_VALUE);
    auto total = renderProperty->GetMaxValue().value_or(PROGRESS_MAX_VALUE);
    auto host = GetHost();
    CHECK_NULL_RETURN(host, nullptr);
    auto eventHub = host->GetOrCreateEventHub<EventHub>();
    CHECK_NULL_RETURN(eventHub, nullptr);
    auto enabled = eventHub->IsEnabled();
    return (makeFunc_.value())(ProgressConfiguration{value, total, enabled});
}

void ProgressPattern::DumpInfo(std::unique_ptr<JsonValue>& json)
{
    auto layoutProperty = GetLayoutProperty<ProgressLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto theme = pipeline->GetTheme<ProgressTheme>();
    CHECK_NULL_VOID(theme);
    auto paintProperty = GetPaintProperty<ProgressPaintProperty>();
    CHECK_NULL_VOID(paintProperty);

    auto value = paintProperty->GetValueValue(PROGRESS_DEFAULT_VALUE);
    auto maxValue = paintProperty->GetMaxValue().value_or(PROGRESS_MAX_VALUE);
    auto jsonValue = JsonUtil::Create(true);
    auto color = paintProperty->GetColor().value_or(theme->GetCapsuleSelectColor());
    jsonValue->Put("strokeWidth", layoutProperty->GetStrokeWidthValue(theme->GetTrackThickness()).ToString().c_str());
    jsonValue->Put("scaleCount", std::to_string(paintProperty->GetScaleCountValue(theme->GetScaleNumber())).c_str());
    jsonValue->Put("scaleWidth", paintProperty->GetScaleWidthValue(theme->GetScaleWidth()).ToString().c_str());
    json->Put("value:", std::to_string(value).c_str());
    json->Put("maxValue:", std::to_string(maxValue).c_str());
    json->Put("color:", color.ToString().c_str());
    json->Put("style:", jsonValue->ToString().c_str());
    json->Put("EnableSmoothEffect", paintProperty->GetEnableSmoothEffectValue(true) ? "true" : "false");
}

void ProgressPattern::OnAccessibilityEvent()
{
    if (!initFlag_) {
        initFlag_ = true;
        return;
    }
    auto paintProperty = GetPaintProperty<ProgressPaintProperty>();
    CHECK_NULL_VOID(paintProperty);
    auto value = paintProperty->GetValueValue(PROGRESS_DEFAULT_VALUE);
    if (!NearEqual(value_, value)) {
        value_ = value;
        auto host = GetHost();
        CHECK_NULL_VOID(host);
        host->OnAccessibilityEvent(AccessibilityEventType::COMPONENT_CHANGE);
    }
}

bool ProgressPattern::OnThemeScopeUpdate(int32_t themeScopeId)
{
    bool result = false;
    auto host = GetHost();
    CHECK_NULL_RETURN(host, result);
    auto paintProperty = host->GetPaintProperty<ProgressPaintProperty>();
    CHECK_NULL_RETURN(paintProperty, result);
    const auto& type = paintProperty->GetProgressType();
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_RETURN(pipeline, result);
    auto progressTheme = pipeline->GetTheme<ProgressTheme>(themeScopeId);
    CHECK_NULL_RETURN(progressTheme, result);

    result = !paintProperty->HasBackgroundColor() ||
        ((type != ProgressType::RING) && (type != ProgressType::SCALE) && !paintProperty->HasColor()) ||
        ((type == ProgressType::CAPSULE) && !paintProperty->HasBorderColor());

    if (themeScopeId && !isUserInitiatedColor_) {
        if (type == ProgressType::LINEAR || type == ProgressType::MOON) {
            paintProperty->UpdateColor(progressTheme->GetTrackSelectedColor());
            result = true;
        } else if (type == ProgressType::CAPSULE) {
            paintProperty->UpdateColor(progressTheme->GetCapsuleSelectColor());
            result = true;
        }
    }

    if (themeScopeId && !isUserInitiatedBgColor_ && type != ProgressType::CAPSULE) {
        paintProperty->UpdateBackgroundColor(progressTheme->GetTrackBgColor());
        result = true;
    }
    isUserInitiatedColor_ = (themeScopeId && isModifierInitiatedColor_) ? false : isUserInitiatedColor_;
    isUserInitiatedBgColor_ = (themeScopeId && isModifierInitiatedBgColor_) ? false : isUserInitiatedBgColor_;

    return result;
}

void ProgressPattern::ReportProgressEvent()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto progressPaintProperty = host->GetPaintProperty<NG::ProgressPaintProperty>();
    CHECK_NULL_VOID(progressPaintProperty);
    auto value = progressPaintProperty->GetValueValue(PROGRESS_DEFAULT_VALUE);
    if (!progressPaintProperty->GetMaxValue().has_value()){
        return;
    }
    auto maxValue = progressPaintProperty->GetMaxValue().value();
    if (value >= maxValue) {
        UiSessionManager::GetInstance()->ReportComponentChangeEvent("event", "Progress.onProgress");
        TAG_LOGI(AceLogTag::ACE_PROGRESS, "nodeId:[%{public}d] Progress reportComponentChangeEvent onProgress",
            GetHost()->GetId());
    }
}
} // namespace OHOS::Ace::NG
