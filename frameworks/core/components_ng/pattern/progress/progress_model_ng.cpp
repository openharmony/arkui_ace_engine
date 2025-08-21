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

#include "core/components_ng/pattern/progress/progress_model_ng.h"

#include "base/geometry/dimension.h"
#include "core/common/resource/resource_parse_utils.h"
#include "core/components/progress/progress_component.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/pattern.h"
#include "core/components_ng/pattern/progress/progress_date.h"
#include "core/components_ng/pattern/progress/progress_paint_property.h"
#include "core/components_ng/pattern/progress/progress_pattern.h"
#include "core/components_ng/pattern/text/text_layout_property.h"
#include "core/components_ng/pattern/text/text_pattern.h"
#include "core/components_v2/inspector/inspector_constants.h"
namespace OHOS::Ace::NG {
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

    RefPtr<ProgressTheme> theme = pipeline->GetTheme<ProgressTheme>(frameNode->GetThemeScopeId());
    CHECK_NULL_VOID(theme);
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
        eventHub->SetHoverEffect(static_cast<HoverEffectType>(theme->GetCapsuleHoverEffectType()));
    } else {
        if (!frameNode->GetChildren().empty()) {
            frameNode->RemoveChildAtIndex(0);
        }
        eventHub->SetHoverEffect(HoverEffectType::NONE);
    }

    auto pros = frameNode->GetPaintProperty<ProgressPaintProperty>();
    if (pros) {
        pros->ResetCapsuleStyleFontColorSetByUser();
        pros->ResetCapsuleStyleSetByUser();
        pros->ResetGradientColorSetByUser();
    }
}

RefPtr<FrameNode> ProgressModelNG::CreateFrameNode(int32_t nodeId, double value, double max, NG::ProgressType type)
{
    auto frameNode = FrameNode::CreateFrameNode(V2::PROGRESS_ETS_TAG, nodeId, AceType::MakeRefPtr<ProgressPattern>());
    CHECK_NULL_RETURN(frameNode, nullptr);
    auto progressPaintProperty = frameNode->GetPaintProperty<NG::ProgressPaintProperty>();
    progressPaintProperty->UpdateValue(value);
    progressPaintProperty->UpdateMaxValue(max);
    progressPaintProperty->UpdateProgressType(type);
    auto progressLayoutProperty = frameNode->GetLayoutProperty<NG::ProgressLayoutProperty>();
    progressLayoutProperty->UpdateType(type);
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
    auto frameNode = NG::ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<ProgressPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetUserInitiatedColor(true);
    ACE_UPDATE_PAINT_PROPERTY(ProgressPaintProperty, Color, value);
}

void ProgressModelNG::ResetColor()
{
    auto frameNode = NG::ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<ProgressPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetUserInitiatedColor(false);
    ACE_RESET_PAINT_PROPERTY_WITH_FLAG(ProgressPaintProperty, Color, PROPERTY_UPDATE_RENDER);
}

void ProgressModelNG::SetGradientColor(const Gradient& value)
{
    ACE_UPDATE_PAINT_PROPERTY(ProgressPaintProperty, GradientColor, value);
}

void ProgressModelNG::ResetGradientColor()
{
    ACE_RESET_PAINT_PROPERTY_WITH_FLAG(ProgressPaintProperty, GradientColor, PROPERTY_UPDATE_RENDER);
}

void ProgressModelNG::SetBackgroundColor(const Color& value)
{
    auto frameNode = NG::ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<ProgressPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetUserInitiatedBgColor(true);
    ACE_UPDATE_PAINT_PROPERTY(ProgressPaintProperty, BackgroundColor, value);
}

void ProgressModelNG::ResetBackgroundColor()
{
    auto frameNode = NG::ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<ProgressPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetUserInitiatedBgColor(false);
    ACE_RESET_PAINT_PROPERTY_WITH_FLAG(ProgressPaintProperty, BackgroundColor, PROPERTY_UPDATE_RENDER);
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
    if (isCapsule()) {
        ACE_UPDATE_PAINT_PROPERTY(ProgressPaintProperty, BorderColor, value);
    }
}

void ProgressModelNG::ResetBorderColor()
{
    if (isCapsule()) {
        ACE_RESET_PAINT_PROPERTY_WITH_FLAG(ProgressPaintProperty, BorderColor, PROPERTY_UPDATE_RENDER);
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

void ProgressModelNG::ResetFontColor()
{
    auto frameNode = NG::ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto textHost = AceType::DynamicCast<FrameNode>(frameNode->GetChildAtIndex(0));
    CHECK_NULL_VOID(textHost);
    textHost->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    ACE_RESET_PAINT_PROPERTY_WITH_FLAG(ProgressPaintProperty, TextColor, PROPERTY_UPDATE_RENDER);
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
        if (maxValue.has_value() && curValue.has_value()) {
            int32_t curPercent = curValue.value() * 100 / maxValue.value();
            std::string number = std::to_string(curPercent) + "%";
            bool isShowText = progressPaintProperty->GetEnableShowText().value_or(false);
            if (!isShowText) {
                number = "";
            }
            textLayoutProperty->UpdateContent(number);
            context = number;
            pattern->SetTextFromUser(false);
        }
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
    RefPtr<ProgressTheme> progressTheme = pipeline->GetTheme<ProgressTheme>(frameNode->GetThemeScopeId());
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
    ACE_UPDATE_NODE_PAINT_PROPERTY(ProgressPaintProperty, ProgressType, type, frameNode);
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(ProgressLayoutProperty, Type, type, frameNode);
}

void ProgressModelNG::SetColor(FrameNode* frameNode, const Color& value)
{
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<ProgressPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetUserInitiatedColor(true);
    ACE_UPDATE_NODE_PAINT_PROPERTY(ProgressPaintProperty, Color, value, frameNode);
}

void ProgressModelNG::SetGradientColor(FrameNode* frameNode, const Gradient& value)
{
    ACE_UPDATE_NODE_PAINT_PROPERTY(ProgressPaintProperty, GradientColor, value, frameNode);
}

void ProgressModelNG::SetSmoothEffect(FrameNode* frameNode, bool value)
{
    ACE_UPDATE_NODE_PAINT_PROPERTY(ProgressPaintProperty, EnableSmoothEffect, value, frameNode);
}

void ProgressModelNG::SetStrokeWidth(FrameNode* frameNode, const Dimension& value)
{
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(ProgressLayoutProperty, StrokeWidth, value, frameNode);
}

void ProgressModelNG::SetLinearSweepingEffect(FrameNode* frameNode, bool value)
{
    ACE_UPDATE_NODE_PAINT_PROPERTY(ProgressPaintProperty, EnableLinearScanEffect, value, frameNode);
}

void ProgressModelNG::SetRingSweepingEffect(FrameNode* frameNode, bool value)
{
    ACE_UPDATE_NODE_PAINT_PROPERTY(ProgressPaintProperty, EnableRingScanEffect, value, frameNode);
}

void ProgressModelNG::SetPaintShadow(FrameNode* frameNode, bool value)
{
    ACE_UPDATE_NODE_PAINT_PROPERTY(ProgressPaintProperty, PaintShadow, value, frameNode);
}

void ProgressModelNG::SetProgressStatus(FrameNode* frameNode, ProgressStatus status)
{
    ACE_UPDATE_NODE_PAINT_PROPERTY(ProgressPaintProperty, ProgressStatus, status, frameNode);
}

void ProgressModelNG::SetScaleCount(FrameNode* frameNode, int32_t value)
{
    ACE_UPDATE_NODE_PAINT_PROPERTY(ProgressPaintProperty, ScaleCount, value, frameNode);
}

void ProgressModelNG::SetScaleWidth(FrameNode* frameNode, const Dimension& value)
{
    ACE_UPDATE_NODE_PAINT_PROPERTY(ProgressPaintProperty, ScaleWidth, value, frameNode);
}

void ProgressModelNG::SetBorderWidth(FrameNode* frameNode, const Dimension& value)
{
    ACE_UPDATE_NODE_PAINT_PROPERTY(ProgressPaintProperty, BorderWidth, value, frameNode);
}

void ProgressModelNG::SetBorderColor(FrameNode* frameNode, const Color& value)
{
    ACE_UPDATE_NODE_PAINT_PROPERTY(ProgressPaintProperty, BorderColor, value, frameNode);
}

void ProgressModelNG::SetSweepingEffect(FrameNode* frameNode, bool value)
{
    ACE_UPDATE_NODE_PAINT_PROPERTY(ProgressPaintProperty, EnableScanEffect, value, frameNode);
}

void ProgressModelNG::SetShowText(FrameNode* frameNode, bool value)
{
    ACE_UPDATE_NODE_PAINT_PROPERTY(ProgressPaintProperty, EnableShowText, value, frameNode);
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
        if (maxValue.has_value() && curValue.has_value()) {
            int32_t curPercent = curValue.value() * 100 / maxValue.value();
            std::string number = std::to_string(curPercent) + "%";
            bool isShowText = progressPaintProperty->GetEnableShowText().value_or(false);
            if (!isShowText) {
                number = "";
            }
            textLayoutProperty->UpdateContent(number);
            context = number;
            pattern->SetTextFromUser(false);
        }
    } else {
        textLayoutProperty->UpdateContent(value.value());
        context = value.value();
        pattern->SetTextFromUser(true);
    }
    textHost->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    ACE_UPDATE_NODE_PAINT_PROPERTY(ProgressPaintProperty, Text, context, frameNode);
}

void ProgressModelNG::SetFontColor(FrameNode* frameNode, const Color& value)
{
    auto textHost = AceType::DynamicCast<FrameNode>(frameNode->GetChildAtIndex(0));
    CHECK_NULL_VOID(textHost);
    auto textLayoutProperty = textHost->GetLayoutProperty<TextLayoutProperty>();
    CHECK_NULL_VOID(textLayoutProperty);
    textLayoutProperty->UpdateTextColor(value);
    textHost->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    ACE_UPDATE_NODE_PAINT_PROPERTY(ProgressPaintProperty, TextColor, value, frameNode);
}

void ProgressModelNG::SetFontSize(FrameNode* frameNode, const Dimension& value)
{
    auto textHost = AceType::DynamicCast<FrameNode>(frameNode->GetChildAtIndex(0));
    CHECK_NULL_VOID(textHost);
    auto textLayoutProperty = textHost->GetLayoutProperty<TextLayoutProperty>();
    CHECK_NULL_VOID(textLayoutProperty);
    textLayoutProperty->UpdateFontSize(value);
    textHost->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    ACE_UPDATE_NODE_PAINT_PROPERTY(ProgressPaintProperty, TextSize, value, frameNode);
}

void ProgressModelNG::SetFontWeight(FrameNode* frameNode, const FontWeight& value)
{
    auto textHost = AceType::DynamicCast<FrameNode>(frameNode->GetChildAtIndex(0));
    CHECK_NULL_VOID(textHost);
    auto textLayoutProperty = textHost->GetLayoutProperty<TextLayoutProperty>();
    CHECK_NULL_VOID(textLayoutProperty);
    textLayoutProperty->UpdateFontWeight(value);
    textHost->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    ACE_UPDATE_NODE_PAINT_PROPERTY(ProgressPaintProperty, FontWeight, value, frameNode);
}

void ProgressModelNG::SetFontFamily(FrameNode* frameNode, const std::vector<std::string>& value)
{
    auto textHost = AceType::DynamicCast<FrameNode>(frameNode->GetChildAtIndex(0));
    CHECK_NULL_VOID(textHost);
    auto textLayoutProperty = textHost->GetLayoutProperty<TextLayoutProperty>();
    CHECK_NULL_VOID(textLayoutProperty);
    textLayoutProperty->UpdateFontFamily(value);
    textHost->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    ACE_UPDATE_NODE_PAINT_PROPERTY(ProgressPaintProperty, FontFamily, value, frameNode);
}

void ProgressModelNG::SetItalicFontStyle(FrameNode* frameNode, const Ace::FontStyle& value)
{
    auto textHost = AceType::DynamicCast<FrameNode>(frameNode->GetChildAtIndex(0));
    CHECK_NULL_VOID(textHost);
    auto textLayoutProperty = textHost->GetLayoutProperty<TextLayoutProperty>();
    CHECK_NULL_VOID(textLayoutProperty);
    textLayoutProperty->UpdateItalicFontStyle(value);
    textHost->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    ACE_UPDATE_NODE_PAINT_PROPERTY(ProgressPaintProperty, ItalicFontStyle, value, frameNode);
}

void ProgressModelNG::SetStrokeRadius(FrameNode* frameNode, const Dimension& value)
{
    ACE_UPDATE_NODE_PAINT_PROPERTY(ProgressPaintProperty, StrokeRadius, value, frameNode);
}

void ProgressModelNG::ResetStrokeRadius(FrameNode* frameNode)
{
    ACE_RESET_NODE_PAINT_PROPERTY_WITH_FLAG(ProgressPaintProperty, StrokeRadius, PROPERTY_UPDATE_RENDER, frameNode);
}

void ProgressModelNG::SetBackgroundColor(FrameNode* frameNode, const Color& value)
{
    auto pattern = frameNode->GetPattern<ProgressPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetUserInitiatedBgColor(true);
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
    RefPtr<ProgressTheme> theme = pipeline->GetTheme<ProgressTheme>(frameNode->GetThemeScopeId());
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
        eventHub->SetHoverEffect(static_cast<HoverEffectType>(theme->GetCapsuleHoverEffectType()));
    } else {
        if (!frameNode->GetChildren().empty()) {
            frameNode->RemoveChildAtIndex(0);
        }
        eventHub->SetHoverEffect(HoverEffectType::NONE);
    }
    if (frameNode->GetThemeScopeId()) {
        if (type == ProgressType::LINEAR || type == ProgressType::MOON) {
            ACE_UPDATE_PAINT_PROPERTY(ProgressPaintProperty, Color, theme->GetTrackSelectedColor());
        } else if (type == ProgressType::CAPSULE) {
            ACE_UPDATE_PAINT_PROPERTY(ProgressPaintProperty, Color, theme->GetCapsuleSelectColor());
        }
        if (type != ProgressType::CAPSULE) {
            ACE_UPDATE_PAINT_PROPERTY(ProgressPaintProperty, BackgroundColor, theme->GetTrackBgColor());
        }
    }
}

void ProgressModelNG::SetBorderRadius(const Dimension& value)
{
    ACE_UPDATE_PAINT_PROPERTY(ProgressPaintProperty, BorderRadius, value);
}

void ProgressModelNG::ResetBorderRadius()
{
    ACE_RESET_PAINT_PROPERTY_WITH_FLAG(ProgressPaintProperty, BorderRadius, PROPERTY_UPDATE_RENDER);
}

void ProgressModelNG::SetBorderRadius(FrameNode* frameNode, const Dimension& value)
{
    ACE_UPDATE_NODE_PAINT_PROPERTY(ProgressPaintProperty, BorderRadius, value, frameNode);
}

void ProgressModelNG::ResetBorderRadius(FrameNode* frameNode)
{
    ACE_RESET_NODE_PAINT_PROPERTY_WITH_FLAG(ProgressPaintProperty, BorderRadius, PROPERTY_UPDATE_RENDER, frameNode);
}

void ProgressModelNG::ResetColor(FrameNode* frameNode)
{
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<ProgressPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetUserInitiatedColor(false);
    ACE_RESET_NODE_PAINT_PROPERTY_WITH_FLAG(ProgressPaintProperty, Color, PROPERTY_UPDATE_RENDER, frameNode);
}

void ProgressModelNG::ResetBackgroundColor(FrameNode* frameNode)
{
    auto pattern = frameNode->GetPattern<ProgressPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetUserInitiatedBgColor(false);
    ACE_RESET_NODE_PAINT_PROPERTY_WITH_FLAG(ProgressPaintProperty, BackgroundColor, PROPERTY_UPDATE_RENDER, frameNode);
}

void ProgressModelNG::ResetGradientColor(FrameNode* frameNode)
{
    ACE_RESET_NODE_PAINT_PROPERTY_WITH_FLAG(ProgressPaintProperty, GradientColor, PROPERTY_UPDATE_RENDER, frameNode);
}

bool ProgressModelNG::isCapsule() const
{
    const bool result = false;
    auto frameNode = NG::ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_RETURN(frameNode, result);
    auto progressPaintProperty = frameNode->GetPaintProperty<NG::ProgressPaintProperty>();
    CHECK_NULL_RETURN(progressPaintProperty, result);
    const auto& progressType = progressPaintProperty->GetProgressType();
    return progressType == ProgressType::CAPSULE;
}

void ProgressModelNG::SetModifierInitiatedColor(FrameNode* frameNode, bool value)
{
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<ProgressPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->IsModifierInitiatedColor(value);
}

void ProgressModelNG::SetModifierInitiatedBgColor(FrameNode* frameNode, bool value)
{
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<ProgressPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->IsModifierInitiatedBgColor(value);
}

void ProgressModelNG::SetProgressColor(FrameNode* frameNode, const RefPtr<ResourceObject>& resObj)
{
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<ProgressPattern>();
    std::string key = "progress.color";
    pattern->RemoveResObj(key);
    CHECK_NULL_VOID(resObj);
    auto&& updateFunc = [patternWeak = AceType::WeakClaim(AceType::RawPtr(pattern)), key,
                            weak = AceType::WeakClaim(frameNode)](
                            const RefPtr<ResourceObject>& resObj, bool isFirstLoad = false) {
        auto frameNode = weak.Upgrade();
        CHECK_NULL_VOID(frameNode);
        auto pattern = patternWeak.Upgrade();
        CHECK_NULL_VOID(pattern);
        Color result;
        NG::Gradient gradient;
        Color endColor;
        Color beginColor;
        if (!ResourceParseUtils::ParseResColor(resObj, result)) {
            auto pipeline = PipelineBase::GetCurrentContext();
            CHECK_NULL_VOID(pipeline);
            auto pops = frameNode->GetPaintProperty<ProgressPaintProperty>();
            CHECK_NULL_VOID(pops);
            const auto& type = pops->GetProgressType();
            auto progressTheme = pipeline->GetTheme<ProgressTheme>();
            CHECK_NULL_VOID(progressTheme);
            endColor = progressTheme->GetRingProgressEndSideColor();
            beginColor = progressTheme->GetRingProgressBeginSideColor();
            result = (type == ProgressType::CAPSULE) ? progressTheme->GetCapsuleParseFailedSelectColor()
                                                     : progressTheme->GetTrackParseFailedSelectedColor();

        } else {
            endColor = result;
            beginColor = result;
        }

        NG::GradientColor endSideColor;
        NG::GradientColor beginSideColor;
        endSideColor.SetLinearColor(LinearColor(endColor));
        endSideColor.SetDimension(Dimension(0.0f));
        beginSideColor.SetLinearColor(LinearColor(beginColor));
        beginSideColor.SetDimension(Dimension(1.0f));
        gradient.AddColor(endSideColor);
        gradient.AddColor(beginSideColor);
        pattern->UpdateGradientColor(gradient, isFirstLoad);
        pattern->UpdateColor(result, isFirstLoad);
    };
    pattern->AddResObj(key, resObj, std::move(updateFunc));
}

void ProgressModelNG::SetLSStrokeWidth(FrameNode* frameNode, const RefPtr<ResourceObject>& resObj)
{
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<ProgressPattern>();
    CHECK_NULL_VOID(pattern);
    std::string key = "progress.strokeWidth";
    pattern->RemoveResObj(key);
    CHECK_NULL_VOID(resObj);
    auto&& updateFunc = [weak = AceType::WeakClaim(AceType::RawPtr(pattern)), key](
                            const RefPtr<ResourceObject>& resObj, bool isFirstLoad = false) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        auto node = pattern->GetHost();
        CHECK_NULL_VOID(node);
        auto pipeline = PipelineBase::GetCurrentContext();
        CHECK_NULL_VOID(pipeline);
        auto progressTheme = pipeline->GetTheme<ProgressTheme>();
        CHECK_NULL_VOID(progressTheme);
        CalcDimension width;
        bool parseOK = false;
        if (Container::GreatOrEqualAPIVersion(PlatformVersion::VERSION_TEN)) {
            parseOK = ResourceParseUtils::ParseResDimensionVpNG(resObj, width);
        } else {
            parseOK = ResourceParseUtils::ParseResDimensionVp(resObj, width);
        }
        if (!parseOK || LessOrEqual(width.Value(), 0.0f) || width.Unit() == DimensionUnit::PERCENT) {
            width = progressTheme->GetTrackThickness();
        }
        SetStrokeWidth(AceType::RawPtr(node), width);
    };
    pattern->AddResObj(key, resObj, std::move(updateFunc));
}

void ProgressModelNG::SetLSSweepingEffect(FrameNode* frameNode, const RefPtr<ResourceObject>& resObj)
{
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<ProgressPattern>();
    CHECK_NULL_VOID(pattern);
    std::string key = "progress.sweepingEffect";
    pattern->RemoveResObj(key);
    CHECK_NULL_VOID(resObj);
    auto&& updateFunc = [weak = AceType::WeakClaim(AceType::RawPtr(pattern)), key](
                            const RefPtr<ResourceObject>& resourceObj, bool isFirstLoad = false) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        auto hostNode = pattern->GetHost();
        CHECK_NULL_VOID(hostNode);
        bool value = false;
        if (!ResourceParseUtils::ParseResBool(resourceObj, value)) {
            value = false;
        }
        SetLinearSweepingEffect(AceType::RawPtr(hostNode), value);
    };
    pattern->AddResObj(key, resObj, std::move(updateFunc));
}

void ProgressModelNG::SetLSStrokeRadius(FrameNode* frameNode, const RefPtr<ResourceObject>& resObj)
{
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<ProgressPattern>();
    CHECK_NULL_VOID(pattern);
    std::string key = "progress.strokeRadius";
    pattern->RemoveResObj(key);
    CHECK_NULL_VOID(resObj);
    auto&& updateFunc = [weak = AceType::WeakClaim(AceType::RawPtr(pattern)), key](
                            const RefPtr<ResourceObject>& resObj, bool isFirstLoad = false) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        auto hostNode = pattern->GetHost();
        CHECK_NULL_VOID(hostNode);
        CalcDimension radius;
        bool parseOK = false;
        parseOK = ResourceParseUtils::ParseResDimensionVpNG(resObj, radius);
        if (!parseOK || LessOrEqual(radius.Value(), 0.0f) || radius.Unit() == DimensionUnit::PERCENT) {
            ResetStrokeRadius(AceType::RawPtr(hostNode));
        } else {
            SetStrokeRadius(AceType::RawPtr(hostNode), radius);
        }
    };
    pattern->AddResObj(key, resObj, std::move(updateFunc));
}

void ProgressModelNG::SetSmoothResEffect(FrameNode* frameNode, const RefPtr<ResourceObject>& resourceObject)
{
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<ProgressPattern>();
    CHECK_NULL_VOID(pattern);
    std::string key = "progress.smoothEffect";
    pattern->RemoveResObj(key);
    CHECK_NULL_VOID(resourceObject);
    auto updateFunction = [weak = AceType::WeakClaim(AceType::RawPtr(pattern)), key](
                              const RefPtr<ResourceObject>& resourceObject, bool isFirstLoad = false) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        auto hostNode = pattern->GetHost();
        CHECK_NULL_VOID(hostNode);
        bool smoothEffectEnabled = true;
        if (!ResourceParseUtils::ParseResBool(resourceObject, smoothEffectEnabled)) {
            smoothEffectEnabled = true;
        }
        SetSmoothEffect(AceType::RawPtr(hostNode), smoothEffectEnabled);
    };
    pattern->AddResObj(key, resourceObject, std::move(updateFunction));
}

void ProgressModelNG::SetRingStrokeWidth(FrameNode* frameNode, const RefPtr<ResourceObject>& resObj)
{
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<ProgressPattern>();
    CHECK_NULL_VOID(pattern);

    const std::string key = "progress.ring.strokeWidth";
    pattern->RemoveResObj(key);
    CHECK_NULL_VOID(resObj);
    auto updateFunc = [weak = AceType::WeakClaim(AceType::RawPtr(pattern)), key](
                          const RefPtr<ResourceObject>& resourceObj, bool isFirstLoad = false) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        auto node = pattern->GetHost();
        CHECK_NULL_VOID(node);
        auto pipeline = PipelineBase::GetCurrentContext();
        CHECK_NULL_VOID(pipeline);
        auto progressTheme = pipeline->GetTheme<ProgressTheme>();
        CHECK_NULL_VOID(progressTheme);

        CalcDimension strokeWidth;
        bool parseOK = false;
        if (Container::GreatOrEqualAPIVersion(PlatformVersion::VERSION_TEN)) {
            parseOK = ResourceParseUtils::ParseResDimensionVpNG(resourceObj, strokeWidth);
        } else {
            parseOK = ResourceParseUtils::ParseResDimensionVp(resourceObj, strokeWidth);
        }
        if (!parseOK || LessOrEqual(strokeWidth.Value(), 0.0f) || strokeWidth.Unit() == DimensionUnit::PERCENT) {
            strokeWidth = progressTheme->GetTrackThickness();
        }
        SetStrokeWidth(AceType::RawPtr(node), strokeWidth);
    };
    pattern->AddResObj(key, resObj, std::move(updateFunc));
}

void ProgressModelNG::SetRingShadow(FrameNode* frameNode, const RefPtr<ResourceObject>& resObj)
{
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<ProgressPattern>();
    CHECK_NULL_VOID(pattern);

    const std::string key = "progress.ring.shadow";
    pattern->RemoveResObj(key);
    CHECK_NULL_VOID(resObj);
    auto updateFunc = [weak = AceType::WeakClaim(AceType::RawPtr(pattern)), key](
                          const RefPtr<ResourceObject>& obj, bool isFirstLoad = false) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        auto node = pattern->GetHost();
        CHECK_NULL_VOID(node);
        bool shadow = false;
        if (ResourceParseUtils::ParseResBool(obj, shadow)) {
            SetPaintShadow(AceType::RawPtr(node), shadow);
        } else {
            SetPaintShadow(AceType::RawPtr(node), false);
        }
    };
    pattern->AddResObj(key, resObj, std::move(updateFunc));
}

void ProgressModelNG::SetRingStatus(FrameNode* frameNode, const RefPtr<ResourceObject>& resObj)
{
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<ProgressPattern>();
    CHECK_NULL_VOID(pattern);
    const std::string key = "progress.ring.status";
    pattern->RemoveResObj(key);
    CHECK_NULL_VOID(resObj);
    auto updateFunc = [weak = AceType::WeakClaim(AceType::RawPtr(pattern)), key](
                          const RefPtr<ResourceObject>& obj, bool isFirstLoad = false) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        auto node = pattern->GetHost();
        CHECK_NULL_VOID(node);
        std::string statusStr;
        NG::ProgressStatus status = NG::ProgressStatus::PROGRESSING;
        if (ResourceParseUtils::ParseResString(obj, statusStr)) {
            status = (statusStr == "LOADING" ? NG::ProgressStatus::LOADING : NG::ProgressStatus::PROGRESSING);
        }
        SetProgressStatus(AceType::RawPtr(node), status);
    };
    pattern->AddResObj(key, resObj, std::move(updateFunc));
}

void ProgressModelNG::SetRingSweepingEffect(FrameNode* frameNode, const RefPtr<ResourceObject>& resObj)
{
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<ProgressPattern>();
    CHECK_NULL_VOID(pattern);

    const std::string key = "progress.ring.sweepingEffect";
    pattern->RemoveResObj(key);
    CHECK_NULL_VOID(resObj);
    auto updateFunc = [weak = AceType::WeakClaim(AceType::RawPtr(pattern)), key](
                          const RefPtr<ResourceObject>& obj, bool isFirstLoad = false) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        auto node = pattern->GetHost();
        CHECK_NULL_VOID(node);
        bool enable = false;
        if (!ResourceParseUtils::ParseResBool(obj, enable)) {
            enable = false;
        }
        SetRingSweepingEffect(AceType::RawPtr(node), enable);
    };
    pattern->AddResObj(key, resObj, std::move(updateFunc));
}

void ProgressModelNG::SetCapsuleBorderWidth(FrameNode* frameNode, const RefPtr<ResourceObject>& resObj)
{
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<ProgressPattern>();
    CHECK_NULL_VOID(pattern);
    const std::string key = "progress.capsule.borderWidth";
    pattern->RemoveResObj(key);
    CHECK_NULL_VOID(resObj);
    auto updateFunc = [weak = AceType::WeakClaim(AceType::RawPtr(pattern)), key](
                          const RefPtr<ResourceObject>& obj, bool isFirstLoad = false) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        auto node = pattern->GetHost();
        CHECK_NULL_VOID(node);
        auto pipeline = PipelineBase::GetCurrentContext();
        CHECK_NULL_VOID(pipeline);
        auto progressTheme = pipeline->GetTheme<ProgressTheme>();
        CHECK_NULL_VOID(progressTheme);
        CalcDimension width;
        bool parseOK = false;
        parseOK = ResourceParseUtils::ParseResDimensionVpNG(obj, width);
        if (!parseOK || LessNotEqual(width.Value(), 0.0f) || width.Unit() == DimensionUnit::PERCENT) {
            width = progressTheme->GetBorderWidth();
        }
        SetBorderWidth(AceType::RawPtr(node), width);
    };
    pattern->AddResObj(key, resObj, std::move(updateFunc));
}

void ProgressModelNG::SetCapsuleBorderColor(FrameNode* frameNode, const RefPtr<ResourceObject>& resObj)
{
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<ProgressPattern>();
    CHECK_NULL_VOID(pattern);

    const std::string resourceKey = "progress.capsule.borderColor";
    pattern->RemoveResObj(resourceKey);
    CHECK_NULL_VOID(resObj);
    auto updateResourceFunction = [weak = AceType::WeakClaim(AceType::RawPtr(pattern)), resourceKey](
                                      const RefPtr<ResourceObject>& resourceObject, bool isFirstLoad = false) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        auto hostNode = pattern->GetHost();
        CHECK_NULL_VOID(hostNode);
        auto pipelineContext = PipelineBase::GetCurrentContext();
        CHECK_NULL_VOID(pipelineContext);
        auto progressTheme = pipelineContext->GetTheme<ProgressTheme>();
        CHECK_NULL_VOID(progressTheme);

        Color borderColor;
        if (ResourceParseUtils::ParseResColor(resourceObject, borderColor)) {
            SetBorderColor(AceType::RawPtr(hostNode), borderColor);
        } else {
            SetBorderColor(AceType::RawPtr(hostNode), progressTheme->GetBorderColor());
        }
    };
    pattern->AddResObj(resourceKey, resObj, std::move(updateResourceFunction));
}

void ProgressModelNG::SetCapsuleSweepingEffect(FrameNode* frameNode, const RefPtr<ResourceObject>& resObj)
{
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<ProgressPattern>();
    CHECK_NULL_VOID(pattern);
    const std::string key = "progress.capsule.sweepingEffect";
    pattern->RemoveResObj(key);
    CHECK_NULL_VOID(resObj);
    auto updateFunc = [weak = AceType::WeakClaim(AceType::RawPtr(pattern)), key](
                          const RefPtr<ResourceObject>& obj, bool isFirstLoad = false) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        auto node = pattern->GetHost();
        CHECK_NULL_VOID(node);
        bool enableScanEffect = false;
        if (!ResourceParseUtils::ParseResBool(obj, enableScanEffect)) {
            enableScanEffect = false;
        }
        SetSweepingEffect(AceType::RawPtr(node), enableScanEffect);
    };
    pattern->AddResObj(key, resObj, std::move(updateFunc));
}

void ProgressModelNG::SetShowDefaultPercentage(FrameNode* frameNode, const RefPtr<ResourceObject>& resObj)
{
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<ProgressPattern>();
    CHECK_NULL_VOID(pattern);
    const std::string key = "progress.capsule.showDefaultPercentage";
    pattern->RemoveResObj(key);
    CHECK_NULL_VOID(resObj);
    auto updateFunc = [weak = AceType::WeakClaim(AceType::RawPtr(pattern)), key](
                          const RefPtr<ResourceObject>& obj, bool isFirstLoad = false) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        auto node = pattern->GetHost();
        CHECK_NULL_VOID(node);
        bool show = false;
        if (!ResourceParseUtils::ParseResBool(obj, show)) {
            show = false;
        }
        SetShowText(AceType::RawPtr(node), show);
    };
    pattern->AddResObj(key, resObj, std::move(updateFunc));
}

void ProgressModelNG::SetFontColorResource(FrameNode* frameNode, const RefPtr<ResourceObject>& resObj)
{
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<ProgressPattern>();
    CHECK_NULL_VOID(pattern);
    const std::string key = "progress.fontColor";
    pattern->RemoveResObj(key);
    CHECK_NULL_VOID(resObj);
    auto updateFunc = [weak = AceType::WeakClaim(AceType::RawPtr(pattern)), key](
                          const RefPtr<ResourceObject>& obj, bool isFirstLoad = false) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        auto node = pattern->GetHost();
        CHECK_NULL_VOID(node);
        Color color;
        if (ResourceParseUtils::ParseResColor(obj, color)) {
            SetFontColor(AceType::RawPtr(node), color);
        } else {
            auto pipeline = PipelineBase::GetCurrentContext();
            CHECK_NULL_VOID(pipeline);
            auto theme = pipeline->GetTheme<TextTheme>();
            CHECK_NULL_VOID(theme);
            SetFontColor(AceType::RawPtr(node), theme->GetTextStyle().GetTextColor());
        }
    };
    pattern->AddResObj(key, resObj, std::move(updateFunc));
}

void ProgressModelNG::SetBackgroundColorResource(FrameNode* frameNode, const RefPtr<ResourceObject>& resObj)
{
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<ProgressPattern>();
    CHECK_NULL_VOID(pattern);
    const std::string key = "progress.backgroundColor";
    pattern->RemoveResObj(key);
    CHECK_NULL_VOID(resObj);
    auto updateFunc = [weak = AceType::WeakClaim(AceType::RawPtr(pattern)), key](
                          const RefPtr<ResourceObject>& obj, bool isFirstLoad = false) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        auto node = pattern->GetHost();
        CHECK_NULL_VOID(node);
        Color color;
        if (ResourceParseUtils::ParseResColor(obj, color)) {
            SetBackgroundColor(AceType::RawPtr(node), color);
        } else {
            auto pipeline = PipelineBase::GetCurrentContext();
            CHECK_NULL_VOID(pipeline);
            auto theme = pipeline->GetTheme<ProgressTheme>();
            CHECK_NULL_VOID(theme);
            auto paintProp = node->GetPaintProperty<ProgressPaintProperty>();
            auto type = paintProp->GetProgressType().value_or(ProgressType::LINEAR);
            Color bg = (type == ProgressType::CAPSULE)
                           ? theme->GetCapsuleBgColor()
                           : (type == ProgressType::RING ? theme->GetRingProgressBgColor() : theme->GetTrackBgColor());
            SetBackgroundColor(AceType::RawPtr(node), bg);
        }
    };
    pattern->AddResObj(key, resObj, std::move(updateFunc));
}

void ProgressModelNG::SetFontWeightResource(FrameNode* frameNode, const RefPtr<ResourceObject>& resObj)
{
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<ProgressPattern>();
    CHECK_NULL_VOID(pattern);

    const std::string key = "progress.fontWeight";
    pattern->RemoveResObj(key);
    CHECK_NULL_VOID(resObj);
    auto updateFunc = [weak = AceType::WeakClaim(AceType::RawPtr(pattern)), key](
                          const RefPtr<ResourceObject>& obj, bool isFirstLoad = false) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        auto node = pattern->GetHost();
        CHECK_NULL_VOID(node);
        std::string weightStr;
        if (ResourceParseUtils::ParseResString(obj, weightStr)) {
            auto weight = StringUtils::StringToFontWeight(weightStr, FontWeight::NORMAL);
            SetFontWeight(AceType::RawPtr(node), weight);
        } else {
            auto pipeline = PipelineBase::GetCurrentContext();
            CHECK_NULL_VOID(pipeline);
            auto theme = pipeline->GetTheme<TextTheme>();
            CHECK_NULL_VOID(theme);
            SetFontWeight(AceType::RawPtr(node), theme->GetTextStyle().GetFontWeight());
        }
    };
    pattern->AddResObj(key, resObj, std::move(updateFunc));
}
void ProgressModelNG::SetRSStrokeWidth(FrameNode* frameNode, const RefPtr<ResourceObject>& resObj)
{
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<ProgressPattern>();
    CHECK_NULL_VOID(pattern);
    std::string key = "progress.style.strokeWidth";
    pattern->RemoveResObj(key);
    CHECK_NULL_VOID(resObj);
    auto&& updateFunc = [weak = AceType::WeakClaim(AceType::RawPtr(pattern)), key](
                            const RefPtr<ResourceObject>& resObj, bool isFirstLoad = false) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        auto node = pattern->GetHost();
        CHECK_NULL_VOID(node);
        auto pipeline = PipelineBase::GetCurrentContext();
        CHECK_NULL_VOID(pipeline);
        auto progressTheme = pipeline->GetTheme<ProgressTheme>();
        CHECK_NULL_VOID(progressTheme);
        CalcDimension width;
        bool parseOK = false;
        if (Container::GreatOrEqualAPIVersion(PlatformVersion::VERSION_TEN)) {
            parseOK = ResourceParseUtils::ParseResDimensionVpNG(resObj, width);
        } else {
            parseOK = ResourceParseUtils::ParseResDimensionVp(resObj, width);
        }
        if (!parseOK || LessOrEqual(width.Value(), 0.0f) || width.Unit() == DimensionUnit::PERCENT) {
            width = progressTheme->GetTrackThickness();
        }
        SetStrokeWidth(AceType::RawPtr(node), width);
    };
    pattern->AddResObj(key, resObj, std::move(updateFunc));
}

void ProgressModelNG::SetRSScaleWidth(FrameNode* frameNode, const RefPtr<ResourceObject>& resObj)
{
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<ProgressPattern>();
    CHECK_NULL_VOID(pattern);
    std::string key = "progress.style.scaleWidth";
    pattern->RemoveResObj(key);
    CHECK_NULL_VOID(resObj);
    auto&& updateFunc = [weak = AceType::WeakClaim(AceType::RawPtr(pattern)), key](
                            const RefPtr<ResourceObject>& resObj, bool isFirstLoad = false) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        auto node = pattern->GetHost();
        CHECK_NULL_VOID(node);
        auto pipeline = PipelineBase::GetCurrentContext();
        CHECK_NULL_VOID(pipeline);
        auto progressTheme = pipeline->GetTheme<ProgressTheme>();
        CHECK_NULL_VOID(progressTheme);
        auto progressPaintProperty = node->GetLayoutProperty<NG::ProgressLayoutProperty>();
        CHECK_NULL_VOID(progressPaintProperty);
        auto strokeWidthDimension =
            progressPaintProperty->GetStrokeWidth().value_or(progressTheme->GetTrackThickness());
        CalcDimension width;
        bool parseOK = false;
        if (Container::GreatOrEqualAPIVersion(PlatformVersion::VERSION_TEN)) {
            parseOK = ResourceParseUtils::ParseResDimensionVpNG(resObj, width);
        } else {
            parseOK = ResourceParseUtils::ParseResDimensionVp(resObj, width);
        }
        if (!parseOK || LessOrEqual(width.Value(), 0.0f) || (width.Value() > strokeWidthDimension.Value()) ||
            width.Unit() == DimensionUnit::PERCENT) {
            width = progressTheme->GetScaleWidth();
        }
        SetScaleWidth(AceType::RawPtr(node), width);
    };
    pattern->AddResObj(key, resObj, std::move(updateFunc));
}

void ProgressModelNG::SetTextResource(FrameNode* frameNode, const RefPtr<ResourceObject>& resObj)
{
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<ProgressPattern>();
    CHECK_NULL_VOID(pattern);
    const std::string key = "progress.text";
    pattern->RemoveResObj(key);
    CHECK_NULL_VOID(resObj);
    auto updateFunc = [weak = AceType::WeakClaim(AceType::RawPtr(pattern)), key](
                          const RefPtr<ResourceObject>& obj, bool isFirstLoad = false) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        auto node = pattern->GetHost();
        CHECK_NULL_VOID(node);
        std::string text;
        if (ResourceParseUtils::ParseResString(obj, text)) {
            SetText(AceType::RawPtr(node), text);
        } else {
            SetText(AceType::RawPtr(node), std::nullopt);
        }
    };
    pattern->AddResObj(key, resObj, std::move(updateFunc));
}

void ProgressModelNG::SetFontSizeResource(FrameNode* frameNode, const RefPtr<ResourceObject>& resObj)
{
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<ProgressPattern>();
    CHECK_NULL_VOID(pattern);
    const std::string key = "progress.fontSize";
    pattern->RemoveResObj(key);
    CHECK_NULL_VOID(resObj);
    auto updateFunc = [weak = AceType::WeakClaim(AceType::RawPtr(pattern)), key](
                          const RefPtr<ResourceObject>& obj, bool isFirstLoad = false) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        auto node = pattern->GetHost();
        CHECK_NULL_VOID(node);
        CalcDimension fontSize;
        bool sizeState = false;
        sizeState = ResourceParseUtils::ParseResDimensionNG(obj, fontSize, DimensionUnit::FP);
        if (!sizeState || LessNotEqual(fontSize.Value(), 0.0f) || fontSize.Unit() == DimensionUnit::PERCENT) {
            auto pipeline = PipelineBase::GetCurrentContext();
            CHECK_NULL_VOID(pipeline);
            auto progressTheme = pipeline->GetTheme<ProgressTheme>();
            CHECK_NULL_VOID(progressTheme);
            fontSize = progressTheme->GetTextSize();
        }
        SetFontSize(AceType::RawPtr(node), fontSize);
    };
    pattern->AddResObj(key, resObj, std::move(updateFunc));
}

void ProgressModelNG::SetCapsuleStyleFontColor(bool value)
{
    ACE_UPDATE_PAINT_PROPERTY(ProgressPaintProperty, CapsuleStyleFontColorSetByUser, value);
}

void ProgressModelNG::SetCapsuleStyle(bool value)
{
    ACE_UPDATE_PAINT_PROPERTY(ProgressPaintProperty, CapsuleStyleSetByUser, value);
}

void ProgressModelNG::SetCapsuleStyle(FrameNode* frameNode, bool value)
{
    ACE_UPDATE_NODE_PAINT_PROPERTY(ProgressPaintProperty, CapsuleStyleSetByUser, value, frameNode);
}

void ProgressModelNG::SetCapsuleStyleFontColor(FrameNode* frameNode, bool value)
{
    ACE_UPDATE_NODE_PAINT_PROPERTY(ProgressPaintProperty, CapsuleStyleFontColorSetByUser, value, frameNode);
}

void ProgressModelNG::SetGradientColorByUser(bool value)
{
    ACE_UPDATE_PAINT_PROPERTY(ProgressPaintProperty, GradientColorSetByUser, value);
}

void ProgressModelNG::SetGradientColorByUser(FrameNode* frameNode, bool value)
{
    ACE_UPDATE_NODE_PAINT_PROPERTY(ProgressPaintProperty, GradientColorSetByUser, value, frameNode);
}

void ProgressModelNG::CreateWithResourceObj(JsProgressResourceType type, const RefPtr<ResourceObject>& resObj)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    CreateWithResourceObj(frameNode, type, resObj);
}

void ProgressModelNG::CreateLSOrRingOrCapsuleWithResourceObj(
    FrameNode* frameNode, JsProgressResourceType type, const RefPtr<ResourceObject>& resObj)
{
    switch (type) {
        case JsProgressResourceType::LSStrokeWidth:
            SetLSStrokeWidth(frameNode, resObj);
            break;
        case JsProgressResourceType::LSSweepingEffect:
            SetLSSweepingEffect(frameNode, resObj);
            break;
        case JsProgressResourceType::LSStrokeRadius:
            SetLSStrokeRadius(frameNode, resObj);
            break;
        case JsProgressResourceType::RingStrokeWidth:
            SetRingStrokeWidth(frameNode, resObj);
            break;
        case JsProgressResourceType::RingShadow:
            SetRingShadow(frameNode, resObj);
            break;
        case JsProgressResourceType::RingStatus:
            SetRingStatus(frameNode, resObj);
            break;
        case JsProgressResourceType::RingSweepingEffect:
            SetRingSweepingEffect(frameNode, resObj);
            break;
        case JsProgressResourceType::CapsuleBorderWidth:
            SetCapsuleBorderWidth(frameNode, resObj);
            break;
        case JsProgressResourceType::CapsuleBorderColor:
            SetCapsuleBorderColor(frameNode, resObj);
            break;
        case JsProgressResourceType::CapsuleSweepingEffect:
            SetCapsuleSweepingEffect(frameNode, resObj);
            break;
        default:
            break;
    }
}

void ProgressModelNG::CreateWithResourceObj(
    FrameNode* frameNode, JsProgressResourceType type, const RefPtr<ResourceObject>& resObj)
{
    switch (type) {
        case JsProgressResourceType::COLOR:
            SetProgressColor(frameNode, resObj);
            break;
        case JsProgressResourceType::SmoothEffect:
            SetSmoothResEffect(frameNode, resObj);
            break;
        case JsProgressResourceType::ShowDefaultPercentage:
            SetShowDefaultPercentage(frameNode, resObj);
            break;
        case JsProgressResourceType::FontColor:
            SetFontColorResource(frameNode, resObj);
            break;
        case JsProgressResourceType::BackgroundColor:
            SetBackgroundColorResource(frameNode, resObj);
            break;
        case JsProgressResourceType::FontWeight:
            SetFontWeightResource(frameNode, resObj);
            break;
        case JsProgressResourceType::PSStrokeWidth:
            SetRSStrokeWidth(frameNode, resObj);
            break;
        case JsProgressResourceType::PSScaleWidth:
            SetRSScaleWidth(frameNode, resObj);
            break;
        case JsProgressResourceType::Text:
            SetTextResource(frameNode, resObj);
            break;
        case JsProgressResourceType::FontSize:
            SetFontSizeResource(frameNode, resObj);
            break;
        default:
            CreateLSOrRingOrCapsuleWithResourceObj(frameNode, type, resObj);
            break;
    }
}
} // namespace OHOS::Ace::NG
