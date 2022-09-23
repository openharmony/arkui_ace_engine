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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_GRID_GRID_ADAPTIVE_GRID_ADAPTIVE_LAYOUT_ALGORITHM_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_GRID_GRID_ADAPTIVE_GRID_ADAPTIVE_LAYOUT_ALGORITHM_H

#include "core/components_ng/layout/layout_algorithm.h"
#include "core/components_ng/layout/layout_wrapper.h"
#include "core/components_ng/pattern/grid/grid_layout_info.h"

namespace OHOS::Ace::NG {

class ACE_EXPORT GridAdaptiveLayoutAlgorithm : public LayoutAlgorithm {
    DECLARE_ACE_TYPE(GridAdaptiveLayoutAlgorithm, LayoutAlgorithm);

public:
    GridAdaptiveLayoutAlgorithm(GridLayoutInfo gridLayoutInfo, uint32_t crossCount, uint32_t mainCount)
        : gridLayoutInfo_(std::move(gridLayoutInfo)), crossCount_(crossCount), mainCount_(mainCount) {};
    ~GridAdaptiveLayoutAlgorithm() override = default;

    void Measure(LayoutWrapper* layoutWrapper) override;
    void Layout(LayoutWrapper* layoutWrapper) override;

    GridLayoutInfo GetGridLayoutInfo();

private:
    GridLayoutInfo gridLayoutInfo_;

    uint32_t crossCount_ = 0;
    uint32_t mainCount_ = 0;

    ACE_DISALLOW_COPY_AND_MOVE(GridAdaptiveLayoutAlgorithm);
};

} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_GRID_GRID_ADAPTIVE_GRID_ADAPTIVE_LAYOUT_ALGORITHM_H
