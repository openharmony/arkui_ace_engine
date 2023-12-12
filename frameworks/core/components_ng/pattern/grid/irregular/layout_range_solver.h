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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_GRID_LAYOUT_RANGE_SOLVER_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_GRID_LAYOUT_RANGE_SOLVER_H

#include "base/utils/noncopyable.h"
#include "core/components_ng/layout/layout_wrapper.h"
#include "core/components_ng/pattern/grid/grid_layout_info.h"

namespace OHOS::Ace::NG {
class GridLayoutRangeSolver {
public:
    GridLayoutRangeSolver(GridLayoutInfo* info, LayoutWrapper* wrapper);
    ~GridLayoutRangeSolver() = default;

    float FindLayoutRange(float mainGap);

private:
    std::pair<int32_t, float> AddNextRow(float mainGap, int32_t row);

    GridLayoutInfo* info_;
    const LayoutWrapper* wrapper_;
    const GridLayoutOptions* opts_;

    ACE_DISALLOW_COPY_AND_MOVE(GridLayoutRangeSolver);
};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_GRID_LAYOUT_RANGE_SOLVER_H
