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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_SLIDER_SLIDER_LAYOUT_ALGORITHM_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_SLIDER_SLIDER_LAYOUT_ALGORITHM_H

#include "core/components_ng/layout/box_layout_algorithm.h"

namespace OHOS::Ace::NG {

// SliderLayoutAlgorithm acts as the underlying slider layout.
class ACE_EXPORT SliderLayoutAlgorithm : public BoxLayoutAlgorithm {
    DECLARE_ACE_TYPE(SliderLayoutAlgorithm, BoxLayoutAlgorithm);

public:
    //TODO: Put it on theme later
    static constexpr Dimension DEFAULT_SLIDER_HEIGHT_DP = 2.0_vp;
    static constexpr Dimension DEFAULT_PRESS_DIAMETER = 12.0_vp;
    static constexpr Dimension DEFAULT_HOVER_DIAMETER = 10.0_vp;
    static constexpr float DEFAULT_THICKNESS_ENLARGES_BLOCKSIZE_RATIO = 4.0;
    static constexpr Dimension BORDER_BLANK = 14.0_vp;
    static constexpr float EXTREMELY_SMALL_SLIDER_LENGTH = 1.0f;

    SliderLayoutAlgorithm() = default;
    ~SliderLayoutAlgorithm() override = default;

    std::optional<SizeF> MeasureContent(
        const LayoutConstraintF& contentConstraint, LayoutWrapper* layoutWrapper) override;

    float GetTrackThickness() const
    {
        return trackThickness_;
    }
    float GetBlockDiameter() const
    {
        return blockDiameter_;
    }
    float GetBlockHotDiameter() const
    {
        return blockHotDiameter_;
    }

private:
    float trackThickness_ = 0.0f;
    float blockDiameter_ = 0.0f;
    float blockHotDiameter_ = 0.0f;
    ACE_DISALLOW_COPY_AND_MOVE(SliderLayoutAlgorithm);
};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_SLIDER_SLIDER_LAYOUT_ALGORITHM_H