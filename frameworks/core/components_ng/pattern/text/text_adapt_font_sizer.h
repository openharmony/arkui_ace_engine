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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_TEXT_TEXT_ADAPT_FONT_SIZER_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_TEXT_TEXT_ADAPT_FONT_SIZER_H

#include <string>

#include "base/geometry/dimension.h"
#include "base/memory/ace_type.h"
#include "core/components_ng/layout/layout_wrapper.h"
#include "core/components_ng/pattern/text/text_styles.h"
#include "core/components_ng/render/paragraph.h"

namespace OHOS::Ace::NG {
class PipelineContext;

class TextAdaptFontSizer : public virtual AceType {
    DECLARE_ACE_TYPE(TextAdaptFontSizer, AceType);
public:
    virtual bool CreateParagraphAndLayout(const TextStyle& textStyle, const std::u16string& content,
        const LayoutConstraintF& contentConstraint, LayoutWrapper* layoutWrapper, bool needLayout = true)
    {
        return false;
    }
    virtual bool CreateParagraphAndLayout(const TextStyle& textStyle, const std::string& content,
        const LayoutConstraintF& contentConstraint, LayoutWrapper* layoutWrapper, bool needLayout = true)
    {
        return false;
    }
    virtual RefPtr<Paragraph> GetParagraph() const = 0;
    virtual void GetSuitableSize(SizeF& maxSize, LayoutWrapper* layoutWrapper) = 0;
    template<typename T>
    bool AdaptMaxFontSize(TextStyle& textStyle, T& content, const Dimension& stepUnit,
        const LayoutConstraintF& contentConstraint, LayoutWrapper* layoutWrapper);
    template<typename T>
    bool AdaptMinFontSize(TextStyle& textStyle, T& content, const Dimension& stepUnit,
        const LayoutConstraintF& contentConstraint, LayoutWrapper* layoutWrapper);
    virtual bool AdaptInlineFocusFontSize(TextStyle& textStyle, const std::u16string& content,
        const Dimension& stepUnit, const LayoutConstraintF& contentConstraint, LayoutWrapper* layoutWrapper)
    {
        return false;
    }

    static bool IsNeedAdaptFontSize(const double& maxFontSize, const double& minFontSize);
    static bool IsNeedAdaptFontSize(const TextStyle& textStyle, const LayoutConstraintF& contentConstraint);
    static void GetAdaptMaxMinFontSize(const TextStyle& textStyle, double& maxFontSize, double& minFontSize,
        const LayoutConstraintF& contentConstraint);
    static void GetAdaptFontSizeStep(const TextStyle& textStyle, double& stepSize, const Dimension& stepUnit,
        const LayoutConstraintF& contentConstraint);
    static SizeF GetMaxMeasureSize(const LayoutConstraintF& contentConstraint);

protected:
    virtual bool DidExceedMaxLines(const SizeF& maxSize);
    void SetAdaptFontSizeLineHeight(const Dimension& lineHeight, const TextStyle& textStyle);
    bool IsAdaptFontSizeExceedLineHeight(const RefPtr<Paragraph>& paragraph);

private:
    virtual bool IsAdaptExceedLimit(const SizeF& maxSize);
    double lineHeight_ = 0.0;
};

template<typename T>
bool TextAdaptFontSizer::AdaptMaxFontSize(TextStyle& textStyle, T& content,
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

template<typename T>
bool TextAdaptFontSizer::AdaptMinFontSize(TextStyle& textStyle, T& content,
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
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_TEXT_TEXT_ADAPT_FONT_SIZER_H
