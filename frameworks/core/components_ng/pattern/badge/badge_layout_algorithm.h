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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_BADGE_BADGE_LAYOUT_ALGORITHM_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_BADGE_BADGE_LAYOUT_ALGORITHM_H

#include "core/components_ng/layout/layout_algorithm.h"
#include "core/components_ng/layout/layout_wrapper.h"

namespace OHOS::Ace::NG {

class ACE_EXPORT BadgeLayoutAlgorithm : public LayoutAlgorithm {
    DECLARE_ACE_TYPE(BadgeLayoutAlgorithm, LayoutAlgorithm);

public:
    BadgeLayoutAlgorithm() = default;

    ~BadgeLayoutAlgorithm() override = default;

    void OnReset() override {}

    void Measure(LayoutWrapper* layoutWrapper) override;
    void Layout(LayoutWrapper* layoutWrapper) override;

private:
    void PerformMeasureSelf(LayoutWrapper* layoutWrapper);

    inline double GetFontSizeInit(const std::optional<Dimension>& badgeFontSize)
    {
        if (badgeFontSize->Unit() == DimensionUnit::FP) {
            return badgeFontSize->Value();
        } else {
            return badgeFontSize->ConvertToVp();
        }
    }

    inline double GetBadgeSizeInit(const std::optional<Dimension>& badgeCircleSize)
    {
        if (badgeCircleSize->Unit() == DimensionUnit::FP) {
            return badgeCircleSize->Value();
        } else {
            return badgeCircleSize->ConvertToVp();
        }
    }

    bool hasFontSize_ = true;

    ACE_DISALLOW_COPY_AND_MOVE(BadgeLayoutAlgorithm);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_BADGE_BADGE_LAYOUT_ALGORITHM_H
