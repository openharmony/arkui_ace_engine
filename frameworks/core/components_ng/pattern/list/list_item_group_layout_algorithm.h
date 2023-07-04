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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_LIST_LIST_ITEM_GROUP_LAYOUT_ALGORITHM_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_LIST_LIST_ITEM_GROUP_LAYOUT_ALGORITHM_H

#include <optional>
#include "base/geometry/axis.h"
#include "core/components_ng/layout/layout_algorithm.h"
#include "core/components_ng/layout/layout_wrapper.h"
#include "core/components_ng/pattern/list/list_layout_property.h"
#include "core/components_v2/list/list_properties.h"

namespace OHOS::Ace::NG {

// TextLayoutAlgorithm acts as the underlying text layout.
class ACE_EXPORT ListItemGroupLayoutAlgorithm : public LayoutAlgorithm {
    DECLARE_ACE_TYPE(ListItemGroupLayoutAlgorithm, LayoutAlgorithm);
public:
    using PositionMap = std::map<int32_t, std::pair<float, float>>;

    static const int32_t LAST_ITEM = -1;
    
    ListItemGroupLayoutAlgorithm(int32_t headerIndex, int32_t footerIndex, int32_t itemStartIndex)
        :headerIndex_(headerIndex), footerIndex_(footerIndex), itemStartIndex_(itemStartIndex) {}

    void Measure(LayoutWrapper* layoutWrapper) override;

    void Layout(LayoutWrapper* layoutWrapper) override;

    const PositionMap& GetItemPosition() const
    {
        return itemPosition_;
    }

    void SetItemsPosition(const PositionMap& itemPosition)
    {
        itemPosition_ = itemPosition;
    }

    float GetSpaceWidth() const
    {
        return spaceWidth_;
    }

    Axis GetAxis() const
    {
        return axis_;
    }

    int32_t GetLanes() const
    {
        return lanes_;
    }

    float GetLaneGutter() const
    {
        return laneGutter_;
    }

    float GetChildCrossSize() const
    {
        return childCrossSize_;
    }

    int32_t GetLanesFloor(int32_t index) const
    {
        if (lanes_ <= 1) {
            return index;
        }
        return index - index % lanes_;
    }

    void SetListMainSize(float startPos, float endPos, float referencePos, bool forwardLayout)
    {
        startPos_ = startPos;
        endPos_ = endPos;
        referencePos_ = referencePos;
        forwardLayout_ = forwardLayout;
    }

    void SetListLayoutProperty(RefPtr<ListLayoutProperty> layoutProperty)
    {
        listLayoutProperty_ = std::move(layoutProperty);
    }

    void SetJumpIndex(int32_t index)
    {
        jumpIndex_ = index;
    }

    void SetTargetIndex(int32_t index)
    {
        targetIndex_ = index;
    }

    int32_t GetStartIndex() const
    {
        return itemPosition_.empty() ? 0 : itemPosition_.begin()->first;
    }

    int32_t GetEndIndex() const
    {
        return itemPosition_.empty() ? 0 : itemPosition_.rbegin()->first;
    }

    float GetStartPosition() const
    {
        if (itemPosition_.empty()) {
            return 0.0f;
        }
        if (GetStartIndex() == 0) {
            return itemPosition_.begin()->second.first;
        }
        return itemPosition_.begin()->second.first - spaceWidth_;
    }

    float GetEndPosition() const
    {
        if (itemPosition_.empty()) {
            return 0.0f;
        }
        if (GetEndIndex() == totalItemCount_ - 1) {
            return itemPosition_.rbegin()->second.second;
        }
        return itemPosition_.rbegin()->second.second + spaceWidth_;
    }

    int32_t GetTotalItemCount() const
    {
        return totalItemCount_;
    }

    float GetChildMaxCrossSize(LayoutWrapper* layoutWrapper, Axis axis);

    void CheckRecycle(const RefPtr<LayoutWrapper>& layoutWrapper, float startPos, float endPos, float referencePos,
        bool forwardLayout);

    void SetNeedAllLayout()
    {
        needAllLayout_ = true;
    }
private:
    float CalculateLaneCrossOffset(float crossSize, float childCrossSize);
    void UpdateListItemConstraint(const OptionalSizeF& selfIdealSize, LayoutConstraintF& contentConstraint);
    void LayoutListItem(LayoutWrapper* layoutWrapper, const OffsetF& paddingOffset, float crossSize);
    void LayoutListItemAll(LayoutWrapper* layoutWrapper, const LayoutConstraintF& layoutConstraint, float startPos);
    void LayoutHeaderFooter(LayoutWrapper* layoutWrapper, const OffsetF& paddingOffset, float crossSize);
    void LayoutIndex(const RefPtr<LayoutWrapper>& wrapper, const OffsetF& paddingOffset,
        float crossSize, float startPos);
    inline RefPtr<LayoutWrapper> GetListItem(LayoutWrapper* layoutWrapper, int32_t index) const
    {
        return layoutWrapper->GetOrCreateChildByIndex(index + itemStartIndex_);
    }
    void CalculateLanes(const RefPtr<ListLayoutProperty>& layoutProperty,
        const LayoutConstraintF& layoutConstraint, std::optional<float> crossSizeOptional, Axis axis);

    void MeasureListItem(LayoutWrapper* layoutWrapper, const LayoutConstraintF& layoutConstraint);
    int32_t MeasureALineForward(LayoutWrapper* layoutWrapper, const LayoutConstraintF& layoutConstraint,
        int32_t& currentIndex, float startPos, float& endPos);
    int32_t MeasureALineBackward(LayoutWrapper* layoutWrapper, const LayoutConstraintF& layoutConstraint,
        int32_t& currentIndex, float endPos, float& startPos);
    void MeasureForward(
        LayoutWrapper* layoutWrapper, const LayoutConstraintF& layoutConstraint, int32_t startIndex, float startPos);
    void MeasureBackward(
        LayoutWrapper* layoutWrapper, const LayoutConstraintF& layoutConstraint, int32_t endIndex, float endPos);
    void UpdateReferencePos(RefPtr<LayoutProperty> layoutProperty);
    bool NeedMeasureItem() const;
    static void SetListItemIndex(const LayoutWrapper* groupLayoutWrapper,
        const RefPtr<LayoutWrapper>& itemLayoutWrapper, int32_t indexInGroup);
    bool IsCardStyleForListItemGroup(const LayoutWrapper* groupLayoutWrapper);
    float GetListItemGroupMaxWidth(const OptionalSizeF& parentIdealSize, RefPtr<LayoutProperty> layoutProperty);

    bool isCardStyle_ = false;
    int32_t headerIndex_;
    int32_t footerIndex_;
    int32_t itemStartIndex_;
    RefPtr<ListLayoutProperty> listLayoutProperty_;

    PositionMap itemPosition_;
    Axis axis_ = Axis::VERTICAL;
    int32_t lanes_ = 1;
    float laneGutter_ = 0.0f;
    float childCrossSize_ = 0.0f;
    std::optional<float> minLaneLength_;
    std::optional<float> maxLaneLength_;
    V2::ListItemAlign itemAlign_ = V2::ListItemAlign::START;
    float spaceWidth_ = 0.0f;

    std::optional<int32_t> jumpIndex_;
    std::optional<int32_t> targetIndex_;
    int32_t totalItemCount_ = 0;
    float totalMainSize_ = 0.0f;
    float headerMainSize_ = 0.0f;
    float footerMainSize_ = 0.0f;
    float startPos_ = 0.0f;
    float prevStartPos_ = 0.0f;
    float prevEndPos_ = 0.0f;
    float endPos_ = 0.0f;
    float referencePos_ = 0.0f;
    bool forwardLayout_ = true;
    bool needAllLayout_ = false;
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_LIST_LIST_LAYOUT_ALGORITHM_H
