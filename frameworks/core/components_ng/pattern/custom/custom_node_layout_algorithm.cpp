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

#include "core/components_ng/pattern/custom/custom_node_layout_algorithm.h"

#include "core/components_ng/base/frame_node.h"

namespace OHOS::Ace::NG {

void CustomNodeLayoutAlgorithm::Measure(LayoutWrapper* layoutWrapper)
{
    auto host = layoutWrapper->GetHostNode();
    if (renderFunction_ && host) {
        // first create child node and wrapper.
        auto child = renderFunction_();
        child->MountToParent(host);
        auto childWrapper = child->CreateLayoutWrapperOnCreate();
        layoutWrapper->AddChild(childWrapper);
    }
    // then use normal measure step.
    auto layoutConstraint =
        layoutWrapper->GetLayoutProperty()->GetContentLayoutConstraint().value_or(LayoutConstraintF());
    if (!layoutConstraint.selfIdealSize.has_value()) {
        // custom node deliver parent ideal size to child.
        layoutConstraint.selfIdealSize = layoutConstraint.parentIdealSize;
    }

    for (auto&& child : layoutWrapper->GetChildren()) {
        child->Measure(layoutConstraint);
    }
    BoxLayoutAlgorithm::PerformMeasureSelf(layoutWrapper);
}

} // namespace OHOS::Ace::NG
