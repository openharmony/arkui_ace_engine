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

#include "base/log/ace_trace.h"
#include "base/log/log_wrapper.h"
#include "base/utils/utils.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/custom/custom_measure_layout_node.h"

namespace OHOS::Ace::NG {

void CustomNodeLayoutAlgorithm::Measure(LayoutWrapper* layoutWrapper)
{
    auto host = DynamicCast<CustomMeasureLayoutNode>(layoutWrapper->GetHostNode());
    CHECK_NULL_VOID(host);
    if (renderFunction_ && host) {
        {
            ACE_SCOPED_TRACE("CustomNode:OnAppear");
            host->FireOnAppear();
        }
        {
            ACE_SCOPED_TRACE("CustomNode:BuildItem");
            // first create child node and wrapper.
            auto child = renderFunction_();
            renderFunction_ = nullptr;
            CHECK_NULL_VOID(child);
            buildItem_ = child;
            child->AdjustLayoutWrapperTree(Claim(layoutWrapper), true, true);
        }
    }

    // call js measure
    if (!host->FireOnMeasure(layoutWrapper)) {
        // use normal measure step.
        auto layoutConstraint = layoutWrapper->GetLayoutProperty()->CreateChildConstraint();
        const auto& children = layoutWrapper->GetAllChildrenWithBuild();
        for (auto&& child : children) {
            child->Measure(layoutConstraint);
        }
        BoxLayoutAlgorithm::PerformMeasureSelf(layoutWrapper);
    }
}

void CustomNodeLayoutAlgorithm::Layout(LayoutWrapper* layoutWrapper)
{
    auto host = DynamicCast<CustomMeasureLayoutNode>(layoutWrapper->GetHostNode());
    if (!host->FireOnLayout(layoutWrapper)) {
        PerformLayout(layoutWrapper);
        for (auto&& child : layoutWrapper->GetAllChildrenWithBuild()) {
            child->Layout();
        }
    }
}

} // namespace OHOS::Ace::NG
