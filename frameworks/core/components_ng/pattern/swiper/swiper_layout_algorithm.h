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
    SwiperLayoutAlgorithm(int32_t currentIndex, int32_t startIndex, int32_t endIndex)
        : currentIndex_(currentIndex), startIndex_(startIndex), endIndex_(endIndex)
    {}
    ~SwiperLayoutAlgorithm() override = default;

    void OnReset() override {}
    void Measure(LayoutWrapper* layoutWrapper) override;
    void Layout(LayoutWrapper* layoutWrapper) override;

    void SetCurrentOffset(float offset)
    {
        currentOffset_ = offset;
    }

    float GetCurrentOffset() const
    {
        return currentOffset_;
    }

    void SetTargetIndex(std::optional<int32_t> targetIndex)
    {
        targetIndex_ = targetIndex;
    }

    void SetTotalCount(int32_t totalCount)
    {
        totalCount_ = totalCount;
    }

    void ResetTargetIndex()
    {
        targetIndex_.reset();
    }

    const std::set<int32_t>& GetItemRange()
    {
        return itemRange_;
    }

    void SetPreItemRange(const std::set<int32_t>& preItemRange)
    {
        preItemRange_ = preItemRange;
    }

    void SetIsLoop(bool isLoop)
    {
        isLoop_ = isLoop;
    }

private:
    void InitItemRange();

    bool isLoop_ = true;
    int32_t currentIndex_ = 0;
    int32_t startIndex_;
    int32_t endIndex_;
    std::optional<int32_t> targetIndex_;
    float currentOffset_ = 0.0f;
    int32_t totalCount_ = 0;
    std::set<int32_t> itemRange_;
    std::set<int32_t> preItemRange_;
    std::vector<int32_t> inActiveItems_;
};

} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_SWIPER_SWIPER_LAYOUT_ALGORITHM_H
