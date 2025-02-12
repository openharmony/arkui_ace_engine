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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_LIST_LIST_LANES_LAYOUT_ALGORITHM_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_LIST_LIST_LANES_LAYOUT_ALGORITHM_H

#include "core/components_ng/pattern/list/list_layout_algorithm.h"

namespace OHOS::Ace::NG {

// TextLayoutAlgorithm acts as the underlying text layout.
class ACE_EXPORT ListLanesLayoutAlgorithm : public ListLayoutAlgorithm {
    DECLARE_ACE_TYPE(ListLanesLayoutAlgorithm, ListLayoutAlgorithm);
public:
    void SwapLanesItemRange(std::map<int32_t, int32_t>& itemRange)
    {
        lanesItemRange_.swap(itemRange);
    }
    void SetLanes(int32_t lanes)
    {
        lanes_ = lanes;
    }
    int32_t GetLanes() const override
    {
        return lanes_;
    }

    float MeasureAndGetChildHeight(LayoutWrapper* layoutWrapper, int32_t childIndex,
        bool groupLayoutAll = true) override;

    float GetChildHeight(LayoutWrapper* layoutWrapper, int32_t childIndex) override;

    static int32_t CalculateLanesParam(std::optional<float>& minLaneLength, std::optional<float>& maxLaneLength,
        int32_t lanes, std::optional<float> crossSizeOptional, float laneGutter = 0.0f);

    const LayoutConstraintF& GetGroupLayoutConstraint() const override
    {
        return groupLayoutConstraint_;
    }

protected:
    void UpdateListItemConstraint(Axis axis, const OptionalSizeF& selfIdealSize,
        LayoutConstraintF& contentConstraint) override;
    int32_t LayoutALineForward(
        LayoutWrapper* layoutWrapper, int32_t& currentIndex, float startPos, float& endPos) override;
    int32_t LayoutALineBackward(
        LayoutWrapper* layoutWrapper, int32_t& currentIndex, float endPos, float& startPos) override;
    float CalculateLaneCrossOffset(float crossSize, float childCrossSize, bool isGroup) override;
    void CalculateLanes(const RefPtr<ListLayoutProperty>& layoutProperty,
        const LayoutConstraintF& layoutConstraint, std::optional<float> crossSizeOptional, Axis axis) override;
    int32_t GetLanesFloor(LayoutWrapper* layoutWrapper, int32_t index) override;
    int32_t GetLanesCeil(LayoutWrapper* layoutWrapper, int32_t index) override;
    void SetCacheCount(LayoutWrapper* layoutWrapper, int32_t cacheCount) override;

private:
    static void ModifyLaneLength(
        std::optional<float>& minLaneLength, std::optional<float>& maxLaneLength, float crossSize);
    int32_t FindLanesStartIndex(LayoutWrapper* layoutWrapper, int32_t index);
    bool CheckCurRowMeasureFinished(LayoutWrapper* layoutWrapper, int32_t curIndex, bool isGroup);
    std::list<int32_t> LayoutCachedItem(LayoutWrapper* layoutWrapper, int32_t cacheCount) override;
    std::list<int32_t> LayoutCachedALineForward(
        LayoutWrapper* layoutWrapper, int32_t& index, float& startPos, float crossSize);
    std::list<int32_t> LayoutCachedALineBackward(
        LayoutWrapper* layoutWrapper, int32_t& index, float& endPos, float crossSize);
    void LayoutCachedALine(LayoutWrapper* layoutWrapper, std::pair<const int, ListItemInfo>& pos,
        int32_t startIndex, float crossSize);
    std::pair<bool, bool> CheckACachedItem(const RefPtr<LayoutWrapper>& wrapper, int32_t cnt, bool& isGroup) const;
    int32_t LayoutCachedForward(LayoutWrapper* layoutWrapper, int32_t cacheCount,
        int32_t& cachedCount, int32_t curIndex, std::list<PredictLayoutItem>& predictList, bool show) override;
    int32_t LayoutCachedBackward(LayoutWrapper* layoutWrapper, int32_t cacheCount,
        int32_t& cachedCount, int32_t curIndex, std::list<PredictLayoutItem>& predictList, bool show) override;
    static int32_t FindLanesStartIndex(LayoutWrapper* layoutWrapper, int32_t startIndex, int32_t index);
    static int32_t GetLazyForEachIndex(const RefPtr<FrameNode>& host);
    void MeasureGroup(LayoutWrapper* listWrapper, const RefPtr<LayoutWrapper>& groupWrapper,
        int32_t index, float& pos, bool forward);
    void MeasureItem(const RefPtr<LayoutWrapper>& itemWrapper, int32_t index, bool forward);
    void SetLaneIdx4Divider(int32_t idx)
    {
        laneIdx4Divider_ = idx;
    }

    int32_t lanes_ = 1;
    std::optional<float> minLaneLength_;
    std::optional<float> maxLaneLength_;
    std::map<int32_t, int32_t> lanesItemRange_;

    LayoutConstraintF groupLayoutConstraint_;
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_LIST_LIST_LAYOUT_ALGORITHM_H