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

namespace OHOS::Ace::NG {

class ACE_EXPORT LazyColumnLayoutAlgorithm : public LayoutAlgorithm {
    DECLARE_ACE_TYPE(LazyColumnLayoutAlgorithm, LayoutAlgorithm);
public:
    LazyColumnLayoutAlgorithm(RefPtr<LazyColumnLayoutInfo> info) : layoutInfo_(info) {}

    void Measure(LayoutWrapper* layoutWrapper) override;
    void Layout(LayoutWrapper* layoutWrapper) override;

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
    void CheckRecycle();
    void CheckCacheRecycle();
    void MeasureItemsLazy(LayoutWrapper* layoutWrapper);
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

    RefPtr<LazyColumnLayoutInfo> layoutInfo_;

    int32_t totalItemCount_ = 0;
    float totalMainSize_ = 0.0f;
    bool needAllLayout_ = true;
    bool forwardLayout_ = true;
    float referencePos_ = 0.0f;
    float startPos_ = 0.0f;
    float endPos_ = 0.0f;
    float space_ = 0.0f;
    LayoutConstraintF childLayoutConstraint_;
    HorizontalAlign horizontalAlign_ = HorizontalAlign::CENTER;
    bool isRtl_ = false;

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
