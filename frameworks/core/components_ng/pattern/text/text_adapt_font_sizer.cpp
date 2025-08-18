/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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

#include "core/components_ng/pattern/text/text_adapt_font_sizer.h"

namespace OHOS::Ace::NG {
bool TextAdaptFontSizer::AdaptMaxFontSize(TextStyle& textStyle, const std::u16string& content,
    const Dimension& stepUnit, const LayoutConstraintF& contentConstraint, LayoutWrapper* layoutWrapper)
{
    double maxFontSize = 0.0;
    double minFontSize = 0.0;
    GetAdaptMaxMinFontSize(textStyle, maxFontSize, minFontSize, contentConstraint);
    if (LessNotEqual(maxFontSize, minFontSize) || LessOrEqual(minFontSize, 0.0)) {
        // minFontSize or maxFontSize is invalid
        return CreateParagraphAndLayout(textStyle, content, contentConstraint, layoutWrapper, false);
    }
    double stepSize = 0.0;
    GetAdaptFontSizeStep(textStyle, stepSize, stepUnit, contentConstraint);
    auto maxSize = GetMaxMeasureSize(contentConstraint);
    GetSuitableSize(maxSize, layoutWrapper);
    // Use the minFontSize to layout the paragraph. While using the minFontSize, if the paragraph could be layout in 1
    // line, then increase the font size and try to layout using the maximum available fontsize.
    textStyle.SetFontSize(Dimension(minFontSize));
    CreateParagraphAndLayout(textStyle, content, contentConstraint, layoutWrapper);
    if (IsAdaptExceedLimit(maxSize)) {
        return true;
    }
    auto tag = static_cast<int32_t>((maxFontSize - minFontSize) / stepSize);
    auto length = tag + 1 + (GreatNotEqual(maxFontSize, minFontSize + stepSize * tag) ? 1 : 0);
    int32_t left = 0;
    int32_t right = length - 1;
    float fontSize = 0.0f;
    while (left <= right) {
        int32_t mid = left + (right - left) / 2;
        fontSize = static_cast<float>((mid == length - 1) ? (maxFontSize) : (minFontSize + stepSize * mid));
        textStyle.SetFontSize(Dimension(fontSize));
        if (!CreateParagraphAndLayout(textStyle, content, contentConstraint, layoutWrapper)) {
            return false;
        }
        if (!IsAdaptExceedLimit(maxSize)) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    fontSize = static_cast<float>((left - 1 == length - 1) ? (maxFontSize) : (minFontSize + stepSize * (left - 1)));
    fontSize = LessNotEqual(fontSize, minFontSize) ? minFontSize : fontSize;
    fontSize = GreatNotEqual(fontSize, maxFontSize) ? maxFontSize : fontSize;
    textStyle.SetFontSize(Dimension(fontSize));
    return CreateParagraphAndLayout(textStyle, content, contentConstraint, layoutWrapper);
}

bool TextAdaptFontSizer::AdaptMinFontSize(TextStyle& textStyle, const std::u16string& content,
    const Dimension& stepUnit, const LayoutConstraintF& contentConstraint, LayoutWrapper* layoutWrapper)
{
    double maxFontSize = 0.0;
    double minFontSize = 0.0;
    GetAdaptMaxMinFontSize(textStyle, maxFontSize, minFontSize, contentConstraint);
    if (LessNotEqual(maxFontSize, minFontSize) || LessOrEqual(minFontSize, 0.0)) {
        return CreateParagraphAndLayout(textStyle, content, contentConstraint, layoutWrapper, false);
    }
    double stepSize = 0.0;
    GetAdaptFontSizeStep(textStyle, stepSize, stepUnit, contentConstraint);
    auto maxSize = GetMaxMeasureSize(contentConstraint);
    GetSuitableSize(maxSize, layoutWrapper);
    while (GreatOrEqual(maxFontSize, minFontSize)) {
        textStyle.SetFontSize(Dimension(maxFontSize));
        if (!CreateParagraphAndLayout(textStyle, content, contentConstraint, layoutWrapper)) {
            return false;
        }
        if (!DidExceedMaxLines(maxSize)) {
            break;
        }
        maxFontSize -= stepSize;
    }
    return true;
}

void TextAdaptFontSizer::GetAdaptMaxMinFontSize(const TextStyle& textStyle, double& maxFontSize, double& minFontSize,
    const LayoutConstraintF& contentConstraint)
{
    maxFontSize = textStyle.GetAdaptMaxFontSize().ConvertToPxDistribute(
        textStyle.GetMinFontScale(), textStyle.GetMaxFontScale(), textStyle.IsAllowScale());
    minFontSize = textStyle.GetAdaptMinFontSize().ConvertToPxDistribute(
        textStyle.GetMinFontScale(), textStyle.GetMaxFontScale(), textStyle.IsAllowScale());
}

void TextAdaptFontSizer::GetAdaptFontSizeStep(const TextStyle& textStyle, double& stepSize, const Dimension& stepUnit,
    const LayoutConstraintF& contentConstraint)
{
    Dimension step = stepUnit;
    if (GreatNotEqual(textStyle.GetAdaptFontSizeStep().Value(), 0.0)) {
        step = textStyle.GetAdaptFontSizeStep();
    }
    stepSize =
        step.ConvertToPxDistribute(textStyle.GetMinFontScale(), textStyle.GetMaxFontScale(), textStyle.IsAllowScale());
}

SizeF TextAdaptFontSizer::GetMaxMeasureSize(const LayoutConstraintF& contentConstraint)
{
    auto maxSize = contentConstraint.selfIdealSize;
    maxSize.UpdateIllegalSizeWithCheck(contentConstraint.maxSize);
    return maxSize.ConvertToSizeT();
}

bool TextAdaptFontSizer::DidExceedMaxLines(const SizeF& maxSize)
{
    auto paragraph = GetParagraph();
    CHECK_NULL_RETURN(paragraph, false);
    bool didExceedMaxLines = paragraph->DidExceedMaxLines();
    didExceedMaxLines = didExceedMaxLines || GreatNotEqual(paragraph->GetHeight(), maxSize.Height());
    didExceedMaxLines = didExceedMaxLines || GreatNotEqual(paragraph->GetLongestLine(), maxSize.Width());
    return didExceedMaxLines;
}

bool TextAdaptFontSizer::IsAdaptExceedLimit(const SizeF& maxSize)
{
    auto paragraph = GetParagraph();
    CHECK_NULL_RETURN(paragraph, false);
    return (paragraph->GetLineCount() > 1) || paragraph->DidExceedMaxLines() ||
        GreatNotEqual(paragraph->GetLongestLine(), maxSize.Width());
}

bool TextAdaptFontSizer::IsNeedAdaptFontSize(const double& maxFontSize, const double& minFontSize)
{
    if (LessNotEqual(maxFontSize, minFontSize) || LessOrEqual(minFontSize, 0.0)) {
        return false;
    }
    return true;
}

bool TextAdaptFontSizer::IsNeedAdaptFontSize(const TextStyle& textStyle, const LayoutConstraintF& contentConstraint)
{
    double maxFontSize = 0.0;
    double minFontSize = 0.0;
    GetAdaptMaxMinFontSize(textStyle, maxFontSize, minFontSize, contentConstraint);
    return IsNeedAdaptFontSize(maxFontSize, minFontSize);
}

void TextAdaptFontSizer::SetAdaptFontSizeLineHeight(const Dimension& lineHeight, const TextStyle& textStyle)
{
    lineHeight_ = lineHeight.ConvertToPxDistribute(
        textStyle.GetMinFontScale(), textStyle.GetMaxFontScale(), textStyle.IsAllowScale());
}

bool TextAdaptFontSizer::IsAdaptFontSizeExceedLineHeight(const RefPtr<Paragraph>& paragraph)
{
    if (LessOrEqual(lineHeight_, 0.0)) {
        return false;
    }
    auto lineMetrics = paragraph->GetLineMetrics(0);
    return GreatNotEqual(lineMetrics.height, lineHeight_);
}
} // namespace OHOS::Ace::NG
