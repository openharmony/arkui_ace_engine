/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_LIST_LIST_LAYOUT_ALGORITHM_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_LIST_LIST_LAYOUT_ALGORITHM_H

#include <map>
#include <optional>
#include <stdint.h>

#include "base/geometry/axis.h"
#include "base/memory/referenced.h"
#include "core/components_ng/layout/layout_algorithm.h"
#include "core/components_ng/layout/layout_wrapper.h"
#include "core/components_v2/list/list_component.h"

namespace OHOS::Ace::NG {
class PipelineContext;

// TextLayoutAlgorithm acts as the underlying text layout.
class ACE_EXPORT ListLayoutAlgorithm : public LayoutAlgorithm {
    DECLARE_ACE_TYPE(ListLayoutAlgorithm, LayoutAlgorithm);

public:
    using PositionMap = std::map<int32_t, std::pair<float, float>>;

    ListLayoutAlgorithm(int32_t startIndex, int32_t endIndex) : preStartIndex_(startIndex), preEndIndex_(endIndex) {}

    ~ListLayoutAlgorithm() override = default;

    void OnReset() override {}

    const PositionMap& GetItemPosition() const
    {
        return itemPosition_;
    }

    void SetIndex(int32_t index)
    {
        jumpIndex_ = index;
    }

    void SetCurrentOffset(float offset)
    {
        currentOffset_ = offset;
    }

    float GetCurrentOffset() const
    {
        return currentOffset_;
    }

    int32_t GetStartIndex() const
    {
        return startIndex_.value_or(0);
    }

    int32_t GetEndIndex() const
    {
        return endIndex_.value_or(0);
    }

    std::optional<int32_t> GetMaxListItemIndex() const
    {
        return maxListItemIndex_;
    }

    void SetSpaceWidth(float spaceWidth)
    {
        spaceWidth_ = spaceWidth;
    }

    float GetSpaceWidth() const
    {
        return spaceWidth_;
    }

    void SetIsInitialized(bool isInitialized)
    {
        isInitialized_ = isInitialized;
    }

    bool GetIsInitialized() const
    {
        return isInitialized_;
    }

    void SetLanes(int32_t lanes)
    {
        lanes_ = lanes;
    }

    std::optional<int32_t> GetLanes() const
    {
        return lanes_;
    }

    void SetPlayEdgeEffectAnimation(bool playEdgeEffectAnimation)
    {
        playEdgeEffectAnimation_ = playEdgeEffectAnimation;
    }

    bool Scrollable() const
    {
        return scrollable_;
    }

    void Measure(LayoutWrapper* layoutWrapper) override;

    void Layout(LayoutWrapper* layoutWrapper) override;

    void LayoutForward(LayoutWrapper* layoutWrapper, const LayoutConstraintF& layoutConstraint, Axis axis);
    void LayoutBackward(LayoutWrapper* layoutWrapper, const LayoutConstraintF& layoutConstraint, Axis axis);

    void LayoutForwardForLaneList(LayoutWrapper* layoutWrapper, const LayoutConstraintF& layoutConstraint, Axis axis);
    void LayoutBackwardForLaneList(LayoutWrapper* layoutWrapper, const LayoutConstraintF& layoutConstraint, Axis axis);

private:
    void LayoutListInIndexMode(LayoutWrapper* layoutWrapper, const LayoutConstraintF& layoutConstraint, Axis axis);

    void LayoutListInOffsetMode(LayoutWrapper* layoutWrapper, const LayoutConstraintF& layoutConstraint, Axis axis);

    std::pair<int32_t, float> LayoutOrRecycleCachedItems(
        LayoutWrapper* layoutWrapper, const LayoutConstraintF& layoutConstraint, Axis axis);

    std::pair<int32_t, float> RequestNewItemsForward(LayoutWrapper* layoutWrapper,
        const LayoutConstraintF& layoutConstraint, int32_t startIndex, float startPos, Axis axis);

    std::pair<int32_t, float> RequestNewItemsBackward(LayoutWrapper* layoutWrapper,
        const LayoutConstraintF& layoutConstraint, int32_t startIndex, float startPos, Axis axis);

    void CalculateLanes(const LayoutConstraintF& layoutConstraint, Axis axis);
    void ModifyLaneLength(const LayoutConstraintF& layoutConstraint, Axis axis);
    float CalculateLaneCrossOffset(float crossSize, float childCrossSize);

    void ResetScrollable();

    std::optional<int32_t> jumpIndex_;
    bool jumpIndexOutOfRange_ = false;

    PositionMap itemPosition_;
    float currentOffset_ = 0.0f;
    float startMainPos_ = 0.0f;
    float endMainPos_ = 0.0f;
    int32_t preStartIndex_ = -1;
    int32_t preEndIndex_ = -1;
    std::optional<int32_t> startIndex_;
    std::optional<int32_t> endIndex_;

    std::optional<int32_t> maxListItemIndex_;
    float spaceWidth_ = 0.0f;
    bool isInitialized_ = false;
    int32_t cachedCount_ = 0;
    int32_t startCachedCount_ = 0;
    int32_t endCachedCount_ = 0;

    std::optional<int32_t> lanes_;
    std::optional<float> minLaneLength_;
    std::optional<float> maxLaneLength_;
    V2::ListItemAlign listItemAlign_ = V2::ListItemAlign::START;

    bool playEdgeEffectAnimation_ = false;
    bool mainSizeIsDefined_ = false;
    float contentMainSize_ = 0.0f;
    float paddingBeforeContent_ = 0.0f;
    float paddingAfterContent_ = 0.0f;
    float edgeEffectOffset_ = 0.0f;

    // List is scrollable when content size is greater than list size in main axis.
    bool scrollable_ = true;
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_LIST_LIST_LAYOUT_ALGORITHM_H
