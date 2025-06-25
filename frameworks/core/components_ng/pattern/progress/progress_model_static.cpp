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
        ACE_RESET_NODE_PAINT_PROPERTY(ProgressPaintProperty, Color, frameNode);
    }
}

void ProgressModelStatic::SetGradientColor(FrameNode* frameNode, const std::optional<Gradient>& value)
{
    if (value) {
        ACE_UPDATE_NODE_PAINT_PROPERTY(ProgressPaintProperty, GradientColor, value.value(), frameNode);
    } else {
        ACE_RESET_NODE_PAINT_PROPERTY(ProgressPaintProperty, GradientColor, frameNode);
    }
}

void ProgressModelStatic::SetSmoothEffect(FrameNode* frameNode, const std::optional<bool>& value)
{
    if (value) {
        ACE_UPDATE_NODE_PAINT_PROPERTY(ProgressPaintProperty, EnableSmoothEffect, value.value(), frameNode);
    } else {
        ACE_RESET_NODE_PAINT_PROPERTY(ProgressPaintProperty, EnableSmoothEffect, frameNode);
    }
}

void ProgressModelStatic::SetStrokeWidth(FrameNode* frameNode, const std::optional<Dimension>& value)
{
    if (value) {
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(ProgressLayoutProperty, StrokeWidth, value.value(), frameNode);
    } else {
        ACE_RESET_NODE_LAYOUT_PROPERTY(ProgressLayoutProperty, StrokeWidth, frameNode);
    }
}

void ProgressModelStatic::SetLinearSweepingEffect(FrameNode* frameNode, const std::optional<bool>& value)
{
    if (value) {
        ACE_UPDATE_NODE_PAINT_PROPERTY(ProgressPaintProperty, EnableLinearScanEffect, value.value(), frameNode);
    } else {
        ACE_RESET_NODE_PAINT_PROPERTY(ProgressPaintProperty, EnableLinearScanEffect, frameNode);
    }
}

void ProgressModelStatic::SetRingSweepingEffect(FrameNode* frameNode, const std::optional<bool>& value)
{
    if (value) {
        ACE_UPDATE_NODE_PAINT_PROPERTY(ProgressPaintProperty, EnableRingScanEffect, value.value(), frameNode);
    } else {
        ACE_RESET_NODE_PAINT_PROPERTY(ProgressPaintProperty, EnableRingScanEffect, frameNode);
    }
}

void ProgressModelStatic::SetPaintShadow(FrameNode* frameNode, const std::optional<bool>& value)
{
    if (value) {
        ACE_UPDATE_NODE_PAINT_PROPERTY(ProgressPaintProperty, PaintShadow, value.value(), frameNode);
    } else {
        ACE_RESET_NODE_PAINT_PROPERTY(ProgressPaintProperty, PaintShadow, frameNode);
    }
}

void ProgressModelStatic::SetProgressStatus(FrameNode* frameNode, const std::optional<ProgressStatus>& status)
{
    if (status) {
        ACE_UPDATE_NODE_PAINT_PROPERTY(ProgressPaintProperty, ProgressStatus, status.value(), frameNode);
    } else {
        ACE_RESET_NODE_PAINT_PROPERTY(ProgressPaintProperty, ProgressStatus, frameNode);
    }
}

void ProgressModelStatic::SetScaleCount(FrameNode* frameNode, const std::optional<int32_t>& value)
{
    if (value) {
        ACE_UPDATE_NODE_PAINT_PROPERTY(ProgressPaintProperty, ScaleCount, value.value(), frameNode);
    } else {
        ACE_RESET_NODE_PAINT_PROPERTY(ProgressPaintProperty, ScaleCount, frameNode);
    }
}

void ProgressModelStatic::SetScaleWidth(FrameNode* frameNode, const std::optional<Dimension>& value)
{
    if (value) {
        ACE_UPDATE_NODE_PAINT_PROPERTY(ProgressPaintProperty, ScaleWidth, value.value(), frameNode);
    } else {
        ACE_RESET_NODE_PAINT_PROPERTY(ProgressPaintProperty, ScaleWidth, frameNode);
    }
}

void ProgressModelStatic::SetBorderWidth(FrameNode* frameNode, const std::optional<Dimension>& value)
{
    if (value) {
        ACE_UPDATE_NODE_PAINT_PROPERTY(ProgressPaintProperty, BorderWidth, value.value(), frameNode);
    } else {
        ACE_RESET_NODE_PAINT_PROPERTY(ProgressPaintProperty, BorderWidth, frameNode);
    }
}

void ProgressModelStatic::SetBorderColor(FrameNode* frameNode, const std::optional<Color>& value)
{
    if (value) {
        ACE_UPDATE_NODE_PAINT_PROPERTY(ProgressPaintProperty, BorderColor, value.value(), frameNode);
    } else {
        ACE_RESET_NODE_PAINT_PROPERTY(ProgressPaintProperty, BorderColor, frameNode);
    }
}

void ProgressModelStatic::SetSweepingEffect(FrameNode* frameNode, const std::optional<bool>& value)
{
    if (value) {
        ACE_UPDATE_NODE_PAINT_PROPERTY(ProgressPaintProperty, EnableScanEffect, value.value(), frameNode);
    } else {
        ACE_RESET_NODE_PAINT_PROPERTY(ProgressPaintProperty, EnableScanEffect, frameNode);
    }
}

void ProgressModelStatic::SetShowText(FrameNode* frameNode, const std::optional<bool>& value)
{
    if (value) {
        ACE_UPDATE_NODE_PAINT_PROPERTY(ProgressPaintProperty, EnableShowText, value.value(), frameNode);
    } else {
        ACE_RESET_NODE_PAINT_PROPERTY(ProgressPaintProperty, EnableShowText, frameNode);
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
        ACE_RESET_NODE_PAINT_PROPERTY(ProgressPaintProperty, TextColor, frameNode);
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
        ACE_RESET_NODE_PAINT_PROPERTY(ProgressPaintProperty, TextSize, frameNode);
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
        ACE_RESET_NODE_PAINT_PROPERTY(ProgressPaintProperty, FontWeight, frameNode);
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
        ACE_RESET_NODE_PAINT_PROPERTY(ProgressPaintProperty, FontFamily, frameNode);
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
        ACE_RESET_NODE_PAINT_PROPERTY(ProgressPaintProperty, ItalicFontStyle, frameNode);
    }
    textHost->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
}

void ProgressModelStatic::SetStrokeRadius(FrameNode* frameNode, const std::optional<Dimension>& value)
{
    if (value) {
        ACE_UPDATE_NODE_PAINT_PROPERTY(ProgressPaintProperty, StrokeRadius, value.value(), frameNode);
    } else {
        ACE_RESET_NODE_PAINT_PROPERTY(ProgressPaintProperty, StrokeRadius, frameNode);
    }
}

void ProgressModelStatic::SetPrivacySensitive(FrameNode* frameNode, const std::optional<bool>& flag)
{
    // if (flag) {
    //     ACE_UPDATE_NODE_PAINT_PROPERTY(ProgressPaintProperty, IsSensitive, *flag, frameNode);
    // } else {
    //     ACE_RESET_NODE_PAINT_PROPERTY_WITH_FLAG(ProgressPaintProperty, IsSensitive, PROPERTY_UPDATE_RENDER, frameNode);
    // }
    // ViewAbstractModelStatic::SetPrivacySensitive(frameNode, flag);
}
} // namespace OHOS::Ace::NG