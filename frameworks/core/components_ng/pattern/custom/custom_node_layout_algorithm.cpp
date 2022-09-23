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
#include "core/components_ng/pattern/custom/custom_node.h"

namespace OHOS::Ace::NG {

void CustomNodeLayoutAlgorithm::Measure(LayoutWrapper* layoutWrapper)
{
    LOGD("%s, CustomNodeLayoutAlgorithm::Measure, in", OHOS::Ace::DEVTAG.c_str());
    auto host = DynamicCast<CustomNode>(layoutWrapper->GetHostNode());
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
    // then use normal measure step.
    auto layoutConstraint = layoutWrapper->GetLayoutProperty()->CreateChildConstraint();

    const auto& children = layoutWrapper->GetAllChildrenWithBuild();
    // call js measure
    if (layoutWrapper->GetGeometryNode()->Measure(layoutWrapper)) {
        LOGD("%s, CustomNodeLayoutAlgorithm::Measure, %d", OHOS::Ace::DEVTAG.c_str(), children.size());
    } else {
        LOGD("%s, CustomNodeLayoutAlgorithm::Measure, default measure", OHOS::Ace::DEVTAG.c_str());
        for (auto&& child : children) {
            child->Measure(layoutConstraint);
        }
    }

    BoxLayoutAlgorithm::PerformMeasureSelf(layoutWrapper);
}

void CustomNodeLayoutAlgorithm::Layout(LayoutWrapper* layoutWrapper)
{
    LOGD("%s, CustomNodeLayoutAlgorithm::Layout, %d", OHOS::Ace::DEVTAG.c_str(),
        layoutWrapper->GetAllChildrenWithBuild().size());
    PerformLayout(layoutWrapper);
    if (layoutWrapper->GetGeometryNode()->Layout(layoutWrapper)) {
        LOGD("%s, CustomNodeLayoutAlgorithm::Layout, custom layout", OHOS::Ace::DEVTAG.c_str());
    } else {
        LOGD("%s, CustomNodeLayoutAlgorithm::Layout, default layout", OHOS::Ace::DEVTAG.c_str());
        for (auto&& child : layoutWrapper->GetAllChildrenWithBuild()) {
            child->Layout();
        }
    }
}

} // namespace OHOS::Ace::NG
