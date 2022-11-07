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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_SWIPER_INDICATOR_SWIPER_INDICATOR_LAYOUT_ALGORITHM_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_SWIPER_INDICATOR_SWIPER_INDICATOR_LAYOUT_ALGORITHM_H

#include <cstdint>
#include <optional>

#include "base/geometry/axis.h"
#include "base/memory/referenced.h"
#include "core/components_ng/layout/layout_algorithm.h"
#include "core/components_ng/layout/layout_wrapper.h"

namespace OHOS::Ace::NG {

class ACE_EXPORT SwiperIndicatorLayoutAlgorithm : public LayoutAlgorithm {
    DECLARE_ACE_TYPE(SwiperIndicatorLayoutAlgorithm, LayoutAlgorithm);

public:
    SwiperIndicatorLayoutAlgorithm() = default;
    ~SwiperIndicatorLayoutAlgorithm() override = default;

    void OnReset() override {}
    void Measure(LayoutWrapper* layoutWrapper) override;
    void Layout(LayoutWrapper* layoutWrapper) override;

    void UpdateIndicatorPosition(LayoutWrapper* layoutWrapper);

    void SetSwiperWidth(double swiperWidth)
    {
        swiperWidth_ = swiperWidth;
    }

    double GetSwiperWidth() const
    {
        return swiperWidth_;
    }

    void SetSwiperHeight(double swiperHeight)
    {
        swiperHeight_ = swiperHeight;
    }

    double GetSwiperHeight() const
    {
        return swiperHeight_;
    }

private:
    double GetValidEdgeLength(double swiperLength, double indicatorLength, const Dimension& edge) const;
    double swiperWidth_ = 0.0;
    double swiperHeight_ = 0.0;
    float indicatorWidth_ = 0.0f;
    float indicatorHeight_ = 0.0f;
    double hotZoneMaxSize_ = 0.0;
    double hotZoneMinSize_ = 0.0;
    double hotZoneRealSize_ = 0.0;
};

} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_SWIPER_INDICATOR_SWIPER_INDICATOR_LAYOUT_ALGORITHM_H
