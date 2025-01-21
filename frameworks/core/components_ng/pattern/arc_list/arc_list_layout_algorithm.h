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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_ARC_LIST_ARC_LIST_LAYOUT_ALGORITHM_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_ARC_LIST_ARC_LIST_LAYOUT_ALGORITHM_H

#include "core/components_ng/pattern/arc_list/arc_list_position_map.h"
#include "core/components_ng/pattern/list/list_layout_algorithm.h"

namespace OHOS::Ace::NG {

class ACE_EXPORT ArcListLayoutAlgorithm : public ListLayoutAlgorithm {
    DECLARE_ACE_TYPE(ArcListLayoutAlgorithm, ListLayoutAlgorithm);

public:
    ArcListLayoutAlgorithm(int32_t headerIndex, int32_t itemStartIndex)
        : ListLayoutAlgorithm(itemStartIndex), headerIndex_(headerIndex)
    {}

    ~ArcListLayoutAlgorithm() override = default;

    struct AscendingOrder {
        bool operator()(const int& a, const int& b) const
        {
            return a < b;
        }
    };

    using CenterPos2ScaleMap = std::map<float, float, AscendingOrder>;

    void OnItemPositionAddOrUpdate(LayoutWrapper* layoutWrapper, uint32_t index);

    float GetStartHeaderPos() const
    {
        return startHeaderPos_;
    }

    void SetStartHeaderPos(float position)
    {
        startHeaderPos_ = position;
    }

    float GetHeaderOffset() const
    {
        return headerOffset_;
    }

    void SetHeaderOffset(float offset)
    {
        headerOffset_ = offset;
    }
    static float GetItemSnapSize();

protected:
    int32_t LayoutALineForward(
        LayoutWrapper* layoutWrapper, int32_t& currentIndex, float startPos, float& endPos) override;
    int32_t LayoutALineBackward(
        LayoutWrapper* layoutWrapper, int32_t& currentIndex, float endPos, float& startPos) override;
    float CalculateLaneCrossOffset(float crossSize, float childCrossSize, bool isGroup) override;
    float GetLayoutFixOffset() override;
    void UpdateSnapCenterContentOffset(LayoutWrapper* layoutWrapper) override;

private:
    void MeasureList(LayoutWrapper* layoutWrapper) override;

    void FixPredictSnapOffset(const RefPtr<ListLayoutProperty>& listLayoutProperty) override;
    void FixPredictSnapOffsetAlignCenter();

    float CalculatePredictSnapEndPositionByIndex(uint32_t index, float prevPredictEndPos);

    static float GetNearScale(float pos);
    float InitItemOffset(LayoutWrapper* layoutWrapper);
    void GenerateItemOffset(LayoutWrapper* layoutWrapper);

    void MeasureHeader(LayoutWrapper* layoutWrapper) override;
    void LayoutHeader(LayoutWrapper* layoutWrapper, const OffsetF& paddingOffset, float crossSize) override;
    void UpdateZIndex(const RefPtr<LayoutWrapper>& layoutWrapper);
    void CalcContentOffset(const RefPtr<ListLayoutProperty>& property) override
    {
        contentStartOffset_ = 0.0;
        contentEndOffset_ = 0.0;
    }
    bool IsScrollSnapAlignCenter(LayoutWrapper* layoutWrapper) override
    {
        return true;
    }
    void FixItemLayoutOffset(LayoutWrapper* layoutWrapper) override;

    int32_t headerIndex_ = -1;
    float headerMainSize_ = 0.0f;
    float startHeaderPos_ = 0.0f;
    float headerOffset_ = -1.0f;
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_ARC_LIST_ARC_LIST_LAYOUT_ALGORITHM_H
