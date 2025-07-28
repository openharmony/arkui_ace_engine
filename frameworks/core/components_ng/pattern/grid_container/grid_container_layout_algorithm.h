
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_GRID_CONTAINER_GRID_CONTAINER_LAYOUT_ALGORITHM_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_GRID_CONTAINER_GRID_CONTAINER_LAYOUT_ALGORITHM_H

#include "grid_container_layout_property.h"

#include "base/utils/utils.h"
#include "core/components_ng/pattern/linear_layout/linear_layout_algorithm.h"
#include "core/components_ng/property/measure_utils.h"

namespace OHOS::Ace::NG {

class ACE_EXPORT GridContainerLayoutAlgorithm : public LinearLayoutAlgorithm {
    DECLARE_ACE_TYPE(GridContainerLayoutAlgorithm, LinearLayoutAlgorithm);

public:
    GridContainerLayoutAlgorithm() = default;
    ~GridContainerLayoutAlgorithm() override = default;

    void Measure(LayoutWrapper* layoutWrapper) override
    {
        const auto& layoutProperty = layoutWrapper->GetLayoutProperty();
        CHECK_NULL_VOID(layoutProperty);
        const auto& gridContainerLayoutProperty = DynamicCast<GridContainerLayoutProperty>(layoutProperty);
        CHECK_NULL_VOID(gridContainerLayoutProperty);
        auto layoutConstraint = layoutProperty->GetLayoutConstraint().value();
        SizeF idealSize = CreateIdealSize(layoutConstraint, Axis::VERTICAL, MeasureType::MATCH_PARENT_CROSS_AXIS, true);
        gridContainerLayoutProperty->BuildWidth(idealSize.Width());

        OptionalSizeF optSize;
        optSize.SetWidth(idealSize.Width());
        layoutConstraint.UpdateIllegalSelfIdealSizeWithCheck(optSize);
        layoutProperty->UpdateLayoutConstraint(layoutConstraint);

        auto curLayoutProp = layoutWrapper->GetHostNode()->GetLayoutProperty<GridContainerLayoutProperty>();
        curLayoutProp->SetReserveObj(gridContainerLayoutProperty);
        curLayoutProp->UpdateContainerInfo(gridContainerLayoutProperty->GetContainerInfoValue());
        LinearLayoutAlgorithm::Measure(layoutWrapper);
    }
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_GRID_CONTAINER_GRID_CONTAINER_LAYOUT_ALGORITHM_H
