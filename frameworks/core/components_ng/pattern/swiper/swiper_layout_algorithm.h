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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_SWIPER_SWIPER_LAYOUT_ALGORITHM_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_SWIPER_SWIPER_LAYOUT_ALGORITHM_H

#include <cstdint>
#include <optional>

#include "base/geometry/axis.h"
#include "base/memory/referenced.h"
#include "core/components_ng/layout/layout_algorithm.h"
#include "core/components_ng/layout/layout_wrapper.h"

namespace OHOS::Ace::NG {

class ACE_EXPORT SwiperLayoutAlgorithm : public LayoutAlgorithm {
    DECLARE_ACE_TYPE(SwiperLayoutAlgorithm, LayoutAlgorithm);

public:
    SwiperLayoutAlgorithm() = default;
    ~SwiperLayoutAlgorithm() override = default;

    void OnReset() override {}
    void Measure(LayoutWrapper* layoutWrapper) override;
    void Layout(LayoutWrapper* layoutWrapper) override;

    const std::set<int32_t>& GetItemRange()
    {
        return itemRange_;
    }

    void SetMaxChildSize(const SizeF& maxChildSize)
    {
        maxChildSize_ = maxChildSize;
    }

    void SetItemRange(const std::set<int32_t>& itemRange)
    {
        itemRange_ = itemRange;
    }

    void SetIsLoop(bool isLoop)
    {
        isLoop_ = isLoop;
    }

    void SetCurrentOffsetTimes(float currentOffsetTimes)
    {
        currentOffsetTimes_ = currentOffsetTimes;
    }

    void SetTotalCount(int32_t totalCount)
    {
        totalCount_ = totalCount;
    }

    void SetDisplayCount(int32_t displayCount)
    {
        displayCount_ = displayCount;
    }

    SizeF GetMaxChildSize() const
    {
        return maxChildSize_;
    }

    void SetOnlyNeedMeasurePages(bool onlyNeedMeasurePages)
    {
        onlyNeedMeasurePages_ = onlyNeedMeasurePages;
    }

    bool GetOnlyNeedMeasurePages() const
    {
        return onlyNeedMeasurePages_;
    }

    void SetHoverRatio(float hoverRatio)
    {
        hoverRatio_ = hoverRatio;
    }
private:
    void MeasureAllPagesToGetMaxChildSize(LayoutWrapper* layoutWrapper, LayoutConstraintF childLayoutConstraint);
    void MeasurePages(LayoutWrapper* layoutWrapper, LayoutConstraintF childLayoutConstraint);
    void MeasureIndicator(LayoutWrapper* layoutWrapper, LayoutConstraintF childLayoutConstraint);

    float GetPagesOffsetTimes(int32_t index) const;
    bool IsVisiblePages(int32_t index) const;

    void PlaceDigitChild(const RefPtr<LayoutWrapper>& indicatorWrapper, const RefPtr<LayoutProperty>& layoutProperty);
    double GetValidEdgeLength(float swiperLength, float indicatorLength, const Dimension& edge);
    RefPtr<LayoutWrapper> GetNodeLayoutWrapperByTag(LayoutWrapper* layoutWrapper, const std::string& tagName) const;
    void MeasureArrow(LayoutWrapper* layoutWrapper, LayoutConstraintF childLayoutConstraint) const;
    void ArrowLayout(LayoutWrapper* layoutWrapper, const RefPtr<LayoutWrapper>& arrowWrapper) const;

    std::set<int32_t> itemRange_;
    bool isLoop_ = true;
    float currentOffsetTimes_ = 0;
    int32_t totalCount_ = 0;
    int32_t displayCount_ = 0;
    // Arrow default hover ratio
    float hoverRatio_ = 1.0f;

    SizeF maxChildSize_ { 0, 0 };
    bool onlyNeedMeasurePages_ = false;
};

} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_SWIPER_SWIPER_LAYOUT_ALGORITHM_H
