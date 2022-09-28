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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_GRID_GRID_LAYOUT_BASE_ALGORITHM_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_GRID_GRID_LAYOUT_BASE_ALGORITHM_H

#include <utility>

#include "core/components_ng/layout/layout_algorithm.h"
#include "core/components_ng/pattern/grid/grid_layout_info.h"

namespace OHOS::Ace::NG {

class ACE_EXPORT GridLayoutBaseAlgorithm : public LayoutAlgorithm {
    DECLARE_ACE_TYPE(GridLayoutBaseAlgorithm, LayoutAlgorithm);

public:
    explicit GridLayoutBaseAlgorithm(GridLayoutInfo gridLayoutInfo) : gridLayoutInfo_(std::move(gridLayoutInfo)) {};
    ~GridLayoutBaseAlgorithm() override = default;

    GridLayoutInfo GetGridLayoutInfo()
    {
        return std::move(gridLayoutInfo_);
    }

protected:
    GridLayoutInfo gridLayoutInfo_;

    ACE_DISALLOW_COPY_AND_MOVE(GridLayoutBaseAlgorithm);
};

} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_GRID_GRID_LAYOUT_BASE_ALGORITHM_H
