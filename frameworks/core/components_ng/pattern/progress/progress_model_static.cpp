/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

#include "core/components_ng/pattern/progress/progress_model_static.h"

#include "base/geometry/dimension.h"
#include "core/components/progress/progress_component.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/view_abstract_model_static.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/pattern.h"
#include "core/components_ng/pattern/progress/progress_date.h"
#include "core/components_ng/pattern/progress/progress_pattern.h"
#include "core/components_ng/pattern/text/text_layout_property.h"
#include "core/components_ng/pattern/text/text_pattern.h"
#include "core/components_v2/inspector/inspector_constants.h"

namespace OHOS::Ace::NG {
void ProgressModelStatic::SetColor(FrameNode* frameNode, const std::optional<Color>& value)
{
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<ProgressPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetUserInitiatedColor(value.has_value());
    if (value) {
        ACE_UPDATE_NODE_PAINT_PROPERTY(ProgressPaintProperty, Color, value.value(), frameNode);
    } else {
        ACE_RESET_NODE_PAINT_PROPERTY_WITH_FLAG(ProgressPaintProperty, Color, PROPERTY_UPDATE_RENDER, frameNode);
    }
}

void ProgressModelStatic::SetGradientColor(FrameNode* frameNode, const std::optional<Gradient>& value)
{
    if (value) {
        ACE_UPDATE_NODE_PAINT_PROPERTY(ProgressPaintProperty, GradientColor, value.value(), frameNode);
    } else {
        ACE_RESET_NODE_PAINT_PROPERTY_WITH_FLAG(
            ProgressPaintProperty, GradientColor, PROPERTY_UPDATE_RENDER, frameNode);
    }
}

void ProgressModelStatic::SetSmoothEffect(FrameNode* frameNode, const std::optional<bool>& value)
{
    if (value) {
        ACE_UPDATE_NODE_PAINT_PROPERTY(ProgressPaintProperty, EnableSmoothEffect, value.value(), frameNode);
    } else {
        ACE_RESET_NODE_PAINT_PROPERTY_WITH_FLAG(
            ProgressPaintProperty, EnableSmoothEffect, PROPERTY_UPDATE_RENDER, frameNode);
    }
}

void ProgressModelStatic::SetStrokeWidth(FrameNode* frameNode, const std::optional<Dimension>& value)
{
    if (value) {
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(ProgressLayoutProperty, StrokeWidth, value.value(), frameNode);
    } else {
        ACE_RESET_NODE_LAYOUT_PROPERTY_WITH_FLAG(
            ProgressLayoutProperty, StrokeWidth, PROPERTY_UPDATE_MEASURE, frameNode);
    }
}

void ProgressModelStatic::SetLinearSweepingEffect(FrameNode* frameNode, const std::optional<bool>& value)
{
    if (value) {
        ACE_UPDATE_NODE_PAINT_PROPERTY(ProgressPaintProperty, EnableLinearScanEffect, value.value(), frameNode);
    } else {
        ACE_RESET_NODE_PAINT_PROPERTY_WITH_FLAG(
            ProgressPaintProperty, EnableLinearScanEffect, PROPERTY_UPDATE_RENDER, frameNode);
    }
}

void ProgressModelStatic::SetRingSweepingEffect(FrameNode* frameNode, const std::optional<bool>& value)
{
    if (value) {
        ACE_UPDATE_NODE_PAINT_PROPERTY(ProgressPaintProperty, EnableRingScanEffect, value.value(), frameNode);
    } else {
        ACE_RESET_NODE_PAINT_PROPERTY_WITH_FLAG(
            ProgressPaintProperty, EnableRingScanEffect, PROPERTY_UPDATE_RENDER, frameNode);
    }
}

void ProgressModelStatic::SetPaintShadow(FrameNode* frameNode, const std::optional<bool>& value)
{
    if (value) {
        ACE_UPDATE_NODE_PAINT_PROPERTY(ProgressPaintProperty, PaintShadow, value.value(), frameNode);
    } else {
        ACE_RESET_NODE_PAINT_PROPERTY_WITH_FLAG(ProgressPaintProperty, PaintShadow, PROPERTY_UPDATE_RENDER, frameNode);
    }
}

void ProgressModelStatic::SetProgressStatus(FrameNode* frameNode, const std::optional<ProgressStatus>& status)
{
    if (status) {
        ACE_UPDATE_NODE_PAINT_PROPERTY(ProgressPaintProperty, ProgressStatus, status.value(), frameNode);
    } else {
        ACE_RESET_NODE_PAINT_PROPERTY_WITH_FLAG(
            ProgressPaintProperty, ProgressStatus, PROPERTY_UPDATE_RENDER, frameNode);
    }
}

void ProgressModelStatic::SetScaleCount(FrameNode* frameNode, const std::optional<int32_t>& value)
{
    if (value) {
        ACE_UPDATE_NODE_PAINT_PROPERTY(ProgressPaintProperty, ScaleCount, value.value(), frameNode);
    } else {
        ACE_RESET_NODE_PAINT_PROPERTY_WITH_FLAG(ProgressPaintProperty, ScaleCount, PROPERTY_UPDATE_RENDER, frameNode);
    }
}

void ProgressModelStatic::SetScaleWidth(FrameNode* frameNode, const std::optional<Dimension>& value)
{
    if (value) {
        ACE_UPDATE_NODE_PAINT_PROPERTY(ProgressPaintProperty, ScaleWidth, value.value(), frameNode);
    } else {
        ACE_RESET_NODE_PAINT_PROPERTY_WITH_FLAG(ProgressPaintProperty, ScaleWidth, PROPERTY_UPDATE_RENDER, frameNode);
    }
}

void ProgressModelStatic::SetBorderWidth(FrameNode* frameNode, const std::optional<Dimension>& value)
{
    if (value) {
        ACE_UPDATE_NODE_PAINT_PROPERTY(ProgressPaintProperty, BorderWidth, value.value(), frameNode);
    } else {
        ACE_RESET_NODE_PAINT_PROPERTY_WITH_FLAG(ProgressPaintProperty, BorderWidth, PROPERTY_UPDATE_RENDER, frameNode);
    }
}

void ProgressModelStatic::SetBorderColor(FrameNode* frameNode, const std::optional<Color>& value)
{
    if (value) {
        ACE_UPDATE_NODE_PAINT_PROPERTY(ProgressPaintProperty, BorderColor, value.value(), frameNode);
    } else {
        ACE_RESET_NODE_PAINT_PROPERTY_WITH_FLAG(ProgressPaintProperty, BorderColor, PROPERTY_UPDATE_RENDER, frameNode);
    }
}

void ProgressModelStatic::SetBorderRadius(FrameNode* frameNode, const std::optional<Dimension>& value)
{
    if (value) {
        ACE_UPDATE_NODE_PAINT_PROPERTY(ProgressPaintProperty, BorderRadius, value.value(), frameNode);
    } else {
        ACE_RESET_NODE_PAINT_PROPERTY_WITH_FLAG(ProgressPaintProperty, BorderRadius, PROPERTY_UPDATE_RENDER,
            frameNode);
    }
}

void ProgressModelStatic::SetSweepingEffect(FrameNode* frameNode, const std::optional<bool>& value)
{
    if (value) {
        ACE_UPDATE_NODE_PAINT_PROPERTY(ProgressPaintProperty, EnableScanEffect, value.value(), frameNode);
    } else {
        ACE_RESET_NODE_PAINT_PROPERTY_WITH_FLAG(
            ProgressPaintProperty, EnableScanEffect, PROPERTY_UPDATE_RENDER, frameNode);
    }
}

void ProgressModelStatic::SetShowText(FrameNode* frameNode, const std::optional<bool>& value)
{
    if (value) {
        ACE_UPDATE_NODE_PAINT_PROPERTY(ProgressPaintProperty, EnableShowText, value.value(), frameNode);
    } else {
        ACE_RESET_NODE_PAINT_PROPERTY_WITH_FLAG(
            ProgressPaintProperty, EnableShowText, PROPERTY_UPDATE_RENDER, frameNode);
    }
}

void ProgressModelStatic::SetText(FrameNode* frameNode, const std::optional<std::string>& value)
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

void ProgressModelStatic::SetFontColor(FrameNode* frameNode, const std::optional<Color>& value)
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
        ACE_RESET_NODE_PAINT_PROPERTY_WITH_FLAG(ProgressPaintProperty, TextColor, PROPERTY_UPDATE_RENDER, frameNode);
    }
    textHost->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
}

void ProgressModelStatic::SetFontSize(FrameNode* frameNode, const std::optional<Dimension>& value)
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
        ACE_RESET_NODE_PAINT_PROPERTY_WITH_FLAG(ProgressPaintProperty, TextSize, PROPERTY_UPDATE_RENDER, frameNode);
    }
    textHost->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
}

void ProgressModelStatic::SetFontWeight(FrameNode* frameNode, const std::optional<FontWeight>& value)
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
        ACE_RESET_NODE_PAINT_PROPERTY_WITH_FLAG(ProgressPaintProperty, FontWeight, PROPERTY_UPDATE_RENDER, frameNode);
    }
    textHost->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
}

void ProgressModelStatic::SetFontFamily(FrameNode* frameNode, const std::optional<std::vector<std::string>>& value)
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
        ACE_RESET_NODE_PAINT_PROPERTY_WITH_FLAG(ProgressPaintProperty, FontFamily, PROPERTY_UPDATE_RENDER, frameNode);
    }
    textHost->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
}

void ProgressModelStatic::SetItalicFontStyle(FrameNode* frameNode, const std::optional<Ace::FontStyle>& value)
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
        ACE_RESET_NODE_PAINT_PROPERTY_WITH_FLAG(
            ProgressPaintProperty, ItalicFontStyle, PROPERTY_UPDATE_RENDER, frameNode);
    }
    textHost->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
}

void ProgressModelStatic::SetStrokeRadius(FrameNode* frameNode, const std::optional<Dimension>& value)
{
    if (value) {
        ACE_UPDATE_NODE_PAINT_PROPERTY(ProgressPaintProperty, StrokeRadius, value.value(), frameNode);
    } else {
        ACE_RESET_NODE_PAINT_PROPERTY_WITH_FLAG(ProgressPaintProperty, StrokeRadius, PROPERTY_UPDATE_RENDER, frameNode);
    }
}

void ProgressModelStatic::SetPrivacySensitive(FrameNode* frameNode, const std::optional<bool>& flag)
{
    if (flag) {
        ACE_UPDATE_NODE_PAINT_PROPERTY(ProgressPaintProperty, IsSensitive, *flag, frameNode);
    } else {
        ACE_RESET_NODE_PAINT_PROPERTY_WITH_FLAG(ProgressPaintProperty, IsSensitive, PROPERTY_UPDATE_RENDER, frameNode);
    }
    ViewAbstractModelStatic::SetPrivacySensitive(frameNode, flag);
}

void ProgressModelStatic::SetValue(FrameNode* frameNode, const std::optional<double>& valueOpt)
{
    auto progressPaintProperty = frameNode->GetPaintProperty<ProgressPaintProperty>();
    CHECK_NULL_VOID(progressPaintProperty);
    if (valueOpt) {
        auto maxValue = progressPaintProperty->GetMaxValue();
        double value = valueOpt.value() < 0 ? 0 : valueOpt.value();
        value = value > maxValue ? maxValue.value_or(0) : value;
        ACE_UPDATE_NODE_PAINT_PROPERTY(ProgressPaintProperty, Value, value, frameNode);
    } else {
        ACE_RESET_NODE_PAINT_PROPERTY_WITH_FLAG(ProgressPaintProperty, Value, PROPERTY_UPDATE_RENDER, frameNode);
    }
    auto pattern = frameNode->GetPattern<ProgressPattern>();
    CHECK_NULL_VOID(pattern);
    if (!pattern->IsTextFromUser()) {
        SetText(frameNode, std::nullopt);
    }
}

void ProgressModelStatic::Initialize(FrameNode* frameNode, double min, double value, double cachedValue, double max,
    NG::ProgressType type)
{
    ACE_UPDATE_NODE_PAINT_PROPERTY(ProgressPaintProperty, Value, value, frameNode);
    ACE_UPDATE_NODE_PAINT_PROPERTY(ProgressPaintProperty, MaxValue, max, frameNode);
    ACE_UPDATE_NODE_PAINT_PROPERTY(ProgressPaintProperty, ProgressType, type, frameNode);
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(ProgressLayoutProperty, Type, type, frameNode);
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
    auto eventHub = frameNode->GetOrCreateInputEventHub();
    CHECK_NULL_VOID(eventHub);
    auto pattern = frameNode->GetPattern<ProgressPattern>();
    CHECK_NULL_VOID(pattern);
    if (type == ProgressType::CAPSULE) {
        if (frameNode->GetChildren().empty()) {
            auto textNode = FrameNode::CreateFrameNode(
                V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
            textNode->SetInternal();
            textNode->MountToParent(AceType::Claim(reinterpret_cast<FrameNode*>(frameNode)));
        }
        auto textHost = AceType::DynamicCast<FrameNode>(frameNode->GetChildAtIndex(0));
        CHECK_NULL_VOID(textHost);
        SetTextDefaultStyle(frameNode, textHost, value, max);
        textHost->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
        eventHub->SetHoverEffect(HoverEffectType::SCALE);
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

void ProgressModelStatic::SetTextDefaultStyle(FrameNode* frameNode, const RefPtr<FrameNode>& textNode,
    double value, double maxValue)
{
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
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
    ACE_UPDATE_NODE_PAINT_PROPERTY(ProgressPaintProperty, Text, number, frameNode);
}

void ProgressModelStatic::SetBackgroundColor(FrameNode* frameNode, const std::optional<Color>& value)
{
    CHECK_NULL_VOID(frameNode);
    if (value) {
        ACE_UPDATE_NODE_PAINT_PROPERTY(ProgressPaintProperty, BackgroundColor, value.value(), frameNode);
    } else {
        ACE_RESET_NODE_PAINT_PROPERTY_WITH_FLAG(
            ProgressPaintProperty, BackgroundColor, PROPERTY_UPDATE_RENDER, frameNode);
    }
}
} // namespace OHOS::Ace::NG
