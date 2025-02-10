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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_ARC_INDEXER_LAYOUT_ALGORITHM_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_ARC_INDEXER_LAYOUT_ALGORITHM_H

#include "core/components_ng/pattern/indexer/indexer_layout_algorithm.h"

namespace OHOS::Ace::NG {

class ACE_EXPORT ArcIndexerLayoutAlgorithm : public IndexerLayoutAlgorithm {
    DECLARE_ACE_TYPE(ArcIndexerLayoutAlgorithm, IndexerLayoutAlgorithm);

public:
    ArcIndexerLayoutAlgorithm() = default;
    ~ArcIndexerLayoutAlgorithm() override = default;
    ArcIndexerLayoutAlgorithm(int32_t itemCount, int32_t fullCount) : itemCount_(itemCount), fullCount_(fullCount) {}

    float GetArcSize() const
    {
        return actualSize_;
    }

    OffsetF GetArcCenter() const
    {
        return arcCenter_;
    }

    float GetStartAngle() const
    {
        return startAngle_;
    }

    float GetSweepAngle() const
    {
        return sweepAngle_;
    }

    float GetArcRadius() const
    {
        return arcRadius_;
    }

    float GetstepAngle() const
    {
        return stepAngle_;
    }

    float GetitemRadius() const
    {
        return itemRadius_;
    }

    void Measure(LayoutWrapper* layoutWrapper) override;

    void Layout(LayoutWrapper* layoutWrapper) override;

private:
    OffsetT<Dimension> GetPositionOfPopupNode(LayoutWrapper* layoutWrapper);
    OffsetT<Dimension> CalcArcItemPosition(LayoutWrapper* layoutWrapper, int32_t index);
    void MeasurePopup(LayoutWrapper* layoutWrapper, uint32_t childCount);
    void MeasureArc(LayoutWrapper* layoutWrapper);
    int32_t itemCount_ = 0;
    float itemSize_ = 0.0f;
    int32_t fullCount_ = 0;
    float actualSize_ = 0.0f;
    OffsetF arcCenter_;
    float startAngle_ = 0.0f;
    float sweepAngle_ = 0.0f;
    float arcRadius_ = 0.0f;
    float stepAngle_ = 13.5f;
    float itemRadius_ = 0.0f;
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_ARC_INDEXER_LAYOUT_ALGORITHM_H
