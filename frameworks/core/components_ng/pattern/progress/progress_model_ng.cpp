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

#include "core/components_ng/pattern/progress/progress_model_ng.h"

#include "base/geometry/dimension.h"
#include "base/log/log_wrapper.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/progress/progress_date.h"
#include "core/components_ng/pattern/progress/progress_pattern.h"
#include "core/components_ng/pattern/text/text_layout_property.h"
#include "core/components_ng/pattern/text/text_pattern.h"
#include "core/components_v2/inspector/inspector_constants.h"

namespace OHOS::Ace::NG {
void ProgressModelNG::Create(double min, double value, double cachedValue, double max, NG::ProgressType type)
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto frameNode = FrameNode::GetOrCreateFrameNode(
        V2::PROGRESS_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<ProgressPattern>(); });
    stack->Push(frameNode);

    ACE_UPDATE_PAINT_PROPERTY(ProgressPaintProperty, Value, value);
    frameNode->OnAccessibilityEvent(AccessibilityEventType::CHANGE);
    ACE_UPDATE_PAINT_PROPERTY(ProgressPaintProperty, MaxValue, max);
    ACE_UPDATE_PAINT_PROPERTY(ProgressPaintProperty, ProgressType, type);
    ACE_UPDATE_LAYOUT_PROPERTY(ProgressLayoutProperty, Type, type);

    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    RefPtr<ProgressTheme> theme = pipeline->GetTheme<ProgressTheme>();
    auto progressFocusNode = frameNode->GetFocusHub();
    CHECK_NULL_VOID(progressFocusNode);
    if (type == ProgressType::CAPSULE) {
        ACE_UPDATE_PAINT_PROPERTY(ProgressPaintProperty, Color, theme->GetCapsuleSelectColor());
        ACE_UPDATE_PAINT_PROPERTY(ProgressPaintProperty, BorderColor, theme->GetBorderColor());
        ACE_UPDATE_PAINT_PROPERTY(ProgressPaintProperty, BackgroundColor, theme->GetCapsuleBgColor());
        progressFocusNode->SetFocusable(true);
    } else if (type == ProgressType::RING) {
        ACE_UPDATE_PAINT_PROPERTY(ProgressPaintProperty, BackgroundColor, theme->GetRingProgressBgColor());
        progressFocusNode->SetFocusable(false);
    } else {
        ACE_UPDATE_PAINT_PROPERTY(ProgressPaintProperty, BackgroundColor, theme->GetTrackBgColor());
        ACE_UPDATE_PAINT_PROPERTY(ProgressPaintProperty, Color, theme->GetTrackSelectedColor());
        progressFocusNode->SetFocusable(false);
    }

    auto eventHub = ViewStackProcessor::GetInstance()->GetMainFrameNodeInputEventHub();
    CHECK_NULL_VOID(eventHub);
    auto pattern = frameNode->GetPattern<ProgressPattern>();
    CHECK_NULL_VOID(pattern);
    if (type == ProgressType::CAPSULE) {
        if (frameNode->GetChildren().empty()) {
            auto textNode = FrameNode::CreateFrameNode(
                V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
            textNode->SetInternal();
            textNode->MountToParent(frameNode);
        }
        auto textHost = AceType::DynamicCast<FrameNode>(frameNode->GetChildAtIndex(0));
        CHECK_NULL_VOID(textHost);
        SetTextDefaultStyle(textHost, value, max);
        textHost->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
        eventHub->SetHoverEffect(HoverEffectType::SCALE);
    } else {
        if (!frameNode->GetChildren().empty()) {
            frameNode->RemoveChildAtIndex(0);
        }
        eventHub->SetHoverEffect(HoverEffectType::NONE);
    }
}

void ProgressModelNG::SetValue(double value)
{
    auto frameNode = NG::ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto progressPaintProperty = frameNode->GetPaintProperty<NG::ProgressPaintProperty>();
    CHECK_NULL_VOID(progressPaintProperty);
    auto maxValue = progressPaintProperty->GetMaxValue();
    if (value > maxValue) {
        LOGE("value is lager than total , set value equals total");
        value = maxValue.value_or(0);
    }
    ACE_UPDATE_PAINT_PROPERTY(ProgressPaintProperty, Value, value);
    auto pattern = frameNode->GetPattern<ProgressPattern>();
    CHECK_NULL_VOID(pattern);
    if (!pattern->IsTextFromUser()) {
        SetText(std::nullopt);
    }
}

void ProgressModelNG::SetColor(const Color& value)
{
    ACE_UPDATE_PAINT_PROPERTY(ProgressPaintProperty, Color, value);
}

void ProgressModelNG::SetGradientColor(const Gradient& value)
{
    ACE_UPDATE_PAINT_PROPERTY(ProgressPaintProperty, GradientColor, value);
}

void ProgressModelNG::SetBackgroundColor(const Color& value)
{
    ACE_UPDATE_PAINT_PROPERTY(ProgressPaintProperty, BackgroundColor, value);
}

void ProgressModelNG::SetStrokeWidth(const Dimension& value)
{
    ACE_UPDATE_LAYOUT_PROPERTY(ProgressLayoutProperty, StrokeWidth, value);
}

void ProgressModelNG::SetScaleCount(int32_t value)
{
    ACE_UPDATE_PAINT_PROPERTY(ProgressPaintProperty, ScaleCount, value);
}

void ProgressModelNG::SetScaleWidth(const Dimension& value)
{
    ACE_UPDATE_PAINT_PROPERTY(ProgressPaintProperty, ScaleWidth, value);
}

void ProgressModelNG::SetBorderColor(const Color& value)
{
    auto frameNode = NG::ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto progressPaintProperty = frameNode->GetPaintProperty<NG::ProgressPaintProperty>();
    CHECK_NULL_VOID(progressPaintProperty);
    auto progressType = progressPaintProperty->GetProgressTypeValue();
    if (progressType == ProgressType::CAPSULE) {
        ACE_UPDATE_PAINT_PROPERTY(ProgressPaintProperty, BorderColor, value);
    }
}

void ProgressModelNG::SetBorderWidth(const Dimension& value)
{
    ACE_UPDATE_PAINT_PROPERTY(ProgressPaintProperty, BorderWidth, value);
}

void ProgressModelNG::SetSweepingEffect(bool value)
{
    ACE_UPDATE_PAINT_PROPERTY(ProgressPaintProperty, EnableScanEffect, value);
}

void ProgressModelNG::SetFontSize(const Dimension& value)
{
    auto frameNode = NG::ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto textHost = AceType::DynamicCast<FrameNode>(frameNode->GetChildAtIndex(0));
    CHECK_NULL_VOID(textHost);
    auto textLayoutProperty = textHost->GetLayoutProperty<TextLayoutProperty>();
    CHECK_NULL_VOID(textLayoutProperty);
    textLayoutProperty->UpdateFontSize(value);
    textHost->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    ACE_UPDATE_PAINT_PROPERTY(ProgressPaintProperty, TextSize, value);
}

void ProgressModelNG::SetFontColor(const Color& value)
{
    auto frameNode = NG::ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto textHost = AceType::DynamicCast<FrameNode>(frameNode->GetChildAtIndex(0));
    CHECK_NULL_VOID(textHost);
    auto textLayoutProperty = textHost->GetLayoutProperty<TextLayoutProperty>();
    CHECK_NULL_VOID(textLayoutProperty);
    textLayoutProperty->UpdateTextColor(value);
    textHost->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    ACE_UPDATE_PAINT_PROPERTY(ProgressPaintProperty, TextColor, value);
}

void ProgressModelNG::SetText(const std::optional<std::string>& value)
{
    auto frameNode = NG::ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto textHost = AceType::DynamicCast<FrameNode>(frameNode->GetChildAtIndex(0));
    CHECK_NULL_VOID(textHost);
    auto pattern = frameNode->GetPattern<ProgressPattern>();
    CHECK_NULL_VOID(pattern);
    auto textLayoutProperty = textHost->GetLayoutProperty<TextLayoutProperty>();
    CHECK_NULL_VOID(textLayoutProperty);
    auto progressPaintProperty = frameNode->GetPaintProperty<NG::ProgressPaintProperty>();
    CHECK_NULL_VOID(progressPaintProperty);
    std::string context = "";
    if (!value.has_value()) {
        auto maxValue = progressPaintProperty->GetMaxValue();
        auto curValue = progressPaintProperty->GetValue();
        int32_t curPercent = curValue.value() * 100 / maxValue.value();
        std::string number = std::to_string(curPercent) + "%";
        bool isShowText = progressPaintProperty->GetEnableShowText().value_or(false);
        if (!isShowText) {
            number = "";
        }
        textLayoutProperty->UpdateContent(number);
        context = number;
        pattern->SetTextFromUser(false);
    } else {
        textLayoutProperty->UpdateContent(value.value());
        context = value.value();
        pattern->SetTextFromUser(true);
    }
    textHost->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    ACE_UPDATE_PAINT_PROPERTY(ProgressPaintProperty, Text, context);
}

void ProgressModelNG::SetFontWeight(const FontWeight& value)
{
    auto frameNode = NG::ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto textHost = AceType::DynamicCast<FrameNode>(frameNode->GetChildAtIndex(0));
    CHECK_NULL_VOID(textHost);
    auto textLayoutProperty = textHost->GetLayoutProperty<TextLayoutProperty>();
    CHECK_NULL_VOID(textLayoutProperty);
    textLayoutProperty->UpdateFontWeight(value);
    textHost->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    ACE_UPDATE_PAINT_PROPERTY(ProgressPaintProperty, FontWeight, value);
}

void ProgressModelNG::SetFontFamily(const std::vector<std::string>& value)
{
    auto frameNode = NG::ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto textHost = AceType::DynamicCast<FrameNode>(frameNode->GetChildAtIndex(0));
    CHECK_NULL_VOID(textHost);
    auto textLayoutProperty = textHost->GetLayoutProperty<TextLayoutProperty>();
    CHECK_NULL_VOID(textLayoutProperty);
    textLayoutProperty->UpdateFontFamily(value);
    textHost->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    ACE_UPDATE_PAINT_PROPERTY(ProgressPaintProperty, FontFamily, value);
}

void ProgressModelNG::SetItalicFontStyle(const Ace::FontStyle& value)
{
    auto frameNode = NG::ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto textHost = AceType::DynamicCast<FrameNode>(frameNode->GetChildAtIndex(0));
    CHECK_NULL_VOID(textHost);
    auto textLayoutProperty = textHost->GetLayoutProperty<TextLayoutProperty>();
    CHECK_NULL_VOID(textLayoutProperty);
    textLayoutProperty->UpdateItalicFontStyle(value);
    textHost->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    ACE_UPDATE_PAINT_PROPERTY(ProgressPaintProperty, ItalicFontStyle, value);
}

void ProgressModelNG::SetTextDefaultStyle(const RefPtr<FrameNode>& textNode, double value, double maxValue)
{
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto frameNode = NG::ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto textProps = textNode->GetLayoutProperty<TextLayoutProperty>();
    CHECK_NULL_VOID(textProps);
    auto renderContext = textNode->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    renderContext->UpdateClipEdge(false);
    RefPtr<ProgressTheme> progressTheme = pipeline->GetTheme<ProgressTheme>();
    CHECK_NULL_VOID(progressTheme);
    auto progressPaintProperty = frameNode->GetPaintProperty<NG::ProgressPaintProperty>();
    CHECK_NULL_VOID(progressPaintProperty);
    int32_t curPercent = 0;
    if (!NearZero(maxValue)) {
        curPercent = value * 100 / maxValue;
    }
    std::string number = std::to_string(curPercent) + "%";
    textProps->UpdateContent(number);
    textProps->UpdateFontSize(progressTheme->GetTextSize());
    textProps->UpdateTextColor(progressTheme->GetTextColor());
    textProps->UpdateFontWeight(FontWeight::MEDIUM);
    textProps->UpdateTextOverflow(TextOverflow::ELLIPSIS);
    textProps->UpdateMaxLines(1);
    MarginProperty margin;
    margin.left = CalcLength(progressTheme->GetTextMargin());
    margin.right = CalcLength(progressTheme->GetTextMargin());
    margin.top = CalcLength(0.0_vp);
    margin.bottom = CalcLength(0.0_vp);
    textProps->UpdateMargin(margin);
    bool isShowText = progressPaintProperty->GetEnableShowText().value_or(false);
    if (!isShowText) {
        number = "";
        textProps->UpdateContent(number);
    }
    textNode->MarkModifyDone();
    ACE_UPDATE_PAINT_PROPERTY(ProgressPaintProperty, Text, number);
}

void ProgressModelNG::SetPaintShadow(bool value)
{
    ACE_UPDATE_PAINT_PROPERTY(ProgressPaintProperty, PaintShadow, value);
}

void ProgressModelNG::SetProgressStatus(ProgressStatus status)
{
    ACE_UPDATE_PAINT_PROPERTY(ProgressPaintProperty, ProgressStatus, status);
}

void ProgressModelNG::SetShowText(bool value)
{
    ACE_UPDATE_PAINT_PROPERTY(ProgressPaintProperty, EnableShowText, value);
}

void ProgressModelNG::SetRingSweepingEffect(bool value)
{
    ACE_UPDATE_PAINT_PROPERTY(ProgressPaintProperty, EnableRingScanEffect, value);
}

void ProgressModelNG::SetLinearSweepingEffect(bool value)
{
    ACE_UPDATE_PAINT_PROPERTY(ProgressPaintProperty, EnableLinearScanEffect, value);
}

void ProgressModelNG::SetSmoothEffect(bool value)
{
    ACE_UPDATE_PAINT_PROPERTY(ProgressPaintProperty, EnableSmoothEffect, value);
}

} // namespace OHOS::Ace::NG
