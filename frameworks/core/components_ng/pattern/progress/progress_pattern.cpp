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

#include "core/components_ng/pattern/progress/progress_pattern.h"

#include "core/components/progress/progress_theme.h"
#include "core/components/theme/app_theme.h"
#include "core/components_ng/pattern/progress/progress_layout_algorithm.h"
#include "core/components_ng/pattern/text/text_layout_property.h"
#include "core/components_ng/pattern/text/text_pattern.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "core/pipeline/pipeline_base.h"

namespace OHOS::Ace::NG {
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

void ProgressPattern::ToJsonValue(std::unique_ptr<JsonValue>& json) const
{
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
    json->Put("style", jsonValue->ToString().c_str());
    ToJsonValueForRingStyleOptions(json);
    ToJsonValueForLinearStyleOptions(json);
    json->Put("enableSmoothEffect", paintProperty->GetEnableSmoothEffectValue(true) ? "true" : "false");
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
    auto paintProperty = host->GetPaintProperty<ProgressPaintProperty>();
    CHECK_NULL_VOID(paintProperty);
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    RefPtr<ProgressTheme> progressTheme = pipeline->GetTheme<ProgressTheme>();
    CHECK_NULL_VOID(progressTheme);
    auto alpha = progressTheme->GetProgressDisable();
    auto backgroundColor = paintProperty->GetBackgroundColor().value_or(progressTheme->GetCapsuleBgColor());
    auto selectColor = paintProperty->GetColor().value_or(progressTheme->GetCapsuleSelectColor());
    auto borderColor = paintProperty->GetBorderColor().value_or(progressTheme->GetBorderColor());
    if (!enabled) {
        auto textHost = AceType::DynamicCast<FrameNode>(host->GetChildAtIndex(0));
        CHECK_NULL_VOID(textHost);
        auto textLayoutProperty = textHost->GetLayoutProperty<TextLayoutProperty>();
        CHECK_NULL_VOID(textLayoutProperty);
        auto textColor = textLayoutProperty->GetTextColor().value_or(progressTheme->GetTextColor());
        textLayoutProperty->UpdateTextColor(textColor.BlendOpacity(alpha));
        textHost->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
        paintProperty->UpdateBackgroundColor(backgroundColor.BlendOpacity(alpha));
        paintProperty->UpdateColor(selectColor.BlendOpacity(alpha));
        paintProperty->UpdateBorderColor(borderColor.BlendOpacity(alpha));
        host->MarkDirtyNode();
    }
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
        CHECK_NULL_VOID_NOLOG(pattern);
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
    auto focusDistance = paintWidth + focusPadding;
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
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto progressLayoutProperty = GetLayoutProperty<ProgressLayoutProperty>();
    CHECK_NULL_VOID(progressLayoutProperty);
    if (progressLayoutProperty->GetType() == ProgressType::CAPSULE) {
        auto hub = host->GetEventHub<EventHub>();
        HandleEnabled();
        InitTouchEvent();
        auto focusHub = hub->GetFocusHub();
        CHECK_NULL_VOID_NOLOG(focusHub);
        InitOnKeyEvent(focusHub);
    } else {
        RemoveTouchEvent();
    }
}

void ProgressPattern::OnVisibleChange(bool isVisible)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    visibilityProp_ = isVisible;
    host->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
}

void ProgressPattern::ToJsonValueForRingStyleOptions(std::unique_ptr<JsonValue>& json) const
{
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
    json->Put("ringStyle", jsonValue);
}

void ProgressPattern::ToJsonValueForLinearStyleOptions(std::unique_ptr<JsonValue>& json) const
{
    auto layoutProperty = GetLayoutProperty<ProgressLayoutProperty>();
    auto paintProperty = GetPaintProperty<ProgressPaintProperty>();
    auto pipeline = PipelineBase::GetCurrentContext();
    auto theme = pipeline->GetTheme<ProgressTheme>();

    auto jsonValue = JsonUtil::Create(true);
    jsonValue->Put("strokeWidth", layoutProperty->GetStrokeWidthValue(theme->GetTrackThickness()).ToString().c_str());
    jsonValue->Put("enableScanEffect", (paintProperty->GetEnableLinearScanEffect().value_or(false)) ? "true" : "false");
    json->Put("linearStyle", jsonValue);
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
} // namespace OHOS::Ace::NG
