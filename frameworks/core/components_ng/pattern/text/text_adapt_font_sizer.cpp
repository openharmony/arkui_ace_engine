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

#include <limits>

#include "base/geometry/dimension.h"
#include "base/utils/utils.h"
#include "core/common/container.h"
#include "core/common/font_manager.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {
bool TextAdaptFontSizer::AdaptMaxFontSize(TextStyle& textStyle, const std::string& content,
    const Dimension& stepUnit, const LayoutConstraintF& contentConstraint, LayoutWrapper* layoutWrapper)
{
    double maxFontSize = 0.0;
    double minFontSize = 0.0;
    if (!GetAdaptMaxMinFontSize(textStyle, maxFontSize, minFontSize, contentConstraint)) {
        return false;
    }
    if (LessNotEqual(maxFontSize, minFontSize) || LessOrEqual(minFontSize, 0.0)) {
        // minFontSize or maxFontSize is invalid
        return CreateParagraphAndLayout(textStyle, content, contentConstraint, layoutWrapper, false);
    }
    double stepSize = 0.0;
    if (!GetAdaptFontSizeStep(textStyle, stepSize, stepUnit, contentConstraint)) {
        return false;
    }
    auto maxSize = GetMaxMeasureSize(contentConstraint);
    GetSuitableSize(maxSize, layoutWrapper);
    // Use the minFontSize to layout the paragraph. While using the minFontSize, if the paragraph could be layout in 1
    // line, then increase the font size and try to layout using the maximum available fontsize.
    textStyle.SetFontSize(Dimension(minFontSize));
    if (!CreateParagraphAndLayout(textStyle, content, contentConstraint, layoutWrapper)) {
        return false;
    }
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

bool TextAdaptFontSizer::AdaptMinFontSize(TextStyle& textStyle, const std::string& content,
    const Dimension& stepUnit, const LayoutConstraintF& contentConstraint, LayoutWrapper* layoutWrapper)
{
    double maxFontSize = 0.0;
    double minFontSize = 0.0;
    if (!GetAdaptMaxMinFontSize(textStyle, maxFontSize, minFontSize, contentConstraint)) {
        return false;
    }
    if (LessNotEqual(maxFontSize, minFontSize) || LessOrEqual(minFontSize, 0.0)) {
        return CreateParagraphAndLayout(textStyle, content, contentConstraint, layoutWrapper, false);
    }
    double stepSize = 0.0;
    if (!GetAdaptFontSizeStep(textStyle, stepSize, stepUnit, contentConstraint)) {
        return false;
    }
    auto tag = static_cast<int32_t>((maxFontSize - minFontSize) / stepSize);
    auto length = tag + 1 + (GreatNotEqual(maxFontSize, minFontSize + stepSize * tag) ? 1 : 0);
    int32_t left = 0;
    int32_t right = length - 1;
    float fontSize = 0.0f;
    auto maxSize = GetMaxMeasureSize(contentConstraint);
    GetSuitableSize(maxSize, layoutWrapper);
    while (left <= right) {
        int32_t mid = left + (right - left) / 2;
        fontSize = static_cast<float>((mid == length - 1) ? (maxFontSize) : (minFontSize + stepSize * mid));
        textStyle.SetFontSize(Dimension(fontSize));
        if (!CreateParagraphAndLayout(textStyle, content, contentConstraint, layoutWrapper)) {
            return false;
        }
        if (!DidExceedMaxLines(maxSize)) {
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

bool TextAdaptFontSizer::GetAdaptMaxMinFontSize(TextStyle& textStyle, double& maxFontSize, double& minFontSize,
    const LayoutConstraintF& contentConstraint)
{
    auto pipeline = NG::PipelineContext::GetCurrentContext();
    CHECK_NULL_RETURN(pipeline, false);
    if (!textStyle.GetAdaptMaxFontSize().NormalizeToPx(pipeline->GetDipScale(), pipeline->GetFontScale(),
        pipeline->GetLogicScale(), contentConstraint.maxSize.Height(), maxFontSize)) {
        return false;
    }
    if (!textStyle.GetAdaptMinFontSize().NormalizeToPx(pipeline->GetDipScale(), pipeline->GetFontScale(),
        pipeline->GetLogicScale(), contentConstraint.maxSize.Height(), minFontSize)) {
        return false;
    }
    return true;
}

bool TextAdaptFontSizer::GetAdaptFontSizeStep(TextStyle& textStyle, double& stepSize, const Dimension& stepUnit,
    const LayoutConstraintF& contentConstraint)
{
    auto pipeline = NG::PipelineContext::GetCurrentContext();
    CHECK_NULL_RETURN(pipeline, false);
    Dimension step = stepUnit;
    if (GreatNotEqual(textStyle.GetAdaptFontSizeStep().Value(), 0.0)) {
        step = textStyle.GetAdaptFontSizeStep();
    }
    stepSize = 0.0;
    if (!step.NormalizeToPx(pipeline->GetDipScale(), pipeline->GetFontScale(),
        pipeline->GetLogicScale(), contentConstraint.maxSize.Height(), stepSize)) {
        return false;
    }
    return true;
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
} // namespace OHOS::Ace::NG
