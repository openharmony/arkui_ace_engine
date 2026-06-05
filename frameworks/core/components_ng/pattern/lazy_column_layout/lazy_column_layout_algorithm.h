/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_LAZY_COLUMN_LAYOUT_LAZY_COLUMN_LAYOUT_ALGORITHM_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_LAZY_COLUMN_LAYOUT_LAZY_COLUMN_LAYOUT_ALGORITHM_H

#include <optional>

#include "core/components_ng/layout/layout_algorithm.h"
#include "core/components_ng/layout/layout_wrapper.h"
#include "core/components_ng/pattern/lazy_column_layout/lazy_column_layout_info.h"
#include "core/components_ng/pattern/lazy_column_layout/lazy_column_layout_property.h"
#include "core/components_ng/pattern/lazy_layout/header_footer_utils.h"

namespace OHOS::Ace::NG {

class ACE_EXPORT LazyColumnLayoutAlgorithm : public LayoutAlgorithm {
    DECLARE_ACE_TYPE(LazyColumnLayoutAlgorithm, LayoutAlgorithm);
public:
    LazyColumnLayoutAlgorithm(RefPtr<LazyColumnLayoutInfo> info) : layoutInfo_(info) {}

    void Measure(LayoutWrapper* layoutWrapper) override;
    void Layout(LayoutWrapper* layoutWrapper) override;

    // Inject the header FrameNode (optional). Pattern calls it once in CreateLayoutAlgorithm.
    void SetHeader(const RefPtr<FrameNode>& header)
    {
        header_ = header;
    }

    // Inject the footer FrameNode (optional). Pattern calls it once in CreateLayoutAlgorithm.
    void SetFooter(const RefPtr<FrameNode>& footer)
    {
        footer_ = footer;
    }

    int32_t GetTotalItemCount() const
    {
        return totalItemCount_;
    }

private:
    void UpdatePosReference(LayoutWrapper* layoutWrapper, std::optional<ViewPosReference>& posRef);
    void UpdateAttribute(const RefPtr<LazyColumnLayoutProperty>& layoutProperty,
        const LayoutConstraintF& contentConstraint);
    void UpdateChildConstraint(const RefPtr<LazyColumnLayoutProperty>& layoutProperty,
        const OptionalSizeF& contentIdealSize);
    bool CheckNeedMeasure(const RefPtr<LayoutWrapper>& layoutWrapper) const;
    void MeasureAllItems(LayoutWrapper* layoutWrapper);
    void GetStartIndexInfo(int32_t& index, float& pos);
    void GetEndIndexInfo(int32_t& index, float& pos);
    bool NeedLazyLayout(const RefPtr<LayoutWrapper>& childWrapper);
    LayoutConstraintF GetLazyLayoutConstraint(float referencePos, bool forwardLayout);
    AdjustOffset GetAdjustOffset(const RefPtr<LayoutWrapper>& item);
    void ApplyLazyNodeAdjustOffset(const RefPtr<LayoutWrapper>& wrapper, float& referencePos, bool forward);
    void MeasureForward(LayoutWrapper* layoutWrapper, int32_t startIndex, float startPos);
    void MeasureBackward(LayoutWrapper* layoutWrapper, int32_t endIndex, float endPos);
    bool MeasureItem(LayoutWrapper* layoutWrapper, int32_t curIndex, float currentPos, bool forward, float& mainSize);
    void CheckRecycle();
    void CalculateVisibleStartIndex();
    void CalculateVisibleEndIndex();
    void CheckCacheRecycle();
    void MeasureItemsLazy(LayoutWrapper* layoutWrapper);
    // Measure the header (if mounted) and update layoutInfo_->headerMainSize_.
    void MeasureHeader(LayoutWrapper* layoutWrapper);
    // Measure the footer (if mounted) and update layoutInfo_->footerMainSize_.
    void MeasureFooter(LayoutWrapper* layoutWrapper);
    // Compose the insets forwarded to child sections: this column's received inset plus its own sticky
    // header/footer size. Updates childStickyTopInset_ / childStickyBottomInset_.
    void ComposeChildStickyInsets(LayoutWrapper* layoutWrapper);
    void SetFrameSize(LayoutWrapper* layoutWrapper, OptionalSizeF& contentIdealSize);

    void LayoutItems(LayoutWrapper* layoutWrapper, float crossSize, const OffsetF& paddingOffset);
    void SetItemOffset(const RefPtr<LayoutWrapper>& wrapper, const ColumnItemMainPos& pos,
        float crossSize, const OffsetF& paddingOffset);
    void SyncGeometry(const RefPtr<LayoutWrapper>& wrapper);
    void LayoutCachedItems(LayoutWrapper* layoutWrapper, float crossSize, const OffsetF& paddingOffset);
    void LayoutCachedItemsForward(LayoutWrapper* layoutWrapper, float crossSize, const OffsetF& paddingOffset);
    void LayoutCachedItemsBackward(LayoutWrapper* layoutWrapper, float crossSize, const OffsetF& paddingOffset);
    void PredictLayoutForward(LayoutWrapper* layoutWrapper, float crossSize, const OffsetF& paddingOffset);
    void PredictLayoutBackward(LayoutWrapper* layoutWrapper, float crossSize, const OffsetF& paddingOffset);
    void FixIndexRange(int32_t& startIndex, int32_t& endIndex);
    void SyncPredictLayoutInfo(LayoutWrapper* layoutWrapper);
    float CalculateCrossOffset(float crossSize, float childCrossSize) const;

    // Resolve the raw indices of header / footer in the child sequence into headerIndex_ / footerIndex_.
    void UpdateHeaderFooterIndexes(LayoutWrapper* layoutWrapper);
    // item index -> raw index: shift by +1 when a header is present.
    int32_t GetRawIndexForItem(int32_t itemIndex) const;
    // Subtract header / footer from the total child count and return the current content item count.
    int32_t CalculateItemCount(LayoutWrapper* layoutWrapper) const;
    // Resolve the active sticky style (NONE / HEADER / FOOTER / BOTH) by reading from LayoutProperty.
    StickyStyle ResolveStickyStyle(LayoutWrapper* layoutWrapper) const;
    // Generic header / footer layout; isSticky reports whether this edge currently participates in sticky
    // layering, in which case its z-index is raised to the sticky default.
    void LayoutHeaderFooter(LayoutWrapper* layoutWrapper, int32_t rawIndex, const OffsetF& offset,
        float crossSize, bool isSticky) const;
    // Compute the header's sticky main-axis position then delegate to LayoutHeaderFooter.
    void LayoutHeader(LayoutWrapper* layoutWrapper, float crossSize, const OffsetF& paddingOffset,
        StickyStyle stickyStyle, float stickyHeaderPos) const;
    // Compute the footer's sticky main-axis position then delegate to LayoutHeaderFooter.
    void LayoutFooter(LayoutWrapper* layoutWrapper, float crossSize, const OffsetF& paddingOffset,
        StickyStyle stickyStyle, float stickyFooterPos) const;
    // Explicitly mark header / footer as active so they are not collected by ActiveChildRange filtering.
    void SetHeaderFooterActive(LayoutWrapper* layoutWrapper) const;

    RefPtr<LazyColumnLayoutInfo> layoutInfo_;

    int32_t totalItemCount_ = 0;
    float totalMainSize_ = 0.0f;
    bool needAllLayout_ = true;
    bool forwardLayout_ = true;
    float referencePos_ = 0.0f;
    float startPos_ = 0.0f;
    float endPos_ = 0.0f;
    float viewExtStart_ = 0.0f;
    float viewExtEnd_ = 0.0f;
    // Parent-reserved insets for this column's own header/footer; childSticky*Inset_ = these + own sticky
    // edge size, passed down to nested lazy children.
    float stickyTopInset_ = 0.0f;
    float stickyBottomInset_ = 0.0f;
    float childStickyTopInset_ = 0.0f;
    float childStickyBottomInset_ = 0.0f;
    float space_ = 0.0f;
    LayoutConstraintF childLayoutConstraint_;
    // Constraint used when measuring header / footer; full cross size, infinite main.
    LayoutConstraintF edgeLayoutConstraint_;
    HorizontalAlign horizontalAlign_ = HorizontalAlign::CENTER;
    bool isRtl_ = false;

    // Header / footer FrameNode weak refs to avoid retain cycles.
    WeakPtr<FrameNode> header_;
    WeakPtr<FrameNode> footer_;
    // Raw indices of header / footer in the child sequence; -1 means not mounted.
    // Raw host-child index of the mounted header / footer (-1 when absent). These live only in raw space —
    // header and footer are not content items and have no item-space counterpart.
    int32_t headerIndex_ = -1;
    int32_t footerIndex_ = -1;

    // cache
    float cacheSize_ = 0.5f; // preload half-screen content above and below viewport
    float layoutedStart_ = 0.0f;
    float layoutedEnd_ = 0.0f;
    int32_t layoutedStartIndex_ = -1;
    int32_t layoutedEndIndex_ = -1;
    float cacheStartPos_ = 0.0f;
    float cacheEndPos_ = 0.0f;
    int32_t cachedStartIndex_ = -1;
    int32_t cachedEndIndex_ = -1;
};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_LAZY_COLUMN_LAYOUT_LAZY_COLUMN_LAYOUT_ALGORITHM_H
