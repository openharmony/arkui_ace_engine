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
    virtual bool CreateParagraphAndLayout(TextStyle& textStyle, const std::u16string& content,
        const LayoutConstraintF& contentConstraint, LayoutWrapper* layoutWrapper, bool needLayout = true)
    {
        return false;
    }
    virtual RefPtr<Paragraph> GetParagraph() const = 0;
    virtual void GetSuitableSize(SizeF& maxSize, LayoutWrapper* layoutWrapper) = 0;
    bool AdaptMaxFontSize(TextStyle& textStyle, const std::u16string& content, const Dimension& stepUnit,
        const LayoutConstraintF& contentConstraint, LayoutWrapper* layoutWrapper);
    bool AdaptMinFontSize(TextStyle& textStyle, const std::u16string& content, const Dimension& stepUnit,
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
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_TEXT_TEXT_ADAPT_FONT_SIZER_H
