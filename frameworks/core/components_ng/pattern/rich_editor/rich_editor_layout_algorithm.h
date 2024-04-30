/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_RICH_EDITOR_RICH_EDITOR_LAYOUT_ALGORITHM_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_RICH_EDITOR_RICH_EDITOR_LAYOUT_ALGORITHM_H

#include "core/components_ng/pattern/text/multiple_paragraph_layout_algorithm.h"
#include "core/components_ng/pattern/text/text_layout_algorithm.h"

namespace OHOS::Ace::NG {
class ACE_EXPORT RichEditorLayoutAlgorithm : public MultipleParagraphLayoutAlgorithm {
    DECLARE_ACE_TYPE(RichEditorLayoutAlgorithm, MultipleParagraphLayoutAlgorithm);

public:
    RichEditorLayoutAlgorithm() = delete;
    RichEditorLayoutAlgorithm(std::list<RefPtr<SpanItem>> spans, ParagraphManager* paragraphs);
    ~RichEditorLayoutAlgorithm() override = default;

    const OffsetF& GetParentGlobalOffset() const
    {
        return parentGlobalOffset_;
    }
    std::optional<SizeF> MeasureContent(
        const LayoutConstraintF& contentConstraint, LayoutWrapper* layoutWrapper) override;
    void Layout(LayoutWrapper* layoutWrapper) override;
    void Measure(LayoutWrapper* layoutWrapper) override;

    const RectF& GetTextRect()
    {
        return richTextRect_;
    }

protected:
    void GetSpanParagraphStyle(const std::unique_ptr<TextLineStyle>& lineStyle, ParagraphStyle& pStyle) override;

private:
    OffsetF GetContentOffset(LayoutWrapper* layoutWrapper) override;
    bool CreateParagraph(
        const TextStyle& textStyle, std::string content, LayoutWrapper* layoutWrapper, double maxWidth = 0.0) override;
    bool BuildParagraph(TextStyle& textStyle, const RefPtr<TextLayoutProperty>& layoutProperty,
        const LayoutConstraintF& contentConstraint, LayoutWrapper* layoutWrapper);
    ParagraphStyle GetParagraphStyle(
        const TextStyle& textStyle, const std::string& content, LayoutWrapper* layoutWrapper) const override;
    float GetShadowOffset(const std::list<RefPtr<SpanItem>>& group) override;
    void UpdateRichTextRect(const SizeF& res, const float& textHeight, LayoutWrapper* layoutWrapper);

    void SetPlaceholder(LayoutWrapper* layoutWrapper);

    void CopySpanStyle(RefPtr<SpanItem> source, RefPtr<SpanItem> target);
    void AppendNewLineSpan();

    const std::list<RefPtr<SpanItem>>& GetSpans() const
    {
        return allSpans_;
    }

    std::list<RefPtr<SpanItem>> allSpans_;
    ParagraphManager* pManager_;
    OffsetF parentGlobalOffset_;
    RectF richTextRect_;
    ACE_DISALLOW_COPY_AND_MOVE(RichEditorLayoutAlgorithm);
};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_RICH_EDITOR_RICH_EDITOR_LAYOUT_ALGORITHM_H
