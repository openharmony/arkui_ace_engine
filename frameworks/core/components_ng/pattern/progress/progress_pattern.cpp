/*
 * Copyright (c) 2022-2024 Huawei Device Co., Ltd.
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
#include "core/components_ng/base/inspector_filter.h"
#include "core/components_ng/pattern/progress/progress_layout_algorithm.h"
#include "core/components_ng/pattern/text/text_layout_property.h"
#include "core/components_ng/pattern/text/text_pattern.h"
#include "core/pipeline/pipeline_base.h"

namespace OHOS::Ace::NG {
namespace {
constexpr float PROGRESS_DEFAULT_VALUE = 0.0f;
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
    auto progressTheme = pipeline->GetTheme<ProgressTheme>();
    CHECK_NULL_VOID(progressTheme);
    auto progressLayoutProperty = GetLayoutProperty<ProgressLayoutProperty>();
    CHECK_NULL_VOID(progressLayoutProperty);
    auto paintProperty = GetPaintProperty<ProgressPaintProperty>();
    CHECK_NULL_VOID(paintProperty);
    auto color = progressTheme->GetTrackSelectedColor();
    auto bgColor = progressTheme->GetTrackBgColor();
    if (progressType_ == ProgressType::CAPSULE) {
        color = progressTheme->GetCapsuleSelectColor();
        bgColor = progressTheme->GetCapsuleBgColor();
    } else if (progressType_ == ProgressType::RING) {
        bgColor = progressTheme->GetRingProgressBgColor();
    }
    color = paintProperty->GetColor().value_or(color);
    bgColor = paintProperty->GetBackgroundColor().value_or(bgColor);
    auto borderColor = paintProperty->GetBorderColor().value_or(progressTheme->GetBorderColor());
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
    progressAnimatableProperty.color = color;
    progressAnimatableProperty.bgColor = bgColor;
    progressAnimatableProperty.borderColor = borderColor;
    progressAnimatableProperty.strokeWidth = strokeWidth_;
    progressAnimatableProperty.strokeRadius = strokeRadius;

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
        return;
    }
    auto layoutProperty = GetLayoutProperty<ProgressLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    auto paintProperty = GetPaintProperty<ProgressPaintProperty>();
    CHECK_NULL_VOID(paintProperty);
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto theme = pipeline->GetTheme<ProgressTheme>();
    CHECK_NULL_VOID(theme);
    auto jsonValue = JsonUtil::Create(true);
    jsonValue->Put("strokeWidth", layoutProperty->GetStrokeWidthValue(theme->GetTrackThickness()).ToString().c_str());
    jsonValue->Put("scaleCount", std::to_string(paintProperty->GetScaleCountValue(theme->GetScaleNumber())).c_str());
    jsonValue->Put("scaleWidth", paintProperty->GetScaleWidthValue(theme->GetScaleWidth()).ToString().c_str());
    json->PutExtAttr("style", jsonValue->ToString().c_str(), filter);
    ToJsonValueForRingStyleOptions(json, filter);
    ToJsonValueForLinearStyleOptions(json, filter);
    json->PutExtAttr("enableSmoothEffect",
        paintProperty->GetEnableSmoothEffectValue(true) ? "true" : "false", filter);
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
    auto eventHub = host->GetEventHub<EventHub>();
    CHECK_NULL_VOID(eventHub);
    auto enabled = eventHub->IsEnabled();
    auto renderContext = host->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto theme = pipeline->GetTheme<ProgressTheme>();
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
    auto theme = pipeline->GetTheme<ProgressTheme>();
    CHECK_NULL_VOID(theme);
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto paintProperty = host->GetPaintProperty<ProgressPaintProperty>();
    CHECK_NULL_VOID(paintProperty);
    auto textHost = AceType::DynamicCast<FrameNode>(host->GetChildAtIndex(0));
    CHECK_NULL_VOID(textHost);
    auto textLayoutProperty = textHost->GetLayoutProperty<TextLayoutProperty>();
    CHECK_NULL_VOID(textLayoutProperty);

    if (touchType == TouchType::DOWN) {
        backgroundColor_ = paintProperty->GetBackgroundColor().value_or(theme->GetCapsuleBgColor());
        selectColor_ = paintProperty->GetColor().value_or(theme->GetCapsuleSelectColor());
        borderColor_ = paintProperty->GetBorderColor().value_or(theme->GetBorderColor());
        fontColor_ = textLayoutProperty->GetTextColor().value_or(theme->GetTextColor());
        Color touchEffect = theme->GetClickEffect();
        Color touchColorDown = backgroundColor_.BlendColor(touchEffect);
        Color touchSelectColorDown = selectColor_.BlendColor(touchEffect);
        Color touchBorderColorDown = borderColor_.BlendColor(touchEffect);
        Color touchFontColorDown = fontColor_.BlendColor(touchEffect);
        paintProperty->UpdateBackgroundColor(touchColorDown);
        paintProperty->UpdateColor(touchSelectColorDown);
        paintProperty->UpdateBorderColor(touchBorderColorDown);
        textLayoutProperty->UpdateTextColor(touchFontColorDown);
    } else if (touchType == TouchType::UP || touchType == TouchType::CANCEL) {
        paintProperty->UpdateBackgroundColor(backgroundColor_);
        paintProperty->UpdateColor(selectColor_);
        paintProperty->UpdateBorderColor(borderColor_);
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
    auto focusRadius =
        std::min(contentSize.Width(), contentSize.Height()) * 0.5 + static_cast<float>(focusDistance.ConvertToPx());
    paintRect.SetRect(RectF(contentOffset.GetX() - focusDistance.ConvertToPx(),
        contentOffset.GetY() - focusDistance.ConvertToPx(), contentSize.Width() + 2 * focusDistance.ConvertToPx(),
        contentSize.Height() + 2 * focusDistance.ConvertToPx()));
    paintRect.SetCornerRadius(focusRadius);
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
        auto hub = host->GetEventHub<EventHub>();
        HandleEnabled();
        InitTouchEvent();
        auto focusHub = hub->GetFocusHub();
        CHECK_NULL_VOID(focusHub);
        InitOnKeyEvent(focusHub);
    } else {
        RemoveTouchEvent();
    }
    OnAccessibilityEvent();
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
    auto maxValue = paintProperty->GetMaxValue().value();
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
    auto theme = pipeline->GetTheme<ProgressTheme>();

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
    auto theme = pipeline->GetTheme<ProgressTheme>();

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
    auto value = renderProperty->GetValue().value_or(0);
    auto total = renderProperty->GetMaxValue().value_or(0);
    auto host = GetHost();
    CHECK_NULL_RETURN(host, nullptr);
    auto eventHub = host->GetEventHub<EventHub>();
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
    auto maxValue = paintProperty->GetMaxValue().value();
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
} // namespace OHOS::Ace::NG
