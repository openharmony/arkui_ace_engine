/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_SWIPER_INDICATOR_DIGIT_INDICATOR_LAYOUT_ALGORITHM_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_SWIPER_INDICATOR_DIGIT_INDICATOR_LAYOUT_ALGORITHM_H

#include <cstdint>
#include <optional>

#include "base/geometry/axis.h"
#include "base/memory/referenced.h"
#include "core/components_ng/layout/layout_algorithm.h"
#include "core/components_ng/layout/layout_wrapper.h"

namespace OHOS::Ace::NG {
class ACE_EXPORT DigitIndicatorLayoutAlgorithm : public LayoutAlgorithm {
    DECLARE_ACE_TYPE(DigitIndicatorLayoutAlgorithm, LayoutAlgorithm);

public:
    DigitIndicatorLayoutAlgorithm() = default;
    ~DigitIndicatorLayoutAlgorithm() override = default;

    void OnReset() override {}
    void Measure(LayoutWrapper* layoutWrapper) override;
    void Layout(LayoutWrapper* layoutWrapper) override;

    void SetIsHoverOrPress(bool isHoverOrPress)
    {
        isHoverOrPress_ = isHoverOrPress;
    }

    void SetHoverPoint(const PointF& hoverPoint)
    {
        hoverPoint_ = hoverPoint;
    }

    void SetIsSingle(bool isSingle)
    {
        isSingle_ = isSingle;
    }

private:
    bool isHoverOrPress_ = false;
    bool isSingle_ = false;
    PointF hoverPoint_;
};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_SWIPER_INDICATOR_DIGIT_INDICATOR_LAYOUT_ALGORITHM_H
