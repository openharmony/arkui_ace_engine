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
#include "core/components/progress/progress_component.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/pattern.h"
#include "core/components_ng/pattern/progress/progress_date.h"
#include "core/components_ng/pattern/progress/progress_pattern.h"
#include "core/components_ng/pattern/text/text_layout_property.h"
#include "core/components_ng/pattern/text/text_pattern.h"
#include "core/components_v2/inspector/inspector_constants.h"

namespace OHOS::Ace::NG {
constexpr double DEFAULT_MAX_VALUE = 100.0;

void ProgressModelNG::Create(double min, double value, double cachedValue, double max, NG::ProgressType type)
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    ACE_LAYOUT_SCOPED_TRACE("Create[%s][self:%d]", V2::PROGRESS_ETS_TAG, nodeId);
    auto frameNode = FrameNode::GetOrCreateFrameNode(
        V2::PROGRESS_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<ProgressPattern>(); });
    stack->Push(frameNode);

    ACE_UPDATE_PAINT_PROPERTY(ProgressPaintProperty, Value, value);
    ACE_UPDATE_PAINT_PROPERTY(ProgressPaintProperty, MaxValue, max);
    ACE_UPDATE_PAINT_PROPERTY(ProgressPaintProperty, ProgressType, type);
    ACE_UPDATE_LAYOUT_PROPERTY(ProgressLayoutProperty, Type, type);
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    if (Container::LessThanAPIVersion(PlatformVersion::VERSION_TEN)) {
        return;
    }
    auto progressFocusNode = frameNode->GetFocusHub();
    CHECK_NULL_VOID(progressFocusNode);
    if (type == ProgressType::CAPSULE) {
        progressFocusNode->SetFocusable(true);
    } else {
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

RefPtr<FrameNode> ProgressModelNG::CreateFrameNode(int32_t nodeId, double value, double max, NG::ProgressType type)
{
    auto frameNode = FrameNode::CreateFrameNode(V2::PROGRESS_ETS_TAG, nodeId, AceType::MakeRefPtr<ProgressPattern>());
    CHECK_NULL_RETURN(frameNode, nullptr);
    auto progressPaintProperty = frameNode->GetPaintProperty<NG::ProgressPaintProperty>();
    ProgressModelNG::SetTotal(frameNode.GetRawPtr(), max);
    ProgressModelNG::SetValue(frameNode.GetRawPtr(), value);
    ProgressModelNG::SetType(frameNode.GetRawPtr(), type);
    return frameNode;
}

void ProgressModelNG::SetValue(double value)
{
    auto frameNode = NG::ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto progressPaintProperty = frameNode->GetPaintProperty<NG::ProgressPaintProperty>();
    CHECK_NULL_VOID(progressPaintProperty);
    auto maxValue = progressPaintProperty->GetMaxValue();
    if (value > maxValue) {
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
    textHost->MarkModifyDone();
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

void ProgressModelNG::SetStrokeRadius(const Dimension& value)
{
    ACE_UPDATE_PAINT_PROPERTY(ProgressPaintProperty, StrokeRadius, value);
}

void ProgressModelNG::ResetStrokeRadius()
{
    ACE_RESET_PAINT_PROPERTY_WITH_FLAG(ProgressPaintProperty, StrokeRadius, PROPERTY_UPDATE_RENDER);
}

void ProgressModelNG::SetValue(FrameNode* frameNode, double value)
{
    if (value < 0) {
        value = 0;
    }
    auto progressPaintProperty = frameNode->GetPaintProperty<NG::ProgressPaintProperty>();
    CHECK_NULL_VOID(progressPaintProperty);
    auto maxValue = progressPaintProperty->GetMaxValue();
    if (value > maxValue) {
        value = maxValue.value_or(0);
    }
    ACE_UPDATE_NODE_PAINT_PROPERTY(ProgressPaintProperty, Value, value, frameNode);
    auto pattern = frameNode->GetPattern<ProgressPattern>();
    CHECK_NULL_VOID(pattern);
    if (!pattern->IsTextFromUser()) {
        SetText(frameNode, std::nullopt);
    }
}

void ProgressModelNG::SetTotal(FrameNode* frameNode, double max)
{
    auto progressPaintProperty = frameNode->GetPaintProperty<NG::ProgressPaintProperty>();
    CHECK_NULL_VOID(progressPaintProperty);
    ACE_UPDATE_NODE_PAINT_PROPERTY(ProgressPaintProperty, MaxValue, max, frameNode);
}

void ProgressModelNG::SetType(FrameNode* frameNode, NG::ProgressType type)
{
    CHECK_NULL_VOID(frameNode);
    ACE_UPDATE_NODE_PAINT_PROPERTY(ProgressPaintProperty, ProgressType, type, frameNode);
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(ProgressLayoutProperty, Type, type, frameNode);

    auto progressFocusNode = frameNode->GetFocusHub();
    CHECK_NULL_VOID(progressFocusNode);
    if (type == ProgressType::CAPSULE) {
        progressFocusNode->SetFocusable(true);
    } else {
        progressFocusNode->SetFocusable(false);
    }

    auto eventHub = frameNode->GetOrCreateInputEventHub();
    CHECK_NULL_VOID(eventHub);
    auto pattern = frameNode->GetPattern<ProgressPattern>();
    CHECK_NULL_VOID(pattern);
    if (type == ProgressType::CAPSULE) {
        if (frameNode->GetChildren().empty()) {
            auto textNode = FrameNode::CreateFrameNode(
                V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
            textNode->SetInternal();
            textNode->MountToParent(Referenced::Claim(frameNode));
        }
        auto textHost = AceType::DynamicCast<FrameNode>(frameNode->GetChildAtIndex(0));
        CHECK_NULL_VOID(textHost);
        auto progressPaintProperty = frameNode->GetPaintProperty<NG::ProgressPaintProperty>();
        CHECK_NULL_VOID(progressPaintProperty);
        auto max = progressPaintProperty->GetMaxValue();
        auto value = progressPaintProperty->GetValue();
        SetTextDefaultStyle(textHost, value.value_or(0), max.value_or(DEFAULT_MAX_VALUE));
        textHost->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
        eventHub->SetHoverEffect(HoverEffectType::SCALE);
    } else {
        if (!frameNode->GetChildren().empty()) {
            frameNode->RemoveChildAtIndex(0);
        }
        eventHub->SetHoverEffect(HoverEffectType::NONE);
    }
}

void ProgressModelNG::SetColor(FrameNode* frameNode, const std::optional<Color>& value)
{
    if (value) {
        ACE_UPDATE_NODE_PAINT_PROPERTY(ProgressPaintProperty, Color, value.value(), frameNode);
    } else {
        ACE_RESET_NODE_PAINT_PROPERTY(ProgressPaintProperty, Color, frameNode);
    }
}

void ProgressModelNG::SetGradientColor(FrameNode* frameNode, const std::optional<Gradient>& value)
{
    if (value) {
        ACE_UPDATE_NODE_PAINT_PROPERTY(ProgressPaintProperty, GradientColor, value.value(), frameNode);
    } else {
        ACE_RESET_NODE_PAINT_PROPERTY(ProgressPaintProperty, GradientColor, frameNode);
    }
}

void ProgressModelNG::SetSmoothEffect(FrameNode* frameNode, const std::optional<bool>& value)
{
    if (value) {
        ACE_UPDATE_NODE_PAINT_PROPERTY(ProgressPaintProperty, EnableSmoothEffect, value.value(), frameNode);
    } else {
        ACE_RESET_NODE_PAINT_PROPERTY(ProgressPaintProperty, EnableSmoothEffect, frameNode);
    }
}

void ProgressModelNG::SetStrokeWidth(FrameNode* frameNode, const std::optional<Dimension>& value)
{
    if (value) {
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(ProgressLayoutProperty, StrokeWidth, value.value(), frameNode);
    } else {
        ACE_RESET_NODE_LAYOUT_PROPERTY(ProgressLayoutProperty, StrokeWidth, frameNode);
    }
}

void ProgressModelNG::SetLinearSweepingEffect(FrameNode* frameNode, const std::optional<bool>& value)
{
    if (value) {
        ACE_UPDATE_NODE_PAINT_PROPERTY(ProgressPaintProperty, EnableLinearScanEffect, value.value(), frameNode);
    } else {
        ACE_RESET_NODE_PAINT_PROPERTY(ProgressPaintProperty, EnableLinearScanEffect, frameNode);
    }
}

void ProgressModelNG::SetRingSweepingEffect(FrameNode* frameNode, const std::optional<bool>& value)
{
    if (value) {
        ACE_UPDATE_NODE_PAINT_PROPERTY(ProgressPaintProperty, EnableRingScanEffect, value.value(), frameNode);
    } else {
        ACE_RESET_NODE_PAINT_PROPERTY(ProgressPaintProperty, EnableRingScanEffect, frameNode);
    }
}

void ProgressModelNG::SetPaintShadow(FrameNode* frameNode, const std::optional<bool>& value)
{
    if (value) {
        ACE_UPDATE_NODE_PAINT_PROPERTY(ProgressPaintProperty, PaintShadow, value.value(), frameNode);
    } else {
        ACE_RESET_NODE_PAINT_PROPERTY(ProgressPaintProperty, PaintShadow, frameNode);
    }
}

void ProgressModelNG::SetProgressStatus(FrameNode* frameNode, const std::optional<ProgressStatus>& status)
{
    if (status) {
        ACE_UPDATE_NODE_PAINT_PROPERTY(ProgressPaintProperty, ProgressStatus, status.value(), frameNode);
    } else {
        ACE_RESET_NODE_PAINT_PROPERTY(ProgressPaintProperty, ProgressStatus, frameNode);
    }
}

void ProgressModelNG::SetScaleCount(FrameNode* frameNode, const std::optional<int32_t>& value)
{
    if (value) {
        ACE_UPDATE_NODE_PAINT_PROPERTY(ProgressPaintProperty, ScaleCount, value.value(), frameNode);
    } else {
        ACE_RESET_NODE_PAINT_PROPERTY(ProgressPaintProperty, ScaleCount, frameNode);
    }
}

void ProgressModelNG::SetScaleWidth(FrameNode* frameNode, const std::optional<Dimension>& value)
{
    if (value) {
        ACE_UPDATE_NODE_PAINT_PROPERTY(ProgressPaintProperty, ScaleWidth, value.value(), frameNode);
    } else {
        ACE_RESET_NODE_PAINT_PROPERTY(ProgressPaintProperty, ScaleWidth, frameNode);
    }
}

void ProgressModelNG::SetBorderWidth(FrameNode* frameNode, const std::optional<Dimension>& value)
{
    if (value) {
        ACE_UPDATE_NODE_PAINT_PROPERTY(ProgressPaintProperty, BorderWidth, value.value(), frameNode);
    } else {
        ACE_RESET_NODE_PAINT_PROPERTY(ProgressPaintProperty, BorderWidth, frameNode);
    }
}

void ProgressModelNG::SetBorderColor(FrameNode* frameNode, const std::optional<Color>& value)
{
    if (value) {
        ACE_UPDATE_NODE_PAINT_PROPERTY(ProgressPaintProperty, BorderColor, value.value(), frameNode);
    } else {
        ACE_RESET_NODE_PAINT_PROPERTY(ProgressPaintProperty, BorderColor, frameNode);
    }
}

void ProgressModelNG::SetSweepingEffect(FrameNode* frameNode, const std::optional<bool>& value)
{
    if (value) {
        ACE_UPDATE_NODE_PAINT_PROPERTY(ProgressPaintProperty, EnableScanEffect, value.value(), frameNode);
    } else {
        ACE_RESET_NODE_PAINT_PROPERTY(ProgressPaintProperty, EnableScanEffect, frameNode);
    }
}

void ProgressModelNG::SetShowText(FrameNode* frameNode, const std::optional<bool>& value)
{
    if (value) {
        ACE_UPDATE_NODE_PAINT_PROPERTY(ProgressPaintProperty, EnableShowText, value.value(), frameNode);
    } else {
        ACE_RESET_NODE_PAINT_PROPERTY(ProgressPaintProperty, EnableShowText, frameNode);
    }
}

void ProgressModelNG::SetText(FrameNode* frameNode, const std::optional<std::string>& value)
{
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
    ACE_UPDATE_NODE_PAINT_PROPERTY(ProgressPaintProperty, Text, context, frameNode);
}

void ProgressModelNG::SetFontColor(FrameNode* frameNode, const std::optional<Color>& value)
{
    auto textHost = AceType::DynamicCast<FrameNode>(frameNode->GetChildAtIndex(0));
    CHECK_NULL_VOID(textHost);
    auto textLayoutProperty = textHost->GetLayoutProperty<TextLayoutProperty>();
    CHECK_NULL_VOID(textLayoutProperty);
    if (value) {
        textLayoutProperty->UpdateTextColor(value.value());
        ACE_UPDATE_NODE_PAINT_PROPERTY(ProgressPaintProperty, TextColor, value.value(), frameNode);
    } else {
        textLayoutProperty->ResetTextColor();
        ACE_RESET_NODE_PAINT_PROPERTY(ProgressPaintProperty, TextColor, frameNode);
    }
    textHost->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
}

void ProgressModelNG::SetFontSize(FrameNode* frameNode, const std::optional<Dimension>& value)
{
    auto textHost = AceType::DynamicCast<FrameNode>(frameNode->GetChildAtIndex(0));
    CHECK_NULL_VOID(textHost);
    auto textLayoutProperty = textHost->GetLayoutProperty<TextLayoutProperty>();
    CHECK_NULL_VOID(textLayoutProperty);
    if (value) {
        textLayoutProperty->UpdateFontSize(value.value());
        ACE_UPDATE_NODE_PAINT_PROPERTY(ProgressPaintProperty, TextSize, value.value(), frameNode);
    } else {
        textLayoutProperty->ResetFontSize();
        ACE_RESET_NODE_PAINT_PROPERTY(ProgressPaintProperty, TextSize, frameNode);
    }
    textHost->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
}

void ProgressModelNG::SetFontWeight(FrameNode* frameNode, const std::optional<FontWeight>& value)
{
    auto textHost = AceType::DynamicCast<FrameNode>(frameNode->GetChildAtIndex(0));
    CHECK_NULL_VOID(textHost);
    auto textLayoutProperty = textHost->GetLayoutProperty<TextLayoutProperty>();
    CHECK_NULL_VOID(textLayoutProperty);
    if (value) {
        textLayoutProperty->UpdateFontWeight(value.value());
        ACE_UPDATE_NODE_PAINT_PROPERTY(ProgressPaintProperty, FontWeight, value.value(), frameNode);
    } else {
        textLayoutProperty->ResetFontWeight();
        ACE_RESET_NODE_PAINT_PROPERTY(ProgressPaintProperty, FontWeight, frameNode);
    }
    textHost->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
}

void ProgressModelNG::SetFontFamily(FrameNode* frameNode, const std::optional<std::vector<std::string>>& value)
{
    auto textHost = AceType::DynamicCast<FrameNode>(frameNode->GetChildAtIndex(0));
    CHECK_NULL_VOID(textHost);
    auto textLayoutProperty = textHost->GetLayoutProperty<TextLayoutProperty>();
    CHECK_NULL_VOID(textLayoutProperty);
    if (value) {
        textLayoutProperty->UpdateFontFamily(value.value());
        ACE_UPDATE_NODE_PAINT_PROPERTY(ProgressPaintProperty, FontFamily, value.value(), frameNode);
    } else {
        textLayoutProperty->ResetFontFamily();
        ACE_RESET_NODE_PAINT_PROPERTY(ProgressPaintProperty, FontFamily, frameNode);
    }
    textHost->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
}

void ProgressModelNG::SetItalicFontStyle(FrameNode* frameNode, const std::optional<Ace::FontStyle>& value)
{
    auto textHost = AceType::DynamicCast<FrameNode>(frameNode->GetChildAtIndex(0));
    CHECK_NULL_VOID(textHost);
    auto textLayoutProperty = textHost->GetLayoutProperty<TextLayoutProperty>();
    CHECK_NULL_VOID(textLayoutProperty);
    if (value) {
        textLayoutProperty->UpdateItalicFontStyle(value.value());
        ACE_UPDATE_NODE_PAINT_PROPERTY(ProgressPaintProperty, ItalicFontStyle, value.value(), frameNode);
    } else {
        textLayoutProperty->ResetItalicFontStyle();
        ACE_RESET_NODE_PAINT_PROPERTY(ProgressPaintProperty, ItalicFontStyle, frameNode);
    }
    textHost->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
}

void ProgressModelNG::SetStrokeRadius(FrameNode* frameNode, const std::optional<Dimension>& value)
{
    if (value) {
        ACE_UPDATE_NODE_PAINT_PROPERTY(ProgressPaintProperty, StrokeRadius, value.value(), frameNode);
    } else {
        ACE_RESET_NODE_PAINT_PROPERTY(ProgressPaintProperty, StrokeRadius, frameNode);
    }
}

void ProgressModelNG::ResetStrokeRadius(FrameNode* frameNode)
{
    ACE_RESET_NODE_PAINT_PROPERTY_WITH_FLAG(ProgressPaintProperty, StrokeRadius, PROPERTY_UPDATE_RENDER, frameNode);
}

void ProgressModelNG::SetBackgroundColor(FrameNode* frameNode, const Color& value)
{
    ACE_UPDATE_NODE_PAINT_PROPERTY(ProgressPaintProperty, BackgroundColor, value, frameNode);
}

double ProgressModelNG::GetValue(FrameNode* frameNode)
{
    double value = 0;
    ACE_GET_NODE_PAINT_PROPERTY_WITH_DEFAULT_VALUE(ProgressPaintProperty, Value, value, frameNode, value);
    return value;
}

Color ProgressModelNG::GetColor(FrameNode* frameNode)
{
    Color value;
    ACE_GET_NODE_PAINT_PROPERTY_WITH_DEFAULT_VALUE(ProgressPaintProperty, Color, value, frameNode, value);
    return value;
}

double ProgressModelNG::GetTotal(FrameNode* frameNode)
{
    double value = 100;
    ACE_GET_NODE_PAINT_PROPERTY_WITH_DEFAULT_VALUE(ProgressPaintProperty, MaxValue, value, frameNode, value);
    return value;
}

NG::ProgressType ProgressModelNG::GetType(FrameNode* frameNode)
{
    NG::ProgressType value = ProgressType::LINEAR;
    ACE_GET_NODE_PAINT_PROPERTY_WITH_DEFAULT_VALUE(ProgressPaintProperty, ProgressType, value, frameNode, value);
    return value;
}

void ProgressModelNG::SetBuilderFunc(FrameNode* frameNode, ProgressMakeCallback&& makeFunc)
{
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<ProgressPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetBuilderFunc(std::move(makeFunc));
}

void ProgressModelNG::ProgressInitialize(
    FrameNode* frameNode, double min, double value, double cachedValue, double max, NG::ProgressType type)
{
    auto pattern = frameNode->GetPattern<ProgressPattern>();
    CHECK_NULL_VOID(pattern);

    ACE_UPDATE_NODE_PAINT_PROPERTY(ProgressPaintProperty, Value, value, frameNode);
    ACE_UPDATE_NODE_PAINT_PROPERTY(ProgressPaintProperty, MaxValue, max, frameNode);
    ACE_UPDATE_NODE_PAINT_PROPERTY(ProgressPaintProperty, ProgressType, type, frameNode);
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(ProgressLayoutProperty, Type, type, frameNode);
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    if (Container::LessThanAPIVersion(PlatformVersion::VERSION_TEN)) {
        return;
    }
    RefPtr<ProgressTheme> theme = pipeline->GetTheme<ProgressTheme>();
    auto progressFocusNode = frameNode->GetFocusHub();
    CHECK_NULL_VOID(progressFocusNode);
    if (type == ProgressType::CAPSULE) {
        progressFocusNode->SetFocusable(true);
    } else {
        progressFocusNode->SetFocusable(false);
    }

    auto eventHub = ViewStackProcessor::GetInstance()->GetMainFrameNodeInputEventHub();
    CHECK_NULL_VOID(eventHub);
    if (type == ProgressType::CAPSULE) {
        if (frameNode->GetChildren().empty()) {
            auto textNode = FrameNode::CreateFrameNode(
                V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
            textNode->SetInternal();
            textNode->MountToParent(AceType::Claim(reinterpret_cast<FrameNode*>(frameNode)));
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

void ProgressModelNG::SetPrivacySensitive(FrameNode* frameNode, const std::optional<bool>& flag)
{
    if (flag) {
        ACE_UPDATE_NODE_PAINT_PROPERTY(ProgressPaintProperty, IsSensitive, *flag, frameNode);
    } else {
        ACE_RESET_NODE_PAINT_PROPERTY_WITH_FLAG(ProgressPaintProperty, IsSensitive, PROPERTY_UPDATE_RENDER, frameNode);
    }
    ViewAbstract::SetPrivacySensitive(frameNode, flag);
}
} // namespace OHOS::Ace::NG
