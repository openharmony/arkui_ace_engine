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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_GRID_CONTAINER_PATTERN_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_GRID_CONTAINER_PATTERN_H

#include "../linear_layout/linear_layout_pattern.h"
#include "grid_container_layout_algorithm.h"
#include "grid_container_layout_property.h"

namespace OHOS::Ace::NG {

class GridContainerLayoutPattern : public LinearLayoutPattern {
    DECLARE_ACE_TYPE(GridContainerLayoutPattern, LinearLayoutPattern);

public:
    GridContainerLayoutPattern() : LinearLayoutPattern(true) {}
    ~GridContainerLayoutPattern() override = default;

    RefPtr<LayoutProperty> CreateLayoutProperty() override
    {
        return MakeRefPtr<GridContainerLayoutProperty>();
    }

    RefPtr<LayoutAlgorithm> CreateLayoutAlgorithm() override
    {
        return MakeRefPtr<GridContainerLayoutAlgorithm>();
    }
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_GRID_CONTAINER_PATTERN_H
