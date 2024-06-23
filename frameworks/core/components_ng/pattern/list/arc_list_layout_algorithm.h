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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_LIST_ARC_LIST_LAYOUT_ALGORITHM_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_LIST_ARC_LIST_LAYOUT_ALGORITHM_H

#include "core/components_ng/pattern/list/arc_list_position_map.h"
#include "core/components_ng/pattern/list/list_layout_algorithm.h"

namespace OHOS::Ace::NG {

namespace {
constexpr float ARC_LIST_ITEM_SNAP_SIZE = 72.5f;
constexpr float ARC_LIST_ITEM_MOVE_THRESHOLD_RATIO = 0.4f;
constexpr float ARC_LIST_MAIN_POS_OFFSET = 200.f;
} // namespace

class ACE_EXPORT ArcListLayoutAlgorithm : public ListLayoutAlgorithm {
    DECLARE_ACE_TYPE(ArcListLayoutAlgorithm, ListLayoutAlgorithm);

public:
    ArcListLayoutAlgorithm(int32_t headerIndex, int32_t itemStartIndex)
        : ListLayoutAlgorithm(itemStartIndex, ListType::ARC_LIST), headerIndex_(headerIndex)
    {}

    ~ArcListLayoutAlgorithm() override = default;

    struct AscendingOrder {
        bool operator()(const int& a, const int& b) const
        {
            return a < b;
        }
    };

    using CenterPos2ScaleMap = std::map<float, float, AscendingOrder>;

    void Measure(LayoutWrapper* layoutWrapper) override;

    void Layout(LayoutWrapper* layoutWrapper) override;

    void OnItemPositionAddOrUpdate(LayoutWrapper* layoutWrapper, uint32_t index);

    float GetStartHeaderPos() const
    {
        return startHeaderPos_;
    }

    void SetStartHeaderPos(float position)
    {
        startHeaderPos_ = position;
    }

protected:
    virtual int32_t LayoutALineForward(
        LayoutWrapper* layoutWrapper, int32_t& currentIndex, float startPos, float& endPos) override;
    virtual int32_t LayoutALineBackward(
        LayoutWrapper* layoutWrapper, int32_t& currentIndex, float endPos, float& startPos) override;
    virtual float CalculateLaneCrossOffset(float crossSize, float childCrossSize) override;
    virtual float GetLayoutFixOffset() override
    {
        return ARC_LIST_MAIN_POS_OFFSET;
    }

private:
    void MeasureList(LayoutWrapper* layoutWrapper);

    void FixPredictSnapOffset(const RefPtr<ListLayoutProperty>& listLayoutProperty);
    void FixPredictSnapOffsetAlignCenter();

    float CalculatePredictSnapEndPositionByIndex(uint32_t index, float prevPredictEndPos);

    static float GetLerpValue(const float a, const float b, const float t)
    {
        return a + t * (b - a);
    }
    static float GetNearScale(const float pos);
    void GenerateItemOffset(LayoutWrapper* layoutWrapper);

    static void LayoutConstraintApplyScale(LayoutConstraintF& layoutConstraint, float scale)
    {
        layoutConstraint.minSize.ApplyScale(scale);
        layoutConstraint.maxSize.ApplyScale(scale);
        layoutConstraint.percentReference.ApplyScale(scale);
        layoutConstraint.parentIdealSize.ApplyScale(scale);
        layoutConstraint.selfIdealSize.ApplyScale(scale);
    }

    void MeasureHeader(LayoutWrapper* layoutWrapper);
    void SetActiveChildRange(LayoutWrapper* layoutWrapper);
    void LayoutHeader(LayoutWrapper* layoutWrapper, const OffsetF& paddingOffset, float crossSize);
    void UpdateZIndex(const RefPtr<LayoutWrapper>& layoutWrapper);

    static CenterPos2ScaleMap centerPos2ScaleMap_;
    int32_t headerIndex_ = -1;
    float headerMainSize_ = 0.0f;
    float startHeaderPos_ = 0.0f;
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_LIST_ARC_LIST_LAYOUT_ALGORITHM_H
