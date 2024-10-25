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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_TEXT_MULTIPLE_PARAGRAPH_LAYOUT_ALGORITHM_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_TEXT_MULTIPLE_PARAGRAPH_LAYOUT_ALGORITHM_H

#include <list>
#include <optional>
#include <string>
#include <unordered_map>
#include <utility>

#include "base/memory/referenced.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/layout/box_layout_algorithm.h"
#include "core/components_ng/layout/layout_wrapper.h"
#include "core/components_ng/pattern/rich_editor/paragraph_manager.h"
#include "core/components_ng/pattern/text/span_node.h"
#include "core/components_ng/pattern/text/text_content_modifier.h"
#include "core/components_ng/pattern/text/text_layout_property.h"
#include "core/components_ng/pattern/text/text_styles.h"

namespace OHOS::Ace::NG {
// TextLayoutAlgorithm acts as the underlying text layout.
class ACE_EXPORT MultipleParagraphLayoutAlgorithm : public BoxLayoutAlgorithm {
    DECLARE_ACE_TYPE(MultipleParagraphLayoutAlgorithm, BoxLayoutAlgorithm);

public:
    MultipleParagraphLayoutAlgorithm() = default;
    ~MultipleParagraphLayoutAlgorithm() override = default;

    void Measure(LayoutWrapper* layoutWrapper) override;
    void Layout(LayoutWrapper* layoutWrapper) override;
    virtual float GetBaselineOffset() const
    {
        return 0.0f;
    }

    static SizeF GetMaxMeasureSize(const LayoutConstraintF& contentConstraint);
    RefPtr<Paragraph> GetSingleParagraph() const;

protected:
    void GetSpanParagraphStyle(LayoutWrapper* layoutWrapper, const RefPtr<SpanItem>& spanItem, ParagraphStyle& pStyle);
    virtual ParagraphStyle GetParagraphStyle(
        const TextStyle& textStyle, const std::string& content, LayoutWrapper* layoutWrapper) const;
    virtual bool CreateParagraph(
        const TextStyle& textStyle, std::string content, LayoutWrapper* layoutWrapper, double maxWidth = 0.0) = 0;
    virtual void HandleEmptyParagraph(RefPtr<Paragraph> paragraph, const std::list<RefPtr<SpanItem>>& spanGroup) {}
    virtual RefPtr<SpanItem> GetParagraphStyleSpanItem(const std::list<RefPtr<SpanItem>>& spanGroup)
    {
        CHECK_NULL_RETURN(!spanGroup.empty(), nullptr);
        return spanGroup.front();
    }

    void ApplyIndent(ParagraphStyle& paragraphStyle, const RefPtr<Paragraph>& paragraph, double width,
        const TextStyle& textStyle);
    void ConstructTextStyles(
        const LayoutConstraintF& contentConstraint, LayoutWrapper* layoutWrapper, TextStyle& textStyle);
    bool ParagraphReLayout(const LayoutConstraintF& contentConstraint);
    bool UpdateParagraphBySpan(LayoutWrapper* layoutWrapper, ParagraphStyle paraStyle, double maxWidth,
        const TextStyle& textStyle);
    OffsetF SetContentOffset(LayoutWrapper* layoutWrapper);
    virtual void SetAdaptFontSizeStepToTextStyle(
        TextStyle& textStyle, const std::optional<Dimension>& adaptFontSizeStep);
    std::string SpansToString()
    {
        std::stringstream ss;
        for (auto& list : spans_) {
            ss << "[";
            for_each(list.begin(), list.end(), [&ss](RefPtr<SpanItem>& item) {
                ss << "[" << item->interval.first << "," << item->interval.second << ":"
                   << StringUtils::RestoreEscape(item->content) << "], ";
            });
            ss << "], ";
        }
        return ss.str();
    }

    std::list<ParagraphManager::ParagraphInfo> GetParagraphs()
    {
        std::list<ParagraphManager::ParagraphInfo> paragraphInfo;
        if (paragraphManager_) {
            paragraphInfo = paragraphManager_->GetParagraphs();
        }
        return paragraphInfo;
    }

    std::vector<std::list<RefPtr<SpanItem>>> spans_;
    RefPtr<ParagraphManager> paragraphManager_;
    std::optional<TextStyle> textStyle_;
    float indent_ = 0.0f;
    float baselineOffset_ = 0.0f;
    float shadowOffset_ = 0.0f;
    bool spanStringHasMaxLines_ = false;
    bool isSpanStringMode_ = false;
    bool isMarquee_ = false;

private:
    virtual OffsetF GetContentOffset(LayoutWrapper* layoutWrapper) = 0;
    virtual float GetShadowOffset(const std::list<RefPtr<SpanItem>>& group)
    {
        return 0.0f;
    }
    static TextDirection GetTextDirection(const std::string& content, LayoutWrapper* layoutWrapper);
    static TextDirection GetTextDirectionByContent(const std::string& content);

    void UpdateSymbolSpanEffect(
        RefPtr<FrameNode>& frameNode, const RefPtr<Paragraph>& paragraph, const std::list<RefPtr<SpanItem>>& spans);
    void FontRegisterCallback(const RefPtr<FrameNode>& frameNode, const TextStyle& textStyle);
    void UpdateTextColorIfForeground(const RefPtr<FrameNode>& frameNode, TextStyle& textStyle);
    void SetPropertyToModifier(const RefPtr<TextLayoutProperty>& layoutProperty,
        const RefPtr<TextContentModifier>& modifier, const TextStyle& textStyle);
    void SetDecorationPropertyToModifier(const RefPtr<TextLayoutProperty>& layoutProperty,
        const RefPtr<TextContentModifier>& modifier, const TextStyle& textStyle);
    void SetFontSizePropertyToModifier(const RefPtr<TextLayoutProperty>& layoutProperty,
        const RefPtr<TextContentModifier>&, const TextStyle& textStyle);

    void AddImageToParagraph(RefPtr<ImageSpanItem>& imageSpanItem, const RefPtr<LayoutWrapper>& iterItem,
        const LayoutConstraintF& layoutConstrain, const RefPtr<Paragraph>& paragraph, int32_t& spanTextLength,
        const TextStyle& textStyle);
    void AddPlaceHolderToParagraph(RefPtr<PlaceholderSpanItem>& placeholderSpanItem,
        const RefPtr<LayoutWrapper>& layoutWrapper, const LayoutConstraintF& layoutConstrain,
        const RefPtr<Paragraph>& paragraph, int32_t& spanTextLength);
    void UpdateParagraphByCustomSpan(RefPtr<CustomSpanItem>& customSpanItem, LayoutWrapper* layoutWrapper,
        const RefPtr<Paragraph>& paragraph, int32_t& spanTextLength, CustomSpanPlaceholderInfo& customSpanPlaceholder);

    void AddSymbolSpanToParagraph(const RefPtr<SpanItem>& child, int32_t& spanTextLength,
        const RefPtr<FrameNode>& frameNode, const RefPtr<Paragraph>& paragraph);
    void AddTextSpanToParagraph(const RefPtr<SpanItem>& child, int32_t& spanTextLength,
        const RefPtr<FrameNode>& frameNode, const RefPtr<Paragraph>& paragraph);

    void GetChildrenPlaceholderIndex(std::vector<int32_t>& placeholderIndex);
    TextStyle InheritParentTextStyle();

    int32_t preParagraphsPlaceholderCount_ = 0;
    int32_t currentParagraphPlaceholderCount_ = 0;

    float paragraphFontSize_ = 0.0f;

    ACE_DISALLOW_COPY_AND_MOVE(MultipleParagraphLayoutAlgorithm);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_TEXT_MULTIPLE_PARAGRAPH_LAYOUT_ALGORITHM_H
