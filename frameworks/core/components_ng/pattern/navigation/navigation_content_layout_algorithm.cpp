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

#include "core/components_ng/pattern/navigation/navigation_content_layout_algorithm.h"

#include "core/components_ng/layout/box_layout_algorithm.h"
#include "core/components_ng/layout/layout_wrapper.h"
#include "core/components_ng/pattern/navrouter/navdestination_layout_algorithm.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace {
constexpr int32_t SIZE_TWO = 2;
} // namespace

namespace OHOS::Ace::NG {

void NavigationContentLayoutAlgorithm::Measure(LayoutWrapper* layoutWrapper)
{
    auto layoutConstraint = layoutWrapper->GetLayoutProperty()->CreateChildConstraint();
    auto childSize = layoutWrapper->GetTotalChildCount();
    std::list<RefPtr<LayoutWrapper>> children;
    if (childSize > 0) {
        auto child = layoutWrapper->GetOrCreateChildByIndex(childSize - 1);
        auto destinationAlgorithm =
            AceType::DynamicCast<NavDestinationLayoutAlgorithm>(child->GetLayoutAlgorithm()->GetLayoutAlgorithm());
        if (destinationAlgorithm->IsOnShown()) {
            // the incoming page in push case
            child->Measure(layoutConstraint);
            children.emplace_back(child);
        }
        // get the second child for animation
        if (childSize > 1) {
            auto child = layoutWrapper->GetOrCreateChildByIndex(childSize - SIZE_TWO);
            auto destinationAlgorithm =
                AceType::DynamicCast<NavDestinationLayoutAlgorithm>(child->GetLayoutAlgorithm()->GetLayoutAlgorithm());
            if (destinationAlgorithm->IsOnShown()) {
                // the incoming page in pop case
                child->Measure(layoutConstraint);
                children.emplace_back(child);
            }
        }
    }
    PerformMeasureSelfWithChildList(layoutWrapper, { children });
}

} // namespace OHOS::Ace::NG
