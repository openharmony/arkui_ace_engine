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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_TEXT_TEXT_LAYOUT_ALGORITHM_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_TEXT_TEXT_LAYOUT_ALGORITHM_H

#include <optional>
#include <string>
#include <utility>

#include "core/components_ng/layout/box_layout_algorithm.h"
#include "core/components_ng/layout/layout_wrapper.h"
#include "core/components_ng/pattern/text/span_node.h"
#include "core/components_ng/pattern/text/text_layout_property.h"
#include "core/components_ng/pattern/text/text_styles.h"

namespace OHOS::Ace::NG {
class PipelineContext;
class TextContentModifier;

// TextLayoutAlgorithm acts as the underlying text layout.
class ACE_EXPORT TextLayoutAlgorithm : public BoxLayoutAlgorithm {
    DECLARE_ACE_TYPE(TextLayoutAlgorithm, BoxLayoutAlgorithm);

public:
    TextLayoutAlgorithm();

    TextLayoutAlgorithm(std::list<RefPtr<SpanItem>> spanItemChildren, const RefPtr<Paragraph>& paragraph)
        : spanItemChildren_(std::move(spanItemChildren)), paragraph_(paragraph)
    {}

    ~TextLayoutAlgorithm() override = default;

    void OnReset() override;

    void Measure(LayoutWrapper* layoutWrapper) override;

    std::optional<SizeF> MeasureContent(
        const LayoutConstraintF& contentConstraint, LayoutWrapper* layoutWrapper) override;

    void Layout(LayoutWrapper* layoutWrapper) override;

    const RefPtr<Paragraph>& GetParagraph();

    std::list<RefPtr<SpanItem>>&& GetSpanItemChildren();

    float GetBaselineOffset() const;
    
    size_t GetLineCount() const;

    std::optional<TextStyle> GetTextStyle() const;
    void ApplyIndents(const TextStyle& textStyle, double width);

private:
    void FontRegisterCallback(RefPtr<FrameNode> frameNode, const TextStyle& textStyle);
    bool CreateParagraph(const TextStyle& textStyle, std::string content, LayoutWrapper* layoutWrapper);
    bool CreateParagraphAndLayout(const TextStyle& textStyle, const std::string& content,
        const LayoutConstraintF& contentConstraint, LayoutWrapper* layoutWrapper);
    bool AdaptMinTextSize(TextStyle& textStyle, const std::string& content, const LayoutConstraintF& contentConstraint,
        const RefPtr<PipelineContext>& pipeline, LayoutWrapper* layoutWrapper);
    bool DidExceedMaxLines(const SizeF& maxSize);
    bool AddPropertiesAndAnimations(TextStyle& textStyle, const RefPtr<TextLayoutProperty>& textLayoutProperty,
        const LayoutConstraintF& contentConstraint, const RefPtr<PipelineContext>& pipeline,
        LayoutWrapper* layoutWrapper);
    static TextDirection GetTextDirection(const std::string& content);
    float GetTextWidth() const;
    SizeF GetMaxMeasureSize(const LayoutConstraintF& contentConstraint) const;
    bool BuildParagraph(TextStyle& textStyle, const RefPtr<TextLayoutProperty>& layoutProperty,
        const LayoutConstraintF& contentConstraint, const RefPtr<PipelineContext>& pipeline,
        LayoutWrapper* layoutWrapper);
    bool BuildParagraphAdaptUseMinFontSize(TextStyle& textStyle, const RefPtr<TextLayoutProperty>& layoutProperty,
        const LayoutConstraintF& contentConstraint, const RefPtr<PipelineContext>& pipeline,
        LayoutWrapper* layoutWrapper);
    bool BuildParagraphAdaptUseLayoutConstraint(TextStyle& textStyle, const RefPtr<TextLayoutProperty>& layoutProperty,
        const LayoutConstraintF& contentConstraint, const RefPtr<PipelineContext>& pipeline,
        LayoutWrapper* layoutWrapper);
    std::optional<SizeF> BuildTextRaceParagraph(TextStyle& textStyle, const RefPtr<TextLayoutProperty>& layoutProperty,
        const LayoutConstraintF& contentConstraint, const RefPtr<PipelineContext>& pipeline,
        LayoutWrapper* layoutWrapper);
    void SetPropertyToModifier(const RefPtr<TextLayoutProperty>& layoutProperty, RefPtr<TextContentModifier> modifier);
    bool AdaptMaxTextSize(TextStyle& textStyle, const std::string& content, const LayoutConstraintF& contentConstraint,
        const RefPtr<PipelineContext>& pipeline, LayoutWrapper* layoutWrapper);
    void UpdateTextColorIfForeground(const RefPtr<FrameNode>& frameNode, TextStyle& textStyle);
    void UpdateParagraph(LayoutWrapper* layoutWrapper);
    OffsetF GetContentOffset(LayoutWrapper* layoutWrapper) const;
    bool CreateImageSpanAndLayout(const TextStyle& textStyle, const std::string& content,
        const LayoutConstraintF& contentConstraint, LayoutWrapper* layoutWrapper);
    bool IncludeImageSpan(LayoutWrapper* layoutWrapper);
    void SetImageSpanTextStyle(const TextStyle& textStyle);
    void GetSpanAndImageSpanList(std::list<RefPtr<SpanItem>>& spanList,
        std::map<int32_t, std::pair<Rect, RefPtr<ImageSpanItem>>>& imageSpanList);
    void SplitSpanContentByLines(const TextStyle& textStyle, const std::list<RefPtr<SpanItem>>& spanList,
        std::map<int32_t, std::pair<Rect, std::list<RefPtr<SpanItem>>>>& spanContentLines);
    void SetImageSpanTextStyleByLines(const TextStyle& textStyle,
        std::map<int32_t, std::pair<Rect, RefPtr<ImageSpanItem>>>& imageSpanList,
        std::map<int32_t, std::pair<Rect, std::list<RefPtr<SpanItem>>>>& spanContentLines);

    std::list<RefPtr<SpanItem>> spanItemChildren_;
    RefPtr<Paragraph> paragraph_;
    float baselineOffset_ = 0.0f;
    std::optional<TextStyle> textStyle_;

    ACE_DISALLOW_COPY_AND_MOVE(TextLayoutAlgorithm);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_TEXT_TEXT_LAYOUT_ALGORITHM_H
