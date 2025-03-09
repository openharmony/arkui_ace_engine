/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_SCROLL_VIEW_GRID_LAZY_LAYOUT_ALGORITHM_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_SCROLL_VIEW_GRID_LAZY_LAYOUT_ALGORITHM_H

#include <optional>
#include "base/geometry/axis.h"
#include "core/components_ng/layout/layout_algorithm.h"
#include "core/components_ng/layout/layout_wrapper.h"
#include "core/components_ng/pattern/lazy_layout/grid_layout/lazy_grid_layout_info.h"
#include "core/components_ng/pattern/lazy_layout/grid_layout/lazy_grid_layout_property.h"

namespace OHOS::Ace::NG {

// TextLayoutAlgorithm acts as the underlying text layout.
class ACE_EXPORT LazyGridLayoutAlgorithm : public LayoutAlgorithm {
    DECLARE_ACE_TYPE(LazyGridLayoutAlgorithm, LayoutAlgorithm);
public:
    LazyGridLayoutAlgorithm(RefPtr<LazyGridLayoutInfo> info) : layoutInfo_(info) {}

    void Measure(LayoutWrapper* layoutWrapper) override;
    void Layout(LayoutWrapper* layoutWrapper) override;

    float GetSpaceWidth() const
    {
        return spaceWidth_;
    }

    Axis GetAxis() const
    {
        return axis_;
    }

    void SetAxis(Axis axis)
    {
        axis_ = axis;
    }

    int32_t GetTotalItemCount() const
    {
        return totalItemCount_;
    }

    void SetRefencesPos(float startPos, float endPos, float referencePos, bool forwardLayout)
    {
        viewStart_ = startPos;
        viewEndPos_ = endPos;
        referencePos_ = referencePos;
        forwardLayout_ = forwardLayout;
        needAllLayout_ = false;
    }

private:
    void SetFrameSize(LayoutWrapper* layoutWrapper, OptionalSizeF& contentIdealSize, const PaddingPropertyF& padding);
    bool CheckNeedMeasure(const RefPtr<LayoutWrapper>& layoutWrapper, int32_t laneIdx) const;
    void UpdateGridItemConstraint(const OptionalSizeF& selfIdealSize, LayoutConstraintF& contentConstraint);
    void UpdateGap(const RefPtr<LazyGridLayoutProperty>& layoutProperty, const OptionalSizeF& selfIdealSize);
    void UpdateReferencePos(LayoutWrapper* layoutWrapper, const std::optional<ViewPosReference>& posRef);
    void MeasureGridItemAll(LayoutWrapper* layoutWrapper);
    void MeasureGridItemLazy(LayoutWrapper* layoutWrapper);
    void GetStartIndexInfo(int32_t& index, float& pos);
    void GetEndIndexInfo(int32_t& index, float& pos);
    void CheckRecycle();
    void MeasureForward(LayoutWrapper* layoutWrapper, int32_t startIndex, float startPos);
    void MeasureBackward(LayoutWrapper* layoutWrapper, int32_t endIndex, float endPos);
    void LayoutGridItems(LayoutWrapper* layoutWrapper, float crossSize, const OffsetF& paddingOffset);
    void SetItemOffset(RefPtr<LayoutWrapper>& wrapper, const GridItemMainPos& pos,
        float crossSize, const OffsetF& paddingOffset);
    void SyncGeometry(RefPtr<LayoutWrapper>& wrapper);
    // cached
    void LayoutCachedItems(LayoutWrapper* layoutWrapper, float crossSize, const OffsetF& paddingOffset);
    void LayoutCachedItemsForward(LayoutWrapper* layoutWrapper, float crossSize, const OffsetF& paddingOffset);
    void LayoutCachedItemsBackward(LayoutWrapper* layoutWrapper, float crossSize, const OffsetF& paddingOffset);
    void PredictLayoutForward(LayoutWrapper* layoutWrapper, float crossSize, const OffsetF& paddingOffset);
    void PredictLayoutBackward(LayoutWrapper* layoutWrapper, float crossSize, const OffsetF& paddingOffset);
    void FixPosMapBackward(int32_t index);
    void FixPosMapForward(int32_t index, LayoutWrapper* layoutWrapper, float crossSize, const OffsetF& paddingOffset);

private:
    Axis axis_ = Axis::VERTICAL;
    TextDirection layoutDirection_ = TextDirection::LTR;
    int32_t totalItemCount_ = 0;
    float spaceWidth_ = 0.0f;
    float laneGutter_ = 0.0f;
    float crossSize_ = 0.0f;
    std::vector<double> crossLens_;
    std::vector<double> crossPos_;
    float totalMainSize_ = 0.0f;
    float realMainSize_ = 0.0f;
    bool needAllLayout_ = true;
    int32_t lanes_ = 1;

    float viewStart_ = 0.0f;
    float viewEndPos_ = 0.0f;
    float referencePos_ = 0.0f;
    bool forwardLayout_ = true;
    float startPos_ = 0.0;
    float endPos_ = 0.0f;

    // cache
    float cacheSize_ = 0.5f;
    float layoutedStart_ = 0.0f;
    float layoutedEnd_ = 0.0f;
    int32_t layoutedStartIndex_ = -1;
    int32_t layoutedEndIndex_ = -1;
    float cacheStartPos_ = 0.0f;
    float cacheEndPos_ = 0.0f;
    int32_t cachedStartIndex_ = -1;
    int32_t cachedEndIndex_ = -1;

    std::vector<LayoutConstraintF> childLayoutConstraints_;
    RefPtr<LazyGridLayoutInfo> layoutInfo_;
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_SCROLL_VIEW_GRID_LAZY_LAYOUT_ALGORITHM_H
