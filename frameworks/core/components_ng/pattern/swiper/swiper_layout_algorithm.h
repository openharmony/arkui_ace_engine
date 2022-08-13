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

#include <map>
#include <stdint.h>

#include "base/geometry/axis.h"
#include "base/memory/referenced.h"
#include "core/components_ng/layout/layout_algorithm.h"
#include "core/components_ng/layout/layout_wrapper.h"

namespace OHOS::Ace::NG {
class PipelineContext;

class ACE_EXPORT SwiperLayoutAlgorithm : public LayoutAlgorithm {
    DECLARE_ACE_TYPE(SwiperLayoutAlgorithm, LayoutAlgorithm);

public:
    using PositionMap = std::map<int32_t, std::pair<float, float>>;

    SwiperLayoutAlgorithm(int32_t currentIndex, int32_t startIndex, int32_t endIndex) :
        currentIndex_(currentIndex), preStartIndex_(startIndex), preEndIndex_(endIndex) {}

    ~SwiperLayoutAlgorithm() override = default;

    void OnReset() override {}

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

    void Measure(LayoutWrapper* layoutWrapper) override;

    void Layout(LayoutWrapper* layoutWrapper) override;

private:
    int32_t currentIndex_ = 0;
    int32_t preStartIndex_ = 0;
    int32_t preEndIndex_ = 0;
    std::optional<int32_t> startIndex_;
    std::optional<int32_t> endIndex_;
    float currentOffset_ = 0.0f;
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_SWIPER_SWIPER_LAYOUT_ALGORITHM_H
