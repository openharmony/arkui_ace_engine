/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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

#include "core/components_ng/pattern/grid/grid_item_layout_algorithm.h"

#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/grid/grid_item_layout_property.h"

namespace OHOS::Ace::NG {
void GridItemLayoutAlgorithm::Measure(LayoutWrapper* layoutWrapper)
{
    auto props = AceType::DynamicCast<GridItemLayoutProperty>(layoutWrapper->GetLayoutProperty());
    CHECK_NULL_VOID(props);
    auto layoutConstraint = CreateChildConstraint(layoutWrapper);

    for (auto&& child : layoutWrapper->GetAllChildrenWithBuild()) {
        child->Measure(layoutConstraint);
    }
    BoxLayoutAlgorithm::PerformMeasureSelf(layoutWrapper);
}

LayoutConstraintF GridItemLayoutAlgorithm::CreateChildConstraint(LayoutWrapper* layoutWrapper)
{
    auto props = AceType::DynamicCast<GridItemLayoutProperty>(layoutWrapper->GetLayoutProperty());
    auto layoutConstraint = props->CreateChildConstraint();

    if (!props->GetNeedStretch()) {
        if (props->GetStretchChild()) {
            props->SetStretchChild(false);
        }
        return layoutConstraint;
    }

    auto child = layoutWrapper->GetOrCreateChildByIndex(0);
    if (!child) {
        return layoutConstraint;
    }

    auto childLayoutProperty = child->GetLayoutProperty();
    if (!childLayoutProperty) {
        layoutConstraint.selfIdealSize.SetHeight(layoutConstraint.parentIdealSize.Height());
        return layoutConstraint;
    }

    auto childConstraint = childLayoutProperty->GetLayoutConstraint();
    if (props->GetStretchChild() || (!childConstraint->selfIdealSize.MainSize(props->GetAxis()).has_value() &&
        layoutConstraint.parentIdealSize.MainSize(props->GetAxis()).has_value())) {
        layoutConstraint.selfIdealSize.SetMainSize(
            layoutConstraint.parentIdealSize.MainSize(props->GetAxis()), props->GetAxis());
        child->GetHostNode()->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
        props->SetStretchChild(true);
    }
    return layoutConstraint;
}
} // namespace OHOS::Ace::NG
