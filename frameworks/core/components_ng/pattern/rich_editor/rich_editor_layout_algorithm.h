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
#include "core/components_ng/pattern/rich_editor/rich_editor_paragraph_manager.h"

namespace OHOS::Ace::NG {
class StyleManager;
template<typename KeyType, typename ValueType>
class LRUMap {
public:
    using Iterator = typename std::list<std::pair<KeyType, ValueType>>::iterator;
 
    LRUMap() {}
    LRUMap(size_t initialCapacity) : capacity(initialCapacity) {}
 
    Iterator Get(const KeyType& key)
    {
        auto it = cacheMap.find(key);
        if (it == cacheMap.end()) {
            return cacheList.end(); // Return end iterator if not found
        }

        // Move the accessed item to the front of the list
        cacheList.splice(cacheList.begin(), cacheList, it->second);
 
        return it->second;
    }

    Iterator End()
    {
        return cacheList.end();
    }

    size_t Size()
    {
        return cacheMap.size();
    }

    void Erase(const KeyType& key)
    {
        auto it = cacheMap.find(key);
        if (it != cacheMap.end()) {
            cacheList.erase(it->second);
            cacheMap.erase(it);
        }
    }
 
    void Clear()
    {
        cacheList.clear();
        cacheMap.clear();
    }
 
    void Put(const KeyType& key, const ValueType& value)
    {
        auto it = cacheMap.find(key);
        if (it != cacheMap.end()) {
            // Update existing item and move to front
            cacheList.splice(cacheList.begin(), cacheList, it->second);
            it->second->second = value;
        } else {
            // Insert new item
            if (cacheList.size() >= capacity) {
                // Remove least recently used item
                auto last = cacheList.end();
                last--;
                cacheMap.erase(last->first);
                cacheList.pop_back();
            }
            cacheList.emplace_front(key, value);
            cacheMap[key] = cacheList.begin();
        }
    }
 
    void SetCapacity(size_t newCapacity)
    {
        capacity = newCapacity;
        while (cacheList.size() > capacity) {
            auto last = cacheList.end();
            last--;
            cacheMap.erase(last->first);
            cacheList.pop_back();
        }
    }

private:
    size_t capacity = SIZE_MAX;
    std::list<std::pair<KeyType, ValueType>> cacheList;
    std::unordered_map<KeyType, Iterator> cacheMap;
};

class ACE_EXPORT RichEditorLayoutAlgorithm : public MultipleParagraphLayoutAlgorithm {
    DECLARE_ACE_TYPE(RichEditorLayoutAlgorithm, MultipleParagraphLayoutAlgorithm);

public:
    RichEditorLayoutAlgorithm() = delete;
    RichEditorLayoutAlgorithm(std::list<RefPtr<SpanItem>> spans, RichEditorParagraphManager* paragraphs,
        LRUMap<std::uintptr_t, RefPtr<Paragraph>>* paraMapPtr,
        std::unique_ptr<StyleManager>& styleManager, bool needShowPlaceholder);
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
    void HandleEmptyParagraph(RefPtr<Paragraph> paragraph, const std::list<RefPtr<SpanItem>>& spanGroup) override;
    RefPtr<SpanItem> GetParagraphStyleSpanItem(const std::list<RefPtr<SpanItem>>& spanGroup) override;
    void SetAdaptFontSizeStepToTextStyle(
        TextStyle& textStyle, const std::optional<Dimension>& adaptFontSizeStep) override
    {}
    void AddImageToParagraph(RefPtr<ImageSpanItem>& imageSpanItem, const RefPtr<LayoutWrapper>& iterItem,
        const RefPtr<Paragraph>& paragraph, int32_t& spanTextLength) override;
    void AddPlaceHolderToParagraph(RefPtr<PlaceholderSpanItem>& placeholderSpanItem,
        const RefPtr<LayoutWrapper>& layoutWrapper, const RefPtr<Paragraph>& paragraph,
        int32_t& spanTextLength) override;
    void UpdateParagraphByCustomSpan(RefPtr<CustomSpanItem>& customSpanItem, const RefPtr<Paragraph>& paragraph,
        int32_t& spanTextLength, CustomSpanPlaceholderInfo& customSpanPlaceholder) override;
    void AddSymbolSpanToParagraph(const RefPtr<SpanItem>& child, int32_t& spanTextLength,
        const RefPtr<FrameNode>& frameNode, const RefPtr<Paragraph>& paragraph) override;
    void AddTextSpanToParagraph(const RefPtr<SpanItem>& child, int32_t& spanTextLength,
        const RefPtr<FrameNode>& frameNode, const RefPtr<Paragraph>& paragraph) override;
    ChildrenListWithGuard GetAllChildrenWithBuild(LayoutWrapper* layoutWrapper) override;

private:
    void UpdateFrameSizeWithLayoutPolicy(LayoutWrapper* layoutWrapper, SizeF& frameSize);
    OffsetF GetContentOffset(LayoutWrapper* layoutWrapper) override;
    bool CreateParagraph(const TextStyle& textStyle, std::u16string content, LayoutWrapper* layoutWrapper,
        double maxWidth = 0.0) override;
    bool BuildParagraph(TextStyle& textStyle, const RefPtr<TextLayoutProperty>& layoutProperty,
        const LayoutConstraintF& contentConstraint, LayoutWrapper* layoutWrapper);
    ParagraphStyle GetEditorParagraphStyle(
        const TextStyle& textStyle, const std::u16string& content, LayoutWrapper* layoutWrapper) const;
    float GetShadowOffset(const std::list<RefPtr<SpanItem>>& group) override;
    void UpdateRichTextRect(const SizeF& textSize, LayoutWrapper* layoutWrapper);
    RefPtr<RichEditorPattern> GetRichEditorPattern(LayoutWrapper* layoutWrapper);

    bool SetPlaceholder(LayoutWrapper* layoutWrapper);

    void CopySpanStyle(RefPtr<SpanItem> source, RefPtr<SpanItem> target);
    void AppendNewLineSpan();
    std::optional<SizeF> MeasureContentSize(const LayoutConstraintF& constraint, LayoutWrapper* layoutWrapper);
    std::optional<SizeF> MeasureEmptyContentSize(const LayoutConstraintF& constraint, LayoutWrapper* layoutWrapper);
    LayoutConstraintF ReMeasureContent(
        SizeF& textSize, const LayoutConstraintF& constraint, LayoutWrapper* layoutWrapper);
    void HandleParagraphCache();
    void UpdateConstraintByLayoutPolicy(
        const SizeF& textSize, LayoutConstraintF& constraint, LayoutWrapper* layoutWrapper);
    void UpdateMaxSizeByLayoutPolicy(const LayoutConstraintF& contentConstraint, LayoutWrapper* layoutWrapper,
        SizeF& maxSize);
    void ReLayoutParagraphByLayoutPolicy(LayoutWrapper* layoutWrapper, float maxWidth);
    void ReLayoutParagraphBySpan(LayoutWrapper* layoutWrapper, std::vector<TextStyle>& textStyles,
        std::list<RefPtr<SpanItem>>& group, bool& needReLayout, bool& needReLayoutParagraph);
    std::uintptr_t Hash(const std::list<RefPtr<SpanItem>>& spanGroup);
    RefPtr<Paragraph> GetOrCreateParagraph(const std::list<RefPtr<SpanItem>>& group,
        const ParagraphStyle& paraStyle, const std::map<int32_t, AISpan>& aiSpanMap) override;
    std::string SpansToString();

    const std::list<RefPtr<SpanItem>>& GetSpans() const
    {
        return allSpans_;
    }

    std::list<RefPtr<SpanItem>> allSpans_;
    RichEditorParagraphManager* pManager_;
    OffsetF parentGlobalOffset_;
    RectF richTextRect_;
    std::optional<TextStyle> typingTextStyle_;
    LRUMap<std::uintptr_t, RefPtr<Paragraph>>* const paraMapPtr_;
    std::unique_ptr<StyleManager>& styleManager_;
    bool needShowPlaceholder_ = false;
    ACE_DISALLOW_COPY_AND_MOVE(RichEditorLayoutAlgorithm);
};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_RICH_EDITOR_RICH_EDITOR_LAYOUT_ALGORITHM_H
